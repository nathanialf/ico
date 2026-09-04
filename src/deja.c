#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkC4;
} GObj__p4;



extern void stage_KillPlayBgAnimation();
extern void SetWayGroupActive();
extern int func_0017B230(int a0);
extern void AdpcmPlay(int a0);
extern int D_00275250[];
extern int D_0061B7F0[];
extern int D_00631AE4;
extern int D_006338EC;
extern void _ACTWait(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actDejaDemo(volatile int a0);
extern int actInitialize(int a0);
extern void scpFadeOut(int a0, int a1, int a2, float f);
extern void RequestStageChange(int a0, int a1, int a2, float f12, float f13);
extern int scpFadeChk(void);
extern void debug_StdPrintfDummy(int *a0);
extern int func_0017B258(int a0);

void actDejaChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    actCreateSubThread(actDejaDemo, 0x15);
    while (func_0017B230(0x144) != 0 || (D_00275250[1] & 0x840) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x145);
    debug_StdPrintfDummy(D_0061B7F0);
    AdpcmPlay(*(int *)(D_006338EC + 0x2C));
    scpFadeOut(0, 0, 0, 4.0f);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }
    RequestStageChange(1, D_00631AE4, 0, 255.0f, 16.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaDemo);

INCLUDE_ASM("asm/nonmatchings/src/deja", actDejaAfter);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0A30[];
extern int D_00631AE8;
extern void actE3St13cInit(volatile int a0);
extern void func_0017E9D8(void);
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actDejaAfterChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (D_00631AE8 == 0) {
        func_0017E9D8();
    }
    if (func_0017B230(0x146) == 0) {
        if (D_00631AE4 != 0) {
            gflagOff(D_00631AE4, 0);
        }
        scpFadeOut(0, 0, 0, 255.0f);
        lt_fade_status(0x33);
        stage_KillPlayBgAnimation(0x1F, 0, 0);
        stage_KillPlayBgAnimation(0x19, 0, -1);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x20, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
        D_004D0A30[1] = (int)actE3St13cInit;
        gobj->unkC4 = D_004D0A30;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, -1);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x20, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
    }
}

extern int D_006338F0;
extern int D_00633F90;
extern int D_00633F94;
extern void scpFadeIn(float f);
extern void actE3CageFall(volatile int a0);
extern void iosThreadSetPri(int a0, int a1);
extern void soundSeVolSet(int a0);

void actDeja(volatile int a0) {
    while (D_00633F94 == 0 || (D_00275250[1] & 0x800) == 0) {
        _ACTWait(1);
    }
    iosThreadSetPri(D_00633F90 + 0x24, 0x22);
    scpFadeOut(0, 0, 0, 8.0f);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }
    soundSeVolSet(D_006338F0);
    stage_KillPlayBgAnimation(0x1F, 0, -1);
    stage_KillPlayBgAnimation(0x19, 0, -1);
    stage_KillPlayBgAnimation(0x20B, -1, -2);
    stage_KillPlayBgAnimation(0x210, -1, -2);
    stage_KillPlayBgAnimation(0x212, -1, -2);
    stage_KillPlayBgAnimation(0x213, -1, -2);
    stage_KillPlayBgAnimation(0x214, -1, -2);
    stage_KillPlayBgAnimation(0x215, -1, -2);
    stage_KillPlayBgAnimation(0x216, -1, -2);
    stage_KillPlayBgAnimation(0x217, -1, -2);
    stage_KillPlayBgAnimation(0x229, 1, 0);
    scpFadeIn(6.0f);
    actCreateSubThread(actE3CageFall, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/src/deja", actEnemySleep);

void func_00208740(void)
{
    SetWayGroupActive(7, 0);
    if (func_0017B230(0x148) != 0) {
        SetWayGroupActive(9, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00208780);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00208880);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_002089B0);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00208CC0);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209080);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209190);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209440);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_002095B8);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209908);

void func_00209AB0(void)
{
    stage_KillPlayBgAnimation(0xA2, 0, -1);
}

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209AC0);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209B78);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209C30);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209CC8);

INCLUDE_ASM("asm/nonmatchings/src/deja", func_00209D40);

