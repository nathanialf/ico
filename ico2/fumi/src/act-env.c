#include "typedef.h"
#include "debug.h"
#include <libvu0.h>
#include "act-game.h"
#include "torch.h"
#include "gobj.h"
#include "camera-editor.h"
#include "commonact.h"

union ENVIF {
    int i;
    float f;
};

/* .data, carved VMA 0x4F1D60..0x4F1E10: the per-stage ditch-distance
   tables getDitchDistTbl selects between (the first six are ranges
   terminated by -1.0f, the rest position/orientation vectors).  Values are
   the shortest decimals that round-trip through binary32; every byte
   verified against baserom/pal/baseelf.rom. */
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
   TU's .rodata run (VMA 0x621A00). */
static const VECTOR sofaSeatOffset = {30.0f, 0.0f, -50.0f, 0.0f};

/* kept local: int here, GObj * in main.h */
extern int boyGObj;
/* kept local: agrees with motionManager2.h, which this TU does not include (CheckWallAttribute differ) */
extern int CheckPureWallAttribute();
/* kept local: agrees with motionManager2.h, which this TU does not include (CheckPureWallAttribute differ) */
extern int CheckWallAttribute();
/* same prototype motionManager2.h carries; kept local because this TU does not include it */
/* kept local: agrees with motionManager2.h, which this TU does not include (CheckPureWallAttribute, CheckWallAttribute differ) */
extern float GetHeightOfFieldPlaneDifference(int *a, int *b);
/* same prototype motionManager2.h carries; kept local because this TU does not include it */
/* kept local: agrees with motionManager2.h, which this TU does not include (CheckPureWallAttribute, CheckWallAttribute differ) */
extern void SetMotionDirection(void *a0, float *a1);
/* same prototype motionManager2.h carries; kept local because this TU does not include it */
/* kept local: agrees with motionManager2.h, which this TU does not include (CheckPureWallAttribute, CheckWallAttribute differ) */
extern void GetRootProjectionPosOfGObj(int a0, int a1);
/* kept local: agrees with main.h, which this TU does not include (boyGObj, ((char *)girlGObj) differ) */
extern int stage_no;

#include "act-env.h"
#include "gv.h"
#include "fieldCollision.h"

inline void GetSofaPosition(char *a0, char *a1)
{
    Act *w = GOBJ_ACT(a0);
    VECTOR v = sofaSeatOffset;
    *(float *)((char *)w + 0x560) = w->f_4B0;
    *(float *)((char *)w + 0x564) = w->f_4B4;
    *(float *)((char *)w + 0x568) = w->f_4B8;
    if (a0 == boyGObj) {
        v.x = -v.x;
    }
    v.w = 1.0f;
    sceVu0ApplyMatrix((char *)w + 0x5B0,
                      *(void **)((char *)((union ENVIF *)((char *)a1 + 0x15C))->i + 0xC), &v);
}

/* kept local: char * here, GObj * in main.h */
extern GObj *girlGObj;

/* Where the first carrier stands in the stage 8 ditch below the -3000 line
   (VMA 0x621A10, the run's second object). */
static const VECTOR ditchCarryPos = {767.0f, -3775.0f, 2621.0f, 1.0f};

static inline int getDitchCarryMode(void)
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

static inline int getDitchCarryModeStage8(void)
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
    /* The ROM frame is 0x1F0 = 0xC0 (work) + 0x10 (tmp) + 0xD0 more of
       aggregate locals under the register saves; act-env.c:1175-1195, inside
       the hit branch between the test (1174) and the copy out (1196), emit no
       instructions in either listing.  work2 and tmp2 are read by the DEBUG
       build's second probe there (probe and report ours); their sizes are
       what the frame proves. */
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
        sceVu0ApplyMatrix(a0, (void *)GOBJ_SUB(a1)->f_C, a0);
    }
}

typedef struct {
    int on;
    char *name;
} OrientFlagRow;

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

inline void ACTSetEnvAllmighty(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    s->f_478 |= (1ULL << 38);
    s->f_478 |= (1ULL << 39);
    s->f_478 |= (1ULL << 40);
    s->f_478 |= (1ULL << 41);
    s->f_478 |= (1ULL << 44);
    s->f_478 |= (1ULL << 45);
    if (ACTGame_FLAG_TETSUNAGI()) {
        s->flags18.ll &= ~(1ULL << 43);
        s->f_28 = 0;
    } else {
        if ((int)(s->flags18.ll >> 43) & 1)
            s->f_478 |= (1ULL << 46);
        s->f_28 += 1;
    }
    s->f_478 |= (1ULL << 50);
    s->f_478 |= (1ULL << 51);
    s->f_478 |= (1ULL << 52);
    s->f_478 |= (1ULL << 53);
    s->f_478 |= (1ULL << 49);
    s->f_480 |= (1ULL << 43);
}

inline int CheckWallAttributeEdegWall(int a0)
{
    if (stage_no == 4) {
        return (unsigned char)CheckPureWallAttribute(a0, 0x1000);
    }
    return (unsigned char)CheckWallAttribute(a0, 0x1000);
}

typedef struct {
    char b[0x20];
} ClipCopy;

/* kept local: the two records ACTGetEnvironment's head reads as members,
   shaped from its own loads (offsets from the ROM, names ours): the motion
   record at actor + 0x130 and the sub-object at object + 0x15C. */
typedef struct {
    char _000[0x110];
    float f_110; /* 0x110 */
    float f_114; /* 0x114 */
    char _118[0x18];
    float f_130; /* 0x130 */
    char _134[0x4];
    float f_138; /* 0x138 */
} EnvMotion;

typedef struct {
    int f_0; /* 0x0 */
    char _004[0x17C];
    char *f_180; /* 0x180 */
    char _184[0x3DC];
    float f_560; /* 0x560 */
    char *f_564; /* 0x564 */
    char _568[0xC];
    char *f_574; /* 0x574 */
    char _578[0x2C];
    float f_5A4; /* 0x5A4 */
} EnvSub;

extern int _FrontGV(float *a0, float *a1, void *ori, int deg);
extern int CheckPureCliffAttribute(void *a0, int attr);
extern float GetCorrectDistance(float d, int n);
extern void GetOrientOfCliffOfGObj(void *out, void *obj);
/* same prototype as its definition in weapon.c; kept local because no header carries it */
extern char *CheckSwapableWeapon(char *a0, float dist);
extern char *CheckTorchChainReactionReverse(char *a0, float dist);
extern char *GetBombTorchGObj(char *a0);
extern int GetBoxHoldPoint(float *out, char *self, void *chara);
/* kept local: char * here, int in main.h */
extern int girlControlMode;

