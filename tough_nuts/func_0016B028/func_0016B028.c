#include "common.h"

/* girl_act 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; } GirlState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", fzMagnitudeByLineSeg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", GetEyeDirection);

extern void ACTLookTargetSystem_Exec(void);
extern void debug_StdPrintfDummy(void *a0);
extern char D_00553720[];
void GirlBrainClearTarget(void) {
    ACTLookTargetSystem_Exec();
    debug_StdPrintfDummy(D_00553720);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", girlBrainMain_DecideMode);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", sort_list);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", ATGoalTurnMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", subGirlBrain_Attract);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", WayTest);

extern char D_00284640[];
extern void *D_00629DE4, *D_00629DE8;
extern void GetRootMatrixByDObj(void *out, void *obj);
extern void GetHeightOfWallFromGObj(void *out, void *obj);
void girlBrainMain_PositionUpdate(void) {
    GetRootMatrixByDObj(D_00284640 + 0x00, D_00629DE8);
    GetRootMatrixByDObj(D_00284640 + 0x20, D_00629DE4);
    GetHeightOfWallFromGObj(D_00284640 + 0x10, D_00629DE8);
    GetHeightOfWallFromGObj(D_00284640 + 0x30, D_00629DE4);
}

extern unsigned char D_0027EE30[];
extern void memset(void *a0, int a1, int a2);

void subGirlCollision(void) {
    memset(D_0027EE30, 0, 0x5910);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", GetBoyMode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlHand);

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
extern int _RotyGV(void *buf, void *vec);

#define REC (*(CamRec *)D_006A58A0)

int func_0016B028(void *a0, float *a1) {
    float buf0[4];
    float vec[4];
    float buf20[4];
    int s1, abs1, r2, val;
    int two;
    int z2;
    int ret = 0;

    vec[0] = a1[0];
    vec[1] = a1[1];
    vec[2] = a1[2];
    func_001443B8(buf0, a0, 0x2C);
    s1 = _RotyGV(buf0, vec);
    abs1 = (s1 < 0) ? -s1 : s1;
    if (abs1 < 0x15) {
        goto epilogue;
    }

    func_001443B8(buf20, a0, 0x23);
    r2 = _RotyGV(buf20, vec);
    z2 = 0;
    if (abs1 >= 0x5A || s1 * r2 >= 0) {
        val = r2;
    } else {
        int nv = 0;
        val = s1;
        do {
        } while (nv);
    }
    if (val <= 0) {
        goto neg;
    }
    two = 2;
    do {
    } while (z2);
    if (two < REC.count) {
        goto setret;
    }
    REC.count = two;
    REC.mode = two;
    REC.x = vec[0];
    REC.y = vec[1];
    REC.z = vec[2];
    goto setret;
neg:
    two = 2;
    do {
    } while (z2);
    if (two < REC.count) {
        goto setret;
    }
    REC.count = two;
    REC.x = vec[0];
    REC.mode = 1;
    REC.y = vec[1];
    REC.z = vec[2];
setret:
    ret = 1;
epilogue:
    return ret;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", checkWaterfallResult);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlPulledGo);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016C580);

extern void func_00104548(void *, void *);
extern int _RotyGV(void *, void *);
extern void GetEyeDirection(void *, void *);
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
    r = _RotyGV(buf, a0);
    r = (r < 0) ? -r : r;
    if (r < 0x2E) {
        return;
    }
    v1 = *(void **)((char *)de8 + 0x164);
    dst = *(void **)((char *)v1 + 0x678);
    *(float *)((char *)dst + 0x3B0) = *(float *)((char *)a0 + 0x0);
    *(float *)((char *)dst + 0x3B4) = *(float *)((char *)a0 + 0x4);
    *(float *)((char *)dst + 0x3B8) = *(float *)((char *)a0 + 0x8);
    GetEyeDirection(buf + 0x10, de8);
    r = _RotyGV(buf + 0x10, a0);
    if (r > 0) {
        debug_StdPrintfDummy(D_00553960);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xD9);
        } else {
            BoxBarSoundOn(de8, 0xDB);
        }
    } else {
        debug_StdPrintfDummy(D_00553970);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xD8);
        } else {
            BoxBarSoundOn(de8, 0xDA);
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", isHideRecheck);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlRescueDst);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016CF18);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlSupportBGBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlStart);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", GirlAct_BoyAndMeCollisionMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", GetSafePosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", DebugDispAutoEscort);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016E5C0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", ACTGame_GirlBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016EB48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlSupportGBBegin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_0016F560);

extern float RotateAccordingToStick_PatternThree(void *, void *);
extern int func_0016F560(void *, void *);
extern float D_006290C4;
extern float D_006290C8;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", isEnterHideadv);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlSupportGBEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlHangG3M);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", func_00170CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", HandMgr_Update);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", HandMgr_Judge);

extern void traceLine();
extern unsigned char D_00284740[];
extern char D_00553BF0[];
extern char D_00553C00[];
extern char D_00553C20[];
extern int D_0062AF84;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", HandMgr_Print);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlRun);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlHang);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlBHang);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlAttack);

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

extern unsigned int _ACTWait(int a0);

extern char D_00553DA8[];

void afterGirlHand(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00553DA8);
    s0[0x30 / 4] = 0x2;
    _ACTWait(0);
}


extern char D_00553DC0[];

void afterGirlPulledGo(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00553DC0);
    s0[0x30 / 4] = 0x3;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/girl_act", actGirlJump);


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
