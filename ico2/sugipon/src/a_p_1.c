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

/* kept local: int (float) here, short (float) in tableSin.h: under the short return
   calcSubMission spills its frame addresses in another order */
extern int GetTableArcCos(float x);
/* kept local: agrees with tableSin.h, which this TU does not include (GetTableArcCos differs) */
extern short GetTableArcTan2(float f12, float f13);

typedef struct {
    float m[4];
} __attribute__((aligned(16))) Vec4A_P_1;

/* RECONSTRUCTION, read from the ROM.  One of the four limbs: its motion state
 * (0 at rest, 1 stepping, 2 swinging), the frame of that motion, the foot's
 * current point, the point it rests at in the body frame, and the knee and the
 * tip the arm solver places. */
typedef struct {
    int state;      /* 0x00 */
    int count;      /* 0x04 */
    int pad8[2];    /* 0x08 */
    Vec4A_P_1 pos;  /* 0x10 */
    Vec4A_P_1 home; /* 0x20 */
    Vec4A_P_1 knee; /* 0x30 */
    Vec4A_P_1 tip;  /* 0x40 */
} AP1Part;

typedef struct {
    long long x;
} __attribute__((packed, aligned(4))) AP1PackedLL;

typedef struct {
    AP1PackedLL p; /* 0x00 */
    int attr;      /* 0x08 */
} AP1ColHit;

/* The clip table the two collision segments are read from: each entry is a
 * pair of endpoints the root matrix is applied to. */
typedef struct {
    Vec4A_P_1 a; /* 0x00 */
    Vec4A_P_1 b; /* 0x10 */
} AP1ColSeg;

/* ClipCollision's work record as this file reaches it: the segment to clip,
 * the clipped point, the probe radius, the wall and floor hits and the hit
 * normal (0xC0 bytes, the stride of the two records below). */
typedef struct {
    Vec4A_P_1 from; /* 0x00 */
    Vec4A_P_1 to;   /* 0x10 */
    Vec4A_P_1 pos;  /* 0x20 */
    char pad30[0x40];
    float radius; /* 0x70 */
    char pad74[0xC];
    AP1ColHit wall;  /* 0x80 */
    AP1ColHit floor; /* 0x8C */
    char pad98[0x8];
    Vec4A_P_1 normal; /* 0xA0 */
    char padB0[0x10];
} AP1Clip;

/* RECONSTRUCTION, read from the ROM.  The 0x280-byte work record InitAP1
 * allocates into the object's work word: the layout row, whether the body is
 * its own skeleton (1) or two arm objects (0), the mode, the four limbs, the
 * two collision hits, the nine focus nodes, the two arm objects, the eye, the
 * up vector, three motion parameters, the body's smoothed attitude and
 * position, its matrix and the root matrix, and three counters. */
typedef struct {
    int layout;       /* 0x000, the row of D_0062B588 */
    int skel;         /* 0x004 */
    int mode;         /* 0x008 */
    int padC;         /* 0x00C */
    AP1Part part[4];  /* 0x010 */
    AP1ColHit hit[2]; /* 0x150 */
    int f_168;        /* 0x168 */
    int f_16C;        /* 0x16C */
    int focus[9];     /* 0x170, the skeleton nodes of ap1FocusNode: the
                           body's, then each limb's pair; calcSubMission
                           reaches a pair from &focus[1] and &focus[2] (the
                           bytes pin the 0x174 + i * 8 address, which
                           focus[i * 2 + 1] folds to another giv) */
    char *arm[2];     /* 0x194, the two arm objects when skel is 0 */
    EnemyEye *eye;    /* 0x19C */
    int pad1A0[4];    /* 0x1A0 */
    Vec4A_P_1 up;     /* 0x1B0 */
    float f_1C0;      /* 0x1C0 */
    float f_1C4;      /* 0x1C4 */
    float f_1C8;      /* 0x1C8 */
    int pad1CC;       /* 0x1CC */
    Vec4A_P_1 quat;   /* 0x1D0 */
    Vec4A_P_1 pos;    /* 0x1E0 */
    float mtx[4][4];  /* 0x1F0 */
    float root[4][4]; /* 0x230 */
    int blink;        /* 0x270 */
    int f_274;        /* 0x274 */
    int visible;      /* 0x278 */
    int pad27C;       /* 0x27C */
} AP1Work;

int standMot(char *a0);
int walkMot(char *a0);
int rollingMot(char *a0);
void attackMotInit(char *a0);
int attackMot(char *a0);

/* The TU's .data, one block in the ROM's order (VMA 0x4E5520..0x4E5A30, 0x510 B
 * = MAIN.MAP a_p_1.o .data); MAIN.MAP names only motFuncList, so every other
 * name is ours. The mode names are the TU's .sdata strings. */
static char *ap1ModeName[9] = {"ST", "WA", "RO", "AT", "DE",
                               "D1", "D2", "TH", "SL"}; /* derived name */

/* the part record every part slot starts from: three unit w components */
static AP1Part ap1PartInit = {0,
                              0,
                              {0, 0}, /* derived name */
                              {{0.0f, 0.0f, 0.0f, 1.0f}},
                              {{0.0f, 0.0f, 0.0f, 1.0f}},
                              {{0.0f, 0.0f, 0.0f, 1.0f}},
                              {{0.0f, 0.0f, 0.0f, 0.0f}}};

/* the skeleton nodes InitAP1 looks the nine focus points up by */
static int ap1FocusNode[9] = {44, 3, 4, 19, 20, 45, 46, 49, 50}; /* derived name */

static Vec4A_P_1 ap1DownVector = {{0.0f, -1.0f, 0.0f, 0.0f}}; /* derived name */

