#include "common.h"



extern void InitMotionOrient();
extern int func_001BB7E0();
extern int clip_floor_1(int *a0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyParticleObject);

INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyObject);

INCLUDE_ASM("asm/nonmatchings/src/enemy", dispEnemyObject);

extern int D_006325B4;
extern int D_00633394;
extern int D_006333AC;
extern char D_006333B8[];
extern void GetParticleEffectPackage(int x);
extern void InitCamera(int x, int y, int z);
extern void debug_assertMessage(char *p);

void EnemyCheckHit(void)
{
    GetParticleEffectPackage(D_00633394);
    D_00633394 = -1;
    InitCamera(D_006333AC, 0, 3);
    D_006325B4 = 0;
    debug_assertMessage(D_006333B8);
}

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

extern void GetMatrixFromQuaternion(void *a0);
extern void MatrixDrive_GetMatrix(void *a0, void *a1, float f12, float f13, float f14);
extern void func_0010E0B8(void *a0, int a1);
extern void func_0010E158(void *a0, int a1);
extern void func_001E8B48(int a0, void *a1, void *a2);

void SetEnemyHitGeometryAction(void *a0, float *a1) {
    char buf[0x20];
    MatrixDrive_GetMatrix(buf + 0x10, buf + 0x12, a1[0], a1[1], -a1[2]);
    GetMatrixFromQuaternion(buf);
    func_0010E0B8(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    func_0010E158(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    func_001E8B48(0xC, a0, buf);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", InitDemoMotionGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", HotInitDemoMotionGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyHitNodeFlag);

