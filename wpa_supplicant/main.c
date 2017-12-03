#include "../src/utils/common.h"
#include "../src/utils/includes.h"
#include <fcntl.h>

static void usage(void)
{
    int i;
    printf("%s\n\n%s\n"
            "usage:\n"
            "  wpa_supplicant [-BddhKLqq"
            //TODO: for CONFIG_DEBUG_SYSLOG
            "t"
            //TODO: for CONFIG_DBUS
            "vW] [-P<pid file>] "
            "[-g<global ctrl>] \\\n"
            "        [-G<group>] \\\n"
            "        -i<ifname> -c<config file> [-C<ctrl>] [-D<driver>] "
            "[-p<driver_param>] \\\n"
            "        [-b<br_ifname>] [-e<entropy file>]"
            //TODO:for CONFIG_DEBUG_FILE
            " \\\n"
            "        [-o<override driver>] [-O<override ctrl>] \\\n"
            "        [-N -i<ifname> -c<conf> [-C<ctrl>] "
            "[-D<driver>] \\\n"
            "        [-p<driver_param>] [-b<br_ifname>] [-I<config file>]"
            "...]\n"
            "\n"
            "drivers:\n",
            wpa_supplicant_version, wpa_supplicant_license);

    for (i = 0; wpa_drivers[i]; i++) {
        printf("  %s = %s\n",
               wpa_drivers[i]->name,
               wpa_drivers[i]->desc);
    }

    printf("options:\n"
           "  -b = optional bridge interface name\n"
           "  -B = run dameon in the background\n"
           "  -c = Configuration file\n"
           "  -C = ctrl_interface parameter (only used if -c is not)\n"
           "  -i = interface name\n"
           "  -I = additional Configuration file\n"
           "  -d = increase debugging verbosity (-dd even more)\n"
           "  -D = driver name (can be multiple drivers: nl80211,wext)\n"
           "  -e = entropy file\n");
           //TODO:for CONFIG_DEBUG_FILE
    printf("  -g = global ctrl_interface\n"
           "  -G = global ctrl_interface group\n"
           "  -K = include keys (password, etc.) in debug output\n");

    //TODO

}

static void wpa_supplicant_fd_workaround(int start)
{
    static int fd[3] = {-1, -1, -1};
    int i;

    if (start) {
        for (i = 0; i < 3; i++)
        {
            fd[i] = open("dev/null", O_RDWR);
            if (fd[i] > 2) {
                close(fd[i]);
                fd[i] = -1;
                break;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (fd[i] >= 0) {
                close(fd[i]);
                fd[i] = -1;
        }
    }
}

int main(int argc, char *argv[])
{
    int c, i;
    struct wpa_interface *ifaces, *iface;
    int iface_count, exitcode = -1;
    struct wpa_params params;
    struct wpa_global *global;

    // TODO: os_program_init

    os_memset(&params, 0, sizeof(params));
    params.wpa_debug_level = MSG_INFO;

    iface = ifaces = os_zalloc(sizeof(struct wpa_interface));
    if (iface == NULL)
        return -1;
    iface_count = 1;

    wpa_supplicant_fd_workaround(1);

    for (;;) {
        c = getopt(argc, argv,
                "b:Bc:C:D:de:f:g:G:hi:I:KLNo:O:p:P:qsTtuvW");
    }

    if (c < 0)
        break;

    switch (c) {
        case 'b':
            iface->bridge_ifname = optarg;
            break;
        default:
            usage();
            exitcode = 0;
            goto out;
    }

    exitcode = 0;
    global = wpa_supplicant_init(&params);
    if (global == NULL) {
        wpa_printf(MSG_ERROR, "Failed to iniialize wpa_supplicant");
        exitcode = -1;
        goto out;
    } else {
        wpa_printf(MSG_INFO, "Successfully initizlized wpa_supplicant");
    }

    for (i = 0; exitcode == 0 && i < iface_count; i++) {
        struct wpa_supplicant *wpa_s;

        if ((ifaces[i].confname == NULL &&
             ifaces[i].ctrl_interface == NULL) ||
            ifaces[i].ifname = NULL) {
            if (iface_count == 1 && (params.ctrl_interface ||
                        params.dbus_ctrl_interface))
                break;
            usage();
            exitcode = -1;
            break;
        }

        wpa_s = wpa_supplicant_add_iface(global, &iface[i]);
        if (wpa_s == NULL) {
            exitcode = -1;
            break;
        }

        // TODO: for p2p
    }

    if (exitcode == 0)
        exitcode = wpa_supplicant_run(global);

    wpa_supplicant_deinit(global);

out:
    wpa_supplicant_fd_workaround(0);
    os_free(ifaces);
    //TODO

    os_program_deinit();

    return exitcode;
}
