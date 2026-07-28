#include "common.h"



extern void InitMotionOrient();
extern int func_001BB7E0();
extern int clip_floor_1(int *a0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyParticleObject);

INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyObject);

INCLUDE_ASM("asm/nonmatchings/src/enemy", dispEnemyObject);

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyCheckHit);

INCLUDE_ASM("asm/nonmatchings/src/enemy", CheckEnemyHit);

INCLUDE_ASM("asm/nonmatchings/src/enemy", InitEnemyGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", DisplayEnemy);

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyDL);

INCLUDE_ASM("asm/nonmatchings/src/enemy", DemoMotionGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyDissolve);

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyAI);

INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyFootPrintSwitch);

void EnemySetfAppearAll(int *self)
{
    char *sub = *(char **)((char *)self + 0x164);
    unsigned long long flag = *(unsigned long long *)(sub + 0x18);
    if (((flag >> 33) & 1) == 0) return;
    func_001BB7E0();
    if (clip_floor_1(self) != 0) return;
    SetEnemyFootPrintSwitch(self);
}

void EnemySetfDisappearAll(int *self)
{
    register int *alias;
    alias = self;

    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x2B0) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x310) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x3B8) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x3BC) = 0;
    InitMotionOrient(self);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemySetfDisappear);

void enemySetParticleDie(void) {}

INCLUDE_ASM("asm/nonmatchings/src/enemy", ReviveEnemyParticle);

INCLUDE_ASM("asm/nonmatchings/src/enemy", isExistEnemyParticle);

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyGetNSafeParts);

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyDeleteParticle);

INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyHitGeometryAction);

INCLUDE_ASM("asm/nonmatchings/src/enemy", InitDemoMotionGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", HotInitDemoMotionGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyHitNodeFlag);

