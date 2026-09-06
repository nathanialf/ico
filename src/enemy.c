#include "common.h"
typedef struct {
    int a;
    int b;
    float life;
    int c;
    int d;
    float dodge;
    int paraIndex : 8;
    unsigned int flyType : 2;
    unsigned int battleType : 2;
} EnemyDef;
extern EnemyDef D_00624880[];

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
void SetEnemyDissolve(char *self, float ratio)
{
    char *sub = *(char **)(self + 0x15C);

    *(float *)(*(char **)(sub + 0x870) + 0x30) = ratio;
    if (*(float *)(*(char **)(sub + 0x870) + 0x30) < 0.0f)
        *(float *)(*(char **)(sub + 0x870) + 0x30) = 0.0f;
    if (*(float *)(*(char **)(sub + 0x870) + 0x30) > 1.0f)
        *(float *)(*(char **)(sub + 0x870) + 0x30) = 1.0f;
}
void SetEnemyFlyXZAccel(char *a0, float f) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x50) = f;
}
extern char *isysGObjSearchFromObjKindID_begin(int kind);
extern char *isysGObjSearchFromObjKindID_next(char *g);

void SetEnemyFlyXZAccelAll(float accel)
{
    char *g = isysGObjSearchFromObjKindID_begin(4);
    while (g != 0) {
        *(float *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 0x50) = accel;
        g = isysGObjSearchFromObjKindID_next(g);
    }
}
float GetEnemyFlyXZAccel(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x50);
}
void EnemyAI(void) {}
void SetEnemyFootPrintSwitch(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x2C) = a1;
}
void EnemySetfAppearAll(char *self)
{
    int n = *(int *)(*(int *)(self + 0x15C) + 0x88);
    int i;

    for (i = 0; i < n; i++)
        ((int *)*(int *)(*(int *)(*(int *)(self + 0x15C) + 0x830) + 0x14))[i] = 0;
}
void EnemySetfDisappearAll(char *self)
{
    int n = *(int *)(*(int *)(self + 0x15C) + 0x88);
    int i;

    for (i = 0; i < n; i++)
        ((int *)*(int *)(*(int *)(*(int *)(self + 0x15C) + 0x830) + 0x14))[i] = 1;
}
extern void MatrixDrive_GetTurnZAngleXY(void *a0, void *a1, float f12, float f13, float f14);
extern void RotQuaternionX(void *a0, int a1);
extern void RotQuaternionY(void *a0, int a1);
extern void SetIdentityQuaternion(void *a0);
extern void SetParticleEffect(int a0, void *a1, void *a2);

/* static helper the listing places at enemy.c lines 382-392, expanded into
 * enemySetParticleDie, EnemySetfDisappear and EnemyDeleteParticle; never emitted
 * out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline void enemySetParticle(int kind, void *obj, float *dir)
{
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, dir[0], dir[1], -dir[2]);
    SetIdentityQuaternion(buf);
    RotQuaternionX(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    RotQuaternionY(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    SetParticleEffect(kind, obj, buf);
}

void EnemySetfDisappear(char *self, float *dir)
{
    char *sub = *(char **)(self + 0x15C);
    int n = *(int *)(sub + 0x88);
    char *w = *(char **)(sub + 0x830);
    int i;

    for (i = 0; i < n; i++) {
        if ((*(int **)(w + 0x14))[i] == 0) {
            (*(int **)(w + 0x14))[i] = 1;
            enemySetParticle(8, *(char **)(sub + 0xC) + i * 0x40 + 0x30, dir);
            return;
        }
    }
}

void enemySetParticleDie(void *a0, float *a1) {
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, a1[0], a1[1], -a1[2]);
    SetIdentityQuaternion(buf);
    RotQuaternionX(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    RotQuaternionY(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    SetParticleEffect(0xC, a0, buf);
}
void ReviveEnemyParticle(char *a0, int a1) {
    (*(int **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14))[a1] = 0;
}
int isExistEnemyParticle(char *a0, int a1) {
    return (*(int **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14))[a1] == 0;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyGetNSafeParts);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyDeleteParticle);
void SetEnemyHitGeometryAction(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x38) = a1;
}
extern void InitMotionOrient(void *o, int a1, int a2, int a3, int a4, int a5);
extern void SetLodLevel(void *o, int lod);
int InitDemoMotionGeo(char *self)
{
    InitMotionOrient(self, 0x84A, 0x967, -1, -1, 0x3D7);
    SetLodLevel(self, 0);
    *(int *)(self + 0x16C) = 0;
    return 0;
}

void HotInitDemoMotionGeo(char *self)
{
    InitMotionOrient(self, 0x84A, 0x967, -1, -1, 0x3D7);
    SetLodLevel(self, 0);
    *(int *)(self + 0x16C) = 0;
}
int GetEnemyHitNodeFlag(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14);
}
extern int setEnemyObject(void *self, int a1, int *a2);

int RandomizeEnemy(char *self)
{
    char *sub = *(char **)(self + 0x15C);
    int *w = *(int **)(sub + 0x830);
    int kind = *w++;

    *(int *)(*(char **)(sub + 0x870) + 0x30) = 0;
    return setEnemyObject(self, kind, w);
}
void SetEnemyWingRatio(char *a0, float f) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = f;
}
int CanThisEnemyFly(char *a0) {
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].flyType;
}
int GetEnemyBattleType(char *a0) {
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].battleType;
}
float GetEnemyDefLife(char *a0) {
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].life;
}
float GetEnemyDefDodgeRange(char *a0) {
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].dodge;
}
float GetEnemyDefParaIndex(char *a0) {
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].paraIndex;
}
extern int D_0028F4C0[];
extern int ResetEnemyEye(char *self);

void ResetEnemyPositionInfo(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    ResetEnemyEye(*(char **)(w + 0x18));
    ResetEnemyEye(*(char **)(w + 0x20));
    *(int *)(*(char **)(self + 0x15C) + 0x514) =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);
}
extern void GetRootPosition(void *dst, int *src);
extern void GetRootQuaternion(void *dst, int *src);

void SetEnemyStonizedVisual(int *self)
{
    int local[8];
    GetRootPosition(local, self);
    GetRootQuaternion(&local[4], self);
    SetParticleEffect(0x31, local, &local[4]);
    ((GObj *)self)->f_16C = 0;
}