static Vec4A_P_1 ap1AttackAxis = {{-1.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

/* the two segment pairs fitToCol clips the body against */
static AP1ColSeg ap1ColSegA[2] = {
    {{{0.0f, -40.0f, 0.0f, 1.0f}}, {{0.0f, 0.0f, 40.0f, 1.0f}}}, /* derived name */
    {{{0.0f, 0.0f, 40.0f, 1.0f}}, {{0.0f, 40.0f, 0.0f, 1.0f}}}};

static AP1ColSeg ap1ColSegB[2] = {
    {{{0.0f, -40.0f, 0.0f, 1.0f}}, {{0.0f, 0.0f, -40.0f, 1.0f}}}, /* derived name */
    {{{0.0f, 0.0f, -40.0f, 1.0f}}, {{0.0f, 40.0f, 0.0f, 1.0f}}}};

/* the part offsets in the body frame */
static Vec4A_P_1 ap1PartOffset[6] = {{{20.0f, 0.0f, 80.0f, 1.0f}}, /* derived name */
                                     {{-20.0f, 0.0f, 80.0f, 1.0f}},  {{50.0f, 0.0f, -20.0f, 1.0f}},
                                     {{-50.0f, 0.0f, -20.0f, 1.0f}}, {{-50.0f, 0.0f, 0.0f, 1.0f}},
                                     {{-50.0f, 0.0f, 0.0f, 1.0f}}};

static float ap1LayoutUp[4] = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

/* the clip records fitToCol and rolling fill */
static AP1Clip ap1PartClip = {{{0.0f}}}; /* derived name */

static AP1Clip ap1RollClip = {{{0.0f}}, {{0.0f}}, {{0.0f}}, {0}, 20.0f}; /* derived name */

static float ap1ArmScale[16] = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, /* derived name */
                                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

static float ap1ArmOffset[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, /* derived name */
                                 0.0f, 0.0f, 1.0f, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f};

static float ap1BodyPos[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float ap1BodyMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, /* derived name */
                                  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

/* per motion kind: the entry and the per-frame function (MAIN.MAP a_p_1.o) */
int (*motFuncList[8][2])(char *) = {
    {0, standMot},
    {0, walkMot},
    {0, rollingMot},
    {(int (*)(char *))attackMotInit, attackMot},
};

/* the eye offset UpdateEnemyEye is handed, then an alternative nothing reads */
static float ap1EyeMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f, /* derived name */
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -20.0f, 30.0f, 1.0f};

static float ap1EyeMatrixAlt[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f,  0.0f, /* derived name */
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -10.0f, 35.0f, 1.0f};

static float ap1HeadScale[16] = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, /* derived name */
                                 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

/* kept local: void (int, int, int) here, void (void *, void *, void *) in Matrix.h */
extern void _ApplyMatrix(int a, int b, int c);

/* static helper the listing places at a_p_1.c lines 156-165, above InitAP1's
 * def line 227, so the name is ours. */
static inline void applyPartOrients(char *g)
{
    char *tbl = (char *)ap1PartOffset;
    Mtx44 m;
    AP1Work *q = GOBJ_SUB(g)->work;
    int i;

    GetRootMatrix(&m, g);
    for (i = 0; i < 4; i++) {
        _ApplyMatrix((int)&q->part[i].pos, (int)&m, (int)(tbl + i * 0x10));
        _ApplyMatrix((int)&q->part[i].home, (int)&m, (int)(tbl + i * 0x10));
    }
}

/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _UnitMatrix(void *m);
/* kept local: int (void *, int) here, int (char *, int) in motionManager2.h */
extern int GetSkeltonFocusNode(void *self, int id);
extern void __assert(char *file, int line, char *expr);

/* the name every iosMallocDebug and assert in this file reports itself under */
static const char a_p_1File[] = "src/a_p_1.c";

/* the banner the failed-node assert prints above its message */
static const char warningBanner[] = "--- WARNING!! ----\n";

typedef struct {
    int unk0;    /* 0x00 */
    int unk4;    /* 0x04 */
    int unk8;    /* 0x08 */
    int unkC;    /* 0x0C */
    int unk10;   /* 0x10 */
    int unk14;   /* 0x14 */
    float unk18; /* 0x18 */
    int unk1C;   /* 0x1C */
} AP1Layout;

extern AP1Layout D_0062B588[];

typedef union {
    int i;
    long long ll;
} AP1Flag;

char *InitAP1(char *self, char *arg)
{
    AP1Work *p;
    char *d;
    int i;

    p = iosMallocDebug(ios_partition_sugipon, sizeof(AP1Work), a_p_1File, 228);
    GOBJ_SUB(self)->work = p;
    p->layout = *(int *)(arg + 0x30);
    p->skel = 1;
    p->f_16C = 0;
    p->mode = 7;
    p->f_168 = 0;
    p->f_1C4 = 0.0f;
    p->f_1C8 = 0.0f;
    p->f_1C0 = 0.0f;
    p->blink = rand() & 0x1F;
    p->f_274 = 0;
    p->visible = 1;
    ap1LayoutUp[2] = D_0062B588[p->layout].unk18;
    CopyVector(&p->up, ap1LayoutUp);
    _UnitMatrix(p->mtx);
    _UnitMatrix(p->root);
    GetRootQuaternion((int)(&p->quat), (int *)self);
    GetRootPosition(&p->pos, self);
    for (i = 0; i < 4; i++) {
        p->part[i] = ap1PartInit;
    }
    for (i = 0; i < 2; i++) {
        p->hit[i] = *(AP1ColHit *)&InitialColInfo;
    }
    applyPartOrients(self);
    if (p->skel == 0) {
        d = CSVSYSTEM_InitDObj(7, arg);
        p->arm[0] = d;
        if (*(int *)(d + 0xC) != 0) {
            iosFree(*(int *)(d + 0xC) & 0xFFFFFFF);
        }
        if (*(int *)(p->arm[0] + 0x10) != 0) {
            iosFree(*(int *)(p->arm[0] + 0x10) & 0xFFFFFFF);
        }
        *(int *)(p->arm[0] + 0xC) = 0;
        *(int *)(p->arm[0] + 0x10) = 0;
        *(int *)(p->arm[0] + 0xC) = (int)iosMallocDebug(ios_partition_seki, 0x100, a_p_1File, 261);
        *(int *)(p->arm[0] + 0x10) = (int)iosMallocDebug(ios_partition_seki, 0x40, a_p_1File, 261);
        *(int *)(p->arm[0] + 0x8) = 4;
        if (*(int *)(p->arm[0] + 0x870) != 0) {
            iosFree(*(int *)(p->arm[0] + 0x870) & 0xFFFFFFF);
        }
        *(int *)(p->arm[0] + 0x870) =
            (int)iosMallocDebug(ios_partition_seki, 0x140, a_p_1File, 261);
        {
            int n;

            for (n = 0; n < 4; n++) {
                ((AP1Flag *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x38))->ll &= ~1;
                ((AP1Flag *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x38))->ll &= ~2;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x40) = 0.0f;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x44) = 0.0f;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x48) = 0.0f;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x4C) = 1.0f;
                ((AP1Flag *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x38))->ll &= ~4;
                *(int *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x30) = 0;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x34) = 1.0f;
                *(short *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x3A) = 0;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x20) = 1.0f;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x24) = 1.0f;
                *(float *)(*(char **)(p->arm[0] + 0x870) + n * 0x50 + 0x28) = 1.0f;
            }
        }
        *(short *)(p->arm[0] + 0x84C) = 2;
        d = CSVSYSTEM_InitDObj(8, arg);
        p->arm[1] = d;
        if (*(int *)(d + 0xC) != 0) {
            iosFree(*(int *)(d + 0xC) & 0xFFFFFFF);
        }
        if (*(int *)(p->arm[1] + 0x10) != 0) {
            iosFree(*(int *)(p->arm[1] + 0x10) & 0xFFFFFFF);
        }
        *(int *)(p->arm[1] + 0xC) = 0;
        *(int *)(p->arm[1] + 0x10) = 0;
        *(int *)(p->arm[1] + 0xC) = (int)iosMallocDebug(ios_partition_seki, 0x100, a_p_1File, 264);
        *(int *)(p->arm[1] + 0x10) = (int)iosMallocDebug(ios_partition_seki, 0x40, a_p_1File, 264);
        *(int *)(p->arm[1] + 0x8) = 4;
        if (*(int *)(p->arm[1] + 0x870) != 0) {
            iosFree(*(int *)(p->arm[1] + 0x870) & 0xFFFFFFF);
        }
        *(int *)(p->arm[1] + 0x870) =
            (int)iosMallocDebug(ios_partition_seki, 0x140, a_p_1File, 264);
        {
            int n;

            for (n = 0; n < 4; n++) {
                ((AP1Flag *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x38))->ll &= ~1;
                ((AP1Flag *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x38))->ll &= ~2;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x40) = 0.0f;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x44) = 0.0f;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x48) = 0.0f;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x4C) = 1.0f;
                ((AP1Flag *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x38))->ll &= ~4;
                *(int *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x30) = 0;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x34) = 1.0f;
                *(short *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x3A) = 0;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x20) = 1.0f;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x24) = 1.0f;
                *(float *)(*(char **)(p->arm[1] + 0x870) + n * 0x50 + 0x28) = 1.0f;
            }
        }
        *(short *)(p->arm[1] + 0x84C) = 2;
    } else {
        for (i = 0; i < 9; i++) {
            p->focus[i] = GetSkeltonFocusNode(self, *(int *)((char *)ap1FocusNode + i * 4));
            if (p->focus[i] == -1) {
                debug_assertMessage(a_p_1File, 0x10D, warningBanner);
                __assert(a_p_1File, 0x10D, "e");
            }
        }
        p->arm[1] = 0;
        p->arm[0] = 0;
    }
    p->eye = InitEnemyEye(0xA, 0, 0xA);
    return p;
}

