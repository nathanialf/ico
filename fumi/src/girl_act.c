#include "common.h"

/* girl_act 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; } GirlState;

extern float func_0023FE70(void *a, void *b);
extern float MatrixDrive_GetTurnYAngleXZ(float a);

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
    r1 = func_0023FE70(d1, d2);
    if (r1 < 0.0f) {
        return MatrixDrive_GetTurnYAngleXZ(func_0023FE70(d2, d2));
    }
    d2[0] = p2[0] - p1[0];
    d2[1] = 0.0f;
    d2[2] = p2[2] - p1[2];
    r2 = func_0023FE70(d1, d2);
    if (-r2 < 0.0f) {
        return MatrixDrive_GetTurnYAngleXZ(func_0023FE70(d2, d2));
    }
    a = -(p1[0] - p0[0]);
    b = p1[2] - p0[2];
    c = p0[2] * p1[0] - p0[0] * p1[2];
    mdret = MatrixDrive_GetTurnYAngleXZ(b * b + a * a);
    ci = (int)(b * p2[0] + a * p2[2] + c);
    ci = __builtin_abs(ci);
    return (float)ci / mdret;
}


typedef struct { int f_0; float f_4; int f_8; int f_C; } GirlHandDisc;

extern int DebugDisp1CollisionWithColor(void *a0, int a1);
extern void func_0023FDD8(void *a0, int a1, void *a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", funcGirlHandDisconnect);


extern void ACTLookTargetSystem_Exec(void);
extern void debug_assertMessage(void *a0);
extern char D_00553720[];
void GirlBrainClearTarget(void) {
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_00553720);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", girlBrainMain_DecideMode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00168658);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00168818);

extern void brainLevelProcess(void *a0);
extern int D_00286A90[];

void func_00168A40(void) {
    brainLevelProcess(D_00286A90);
}

extern void func_00149CD8(void *a0, int a1, float a2);

void subGirlBrainMain(void *a0) {
    GirlState *p = *(GirlState **)((char *)a0 + 0x164);
    if (p->f_30 == 0xA) {
        func_00149CD8(a0, 5, 1.5f);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", subGirlBrain_Pulledup);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", ATGoalTurnMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", subGirlBrain_Attract);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", WayTest);

extern char D_00284640[];
extern void *D_00629DE4, *D_00629DE8;
extern void GetRootMatrixByDObj(void *out, void *obj);
extern void GetHeightOfWallFromGObj(void *out, void *obj);
void subGirlControl(void) {
    GetRootMatrixByDObj(D_00284640 + 0x00, D_00629DE8);
    GetRootMatrixByDObj(D_00284640 + 0x20, D_00629DE4);
    GetHeightOfWallFromGObj(D_00284640 + 0x10, D_00629DE8);
    GetHeightOfWallFromGObj(D_00284640 + 0x30, D_00629DE4);
}

extern unsigned char D_0027EE30[];
extern void func_00260568(void *a0, int a1, int a2);

void subGirlCollision(void) {
    func_00260568(D_0027EE30, 0, 0x5910);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", GetBoyMode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016AC18);

typedef struct {
    int count;   /* 0x0 */
    int mode;    /* 0x4 */
    int unk8;    /* 0x8 */
    int unkC;    /* 0xC */
    float x;     /* 0x10 */
    float y;     /* 0x14 */
    float z;     /* 0x18 */
} CamRec;
typedef struct { float x, y, z; } Vec3;
extern int D_006A58A0[];
extern int func_001443B8(void *buf, void *a1, int id);
extern int HandCameraCorrect(void *buf, void *vec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016B028);




INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlPulledReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlPulledGo);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016C580);

extern void func_00104548(void *, void *);
extern int HandCameraCorrect(void *, void *);
extern void BoxBarSoundOn(void *, int);
extern char D_00553960[];
extern char D_00553970[];

