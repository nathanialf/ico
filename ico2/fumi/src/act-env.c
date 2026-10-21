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
#include "include_asm.h"

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

static void getDitchDistTbl(float **tbl, float *range, int *sofa, float *pos, void *obj,
                            int *carry);

static int GetDitchPosition(float *out, float *org, float *dir, float d0, float d1, float h);

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
        sceVu0ScaleVector(GOBJ_WORK(self)->boxSidePos, env->cliffOrient,                       \
                          (p120[0] < 0.0f ? -p120[0] : p120[0]) - (ofs));                       \
        _ApplyRyGV(GOBJ_WORK(self)->boxSidePos, (ang));                                          \
        sceVu0AddVector(GOBJ_WORK(self)->boxSidePos, pos, GOBJ_WORK(self)->boxSidePos);           \
        GOBJ_WORK(self)->boxSideSet = 1;                                                         \
        if (cond)                                                                                \
            sel = (to);                                                                          \
        break;                                                                                   \
    }

INCLUDE_ASM(ACTGetEnvironment);

/* clang-format on */
