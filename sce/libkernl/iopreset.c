/* Vendor SCE library member: libkernl.a(iopreset.o).  MAIN.MAP names the
 * member and its .text size (0x2B0), which tiles the shipped ELF from one
 * retail function start to the next; VMA 0x264838..0x264AE8,
 * 4 functions. */

#include <sifrpc.h>
#include <string.h>
#include <sifcmd.h>

/* sifrpc.o's definition: a void call, no value register after it */
extern void sceSifExitRpc(void);
static SifCmdResetData resetData __attribute__((aligned(16))); /* derived name */
extern void sceSifStopDma(void);

int sceSifResetIop(char *arg, int mode)
{
    SifDmaTransfer dma;
    int i;
    unsigned int addr;

    sceSifStopDma();
    addr = sceSifGetReg(0x80000000);
    resetData.mode = mode;
    for (i = 0; arg[i] != 0; i++) {
        resetData.arg[i] = arg[i];
    }
    resetData.arglen = i;
    resetData.header.dest = 0;
    resetData.header.cid = 0x80000003;
    resetData.header.dsize = 0;
    resetData.header.psize = sizeof(resetData);
    dma.src = (int)&resetData;
    dma.dest = addr;
    dma.size = sizeof(resetData);
    dma.u.attr = 0x44;
    sceSifWriteBackDCache(&resetData, sizeof(resetData));
    if (sceSifSetDma((int)&dma, 1) != 0) {
        sceSifSetReg(4, 0x10000);
        sceSifSetReg(4, 0x20000);
        sceSifSetReg(0x80000002, 0);
        sceSifSetReg(0x80000000, 0);
        return 1;
    }
    return 0;
}

int sceSifIsAliveIop(void)
{
    int t = sceSifGetReg(4) & 0x10000;
    return t != 0;
}

extern void sceResetttyinit();

int sceSifSyncIop(void)
{
    if (sceSifGetReg(4) & 0x40000) {
        sceSifSetReg(4, 0x40000);
        ((void (*)(void))sceResetttyinit)();
        return 1;
    }
    return 0;
}

extern int printf(const char *fmt, ...);
extern int sceSifResetIop(char *arg, int mode);

int sceSifRebootIop(const char *arg)
{
    char buf[80];
    char *s = "rom0:UDNL ";
    char *d;
    char *p;

    for (p = (char *)arg; *p != 0; p++) {}
    /* the ten characters of "rom0:UDNL " plus the terminator */
    if ((unsigned int)(p + 11 - (char *)arg) > 80) {
        printf("too long parameter '%s'\n", arg);
        return 0;
    }
    sceSifInitRpc(0);
    sceSifExitRpc();
    d = buf;
    while (*s != 0) {
        *d++ = *s++;
    }
    while (*arg != 0) {
        *d++ = *arg++;
    }
    *d = 0;
    return sceSifResetIop(buf, 0);
}
