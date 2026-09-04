#include "common.h"

typedef struct { long long q[8]; } Mtx64;

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D15D0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void scpFadeOut(int a0, int a1, int a2, float f);
extern int func_0017B230(int a0);
extern void func_0017B258(int a0);
extern void func_002171D0(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04cEnd(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x7D) == 0) {
        func_0017B258(0x164);
        scpFadeOut(0, 0, 0, 255.0f);
        stage_KillPlayBgAnimation(0x104, 0, -1);
        D_004D15D0[1] = (int)func_002171D0;
        gobj->unkB4 = D_004D15D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04cDoorDownChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x102, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoorChk);

extern int D_004D1590[];
extern void actSt04bGirlWay(void);
extern void func_0012ABE0(int a0, int a1);

void actSt04cSolarXL(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x80) == 0) {
        stage_KillPlayBgAnimation(0xF4, 0, -1);
        stage_KillPlayBgAnimation(0xF5, 0, -1);
        stage_KillPlayBgAnimation(0xF6, 0, -1);
        func_0012ABE0(0x1E4, 0);
        D_004D1590[1] = (int)actSt04bGirlWay;
        gobj->unkB4 = D_004D1590;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        func_0012ABE0(0x1E4, 0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1550[];
extern void actSt04cEnemy2(volatile int a0);

void actSt04lDoor(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    D_004D1550[1] = (int)actSt04cEnemy2;
    gobj->unkB4 = D_004D1550;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D1610[];
extern void actSt04cDoorDownEffect(volatile int a0);

void actSt04cIntro(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    D_004D1610[1] = (int)actSt04cDoorDownEffect;
    gobj->unkB4 = D_004D1610;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04aEnvSe);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04aEnvSeWakare1);

extern int D_00275880[];
extern Mtx64 D_004D1510;
extern void _NormalizeVector(void *a0, int *a1);
extern void _ApplyMatrix(int *a0, int a1, void *a2);

void actSt04cEnemy1(void *a0) {
    int m[4];
    int i;
    _ApplyMatrix(m, *(int *)((char *)*(void **)((char *)a0 + 0x15C) + 0xC), D_00275880);
    m[1] = 0;
    _NormalizeVector((char *)*(void **)((char *)a0 + 0x15C) + 0x520, m);
    for (i = 0; i < *(int *)((char *)*(void **)((char *)a0 + 0x15C) + 0x88); i++) {
        ((Mtx64 *)*(void **)((char *)*(void **)((char *)a0 + 0x15C) + 0x7DC))[i] = D_004D1510;
    }
}

extern int D_006123A8[];
extern int D_0061BB20[];
extern int D_00631AE8;
extern int D_00633984;
extern int CheckReadyStreamMotion(void);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void debug_StdPrintfDummy();
extern void func_001F0E40(int *a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt04cEnemy2(volatile int a0) {
    int i;
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (D_00631AE8 == 0 || scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) == 0) { _ACTWait(1); }
    func_001F0E40(D_006123A8);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_0061BB20, i);
        _ACTWait(1);
    }
    scpPlayStart(0x1F, (int)&D_00633984, 1, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04aEnvSeWakare2);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actConte09_3Jimaku);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownEffect);

void func_00218518(void) {
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x7C) == 0) {
        return;
    }
    if (func_0017B230(0x8C) != 0) {
        return;
    }
    func_0017B258(0x166);
}

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEneChk);

extern int D_006325B4;
extern int func_0012AA80(int a0);
extern void func_0017B288(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void scpSleepEnemyOne(int a0);
extern void func_0018CED0(void);
extern void lt_fade_status(int a0);

void actSt04cIntroChk(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (func_0017B230(0x7C) == 0 || scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpSleepEnemyOne(0xD7D);
    func_0017B288(0x166);
    _ACTWait(0x3C);
    func_0017B258(0x8C);
    func_0017B258(0x8D);
    stage_KillPlayBgAnimation(0xA3, 1, 0);
    func_0018CED0();
    while (func_0012AA80(0xA3) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
    scpWakeupEnemyOne(0xD7D);
}

extern int func_0017B230(int a0);
extern void gflagInit(int a0);

void actSt04lDoorEvent(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_0017B230(0x9B)==0){ stage_KillPlayBgAnimation(0xA4,0,0); stage_KillPlayBgAnimation(0xA5,0,0); } else { stage_KillPlayBgAnimation(0xA4,0,-1); stage_KillPlayBgAnimation(0xA5,0,-1); gflagInit(0x3C8); gflagInit(0x3C9); } }

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_002189E0);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218A20);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218A80);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218B40);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218BB8);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218C58);

