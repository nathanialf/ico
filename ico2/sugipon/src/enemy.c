#include "typedef.h"
#include "enemy.h"
#include "act_a_p_1.h"
#include "sugiCommon.h"
#include "charFileManager.h"
#include "debug.h"
#include "debug_exception.h"
#include "memory.h"
#include "gobj.h"
#include "GifPacket.h"
#include "enemy_act.h"
#include "EnemyInit.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "enemyParts.h"
#include "geometryManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "particleEffect.h"
#include "quaternion.h"
#include <libvu0.h>
#include <stdlib.h>
#include "ios.h"
#include "main.h"
#include <assert.h>
#include "sceneManager.h"
#include "Primitive.h"
#include "include_asm.h"

typedef struct { /* field names derived */
    float x;
    float y;
    float z;
    float w;
} EnemyPosEntry; /* derived name */

static inline void clearEnemyParticleFlags(int *p, int n) /* derived name */
{
    int i;
    for (i = 0; i < n; i++)
        p[i] = 0;
}

/* a unit matrix with the translation (10, 0, 0); nothing in the file reads
   it */
static float offsetMatrix[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {10.0f, 0.0f, 0.0f, 1.0f},
}; /* derived name */

/* The 84-byte work record InitEnemyGeo allocates into the object's work
   word: the variation kind and the counter setEnemyObject randomises it with,
   the enemy-table row, the particle and broken-part tables, the two eyes, the
   footprints, the per-node particle flags, the object-loaded flag, the wing
   and stone parameters and the scale. */
typedef struct {              /* field names derived */
    int kind;                 /* 0x00 */
    int ctr;                  /* 0x04, setEnemyObject's randomiser state */
    int def;                  /* 0x08, the enemyKind row */
    int padC;                 /* 0x0C */
    PrimParticle **particle;  /* 0x10 */
    int *broken;              /* 0x14 */
    EnemyEye *eye0;           /* 0x18 */
    int word1C;               /* 0x1C */
    EnemyEye *eye1;           /* 0x20 */
    int word24;               /* 0x24 */
    EnemyFootPrintHead *foot; /* 0x28 */
    int footSwitch; /* 0x2C, nonzero while the enemy leaves footprints (SetEnemyFootPrintSwitch) */
    int *flag;      /* 0x30 */
    int pad34;      /* 0x34 */
    int loaded;     /* 0x38 */
    float float3C;  /* 0x3C */
    short short40;  /* 0x40 */
    float wing;     /* 0x44 */
    float scale;    /* 0x48 */
    int timer;      /* 0x4C */
    float flyXZAccel; /* 0x50, the fly XZ acceleration, from the enemyKind row */
} EnemyWork;          /* derived name */

/* The 0x15C slot is the engine's sub-object HANDLE: the code stores an int and
 * reads it back as a pointer, so every read of it is a union view, the same
 * spelling ico2/sugipon/src/geometryManager.c uses for the same slot. */

#define SUBOF(o) (((SubHandle *)&((GObj *)(o))->dobj)->sub) /* derived name */

static int setEnemyObject(GObj *self, int kind, int *ctr);

/* InitEnemyGeo's parts list; its body inlines clearEnemyParticleFlags */
static inline int enemyInitPartsList(GObj *self, SObjSimpleSetting *param) /* derived name */
{
    int kind = param->obj;
    EnemyWork *w;
    int n;
    int *parts;

    n = SUBOF(self)->skelNodeNum;
    /* the work-record entry is read as an int and cast */
    w = (EnemyWork *)*(int *)&SUBOF(self)->work;

    parts = (int *)iosMallocDebug(ios_partition_sugipon, n * 4, "src/enemy.c", 285);
    w->broken = parts;
    clearEnemyParticleFlags(parts, n);
    w->kind = kind;
    w->ctr = 0;
    return setEnemyObject(self, kind, &w->ctr);
}

INCLUDE_ASM(setEnemyParticleObject);

static inline int enemyRandomizeID(int kind, int *ctr) /* derived name */
{
    int lo = randomEnemyKind[kind - 0x10000].first;
    int n = randomEnemyKind[kind - 0x10000].last - lo;
    int id = lo + *ctr;

    debug_StdPrintfDummy("\x1b[36mRANDOMIZE COUNT: %d > RID: %d\x1b[m\n", *ctr, id);
    *ctr = *ctr + 1;
    if (*ctr >= n) {
        *ctr = 0;
    }
    return randomEnemyVariationKind[id];
}

