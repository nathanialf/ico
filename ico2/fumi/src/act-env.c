#include "typedef.h"
#include "debug.h"
#include <libvu0.h>
#include "act-game.h"
#include "torch.h"
#include "gobj.h"
#include "camera-editor.h"
#include "commonact.h"
#include "motionManager2.h"
#include "debug_exception.h"
#include <assert.h>
#include "chain.h"
#include "geometryManager.h"
#include "cage.h"
#include "box.h"
#include "switch.h"
#include "queen.h"
#include "weapon.h"
#include "item.h"

union ENVIF { /* field names derived */
    int i;
    float f;
}; /* derived name */

/* (this build's act-env.o has no .data: no per-stage ditch tables) */

/* The sofa seat offset in the room's local space, the first object of the
   TU's .rodata. */
static const VECTOR sofaSeatOffset = {30.0f, 0.0f, -50.0f, 0.0f}; /* derived name */

#include "main.h"
#include "act-env.h"
#include "gv.h"
#include "fieldCollision.h"
#include "motionOrientManager.h"

inline void GetSofaPosition(GObj *self, GObj *sofa)
{
    Act *w = GOBJ_ACT(self);
    VECTOR v = sofaSeatOffset;
    w->env.sofaOrient[0] = w->env.wallOrient[0];
    w->env.sofaOrient[1] = w->env.wallOrient[1];
    w->env.sofaOrient[2] = w->env.wallOrient[2];
    if (self == boyGObj) {
        v.x = -v.x;
    }
    v.w = 1.0f;
    sceVu0ApplyMatrix(w->env.sofaPos,
                      *(void **)((char *)((union ENVIF *)((char *)sofa + 0x15C))->i + 0xC), &v);
}

/* PAL's stage-8 ditch carrier position (ditchCarryPos) is not in this
   build's .rodata. */

