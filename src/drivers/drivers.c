struct wpa_driver_ops *wpa_drivers[] =
{
    //TODO: CONFIG_DRIVER_NL80211, ...
#ifdef CONFIG_DRIVER_TEST
    &wpa_driver_test_ops, //TODO: implement
#endif /* CONFIG_DRIVER_TEST */
    NULL
};
