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

typedef struct AP1Vec {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) AP1Vec;

/* --- the TU's whole .data run, VMA 0x4E5A30..0x4E5A90 (0x60), in emission
   order.  The six AI mode names are eight bytes or fewer, so the compiler
   puts them (and GetAP1AIMode's "--") in the TU's .sdata run, in this order.
   The modes are stand, walk, jump, attack, dead, sleep. */

/* the two-letter tag GetAP1AIMode hands the debug display. */
static char *ap1ModeTag[] = {"ST", "WA", "JM", "AT", "DE", "SL"};

inline char *GetAP1AIMode(GObj *self)
{
    char *p = *(char **)&self->act;

    if (p == 0 || *(unsigned int *)(p + 0x34) >= 6) {
        return "--";
    }
    return ap1ModeTag[*(int *)(p + 0x34)];
}

/* the fixed hop walkAI asks for when it is boxed in: straight down and
   two units forward. */
static AP1Vec ap1BoxedInJump = {0.0f, -20.0f, 2.0f, 0.0f};

int standAI(GObj *self);
int walkAI(GObj *self);
int jumpAI(GObj *);
int attackAI(GObj *);

/* one entry per mode; dead and sleep run no AI of their own. */
static int (*ap1ModeAI[])() = {standAI, walkAI, jumpAI, attackAI, 0, 0};

/* the spelled-out mode name hehehe() prints. */
static char *ap1ModeName[] = {"STAND", "WALK", "JUMP", "ATTACK", "DEAD", "SLEEP"};

/* .sbss and .bss, owned by act_a_p_1.o and reached only from this file
   (MAIN.MAP names no symbol in either run), each in the ROM's run order.
   The AI's view of the boy and of the object it is watching, refreshed once a
   frame by the sense pass and read by every mode routine. */
static float boyDist; /* distance to the boy */

static short boyPitch; /* vertical angle to the boy */

static short boyYaw; /* heading to the boy in local space */

static short boyYawBack; /* the opposite heading, boyYaw - 32768 */

static int boySafe; /* the boy is not in danger */

static float lookDist; /* distance to the object being watched */

static short lookYaw; /* heading to it in local space */

static AP1Vec boyLocalDir; /* direction to the boy, in local space */

static AP1Vec boyLocalFlat; /* the same with y removed and normalised */

static AP1Vec boyDelta; /* the boy's offset in world space */

static AP1Vec boyDeltaFlat; /* the same with y removed */

static AP1Vec lookDelta; /* the watched object's offset in world space */

static AP1Vec lookLocalDir; /* direction to it, in local space */

static AP1Vec lookLocalFlat; /* the same with y removed and normalised */

static AP1Vec lookDeltaFlat; /* lookDelta with y removed */

static AP1Vec selfPos; /* this actor's own root position */

int standAI(GObj *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(((char *)self) + 0x164);

    if ((int)(((U *)(p + 0x20))->ll >> 21) & 1) {
        short r = boyYaw;
        r = r > 2048 ? 2048 : (r < -2048 ? -2048 : r);
        AP1Turn(self, r);
        return -1;
    }

    if (boyDist < 500.0f) {
        if (*(int *)(p + 0xAC) != 0) {
            if (AP1MotReq(self, 1))
                return 1;
        }
        if (lookDist > 100.0f) {
            if (AP1MotReq(self, 1))
                return 1;
        }
        if (boyPitch < 16384 && boyDist > 300.0f) {
            short r = boyYaw;
            r = r > 4096 ? 4096 : (r < -4096 ? -4096 : r);
            AP1Turn(self, r);
            return -1;
        }
        if (AP1MotReq(self, 1))
            return 1;
    }

    if (*(int *)(p + 0xAC) != 0) {
        if (lookDist < 50.0f) {
            short r = lookYaw;
            r = r > 2048 ? 2048 : (r < -2048 ? -2048 : r);
            AP1Turn(self, r);
            return -1;
        }
        if (AP1MotReq(self, 1))
            return 1;
    }

    if (lookDist < 100.0f) {
        short r = boyYaw;
        r = r > 2048 ? 2048 : (r < -2048 ? -2048 : r);
        AP1Turn(self, r);
        return -1;
    }

    return AP1MotReq(self, 1) ? 1 : -1;
}