/* kept local: void (int, int) here, void (float *, float *) in quaternion.h */
extern void GetMatrixFromQuaternion(int dst, int src);
/* kept local: void (int, int, int) here, void (void *, void *, void *) in quaternion.h */
extern void MultiQuaternion(int dst, int a, int b);
/* kept local: void (int, int, int) here, void (float *, short, float *) in quaternion.h */
extern void SetQuaternionByAxisRotateV(int dst, int p, int src);
/* kept local: float (int, int) here, float (void *, void *) in Matrix.h */
extern float _InnerProduct(int dst, int v);
/* kept local: void (int, int) here, void (void *, void *) in Matrix.h */
extern void _NormalizeVector(int dst, int src);
/* kept local: void (int, int, int) here, void (void *, void *, void *) in Matrix.h */
extern void _OuterProduct(int dst, int v, int src);

void yAxisRotFitting(int *self, int arg2)
{
    Vec4A_P_1 l0;
    Vec4A_P_1 l10;
    Mtx44 m20;
    Vec4A_P_1 l60;
    Vec4A_P_1 l70;
    int r;
    float f;

    GetRootQuaternion((int)&l70, self);
    GetMatrixFromQuaternion((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)&ap1DownVector);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        SetRootQuaternion((int)self, (int)&l70);
    }
}

void zAxisRotFitting(int *self, int arg2)
{
    Vec4A_P_1 l0;
    Vec4A_P_1 l10;
    Mtx44 m20;
    Vec4A_P_1 l60;
    Vec4A_P_1 l70;
    int r;
    float f;

    GetRootQuaternion((int)&l70, self);
    GetMatrixFromQuaternion((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)ZUnitVector);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        SetRootQuaternion((int)self, (int)&l70);
    }
}

/* Two static helpers the listing places at a_p_1.c lines 283-292 and 156-165,
 * above the def lines of fitToCol and InitAP1, so both names are ours. */
