/*
 * struct wpa_driver_ops - Driver interface API definition
 *
 * This structure defines the API that each driver interface needs to implement
 * for core wpa_supplicant code. All driver specific functionality is captured
 * in this wrapper.
 */
struct wpa_driver_ops {
    /* Name of the driver interface */
    const char *name;
    /* One line description of the driver interface */
    const char *desc;
    //TODO: implement
};