void actGirlDitch3mReady(void *a0, int a1) {
    char buf[0x20];
    void *de8 = D_00629DE8;
    int s3 = a1 & 0xFF;
    int r;
    void *v1;
    void *dst;
    func_00104548(buf, de8);
    r = HandCameraCorrect(buf, a0);
    r = (r < 0) ? -r : r;
    if (r < 0x2E) {
        return;
    }
    v1 = *(void **)((char *)de8 + 0x164);
    dst = *(void **)((char *)v1 + 0x678);
    *(float *)((char *)dst + 0x3B0) = *(float *)((char *)a0 + 0x0);
    *(float *)((char *)dst + 0x3B4) = *(float *)((char *)a0 + 0x4);
    *(float *)((char *)dst + 0x3B8) = *(float *)((char *)a0 + 0x8);
    funcGirlHandDisconnect(buf + 0x10, de8);
    r = HandCameraCorrect(buf + 0x10, a0);
    if (r > 0) {
        debug_assertMessage(D_00553960);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xD9);
        } else {
            BoxBarSoundOn(de8, 0xDB);
        }
    } else {
        debug_assertMessage(D_00553970);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xD8);
        } else {
            BoxBarSoundOn(de8, 0xDA);
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlReadyMove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlRescueDst);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016CF18);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlSupportBGBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlStart);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", GirlAct_BoyAndMeCollisionMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016DFF0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", IsGirlStatusEscortEnable);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", DebugDispAutoEscort);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016E5C0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", ACTGame_GirlBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016EB48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlSupportGBBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016F3A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016F560);

extern float RotateAccordingToStick_PatternThree(void *, void *);
extern int func_0016F560(void *, void *);
extern float D_006290C4;
extern float D_006290C8;

int actGirlSupportGBLoop(void) {
    char buf[0x20];
    int rv = 0;
    float diff;
    if (D_00629DE4 == 0) {
        goto ret0;
    }
    if (D_00629DE8 == 0) {
        return 0;
    }
    GetHeightOfWallFromGObj(buf, D_00629DE4);
    GetHeightOfWallFromGObj(buf + 0x10, D_00629DE8);
    diff = *(float *)(buf + 0x4) - *(float *)(buf + 0x14);
    if (diff < 0.0f) {
        if (-diff > 200.0f) {
            goto set;
        }
        goto test;
    }
    if (diff > 200.0f) {
    set:
        rv = 1;
    }
test:
    if (rv == 0) {
        goto ret0;
    }
    if (RotateAccordingToStick_PatternThree(buf, buf + 0x10) < D_006290C4) {
        return 1;
    }
    if (RotateAccordingToStick_PatternThree(buf, buf + 0x10) < D_006290C8) {
        if (func_0016F560(buf, buf + 0x10) != 0) {
            return 1;
        }
    }
ret0:
    return 0;
}



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlSupportGBEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlHangG3M);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00170220);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00170CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlDitch3mExec);

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
extern GirlStand D_gStand __asm__("D_00284740");

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



extern void traceLine();
extern unsigned char D_00284740[];
extern char D_00553BF0[];
extern char D_00553C00[];
extern char D_00553C20[];
extern int D_0062AF84;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlWalk);



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlRun);

typedef struct {
    char _0[0x184];
    int f_184;          /* 0x184 */
    char _188[0x8];
} HangOrientEntry;      /* stride 0x190 */

extern HangOrientEntry D_0055DA10[];

#define SUB(g)  (*(int *)((char *)(g) + 0x164))
#define REF(g)  (*(int *)((char *)(g) + 0x15C))

void actGirlHang(int *a0, int *a1, int *a2, int *a3) {
    volatile int home;
    int uninit;
    int *g = (int *)D_00629DE4;
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
        if (*(int *)(SUB(g) + 0x134) != 0) {
            *a0 = 2;
        }
        {
        int idx = *(int *)(REF(g) + 0x490);
        HangOrientEntry *e = (HangOrientEntry *)(idx * 0x190 + (int)D_0055DA10);
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
            long long v = *(long long *)(*(int *)(SUB(g) + 0x678) + 0x3E8);
            if ((int)((unsigned long long)v >> 33) & 1) {
                *a0 = 1;
                r4 = 1;
            } else if ((int)(v >> 32) & 1) {
                *a0 = 2;
                r4 = 2;
            }
        }
        if (r4 == 2) {
            long long v = *(long long *)(*(int *)(SUB(g) + 0x678) + 0x3E8);
            if ((int)((unsigned long long)v >> 33) & 1) {
                *a0 = 1;
            }
        }
        break;
    case 36:
        if (*(int *)(SUB(g) + 0x38) == 0x54) {
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


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlBHang);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00171EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172008);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172170);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172258);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172390);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172638);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172790);

extern void func_00240008(void *out, void *m1, void *m2);
extern void func_0023FE98(void *a, void *b);
extern void *subCommonIdle(void *a0);

