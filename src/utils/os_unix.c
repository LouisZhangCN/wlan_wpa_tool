#include "includes.h"

#ifndef WPA_TRACE
void *os_zalloc(size_t size)
{
    return calloc(1, size);
}
#endif /* WPA_TRACE */

#ifdef WPA_TRACE
void *os_malloc(size_t size)
{
    struct os_alloc_trace *a;
    a = malloc(sizeof(*a) + size);
    if (a == NULL)
        return NULL;
}


void * os_zalloc(size_t size)
{
    void *ptr = os_malloc(size);
    if (ptr)
        os_memset(ptr, 0, size);

    return ptr;
}
#endif /* WPA_TRACE */

int os_strcmp(const char *str1, const char *str2)
{
    while (*str1 == *str2) {
        if (*str1 == '\0') {
            break;
        }

        str1++;
        str2++;
    }

    return *str1 - *str2;
}

char *os_strchr(const char *str, int c)
{
    while (*str) {
        if (*str == c)
            return (char *)str;

        str++;
    }

    return NULL;
}
