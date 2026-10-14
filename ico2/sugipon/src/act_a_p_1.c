#include "typedef.h"
#include "sugiCommon.h"
#include "act_a_p_1.h"
#include "debug.h"
#include "pad.h"
#include "obj_manager.h"
#include "act-game.h"
#include "act.h"
#include "boyact.h"
#include "a_p_1.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "particleEffect.h"
#include "quaternion.h"
#include "tableSin.h"
#include "Matrix.h"
#include "matrixDrive.h"
#include "main.h"
#include "motionManager2.h"
#include "spider.h"
#include "include_asm.h"

typedef struct AP1Vec { /* field names derived */
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) AP1Vec; /* derived name */

/* the AI modes are stand, walk, jump, attack, dead and sleep */

/* the two-letter tag GetAP1AIMode hands the debug display. */
static char *ap1ModeTag[] = {"ST", "WA", "JM", "AT", "DE", "SL"}; /* derived name */

INCLUDE_ASM_LIT(GetAP1AIMode);

/* a hop ten units down and fifteen back, which no code of this build reads */
static AP1Vec ap1BackHop = {0.0f, -10.0f, -15.0f, 0.0f}; /* derived name */

/* the fixed hop walkAI asks for when it is boxed in: straight down and
   two units forward. */
static AP1Vec ap1BoxedInJump = {0.0f, -20.0f, 2.0f, 0.0f}; /* derived name */

static int standAI(GObj *self);
static int walkAI(GObj *self);
static int jumpAI(GObj *);
static int attackAI(GObj *);

/* one entry per mode; dead and sleep run no AI of their own. */
static int (*ap1ModeAI[])(GObj *) = {standAI, walkAI, jumpAI, attackAI, 0, 0};

/* the spelled-out mode name hehehe() prints. */
static char *ap1ModeName[] = {"STAND",  "WALK", "JUMP",
                              "ATTACK", "DEAD", "SLEEP"}; /* derived name */

/* the AI's view of the boy and of the object it is watching, refreshed once
   a frame by the sense pass and read by every mode routine */
static float boyDist; /* derived name */ /* distance to the boy */

static short boyPitch; /* derived name */ /* vertical angle to the boy */

static short boyYaw; /* derived name */ /* heading to the boy in local space */

static short boyYawBack; /* derived name */ /* the opposite heading, boyYaw - 32768 */

static int boySafe; /* derived name */ /* the boy is not in danger */

static float lookDist; /* derived name */ /* distance to the object being watched */

static AP1Vec boyLocalDir; /* derived name */ /* direction to the boy, in local space */

static AP1Vec boyLocalFlat; /* derived name */ /* the same with y removed and normalised */

static AP1Vec boyDelta; /* derived name */ /* the boy's offset in world space */

static AP1Vec boyDeltaFlat; /* derived name */ /* the same with y removed */

static AP1Vec lookDelta; /* derived name */ /* the watched object's offset in world space */

static AP1Vec lookLocalDir; /* derived name */ /* direction to it, in local space */

static AP1Vec lookLocalFlat; /* derived name */ /* the same with y removed and normalised */

static AP1Vec lookDeltaFlat; /* derived name */ /* lookDelta with y removed */

static AP1Vec selfPos; /* derived name */ /* this actor's own root position */

INCLUDE_ASM(standAI);

INCLUDE_ASM(walkAI);

INCLUDE_ASM(hehehe);

INCLUDE_ASM(SleepAP1);

INCLUDE_ASM(WakeUpAP1);

/* three helpers for subAP1BrainMain */

typedef struct AP1Mtx { /* field names derived */
    float m[16];
} __attribute__((aligned(16))) AP1Mtx; /* derived name */

static inline int AP1GetVerticalAngle(GObj *g, AP1Vec *v) /* derived name */
{
    AP1Vec q;
    AP1Mtx m;
    AP1Vec r;
    int a;

    GetRootQuaternion(&q, g);
    GetInverseQuaternion(&q, &q);
    GetMatrixFromQuaternion(&m, &q);
    _ApplyMatrix(&r, &m, v);
    a = GetTableArcTan2(_Sqrt(r.y * r.y + r.x * r.x), -r.z);
    return a < 0 ? -a : a;
}