/* kept local, as act-game.c keeps it: the 0x194-byte-per-entry motion record
   table indexed by the object's current motion id (obj->0x15C->0x4A0). */
typedef struct {
    char _000[0x150];
    int f_150;
    char _154[0x10];
    float f_164;
    char _168[0x18];
    short f_180;
    short f_182;
    short f_184;
    char _186[0x02];

    union {
        unsigned int w;

        struct {
            unsigned short lo, hi;
        } h;

        char b;
    } u_188;

    unsigned int f_18C;
    unsigned int f_190;
} MotionRec;

extern MotionRec motionKind[];
extern const StgPre stageData[];

/* act-env.c:949-953: the negated-orient angle, eight call sites.  Interim
   name: the listing inlines it everywhere, so neither MAIN.MAP nor the
   census carries one. */
static inline int H0950(void *o, float *v)
{
    float t[4];

    sceVu0ScaleVector(t, v, -1.0f);
    return _RotyGV(o, t);
}

/* act-env.c:958-963: the same with the scale as a parameter, two sites. */
static inline int H0960(void *o, float *v, float s)
{
    float t[4];

    sceVu0ScaleVector(t, v, s);
    return _RotyGV(o, t);
}

/* act-env.c:966-969 and 971-974: the absolute values of the two above. */
static inline int H0968(void *o, float *v)
{
    int r = H0950(o, v);

    return (r < 0) ? -r : r;
}

static inline int H0973(void *o, float *v, float s)
{
    int r = H0960(o, v, s);

    return (r < 0) ? -r : r;
}

