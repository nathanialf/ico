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

void actSt13aElevUp(volatile int a0) {
    GObj *gobj = (GObj *)*(int *)(a0 + 0x164);
    while (1) {
        int q = actSt25aQueenDeadChk(0x65D);
        if (scpSleepSpiderGroupOne(q, 0x2000000) != 0) {
            break;
        }
        _ACTWait(1);
    }
    func_00178DD8(0x63);
    D_004CD380[1] = (int)actSt13aElevDownChk;
    gobj->unkB4 = D_004CD380;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", func_00225E00);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", func_00225F58);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", func_00226010);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13a", func_00226098);
