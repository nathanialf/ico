/* libm.a member wf_acos.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <math.h>
#include <math_private.h>

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

/* kept local: errno.h declares it as its definition, returning int, where these uses take int * */
extern int *__errno(void);

float acosf(float x)
{
    float z;
    struct exception exc;

    z = __ieee754_acosf(x);
    if (_LIB_VERSION == _IEEE_ || isnanf(x))
        return z;
    if (fabsf(x) > 1.0f) {
        exc.type = 1;
        exc.name = "acosf";
        exc.err = 0;
        exc.arg1 = exc.arg2 = x;
        exc.retval = 0.0;
        if (_LIB_VERSION == _POSIX_)
            *__errno() = 33;
        else if (!matherr(&exc))
            *__errno() = 33;
        if (exc.err != 0)
            *__errno() = exc.err;
        return (float)exc.retval;
    } else
        return z;
}
