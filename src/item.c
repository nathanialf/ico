#include "common.h"



extern void CylinderCollision();
extern void ClipWallBoxStop(int arg);
extern void GetRootMatrixByDObj(void *a0, char *outer);
extern float D_004C4760[48];
extern void playSEConditionID(int a0, int a1);
void bombSparkStartSE(int a0)
{
    playSEConditionID(a0, 0x31);
}

void bombSparkSE(int a0)
{
    playSEConditionID(a0, 0x32);
}

INCLUDE_ASM("asm/nonmatchings/src/item", bombExplodeSE);

void HoldItem(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)D_004C4760;
    GetRootMatrixByDObj(p, arg);
    GetRootMatrixByDObj(p + 0x10, (int)self);
    ClipWallBoxStop((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    CylinderCollision(self, p + 0x20);
}

INCLUDE_ASM("asm/nonmatchings/src/item", avoidInsideOfWall);

INCLUDE_ASM("asm/nonmatchings/src/item", ReleaseItem);

INCLUDE_ASM("asm/nonmatchings/src/item", ThrowItem);

INCLUDE_ASM("asm/nonmatchings/src/item", InitItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", carriedItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", uncarriedItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", execBombGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", ItemGeo);

INCLUDE_ASM("asm/nonmatchings/src/item", ItemDL);

