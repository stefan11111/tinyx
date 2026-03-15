#ifndef TINYX_COMPAT_H
#define TINYX_COMPAT_H

#include <stddef.h>
#include <stdlib.h>

#ifndef HAVE_REALLOCARRAY
static inline void *tinyx_reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (size != 0 && nmemb > ((size_t)-1) / size)
        return NULL;
    return realloc(ptr, nmemb * size);
}
#define reallocarray tinyx_reallocarray
#endif

#endif
