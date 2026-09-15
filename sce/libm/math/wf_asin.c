/* libm.a member wf_asin.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

/* newlib's math wrapper machinery.  The listing attributes no row to a header,
   so the shapes are kept per member.  D_006379C8 is _LIB_VERSION (a plain
   extern int here: naming it would need a symbol alias, which is banned). */
struct exception {
    int type;      /* 0x00 */
    char *name;    /* 0x04 */
    double arg1;   /* 0x08 */
    double arg2;   /* 0x10 */
    double retval; /* 0x18 */
    int err;       /* 0x20 */
};

#define DOMAIN 1
#define _IEEE_ (-1)
#define _POSIX_ 2
#define EDOM 33

extern const int D_006379C8[];
/* The wrapper's name string, "asinf".  It stays a reference to the shared
   .rodata run: written as a C literal the -G 8 compiler emits it into this
   object's .sdata, where the ROM keeps it in .rodata at 0x006374B8, so the
   literal cannot be carved back to its own address yet. */
extern char D_006374B8[];
extern float __ieee754_asinf(float x);
extern int isnanf(float x);
extern float fabsf(float x);
extern int matherr(void *a0);
extern int *__errno(void);

float asinf(float x)
{
    float z;
    struct exception exc;

    z = __ieee754_asinf(x);
    if (D_006379C8[0] == _IEEE_ || isnanf(x))
        return z;
    if (fabsf(x) > (float)1.0) {
        /* asinf(|x|>1) */
        exc.type = DOMAIN;
        exc.name = D_006374B8;
        exc.err = 0;
        exc.arg1 = exc.arg2 = (double)x;
        exc.retval = 0.0;
        if (D_006379C8[0] == _POSIX_)
            *__errno() = EDOM;
        else if (!matherr(&exc)) {
            *__errno() = EDOM;
        }
        if (exc.err != 0)
            *__errno() = exc.err;
        return (float)exc.retval;
    } else
        return z;
}
