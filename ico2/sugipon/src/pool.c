#include "common.h"
#include "ico/types.h"
#include "vu0.h"

typedef struct {
    char c[16];
} Blob16;

typedef struct {
    char c[4];
} Blob4;

extern void ExecuteSEPackage(int a0, int a1);

void falldownSE(int a0)
{
    ExecuteSEPackage(a0, 0x56);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", copyToWork);

extern char D_0054DA50[];
extern int D_00639F28;
extern int D_00639F2C;
extern char D_00639F38[];
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetDrawEnviroment(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_SetZTest(int a0);
extern void gif_SpriteSensitiveOrg(void *a0, int a1, void *a2, void *a3, int a4);
extern int tex_AllocVramAuto(int a0, int a1);
extern void tex_ResetVramPri(void);

void flushWork(void)
{
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
        int r = SetParticleEffectActiveSensing((int)a0, *(int *)(p + 0xC) + ret * 0x40 + 0x30,
                                               (int)D_002907E0);
        SetParticleEffectUpperLimit(r, f);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", SetFallDownSplash);

extern void CopyVector(void *a0, void *a1);

void GetPoolGlobalDrainVector(void *dst, char *a0)
{
    CopyVector(dst, *(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10);
}

ASM_LIT4_SLOT(D_00638B84, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", InitPoolGeo);
ASM_LIT4_SLOT(D_00638B88, 0.0005f);
ASM_LIT4_SLOT(D_00638B8C, 0.05f);
ASM_LIT4_SLOT(D_00638B90, 0.8f);
ASM_LIT4_SLOT(D_00638B94, 0.1f);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", updatePoolGeo);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", dispPool);

extern int D_0028F4C0[];
extern void DispMultiBgaManagerWithKind(int kind, int a1, int a2);
extern void updatePoolGeo(char *self);
extern void dispPool(char *self);
extern void p2o_DispVU1(char *self);

void PoolDL(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    DispMultiBgaManagerWithKind(0x1F2, *(int *)(w + 0x2C), 10);
    DispMultiBgaManagerWithKind(0x1F3, *(int *)(w + 0x24), 2);
    if (D_0028F4C0[5] == 0) {
        *(short *)(w + 0xCC) =
            (short)((float)*(short *)(w + 0xCC) +
                    60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 2000.0f);
    }
    if (*(int *)(w + 0x30) != 0) {
        updatePoolGeo(self);
        dispPool(self);
    } else {
        p2o_DispVU1(self);
    }
}

extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern char *prim_InitMesh3D(int nx, int ny, int rot, long long col, unsigned int col2, int f58);
extern char D_0054DA60[];
extern int D_0063A438;

void InitLimitedPoolReflactionMesh(char *a0)
{
    int i;
    int j;

    *(char **)(a0 + 0x10) = prim_InitMesh3D(*(int *)(a0 + 0x4), *(int *)(a0 + 0x0), 1, 0x1C,
                                            *(unsigned int *)(a0 + 0x1C), 1);
    *(char ****)(a0 + 0x14) =
        (char ***)iosMallocDebug(D_0063A438, *(int *)(a0 + 0x0) * 4, D_0054DA60, 884);
    *(char **)(a0 + 0x18) = iosMallocDebug(D_0063A438, *(int *)(a0 + 0x0) * 4, D_0054DA60, 885);
    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        *(char **)(*(char **)(a0 + 0x18) + i * 4) =
            *(char **)(*(char **)(a0 + 0x10) + 0x6C) + i * *(int *)(a0 + 0x4) * 16;
        (*(char ****)(a0 + 0x14))[i] =
            (char **)iosMallocDebug(D_0063A438, *(int *)(a0 + 0x4) * 4, D_0054DA60, 890);
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            (*(char ****)(a0 + 0x14))[i][j] = 0;
        }
    }
}

ASM_LIT4_SLOT(D_00638B98, 0.1f);
ASM_LIT4_SLOT(D_00638B9C, 0.8f);
ASM_LIT4_SLOT(D_00638BA0, 1.15f);
ASM_LIT4_SLOT(D_00638BA4, 0.8f);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", SetLayoutedPoolReflactionMesh);
ASM_LIT4_SLOT(D_00638BA8, 0.3f);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/pool", SetLimitedPoolReflactionMesh);

extern int D_0063A064;
extern int D_0063A068;
extern int D_0063B148;
extern char D_002906E0[];
extern char D_00290720[];
extern int matrixptr;
extern void gif_StartPacketPri(int pri);
extern void copyToWork(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_EndPacket(void);
extern void _SetCurrentMatrix(int m);
extern void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
extern void DispMeshWire(int *rows, int nx, int ny);

void DispLimitedPoolReflactionMesh(int *a0)
{
    gif_StartPacketPri(4);
    copyToWork(4);
    gif_SetGsReg(6, D_00639F28 | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(a0[4], D_002906E0, D_00290720, -1);
    if (D_0063B148 != 0) {
        DispMeshWire((int *)a0[6], a0[0], a0[1]);
    }
}

void PoolGeo(void) {}

float GetPoolGlobalHeight(char *a0)
{
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4);
}

float GetPoolGlobalHeightDetail(char *a0, float *pos)
{
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
        return *(float *)(*(char **)(*(char **)(p + 0x4C) + ix * 4) + iz * 4) * 100.0f +
               *(float *)(p + 0x4);
    }
    return *(float *)(p + 0x4);
}

int CheckPoolHasGridMesh(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x30) != 0;
}

extern void InitLimitedPoolReflactionMesh(char *a0);
extern void _InterVectorXYZ(void *p0, void *p1, void *p2, float t);

void InitLayoutedPoolReflactionMesh(char *a0, char *a1)
{
    float v0[4];
    float v1[4];
    int i;
    int j;

    InitLimitedPoolReflactionMesh(a0);
    for (i = 0; i < *(int *)(a0 + 0x0); i++) {
        _InterVectorXYZ(v0, a1 + 0x0, a1 + 0x20, (float)i / (float)(*(int *)(a0 + 0x0) - 1));
        _InterVectorXYZ(v1, a1 + 0x10, a1 + 0x30, (float)i / (float)(*(int *)(a0 + 0x0) - 1));
        for (j = 0; j < *(int *)(a0 + 0x4); j++) {
            _InterVectorXYZ(*(char **)(*(char **)(a0 + 0x10) + 0x6C) +
                                (i * *(int *)(a0 + 0x4) + j) * 0x10,
                            v0, v1, (float)j / (float)(*(int *)(a0 + 0x4) - 1));
            *(float *)(*(char **)(*(char **)(a0 + 0x10) + 0x6C) +
                       (i * *(int *)(a0 + 0x4) + j) * 0x10 + 0xC) = 1.0f;
        }
    }
}

int poolRideFunc(char **a0, char *a1)
{
    char *e = *(char **)(a1 + 0x15C);
    char *p = *(char **)(*(char **)(a0[0] + 0x15C) + 0x830);
    *(float *)(e + 0x644) = *(float *)(e + 0xA4) - *(float *)(p + 4);
    return 1;
}

float getWave(float t)
{
    t += 50.0f;
    t -= (float)(int)(t * 0.005f) * 200.0f;
    if (t < 100.0f) {
        return t * 0.01f - 0.5f;
    }
    return -(t - 100.0f) * 0.01f + 0.5f;
}
