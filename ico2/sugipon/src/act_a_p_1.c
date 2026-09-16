#include "common.h"
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

typedef struct AP1Vec {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) AP1Vec;

/* --- the TU's whole .data run, VMA 0x4E5A30..0x4E5A90 (0x60), in emission
   order.  The six AI mode names are eight bytes or fewer, so the compiler
   puts them in .sdata, which this pass does not carve: they stay extern into
   the .sdata blob.  The modes are stand, walk, jump, attack, dead, sleep. */
extern char D_0063B6C8[]; /* "SL" */
extern char D_0063B6D0[]; /* "DE" */
extern char D_0063B6D8[]; /* "AT" */
extern char D_0063B6E0[]; /* "JM" */
extern char D_0063B6E8[]; /* "WA" */
extern char D_0063B6F0[]; /* "ST" */
extern char D_0063B700[]; /* "SLEEP" */
extern char D_0063B708[]; /* "DEAD" */
extern char D_0063B710[]; /* "ATTACK" */
extern char D_0063B718[]; /* "JUMP" */
extern char D_0063B720[]; /* "WALK" */
extern char D_0063B728[]; /* "STAND" */

/* the two-letter tag GetAP1AIMode hands the debug display. */
static char *ap1ModeTag[] = {D_0063B6F0, D_0063B6E8, D_0063B6E0,
                             D_0063B6D8, D_0063B6D0, D_0063B6C8};

/* the fixed hop walkAI asks for when it is boxed in: straight down and
   two units forward. */
static AP1Vec ap1BoxedInJump = {0.0f, -20.0f, 2.0f, 0.0f};

int standAI(char *self);
int walkAI(char *self);
int jumpAI();
int attackAI();

/* one entry per mode; dead and sleep run no AI of their own. */
static int (*ap1ModeAI[])() = {standAI, walkAI, jumpAI, attackAI, 0, 0};

/* the spelled-out mode name hehehe() prints. */
static char *ap1ModeName[] = {D_0063B728, D_0063B720, D_0063B718,
                              D_0063B710, D_0063B708, D_0063B700};

extern float D_0063C440;
extern short D_0063C444;
extern short D_0063C446;
extern float D_0063C450;
extern short D_0063C454;

int standAI(char *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(self + 0x164);

    if ((int)(((U *)(p + 0x20))->ll >> 21) & 1) {
        short r = D_0063C446;
        r = r > 2048 ? 2048 : (r < -2048 ? -2048 : r);
        AP1Turn(self, r);
        return -1;
    }

    if (D_0063C440 < 500.0f) {
        if (*(int *)(p + 0xAC) != 0) {
            if (AP1MotReq(self, 1))
                return 1;
        }
        if (D_0063C450 > 100.0f) {
            if (AP1MotReq(self, 1))
                return 1;
        }
        if (D_0063C444 < 16384 && D_0063C440 > 300.0f) {
            short r = D_0063C446;
            r = r > 4096 ? 4096 : (r < -4096 ? -4096 : r);
            AP1Turn(self, r);
            return -1;
        }
        if (AP1MotReq(self, 1))
            return 1;
    }

    if (*(int *)(p + 0xAC) != 0) {
        if (D_0063C450 < 50.0f) {
            short r = D_0063C454;
            r = r > 2048 ? 2048 : (r < -2048 ? -2048 : r);
            AP1Turn(self, r);
            return -1;
        }
        if (AP1MotReq(self, 1))
            return 1;
    }

    if (D_0063C450 < 100.0f) {
        short r = D_0063C446;
        r = r > 2048 ? 2048 : (r < -2048 ? -2048 : r);
        AP1Turn(self, r);
        return -1;
    }

    return AP1MotReq(self, 1) ? 1 : -1;
}

extern short D_0063C448;
extern int D_0063C44C;
extern float D_0071EC64[];
extern float D_0071EC70[];
extern float D_0071EC84[];
extern float D_0071ECB0[];
/* kept local: this TU's uses of VectorLengthSquare do not fit the prototype in matrixDrive.h */
extern float VectorLengthSquare(void *v);

