/* libc.a member callocr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

typedef unsigned int INTERNAL_SIZE_T;

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
};

typedef struct malloc_chunk *mchunkptr;

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

extern void *_malloc_r(void *rptr, unsigned int nbytes);
extern void *memset(void *dst, int c, unsigned int n);

void *_calloc_r(void *rptr, unsigned int n, unsigned int elem_size)
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
