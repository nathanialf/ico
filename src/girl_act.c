#include "common.h"

typedef struct {
    char _0[0x184];
    int f_184;          /* 0x184 */
    char _188[0x8];
} HangOrientEntry;

typedef struct {
    char _0[0x20];
    float f_20;        /* 0x20 */
    char _24[0x0C];
    float sub30[4];    /* 0x30 */
    float sub40[4];    /* 0x40 */
    float f_50;        /* 0x50 */
    float f_54;        /* 0x54 */
    signed char f_58;  /* 0x58 */
    signed char f_59;
    signed char f_5A;
    signed char f_5B;
    signed char f_5C;
    signed char f_5D;
    signed char f_5E;
} GirlStand;






extern int D_0028829C;
extern void *D_00631AE8;
extern int *D_00631AE4;
extern int D_006ABDE0[100];
extern void func_0014B330(char *self, unsigned int a1, float v);
extern int D_0028A890[];
extern void brainLevelProcess();
extern void ACTLookTargetSystem_Exec(void);
extern int D_00559430[];
extern void debug_assertMessage();
extern float MatrixDrive_GetTurnYAngleXZ(float a);
extern float func_00243950(void *a, void *b);

float GetEyeDirection(float *p0, float *p1, float *p2) {
    float d1[4];
    float d2[4];
    float r1, r2;
    float a, b, c, mdret;
    int ci;

    d1[0] = p1[0] - p0[0];
    d1[2] = p1[2] - p0[2];
    d1[1] = 0.0f;
    d2[0] = p2[0] - p0[0];
    d2[2] = p2[2] - p0[2];
    d2[1] = 0.0f;
    r1 = func_00243950(d1, d2);
    if (r1 < 0.0f) {
        return MatrixDrive_GetTurnYAngleXZ(func_00243950(d2, d2));
    }
    d2[0] = p2[0] - p1[0];
    d2[1] = 0.0f;
    d2[2] = p2[2] - p1[2];
    r2 = func_00243950(d1, d2);
    if (-r2 < 0.0f) {
        return MatrixDrive_GetTurnYAngleXZ(func_00243950(d2, d2));
    }
    a = -(p1[0] - p0[0]);
    b = p1[2] - p0[2];
    c = p0[2] * p1[0] - p0[0] * p1[2];
    mdret = MatrixDrive_GetTurnYAngleXZ(b * b + a * a);
    ci = (int)(b * p2[0] + a * p2[2] + c);
    ci = __builtin_abs(ci);
    return (float)ci / mdret;
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", funcGirlHandDisconnect);

void GirlBrainClearTarget(void) {
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_00559430);
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_DecideMode);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016A828);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016A9E8);

void func_0016AC10(void)
{
    brainLevelProcess(D_0028A890);
}

void subGirlBrainMain(int *self) {
    int v = ((int *)self[0x164/4])[0x30/4];
    if (v == 10) {
        func_0014B330(self, 5, 1.5f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Pulledup);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", ATGoalTurnMail);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Attract);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", WayTest);

extern char D_002882D0[];
extern int D_00631AE4__p4 __asm__("D_00631AE4");
extern void *D_00629DE4, *D_00631AE8__p4 __asm__("D_00631AE8");
extern void GetHeightOfWallFromGObj(void *out, void *obj);
extern void GetRootMatrixByDObj(void *out, void *obj);

void subGirlControl(void) {
    GetRootMatrixByDObj(D_002882D0 + 0x00, D_00631AE8__p4);
    GetRootMatrixByDObj(D_002882D0 + 0x20, D_00631AE4__p4);
    GetHeightOfWallFromGObj(D_002882D0 + 0x10, D_00631AE8__p4);
    GetHeightOfWallFromGObj(D_002882D0 + 0x30, D_00631AE4__p4);
}

extern unsigned char D_00282AC0[];
extern void func_002641D8(void *a0, int a1, int a2);

void subGirlCollision(void) {
    func_002641D8(D_00282AC0, 0, 0x5910);
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetBoyMode);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016CED0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016D330);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledReady);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledGo);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016E910);

extern void BoxBarSoundOn(void *, int);
extern char D_00559670[];
extern char D_00559680[];
extern int HandCameraCorrect(void *buf, void *vec);
extern void debug_assertMessage__p4(void *a0) __asm__("debug_assertMessage");
extern void funcGirlHandDisconnect();
extern void func_00104748(void *, void *);

