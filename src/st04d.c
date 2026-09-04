#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1DownChk);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2DownChk);
void actSt04dDoor1Event(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1UpEffect);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1DownEffect);
void actSt04dDoor2Event(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2UpEffect);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2DownEffect);
