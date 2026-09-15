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

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/kprintf", deci2Putchar);

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

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/kprintf", scePrintf);
