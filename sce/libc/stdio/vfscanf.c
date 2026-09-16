/* libc.a member vfscanf.o.  MAIN.MAP member spans tile this run exactly and
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

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

/* newlib's struct __sbuf / struct __sFILE, reconstructed from the ROM's own
   field offsets in this member (evidence rung: ROM bytes; the newlib member
   layout gives the names). */
typedef struct {
    unsigned char *base; /* 0x0 */
    int size;            /* 0x4 */
} Sbuf;

typedef struct Fil {
    unsigned char *p; /* 0x00 */
    int r;            /* 0x04 */
    int w;            /* 0x08 */
    short flags;      /* 0x0C */
    short file;       /* 0x0E */
    Sbuf bf;          /* 0x10 */
    int lbfsize;      /* 0x18 */
    char pad1C[0x14]; /* 0x1C */
    Sbuf ub;          /* 0x30 */
} Fil;

/* newlib's _ctype_ table, reached one byte in (the EOF slot sits at -1). */
extern unsigned char D_00637E69[];

#define _U 001
#define _L 002
#define _N 004
#define _S 010
#define isspace(c) (D_00637E69[(int)(c)] & _S)
#define isupper(c) (D_00637E69[(int)(c)] & _U)

/* newlib's own table: the base a `%i` conversion falls back to, indexed by
   the base the format asked for (0 becomes 10). */
static const short basefix[17] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

typedef char *va_list;

/* The EE ABI's argument slot is 8 bytes wide (sscanf.c's own
   `__builtin_next_arg(...) - 48` counts six of them). */
#define va_arg(ap, type) (*(type *)((ap += 8) - 8))

typedef int wchar_t;

#define LONG 0x01
#define LONGDBL 0x02
#define SHORT 0x04
#define SUPPRESS 0x08
#define POINTER 0x10
#define NOSKIP 0x20
#define SIGNOK 0x40
#define NDIGITS 0x80
#define DPTOK 0x100
#define EXPOK 0x200
#define PFXOK 0x100
#define NZDIGITS 0x200
#define CT_CHAR 0
#define CT_CCL 1
#define CT_STRING 2
#define CT_INT 3
#define CT_FLOAT 4
#define u_char char
#define u_long unsigned long
#define MAXEXP 308
#define MAXFRACT 39
#define BUF (MAXEXP + MAXFRACT + 3)
#define EOF (-1)

extern int __srefill(Fil *fp);
extern int ungetc(int c, Fil *fp);
extern unsigned int fread(void *buf, int size, int count, Fil *fp);
extern u_char *__sccl(char *tab, u_char *fmt);
extern long strtol();
extern unsigned long strtoul();
/* newlib atof (sce/libc/stdlib/atof): strtod with a null end pointer. */
extern double atof(char *nptr);

#define BufferEmpty (fp->r <= 0 && __srefill(fp))

