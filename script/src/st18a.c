#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchLChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchLUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchRChk);

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int D_00629DE4;
void actSt18aSwitchRUpChk(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00629DE4, 400.0f) == 0 || func_00178DB0(0xF) != 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x127);
    actSt25aQueenDead(0xF, D_00629DE4, 0, 16.0f, 16.0f);
}

extern void _ACTWait(int a0);
extern void backStageProcessMain(void);
extern void func_00178DD8(int a0);

void actSt18aDoorChk(volatile int a0) {
    _ACTWait(1);
    backStageProcessMain();
    func_00178DD8(0x129);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aDoorDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEnemy1_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEnemy2_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchR);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEnemy1_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEne2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEnemy2_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aIntroChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aEne2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", func_0022D7F8);
