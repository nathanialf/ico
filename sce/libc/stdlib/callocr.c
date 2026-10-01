/* libc.a member callocr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <string.h>
#include <reent.h>
#include <stdlib.h>
#include <libc_internal.h>

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - 2 * SIZE_SZ))
#define SIZE_BITS 0x3
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define MALLOC_ZERO(charp, nbytes)                                                                 \
    do {                                                                                           \
        INTERNAL_SIZE_T mzsz = (nbytes);                                                           \
        if (mzsz <= 9 * sizeof(mzsz)) {                                                            \
            INTERNAL_SIZE_T *mz = (INTERNAL_SIZE_T *)(charp);                                      \
            if (mzsz >= 5 * sizeof(mzsz)) {                                                        \
                *mz++ = 0;                                                                         \
                *mz++ = 0;                                                                         \
                if (mzsz >= 7 * sizeof(mzsz)) {                                                    \
                    *mz++ = 0;                                                                     \
                    *mz++ = 0;                                                                     \
                    if (mzsz >= 9 * sizeof(mzsz)) {                                                \
                        *mz++ = 0;                                                                 \
                        *mz++ = 0;                                                                 \
                    }                                                                              \
                }                                                                                  \
            }                                                                                      \
            *mz++ = 0;                                                                             \
            *mz++ = 0;                                                                             \
            *mz = 0;                                                                               \
        } else                                                                                     \
            memset((charp), 0, mzsz);                                                              \
    } while (0)

void *_calloc_r(Reent *rptr, unsigned int n, unsigned int elem_size)
{
    mchunkptr p;
    INTERNAL_SIZE_T csz;
    INTERNAL_SIZE_T sz = n * elem_size;
    void *mem = _malloc_r(rptr, sz);

    if (mem == 0) {
        return 0;
    } else {
        p = mem2chunk(mem);
        csz = chunksize(p);
        MALLOC_ZERO(mem, csz - SIZE_SZ);
        return mem;
    }
}
