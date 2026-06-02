#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFloorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rCageMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rTowerChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rTowerConte);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rChainMove);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFence);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceDownChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceUpChk2);

void actSt10rFloor(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rCage);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rTower);

void actSt10rExit(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rChain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rElv);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rGateXL);
