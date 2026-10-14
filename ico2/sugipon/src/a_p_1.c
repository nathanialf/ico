#include "a_p_1.h"
#include "DObj.h"
#include "debug.h"
#include "debug_exception.h"
#include "sceneManager.h"
#include "memory.h"
#include "obj_manager.h"
#include "fieldCollision.h"
#include "DisplayP2O.h"
#include "enemyParts.h"
#include "geometryManager.h"
#include "pool.h"
#include <stdlib.h>
#include "typedef.h"
#include "sugiCommon.h"
#include "matrixDrive.h"
#include "main.h"
#include "ios.h"
#include "Matrix.h"
#include "motionManager2.h"
#include "frameDependSequence.h"
#include "attackhit.h"
#include "spider.h"
#include <assert.h>
#include "include_asm.h"

/* int (float) here, short (float) in tableSin.h: PAL's ROM needs int, as
   declared short PAL's object differs in calcSubMission at 0x001C37D8
   (quaternion.c's slerp declares it short and matches) */
extern int GetTableArcCos(float x);
/* as in tableSin.h, which this file does not include */
extern short GetTableArcTan2(float y, float x);

typedef struct { /* field names derived */
    float m[4];
} __attribute__((aligned(16))) Vec4A_P_1; /* derived name */

/* One of the four limbs: its motion state (0 at rest, 1 stepping, 2
 * swinging), the frame of that motion, the foot's current point, the point it
 * rests at in the body frame, and the knee and the tip the arm solver
 * places. */
typedef struct {    /* field names derived */
    int state;      /* 0x00 */
    int count;      /* 0x04 */
    int pad8[2];    /* 0x08 */
    Vec4A_P_1 pos;  /* 0x10 */
    Vec4A_P_1 home; /* 0x20 */
    Vec4A_P_1 knee; /* 0x30 */
    Vec4A_P_1 tip;  /* 0x40 */
} AP1Part;          /* derived name */

/* The clip table the two collision segments are read from: each entry is a
 * pair of endpoints the root matrix is applied to. */
typedef struct { /* field names derived */
    Vec4A_P_1 a; /* 0x00 */
    Vec4A_P_1 b; /* 0x10 */
} AP1ColSeg;     /* derived name */

/* The 0x280-byte work record InitAP1 allocates into the object's work word:
 * the layout row, whether the body is its own skeleton (1) or two arm objects
 * (0), the mode, the four limbs, the two collision hits, the nine focus nodes,
 * the two arm objects, the eye, the up vector, three motion parameters, the
 * body's smoothed attitude and position, its matrix and the root matrix, and
 * three counters. */
typedef struct {     /* field names derived */
    int layout;      /* 0x000, the row of spiderDef */
    int skel;        /* 0x004 */
    int mode;        /* 0x008 */
    int padC;        /* 0x00C */
    AP1Part part[4]; /* 0x010 */
    WallCfg hit[2];  /* 0x150 */
    int word168;     /* 0x168 */
    int word16C;     /* 0x16C */
    int focus[9];    /* 0x170, the skeleton nodes of ap1FocusNode: the
                           body's, then each limb's pair; calcSubMission
                           reaches a pair from &focus[1] and &focus[2] */
    Sub15C *arm[2];  /* 0x194, the two arm objects when skel is 0 */
    EnemyEye *eye;   /* 0x19C */
    int pad1A0[4];   /* 0x1A0 */
    Vec4A_P_1 up;    /* 0x1B0 */
    float tilt;      /* 0x1C0, the forward tilt the speed gives */
    float roll;      /* 0x1C4, the roll the sideways motion gives */
    float sink;      /* 0x1C8, 0 to 1, how far the body sinks and tips forward */
    int pad1CC;      /* 0x1CC */
    Vec4A_P_1 quat;  /* 0x1D0 */
    Vec4A_P_1 pos;   /* 0x1E0 */
    float mtx[16];   /* 0x1F0 */
    float root[16];  /* 0x230 */
    int blink;       /* 0x270 */
    int settleCount; /* 0x274, the first 10 frames reset the position info */
    int visible;     /* 0x278 */
    int pad27C;      /* 0x27C */
} AP1Work;           /* derived name */

