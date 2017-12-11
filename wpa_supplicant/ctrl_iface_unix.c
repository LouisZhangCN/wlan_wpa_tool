#include "wpa_supplicant_i.h"


struct ctrl_iface_global_priv {
    struct wpa_global *global;
    int sock;
};


static int wpas_global_ctrl_iface_open_sock(struct wpa_global *global, \
                                            struct ctrl_iface_global_priv *priv)
{
    struct sockaddr_un addr;
    const char *ctrl = global->params.ctrl_interface;
    int flags;

    wpa_printf(MSG_DEBUG, "Global control interface '%s'", ctrl);

    priv->sock = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (priv->sock < 0) {
        wpa_printf(MSG_ERROR, "socket(PF_UNIX): %s", strerror(errno));
        goto fail;
    }

    os_memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;

    if (os_strncmp(ctrl, "@abstract:", 10) == 0) {
        addr.sun_path[0] = '\0';
        os_strlcpy(addr.sun_path + 1, ctrl + 10, sizeof(addr.sun_path) - 1);

        if (bind(priv->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            wpa_printf(MSG_ERROR, "supp-global-ctrl-iface-init: "\
                    "bind(PF_UNIX;%s) failed: %s", ctrl, strerror(errno));
            goto fail;
        }
        wpa_printf(MSG_DEBUG, "Using Abstract control socket '%s'", ctrl + 10);
        goto havesock;
    }

    os_strlcpy(addr.sun_path, ctrl, sizeof(addr.sun_path));
    if (bind(priv->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        //TODO bind error handle
    }

    wpa_printf(MSG_DEBUG, "Using UNIX control socket '%s'", ctrl);

    if (global->params.ctrl_interface_group) {
        char *gid_str = global->params.ctrl_interface_group;
        gid_t gid = 0;
        struct group *grp;
        char *endp;

        grp = getgrnam(gid_str);
        if (grp) {
            gid = grp->gr_gid;
            wpa_printf(MSG_DEBUG, "ctrl_interface_group=%d (from group name '%s'", (int)gid, gid_str);
        } else {
            /* Group name not found - try to parse this as gid */
            //TODO not fond group name, error handle
        }

        if (chown(ctrl, -1, gid) < 0) {
            //TODO error handle
        }

        if (chmod(ctrl, S_IRWXU | S_IRWXG) < 0) {
            //TODO error handle
        }
    } else {
        chmod (ctrl, S_IRWXU);
    }

have_sock:
    /*
     * Make socket non-blocking so that we don't hang forever if
     * target dies unexpectedly.
     */
    flags = fcntl(priv->sock, F_GETFL);
    if (flags >= 0) {
        flags |= O_NONBLOCK;
        if (fcntl(priv->sock, F_SETFL, flags) < 0) {
            //TODO error handle
        }
    }

    eloop_register_read_sock(priv->sock, \
            wpa_supplicant_global_ctrl_iface_receive,
            global, priv);

    return 0;

fail:
    if (priv->sock >= 0) {
        close(priv->sock);
        priv->sock = -1;
    }

    return -1;
}


struct ctrl_iface_global_priv *wpa_supplicant_global_ctrl_iface_init(struct wpa_global *global)
{
    struct ctrl_iface_global_priv *priv;

    priv = os_zalloc(sizeof(*priv));
    if (priv == NULL) {
        return NULL;
    }
    priv->global = global;
    priv->sock = -1;

    if (global->params.ctrl_interface == NULL)
        return priv;

    if (wpas_global_ctrl_iface_open_sock(global, priv) < 0) {
        os_free(priv);
        return NULL;
    }

    wpa_msg_register_cb(wpa_supplicant_ctrl_iface_msg_cb);
}
