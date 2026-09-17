/* libc.a member reallocr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

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

#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
/* This build of the allocator is configured with MALLOC_ALIGNMENT 16: the ROM's
   request2size adds 0x13 and masks with 0xFFFFFFF0, and its small-request arm
   yields 0x10. */
#define MALLOC_ALIGNMENT 16
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE (sizeof(struct malloc_chunk))
#define chunk2mem(p) ((void *)((char *)(p) + 2 * SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - 2 * SIZE_SZ))
#define request2size(req)                                                                          \
    (((long)((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < (long)(MINSIZE + MALLOC_ALIGN_MASK))         \
         ? ((MINSIZE + MALLOC_ALIGN_MASK) & ~(MALLOC_ALIGN_MASK))                                  \
         : (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define next_chunk(p) ((mchunkptr)(((char *)(p)) + ((p)->size & ~PREV_INUSE)))
#define prev_chunk(p) ((mchunkptr)(((char *)(p)) - ((p)->prev_size)))
#define inuse(p) ((((mchunkptr)(((char *)(p)) + ((p)->size & ~PREV_INUSE)))->size) & PREV_INUSE)
#define prev_inuse(p) ((p)->size & PREV_INUSE)
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size |= PREV_INUSE)
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head_size(p, s) ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define set_head(p, s) ((p)->size = (s))

/* The bin array of the shipped allocator. */
extern mchunkptr __malloc_av_[];

#define bin_at(i) ((mchunkptr)((char *)&(__malloc_av_[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)
#define unlink(P, BK, FD)                                                                          \
    {                                                                                              \
        BK = P->bk;                                                                                \
        FD = P->fd;                                                                                \
        FD->bk = BK;                                                                               \
        BK->fd = FD;                                                                               \
    }
#define long_sub_size_t(x, y) ((x < y) ? -((long)(y - x)) : (x - y));
#define MALLOC_COPY(dest, src, nbytes)                                                             \
    do {                                                                                           \
        INTERNAL_SIZE_T mcsz = (nbytes);                                                           \
        if (mcsz <= 9 * sizeof(mcsz)) {                                                            \
            INTERNAL_SIZE_T *mcsrc = (INTERNAL_SIZE_T *)(src);                                     \
            INTERNAL_SIZE_T *mcdst = (INTERNAL_SIZE_T *)(dest);                                    \
            if (mcsz >= 5 * sizeof(mcsz)) {                                                        \
                *mcdst++ = *mcsrc++;                                                               \
                *mcdst++ = *mcsrc++;                                                               \
                if (mcsz >= 7 * sizeof(mcsz)) {                                                    \
                    *mcdst++ = *mcsrc++;                                                           \
                    *mcdst++ = *mcsrc++;                                                           \
                    if (mcsz >= 9 * sizeof(mcsz)) {                                                \
                        *mcdst++ = *mcsrc++;                                                       \
                        *mcdst++ = *mcsrc++;                                                       \
                    }                                                                              \
                }                                                                                  \
            }                                                                                      \
            *mcdst++ = *mcsrc++;                                                                   \
            *mcdst++ = *mcsrc++;                                                                   \
            *mcdst = *mcsrc;                                                                       \
        } else                                                                                     \
            memcpy(dest, src, mcsz);                                                               \
    } while (0)

extern void __malloc_lock(void *r);
extern void __malloc_unlock(void *r);
extern void *_malloc_r(void *r, unsigned int bytes);
extern void _free_r(void *r, void *mem);

void *_realloc_r(void *reent_ptr, void *oldmem, unsigned int bytes)
{
    INTERNAL_SIZE_T nb;

    mchunkptr oldp;
    INTERNAL_SIZE_T oldsize;

    mchunkptr newp;
    INTERNAL_SIZE_T newsize;
    void *newmem;

    mchunkptr next;
    INTERNAL_SIZE_T nextsize;

    mchunkptr prev;
    INTERNAL_SIZE_T prevsize;

    mchunkptr remainder;
    INTERNAL_SIZE_T remainder_size;

    mchunkptr bck;
    mchunkptr fwd;

    if (oldmem == 0)
        return _malloc_r(reent_ptr, bytes);

    __malloc_lock(reent_ptr);

    newp = oldp = mem2chunk(oldmem);
    newsize = oldsize = chunksize(oldp);

    nb = request2size(bytes);

    if ((long)(oldsize) < (long)(nb)) {
        next = chunk_at_offset(oldp, oldsize);
        if (next == top || !inuse(next)) {
            nextsize = chunksize(next);

            if (next == top) {
                if ((long)(nextsize + newsize) >= (long)(nb + MINSIZE)) {
                    newsize += nextsize;
                    top = chunk_at_offset(oldp, nb);
                    set_head(top, (newsize - nb) | PREV_INUSE);
                    set_head_size(oldp, nb);
                    __malloc_unlock(reent_ptr);
                    return chunk2mem(oldp);
                }
            }

            else if (((long)(nextsize + newsize) >= (long)(nb))) {
                unlink(next, bck, fwd);
                newsize += nextsize;
                goto split;
            }
        } else {
            next = 0;
            nextsize = 0;
        }

        if (!prev_inuse(oldp)) {
            prev = prev_chunk(oldp);
            prevsize = chunksize(prev);

            if (next != 0) {
                if (next == top) {
                    if ((long)(nextsize + prevsize + newsize) >= (long)(nb + MINSIZE)) {
                        unlink(prev, bck, fwd);
                        newp = prev;
                        newsize += prevsize + nextsize;
                        newmem = chunk2mem(newp);
                        MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
                        top = chunk_at_offset(newp, nb);
                        set_head(top, (newsize - nb) | PREV_INUSE);
                        set_head_size(newp, nb);
                        __malloc_unlock(reent_ptr);
                        return newmem;
                    }
                }

                else if (((long)(nextsize + prevsize + newsize) >= (long)(nb))) {
                    unlink(next, bck, fwd);
                    unlink(prev, bck, fwd);
                    newp = prev;
                    newsize += nextsize + prevsize;
                    newmem = chunk2mem(newp);
                    MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
                    goto split;
                }
            }

            if (prev != 0 && (long)(prevsize + newsize) >= (long)nb) {
                unlink(prev, bck, fwd);
                newp = prev;
                newsize += prevsize;
                newmem = chunk2mem(newp);
                MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
                goto split;
            }
        }

        newmem = _malloc_r(reent_ptr, bytes);

        if (newmem == 0) {
            __malloc_unlock(reent_ptr);
            return 0;
        }

        if ((newp = mem2chunk(newmem)) == next_chunk(oldp)) {
            newsize += chunksize(newp);
            newp = oldp;
            goto split;
        }

        MALLOC_COPY(newmem, oldmem, oldsize - SIZE_SZ);
        _free_r(reent_ptr, oldmem);
        __malloc_unlock(reent_ptr);
        return newmem;
    }

split:

    remainder_size = long_sub_size_t(newsize, nb);

    if (remainder_size >= (long)MINSIZE) {
        remainder = chunk_at_offset(newp, nb);
        set_head_size(newp, nb);
        set_head(remainder, remainder_size | PREV_INUSE);
        set_inuse_bit_at_offset(remainder, remainder_size);
        _free_r(reent_ptr, chunk2mem(remainder));
    } else {
        set_head_size(newp, newsize);
        set_inuse_bit_at_offset(newp, newsize);
    }

    __malloc_unlock(reent_ptr);
    return chunk2mem(newp);
}
