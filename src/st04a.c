#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGate);

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateChk);

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aConte06);

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpExplodeSecretItem(void);

void actSt04aConte06Jimaku(volatile int a0) {
    while (actSt25aQueenDeadChk(0x667) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    scpExplodeSecretItem();
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D12D0[];
extern int D_004D12F0[];
extern void actConte09(volatile int a0);
extern int actInitialize(int a0);
extern void actSt04aGateOpenChk(volatile int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04aGateOpen(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x50) == 0) {
        stage_KillPlayBgAnimation(0x149, 0, 0);
        stage_KillPlayBgAnimation(0x14B, 0, 0);
        D_004D12D0[1] = (int)actSt04aGateOpenChk;
        gobj->unkB4 = D_004D12D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x149, 0, 0x2D);
        stage_KillPlayBgAnimation(0x14B, 0, -1);
        D_004D12F0[1] = (int)actConte09;
        gobj->unkB4 = D_004D12F0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpenChk);

INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09);

extern int D_004D1350[];
extern int D_004D1370[];
extern void actConte09_2(volatile int a0);
extern void actSt04aGateOpen2Chk(volatile int a0);

void actConte09Jimaku(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x51) == 0) {
        stage_KillPlayBgAnimation(0x14A, 0, 0);
        stage_KillPlayBgAnimation(0x14D, 0, 0);
        D_004D1350[1] = (int)actSt04aGateOpen2Chk;
        gobj->unkB4 = D_004D1350;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x14A, 0, 0x2D);
        stage_KillPlayBgAnimation(0x14D, 0, -1);
        D_004D1370[1] = (int)actConte09_2;
        gobj->unkB4 = D_004D1370;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpen2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09_2);

extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void scpTransGObj(void *a0, float f12, float f13, float f14);
extern void func_001BFFE8(int a0);

void actSt04aGateOpen3Chk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x110) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x326) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x319) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x324) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x326) + 0x16C) = 1;
        scpTransGObj((void *)actSt25aQueenDeadChk(0x326), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        func_001BFFE8(actSt25aQueenDeadChk(0x326));
    }
}

extern void func_0017B258(int a0);

void actConte09_3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x111) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x327) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x31A) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x325) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x327) + 0x16C) = 1;
        func_0017B258(0x59);
        scpTransGObj((void *)actSt25aQueenDeadChk(0x327), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        func_001BFFE8(actSt25aQueenDeadChk(0x327));
    }
}

extern void SetWayGroupActive(int a0, int a1);

void actSt04aGateLChk(void) {
    if (func_0017B230(0x52)) {
        SetWayGroupActive(7, 1);
    } else {
        SetWayGroupActive(7, 0);
    }
    if (func_0017B230(0x53)) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D13D0[];
extern int actInitialize(int a0);
extern void actSt04aTorchXL(volatile int a0);

void actSt04aGateRChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    D_004D13D0[1] = (int)actSt04aTorchXL;
    gobj->unkB4 = D_004D13D0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aTorch1);

extern int D_004D1450[];
extern int D_004D1470[];
extern void actSt04bEne1Chk(volatile int a0);
extern void actSt04bSekizoChk(volatile int a0);
extern int func_0017B230(int a0);

void actSt04aTorch1Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x5B) == 0) {
        D_004D1450[1] = (int)actSt04bSekizoChk;
        gobj->unkB4 = D_004D1450;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        D_004D1470[1] = (int)actSt04bEne1Chk;
        gobj->unkB4 = D_004D1470;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1430[];
extern void actSt04bEnd(volatile int a0);
extern int func_0017B230(int a0);

void actSt04aTorchAllFlagfChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x5D) == 0) {
        D_004D1430[1] = (int)actSt04bEnd;
        gobj->unkB4 = D_004D1430;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void actSt04aGateL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x332));
 while(func_0017B230(0x5E)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x14); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x332)); }

void actSt04aGateR(int x) {
    volatile int local = x;
}

extern void AddPluralCameraSet(int a0);
extern int D_004D13F0[];
extern int D_00631AE4;
extern int D_00631AE8;
extern void GetCameraDefaultTargetGObj(void);
extern int GetSkeltonFocusNode(int a0);
extern void Camctrl_SetTarget(int a0, int a1, int a2);
extern void actSt04aGateOpen2(volatile int a0);
extern int scpTriggerBall(int a0, int a1, float f);

void actSt04aTorchXL(volatile int a0) {
    int x = a0;
    GObj__p4 *g = *(GObj__p4 **)(x + 0x164);
    while (scpTriggerBall(a0, D_00631AE4, 100.0f) == 0 ||
           GetSkeltonFocusNode(D_00631AE4) != 0xC6) {
        _ACTWait(1);
    }
    GetCameraDefaultTargetGObj();
    Camctrl_SetTarget(D_00631AE8, 0, 3);
    _ACTWait(0xF);
    AddPluralCameraSet(0x30);
    D_004D13F0[1] = (int)actSt04aGateOpen2;
    g->unkB4 = D_004D13F0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpen2);

void actSt04aGateOpen3(int x) {
    volatile int local = x;
}

