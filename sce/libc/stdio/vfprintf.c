/* libc.a member vfprintf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);
extern int _vfprintf_r();
extern int strtok_r(int a0, int a1, int a2);
extern int __sfvwrite();

/* The stdio stream, as this libc lays it out: __sbprintf builds one on its own
   stack so a line-buffered stream is written through a full-size buffer. */
#define __SNBF 0x0002
#define __SERR 0x0040
#define BUFSIZ 1024
#define EOF (-1)

extern int fflush(Fil *fp);

/* fvwrite.h */
struct __siov {
    void *iov_base; /* 0x0 */
    int iov_len;    /* 0x4 */
};

struct __suio {
    struct __siov *uio_iov; /* 0x0 */
    int uio_iovcnt;         /* 0x4 */
    int uio_resid;          /* 0x8 */
};

/* census __sprint, a file static (sce/libc/stdio/vfiprintf holds the global);
   _vfprintf_r's stub calls it and the same-object definition binds first. */
static int __sprint(fp, uio)
Fil *fp;

register struct __suio *uio;

{
    register int err;

    if (uio->uio_resid == 0) {
        uio->uio_iovcnt = 0;
        return (0);
    }
    err = __sfvwrite(fp, uio);
    uio->uio_resid = 0;
    uio->uio_iovcnt = 0;
    return (err);
}

/* census __sbprintf, a file static (sce/libc/stdio/vfiprintf holds the global
   at 0x00280160); _vfprintf_r's stub calls it and the same-object definition
   binds first. */
static int __sbprintf(Fil *fp, const char *fmt, void *ap)
{
    int ret;
    Fil fake;
    unsigned char buf[BUFSIZ];

    /* copy the important variables */
    fake.data = fp->data;
    fake.flags = fp->flags & ~__SNBF;
    fake.file = fp->file;
    fake.cookie = fp->cookie;
    fake.write = fp->write;

    /* set up the buffer */
    fake.bf.base = fake.p = buf;
    fake.bf.size = fake.w = sizeof(buf);
    fake.lbfsize = 0;

    /* do the work, then copy any error status */
    ret = vfprintf(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake))
        ret = EOF;
    if (fake.flags & __SERR)
        fp->flags |= __SERR;
    return ret;
}

/* newlib's vfprintf.c, the FLOATING_POINT (non INTEGER_ONLY) build of the
   member: VFPRINTF is `vfprintf`, _VFPRINTF_R is `_vfprintf_r`, and
   _NO_LONGLONG stays defined (WANT_PRINTF_LONG_LONG is off), which is why the
   [diouxX] accumulator is a 64-bit `unsigned long` and the base conversions go
   through __udivdi3 / __umoddi3. */
typedef char *va_list;

#define va_arg(ap, type) (*(type *)((ap += 8) - 8))

typedef int wchar_t;

/* floatio.h */
#define MAXEXP 308
#define MAXFRACT 39
#define BUF (MAXEXP + MAXFRACT + 1)
#define DEFPREC 6
#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SRD 0x0004
#define __SWR 0x0008
#define __SRW 0x0010
#define __SEOF 0x0020
#define __SERR 0x0040
#define NULL 0

extern int __sfvwrite(Fil *fp, struct __suio *uio);
extern int __swsetup(Fil *fp);
extern void __sinit(Reent *ptr);
extern int _mbtowc_r(Reent *ptr, wchar_t *pwc, const char *s, int n, int *state);
extern void *memchr(const void *s, int c, int n);
extern int isinf(double d);
extern int isnan(double d);
extern char *_dtoa_r(Reent *ptr, double d, int mode, int ndigits, int *decpt, int *sign,
                     char **rve);

/* locale.h: only the first member is read here. */
struct lconv {
    char *decimal_point; /* 0x0 */
};

extern struct lconv *localeconv(void);
/* stdlib.h's MB_CUR_MAX is the library's own __mb_cur_max. */
extern int D_0054CEB0;

#define MB_CUR_MAX D_0054CEB0
#define _REENT ((Reent *)D_0054CEAC[0])
#define CHECK_INIT(fp)                                                                             \
    do {                                                                                           \
        if ((fp)->data == 0)                                                                       \
            (fp)->data = _REENT;                                                                   \
        if (!(fp)->data->sdidinit)                                                                 \
            __sinit((fp)->data);                                                                   \
    } while (0)
