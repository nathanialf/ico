/* Vendor SCE library member: libcdvd.a(cdvd047).  The stream entry points and the IOP stream helper.  The January
 * member ends at sceCdStream; _send_to_iop is unreferenced (no jal, no address
 * word), so only a member linked for another symbol can carry it, and that is
 * this one, in the retail revision.  Rung: MAIN.MAP member
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

extern int SCE_CD_debug[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_ncmd_semid[];
extern int _sceCd_ncmdrdata[];
extern int _sceCd_ncmd_prechk(int a0);
extern int sceSifCallRpc();
extern void sceSifWriteBackDCache(void *p, int n);
extern int D_0054BFB0[];
extern int D_0072F1D8[];

typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdRMode;

extern int sceCdStream(int a0, int a1, int a2, int a3, CdRMode *mode);

int sceCdStInit(int a0, int a1, int a2)
{
    D_0054BFB0[0] = 0;
    return sceCdStream(a0, a1, a2, 5, D_0072F1D8);
}

int sceCdStStart(int a0, void *a1)
{
    D_0054BFB0[0] = 1;
    return sceCdStream(a0, 0, 0, 1, a1);
}

int sceCdStSeekF(int a0)
{
    return sceCdStream(a0, 0, 0, 9, D_0072F1D8);
}

int sceCdStSeek(int a0)
{
    return sceCdStream(a0, 0, 0, 4, D_0072F1D8);
}

int sceCdStStop(void)
{
    D_0054BFB0[0] = 0;
    return sceCdStream(0, 0, 0, 3, D_0072F1D8);
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/cdvd047", sceCdStRead);

extern char D_00636AB0[];

int sceCdStPause(void)
{
    D_0054BFB0[0] = 0;
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AB0);
    }
    return sceCdStream(0, 0, 0, 7, D_0072F1D8);
}

extern char D_00636AC8[];

int sceCdStResume(void)
{
    D_0054BFB0[0] = 1;
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AC8);
    }
    return sceCdStream(0, 0, 0, 8, D_0072F1D8);
}

extern int D_00636AE0[];

int sceCdStStat(void)
{
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AE0);
    }
    return sceCdStream(0, 0, 0, 6, D_0072F1D8);
}

extern int _sceCd_ncmdsdata[];
extern char D_00636AF8[];
extern char D_00636B10[];
extern char D_00636B28[];

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
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AF8);
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
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636B10);
    }
    sceSifWriteBackDCache(sd, 0x14);
    p = _sceCd_ncmdrdata;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 9, 0, sd, 0x14, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid[0]);
        return 0;
    }
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636B28);
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_ncmd_semid[0]);
    return v;
}

extern int D_0054BFCC[];
extern char D_00636B38[];
extern PObjA8B8Ent D_0072F250[][4];
extern int sceSifDmaStat(int a0);

void _send_to_iop(int a0, int a1)
{
    struct {
        int *f0;
        int f4;
        int f8;
        int fC;
        char rest[0xF0];
    } buf;

    int *p17 = D_0072F250[a0][a1].f4;
    int ret = sceSifDmaStat(D_0072F250[a0][a1].fC);

    if (ret >= 0) {
        if (D_0054BFCC[0] != 0) {
            printf(D_00636B38);
        }
    } else {
        int n = *p17 + 1;
        int v = D_0072F250[a0][a1].f8 + ((n & 1) << 5);
        int r;
        *p17 = n;
        SyncDCache(p17, (char *)p17 + 0x20);
        buf.f0 = p17;
        buf.f4 = v;
        buf.f8 = 0x20;
        buf.fC = 0;
        r = sceSifSetDma(&buf, 1);
        if (r == 0) {
            if (D_0054BFCC[0] != 0) {
                printf(D_00636B38);
            }
        }
        D_0072F250[a0][a1].fC = r;
    }
}
