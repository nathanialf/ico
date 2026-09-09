#include "common.h"

typedef struct {
    int a;
    int b;
    float life;
    int c;
    float d;
    float dodge;
    int paraIndex : 8;
    unsigned int flyType : 2;
    unsigned int battleType : 2;
} EnemyDef;

extern EnemyDef D_00624880[];

#include "ico/types.h"

extern int iosMallocDebug(int part, int size, char *file, int line);
extern int prim_InitParticle(float f12, float f13, float f14, int num, int a1, char *tag, int a3);
extern int enemy_GetPositionTable(int idx, int sub_idx);
extern void _CopyVector(void *dst, void *src);
extern void debug_StdPrintfDummy();
extern void debug_assertMessage(char *file, int line, char *mes);
extern void __assert(char *file, int line, char *mes);
extern int rand(void);
extern float D_006394BC;
extern int D_0063A438;
extern char D_0061F650[];
extern char D_0061F660[];
extern char D_0061F670[];
extern char D_0061F6A0[];
extern char D_0063B888[];

typedef struct {
    float x;
    float y;
    float z;
    float w;
} EnemyPosEntry;

/* static helper the listing places at enemy.c lines 99-100, expanded only into
 * setEnemyParticleObject; never emitted out of line, so it has no MAIN.MAP
 * symbol and this name is ours. */
static inline void clearEnemyParticleFlags(int *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
        p[i] = 0;
}

void setEnemyParticleObject(char *self, int pid)
{
    char *sub = *(char **)(self + 0x15C);
    char *w = *(char **)(sub + 0x830);
    int n = *(int *)(sub + 0x88);
    char *tbl = *(char **)(sub + 0x8C);
    char *p = *(char **)(sub + 0x870);
    int *parts;
    int *fl;
    float size;
    int i;
    int cnt;
    int num;
    int n4;
    int type;
    EnemyPosEntry *v;
    EnemyPosEntry *q;

    size = (*(float *)(p + 0x20) + *(float *)(p + 0x24) + *(float *)(p + 0x28)) * 32.0f *
           D_006394BC * 0.5f * 10.0f;
    parts = (int *)iosMallocDebug(D_0063A438, n * 4, D_0061F650, 130);
    *(int **)(w + 0x10) = parts;
    fl = (int *)iosMallocDebug(D_0063A438, n * 4, D_0061F650, 132);
    *(int **)(w + 0x30) = fl;
    clearEnemyParticleFlags(fl, n);
    for (i = 0; i < n; i++) {
        q = (EnemyPosEntry *)enemy_GetPositionTable(pid, i);
        v = q;
        if (q == 0) {
            (*(int **)(w + 0x30))[i] = 0;
            continue;
        }
        (*(int **)(w + 0x30))[i] = 1;
        for (cnt = 0; q->w > -1.0f; cnt++)
            q++;
        q = v;
        parts[i] = 0;
        if (cnt <= 0)
            continue;
        if (cnt >= 80)
            num = 80;
        else
            num = cnt;
        parts[i] = prim_InitParticle(size, 0.5f, 0.5f, num, 1, D_0061F660, 0);
        if (parts[i] == 0) {
            debug_StdPrintfDummy(D_0061F670);
            debug_assertMessage(D_0061F650, 177, D_0061F6A0);
            __assert(D_0061F650, 177, D_0063B888);
        }
        for (cnt = 0; q->w > -1.0f && cnt < 80; cnt++, q++) {
            n4 = rand() % 4;
            _CopyVector(*(char **)(parts[i] + 0x190) + cnt * 32, q);
            _CopyVector(*(char **)(parts[i] + 0x194) + cnt * 32, q);
            type = *(int *)(tbl + i * 0x40 + 4);
            if (type >= 38)
                goto spread;
            if (type < 36)
                goto spread;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x10) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x10) = 0.5f;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x14) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x14) = 0.0f;
            goto done;
        spread:
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x10) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x10) = (n4 / 2) * 0.5f;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x14) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x14) = (n4 % 2) * 0.5f;
        done:
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x18) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x18) = 128.0f;
            *(float *)(*(char **)(parts[i] + 0x190) + cnt * 32 + 0x1C) =
                *(float *)(*(char **)(parts[i] + 0x194) + cnt * 32 + 0x1C) = 64.0f;
        }
    }
}

typedef struct {
    int first;
    int last;
} EnemyKindRange;

extern EnemyKindRange D_00624F68[];
extern int D_00625018[];
extern char D_0061F6C8[];
extern char D_0061F6F0[];
extern char D_0063B890[];
extern int GetPObjAddress(int obj);

/* static helper the listing places at enemy.c lines 223-233, expanded only into
 * setEnemyObject; never emitted out of line, so it has no MAIN.MAP symbol and
 * this name is ours. */
