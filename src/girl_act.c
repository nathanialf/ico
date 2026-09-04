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






extern unsigned int D_0028829C[];
extern void *D_00631AE8;
extern int *D_00631AE4;
extern int D_006ABDE0[100];
extern void func_0014B330(char *self, unsigned int a1, float v);
extern int D_0028A890[];
extern void brainLevelProcess();
extern void ACTLookTargetSystem_Exec(void);
extern void debug_StdPrintfDummy();
extern float FSqrt(float a);
extern float sceVu0InnerProduct(void *a, void *b);

float fzMagnitudeByLineSeg(float *p0, float *p1, float *p2) {
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
    r1 = sceVu0InnerProduct(d1, d2);
    if (r1 < 0.0f) {
        return FSqrt(sceVu0InnerProduct(d2, d2));
    }
    d2[0] = p2[0] - p1[0];
    d2[1] = 0.0f;
    d2[2] = p2[2] - p1[2];
    r2 = sceVu0InnerProduct(d1, d2);
    if (-r2 < 0.0f) {
        return FSqrt(sceVu0InnerProduct(d2, d2));
    }
    a = -(p1[0] - p0[0]);
    b = p1[2] - p0[2];
    c = p0[2] * p1[0] - p0[0] * p1[2];
    mdret = FSqrt(b * b + a * a);
    ci = (int)(b * p2[0] + a * p2[2] + c);
    ci = __builtin_abs(ci);
    return (float)ci / mdret;
}

/* girl_act .rodata run 0x559430..0x559B50 â€” byte-verified against baseelf.
 * Definitions are interleaved with the INCLUDE_ASM stubs so the .o's section
 * order equals VMA order (jtbls and stub-referenced rodata are emitted by the
 * stubs themselves). */
const char D_00559430[0x10] = "--disconnect--\n";
const char D_00559440[0x18] = "girl after func\n";
const char D_00559458[0x18] = "enter actGirlHand50\n";
const char D_00559470[0x18] = "girl error flg get\n";

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetEyeDirection);

void GirlBrainClearTarget(void) {
    ACTLookTargetSystem_Exec();
    debug_StdPrintfDummy(D_00559430);
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_DecideMode);

const char D_005594A0[0x18] = "enter actGirlHand100\n";

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016A828);

const char D_005594D0[0x18] = "enter actGirlHand200\n";

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016A9E8);

const char D_00559510[0x18] = "Å¨¤Î¿ô¤¬Â¿¤¹¤®¤Þ¤¹";  /* EUC-JP */
const char D_00559528[0x20] = "src/girl_brain_main.c.inc";
const char D_00559548[0x10] = "SAMEGROUP";
const char D_00559558[0x18] = "OTHERGROUP";

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

INCLUDE_ASM("asm/nonmatchings/src/girl_act", sort_list);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", ATGoalTurnMail);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Attract);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", WayTest);

extern char D_002882D0[];
extern void *D_00629DE4;
extern void GetRootProjectionPosOfGObj(void *out, void *obj);
extern void GetRootPosition(void *out, void *obj);

void girlBrainMain_PositionUpdate(void) {
    GetRootPosition(D_002882D0 + 0x00, D_00631AE8);
    GetRootPosition(D_002882D0 + 0x20, D_00631AE4);
    GetRootProjectionPosOfGObj(D_002882D0 + 0x10, D_00631AE8);
    GetRootProjectionPosOfGObj(D_002882D0 + 0x30, D_00631AE4);
}

extern unsigned char D_00282AC0[];
extern void memset(void *a0, int a1, int a2);

void subGirlCollision(void) {
    memset(D_00282AC0, 0, 0x5910);
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetBoyMode);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016CED0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016D330);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", checkWaterfallResult);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledGo);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016E910);

/* 8-byte double: a C `const double` escapes to .sdata under -G8, so emit
 * the splat block verbatim at its VMA-ordered position instead */
INCLUDE_RODATA("asm/nonmatchings/src/girl_act", D_00559668);
const char D_00559670[0x10] = "turnL mail\n";
const char D_00559680[0x10] = "turnR mail\n";
const char D_00559690[0x10] = "MOVE LOOP";
const char D_005596A0[0x10] = "MOVE START";

extern void BoxBarSoundOn(void *, int);
extern int _RotyGV(void *buf, void *vec);
extern void debug_StdPrintfDummy(void *a0);
extern float _DistGV(void *a0, void *a1);
extern float *ContinueCorrectPosition(void *a0);
extern void GetEyeDirection();
extern void GetRootMotionOrient(void *, void *);

