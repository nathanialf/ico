#include "common.h"

typedef union ActStatus {
    unsigned long long ll;
    int i[2];
} ActStatus;

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD0];           /* 0x00 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x15C];          /* 0x000 */
    char *f15C;                 /* 0x15C */
    char pad160[0x4];           /* 0x160 */
    Act *act;                   /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern PObjGObj *scpSearchGobj(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern int scpTriggerFloorAttr(void *a0, int a1);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void iosOmSendMail(void *gobj, int mail, void *src);
extern char *D_00639EA4;
extern char *D_00639EA8;
extern void debug_StdPrintfDummy();
extern Act *actInitialize(int a0);
extern int D_0028F4C0[];
extern float D_0063AA0C;

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGate);
ASM_LIT4_SLOT(D_006398D8, 3000.0f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateChk);
ASM_LIT4_SLOT(D_006398DC, 0.99f);
ASM_LIT4_SLOT(D_006398E0, 0.1f);
ASM_LIT4_SLOT(D_006398E4, 0.8f);
ASM_LIT4_SLOT(D_006398E8, 0.45f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aConte06);
ASM_LIT4_SLOT(D_006398EC, 7300.0f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aConte06Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpen);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpenChk);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09);
ASM_LIT4_SLOT(D_006398F0, 2700.0f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpen2Chk);
ASM_LIT4_SLOT(D_006398F4, 14.8948f);
ASM_LIT4_SLOT(D_006398F8, 210.136f);
ASM_LIT4_SLOT(D_006398FC, 4858.48f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09_2);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpen3);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpen3Chk);
ASM_LIT4_SLOT(D_00639900, 0.99f);
ASM_LIT4_SLOT(D_00639904, 0.1f);
ASM_LIT4_SLOT(D_00639908, 0.8f);
ASM_LIT4_SLOT(D_0063990C, 0.45f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09_3);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateLChk);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateRChk);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aTorch1);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aTorch1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aTorchAllFlagfChk);
ASM_LIT4_SLOT(D_00639910, 0.001f);
ASM_LIT4_SLOT(D_00639914, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aTorchHintChk);
extern ActMail D_004F86B0[];
extern void actSt04aGateLChk(volatile int a0);

