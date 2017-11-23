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
}
