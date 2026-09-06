#include "common.h"
#include "sugiCommon.h"

extern void ExecuteSEPackage(int a0, int a1);
void torchOnOfWeaponSE(int a0) {
    ExecuteSEPackage(a0, 0x42);
}
extern void StopSEPackage(int a0);
void torchOffOfWeaponSE(int a0) {
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x43);
}
extern void ExecuteSEPackage(int a0, int a1);
void weaponHitReactionSE(int a0, int a1, int a2, int a3) {
    ExecuteSEPackage(a0, 0x44);
}
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
void WeaponCurPos(char *a0, void *a1, void *a2, void *a3) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    CopyVector(a1, p + 0x20);
    CopyVector(a2, p + 0x30);
    CopyVector(a3, p + 0x40);
}
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
extern int GetSkeltonFocusNode(char *obj, int kind);
void PickupWeapon(char *a0, char *a1, int a2) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    *(char **)(p + 0x8) = a1;
    *(int *)(p + 0xC) = GetSkeltonFocusNode(a1, a2);
    *(int *)(*(int *)(a1 + 0x15C) + 0x630) = (int)a0;
}
extern int stage_no;
extern void GetRootPosition(void *out, void *obj);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);

char *CheckSwapableWeapon(char *a0, float dist) {
    char *found = 0;
    float best = dist * dist;
    char *g = (char *)isysGObjSearchFromObjKindID_begin(14);
    float pos[4];
    float d;

    GetRootPosition(pos, a0);

    for (; g != 0; g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *w;
        char *wp;

        if (g == a0) continue;

        w = *(char **)(*(char **)(g + 0x15C) + 0x830);
        if (*(int *)w == 0) continue;

        if (*(int *)(w + 0x8) != 0) continue;

        if (*(int *)(g + 0x16C) == 0) continue;

        wp = w + 0xD0;
        if (stage_no == 4 && *(int *)(g + 0x8) != 0x80) continue;

        d = distance_squared(pos, wp);
        if (d < best) {
            found = g;
            best = d;
        }
    }
    return found;
}
void ReleaseWeapon(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(char **)(p + 0x8)) {
        *(int *)(*(char **)(*(char **)(p + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(p + 0x8) = 0;
    *(int *)(p + 0xC) = -1;
    *(int *)(p + 0x4) = 0;
}
int CheckWeaponKind(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830));
}
extern void LightTorchOn(int torch);
void LightTorchOnOfWeapon(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int i;

    if (*(int *)(p + 0x50)) {
        torchOnOfWeaponSE(**(int **)(p + 0x54));
    }
    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOn(*(int *)(*(char **)(p + 0x54) + i * 4));
    }
}
void LightTorchOnOfWeaponWithNoSE(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int i;

    if (*(int *)(p + 0x50)) {
        torchOnOfWeaponSE(**(int **)(p + 0x54));
    }
    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOn(*(int *)(*(char **)(p + 0x54) + i * 4));
    }
}
extern void LightTorchOff(char *torch);
void LightTorchOffOfWeapon(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int i;

    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOff(*(char **)(*(char **)(p + 0x54) + i * 4));
    }
}
int GetTorchGObjOfWeapon(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(p + 0x50)) {
        return **(int **)(p + 0x54);
    }
    return 0;
}
extern void CopyQuaternion(void *dst, void *src);
/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * ReleaseWeapon's lines 262-265 here, so ReleaseWeapon is a public `inline` of
 * the deferred tail; its body is expanded in place until the tail's asm
 * members are C, when it collapses into a call.  LightTorchOnOfWeapon and
 * LightTorchOnOfWeaponWithNoSE are one source body (both symbols carry
 * weapon.c:173-177); their shared form is decided at layout. */
void ReleaseWeaponWithFumble(char *a0, void *a1, void *a2) {
    char *e = *(char **)(a0 + 0x15C);
    char *w = *(char **)(e + 0x830);
    char *f = e + 0xA0;

    if (*(char **)(w + 0x8)) {
        *(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(w + 0x8) = 0;
    *(int *)(w + 0xC) = -1;
    *(int *)(w + 0x4) = 1;

    if (a2) {
        CopyQuaternion(e + 0x150, a2);
    }
    CopyVector(e + 0x130, a1);
    *(int *)(f + 0x9C) = 0;
}
int InitWeaponFumbleSequence(char *a0) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xA0) = 0;
    return 1;
}
typedef struct { int w[9]; } WeaponDef;
extern WeaponDef D_00318EB8[];
float GetWeaponWeight(char *a0) {
    return (float)D_00318EB8[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830))].w[3];
}
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void SetTorchChainReactionFlag(char *gobj, int flag);
void SetWeaponTorchChainReactionFlagAll(int a0) {
    char *g;
    char *w;
    int i;

    for (g = isysGObjSearchFromObjKindID_begin(14); g;
         g = isysGObjSearchFromObjKindID_next(g)) {
        w = *(char **)(*(char **)(g + 0x15C) + 0x830);
        if (*(int *)w == 1) {
            for (i = 0; i < *(int *)(w + 0x50); i++) {
                SetTorchChainReactionFlag(*(char **)(*(char **)(w + 0x54) + i * 4), a0);
            }
        }
    }
}
typedef struct { double d[28]; } DemoQueenSwordWork;
extern int D_0063A438;
extern const char D_006214E0[];
extern DemoQueenSwordWork D_004ED1F0;
extern void *iosMallocDebug(int heap, int size, const char *file, int line);
extern void initializeQueenzSword(char *gobj, int index, void *a2);

void *InitDemoQueensSword(char *a0, void *a1) {
    DemoQueenSwordWork *w;
    int i;

    w = (DemoQueenSwordWork *)iosMallocDebug(D_0063A438, 0xE0, D_006214E0, 802);
    *(DemoQueenSwordWork **)(*(char **)(a0 + 0x15C) + 0x830) = w;
    *w = D_004ED1F0;
    for (i = 0; i < *(int *)(*(char **)(a0 + 0x15C) + 0x8); i++) {
        initializeQueenzSword(a0, i, a1);
    }
    return w;
}
void ExecDemoQueensSword(char *a0) {
    char *e = *(char **)(a0 + 0x15C);
    char *p = *(char **)(e + 0x830);
    *(int *)(*(char **)(p + 0x5C) + 0x16C) = *(int *)(e + 0x74);
}
void SetWeaponOffsetMode(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC0) = a1;
}