int walkAI(char *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(self + 0x164);

    if ((int)(((U *)(p + 0x20))->ll >> 21) & 1) {
        if (AP1MotReq(self, 0))
            return 0;
    }

    if (D_0063C440 < 300.0f) {
        if (*(int *)(p + 0xDC) == 0 || D_0063C44C == 0 || D_0063C444 < 16384) {
            short r;

            if (*(int *)(p + 0x4C) >= 31) {
                AP1Turn(self, D_0063C446);
                if (AP1JumpReq(self, 2, p + 0xF0)) {
                    *(int *)(p + 0x4C) = 0;
                    return 2;
                }
            }
            r = D_0063C448;
            r = r > 12288 ? 12288 : (r < -12288 ? -12288 : r);
            AP1Turn(self, r);
            return -1;
        }
    }

    if (*(int *)(p + 0xDC) != 0 && D_0063C44C != 0) {
        if ((D_0063C446 < 0 ? -D_0063C446 : D_0063C446) < 8192) {
            if (D_0063C440 < 150.0f) {
                short r = D_0063C446;

                r = r > 4096 ? 4096 : (r < -4096 ? -4096 : r);
                AP1Turn(self, r);
                if (AP1MotReq(self, 3))
                    return 3;
            }
        }
    }

    if (D_0071EC64[0] > 100.0f) {
        if (VectorLengthSquare(D_0071EC70) < 10000.0f) {
            if (AP1JumpReq(self, 2, &ap1BoxedInJump)) {
                *(int *)(p + 0x4C) = 0;
                return 2;
            }
        }
    }

    if (D_0071EC84[0] > 100.0f) {
        if (VectorLengthSquare(D_0071ECB0) < 10000.0f) {
            if (AP1JumpReq(self, 2, &ap1BoxedInJump)) {
                *(int *)(p + 0x4C) = 0;
                return 2;
            }
        }
    }

    if (*(int *)(p + 0xAC) != 0) {
        short r = D_0063C454;

        r = r > 4096 ? 4096 : (r < -4096 ? -4096 : r);
        AP1Turn(self, r);
        if (D_0063C450 < 50.0f) {
            if (AP1MotReq(self, 0))
                return 0;
        }
        return AP1MotReq(self, 1) == 0 ? -1 : 1;
    }

    if (D_0063C450 < 100.0f) {
        if (AP1MotReq(self, 0))
            return 0;
    }

    if (*(int *)(p + 0xDC) != 0 && D_0063C44C != 0 && D_0063C440 < 300.0f) {
        short r = D_0063C446;

        r = r > 512 ? 512 : (r < -512 ? -512 : r);
        AP1Turn(self, r);
    }

    {
        short r = D_0063C454;

        r = r > 512 ? 512 : (r < -512 ? -512 : r);
        AP1Turn(self, r);
    }
    return AP1MotReq(self, 1) ? 1 : -1;
}

void hehehe(char *a0)
{
    debug_StdPrintfDummy(ap1ModeName[*(int *)(*(char **)(a0 + 0x164) + 0x34)]);
}

void SleepAP1(int *a0)
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

void WakeUpAP1(int *a0)
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
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *dst, void *m, void *src);
/* kept local: this TU's uses of _Sqrt do not fit the prototype in Matrix.h */
extern float _Sqrt(float x);
/* kept local: this TU's uses of _SubVectorXYZ do not fit the prototype in Matrix.h */
extern void _SubVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of VectorLength do not fit the prototype in matrixDrive.h */
extern float VectorLength(void *v);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float s);
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);

typedef struct AP1Mtx {
    float m[16];
} __attribute__((aligned(16))) AP1Mtx;

static inline int AP1GetVerticalAngle(char *g, AP1Vec *v)
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

static inline void AP1ToLocal(char *self, AP1Vec *v)
{
    AP1Mtx m;

    GetRootMatrix(&m, self);
    MatrixDrive_SetTransposeMatrix(&m, &m);
    _ApplyMatrix(v, &m, v);
}

