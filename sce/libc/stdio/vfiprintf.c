/* libc.a member vfiprintf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern char *D_0054CEAC; /* _impure_ptr */
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);
extern long long strtol(void *a0, int a1, int a2);
extern int strtok_r(int a0, int a1, int a2);
extern int __sfvwrite();

int __sprint(int a0, int *a1)
{
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = __sfvwrite(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}

/* newlib's struct __sFILE for this build; the tail padding is what puts
   __sbprintf's 0x400-byte buffer at sp+0x60 behind the fake FILE at sp+0. */
typedef struct {
    char *_p;               /* 0x0 */
    int _r;                 /* 0x4 */
    int _w;                 /* 0x8 */
    short _flags;           /* 0xC */
    short _file;            /* 0xE */
    char *_bf_base;         /* 0x10 */
    int _bf_size;           /* 0x14 */
    int _lbfsize;           /* 0x18 */
    void *_cookie;          /* 0x1C */
    int _read;              /* 0x20 */
    int _write;             /* 0x24 */
    int _seek;              /* 0x28 */
    int _close;             /* 0x2C */
    char *_ub_base;         /* 0x30 */
    int _ub_size;           /* 0x34 */
    char *_up;              /* 0x38 */
    int _ur;                /* 0x3C */
    unsigned char _ubuf[3]; /* 0x40 */
    unsigned char _nbuf[1]; /* 0x43 */
    char *_lb_base;         /* 0x44 */
    int _lb_size;           /* 0x48 */
    int _blksize;           /* 0x4C */
    int _offset;            /* 0x50 */
    void *_data;            /* 0x54 */
} FileS;

extern int fflush();
extern int vfiprintf(char *fp, char *fmt, void *ap);

int __sbprintf(FileS *fp, char *fmt, void *ap)
{
    FileS fake;
    unsigned char buf[0x400];
    int ret;

    /* copy the important variables */
    fake._data = fp->_data;
    fake._flags = fp->_flags & ~2;
    fake._file = fp->_file;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;

    /* set up the buffer */
    fake._bf_base = fake._p = (char *)buf;
    fake._bf_size = fake._w = sizeof(buf);
    fake._lbfsize = 0;

    /* do the work, then copy any error status */
    ret = vfiprintf((char *)&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake)) {
        ret = -1;
    }
    if (fake._flags & 0x40) {
        fp->_flags |= 0x40;
    }
    return ret;
}

extern void __sinit(void *r);
extern int _vfiprintf_r(void *r, FileS *fp, const char *fmt, char *ap);

int vfiprintf(char *fp, char *fmt0, void *ap)
{
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (*(char **)(fp + 0x54) == 0)
            *(char **)(fp + 0x54) = D_0054CEAC;
        if (*(int *)(*(char **)(fp + 0x54) + 0x38) == 0)
            __sinit(*(char **)(fp + 0x54));
    } while (0);
    return _vfiprintf_r(*(char **)(fp + 0x54), (FileS *)fp, fmt0, ap);
}

/* newlib's vfprintf.c built INTEGER_ONLY (so the entry point is
 * _vfiprintf_r) and MB_CAPABLE (so the plain-text scan runs through
 * _mbtowc_r).  ee-gcc's long is 64 bits with -mips3, which is why every
 * LONGINT fetch is an ld and the conversion arithmetic is 64-bit. */

typedef unsigned long u_long;

typedef unsigned short u_short;

typedef unsigned int u_int;

struct __siov {
    void *iov_base; /* 0x0 */
    int iov_len;    /* 0x4 */
};

struct __suio {
    struct __siov *uio_iov; /* 0x0 */
    int uio_iovcnt;         /* 0x4 */
    int uio_resid;          /* 0x8 */
};

extern int __swsetup(FileS *fp);
extern int _mbtowc_r(void *r, int *pwc, const char *s, int n, int *state);
extern char *memchr(const char *s, int c, int n);
extern int strlen(const char *s);
extern int D_0054CEB0; /* __mb_cur_max */

#define NULL 0
#define _REENT ((void *)D_0054CEAC)
#define MB_CUR_MAX D_0054CEB0

/*
 * Actual printf innards.
 */

#define va_arg(ap, type) (*(type *)((ap += 8) - 8))
/*
 * Macros for converting digits to letters and vice versa
 */