int walkAI(GObj *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(((char *)self) + 0x164);

    if ((int)(((U *)(p + 0x20))->ll >> 21) & 1) {
        if (AP1MotReq(self, 0))
            return 0;
    }

    if (boyDist < 300.0f) {
        if (*(int *)(p + 0xDC) == 0 || boySafe == 0 || boyPitch < 16384) {
            short r;

            if (*(int *)(p + 0x4C) >= 31) {
                AP1Turn(self, boyYaw);
                if (AP1JumpReq(self, 2, p + 0xF0)) {
                    *(int *)(p + 0x4C) = 0;
                    return 2;
                }
            }
            r = boyYawBack;
            r = r > 12288 ? 12288 : (r < -12288 ? -12288 : r);
            AP1Turn(self, r);
            return -1;
        }
    }

    if (*(int *)(p + 0xDC) != 0 && boySafe != 0) {
        if ((boyYaw < 0 ? -boyYaw : boyYaw) < 8192) {
            if (boyDist < 150.0f) {
                short r = boyYaw;

                r = r > 4096 ? 4096 : (r < -4096 ? -4096 : r);
                AP1Turn(self, r);
                if (AP1MotReq(self, 3))
                    return 3;
            }
        }
    }

    if (boyDelta.y > 100.0f) {
        if (VectorLengthSquare(&boyDeltaFlat) < 10000.0f) {
            if (AP1JumpReq(self, 2, &ap1BoxedInJump)) {
                *(int *)(p + 0x4C) = 0;
                return 2;
            }
        }
    }

    if (lookDelta.y > 100.0f) {
        if (VectorLengthSquare(&lookDeltaFlat) < 10000.0f) {
            if (AP1JumpReq(self, 2, &ap1BoxedInJump)) {
                *(int *)(p + 0x4C) = 0;
                return 2;
            }
        }
    }

    if (*(int *)(p + 0xAC) != 0) {
        short r = lookYaw;

        r = r > 4096 ? 4096 : (r < -4096 ? -4096 : r);
        AP1Turn(self, r);
        if (lookDist < 50.0f) {
            if (AP1MotReq(self, 0))
                return 0;
        }
        return AP1MotReq(self, 1) == 0 ? -1 : 1;
    }

    if (lookDist < 100.0f) {
        if (AP1MotReq(self, 0))
            return 0;
    }

    if (*(int *)(p + 0xDC) != 0 && boySafe != 0 && boyDist < 300.0f) {
        short r = boyYaw;

        r = r > 512 ? 512 : (r < -512 ? -512 : r);
        AP1Turn(self, r);
    }

    {
        short r = lookYaw;

        r = r > 512 ? 512 : (r < -512 ? -512 : r);
        AP1Turn(self, r);
    }
    return AP1MotReq(self, 1) ? 1 : -1;
}

void hehehe(char *a0)
{
    debug_StdPrintfDummy(ap1ModeName[GOBJ_ACT(a0)->actMode]);
}

void SleepAP1(GObj *a0)
{
    typedef union {
        int i;
        long long ll;
    } U;

    int s = ((U *)((char *)a0 + 0x164))->i;
    *(int *)(s + 0x34) = 5;
    ((U *)(s + 0x18))->ll &= ~(1LL << 32);
    *(char *)(((U *)((char *)a0 + 0x164))->i + 0x1DA) = 1;
    AP1MotReqForce(a0, 7);
}

void WakeUpAP1(GObj *a0)
{
    typedef union {
        int i;
        long long ll;
    } U;

    int s = ((U *)((char *)a0 + 0x164))->i;

    if (*(int *)(s + 0x34) == 4) {
        /* already dead, so it is not woken */
        debug_StdPrintfDummy("既に死んでいるので起こしません\n");
        return;
    }
    *(int *)(s + 0x34) = 2;
    AP1MotReqForce(a0, 2);
    ((U *)(s + 0x18))->ll |= 1LL << 32;
    {
        int t = ((U *)((char *)a0 + 0x164))->i;
        *(int *)(t + 0x1B0) = 0;
        *(char *)(t + 0x1DA) = 0;
    }
}

/* Three static helpers the January-2002 listing places at act_a_p_1.c lines
 * 320-331, 335-344 and 346-352, expanded into subAP1BrainMain; never emitted
 * out of line, so none has a MAIN.MAP symbol and these three names are ours. */

typedef struct AP1Mtx {
    float m[16];
} __attribute__((aligned(16))) AP1Mtx;

static inline int AP1GetVerticalAngle(GObj *g, AP1Vec *v)
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

static inline float AP1GetDirection(AP1Vec *dst, AP1Vec *tmp, AP1Vec *from, AP1Vec *to)
{
    float len;

    _SubVectorXYZ(tmp, from, to);
    len = VectorLength(tmp);
    _ScaleVectorXYZ(dst, tmp, 1.0f / len);
    dst->w = 0.0f;
    return len;
}

static inline void AP1ToLocal(GObj *self, AP1Vec *v)
{
    AP1Mtx m;

    GetRootMatrix(&m, self);
    MatrixDrive_SetTransposeMatrix(&m, &m);
    _ApplyMatrix(v, &m, v);
}

