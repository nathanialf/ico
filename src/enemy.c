#include "common.h"



extern void InitMotionOrient();
extern int func_001BB7E0();
extern int isEnemyHyde(int *a0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", saveEffectData);

INCLUDE_ASM("asm/nonmatchings/src/enemy", setEnemyObject);

INCLUDE_ASM("asm/nonmatchings/src/enemy", dispEnemyObject);

extern int D_006325B4;
extern int D_00633394;
extern int D_006333AC;
extern char D_006333B8[];
extern void GetParticleEffectPackage(int x);
extern void Camctrl_SetTarget(int x, int y, int z);
extern void debug_StdPrintfDummy(char *p);

void exitEffectTool(void)
{
    GetParticleEffectPackage(D_00633394);
    D_00633394 = -1;
    Camctrl_SetTarget(D_006333AC, 0, 3);
    D_006325B4 = 0;
    debug_StdPrintfDummy(D_006333B8);
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
    if (isEnemyHyde(self) != 0) return;
    SetEnemyFootPrintSwitch(self);
}

void EnemySetfDisappearAll(int *self)
{
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x2B0) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x310) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x3B8) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x3BC) = 0;
    InitMotionOrient(self);
}

void EnemySetfDisappear(char *self, float arg) {
    char *s = *(char **)(self + 0x15C);
    *(float *)(*(char **)(s + 0x840) + 0x30) = arg;
    if (arg < 0.0f) {
        *(float *)(*(char **)(s + 0x840) + 0x30) = 0.0f;
    }
    if (1.0f < *(float *)(*(char **)(s + 0x840) + 0x30)) {
        *(float *)(*(char **)(s + 0x840) + 0x30) = 1.0f;
    }
}

void enemySetParticleDie(void) {}

typedef struct { char _0[0x2C]; int f_2C; } EnemyGeo2;

void ReviveEnemyParticle(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EnemyGeo2 *q = *(EnemyGeo2 **)((char *)p + 0x800);
    q->f_2C = a1;
}

void isExistEnemyParticle(char *a0) {
    int i;
    int n = *(int *)(*(int *)(a0 + 0x15C) + 0x88);
    for (i = 0; i < n; i++) {
        int *p = *(int **)(*(int *)(a0 + 0x15C) + 0x800);
        *(int *)(*(int *)((char *)p + 0x14) + i * 4) = 0;
    }
}

void EnemyGetNSafeParts(char *a0) {
    int i;
    int n = *(int *)(*(int *)(a0 + 0x15C) + 0x88);
    for (i = 0; i < n; i++) {
        int *p = *(int **)(*(int *)(a0 + 0x15C) + 0x800);
        *(int *)(*(int *)((char *)p + 0x14) + i * 4) = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyDeleteParticle);

extern void GetMatrixFromQuaternion(void *a0);
extern void MatrixDrive_GetTurnZAngleXY(void *a0, void *a1, float f12, float f13, float f14);
extern void func_0010E0B8(void *a0, int a1);
extern void func_0010E158(void *a0, int a1);
extern void func_001E8B48(int a0, void *a1, void *a2);

void SetEnemyHitGeometryAction(void *a0, float *a1) {
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, a1[0], a1[1], -a1[2]);
    GetMatrixFromQuaternion(buf);
    func_0010E0B8(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    func_0010E158(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    func_001E8B48(0xC, a0, buf);
}

void InitDemoMotionGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x800);
    int *base = *(int **)((char *)q + 0x14);
    base[a1] = 0;
}

int HotInitDemoMotionGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x800);
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
        int *q = *(int **)((char *)p + 0x800);
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

