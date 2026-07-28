#include "common.h"


extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern void _ACTWait(int a0);

void actClipCollisionCore(void) {
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", func_001C3778);

void CreateClipCollisionManagerGObj(int a0, int a1, int a2)
{
    MatrixDrive_TurnObjectMatrix(a0, a1 + a2 * 0x50 + 0x30);
}

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", RequestClipCollision);

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", thStart);

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", func_001C4150);

INCLUDE_ASM("asm/nonmatchings/src/clipCollisionManager", func_001C42F0);

