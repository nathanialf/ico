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

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/kprintf", ftoi);
INCLUDE_ASM("asm/nonmatchings/sce/libkernl/kprintf", printfloat);
INCLUDE_ASM("asm/nonmatchings/sce/libkernl/kprintf", _printf);

extern int _printf(int a0, void *va);

void kprintf(int a0, ...)
{
    void *va = (char *)__builtin_next_arg(a0) - 0x38;
    _printf(a0, va);
}

void scePrintf(int a0, ...)
{
    void *va = (char *)__builtin_next_arg(a0) - 0x38;
    PutcharFn save = D_0028F4B8[0];

    D_0028F4B8[0] = deci2Putchar;
    _printf(a0, va);
    D_0028F4B8[0] = save;
}
