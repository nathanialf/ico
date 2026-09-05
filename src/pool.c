#include "common.h"

#include "ico/types.h"
#include "vu0.h"
typedef struct { char c[16]; } Blob16;
typedef struct { char c[4]; } Blob4;

extern void ExecuteSEPackage(int a0, int a1);
void falldownSE(int a0) {
    ExecuteSEPackage(a0, 0x56);
}
INCLUDE_ASM("asm/nonmatchings/src/pool", copyToWork);
extern char D_0054DA50[];
extern int D_00639F28;
extern int D_00639F2C;
extern char D_00639F38[];
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetDrawEnviroment(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_SetZTest(int a0);
extern void gif_SpriteSensitiveOrg(void *a0, int a1, int a2, void *a3, int a4);
extern int tex_AllocVramAuto(int a0, int a1);
extern void tex_ResetVramPri(void);

void flushWork(void) {
    char buf[0x20];

    tex_ResetVramPri();
    D_00639F28 = tex_AllocVramAuto(0, 0x400);
    D_00639F2C = tex_AllocVramAuto(0, 0x400);
    gif_SetDrawEnviroment(D_00639F28, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (D_00639F2C / 32));
    gif_SetAlpha(0, 4, 0);
    *(Blob16 *)buf = *(Blob16 *)D_0054DA50;
    *(Blob4 *)(buf + 0x10) = *(Blob4 *)D_00639F38;
    gif_SpriteSensitiveOrg(buf, 0, 0, buf + 0x10, 0);
    gif_SetZTest(1);
}
extern char D_002907E0[];
extern int GetSkeltonFocusNode(char *a0, int a1);
extern int SetParticleEffectActiveSensing(int a0, int a1, int a2);
extern void SetParticleEffectUpperLimit(int a0, float f);

void setNodePursueParticleEffectWithUpperLimit(char *a0, char *a1, int a2, float f)
{
    int ret = GetSkeltonFocusNode(a1, a2);
    if (ret != -1) {
        char *p = *(char **)(a1 + 0x15C);
        int r = SetParticleEffectActiveSensing((int)a0, *(int *)(p + 0xC) + ret * 0x40 + 0x30, (int)D_002907E0);
        SetParticleEffectUpperLimit(r, f);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/pool", SetFallDownSplash);
extern void CopyVector(void *a0, void *a1);
void GetPoolGlobalDrainVector(void *dst, char *a0) {
    CopyVector(dst, *(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10);
}
ASM_LIT4_SLOT(D_00638B84, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/pool", InitPoolGeo);
ASM_LIT4_SLOT(D_00638B88, 0.0005f);
ASM_LIT4_SLOT(D_00638B8C, 0.05f);
ASM_LIT4_SLOT(D_00638B90, 0.8f);
ASM_LIT4_SLOT(D_00638B94, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/pool", updatePoolGeo);
INCLUDE_ASM("asm/nonmatchings/src/pool", dispPool);
INCLUDE_ASM("asm/nonmatchings/src/pool", PoolDL);
INCLUDE_ASM("asm/nonmatchings/src/pool", InitLimitedPoolReflactionMesh);
ASM_LIT4_SLOT(D_00638B98, 0.1f);
ASM_LIT4_SLOT(D_00638B9C, 0.8f);
ASM_LIT4_SLOT(D_00638BA0, 1.15f);
ASM_LIT4_SLOT(D_00638BA4, 0.8f);
INCLUDE_ASM("asm/nonmatchings/src/pool", SetLayoutedPoolReflactionMesh);
ASM_LIT4_SLOT(D_00638BA8, 0.3f);
INCLUDE_ASM("asm/nonmatchings/src/pool", SetLimitedPoolReflactionMesh);
INCLUDE_ASM("asm/nonmatchings/src/pool", DispLimitedPoolReflactionMesh);
void PoolGeo(void) {}
float GetPoolGlobalHeight(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4);
}
float GetPoolGlobalHeightDetail(char *a0, float *pos) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    float inv;
    int ix;
    int iz;

    if (*(int *)(p + 0x30) != 0) {
        inv = 1.0f / *(float *)(p + 0x3C);
        ix = (int)((pos[0] - *(float *)(p + 0x0)) * inv + (float)(*(int *)(p + 0x34) >> 1));
        iz = (int)((pos[2] - *(float *)(p + 0x8)) * inv + (float)(*(int *)(p + 0x38) >> 1));
        ix = ix >= 0 ? (ix < *(int *)(p + 0x34) ? ix : *(int *)(p + 0x34) - 1) : 0;
        iz = iz >= 0 ? (iz < *(int *)(p + 0x38) ? iz : *(int *)(p + 0x38) - 1) : 0;
        return *(float *)(*(char **)(*(char **)(p + 0x4C) + ix * 4) + iz * 4) * 100.0f + *(float *)(p + 0x4);
    }
    return *(float *)(p + 0x4);
}
int CheckPoolHasGridMesh(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x30) != 0;
}
extern void InitLimitedPoolReflactionMesh(char *a0);
extern void _InterVectorXYZ(void *p0, void *p1, void *p2, float t);

void InitLayoutedPoolReflactionMesh(char *a0, char *a1) {
    float v0[4];
    float v1[4];
    int i;
    int j;

    InitLimitedPoolReflactionMesh(a0);
    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        _InterVectorXYZ(v0, a1 + 0x0, a1 + 0x20, (float)i / (float)(*(int *)(a0 + 0x0) - 1));
        _InterVectorXYZ(v1, a1 + 0x10, a1 + 0x30, (float)i / (float)(*(int *)(a0 + 0x0) - 1));
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            _InterVectorXYZ(*(char **)(*(char **)(a0 + 0x10) + 0x6C) + (i * *(int *)(a0 + 0x4) + j) * 0x10, v0, v1, (float)j / (float)(*(int *)(a0 + 0x4) - 1));
            *(float *)(*(char **)(*(char **)(a0 + 0x10) + 0x6C) + (i * *(int *)(a0 + 0x4) + j) * 0x10 + 0xC) = 1.0f;
        }
    }
}
int poolRideFunc(char **a0, char *a1) {
    char *e = *(char **)(a1 + 0x15C);
    char *p = *(char **)(*(char **)(a0[0] + 0x15C) + 0x830);
    *(float *)(e + 0x644) = *(float *)(e + 0xA4) - *(float *)(p + 4);
    return 1;
}

float getWave(float t) {
    t += 50.0f;
    t -= (float)(int)(t * 0.005f) * 200.0f;
    if (t < 100.0f) {
        return t * 0.01f - 0.5f;
    }
    return -(t - 100.0f) * 0.01f + 0.5f;
}