static inline int getDitchCarryMode(void) /* derived name */
{
    void *a;
    void *b;

    if (boyGObj != 0 && girlGObj != 0) {
        a = *(void **)(char *)GOBJ_SUB(boyGObj);
        b = *(void **)(char *)GOBJ_SUB(girlGObj);

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

/* the floor probe beyond the cliff, d0 + d1 out along dir: three sites with
   the distances 150, 215 and 315 */
static inline unsigned char GetDitchPosition(float *out, float *org, float *dir, float d0, float d1)
{
    ClipWork work;
    float tmp[4];

    sceVu0ScaleVector(tmp, dir, d0 + d1);
    sceVu0AddVector(work.pt[0], org, tmp);
    work.pt[1][0] = work.pt[0][0];
    work.pt[1][1] = work.pt[0][1];
    work.pt[1][2] = work.pt[0][2];
    work.pt[0][1] -= 100.0f;
    work.pt[1][1] += 100.0f;
    ClipFloor(&work);
    if (work.floor.elem != 0) {
        out[0] = work.pt[2][0];
        out[1] = work.pt[2][1];
        out[2] = work.pt[2][2];
        return 1;
    }
    return 0;
}

inline void GetCollisCenterPositionSimple(void *out, void *obj, void *corners)
{
    sceVu0FVECTOR acc;
    char *w;
    int i;
    ((int *)acc)[0] = 0;
    ((int *)acc)[1] = 0;
    ((int *)acc)[2] = 0;
    for (i = 0, w = (char *)corners; i < 4; i++) {
        sceVu0AddVector(acc, acc, (float *)w);
        w += 0x10;
    }
    sceVu0ScaleVector((float *)out, acc, 0.25f);
    if (obj != 0) {
        ((union ENVIF *)((char *)out + 0xC))->f = 1.0f;
        sceVu0ApplyMatrix(out, (void *)GOBJ_SUB(obj)->nodeMtx, out);
    }
}

typedef struct { /* field names derived */
    int on;
    char *name;
} OrientFlagRow; /* derived name */

void DebugActOrientFlag(unsigned int *f)
{
    OrientFlagRow tbl[16] = {
        {(f[1] >> 8) & 1, "climb_50  "},    {(f[1] >> 9) & 1, "climb_100 "},
        {(f[1] >> 10) & 1, "climb_200 "},   {(f[1] >> 11) & 1, "climb_300 "},
        {(f[1] >> 26) & 1, "hold_box  "},   {(f[2] >> 3) & 1, "hang_hand "},
        {(f[2] >> 4) & 1, "hang_breas"},    {(f[2] >> 12) & 1, "ladder_up "},
        {(f[2] >> 13) & 1, "ladder_dow"},   {(f[2] >> 19) & 1, "down_cliff"},
        {(f[2] >> 20) & 1, "walk_wall"},    {(f[2] >> 22) & 1, "walk_stair"},
        {(f[2] >> 23) & 1, "pulledup_50 "}, {(f[2] >> 24) & 1, "pulledup_100"},
        {(f[2] >> 25) & 1, "pulledup_200"}, {-1},
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

inline void ACTSetEnvAllmighty(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    s->wish0.ll |= (1ULL << 37);
    s->wish0.ll |= (1ULL << 38);
    s->wish0.ll |= (1ULL << 39);
    s->wish0.ll |= (1ULL << 40);
    s->wish0.ll |= (1ULL << 42);
    s->wish0.ll |= (1ULL << 43);
    if (ACTGame_FLAG_TETSUNAGI()) {
        s->flags18.ll &= ~(1ULL << 37);
        s->flags20.w.handFreeFrame = 0;
    } else {
        if ((int)(s->flags18.ll >> 37) & 1)
            s->wish0.ll |= (1ULL << 44);
        s->flags20.w.handFreeFrame += 1;
    }
    s->wish0.ll |= (1ULL << 47);
    s->wish0.ll |= (1ULL << 48);
    s->wish0.ll |= (1ULL << 49);
    s->wish0.ll |= (1ULL << 50);
    s->wish0.ll |= (1ULL << 46);
    s->wish1.ll |= (1ULL << 33);
}

inline int CheckWallAttributeEdegWall(GObj *obj);

/* The motion record at actor + 0x130 and the two sub-object words
   ACTGetEnvironment's head reads that Sub15C does not name yet (the wall
   record at 0x574, the wall height at 0x5A4). */
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
    char pad000[1396];
    char *wallRec; /* 0x574 */
    char pad578[44];
    float wallTop; /* 0x5A4 */
} EnvSub;          /* derived name */

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
        GetSkeltonPosition(work.pt[0], o, 0x2C);
        work.pt[1][0] = work.pt[0][0];
        work.pt[1][2] = work.pt[0][2];
        work.pt[1][1] = work.pt[0][1] + 200.0f;
        ClipFloor(&work);
        if (work.floor.elem) {
            y = work.pt[2][1] - work.pt[0][1];
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
        p = *(float **)((char *)((union ENVIF *)((char *)o + 0x15C))->i + 0x178);
    else
        p = *(float **)((char *)((union ENVIF *)((char *)o + 0x15C))->i + 0x188);
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
    sceVu0ScaleVector(t, (float *)(s + 0x4A0), k);
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
        sceVu0ScaleVector(GOBJ_WORK(self)->boxSidePos, env->cliffOrient,                       \
                          (p120[0] < 0.0f ? -p120[0] : p120[0]) - (ofs));                       \
        _ApplyRyGV(GOBJ_WORK(self)->boxSidePos, (ang));                                          \
        sceVu0AddVector(GOBJ_WORK(self)->boxSidePos, pos, GOBJ_WORK(self)->boxSidePos);           \
        GOBJ_WORK(self)->boxSideSet = 1;                                                         \
        if (cond)                                                                                \
            sel = (to);                                                                          \
        break;                                                                                   \
    }

void ACTGetEnvironment(void *self, void *dir, float *orient, EnvFlag *flags, ActEnv *env)
{
    float prj[4];
    float pos[4];
    /* the two GNU nested functions below read the actor parameter and hgt
       through the static chain */
    Act *sub = GOBJ_ACT(self);
    GObj *obj = GOBJ_SUB(self)->root.wall.o.obj;
    GObj *parent = GOBJ_SUB(self)->parent.obj;
    float dist = ((EnvMotion *)(char *)sub->motReq)->wallDist;
    float hgt = -((EnvMotion *)(char *)sub->motReq)->height;
    float wallh = -GOBJ_SUB(self)->ctrl.wallTopHeight;
    float hh = ((EnvMotion *)(char *)sub->motReq)->cliffDist;
    float f26 = ((EnvMotion *)(char *)sub->motReq)->cliffDepth;
    int v1D8 = 1;
    int v1DC = 1;
    int v1E0;
    char *wallHit = (char *)GOBJ_SUB(self)->ctrl.wallHit;
    char *fieldWallHit = (char *)GOBJ_SUB(self)->ctrl.fieldWallHit;
    GObj *v1EC = 0;
    float k;
    float kk;
    float kd;
    int g;

    inline int CheckWallAttributeNotYorda(int attr, int notYorda) /* derived name */
    {
        GObj *o = self;

        if (notYorda && o == girlGObj)
            return 0;
        return CheckWallAttribute(o, attr);
    }

    inline float PosOrFar(void) /* derived name */
    {
        if (hgt < 0.0f)
            return 3.40282347e+38f /* FLT_MAX */;
        return hgt;
    }

    GObj *o;

    memset(prj, 0, 16);
    if ((char *)GOBJ_SUB(self)->root.wall.elem == 0) {
        fieldWallHit = 0;
        wallHit = 0;
    }
    if (fieldWallHit == 0 && wallHit == 0)
        dist = 3.40282347e+38f /* FLT_MAX */;
    if (GOBJ_SUB(self)->ctrl.cliffEdge == 0)
        hh = 3.40282347e+38f /* FLT_MAX */;
    if ((int)(sub->flags18.ll >> 46) & 1)
        v1D8 = 0;
    if (GOBJ_SUB(self)->ctrl.groundHeight > _ACTGame_GetParamF(1)) {
        v1D8 = 0;
        v1DC = 0;
    }
    GetRootProjectionPosOfGObj(prj, self);
    GetRootPosition(pos, self);
    env->motOriReq = *(MotOriReq *)&GOBJ_SUB(self)->root.wall;
    sub->flags18.ll &= ~(1ULL << 38);
    sub->flags18.ll &= ~(1ULL << 39);
    sub->flags18.ll &= ~(1ULL << 59);
    if ((int)sub->flags20.ll & 1) {
        k = 100.0f;
        v1E0 = 0;
    } else {
        k = 300.0f;
        v1E0 = 1;
    }
    if (self == girlGObj)
        v1E0 = 0;
    {
        float p40[4], p50[4], p60[4], p70[4], p80[4];

        for (o = isysGObjSearchFromObjKindID_begin(42); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (o->active) {
                GetCageChainPoint(p40, p50, o);
                if (_DistxzSqGV(test_CURRENTROOT(self), p40) < 4900.0f && p50[1] > pos[1]) {
                    v1EC = o;
                    env->cageObj.obj = o;
                    break;
                }
            }
        }
        if (v1EC != 0) {
            GetRootPositionHandExtra(self, p60);
            GetCageChainPoint(p70, p80, v1EC);
            if (p70[1] + 50.0f < p60[1])
                flags[0].w |= 0x800000;
            if (((p60[1] - p70[1]) < 0.0f ? -(p60[1] - p70[1]) : (p60[1] - p70[1])) < 100.0f)
                flags[0].w |= 0x1000000;
            debug_NMarker(p80, 0, 0xFF, 0, 100.0f);
            debug_NMarker(p70, 0, 0, 0xFF, 100.0f);
        }
    }
    if (wallHit != 0) {
        if (CheckPureWallAttribute(self, 0x300))
            hgt = wallh = 3.40282347e+38f /* FLT_MAX */;
    }
    if (GOBJ_SUB(self)->ctrl.cliffEdge) {
        if (CheckPureCliffAttribute(self, 0x300))
            hh = 3.40282347e+38f /* FLT_MAX */;
    }
    if ((fieldWallHit != 0 || wallHit != 0) && (char *)GOBJ_SUB(self)->root.wall.elem != 0) {
        GetOrientOfWall(env->wallOrient, GOBJ_SUB(self)->root.wall.elem, &GOBJ_SUB(self)->root.wall.o);
        env->wallOrient[3] = 1.0f;
        if (wallHit != 0) {
            float p60[4];
            int c1 = 1;
            int c2 = 1;
            int r;

            if (ACTGame_FLAG_TETSUNAGI()) {
                if (self == boyGObj)
                    c2 = 0;
                if (self == girlGObj)
                    c1 = 0;
            }
            GetSkeltonOrient(p60, self, 44);
            r = rotyFromBack(p60, env->wallOrient);
            if (c2 && 30 < r)
                flags[0].w |= 0x10;
            if (c1 && r < -30)
                flags[0].w |= 8;
        }
        if (fieldWallHit != 0) {
            if (dist < k) {
                int ry = absRotyFromBack(dir, env->wallOrient);

                sub->flags18.ll |= (1ULL << 49);
                if (dist < 60.0f && ry < 30)
                    sub->flags18.ll |= (1ULL << 48);
            }
        }
    }
    if (wallHit == 0 && GOBJ_SUB(self)->ctrl.sideWall) {
        if (GOBJ_SUB(self)->ctrl.sideWallDist < 100.0f) {
            if (absRotyFromBack(dir, GOBJ_SUB(self)->ctrl.sideWallNormal) < 40) {
                sub->flags18.ll |= (1ULL << 38);
                sub->flags18.ll |= (1ULL << 39);
            }
        }
    }
    if (dist != 3.40282347e+38f /* FLT_MAX */ && wallHit != 0 && v1D8) {
        void *ori2 = test_CURRENTORIENT(self);
        int wallDeg;

        wallDeg = absRotyFromBack(ori2, env->wallOrient);
        env->wallWord = ((FcWallEnt *)env->motOriReq.a.wall.elem)->attr;
        env->wallObj = obj;
        flags[0].w |= 1;
        if (hgt < wallh && hgt != -3.40282347e+38f /* -FLT_MAX */)
            hgt = wallh;
        if (dist < k && 40.0f <= PosOrFar())
            sub->flags18.ll |= (1ULL << 49);
        if (dist < 300.0f && PosOrFar() <= 250.0f)
            flags[0].w |= 2;
        if (CheckWallAttributeNotYorda(0xB000, 1) || CheckWallAttributeNotYorda(0xE000, 1) ||
            CheckWallAttributeNotYorda(0xC000, 0) || CheckWallAttributeNotYorda(0xD000, 1) ||
            CheckWallAttributeNotYorda(0x1000, 1) || CheckWallAttributeNotYorda(0x3000, 0))
            hgt = wallh;
        if (self == girlGObj && CheckPureWallAttribute(self, 0x7000)) {
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
                    sub->flags20.ll |= (1ULL << 3);
            }
        }
        sub->envWallHeight = hgt;
        sub->envWallAttr = ((Sub15C *)((union ENVIF *)((char *)self + 0x15C))->i)->ctrl.wallAttr;
        if (dist < 40.0f) {
            sub->flags18.ll |= (1ULL << 38);
            if (136 <= _AbsRotyGV(test_CURRENTORIENT(self), env))
                sub->flags18.ll |= (1ULL << 39);
        }
        {
            float p60[4];
            int t7 = 90.0f < hgt && hgt < 110.0f;
            int t3;
            char t16;
            char t17;
            MotionDef *row;

            row = &motionKind[GOBJ_SUB(self)->ctrl.motion];
            g = 1;
            if ((row->modeBits.word >> 16) & 7) {
                kk = 60.0f;
            } else if ((row->flags.word >> 16) & 1) {
                kk = 50.0f;
            } else {
                kk = 40.0f;
            }
            if (dist < 120.0f && t7) {
                sceVu0ScaleVector(p60, env->wallOrient, dist);
                sceVu0AddVector((float *)((char *)GOBJ_ACT(self)->enemy + 0x360),
                                pos, p60);
                sceVu0ScaleVector((float *)((char *)GOBJ_ACT(self)->enemy + 0x370),
                                  env->wallOrient, -1.0f);
                *(float *)((char *)GOBJ_ACT(self)->enemy + 0x380) = 40.0f;
                *(int *)((char *)GOBJ_ACT(self)->enemy + 0x384) = 20;
                *(int *)((char *)GOBJ_ACT(self)->enemy + 0x388) = 1;
                flags[0].w |= 0x20000000;
            }
            if (self == girlGObj && _ACTCharStatus_Check(self, 24)) {
                sceVu0SubVector(p60, test_CURRENTROOT((girlGObj)),
                                test_CURRENTROOT(boyGObj));
                p60[1] = 0.0f;
                if (sceVu0InnerProduct(p60, test_CURRENTORIENT(boyGObj)) < 100.0f) {
                    int t = 0;

                    if (obj->kind == 17)
                        t = (GOBJ_SUB(boyGObj)->parent.obj != 0 &&
                             obj != GOBJ_SUB(boyGObj)->parent.obj);
                    else
                        t = 0;
                    if (!t)
                        g = 0;
                }
            }
            t3 = 10.0f < hgt && hgt < 75.0f;
            t17 = 75.0f < hgt && hgt < 150.0f;
            t16 = 150.0f < hgt && hgt < 250.0f;
            if (dist < kk && g) {
                if (t3) {
                    if (CheckPureWallAttribute(self, 0xA00))
                        flags[1].w |= 0x200;
                    else
                        flags[1].w |= 0x100;
                }
                if (t17)
                    flags[1].w |= 0x200;
                if (t16)
                    flags[1].w |= 0x400;
                if (*(unsigned long long *)((char *)sub + 0x478) & 0xF00) {
                    if (((int)(*(unsigned long long *)((char *)sub + 0x478) >> 10) & 1) &&
                        *(int *)(self + 0xC) == 4)
                        wallContactPosEnemy(self, env->wallOrient, dist, sub->env.wallPos);
                    else
                        wallContactPos(self, env->wallOrient, dist, sub->env.wallPos);
                }
                if (80.0f < hgt && hgt < 180.0f) {
                    if (obj->kind == 17)
                        flags[1].w |= 0x2000;
                    else
                        flags[1].w |= 0x1000;
                }
                if (CheckPureWallAttribute(self, 0x2000) && 80.0f < wallh && wallh < 180.0f)
                    flags[0].w |= 0x80000000;
            }
            if (dist < 50.0f) {
                if (obj->kind == 16) {
                    GetSofaPosition(self, obj);
                    debug_NMarker(sub->env.sofaPos, 0, 0xFF, 0, 100.0f);
                    if (_DistxzSqGV(prj, sub->env.sofaPos) < 900.0f) {
                        flags[0].w |= 0x40000000;
                        env->sofaObj.i = (int)obj;
                    }
                }
        if (obj->kind == 17 && IsThisBoxTruck(obj) != 7 && !CheckWallAttribute(self, 0xB00)) {
            float p70[4];

            flags[1].w |= 0x8000000;
            env->boxObj = obj;
            if (CanHoldBox(obj) && GetBoxHoldPoint(p70, obj, self)) {
                flags[1].w |= 0x4000000;
                env->holdBoxObj = obj;
            }
        }
        if (obj->kind == 18 && CheckWallAttribute(self, 0x700)) {
            flags[1].w |= 0x10000000;
            env->barObj = obj;
        }
        if (obj->kind == 23 && CheckPureWallAttribute(self, 0x500)) {
            flags[1].w |= 0x20000000;
            env->pullParent = parent;
            env->pullObj = obj;
            pullPosition(env->pullPos, self, obj, 5.0f);
        }
        if (obj->kind == 22 && CheckWallAttribute(self, 0x500) &&
            CanFloorLeverPull(obj)) {
            flags[1].w |= 0x40000000;
            env->pullObj = obj;
            pullPosition(env->pullPos, self, obj, 5.0f);
        }
        if (obj->kind == 24 && CheckWallAttribute(self, 0x600) &&
            CanWallLeverPull(obj)) {
            flags[1].w |= 0x80000000;
            env->pullObj = obj;
            pullPosition(env->pullPos, self, obj, 30.0f);
        }
        if (obj->kind == 25 && CheckWallAttribute(self, 0x600) &&
            CanWallLeverPull(obj)) {
            flags[2].w |= 1;
            env->pullObj = obj;
            pullPosition(env->pullPos, self, obj, 30.0f);
        }
    }
    if (dist < 40.0f) {
        if (CheckWallAttribute(self, 0x400) || CheckPureWallAttribute(self, 0x400)) {
            flags[2].w |= 0x1000;
            env->edgeOrient[0] = env->wallOrient[0];
            env->edgeOrient[1] = env->wallOrient[1];
            env->edgeOrient[2] = env->wallOrient[2];
            collisCenterOwn(env->edgePos, self, 0);
            {
                float p70[4];

                sceVu0ScaleVector(p70, env->wallOrient, 30.0f);
                sceVu0AddVector(env->edgePos, env->edgePos, p70);
            }
            env->edgePos[3] = 1.0f;
        }
        if (CheckWallAttribute(self, 0xC000)) {
            flags[2].w |= 0x80;
        }
    }
    switch (((int)(&motionKind[GOBJ_SUB(self)->ctrl.motion])->modeBits.word << 11) >> 30) {
    default:
        kd = 60.0f;
        break;
    case -1:
        if (CheckWallAttributeNotYorda(0x1000, 1)) {
            kd = 30.0f;
        } else {
            kd = GetCorrectDistance(wallDeg, motionKind[GOBJ_SUB(self)->ctrl.motion].clipRadius + 2.0f);
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

        if (CheckWallAttribute(self, 0xB000))
            flags[2].bit.b5 = c60b;
        else if (CheckWallAttribute(self, 0xE000))
            flags[2].bit.b6 = c60b;
        else if (CheckWallAttribute(self, 0xD000))
            flags[2].bit.b9 = c60b;
        else if (CheckWallAttribute(self, 0x1000))
            flags[2].bit.b10 = c60b;
        else if (CheckWallAttribute(self, 0x3000))
            flags[2].bit.b11 = c60b;
        else if (GOBJ_SUB(self)->root.cliffFloor) {
            flags[2].bit.b4 = c60a;
            flags[2].bit.b3 = c130;
            if (obj->kind == 42)
                flags[2].bit.b3 = c60c;
        }
    }
    if (dist < 50.0f && absRotyFromBack(orient, env->wallOrient) < 40 &&
        (self == boyGObj || (130.0f < hgt && obj->kind != 16)))
        *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 52);
    if (((int)(*(unsigned long long *)((char *)sub + 0x478) >> 52) & 1) && 65.0f < PosOrFar() &&
        (float)wallDeg < 30.0f)
        *(unsigned long long *)((char *)sub + 0x470) |= (1ULL << 41);
    if (dist < 60.0f) {
        int e = ((float)wallDeg < 30.0f) ? 1 : 0;

        if (obj->kind == 52) {
            if (!QueenBarrierInqBreakable())
                *(unsigned long long *)((char *)sub + 0x470) |= (1ULL << 58);
        } else
            *(unsigned long long *)((char *)sub + 0x470) |= (1ULL << 57);
        if (230.0f < PosOrFar() && !CheckWallAttribute(self, 0x400)) {
            if (e)
                *(unsigned long long *)((char *)sub + 0x470) |= (1ULL << 59);
        }
    }
    if (*(int *)(self + 0xC) == 4 && *(int *)((char *)GOBJ_ACT(self)->enemy + 0x1DC) == 3 &&
        dist < 180.0f && GOBJ_SUB(self)->root.cliffFloor) {
        if (40.0f <= hgt && hgt < 300.0f)
            flags[1].w |= 0x20000;
        else if (300.0f <= hgt && hgt < 500.0f)
            flags[1].w |= 0x40000;
        else if (500.0f <= hgt && hgt < 700.0f)
            flags[1].w |= 0x80000;
    }
        }
    }
    if (hh != 3.40282347e+38f /* FLT_MAX */ && GOBJ_SUB(self)->ctrl.cliffEdge && v1DC) {
        int r;

        GetOrientOfCliffOfGObj(env->cliffOrient, self);
        env->cliffOrient[3] = 1.0f;
        r = absRotyFromScaled(test_CURRENTORIENT(self), env->cliffOrient, 1.0f);
        if (sub->actMode == 41)
            flags[1].w |= 1;
        if (hh < k && 40.0f <= f26)
            sub->flags18.ll |= (1ULL << 50);
        if (hh < 300.0f && 100.0f <= f26) {
            flags[0].w |= 4;
            env->cliffHeight = hh;
        }
        switch ((unsigned int)sub->actMode) {
        case 2:
            if (hh < 20.0f && 180.0f < f26) {
                flags[2].bit.b19 = v1E0;
                {
                    float p60[4], p70[4];

                    p60[0] = ((float *)orient)[0];
                    p60[1] = ((float *)orient)[1];
                    p60[2] = ((float *)orient)[2];
                    sceVu0ScaleVector(p60, p60, hh);
                    GetRootPosition(p70, self);
                    sceVu0AddVector(env->cliffEdgePos, p70, p60);
                    if (5.0f < hh && CheckFloorAttribute(self, 0xF000) && 20.0f < (float)r) {
                        float d = (15.0f - hh) * 5.0f / 15.0f;
                        float s;
                        float p80[4], p90[4];

                        s = (d < 0.0f) ? 0.0f : ((5.0f < d) ? 5.0f : d);
                        sceVu0ScaleVector(p90, env->cliffOrient, -s);
                        sceVu0AddVector(p80, test_CURRENTROOT(self), p90);
                        env->cliffBackPos[0] = p80[0];
                        env->cliffBackPos[1] = p80[1];
                        env->cliffBackPos[2] = p80[2];
                        flags[2].w |= 0x40000000;
                        flags[2].w &= ~0x80000;
                    }
                }
            }
            break;
        case 1:
        case 42:
        case 15:
            if (hh < 40.0f && 1000.0f < f26)
                flags[2].w |= 0x40000;
            break;
        case 3:
            if (hh < 40.0f && 1000.0f < f26) {
                flags[2].bit.b19 = v1E0;
                flags[2].w |= 0x40000;
                {
                    float p60[4], p70[4];

                    p60[0] = ((float *)orient)[0];
                    p60[1] = ((float *)orient)[1];
                    p60[2] = ((float *)orient)[2];
                    sceVu0ScaleVector(p60, p60, hh + 10.0f);
                    GetRootPosition(p70, self);
                    sceVu0AddVector(env->cliffEdgePos, p70, p60);
                    if (5.0f < hh && CheckFloorAttribute(self, 0xF000) && 20.0f < (float)r) {
                        float d = (25.0f - hh) * 5.0f / 25.0f;
                        float s;
                        float p80[4], p90[4];

                        s = (d < 0.0f) ? 0.0f : ((5.0f < d) ? 5.0f : d);
                        sceVu0ScaleVector(p90, env->cliffOrient, -s);
                        sceVu0AddVector(p80, test_CURRENTROOT(self), p90);
                        env->cliffBackPos[0] = p80[0];
                        env->cliffBackPos[1] = p80[1];
                        env->cliffBackPos[2] = p80[2];
                        flags[2].w |= 0x40000000;
                        flags[2].w &= ~0x80000;
                        flags[2].w &= ~0x40000;
                    }
                }
            }
            break;
        }
        if (ACTGame_FLAG_TETSUNAGI() && hh < 40.0f && 1000.0f < f26) {
            env->cliffContact = *(MotOriReq *)&GOBJ_SUB(self)->root.wall;
            flags[0].w |= 0x400000;
        }
        if (hh < 40.0f) {
            if (CheckPureCliffAttribute(self, 0x400) && 60.0f < f26) {
                env->edgeOrient[0] = env->cliffOrient[0];
                env->edgeOrient[1] = env->cliffOrient[1];
                env->edgeOrient[2] = env->cliffOrient[2];
                flags[2].w |= 0x2000;
                collisCenterOwn(env->edgePos, self, 1);
                env->edgePos[3] = 1.0f;
            }
            if (CheckPureCliffAttribute(self, 0xC000))
                flags[2].w |= 0x100;
        }
        if (hh < 25.0f && v1E0) {
            if (f26 < 55.0f)
                sub->wish1.ll |= (1ULL << 14);
            else if (f26 < 105.0f)
                sub->wish1.ll |= (1ULL << 15);
            else if (f26 < 205.0f)
                sub->wish1.ll |= (1ULL << 16);
        }

        {
        float p60[4], p70[4], p80[4], p90[4];
        int sel;
        int v200;
        int v204;
        float lim;
        float hdif;

        if (girlGObj != 0 && self == boyGObj && hh < 200.0f &&
            !ACTGame_FLAG_TETSUNAGI() && !CheckPureCliffAttribute(self, 0x7000) &&
            !CheckPureCliffAttribute(self, 0x400)) {
            float pA0[4], pB0[4];
            float pC0[4][4];
            float p100[4], p110[4], p120[4], p130[4], p140[4], p150[4], p160[4], p170[4];

            v200 = 1;
            hdif = -GetHeightOfFieldPlaneDifference(boyGObj, girlGObj);
            if (!(hh < 60.0f))
                v200 = 0;
            v204 = 1;
            sel = 0;
            lim = 3.40282347e+38f /* FLT_MAX */;
            GetRootPosition(p60, boyGObj);
            GetRootPosition(p70, girlGObj);
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
            }
            if (stage_no == 7) {
                GetRootProjectionPosOfGObj(p80, girlGObj);
                if (sel == 200) {
                    if (!(180.0f < p80[1] - prj[1]))
                        v204 = 0;
                    if (prj[0] * p80[0] < 0.0f)
                        v204 = 0;
                }
            }
            /* the low-step flag is declared once the root positions are
               taken: the demo's spill slots run v200, v204, &p60, v208 (aug6
               keeps the same order), so v208's register is numbered after
               the &p60 argument's; the block's spelling is not pinned */
            {
            int v208 = (sel < 200);

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
                    if (o->active && IsThisBoxTruck(o) != 7) {
                        p100[0] = test_CURRENTROOT(o)[0];
                        p100[1] = test_CURRENTROOT(o)[1];
                        p100[2] = test_CURRENTROOT(o)[2];
                        if (_DistxzSqGV(pB0, p100) < 10000.0f &&
                            !(100.0f < ((pB0[1] - p100[1]) < 0.0f ? -(pB0[1] - p100[1])
                                                                  : (pB0[1] - p100[1])))) {
                            sceVu0SubVector(p110, pos, p100);
                            p110[3] = 0.0f;
                            sceVu0ApplyMatrix(p120, pC0, p110);
                            if (p120[0] < -30.0f || 40.0f < p120[0]) {
                                v204 = 0;
                                break;
                            }
                        }
                    }
                }
            }
            if (sel != 0 && lim < hdif && _DistxzSqGV(p60, p70) < 2250000.0f && v204) {
                GetRootPosition(p140, self);
                sceVu0ScaleVector(p130, env->cliffOrient, hh);
                sceVu0AddVector(env->cliffStepPos, p140, p130);
                GetRootPosition(p160, self);
                sceVu0ScaleVector(p150, env->cliffOrient, hh - 30.0f);
                sceVu0AddVector((float *)((char *)GOBJ_ACT(self)->enemy + 0x330), p160, p150);
                *(float *)((char *)GOBJ_ACT(self)->enemy + 0x340) = env->cliffOrient[0];
                *(float *)((char *)GOBJ_ACT(self)->enemy + 0x344) = env->cliffOrient[1];
                *(float *)((char *)GOBJ_ACT(self)->enemy + 0x348) = env->cliffOrient[2];
                *(float *)((char *)GOBJ_ACT(self)->enemy + 0x350) = 30.0f;
                *(int *)((char *)GOBJ_ACT(self)->enemy + 0x354) = 20;
                *(int *)((char *)GOBJ_ACT(self)->enemy + 0x358) = 0;
                sub->wish0.ll |= (1ULL << 60);
                if (v200) {
                    if (stage_no == 97) {
                        GObj *box = isysGObjSearchFromObjKindID_begin(17);

                        if (box != 0 &&
                            _DistxzSqGV(test_CURRENTROOT(box), test_CURRENTROOT(self)) < 22500.0f &&
                            !v208 && sel <= 300 &&
                            test_CURRENTROOT(box)[1] > test_CURRENTROOT(self)[1] &&
                            100.0f < ((test_CURRENTROOT(box)[1] - test_CURRENTROOT(self)[1]) < 0.0f
                                          ? -(test_CURRENTROOT(box)[1] - test_CURRENTROOT(self)[1])
                                          : (test_CURRENTROOT(box)[1] - test_CURRENTROOT(self)[1]))) {
                            sceVu0ScaleVector(p170, env->cliffOrient, -50.0f);
                            sel = 200;
                            sceVu0AddVector(env->cliffStepPos, test_CURRENTROOT(box), p170);
                        }
                        env->cliffSel = sel;
                    } else
                        env->cliffSel = sel; /* stored on both paths: the words keep
                                                one store (jump2 cross-jumps them),
                                                the allocator counts both and sorts
                                                env ahead of the front search's
                                                &p90; spelling not pinned */
                    switch (sel) {
                    case 100:
                        sub->wish1.ll |= (1ULL << 56);
                        break;
                    case 200:
                        sub->wish1.ll |= (1ULL << 57);
                        break;
                    case 300:
                        sub->wish1.ll |= (1ULL << 58);
                        break;
                    default:
                        debug_assert("src/act-env.c", 1972);
                        __assert("src/act-env.c", 1972, "0");
                        break;
                    }
                }
            }
            }
        }
        if (girlGObj != 0 && self == boyGObj && hh < 80.0f && 350.0f < f26 &&
            !ACTGame_FLAG_TETSUNAGI() &&
            !(_DistSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj))) <
              10000.0f) &&
            (GOBJ_ACT(girlGObj)->actMode == 4 ||
             !(_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj))) <
               (hh + 100.0f) * (hh + 100.0f))) &&
            !(_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj))) < 40000.0f &&
              300.0f < GetHeightOfFieldPlaneDifference(girlGObj, boyGObj))) {
            _OrientXZGV(p80, test_CURRENTROOT((girlGObj)), test_CURRENTROOT(boyGObj));
            if (_AbsRotyGV(p80, env->cliffOrient) < 80) {
                if (GetDitchPosition(p90, pos, env->cliffOrient, hh, 150.0f) ||
                    GetDitchPosition(p90, pos, env->cliffOrient, hh, 215.0f) ||
                    GetDitchPosition(p90, pos, env->cliffOrient, hh, 315.0f)) {
                    env->ditchPos[0] = p90[0];
                    env->ditchPos[1] = p90[1];
                    env->ditchPos[2] = p90[2];
                    sub->wish1.ll |= (1ULL << 61);
                }
            }
        }
        if (hh < 30.0f) {
            GObj *found = 0;
            float p150[4], p160[4], p180[4], p190[4], p1A0[4];

            p90[0] = env->cliffOrient[0];
            p90[1] = env->cliffOrient[1];
            p90[2] = env->cliffOrient[2];
            _ApplyRyGV(p90, 1.5707964f);
            for (o = isysGObjSearchFromObjKindID_begin(0x15); o != 0;
                 o = isysGObjSearchFromObjKindID_next(o)) {
                float d;

                GetRootPosition(p160, o);
                sceVu0SubVector(p150, p160, prj);
                d = sceVu0InnerProduct(p150, p90);
                if (_DistSqGV(prj, p160) < 4900.0f && (d < 0.0f ? -d : d) < 30.0f) {
                    found = o;
                    break;
                }
            }
            if (v1EC != 0) {
                sceVu0SubVector(p180, test_CURRENTROOT(v1EC), pos);
                p180[1] = 0.0f;
                if (0.0f < sceVu0InnerProduct(p180, env->cliffOrient))
                    found = v1EC;
            }
            if (found != 0) {
                sub->wish1.ll |= (1ULL << 49);
                env->frontObj = found;
                p1A0[0] = test_CURRENTROOT(found)[0];
                p1A0[1] = test_CURRENTROOT(found)[1];
                p1A0[2] = test_CURRENTROOT(found)[2];
                sceVu0ScaleVector(p190, env->cliffOrient, -20.0f);
                sceVu0AddVector((float *)((char *)GOBJ_ACT(self)->enemy + 0x1C0), p1A0, p190);
                *(float *)((char *)GOBJ_ACT(self)->enemy + 0x1C4) = pos[1];
            }
        }
        }
    }
    CheckFloorAttribute(self, 0x200);
    if (self == girlGObj && sub->actMode == 68) {
        float hd = -GetHeightOfFieldPlaneDifference(boyGObj, self);

        if (((int)(*(unsigned long long *)((char *)sub + 0x478) >> 8) & 1) && 5.0f < hd) {
            *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 55);
            *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 59);
        }
        if (((int)(*(unsigned long long *)((char *)sub + 0x478) >> 9) & 1) && 60.0f < hd) {
            if (GOBJ_ACT(boyGObj)->actMode == 55)
                *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 60);
        }
        if (((int)(*(unsigned long long *)((char *)sub + 0x478) >> 10) & 1) && 195.0f < hd)
            envDebugPrint();
    }
    /* the loop cursor starts at the actor */
    o = self;
    if (girlGObj != 0) {
        sub->wish0.ll |= (1ULL << 45);
    }
    if (sub->heldItem.p != 0)
        sub->wish1.ll |= (1ULL << 34);
    if (self == boyGObj && sub->actMode != 14) {
        GObj *w;

        if (sub->weapon != 0)
            w = CheckSwapableWeapon(sub->weapon, 150.0f);
        else
            w = CheckSwapableWeapon(self, 150.0f);
        if (w != 0) {
            float p60[4], p70[4];

            env->swapWeapon = w;
            sub->wish0.ll |= (1ULL << 52);
            p60[0] = test_CURRENTROOT(w)[0];
            p60[1] = test_CURRENTROOT(w)[1];
            p60[2] = test_CURRENTROOT(w)[2];
            _OrientXZGV(p70, p60, pos);
            if ((_AbsRotyGV(p70, orient) < 45 && _DistxzSqGV(p60, pos) < 6400.0f) ||
                (45 <= _AbsRotyGV(p70, orient) && _DistxzSqGV(p60, pos) < 900.0f)) {
                sub->wish0.ll |= (1ULL << 51);
                env->swapWeapon = w;
            }
        }
    }
    if ((unsigned int)sub->actMode < 0x3B) {
        if (0x39 <= (unsigned int)sub->actMode) {
        float c0, c4, c8;

        GetChainPendulum(sub->chain, &c0, &c4, &c8);
        if (0.0f < c0)
            *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 47);
        else
            *(unsigned long long *)((char *)sub + 0x478) |= (1ULL << 48);
        }
    }
    if (self == boyGObj && girlGObj != 0 &&
        GOBJ_ACT(girlGObj)->actMode == 106) {
        GObj *h = GOBJ_ACT(girlGObj)->carrier;

        if (GOBJ_ACT(h)->actMode == 99 && GetMotionFrameFlag1(h)) {
            float p60[4];

            if (_ACTGame_SearchGObj(self, (girlGObj), 200.0f, 400.0f, 0x78, p60)) {
                GObj *n = ACTGame_GetNearestGObj(pos, 0x21);

                if (_DistxzSqGV(pos, test_CURRENTROOT(n)) < 22500.0f) {
                    sub->wish0.ll |= (1ULL << 53);
                    *(GObj **)((char *)GOBJ_ACT(self)->enemy + 0x2E0) = n;
                }
            }
        }
    }
    if (CheckFloorAttribute(self, 0x800) || CheckFloorAttribute(self, 0x900))
        *(unsigned long long *)((char *)sub + 0x478) |= 0x20;
    if (CheckFloorAttribute(self, 0x800000)) {
        float p60[4];

        sceVu0Normalize(p60, (char *)GOBJ_SUB(self) + 0x1C0);
        *(float *)((char *)GOBJ_ACT(self)->enemy + 0x270) = p60[0];
        *(float *)((char *)GOBJ_ACT(self)->enemy + 0x274) = p60[1];
        *(float *)((char *)GOBJ_ACT(self)->enemy + 0x278) = p60[2];
        if (0.0f < sceVu0InnerProduct(test_CURRENTORIENT(self), p60)) {
            sub->wish1.ll |= 0x40;
            *(char *)((char *)GOBJ_ACT(self)->enemy + 0x280) = 0;
        } else {
            sub->wish1.ll |= 0x80;
            *(char *)((char *)GOBJ_ACT(self)->enemy + 0x280) = 1;
        }
    }
    if (CheckFloorAttribute(self, 0x40)) {
        sub->wish1.ll |= 4;
        debug_StdPrintfDummy("water\n");
    }
    if (CheckFloorAttribute(self, 0x50)) {
        if (GOBJ_SUB(self)->ctrl.waterDepth > 135.0f) {
            *(unsigned long long *)((char *)sub + 0x478) |= 8;
            debug_StdPrintfDummy("enter water\n");
        }
        if (GOBJ_SUB(self)->ctrl.waterDepth < 130.0f) {
            *(unsigned long long *)((char *)sub + 0x478) |= 0x10;
            debug_StdPrintfDummy("exit water\n");
        }
    }
    if (self == boyGObj) {
        float p70[4];
        GObj *t30 = 0;
        GObj *t19 = 0;
        GObj *t23 = 0;
        GObj *c;
        int x;
        int n;
        float rad;
        MotionDef *row = &motionKind[GOBJ_SUB(self)->ctrl.motion];

        rad = ((row->modeBits.word >> 16) & 7) ? 100.0f : 90.0f;
        c = CheckTorchChainReaction(self, 200.0f);
        if (c != 0) {
            GetRootPosition(p70, c);
            if (_DistxzSqGV(prj, p70) < rad * rad && p70[1] < prj[1] &&
                _FrontGV(p70, prj, test_CURRENTORIENT(self), 45)) {
                if (((p70[1] - prj[1]) < 0.0f ? -(p70[1] - prj[1]) : (p70[1] - prj[1])) <
                        200.0f &&
                    p70[1] < prj[1]) {
                    _OrientXZGV(env->torchOrient, p70, prj);
                    t23 = c;
                    t30 = t23;
                }
            }
        }
        c = CheckTorchChainReactionReverse(self, 200.0f);
        if (c != 0) {
            GetRootPosition(p70, c);
            if (_DistxzSqGV(prj, p70) < 12100.0f && p70[1] < prj[1] &&
                _FrontGV(p70, prj, test_CURRENTORIENT(self), 45)) {
                if (((p70[1] - prj[1]) < 0.0f ? -(p70[1] - prj[1]) : (p70[1] - prj[1])) <
                        200.0f &&
                    p70[1] < prj[1]) {
                    _OrientXZGV(env->torchRevOrient, p70, prj);
                    t19 = c;
                    env->torchRevObj = t19;
                }
            }
        }
        if (!ACTGame_NoWeapon(self)) {
            x = ACTGame_isWeaponEnableCatchfire(sub->weapon);
            if (x != 0) {
                if (!IsTorchLightOn((GObj *)x)) {
                    if (t30 != 0)
                        *(unsigned long long *)((char *)sub + 0x478) |= 0x800000;
                } else {
                    if (t19 != 0)
                        *(unsigned long long *)((char *)sub + 0x478) |= 0x2000000;
                }
            }
        }
        if (sub->heldItem.p != 0) {
            GObj *b = GetBombTorchGObj(sub->heldItem.p);

            if (t23 != 0 && b != 0 && !IsTorchLightOn(b)) {
                env->bombObj = b;
                sub->wish1.ll |= 0x1000000;
            }
        }
        n = 0;
        if (GOBJ_SUB(self)->ctrl.upperWall) {
            if (GOBJ_SUB(self)->ctrl.upperWallDist < 50.0f)
                n = 1;
        }
        if (!n)
            sub->wish1.ll |= 2;
    }
    if (((unsigned int)flags[1].w >> 27) & 1) {
        *(int *)(*(char **)(*(char **)(self + 0x164) + 0x650) + 0x2C4) = (int)obj;
        GetBoxHoldPoint((float *)((char *)GOBJ_ACT(self)->enemy + 0x2D0), obj, self);
    }
}

/* clang-format on */