static inline int clipAndTakeHit(AP1ColHit *dst, char *col)
{
    ClipCollision(col);
    if (*(int *)(col + 0x88) != 0) {
        dst->attr = *(int *)(col + 0x88);
        dst->p = *(AP1PackedLL *)(col + 0x80);
        return 1;
    }
    if (*(int *)(col + 0x94) != 0) {
        dst->attr = *(int *)(col + 0x94);
        dst->p = *(AP1PackedLL *)(col + 0x8C);
        return 1;
    }
    return 0;
}

/* kept local: void (void *, void *) here, void (float *, float *) in quaternion.h */
extern void GetInverseQuaternion(void *dst, void *src);
/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _SubVectorXYZ(void *dst, void *a, void *b);
/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _InterVector(void *dst, void *a, void *b, float t);

/* Listing lines 322-332, above fitToCol's def line, so the name is ours. */
static inline void fitYawToVector(char *self, Vec4A_P_1 *dir)
{
    Vec4A_P_1 q;
    Vec4A_P_1 qi;
    Vec4A_P_1 rot;
    Mtx44 mm;
    Vec4A_P_1 v;

    GetRootQuaternion((int)&q, (int *)self);
    GetInverseQuaternion(&qi, &q);
    GetMatrixFromQuaternion((int)&mm, (int)&qi);
    _ApplyMatrix((int)&v, (int)&mm, (int)dir);
    v.m[2] = 0.0f;
    _NormalizeVector((int)&v, (int)&v);
    SetQuaternionByAxisRotateV((int)&rot, (short)-GetTableArcTan2(v.m[0], -v.m[1]),
                               (int)ZUnitVector);
    MultiQuaternion((int)&q, (int)&q, (int)&rot);
    SetRootQuaternion((int)self, (int)&q);
}

/* Listing lines 360-373, above fitToCol's def line, so the name is ours. */
static inline int clipPartPair(AP1ColHit *dst, Mtx44 *m, AP1ColSeg *tbl, Vec4A_P_1 *pos,
                               Vec4A_P_1 *nrm)
{
    int i;

    for (i = 0; i < 2; i++) {
        _ApplyMatrix((int)&ap1PartClip, (int)m, (int)&tbl[i].a);
        _ApplyMatrix((int)&ap1PartClip.to, (int)m, (int)&tbl[i].b);
        if (clipAndTakeHit(dst, (char *)&ap1PartClip)) {
            CopyVector(pos, &ap1PartClip.pos);
            CopyVector(nrm, &ap1PartClip.normal);
            return 1;
        }
    }
    dst->attr = 0;
    return 0;
}

/* Two static helpers above fitToCol's def line, so both names are ours. The
   listing runs a_p_1.c:392 (the CopyVector) before 386 and 387 (the two field
   writes), so the writes cannot sit below the call in one function: they are
   their own helper at listing lines 385-388, called from the one at 390-393. */
static inline void setPartHit(AP1Part *part)
{
    part->state = 1;
    part->count = 0;
}

static inline void resetPartHit(AP1Part *part, float *orient)
{
    CopyVector(&part->home, orient);
    setPartHit(part);
}

int fitToCol(char *self, int arg1)
{
    Mtx44 m;
    Vec4A_P_1 posA;
    Vec4A_P_1 posB;
    Vec4A_P_1 nrmA;
    Vec4A_P_1 nrmB;
    Vec4A_P_1 nrm;
    Vec4A_P_1 dir;
    Vec4A_P_1 pos;
    AP1Work *p;
    int hit1;
    int hit2;

    p = GOBJ_SUB(self)->work;
    GetRootMatrix(&m, self);
    hit1 = clipPartPair(&p->hit[0], &m, ap1ColSegA, &posA, &nrmA);
    hit2 = clipPartPair(&p->hit[1], &m, ap1ColSegB, &posB, &nrmB);
    if (hit1) {
        if (hit2) {
            _SubVectorXYZ(&dir, &posA, &posB);
            _NormalizeVector((int)&dir, (int)&dir);
            zAxisRotFitting((int *)self, (int)&dir);
            _InterVector(&nrm, &nrmA, &nrmB, 0.5f);
            _NormalizeVector((int)&nrm, (int)&nrm);
            fitYawToVector(self, &nrm);
            _InterVector(&pos, &posA, &posB, 0.5f);
            SetRootPosition(self, &pos);
            {
                Mtx44 tm;
                Vec4A_P_1 t;
                int i;
                float rangeSq = 10000.0f;
                char *tbl;

                MatrixDrive_SetTransposeMatrix(&tm, &m);
                tbl = (char *)ap1PartOffset;
                /* part, tbl, lim and z are our names: the listing carries no
                   symbols for locals. ROM holds every bound of the test in one
                   FP scratch and the component under test in another, which is
                   what lim and z spell. */
                for (i = 0; i < 4; i++) {
                    AP1Part *part = &p->part[i];
                    float lim;
                    float z;

                    _ApplyMatrix((int)&t, (int)&tm, (int)&part->pos);
                    if (part->state != 0) {
                        continue;
                    }
                    if (arg1 != 0) {
                        if (i == 0) {
                            if (p->part[1].state == 0) {
                                goto reset;
                            }
                        }
                        if (i == 3) {
                            if (p->part[2].state == 0) {
                                goto reset;
                            }
                        }
                    }
                    if (distance_squared(&pos, &part->pos) > rangeSq) {
                        goto reset;
                    }
                    z = t.m[2];
                    if (i & 2) {
                        lim = 0.0f;
                        if (z > lim) {
                            goto reset;
                        }
                        lim = -50.0f;
                    } else {
                        lim = 20.0f;
                    }
                    if (z < lim) {
                        goto reset;
                    }
                    z = t.m[0];
                    if (i & 1) {
                        lim = -10.0f;
                        if (z > lim) {
                            goto reset;
                        }
                    } else {
                        lim = 10.0f;
                        if (z < lim) {
                            goto reset;
                        }
                    }
                    continue;
                reset:
                    resetPartHit(part, (float *)(tbl + i * 0x10));
                }
            }
            return -1;
        }
        fitYawToVector(self, &nrmA);
        return -1;
    }
    if (hit2) {
        fitYawToVector(self, &nrmB);
    }
    return 2;
}

