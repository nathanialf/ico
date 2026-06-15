#include "common.h"

void falldownSE(void) {
}

void copyToWork(void) {
}

#include "vu0.h"

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void func_00166AF8(void *a0, void *a1);
extern float func_001047C0(void *a0, void *a1, void *a2, float t);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);

void flushWork(void *obj, float threshold) {
    int buf0[4];
    int buf1[4];
    register float thr __asm__("$f20") = threshold;
    if (*(int *)(*(char **)((char *)obj + 0x15C) + 0x178) != 0) {
        register float dot __asm__("$f0");
        GetRootMatrixByDObj(buf0, obj);
        func_00166AF8(buf1, *(char **)((char *)obj + 0x15C) + 0x170);
        VU0_LSV_R(lqc2, 1, 0x0, buf0);
        VU0_LSV_R(lqc2, 2, 0x0, buf1);
        VU0_V3OP(vmul.xyz, 3, 1, 2);
        VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
        VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
        VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
        VU0_QMFC2_NI(v0, 3);
        VU0_MTC1(v0, 0);
        if (dot < thr) {
            func_001047C0(buf0, buf1, buf0, thr);
        }
        GetCylinderCollisionWithExceptOwnCollision(obj, buf0);
    }
}

extern void func_00260568(void *a0, int a1, int a2);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float f);
extern void ClipWallBoxStop(void *a0);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);
extern void debug_assertMessage(void *msg);
extern char D_0054DFF0[];

void setNodePursueParticleEffectWithUpperLimit(void *a0, void *a1, float f) {
    char buf[0xC0];
    func_00260568(buf, 0, 0xC0);
    GetRootMatrixByDObj(buf, a0);
    SlopeIKControl(buf + 0x10, a1, buf, f);
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        GetCylinderCollisionWithExceptOwnCollision(a0, buf + 0x20);
        debug_assertMessage(D_0054DFF0);
    } else {
        GetCylinderCollisionWithExceptOwnCollision(a0, buf + 0x10);
    }
}

extern float func_00166A48(int *buf, int *dest);

void SetFallDownSplash(long long *src, int *dest) {
    long long buf[2];
    buf[0] = src[0];
    buf[1] = src[1];
    *(float *)((char *)dest + 4) = func_00166A48((int *)buf, dest);
}

void GetPoolGlobalDrainVector(float *a0, float *a1, float *a2, float t) {
    float s = 1.0f - t;
    a0[0] = a1[0] * t + a2[0] * s;
    a0[1] = a1[1] * t + a2[1] * s;
    a0[2] = a1[2] * t + a2[2] * s;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", InitPoolGeo);

extern void playSEConditionID(int a0, int a1);

void updatePoolGeo(int a0) {
    return playSEConditionID(a0, 0x51);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", dispPool);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", PoolDL);

extern int DebugDisp1CollisionWithColor(char *a0, int a1);
extern int DeleteParticleEffectsByPackage(int a0, int a1, int a2);
extern void ResetParticleEffectPackages(int a0, float f);
extern char D_002724B0[];

void InitLimitedPoolReflactionMesh(char *a0, char *a1, int a2, float f)
{
    int ret = DebugDisp1CollisionWithColor(a1, a2);
    if (ret != -1) {
        char *p = *(char **)(a1 + 0x15C);
        int r = DeleteParticleEffectsByPackage((int)a0, *(int *)(p + 0xC) + ret * 0x40 + 0x30, (int)D_002724B0);
        ResetParticleEffectPackages(r, f);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", SetLayoutedPoolReflactionMesh);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void SetLimitedPoolReflactionMesh(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, *(char **)(*(char **)(a1 + 0x15C) + 0x7F0) + 0x10);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", DispLimitedPoolReflactionMesh);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", PoolGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", GetPoolGlobalHeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", GetPoolGlobalHeightDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", CheckPoolHasGridMesh);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", InitLayoutedPoolReflactionMesh);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", poolRideFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", getWave);

void func_0010D3B0(void) {
}

extern void debug_assertMessage();
extern char D_0054E110[];

float func_0010D3B8(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    if (p == 0) {
        debug_assertMessage(D_0054E110);
        return 0.0f;
    }
    return *(float *)(p + 0x4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", func_0010D3F8);

int func_0010D510(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x7F0) + 0x30) != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", func_0010D528);

int func_0010D6C8(char *a0, char *a1) {
    char *x = *(char **)a0;
    char *b = *(char **)(a1 + 0x15C);
    char *c = *(char **)(x + 0x15C);
    char *d = *(char **)(c + 0x7F0);
    *(float *)(b + 0x634) = *(float *)(b + 0xA4) - *(float *)(d + 4);
    return 1;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_004B8C40;

/* end struct shapes */
