/* Vendor SCE library member: libcdvd.a(cdvd047).  The stream entry points and the IOP stream helper.  The January
 * member ends at sceCdStream, where MAIN.MAP's 0x4E0 ends too: _send_to_iop after
 * it is libpad.o's first function (the listing's jal from libpad at 0x26C754, its
 * string is libpad.o's first .rodata entry).  Rung: MAIN.MAP member
 * sizes tile the retail run (cdvd000 0x1434, cdvd005 0x1E0, cdvd006 0x154,
 * cdvd014 0x98, cdvd015 0x98, cdvd047 0x4E0 up to sceCdStream's end), and
 * SRCFILE.TXT's libcdvd is the retail revision function for function. */
#include "common.h"
#include <eekernel.h>
#include <stdio.h>
#include <sifrpc.h>

typedef struct {
    int f0;
    int *f4;
    int f8;
    int fC;
    int f10;
    char pad14[0x8];
} PObjA8B8Ent;

extern int SCE_CD_debug;
extern int _sceCd_cd_ncmd[];
extern int _sceCd_ncmd_semid;
extern int _sceCd_ncmdrdata[];
extern int _sceCd_ncmd_prechk(int a0);
extern int sceSifCallRpc();
extern void sceSifWriteBackDCache(void *p, int n);

typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdRMode;

/* The member's own .data word: set by sceCdStStart and sceCdStResume, cleared
 * by sceCdStInit, sceCdStStop and sceCdStPause, and tested by sceCdStRead
 * (explicit zero initialiser: the ROM keeps it in .data, not .bss). */
static int stStarted = 0;

/* The member's own .bss: the mode record every call but sceCdStStart passes. */
static CdRMode stMode;

extern int sceCdStream(int a0, int a1, int a2, int a3, CdRMode *mode);

int sceCdStInit(int a0, int a1, int a2)
{
    stStarted = 0;
    return sceCdStream(a0, a1, a2, 5, &stMode);
}

int sceCdStStart(int a0, void *a1)
{
    stStarted = 1;
    return sceCdStream(a0, 0, 0, 1, a1);
}

int sceCdStSeekF(int a0)
{
    return sceCdStream(a0, 0, 0, 9, &stMode);
}

int sceCdStSeek(int a0)
{
    return sceCdStream(a0, 0, 0, 4, &stMode);
}

int sceCdStStop(void)
{
    stStarted = 0;
    return sceCdStream(0, 0, 0, 3, &stMode);
}

extern void sceCdDelayThread(unsigned short a0);

int sceCdStRead(int sectors, void *buf, int mode, int *err)
{
    int got;
    unsigned int r;
    unsigned int n;
    int e;
    int rerr;

    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStRead call read size= %d mode= %d\n", sectors);
    }
    if (stStarted == 0) {
        return 0;
    }
    rerr = 0;
    got = 0;
    sceSifWriteBackDCache(buf, sectors << 11);
    if (mode != 0) {
        do {
            r = sceCdStream(0, sectors - got, (char *)buf + (got << 11), 2, &stMode);
            n = r & 0xFFFF;
            e = r >> 16;
            got += n;
            if (e != 0) {
                rerr = e;
                if (SCE_CD_debug > 0) {
                    scePrintf(
                        "sceCdStRead BLK Read cur_size= %d read_size= %d req_size= %d err 0x%x\n",
                        got, n, sectors, e);
                }
            } else if (n == 0) {
                sceCdDelayThread(8);
            }
        } while (got != sectors && (e == 0 || n != 0));
        if (SCE_CD_debug > 0) {
            scePrintf("sceCdStRead BLK Read Ended\n");
        }
        *err = rerr;
    } else {
        r = sceCdStream(0, sectors, buf, 2, &stMode);
        e = r >> 16;
        got = r & 0xFFFF;
        *err = e;
    }
    return got;
}

int sceCdStPause(void)
{
    stStarted = 0;
    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStPause call\n");
    }
    return sceCdStream(0, 0, 0, 7, &stMode);
}

int sceCdStResume(void)
{
    stStarted = 1;
    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStResume call\n");
    }
    return sceCdStream(0, 0, 0, 8, &stMode);
}

int sceCdStStat(void)
{
    if (SCE_CD_debug > 0) {
        scePrintf("sceCdStStat call\n");
    }
    return sceCdStream(0, 0, 0, 6, &stMode);
}

extern int _sceCd_ncmdsdata[];

typedef struct {
    int f0;
    int f4;
    int f8;
    int cmd;
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdStreamCmd;

int sceCdStream(int a0, int a1, int a2, int cmd, CdRMode *mode)
{
    CdStreamCmd *sd = (CdStreamCmd *)_sceCd_ncmdsdata;
    int *p;
    int v;

    if (_sceCd_ncmd_prechk(0xF) == 0) {
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("call cdreadstm call\n");
    }
    sd->f0 = a0;
    sd->f4 = a1;
    sd->f8 = a2;
    sd->cmd = cmd;
    if (mode != 0) {
        sd->trycount = mode->trycount;
        sd->spindlctrl = mode->spindlctrl;
        sd->datapattern = mode->datapattern;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("call cdreadstm cmd\n");
    }
    sceSifWriteBackDCache(sd, 0x14);
    p = _sceCd_ncmdrdata;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 9, 0, sd, 0x14, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid);
        return 0;
    }
    if (SCE_CD_debug > 0) {
        scePrintf("cdread end\n");
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_ncmd_semid);
    return v;
}
