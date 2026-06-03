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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", SetLimitedPoolReflactionMesh);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", func_0010D510);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", func_0010D528);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/pool", func_0010D6C8);
