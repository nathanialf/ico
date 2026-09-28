/* Vendor SCE library member: libmpeg.a(bit.o).  MAIN.MAP's member size (0x20C)
 * tiles the retail run, VMA 0x272058..0x272264, the seven _sysbit functions of
 * the demultiplexer's bit reader.  The two DMA channel control helpers after
 * them (setD3_CHCR, setD4_CHCR, VMA 0x272268..0x272338) are libipu.o's own
 * functions in the listing, where libipu.o begins after bit.o's 4 bytes of
 * link fill; they stay in this file until libipu's row is moved to take them. */
#include "common.h"
#include <libmpeg.h>

extern void _sysbitFlush(int *a0, int a1);

void _sysbitInit(int *a0, int a1, int a2, int a3)
{
    a0[2] = a1;
    a0[3] = a1;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = 0;
    a0[8] = a2;
    a0[9] = a2 + a3;
    a0[0xA] = a3;
    _sysbitFlush(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/bit", _sysbitNext);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/bit", _sysbitFlush);

int _sysbitGet(int *self, int a1)
{
    int ret = _sysbitNext(self, a1);
    _sysbitFlush(self, a1);
    return ret;
}

int _sysbitMarker(int *self)
{
    int ret = _sysbitNext(self, 1);
    _sysbitFlush(self, 1);
    return ret;
}

void _sysbitJump(int *a0, int a1)
{
    long long x = *(long long *)(a0 + 6) + (a1 << 3);
    int v;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = x;
    v = a0[2] + (int)(x >> 3);
    a0[3] = v;
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        a0[3] = v - a0[10];
    }
    _sysbitFlush(a0, 0);
}

int _sysbitPtr(int *a0, int a1)
{
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

extern void DIntr(int *self);
extern int EIntr(void);

void setD3_CHCR(int *a0)
{
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B000 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}

void setD4_CHCR(int *a0)
{
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}
