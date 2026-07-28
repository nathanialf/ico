#include "common.h"

typedef struct { char pad[0xC4]; int *unkB4; } B4ObjU;

typedef struct ActB4Obj { char pad[0xC4]; int *unkB4; } ActB4Obj;


extern int func_0017B230(int a0);
extern void func_0017B258(int bit_idx);
extern void *D_00631AE8;
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aInit);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnd);

INCLUDE_ASM("asm/nonmatchings/src/st00a", func_0020D850);

extern int D_00274EC0[];
extern int D_00631AE4;
extern int D_006325B4;
extern int D_00633060;
extern void _ACTWait(int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int actSt25aQueenDeadEvent(void);
extern void func_0017C9B0(int a0);

void actSt00aStairChk(volatile int a0) {
    D_006325B4 = 1;
    D_00633060 = 0;
    func_0017C9B0(1);
    _ACTWait((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 0x1E);
    actSt25aQueenBeforeChk(0, 0, 0, 6.0f);
    while (actSt25aQueenDeadEvent() != 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(1, D_00631AE4, 0, 255.0f, 8.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2UpChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2DownChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0DB0[];
extern int D_00633948;
extern int D_00633FA4;
extern void *actInitialize(int a0);
extern void actSt00aAtr2Chk();
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt00aDoor1UpChk(volatile int a0) {
    int x = a0;
    B4ObjU *gobj = (B4ObjU *)actInitialize(a0);
    _ACTWait(1);
    if (D_00631AE4 != 0) {
        gflagOff(D_00631AE4, 0);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    stage_KillPlayBgAnimation(0x83, 0, 0);
    scpPlayStart(8, &D_00633FA4, 0, 1, 1);
    while (D_00633FA4 == 0) {
        _ACTWait(1);
    }
    if (D_00633948 == 0) {
        scpPlayStart(0xA, &D_00633948, 0, 1, 1);
    }
    D_004D0DB0[1] = (int)actSt00aAtr2Chk;
    gobj->unkB4 = D_004D0DB0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEne);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy1);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0DD0[];
extern void *actInitialize(int a0);
extern void actSt00aEne();
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt00aEnemy2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    stage_KillPlayBgAnimation(0x9B, 0, 0);
    stage_KillPlayBgAnimation(0x97, 0, 0);
    D_004D0DD0[1] = (int)actSt00aEne;
    gobj->unkB4 = D_004D0DD0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void backStageProcessOutStage(int a0);
extern void stgmgrForceSwitchWithFade(int a0);

void actSt00aStair(int a0) {
    volatile int x;
    x = a0;
    _ACTWait((int)((float)((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) * 5.0f));
    stgmgrForceSwitchWithFade(1);
    backStageProcessOutStage(1);
}

extern char D_0061B980[];
extern char D_0061B990[];
extern void debug_assertMessage();

void actSt00aAtr2(volatile int a0) {
    _ACTWait(1);
    while (func_0017B230(0x15D) == 0) {
        _ACTWait(1);
    }
    debug_assertMessage(D_0061B980);
    debug_assertMessage(D_0061B990);
    func_0017B258(2);
    actSt25aQueenDead(1, D_00631AE4, 0, 0.25f, 2.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2Event);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt00aDoor2UpEffect(void) {
    if (func_0017B230(0x26) == 0) {
        stage_KillPlayBgAnimation(0x4D, 0, 0);
        stage_KillPlayBgAnimation(0x4A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x4B, 0, -1);
        stage_KillPlayBgAnimation(0x4A, 0, -1);
    }
}

void actSt00aDoor2DownEffect(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x27) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

extern int D_00631AE8__p4 __asm__("D_00631AE8");
extern int func_0012AA80(int a0);
extern void func_0017B288(int a0);
extern void func_0017C8C0(int a0);
extern void func_0017C8F8(int a0);

void actSt00aDoor1Event(volatile int a0) {
    if (D_00631AE8__p4 == 0) { _ACTWait(0); }
    while (func_0017B230(0x27) == 0 || func_0017B230(0x23) != 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017B258(0x24);
    func_0017C8F8(0xD7D);
    func_0017B288(0x166);
    _ACTWait(0x3C);
    func_0017B258(0x25);
    stage_KillPlayBgAnimation(0x9C, 1, 0);
    _ACTWait(0x96);
    while (func_0012AA80(0x9C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    _ACTWait(0x78);
    D_006325B4 = 0;
    func_0017B288(0x24);
    func_0017C8C0(0xD7D);
}

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpEffect);

extern int D_004D0E50[];
extern int D_004D0E70[];
extern void actSt01bEneChk(void);
extern void actSt01bInit(void);
extern int scpSleepEnemyOne(int a0, int a1, float f0);

void actSt00aDoor1DownEffect(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00631AE4, 200.0f) != 0 ||
        (D_00631AE8__p4 != 0 && scpSleepEnemyOne(a0, D_00631AE8__p4, 400.0f) != 0)) {
        stage_KillPlayBgAnimation(0x51, 0, 0);
        _ACTWait(0x3C);
        D_004D0E50[1] = (int)actSt01bEneChk;
        gobj->unkB4 = D_004D0E50;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x50, 0, 0);
        D_004D0E70[1] = (int)actSt01bInit;
        gobj->unkB4 = D_004D0E70;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

