#include "common.h"

extern void _ACTWait(int a0);

void actClipCollisionCore(void) {
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clipCollisionManager", func_001C09E8);

extern void MatrixDrive_TurnObjectMatrix(void *a0, int a1);

void CreateClipCollisionManagerGObj(void *a0, int a1, int a2) {
    MatrixDrive_TurnObjectMatrix(a0, a1 + a2 * 0x50 + 0x30);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clipCollisionManager", RequestClipCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clipCollisionManager", thStart);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clipCollisionManager", func_001C13C0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clipCollisionManager", func_001C1560);
