/**
 * struct wpa_params - Parameters for wpa_supplicant_init()
 */
struct wpa_params {
    /**
     * daemonize - Run %wpa_supplicant in the backgound
     */
    int daemonize;

    /**
     * wpa_debug_level - Debugging verbosity level (e.g.,  MSG_INFO)
     */
    int wpa_debug_level;
    // TODO: finish members left.
};


/*
 * struct wpa_interface - Parameters for wpa_supplicant_add_iface()
 */
struct wpa_interface {

    /*
     * bridge_ifname - Optional bridge interface name
     *
     * If the driver interface (ifname) is included in a Linux bridge
     * devices, the bridge interface may need to be used for receiving EAPOL
     * frames. This can be enabled by setting this variable to enable
     * receiving of EAPOL frames from an additional interface.
     */
    const char *bridge_ifname;
};
