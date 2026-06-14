#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lFloorLeft);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lFloorRight);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam3Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lChainMove);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lChain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lFloor);

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt10lGondola(void) {
    if (func_00178DB0(0x5F) == 0) {
        AddWayPointTop(0x9, 0);
        AddWayPointTop(0xA, 0);
    } else {
        AddWayPointTop(0x9, 1);
        AddWayPointTop(0xA, 1);
    }
    if (func_00178DB0(0x60) == 0) {
        AddWayPointTop(0xC, 0);
    } else {
        AddWayPointTop(0xC, 1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lBox);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy1_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy1_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy2_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy2_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy2_3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy3_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy3_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam2);