/* `self` is volatile because this is an actor sub-thread entry: _ACTWait
 * yields to the scheduler inside the loop, so the GObj handle is re-read at
 * every use rather than cached in a register. */
void subAP1BrainMain(volatile int self)
{
    AP1Vec smooth = {0.0f, 0.0f, 0.0f, 1.0f};
    AP1Vec boy;
    AP1Vec look;
    int hold = 0;
    char *p;
    GObj *boyObj;
    GObj *host;
    int r;

    p = *(char **)((char *)self + 0x164);
    *(int *)(p + 0x34) = 5;
    *(int *)(p + 0x4C) = 0;

    while (1) {
        boyObj = boyGObj;
        GetRootPosition(&selfPos, (GObj *)self);
        GetRootPosition(&boy, boyObj);
        boy.y -= GOBJ_SUB(boyObj)->root.height - 10.0f;
        boyDist = AP1GetDirection(&boyLocalDir, &boyDelta, &boy, &selfPos);
        boyPitch = AP1GetVerticalAngle(boyObj, &boyLocalDir);
        AP1ToLocal((GObj *)self, &boyLocalDir);
        CopyVector(&boyLocalFlat, &boyLocalDir);
        boyLocalFlat.y = 0.0f;
        _NormalizeVector(&boyLocalFlat, &boyLocalFlat);
        boyYaw = GetTableArcTan2(boyLocalFlat.x, boyLocalFlat.z);
        boyYawBack = boyYaw - 32768;
        CopyVector(&boyDeltaFlat, &boyDelta);
        boyDeltaFlat.y = 0.0f;
        boySafe = IsBoyStatus_NotDanger() == 0;

        host = *(GObj **)(p + 0xA8);
        if (host != 0) {
            AP1Vec dest;

            GetRootPosition(&dest, host);
            dest.y -= *(float *)(*(int *)(*(char **)(p + 0xA8) + 0x15C) + 0x160) - 10.0f;
            if (hold == 0) {
                CopyVector(&smooth, &dest);
                hold = 1;
            } else {
                /* The census puts this row on sugiCommon.h:87, but only the
                 * line-95 spelling reaches rc0 here: the line-87 helper's
                 * single `__asm__ __volatile__` block hard-wires `$2` in its
                 * clobber list, which conflicts $2 with everything live across
                 * the block and moves this function's whole entry-block
                 * reload. See the ledger row for the measurement. */
                /* PLACEHOLDER: the census puts this row on sugiCommon.h:87, so the
                   host absorbed the line 85-88 helper, not the line 95-98 one.
                   No spelling of that helper reaches rc0 in both this TU and
                   clothAnimation.c; `_b` carries the multi-block body this host
                   needs. See docs/HEADERS.md, distance_squared. */
                if (40000.0f < distance_squared_b(&dest, &smooth)) {
                    _InterVectorXYZ(&smooth, &smooth, &dest, 0.5f);
                }
            }
            CopyVector(&look, &smooth);
        } else {
            GetRootPosition(&look, boyObj);
            look.y -= GOBJ_SUB(boyObj)->root.height - 10.0f;
            hold = 0;
        }

        lookDist = AP1GetDirection(&lookLocalDir, &lookDelta, &look, &selfPos);
        AP1ToLocal((GObj *)self, &lookLocalDir);
        CopyVector(&lookLocalFlat, &lookLocalDir);
        lookLocalFlat.y = 0.0f;
        _NormalizeVector(&lookLocalFlat, &lookLocalFlat);
        lookYaw = GetTableArcTan2(lookLocalFlat.x, lookLocalFlat.z);
        CopyVector(&lookDeltaFlat, &lookDelta);
        lookDeltaFlat.y = 0.0f;

        if (ap1ModeAI[*(int *)(p + 0x34)] != 0) {
            r = ap1ModeAI[*(int *)(p + 0x34)]((int)self);
            if (r != -1) {
                *(int *)(p + 0x34) = r;
            }
        }
        if (*(int *)(p + 0x34) == 4) {
            break;
        }

        if (CheckFloorAttribute(self, 0x800) || CheckFloorAttribute(self, 0x900)) {
            iosOmSendMail(self, 0xDF, (int)self);
            /* forced death */
            debug_StdPrintfDummy("強制死亡\n");
        }
        *(int *)(p + 0x4C) = *(int *)(p + 0x4C) + 1;
        _ACTWait(1);
    }

    while (1) {
        _ACTWait(1);
    }
}

void hitProc(GObj *a0)
{
    AP1MotReqForce(a0, 5);
}

