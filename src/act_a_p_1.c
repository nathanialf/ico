#include "common.h"
#include "ico/types.h"

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

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", subAP1BrainMain);

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

INCLUDE_ASM("asm/nonmatchings/src/act_a_p_1", AP1BeforeFunc);

typedef struct AP1Spec {
    float a;      /* 0x00 */
    float b;      /* 0x04 */
    float c;      /* 0x08 */
    int unk0C[4]; /* 0x0C */
    float d;      /* 0x1C */
} AP1Spec;

typedef struct AP1Vec {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) AP1Vec;

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
