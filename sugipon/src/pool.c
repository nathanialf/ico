#include "common.h"

void falldownSE(void) {
}

void copyToWork(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", flushWork);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", setNodePursueParticleEffectWithUpperLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", SetFallDownSplash);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", GetPoolGlobalDrainVector);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", InitPoolGeo);

extern void playSEConditionID(int a0, int a1);

void updatePoolGeo(int a0) {
    return playSEConditionID(a0, 0x51);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", dispPool);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", PoolDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", InitLimitedPoolReflactionMesh);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", func_0010D3B8);

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
