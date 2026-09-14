#include "common.h"
#include "ico/types.h"
#include "sugiCommon.h"

extern float D_0063C440;
extern short D_0063C444;
extern short D_0063C446;
extern float D_0063C450;
extern short D_0063C454;
extern int AP1MotReq(char *self, int mot);
extern int AP1Turn(char *self, int rot);

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
extern float D_00639394;
extern float D_00639398;
extern float D_0071EC64[];
extern float D_0071EC70[];
extern float D_0071EC84[];
extern float D_0071ECB0[];
extern char D_004E5A50[];
extern int AP1JumpReq(char *self, int kind, void *dst);
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
        if (VectorLengthSquare(D_0071EC70) < D_00639394) {
            if (AP1JumpReq(self, 2, D_004E5A50)) {
                *(int *)(p + 0x4C) = 0;
                return 2;
            }
        }
    }

    if (D_0071EC84[0] > 100.0f) {
        if (VectorLengthSquare(D_0071ECB0) < D_00639398) {
            if (AP1JumpReq(self, 2, D_004E5A50)) {
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

extern char *D_004E5A78[];
extern void debug_StdPrintfDummy(char *a0);

void hehehe(char *a0)
{
    debug_StdPrintfDummy(D_004E5A78[*(int *)(*(char **)(a0 + 0x164) + 0x34)]);
}

extern int AP1MotReqForce(int *self, int a1);

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

extern char D_0061EE98[];

void WakeUpAP1(int *a0)
{
    typedef union {
        int i;
        long long ll;
    } U;

    int s = ((U *)((char *)a0 + 0x164))->i;

    if (*(int *)(s + 0x34) == 4) {
        debug_StdPrintfDummy(D_0061EE98);
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
extern void GetRootPosition(void *dst, char *gobj);
extern void GetRootQuaternion(void *dst, char *gobj);
extern void GetInverseQuaternion(void *dst, void *src);
extern void GetMatrixFromQuaternion(void *dst, void *q);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern float _Sqrt(float x);
extern int GetTableArcTan2(float y, float x);
extern void _SubVectorXYZ(void *dst, void *a, void *b);
extern float VectorLength(void *v);
extern void _ScaleVectorXYZ(void *dst, void *src, float s);
extern void GetRootMatrix(void *dst, char *self);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);

typedef struct AP1Vec {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) AP1Vec;

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
extern float D_0063939C;
extern int (*D_004E5A60[])(int self);
extern char D_0061EEB8[];
extern void CopyVector(void *dst, void *src);
extern void _NormalizeVector(void *dst, void *src);
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
extern int IsBoyStatus_NotDanger(void);
extern int iosOmSendMail(int dst, int mail, int src);
extern int CheckFloorAttribute(int self, int attr);
extern void _ACTWait(int frames);

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
                if (D_0063939C < distance_squared_b(&dest, &smooth)) {
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

        if (D_004E5A60[*(int *)(p + 0x34)] != 0) {
            r = D_004E5A60[*(int *)(p + 0x34)]((int)self);
            if (r != -1) {
                *(int *)(p + 0x34) = r;
            }
        }
        if (*(int *)(p + 0x34) == 4) {
            break;
        }

        if (CheckFloorAttribute((int)self, 0x800) || CheckFloorAttribute((int)self, 0x900)) {
            iosOmSendMail((int)self, 0xDF, (int)self);
            debug_StdPrintfDummy(D_0061EEB8);
        }
        *(int *)(p + 0x4C) = *(int *)(p + 0x4C) + 1;
        _ACTWait(1);
    }

    while (1) {
        _ACTWait(1);
    }
}

extern int AP1MotReqForce(int *self, int a1);

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

extern void GetRootPosition(void *dst, char *gobj);
extern void GetRootQuaternion(void *dst, char *gobj);
extern void SetParticleEffect(int id, void *pos, void *quat);
extern int iosPadActRequest(int port, int id);
extern void ExecuteSEPackage(char *self, int id);
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
extern char *actInitialize(char *g);
extern void actInitialize_ext_charcter(char *g);
extern void ACTGameView_Add(void *view, char *g);
extern void _ACTWait(int frames);
extern int GetAP1SpecType(char *g);
extern void CopyVector(void *dst, void *src);
extern void actCreateSubThread(void *entry, int pri);
extern void subAP1BrainMain(int x);
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

extern char *D_004E5A30[];
extern char D_0063B6F8[];

char *GetAP1AIMode(char *self)
{
    char *p = *(char **)(self + 0x164);

    if (p == 0 || *(unsigned int *)(p + 0x34) >= 6) {
        return D_0063B6F8;
    }
    return D_004E5A30[*(int *)(p + 0x34)];
}

extern int AP1MotReq();

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
