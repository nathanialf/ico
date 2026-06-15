#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lFloorLeft);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
void actSt10lFloorRight(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (D_00629DE8 == 0 || func_00178DB0(0x98) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x99);
    func_00178DD8(0x9A);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam3Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lChainMove);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lChain);

extern int func_0025F4F0(int a0);
extern int func_0025EF78(int a0, long a1);
extern int func_0025F5A8(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);
extern int D_00271240[];
void actSt10lFloor(volatile int a0) {
    _ACTWait(func_0025F5A8(func_0025EF78(func_0025F4F0((0x3C - D_00271240[0] * 0xA) / D_00271240[1]), (long)0x804C << 47)));
    func_00178DD8(0xCE);
}

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
