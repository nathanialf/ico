/* libc.a member qsort.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);
typedef int (*QCmp)();

#define qswapcode(TYPE, parmi, parmj, n)                                                           \
    {                                                                                              \
        long long i = (n) / sizeof(TYPE);                                                          \
        TYPE *pi = (TYPE *)(parmi);                                                                \
        TYPE *pj = (TYPE *)(parmj);                                                                \
        do {                                                                                       \
            TYPE t = *pi;                                                                          \
            *pi++ = *pj;                                                                           \
            *pj++ = t;                                                                             \
        } while (--i > 0);                                                                         \
    }

static inline void swapfunc(char *a, char *b, int n, int swaptype)
{
    if (swaptype <= 1) {
        qswapcode(long long, a, b, n)
    } else {
        qswapcode(char, a, b, n)
    }
}

#define QSWAPINIT(a, es)                                                                           \
    swaptype = ((char *)a - (char *)0) % sizeof(long long) || es % sizeof(long long) ? 2           \
               : es == sizeof(long long)                                             ? 0           \
                                                                                     : 1;
#define qswap(a, b)                                                                                \
    if (swaptype == 0) {                                                                           \
        long long t = *(long long *)(a);                                                           \
        *(long long *)(a) = *(long long *)(b);                                                     \
        *(long long *)(b) = t;                                                                     \
    } else                                                                                         \
        swapfunc(a, b, es, swaptype)
#define qvecswap(a, b, n)                                                                          \
    if ((n) > 0)                                                                                   \
    swapfunc(a, b, n, swaptype)

static inline char *med3(char *a, char *b, char *c, QCmp cmp)
{
    return cmp(a, b) < 0 ? (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a))
                         : (cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c));
}

void qsort(void *a, unsigned int n, unsigned int es, QCmp cmp)
{
    char *pa;
    char *pb;
    char *pc;
    char *pd;
    char *pl;
    char *pm;
    char *pn;
    int d;
    int r;
    int swaptype;
    int swap_cnt;

loop:
    QSWAPINIT(a, es);
    swap_cnt = 0;
    if (n < 7) {
        for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es) {
            for (pl = pm; pl > (char *)a && cmp(pl - es, pl) > 0; pl -= es) {
                qswap(pl, pl - es);
            }
        }
        return;
    }
    pm = (char *)a + (n / 2) * es;
    if (n > 7) {
        pl = (char *)a;
        pn = (char *)a + (n - 1) * es;
        if (n > 40) {
            d = (n / 8) * es;
            pl = med3(pl, pl + d, pl + 2 * d, cmp);
            pm = med3(pm - d, pm, pm + d, cmp);
            pn = med3(pn - 2 * d, pn - d, pn, cmp);
        }
        pm = med3(pl, pm, pn, cmp);
    }
    qswap(a, pm);
    pa = pb = (char *)a + es;

    pc = pd = (char *)a + (n - 1) * es;
    for (;;) {
        while (pb <= pc && (r = cmp(pb, a)) <= 0) {
            if (r == 0) {
                swap_cnt = 1;
                qswap(pa, pb);
                pa += es;
            }
            pb += es;
        }
        while (pb <= pc && (r = cmp(pc, a)) >= 0) {
            if (r == 0) {
                swap_cnt = 1;
                qswap(pc, pd);
                pd -= es;
            }
            pc -= es;
        }
        if (pb > pc) {
            break;
        }
        qswap(pb, pc);
        swap_cnt = 1;
        pb += es;
        pc -= es;
    }
    if (swap_cnt == 0) {
        for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es) {
            for (pl = pm; pl > (char *)a && cmp(pl - es, pl) > 0; pl -= es) {
                qswap(pl, pl - es);
            }
        }
        return;
    }

    pn = (char *)a + n * es;
    r = pa - (char *)a < pb - pa ? pa - (char *)a : pb - pa;
    qvecswap(a, pb - r, r);
    r = pd - pc < pn - pd - es ? pd - pc : pn - pd - es;
    qvecswap(pb, pn - r, r);
    if ((r = pb - pa) > es) {
        qsort(a, r / es, es, cmp);
    }
    if ((r = pd - pc) > es) {
        a = pn - r;
        n = r / es;
        goto loop;
    }
}