int __svfscanf(Fil *fp, const char *fmt0, va_list ap)
{
    register u_char *fmt = (u_char *)fmt0;
    register int c;
    register unsigned int width;
    register char *p;
    register int n;
    register int flags;
    register char *p0;
    int nassigned;
    int nread;
    int base = 0;
    int nbytes = 1;
    wchar_t wc;

    u_long (*ccfn)() = 0;
    char ccltab[256];
    char buf[BUF];
    char *lptr;

    short *sp;
    int *ip;
    float *flp;
    double *dp;
    long double *ldp;
    long *lp;

    nassigned = 0;
    nread = 0;
    for (;;) {
        wc = *fmt;
        fmt += nbytes;
        if (wc == 0)
            return nassigned;
        if (nbytes == 1 && isspace(wc)) {
            for (;;) {
                if (BufferEmpty)
                    return nassigned;
                if (!isspace(*fp->p))
                    break;
                nread++, fp->r--, fp->p++;
            }
            continue;
        }
        if (wc != '%')
            goto literal;
        width = 0;
        flags = 0;

    again:
        c = *fmt++;

        switch (c) {
        case '%':
        literal:
            lptr = fmt - nbytes;
            for (n = 0; n < nbytes; ++n) {
                if (BufferEmpty)
                    goto input_failure;
                if (*fp->p != *lptr)
                    goto match_failure;
                fp->r--, fp->p++;
                nread++;
                ++lptr;
            }
            continue;

        case '*':
            flags |= SUPPRESS;
            goto again;
        case 'l':
            flags |= LONG;
            goto again;
        case 'L':
            flags |= LONGDBL;
            goto again;
        case 'h':
            flags |= SHORT;
            goto again;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            width = width * 10 + c - '0';
            goto again;

        case 'D':
            flags |= LONG;
            /* FALLTHROUGH */
        case 'd':
            c = CT_INT;
            ccfn = (u_long (*)())strtol;
            base = 10;
            break;

        case 'i':
            c = CT_INT;
            ccfn = (u_long (*)())strtol;
            base = 0;
            break;

        case 'O':
            flags |= LONG;
            /* FALLTHROUGH */
        case 'o':
            c = CT_INT;
            ccfn = strtoul;
            base = 8;
            break;

        case 'u':
            c = CT_INT;
            ccfn = strtoul;
            base = 10;
            break;

        case 'X':
        case 'x':
            flags |= PFXOK;
            c = CT_INT;
            ccfn = strtoul;
            base = 16;
            break;

        case 'E':
        case 'G':
        case 'e':
        case 'f':
        case 'g':
            c = CT_FLOAT;
            break;

        case 's':
            c = CT_STRING;
            break;

        case '[':
            fmt = __sccl(ccltab, fmt);
            flags |= NOSKIP;
            c = CT_CCL;
            break;

        case 'c':
            flags |= NOSKIP;
            c = CT_CHAR;
            break;

        case 'p':
            flags |= POINTER | PFXOK;
            c = CT_INT;
            ccfn = strtoul;
            base = 16;
            break;

        case 'n':
            if (flags & SUPPRESS)
                continue;
            if (flags & SHORT) {
                sp = va_arg(ap, short *);
                *sp = nread;
            } else if (flags & LONG) {
                lp = va_arg(ap, long *);
                *lp = nread;
            } else {
                ip = va_arg(ap, int *);
                *ip = nread;
            }
            continue;

        case '\0':
            return EOF;

        default:
            if (isupper(c))
                flags |= LONG;
            c = CT_INT;
            ccfn = (u_long (*)())strtol;
            base = 10;
            break;
        }

        if (BufferEmpty)
            goto input_failure;

        if ((flags & NOSKIP) == 0) {
            while (isspace(*fp->p)) {
                nread++;
                if (--fp->r > 0)
                    fp->p++;
                else if (__srefill(fp))
                    goto input_failure;
            }
        }

        switch (c) {
        case CT_CHAR:
            if (width == 0)
                width = 1;
            if (flags & SUPPRESS) {
                unsigned int sum = 0;

                for (;;) {
                    if ((n = fp->r) < width) {
                        sum += n;
                        width -= n;
                        fp->p += n;
                        if (__srefill(fp)) {
                            if (sum == 0)
                                goto input_failure;
                            break;
                        }
                    } else {
                        sum += width;
                        fp->r -= width;
                        fp->p += width;
                        break;
                    }
                }
                nread += sum;
            } else {
                unsigned int r = fread((void *)va_arg(ap, char *), 1, width, fp);

                if (r == 0)
                    goto input_failure;
                nread += r;
                nassigned++;
            }
            break;

        case CT_CCL:
            if (width == 0)
                width = ~0;
            if (flags & SUPPRESS) {
                n = 0;
                while (ccltab[*fp->p]) {
                    n++, fp->r--, fp->p++;
                    if (--width == 0)
                        break;
                    if (BufferEmpty) {
                        if (n == 0)
                            goto input_failure;
                        break;
                    }
                }
                if (n == 0)
                    goto match_failure;
            } else {
                p0 = p = va_arg(ap, char *);
                while (ccltab[*fp->p]) {
                    fp->r--;
                    *p++ = *fp->p++;
                    if (--width == 0)
                        break;
                    if (BufferEmpty) {
                        if (p == p0)
                            goto input_failure;
                        break;
                    }
                }
                n = p - p0;
                if (n == 0)
                    goto match_failure;
                *p = 0;
                nassigned++;
            }
            nread += n;
            break;

        case CT_STRING:
            if (width == 0)
                width = ~0;
            if (flags & SUPPRESS) {
                n = 0;
                while (!isspace(*fp->p)) {
                    n++, fp->r--, fp->p++;
                    if (--width == 0)
                        break;
                    if (BufferEmpty)
                        break;
                }
                nread += n;
            } else {
                p0 = p = va_arg(ap, char *);
                while (!isspace(*fp->p)) {
                    fp->r--;
                    *p++ = *fp->p++;
                    if (--width == 0)
                        break;
                    if (BufferEmpty)
                        break;
                }
                *p = 0;
                nread += p - p0;
                nassigned++;
            }
            continue;

        case CT_INT:
            if (--width > sizeof(buf) - 2)
                width = sizeof(buf) - 2;
            width++;
            flags |= SIGNOK | NDIGITS | NZDIGITS;
            for (p = buf; width; width--) {
                c = *fp->p;
                switch (c) {
                case '0':
                    if (base == 0) {
                        base = 8;
                        flags |= PFXOK;
                    }
                    if (flags & NZDIGITS)
                        flags &= ~(SIGNOK | NZDIGITS | NDIGITS);
                    else
                        flags &= ~(SIGNOK | PFXOK | NDIGITS);
                    goto ok;

                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    base = basefix[base];
                    flags &= ~(SIGNOK | PFXOK | NDIGITS);
                    goto ok;

                case '8':
                case '9':
                    base = basefix[base];
                    if (base <= 8)
                        break;
                    flags &= ~(SIGNOK | PFXOK | NDIGITS);
                    goto ok;

                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                    if (base <= 10)
                        break;
                    flags &= ~(SIGNOK | PFXOK | NDIGITS);
                    goto ok;

                case '+':
                case '-':
                    if (flags & SIGNOK) {
                        flags &= ~SIGNOK;
                        goto ok;
                    }
                    break;

                case 'x':
                case 'X':
                    if (flags & PFXOK && p == buf + 1) {
                        base = 16;
                        flags &= ~PFXOK;
                        goto ok;
                    }
                    break;
                }

                break;
            ok:
                *p++ = c;
                if (--fp->r > 0)
                    fp->p++;
                else if (__srefill(fp))
                    break;
            }
            if (flags & NDIGITS) {
                if (p > buf)
                    ungetc(*(u_char *)--p, fp);
                goto match_failure;
            }
            c = ((u_char *)p)[-1];
            if (c == 'x' || c == 'X') {
                --p;
                ungetc(c, fp);
            }
            if ((flags & SUPPRESS) == 0) {
                u_long res;

                *p = 0;
                res = (*ccfn)(buf, (char **)0, base);
                if (flags & POINTER)
                    *(va_arg(ap, void **)) = (void *)(unsigned int)res;
                else if (flags & SHORT) {
                    sp = va_arg(ap, short *);
                    *sp = res;
                } else if (flags & LONG) {
                    lp = va_arg(ap, long *);
                    *lp = res;
                } else {
                    ip = va_arg(ap, int *);
                    *ip = res;
                }
                nassigned++;
            }
            nread += p - buf;
            break;

        case CT_FLOAT:
            if (--width > sizeof(buf) - 2)
                width = sizeof(buf) - 2;
            width++;
            flags |= SIGNOK | NDIGITS | DPTOK | EXPOK;
            for (p = buf; width; width--) {
                c = *fp->p;
                switch (c) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    flags &= ~(SIGNOK | NDIGITS);
                    goto fok;

                case '+':
                case '-':
                    if (flags & SIGNOK) {
                        flags &= ~SIGNOK;
                        goto fok;
                    }
                    break;
                case '.':
                    if (flags & DPTOK) {
                        flags &= ~(SIGNOK | DPTOK);
                        goto fok;
                    }
                    break;
                case 'e':
                case 'E':
                    if ((flags & (NDIGITS | EXPOK)) == EXPOK) {
                        flags = (flags & ~(EXPOK | DPTOK)) | SIGNOK | NDIGITS;
                        goto fok;
                    }
                    break;
                }
                break;
            fok:
                *p++ = c;
                if (--fp->r > 0)
                    fp->p++;
                else if (__srefill(fp))
                    break;
            }
            if (flags & NDIGITS) {
                if (flags & EXPOK) {
                    while (p > buf)
                        ungetc(*(u_char *)--p, fp);
                    goto match_failure;
                }
                c = *(u_char *)--p;
                if (c != 'e' && c != 'E') {
                    ungetc(c, fp);
                    c = *(u_char *)--p;
                }
                ungetc(c, fp);
            }
            if ((flags & SUPPRESS) == 0) {
                double res;

                *p = 0;
                res = atof(buf);
                if (flags & LONG) {
                    dp = va_arg(ap, double *);
                    *dp = res;
                } else if (flags & LONGDBL) {
                    ldp = va_arg(ap, long double *);
                    *ldp = res;
                } else {
                    flp = va_arg(ap, float *);
                    *flp = res;
                }
                nassigned++;
            }
            nread += p - buf;
            break;
        }
    }
input_failure:
    return nassigned ? nassigned : -1;
match_failure:
    return nassigned;
}

char *__sccl(char *tab, char *fmt)
{
    int c;
    int n;
    int v;

    c = *fmt++;
    if (c == '^') {
        v = 1;
        c = *fmt++;
    } else {
        v = 0;
    }

    for (n = 0; n < 256; n++) {
        tab[n] = v;
    }
    if (c == 0) {
        return fmt - 1;
    }

    v = 1 - v;
    for (;;) {
        tab[c] = v;
    doswitch:
        n = *fmt++;
        switch (n) {
        case 0:
            return fmt - 1;

        case '-':
            n = *fmt;
            if (n == ']' || n < c) {
                c = '-';
                break;
            }
            fmt++;
            do {
                tab[++c] = v;
            } while (c < n);
            goto doswitch;

        case ']':
            return fmt;

        default:
            c = n;
            break;
        }
    }
}
