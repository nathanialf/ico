#include "common.h"

extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CD380[];
extern void actSt13aElevDownChk(void);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aElevUp);



INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aElevDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aElev);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aElevDown);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aExit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aCheck);

extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int GetSkeltonFocusNode(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void DrawLine(void);
extern int D_00629DE4;

void actSt13aChain(volatile int a0) {
    while (1) {
        if (scpSleepEnemyOne(a0, D_00629DE4, 150.0f) != 0) {
            if (GetSkeltonFocusNode(D_00629DE4) == 0x2E) break;
            if (GetSkeltonFocusNode(D_00629DE4) == 0x2F) break;
            if (GetSkeltonFocusNode(D_00629DE4) == 0x30) break;
            if (GetSkeltonFocusNode(D_00629DE4) == 0x3E) break;
        }
        _ACTWait(1);
    }
    *(int *)(actSt25aQueenDeadChk(0x659) + 0x16C) = 1;
    DrawLine();
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt13aElevMain(void) {
    if (func_00178DB0(0x71) != 0) {
        if (func_00178DB0(0x72) != 0) {
            AddWayPointTop(0xB, 0);
            AddWayPointTop(0xC, 0);
            stage_KillPlayBgAnimation(0x142, 0, -1);
        } else {
            AddWayPointTop(0xD, 0);
            AddWayPointTop(0xE, 0);
            AddWayPointTop(0xF, 0);
            stage_KillPlayBgAnimation(0x141, 0, -1);
        }
    } else {
        AddWayPointTop(0xD, 0);
        AddWayPointTop(0xE, 0);
        AddWayPointTop(0xF, 0);
        stage_KillPlayBgAnimation(0x141, 0, 0);
    }
}

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSt13aElevSwitch(void) {
    if (D_00629DE8 && func_00178DB0(0x75) == 0 && func_00178DB0(0x72)) {
        func_00178DD8(0x165);
    }
    if (D_00629DE8 && func_00178DB0(0x78) == 0 && func_00178DB0(0x9B)) {
        func_00178DD8(0x165);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aExitChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aCheckChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aChainOK);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", actSt13aChainNG);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", func_00225A18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", func_00225D30);


extern int D_0062A894;
extern void lt_fade_status(int a0);
extern void func_0017A040(int a0);
extern void func_0017A078(int a0);
extern void func_0017A008(int a0);
extern void func_0017A0A8(int a0);
extern void func_00178E08(int a0);
extern void func_0018A380(void);
extern void shadow_Tool(int a0);
extern void UpdateStormPackage(int a0);
extern int func_0012A958(int a0);

void func_00225E00(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (func_00178DB0(0x77) == 0 ||
           scpSleepEnemyOne(a0, D_00629DE8, 400.0f) == 0) {
        _ACTWait(1);
    }
    *(int *)(actSt25aQueenDeadChk(0x168) + 0x16C) = 1;
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_0017A040(0xD57);
    func_00178E08(0x165);
    func_00178DD8(0x75);
    func_00178DD8(0x76);
    stage_KillPlayBgAnimation(0x144, 1, 0);
    func_0018A380();
    shadow_Tool(1);
    UpdateStormPackage(0);
    func_0017A040(0x16B);
    func_0017A078(0x170);
    while (func_0012A958(0x144) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    shadow_Tool(0);
    UpdateStormPackage(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    *(int *)(actSt25aQueenDeadChk(0x168) + 0x16C) = 0;
    _ACTWait(0x1E);
    func_0017A008(0xD57);
    func_0017A008(0x16B);
    func_0017A0A8(0x170);
}


extern int actInitialize(int a0);
extern void gflagSave(int a0);
extern void func_001C04E0(void);
extern int D_004CD580[];
extern void actSt13aExitChk(void);

void func_00225F58(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x71) != 0) {
        func_001C04E0();
        if (func_00178DB0(0x72) != 0) {
            gflagSave(0x189);
            gflagSave(0x18A);
        }
    } else {
        gflagSave(0x189);
        gflagSave(0x18A);
        D_004CD580[1] = (int)actSt13aExitChk;
        gobj->unkB4 = D_004CD580;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CD5A0[];
extern void actSt13aChainOK(void);

void func_00226010(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x72) == 0) {
        D_004CD5A0[1] = (int)actSt13aChainOK;
        gobj->unkB4 = D_004CD5A0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        func_00178DD8(0x77);
    }
}


extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern int D_004CD5C0[];
extern void actSt13bDoor(void);

void func_00226098(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x73) == 0) {
        D_004CD5C0[1] = (int)actSt13bDoor;
        gobj->unkB4 = D_004CD5C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