void actGirlDitch3mReady(void *a0, int a1) {
    char buf[0x20];
    void *de8 = D_00631AE8;
    int s3 = a1 & 0xFF;
    int r;
    void *v1;
    void *dst;
    GetRootMotionOrient(buf, de8);
    r = _RotyGV(buf, a0);
    r = (r < 0) ? -r : r;
    if (r < 0x2E) {
        return;
    }
    v1 = *(void **)((char *)de8 + 0x164);
    dst = *(void **)((char *)v1 + 0x678);
    *(float *)((char *)dst + 0x3D0) = *(float *)((char *)a0 + 0x0);
    *(float *)((char *)dst + 0x3D4) = *(float *)((char *)a0 + 0x4);
    *(float *)((char *)dst + 0x3D8) = *(float *)((char *)a0 + 0x8);
    GetEyeDirection(buf + 0x10, de8);
    r = _RotyGV(buf + 0x10, a0);
    if (r > 0) {
        debug_StdPrintfDummy(D_00559670);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xDC);
        } else {
            BoxBarSoundOn(de8, 0xDE);
        }
    } else {
        debug_StdPrintfDummy(D_00559680);
        if (s3 != 0) {
            BoxBarSoundOn(de8, 0xDB);
        } else {
            BoxBarSoundOn(de8, 0xDD);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", isHideRecheck);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRescueDst);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016F2A8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportBGBegin);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlStart);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GirlAct_BoyAndMeCollisionMail);

extern void _InterGV(void *dst, void *a1, void *src, float f12, float f13);

void func_00170380(float *dst, void *a1, float *src, float thresh) {
    float d = _DistGV(a1, src);
    if (thresh < d) {
        float t = (d - thresh) / d;
        _InterGV(dst, a1, src, t, 1.0f - t);
        return;
    }
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetSafePosition);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", DebugDispAutoEscort);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170950);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", ACTGame_GirlBeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00170ED8);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBBegin);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00171738);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001718F0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", isEnterHideadv);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBEnd);

const unsigned int D_00559710[0x4] = { 0x000000FF, 0x000000FF, 0x000000FF, 0x00000080 };
const char D_00559720[0x10] = "ATTRLOOK";
const char D_00559730[0x10] = "LOOKONLY";
const char D_00559740[0x10] = "APPROACH";
const char D_00559750[0x10] = "LOSTTWAY";
const char D_00559760[0x10] = "SEARCHWAY";

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHangG3M);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001725C8);

const unsigned int D_005598D0[0x4] = { 0x444B8000, 0x44E46000, 0x44584000, 0x3F800000 };
const unsigned int D_005598E0[0x4] = { 0x44180000, 0x44C80000, 0xC441C000, 0x3F800000 };
const char D_005598F0[0x10] = "after func\n";

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00173060);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Update);

extern GirlStand D_002883D0;
extern int _RotyGV(void *buf, void *vec);

void HandMgr_Judge(void) {
    volatile int home;
    int uninit;
    float one = 1.0f;
    home = uninit;
    if (D_002883D0.f_20 < 2.0f) {
        D_002883D0.f_58 = 1;
    }
    if ((_RotyGV(D_002883D0.sub40, D_002883D0.sub30) < 0
            ? -_RotyGV(D_002883D0.sub40, D_002883D0.sub30)
            : _RotyGV(D_002883D0.sub40, D_002883D0.sub30)) >= 0x3D) {
        D_002883D0.f_59 = 1;
    }
    if (D_002883D0.f_54 > 15.0f) {
        D_002883D0.f_5E = 1;
    }
    if (one * 100.0f < D_002883D0.f_50) {
        D_002883D0.f_5A = 1;
    }
    if (one * 125.0f < D_002883D0.f_50) {
        D_002883D0.f_5B = 1;
    }
    if (one * 135.0f < D_002883D0.f_50) {
        D_002883D0.f_5C = 1;
    }
    if (D_002883D0.f_50 < 90.0f) {
        D_002883D0.f_5D = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Print);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRun);

extern HangOrientEntry D_00565060[];

#define SUB(g)  (*(int *)((char *)(g) + 0x164))
#define REF(g)  (*(int *)((char *)(g) + 0x15C))

void actGirlHang(int *a0, int *a1, int *a2, int *a3) {
    volatile int home;
    int uninit;
    int *g = (int *)D_00631AE4;
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

/* two NUL-separated strings in one splat symbol; sized to cover both */
const char D_00559A70[0x30] = "ditch3m hand connect\n\0\0\0WBP set [ditch jump]\n";
const char D_00559AA0[0x18] = "enter actGirlStand\n";
const char D_00559AB8[0x18] = "enter actGirlWalk\n";
const char D_00559AD0[0x18] = "enter actGirlRun\n";
const char D_00559AE8[0x18] = "enter actGirlJump\n";
const char D_00559B00[0x18] = "enter actGirlAttack\n";

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001742A0);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001743F0);

extern void GetRootPosition(void *out, void *obj);
extern void RequestChangeHandMode(float *a0, float *a1);
extern float *ContinueCorrectPosition(void *a0);
extern void actCommonTurn(void *a0, float *a1, float *a2, int a3, float f);
extern int actCommonBackhand(void *a0);
extern void debug_Marker(int *self, int a1, int a2, int a3, float t);
extern void func_0015CD70(void *a0);
extern int ACTNotNeedCameraOffset(void);
extern void BoxBarSoundOn(void *a0, int a1);
extern unsigned int _ACTWait(int a0);