static inline int enemyRandomizeID(int kind, int *ctr)
{
    int lo = D_00624F68[kind - 0x10000].first;
    int n = D_00624F68[kind - 0x10000].last - lo;
    int id = lo + *ctr;

    debug_StdPrintfDummy(D_0061F6C8, *ctr, id);
    *ctr = *ctr + 1;
    if (*ctr >= n) {
        *ctr = 0;
    }
    return D_00625018[id];
}

int setEnemyObject(char *self, int kind, int *ctr)
{
    char *p;
    char *sub;
    char *w;
    float sc;
    int obj;
    int pid;

retry:
    sub = *(char **)(self + 0x15C);
    w = *(char **)(sub + 0x830);
    if (kind > 0xFFFF) {
        kind = enemyRandomizeID(kind, ctr);
        goto retry;
    }
    p = *(char **)(sub + 0x870);
    sc = D_00624880[kind].d;
    *(float *)(p + 0x28) = sc;
    *(float *)(p + 0x24) = sc;
    *(float *)(p + 0x20) = sc;
    *(float *)(w + 0x48) = sc;
    obj = D_00624880[kind].a;
    if (obj != 0x610) {
        *(int *)(*(int *)(self + 0x15C) + 0x854) = GetPObjAddress(obj);
        *(int *)(*(int *)(self + 0x15C) + 0x84) = obj;
        debug_StdPrintfDummy(D_0063B890, *(int *)(*(int *)(self + 0x15C) + 0x854));
        *(int *)(w + 0x38) = 1;
    }
    pid = D_00624880[kind].b;
    if (pid != -1) {
        setEnemyParticleObject(self, pid);
    }
    debug_StdPrintfDummy(D_0061F6F0, kind);
    return kind;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", dispEnemyObject);
INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyCheckHit);
INCLUDE_ASM("asm/nonmatchings/src/enemy", CheckEnemyHit);
INCLUDE_ASM("asm/nonmatchings/src/enemy", InitEnemyGeo);

extern int GetEnemyTypeFromGObj(char *self);
extern void ExecMotionOrient();
extern void CylinderCollisionWithControlDynamics(char *self, int a1, int a2, float f12, float f13,
                                                 float f14);
extern int isEnemyActive(int *self);
extern void GetProjectionOfPlane(float *dst, float *plane, float *pos);
extern void EntryEnemyFootPrint(int *fp, float *v);
extern void ExecEnemyFootPrints(int *fp);
extern void *MatrixDrive_GetMatrix(void);
extern int GetSkeltonFocusNode(char *self, int kind);
extern void _MulMatrix(void *d, void *a, void *b);
extern void UpdateEnemyEye(char *eye, void *m, float ratio);
extern char D_004E78A0[];

void EnemyGeo(char *self)
{
    int sub = *(int *)(self + 0x15C);
    char *node = *(char **)(self + 0x164);
    unsigned long long flag = *(unsigned long long *)(node + 0x18);
    char *w = *(char **)(sub + 0x830);
    float ratio;
    float buf[4];

    if ((int)(flag >> 33) & 1) {
        *(int *)(w + 0x4C) = 0;
    } else {
        if (*(int *)(w + 0x4C) >= 0xB)
            return;
        *(int *)(w + 0x4C) = *(int *)(w + 0x4C) + 1;
    }

    *(int *)(*(int *)(self + 0x15C) + 0x550) = 0;
    *(int *)(*(int *)(self + 0x15C) + 0x54C) = 2;
    *(int *)(*(int *)(self + 0x15C) + 0x548) = 0;
    if (GetEnemyTypeFromGObj(self) == 3)
        *(int *)(*(int *)(self + 0x15C) + 0x550) = 1;

    ExecMotionOrient(self);

    CylinderCollisionWithControlDynamics(self, 4, 0, *(float *)(w + 0x48) * 70.0f,
                                         *(float *)(w + 0x48) * 50.0f, 0.5f);

    if (isEnemyActive((int *)self) != 0) {
        char *s = *(char **)(self + 0x15C);
        if (*(int *)(s + 0x63C) != 0) {
            if (*(int *)(w + 0x2C) != 0) {
                if (!(*(int *)(s + 0x4A0) == 0x3A1 || *(int *)(s + 0x4A0) == 0x3A2)) {
                    GetProjectionOfPlane(
                        buf, (float *)(s + 0x1D0),
                        (float *)(*(char **)(s + 0xC) + *(int *)(s + 0x220) * 0x40 + 0x30));
                    EntryEnemyFootPrint(*(int **)(w + 0x28), buf);
                }
            }
        }
    }
    ExecEnemyFootPrints(*(int **)(w + 0x28));

    *(int *)(*(int *)(self + 0x15C) + 0x558) = (*(int *)(*(int *)(self + 0x15C) + 0x558) + 1) % 10;

    ratio = (*(float *)(*(char **)(*(int *)(self + 0x15C) + 0x870) + 0x20) +
             *(float *)(*(char **)(*(int *)(self + 0x15C) + 0x870) + 0x24) +
             *(float *)(*(char **)(*(int *)(self + 0x15C) + 0x870) + 0x28)) /
            3.0f;

    _MulMatrix(MatrixDrive_GetMatrix(),
               *(char **)(*(int *)(self + 0x15C) + 0xC) + GetSkeltonFocusNode(self, 0x24) * 0x40,
               D_004E78A0);
    UpdateEnemyEye(*(char **)(w + 0x18), MatrixDrive_GetMatrix(), ratio);
    _MulMatrix(MatrixDrive_GetMatrix(),
               *(char **)(*(int *)(self + 0x15C) + 0xC) + GetSkeltonFocusNode(self, 0x25) * 0x40,
               D_004E78A0);
    UpdateEnemyEye(*(char **)(w + 0x20), MatrixDrive_GetMatrix(), ratio);
}

