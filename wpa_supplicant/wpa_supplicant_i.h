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
