/* libm.a member wf_asin.o */
#include <math.h>
#include <errno.h>
#include <math_private.h>

#define DOMAIN 1
#define EDOM 33

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