/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _ScaleVector(void *dst, void *src, float s);
/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _AddVectorXYZ(void *dst, void *a, void *b);

typedef union {
    int i;
    float f;
} AP1Val;

int walkMot(char *a0)
{
    Vec4A_P_1 pos;
    Vec4A_P_1 v;
    Mtx44 m;
    Mtx44 tm;
    Vec4A_P_1 out;
    AP1Work *p = GOBJ_SUB(a0)->work;
    int ret = fitToCol(a0, 1);
    int i;
    int n;

    if (ret != -1)
        return ret;

    GetRootPosition(&pos, a0);
    GetRootMatrix(&m, a0);
    _ApplyMatrix((int)&v, (int)&m, (int)&p->up);
    n = 0;
    for (i = 0; i < 4; i++) {
        if (p->part[i].state == 0) {
            n++;
        }
    }
    _ScaleVector(&v, &v, ((float)n * 0.25f + 0.5f) * 0.5f);
    _ScaleVector((char *)GOBJ_SUB(a0) + 0x130, (char *)GOBJ_SUB(a0) + 0x130, 0.8f);
    _AddVectorXYZ((char *)GOBJ_SUB(a0) + 0x130, (char *)GOBJ_SUB(a0) + 0x130, &v);
    MatrixDrive_SetTransposeMatrix(&tm, &m);
    _ApplyMatrix((int)&out, (int)&tm, (int)((char *)GOBJ_SUB(a0) + 0x130));
    /* the two stores go through the TU's AP1Val view: the ROM keeps the
       object-sub load after them, which only an alias-set-0 store gives */
    ((AP1Val *)&p->f_1C4)->f = out.m[0];
    ((AP1Val *)&p->f_1C0)->f = VectorLength((char *)GOBJ_SUB(a0) + 0x130) * 0.1f;
    _AddVectorXYZ(&pos, &pos, (char *)GOBJ_SUB(a0) + 0x130);
    SetRootPosition(a0, &pos);
    p->f_1C8 = 0.0f;
    return 1;
}

/* kept local: int (void *, int) here, int (char *, int) in motionManager2.h */
extern int CheckWallAttribute(void *gobj, int mask);
/* kept local: int (void *, int) here, int (char *, int) in motionManager2.h */
extern int CheckFloorAttribute(void *gobj, int mask);
/* kept local: int (void *, void *, void *, float) here, int (char *, char *, float *, float) in motionManager2.h */
extern int CheckFieldContact(void *col, void *gobj, void *pos, float r);

