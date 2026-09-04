#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyParticleObject);
INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyObject);
INCLUDE_ASM("asm/nonmatchings/src/enemy", dispEnemyObject);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyCheckHit);
INCLUDE_ASM("asm/nonmatchings/src/enemy", CheckEnemyHit);
INCLUDE_ASM("asm/nonmatchings/src/enemy", InitEnemyGeo);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyGeo);
INCLUDE_ASM("asm/nonmatchings/src/enemy", DisplayEnemy);
extern void DisplayEnemy();
extern int IsActCharDead();
extern int isEnemyHyde(int *a0);

void EnemyDL(int *self)
{
    char *sub = *(char **)((char *)self + 0x164);
    unsigned long long flag = *(unsigned long long *)(sub + 0x18);
    if (((flag >> 33) & 1) == 0) return;
    IsActCharDead();
    if (isEnemyHyde(self) != 0) return;
    DisplayEnemy(self);
}
extern void ExecMotionOrient();

void DemoMotionGeo(int *self)
{
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x2B0) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x310) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x3B8) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x3BC) = 0;
    ExecMotionOrient(self);
}
INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyDissolve);
INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyFlyXZAccel);
INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyFlyXZAccelAll);
INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyFlyXZAccel);
void EnemyAI(void) {}
INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyFootPrintSwitch);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemySetfAppearAll);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemySetfDisappearAll);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemySetfDisappear);
extern void MatrixDrive_GetTurnZAngleXY(void *a0, void *a1, float f12, float f13, float f14);
extern void RotQuaternionX(void *a0, int a1);
extern void RotQuaternionY(void *a0, int a1);
extern void SetIdentityQuaternion(void *a0);
extern void SetParticleEffect(int a0, void *a1, void *a2);

void enemySetParticleDie(void *a0, float *a1) {
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, a1[0], a1[1], -a1[2]);
    SetIdentityQuaternion(buf);
    RotQuaternionX(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    RotQuaternionY(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    SetParticleEffect(0xC, a0, buf);
}
INCLUDE_ASM("asm/nonmatchings/src/enemy", ReviveEnemyParticle);
INCLUDE_ASM("asm/nonmatchings/src/enemy", isExistEnemyParticle);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyGetNSafeParts);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyDeleteParticle);
INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyHitGeometryAction);
INCLUDE_ASM("asm/nonmatchings/src/enemy", InitDemoMotionGeo);
INCLUDE_ASM("asm/nonmatchings/src/enemy", HotInitDemoMotionGeo);
INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyHitNodeFlag);
INCLUDE_ASM("asm/nonmatchings/src/enemy", RandomizeEnemy);
INCLUDE_ASM("asm/nonmatchings/src/enemy", SetEnemyWingRatio);
INCLUDE_ASM("asm/nonmatchings/src/enemy", CanThisEnemyFly);
INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyBattleType);
INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyDefLife);
INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyDefDodgeRange);
INCLUDE_ASM("asm/nonmatchings/src/enemy", GetEnemyDefParaIndex);
INCLUDE_ASM("asm/nonmatchings/src/enemy", ResetEnemyPositionInfo);
extern void GetRootPosition(void *dst, int *src);
extern void GetRootQuaternion(void *dst, int *src);
extern int SetParticleEffect__pn(int a, void *b, void *c) __asm__("SetParticleEffect");

void SetEnemyStonizedVisual(int *self)
{
    int local[8];
    GetRootPosition(local, self);
    GetRootQuaternion(&local[4], self);
    SetParticleEffect__pn(0x31, local, &local[4]);
    ((GObj *)self)->f_16C = 0;
}
