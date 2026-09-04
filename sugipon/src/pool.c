#include "common.h"

void falldownSE(void) {
}

void copyToWork(void) {
}

#include "vu0.h"

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void GetGlobalWallPlane(void *a0, void *a1);
extern float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float t);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);

void flushWork(void *obj, float threshold) {
    int buf0[4];
    int buf1[4];
    register float thr __asm__("$f20") = threshold;
    if (*(int *)(*(char **)((char *)obj + 0x15C) + 0x178) != 0) {
        register float dot __asm__("$f0");
        GetRootMatrixByDObj(buf0, obj);
        GetGlobalWallPlane(buf1, *(char **)((char *)obj + 0x15C) + 0x170);
        VU0_LSV_R(lqc2, 1, 0x0, buf0);
        VU0_LSV_R(lqc2, 2, 0x0, buf1);
        VU0_V3OP(vmul.xyz, 3, 1, 2);
        VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
        VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
        VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
        VU0_QMFC2_NI(v0, 3);
        VU0_MTC1(v0, 0);
        if (dot < thr) {
            GetProjectionOfPlaneWithKeepAway(buf0, buf1, buf0, thr);
        }
        GetCylinderCollisionWithExceptOwnCollision(obj, buf0);
    }
}

extern void memset(void *a0, int a1, int a2);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float f);
extern void ClipWallBoxStop(void *a0);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);
extern void debug_StdPrintfDummy(void *msg);
extern char D_0054DFF0[];

void AdjustRootPositionToVerticalSidePlaneOfWall(void *a0, void *a1, float f) {
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    GetRootMatrixByDObj(buf, a0);
    SlopeIKControl(buf + 0x10, a1, buf, f);
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        GetCylinderCollisionWithExceptOwnCollision(a0, buf + 0x20);
        debug_StdPrintfDummy(D_0054DFF0);
    } else {
        GetCylinderCollisionWithExceptOwnCollision(a0, buf + 0x10);
    }
}

extern float GetYProjectionOfPlane(int *buf, int *dest);

void fitYToPlane(long long *src, int *dest) {
    long long buf[2];
    buf[0] = src[0];
    buf[1] = src[1];
    *(float *)((char *)dest + 4) = GetYProjectionOfPlane((int *)buf, dest);
}

void GetBlendedMotionRootPos(float *a0, float *a1, float *a2, float t) {
    float s = 1.0f - t;
    a0[0] = a1[0] * t + a2[0] * s;
    a0[1] = a1[1] * t + a2[1] * s;
    a0[2] = a1[2] * t + a2[2] * s;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", _getMotRotElem);

extern void playSEConditionID(int a0, int a1);

void updatePoolGeo(int a0) {
    return playSEConditionID(a0, 0x51);
}

extern void func_0012FE30(void);
extern int tex_transVramClutTex(int a0, int a1);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_MakeSprite(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetZTest(int a0);
extern void gsb_KeepFrameBuffer(int a0);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_MakeLine2DOffset(void *a0, int a1, int a2, void *a3, int a4);
extern int D_00629E60;
extern int D_00629F5C;
extern int D_00629F60;
extern char D_0054E100[];
extern char D_0062BCE8[];
typedef struct { char c[16]; } Cpy16;
typedef struct { char c[4]; } Cpy4;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", dispPool);


extern void func_0012FE30(void);
extern int tex_transVramClutTex(int a0, int a1);
extern void gif_MakeSprite(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetZTest(int a0);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_MakeLine2DOffset(void *a0, int a1, int a2, void *a3, int a4);
extern int D_00629E60;
extern int D_00629E64;
extern char D_0054E100[];
extern char D_0062BCF0[];

typedef struct { char c[16]; } Blob16;
typedef struct { char c[4]; } Blob4;

void PoolDL(void) {
    char buf[0x20];

    func_0012FE30();
    D_00629E60 = tex_transVramClutTex(0, 0x400);
    D_00629E64 = tex_transVramClutTex(0, 0x400);
    gif_MakeSprite(D_00629E60, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (D_00629E64 / 32));
    gif_SetAlpha(0, 4, 0);
    *(Blob16 *)buf = *(Blob16 *)D_0054E100;
    *(Blob4 *)(buf + 0x10) = *(Blob4 *)D_0062BCF0;
    gif_MakeLine2DOffset(buf, 0, 0, buf + 0x10, 0);
    gif_SetZTest(1);
}

extern int DebugDisp1CollisionWithColor(char *a0, int a1);
extern int DeleteParticleEffectsByPackage(int a0, int a1, int a2);
extern void ResetParticleEffectPackages(int a0, float f);
extern char D_002724B0[];

void setNodePursueParticleEffectWithUpperLimit(char *a0, char *a1, int a2, float f)
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

extern void gif_SpriteOffset(int a0);
extern void dispPool(int a0);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_MakeSprite(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gsb_KeepFrameBuffer(int a0);
extern void gif_SetZTest(int a0);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void func_0010F9D0(void);
extern void _SetCurrentMatrix(int a0);
extern void prim_DispParticle(int a0, void *a1, void *a2, int a3);
extern void SetChainExtendedWeight(int a0, int a1, int a2);
extern int D_00629E60;
extern int D_00629F5C;
extern int D_00629F60;
extern int D_00629C70;
extern int D_0062AF90;
extern char D_002723B0[];
extern char D_002723F0[];

void getWave(int *a0) {
    gif_SpriteOffset(4);
    dispPool(4);
    gif_SetGsReg(6, D_00629E60 | 0x20010000 | (0xC000LL << 19));
    gif_MakeSprite(0x800, 0, D_00629F5C, D_00629F60, 0, 0);
    gif_SetGsReg(0x14, 0x60);
    gsb_KeepFrameBuffer(0);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    func_0010F9D0();
    _SetCurrentMatrix(D_00629C70 + 0x100);
    prim_DispParticle(a0[4], D_002723B0, D_002723F0, -1);
    if (D_0062AF90 != 0) {
        SetChainExtendedWeight(a0[6], a0[0], a0[1]);
    }
}

void func_0010D3B0(void) {
}

extern void debug_StdPrintfDummy();
extern char D_0054E110[];

float func_0010D3B8(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    if (p == 0) {
        debug_StdPrintfDummy(D_0054E110);
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