int rolling(char *a0)
{
    AP1ColHit info;

    if (*(int *)((char *)GOBJ_SUB(a0)) != 0) {
        UnlinkParentOfDObj(a0);
    }
    ((AP1Val *)((char *)GOBJ_SUB(a0) + 0x134))->f +=
        60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
        (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
    _AddVectorXYZ((char *)GOBJ_SUB(a0) + 0xA0, (char *)GOBJ_SUB(a0) + 0xA0,
                  (char *)GOBJ_SUB(a0) + 0x130);
    {
        char *col = (char *)&ap1RollClip;
        CopyVector(col, (char *)GOBJ_SUB(a0) + 0x1F0);
        CopyVector(col + 0x10, (char *)GOBJ_SUB(a0) + 0xA0);
        *(float *)(col + 4) -= 50.0f;
        if (clipAndTakeHit(&info, col)) {
            CopyVector((char *)GOBJ_SUB(a0) + 0xA0, &ap1RollClip.pos);
            CopyVector((char *)GOBJ_SUB(a0) + 0x130, ZeroVector);
            yAxisRotFitting((int *)a0, (int)&ap1RollClip.normal);
            LinkParentOfDObj(a0, &info);
            UpdateRootMatrix(a0);
            applyPartOrients(a0);
            {
                char *col = (char *)&ap1RollClip;
                if (*(int *)(col + 0x88) != 0) {
                    GOBJ_SUB(a0)->floorAttr = GetWallAttribute(col);
                }
                if (CheckWallAttribute(a0, 0x50) != 0) {
                    if (GetPoolGlobalHeight(*(int *)(col + 0x80)) <
                        GOBJ_SUB(a0)->rootPosY + 50.0f) {
                        iosOmSendMail(a0, 0x26, a0);
                    }
                }
            }
            {
                char *col = (char *)&ap1RollClip;
                if (*(int *)(col + 0x94) != 0) {
                    GOBJ_SUB(a0)->floorAttr = GetFloorAttribute(col);
                    if (CheckFloorAttribute(a0, 0x50) != 0) {
                        if (GetPoolGlobalHeight(*(int *)(col + 0x8C)) <
                            GOBJ_SUB(a0)->rootPosY + 50.0f) {
                            iosOmSendMail(a0, 0x26, a0);
                        }
                    }
                }
            }
            return 0;
        }
    }
    {
        char *col = (char *)&ap1RollClip;
        *(float *)(col + 0x14) += 500.0f;
        ClipFloor(col);
        if (CheckFieldContact(col, a0, (char *)GOBJ_SUB(a0) + 0xA0, 50.0f) == 2) {
            CopyVector((char *)GOBJ_SUB(a0) + 0x130, ZeroVector);
            iosOmSendMail(a0, 0x1A, a0);
        }
    }
    return -1;
}

/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _MulMatrix(void *dst, void *a, void *b);
/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _SubVector(void *dst, void *a, void *b);
/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
/* kept local: agrees with Matrix.h, which this TU does not include (_ApplyMatrix, _InnerProduct differ) */
extern float _GetLength(void *a, void *b);
/* kept local: void (void *, int) here, void (int, int) in frameDependSequence.h */
extern void ExecuteSEPackage(void *self, int id);
/* kept local: void (void *, int, void *, int, float, int) here, int (char *, int, float *, float *, float, int) in attackhit.h */
extern void _AttackCenter(void *self, int a1, void *v, int a3, float r, int a5);

/* the point the spider's bite attack is centred on, 50 units down its own arm */
static const Vec4A_P_1 attackCenterOffset = {50.0f, 0.0f, 0.0f, 1.0f};

/* static helper the listing places at a_p_1.c lines 628-631, above
 * calcSubMission's def line 637, so the name is ours: the law of cosines for
 * the two arm segments, one named local per listing line. */
static inline short armCosine(float a, float b, float c)
{
    float aa = a * a;
    float bb = b * b;
    float cc = c * c;

    return (short)(int)GetTableArcCos((aa + bb - cc) / (2.0f * a * b));
}

void calcSubMission(char *self)
{
    AP1Work *p = GOBJ_SUB(self)->work;
    Vec4A_P_1 base;
    Vec4A_P_1 axis;
    Vec4A_P_1 rq;
    Mtx44 tm;
    Vec4A_P_1 q;
    Vec4A_P_1 w;
    Vec4A_P_1 dir;
    Vec4A_P_1 v;
    Vec4A_P_1 v2;
    Mtx44 rm;
    Vec4A_P_1 lv;
    Vec4A_P_1 save;
    Vec4A_P_1 save2;
    Vec4A_P_1 atk;
    int i;
    int ang;

    CopyMatrix(MatrixDrive_GetMatrix(), p->mtx);
    MatrixDrive_RotMatrixZ(0x4000);
    MatrixDrive_RotMatrixX(0x4000);
    CopyVector(&base, (char *)MatrixDrive_GetMatrix() + 0x30);
    GetRootQuaternion((int)&rq, (int *)self);
    _ApplyMatrix((int)&axis, (int)MatrixDrive_GetMatrix(), (int)&ap1AttackAxis);
    MatrixDrive_SetTransposeMatrix(&tm, MatrixDrive_GetMatrix());

    for (i = 0; i < 4; i++) {
        AP1Part *part = &p->part[i];
        float len;

        switch (part->state) {
        case 1: {
            float t = (float)part->count / 10.0f;

            CopyVector(&w, &part->home);
            w.m[1] -= (t < 0.5f) ? t * 2.0f * 20.0f : (1.0f - t) * 2.0f * 20.0f;
            _ApplyMatrix((int)&q, (int)p->root, (int)&w);
            _InterVectorXYZ(&part->pos, &q, &part->pos, t);
            if ((part->count += 1) >= 10) {
                part->state = 0;
            }
            break;
        }
        case 2: {
            float t = (float)part->count / 10.0f;

            MatrixDrive_PushMatrix();
            _UnitMatrix(MatrixDrive_GetMatrix());
            {
                float f = t * 49152.0f + -32768.0f;

                MatrixDrive_RotMatrixY((short)(i == 0 ? -f : f));
            }
            _ApplyMatrix((int)&v, (int)MatrixDrive_GetMatrix(), (int)&part->home);
            v.m[3] = 1.0f;
            _ApplyMatrix((int)&dir, (int)p->root, (int)&v);
            _InterVectorXYZ(&part->pos, &dir, &part->pos, t);
            MatrixDrive_PopMatrix();
            if ((part->count += 1) >= 10) {
                ExecuteSEPackage(self, 0x68);
                CopyVector(&part->home, (char *)ap1PartOffset + i * 0x10);
                part->state = 1;
                part->count = 0;
            }
            break;
        }
        }

        MatrixDrive_PushMatrix();

        len = _GetLength(&base, &part->pos);
        ang = armCosine(len, 50.0f, 50.0f);
        _SubVector(&dir, &part->pos, &base);
        _NormalizeVector((int)&dir, (int)&dir);

        if (part->state == 2) {
            _OuterProduct((int)&w, (int)&dir, (int)&axis);
        } else {
            _OuterProduct((int)&w, (int)&dir, (int)&axis);
        }
        _ApplyMatrix((int)&lv, (int)&tm, (int)&dir);
        MatrixDrive_TurnXObjectMatrixYZ(lv.m[0], lv.m[1], lv.m[2]);

        _ScaleVector(&v, &dir, 50.0f);
        SetQuaternionByAxisRotateV((int)&q, (short)-ang, (int)&w);
        GetMatrixFromQuaternion((int)&rm, (int)&q);
        _ApplyMatrix((int)&v, (int)&rm, (int)&v);
        _AddVectorXYZ(&part->knee, &base, &v);

        CopyVector(&save, (char *)MatrixDrive_GetMatrix() + 0x30);
        _MulMatrix(MatrixDrive_GetMatrix(), &rm, MatrixDrive_GetMatrix());
        CopyVector((char *)MatrixDrive_GetMatrix() + 0x30, &save);

        if (p->skel != 0) {
            _MulMatrix((char *)GOBJ_SUB(self)->nodeMtx + ((&p->focus[1])[i * 2] << 6),
                       MatrixDrive_GetMatrix(), ap1ArmScale);
        } else {
            _MulMatrix(*(char **)(p->arm[0] + 0xC) + (i << 6), MatrixDrive_GetMatrix(),
                       ap1ArmScale);
        }

        _ScaleVector(&v2, &dir, 50.0f);
        SetQuaternionByAxisRotateV((int)&q, (short)ang, (int)&w);
        GetMatrixFromQuaternion((int)&rm, (int)&q);
        _ApplyMatrix((int)&v2, (int)&rm, (int)&v2);
        _AddVectorXYZ(&part->tip, &part->knee, &v2);

        _MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), ap1ArmOffset);

        CopyVector(&save2, (char *)MatrixDrive_GetMatrix() + 0x30);
        _MulMatrix(MatrixDrive_GetMatrix(), &rm, MatrixDrive_GetMatrix());
        _MulMatrix(MatrixDrive_GetMatrix(), &rm, MatrixDrive_GetMatrix());
        CopyVector((char *)MatrixDrive_GetMatrix() + 0x30, &save2);

        if (part->state == 2) {
            atk = attackCenterOffset;
            _ApplyMatrix((int)&atk, (int)MatrixDrive_GetMatrix(), (int)&atk);
            _AttackCenter(self, -1, &atk, 0, 30.0f, 0);
        }

        if (p->skel != 0) {
            _MulMatrix((char *)GOBJ_SUB(self)->nodeMtx + ((&p->focus[2])[i * 2] << 6),
                       MatrixDrive_GetMatrix(), ap1ArmScale);
        } else {
            _MulMatrix(*(char **)(p->arm[1] + 0xC) + (i << 6), MatrixDrive_GetMatrix(),
                       ap1ArmScale);
        }

        MatrixDrive_PopMatrix();
    }
}

