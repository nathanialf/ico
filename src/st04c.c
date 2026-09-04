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
extern char *D_00639EA8;
void actSt04cEneChk(volatile int a0) {
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }
    gflagOff(0x187);
    _ACTWait(1);
    gflagOn(0xA3);
    gflagOn(0xA4);
}
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntroChkSub);
void actSt04lDoorEvent(int x) {
    volatile int local = x;
}
