#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEnd);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04cDoorDownChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x101, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cWaterXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDownEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cDoorDownEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04cIntroChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", actSt04lDoorEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215CD0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215D10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215D70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215E30);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215EA8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04c", func_00215F48);
