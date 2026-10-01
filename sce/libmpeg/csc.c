/* Vendor SCE library member: libmpeg.a(csc.o).  MAIN.MAP's member size (0x71C)
 * tiles the retail run, VMA 0x271938..0x272054, 5 functions, then 4 bytes of
 * link fill to bit.o: the IPU colour space conversion and its DMA feeders. */
#include <libmpeg.h>
#include <libmpeg_internal.h>
#include <eeregs.h>
#include <eekernel.h>

void _doCSC(int a0, int a1)
{
    int buf[8];

    while (*IPU_CTRL < 0) {}
    *D3_MADR = a0 & 0x0FFFFFFF;
    *D3_QWC = a1 << 6;
    *D3_CHCR = 0x100;
    _sendIpuCommand(a1 | 0x70000000);
    buf[0] = 4;
    _dispatchMpegCallback(_theSceMpeg, buf);
    while (((*(volatile unsigned int *)D3_CHCR) >> 8) & 1) {}
    while (*IPU_CTRL < 0) {}
}

/* the member's .data: the conversion's error flag, then the chunk count
 * (MAIN.MAP's _cscDma, the member's one global): the channel-3 handler bumps
 * it while _doCSC2 polls it, so every read is fresh.  The ROM pins _cscDma's
 * 8-aligned start at +8 and the member's 0x18 end, not the array's length. */
static int cscError = 0; /* derived name */

volatile int _cscDma[4] = {0, 0, 0, 0};

/* the member's .bss: the macroblocks left, the next source address and the
 * chunk count of a conversion, then the qword count and address of the
 * reference-image store the channel-4 handler feeds */
static int cscRest; /* derived name */

static int cscAddr; /* derived name */

static int cscChunks; /* derived name */

static int storeCount; /* derived name */

static int storeQwc; /* derived name */

static int storeAddr; /* derived name */

int _ch3dmaCSC(int channel)
{
    *D_STAT = 8;
    _cscDma[0]++;
    if (*D3_QWC != 0 || (*D3_CHCR & 0x100) != 0) {
        cscError = 1;
        return 0;
    }
    if (_cscDma[0] < cscChunks - 1) {
        *D3_MADR = cscAddr;
        *D3_QWC = 0xFFC0;
        *D3_CHCR = 0x100;
        *IPU_CMD = 0x700003FF;
        cscAddr = (cscAddr + 0xFFC00) & 0x0FFFFFFF;
    } else if (_cscDma[0] == cscChunks - 1) {
        cscRest -= _cscDma[0] * 1023;
        *D3_MADR = cscAddr;
        *D3_QWC = cscRest << 6;
        *D3_CHCR = 0x100;
        *IPU_CMD = cscRest | 0x70000000;
    }
    __asm__ __volatile__("sync");
    __asm__ __volatile__("ei");
    return 0;
}

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

    cscChunks = a1 / 1023 + 1;
    cscRest = a1;
    cscAddr = (a0 + 0xFFC00) & 0x0FFFFFFF;
    cscError = 0;
    _cscDma[0] = 0;
    while (*IPU_CTRL < 0) {}
    id = AddDmacHandler(3, _ch3dmaCSC, 0);
    *D_STAT = 8;
    EnableDmac(3);
    *D3_MADR = a0 & 0x0FFFFFFF;
    *D3_QWC = qwc;
    *D3_CHCR = 0x100;
    *IPU_CMD = 0x700003FF;
    buf[0] = 4;
    /* the handle read in int's alias set, as mpc.c's _groupOfPicturesHeader
     * reads it: the load then waits for the register writes, after the
     * record store */
    _dispatchMpegCallback((void *)(int)_theSceMpeg, buf);
    while (_cscDma[0] < cscChunks) {}
    if (*(volatile int *)&cscError != 0) {
        _Error("CSC handler error\n");
    }
    while (*IPU_CTRL < 0) {}
    DisableDmac(3);
    RemoveDmacHandler(3, id);
}

int _ch4dma(int channel)
{
    *D_STAT = 0x10;
    storeCount++;
    if (storeQwc == 0)
        return 1;
    if ((unsigned int)storeQwc > 0xFFFF) {
        *D4_MADR = storeAddr;
        *D4_QWC = 0xFFFF;
        *D4_CHCR = 0x101;
        storeAddr = (storeAddr + 0xFFFF0) & 0xFFFFFFF;
        storeQwc -= 0xFFFF;
    } else {
        *D4_MADR = storeAddr;
        *D4_QWC = storeQwc;
        *D4_CHCR = 0x101;
        storeQwc = 0;
    }
    return 0;
}

void _csc_storeRefImage(char *p)
{
    int buf[8];
    void *self = _theSceMpeg;
    char *r = (char *)*(int *)((char *)self + 0x40);
    int n;
    int addr;
    int qwc;
    int hid;

    buf[0] = 2;
    n = *(int *)(p + 0xC) * *(int *)(p + 0x10);
    _dispatchMpegCallback(self, buf);
    if (*IPU_CTRL & 0x4000) {
        *(int *)IPU_CTRL = 0x40000000;
    }
    while (*IPU_CTRL < 0) {}
    _sendIpuCommand(0);
    while (*IPU_CTRL < 0) {}
    addr = *(int *)p & 0x0FFFFFFF;
    qwc = n * 24;
    storeQwc = qwc;
    storeAddr = addr;
    if ((unsigned int)qwc > 0xFFFF) {
        hid = AddDmacHandler(4, _ch4dma, 0);
        *D_STAT = 0x10;
        EnableDmac(4);
        *D4_MADR = storeAddr;
        *D4_QWC = 0xFFFF;
        *D4_CHCR = 0x101;
        storeAddr = (storeAddr + 0xFFFF0) & 0x0FFFFFFF;
        storeQwc -= 0xFFFF;
        if (n < 1024) {
            _doCSC(*(int *)(r + 0xD8), n);
        } else {
            _doCSC2(*(int *)(r + 0xD8), n);
        }
        DisableDmac(4);
        RemoveDmacHandler(4, hid);
    } else {
        *D4_MADR = storeAddr;
        *D4_QWC = storeQwc;
        *D4_CHCR = 0x101;
        storeQwc = 0;
        if (n < 1024) {
            _doCSC(*(int *)(r + 0xD8), n);
        } else {
            _doCSC2(*(int *)(r + 0xD8), n);
        }
    }
    buf[0] = 3;
    _dispatchMpegCallback(_theSceMpeg, buf);
}