extern void reg_DispEnemy(void *sub);
extern int DispEnemyEye(char *node);
extern int DispEnemyFootPrints(int *fp);
extern void dispEnemyObject(void *self);

void DisplayEnemy(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    if (*(int *)(w + 0x38) != 0) {
        reg_DispEnemy(*(char **)(self + 0x15C));
        if (*(float *)(*(char **)(*(char **)(self + 0x15C) + 0x870) + 0x30) == 0.0f) {
            DispEnemyEye(*(char **)(w + 0x18));
            DispEnemyEye(*(char **)(w + 0x20));
        }
    }
    DispEnemyFootPrints(*(int **)(w + 0x28));
    if (*(int *)(w + 0x10) != 0) {
        dispEnemyObject(self);
    }
}

extern int IsActCharDead();
extern int isEnemyHyde(int *a0);

void EnemyDL(int *self)
{
    char *sub = *(char **)((char *)self + 0x164);
    unsigned long long flag = *(unsigned long long *)(sub + 0x18);
    if (((flag >> 33) & 1) == 0)
        return;
    IsActCharDead();
    if (isEnemyHyde(self) != 0)
        return;
    DisplayEnemy((char *)self);
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

void SetEnemyFlyXZAccel(char *a0, float f)
{
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

float GetEnemyFlyXZAccel(char *a0)
{
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x50);
}

void EnemyAI(void) {}

void SetEnemyFootPrintSwitch(char *a0, int a1)
{
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

void enemySetParticleDie(void *a0, float *a1)
{
    char buf[0x20];
    MatrixDrive_GetTurnZAngleXY(buf + 0x10, buf + 0x12, a1[0], a1[1], -a1[2]);
    SetIdentityQuaternion(buf);
    RotQuaternionX(buf, (short)(-*(unsigned short *)(buf + 0x10)));
    RotQuaternionY(buf, (short)(-*(unsigned short *)(buf + 0x12)));
    SetParticleEffect(0xC, a0, buf);
}

void ReviveEnemyParticle(char *a0, int a1)
{
    (*(int **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14))[a1] = 0;
}

int isExistEnemyParticle(char *a0, int a1)
{
    return (*(int **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14))[a1] == 0;
}

int EnemyGetNSafeParts(char *self)
{
    int n = *(int *)(*(char **)(self + 0x15C) + 0x88);
    int *p;
    int i;
    int cnt = 0;

    for (i = 0; i < n; i++) {
        p = *(int **)(*(char **)(*(char **)(self + 0x15C) + 0x830) + 0x14);
        if (p[i] == 0)
            cnt++;
    }
    return cnt;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", EnemyDeleteParticle);

void SetEnemyHitGeometryAction(char *a0, int a1)
{
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

int GetEnemyHitNodeFlag(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14);
}

int RandomizeEnemy(char *self)
{
    char *sub = *(char **)(self + 0x15C);
    int *w = *(int **)(sub + 0x830);
    int kind = *w++;

    *(int *)(*(char **)(sub + 0x870) + 0x30) = 0;
    return setEnemyObject(self, kind, w);
}

void SetEnemyWingRatio(char *a0, float f)
{
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = f;
}

int CanThisEnemyFly(char *a0)
{
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].flyType;
}

int GetEnemyBattleType(char *a0)
{
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].battleType;
}

float GetEnemyDefLife(char *a0)
{
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].life;
}

float GetEnemyDefDodgeRange(char *a0)
{
    return D_00624880[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)].dodge;
}

float GetEnemyDefParaIndex(char *a0)
{
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
