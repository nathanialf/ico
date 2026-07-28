#include "common.h"




#include "ico/types.h"
extern void MatrixDrive_TurnObjectMatrix();
extern void playSEConditionID();
extern float func_00168C18();
void falldownSE(void) {}

void copyToWork(void) {}

INCLUDE_ASM("asm/nonmatchings/src/pool", flushWork);

INCLUDE_ASM("asm/nonmatchings/src/pool", setNodePursueParticleEffectWithUpperLimit);

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

INCLUDE_ASM("asm/nonmatchings/src/pool", PoolDL);

INCLUDE_ASM("asm/nonmatchings/src/pool", InitLimitedPoolReflactionMesh);

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

INCLUDE_ASM("asm/nonmatchings/src/pool", getWave);

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

