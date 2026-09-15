/* libgcc.a member _muldi3.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
} PCmpV;

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
    unsigned long long f10;
} PCmpV2;

typedef int SItype;

typedef unsigned int USItype;

typedef long long DItype;

struct DIstruct {
    SItype low, high;
};

typedef union {
    struct DIstruct s;
    DItype ll;
} DIunion;

#define umul_ppmm(w1, w0, u, v)                                                                    \
    __asm__("multu %2,%3"                                                                          \
            : "=l"((USItype)(w0)), "=h"((USItype)(w1))                                             \
            : "d"((USItype)(u)), "d"((USItype)(v)))
#define __umulsidi3(u, v)                                                                          \
    ({                                                                                             \
        DIunion __w;                                                                               \
        umul_ppmm(__w.s.high, __w.s.low, u, v);                                                    \
        __w.ll;                                                                                    \
    })

DItype __muldi3(DItype u, DItype v)
{
    DIunion w;
    DIunion uu, vv;

    uu.ll = u;
    vv.ll = v;

    w.ll = __umulsidi3(uu.s.low, vv.s.low);
    w.s.high += ((USItype)uu.s.low * (USItype)vv.s.high + (USItype)uu.s.high * (USItype)vv.s.low);

    return w.ll;
}