#define to_digit(c) ((c) - '0')
#define is_digit(c) ((u_int)to_digit(c) <= 9)
#define to_char(n) ((n) + '0')
/*
 * Flags used during conversion.
 */
#define ALT 0x001       /* alternate form */
#define HEXPREFIX 0x002 /* add 0x or 0X prefix */
#define LADJUST 0x004   /* left adjustment */
#define LONGDBL 0x008   /* long double; unimplemented */
#define LONGINT 0x010   /* long integer */
#define QUADINT 0x020   /* quad integer */
#define SHORTINT 0x040  /* short integer */
#define ZEROPAD 0x080   /* zero (as opposed to blank) pad */
#define FPT 0x100       /* floating point number */
#define BUF 40          /* space for %c, %[diouxX], %[eEfgG] */
#define PADSIZE 16      /* pad chunk size */
#define NIOV 8

static const char blanks[PADSIZE] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                     ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

static const char zeroes[PADSIZE] = {'0', '0', '0', '0', '0', '0', '0', '0',
                                     '0', '0', '0', '0', '0', '0', '0', '0'};

int _vfiprintf_r(void *data, FileS *fp, const char *fmt0, char *ap)
{
    register const char *fmt;     /* format string */
    register int ch;              /* character from fmt */
    register int n, m;            /* handy integers (short term usage) */
    register char *cp;            /* handy char pointer (short term usage) */
    register struct __siov *iovp; /* for PRINT macro */
    register int flags;           /* flags as above */
    int ret;                      /* return value accumulator */
    int width;                    /* width from format (%8d), or 0 */
    int prec;                     /* precision from format (%.3d), or -1 */
    char sign;                    /* sign prefix (' ', '+', '-', or \0) */
    u_long _ulong;                /* integer arguments %[diouxX] */

    enum { OCT, DEC, HEX } base; /* base for [diouxX] conversion */

    int dprec;               /* a copy of prec if [diouxX], 0 otherwise */
    int realsz;              /* field size expanded by dprec */
    int size;                /* size of converted field or string */
    const char *xdigs;       /* digits for [xX] conversion */
    struct __suio uio;       /* output information: summary */
    struct __siov iov[NIOV]; /* ... and individual io vectors */
    char buf[BUF];           /* space for %c, %[diouxX], %[eEfgG] */
    char ox[2];              /* space for 0x hex-prefix */
    int wc;
    int state;

/*
 * Choose PADSIZE to trade efficiency vs size.  If larger printf
 * fields occur frequently, increase PADSIZE (and make the initialisers
 * below longer).
 */
#define PRINT(ptr, len)                                                                            \
    {                                                                                              \
        iovp->iov_base = (void *)(ptr);                                                            \
        iovp->iov_len = (len);                                                                     \
        uio.uio_resid += (len);                                                                    \
        iovp++;                                                                                    \
        if (++uio.uio_iovcnt >= NIOV) {                                                            \
            if (__sprint((int)fp, (int *)&uio))                                                    \
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
        if (uio.uio_resid && __sprint((int)fp, (int *)&uio))                                       \
            goto error;                                                                            \
        uio.uio_iovcnt = 0;                                                                        \
        iovp = iov;                                                                                \
    }

#define SARG()                                                                                     \
    (flags & LONGINT    ? va_arg(ap, long)                                                         \
     : flags & SHORTINT ? (long)(short)va_arg(ap, int)                                             \
                        : (long)va_arg(ap, int))
#define UARG()                                                                                     \
    (flags & LONGINT    ? va_arg(ap, u_long)                                                       \
     : flags & SHORTINT ? (u_long)(u_short)va_arg(ap, int)                                         \
                        : (u_long)va_arg(ap, u_int))

    state = 0;

    /* sorry, fprintf(read_only_file, "") returns EOF, not 0 */
    if ((fp->_flags & 0x8) == 0 || fp->_bf_base == NULL) {
        if (__swsetup(fp))
            return -1;
    }

    /* optimise fprintf(stderr) (and other unbuffered Unix files) */
    if ((fp->_flags & (0x2 | 0x8 | 0x10)) == (0x2 | 0x8) && fp->_file >= 0)
        return __sbprintf(fp, (char *)fmt0, ap);

    fmt = fmt0;
    uio.uio_iov = iovp = iov;
    uio.uio_resid = 0;
    uio.uio_iovcnt = 0;
    ret = 0;

    /*
     * Scan the format for conversions (`%' character).
     */
    for (;;) {
        cp = (char *)fmt;
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
            /*
             * ``If the space and + flags both appear, the space
             * flag will be ignored.''
             *	-- ANSI X3J11
             */
            if (!sign)
                sign = ' ';
            goto rflag;
        case '#':
            flags |= ALT;
            goto rflag;
        case '*':
            /*
             * ``A negative field width argument is taken as a
             * - flag followed by a positive field width.''
             *	-- ANSI X3J11
             * They don't exclude field widths read from args.
             */
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
            /*
             * ``Note that 0 is taken as a flag, not as the
             * beginning of a field width.''
             *	-- ANSI X3J11
             */
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
            _ulong = SARG();
            if ((long)_ulong < 0) {
                _ulong = -_ulong;
                sign = '-';
            }
            base = DEC;
            goto number;
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
            _ulong = UARG();
            base = OCT;
            goto nosign;
        case 'p':
            /*
             * ``The argument shall be a pointer to void.  The
             * value of the pointer is converted to a sequence
             * of printable characters, in an implementation-
             * defined manner.''
             *	-- ANSI X3J11
             */
            /* NOSTRICT */
            _ulong = (u_long)va_arg(ap, void *);
            base = HEX;
            xdigs = "0123456789abcdef";
            flags |= HEXPREFIX;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = va_arg(ap, char *)) == NULL)
                cp = (char *)"(null)";
            if (prec >= 0) {
                /*
                 * can't use strlen; can only look for the
                 * NUL in the first `prec' characters, and
                 * strlen() will go further.
                 */
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
            _ulong = UARG();
            base = DEC;
            goto nosign;
        case 'X':
            xdigs = "0123456789ABCDEF";
            goto hex;
        case 'x':
            xdigs = "0123456789abcdef";
        hex:
            _ulong = UARG();
            base = HEX;
            /* leading 0x/X only if non-zero */
            if (flags & ALT && _ulong != 0)
                flags |= HEXPREFIX;

            /* unsigned conversions */
        nosign:
            sign = '\0';
            /*
             * ``... diouXx conversions ... if a precision is
             * specified, the 0 flag will be ignored.''
             *	-- ANSI X3J11
             */
        number:
            if ((dprec = prec) >= 0)
                flags &= ~ZEROPAD;

            /*
             * ``The result of converting a zero value with an
             * explicit precision of zero is no characters.''
             *	-- ANSI X3J11
             */
            cp = buf + BUF;
            if (_ulong != 0 || dprec != 0) {
                /*
                 * unsigned mod is hard, and unsigned mod
                 * by a constant is easier than that by
                 * a variable; hence this switch.
                 */
                switch (base) {
                case OCT:
                    do {
                        *--cp = to_char(_ulong & 7);
                        _ulong >>= 3;
                    } while (_ulong);
                    /* handle octal leading 0 */
                    if (flags & ALT && *cp != '0')
                        *--cp = '0';
                    break;

                case DEC:
                    /* many numbers are 1 digit */
                    while (_ulong >= 10) {
                        *--cp = to_char(_ulong % 10);
                        _ulong /= 10;
                    }
                    *--cp = to_char(_ulong);
                    break;

                case HEX:
                    do {
                        *--cp = xdigs[_ulong & 15];
                        _ulong >>= 4;
                    } while (_ulong);
                    break;

                default:
                    cp = (char *)"bug in vfprintf: bad base";
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

        /*
         * All reasonable formats wind up here.  At this point, `cp'
         * points to a string which (if not flags&LADJUST) should be
         * padded out to `width' places.  If flags&ZEROPAD, it should
         * first be prefixed by any sign or other prefix; otherwise,
         * it should be blank padded before the prefix is emitted.
         * After any left-hand padding and prefixing, emit zeroes
         * required by a decimal [diouxX] precision, then print the
         * string proper, then emit zeroes required by any leftover
         * floating precision; finally, if LADJUST, pad with blanks.
         *
         * Compute actual size, so we know how much to pad.
         */
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
        PRINT(cp, size);
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
    return (fp->_flags & 0x40) ? -1 : ret;
    /* NOTREACHED */
}

extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);
extern void _fwalk(int a0, void *a1);
extern int memcpy(char *a0, char *a1, int a2);
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
