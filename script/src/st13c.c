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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCage1stDownDemoCancel);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cEnemyNull);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cSekizo);
