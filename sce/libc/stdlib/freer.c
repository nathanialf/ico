/* libc.a member freer.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <libc_internal.h>
#include <string.h>
#include <reent.h>

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define MINSIZE 16
#define malloc_getpagesize (4096)
#define MAX_SMALLBIN_SIZE 512
#define BINBLOCKWIDTH 4
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - 2 * SIZE_SZ))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define inuse_bit_at_offset(p, s) (((mchunkptr)((char *)(p) + (s)))->size & PREV_INUSE)

/* The bin array of the shipped allocator (mallocr.o owns it; MAIN.MAP map
   line 6262 names it __malloc_av_). */

#define bin_at(i) ((mchunkptr)((char *)&(__malloc_av_[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)
#define last_remainder (bin_at(1))
#define binblocks (bin_at(0)->size)
#define smallbin_index(sz) ((sz) >> 3)
#define bin_index(sz)                                                                              \
    ((((sz) >> 9) == 0)      ? ((sz) >> 3)                                                         \
     : (((sz) >> 9) <= 4)    ? 56 + ((sz) >> 6)                                                    \
     : (((sz) >> 9) <= 20)   ? 91 + ((sz) >> 9)                                                    \
     : (((sz) >> 9) <= 84)   ? 110 + ((sz) >> 12)                                                  \
     : (((sz) >> 9) <= 340)  ? 119 + ((sz) >> 15)                                                  \
     : (((sz) >> 9) <= 1364) ? 124 + ((sz) >> 18)                                                  \
                             : 126)
#define idx2binblock(ix) ((unsigned long)1 << ((ix) / BINBLOCKWIDTH))
#define mark_binblock(ii) (binblocks |= idx2binblock(ii))
#define unlink(P, BK, FD)                                                                          \
    {                                                                                              \
        BK = P->bk;                                                                                \
        FD = P->fd;                                                                                \
        FD->bk = BK;                                                                               \
        BK->fd = FD;                                                                               \
    }
#define link_last_remainder(P)                                                                     \
    {                                                                                              \
        last_remainder->fd = last_remainder->bk = P;                                               \
        P->fd = P->bk = last_remainder;                                                            \
    }
#define frontlink(P, S, IDX, BK, FD)                                                               \
    {                                                                                              \
        if (S < MAX_SMALLBIN_SIZE) {                                                               \
            IDX = smallbin_index(S);                                                               \
            mark_binblock(IDX);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        } else {                                                                                   \
            IDX = bin_index(S);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            if (FD == BK) {                                                                        \
                mark_binblock(IDX);                                                                \
            } else {                                                                               \
                while (FD != BK && S < chunksize(FD))                                              \
                    FD = FD->fd;                                                                   \
                BK = FD->bk;                                                                       \
            }                                                                                      \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        }                                                                                          \
    }

void _free_r(Reent *self, void *mem)
{
    mchunkptr p;
    INTERNAL_SIZE_T hd;
    INTERNAL_SIZE_T sz;
    int idx;
    mchunkptr next;
    INTERNAL_SIZE_T nextsz;
    INTERNAL_SIZE_T prevsz;
    mchunkptr bck;
    mchunkptr fwd;
    int islr;

    if (mem == 0) {
        return;
    }

    __malloc_lock(self);
    p = mem2chunk(mem);
    hd = p->size;

    sz = hd & ~PREV_INUSE;
    next = chunk_at_offset(p, sz);
    nextsz = chunksize(next);

    if (next == top) {
        sz += nextsz;

        if (!(hd & PREV_INUSE)) {
            prevsz = p->prev_size;
            p = chunk_at_offset(p, -((long)prevsz));
            sz += prevsz;
            unlink(p, bck, fwd);
        }

        set_head(p, sz | PREV_INUSE);
        top = p;
        if ((unsigned long)(sz) >= (unsigned long)__malloc_trim_threshold) {
            _malloc_trim_r(self, __malloc_top_pad);
        }
        __malloc_unlock(self);
        return;
    }

    set_head(next, nextsz);

    islr = 0;

    if (!(hd & PREV_INUSE)) {
        prevsz = p->prev_size;
        p = chunk_at_offset(p, -((long)prevsz));
        sz += prevsz;

        if (p->fd == last_remainder) {
            islr = 1;
        } else {
            unlink(p, bck, fwd);
        }
    }

    if (!(inuse_bit_at_offset(next, nextsz))) {
        sz += nextsz;

        if (!islr && next->fd == last_remainder) {
            islr = 1;
            link_last_remainder(p);
        } else {
            unlink(next, bck, fwd);
        }
    }

    set_head(p, sz | PREV_INUSE);
    set_foot(p, sz);
    if (!islr) {
        frontlink(p, sz, idx, bck, fwd);
    }

    __malloc_unlock(self);
}

int _malloc_trim_r(Reent *reent_ptr, unsigned int pad)
{
    long top_size;     /* Amount of top-most memory */
    long extra;        /* Amount to release */
    char *current_brk; /* address returned by pre-check sbrk call */
    char *new_brk;     /* address returned by negative sbrk call */
    unsigned long pagesz = malloc_getpagesize;

    __malloc_lock(reent_ptr);
    top_size = chunksize(top);
    extra = ((top_size - pad - MINSIZE + (pagesz - 1)) / pagesz - 1) * pagesz;

    if (extra < (long)pagesz) { /* Not enough memory to release */
        __malloc_unlock(reent_ptr);
        return 0;
    } else {
        /* Test to make sure no one else called sbrk */
        current_brk = (char *)(_sbrk_r(reent_ptr, 0));
        if (current_brk != (char *)(top) + top_size) {
            __malloc_unlock(reent_ptr);
            return 0;
        } else {
            new_brk = (char *)(_sbrk_r(reent_ptr, -extra));
            if (new_brk == (char *)(-1)) { /* sbrk failed? */
                /* Try to figure out what we have */
                current_brk = (char *)(_sbrk_r(reent_ptr, 0));
                top_size = current_brk - (char *)top;
                if (top_size >= (long)MINSIZE) { /* if not, we are very very dead! */
                    __malloc_current_mallinfo.arena = current_brk - __malloc_sbrk_base;
                    set_head(top, top_size | PREV_INUSE);
                }
                __malloc_unlock(reent_ptr);
                return 0;
            } else {
                /* Success. Adjust top accordingly. */
                set_head(top, (top_size - extra) | PREV_INUSE);
                __malloc_current_mallinfo.arena -= extra;
                __malloc_unlock(reent_ptr);
                return 1;
            }
        }
    }
}