/* kept local: agrees with quaternion.h, which this TU does not include (GetMatrixFromQuaternion, SetQuaternionByAxisRotateV differ) */
extern void RotQuaternionX(void *q, short ang);
/* kept local: agrees with quaternion.h, which this TU does not include (GetMatrixFromQuaternion, SetQuaternionByAxisRotateV differ) */
extern void RotQuaternionZ(void *q, short ang);
/* kept local: void (void *, void *, void *) here, void (float *, float *, float *) in quaternion.h */
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
/* kept local: agrees with quaternion.h, which this TU does not include (GetMatrixFromQuaternion, SetQuaternionByAxisRotateV differ) */
extern void GetSlerpQuaternion(void *dst, void *a, void *b, float t);

void updateMatrix(char *a0)
{
    float pos[4];
    float quat[4];
    float mtx[16];
    AP1Work *p = GOBJ_SUB(a0)->work;

    CopyVector((char *)GOBJ_SUB(a0) + 0x1F0, (char *)GOBJ_SUB(a0) + 0xA0);
    UpdateRootMatrix(a0);
    CopyMatrix(p->root, (void *)GOBJ_SUB(a0)->nodeMtx);

    ap1BodyPos[1] = ((float)p->blink * 0.03125f < 0.5f)
                        ? ((float)p->blink * 0.03125f) * 2.0f * 5.0f + -10.0f
                        : (1.0f - (float)p->blink * 0.03125f) * 2.0f * 5.0f + -10.0f;
    ap1BodyPos[1] -= p->f_1C8 * 25.0f;
    ap1BodyPos[2] = p->f_1C8 * 50.0f;

    GetRootPosition(pos, a0);
    GetRootQuaternion((int)quat, (int *)a0);

    RotQuaternionX(quat, (short)(p->f_1C8 * 8192.0f));
    RotQuaternionX(quat, (short)(p->f_1C0 * 4096.0f));
    GetMatrixFromQuaternionPos(mtx, quat, pos);
    _ApplyMatrix((int)pos, (int)mtx, (int)ap1BodyPos);
    RotQuaternionZ(quat, (short)(-p->f_1C4 * 2048.0f));
    _InterVectorXYZ(&p->pos, pos, &p->pos, 0.5f);
    GetSlerpQuaternion(&p->quat, quat, &p->quat, 0.1f);
    GetMatrixFromQuaternionPos(p->mtx, &p->quat, &p->pos);
    _MulMatrix((void *)GOBJ_SUB(a0)->nodeMtx, p->mtx, ap1BodyMatrix);
}

void resetPositionInfo(char *a0)
{
    AP1Work *p = GOBJ_SUB(a0)->work;
    GetRootPosition(&p->pos, a0);
    GetRootQuaternion(&p->quat, a0);
    ResetEnemyEye(p->eye);
}

/* static helper the listing places at a_p_1.c lines 889-891, expanded only
 * into AP1Geo, so this name is ours. */
static inline void stepAP1BlinkTimer(char *g)
{
    AP1Work *q = GOBJ_SUB(g)->work;
    int t = q->blink + 1;

    q->blink = t;
    if (t > 32) {
        q->blink = 0;
    }
}

void AP1Geo(char *a0)
{
    AP1Work *p = GOBJ_SUB(a0)->work;
    float d;

    switch (p->mode) {
    default:
        if (p->f_274 < 10) {
            p->f_274 = p->f_274 + 1;
            resetPositionInfo(a0);
        }
        p->mode = motFuncList[p->mode][1](a0);
        stepAP1BlinkTimer(a0);
        break;

    case 5:
        p->mode = 4;
        break;

    case 4:
        p->mode = 6;
        break;

    case 6:
        *(int *)(a0 + 0x16C) = 0;
        break;

    case 7:
        break;
    }
    updateMatrix(a0);
    calcSubMission(a0);
    _MulMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(a0)->nodeMtx, ap1EyeMatrix);
    UpdateEnemyEye(p->eye, MatrixDrive_GetMatrix(), 1.0f);
    if (p->skel != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(a0)->nodeMtx);
        MatrixDrive_RotMatrixZ(0x4000);
        MatrixDrive_RotMatrixX(0x4000);
        _MulMatrix((void *)GOBJ_SUB(a0)->nodeMtx, MatrixDrive_GetMatrix(), ap1HeadScale);
    }
    d = GOBJ_SUB(a0)->matrixTy - *(float *)((char *)GOBJ_SUB(a0)->nodeMtx + 0x34);
    if ((d < 0.0f) ? ((d = -d) > 10000.0f) : (d > 10000.0f)) {
        GOBJ_SUB(a0)->floorAttr = 0x800;
        /* EUC-JP: "fall-death request from the spider slipping free" */
        debug_StdPrintfDummy("蜘蛛の抜けによる落下死リクエスト\n");
    }
}

