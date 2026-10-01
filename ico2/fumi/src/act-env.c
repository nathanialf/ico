#include "typedef.h"
#include "debug.h"
#include <libvu0.h>
#include "act-game.h"
#include "torch.h"
#include "gobj.h"
#include "camera-editor.h"
#include "commonact.h"
#include "motionManager2.h"

union ENVIF { /* field names derived */
    int i;
    float f;
}; /* derived name */

/* the per-stage ditch-distance tables getDitchDistTbl selects between (the
   first six are ranges terminated by -1.0f, the rest position/orientation
   vectors) */
static float ditchDistTbl[4] = {150.0f, 215.0f, 315.0f, -1.0f}; /* derived name */

static float ditchDistTblStage26[4] = {150.0f, 235.0f, 315.0f, -1.0f}; /* derived name */

static float ditchDistTblStage8[4] = {315.0f, 330.0f, 350.0f, -1.0f}; /* derived name */

static float ditchDistTblCarry[4] = {150.0f, 215.0f, 315.0f, -1.0f}; /* derived name */

static float ditchDistTblSofa[4] = {150.0f, 215.0f, 315.0f, -1.0f}; /* derived name */

static float ditchDistTblNone[4] = {-1.0f, 0.0f, 0.0f, 0.0f}; /* derived name */

static float ditchCheckBase[4] = {226.0f, -2328.0f, 343.0f, 1.0f}; /* derived name */

static float ditchCheckDir[4] = {0.642799f, 0.0f, -0.765893f, 0.0f}; /* derived name */

static float ditchCarryTarget[4] = {602.0f, -3775.0f, 2480.0f, 1.0f}; /* derived name */

static float ditchSofaTarget[4] = {749.0f, -3775.0f, 2650.0f, 1.0f}; /* derived name */

static float ditchSofaPos[4] = {559.0f, -3775.0f, 2503.0f, 1.0f}; /* derived name */

/* The sofa seat offset in the room's local space, the first object of the
   TU's .rodata. */
static const VECTOR sofaSeatOffset = {30.0f, 0.0f, -50.0f, 0.0f}; /* derived name */

/* int here, GObj * in main.h */
extern int boyGObj;
/* as in main.h, which this TU does not include (boyGObj, ((char *)girlGObj) differ) */
extern int stage_no;

#include "act-env.h"
#include "gv.h"
#include "fieldCollision.h"
#include "motionOrientManager.h"

inline void GetSofaPosition(GObj *a0, char *a1)
{
    Act *w = GOBJ_ACT(a0);
    VECTOR v = sofaSeatOffset;
    w->sofaOrient[0] = w->wallOrient[0];
    w->sofaOrient[1] = w->wallOrient[1];
    w->sofaOrient[2] = w->wallOrient[2];
    if (a0 == boyGObj) {
        v.x = -v.x;
    }
    v.w = 1.0f;
    sceVu0ApplyMatrix(w->sofaPos,
                      *(void **)((char *)((union ENVIF *)((char *)a1 + 0x15C))->i + 0xC), &v);
}

/* char * here, GObj * in main.h */
extern GObj *girlGObj;

/* Where the first carrier stands in the stage 8 ditch below the -3000 line
   (the .rodata's second object). */
static const VECTOR ditchCarryPos = {767.0f, -3775.0f, 2621.0f, 1.0f}; /* derived name */

static inline int getDitchCarryMode(void) /* derived name */
{
    void *a;
    void *b;

    if (boyGObj != 0 && ((char *)girlGObj) != 0) {
        a = *(void **)(char *)GOBJ_SUB(boyGObj);
        b = *(void **)(char *)GOBJ_SUB(((char *)girlGObj));

        if (a != 0 && *(int *)((char *)a + 0xC) == 0x2C)
            return 1;
        if (b != 0 && *(int *)((char *)b + 0xC) == 0x2C)
            return 2;
    }
    return 0;
}

static inline int getDitchCarryModeStage8(void) /* derived name */
{
    if (stage_no == 8) {
        return getDitchCarryMode();
    }
    return 0;
}

void getDitchDistTbl(float **tbl, float *range, int *sofa, float *pos, void *obj, int *carry)
{
    VECTOR v;
    int mode;

    *tbl = ditchDistTbl;

    *sofa = 0;
    *carry = 0;
    *range = 0.0f;
    if (stage_no == 26) {
        *tbl = ditchDistTblStage26;
        if (getDitchCarryMode()) {
            *range = 50.0f;
        }
    }
    mode = getDitchCarryModeStage8();
    if (mode) {
        if (-3000.0f < test_CURRENTROOT(boyGObj)[1]) {
            *tbl = ditchDistTblStage8;
            if (mode == 1) {
                v.x = test_CURRENTROOT(boyGObj)[0];
                v.y = test_CURRENTROOT(boyGObj)[1];
                v.z = test_CURRENTROOT(boyGObj)[2];
                sceVu0SubVector(&v, &v, ditchCheckBase);
                _ApplyRyGV(&v, (float)(int)(_GetDirection(ditchCheckDir) / 3.1415927f * 180.0f) *
                                   3.1415927f / 180.0f);
                if (v.z < -150.0f) {
                    *tbl = ditchDistTblNone;
                }
            }
            if (mode == 2) {
                v.x = test_CURRENTROOT(boyGObj)[0];
                v.y = test_CURRENTROOT(boyGObj)[1];
                v.z = test_CURRENTROOT(boyGObj)[2];

                if (520.0f < v.x) {
                    *tbl = ditchDistTblNone;
                }
            }
        } else {
            if (mode == 1) {
                v = ditchCarryPos;

                *tbl = ditchDistTblCarry;
                pos[0] = v.x;
                pos[1] = v.y;
                pos[2] = v.z;
                _OrientXZGV(obj, ditchCarryTarget, &v);

                *carry = mode;
            } else {
                *tbl = ditchDistTblSofa;
                pos[0] = ditchSofaPos[0];
                pos[1] = ditchSofaPos[1];
                pos[2] = ditchSofaPos[2];
                _OrientXZGV(obj, ditchSofaTarget, ditchSofaPos);
            }
            *sofa = 1;
        }
    }
}

int GetDitchPosition(float *out, float *org, float *dir, float d0, float d1, float h)
{
    ClipWork work;
    float tmp[4];
    /* work2 and tmp2 are read only by the DEBUG build's second probe in the
       hit branch */
    ClipWork work2;
    float tmp2[4];

    sceVu0ScaleVector(tmp, dir, d0 + d1);
    sceVu0AddVector(work.a, org, tmp);
    work.b[0] = work.a[0];
    work.b[1] = work.a[1];
    work.b[2] = work.a[2];
    work.a[1] -= 100.0f;
    work.b[1] += h + 100.0f;
    ClipFloor(&work);
    if (work.floorHit != 0) {
#ifdef DEBUG
        sceVu0ScaleVector(tmp2, dir, d0);
        sceVu0AddVector(work2.a, org, tmp2);
        work2.b[0] = work2.a[0];
        work2.b[1] = work2.a[1];
        work2.b[2] = work2.a[2];
        work2.a[1] -= 100.0f;
        work2.b[1] += h + 100.0f;
        ClipFloor(&work2);
        if (work2.floorHit == 0) {
            scePrintf("env: ditch without floor at its near edge\n");
        }
#endif
        out[0] = work.pos[0];
        out[1] = work.pos[1];
        out[2] = work.pos[2];
        return 1;
    }
    return 0;
}

inline void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2)
{
    sceVu0FVECTOR acc;
    char *w;
    int i;
    ((int *)acc)[0] = 0;
    ((int *)acc)[1] = 0;
    ((int *)acc)[2] = 0;
    for (i = 0, w = (char *)a2; i < 4; i++) {
        sceVu0AddVector(acc, acc, (float *)w);
        w += 0x10;
    }
    sceVu0ScaleVector((float *)a0, acc, 0.25f);
    if (a1 != 0) {
        ((union ENVIF *)((char *)a0 + 0xC))->f = 1.0f;
        sceVu0ApplyMatrix(a0, (void *)GOBJ_SUB(a1)->nodeMtx, a0);
    }
}

typedef struct { /* field names derived */
    int on;
    char *name;
} OrientFlagRow; /* derived name */

