#ifndef OS_H

/*
 *#ifndef os_strcmp
 *#define os_strcmp(s1, s2) strcmp((s1), (s2))
 *#endif / os_strcmp /
 */

#ifndef os_free
#define os_free(x) free((x))
#endif

#ifndef os_memset
#define osmemset(s, c, n) memset(s, c, n)
#endif

#endif /* OS_H */
