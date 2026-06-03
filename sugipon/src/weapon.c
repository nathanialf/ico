#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", torchOnOfWeaponSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", torchOffOfWeaponSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", weaponHitReactionSE);

extern void func_001EF3B0(int a0);

void weaponFumbleSE(int a0) {
    func_001EF3B0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", weaponStickSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", ReleaseWeaponWithFumbleTargetPos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", ReleaseWeaponWithFumbleSequential);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", calcDynamicPathGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", calcDynamicGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", getGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponCurPos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponHitEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", ExecWeaponHitReaction);

int checkHit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", initializeQueenzSword);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", InitWeaponGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", dispInsectNet);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponDL);

int PickupWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[0x28] = 0;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", CheckSwapableWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", ReleaseWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", CheckWeaponKind);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOnOfWeapon);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOnOfWeaponWithNoSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOffOfWeapon);
