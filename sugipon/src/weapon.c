#include "common.h"

/* weapon 0x7F0 view (local) */
typedef struct { int f_0, f_4, f_8, f_C; char _pad10[0x40]; int f_50; char _pad54[0x4C]; int f_A0; } WGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", torchOnOfWeaponSE);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void torchOffOfWeaponSE(char *a0, int a1, int a2, int a3) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    MatrixDrive_TurnObjectMatrix(a1, sub + 0x20);
    MatrixDrive_TurnObjectMatrix(a2, sub + 0x30);
    MatrixDrive_TurnObjectMatrix(a3, sub + 0x40);
}

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

extern void torchOnOfWeaponSE(void *a0);
extern void weaponStickSE(void *a0);

void calcDynamicPathGeometry(void *a0) {
    torchOnOfWeaponSE(a0);
    weaponStickSE(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", calcDynamicGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", getGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponCurPos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponHitEffect);

void ExecWeaponHitReaction(void *a0) {
    WGeo *p = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    int x = p->f_8;
    if (x != 0) {
        *(int *)(*(char **)((char *)x + 0x15C) + 0x620) = 0;
    }
    p->f_8 = 0;
    p->f_C = -1;
    p->f_4 = 0;
}

int checkHit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x7F0);
    return q->f_0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", initializeQueenzSword);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", InitWeaponGeo);

extern void func_001EEB10();

void WeaponGeo(char *a0) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    int i;
    for (i = 0; i < *(int *)(sub + 0x50); i++) {
        func_001EEB10(*(int *)(*(int *)(sub + 0x54) + i * 4));
    }
}

int dispInsectNet(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x7F0);
    if (q->f_50) {
        return **(int **)((char *)q + 0x54);
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/weapon", WeaponDL);

int PickupWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x7F0);
    q->f_A0 = 0;
    return 1;
}

typedef struct { char _0[0xC]; int f_C; char _10[0x14]; } WeaponEntry;
extern WeaponEntry D_0060AF70[];

float CheckSwapableWeapon(void *a0) {
    WGeo *p = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    int idx = p->f_0;
    return (float)D_0060AF70[idx].f_C;
}

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
