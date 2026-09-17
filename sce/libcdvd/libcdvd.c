/* Vendor SCE library run.  The archive attribution (libcdvd.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
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

extern void CB_DelayTh(void);

void sceCdDelayThread(unsigned short a0)
{
    int buf[8];
    unsigned short id = a0;
    int r;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    r = CreateSema(buf);
    SetAlarm(id, CB_DelayTh, r);
    WaitSema(r);
    DeleteSema(r);
}

extern void DIntr(int *self);
extern int D_0072EF00[];
extern void EIntr(void);
extern int sceCdSync(int a0);

int sceCdCallback(int a0)
{
    int ret;
    if (sceCdSync(1) != 0) {
        return 0;
    }
    (*(int (*)(void))DIntr)();
    ret = D_0072EF00[0];
    D_0072EF00[0] = a0;
    EIntr();
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", _sceCd_cd_callback);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", _Cdvd_cbLoop);

extern int D_0054A554;
extern int D_0072EF10;
extern int D_0072EF18[];
extern int D_0072EF48[];
extern char D_00640AF0[];
extern void _Cdvd_cbLoop(void);
extern int CreateThread(int *param);

int sceCdInitEeCB(int priority, void *stack, int stackSize)
{
    int r = 1;

    if (D_0054A554 == 0) {
        D_0072EF10 = GetThreadId();
        ReferThreadStatus(D_0072EF10, D_0072EF18);
        D_0072EF48[3] = stackSize;
        D_0072EF48[4] = (int)D_00640AF0;
        D_0072EF48[1] = (int)_Cdvd_cbLoop;
        D_0072EF48[2] = (int)stack;
        D_0072EF48[5] = priority;
        D_0054A554 = CreateThread(D_0072EF48);
        StartThread(D_0054A554, 0);
    } else {
        ChangeThreadPriority(D_0054A554, priority);
        r = 0;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", _sceCd_cd_read_intr);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", cmd_sem_init);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", cdvd_exit);

extern int D_0054A57C[];
extern void (*D_0072EF04[])(int);
extern int D_0072EF08[];
extern void PowerOffCB();

int sceCdPOffCallback(int a0, int a1)
{
    int ret;
    if (D_0054A57C[0] < 0) {
        PowerOffCB();
    }
    (*(int (*)(void))DIntr)();
    ret = (int)D_0072EF04[0];
    D_0072EF08[0] = a1;
    D_0072EF04[0] = (void (*)(int))a0;
    EIntr();
    return ret;
}

extern int D_0054A564[];

void _sceCd_Poff_Intr(void)
{
    if (D_0072EF04[0] != 0 && D_0054A564[0] == 0) {
        D_0072EF04[0](D_0072EF08[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", PowerOffCB);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdSearchFile);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", _sceCd_ncmd_prechk);

extern int _sceCd_ncmd_semid[];
extern int _sceCd_ncmdrdata[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_ncmd_prechk(int a0);
extern int sceSifCallRpc();

int sceCdNcmdDiskReady(void)
{
    int *p;
    int v;
    if (_sceCd_ncmd_prechk(2) == 0) {
        return 0;
    }
    p = _sceCd_ncmdrdata;
    if (sceSifCallRpc(_sceCd_cd_ncmd, 0xE, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_ncmd_semid[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_ncmd_semid[0]);
    return v;
}

extern int SCE_CD_debug[];
extern int _sceCd_cd_ncmd[];
extern int _sceCd_c_cb_sem;
extern char D_006368B8[];
extern int sceSifCheckStatRpc(char *a0);

int sceCdSync(int mode)
{
    if (!mode) {
        if (SCE_CD_debug[0] > 0)
            scePrintf(D_006368B8);
        while (_sceCd_c_cb_sem != 0 || sceSifCheckStatRpc((char *)_sceCd_cd_ncmd)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    if (_sceCd_c_cb_sem != 0 || sceSifCheckStatRpc((char *)_sceCd_cd_ncmd) != 0) {
        return 1;
    }
    return 0;
}

extern char _sceCd_cd_scmd[];
extern char D_006368C8[];

int sceCdSyncS(int a0)
{
    if (!a0) {
        if (SCE_CD_debug[0] > 0)
            scePrintf(D_006368C8);
        while (sceSifCheckStatRpc(_sceCd_cd_scmd)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    return sceSifCheckStatRpc(_sceCd_cd_scmd);
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", _sceCd_scmd_prechk);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdInit);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdDiskReady);

extern int _sceCd_scmdsdata[];
extern int _sceCd_scmdrdata[];
extern int _sceCd_scmd_semid[];
extern int _sceCd_scmd_prechk(int a0);
extern void sceSifWriteBackDCache(void *p, int n);

int sceCdMmode(int media)
{
    int *p;
    int *sd;
    int v;
    sd = _sceCd_scmdsdata;
    if (_sceCd_scmd_prechk(0x22) == 0) {
        return 0;
    }
    sd[0] = media;
    sceSifWriteBackDCache(sd, 4);
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 0x22, 0, sd, 4, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdRead);
INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdReadIOPm);

int sceCdGetDiskType(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(1) == 0) {
        return 0;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 3, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}

int sceCdGetError(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(3) == 0) {
        return -1;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 4, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return -1;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}

extern char D_006369C8[];

int sceCdStatus(void)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(2) == 0) {
        return -1;
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 0xC, 0, 0, 0, p, 4, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return -1;
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    if (SCE_CD_debug[0] > 1) {
        scePrintf(D_006369C8);
    }
    return v;
}

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdBreak);

extern char D_006369D8[];
extern char D_006369F8[];

typedef struct {
    unsigned char b[8];
} CdClock;

int sceCdReadClock(CdClock *clock)
{
    int *p;
    int v;
    if (_sceCd_scmd_prechk(0xF) == 0) {
        return 0;
    }
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_006369D8);
    }
    p = _sceCd_scmdrdata;
    if (sceSifCallRpc(_sceCd_cd_scmd, 1, 0, 0, 0, p, 0x10, 0, 0) < 0) {
        SignalSema(_sceCd_scmd_semid[0]);
        return 0;
    }
    *clock = *(CdClock *)((int)(p + 1) | 0x20000000);
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_006369F8);
    }
    v = *(int *)((int)p | 0x20000000);
    SignalSema(_sceCd_scmd_semid[0]);
    return v;
}

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

INCLUDE_ASM("asm/nonmatchings/sce/libcdvd/libcdvd", sceCdStRead);

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