/* act-env.c:999-1019: the ditch-height probe, one site. */
static inline unsigned char H1000(void *o, float h)
{
    ClipWork work;
    Act *s;
    float y, d;

    s = GOBJ_ACT(o);
    if (o == boyGObj && stageData[stage_no].flag2 && (s->unk34 == 4 || s->unk34 == 5)) {
        memset(&work, 0, 0xC0);
        GetSkeltonPosition(work.a, o, (void *)0x2C);
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

/* act-env.c:1226-1243 and 1262-1269: the collision-centre wrapper and the
   scaled offset around it, four sites with scales 5, 45, 30, 30.  Its rows
   1228 and 1229 read the wall record (+0x188) and the cliff record (+0x198)
   of the object's collision data: `cliff` selects between them (the
   parameter's name is ours). */
static inline void H1228(float *out, void *ref, void *o, int cliff)
{
    float *p;

    if (!cliff)
        p = *(float **)((char *)((union ENVIF *)((char *)o + 0x15C))->i + 0x188);
    else
        p = *(float **)((char *)((union ENVIF *)((char *)o + 0x15C))->i + 0x198);
    GetCollisCenterPositionSimple(out, 0, p);
    if (ref != 0) {
        ((union ENVIF *)((char *)out + 0xC))->f = 1.0f;
        sceVu0ApplyMatrix(out, (void *)GOBJ_SUB(ref)->f_C, out);
    }
}

/* act-env.c:1252-1255: the wrapper with no reference object, two sites
   (the wall and the cliff collision centres). */
static inline void H1253(float *out, void *o, int cliff)
{
    H1228(out, 0, o, cliff);
}

static inline void H1263(float *out, void *o, void *ref, float k)
{
    char *s = *(char **)((char *)o + 0x164);
    float t[4];
    H1228(out, ref, o, 0);
    sceVu0ScaleVector(t, (float *)(s + 0x4B0), k);
    sceVu0AddVector(out, out, t);
}

/* act-env.c:1364-1371 and 1377-1384: written out twice in the source, the
   seed differs only in the -20.0f and 5.0f. */
static inline void H1366(void *o, float *v, float top, float *out)
{
    float p[4], t[4];
    float d = -20.0f;

    GetRootPosition(p, o);
    sceVu0ScaleVector(t, v, -(top - d));
    sceVu0AddVector(out, p, t);
}

static inline void H1379(void *o, float *v, float top, float *out)
{
    float p[4], t[4];
    float d = 5.0f;

    GetRootPosition(p, o);
    sceVu0ScaleVector(t, v, -(top - d));
    sceVu0AddVector(out, p, t);
}

/* The environment check's TTY trace, built only when DEBUG is defined; the
   retail build does not define it, so the preprocessor leaves the helper
   without a body.  A parameterless inline whose body is empty is saved as the
   single (use (const_int 0)) flow.c:count_basic_blocks gives a function with
   no insns, and each call copies it into the caller: it emits no instruction
   and keeps the if's branch alive past flow, which is what leaves the ROM's
   bare c.lt.s under the girl-climb bit-20 test (reorg later deletes the
   branch to the next active insn and keeps the compare).  A helper with a
   parameter would leave nothing (its parameter move is an insn, so no USE is
   saved).  The name and the trace text are ours: an inlined empty body
   leaves no symbol and no listing row. */
static __inline__ void envDebugPrint(void)
{
#ifdef DEBUG
    scePrintf("env: girl climb height over 195\n");
#endif
}

/* ACTGetEnvironment is laid out on the listing's rows, and under -g its line
   breaks are part of the bytes (docs/NOTES.md "-g for the game"), so the
   formatter leaves it alone. */
/* clang-format off */
/* act-env.c:2582-2585: the box loop's four sides, one listing line each. */
#define BOX_DY ((p100[1] - prj[1]) < 0.0f ? -(p100[1] - prj[1]) : (p100[1] - prj[1]))
#define BOX_SIDE(lo, hi, ofs, ang, cond, to)                                                      \
    if ((lo) < p120[0] && p120[0] <= (hi)) {                                                     \
        sceVu0ScaleVector(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500, env + 0x10,       \
                          (p120[0] < 0.0f ? -p120[0] : p120[0]) - (ofs));                       \
        _ApplyRyGV(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500, (ang));                  \
        sceVu0AddVector((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500), pos,     \
                        (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500));         \
        *(char *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x4F0) = 1;                      \
        if (cond)                                                                                \
            sel = (to);                                                                          \
        break;                                                                                   \
    }

void ACTGetEnvironment(void *a0, void *a1, float *a2, EnvFlag *flags, char *env)
{
    float prj[4];
    float pos[4];
    float ori[4];
    /* The two GNU nested functions below are what put the actor parameter and
       hgt into the frame at 0x30 and 0x34 (put_var_into_stack): their bodies
       sit at act-env.c:1432-1445 and 1486-1488, inside this function's span
       and below its 1403 def line.  `inline` is required or gcc emits
       out-of-line copies ahead of this function and breaks the TU order. */
    char *sub = *(char **)(a0 + 0x164);
    char *obj = ((EnvSub *)(char *)GOBJ_SUB(a0))->f_180;
    int kind = ((EnvSub *)(char *)GOBJ_SUB(a0))->f_0;
    float dist = ((EnvMotion *)*(char **)(sub + 0x130))->f_138;
    float hgt = -((EnvMotion *)*(char **)(sub + 0x130))->f_130;
    float wallh = -((EnvSub *)(char *)GOBJ_SUB(a0))->f_5A4;
    float hh = ((EnvMotion *)*(char **)(sub + 0x130))->f_114;
    float f26 = ((EnvMotion *)*(char **)(sub + 0x130))->f_110;
    int v1D8 = 1;
    int v1DC = 1;
    int v1E0;
    int v1E4 = 0;
    int v1E8 = 0;
    char *w564 = ((EnvSub *)(char *)GOBJ_SUB(a0))->f_564;
    char *w574 = ((EnvSub *)(char *)GOBJ_SUB(a0))->f_574;
    char *v1EC = 0;
    float k;
    float kk;
    float kd;
    int g;

    inline int CheckWallAttributeNotYorda(int attr, int notYorda)
    {
        int o = (int)a0;

        if (notYorda && o == (int)((char *)girlGObj))
            return 0;
        return CheckWallAttribute(o, attr);
    }

    inline float PosOrFar(void)
    {
        if (hgt < 0.0f)
            return 3.40282347e+38f /* FLT_MAX */;
        return hgt;
    }

    char *o;

    memset(prj, 0, 16);
    if ((char *)GOBJ_SUB(a0)->f_188 == 0) {
        w574 = 0;
        w564 = 0;
    }
    if (w574 == 0 && w564 == 0)
        dist = 3.40282347e+38f /* FLT_MAX */;
    if (GOBJ_SUB(a0)->f_568 == 0)
        hh = 3.40282347e+38f /* FLT_MAX */;
    if ((int)(*(unsigned long long *)(sub + 0x18) >> 52) & 1)
        v1D8 = 0;
    if (((EnvSub *)(char *)GOBJ_SUB(a0))->f_560 > _ACTGame_GetParamF(2)) {
        v1D8 = 0;
        v1DC = 0;
    }
    GetRootProjectionPosOfGObj((int)prj, (int)a0);
    GetRootPosition(pos, a0);
    GetSkeltonOrient(ori, a0, 0x2C);
    *(ClipCopy *)(env + 0x170) = *(ClipCopy *)((char *)GOBJ_SUB(a0) + 0x180);
    ((ActStatusWord *)(sub + 0x18))->q &= ~(1ULL << 44);
    ((ActStatusWord *)(sub + 0x18))->q &= ~(1ULL << 45);
    ((ActStatusWord *)(sub + 0x20))->q &= ~(1ULL << 7);
    ((ActStatusWord *)(sub + 0x20))->q &= ~(1ULL << 36);
    *(char *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x4F0) = 0;
    if ((int)(*(unsigned long long *)(sub + 0x20) >> 15) & 1) {
        k = 0.0f;
        v1E0 = 0;
    } else if ((int)(*(unsigned long long *)(sub + 0x20) >> 14) & 1) {
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
                        *(char **)(env + 0x160) = o;
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
    if (GOBJ_SUB(a0)->f_568) {
        if (CheckPureCliffAttribute(a0, 0x300) || CheckPureCliffAttribute(a0, 0x500) ||
            CheckPureCliffAttribute(a0, 0x600))
            hh = 3.40282347e+38f /* FLT_MAX */;
    }
    if ((w574 != 0 || w564 != 0) && (char *)GOBJ_SUB(a0)->f_188 != 0) {
        GetOrientOfWall(env, (void *)GOBJ_SUB(a0)->f_188,
                        (int *)((char *)GOBJ_SUB(a0) + 0x180));
        *(float *)(env + 0xC) = 1.0f;
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
            r = H0950(p60, (float *)env);
            if (c2 && 30 < r)
                flags[0].w |= 0x20;
            if (c1 && r < -30)
                flags[0].w |= 0x10;
        }
        if (w574 != 0) {
            if (dist < 40.0f && H0968(a1, (float *)env) < 75)
                flags[0].w |= 2;
            if (dist < k) {
                int ry = H0968(a1, (float *)env);

                *(unsigned long long *)(sub + 0x18) |= (1ULL << 60);
                if (dist < 60.0f && ry < 30)
                    *(unsigned long long *)(sub + 0x18) |= (1ULL << 59);
            }
        }
    }
    if (w564 == 0 && GOBJ_SUB(a0)->f_57C) {
        if (GOBJ_SUB(a0)->f_5E4 < 100.0f) {
            if (H0968(a1, (float *)((char *)GOBJ_SUB(a0) + 0x5D0)) < 40) {
                *(unsigned long long *)(sub + 0x18) |= (1ULL << 44);
                *(unsigned long long *)(sub + 0x18) |= (1ULL << 45);
            }
        }
    }
    if (dist != 3.40282347e+38f /* FLT_MAX */ && w564 != 0 && v1D8) {
        void *ori2 = test_CURRENTORIENT(a0);
        int v1F8;

        v1F8 = H0968(ori2, (float *)env);
        *(int *)(env + 0x130) = *(int *)(*(char **)(env + 0x178) + 0x48);
        w564 = (char *)(CheckPureWallAttribute(a0, 0x1000) & 0xFF);
        *(int *)(env + 0x13C) = (int)obj;
        flags[0].w |= 1;
        if (hgt < wallh && hgt != -3.40282347e+38f /* -FLT_MAX */)
            hgt = wallh;
        if (dist < k && 40.0f <= PosOrFar())
            *(unsigned long long *)(sub + 0x18) |= (1ULL << 60);
        if (dist < 300.0f && PosOrFar() <= 250.0f)
            flags[0].w |= 4;
        if (a0 == ((char *)girlGObj) && dist < 300.0f && *(int *)(obj + 0xC) == 0x11 &&
            IsThisBoxTruck(obj) == 7 && H0968(a1, (float *)env) < 45 &&
            H0968(a2, (float *)env) < 45 && _AbsRotyGV(a1, a2) < 45)
            ((ActStatusWord *)(sub + 0x20))->q |= (1ULL << 38);
        if (CheckWallAttributeNotYorda(0xB000, 1) || CheckWallAttributeNotYorda(0xE000, 1) ||
            CheckWallAttributeNotYorda(0xC000, 0) || CheckWallAttributeNotYorda(0xD000, 1) ||
            CheckWallAttributeEdegWall((int)a0) || CheckWallAttributeNotYorda(0x3000, 0))
            hgt = wallh;
        if (a0 == ((char *)girlGObj) && CheckPureWallAttribute(a0, 0x7000)) {
            wallh = 3.40282347e+38f /* FLT_MAX */;
            hgt = wallh;
            if (ACTGame_FLAG_TETSUNAGI() &&
                test_CURRENTROOT(((char *)girlGObj))[1] >
                    test_CURRENTROOT(boyGObj)[1] + 50.0f) {
                float p60[4], p70[4], p80[4];
                float p90[4][4];

                sceVu0ScaleVector(p60, (float *)env, -1.0f);
                GetMatrixDirectionToZ(p90[0], p60);
                sceVu0SubVector(p70, test_CURRENTROOT(boyGObj),
                                test_CURRENTROOT(((char *)girlGObj)));
                p70[3] = 0.0f;
                sceVu0ApplyMatrix(p80, p90, p70);
                if (dist < p80[2])
                    *(unsigned long long *)(sub + 0x20) |= (1ULL << 19);
            }
        }
        if (stage_no == 16 && dist < 40.0f && 150.0f < (hgt < 0.0f ? -hgt : hgt) &&
            v1F8 < 45 && *(int *)(obj + 0xC) == 0x11)
            *(unsigned long long *)(sub + 0x20) |= (1ULL << 39);
        if (dist < 40.0f) {
            *(unsigned long long *)(sub + 0x18) |= (1ULL << 44);
            if (136 <= _AbsRotyGV(test_CURRENTORIENT(a0), env))
                *(unsigned long long *)(sub + 0x18) |= (1ULL << 45);
        }
        {
            float p60[4];
            int t7 = 90.0f < hgt && hgt < 110.0f && w564 == 0;
            int t3;
            char t16;
            char t17;
            MotionRec *row;

            if (190.0f < hgt && hgt < 210.0f && hgt < 40.0f) {
            }
            row = &motionKind[GOBJ_SUB(a0)->f_4A0];
            g = 1;
            if ((row->u_188.w >> 19) & 7) {
                kk = 60.0f;
            } else if ((row->f_18C >> 28) & 1) {
                kk = 50.0f;
            } else {
                kk = 40.0f;
            }
            if (dist < 120.0f && t7) {
                sceVu0ScaleVector(p60, (float *)env, dist);
                sceVu0AddVector((float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x840),
                                pos, p60);
                sceVu0ScaleVector((float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x850),
                                  (float *)env, -1.0f);
                *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x860) = 40.0f;
                *(int *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x864) = 20;
                *(int *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x868) = 1;
                flags[1].w |= 8;
            }
            if (a0 == ((char *)girlGObj) && _ACTCharStatus_Check(a0, 0x1C)) {
                sceVu0SubVector(p60, test_CURRENTROOT(((char *)girlGObj)),
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
                if (*(unsigned long long *)(sub + 0x480) & 0x3C0000) {
                    if (((int)(*(unsigned long long *)(sub + 0x480) >> 20) & 1) &&
                        *(int *)(a0 + 0xC) == 4)
                        H1366(a0, (float *)env, dist, (float *)(sub + 0x590));
                    else
                        H1379(a0, (float *)env, dist, (float *)(sub + 0x590));
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
                if (!((int)(*(unsigned long long *)(sub + 0x20) >> 12) & 1) &&
                    *(int *)(obj + 0xC) == 0x10) {
                    float rad = (a0 == boyGObj) ? 30.0f : 10.0f;

                    GetSofaPosition(a0, obj);
                    debug_NMarker((float *)(sub + 0x5B0), 0, 0xFF, 0, 100.0f);
                    if (_DistxzSqGV(prj, sub + 0x5B0) < rad * rad) {
                        flags[1].w |= 0x20;
                        *(int *)(env + 0x16C) = (int)obj;
                    }
                }
            }
    if (a0 == boyGObj && dist < 50.0f) {
        if (*(int *)(obj + 0xC) == 0x11 && !CheckPureWallAttribute(a0, 0xB00)) {
            float p70[4];

            flags[2].w |= 0x20;
            *(int *)(env + 0x140) = (int)obj;
            if (CanHoldBox(obj) && GetBoxHoldPoint(p70, obj, a0)) {
                flags[2].w |= 0x10;
                *(int *)(env + 0x144) = (int)obj;
            }
        }
        if (*(int *)(obj + 0xC) == 0x12 && CheckWallAttribute(a0, 0x700)) {
            flags[2].w |= 0x40;
            *(int *)(env + 0x148) = (int)obj;
        }
        if (*(int *)(obj + 0xC) == 0x17 && CheckPureWallAttribute(a0, 0x500)) {
            flags[2].w |= 0x80;
            *(int *)(env + 0x14C) = (int)obj;
            *(int *)(env + 0x150) = kind;
            H1263((float *)(env + 0xF0), a0, obj, 5.0f);
        }
        if (*(int *)(obj + 0xC) == 0x16 && CheckWallAttribute(a0, 0x500) &&
            CanFloorLeverPull(obj)) {
            flags[2].w |= 0x100;
            *(int *)(env + 0x14C) = (int)obj;
            H1263((float *)(env + 0xF0), a0, obj, 45.0f);
            {
                float p70[4];

                sceVu0ScaleVector(p70, (float *)env, -10.0f);
                _ApplyRyGV(p70, 1.5707964f);
                sceVu0AddVector((float *)(env + 0xF0), (float *)(env + 0xF0), p70);
            }
        }
        if (*(int *)(obj + 0xC) == 0x18 && CheckWallAttribute(a0, 0x600) &&
            CanWallLeverPull(obj)) {
            flags[2].w |= 0x200;
            *(int *)(env + 0x14C) = (int)obj;
            H1263((float *)(env + 0xF0), a0, obj, 30.0f);
        }
        if (*(int *)(obj + 0xC) == 0x19 && CheckWallAttribute(a0, 0x600) &&
            CanWallLeverPull(obj)) {
            flags[2].w |= 0x400;
            *(int *)(env + 0x14C) = (int)obj;
            H1263((float *)(env + 0xF0), a0, obj, 30.0f);
        }
    }
    if (dist < 200.0f) {
        int b = (dist < 40.0f) ? 1 : 0;

        if (!((stage_no == 86 || stage_no == 3 || stage_no == 46) && *(int *)(a0 + 0xC) == 4) &&
            CheckPureWallAttribute(a0, 0x400)) {
            flags[2].bit.b24 = b;
            flags[2].w |= 0x800000;
            *(float *)(env + 0xA0) = *(float *)(env + 0x0);
            *(float *)(env + 0xA4) = *(float *)(env + 0x4);
            *(float *)(env + 0xA8) = *(float *)(env + 0x8);
            H1253((float *)(env + 0xC0), a0, 0);
            {
                float p70[4];

                sceVu0ScaleVector(p70, (float *)env, 30.0f);
                sceVu0AddVector((float *)(env + 0xC0), (float *)(env + 0xC0), p70);
            }
            *(float *)(env + 0xCC) = 1.0f;
        }
        if (CheckPureWallAttribute(a0, 0xC000)) {
            flags[2].bit.b18 = b;
            flags[2].w |= 0x20000;
        }
    }
    switch (((int)(&motionKind[GOBJ_SUB(a0)->f_4A0])->u_188.w << 6) >> 30) {
    default:
        kd = 60.0f;
        break;
    case -1:
        if (CheckWallAttributeEdegWall((int)a0)) {
            kd = 30.0f;
        } else {
            kd = GetCorrectDistance(motionKind[GOBJ_SUB(a0)->f_4A0].f_164 + 2.0f,
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
                if (H1000(a0, hgt) == 0)
                    flags[2].w &= ~0x200000;
            }
        }
        else if (CheckWallAttribute(a0, 0x3000))
            flags[2].bit.b22 = c60b;
        else if (GOBJ_SUB(a0)->f_1E4) {
            flags[2].bit.b14 = c60a;
            flags[2].bit.b13 = c130;
            if (debug_no_breast_hang)
                flags[2].bit.b14 = 0;
            if (a0 == boyGObj && *(int *)(obj + 0xC) == 0x2C)
                flags[2].bit.b13 = c60c;
        }
    }
    if (dist < 50.0f && H0968(a2, (float *)env) < 40 &&
        (a0 == boyGObj || a0 == ((char *)girlGObj) || (130.0f < hgt && *(int *)(obj + 0xC) != 0x10)))
        *(unsigned long long *)(sub + 0x488) |= 8;
    if (((int)(*(unsigned long long *)(sub + 0x488) >> 3) & 1) && 65.0f < PosOrFar() &&
        (float)v1F8 < 30.0f)
        *(unsigned long long *)(sub + 0x478) |= (1ULL << 42);
    if (dist < 60.0f) {
        int e = ((float)v1F8 < 30.0f) ? 1 : 0;

        if (*(int *)(obj + 0xC) == 0x36) {
            if (!QueenBarrierInqBreakable())
                *(unsigned long long *)(sub + 0x478) |= (1ULL << 63);
        } else
            *(unsigned long long *)(sub + 0x478) |= (1ULL << 62);
        if (230.0f < PosOrFar() && !CheckWallAttribute(a0, 0x400) &&
            !CheckWallAttribute(a0, 0x8000) && *(int *)(obj + 0xC) != 0x2C &&
            *(int *)(obj + 0xC) != 0x36) {
            if (e) {
                if (CheckWallAttribute(a0, 0xE000))
                    *(unsigned long long *)(sub + 0x480) |= 1;
                else
                    *(unsigned long long *)(sub + 0x480) |= 2;
            }
        }
    }
    if (*(int *)(a0 + 0xC) == 4 && *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E4) == 3 &&
        dist < 180.0f && GOBJ_SUB(a0)->f_1E4) {
        if (40.0f <= hgt && hgt < 300.0f)
            flags[1].w |= 0x8000000;
        else if (300.0f <= hgt && hgt < 500.0f)
            flags[1].w |= 0x10000000;
        else if (500.0f <= hgt && hgt < 700.0f)
            flags[1].w |= 0x20000000;
    }
        }
    }
    if (hh != 3.40282347e+38f /* FLT_MAX */ && GOBJ_SUB(a0)->f_568 && v1DC) {
        float rr;
        int r;

        GetOrientOfCliffOfGObj(env + 0x10, a0);
        *(float *)(env + 0x1C) = 1.0f;
        r = H0973(test_CURRENTORIENT(a0), (float *)(env + 0x10), 1.0f);
        if (a0 == boyGObj && ((char *)girlGObj) != 0) {
            float p60[4];

            p60[0] = test_CURRENTROOT(((char *)girlGObj))[0];
            p60[1] = test_CURRENTROOT(((char *)girlGObj))[1];
            p60[2] = test_CURRENTROOT(((char *)girlGObj))[2];
            if (_DistSqGV(pos, p60) < stageData[stage_no].f_180 * stageData[stage_no].f_180) {
                float p70[4][4];
                float pB0[4], pC0[4];

                sceVu0SubVector(pB0, p60, pos);
                GetMatrixDirectionToZ(p70[0], (float *)(env + 0x10));
                pB0[3] = 0.0f;
                sceVu0ApplyMatrix(pC0, p70, pB0);
                if (0.0f < pC0[2])
                    v1E4 = 1;
                if (stage_no == 16)
                    v1E4 = 1;
            }
        }
        if (a0 == boyGObj && hh < 80.0f && ((char *)girlGObj) != 0 &&
            171 <= _AbsRotyGV(test_CURRENTORIENT(((char *)girlGObj)), env + 0x10)) {
            if (*(int *)(*(char **)(((char *)girlGObj) + 0x164) + 0x34) == 0x1D &&
                _DistSqGV(pos, test_CURRENTROOT(((char *)girlGObj))) < 14400.0f)
                flags[0].w |= 0x4000000;
            if (*(int *)(*(char **)(((char *)girlGObj) + 0x164) + 0x34) == 0x1C &&
                _DistSqGV(pos, test_CURRENTROOT(((char *)girlGObj))) < 40000.0f)
                flags[0].w |= 0x2000000;
        }
        if (hh < 20.0f && 45 < r) {
            if ((int)(*(unsigned long long *)(sub + 0x20) >> 42) & 1) {
                SetMotionDirection(a0, (float *)(env + 0x10));
                *(unsigned long long *)(sub + 0x20) &= ~(1ULL << 42);
            }
        }
        if (((char *)girlControlMode) != 0 && stage_no == 26 && 3000.0f < pos[2])
            v1E8 = 1;
        if ((v1E8 ? hh < 35.0f : hh < 50.0f) && a0 == ((char *)girlGObj) && boyGObj != 0 &&
            *(int *)(*(char **)(boyGObj + 0x164) + 0x34) == 0x58) {
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
                _OrientXZGV(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x510, p60, pos);
                flags[0].w |= 0x800;
            }
        }
        if (*(int *)(sub + 0x34) == 0x29) {
            if (900.0f < f26)
                flags[1].w |= 0x180;
            else
                flags[1].w |= 0x200;
        }
        if (hh < k && 40.0f <= f26)
            *(unsigned long long *)(sub + 0x18) |= (1ULL << 61);
        if (hh < 300.0f && 100.0f <= f26) {
            flags[0].w |= 8;
            *(float *)(env + 0x138) = hh;
        }
        switch (*(unsigned int *)(sub + 0x34)) {
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
                    sceVu0AddVector((float *)(env + 0x40), p70, p60);
                    if (5.0f < hh && CheckFloorAttribute(a0, 0xF000) && 20.0f < (float)r) {
                        float d = (15.0f - hh) * 5.0f / 15.0f;
                        float s;
                        float p80[4], p90[4];

                        s = (d < 0.0f) ? 0.0f : ((5.0f < d) ? 5.0f : d);
                        sceVu0ScaleVector(p90, (float *)(env + 0x10), -s);
                        sceVu0AddVector(p80, test_CURRENTROOT(a0), p90);
                        *(float *)(env + 0x90) = p80[0];
                        *(float *)(env + 0x94) = p80[1];
                        *(float *)(env + 0x98) = p80[2];
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
        /* Two identical arms, which the post-reload cross-jump merges (as it
           merges case 116's tail into them): the listing keeps only the
           second (row 2388) and nothing on rows 2372-2387.  The bytes pin one
           such extra arm through the f26 variable's reference count (its
           register against lim's), not which case value it carried. */
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
                    sceVu0AddVector((float *)(env + 0x40), p70, p60);
                    if (5.0f < hh && CheckFloorAttribute(a0, 0xF000) && 20.0f < (float)r) {
                        float d = (25.0f - hh) * 5.0f / 25.0f;
                        float s;
                        float p80[4], p90[4];

                        s = (d < 0.0f) ? 0.0f : ((5.0f < d) ? 5.0f : d);
                        sceVu0ScaleVector(p90, (float *)(env + 0x10), -s);
                        sceVu0AddVector(p80, test_CURRENTROOT(a0), p90);
                        *(float *)(env + 0x90) = p80[0];
                        *(float *)(env + 0x94) = p80[1];
                        *(float *)(env + 0x98) = p80[2];
                        flags[3].w |= 0x4000;
                        flags[3].w &= ~2;
                        flags[2].w &= 0x7FFFFFFF;
                    }
                }
            }
            break;
        }
        if (ACTGame_FLAG_TETSUNAGI() && hh < 40.0f && 1000.0f < f26) {
            *(ClipCopy *)(env + 0x190) = *(ClipCopy *)((char *)GOBJ_SUB(a0) + 0x180);
            flags[0].w |= 0x8000000;
        }
        if (hh < 40.0f) {
            if (!((stage_no == 86 || stage_no == 3 || stage_no == 46) && *(int *)(a0 + 0xC) == 4) &&
                CheckPureCliffAttribute(a0, 0x400) && 60.0f < f26) {
                *(float *)(env + 0xA0) = *(float *)(env + 0x10);
                *(float *)(env + 0xA4) = *(float *)(env + 0x14);
                *(float *)(env + 0xA8) = *(float *)(env + 0x18);
                flags[2].w |= 0x2000000;
                if (hh < 10.0f && H0973(ori, (float *)(env + 0x10), 1.0f) < 60)
                    flags[2].w |= 0x4000000;
                H1253((float *)(env + 0xC0), a0, 1);
                *(float *)(env + 0xCC) = 1.0f;
            }
            if (CheckPureCliffAttribute(a0, 0xC000))
                flags[2].w |= 0x80000;
        }
        if (hh < 25.0f && v1E0 &&
            !(((char *)girlGObj) != 0 && *(int *)(*(char **)(((char *)girlGObj) + 0x164) + 0x34) == 0x6F &&
              *(char **)(*(char **)(((char *)girlGObj) + 0x164) + 0x144) == a0)) {
            if (f26 < 55.0f)
                ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 24);
            else if (f26 < 105.0f)
                ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 25);
            else if (f26 < 205.0f)
                ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 26);
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
            *(int *)(*(char **)(((char *)girlGObj) + 0x164) + 0x34) != 0x26 && hh < 200.0f &&
            !ACTGame_FLAG_TETSUNAGI() && !CheckPureCliffAttribute(a0, 0x7000) &&
            !CheckPureCliffAttribute(a0, 0x400) &&
            _AbsRotyGV(env + 0x10, ori) < 60) {
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
                test_CURRENTROOT(((char *)girlGObj))[1] >
                    test_CURRENTROOT(boyGObj)[1] + 800.0f)
                v204 = 0;
            if (stage_no == 7) {
                GetRootProjectionPosOfGObj((int)p80, (int)((char *)girlGObj));
                if (sel == 200) {
                    if (!(180.0f < p80[1] - prj[1]))
                        v204 = 0;
                    if (prj[0] * p80[0] < 0.0f)
                        v204 = 0;
                }
            }
            if (((int)(*(unsigned long long *)(*(char **)(boyGObj + 0x164) + 0x20) >> 43) &
                 1) &&
                1600.0f < pos[1] && 200 <= sel)
                sel = 0;
            v208 = (sel < 200);
            if (!v208) {
                pA0[0] = prj[0];
                pA0[1] = prj[1];
                pA0[2] = prj[2];
                sceVu0ScaleVector(p90, (float *)(env + 0x10), hh + 50.0f);
                sceVu0AddVector(pB0, pA0, p90);
                pB0[1] = pB0[1] + f26;
                GetMatrixDirectionToZ(pC0[0], (float *)(env + 0x10));
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
                sceVu0ScaleVector(p130, (float *)(env + 0x10), hh);
                sceVu0AddVector((float *)(env + 0x50), p140, p130);
                if (*(unsigned char *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x4F0))
                    sceVu0AddVector((float *)(env + 0x50),
                                    (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x500), p130);
                GetRootPosition(p160, a0);
                sceVu0ScaleVector(p150, (float *)(env + 0x10), hh - 30.0f);
                sceVu0AddVector((float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x810), p160, p150);
                *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x820) = *(float *)(env + 0x10);
                *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x824) = *(float *)(env + 0x14);
                *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x828) = *(float *)(env + 0x18);
                *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x830) = 30.0f;
                *(int *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x834) = 20;
                *(int *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x838) = 0;
                ((ActStatusWord *)(sub + 0x480))->q |= 4;
                if (v200) {
                    *(int *)(env + 0x134) = sel;
                    switch (sel) {
                    case 100:
                        ((ActStatusWord *)(sub + 0x488))->q |= 0x80;
                        break;
                    case 200:
                        ((ActStatusWord *)(sub + 0x488))->q |= 0x100;
                        break;
                    case 300:
                        ((ActStatusWord *)(sub + 0x488))->q |= 0x200;
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
            !(_DistSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(((char *)girlGObj))) <
              10000.0f) &&
            !(((char *)girlGObj) != 0 && boyGObj != 0 &&
              test_CURRENTROOT(((char *)girlGObj))[1] >
                  test_CURRENTROOT(boyGObj)[1] + 800.0f) &&
            (*(int *)(*(char **)(((char *)girlGObj) + 0x164) + 0x34) == 4 ||
             !(_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(((char *)girlGObj))) <
               (hh + 100.0f) * (hh + 100.0f))) &&
            !(_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(((char *)girlGObj))) < 40000.0f &&
              300.0f < GetHeightOfFieldPlaneDifference((int *)((char *)girlGObj), (int *)boyGObj))) {
            _OrientXZGV(p130, test_CURRENTROOT(((char *)girlGObj)), test_CURRENTROOT(boyGObj));
            if (_AbsRotyGV(p130, env + 0x10) < 80) {
                float *tbl;
                float range;
                int sofa = 0;
                int carry = 0;
                int i;

                getDitchDistTbl(&tbl, &range, &sofa, p160, p170, &carry);
                for (i = 0; 0.0f <= tbl[i]; i++) {
                    if (GetDitchPosition(p140, pos, (float *)(env + 0x10), hh, tbl[i],
                                         range)) {
                        sceVu0ScaleVector(p150, (float *)(env + 0x10), -1.0f);
                        if (sofa) {
                            p140[0] = p160[0];
                            p140[1] = p160[1];
                            p140[2] = p160[2];
                            p150[0] = p170[0];
                            p150[1] = p170[1];
                            p150[2] = p170[2];
                        }
                        if (hh < 60.0f) {
                            *(char *)(sub + 0x530) = *(char *)&carry;
                            *(float *)(env + 0x60) = p140[0];
                            *(float *)(env + 0x64) = p140[1];
                            *(float *)(env + 0x68) = p140[2];
                            *(float *)(env + 0x70) = p150[0];
                            *(float *)(env + 0x74) = p150[1];
                            *(float *)(env + 0x78) = p150[2];
                            ((ActStatusWord *)(sub + 0x488))->q |= 0x2000;
                        } else {
                            sceVu0ScaleVector(p180, (float *)(env + 0x10), hh - 30.0f);
                            sceVu0AddVector((float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x870), pos,
                                            p180);
                            *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x880) =
                                *(float *)(env + 0x10);
                            *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x884) =
                                *(float *)(env + 0x14);
                            *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x888) =
                                *(float *)(env + 0x18);
                            *(float *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x890) = 30.0f;
                            *(int *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x894) = 20;
                            *(int *)((char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x688) + 0x898) = 0;
                            ((ActStatusWord *)(sub + 0x480))->q |= 0x10;
                        }
                        break;
                    }
                }
            }
        }
        if (flags[2].w < 0 ? hh < 40.0f : hh < 30.0f) {
            char *found = 0;

            p140[0] = *(float *)(env + 0x10);
            p140[1] = *(float *)(env + 0x14);
            p140[2] = *(float *)(env + 0x18);
            _ApplyRyGV(p140, 1.5707964f);
            for (o = isysGObjSearchFromObjKindID_begin(0x15); o != 0;
                 o = isysGObjSearchFromObjKindID_next(o)) {
                if (*(int *)(o + 0x16C)) {
                    float d;

                    if (CheckChainClimbablePos(o)) {
                        GetChainClimbOrient(p170, o);
                        if (46 <= _AbsRotyGV(p170, env + 0x10))
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
                if (0.0f < sceVu0InnerProduct(p180, env + 0x10))
                    found = v1EC;
            }
            if (found != 0) {
                ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 62);
                *(char **)(env + 0x15C) = found;
                p1A0[0] = test_CURRENTROOT(found)[0];
                p1A0[1] = test_CURRENTROOT(found)[1];
                p1A0[2] = test_CURRENTROOT(found)[2];
                sceVu0ScaleVector(p190, (float *)(env + 0x10), -20.0f);
                *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1D0) = p1A0[0];
                *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1D4) = p1A0[1];
                *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1D8) = p1A0[2];
                sceVu0AddVector((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1C0), p1A0, p190);
                *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1C4) = pos[1];
            }
        }
        }
    }
    CheckFloorAttribute(a0, 0x200);
    if (a0 == ((char *)girlGObj) && *(int *)(sub + 0x34) == 0x45) {
        float hd = -GetHeightOfFieldPlaneDifference((int *)boyGObj, (int *)a0);

        if (((int)(*(unsigned long long *)(sub + 0x480) >> 18) & 1) && 5.0f < hd) {
            *(unsigned long long *)(sub + 0x488) |= 0x40;
            *(unsigned long long *)(sub + 0x488) |= 0x400;
        }
        if (((int)(*(unsigned long long *)(sub + 0x480) >> 19) & 1) && 60.0f < hd) {
            if (dist < 40.0f)
                *(unsigned long long *)(sub + 0x20) |= (1ULL << 36);
            if (*(int *)(*(char **)(boyGObj + 0x164) + 0x34) == 0x37)
                *(unsigned long long *)(sub + 0x488) |= 0x800;
            *(unsigned long long *)(sub + 0x488) |= 0x1000;
        }
        if (((int)(*(unsigned long long *)(sub + 0x480) >> 20) & 1) && 195.0f < hd)
            envDebugPrint();
    }
    /* RECONSTRUCTION, ROM-proven deleted-code window: the bytes pin an
       unconditional read of the actor here whose value flow later finds
       dead (it keeps the row-2788 copy as GetHeightOfFieldPlaneDifference's
       argument, `daddu $5,$6`, while nothing of it survives); they do not
       pin its text.  The assignment to the loop cursor is our spelling. */
    o = a0;
    if (((char *)girlGObj) != 0) {
        ((ActStatusWord *)(sub + 0x478))->q |= (1ULL << 47);
        ((ActStatusWord *)(sub + 0x478))->q |= (1ULL << 48);
    }
    if (*(char **)(sub + 0x180) != 0)
        ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 44);
    if (a0 == boyGObj && *(int *)(sub + 0x34) != 14) {
        char *w;

        if (*(char **)(sub + 0x150) != 0)
            w = CheckSwapableWeapon(*(char **)(sub + 0x150), 150.0f);
        else
            w = CheckSwapableWeapon(a0, 150.0f);
        if (w != 0) {
            float p60[4], p70[4];

            *(char **)(env + 0x158) = w;
            ((ActStatusWord *)(sub + 0x478))->q |= (1ULL << 55);
            p60[0] = test_CURRENTROOT(w)[0];
            p60[1] = test_CURRENTROOT(w)[1];
            p60[2] = test_CURRENTROOT(w)[2];
            _OrientXZGV(p70, p60, pos);
            if ((_AbsRotyGV(p70, a2) < 45 && _DistxzSqGV(p60, pos) < 6400.0f) ||
                (45 <= _AbsRotyGV(p70, a2) && _DistxzSqGV(p60, pos) < 900.0f)) {
                ((ActStatusWord *)(sub + 0x478))->q |= (1ULL << 54);
                *(char **)(env + 0x158) = w;
            }
        }
    }
    if (*(unsigned int *)(sub + 0x34) < 0x3B) {
        if (0x39 <= *(unsigned int *)(sub + 0x34)) {
        float c0, c4, c8;

        GetChainPendulum(*(char **)(sub + 0x190), &c0, &c4, &c8);
        if (0.0f < c0)
            *(unsigned long long *)(sub + 0x480) |= (1ULL << 60);
        else
            *(unsigned long long *)(sub + 0x480) |= (1ULL << 61);
        }
    }
    if (a0 == boyGObj && ((char *)girlGObj) != 0 &&
        *(int *)(*(char **)(((char *)girlGObj) + 0x164) + 0x34) == 0x6F) {
        char *h = *(char **)(*(char **)(((char *)girlGObj) + 0x164) + 0x144);

        if (*(int *)(*(char **)(h + 0x164) + 0x34) == 0x67 && GetMotionFrameFlag1(h)) {
            float p60[4], p70[4];

            if (_ACTGame_SearchGObj(a0, ((char *)girlGObj), 200.0f, 400.0f, 0x78, p60)) {
                char *n = ACTGame_GetNearestGObj(test_CURRENTROOT(h), 0x21);

                p70[0] = test_CURRENTROOT(n)[0];
                p70[1] = test_CURRENTROOT(n)[1];
                p70[2] = test_CURRENTROOT(n)[2];
                if (_DistxzSqGV(pos, p70) < 22500.0f &&
                    ((prj[1] - p70[1]) < 0.0f ? -(prj[1] - p70[1]) : (prj[1] - p70[1])) <
                        50.0f) {
                    ((ActStatusWord *)(sub + 0x478))->q |= (1ULL << 56);
                    *(char **)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x2E0) = n;
                }
            }
        }
    }
    if (CheckFloorAttribute(a0, 0x800) || CheckFloorAttribute(a0, 0x900))
        *(unsigned long long *)(sub + 0x480) |= (1ULL << 15);
    if (CheckFloorAttribute(a0, 0x800000)) {
        float p60[4];

        sceVu0Normalize(p60, (char *)GOBJ_SUB(a0) + 0x1D0);
        *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270) = p60[0];
        *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x274) = p60[1];
        *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x278) = p60[2];
        if (0.0f < sceVu0InnerProduct(test_CURRENTORIENT(a0), p60)) {
            ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 16);
            *(char *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x280) = 0;
        } else {
            ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 17);
            *(char *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x280) = 1;
        }
    }
    if (CheckFloorAttribute(a0, 0x50)) {
        ((ActStatusWord *)(sub + 0x480))->q |= 0x1000;
        if (GOBJ_SUB(a0)->f_644 > (a0 == boyGObj ? 110.0f : 135.0f)) {
            *(unsigned long long *)(sub + 0x480) |= 0x2000;
            debug_StdPrintfDummy("enter water\n");
        }
        if (GOBJ_SUB(a0)->f_644 < (a0 == boyGObj ? 105.0f : 130.0f)) {
            *(unsigned long long *)(sub + 0x480) |= 0x4000;
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
        MotionRec *row = &motionKind[GOBJ_SUB(a0)->f_4A0];

        rad = ((row->u_188.w >> 19) & 7) ? 100.0f : 90.0f;
        c = CheckTorchChainReaction(a0, 200.0f);
        if (c != 0) {
            GetRootPosition(p70, c);
            if (_DistxzSqGV(prj, p70) < rad * rad && p70[1] < prj[1] &&
                _FrontGV(p70, prj, test_CURRENTORIENT(a0), 45)) {
                if (((p70[1] - prj[1]) < 0.0f ? -(p70[1] - prj[1]) : (p70[1] - prj[1])) <
                        200.0f &&
                    p70[1] < prj[1]) {
                    _OrientXZGV(env + 0x20, p70, prj);
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
                    _OrientXZGV(env + 0x30, p70, prj);
                    t19 = c;
                    *(char **)(env + 0x168) = t19;
                }
            }
        }
        if (!ACTGame_NoWeapon(a0)) {
            x = ACTGame_isWeaponEnableCatchfire(*(int **)(sub + 0x150));
            if (x != 0) {
                if (!IsTorchLightOn(x)) {
                    if (t30 != 0)
                        *(unsigned long long *)(sub + 0x480) |= (1ULL << 33);
                } else {
                    if (t19 != 0)
                        *(unsigned long long *)(sub + 0x480) |= (1ULL << 35);
                }
            }
        }
        if (*(char **)(sub + 0x180) != 0) {
            char *b = GetBombTorchGObj(*(char **)(sub + 0x180));

            if (t23 != 0 && b != 0 && !IsTorchLightOn(b)) {
                *(char **)(env + 0x164) = b;
                ((ActStatusWord *)(sub + 0x480))->q |= (1ULL << 34);
            }
        }
        n = 0;
        if (GOBJ_SUB(a0)->f_578) {
            if (GOBJ_SUB(a0)->f_5E0 < 50.0f)
                n = 1;
        }
        if (!n)
            ((ActStatusWord *)(sub + 0x480))->q |= 0x400;
    }
    if (((unsigned int)flags[2].w >> 5) & 1) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x2C4) = (int)obj;
        GetBoxHoldPoint((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x2D0), obj, a0);
    }
}

/* clang-format on */