extern AP1Vec D_0071EC40;
extern AP1Vec D_0071EC50;
extern AP1Vec D_0071EC60;
extern AP1Vec D_0071EC80;
extern AP1Vec D_0071EC90;
extern AP1Vec D_0071ECA0;
extern AP1Vec D_0071ECC0;
extern int D_00639EA4;
/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *src);
/* kept local: this TU's uses of _InterVectorXYZ do not fit the prototype in Matrix.h */
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
/* kept local: this TU's uses of CheckFloorAttribute do not fit the prototype in motionManager2.h */
extern int CheckFloorAttribute(int self, int attr);

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
    char *boyObj;
    char *host;
    int r;

    p = *(char **)((char *)self + 0x164);
    *(int *)(p + 0x34) = 5;
    *(int *)(p + 0x4C) = 0;

    while (1) {
        boyObj = (char *)D_00639EA4;
        GetRootPosition(&D_0071ECC0, (char *)self);
        GetRootPosition(&boy, boyObj);
        boy.y -= *(float *)(*(int *)(boyObj + 0x15C) + 0x160) - 10.0f;
        D_0063C440 = AP1GetDirection(&D_0071EC40, &D_0071EC60, &boy, &D_0071ECC0);
        D_0063C444 = AP1GetVerticalAngle(boyObj, &D_0071EC40);
        AP1ToLocal((char *)self, &D_0071EC40);
        CopyVector(&D_0071EC50, &D_0071EC40);
        D_0071EC50.y = 0.0f;
        _NormalizeVector(&D_0071EC50, &D_0071EC50);
        D_0063C446 = GetTableArcTan2(D_0071EC50.x, D_0071EC50.z);
        D_0063C448 = D_0063C446 - 32768;
        CopyVector(D_0071EC70, &D_0071EC60);
        D_0071EC70[1] = 0.0f;
        D_0063C44C = IsBoyStatus_NotDanger() == 0;

        host = *(char **)(p + 0xA8);
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
            look.y -= *(float *)(*(int *)(boyObj + 0x15C) + 0x160) - 10.0f;
            hold = 0;
        }

        D_0063C450 = AP1GetDirection(&D_0071EC90, &D_0071EC80, &look, &D_0071ECC0);
        AP1ToLocal((char *)self, &D_0071EC90);
        CopyVector(&D_0071ECA0, &D_0071EC90);
        D_0071ECA0.y = 0.0f;
        _NormalizeVector(&D_0071ECA0, &D_0071ECA0);
        D_0063C454 = GetTableArcTan2(D_0071ECA0.x, D_0071ECA0.z);
        CopyVector(D_0071ECB0, &D_0071EC80);
        D_0071ECB0[1] = 0.0f;

        if (ap1ModeAI[*(int *)(p + 0x34)] != 0) {
            r = ap1ModeAI[*(int *)(p + 0x34)]((int)self);
            if (r != -1) {
                *(int *)(p + 0x34) = r;
            }
        }
        if (*(int *)(p + 0x34) == 4) {
            break;
        }

        if (CheckFloorAttribute((int)self, 0x800) || CheckFloorAttribute((int)self, 0x900)) {
            iosOmSendMail((int)self, 0xDF, (int)self);
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

void hitProc(int a0)
{
    AP1MotReqForce(a0, 5);
}

void SetAP1DeadStatus(int *a0)
{
    typedef union {
        int i;
        long long ll;
    } U;

    int s = ((U *)((char *)a0 + 0x164))->i;
    *(int *)(s + 0x34) = 4;
    ((U *)(s + 0x18))->ll &= ~(1LL << 32);
    *(char *)(((U *)((char *)a0 + 0x164))->i + 0x1DA) = 1;
    AP1MotReqForce((int)a0, 5);
}

extern int D_00639EAC;

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
static inline void AP1SetMode(char *self, int mode)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(self + 0x164);

    *(int *)(p + 0x34) = mode;
    ((U *)(p + 0x18))->ll &= ~(1LL << 32);
    *(char *)(*(char **)(self + 0x164) + 0x1DA) = 1;
}