#define cantwrite(fp) ((((fp)->flags & __SWR) == 0 || (fp)->bf.base == NULL) && __swsetup(fp))
#define __sferror(p) ((p)->flags & __SERR)
#define to_digit(c) ((c) - '0')
#define is_digit(c) ((unsigned)to_digit(c) <= 9)
#define to_char(n) ((n) + '0')
#define ALT 0x001
#define HEXPREFIX 0x002
#define LADJUST 0x004
#define LONGDBL 0x008
#define LONGINT 0x010
#define QUADINT 0x020
#define SHORTINT 0x040
#define ZEROPAD 0x080
#define FPT 0x100

/* mprec.h's view of a double, for cvt's sign test. */
union double_union {
    double d;
    unsigned int i[2];
};

#define word0(x) (x.i[1])
#define Sign_bit ((unsigned int)0x80000000L)

static char *cvt(Reent *data, double value, int ndigits, int flags, char *sign, int *decpt, int ch,
                 int *length);

static int exponent(char *p0, int exp, int fmtch);

int vfprintf(fp, fmt0, ap)
Fil *fp;

const char *fmt0;

va_list ap;

{
    CHECK_INIT(fp);
    return _vfprintf_r(fp->data, fp, fmt0, ap);
}

int _vfprintf_r(data, fp, fmt0, ap)
Reent *data;

Fil *fp;

const char *fmt0;

va_list ap;