void DebugActOrientFlag(unsigned int *f)
{
    OrientFlagRow tbl[16] = {
        {(f[1] >> 18) & 1, "climb_50  "},  {(f[1] >> 19) & 1, "climb_100 "},
        {(f[1] >> 20) & 1, "climb_200 "},  {(f[1] >> 21) & 1, "climb_300 "},
        {(f[2] >> 4) & 1, "hold_box  "},   {(f[2] >> 13) & 1, "hang_hand "},
        {(f[2] >> 14) & 1, "hang_breas"},  {(f[2] >> 24) & 1, "ladder_up "},
        {(f[2] >> 25) & 1, "ladder_dow"},  {(f[3] >> 1) & 1, "down_cliff"},
        {(f[3] >> 3) & 1, "walk_wall"},    {(f[3] >> 5) & 1, "walk_stair"},
        {(f[3] >> 6) & 1, "pulledup_50 "}, {(f[3] >> 7) & 1, "pulledup_100"},
        {(f[3] >> 8) & 1, "pulledup_200"}, {-1},
    };
    int y = 40;
    int i;

    for (i = 0; tbl[i].on != -1; i++) {
        if (tbl[i].on) {
            if (debug_font_flag & 1) {
                debug_Printf(10, y += 8, 0x0FFFFFFF, "%s=on\n", tbl[i].name);
            }
        } else {
            if (debug_font_flag & 1) {
                debug_Printf(10, y += 8, 0x0FFFFFFF, "%s=off\n", tbl[i].name);
            }
        }
    }
}

inline void ACTSetEnvAllmighty(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    s->wish0.ll |= (1ULL << 38);
    s->wish0.ll |= (1ULL << 39);
    s->wish0.ll |= (1ULL << 40);
    s->wish0.ll |= (1ULL << 41);
    s->wish0.ll |= (1ULL << 44);
    s->wish0.ll |= (1ULL << 45);
    if (ACTGame_FLAG_TETSUNAGI()) {
        s->flags18.ll &= ~(1ULL << 43);
        s->handFreeFrame = 0;
    } else {
        if ((int)(s->flags18.ll >> 43) & 1)
            s->wish0.ll |= (1ULL << 46);
        s->handFreeFrame += 1;
    }
    s->wish0.ll |= (1ULL << 50);
    s->wish0.ll |= (1ULL << 51);
    s->wish0.ll |= (1ULL << 52);
    s->wish0.ll |= (1ULL << 53);
    s->wish0.ll |= (1ULL << 49);
    s->wish1.ll |= (1ULL << 43);
}

inline int CheckWallAttributeEdegWall(int a0)
{
    if (stage_no == 4) {
        return (unsigned char)CheckPureWallAttribute(a0, 0x1000);
    }
    return (unsigned char)CheckWallAttribute(a0, 0x1000);
}

/* The motion record at actor + 0x130 and the three sub-object words
   ACTGetEnvironment's head reads that Sub15C does not name yet (the object
   kind at 0x0, the wall record at 0x574, the wall height at 0x5A4). */
typedef struct { /* field names derived */
    char pad000[272];
    float cliffDepth; /* 0x110 */
    float cliffDist;  /* 0x114 */
    char pad118[24];
    float height; /* 0x130 */
    char pad134[4];
    float wallDist; /* 0x138 */
} EnvMotion;        /* derived name */

typedef struct { /* field names derived */
    int kind;    /* 0x0 */
    char pad004[1392];
    char *wallRec; /* 0x574 */
    char pad578[44];
    float wallTop; /* 0x5A4 */
} EnvSub;          /* derived name */

extern int _FrontGV(float *a0, float *a1, void *ori, int deg);
extern float GetCorrectDistance(float d, int n);
extern void GetOrientOfCliffOfGObj(void *out, void *obj);
/* same prototype as its definition in weapon.c; no header carries it */
extern char *CheckSwapableWeapon(char *a0, float dist);
extern char *CheckTorchChainReactionReverse(char *a0, float dist);
extern char *GetBombTorchGObj(char *a0);
extern int GetBoxHoldPoint(float *out, char *self, void *chara);
/* char * here, int in main.h */
extern int girlControlMode;
/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* the negated-orient angle, eight call sites */
static inline int rotyFromBack(void *o, float *v) /* derived name */
{
    float t[4];

    sceVu0ScaleVector(t, v, -1.0f);
    return _RotyGV(o, t);
}

/* the same with the scale as a parameter, two sites */
static inline int rotyFromScaled(void *o, float *v, float s) /* derived name */
{
    float t[4];

    sceVu0ScaleVector(t, v, s);
    return _RotyGV(o, t);
}

/* the absolute values of the two above */
static inline int absRotyFromBack(void *o, float *v) /* derived name */
{
    int r = rotyFromBack(o, v);

    return (r < 0) ? -r : r;
}

static inline int absRotyFromScaled(void *o, float *v, float s) /* derived name */
{
    int r = rotyFromScaled(o, v, s);

    return (r < 0) ? -r : r;
}

/* the ditch-height probe, one site */
static inline unsigned char ditchProbe(GObj *o, float h) /* derived name */
{
    ClipWork work;
    Act *s;
    float y, d;

    s = GOBJ_ACT(o);
    if (o == boyGObj && stageData[stage_no].flag2 && (s->actMode == 4 || s->actMode == 5)) {
        memset(&work, 0, 0xC0);
        GetSkeltonPosition(work.a, o, 0x2C);
        work.b[0] = work.a[0];
        work.b[2] = work.a[2];
        work.b[1] = work.a[1] + 200.0f;
        ClipFloor(&work);
        if (work.floorHit) {
            y = work.pos[1] - work.a[1];
            d = h + y;
            if (d < 250.0f)
                return 0;
        }
    }
    return 1;
}

/* The collision-centre wrapper and the scaled offset around it, four sites
   with scales 5, 45, 30, 30.  It reads the wall record (+0x188) or the cliff
   record (+0x198) of the object's collision data, as `cliff` selects. */
static inline void collisCenter(float *out, void *ref, void *o, int cliff) /* derived name */
{
    float *p;

    if (!cliff)
        p = *(float **)((char *)((union ENVIF *)((char *)o + 0x15C))->i + 0x188);
    else
        p = *(float **)((char *)((union ENVIF *)((char *)o + 0x15C))->i + 0x198);
    GetCollisCenterPositionSimple(out, 0, p);
    if (ref != 0) {
        ((union ENVIF *)((char *)out + 0xC))->f = 1.0f;
        sceVu0ApplyMatrix(out, (void *)GOBJ_SUB(ref)->nodeMtx, out);
    }
}

/* the wrapper with no reference object, two sites (the wall and the cliff
   collision centres) */
static inline void collisCenterOwn(float *out, void *o, int cliff) /* derived name */
{
    collisCenter(out, 0, o, cliff);
}

static inline void pullPosition(float *out, void *o, void *ref, float k) /* derived name */
{
    char *s = *(char **)((char *)o + 0x164);
    float t[4];
    collisCenter(out, ref, o, 0);
    sceVu0ScaleVector(t, (float *)(s + 0x4B0), k);
    sceVu0AddVector(out, out, t);
}

/* the actor's position moved back from the wall by the wall distance less
   a margin: -20 for an enemy (kind 4), 5 for the others */
static inline void wallContactPosEnemy(void *o, float *v, float top, float *out) /* derived name */
{
    float p[4], t[4];
    float d = -20.0f;

    GetRootPosition(p, o);
    sceVu0ScaleVector(t, v, -(top - d));
    sceVu0AddVector(out, p, t);
}

static inline void wallContactPos(void *o, float *v, float top, float *out) /* derived name */
{
    float p[4], t[4];
    float d = 5.0f;

    GetRootPosition(p, o);
    sceVu0ScaleVector(t, v, -(top - d));
    sceVu0AddVector(out, p, t);
}

/* The environment check's TTY trace, built only when DEBUG is defined; the
   retail build leaves the helper without a body. */
static __inline__ void envDebugPrint(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("env: girl climb height over 195\n");
#endif
}

/* ACTGetEnvironment keeps its line breaks as written: under -g a moved line
   changes the code, so the formatter leaves it alone. */
/* clang-format off */
/* the box loop's four sides */
#define BOX_DY ((p100[1] - prj[1]) < 0.0f ? -(p100[1] - prj[1]) : (p100[1] - prj[1])) /* derived name */
#define BOX_SIDE(lo, hi, ofs, ang, cond, to) /* derived name */ \
    if ((lo) < p120[0] && p120[0] <= (hi)) {                                                     \
        sceVu0ScaleVector(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500, env->cliffOrient,       \
                          (p120[0] < 0.0f ? -p120[0] : p120[0]) - (ofs));                       \
        _ApplyRyGV(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500, (ang));                  \
        sceVu0AddVector((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500), pos,     \
                        (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500));         \
        *(char *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x4F0) = 1;                      \
        if (cond)                                                                                \
            sel = (to);                                                                          \
        break;                                                                                   \
    }

