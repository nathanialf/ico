/* libc.a member freer.o.  MAIN.MAP member spans tile this run exactly and
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
extern long long strtol(void *a0, int a1, int a2);
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void memset(void *a0, int a1, int a2);
extern int memcpy(char *a0, char *a1, int a2);

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
#define MINSIZE 16
#define MAX_SMALLBIN_SIZE 512
#define BINBLOCKWIDTH 4
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - 2 * SIZE_SZ))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define inuse_bit_at_offset(p, s) (((mchunkptr)((char *)(p) + (s)))->size & PREV_INUSE)

/* The bin array of the shipped allocator. */
extern mchunkptr D_0054CEC8[];

#define bin_at(i) ((mchunkptr)((char *)&(D_0054CEC8[2 * (i) + 2]) - 2 * SIZE_SZ))
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

/* trim_threshold */
extern unsigned long D_0054D2D0[];
/* top_pad */
extern unsigned int D_0054D2D8[];
extern void __malloc_lock(void);
extern void __malloc_unlock();
extern int _malloc_trim_r(int *self, unsigned int pad);

void _free_r(int *self, void *mem)
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

    __malloc_lock();
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
        if ((unsigned long)(sz) >= (unsigned long)D_0054D2D0[0]) {
            _malloc_trim_r(self, D_0054D2D8[0]);
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

extern int D_0054D2E0[];
extern int D_0054D2F8[];
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int _sbrk_r(int *self, int a1);

int _malloc_trim_r(int *self, unsigned int a1)
{
    long long A;
    long long need;
    long long newlen;
    int r4;

    __malloc_lock();
    A = top->size & 0xFFFFFFFC;
    need = __udivdi3((A - a1) + 0xFEF, 0x1000);
    newlen = __muldi3(need - 1, 0x1000);
    if (newlen < 0x1000) {
        goto fail;
    }
    if (_sbrk_r(self, 0) != (int)top + (int)A) {
        goto fail;
    }
    if (_sbrk_r(self, -(int)newlen) != 0xFFFFFFFFU) {
        goto adjust;
    }
    r4 = _sbrk_r(self, 0);
    A = r4 - (int)top;
    if (A >= 0x10) {
        D_0054D2F8[0] = r4 - D_0054D2E0[0];
        top->size = A | 1;
    }
fail:
    __malloc_unlock(self);
    return 0;
adjust:
    top->size = (A - newlen) | 1;
    D_0054D2F8[0] -= (int)newlen;
    __malloc_unlock(self);
    return 1;
}

extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern int _close_r(int *self, int a1);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
