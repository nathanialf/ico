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

typedef unsigned int u128_ipu __attribute__((mode(TI)));
/* volatile: the shipped code re-loads element [4] for each of its four FIFO
   writes instead of keeping it in a register; no data-model reason for the
   qualifier is known, the reload is what the ROM does. */
extern volatile u128_ipu D_0054CAE0[];
extern u128_ipu D_0054CB30[];

void sceIpuInit(void)
{
    setD4_CHCR((int *)1);
    *(volatile int *)0x10002010 = 0x40000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[0];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[1];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[2];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[3];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[4];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[4];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[4];
    *(volatile u128_ipu *)0x10007010 = D_0054CAE0[4];
    *(volatile int *)0x10002000 = 0x50000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0x58000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile u128_ipu *)0x10007010 = D_0054CB30[0];
    *(volatile u128_ipu *)0x10007010 = D_0054CB30[1];
    *(volatile int *)0x10002000 = 0x60000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0x90000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002010 = 0x40000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0;
    while (*(volatile int *)0x10002010 < 0) {}
}
