#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEnd);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownChk);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoorChk);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cSolarXL);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoor);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntro);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDown);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEne);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEnemy1);

extern int D_006123A8[];
extern int D_0061BB20[];
extern int D_00631AE8;
extern int D_00633984;
extern int DeleteStreamMotionManager(void);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void debug_assertMessage();
extern void func_001F0E40(int *a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt04cEnemy2(volatile int a0) {
    int i;
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (D_00631AE8 == 0 || scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) == 0) { _ACTWait(1); }
    func_001F0E40(D_006123A8);
    i = 0;
    while (DeleteStreamMotionManager() == 0) {
        i++;
        debug_assertMessage(D_0061BB20, i);
        _ACTWait(1);
    }
    scpPlayStart(0x1F, (int)&D_00633984, 1, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cWaterXL);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownEvent);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownEffect);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEneChk);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntroChk);

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoorEvent);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_002189E0);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218A20);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218A80);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218B40);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218BB8);

INCLUDE_ASM("asm/nonmatchings/src/st04c", func_00218C58);

