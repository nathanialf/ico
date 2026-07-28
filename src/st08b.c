#include "common.h"

void actSt08bKurenSwitch(int x) {
    volatile int local = x;
}

void actSt08bKurenLeft(int x) {
    volatile int local = x;
}

void actSt08bKurenRight(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoor);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorUpChk);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorDownChk);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKuren);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEne);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEnemy2);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenMain);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08aGirlYoro);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorEvent);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorUpEffect);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorDownEffect);

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEneChk);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00224778);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_002247D8);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00224898);

INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00224900);

void func_00224960(int x) {
    volatile int local = x;
}