static int standMot(GObj *self);
static int walkMot(GObj *self);
static int rollingMot(GObj *self);
static void attackMotInit(GObj *self);
static int attackMot(GObj *self);

/* the mode names */
static char *ap1ModeName[9] = {"ST", "WA", "RO", "AT", "DE",
                               "D1", "D2", "TH", "SL"}; /* derived name */

/* the part record every part slot starts from: three unit w components */
static AP1Part ap1PartInit = {0,
                              0,
                              {0, 0}, /* derived name */
                              {{0.0f, 0.0f, 0.0f, 1.0f}},
                              {{0.0f, 0.0f, 0.0f, 1.0f}},
                              {{0.0f, 0.0f, 0.0f, 1.0f}},
                              {{0.0f, 0.0f, 0.0f, 0.0f}}}; /* derived name */

/* the skeleton nodes InitAP1 looks the nine focus points up by */
static int ap1FocusNode[9] = {44, 3, 4, 19, 20, 45, 46, 49, 50}; /* derived name */

static Vec4A_P_1 ap1DownVector = {{0.0f, -1.0f, 0.0f, 0.0f}}; /* derived name */

static Vec4A_P_1 ap1AttackAxis = {{-1.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

/* the two segment pairs fitToCol clips the body against */
static AP1ColSeg ap1ColSegA[2] = {
    {{{0.0f, -40.0f, 0.0f, 1.0f}}, {{0.0f, 0.0f, 40.0f, 1.0f}}}, /* derived name */
    {{{0.0f, 0.0f, 40.0f, 1.0f}}, {{0.0f, 40.0f, 0.0f, 1.0f}}}}; /* derived name */

static AP1ColSeg ap1ColSegB[2] = {
    {{{0.0f, -40.0f, 0.0f, 1.0f}}, {{0.0f, 0.0f, -40.0f, 1.0f}}}, /* derived name */
    {{{0.0f, 0.0f, -40.0f, 1.0f}}, {{0.0f, 40.0f, 0.0f, 1.0f}}}}; /* derived name */

/* the part offsets in the body frame */
static Vec4A_P_1 ap1PartOffset[6] = {{{20.0f, 0.0f, 80.0f, 1.0f}}, /* derived name */
                                     {{-20.0f, 0.0f, 80.0f, 1.0f}},  {{50.0f, 0.0f, -20.0f, 1.0f}},
                                     {{-50.0f, 0.0f, -20.0f, 1.0f}}, {{-50.0f, 0.0f, 0.0f, 1.0f}},
                                     {{-50.0f, 0.0f, 0.0f, 1.0f}}}; /* derived name */

static float ap1LayoutUp[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

/* the clip records fitToCol and rolling fill */
static ClipWork ap1PartClip = {{{0.0f}}}; /* derived name */

static ClipWork ap1RollClip = {{{0.0f}}, {{0.0f}}, 20.0f}; /* derived name */

static float ap1ArmScale[16] = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, /* derived name */
                                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

static float ap1ArmOffset[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, /* derived name */
                                 0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f};

static float ap1BodyPos[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float ap1BodyMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, /* derived name */
                                  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

/* per motion kind: the entry and the per-frame function */
int (*motFuncList[8][2])(GObj *) = {
    {0, standMot},
    {0, walkMot},
    {0, rollingMot},
    {(int (*)(GObj *))attackMotInit, attackMot},
};

/* the eye offset UpdateEnemyEye is handed, then an alternative nothing reads */
static float ap1EyeMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  /* derived name */
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -20.0f, 30.0f, 1.0f}; /* derived name */

static float ap1EyeMatrixAlt[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  /* derived name */
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -10.0f, 35.0f, 1.0f}; /* derived name */

static float ap1HeadScale[16] = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, /* derived name */
                                 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

static inline void applyPartOrients(GObj *g) /* derived name */
{
    char *tbl = (char *)ap1PartOffset;
    Mtx44 m;
    AP1Work *q = GOBJ_SUB(g)->work;
    int i;

    GetRootMatrix(m.m, g);
    for (i = 0; i < 4; i++) {
        _ApplyMatrix(&q->part[i].pos, &m, (tbl + i * 0x10));
        _ApplyMatrix(&q->part[i].home, &m, (tbl + i * 0x10));
    }
}

/* the name every iosMallocDebug and assert in this file reports itself under */
static const char a_p_1File[] = "src/a_p_1.c"; /* derived name */

/* the banner the failed-node assert prints above its message */
static const char warningBanner[] = "--- WARNING!! ----\n"; /* derived name */

typedef union { /* field names derived */
    int i;
    long long ll;
} AP1Flag; /* derived name */

INCLUDE_ASM(InitAP1);

/* quaternion.h is not included here: this file's SetQuaternionByAxisRotateV
 * and RotQuaternionY calls pass the angle as an int (quaternion.h: short) */
extern void GetMatrixFromQuaternion(void *mtx, void *q);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void SetQuaternionByAxisRotateV(void *dst, int ang, void *axis);

static void yAxisRotFitting(GObj *self, void *nrm)
{
    Vec4A_P_1 down;
    Vec4A_P_1 axis;
    Mtx44 m;
    Vec4A_P_1 rot;
    Vec4A_P_1 q;
    int r;
    float f;

    GetRootQuaternion(&q, self);
    GetMatrixFromQuaternion(&m, &q);
    _ApplyMatrix(&down, &m, &ap1DownVector);
    f = _InnerProduct(&down, nrm);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct(&axis, nrm, &down);
        _NormalizeVector(&axis, &axis);
        SetQuaternionByAxisRotateV(&rot, r, &axis);
        MultiQuaternion(&q, &rot, &q);
        SetRootQuaternion(self, &q);
    }
}

static void zAxisRotFitting(GObj *self, void *nrm)
{
    Vec4A_P_1 front;
    Vec4A_P_1 axis;
    Mtx44 m;
    Vec4A_P_1 rot;
    Vec4A_P_1 q;
    int r;
    float f;

    GetRootQuaternion(&q, self);
    GetMatrixFromQuaternion(&m, &q);
    _ApplyMatrix(&front, &m, ZUnitVector);
    f = _InnerProduct(&front, nrm);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct(&axis, nrm, &front);
        _NormalizeVector(&axis, &axis);
        SetQuaternionByAxisRotateV(&rot, r, &axis);
        MultiQuaternion(&q, &rot, &q);
        SetRootQuaternion(self, &q);
    }
}

static inline int clipAndTakeHit(WallCfg *dst, ClipWork *col) /* derived name */
{
    ClipCollision(col);
    if (col->wall.elem != 0) {
        dst->elem = col->wall.elem;
        dst->o = col->wall.o;
        return 1;
    }
    if (col->floor.elem != 0) {
        dst->elem = col->floor.elem;
        dst->o = col->floor.o;
        return 1;
    }
    return 0;
}

/* void (void *, void *) here, void (float *, float *) in quaternion.h */
extern void GetInverseQuaternion(void *dst, void *src);

static inline void fitYawToVector(GObj *self, Vec4A_P_1 *dir) /* derived name */
{
    Vec4A_P_1 q;
    Vec4A_P_1 qi;
    Vec4A_P_1 rot;
    Mtx44 mm;
    Vec4A_P_1 v;

    GetRootQuaternion(&q, self);
    GetInverseQuaternion(&qi, &q);
    GetMatrixFromQuaternion(&mm, &qi);
    _ApplyMatrix(&v, &mm, dir);
    v.m[2] = 0.0f;
    _NormalizeVector(&v, &v);
    SetQuaternionByAxisRotateV(&rot, (short)-GetTableArcTan2(v.m[0], -v.m[1]), ZUnitVector);
    MultiQuaternion(&q, &q, &rot);
    SetRootQuaternion(self, &q);
}

static inline int clipPartPair(WallCfg *dst, Mtx44 *m, AP1ColSeg *tbl, Vec4A_P_1 *pos,
                               Vec4A_P_1 *nrm) /* derived name */
{
    int i;

    for (i = 0; i < 2; i++) {
        _ApplyMatrix(ap1PartClip.pt[0], m, &tbl[i].a);
        _ApplyMatrix(ap1PartClip.pt[1], m, &tbl[i].b);
        if (clipAndTakeHit(dst, &ap1PartClip)) {
            CopyVector(pos, ap1PartClip.pt[2]);
            CopyVector(nrm, &ap1PartClip.normal);
            return 1;
        }
    }
    dst->elem = 0;
    return 0;
}

/* a limb's hit: setPartHit marks it, resetPartHit first puts the limb back
   at its rest point */
static inline void setPartHit(AP1Part *part) /* derived name */
{
    part->state = 1;
    part->count = 0;
}

static inline void resetPartHit(AP1Part *part, float *orient) /* derived name */
{
    CopyVector(&part->home, orient);
    setPartHit(part);
}

INCLUDE_ASM(fitToCol);

typedef union { /* field names derived */
    int i;
    float f;
} AP1Val; /* derived name */

INCLUDE_ASM(walkMot);

INCLUDE_ASM(rolling);

/* the point the spider's bite attack is centred on, 50 units down its own arm */
static const Vec4A_P_1 attackCenterOffset = {50.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

/* the law of cosines for the two arm segments, one named local per
 * line */
static inline short armCosine(float a, float b, float c) /* derived name */
{
    float aa = a * a;
    float bb = b * b;
    float cc = c * c;

    return (short)(int)GetTableArcCos((aa + bb - cc) / (2.0f * a * b));
}

INCLUDE_ASM(calcSubMission);

/* as in quaternion.h, which this file does not include */
extern void RotQuaternionX(void *q, short ang);
/* as in quaternion.h, which this file does not include */
extern void RotQuaternionZ(void *q, short ang);
/* void (void *, void *, void *) here, void (float *, float *, float *) in quaternion.h */
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
/* as in quaternion.h, which this file does not include */
extern void GetSlerpQuaternion(void *dst, void *a, void *b, float t);

INCLUDE_ASM(updateMatrix);

INCLUDE_ASM(resetPositionInfo);

static inline void stepAP1BlinkTimer(GObj *g) /* derived name */
{
    AP1Work *q = GOBJ_SUB(g)->work;
    int t = q->blink + 1;

    q->blink = t;
    if (t > 32) {
        q->blink = 0;
    }
}

INCLUDE_ASM(AP1Geo);

INCLUDE_ASM(AP1DL);

INCLUDE_ASM(GetAP1SpecType);

INCLUDE_ASM(SetAP1VisualState);

/* the angle passes as an int here (quaternion.h: short) */
extern void RotQuaternionY(void *q, int ang);
/* quaternion.h is not included in this file (see RotQuaternionY above) */
extern void RegularizeQuaternion(void *q);

INCLUDE_ASM(AP1Turn);

INCLUDE_ASM(AP1MotReqForce);

INCLUDE_ASM(AP1MotReq);

INCLUDE_ASM(AP1JumpReq);

INCLUDE_ASM(MakeAP1GObj);

INCLUDE_ASM(GetAP1Mode);

INCLUDE_ASM(standMot);

INCLUDE_ASM(rollingMot);

typedef struct { /* field names derived */
    int state;   /* 0x00 */
    float frame; /* 0x04 */
    char pad08[24];
    Vec4A_P_1 vec; /* 0x20 */
} AP1MotCtrl;      /* derived name */

/* two helpers, each expanded twice into attackMotInit and attackMot */
static inline void setAP1MotCtrlState(AP1MotCtrl *m, int state) /* derived name */
{
    m->state = state;
    m->frame = 0.0f;
}

static inline void setAP1MotCtrlVector(AP1MotCtrl *m, Vec4A_P_1 *v) /* derived name */
{
    CopyVector(&m->vec, v);
    setAP1MotCtrlState(m, 0);
}

INCLUDE_ASM(attackMotInit);

INCLUDE_ASM(attackMot);
