#include "common.h"




#include "ico/types.h"

#include "vu0.h"

typedef struct { char c[16]; } Blob16;
typedef struct { char c[4]; } Blob4;
extern void MatrixDrive_TurnObjectMatrix();
extern void playSEConditionID();
extern float func_00168C18();
void falldownSE(void) {}

void copyToWork(void) {}

INCLUDE_ASM("asm/nonmatchings/src/pool", flushWork);

extern void ClipWallBoxStop(void *a0);
extern char D_00553CB8[];
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float f);
extern void debug_assertMessage(void *msg);
extern void func_002641D8(void *a0, int a1, int a2);

void setNodePursueParticleEffectWithUpperLimit(void *a0, void *a1, float f) {
    char buf[0xC0];
    func_002641D8(buf, 0, 0xC0);
    GetRootMatrixByDObj(buf, a0);
    SlopeIKControl(buf + 0x10, a1, buf, f);
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        GetCylinderCollisionWithExceptOwnCollision(a0, buf + 0x20);
        debug_assertMessage(D_00553CB8);
    } else {
        GetCylinderCollisionWithExceptOwnCollision(a0, buf + 0x10);
    }
}

void SetFallDownSplash(long long *src, int *dest) {
    long long buf[2];
    buf[0] = src[0];
    buf[1] = src[1];
    *(float *)((char *)dest + 4) = func_00168C18((int *)buf, dest);
}

void GetPoolGlobalDrainVector(float *dst, float *a, float *b, float t)
{
    float u = 1.0f - t;
    dst[0] = a[0] * t + b[0] * u;
    dst[1] = a[1] * t + b[1] * u;
    dst[2] = a[2] * t + b[2] * u;
}

INCLUDE_ASM("asm/nonmatchings/src/pool", InitPoolGeo);

void updatePoolGeo(int a0)
{
    playSEConditionID(a0, 0x51);
}

INCLUDE_ASM("asm/nonmatchings/src/pool", dispPool);

extern char D_00553DD0[];
extern int D_00631B68;
extern int D_00631B6C;
extern char D_00631B78[];
extern void func_0012FF58(void);
extern void gif_MakeLine2DOffset(void *a0, int a1, int a2, void *a3, int a4);
extern void gif_MakeSprite(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SpriteOrg(int a0, long long a1);
extern void gsb_Reduction(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);
extern int tex_transVramClutTex(int a0, int a1);

void PoolDL(void) {
    char buf[0x20];

    func_0012FF58();
    D_00631B68 = tex_transVramClutTex(0, 0x400);
    D_00631B6C = tex_transVramClutTex(0, 0x400);
    gif_MakeSprite(D_00631B68, 0, 0x100, 0x100, 0, 0);
    gsb_Reduction(0);
    gif_SpriteOrg(0x4E, 0x30000000 | (D_00631B6C / 32));
    gsb_SetFrame(0, 4, 0);
    *(Blob16 *)buf = *(Blob16 *)D_00553DD0;
    *(Blob4 *)(buf + 0x10) = *(Blob4 *)D_00631B78;
    gif_MakeLine2DOffset(buf, 0, 0, buf + 0x10, 0);
    gsb_Reduction(1);
}

extern char D_00276140[];
extern int DebugDisp1CollisionWithColor(char *a0, int a1);
extern void ResetParticleEffectPackages(int a0, float f);
extern int func_001E8B68(int a0, int a1, int a2);

void InitLimitedPoolReflactionMesh(char *a0, char *a1, int a2, float f)
{
    int ret = DebugDisp1CollisionWithColor(a1, a2);
    if (ret != -1) {
        char *p = *(char **)(a1 + 0x15C);
        int r = func_001E8B68((int)a0, *(int *)(p + 0xC) + ret * 0x40 + 0x30, (int)D_00276140);
        ResetParticleEffectPackages(r, f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/pool", SetLayoutedPoolReflactionMesh);

void SetLimitedPoolReflactionMesh(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, *(int *)((int)((GObj *)(a1))->p_15C + 0x800) + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/src/pool", DispLimitedPoolReflactionMesh);

INCLUDE_ASM("asm/nonmatchings/src/pool", PoolGeo);

INCLUDE_ASM("asm/nonmatchings/src/pool", GetPoolGlobalHeight);

INCLUDE_ASM("asm/nonmatchings/src/pool", GetPoolGlobalHeightDetail);

INCLUDE_ASM("asm/nonmatchings/src/pool", CheckPoolHasGridMesh);

INCLUDE_ASM("asm/nonmatchings/src/pool", InitLayoutedPoolReflactionMesh);

INCLUDE_ASM("asm/nonmatchings/src/pool", poolRideFunc);

extern char D_00276040[];
extern char D_00276080[];
extern int D_00631970;
extern int D_00631C5C;
extern int D_00631C60;
extern int D_00632CC8;
extern void SetChainExtendedWeight(int a0, int a1, int a2);
extern void _PopCurrentMatrix(int a0);
extern void dispPool(int a0);
extern void func_0010F630(void);
extern void gif_SpriteOffset(int a0);
extern void gsb_KeepFrameBuffer(int a0);
extern void prim_DispParticle(int a0, void *a1, void *a2, int a3);

void getWave(int *a0) {
    gif_SpriteOffset(4);
    dispPool(4);
    gif_SpriteOrg(6, D_00631B68 | 0x20010000 | (0xC000LL << 19));
    gif_MakeSprite(0x800, 0, D_00631C5C, D_00631C60, 0, 0);
    gif_SpriteOrg(0x14, 0x60);
    gsb_KeepFrameBuffer(0);
    gsb_Reduction(1);
    gsb_SetFrame(0, 4, 0x80);
    func_0010F630();
    _PopCurrentMatrix(D_00631970 + 0x100);
    prim_DispParticle(a0[4], D_00276040, D_00276080, -1);
    if (D_00632CC8 != 0) {
        SetChainExtendedWeight(a0[6], a0[0], a0[1]);
    }
}

void func_0010D070(void) {}

float func_0010D078(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(float *)(p + 0x4);
}

INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010D088);

int func_0010D180(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x30) != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010D198);

INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010D338);

