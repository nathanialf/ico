/* Vendor SCE library member: libkernl.a(kprintf.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x1010C8..0x101A40, 8 functions. */
#include "common.h"

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
extern PutcharFn D_0028F4B8[];
extern void deci2Putchar(int c);
extern int D_0028F4B4[];
extern char D_0063CF60[];
extern void kputs(char *s);

void deci2Putchar(int c)
{
    int n;

    if (D_0028F4B4[0] >= 0x7E) {
        D_0028F4B4[0] = 0;
        D_0063CF60[0x7F] = 0;
        kputs(D_0063CF60);
    }
    n = D_0028F4B4[0];
    if (c == 0xA) {
        D_0028F4B4[0] = 0;
        D_0063CF60[n] = c;
        D_0063CF60[n + 1] = 0;
        kputs(D_0063CF60);
    } else {
        D_0028F4B4[0] = n + 1;
        D_0063CF60[n] = c;
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

extern int dpcmp(double a, double b);
extern double dpsub(double a, double b);
extern double dpmul(double a, double b);
extern double dpdiv(double a, double b);
extern unsigned long long __fixunsdfdi(double a);
extern void kprintf(char *fmt, ...);

void printfloat(double v)
{
    double zero = 0.0;
    int e = 0;
    int n;

    if (dpcmp(v, zero) < 0) {
        v = dpsub(zero, v);
        D_0028F4B8[0]('-');
    }
    if (dpcmp(v, 0.1) < 0) {
        while (dpcmp(v, 0.1) < 0) {
            v = dpmul(v, 10.0);
            e--;
        }
    } else if (dpcmp(v, 1.0) >= 0) {
        while (dpcmp(v, 1.0) >= 0) {
            v = dpdiv(v, 10.0);
            e++;
        }
    }
    v = dpmul(v, 1000000.0);
    n = ftoi(__fixunsdfdi(v));
    kprintf("0.%d", n);
    if (e >= 0) {
        kprintf("e+%d", e);
    } else {
        kprintf("e%d", e);
    }
}

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/kprintf", _printf);

extern int _printf(char *fmt, void *va);

void kprintf(char *fmt, ...)
{
    void *va = (char *)__builtin_next_arg(fmt) - 0x38;
    _printf(fmt, va);
}

void scePrintf(char *fmt, ...)
{
    void *va = (char *)__builtin_next_arg(fmt) - 0x38;
    PutcharFn save = D_0028F4B8[0];

    D_0028F4B8[0] = deci2Putchar;
    _printf(fmt, va);
    D_0028F4B8[0] = save;
}