static inline void AP1DeadEffect(char *self)
{
    char *p = *(char **)(self + 0x164);

    if (*(int *)(p + 0x34) != 4) {
        int pos[4];
        int quat[4];

        GetRootPosition(pos, self);
        GetRootQuaternion(quat, self);
        SetParticleEffect(12, pos, quat);
    }
}

static inline void AP1DeadMode(char *self)
{
    if (*(int *)(*(char **)(self + 0x164) + 0x34) != 4)
        AP1SetMode(self, 4);
}

static inline void AP1DeadEffectHit(char *self)
{
    char *p = *(char **)(self + 0x164);

    if (*(int *)(p + 0x34) != 4) {
        int pos[4];
        int quat[4];

        AP1SetMode(self, 4);
        GetRootPosition(pos, self);
        GetRootQuaternion(quat, self);
        SetParticleEffect(49, pos, quat);
        hitProc((int)self);
    }
}

static inline void AP1SetHold(char *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(self + 0x164);

    ((U *)(p + 0x20))->ll |= 0x200000;
}

static inline void AP1ClrHold(char *self)
{
    typedef union {
        int i;
        long long ll;
    } U;

    char *p = *(char **)(self + 0x164);

    ((U *)(p + 0x20))->ll &= ~0x200000;
}

void AP1BeforeFunc(char *self)
{
    AP1MailQueue *q = (AP1MailQueue *)(self + 0x54);
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
            hitProc((int)self);
            AP1DeadEffect(self);
            AP1DeadMode(self);
            iosPadActRequest(D_00639EAC, 17);
            ExecuteSEPackage(self, 105);
            break;

        case 26:
        case 38:
            AP1DeadEffect(self);
            AP1DeadMode(self);
            hitProc((int)self);
            break;

        case 223:
            AP1DeadMode(self);
            hitProc((int)self);
            break;
        }
    }
    q->num = 0;
}

typedef struct AP1Spec {
    float a;      /* 0x00 */
    float b;      /* 0x04 */
    float c;      /* 0x08 */
    int unk0C[4]; /* 0x0C */
    float d;      /* 0x1C */
} AP1Spec;

extern AP1Spec D_0062B588[];
extern void *D_00639EA8;
/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);
void subAP1Control(int x);

void actAP1Start(char *g)
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
    *(char *)(*(int *)(g + 0x164) + 0x1DA) = 1;

    ACTGameView_Add(D_00639EA8, g);

    _ACTWait(1);

    *(int *)(s + 0x48) = GetAP1SpecType(g);

    {
        AP1Vec v = {D_0062B588[*(int *)(s + 0x48)].a, D_0062B588[*(int *)(s + 0x48)].b,
                    D_0062B588[*(int *)(s + 0x48)].c, 0};

        CopyVector(s + 0xF0, &v);
    }

    *(int *)(s + 0xDC) = (unsigned int)D_0062B588[*(int *)(s + 0x48)].d;
    actCreateSubThread(subAP1BrainMain, 20);
    actCreateSubThread(subAP1Control, 21);
}

int IsActCharDead(int *a0)
{
    int *v1 = (int *)a0[0x164 / 4];
    long x = *(unsigned int *)((char *)v1 + 0x1C);
    return (((int)x) & 1) ^ 1;
}

void SetAP1HostGObj(char *self, int val)
{
    *(int *)(*(char **)(self + 0x164) + 0xA8) = val;
}

void SetAP1PriorLevel(char *self, int val)
{
    *(int *)(*(char **)(self + 0x164) + 0xAC) = val;
}

extern char D_0063B6F8[];

char *GetAP1AIMode(char *self)
{
    char *p = *(char **)(self + 0x164);

    if (p == 0 || *(unsigned int *)(p + 0x34) >= 6) {
        return D_0063B6F8;
    }
    return ap1ModeTag[*(int *)(p + 0x34)];
}

int jumpAI(int a0)
{
    return AP1MotReq(a0, 0) ? 0 : -1;
}

int attackAI(int a0)
{
    return AP1MotReq(a0, 0) ? 0 : -1;
}

void subAP1Control(int x)
{
    volatile int local = x;
}
