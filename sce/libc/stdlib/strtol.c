/* libc.a member strtol.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <ctype.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* libc.a member strtol.o: this is the reentrant worker `strtol` calls, i.e.
   newlib's _strtol_r; the ELF has no symbol for it.  _strtoul_r sits in the
   strtoul.o member. */

struct _reent {
    int _errno; /* 0x00 */
};

#define ERANGE 34
#define LONG_MAX 0x7FFFFFFFFFFFFFFFL
#define LONG_MIN (-LONG_MAX - 1L)

long _strtol_r(struct _reent *rptr, const char *nptr, char **endptr, int base)
{
    register const char *s = nptr;
    register unsigned long acc;
    register int c;
    register unsigned long cutoff;
    register int neg = 0, any, cutlim;

    do {
        c = *s++;
    } while ((_ctype_ + 1)[c] & _S);
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+') {
        c = *s++;
    }
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0) {
        base = c == '0' ? 8 : 10;
    }

    cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
    cutlim = cutoff % (unsigned long)base;
    cutoff /= (unsigned long)base;
    for (acc = 0, any = 0;; c = *s++) {
        if ((_ctype_ + 1)[c] & _N) {
            c -= '0';
        } else if ((_ctype_ + 1)[c] & (_U | _L)) {
            c -= ((_ctype_ + 1)[c] & _U) ? 'A' - 10 : 'a' - 10;
        } else {
            break;
        }
        if (c >= base) {
            break;
        }
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim)) {
            any = -1;
        } else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = neg ? LONG_MIN : LONG_MAX;
        rptr->_errno = ERANGE;
    } else if (neg) {
        acc = -acc;
    }
    if (endptr != 0) {
        *endptr = (char *)(any ? s - 1 : nptr);
    }
    return acc;
}

long strtol(const char *s, char **ptr, int base)
{
    return _strtol_r((struct _reent *)_impure_ptr, s, ptr, base);
}