static inline float AP1GetDirection(AP1Vec *dst, AP1Vec *tmp, AP1Vec *from,
                                    AP1Vec *to) /* derived name */
{
    float len;

    _SubVectorXYZ(tmp, from, to);
    len = VectorLength(tmp);
    _ScaleVectorXYZ(dst, tmp, 1.0f / len);
    dst->w = 0.0f;
    return len;
}

static inline void AP1ToLocal(GObj *self, AP1Vec *v) /* derived name */
{
    AP1Mtx m;

    GetRootMatrix(&m, self);
    MatrixDrive_SetTransposeMatrix(&m, &m);
    _ApplyMatrix(v, &m, v);
}

/* `self` is volatile: this is an actor sub-thread entry, and _ACTWait
 * yields to the other threads inside the loop */
INCLUDE_ASM(subAP1BrainMain);

static void hitProc(GObj *self)
{
    AP1MotReqForce(self, 5);
}

INCLUDE_ASM(SetAP1DeadStatus);

typedef struct AP1MailEntry { /* field names derived */
    /* 0x0 */ unsigned int mail;
    /* 0x4 */ void *data;
} AP1MailEntry; /* derived name */

/* The GObj's pending-mail box at +0x54 (typedef.h's IosMailBox): a word
   nothing reads, a count and a run of 8-byte slots. */
typedef struct AP1MailQueue { /* field names derived */
    /* 0x00 */ int queue;
    /* 0x04 */ int num;
    /* 0x08 */ AP1MailEntry e[1];
} AP1MailQueue; /* derived name */

/* four helpers for AP1BeforeFunc; SetAP1DeadStatus also uses the first */
static inline void AP1SetMode(GObj *self, int mode) /* derived name */
{
    Act *p = GOBJ_ACT(self);

    p->actMode = mode;
    p->flags18.ll &= ~(1LL << 32);
    GOBJ_ACT(self)->hit = 1;
}

static inline void AP1DeadEffect(GObj *self) /* derived name */
{
    Act *p = GOBJ_ACT(self);

    if (p->actMode != 4) {
        int pos[4];
        int quat[4];

        GetRootPosition(pos, self);
        GetRootQuaternion(quat, self);
        SetParticleEffect(12, pos, quat);
    }
}

static inline void AP1DeadMode(GObj *self) /* derived name */
{
    if (GOBJ_ACT(self)->actMode != 4)
        AP1SetMode(self, 4);
}

static inline void AP1DeadEffectHit(GObj *self) /* derived name */
{
    Act *p = GOBJ_ACT(self);

    if (p->actMode != 4) {
        int pos[4];
        int quat[4];

        AP1SetMode(self, 4);
        GetRootPosition(pos, self);
        GetRootQuaternion(quat, self);
        SetParticleEffect(49, pos, quat);
        hitProc(self);
    }
}

static inline void AP1SetHold(GObj *self) /* derived name */
{
    Act *p = GOBJ_ACT(self);

    p->flags20.ll |= 0x200000;
}

static inline void AP1ClrHold(GObj *self) /* derived name */
{
    Act *p = GOBJ_ACT(self);

    p->flags20.ll &= ~0x200000;
}

INCLUDE_ASM(AP1BeforeFunc);

void subAP1Control(int x);

INCLUDE_ASM(actAP1Start);

int IsActCharDead(GObj *self)
{
    return ((int)(GOBJ_ACT(self)->flags18.ll >> 32) & 1) ^ 1;
}

INCLUDE_ASM(SetAP1HostGObj);

INCLUDE_ASM(SetAP1PriorLevel);

static inline int jumpAI(GObj *self)
{
    return AP1MotReq(self, 0) ? 0 : -1;
}

static inline int attackAI(GObj *self)
{
    return AP1MotReq(self, 0) ? 0 : -1;
}

inline void subAP1Control(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(GetAP1AIMode);
