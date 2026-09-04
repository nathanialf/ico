#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoorChk);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoor2Chk);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cSolarXL);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cWaterXL);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoor);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoor2);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cDoorDown);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEne);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cCrestHint);
void actSt05cDoorDownEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cDoorDownEffect);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoorSub);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoor2Sub);
INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cCrestHintChk);
