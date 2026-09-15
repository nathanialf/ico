/* libm.a member wf_fmod.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

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
#define _SVID_ 0
#define _POSIX_ 2
#define EDOM 33

extern const int D_006379C8[]; /* _LIB_VERSION */
extern float __ieee754_fmodf(float x, float y);
extern int isnanf(float x);
extern int matherr(struct exception *e);
extern int *__errno(void);

float fmodf(float x, float y)
{
    float z;
    struct exception exc;

    z = __ieee754_fmodf(x, y);
    if (D_006379C8[0] == _IEEE_ || isnanf(y) || isnanf(x)) {
        return z;
    }
    if (y == (float)0.0) {
        exc.type = DOMAIN;
        exc.name = "fmodf";
        exc.err = 0;
        exc.arg1 = (double)x;
        exc.arg2 = (double)y;
        if (D_006379C8[0] == _SVID_) {
            exc.retval = (double)x;
        } else {
            exc.retval = 0.0 / 0.0;
        }
        if (D_006379C8[0] == _POSIX_) {
            *__errno() = EDOM;
        } else if (!matherr(&exc)) {
            *__errno() = EDOM;
        }
        if (exc.err != 0) {
            *__errno() = exc.err;
        }
        return (float)exc.retval;
    }
    return z;
}
