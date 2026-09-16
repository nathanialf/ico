/* libc.a member mallocr.o.  MAIN.MAP member spans tile this run exactly and
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
extern void *_malloc_r(void *a0, int a1);

typedef unsigned int INTERNAL_SIZE_T;

#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))

struct malloc_chunk {
    INTERNAL_SIZE_T prev_size;
    INTERNAL_SIZE_T size;
    struct malloc_chunk *fd;
    struct malloc_chunk *bk;
};

typedef struct malloc_chunk *mchunkptr;

typedef struct malloc_chunk *mbinptr;

#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
/* MALLOC_ALIGNMENT 16 in this build: request2size adds 0x13 and masks 0xFFFFFFF0. */
#define MALLOC_ALIGNMENT 16
#define MALLOC_ALIGN 16
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE (sizeof(struct malloc_chunk))
#define chunk2mem(p) ((void *)((char *)(p) + 2 * SIZE_SZ))
#define request2size(req)                                                                          \
    (((long)((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < (long)(MINSIZE + MALLOC_ALIGN_MASK))         \
         ? ((MINSIZE + MALLOC_ALIGN_MASK) & ~(MALLOC_ALIGN_MASK))                                  \
         : (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size |= PREV_INUSE)
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head_size(p, s) ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))

/* The bin array of the shipped allocator. */
extern mchunkptr D_0054CEC8[];

#define av_ D_0054CEC8
#define NAV 128
#define bin_at(i) ((mbinptr)((char *)&(av_[2 * (i) + 2]) - 2 * SIZE_SZ))
#define next_bin(b) ((mbinptr)((char *)(b) + 2 * sizeof(mbinptr)))
#define prev_bin(b) ((mbinptr)((char *)(b) - 2 * sizeof(mbinptr)))
#define top (bin_at(0)->fd)
#define last_remainder (bin_at(1))
#define initial_top ((mchunkptr)(bin_at(0)))
#define first(b) ((b)->fd)
#define last(b) ((b)->bk)
#define MAX_SMALLBIN_SIZE 512
#define SMALLBIN_WIDTH 8
#define SMALLBIN_WIDTH_BITS 3
#define MAX_SMALLBIN ((MAX_SMALLBIN_SIZE / SMALLBIN_WIDTH) - 1)
#define smallbin_index(sz) (((unsigned long)(sz)) >> SMALLBIN_WIDTH_BITS)
#define is_small_request(nb) (nb < MAX_SMALLBIN_SIZE - SMALLBIN_WIDTH)
#define bin_index(sz)                                                                              \
    ((((sz) >> 9) == 0)      ? ((sz) >> 3)                                                         \
     : (((sz) >> 9) <= 4)    ? 56 + ((sz) >> 6)                                                    \
     : (((sz) >> 9) <= 20)   ? 91 + ((sz) >> 9)                                                    \
     : (((sz) >> 9) <= 84)   ? 110 + ((sz) >> 12)                                                  \
     : (((sz) >> 9) <= 340)  ? 119 + ((sz) >> 15)                                                  \
     : (((sz) >> 9) <= 1364) ? 124 + ((sz) >> 18)                                                  \
                             : 126)
#define BINBLOCKWIDTH 4
#define binblocks (bin_at(0)->size)
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
#define clear_last_remainder (last_remainder->fd = last_remainder->bk = last_remainder)
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
/* SIZE_T_SMALLER_THAN_LONG: long is 64-bit here and size_t is 32-bit, so the
   member uses mallocr.c's guarded form, which the ROM's branchy sequence
   (sltu, subu both ways, zero-extend, dsubu) shows verbatim. */
#define long_sub_size_t(x, y) ((x < y) ? -((long)(y - x)) : (x - y));

/* The allocator's own file statics, which live in the shipped data blob. */
/* Spelled as arrays so the references are not gp-relative, as in the shipped
   member: at -G 8 a plain 8-byte extern would be small-data addressed. */
extern unsigned long D_0054D2D8[]; /* top_pad */
extern char *D_0054D2E0[];         /* sbrk_base */
extern unsigned long D_0054D2E8[]; /* max_sbrked_mem */
extern unsigned long D_0054D2F0[]; /* max_total_mem */
extern int D_0054D2F8[]; /* current_mallinfo.arena, i.e. sbrked_mem (struct mallinfo is ints) */

#define top_pad D_0054D2D8[0]
#define sbrk_base D_0054D2E0[0]
#define max_sbrked_mem D_0054D2E8[0]
#define max_total_mem D_0054D2F0[0]
#define sbrked_mem D_0054D2F8[0]
#define malloc_getpagesize (4096)
#define POINTER_UINT unsigned int
#define MORECORE(size) _sbrk_r(reent_ptr, (size))
#define MORECORE_FAILURE -1

extern char *_sbrk_r(void *r, int size);
extern void __malloc_lock(void *r);
extern void __malloc_unlock(void *r);
extern void _free_r(void *r, void *mem);

static void malloc_extend_top(void *reent_ptr, INTERNAL_SIZE_T nb)
{
    char *brk;
    INTERNAL_SIZE_T front_misalign;
    INTERNAL_SIZE_T correction;
    char *new_brk;
    INTERNAL_SIZE_T top_size;

    mchunkptr old_top = top;
    INTERNAL_SIZE_T old_top_size = chunksize(old_top);
    char *old_end = (char *)(chunk_at_offset(old_top, old_top_size));

    INTERNAL_SIZE_T sbrk_size = nb + top_pad + MINSIZE;
    unsigned long pagesz = malloc_getpagesize;

    if (sbrk_base != (char *)(-1))
        sbrk_size = (sbrk_size + (pagesz - 1)) & ~(pagesz - 1);

    brk = (char *)(MORECORE(sbrk_size));

    if (brk == (char *)(MORECORE_FAILURE) || (brk < old_end && old_top != initial_top))
        return;

    sbrked_mem += sbrk_size;

    if (brk == old_end) {
        top_size = sbrk_size + old_top_size;
        set_head(top, top_size | PREV_INUSE);
    } else {
        if (sbrk_base == (char *)(-1))
            sbrk_base = brk;
        else
            sbrked_mem += brk - (char *)old_end;

        front_misalign = (POINTER_UINT)chunk2mem(brk) & MALLOC_ALIGN_MASK;
        if (front_misalign > 0) {
            correction = (MALLOC_ALIGNMENT)-front_misalign;
            brk += correction;
        } else
            correction = 0;

        correction += pagesz - ((POINTER_UINT)(brk + sbrk_size) & (pagesz - 1));

        new_brk = (char *)(MORECORE(correction));
        if (new_brk == (char *)(MORECORE_FAILURE))
            return;

        sbrked_mem += correction;

        top = (mchunkptr)brk;
        top_size = new_brk - brk + correction;
        set_head(top, top_size | PREV_INUSE);

        if (old_top != initial_top) {
            if (old_top_size < MINSIZE) {
                set_head(top, PREV_INUSE);
                return;
            }

            old_top_size = (old_top_size - 3 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
            set_head_size(old_top, old_top_size);
            chunk_at_offset(old_top, old_top_size)->size = SIZE_SZ | PREV_INUSE;
            chunk_at_offset(old_top, old_top_size + SIZE_SZ)->size = SIZE_SZ | PREV_INUSE;
            if (old_top_size >= MINSIZE)
                _free_r(reent_ptr, chunk2mem(old_top));
        }
    }

    if ((unsigned long)sbrked_mem > (unsigned long)max_sbrked_mem)
        max_sbrked_mem = sbrked_mem;
    if ((unsigned long)(sbrked_mem) > (unsigned long)max_total_mem)
        max_total_mem = sbrked_mem;
}

void *_malloc_r(void *reent_ptr, int bytes)
{
    mchunkptr victim;
    INTERNAL_SIZE_T victim_size;
    int idx;
    mbinptr bin;
    mchunkptr remainder;
    long remainder_size;
    int remainder_index;
    unsigned long block;
    int startidx;
    mchunkptr fwd;
    mchunkptr bck;
    mbinptr q;

    INTERNAL_SIZE_T nb = request2size(bytes);

    __malloc_lock(reent_ptr);

    if (is_small_request(nb)) {
        idx = smallbin_index(nb);

        q = bin_at(idx);
        victim = last(q);

        if (victim != q) {
            victim_size = chunksize(victim);
            unlink(victim, bck, fwd);
            set_inuse_bit_at_offset(victim, victim_size);
            __malloc_unlock(reent_ptr);
            return chunk2mem(victim);
        }

        idx += 2;

    } else {
        idx = bin_index(nb);
        bin = bin_at(idx);

        for (victim = last(bin); victim != bin; victim = victim->bk) {
            victim_size = chunksize(victim);
            remainder_size = long_sub_size_t(victim_size, nb);

            if (remainder_size >= (long)MINSIZE) {
                --idx;
                break;
            }

            else if (remainder_size >= 0) {
                unlink(victim, bck, fwd);
                set_inuse_bit_at_offset(victim, victim_size);
                __malloc_unlock(reent_ptr);
                return chunk2mem(victim);
            }
        }

        ++idx;
    }

    if ((victim = last_remainder->fd) != last_remainder) {
        victim_size = chunksize(victim);
        remainder_size = long_sub_size_t(victim_size, nb);

        if (remainder_size >= (long)MINSIZE) {
            remainder = chunk_at_offset(victim, nb);
            set_head(victim, nb | PREV_INUSE);
            link_last_remainder(remainder);
            set_head(remainder, remainder_size | PREV_INUSE);
            set_foot(remainder, remainder_size);
            __malloc_unlock(reent_ptr);
            return chunk2mem(victim);
        }

        clear_last_remainder;

        if (remainder_size >= 0) {
            set_inuse_bit_at_offset(victim, victim_size);
            __malloc_unlock(reent_ptr);
            return chunk2mem(victim);
        }

        frontlink(victim, victim_size, remainder_index, bck, fwd);
    }

    if ((block = idx2binblock(idx)) <= binblocks) {
        if ((block & binblocks) == 0) {
            idx = (idx & ~(BINBLOCKWIDTH - 1)) + BINBLOCKWIDTH;
            block <<= 1;
            while ((block & binblocks) == 0) {
                idx += BINBLOCKWIDTH;
                block <<= 1;
            }
        }

        for (;;) {
            startidx = idx;
            q = bin = bin_at(idx);

            do {
                for (victim = last(bin); victim != bin; victim = victim->bk) {
                    victim_size = chunksize(victim);
                    remainder_size = long_sub_size_t(victim_size, nb);

                    if (remainder_size >= (long)MINSIZE) {
                        remainder = chunk_at_offset(victim, nb);
                        set_head(victim, nb | PREV_INUSE);
                        unlink(victim, bck, fwd);
                        link_last_remainder(remainder);
                        set_head(remainder, remainder_size | PREV_INUSE);
                        set_foot(remainder, remainder_size);
                        __malloc_unlock(reent_ptr);
                        return chunk2mem(victim);
                    }

                    else if (remainder_size >= 0) {
                        set_inuse_bit_at_offset(victim, victim_size);
                        unlink(victim, bck, fwd);
                        __malloc_unlock(reent_ptr);
                        return chunk2mem(victim);
                    }
                }

                bin = next_bin(bin);

                if (idx < MAX_SMALLBIN) {
                    bin = next_bin(bin);
                    ++idx;
                }
            } while ((++idx & (BINBLOCKWIDTH - 1)) != 0);

            do {
                if ((startidx & (BINBLOCKWIDTH - 1)) == 0) {
                    binblocks &= ~block;
                    break;
                }
                --startidx;
                q = prev_bin(q);
            } while (first(q) == q);

            if ((block <<= 1) <= binblocks && (block != 0)) {
                while ((block & binblocks) == 0) {
                    idx += BINBLOCKWIDTH;
                    block <<= 1;
                }
            } else
                break;
        }
    }

    remainder_size = long_sub_size_t(chunksize(top), nb);
    if (chunksize(top) < nb || remainder_size < (long)MINSIZE) {
        malloc_extend_top(reent_ptr, nb);
        remainder_size = long_sub_size_t(chunksize(top), nb);
        if (chunksize(top) < nb || remainder_size < (long)MINSIZE) {
            __malloc_unlock(reent_ptr);
            return 0;
        }
    }

    victim = top;
    set_head(victim, nb | PREV_INUSE);
    top = chunk_at_offset(victim, nb);
    set_head(top, remainder_size | PREV_INUSE);
    __malloc_unlock(reent_ptr);
    return chunk2mem(victim);
}
