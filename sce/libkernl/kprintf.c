/* libkernl.a(kprintf.o) */
#include <eekernel.h>

int kputchar(int c)
{
    unsigned int base;

    do {
        base = 0x10000000;
    } while (*(volatile unsigned int *)(base | 0xF130) & 0x8000);

    *(unsigned char *)(base | 0xF180) = c;
    return c;
}

typedef void (*PutcharFn)(int c);
/* this member does not include libkernl_internal.h, whose kputs conflicts with its
   own */
extern void deci2Putchar(int c);
/* this member's own declaration; libkernl_internal.h declares it as `void kputs(int a0)` */
extern void kputs(char *s);

/* deci2Putchar's line buffer and its fill count; kputs sends a full line. */
static int deci2_count = 0; /* derived name */

static char deci2_line[128]; /* derived name */

void deci2Putchar(int c)
{
    int n;

    if (deci2_count >= 0x7E) {
        deci2_count = 0;
        deci2_line[0x7F] = 0;
        kputs(deci2_line);
    }
    n = deci2_count;
    if (c == 0xA) {
        deci2_count = 0;
        deci2_line[n] = c;
        deci2_line[n + 1] = 0;
        kputs(deci2_line);
    } else {
        deci2_count = n + 1;
        deci2_line[n] = c;
    }
}

void serialPutchar(int c)
{
    if (c == 0xA) {
        kputchar(0xD);
        kputchar(0xA);
    } else {
        kputchar(c);
    }
}

/* the character sink _printf writes through; scePrintf swaps in deci2Putchar */
static PutcharFn putchar_fn = serialPutchar; /* derived name */

int ftoi(unsigned long long a)
{
    unsigned long long m = a;
    long long e;

    e = (long long)((m << 1) >> 53);
    e -= 1075;
    if (e < -53) {
        return 0;
    }
    if (e >= 13) {
        return 9999;
    }
    m = (m << 12) >> 12;
    m |= (unsigned long long)1 << 52;
    if (e < 0) {
        int s;

        e = -e;
        s = e - 2;
        m >>= s;
        if ((m & 3) == 3) {
            m = (m >> 2) + 1;
        } else {
            m >>= 2;
        }
    } else {
        m <<= e;
    }
    return (int)m;
}

/* this member does not include libkernl_internal.h, whose kputs conflicts with its
   own */
extern void kprintf(char *fmt, ...);

void printfloat(double v)
{
    double zero = 0.0;
    int e = 0;
    int n;

    if (v < zero) {
        v = zero - v;
        putchar_fn('-');
    }
    if (v < 0.1) {
        while (v < 0.1) {
            v *= 10.0;
            e--;
        }
    } else if (v >= 1.0) {
        while (v >= 1.0) {
            v /= 10.0;
            e++;
        }
    }
    v *= 1000000.0;
    n = ftoi(v);
    kprintf("0.%d", n);
    if (e >= 0) {
        kprintf("e+%d", e);
    } else {
        kprintf("e%d", e);
    }
}

