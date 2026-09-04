#include "common.h"

extern void StopSEPackage(int a0);
void torchOffOfWeaponSE(int a0) {
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x43);
}
INCLUDE_ASM("asm/nonmatchings/src/weapon", weaponHitReactionSE);
extern void ExecuteSEPackage(int a0, int a1);
void weaponFumbleSE(int a0) {
    ExecuteSEPackage(a0, 0x5C);
}
void weaponStickSE(int a0) {
    ExecuteSEPackage(a0, 0x5D);
}
INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeaponWithFumbleTargetPos);
INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeaponWithFumbleSequential);
INCLUDE_ASM("asm/nonmatchings/src/weapon", calcDynamicPathGeometry);
INCLUDE_ASM("asm/nonmatchings/src/weapon", calcDynamicGeometry);
INCLUDE_ASM("asm/nonmatchings/src/weapon", getGeometry);
INCLUDE_ASM("asm/nonmatchings/src/weapon", WeaponCurPos);
extern void CheckEnemyHit(void *a0, void *a1, void *a2, void *a3);
void WeaponHitEffect(char *a0, void *a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    CheckEnemyHit(a1, p + 0x20, p + 0x30, p + 0x40);
}
extern void weaponHitReactionSE();

void ExecWeaponHitReaction(int a0, int a1, int a2, int a3)
{
    weaponHitReactionSE(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/weapon", checkHit);
INCLUDE_ASM("asm/nonmatchings/src/weapon", initializeQueenzSword);
INCLUDE_ASM("asm/nonmatchings/src/weapon", InitWeaponGeo);
INCLUDE_ASM("asm/nonmatchings/src/weapon", dispLaserSword);
INCLUDE_ASM("asm/nonmatchings/src/weapon", dispInsectNet);
INCLUDE_ASM("asm/nonmatchings/src/weapon", dispBlur);
INCLUDE_ASM("asm/nonmatchings/src/weapon", calcBlur);
INCLUDE_ASM("asm/nonmatchings/src/weapon", WeaponGeo);
INCLUDE_ASM("asm/nonmatchings/src/weapon", WeaponDL);
INCLUDE_ASM("asm/nonmatchings/src/weapon", PickupWeapon);
INCLUDE_ASM("asm/nonmatchings/src/weapon", CheckSwapableWeapon);
INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeapon);
INCLUDE_ASM("asm/nonmatchings/src/weapon", CheckWeaponKind);
INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOnOfWeapon);
INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOnOfWeaponWithNoSE);
INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOffOfWeapon);
INCLUDE_ASM("asm/nonmatchings/src/weapon", GetTorchGObjOfWeapon);
INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeaponWithFumble);
INCLUDE_ASM("asm/nonmatchings/src/weapon", InitWeaponFumbleSequence);
INCLUDE_ASM("asm/nonmatchings/src/weapon", GetWeaponWeight);
INCLUDE_ASM("asm/nonmatchings/src/weapon", SetWeaponTorchChainReactionFlagAll);
INCLUDE_ASM("asm/nonmatchings/src/weapon", InitDemoQueensSword);
INCLUDE_ASM("asm/nonmatchings/src/weapon", ExecDemoQueensSword);
INCLUDE_ASM("asm/nonmatchings/src/weapon", SetWeaponOffsetMode);
