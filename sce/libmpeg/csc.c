/* Vendor SCE library member: libmpeg.a(csc.o).  MAIN.MAP's member size (0x71C)
 * tiles the retail run, VMA 0x271938..0x272054, 5 functions, then 4 bytes of
 * link fill to bit.o: the IPU colour space conversion and its DMA feeders. */
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
    _dispatchMpegCallback(_theSceMpeg[0], buf);
    while (((*(volatile unsigned int *)0x1000B000) >> 8) & 1) {}
    while (*(volatile int *)0x10002010 < 0) {}
}

extern int D_0054CAB8[];
/* the chunk count (MAIN.MAP's _cscDma): this channel-3 handler bumps it while
 * _doCSC2 polls it, so every read is fresh */
extern volatile int _cscDma[];
extern int D_007315D0[];
extern int D_007315D4[];
extern int D_007315D8[];

int _ch3dmaCSC(void)
{
    *(volatile int *)0x1000E010 = 8;
    _cscDma[0]++;
    if (*(volatile int *)0x1000B020 != 0 || (*(volatile int *)0x1000B000 & 0x100) != 0) {
        D_0054CAB8[0] = 1;
        return 0;
    }
    if (_cscDma[0] < D_007315D8[0] - 1) {
        *(volatile int *)0x1000B010 = D_007315D4[0];
        *(volatile int *)0x1000B020 = 0xFFC0;
        *(volatile int *)0x1000B000 = 0x100;
        *(volatile int *)0x10002000 = 0x700003FF;
        D_007315D4[0] = (D_007315D4[0] + 0xFFC00) & 0x0FFFFFFF;
    } else if (_cscDma[0] == D_007315D8[0] - 1) {
        D_007315D0[0] -= _cscDma[0] * 1023;
        *(volatile int *)0x1000B010 = D_007315D4[0];
        *(volatile int *)0x1000B020 = D_007315D0[0] << 6;
        *(volatile int *)0x1000B000 = 0x100;
        *(volatile int *)0x10002000 = D_007315D0[0] | 0x70000000;
    }
    __asm__ __volatile__("sync");
    __asm__ __volatile__("ei");
    return 0;
}

extern int AddDmacHandler(int a0, int (*a1)(void), int a2);
extern int EnableDmac(int a0);
extern int DisableDmac(int a0);
extern int RemoveDmacHandler(int a0, int a1);

/* More than 1023 macroblocks: the conversion runs in 1023-macroblock chunks,
 * the first kicked here and the rest by _ch3dmaCSC.  The first chunk's
 * quadword count is named once at the top; the compiler re-materialises it
 * just before its store, after the first scheduling pass, and that pass's
 * order is what puts the callback kind in $a0 ahead of the IPU command write
 * (the bytes pin the moved constant, not the variable's name). */
void _doCSC2(int a0, int a1)
{
    int buf[8];
    int id;
    int qwc = 0xFFC0;

    D_007315D8[0] = a1 / 1023 + 1;
    D_007315D0[0] = a1;
    D_007315D4[0] = (a0 + 0xFFC00) & 0x0FFFFFFF;
    D_0054CAB8[0] = 0;
    _cscDma[0] = 0;
    while (*(volatile int *)0x10002010 < 0) {}
    id = AddDmacHandler(3, _ch3dmaCSC, 0);
    *(volatile int *)0x1000E010 = 8;
    EnableDmac(3);
    *(volatile int *)0x1000B010 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000B020 = qwc;
    *(volatile int *)0x1000B000 = 0x100;
    *(volatile int *)0x10002000 = 0x700003FF;
    buf[0] = 4;
    /* the handle read in int's alias set, as mpc.c's _groupOfPicturesHeader
     * reads it: the load then waits for the register writes, after the
     * record store */
    _dispatchMpegCallback((void *)((int *)_theSceMpeg)[0], buf);
    while (_cscDma[0] < D_007315D8[0]) {}
    if (*(volatile int *)D_0054CAB8 != 0) {
        _Error("CSC handler error\n");
    }
    while (*(volatile int *)0x10002010 < 0) {}
    DisableDmac(3);
    RemoveDmacHandler(3, id);
}

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

extern void _doCSC2(int a0, int a1);
extern int AddDmacHandler(int a0, int (*a1)(void), int a2);
extern int EnableDmac(int a0);
extern int DisableDmac(int a0);
extern int RemoveDmacHandler(int a0, int a1);

void _csc_storeRefImage(char *p)
{
    int buf[8];
    void *self = _theSceMpeg[0];
    char *r = (char *)*(int *)((char *)self + 0x40);
    int n;
    int addr;
    int qwc;
    int hid;

    buf[0] = 2;
    n = *(int *)(p + 0xC) * *(int *)(p + 0x10);
    _dispatchMpegCallback(self, buf);
    if (*(volatile int *)0x10002010 & 0x4000) {
        *(int *)0x10002010 = 0x40000000;
    }
    while (*(volatile int *)0x10002010 < 0) {}
    _sendIpuCommand(0);
    while (*(volatile int *)0x10002010 < 0) {}
    addr = *(int *)p & 0x0FFFFFFF;
    qwc = n * 24;
    D_007315E0[0] = qwc;
    D_007315E4[0] = addr;
    if ((unsigned int)qwc > 0xFFFF) {
        hid = AddDmacHandler(4, _ch4dma, 0);
        *(volatile int *)0x1000E010 = 0x10;
        EnableDmac(4);
        *(volatile int *)0x1000B410 = D_007315E4[0];
        *(volatile int *)0x1000B420 = 0xFFFF;
        *(volatile int *)0x1000B400 = 0x101;
        D_007315E4[0] = (D_007315E4[0] + 0xFFFF0) & 0x0FFFFFFF;
        D_007315E0[0] -= 0xFFFF;
        if (n < 1024) {
            _doCSC(*(int *)(r + 0xD8), n);
        } else {
            _doCSC2(*(int *)(r + 0xD8), n);
        }
        DisableDmac(4);
        RemoveDmacHandler(4, hid);
    } else {
        *(volatile int *)0x1000B410 = D_007315E4[0];
        *(volatile int *)0x1000B420 = D_007315E0[0];
        *(volatile int *)0x1000B400 = 0x101;
        D_007315E0[0] = 0;
        if (n < 1024) {
            _doCSC(*(int *)(r + 0xD8), n);
        } else {
            _doCSC2(*(int *)(r + 0xD8), n);
        }
    }
    buf[0] = 3;
    _dispatchMpegCallback(_theSceMpeg[0], buf);
}
