#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEnd);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntroChk);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoorChk);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cSolarXL);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoor);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntro);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDown);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEne);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cWaterXL);
void actSt04cDoorDownEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownEffect);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntroChkSub);
void actSt04lDoorEvent(int x) {
    volatile int local = x;
}