void SetAP1DeadStatus(GObj *a0)
{
    typedef union {
        int i;
        long long ll;
    } U;

    int s = ((U *)((char *)a0 + 0x164))->i;
    *(int *)(s + 0x34) = 4;
    ((U *)(s + 0x18))->ll &= ~(1LL << 32);
    *(char *)(((U *)((char *)a0 + 0x164))->i + 0x1DA) = 1;
    AP1MotReqForce(a0, 5);
}

typedef struct AP1MailEntry {
    /* 0x0 */ unsigned int mail;
    /* 0x4 */ void *data;
} AP1MailEntry;

/* The GObj's pending-mail box at +0x54: a count and a run of 8-byte slots. */
typedef struct AP1MailQueue {
    /* 0x00 */ int unk0;
    /* 0x04 */ int num;
    /* 0x08 */ AP1MailEntry e[1];
} AP1MailQueue;

/* Four static helpers the January-2002 listing places at act_a_p_1.c lines
 * 510-515, 517-527, 530-533 and 543-556, expanded into AP1BeforeFunc (and, for
 * the first, into SetAP1DeadStatus); never emitted out of line, so none has a
 * MAIN.MAP symbol and these four names are ours. */
static inline void AP1SetMode(GObj *self, int mode)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)&self->act;

    *(int *)(p + 0x34) = mode;
    ((U *)(p + 0x18))->ll &= ~(1LL << 32);
    GOBJ_ACT(self)->hit = 1;
}

static inline void AP1DeadEffect(GObj *self)
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

static inline void AP1DeadMode(GObj *self)
{
    if (GOBJ_ACT(self)->actMode != 4)
        AP1SetMode(self, 4);
}

static inline void AP1DeadEffectHit(GObj *self)
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

static inline void AP1SetHold(GObj *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)&self->act;

    ((U *)(p + 0x20))->ll |= 0x200000;
}

static inline void AP1ClrHold(GObj *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)&self->act;

    ((U *)(p + 0x20))->ll &= ~0x200000;
}

void AP1BeforeFunc(GObj *self)
{
    AP1MailQueue *q = (AP1MailQueue *)(((char *)self) + 0x54);
    AP1MailEntry *e = q->e;
    int i;

    for (i = 0; i < q->num; i++, e++) {
        switch (e->mail) {
        default:
            break;

        case 32:
            AP1SetHold(self);
            break;

        case 31:
            AP1ClrHold(self);
            break;

        case 34:
            AP1DeadEffectHit(self);
            break;

        case 13:
            hitProc(self);
            AP1DeadEffect(self);
            AP1DeadMode(self);
            iosPadActRequest(boyPad, 17);
            ExecuteSEPackage(self, 105);
            break;

        case 26:
        case 38:
            AP1DeadEffect(self);
            AP1DeadMode(self);
            hitProc(self);
            break;

        case 223:
            AP1DeadMode(self);
            hitProc(self);
            break;
        }
    }
    q->num = 0;
}

void subAP1Control(int x);

void actAP1Start(GObj *g)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *s = actInitialize(g);

    actInitialize_ext_charcter(g);
    ((U *)(s + 0x18))->ll &= ~(1LL << 32);
    *(int *)(s + 0x34) = 5;
    *(int *)(s + 0xAC) = 0;
    *(int *)(s + 0xA8) = 0;
    GOBJ_ACT(g)->hit = 1;

    ACTGameView_Add(girlGObj, g);

    _ACTWait(1);

    *(int *)(s + 0x48) = GetAP1SpecType(g);

    {
        AP1Vec v = {spiderDef[*(int *)(s + 0x48)].jump[0], spiderDef[*(int *)(s + 0x48)].jump[1],
                    spiderDef[*(int *)(s + 0x48)].jump[2], 0};

        CopyVector(s + 0xF0, &v);
    }

    *(int *)(s + 0xDC) = (unsigned int)spiderDef[*(int *)(s + 0x48)].attack;
    actCreateSubThread(subAP1BrainMain, 20);
    actCreateSubThread(subAP1Control, 21);
}

int IsActCharDead(GObj *a0)
{
    int *v1 = (int *)a0->act;
    long x = *(unsigned int *)((char *)v1 + 0x1C);
    return (((int)x) & 1) ^ 1;
}

void SetAP1HostGObj(GObj *self, GObj *host)
{
    GOBJ_ACT(self)->lookTarget = host;
}

void SetAP1PriorLevel(GObj *self, int val)
{
    GOBJ_ACT(self)->lookPri = val;
}

inline int jumpAI(GObj *a0)
{
    return AP1MotReq(a0, 0) ? 0 : -1;
}

inline int attackAI(GObj *a0)
{
    return AP1MotReq(a0, 0) ? 0 : -1;
}

inline void subAP1Control(int x)
{
    volatile int local = x;
}
