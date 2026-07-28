#include "common.h"


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

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownChk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEne);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy2);

extern void backStageProcessOutStage(int a0);
extern void stgmgrForceSwitchWithFade(int a0);

void actSt00aStair(int a0) {
    volatile int x;
    x = a0;
    _ACTWait((int)((float)((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) * 5.0f));
    stgmgrForceSwitchWithFade(1);
    backStageProcessOutStage(1);
}

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2Event);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2UpEffect);

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

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1Event);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpEffect);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownEffect);

