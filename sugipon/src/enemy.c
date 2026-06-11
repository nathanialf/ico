#include "common.h"

/* enemy 0x164 actor-state view (local) */
typedef struct { char _0[0x18]; unsigned long long f_18; } EnemyState;

/* enemy 0x7F0 view (local) */
typedef struct { char _0[0x2C]; int f_2C; } EnemyGeo;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", setEnemyParticleObject);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", setEnemyObject);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", dispEnemyObject);

extern int D_0062B654;
extern int D_0062B66C;
extern int D_0062A894;
extern char D_0062D4F8[];
extern void GetParticleEffectPackage(int x);
extern void InitCamera(int x, int y, int z);
extern void debug_assertMessage(char *p);

void EnemyCheckHit(void)
{
    GetParticleEffectPackage(D_0062B654);
    D_0062B654 = -1;
    InitCamera(D_0062B66C, 0, 3);
    D_0062A894 = 0;
    debug_assertMessage(D_0062D4F8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", CheckEnemyHit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", InitEnemyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", DisplayEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", DemoMotionGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", SetEnemyDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", SetEnemyFootPrintSwitch);

extern int clip_floor_1(int *self);
extern void func_001B8D08(void);
extern void SetEnemyFootPrintSwitch(int *self);

void EnemySetfAppearAll(int *self)
{
    EnemyState *sub = *(EnemyState **)((char *)self + 0x164);
    unsigned long long flag = sub->f_18;
    if (((flag >> 33) & 1) == 0) return;
    func_001B8D08();
    if (clip_floor_1(self) != 0) return;
    SetEnemyFootPrintSwitch(self);
}

extern void InitMotionOrient(int a0);

void EnemySetfDisappearAll(int a0) {
    *(int *)(*(int *)(a0 + 0x15C) + 0x2A0) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x300) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x3A8) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x3AC) = 0;
    InitMotionOrient(a0);
}

void EnemySetfDisappear(char *self, float arg) {
    char *s = *(char **)(self + 0x15C);
    *(float *)(*(char **)(s + 0x830) + 0x30) = arg;
    if (arg < 0.0f) {
        *(float *)(*(char **)(s + 0x830) + 0x30) = 0.0f;
    }
    if (1.0f < *(float *)(*(char **)(s + 0x830) + 0x30)) {
        *(float *)(*(char **)(s + 0x830) + 0x30) = 1.0f;
    }
}

void enemySetParticleDie(void) {
}

void ReviveEnemyParticle(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EnemyGeo *q = *(EnemyGeo **)((char *)p + 0x7F0);
    q->f_2C = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", isExistEnemyParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyGetNSafeParts);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", EnemyDeleteParticle);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemy", SetEnemyHitGeometryAction);

void InitDemoMotionGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *base = *(int **)((char *)q + 0x14);
    base[a1] = 0;
}

int HotInitDemoMotionGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *r = *(int **)((char *)q + 0x14);
    return r[a1] == 0;
}

int GetEnemyHitNodeFlag(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int zero;
    int n;
    int count = *(int *)((char *)p + 0x88);
    int result = 0;
    zero = 0;
    n = count;
    if (n > zero) {
        int *q = *(int **)((char *)p + 0x7F0);
        int *base = *(int **)((char *)q + 0x14);
        int i;
        for (i = zero; i < count; i++) {
            if (base[i] == zero) {
                result++;
            }
        }
    }
    return result;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_00617DA8;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00617E50;  /* stride 0x4 */

/* end struct shapes */