INCLUDE_ASM(setEnemyObject);

/* One part's projected position: the sqc2 stores the integer x, y, z and w,
   and the part's index then takes the x word's place. */
typedef struct { /* field names derived */
    int idx;
    int y;
    int z;
    int w;
} EnemyDispEntry; /* derived name */

/* dispEnemyObject keeps the developer's own line layout: the lines without
 * code hold declarations, braces and comments.  The first loop's condition
 * reads the sub-object handle through a volatile int view; the body's own
 * read of the handle is GOBJ_SUB's int view. */
INCLUDE_ASM(dispEnemyObject);

/* expanded into EnemyCheckHit, enemySetParticleDie, EnemySetfDisappear and
 * EnemyDeleteParticle; it returns SetParticleEffect's result */
static inline int enemySetParticle(int kind, void *obj, float *dir) /* derived name */
{
    float q[4];
    unsigned short ax, ay;
    MatrixDrive_GetTurnZAngleXY(&ax, &ay, dir[0], dir[1], -dir[2]);
    SetIdentityQuaternion(q);
    RotQuaternionX(q, (short)-ax);
    RotQuaternionY(q, (short)-ay);
    return SetParticleEffect(kind, obj, q);
}

INCLUDE_ASM(EnemyCheckHit);

/* CheckEnemyHit keeps the developer's own line layout: the lines without
 * code hold declarations, braces and comments.  The counter starts at 0 in a
 * statement of its own ahead of a test on n alone, and the for has no
 * initialiser; the particle calls sit under a test of a local constant. */
INCLUDE_ASM(CheckEnemyHit);

/* the variation number the next enemy takes, stepped by two modulo ten */
static int enemyVariation = 0; /* derived name */

INCLUDE_ASM(InitEnemyGeo);

INCLUDE_ASM(EnemyGeo);

void DisplayEnemy(GObj *self);

INCLUDE_ASM(DisplayEnemy);

void EnemyDL(GObj *self)
{
    Act *sub = GOBJ_ACT(self);
    unsigned long long flag = sub->flags18.ll;
    if (((flag >> 33) & 1) == 0)
        return;
    IsActCharDead(self);
    if (isEnemyHyde(self) != 0)
        return;
    DisplayEnemy(self);
}

void DemoMotionGeo(GObj *self)
{
    GOBJ_SUB(self)->root.hand1.mode = 0;
    GOBJ_SUB(self)->root.hand0.mode = 0;
    GOBJ_SUB(self)->root.lookIK = 0;
    GOBJ_SUB(self)->root.handTurnIK = 0;
    ExecMotionOrient(self);
}

INCLUDE_ASM(SetEnemyDissolve);

void EnemyAI(void) {}

INCLUDE_ASM(SetEnemyFootPrintSwitch);

INCLUDE_ASM(EnemySetfAppearAll);

INCLUDE_ASM(EnemySetfDisappearAll);

INCLUDE_ASM(EnemySetfDisappear);

void enemySetParticleDie(void *root, float *dir)
{
    float q[4];
    unsigned short ax, ay;
    MatrixDrive_GetTurnZAngleXY(&ax, &ay, dir[0], dir[1], -dir[2]);
    SetIdentityQuaternion(q);
    RotQuaternionX(q, (short)-ax);
    RotQuaternionY(q, (short)-ay);
    SetParticleEffect(12, root, q);
}

INCLUDE_ASM(ReviveEnemyParticle);

INCLUDE_ASM(isExistEnemyParticle);

INCLUDE_ASM(EnemyGetNSafeParts);

INCLUDE_ASM(EnemyDeleteParticle);

INCLUDE_ASM(SetEnemyHitGeometryAction);

INCLUDE_ASM(InitDemoMotionGeo);

INCLUDE_ASM(HotInitDemoMotionGeo);

INCLUDE_ASM(GetEnemyHitNodeFlag);

INCLUDE_ASM(RandomizeEnemy);

INCLUDE_ASM(SetEnemyWingRatio);

INCLUDE_ASM(CanThisEnemyFly);

INCLUDE_ASM(GetEnemyBattleType);

INCLUDE_ASM(GetEnemyDefLife);

INCLUDE_ASM(ResetEnemyPositionInfo);

void SetEnemyStonizedVisual(GObj *self)
{
    int local[8];
    GetRootPosition(local, self);
    GetRootQuaternion(&local[4], self);
    SetParticleEffect(0x31, local, &local[4]);
    self->active = 0;
}
