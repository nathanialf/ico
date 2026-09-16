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
/* libipu.a's build stamp, exactly sixteen characters with no terminator,
   the first object in ipuinit.o's .data. */
static char sceIpuVersion[16] = "PsIIlibipu  2200";

/* The quantiser matrices sceIpuInit feeds to the IPU command FIFO: the four
   quadwords of the MPEG default INTRA matrix, then one quadword of 16 that
   is written four times to fill the flat NON-INTRA matrix.  The byte view
   carries the values, the quadword view carries the 16-byte alignment and
   the volatile the shipped code's per-write reload of element 4. */
static union {
    unsigned char b[80];
    volatile u128_ipu q[5];
} ipuQuantMatrix = {{8,  16, 16, 19, 16, 19, 22, 22, 22, 22, 22, 22, 26, 24, 26, 27,
                     27, 27, 26, 26, 26, 26, 27, 27, 27, 29, 29, 29, 34, 34, 34, 29,
                     29, 29, 27, 27, 29, 29, 32, 32, 34, 34, 37, 38, 37, 35, 35, 34,
                     35, 38, 38, 40, 40, 40, 48, 48, 46, 46, 56, 56, 58, 69, 69, 83,
                     16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}};

/* The sixteen-entry RGBA5551 colour table that follows it. */
static union {
    unsigned short c[16];
    u128_ipu q[2];
} ipuColorTable = {{0x0000, 0x0421, 0x0842, 0x03E0, 0x1084, 0x14A5, 0x18C6, 0x1CE7, 0x001F, 0x2529,
                    0x294A, 0x7C00, 0x318C, 0x35AD, 0x7FFF, 0x39CE}};

void sceIpuInit(void)
{
    setD4_CHCR((int *)1);
    *(volatile int *)0x10002010 = 0x40000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[0];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[1];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[2];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[3];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[4];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[4];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[4];
    *(volatile u128_ipu *)0x10007010 = ipuQuantMatrix.q[4];
    *(volatile int *)0x10002000 = 0x50000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0x58000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile u128_ipu *)0x10007010 = ipuColorTable.q[0];
    *(volatile u128_ipu *)0x10007010 = ipuColorTable.q[1];
    *(volatile int *)0x10002000 = 0x60000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0x90000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002010 = 0x40000000;
    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x10002000 = 0;
    while (*(volatile int *)0x10002010 < 0) {}
}
