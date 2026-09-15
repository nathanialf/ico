/* libm.a member wf_atan2.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

/* newlib's wrapper layer: struct exception and the _LIB_VERSION guard.  The
   member's own copies stand for the Sony/newlib math.h this tree cannot name. */
struct exception {
    int type;      /* 0x0 */
    char *name;    /* 0x4 */
    double arg1;   /* 0x8 */
    double arg2;   /* 0x10 */
    double retval; /* 0x18 */
    int err;       /* 0x20 */
};

extern const int D_006379C8[]; /* _LIB_VERSION */
extern float __ieee754_atan2f(float y, float x);
extern int isnanf(float x);
extern int matherr(struct exception *e);
extern int *__errno(void);

float atan2f(float y, float x)
{
    float z;
    struct exception exc;

    z = __ieee754_atan2f(y, x);
    if (D_006379C8[0] == -1 || isnanf(x) || isnanf(y))
        return z;
    if (x == 0.0f && y == 0.0f) {
        exc.arg1 = y;
        exc.arg2 = x;
        exc.type = 1;
        exc.name = "atan2f";
        exc.err = 0;
        exc.retval = 0.0;
        if (D_006379C8[0] == 2)
            *__errno() = 33;
        else if (!matherr(&exc))
            *__errno() = 33;
        if (exc.err != 0)
            *__errno() = exc.err;
        return (float)exc.retval;
    } else
        return z;
}
