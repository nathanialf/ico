#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", torchOnOfWeaponSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", torchOffOfWeaponSE);

extern void DemoMotionGeo(int a0, int a1, int a2, int a3);

void weaponHitReactionSE(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int x = *(int *)((char *)p + 0x7F0);
    DemoMotionGeo(a1, x + 0x20, x + 0x30, x + 0x40);
}

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

void LightTorchOnOfWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int v = p[0x1D];
    int *r = *(int **)((char *)q + 0x5C);
    r[0x5B] = v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOnOfWeaponWithNoSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", LightTorchOffOfWeapon);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_14;  /* 0x14 */
    unsigned char      f_18;  /* 0x18 */
    unsigned char      f_19;  /* 0x19 */
    unsigned char      f_1A;  /* 0x1A */
    unsigned char      f_1B;  /* 0x1B */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
} S_0060AF70;  /* stride 0x24 */

/* end struct shapes */
