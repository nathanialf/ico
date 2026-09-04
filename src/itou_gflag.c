#include "common.h"


extern void itou_boss_gflag_init();
extern void *InitParticleLayoutGeo(void);

void itouGFlagInit(void) {
    void *r = InitParticleLayoutGeo();
    **(int **)((char *)r + 0x60) = 1;
}

void itouGflagLoad(int a0, int a1, int a2, int a3)
{
    itou_boss_gflag_init(a0, a1, a2, a3);
}

void itouGflagSave(int a0, int a1, int a2, int a3)
{
    itou_boss_gflag_init(a0, a1, a2, a3);
}

void func_00198430(void) {}

INCLUDE_ASM("asm/nonmatchings/src/itou_gflag", m33_to_quat);

