#include "common.h"

extern void ExecuteSEPackage(int a0, int a1);

void bombSparkStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x32);
}
INCLUDE_ASM("asm/nonmatchings/src/item", bombSparkSE);
INCLUDE_ASM("asm/nonmatchings/src/item", bombExplodeSE);
INCLUDE_ASM("asm/nonmatchings/src/item", HoldItem);
extern void ClipWall(int arg);
extern float D_004EB500[48];
extern void GetRootPosition(void *a0, char *outer);
extern void SetDirectRootPositionNoFitting();

void avoidInsideOfWall(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)D_004EB500;
    GetRootPosition(p, arg);
    GetRootPosition(p + 0x10, (int)self);
    ClipWall((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    SetDirectRootPositionNoFitting(self, p + 0x20);
}
INCLUDE_ASM("asm/nonmatchings/src/item", ReleaseItem);
INCLUDE_ASM("asm/nonmatchings/src/item", ThrowItem);
INCLUDE_ASM("asm/nonmatchings/src/item", InitItemGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", carriedItemGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", floatGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", uncarriedItemGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", execBombGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", ItemGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", ItemDL);
INCLUDE_ASM("asm/nonmatchings/src/item", BreakItemFromOutside);
INCLUDE_ASM("asm/nonmatchings/src/item", CheckCarryableItem);
INCLUDE_ASM("asm/nonmatchings/src/item", GetItemKind);
INCLUDE_ASM("asm/nonmatchings/src/item", GetCharHeldItem);
INCLUDE_ASM("asm/nonmatchings/src/item", IsItemHoldable);
INCLUDE_ASM("asm/nonmatchings/src/item", IsBombExplode);
INCLUDE_ASM("asm/nonmatchings/src/item", GetBombTorchGObj);
INCLUDE_ASM("asm/nonmatchings/src/item", ReviveAllCarryableItems);
INCLUDE_ASM("asm/nonmatchings/src/item", ReviveCarryableItemsWithBoundary);
INCLUDE_ASM("asm/nonmatchings/src/item", ReviveAllCarryableItemsWithRandomVelocity);
INCLUDE_ASM("asm/nonmatchings/src/item", CheckItemDead);
INCLUDE_ASM("asm/nonmatchings/src/item", StopItemExplodeAnimationAll);
INCLUDE_ASM("asm/nonmatchings/src/item", BreakItemWithAttackHit);
INCLUDE_ASM("asm/nonmatchings/src/item", ReviveAllCarryableItemsWithNonSleepFrame);