void actGirlDitch3mReady(void *a0, int a1) {
    char buf[0x20];
    void *de8 = D_00631AE8__p4;
    int s3 = a1 & 0xFF;
    int r;
    void *v1;
    void *dst;
    func_00104748(buf, de8);
    r = HandCameraCorrect(buf, a0);
    r = (r < 0) ? -r : r;
    if (r < 0x2E) {
        return;
    }
    v1 = *(void **)((char *)de8 + 0x164);
    dst = *(void **)((char *)v1 + 0x678);
    *(float *)((char *)dst + 0x3D0) = *(float *)((char *)a0 + 0x0);
    *(float *)((char *)dst + 0x3D4) = *(float *)((char *)a0 + 0x4);
    *(float *)((char *)dst + 0x3D8) = *(float *)((char *)a0 + 0x8);
    funcGirlHandDisconnect(buf + 0x10, de8);
    r = HandCameraCorrect(buf + 0x10, a0);
    if (r > 0) {
        debug_assertMessage__p4(D_00559670);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xDC);
        } else {
            BoxBarSoundOn(de8, 0xDE);
        }
    } else {
        debug_assertMessage__p4(D_00559680);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xDB);
        } else {
            BoxBarSoundOn(de8, 0xDD);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlReadyMove);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRescueDst);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016F2A8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportBGBegin);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlStart);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GirlAct_BoyAndMeCollisionMail);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170380);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", IsGirlStatusEscortEnable);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", DebugDispAutoEscort);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170950);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", ACTGame_GirlBeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170ED8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBBegin);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00171738);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001718F0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBLoop);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBEnd);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHangG3M);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001725C8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00173060);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlDitch3mExec);

extern GirlStand D_gStand __asm__("D_002883D0");
extern int HandCameraCorrect(void *buf, void *vec);

void actGirlStand(void) {
    volatile int home;
    int uninit;
    float one = 1.0f;
    home = uninit;
    if (D_gStand.f_20 < 2.0f) {
        D_gStand.f_58 = 1;
    }
    if ((HandCameraCorrect(D_gStand.sub40, D_gStand.sub30) < 0
            ? -HandCameraCorrect(D_gStand.sub40, D_gStand.sub30)
            : HandCameraCorrect(D_gStand.sub40, D_gStand.sub30)) >= 0x3D) {
        D_gStand.f_59 = 1;
    }
    if (D_gStand.f_54 > 15.0f) {
        D_gStand.f_5E = 1;
    }
    if (one * 100.0f < D_gStand.f_50) {
        D_gStand.f_5A = 1;
    }
    if (one * 125.0f < D_gStand.f_50) {
        D_gStand.f_5B = 1;
    }
    if (one * 135.0f < D_gStand.f_50) {
        D_gStand.f_5C = 1;
    }
    if (D_gStand.f_50 < 90.0f) {
        D_gStand.f_5D = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlWalk);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRun);

extern HangOrientEntry D_00565060[];

#define SUB(g)  (*(int *)((char *)(g) + 0x164))
#define REF(g)  (*(int *)((char *)(g) + 0x15C))

void actGirlHang(int *a0, int *a1, int *a2, int *a3) {
    volatile int home;
    int uninit;
    int *g = (int *)D_00631AE4__p4;
    int x;
    int r4;

    home = uninit;

    *a0 = *(int *)(SUB(g) + 0x30);
    *a1 = 0;
    *a2 = 0;
    *a3 = 0;
    x = *a0;
    switch (x) {
    case 8:
        *a0 = 1;
        break;
    case 2:
    case 3:
        if (*(int *)(SUB(g) + 0x144) != 0) {
            *a0 = 2;
        }
        {
        int idx = *(int *)(REF(g) + 0x4A0);
        HangOrientEntry *e = (HangOrientEntry *)(idx * 0x190 + (int)D_00565060);
        switch ((unsigned int)e->f_184 >> 30) {
        case 1:
            *a0 = 2;
            break;
        case 2:
            *a0 = 3;
            break;
        }
        }
        r4 = *a0;
        if (r4 == 3) {
            long long v = *(long long *)(*(int *)(SUB(g) + 0x678) + 0x408);
            if ((int)((unsigned long long)v >> 33) & 1) {
                *a0 = 1;
                r4 = 1;
            } else if ((int)(v >> 32) & 1) {
                *a0 = 2;
                r4 = 2;
            }
        }
        if (r4 == 2) {
            long long v = *(long long *)(*(int *)(SUB(g) + 0x678) + 0x408);
            if ((int)((unsigned long long)v >> 33) & 1) {
                *a0 = 1;
            }
        }
        break;
    case 36:
        if (*(int *)(SUB(g) + 0x38) == 0x55) {
            *a2 = 1;
        } else {
            *a3 = 1;
        }
        break;
    case 5:
    case 17:
    case 18:
    case 68:
        *a0 = 3;
        break;
    }
}
#undef SUB
#undef REF

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBHang);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001742A0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001743F0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174558);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174640);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174778);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174A48);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174BA0);

extern void func_00243978(void *a, void *b);
extern void func_00243AE8(void *out, void *m1, void *m2);
extern void *subCommonIdle(void *a0);