void AP1DL(char *a0)
{
    AP1Work *p = GOBJ_SUB(a0)->work;

    if (p->mode < 5) {
        if (p->visible != 0) {
            p2o_SetDefaultEnviroment();
            p2o_DispVU1(a0);
            if (p->skel == 0) {
                p2o_DispVU1DObjMulti(p->arm[0]);
                p2o_DispVU1DObjMulti(p->arm[1]);
            }
            DispEnemyEye(p->eye);
        }
    }
}

int GetAP1SpecType(char *a0)
{
    return ((AP1Work *)GOBJ_SUB(a0)->work)->layout;
}

void SetAP1VisualState(char *a0, int a1)
{
    ((AP1Work *)GOBJ_SUB(a0)->work)->visible = a1;
}

/* kept local: void (int, int) here, void (void *, short) in quaternion.h */
extern void RotQuaternionY(int q, int ang);
/* kept local: void (int) here, void (void *) in quaternion.h */
extern void RegularizeQuaternion(int q);

int AP1Turn(char *a0, short a1)
{
    Vec4A_P_1 q;
    int s = ((AP1Work *)GOBJ_SUB(a0)->work)->mode;
    if (s < 6) {
        if (s >= 2)
            goto out;
    }
    GetRootQuaternion((int)&q, (int *)a0);
    RotQuaternionY((int)&q, a1);
    RegularizeQuaternion((int)&q);
    SetRootQuaternion((int)a0, (int)&q);
    updateMatrix(a0);
    return 1;
out:
    return 0;
}

int AP1MotReqForce(char *a0, int a1)
{
    AP1Work *p = GOBJ_SUB(a0)->work;

    p->mode = a1;
    if (motFuncList[a1][0] != 0) {
        motFuncList[a1][0](a0);
    }
    return 1;
}

int AP1MotReq(char *a0, int a1)
{
    int s = ((AP1Work *)GOBJ_SUB(a0)->work)->mode;
    if (s < 6) {
        if (s >= 2)
            return 0;
    }
    AP1MotReqForce(a0, a1);
    return 1;
}

int AP1JumpReq(char *a0, int a1, void *a2)
{
    int flag;
    Sub15C *p = GOBJ_SUB(a0);
    AP1Work *q = (AP1Work *)p->work;
    if (q->mode < 6) {
        if (q->mode >= 2) {
            flag = 0;
            goto check;
        }
    }
    AP1MotReqForce(a0, a1);
    flag = 1;
check:
    if (flag != 0) {
        Sub15C *pp = GOBJ_SUB(a0);
        AP1Work *qq = (AP1Work *)pp->work;
        _ApplyMatrix((int)((char *)pp + 0x130), (int)qq->root, (int)a2);
        return 1;
    }
    return 0;
}

char *MakeAP1GObj(char *a0)
{
    return CreateLayoutedGObj(62, D_0062B588[*(int *)(a0 + 0x30)].unkC, -1, 0, a0, 0, 7, 1);
}

int GetAP1Mode(char *a0)
{
    return (int)ap1ModeName[((AP1Work *)GOBJ_SUB(a0)->work)->mode];
}

int standMot(char *a0)
{
    AP1Work *p = GOBJ_SUB(a0)->work;
    int ret = fitToCol(a0, 0);
    if (ret != -1)
        return ret;
    p->f_1C0 = 0.0f;
    p->f_1C4 = 0.0f;
    p->f_1C8 = 0.0f;
    return 0;
}

int rollingMot(char *a0)
{
    AP1Work *p = GOBJ_SUB(a0)->work;
    int ret = rolling(a0);
    if (ret != -1)
        return ret;
    p->f_1C0 = 0.0f;
    p->f_1C4 = 0.0f;
    p->f_1C8 = 0.0f;
    return 2;
}

typedef struct {
    int state;     /* 0x00 */
    float frame;   /* 0x04 */
    int unk8[6];   /* 0x08 */
    Vec4A_P_1 vec; /* 0x20 */
} AP1MotCtrl;

/* Two static helpers the listing places at a_p_1.c lines 384-393 (the census
 * gap between 353 and 397), expanded twice each into attackMotInit and
 * attackMot; neither is emitted out of line, so both names are ours. */
static inline void setAP1MotCtrlState(AP1MotCtrl *m, int state)
{
    m->state = state;
    m->frame = 0.0f;
}

static inline void setAP1MotCtrlVector(AP1MotCtrl *m, Vec4A_P_1 *v)
{
    CopyVector(&m->vec, v);
    setAP1MotCtrlState(m, 0);
}

void attackMotInit(char *a0)
{
    Vec4A_P_1 pos;
    Mtx44 mtx;
    Vec4A_P_1 dir;
    AP1Work *p = GOBJ_SUB(a0)->work;

    GetRootPosition(&pos, (void *)boyGObj);
    MatrixDrive_SetTransposeMatrix(&mtx, p->root);
    _ApplyMatrix((int)&dir, (int)&mtx, (int)&pos);
    setAP1MotCtrlVector((AP1MotCtrl *)&p->part[0], &dir);
    setAP1MotCtrlVector((AP1MotCtrl *)&p->part[1], &dir);
}

int attackMot(char *a0)
{
    AP1Work *p = GOBJ_SUB(a0)->work;
    int ret = fitToCol(a0, 0);
    if (ret != -1)
        return ret;
    p->f_1C0 = 0.0f;
    p->f_1C4 = 0.0f;
    p->f_1C8 += 0.05f;
    if (p->f_1C8 > 1.0f) {
        setAP1MotCtrlState((AP1MotCtrl *)&p->part[0], 2);
        setAP1MotCtrlState((AP1MotCtrl *)&p->part[1], 2);
        return 0;
    }
    return 3;
}