void _printf(char *fmt, char *ap)
{
    char buf[32];
    char *s;
    char *p;
    char *pad;
    char *t;
    char *q;
    char c;
    int sz;
    int n;
    int m;
    long long val;
    unsigned long long uval;
    unsigned long long d;
    float f;

    s = fmt;
    while (*s) {
        c = *s;
        pad = 0;
        sz = 0;
        if (c == '%') {
            p = s + 1;
        next:
            s = p;
            switch (*s) {
            case '0':
                n = p[1] - '0';
                m = p[2];
                if ((unsigned char)n < 10) {
                    if ((unsigned int)(m - '0') < 10) {
                        n = n * 10 + (m - '0');
                        if (n >= 32) {
                            n = 31;
                        }
                        s = p + 2;
                    } else {
                        s = p + 1;
                    }
                    pad = &buf[31 - n];
                    if (n > 0) {
                        p = s + 1;
                    fill:
                        buf[31 - n] = '0';
                        n--;
                        if (n > 0) {
                            goto fill;
                        }
                        goto next;
                    }
                    p = s + 1;
                    goto next;
                }
                p++;
                goto next;
            case 'l':
                sz = 'l';
                p++;
                goto next;
            case 'h':
                sz = 'h';
                p++;
                goto next;
            case 'o':
                if (sz == 'l') {
                    ap += 8;
                    uval = *(unsigned long long *)(ap - 8);
                } else if (sz == 'h') {
                    ap += 8;
                    uval = *(unsigned short *)(ap - 8);
                } else {
                    ap += 8;
                    uval = *(unsigned int *)(ap - 8);
                }
                s = &buf[31];
                *s = 0;
                if (uval == 0) {
                    *--s = '0';
                    p++;
                } else {
                    p++;
                    do {
                        *--s = (uval & 7) + '0';
                        uval >>= 3;
                    } while (uval != 0);
                }
                if (pad != 0 && pad < s) {
                    s = pad;
                }
                while (*s) {
                    (*putchar_fn)(*s++);
                }
                break;
            case 'x':
                if (sz == 'l') {
                    ap += 8;
                    uval = *(unsigned long long *)(ap - 8);
                } else if (sz == 'h') {
                    ap += 8;
                    uval = *(unsigned short *)(ap - 8);
                } else {
                    ap += 8;
                    uval = *(unsigned int *)(ap - 8);
                }
                s = &buf[31];
                *s = 0;
                if (uval == 0) {
                    *--s = '0';
                    p++;
                } else {
                    p++;
                    do {
                        d = uval & 0xF;
                        if (d < 10) {
                            *--s = d + '0';
                        } else {
                            *--s = d + 'a' - 10;
                        }
                        uval >>= 4;
                    } while (uval != 0);
                }
                if (pad != 0 && pad < s) {
                    s = pad;
                }
                while (*s) {
                    (*putchar_fn)(*s++);
                }
                break;
            case 'd':
                if (sz == 'l') {
                    ap += 8;
                    val = *(long long *)(ap - 8);
                } else if (sz == 'h') {
                    ap += 8;
                    val = *(short *)(ap - 8);
                } else {
                    ap += 8;
                    val = *(int *)(ap - 8);
                }
                s = &buf[31];
                *s = 0;
                if (val == 0) {
                    *--s = '0';
                    p++;
                } else {
                    if (val < 0) {
                        val = -val;
                        (*putchar_fn)('-');
                    }
                    while (val != 0) {
                        *--s = val % 10 + '0';
                        val /= 10;
                    }
                    p++;
                }
                if (pad != 0 && pad < s) {
                    s = pad;
                }
                while (*s) {
                    (*putchar_fn)(*s++);
                }
                break;
            case 'u':
                if (sz == 'l') {
                    ap += 8;
                    uval = *(unsigned long long *)(ap - 8);
                } else if (sz == 'h') {
                    ap += 8;
                    uval = *(unsigned short *)(ap - 8);
                } else {
                    ap += 8;
                    uval = *(unsigned int *)(ap - 8);
                }
                s = &buf[31];
                *s = 0;
                if (uval == 0) {
                    *--s = '0';
                    p++;
                } else {
                    p++;
                    while (uval != 0) {
                        *--s = uval % 10 + '0';
                        uval /= 10;
                    }
                }
                if (pad != 0 && pad < s) {
                    s = pad;
                }
                while (*s) {
                    (*putchar_fn)(*s++);
                }
                break;
            case 'e':
            case 'f': {
                /* CRUTCH, open: the register variable x and the nop asm stand in for the
                 * hazard nop Sony's library assembler put between c.eq.s and
                 * bc1f here; neither assembler in the tree emits it. */
                register float x __asm__("$f12");

                ap += 8;
                f = *(float *)(ap - 8);
                x = f;
                __asm__("nop" : "=f"(x) : "0"(x));
                if (f == 0.0f) {
                    (*putchar_fn)('0');
                } else {
                    printfloat(x);
                }
                goto skip;
            }
            case 's':
                ap += 8;
                t = *(char **)(ap - 8);
                if (*t == 0) {
                    (*putchar_fn)('(');
                    (*putchar_fn)('n');
                    (*putchar_fn)('u');
                    (*putchar_fn)('l');
                    (*putchar_fn)('l');
                    (*putchar_fn)(')');
                } else {
                    q = t;
                    while (*q) {
                        (*putchar_fn)(*q);
                        q++;
                    }
                }
                goto skip;
            case 'c':
                ap += 8;
                val = *(char *)(ap - 8);
                (*putchar_fn)(val);
                goto skip;
            default:
                goto skip;
            }
        } else {
            p = s;
            (*putchar_fn)(c);
        skip:
            p++;
        }
        s = p;
    }
}

void kprintf(char *fmt, ...)
{
    void *va = (char *)__builtin_next_arg(fmt) - 0x38;
    _printf(fmt, va);
}

void scePrintf(char *fmt, ...)
{
    void *va = (char *)__builtin_next_arg(fmt) - 0x38;
    PutcharFn save = putchar_fn;

    putchar_fn = deci2Putchar;
    _printf(fmt, va);
    putchar_fn = save;
}