void actGirlAttack(void *a0) {
    float res[4];
    float m1[4];
    float m2[4];
    void *dobj;
    void *sub;
    float a;

    BoxBarSoundOn(a0, 0xFD);
    dobj = D_00631AE4__p4;
    sub = *(void **)((char *)dobj + 0x164);
    if (*(int *)((char *)sub + 0x30) == 1) {
        return;
    }
    GetRootMatrixByDObj(m1, dobj);
    GetRootMatrixByDObj(m2, a0);
    func_00243AE8(res, m1, m2);
    func_00243978(res, res);
    a = (float)HandCameraCorrect(res, subCommonIdle(a0));
    if (a < 0.0f ? -a < 45.0f : a < 45.0f) {
        BoxBarSoundOn(a0, 0xFE);
    } else if (a < 0.0f ? 135.0f < -a : 135.0f < a) {
        BoxBarSoundOn(a0, 0xFF);
    } else if (45.0f < a) {
        BoxBarSoundOn(a0, 0x100);
    } else {
        BoxBarSoundOn(a0, 0x101);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBecall);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBehanged);

void func_001752D0(int *self)
{
    int *p;
    p = (int *)self[0x59];
    D_006ABDE0[0] = 0;
    D_006ABDE0[1] = 0;
    if (p[0xC] != 0x45) {
        *(long long *)((char *)p + 0x20) &= ~0x200LL;
    }
}

int func_00175308(void)
{
    extern unsigned int D_0028829C_far[] __asm__("D_0028829C");
    int *a, *b, *sub, *sub2, *p;
    b = D_00631AE8;
    if (D_0028829C_far[0] != 7) goto ret0;
    a = D_00631AE4;
    sub = (int *)a[0x164 / 4];
    if (sub[0x30 / 4] != 0x4B) goto ret0;
    sub2 = (int *)b[0x164 / 4];
    p = (int *)sub2[0x678 / 4];
    return p[0x374 / 4];
ret0:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00175350);

extern unsigned int _ACTWait(int a0);

void func_00175420(void *volatile a0) {
    int flag;
    for (;;) {
        unsigned int state = *(unsigned int *)(*(int *)((char *)D_00631AE4__p4 + 0x164) + 0x30);
        flag = 0;
        if (state < 0x68) { if (state >= 0x65) goto s; }
    g:
        if (!(flag & 0xff)) BoxBarSoundOn(a0, 0x164);
        _ACTWait(1);
        continue;
    s:
        flag = 1;
        goto g;
    }
}

void func_00175480(void *volatile a0) {
    for (;;) {
        BoxBarSoundOn(a0, 0xB7);
        _ACTWait(1);
    }
}

extern int ACTNotNeedCameraOffset(void);
extern void ACTWay_SetBeginPositionIllegal(void *a0);

void func_001754B0(void *volatile a0) {
    ACTWay_SetBeginPositionIllegal(a0);
    for (;;) {
        if (ACTNotNeedCameraOffset() == 0) {
            BoxBarSoundOn(a0, 0x176);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001754F8);

extern char D_00559AA0[];

void func_001755F8(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage__p4((char *)D_00559AA0);
    s0[0x30 / 4] = 1;
    _ACTWait(0);
}

extern char D_00559AB8[];
extern unsigned int _ACTWait(int a0);
extern void debug_assertMessage__p4(void *a0) __asm__("debug_assertMessage");

void afterGirlHand(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage__p4((char *)D_00559AB8);
    s0[0x30 / 4] = 0x2;
    _ACTWait(0);
}

extern char D_00559AD0[];
extern void debug_assertMessage__p4(void *a0) __asm__("debug_assertMessage");

void afterGirlPulledGo(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage__p4((char *)D_00559AD0);
    s0[0x30 / 4] = 0x3;
    _ACTWait(0);
}

void actGirlJump(volatile unsigned int a0) {
    int cond = 0;
    if (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x678) + 0x834) == 0x57) {
        cond = (*(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x678) + 0x830) == 4);
    }
    while (1) {
        if (cond) {
            BoxBarSoundOn((void *)a0, 0xB7);
        }
        _ACTWait(1);
    }
}

extern void BoxBarSoundOn(void *a0, int a1);

void func_00175740(volatile int a0)
{
    int flag = 0;
    if (*(int *)((char *)*(int **)((char *)*(int **)((char *)a0 + 0x164) + 0x678) + 0x834) == 0x57 &&
        *(int *)((char *)*(int **)((char *)*(int **)((char *)a0 + 0x164) + 0x678) + 0x830) == 4) {
        flag = 1;
    }
    while (1) {
        if (flag) {
            BoxBarSoundOn((void *)a0, 0xB7);
        }
        BoxBarSoundOn((void *)a0, 0x13A);
        _ACTWait(1);
    }
}

extern char D_00559B00[];

void func_001757B8(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage__p4((char *)D_00559B00);
    s0[0x30 / 4] = 0xF;
    _ACTWait(0);
}

