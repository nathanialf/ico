/* libm.a member wf_atan2.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <math.h>
#include <errno.h>
#include <math_private.h>

float atan2f(float y, float x)
{
    float z;
    struct exception exc;

    z = __ieee754_atan2f(y, x);
    if (_LIB_VERSION == _IEEE_ || isnanf(x) || isnanf(y))
        return z;
    if (x == 0.0f && y == 0.0f) {
        exc.arg1 = y;
        exc.arg2 = x;
        exc.type = 1;
        exc.name = "atan2f";
        exc.err = 0;
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
