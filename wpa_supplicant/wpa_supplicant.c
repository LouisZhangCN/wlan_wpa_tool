const char *wpa_supplicant_version =
"wpa_supplicant v" VERSION_STR "\n"
"Copyright (c) 2003-2014, Louis Zhang <louis.zhang@126.com> and contributors";

const char *wpa_supplicant_license =
"This software may be distributed under the terms of the BSD license.\n"
"See README for more details.\n"
//TODO:for EAP_TLS_OPENSSL
;

static wpa_global *wpa_supplicant_init(struct wpa_params *params)
{
    struct wpa_global *global;
    int ret, i;

    if (params == NULL)
        return NULL;

#ifdef CONFIG_DRIVER_NDIS
    {
        void driver_ndis_init_ops(void);
        driver_ndis_init_ops(); //TODO
    }
#endif

    ret = eap_register_methods(); //TODO
    if (ret) {
        wpa_printf(MSG_ERROR, "Failed to register EAP methods");
        if (ret == -2)
            wpa_printf(MSG_ERROR, "Two or more EAP methods used the same EAP type.");

        return NULL;
    }

    global = os_zalloc(sizeof(struct wpa_global));
    if (global == NULL)
        return NULL;

    // TODO init the global structure
    if (eloop_init()) {
        wpa_printf(MSG_ERROR, "Failed to initialize event loop");
        wpa_supplicant_deinit(global);
        return NULL;
    }

    random_init(params->entropy_file);
}
