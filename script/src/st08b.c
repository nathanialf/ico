#include "common.h"

void actSt08bKurenSwitch(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08bKurenLeft(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08bKurenRight(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bKuren);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bKurenMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08aGirlYoro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorUpEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bDoorDownEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", actSt08bEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", func_002214A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", func_00221508);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", func_002215C8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08b", func_00221630);

void func_00221690(int a0) {
    int buf[4];
    buf[0] = a0;
}
