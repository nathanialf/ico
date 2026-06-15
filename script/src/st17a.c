#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);

void actSt17aDoor(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9B) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x374) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x373) + 0x16C) = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aDoorUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aDoorDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aHasiChk);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);

void actSt17aHasiEffect(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x385), 0x1000000) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x10A);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actLinkTest);

void actSt17aSekizo(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void func_00178DD8(int a0);

void actSt17aHasi(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x37A), 100.0f) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x10F);
    *(int *)(actSt25aQueenDeadChk(0x37A) + 0x16C) = 0;
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void func_00178DD8(int a0);

void actSt17aIntro(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x37B), 100.0f) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x110);
    *(int *)(actSt25aQueenDeadChk(0x37B) + 0x16C) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aSekizoEvent);

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void actLinkTestChk(void) {
    if (func_00178DB0(0x111) != 0) {
        stage_KillPlayBgAnimation(0x15D, 0, -1);
        AddWayPointTop(0xF, 1);
    } else {
        stage_KillPlayBgAnimation(0x15D, 0, 0);
    }
    if (func_00178DB0(0x113) == 0) {
        AddWayPointTop(0x17, 0);
        stage_KillPlayBgAnimation(0x160, 0, 0);
    } else {
        AddWayPointTop(0x17, 1);
        stage_KillPlayBgAnimation(0x160, 0, -1);
    }
    if (func_00178DB0(0x112) == 0) {
        stage_KillPlayBgAnimation(0x15F, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x15F, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aDoorEvent);

extern float scpSekizou(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern int func_0012A958(int a0);
extern void iosPadDevRead(int a0, int a1);
extern void scpActivateAllWithKind(void);
extern int D_00629DEC;
extern int D_0062A894;
extern int D_0062BD84;

void actSt17aDoorUpEffect(int a0) {
    volatile int x;
    x = a0;
    while (!(scpSekizou(0x5D5) < -2.0f)) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0x112);
    _ACTWait(0x1E);
    scpPlayStart(0x47, &D_0062BD84, 1, 1, 1);
    while (D_0062BD84 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x15F, 1, 0);
    while (func_0012A958(0x15F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aDoorDownEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aHasiEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aIntroChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", actSt17aGirlWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", func_0022A970);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", func_0022AAB0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", func_0022ABE8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", func_0022AD28);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17a", func_0022AE60);
