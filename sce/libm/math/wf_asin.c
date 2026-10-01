/* libm.a member wf_asin.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <math.h>
#include <math_private.h>

/* newlib's math wrapper machinery.  The listing attributes no row to a header,
   so the shapes are kept per member; _LIB_VERSION comes from math.h. */
struct exception {
    int type;      /* 0x00 */
    char *name;    /* 0x04 */
    double arg1;   /* 0x08 */
    double arg2;   /* 0x10 */
    double retval; /* 0x18 */
    int err;       /* 0x20 */
};

#define DOMAIN 1
#define EDOM 33

/* kept local: errno.h declares it as its definition, returning int, where these uses take int * */
extern int *__errno(void);

float asinf(float x)
{
    float z;
    struct exception exc;

    z = __ieee754_asinf(x);
    if (_LIB_VERSION == _IEEE_ || isnanf(x))
        return z;
    if (fabsf(x) > (float)1.0) {
        /* asinf(|x|>1) */
        exc.type = DOMAIN;
        exc.name = "asinf";
        exc.err = 0;
        exc.arg1 = exc.arg2 = (double)x;
        exc.retval = 0.0;
        if (_LIB_VERSION == _POSIX_)
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