{
    register char *fmt;           /* format string */
    register int ch;              /* character from fmt */
    register int n, m;            /* handy integers (short term usage) */
    register char *cp;            /* handy char pointer (short term usage) */
    register struct __siov *iovp; /* for PRINT macro */
    register int flags;           /* flags as above */
    int ret;                      /* return value accumulator */
    int width;                    /* width from format (%8d), or 0 */
    int prec;                     /* precision from format (%.3d), or -1 */
    char sign;                    /* sign prefix (' ', '+', '-', or \0) */
    wchar_t wc;
    char *decimal_point = localeconv()->decimal_point;
    char softsign;  /* temporary negative sign for floats */
    double _double; /* double precision arguments %[eEfgG] */
    int expt;       /* integer value of exponent */
    int expsize;    /* character count for expstr */
    int ndig;       /* actual number of digits returned by cvt */
    char expstr[7]; /* buffer for exponent string */

    unsigned long _uquad; /* integer arguments %[diouxX] */

    enum { OCT, DEC, HEX } base; /* base for [diouxX] conversion */

    int dprec;   /* a copy of prec if [diouxX], 0 otherwise */
    int realsz;  /* field size expanded by dprec */
    int size;    /* size of converted field or string */
    char *xdigs; /* digits for [xX] conversion */
#define NIOV 8
    struct __suio uio;       /* output information: summary */
    struct __siov iov[NIOV]; /* ... and individual io vectors */
    char buf[BUF];           /* space for %c, %[diouxX], %[eEfgG] */
    char ox[2];              /* space for 0x hex-prefix */
    int state = 0;           /* mbtowc calls from library must not change state */

#define PADSIZE 16 /* pad chunk size */
    static const char blanks[PADSIZE] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                         ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    static const char zeroes[PADSIZE] = {'0', '0', '0', '0', '0', '0', '0', '0',
                                         '0', '0', '0', '0', '0', '0', '0', '0'};

#define PRINT(ptr, len)                                                                            \
    {                                                                                              \
        iovp->iov_base = (ptr);                                                                    \
        iovp->iov_len = (len);                                                                     \
        uio.uio_resid += (len);                                                                    \
        iovp++;                                                                                    \
        if (++uio.uio_iovcnt >= NIOV) {                                                            \
            if (__sprint(fp, &uio))                                                                \
                goto error;                                                                        \
            iovp = iov;                                                                            \
        }                                                                                          \
    }
#define PAD(howmany, with)                                                                         \
    {                                                                                              \
        if ((n = (howmany)) > 0) {                                                                 \
            while (n > PADSIZE) {                                                                  \
                PRINT(with, PADSIZE);                                                              \
                n -= PADSIZE;                                                                      \
            }                                                                                      \
            PRINT(with, n);                                                                        \
        }                                                                                          \
    }
#define FLUSH()                                                                                    \
    {                                                                                              \
        if (uio.uio_resid && __sprint(fp, &uio))                                                   \
            goto error;                                                                            \
        uio.uio_iovcnt = 0;                                                                        \
        iovp = iov;                                                                                \
    }

#define SARG()                                                                                     \
    (flags & LONGINT    ? va_arg(ap, long)                                                         \
     : flags & SHORTINT ? (long)(short)va_arg(ap, int)                                             \
                        : (long)va_arg(ap, int))
#define UARG()                                                                                     \
    (flags & LONGINT    ? va_arg(ap, unsigned long)                                                \
     : flags & SHORTINT ? (unsigned long)(unsigned short)va_arg(ap, int)                           \
                        : (unsigned long)va_arg(ap, unsigned int))

    /* sorry, fprintf(read_only_file, "") returns EOF, not 0 */
    if (cantwrite(fp))
        return (EOF);

    /* optimise fprintf(stderr) (and other unbuffered Unix files) */
    if ((fp->flags & (__SNBF | __SWR | __SRW)) == (__SNBF | __SWR) && fp->file >= 0)
        return (__sbprintf(fp, fmt0, ap));

    fmt = (char *)fmt0;
    uio.uio_iov = iovp = iov;
    uio.uio_resid = 0;
    uio.uio_iovcnt = 0;
    ret = 0;

    /*
     * Scan the format for conversions (`%' character).
     */
    for (;;) {
        cp = fmt;
        while ((n = _mbtowc_r(_REENT, &wc, fmt, MB_CUR_MAX, &state)) > 0) {
            fmt += n;
            if (wc == '%') {
                fmt--;
                break;
            }
        }
        if ((m = fmt - cp) != 0) {
            PRINT(cp, m);
            ret += m;
        }
        if (n <= 0)
            goto done;
        fmt++; /* skip over '%' */

        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';

    rflag:
        ch = *fmt++;
    reswitch:
        switch (ch) {
        case ' ':
            if (!sign)
                sign = ' ';
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            if ((width = va_arg(ap, int)) >= 0)
                goto rflag;
            width = -width;
            /* FALLTHROUGH */
        case '-':
            flags |= LADJUST;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if ((ch = *fmt++) == '*') {
                n = va_arg(ap, int);
                prec = n < 0 ? -1 : n;
                goto rflag;
            }
            n = 0;
            while (is_digit(ch)) {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            }
            prec = n < 0 ? -1 : n;
            goto reswitch;
        case '0':
            flags |= ZEROPAD;
            goto rflag;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            n = 0;
            do {
                n = 10 * n + to_digit(ch);
                ch = *fmt++;
            } while (is_digit(ch));
            width = n;
            goto reswitch;
        case 'L':
            flags |= LONGDBL;
            goto rflag;
        case 'h':
            flags |= SHORTINT;
            goto rflag;
        case 'l':
            if (*fmt == 'l') {
                fmt++;
                flags |= QUADINT;
            } else {
                flags |= LONGINT;
            }
            goto rflag;
        case 'q':
            flags |= QUADINT;
            goto rflag;
        case 'c':
            *(cp = buf) = va_arg(ap, int);
            size = 1;
            sign = '\0';
            break;
        case 'D':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'd':
        case 'i':
            _uquad = SARG();
            if ((long)_uquad < 0) {
                _uquad = -_uquad;
                sign = '-';
            }
            base = DEC;
            goto number;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
            if (prec == -1) {
                prec = DEFPREC;
            } else if ((ch == 'g' || ch == 'G') && prec == 0) {
                prec = 1;
            }

            if (flags & LONGDBL) {
                _double = (double)va_arg(ap, long double);
            } else {
                _double = va_arg(ap, double);
            }

            /* do this before tricky precision changes */
            if (isinf(_double)) {
                if (_double < 0)
                    sign = '-';
                cp = "Inf";
                size = 3;
                break;
            }
            if (isnan(_double)) {
                cp = "NaN";
                size = 3;
                break;
            }

            flags |= FPT;
            cp = cvt(data, _double, prec, flags, &softsign, &expt, ch, &ndig);
            if (ch == 'g' || ch == 'G') {
                if (expt <= -4 || expt > prec)
                    ch = (ch == 'g') ? 'e' : 'E';
                else
                    ch = 'g';
            }
            if (ch <= 'e') { /* 'e' or 'E' fmt */
                --expt;
                expsize = exponent(expstr, expt, ch);
                size = expsize + ndig;
                if (ndig > 1 || flags & ALT)
                    ++size;
            } else if (ch == 'f') { /* f fmt */
                if (expt > 0) {
                    size = expt;
                    if (prec || flags & ALT)
                        size += prec + 1;
                } else /* "0.X" */
                    size = prec + 2;
            } else if (expt >= ndig) { /* fixed g fmt */
                size = expt;
                if (flags & ALT)
                    ++size;
            } else
                size = ndig + (expt > 0 ? 1 : 2 - expt);

            if (softsign)
                sign = '-';
            break;
        case 'n':
            if (flags & LONGINT)
                *va_arg(ap, long *) = ret;
            else if (flags & SHORTINT)
                *va_arg(ap, short *) = ret;
            else
                *va_arg(ap, int *) = ret;
            continue; /* no output */
        case 'O':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'o':
            _uquad = UARG();
            base = OCT;
            goto nosign;
        case 'p':
            /* NOSTRICT */
            _uquad = (unsigned long)(unsigned long)va_arg(ap, void *);
            base = HEX;
            xdigs = "0123456789abcdef";
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = va_arg(ap, char *)) == NULL)
                cp = "(null)";
            if (prec >= 0) {
                char *p = memchr(cp, 0, prec);

                if (p != NULL) {
                    size = p - cp;
                    if (size > prec)
                        size = prec;
                } else
                    size = prec;
            } else
                size = strlen(cp);
            sign = '\0';
            break;
        case 'U':
            flags |= LONGINT;
            /*FALLTHROUGH*/
        case 'u':
            _uquad = UARG();
            base = DEC;
            goto nosign;
        case 'X':
            xdigs = "0123456789ABCDEF";
            goto hex;
        case 'x':
            xdigs = "0123456789abcdef";
        hex:
            _uquad = UARG();
            base = HEX;
            /* leading 0x/X only if non-zero */
            if (flags & ALT && _uquad != 0)
                flags |= HEXPREFIX;

            /* unsigned conversions */
        nosign:
            sign = '\0';
        number:
            if ((dprec = prec) >= 0)
                flags &= ~ZEROPAD;

            cp = buf + BUF;
            if (_uquad != 0 || prec != 0) {
                switch (base) {
                case OCT:
                    do {
                        *--cp = to_char(_uquad & 7);
                        _uquad >>= 3;
                    } while (_uquad);
                    /* handle octal leading 0 */
                    if (flags & ALT && *cp != '0')
                        *--cp = '0';
                    break;

                case DEC:
                    /* many numbers are 1 digit */
                    while (_uquad >= 10) {
                        *--cp = to_char(_uquad % 10);
                        _uquad /= 10;
                    }
                    *--cp = to_char(_uquad);
                    break;

                case HEX:
                    do {
                        *--cp = xdigs[_uquad & 15];
                        _uquad >>= 4;
                    } while (_uquad);
                    break;

                default:
                    cp = "bug in vfprintf: bad base";
                    size = strlen(cp);
                    goto skipsize;
                }
            }
            size = buf + BUF - cp;
        skipsize:
            break;
        default: /* "%?" prints ?, unless ? is NUL */
            if (ch == '\0')
                goto done;
            /* pretend it was %c with argument ch */
            cp = buf;
            *cp = ch;
            size = 1;
            sign = '\0';
            break;
        }

        realsz = dprec > size ? dprec : size;
        if (sign)
            realsz++;
        else if (flags & HEXPREFIX)
            realsz += 2;

        /* right-adjusting blank padding */
        if ((flags & (LADJUST | ZEROPAD)) == 0)
            PAD(width - realsz, blanks);

        /* prefix */
        if (sign) {
            PRINT(&sign, 1);
        } else if (flags & HEXPREFIX) {
            ox[0] = '0';
            ox[1] = ch;
            PRINT(ox, 2);
        }

        /* right-adjusting zero padding */
        if ((flags & (LADJUST | ZEROPAD)) == ZEROPAD)
            PAD(width - realsz, zeroes);

        /* leading zeroes from decimal precision */
        PAD(dprec - size, zeroes);

        /* the string or number proper */
        if ((flags & FPT) == 0) {
            PRINT(cp, size);
        } else {             /* glue together f_p fragments */
            if (ch >= 'f') { /* 'f' or 'g' */
                if (_double == 0) {
                    /* kludge for __dtoa irregularity */
                    PRINT("0", 1);
                    if (expt < ndig || (flags & ALT) != 0) {
                        PRINT(decimal_point, 1);
                        PAD(ndig - 1, zeroes);
                    }
                } else if (expt <= 0) {
                    PRINT("0", 1);
                    PRINT(decimal_point, 1);
                    PAD(-expt, zeroes);
                    PRINT(cp, ndig);
                } else if (expt >= ndig) {
                    PRINT(cp, ndig);
                    PAD(expt - ndig, zeroes);
                    if (flags & ALT)
                        PRINT(".", 1);
                } else {
                    PRINT(cp, expt);
                    cp += expt;
                    PRINT(".", 1);
                    PRINT(cp, ndig - expt);
                }
            } else { /* 'e' or 'E' */
                if (ndig > 1 || flags & ALT) {
                    ox[0] = *cp++;
                    ox[1] = '.';
                    PRINT(ox, 2);
                    if (_double || flags & ALT == 0) {
                        PRINT(cp, ndig - 1);
                    } else /* 0.[0..] */
                        /* __dtoa irregularity */
                        PAD(ndig - 1, zeroes);
                } else /* XeYYY */
                    PRINT(cp, 1);
                PRINT(expstr, expsize);
            }
        }
        /* left-adjusting padding (always blank) */
        if (flags & LADJUST)
            PAD(width - realsz, blanks);

        /* finally, adjust ret */
        ret += width > realsz ? width : realsz;

        FLUSH(); /* copy out the I/O vectors */
    }