void ACTGetEnvironment(void *a0, void *a1, float *a2, EnvFlag *flags, ActEnv *env)
{
    float prj[4];
    float pos[4];
    float ori[4];
    /* the two GNU nested functions below read the actor parameter and hgt
       through the static chain */
    Act *sub = GOBJ_ACT(a0);
    char *obj = (char *)GOBJ_SUB(a0)->root.wall.o.obj;
    int kind = ((EnvSub *)(char *)GOBJ_SUB(a0))->kind;
    float dist = ((EnvMotion *)(char *)sub->motReq)->wallDist;
    float hgt = -((EnvMotion *)(char *)sub->motReq)->height;
    float wallh = -((EnvSub *)(char *)GOBJ_SUB(a0))->wallTop;
    float hh = ((EnvMotion *)(char *)sub->motReq)->cliffDist;
    float f26 = ((EnvMotion *)(char *)sub->motReq)->cliffDepth;
    int v1D8 = 1;
    int v1DC = 1;
    int v1E0;
    int v1E4 = 0;
    int v1E8 = 0;
    char *w564 = (char *)GOBJ_SUB(a0)->ctrl.wallHit;
    char *w574 = ((EnvSub *)(char *)GOBJ_SUB(a0))->wallRec;
    char *v1EC = 0;
    float k;
    float kk;
    float kd;
    int g;

    inline int CheckWallAttributeNotYorda(int attr, int notYorda) /* derived name */
    {
        int o = (int)a0;

        if (notYorda && o == (int)((char *)girlGObj))
            return 0;
        return CheckWallAttribute(o, attr);
    }

    inline float PosOrFar(void) /* derived name */
    {
        if (hgt < 0.0f)
            return 3.40282347e+38f /* FLT_MAX */;
        return hgt;
    }

    char *o;

    memset(prj, 0, 16);
    if ((char *)GOBJ_SUB(a0)->root.wall.n == 0) {
        w574 = 0;
        w564 = 0;
    }
    if (w574 == 0 && w564 == 0)
        dist = 3.40282347e+38f /* FLT_MAX */;
    if (GOBJ_SUB(a0)->ctrl.cliffEdge == 0)
        hh = 3.40282347e+38f /* FLT_MAX */;
    if ((int)(sub->flags18.ll >> 52) & 1)
        v1D8 = 0;
    if (GOBJ_SUB(a0)->ctrl.groundHeight > _ACTGame_GetParamF(2)) {
        v1D8 = 0;
        v1DC = 0;
    }
    GetRootProjectionPosOfGObj(prj, a0);
    GetRootPosition(pos, a0);
    GetSkeltonOrient(ori, a0, 0x2C);
    env->wallContact = *(ClipCopy *)((char *)GOBJ_SUB(a0) + 0x180);
    sub->flags18.ll &= ~(1ULL << 44);
    sub->flags18.ll &= ~(1ULL << 45);
    sub->flags20.ll &= ~(1ULL << 7);
    sub->flags20.ll &= ~(1ULL << 36);
    *(char *)((char *)GOBJ_ACT(a0)->work + 0x4F0) = 0;
    if ((int)(sub->flags20.ll >> 15) & 1) {
        k = 0.0f;
        v1E0 = 0;
    } else if ((int)(sub->flags20.ll >> 14) & 1) {
        k = 100.0f;
        v1E0 = 0;
    } else {
        k = 300.0f;
        v1E0 = 1;
    }
    if (a0 == ((char *)girlGObj))
        v1E0 = 0;
    {
        float p40[4], p50[4], p60[4], p70[4], p80[4];

        for (o = isysGObjSearchFromObjKindID_begin(0x2C); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (*(int *)(o + 0x16C)) {
                if (GetCageChainPoint((char *)p40, (char *)p50, o)) {
                    if (_DistxzSqGV(test_CURRENTROOT(a0), p40) < 4900.0f && p50[1] > pos[1]) {
                        v1EC = o;
                        env->cageObj = o;
                        break;
                    }
                }
            }
        }
        if (v1EC != 0) {
            GetRootPositionHandExtra(a0, p60);
            GetCageChainPoint((char *)p70, (char *)p80, v1EC);
            if (p70[1] + 50.0f < p60[1])
                flags[0].w |= 0x10000000;
            if (((p60[1] - p70[1]) < 0.0f ? -(p60[1] - p70[1]) : (p60[1] - p70[1])) < 100.0f)
                flags[0].w |= 0x20000000;
            debug_NMarker(p80, 0, 0xFF, 0, 100.0f);
            debug_NMarker(p70, 0, 0, 0xFF, 100.0f);
        }
    }
    if (w564 != 0) {
        if (CheckPureWallAttribute(a0, 0x300) || CheckPureWallAttribute(a0, 0x500) ||
            CheckPureWallAttribute(a0, 0x600))
            hgt = wallh = 3.40282347e+38f /* FLT_MAX */;
    }
    if (GOBJ_SUB(a0)->ctrl.cliffEdge) {
        if (CheckPureCliffAttribute(a0, 0x300) || CheckPureCliffAttribute(a0, 0x500) ||
            CheckPureCliffAttribute(a0, 0x600))
            hh = 3.40282347e+38f /* FLT_MAX */;
    }
    if ((w574 != 0 || w564 != 0) && (char *)GOBJ_SUB(a0)->root.wall.n != 0) {
        GetOrientOfWall(env->wallOrient, (void *)GOBJ_SUB(a0)->root.wall.n,
                        (int *)((char *)GOBJ_SUB(a0) + 0x180));
        env->wallOrient[3] = 1.0f;
        if (w564 != 0) {
            float p60[4];
            int c1 = 1;
            int c2 = 1;
            int r;

            if (ACTGame_FLAG_TETSUNAGI()) {
                if (a0 == boyGObj)
                    c2 = 0;
                if (a0 == ((char *)girlGObj))
                    c1 = 0;
            }
            GetSkeltonOrient(p60, a0, 0x2C);
            r = rotyFromBack(p60, env->wallOrient);
            if (c2 && 30 < r)
                flags[0].w |= 0x20;
            if (c1 && r < -30)
                flags[0].w |= 0x10;
        }
        if (w574 != 0) {
            if (dist < 40.0f && absRotyFromBack(a1, env->wallOrient) < 75)
                flags[0].w |= 2;
            if (dist < k) {
                int ry = absRotyFromBack(a1, env->wallOrient);

                sub->flags18.ll |= (1ULL << 60);
                if (dist < 60.0f && ry < 30)
                    sub->flags18.ll |= (1ULL << 59);
            }
        }
    }
    if (w564 == 0 && GOBJ_SUB(a0)->ctrl.sideWall) {
        if (GOBJ_SUB(a0)->ctrl.sideWallDist < 100.0f) {
            if (absRotyFromBack(a1, (float *)((char *)GOBJ_SUB(a0) + 0x5D0)) < 40) {
                sub->flags18.ll |= (1ULL << 44);
                sub->flags18.ll |= (1ULL << 45);
            }
        }
    }
    if (dist != 3.40282347e+38f /* FLT_MAX */ && w564 != 0 && v1D8) {
        void *ori2 = test_CURRENTORIENT(a0);
        int v1F8;

        v1F8 = absRotyFromBack(ori2, env->wallOrient);
        env->wallWord = *(int *)(*(char **)((char *)env + 0x178) + 0x48);
        w564 = (char *)(CheckPureWallAttribute(a0, 0x1000) & 0xFF);
        env->wallObj = (int)obj;
        flags[0].w |= 1;
        if (hgt < wallh && hgt != -3.40282347e+38f /* -FLT_MAX */)
            hgt = wallh;
        if (dist < k && 40.0f <= PosOrFar())
            sub->flags18.ll |= (1ULL << 60);
        if (dist < 300.0f && PosOrFar() <= 250.0f)
            flags[0].w |= 4;
        if (a0 == ((char *)girlGObj) && dist < 300.0f && *(int *)(obj + 0xC) == 0x11 &&
            IsThisBoxTruck(obj) == 7 && absRotyFromBack(a1, env->wallOrient) < 45 &&
            absRotyFromBack(a2, env->wallOrient) < 45 && _AbsRotyGV(a1, a2) < 45)
            sub->flags20.ll |= (1ULL << 38);
        if (CheckWallAttributeNotYorda(0xB000, 1) || CheckWallAttributeNotYorda(0xE000, 1) ||
            CheckWallAttributeNotYorda(0xC000, 0) || CheckWallAttributeNotYorda(0xD000, 1) ||
            CheckWallAttributeEdegWall((int)a0) || CheckWallAttributeNotYorda(0x3000, 0))
            hgt = wallh;
        if (a0 == ((char *)girlGObj) && CheckPureWallAttribute(a0, 0x7000)) {
            wallh = 3.40282347e+38f /* FLT_MAX */;
            hgt = wallh;
            if (ACTGame_FLAG_TETSUNAGI() &&
                test_CURRENTROOT((girlGObj))[1] >
                    test_CURRENTROOT(boyGObj)[1] + 50.0f) {
                float p60[4], p70[4], p80[4];
                float p90[4][4];

                sceVu0ScaleVector(p60, env->wallOrient, -1.0f);
                GetMatrixDirectionToZ(p90[0], p60);
                sceVu0SubVector(p70, test_CURRENTROOT(boyGObj),
                                test_CURRENTROOT((girlGObj)));
                p70[3] = 0.0f;
                sceVu0ApplyMatrix(p80, p90, p70);
                if (dist < p80[2])
                    sub->flags20.ll |= (1ULL << 19);
            }
        }
        if (stage_no == 16 && dist < 40.0f && 150.0f < (hgt < 0.0f ? -hgt : hgt) &&
            v1F8 < 45 && *(int *)(obj + 0xC) == 0x11)
            sub->flags20.ll |= (1ULL << 39);
        if (dist < 40.0f) {
            sub->flags18.ll |= (1ULL << 44);
            if (136 <= _AbsRotyGV(test_CURRENTORIENT(a0), env))
                sub->flags18.ll |= (1ULL << 45);
        }
        {
            float p60[4];
            int t7 = 90.0f < hgt && hgt < 110.0f && w564 == 0;
            int t3;
            char t16;
            char t17;
            MotionDef *row;

            if (190.0f < hgt && hgt < 210.0f && hgt < 40.0f) {
            }
            row = &motionKind[GOBJ_SUB(a0)->ctrl.motion];
            g = 1;
            if ((row->modeBits.word >> 19) & 7) {
                kk = 60.0f;
            } else if ((row->flags.word >> 28) & 1) {
                kk = 50.0f;
            } else {
                kk = 40.0f;
            }
            if (dist < 120.0f && t7) {
                sceVu0ScaleVector(p60, env->wallOrient, dist);
                sceVu0AddVector((float *)((char *)GOBJ_ACT(a0)->work + 0x840),
                                pos, p60);
                sceVu0ScaleVector((float *)((char *)GOBJ_ACT(a0)->work + 0x850),
                                  env->wallOrient, -1.0f);
                *(float *)((char *)GOBJ_ACT(a0)->work + 0x860) = 40.0f;
                *(int *)((char *)GOBJ_ACT(a0)->work + 0x864) = 20;
                *(int *)((char *)GOBJ_ACT(a0)->work + 0x868) = 1;
                flags[1].w |= 8;
            }
            if (a0 == ((char *)girlGObj) && _ACTCharStatus_Check(a0, 0x1C)) {
                sceVu0SubVector(p60, test_CURRENTROOT((girlGObj)),
                                test_CURRENTROOT(boyGObj));
                p60[1] = 0.0f;
                if (sceVu0InnerProduct(p60, test_CURRENTORIENT(boyGObj)) < 100.0f) {
                    int t = 0;

                    if (*(int *)(obj + 0xC) == 0x11)
                        t = (*(char **)(char *)GOBJ_SUB(boyGObj) != 0 &&
                             obj != *(char **)(char *)GOBJ_SUB(boyGObj));
                    else
                        t = 0;
                    if (!t)
                        g = 0;
                }
            }
            t3 = 10.0f < hgt && hgt < 75.0f && w564 == 0;
            t17 = 75.0f < hgt && hgt < 150.0f && w564 == 0;
            t16 = 150.0f < hgt && hgt < 250.0f;
            if (a0 != boyGObj) {
                if (w564 != 0)
                    t16 = 0;
            } else {
                t17 = 75.0f < hgt && hgt < 120.0f && w564 == 0;
            }
            if (dist < kk && g) {
                if (t3) {
                    if (CheckPureWallAttribute(a0, 0xA00))
                        flags[1].w |= 0x80000;
                    else
                        flags[1].w |= 0x40000;
                }
                if (t17)
                    flags[1].w |= 0x80000;
                if (t16)
                    flags[1].w |= 0x100000;
                if (*(unsigned long long *)((char *)sub + 0x480) & 0x3C0000) {
                    if (((int)(*(unsigned long long *)((char *)sub + 0x480) >> 20) & 1) &&
                        *(int *)(a0 + 0xC) == 4)
                        wallContactPosEnemy(a0, env->wallOrient, dist, (float *)((char *)sub + 0x590));
                    else
                        wallContactPos(a0, env->wallOrient, dist, (float *)((char *)sub + 0x590));
                }
                if (80.0f < hgt && hgt < 180.0f) {
                    if (*(int *)(obj + 0xC) == 0x11)
                        flags[1].w |= 0x800000;
                    else
                        flags[1].w |= 0x400000;
                }
                if (CheckPureWallAttribute(a0, 0x2000) && 80.0f < wallh && wallh < 180.0f)
                    flags[1].w |= 0x40;
            }
            if (dist < 50.0f) {
                if (!((int)(sub->flags20.ll >> 12) & 1) &&
                    *(int *)(obj + 0xC) == 0x10) {
                    float rad = (a0 == boyGObj) ? 30.0f : 10.0f;

                    GetSofaPosition(a0, obj);
                    debug_NMarker(sub->sofaPos, 0, 0xFF, 0, 100.0f);
                    if (_DistxzSqGV(prj, sub->sofaPos) < rad * rad) {
                        flags[1].w |= 0x20;
                        env->sofaObj = (int)obj;
                    }
                }
            }
    if (a0 == boyGObj && dist < 50.0f) {
        if (*(int *)(obj + 0xC) == 0x11 && !CheckPureWallAttribute(a0, 0xB00)) {
            float p70[4];

            flags[2].w |= 0x20;
            env->boxObj = (int)obj;
            if (CanHoldBox(obj) && GetBoxHoldPoint(p70, obj, a0)) {
                flags[2].w |= 0x10;
                env->holdBoxObj = (int)obj;
            }
        }
        if (*(int *)(obj + 0xC) == 0x12 && CheckWallAttribute(a0, 0x700)) {
            flags[2].w |= 0x40;
            env->kind12Obj = (int)obj;
        }
        if (*(int *)(obj + 0xC) == 0x17 && CheckPureWallAttribute(a0, 0x500)) {
            flags[2].w |= 0x80;
            env->pullObj = (int)obj;
            env->pullKind = kind;
            pullPosition(env->pullPos, a0, obj, 5.0f);
        }
        if (*(int *)(obj + 0xC) == 0x16 && CheckWallAttribute(a0, 0x500) &&
            CanFloorLeverPull(obj)) {
            flags[2].w |= 0x100;
            env->pullObj = (int)obj;
            pullPosition(env->pullPos, a0, obj, 45.0f);
            {
                float p70[4];

                sceVu0ScaleVector(p70, env->wallOrient, -10.0f);
                _ApplyRyGV(p70, 1.5707964f);
                sceVu0AddVector(env->pullPos, env->pullPos, p70);
            }
        }
        if (*(int *)(obj + 0xC) == 0x18 && CheckWallAttribute(a0, 0x600) &&
            CanWallLeverPull(obj)) {
            flags[2].w |= 0x200;
            env->pullObj = (int)obj;
            pullPosition(env->pullPos, a0, obj, 30.0f);
        }
        if (*(int *)(obj + 0xC) == 0x19 && CheckWallAttribute(a0, 0x600) &&
            CanWallLeverPull(obj)) {
            flags[2].w |= 0x400;
            env->pullObj = (int)obj;
            pullPosition(env->pullPos, a0, obj, 30.0f);
        }
    }
    if (dist < 200.0f) {
        int b = (dist < 40.0f) ? 1 : 0;

        if (!((stage_no == 86 || stage_no == 3 || stage_no == 46) && *(int *)(a0 + 0xC) == 4) &&
            CheckPureWallAttribute(a0, 0x400)) {
            flags[2].bit.b24 = b;
            flags[2].w |= 0x800000;
            env->edgeOrient[0] = env->wallOrient[0];
            env->edgeOrient[1] = env->wallOrient[1];
            env->edgeOrient[2] = env->wallOrient[2];
            collisCenterOwn(env->edgePos, a0, 0);
            {
                float p70[4];

                sceVu0ScaleVector(p70, env->wallOrient, 30.0f);
                sceVu0AddVector(env->edgePos, env->edgePos, p70);
            }
            env->edgePos[3] = 1.0f;
        }
        if (CheckPureWallAttribute(a0, 0xC000)) {
            flags[2].bit.b18 = b;
            flags[2].w |= 0x20000;
        }
    }
    switch (((int)(&motionKind[GOBJ_SUB(a0)->ctrl.motion])->modeBits.word << 6) >> 30) {
    default:
        kd = 60.0f;
        break;
    case -1:
        if (CheckWallAttributeEdegWall((int)a0)) {
            kd = 30.0f;
        } else {
            kd = GetCorrectDistance(motionKind[GOBJ_SUB(a0)->ctrl.motion].clipRadius + 2.0f,
                                    v1F8);
        }
        kd = (kd < 0.0f) ? 0.0f : ((30.0f < kd) ? 30.0f : kd);
        break;
    case 1:
        kd = 150.0f;
        break;
    }
    if (dist < kd) {
        int c130 = (130.0f <= hgt && hgt < 170.0f);
        char c60a = (60.0f < hgt && hgt < 100.0f);
        int c60b = (60.0f < hgt && hgt < 150.0f);
        int c60c = (60.0f < hgt && hgt < 230.0f);

        if (a0 == ((char *)girlGObj))
            c60a = (60.0f < hgt && hgt < 130.0f);
        if (CheckWallAttribute(a0, 0xB000))
            flags[2].bit.b15 = c60b;
        else if (CheckWallAttribute(a0, 0xE000))
            flags[2].bit.b16 = c60b;
        else if (CheckWallAttribute(a0, 0xD000))
            flags[2].bit.b20 = c60b;
        else if (CheckWallAttributeEdegWall((int)a0)) {
            flags[2].bit.b21 = c60b;
            if (((unsigned int)flags[2].w >> 21) & 1) {
                if (ditchProbe(a0, hgt) == 0)
                    flags[2].w &= ~0x200000;
            }
        }
        else if (CheckWallAttribute(a0, 0x3000))
            flags[2].bit.b22 = c60b;
        else if (GOBJ_SUB(a0)->root.cliffFloor) {
            flags[2].bit.b14 = c60a;
            flags[2].bit.b13 = c130;
            if (debug_no_breast_hang)
                flags[2].bit.b14 = 0;
            if (a0 == boyGObj && *(int *)(obj + 0xC) == 0x2C)
                flags[2].bit.b13 = c60c;
        }
    }
    if (dist < 50.0f && absRotyFromBack(a2, env->wallOrient) < 40 &&
        (a0 == boyGObj || a0 == ((char *)girlGObj) || (130.0f < hgt && *(int *)(obj + 0xC) != 0x10)))
        *(unsigned long long *)((char *)sub + 0x488) |= 8;
    if (((int)(*(unsigned long long *)((char *)sub + 0x488) >> 3) & 1) && 65.0f < PosOrFar() &&
        (float)v1F8 < 30.0f)
        *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 42);
    if (dist < 60.0f) {
        int e = ((float)v1F8 < 30.0f) ? 1 : 0;

        if (*(int *)(obj + 0xC) == 0x36) {
            if (!QueenBarrierInqBreakable())
                *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 63);
        } else
            *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 62);
        if (230.0f < PosOrFar() && !CheckWallAttribute(a0, 0x400) &&
            !CheckWallAttribute(a0, 0x8000) && *(int *)(obj + 0xC) != 0x2C &&
            *(int *)(obj + 0xC) != 0x36) {
            if (e) {
                if (CheckWallAttribute(a0, 0xE000))
                    *(unsigned long long *)((char *)sub + 0x480) |= 1;
                else
                    *(unsigned long long *)((char *)sub + 0x480) |= 2;
            }
        }
    }
    if (*(int *)(a0 + 0xC) == 4 && *(int *)((char *)GOBJ_ACT(a0)->enemy + 0x1E4) == 3 &&
        dist < 180.0f && GOBJ_SUB(a0)->root.cliffFloor) {
        if (40.0f <= hgt && hgt < 300.0f)
            flags[1].w |= 0x8000000;
        else if (300.0f <= hgt && hgt < 500.0f)
            flags[1].w |= 0x10000000;
        else if (500.0f <= hgt && hgt < 700.0f)
            flags[1].w |= 0x20000000;
    }
        }
    }
    if (hh != 3.40282347e+38f /* FLT_MAX */ && GOBJ_SUB(a0)->ctrl.cliffEdge && v1DC) {
        float rr;
        int r;

        GetOrientOfCliffOfGObj(env->cliffOrient, a0);
        env->cliffOrient[3] = 1.0f;
        r = absRotyFromScaled(test_CURRENTORIENT(a0), env->cliffOrient, 1.0f);
        if (a0 == boyGObj && ((char *)girlGObj) != 0) {
            float p60[4];

            p60[0] = test_CURRENTROOT((girlGObj))[0];
            p60[1] = test_CURRENTROOT((girlGObj))[1];
            p60[2] = test_CURRENTROOT((girlGObj))[2];
            if (_DistSqGV(pos, p60) < stageData[stage_no].ledgeRange * stageData[stage_no].ledgeRange) {
                float p70[4][4];
                float pB0[4], pC0[4];

                sceVu0SubVector(pB0, p60, pos);
                GetMatrixDirectionToZ(p70[0], env->cliffOrient);
                pB0[3] = 0.0f;
                sceVu0ApplyMatrix(pC0, p70, pB0);
                if (0.0f < pC0[2])
                    v1E4 = 1;
                if (stage_no == 16)
                    v1E4 = 1;
            }
        }
        if (a0 == boyGObj && hh < 80.0f && ((char *)girlGObj) != 0 &&
            171 <= _AbsRotyGV(test_CURRENTORIENT((girlGObj)), env->cliffOrient)) {
            if (GOBJ_ACT(girlGObj)->actMode == 0x1D &&
                _DistSqGV(pos, test_CURRENTROOT((girlGObj))) < 14400.0f)
                flags[0].w |= 0x4000000;
            if (GOBJ_ACT(girlGObj)->actMode == 0x1C &&
                _DistSqGV(pos, test_CURRENTROOT((girlGObj))) < 40000.0f)
                flags[0].w |= 0x2000000;
        }
        if (hh < 20.0f && 45 < r) {
            if ((int)(sub->flags20.ll >> 42) & 1) {
                SetMotionDirection(a0, env->cliffOrient);
                sub->flags20.ll &= ~(1ULL << 42);
            }
        }
        if (((char *)girlControlMode) != 0 && stage_no == 26 && 3000.0f < pos[2])
            v1E8 = 1;
        if ((v1E8 ? hh < 35.0f : hh < 50.0f) && a0 == ((char *)girlGObj) && boyGObj != 0 &&
            GOBJ_ACT(boyGObj)->actMode == 0x58) {
            float p60[4];

            rr = 400.0f;
            p60[0] = test_CURRENTROOT(boyGObj)[0];
            p60[1] = test_CURRENTROOT(boyGObj)[1];
            p60[2] = test_CURRENTROOT(boyGObj)[2];
            if (_ACTCharStatus_Check(boyGObj, 0x1D))
                rr = 300.0f;
            if (stage_no == 26 && 3000.0f < pos[2] &&
                150.0f < (pos[0] < 0.0f ? -pos[0] : pos[0]))
                rr = 0.0f;
            if (_DistSqGV(p60, pos) < rr * rr &&
                _FrontGV(p60, pos, test_CURRENTORIENT(a0), 45)) {
                _OrientXZGV(GOBJ_WORK(a0)->boyOrient, p60, pos);
                flags[0].w |= 0x800;
            }
        }
        if (sub->actMode == 0x29) {
            if (900.0f < f26)
                flags[1].w |= 0x180;
            else
                flags[1].w |= 0x200;
        }
        if (hh < k && 40.0f <= f26)
            sub->flags18.ll |= (1ULL << 61);
        if (hh < 300.0f && 100.0f <= f26) {
            flags[0].w |= 8;
            env->cliffHeight = hh;
        }
        switch ((unsigned int)sub->actMode) {
        case 2:
            if (hh < 20.0f && 180.0f < f26) {
                if (a0 == boyGObj && 900.0f < f26)
                    flags[3].bit.b1 = v1E0;
                else if (a0 == boyGObj)
                    flags[3].bit.b2 = v1E0;
                else
                    flags[3].bit.b1 = v1E0;
                if (1000.0f < f26)
                    flags[3].w |= 1;
                {
                    float p60[4], p70[4];

                    p60[0] = ((float *)a2)[0];
                    p60[1] = ((float *)a2)[1];
                    p60[2] = ((float *)a2)[2];
                    sceVu0ScaleVector(p60, p60, hh);
                    GetRootPosition(p70, a0);
                    sceVu0AddVector(env->cliffEdgePos, p70, p60);
                    if (5.0f < hh && CheckFloorAttribute(a0, 0xF000) && 20.0f < (float)r) {
                        float d = (15.0f - hh) * 5.0f / 15.0f;
                        float s;
                        float p80[4], p90[4];

                        s = (d < 0.0f) ? 0.0f : ((5.0f < d) ? 5.0f : d);
                        sceVu0ScaleVector(p90, env->cliffOrient, -s);
                        sceVu0AddVector(p80, test_CURRENTROOT(a0), p90);
                        env->cliffBackPos[0] = p80[0];
                        env->cliffBackPos[1] = p80[1];
                        env->cliffBackPos[2] = p80[2];
                        flags[3].w |= 0x4000;
                        flags[3].w &= ~2;
                        flags[3].w &= ~4;
                    }
                }
            }
            break;
        case 116:
            if (hh < 20.0f && 1000.0f < f26)
                flags[2].w |= 0x80000000;
            break;
        /* two identical arms */
        case 1:
            if (hh < 40.0f && 1000.0f < f26)
                flags[2].w |= 0x80000000;
            break;
        case 42:
        case 15:
            if (hh < 40.0f && 1000.0f < f26)
                flags[2].w |= 0x80000000;
            break;
        case 3:
            if (hh < 40.0f && 1000.0f < f26) {
                flags[3].bit.b1 = v1E0;
                flags[2].w |= 0x80000000;
                {
                    float p60[4], p70[4];

                    p60[0] = ((float *)a2)[0];
                    p60[1] = ((float *)a2)[1];
                    p60[2] = ((float *)a2)[2];
                    sceVu0ScaleVector(p60, p60, hh + 10.0f);
                    GetRootPosition(p70, a0);
                    sceVu0AddVector(env->cliffEdgePos, p70, p60);
                    if (5.0f < hh && CheckFloorAttribute(a0, 0xF000) && 20.0f < (float)r) {
                        float d = (25.0f - hh) * 5.0f / 25.0f;
                        float s;
                        float p80[4], p90[4];

                        s = (d < 0.0f) ? 0.0f : ((5.0f < d) ? 5.0f : d);
                        sceVu0ScaleVector(p90, env->cliffOrient, -s);
                        sceVu0AddVector(p80, test_CURRENTROOT(a0), p90);
                        env->cliffBackPos[0] = p80[0];
                        env->cliffBackPos[1] = p80[1];
                        env->cliffBackPos[2] = p80[2];
                        flags[3].w |= 0x4000;
                        flags[3].w &= ~2;
                        flags[2].w &= 0x7FFFFFFF;
                    }
                }
            }
            break;
        }
        if (ACTGame_FLAG_TETSUNAGI() && hh < 40.0f && 1000.0f < f26) {
            env->cliffContact = *(ClipCopy *)((char *)GOBJ_SUB(a0) + 0x180);
            flags[0].w |= 0x8000000;
        }
        if (hh < 40.0f) {
            if (!((stage_no == 86 || stage_no == 3 || stage_no == 46) && *(int *)(a0 + 0xC) == 4) &&
                CheckPureCliffAttribute(a0, 0x400) && 60.0f < f26) {
                env->edgeOrient[0] = env->cliffOrient[0];
                env->edgeOrient[1] = env->cliffOrient[1];
                env->edgeOrient[2] = env->cliffOrient[2];
                flags[2].w |= 0x2000000;
                if (hh < 10.0f && absRotyFromScaled(ori, env->cliffOrient, 1.0f) < 60)
                    flags[2].w |= 0x4000000;
                collisCenterOwn(env->edgePos, a0, 1);
                env->edgePos[3] = 1.0f;
            }
            if (CheckPureCliffAttribute(a0, 0xC000))
                flags[2].w |= 0x80000;
        }
        if (hh < 25.0f && v1E0 &&
            !(((char *)girlGObj) != 0 && GOBJ_ACT(girlGObj)->actMode == 0x6F &&
              (char *)GOBJ_ACT(girlGObj)->carrier == a0)) {
            if (f26 < 55.0f)
                sub->wish1.ll |= (1ULL << 24);
            else if (f26 < 105.0f)
                sub->wish1.ll |= (1ULL << 25);
            else if (f26 < 205.0f)
                sub->wish1.ll |= (1ULL << 26);
        }
        {
        float p60[4], p70[4], p80[4], p90[4], pA0[4], pB0[4];
        float pC0[4][4];
        float p100[4], p110[4], p120[4], p130[4], p140[4], p150[4], p160[4], p170[4];
        float p180[4], p190[4], p1A0[4];
        int sel;
        int v200;
        int v204;
        int v208;
        float lim;
        float hdif;

        if (a0 == boyGObj && ((char *)girlGObj) != 0 &&
            GOBJ_ACT(girlGObj)->actMode != 0x26 && hh < 200.0f &&
            !ACTGame_FLAG_TETSUNAGI() && !CheckPureCliffAttribute(a0, 0x7000) &&
            !CheckPureCliffAttribute(a0, 0x400) &&
            _AbsRotyGV(env->cliffOrient, ori) < 60) {
            v200 = 1;
            hdif = -GetHeightOfFieldPlaneDifference((int *)boyGObj, (int *)((char *)girlGObj));
            if (!(hh < 60.0f))
                v200 = 0;
            v204 = 1;
            sel = 0;
            lim = 3.40282347e+38f /* FLT_MAX */;
            GetRootPosition(p60, boyGObj);
            GetRootPosition(p70, ((char *)girlGObj));
            if (f26 < 55.0f) {
            } else if (f26 < 155.0f) {
                lim = 80.0f;
                sel = 100;
            } else if (f26 < 255.0f) {
                lim = 160.0f;
                sel = 200;
            } else if (f26 < 355.0f) {
                sel = 300;
                lim = 160.0f;
            } else if (f26 < 455.0f) {
                lim = 160.0f;
                sel = 300;
            }
            if (((char *)girlGObj) != 0 && boyGObj != 0 &&
                test_CURRENTROOT((girlGObj))[1] >
                    test_CURRENTROOT(boyGObj)[1] + 800.0f)
                v204 = 0;
            if (stage_no == 7) {
                GetRootProjectionPosOfGObj(p80, (int)((char *)girlGObj));
                if (sel == 200) {
                    if (!(180.0f < p80[1] - prj[1]))
                        v204 = 0;
                    if (prj[0] * p80[0] < 0.0f)
                        v204 = 0;
                }
            }
            if (((int)(GOBJ_ACT(boyGObj)->flags20.ll >> 43) &
                 1) &&
                1600.0f < pos[1] && 200 <= sel)
                sel = 0;
            v208 = (sel < 200);
            if (!v208) {
                pA0[0] = prj[0];
                pA0[1] = prj[1];
                pA0[2] = prj[2];
                sceVu0ScaleVector(p90, env->cliffOrient, hh + 50.0f);
                sceVu0AddVector(pB0, pA0, p90);
                pB0[1] = pB0[1] + f26;
                GetMatrixDirectionToZ(pC0[0], env->cliffOrient);
                for (o = isysGObjSearchFromObjKindID_begin(0x11); o != 0;
                     o = isysGObjSearchFromObjKindID_next(o)) {
                    if (*(int *)(o + 0x16C) && IsThisBoxTruck(o) != 7) {
                        p100[0] = test_CURRENTROOT(o)[0];
                        p100[1] = test_CURRENTROOT(o)[1];
                        p100[2] = test_CURRENTROOT(o)[2];
                        if (_DistxzSqGV(pB0, p100) < 10000.0f &&
                            !(100.0f < ((pB0[1] - p100[1]) < 0.0f ? -(pB0[1] - p100[1])
                                                                  : (pB0[1] - p100[1])))) {
                            sceVu0SubVector(p110, pos, p100);
                            p110[1] = 0.0f;
                            p110[3] = 0.0f;
                            sceVu0ApplyMatrix(p120, pC0, p110);
                            if (!v208) {
                                BOX_SIDE(-70.0f, -60.0f, 40.0f, -1.5707964f, sel == 200 && 200.0f < BOX_DY, 300)
                                else BOX_SIDE(-60.0f, -40.0f, 20.0f, 1.5707964f, sel == 300 && BOX_DY < 300.0f, 200)
                                else BOX_SIDE(40.0f, 60.0f, 35.0f, -1.5707964f, sel == 300 && BOX_DY < 300.0f, 200)
                                else BOX_SIDE(60.0f, 80.0f, 40.0f, 1.5707964f, sel == 200 && 200.0f < BOX_DY, 300)
                            } else if (p120[0] < -30.0f || 40.0f < p120[0]) {
                                v204 = 0;
                                break;
                            }
                        }
                    }
                }
            }
            if (v1E4 == 0)
                v204 = 0;
            if (sel != 0 && lim < hdif && v204) {
                GetRootPosition(p140, a0);
                sceVu0ScaleVector(p130, env->cliffOrient, hh);
                sceVu0AddVector(env->cliffStepPos, p140, p130);
                if (*(unsigned char *)((char *)GOBJ_ACT(a0)->work + 0x4F0))
                    sceVu0AddVector(env->cliffStepPos,
                                    (float *)((char *)GOBJ_ACT(a0)->work + 0x500), p130);
                GetRootPosition(p160, a0);
                sceVu0ScaleVector(p150, env->cliffOrient, hh - 30.0f);
                sceVu0AddVector((float *)((char *)GOBJ_ACT(a0)->work + 0x810), p160, p150);
                *(float *)((char *)GOBJ_ACT(a0)->work + 0x820) = env->cliffOrient[0];
                *(float *)((char *)GOBJ_ACT(a0)->work + 0x824) = env->cliffOrient[1];
                *(float *)((char *)GOBJ_ACT(a0)->work + 0x828) = env->cliffOrient[2];
                *(float *)((char *)GOBJ_ACT(a0)->work + 0x830) = 30.0f;
                *(int *)((char *)GOBJ_ACT(a0)->work + 0x834) = 20;
                *(int *)((char *)GOBJ_ACT(a0)->work + 0x838) = 0;
                sub->wish1.ll |= 4;
                if (v200) {
                    env->cliffSel = sel;
                    switch (sel) {
                    case 100:
                        sub->wish2.ll |= 0x80;
                        break;
                    case 200:
                        sub->wish2.ll |= 0x100;
                        break;
                    case 300:
                        sub->wish2.ll |= 0x200;
                        break;
                    default:
                        debug_assert("src/act-env.c", 2633);
                        __assert("src/act-env.c", 2633, "0");
                        break;
                    }
                }
            }
        }
        if (((char *)girlGObj) != 0 && a0 == boyGObj && hh < 200.0f && 350.0f < f26 &&
            v1E4 && !ACTGame_FLAG_TETSUNAGI() &&
            !(_DistSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj))) <
              10000.0f) &&
            !(((char *)girlGObj) != 0 && boyGObj != 0 &&
              test_CURRENTROOT((girlGObj))[1] >
                  test_CURRENTROOT(boyGObj)[1] + 800.0f) &&
            (GOBJ_ACT(girlGObj)->actMode == 4 ||
             !(_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj))) <
               (hh + 100.0f) * (hh + 100.0f))) &&
            !(_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj))) < 40000.0f &&
              300.0f < GetHeightOfFieldPlaneDifference((int *)((char *)girlGObj), (int *)boyGObj))) {
            _OrientXZGV(p130, test_CURRENTROOT((girlGObj)), test_CURRENTROOT(boyGObj));
            if (_AbsRotyGV(p130, env->cliffOrient) < 80) {
                float *tbl;
                float range;
                int sofa = 0;
                int carry = 0;
                int i;

                getDitchDistTbl(&tbl, &range, &sofa, p160, p170, &carry);
                for (i = 0; 0.0f <= tbl[i]; i++) {
                    if (GetDitchPosition(p140, pos, env->cliffOrient, hh, tbl[i],
                                         range)) {
                        sceVu0ScaleVector(p150, env->cliffOrient, -1.0f);
                        if (sofa) {
                            p140[0] = p160[0];
                            p140[1] = p160[1];
                            p140[2] = p160[2];
                            p150[0] = p170[0];
                            p150[1] = p170[1];
                            p150[2] = p170[2];
                        }
                        if (hh < 60.0f) {
                            *(char *)((char *)sub + 0x530) = *(char *)&carry;
                            env->ditchPos[0] = p140[0];
                            env->ditchPos[1] = p140[1];
                            env->ditchPos[2] = p140[2];
                            env->ditchDir[0] = p150[0];
                            env->ditchDir[1] = p150[1];
                            env->ditchDir[2] = p150[2];
                            sub->wish2.ll |= 0x2000;
                        } else {
                            sceVu0ScaleVector(p180, env->cliffOrient, hh - 30.0f);
                            sceVu0AddVector((float *)((char *)GOBJ_ACT(a0)->work + 0x870), pos,
                                            p180);
                            *(float *)((char *)GOBJ_ACT(a0)->work + 0x880) =
                                env->cliffOrient[0];
                            *(float *)((char *)GOBJ_ACT(a0)->work + 0x884) =
                                env->cliffOrient[1];
                            *(float *)((char *)GOBJ_ACT(a0)->work + 0x888) =
                                env->cliffOrient[2];
                            *(float *)((char *)GOBJ_ACT(a0)->work + 0x890) = 30.0f;
                            *(int *)((char *)GOBJ_ACT(a0)->work + 0x894) = 20;
                            *(int *)((char *)GOBJ_ACT(a0)->work + 0x898) = 0;
                            sub->wish1.ll |= 0x10;
                        }
                        break;
                    }
                }
            }
        }
        if (flags[2].w < 0 ? hh < 40.0f : hh < 30.0f) {
            char *found = 0;

            p140[0] = env->cliffOrient[0];
            p140[1] = env->cliffOrient[1];
            p140[2] = env->cliffOrient[2];
            _ApplyRyGV(p140, 1.5707964f);
            for (o = isysGObjSearchFromObjKindID_begin(0x15); o != 0;
                 o = isysGObjSearchFromObjKindID_next(o)) {
                if (*(int *)(o + 0x16C)) {
                    float d;

                    if (CheckChainClimbablePos(o)) {
                        GetChainClimbOrient(p170, o);
                        if (46 <= _AbsRotyGV(p170, env->cliffOrient))
                            continue;
                    }
                    GetRootPosition(p160, o);
                    sceVu0SubVector(p150, p160, prj);
                    d = sceVu0InnerProduct(p150, p140);
                    if (_DistxzSqGV(prj, p160) < 4900.0f &&
                        ((prj[1] - p160[1]) < 0.0f ? -(prj[1] - p160[1])
                                                   : (prj[1] - p160[1])) < 70.0f &&
                        (d < 0.0f ? -d : d) < 100.0f) {
                        found = o;
                        break;
                    }
                }
            }
            if (v1EC != 0) {
                sceVu0SubVector(p180, test_CURRENTROOT(v1EC), pos);
                p180[1] = 0.0f;
                if (0.0f < sceVu0InnerProduct(p180, env->cliffOrient))
                    found = v1EC;
            }
            if (found != 0) {
                sub->wish1.ll |= (1ULL << 62);
                env->frontObj = found;
                p1A0[0] = test_CURRENTROOT(found)[0];
                p1A0[1] = test_CURRENTROOT(found)[1];
                p1A0[2] = test_CURRENTROOT(found)[2];
                sceVu0ScaleVector(p190, env->cliffOrient, -20.0f);
                *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x1D0) = p1A0[0];
                *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x1D4) = p1A0[1];
                *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x1D8) = p1A0[2];
                sceVu0AddVector((float *)((char *)GOBJ_ACT(a0)->enemy + 0x1C0), p1A0, p190);
                *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x1C4) = pos[1];
            }
        }
        }
    }
    CheckFloorAttribute(a0, 0x200);
    if (a0 == ((char *)girlGObj) && sub->actMode == 0x45) {
        float hd = -GetHeightOfFieldPlaneDifference((int *)boyGObj, a0);

        if (((int)(*(unsigned long long *)((char *)sub + 0x480) >> 18) & 1) && 5.0f < hd) {
            *(unsigned long long *)((char *)sub + 0x488) |= 0x40;
            *(unsigned long long *)((char *)sub + 0x488) |= 0x400;
        }
        if (((int)(*(unsigned long long *)((char *)sub + 0x480) >> 19) & 1) && 60.0f < hd) {
            if (dist < 40.0f)
                sub->flags20.ll |= (1ULL << 36);
            if (GOBJ_ACT(boyGObj)->actMode == 0x37)
                *(unsigned long long *)((char *)sub + 0x488) |= 0x800;
            *(unsigned long long *)((char *)sub + 0x488) |= 0x1000;
        }
        if (((int)(*(unsigned long long *)((char *)sub + 0x480) >> 20) & 1) && 195.0f < hd)
            envDebugPrint();
    }
    /* the loop cursor starts at the actor */
    o = a0;
    if (((char *)girlGObj) != 0) {
        sub->wish0.ll |= (1ULL << 47);
        sub->wish0.ll |= (1ULL << 48);
    }
    if (sub->heldItem.p != 0)
        sub->wish1.ll |= (1ULL << 44);
    if (a0 == boyGObj && sub->actMode != 14) {
        char *w;

        if ((char *)sub->weapon != 0)
            w = CheckSwapableWeapon((char *)sub->weapon, 150.0f);
        else
            w = CheckSwapableWeapon(a0, 150.0f);
        if (w != 0) {
            float p60[4], p70[4];

            env->swapWeapon = w;
            sub->wish0.ll |= (1ULL << 55);
            p60[0] = test_CURRENTROOT(w)[0];
            p60[1] = test_CURRENTROOT(w)[1];
            p60[2] = test_CURRENTROOT(w)[2];
            _OrientXZGV(p70, p60, pos);
            if ((_AbsRotyGV(p70, a2) < 45 && _DistxzSqGV(p60, pos) < 6400.0f) ||
                (45 <= _AbsRotyGV(p70, a2) && _DistxzSqGV(p60, pos) < 900.0f)) {
                sub->wish0.ll |= (1ULL << 54);
                env->swapWeapon = w;
            }
        }
    }
    if ((unsigned int)sub->actMode < 0x3B) {
        if (0x39 <= (unsigned int)sub->actMode) {
        float c0, c4, c8;

        GetChainPendulum((char *)sub->chain, &c0, &c4, &c8);
        if (0.0f < c0)
            *(unsigned long long *)((char *)sub + 0x480) |= (1ULL << 60);
        else
            *(unsigned long long *)((char *)sub + 0x480) |= (1ULL << 61);
        }
    }
    if (a0 == boyGObj && ((char *)girlGObj) != 0 &&
        GOBJ_ACT(girlGObj)->actMode == 0x6F) {
        GObj *h = (char *)GOBJ_ACT(girlGObj)->carrier;

        if (GOBJ_ACT(h)->actMode == 0x67 && GetMotionFrameFlag1(h)) {
            float p60[4], p70[4];

            if (_ACTGame_SearchGObj(a0, (girlGObj), 200.0f, 400.0f, 0x78, p60)) {
                GObj *n = ACTGame_GetNearestGObj(test_CURRENTROOT(h), 0x21);

                p70[0] = test_CURRENTROOT(n)[0];
                p70[1] = test_CURRENTROOT(n)[1];
                p70[2] = test_CURRENTROOT(n)[2];
                if (_DistxzSqGV(pos, p70) < 22500.0f &&
                    ((prj[1] - p70[1]) < 0.0f ? -(prj[1] - p70[1]) : (prj[1] - p70[1])) <
                        50.0f) {
                    sub->wish0.ll |= (1ULL << 56);
                    *(char **)((char *)GOBJ_ACT(a0)->enemy + 0x2E0) = n;
                }
            }
        }
    }
    if (CheckFloorAttribute(a0, 0x800) || CheckFloorAttribute(a0, 0x900))
        *(unsigned long long *)((char *)sub + 0x480) |= (1ULL << 15);
    if (CheckFloorAttribute(a0, 0x800000)) {
        float p60[4];

        sceVu0Normalize(p60, (char *)GOBJ_SUB(a0) + 0x1D0);
        *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x270) = p60[0];
        *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x274) = p60[1];
        *(float *)((char *)GOBJ_ACT(a0)->enemy + 0x278) = p60[2];
        if (0.0f < sceVu0InnerProduct(test_CURRENTORIENT(a0), p60)) {
            sub->wish1.ll |= (1ULL << 16);
            *(char *)((char *)GOBJ_ACT(a0)->enemy + 0x280) = 0;
        } else {
            sub->wish1.ll |= (1ULL << 17);
            *(char *)((char *)GOBJ_ACT(a0)->enemy + 0x280) = 1;
        }
    }
    if (CheckFloorAttribute(a0, 0x50)) {
        sub->wish1.ll |= 0x1000;
        if (GOBJ_SUB(a0)->ctrl.waterDepth > (a0 == boyGObj ? 110.0f : 135.0f)) {
            *(unsigned long long *)((char *)sub + 0x480) |= 0x2000;
            debug_StdPrintfDummy("enter water\n");
        }
        if (GOBJ_SUB(a0)->ctrl.waterDepth < (a0 == boyGObj ? 105.0f : 130.0f)) {
            *(unsigned long long *)((char *)sub + 0x480) |= 0x4000;
            debug_StdPrintfDummy("exit water\n");
        }
    }
    if (a0 == boyGObj) {
        float p70[4];
        char *t30 = 0;
        char *t19 = 0;
        char *t23 = 0;
        char *c;
        int x;
        int n;
        float rad;
        MotionDef *row = &motionKind[GOBJ_SUB(a0)->ctrl.motion];

        rad = ((row->modeBits.word >> 19) & 7) ? 100.0f : 90.0f;
        c = CheckTorchChainReaction(a0, 200.0f);
        if (c != 0) {
            GetRootPosition(p70, c);
            if (_DistxzSqGV(prj, p70) < rad * rad && p70[1] < prj[1] &&
                _FrontGV(p70, prj, test_CURRENTORIENT(a0), 45)) {
                if (((p70[1] - prj[1]) < 0.0f ? -(p70[1] - prj[1]) : (p70[1] - prj[1])) <
                        200.0f &&
                    p70[1] < prj[1]) {
                    _OrientXZGV(env->torchOrient, p70, prj);
                    t23 = c;
                    t30 = t23;
                }
            }
        }
        c = CheckTorchChainReactionReverse(a0, 200.0f);
        if (c != 0) {
            int skip = (*(char **)(char *)GOBJ_SUB(c) != 0 &&
                        *(int *)(*(char **)(char *)GOBJ_SUB(c) + 0xC) == 0x13);

            GetRootPosition(p70, c);
            if (!skip && _DistxzSqGV(prj, p70) < 12100.0f && p70[1] < prj[1] &&
                _FrontGV(p70, prj, test_CURRENTORIENT(a0), 45)) {
                if (((p70[1] - prj[1]) < 0.0f ? -(p70[1] - prj[1]) : (p70[1] - prj[1])) <
                        200.0f &&
                    p70[1] < prj[1]) {
                    _OrientXZGV(env->torchRevOrient, p70, prj);
                    t19 = c;
                    env->torchRevObj = t19;
                }
            }
        }
        if (!ACTGame_NoWeapon(a0)) {
            x = ACTGame_isWeaponEnableCatchfire((int *)sub->weapon);
            if (x != 0) {
                if (!IsTorchLightOn(x)) {
                    if (t30 != 0)
                        *(unsigned long long *)((char *)sub + 0x480) |= (1ULL << 33);
                } else {
                    if (t19 != 0)
                        *(unsigned long long *)((char *)sub + 0x480) |= (1ULL << 35);
                }
            }
        }
        if (sub->heldItem.p != 0) {
            char *b = GetBombTorchGObj(sub->heldItem.p);

            if (t23 != 0 && b != 0 && !IsTorchLightOn(b)) {
                env->bombObj = b;
                sub->wish1.ll |= (1ULL << 34);
            }
        }
        n = 0;
        if (GOBJ_SUB(a0)->ctrl.upperWall) {
            if (GOBJ_SUB(a0)->ctrl.upperWallDist < 50.0f)
                n = 1;
        }
        if (!n)
            sub->wish1.ll |= 0x400;
    }
    if (((unsigned int)flags[2].w >> 5) & 1) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x2C4) = (int)obj;
        GetBoxHoldPoint((float *)((char *)GOBJ_ACT(a0)->enemy + 0x2D0), obj, a0);
    }
}

/* clang-format on */
