#include "include_asm.h"

/* girl_brain_attract.c.inc: the girl brain's "attract" state, #included as
 * source into girl_act.c.  Its includer in the 2002 tree is
 * girl_brain_main.c.inc, which is not split out, so the include sits at the
 * point of girl_act.c that girl_brain_main.c.inc's text occupies. */

static int ATGoalTurnMail(void *actor, float *dir, int node);
/* void (void *, int, void *, void *) here, int (char *, int, void *, void *) in mail-add-data.h */
extern void ActSendMail_WithAdditionalData(void *gop, int msg, void *sender, void *data);

static void *attractMailData; /* derived name */

/* expanded twice in subGirlBrain_Attract: turn toward the target, and when
   already facing it send the attract mail with the target attached.  The
   result (whether a turn was started) is dropped by both callers. */
static inline int girlAttractTurnMailL(void *actor, void *obj, float *from,
                                       float *to) /* derived name */
{
    float dir[4];

    _OrientXZGV(dir, from, to);
    if (ATGoalTurnMail(actor, dir, 0x2C)) {
        return 1;
    }
    attractMailData = obj;
    ActSendMail_WithAdditionalData(actor, 0x156, actor, &attractMailData);
    return 0;
}

/* the same turn toward the boy, then the plain mail */
static inline int girlAttractTurnMailR(void *actor, float *from, float *to) /* derived name */
{
    float dir[4];

    _OrientXZGV(dir, from, to);
    if (!ATGoalTurnMail(actor, dir, 0x2C)) {
        ACTSendMailCorrect(actor, 0x158);
        return 0;
    }
    return 1;
}

INCLUDE_ASM(ATGoalTurnMail);

static int checkWaterfallResult(float *out)
{
    union { /* field names derived */
        float f[4];
        int i[4];
    } t;

    float pa[4];
    float pb[4];
    int r1;
    int r0;
    int ret;

    r1 = -1;
    r0 = -1;
    ret = 0;
    GetRootProjectionPosOfGObj(pa, boyGObj);
    GetRootProjectionPosOfGObj(pb, girlGObj);
    if (1600.0f < pb[1] && pb[1] < 2300.0f) {
        if (pb[2] < -150.0f) {
            r1 = 0;
        } else if (850.0f < pb[2]) {
            r1 = 2;
        } else {
            r1 = 1;
        }
    }
    if (1600.0f < pa[1] && pa[1] < 2300.0f) {
        if (pa[2] < -150.0f) {
            r0 = 0;
        } else if (850.0f < pa[2]) {
            r0 = 2;
        } else {
            r0 = 1;
        }
    }
    if (r0 == -1) {
        return 0;
    }
    if (r1 == -1) {
        return 0;
    }
    if (r1 == 1) {
        return 1;
    }
    if (r0 == 1) {
        if (*(void **)((char *)GOBJ_SUB(boyGObj)) != 0 &&
            *(int *)((char *)*(void **)((char *)GOBJ_SUB(boyGObj)) + 0xC) == 17) {
            t.f[0] = (test_CURRENTROOT(*(void **)((char *)GOBJ_SUB(boyGObj))))[0];
            t.f[1] = (test_CURRENTROOT(*(void **)((char *)GOBJ_SUB(boyGObj))))[1];
            t.f[2] = (test_CURRENTROOT(*(void **)((char *)GOBJ_SUB(boyGObj))))[2];
        } else {
            return 1;
        }
    }
    if (r1 == 0 && r0 != 0) {
        ret = 1;
        if (r0 == 1 && t.f[2] < -50.0f) {
            out[0] = pa[0];
            out[1] = 1800.0f;
            out[2] = -170.0f;
            ret = 2;
        }
    }
    if (r1 == 2 && r0 != r1) {
        ret = 1;
        if (r0 == 1 && 750.0f < t.f[2] && 650.0f < t.f[0] && t.f[0] < 950.0f) {
            out[0] = pa[0];
            out[1] = 1900.0f;
            out[2] = 870.0f;
            ret = 2;
        }
    }
    return ret;
}

/* The record Act.enemy points at, as far as this file uses it: the sofa
   position the attract state hands over (copied from the actor's 0x5B0) and
   the facing _GetRootObjectOrient fills for it. */
typedef struct { /* field names derived */
    char pad0[560];
    sceVu0FVECTOR pos; /* 0x230 */
    sceVu0FVECTOR dir; /* 0x240 */
} GirlSofaWork;        /* derived name */

/* the three attract parameter sets */
static GirlAttractParam attractObjParam = {0, {0}, {0}, 0, 338, 100.0f, 100.0f}; /* derived name */

static GirlAttractParam attractSofaParam = {0, {0}, {0}, 68, 267, 50.0f, 100.0f,
                                            1, {0}, {0}, 0,  {0}, 200.0f}; /* derived name */

static GirlAttractParam attractBoyParam = {0, {0}, {0}, 0, 338, 100.0f, 70.0f}; /* derived name */

/* The actor entry parameter is volatile: the actor scheduler writes the
 * caller's home slot while this thread is parked in _ACTWait. */
INCLUDE_ASM(subGirlBrain_Attract);
