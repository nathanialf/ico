/* libm.a member wf_acos.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <math.h>
#include <errno.h>
#include <math_private.h>

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
