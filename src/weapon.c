#include "common.h"



extern char DebugDisp1CollisionWithColor(char *self, int idx);
extern void func_001F23C0();
INCLUDE_ASM("asm/nonmatchings/src/weapon", torchOnOfWeaponSE);

INCLUDE_ASM("asm/nonmatchings/src/weapon", torchOffOfWeaponSE);

INCLUDE_ASM("asm/nonmatchings/src/weapon", weaponHitReactionSE);

void weaponFumbleSE(int a0, int a1, int a2, int a3)
{
    func_001F23C0(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", weaponStickSE);

INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeaponWithFumbleTargetPos);

INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeaponWithFumbleSequential);

extern void torchOnOfWeaponSE(void *a0);
extern void weaponStickSE(void *a0);

void calcDynamicPathGeometry(void *a0) {
    torchOnOfWeaponSE(a0);
    weaponStickSE(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", calcDynamicGeometry);

INCLUDE_ASM("asm/nonmatchings/src/weapon", getGeometry);

void WeaponCurPos(int *self, int *other, int a2)
{
    int *s1;
    int rv;
    s1 = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    s1[0x8 / 4] = (int)other;
    rv = DebugDisp1CollisionWithColor((int)other, a2);
    s1[0xC / 4] = rv;
    ((int *)other[0x15C / 4])[0x630 / 4] = (int)self;
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", WeaponHitEffect);

INCLUDE_ASM("asm/nonmatchings/src/weapon", ExecWeaponHitReaction);

INCLUDE_ASM("asm/nonmatchings/src/weapon", checkHit);

INCLUDE_ASM("asm/nonmatchings/src/weapon", initializeQueenzSword);

INCLUDE_ASM("asm/nonmatchings/src/weapon", InitWeaponGeo);

INCLUDE_ASM("asm/nonmatchings/src/weapon", WeaponGeo);

long dispInsectNet(int *a0)
{
    register int *v = (int *)a0[0x57];
    register int *v1;
    v = (int *)v[0x200];
    v1 = (int *)v[0x14];
    if (0 == v1) goto fail;
    v1 = (int *)v[0x15];
    return v1[0];
fail:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", WeaponDL);

INCLUDE_ASM("asm/nonmatchings/src/weapon", PickupWeapon);

INCLUDE_ASM("asm/nonmatchings/src/weapon", CheckSwapableWeapon);

INCLUDE_ASM("asm/nonmatchings/src/weapon", ReleaseWeapon);

INCLUDE_ASM("asm/nonmatchings/src/weapon", CheckWeaponKind);

INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOnOfWeapon);

INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOnOfWeaponWithNoSE);

INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOffOfWeapon);

