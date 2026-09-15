/* Vendor SCE library member: libipu.a(ipuinit.o).  MAIN.MAP's size (0x2A0) tiles the
 * retail run exactly, VMA 0x2725D8..0x272878, 2 functions. */
#include "common.h"

extern void DIntr(int *self);
extern void EIntr(void);

/* ipuinit.o's own file static setD4_CHCR (libmpeg holds the global of the name, which
   libipu.o's functions call); sceIpuInit calls this one. */
static void setD4_CHCR(int *a0)
{
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}

INCLUDE_ASM("asm/nonmatchings/sce/libipu/ipuinit", sceIpuInit);