void func_00174558(void *volatile a0) {
    float buf10[4];
    float buf20[4];
    float buf30[4];

    GetRootPosition(buf20, a0);
    RequestChangeHandMode(buf30, buf10);
    buf30[1] = ContinueCorrectPosition(a0)[1];
    actCommonTurn(a0, buf30, buf10, 1, 20.0f);
    while (actCommonBackhand(a0)) {
        debug_Marker((int *)buf30, 0, 0, 0xFF, 100.0f);
        func_0015CD70(a0);
        _ACTWait(1);
    }
    for (;;) {
        if (ACTNotNeedCameraOffset() == 0) {
            BoxBarSoundOn(a0, 0x170);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174640);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174778);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174A48);

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174BA0);

const unsigned int D_00559B30[0x4] = { 0x00000000, 0x00000010, 0x00000020, 0x00000080 };
const unsigned int D_00559B40[0x4] = { 0x7F7FFFFF, 0x00000000, 0x00000000, 0x3F800000 };

extern void sceVu0Normalize(void *a, void *b);
extern void sceVu0SubVector(void *out, void *m1, void *m2);
extern void *subCommonIdle(void *a0);

void actGirlAttack(void *a0) {
    float res[4];
    float m1[4];
    float m2[4];
    void *dobj;
    void *sub;
    float a;

    BoxBarSoundOn(a0, 0xFD);
    dobj = D_00631AE4;
    sub = *(void **)((char *)dobj + 0x164);
    if (*(int *)((char *)sub + 0x30) == 1) {
        return;
    }
    GetRootPosition(m1, dobj);
    GetRootPosition(m2, a0);
    sceVu0SubVector(res, m1, m2);
    sceVu0Normalize(res, res);
    a = (float)_RotyGV(res, subCommonIdle(a0));
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
    int *a, *b, *sub, *sub2, *p;
    b = D_00631AE8;
    if (D_0028829C[0] != 7) goto ret0;
    a = D_00631AE4;
    sub = (int *)a[0x164 / 4];
    if (sub[0x30 / 4] != 0x4B) goto ret0;
    sub2 = (int *)b[0x164 / 4];
    p = (int *)sub2[0x678 / 4];
    return p[0x374 / 4];
ret0:
    return 0;
}

extern void SetLimitHandCameraCorrect(float *dst, float *a1, float *a2, float f12);
extern void SetDirectRootPositionNoFitting(void *a0, void *a1);

void func_00175350(void *volatile a0) {
    float buf10[4];
    float buf20[4];
    float buf30[4];

    for (;;) {
        buf10[0] = ContinueCorrectPosition(D_00631AE8)[0];
        buf10[1] = ContinueCorrectPosition(D_00631AE8)[1];
        buf10[2] = ContinueCorrectPosition(D_00631AE8)[2];
        buf20[0] = ContinueCorrectPosition(D_00631AE4)[0];
        buf20[1] = ContinueCorrectPosition(D_00631AE4)[1];
        buf20[2] = ContinueCorrectPosition(D_00631AE4)[2];
        buf20[1] = buf10[1];
        SetLimitHandCameraCorrect(buf30, buf10, buf20, 20.0f);
        SetDirectRootPositionNoFitting(a0, buf30);
        BoxBarSoundOn(a0, 0x162);
        _ACTWait(1);
    }
}

extern unsigned int _ACTWait(int a0);

void func_00175420(void *volatile a0) {
    int flag;
    for (;;) {
        unsigned int state = *(unsigned int *)(*(int *)((char *)D_00631AE4 + 0x164) + 0x30);
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

extern void GetTarget(void);
extern void SetRootPosition(void *o, void *param);

void func_001754F8(void *volatile a0) {
    float buf10[4];
    float buf20[4];
    float buf30[4];
    int cont = 1;
    int i = 0;

    GetTarget();
    debug_StdPrintfDummy(D_00559A70);
    for (;;) {
        if (cont) {
            i++;
            cont = i < 3;
            buf10[0] = ContinueCorrectPosition(D_00631AE4)[0];
            buf10[1] = ContinueCorrectPosition(D_00631AE4)[1];
            buf10[2] = ContinueCorrectPosition(D_00631AE4)[2];
            buf20[0] = ContinueCorrectPosition(D_00631AE8)[0];
            buf20[1] = ContinueCorrectPosition(D_00631AE8)[1];
            buf20[2] = ContinueCorrectPosition(D_00631AE8)[2];
            _InterGV(buf30, buf10, buf20, 1.0f, 1.0f);
            SetRootPosition(a0, buf30);
        }
        BoxBarSoundOn(a0, 0x175);
        _ACTWait(1);
    }
}


void func_001755F8(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00559AA0);
    s0[0x30 / 4] = 1;
    _ACTWait(0);
}

extern unsigned int _ACTWait(int a0);

void afterGirlHand(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00559AB8);
    s0[0x30 / 4] = 0x2;
    _ACTWait(0);
}


void afterGirlPulledGo(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00559AD0);
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


void func_001757B8(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    debug_StdPrintfDummy((char *)D_00559B00);
    s0[0x30 / 4] = 0xF;
    _ACTWait(0);
}

