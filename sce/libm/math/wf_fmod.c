/* libm.a member wf_fmod.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <math.h>
#include <errno.h>
#include <math_private.h>

#define DOMAIN 1
#define EDOM 33

float fmodf(float x, float y)
{
    float z;
    struct exception exc;

    z = __ieee754_fmodf(x, y);
    if (_LIB_VERSION == _IEEE_ || isnanf(y) || isnanf(x)) {
        return z;
    }
    if (y == (float)0.0) {
        exc.type = DOMAIN;
        exc.name = "fmodf";
        exc.err = 0;
        exc.arg1 = (double)x;
        exc.arg2 = (double)y;
        if (_LIB_VERSION == _SVID_) {
            exc.retval = (double)x;
        } else {
            exc.retval = 0.0 / 0.0;
        }
        if (_LIB_VERSION == _POSIX_) {
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