void actGirlAttack(void *a0) {
    float res[4];
    float m1[4];
    float m2[4];
    void *dobj;
    void *sub;
    float a;

    BoxBarSoundOn(a0, 0xFA);
    dobj = D_00629DE4;
    sub = *(void **)((char *)dobj + 0x164);
    if (*(int *)((char *)sub + 0x30) == 1) {
        return;
    }
    GetRootMatrixByDObj(m1, dobj);
    GetRootMatrixByDObj(m2, a0);
    func_00240008(res, m1, m2);
    func_0023FE98(res, res);
    a = (float)HandCameraCorrect(res, subCommonIdle(a0));
    if (a < 0.0f ? -a < 45.0f : a < 45.0f) {
        BoxBarSoundOn(a0, 0xFB);
    } else if (a < 0.0f ? 135.0f < -a : 135.0f < a) {
        BoxBarSoundOn(a0, 0xFC);
    } else if (45.0f < a) {
        BoxBarSoundOn(a0, 0xFD);
    } else {
        BoxBarSoundOn(a0, 0xFE);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlBecall);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlBehanged);

extern int D_006A58A0[];

void actGirlAttractAction(void *a0) {
    int *s = *(int **)((char *)a0 + 0x164);
    do { } while (0);
    D_006A58A0[0] = 0;
    D_006A58A0[1] = 0;
    if (*(int *)((char *)s + 0x30) != 0x45) {
        *(long long *)((char *)s + 0x20) &= ~0x40;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", NotNeedBackHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00172FC8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00173028);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00173058);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_001730A0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_001731A0);

extern unsigned int _ACTWait(int a0);

extern char D_00553DA8[];

void afterGirlHand(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00553DA8);
    s0[0x30 / 4] = 0x2;
    _ACTWait(0);
}


extern char D_00553DC0[];

void afterGirlPulledGo(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00553DC0);
    s0[0x30 / 4] = 0x3;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlJump);

extern void BoxBarSoundOn(void *a0, int a1);

void func_001732F0(volatile int a0)
{
    int x = a0;
    int flag = 0;
    if (*(int *)((char *)*(int **)((char *)*(int **)((char *)a0 + 0x164) + 0x678) + 0x814) == 0x57 &&
        *(int *)((char *)*(int **)((char *)*(int **)((char *)a0 + 0x164) + 0x678) + 0x810) == 4) {
        flag = 1;
    }
    while (1) {
        if (flag) {
            BoxBarSoundOn((void *)a0, 0xB4);
        }
        BoxBarSoundOn((void *)a0, 0x136);
        _ACTWait(1);
    }
}

extern char D_00553DF0[];

void func_00173370(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_assertMessage((char *)D_00553DF0);
    s0[0x30 / 4] = 0xF;
    _ACTWait(0);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
    unsigned int       f_2C;  /* 0x2C */
} S_00271240;

typedef struct {
    unsigned int       f_C90;  /* 0xC90 */
    unsigned int       f_1F60;  /* 0x1F60 */
    unsigned int       f_3230;  /* 0x3230 */
    unsigned int       f_57D0;  /* 0x57D0 */
    unsigned int       f_57D4;  /* 0x57D4 */
    unsigned int       f_5850;  /* 0x5850 */
    char               f_58E0;  /* 0x58E0 */
    char               f_58E1;  /* 0x58E1 */
    unsigned char      f_58E3;  /* 0x58E3 */
    unsigned int       f_58E8;  /* 0x58E8 */
    unsigned int       f_58F0;  /* 0x58F0 */
} S_0027EE30;

typedef struct {
    unsigned long long f_58;  /* 0x58 */
    unsigned char      f_59;  /* 0x59 */
    unsigned char      f_5A;  /* 0x5A */
    unsigned char      f_5B;  /* 0x5B */
    unsigned char      f_5C;  /* 0x5C */
    unsigned char      f_5D;  /* 0x5D */
    unsigned char      f_5E;  /* 0x5E */
} S_00284740;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_18;  /* 0x18 */
    unsigned short     f_1C;  /* 0x1C */
    short              f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
} S_00286A90;  /* stride 0x1C */

typedef struct {
    char               f_48;  /* 0x48 */
    char               f_49;  /* 0x49 */
    char               f_4A;  /* 0x4A */
    char               f_4B;  /* 0x4B */
    char               f_4C;  /* 0x4C */
    char               f_4D;  /* 0x4D */
    char               f_4E;  /* 0x4E */
} S_00284750;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_006A58C0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027EC78;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553860;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553890;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005538C0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005538F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553930;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005539A0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00553C40;  /* stride 0x4 */

/* end struct shapes */
