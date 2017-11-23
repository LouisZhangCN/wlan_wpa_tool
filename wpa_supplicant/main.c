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
#ifdef __linux__
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
#endif /* __linux__ */
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
    }
}
