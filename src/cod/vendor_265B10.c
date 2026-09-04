#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { int f0; int *f4; int f8; int fC; int f10; char pad14[0x8]; } PObjA8B8Ent;

extern int CreateSema(int *self);
extern int DeleteSema(int a0);
extern int SetAlarm(int a0, void *a1, int a2);
extern int WaitSema(int a0);
extern void func_00265AE4(void);

void sceCdDelayThread(unsigned short a0) {
    int buf[8];
    unsigned short id = a0;
    int r;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    r = CreateSema(buf);
    SetAlarm(id, (char *)func_00265AE4 + 4, r);
    WaitSema(r);
    DeleteSema(r);
}
extern void DIntr(int *self);
extern int D_0072EF00[];
extern void EIntr(void);
extern int sceCdSync(int a0);

int sceCdCallback(int a0) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", _sceCd_cd_callback);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", func_00265C70);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", _sceCd_cd_read_intr);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", cmd_sem_init);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", cdvd_exit);
extern int D_0054A57C[];
extern void (*D_0072EF04[])(int);
extern int D_0072EF08[];
extern void PowerOffCB();

int sceCdPOffCallback(int a0, int a1) {
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

void _sceCd_Poff_Intr(void) {
    if (D_0072EF04[0] != 0 && D_0054A564[0] == 0) {
        D_0072EF04[0](D_0072EF08[0]);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", PowerOffCB);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdSearchFile);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", _sceCd_ncmd_prechk);
extern int _sceCd_ncmd_semid[];
extern int _sceCd_ncmdrdata[];
extern int _sceCd_cd_ncmd[];
extern void SignalSema(int sema);
extern int _sceCd_ncmd_prechk(int a0);
extern int sceSifCallRpc();

int sceCdNcmdDiskReady(void) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdSync);
extern int SCE_CD_debug[];
extern char _sceCd_cd_scmd[];
extern char D_006368C8[];
extern void scePrintf();
extern int sceSifCheckStatRpc(char *a0);

int sceCdSyncS(int a0) {
    if (!a0) {
        if (SCE_CD_debug[0] > 0) scePrintf(D_006368C8);
        while (sceSifCheckStatRpc(_sceCd_cd_scmd)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    return sceSifCheckStatRpc(_sceCd_cd_scmd);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", _sceCd_scmd_prechk);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdInit);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdDiskReady);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdMmode);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdRead);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdReadIOPm);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdGetDiskType);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdGetError);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdBreak);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdReadClock);
extern int D_0054BFB0[];
extern int D_0072F1D8[];
extern int sceCdStream(int a0, int a1, int a2, int a3, void *a4);

int sceCdStInit(int a0, int a1, int a2) {
    D_0054BFB0[0] = 0;
    return sceCdStream(a0, a1, a2, 5, D_0072F1D8);
}
int sceCdStStart(int a0, void *a1) {
    D_0054BFB0[0] = 1;
    return sceCdStream(a0, 0, 0, 1, a1);
}
int sceCdStSeekF(int a0) {
    return sceCdStream(a0, 0, 0, 9, D_0072F1D8);
}
int sceCdStSeek(int a0) {
    return sceCdStream(a0, 0, 0, 4, D_0072F1D8);
}
int sceCdStStop(void) {
    D_0054BFB0[0] = 0;
    return sceCdStream(0, 0, 0, 3, D_0072F1D8);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdStRead);
extern char D_00636AB0[];

int sceCdStPause(void) {
    D_0054BFB0[0] = 0;
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AB0);
    }
    return sceCdStream(0, 0, 0, 7, D_0072F1D8);
}
extern char D_00636AC8[];

int sceCdStResume(void) {
    D_0054BFB0[0] = 1;
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AC8);
    }
    return sceCdStream(0, 0, 0, 8, D_0072F1D8);
}
extern int D_00636AE0[];

int sceCdStStat(void) {
    if (SCE_CD_debug[0] > 0) {
        scePrintf(D_00636AE0);
    }
    return sceCdStream(0, 0, 0, 6, D_0072F1D8);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_265B10", sceCdStream);
extern int D_0054BFCC[];
extern char D_00636B38[];
extern PObjA8B8Ent D_0072F250[][4];
extern void SyncDCache(void *a0, void *a1);
extern void printf();
extern int sceSifDmaStat(int a0);
extern int sceSifSetDma(void *a0, int a1);

void _send_to_iop(int a0, int a1) {
    struct { int *f0; int f4; int f8; int fC; char rest[0xF0]; } buf;
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
        SyncDCache(p17, (char *) p17 + 0x20);
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
