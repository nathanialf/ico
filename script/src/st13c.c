#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cBmg1);

void actSt13cBmg1Chk(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cConte04);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cConte04Jimaku);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void actSt13cCage1stDownDemoCancel(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x4A);
    func_00178DD8(0x4B);
}

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt13cCage1stDown(void) {
    if (func_00178DB0(0x4F) == 0) {
        stage_KillPlayBgAnimation(0x156, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x156, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFall);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFallChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cConte05);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cConte05Jimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFallEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cGirlCarryChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cHandChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cHandJimaku);

void actSt13cSleep(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFallReady);

extern void AddWayPointTop(int a0, int a1);

void actSt13cEnemy(void) {
    if (func_00178DB0(0x107) != 0) {
        AddWayPointTop(0x16, 1);
        AddWayPointTop(0x17, 1);
        stage_KillPlayBgAnimation(0x157, 0, 0x59);
    } else {
        AddWayPointTop(0x14, 1);
        AddWayPointTop(0x15, 1);
        stage_KillPlayBgAnimation(0x157, 0, 0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cEnemyNull);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cSekizo);