void actSt04aGateL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0) {
        gflagOn(0x185);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(0x127, 0, 0);

        D_004F86B0[0].func = actSt04aGateLChk;
        self->mail = D_004F86B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F86D0[];
extern void actSt04aGateRChk(volatile int a0);

void actSt04aGateR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        gflagOn(0x185);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(0x125, 0, -1);

        D_004F86D0[0].func = actSt04aGateRChk;
        self->mail = D_004F86D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt04aTorchXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(0x123, 0, 0);
}
void actSt04aDeadCam(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x8D) == 0 || scpTriggerBall(a0, D_00639EA4, 600.0f) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(0x111, 1400, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(0x112, 1, 0);

    while (stage_CheckAnimationFinish(0x112) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}
extern ActMail D_004F8670[];
extern void actSt04aGateOpen2Chk(volatile int a0);

void actSt04aGateOpen2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8D) == 0) {

        scpSearchGobj(0x29D)->f16C = 0;

        D_004F8670[0].func = actSt04aGateOpen2Chk;
        self->mail = D_004F8670;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8650[];
extern void actSt04aGateOpen2ReadyChk(volatile int a0);

void actSt04aGateOpen2Ready(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8650[0].func = actSt04aGateOpen2ReadyChk;
    self->mail = D_004F8650;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8710[];
extern void actSt04aGirlSitChk(volatile int a0);

void actSt04aGirlSit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8710[0].func = actSt04aGirlSitChk;
    self->mail = D_004F8710;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8730[];
extern void actSt04aTorchHintChk(volatile int a0);

void actSt04aTorchHint(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x99) == 0) {
        D_004F8730[0].func = actSt04aTorchHintChk;
        self->mail = D_004F8730;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8750[];
extern void actSt04aModelOnChk(volatile int a0);

void actSt04aModel(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    scpSearchGobj(0x288)->f16C = 0;

    D_004F8750[0].func = actSt04aModelOnChk;
    self->mail = D_004F8750;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04aEnvSe(volatile int a0)
{
    float f = 0.0f;

    D_0063AA0C = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 5401) {
            D_0063AA0C += 1.0f / 1800.0f;
            if (D_0063AA0C > 1.0f) {
                D_0063AA0C = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actSt04aEnvSeWakare1(volatile int a0)
{
    float f = 0.0f;

    D_0063AA0C = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2201) {
            D_0063AA0C += 1.0f / 3800.0f;
            if (D_0063AA0C > 1.0f) {
                D_0063AA0C = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}
typedef struct { float m[16]; } Mtx44 __attribute__((aligned(16)));
typedef struct { float m[4]; } Vec4;

extern void _ApplyMatrix(int dst, int m, int src);
extern void _NormalizeVector(int dst, int src);
extern char D_0028FF20[];
extern Mtx44 D_004F8610;

void finishCallBackFunc(int a0)
{
    Vec4 v;
    int i;

    _ApplyMatrix((int)&v, *(int *)(*(int *)(a0 + 0x15C) + 0xC), (int)D_0028FF20);
    v.m[1] = 0.0f;
    _NormalizeVector(*(int *)(a0 + 0x15C) + 0x520, (int)&v);

    for (i = 0; i < *(int *)(*(int *)(a0 + 0x15C) + 0x88); i++) {
        *(Mtx44 *)(*(int *)(*(int *)(a0 + 0x15C) + 0x80C) + i * 64) = D_004F8610;
    }
}
extern char D_00618DE0[];
extern char D_00622840[];
extern void StandbyStreamMotion(char *a0);
extern int CheckReadyStreamMotion(void);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern int D_0063BEA8;

void actSt04aGateOpen2ReadyChk(volatile int a0)
{
    int x = a0;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(D_00618DE0);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00622840, i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x20, &D_0063BEA8, 1, 0, 0);
}

void actSt04aEnvSeWakare2(volatile int a0)
{
    float f = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2351) {
            D_0063AA0C -= 1.0f / 720.0f;
            if (D_0063AA0C < 0.0f) {
                D_0063AA0C = 0.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}
typedef struct JimakuSub {
    char unk00[0x2C];           /* 0x0C */
    int  unk2C;                 /* 0x38 */
    int  n;                     /* 0x3C */
    int  unk34;                 /* 0x40 */
    int  unk38;                 /* 0x44 */
    void *unk3C;                /* 0x48 */
    void *unk40;                /* 0x4C */
} JimakuSub;
typedef struct JimakuArg {
    int  cmd;                   /* 0x00 */
    int  unk04;                 /* 0x04 */
    int  done;                  /* 0x08 */
    JimakuSub sub;              /* 0x0C */
} JimakuArg;
extern JimakuArg jimaku_msg;
extern int jimakuOn;
extern void jimakuBegin(int a0);
extern void jimakuJump(int a0);

void actConte09_3Jimaku(volatile int a0)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin((int)&jimaku_msg);
            break;
        case 2470:
            jimaku_msg.sub.unk2C = 91;
            jimaku_msg.sub.unk38 = 300;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 3000.0f);
}
extern void _ACTWait(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C508;

void actConte09_3_demoCancel(volatile int a0)
{
    while (1) {
        _ACTWait(1);
    }
}
void actSt04aGateLSub(volatile int a0)
{
    stage_SetAnimation(0x125, 1, 0);
    while (stage_CheckAnimationFinish(0x125) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C508 = 1;
    _ACTWait(0);
}
void actSt04aGateRSub(volatile int a0)
{
    stage_SetAnimation(0x127, 1, 0);
    while (stage_CheckAnimationFinish(0x127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C508 = 1;
    _ACTWait(0);
}
void actSt04aGirlSitChk(volatile int a0)
{
    int n;

    while (gflagChk(0x8C) == 0) {
        _ACTWait(1);
    }
    ((ActStatus *)(*(char **)(D_00639EA8 + 0x164) + 0x20))->ll |= 0x10000;
    n = 0;
    for (;;) {
        if ((int)(*(unsigned long long *)(*(char **)(D_00639EA8 + 0x164) + 0x20) >> 20) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 3 < n) {
            iosOmSendMail(D_00639EA8, 0x6D, D_00639EA8);
            n = 0;
        }
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aModelOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aModelOffChk);
