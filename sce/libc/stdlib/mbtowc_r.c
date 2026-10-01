/* libc.a member mbtowc_r.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

int _mbtowc_r(struct Reent *r, int *pwc, const char *s, int n, int *state)
{
    int dummy;
    int *p = &dummy;
    unsigned char *t = (unsigned char *)s;
    if (pwc != 0)
        p = pwc;
    if (t == 0)
        goto zero;
    if (n != 0)
        goto store;
    return -1;
zero:
    return 0;
store:
    *p = *t;
    return *t != 0;
}