done:
    FLUSH();
error:
    return (__sferror(fp) ? EOF : ret);
    /* NOTREACHED */
}

static char *cvt(data, value, ndigits, flags, sign, decpt, ch, length)
Reent *data;

double value;

int ndigits, flags, *decpt, ch, *length;

char *sign;

{
    int mode, dsgn;
    char *digits, *bp, *rve;
    union double_union tmp;

    if (ch == 'f') {
        mode = 3; /* ndigits after the decimal point */
    } else {
        /* To obtain ndigits after the decimal point for the 'e'
         * and 'E' formats, round to ndigits + 1 significant
         * figures.
         */
        if (ch == 'e' || ch == 'E') {
            ndigits++;
        }
        mode = 2; /* ndigits significant digits */
    }

    tmp.d = value;
    if (word0(tmp) & Sign_bit) { /* this will check for < 0 and -0.0 */
        value = -value;
        *sign = '-';
    } else
        *sign = '\000';
    digits = _dtoa_r(data, value, mode, ndigits, decpt, &dsgn, &rve);
    if ((ch != 'g' && ch != 'G') || flags & ALT) { /* Print trailing zeros */
        bp = digits + ndigits;
        if (ch == 'f') {
            if (*digits == '0' && value)
                *decpt = -ndigits + 1;
            bp += *decpt;
        }
        if (value == 0) /* kludge for __dtoa irregularity */
            rve = bp;
        while (rve < bp)
            *rve++ = '0';
    }
    *length = rve - digits;
    return (digits);
}

static int exponent(p0, exp, fmtch)
char *p0;

int exp, fmtch;

{
    register char *p, *t;
    char expbuf[MAXEXP];

    p = p0;
    *p++ = fmtch;
    if (exp < 0) {
        exp = -exp;
        *p++ = '-';
    } else
        *p++ = '+';
    t = expbuf + MAXEXP;
    if (exp > 9) {
        do {
            *--t = to_char(exp % 10);
        } while ((exp /= 10) > 9);
        *--t = to_char(exp);
        for (; t < expbuf + MAXEXP; *p++ = *t++)
            ;
    } else {
        *p++ = '0';
        *p++ = to_char(exp);
    }
    return (p - p0);
}

extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void _fwalk(int a0, void *a1);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
