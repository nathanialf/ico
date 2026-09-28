/* Vendor SCE library member: libmpeg.a(csc.o).  MAIN.MAP's member size (0x71C)
 * tiles the retail run, VMA 0x271938..0x272054, 5 functions, then 4 bytes of
 * link fill to bit.o: the IPU colour space conversion and its DMA feeders. */
#include "common.h"
#include <libmpeg.h>

void _doCSC(int a0, int a1)
{
    int buf[8];

    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x1000B010 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000B020 = a1 << 6;
    *(volatile int *)0x1000B000 = 0x100;
    _sendIpuCommand(a1 | 0x70000000);
    buf[0] = 4;
    _dispatchMpegCallback(D_0054C0E4[0], buf);
    while (((*(volatile unsigned int *)0x1000B000) >> 8) & 1) {}
    while (*(volatile int *)0x10002010 < 0) {}
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/csc", _ch3dmaCSC);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/csc", _doCSC2);

extern int D_007315DC[];
extern int D_007315E0[];
extern int D_007315E4[];
extern int D_007315DC[];
extern int D_007315E0[];
extern int D_007315E4[];

int _ch4dma(void)
{
    *(volatile unsigned int *)0x1000E010 = 0x10;
    D_007315DC[0]++;
    if (D_007315E0[0] == 0)
        return 1;
    if ((unsigned int)D_007315E0[0] > 0xFFFF) {
        *(volatile unsigned int *)0x1000B410 = D_007315E4[0];
        *(volatile unsigned int *)0x1000B420 = 0xFFFF;
        *(volatile unsigned int *)0x1000B400 = 0x101;
        D_007315E4[0] = (D_007315E4[0] + 0xFFFF0) & 0xFFFFFFF;
        D_007315E0[0] -= 0xFFFF;
    } else {
        *(volatile unsigned int *)0x1000B410 = D_007315E4[0];
        *(volatile unsigned int *)0x1000B420 = D_007315E0[0];
        *(volatile unsigned int *)0x1000B400 = 0x101;
        D_007315E0[0] = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/csc", _csc_storeRefImage);
