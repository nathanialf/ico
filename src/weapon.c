#include "common.h"

typedef struct { long long w[22]; } WeaponBlob;

typedef struct { char _0[0xC]; int f_C; char _10[0x14]; } WeaponEntry;

typedef struct { int f_0, f_4, f_8, f_C; char _pad10[0x40]; int f_50; char _pad54[0x4C]; int f_A0; } WGeo;



extern char DebugDisp1CollisionWithColor(char *self, int idx);
extern void func_001F23C0();
INCLUDE_ASM("asm/nonmatchings/src/weapon", torchOnOfWeaponSE);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void torchOffOfWeaponSE(char *a0, int a1, int a2, int a3) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    MatrixDrive_TurnObjectMatrix(a1, sub + 0x20);
    MatrixDrive_TurnObjectMatrix(a2, sub + 0x30);
    MatrixDrive_TurnObjectMatrix(a3, sub + 0x40);
}

extern void DemoMotionGeo(int a0, int a1, int a2, int a3);

void weaponHitReactionSE(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int x = *(int *)((char *)p + 0x800);
    DemoMotionGeo(a1, x + 0x20, x + 0x30, x + 0x40);
}

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

extern void GetRootPosition(void *buf, void *obj);
extern void *isysGObjSearchFromObjKindID_next(void *o);
extern void *isysGObjSearchFromObjLayoutID(int id);

void *WeaponHitEffect(void *a0, float radius) {
    int buf[4];
    float thresh2 = radius * radius;
    void *best = 0;
    char *obj;

    obj = (char *)isysGObjSearchFromObjLayoutID(0xE);
    GetRootPosition(buf, a0);
    while (obj != 0) {
        if (obj != (char *)a0) {
            char *sub = *(char **)(obj + 0x15C);
            char *p = *(char **)(sub + 0x800);
            if (*(int *)p != 0 && *(int *)(p + 8) == 0 && *(int *)(obj + 0x16C) != 0) {
                char *m = *(char **)(sub + 0xC) + 0x30;
                float d2;
                register float rd __asm__("$f0");
                __asm__ __volatile__(
                    "lqc2 $vf1, 0x0($29)\n"
                    "lqc2 $vf2, 0x0(%1)\n"
                    "vsub.xyzw $vf3, $vf1, $vf2\n"
                    "vmul.xyz $vf3, $vf3, $vf3\n"
                    "vaddy.x $vf3, $vf3, $vf3y\n"
                    "vaddz.x $vf3, $vf3, $vf3z\n"
                    "qmfc2.ni $2, $vf3\n"
                    "mtc1 $2, $f0\n"
                    : "=f"(rd) : "r"(m) : "$2", "memory");
                d2 = rd;
                if (d2 < thresh2) {
                    thresh2 = d2;
                    best = obj;
                }
            }
        }
        obj = (char *)isysGObjSearchFromObjKindID_next(obj);
    }
    return best;
}

void ExecWeaponHitReaction(void *a0) {
    WGeo *p = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    int x = p->f_8;
    if (x != 0) {
        *(int *)(*(char **)((char *)x + 0x15C) + 0x630) = 0;
    }
    p->f_8 = 0;
    p->f_C = -1;
    p->f_4 = 0;
}

int checkHit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x800);
    return q->f_0;
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", initializeQueenzSword);

INCLUDE_ASM("asm/nonmatchings/src/weapon", InitWeaponGeo);

extern void func_001F19F0();

void WeaponGeo(char *a0) {
    char *sub = *(char **)(*(char **)(a0 + 0x15C) + 0x800);
    int i;
    for (i = 0; i < *(int *)(sub + 0x50); i++) {
        func_001F19F0(*(int *)(*(int *)(sub + 0x54) + i * 4));
    }
}

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

extern void GetInverseQuaternion(void *a0, void *a1);

void WeaponDL(void *a0, void *a1, void *a2) {
    char *base = *(char **)((char *)a0 + 0x15C);
    char *r = base + 0xA0;
    WGeo *sub = *(WGeo **)(base + 0x800);
    int one = 1;
    int x = sub->f_8;
    if (x != 0) {
        x = *(int *)((char *)x + 0x15C);
        *(int *)(x + 0x630) = 0;
    }
    sub->f_4 = one;
    sub->f_C = -1;
    sub->f_8 = 0;
    if (a2 != 0) {
        GetInverseQuaternion(base + 0x150, a2);
    }
    MatrixDrive_TurnObjectMatrix(base + 0x130, a1);
    *(int *)(r + 0x9C) = 0;
}

int PickupWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    WGeo *q = *(WGeo **)((char *)p + 0x800);
    q->f_A0 = 0;
    return 1;
}

extern WeaponEntry D_006124F8[];

float CheckSwapableWeapon(void *a0) {
    WGeo *p = *(WGeo **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    int idx = p->f_0;
    return (float)D_006124F8[idx].f_C;
}

extern void IsTorchLightOn(int a0, void *a1);
extern void *isysGObjSearchFromObjKindID_next(void *o);
extern void *isysGObjSearchFromObjLayoutID(int id);

void ReleaseWeapon(void *a0) {
    char *g = isysGObjSearchFromObjLayoutID(0xE);
    if (g != 0) {
        do {
            char *s1 = *(char **)(*(char **)(g + 0x15C) + 0x800);
            if (*(int *)s1 == 1) {
                int i;
                for (i = 0; i < *(int *)(s1 + 0x50); i++) {
                    int *base = *(int **)(s1 + 0x54);
                    IsTorchLightOn(base[i], a0);
                }
            }
            g = isysGObjSearchFromObjKindID_next(g);
        } while (g != 0);
    }
}

extern char D_004C6240[];
extern char D_0061A850[];
extern int D_00632010;
extern void ReleaseWeaponWithFumbleTargetPos(void *a0, int a1, int a2);
extern void *func_0013A0F8(int a0, int a1, char *a2, int a3);

void *CheckWeaponKind(void *a0, int a1) {
    void *p = func_0013A0F8(D_00632010, 0xB0, D_0061A850, 0x2F2);
    char *m = *(char **)((char *)a0 + 0x15C);
    int i;

    *(void **)(m + 0x800) = p;
    *(WeaponBlob *)p = *(WeaponBlob *)D_004C6240;
    for (i = 0; i < *(int *)(*(char **)((char *)a0 + 0x15C) + 0x8); i++) {
        ReleaseWeaponWithFumbleTargetPos(a0, i, a1);
    }
    return p;
}

void LightTorchOnOfWeapon(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x800);
    int v = p[0x1D];
    int *r = *(int **)((char *)q + 0x5C);
    r[0x5B] = v;
}

INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOnOfWeaponWithNoSE);

INCLUDE_ASM("asm/nonmatchings/src/weapon", LightTorchOffOfWeapon);

