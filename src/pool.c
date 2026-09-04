#include "common.h"

#include "ico/types.h"
#include "vu0.h"
typedef struct { char c[16]; } Blob16;
typedef struct { char c[4]; } Blob4;

INCLUDE_ASM("asm/nonmatchings/src/pool", falldownSE);
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
INCLUDE_ASM("asm/nonmatchings/src/pool", GetPoolGlobalDrainVector);
INCLUDE_ASM("asm/nonmatchings/src/pool", InitPoolGeo);
INCLUDE_ASM("asm/nonmatchings/src/pool", updatePoolGeo);
INCLUDE_ASM("asm/nonmatchings/src/pool", dispPool);
INCLUDE_ASM("asm/nonmatchings/src/pool", PoolDL);
INCLUDE_ASM("asm/nonmatchings/src/pool", InitLimitedPoolReflactionMesh);
INCLUDE_ASM("asm/nonmatchings/src/pool", SetLayoutedPoolReflactionMesh);
INCLUDE_ASM("asm/nonmatchings/src/pool", SetLimitedPoolReflactionMesh);
INCLUDE_ASM("asm/nonmatchings/src/pool", DispLimitedPoolReflactionMesh);
void PoolGeo(void) {}
float GetPoolGlobalHeight(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4);
}
INCLUDE_ASM("asm/nonmatchings/src/pool", GetPoolGlobalHeightDetail);
int CheckPoolHasGridMesh(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x30) != 0;
}
INCLUDE_ASM("asm/nonmatchings/src/pool", InitLayoutedPoolReflactionMesh);
int poolRideFunc(char **a0, char *a1) {
    char *e = *(char **)(a1 + 0x15C);
    char *p = *(char **)(*(char **)(a0[0] + 0x15C) + 0x830);
    *(float *)(e + 0x644) = *(float *)(e + 0xA4) - *(float *)(p + 4);
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/pool", getWave);
