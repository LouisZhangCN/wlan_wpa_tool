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
