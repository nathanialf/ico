#include "common.h"

#include "ico/types.h"
typedef float AVEC[4] __attribute__((aligned(16)));
typedef struct {
    long long a, b, c, d;
} __attribute__((packed)) EnvCopy32;
union IFAlias { int i; float f; };
union LLAlias { long long ll; };
typedef struct {
    char pad0[0x17C];
    float f17C;
    int i180;
    unsigned short u184, u186;
    unsigned int u188;
    unsigned int u18C;
} MotionEntry;
typedef struct {
    char pad0[0x180];
    float f180;
    char pad184[0xC];
    unsigned int u190;
} CamEntry;
union PFAlias { char *p; float f; };
struct SFld { float v; };
typedef int TI128 __attribute__((mode(TI)));

extern int EnableMotionOrientUpdate();
extern int ForMotionViewer_GetCurrentMotion();
extern int D_00631990;
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC6C8);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC780);

extern int ACTEnvGetTest(void);
extern int InitPendulum(void *a0);
extern void *ACTGameCollisionOff(void *a0);
extern int ACTGame_ConnectHand(void *a0);
extern void ActOrientTest(void *a0, void *a1, int a2);
extern int CageFixDL(void *a0, void *a1, void *a2);
extern void ChangeFieldCollisionDebugMode(void *a0);
extern void CheckFieldContact(void *a0, void *a1);
extern int ContinueCorrectPosition(void *a0);
extern float D_004C6EC0[];
extern float D_004C6ED0[];
extern float D_004C6EE0[];
extern float D_004C6EF0[];
extern float D_004C6F00[];
extern char D_004C6F10[];
extern char D_004C6F20[];
extern float D_004C6F30[];
extern MotionEntry D_00565060[];
extern CamEntry D_005F2FB8[];
extern char D_0061AD10[];
extern char D_0061AE10[];
extern char D_0061AE20[];
extern char D_0061AE30[];
extern float D_0062973C;
extern float D_0062974C;
extern float D_00629754;
extern float D_0063146C;
extern float D_0063144C;
extern float D_00631450;
extern volatile float D_00631454;
extern float D_00631458;
extern float D_0063145C;
extern float D_00631460;
extern float D_00631464;
extern float D_00631468;
extern float D_00631470;
extern float D_00631474;
extern int *D_00631AE4;
extern int D_00631AE8;
extern char D_00633840[];
extern char D_00633848[];
extern float D_00633850_[] __asm__("D_00633850");
extern float D_00633854_[] __asm__("D_00633854");
extern int DisableMotionOrientUpdate(int a0, int a1);
extern float EnableChangeRootUpdateMode();
extern int EnableMotionOrientUpdate__p4(int a0, int a1) __asm__("EnableMotionOrientUpdate");
extern int ExecBoxMoveEndReaction(void *a0);
extern int ForMotionViewer_GetCurrentAnimationFrame(int a0, int a1);
extern int ForMotionViewer_GetCurrentMotion__p4(int a0, int a1) __asm__("ForMotionViewer_GetCurrentMotion");
extern int GetDifferenceFromWallUpperPlane(void *a0);
extern void GetHeightOfWallFromGObj(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern float HandyCamera_TargetMoveType(void *a0, void *a1);
extern void *InitTorchGeo(void *a0, float radius);
extern int InitWallLeverGeo(void *a0);
extern void *LightTorchOn(void *a0, float radius);
extern int *PAIR_GetPosition_BOY(int a0, int a1);
extern float RotateAccordingToStick_PatternThree(int a0, void *a1);
extern int TorchGeo(void *a0);
extern void *WeaponHitEffect(void *a0, void *a1, float radius);
extern void _OrientGV(void *a0, void *a1);
extern void * _getLine();
extern void debug_Marker(void *a0, int a1, int a2, int a3, float a4);
extern void debug_assertMessage();
extern void dispPlane(void *a0, void *a1);
extern void eBrainProcess(void *a0, void *a1);
extern int func_00145328(void *a0, void *a1, int a2, void *a3, float f12, float f13);
extern void func_00145900(void *a0, void *a1, int a2);
extern int func_0014B2F0(void *a0, int a1);
extern float func_0014B358(int a0);
extern int func_00194590(void *a0, void *a1);
extern void func_001945B8(void *a0, float f12);
extern void func_001947D0();
extern int func_00194840(void *a0, void *a1, void *a2, int a3);
extern float func_001948F0(int a0, float a1);
extern int func_0019B948(void);
extern void func_001AD768(void *a0, int a1);
extern int func_001C05B8(void *a0);
extern void func_001FC520(void *a0, void *a1, void *a2, void *a3, void *a4);
extern int func_001C0BE0(void *a0);
extern int func_001FC6C8(void *a0, void *a1, void *a2, float f12, float f13);
extern void func_002438B8(void *a0, void *a1, void *a2);
extern float func_00243950(void *a0, void *a1);
extern void func_00243978(void *a0, void *a1);
extern void func_00243AD0(float *a0, float *a1, float *a2);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void func_00243B18(float *a0, float *a1, float a2);
extern void func_00263FF0(void *a0, int a1, void *a2);
extern void func_002641D8(void *a0, int a1, int a2);
extern void fzMagnitudefv(void *a0, int a1, void *a2);
extern void isStopChain(void *a0, void *a1, void *a2, void *a3);
extern void *isysGObjSearchFromObjKindID_begin(void *a0);
extern void * isysGObjSearchFromObjLayoutID();
extern int moveBoxAutoMatic(void *a0, void *a1, void *a2);
extern void *subCommonIdle(void *a0);
static inline float EnvSlotDist(int p, float *q) {
    return RotateAccordingToStick_PatternThree(p, q);
}
static inline int EnvPushPlane(float *tA, float *tB, void *Sv, char *env, void *a4v, float kf, float dist)
{
    float *dst = (float *)(env + 0x580);
    float k;
    GetRootMatrixByDObj(tA, Sv);
    k = dist - kf;
    func_00243B18(tB, (float *)a4v, -k);
    func_00243AD0(dst, tA, tB);
    return 0;
}
static inline int EnvPushAvg(float *acc, void *Sv, char *dstc, int woff)
{
    char *S = (char *)Sv;
    char *head;
    char *w;
    int i;
    head = *(char **)(((union PFAlias *)(S + 0x15C))->p + woff);
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    i = 3;
    w = head;
    do {
        func_00243AD0(acc, acc, (float *)w);
        w += 0x10;
        i--;
    } while (i >= 0);
    func_00243B18((float *)dstc, acc, 0.25f);
    return 0;
}





#define EnvCamAngle(tgt, refsrc, buf, k) ({ \
    func_00243B18((buf), (refsrc), (k)); \
    HandCameraCorrect((tgt), (buf)); \
})

#define EnvCamAngleP(tgt, refsrc, buf, k) ({ \
    func_00243B18((buf), (refsrc), (k)); \
    HandCameraCorrect((void *)(tgt), (buf)); \
})

#define EnvAssistLoop(acc_, S_, dst_) { \
    char *head; \
    char *w; \
    int i; \
    head = *(char **)(((union PFAlias *)((S_) + 0x15C))->p + 0x188); \
    (acc_)[0] = 0; \
    (acc_)[1] = 0; \
    (acc_)[2] = 0; \
    i = 3; \
    w = head; \
    do { \
        func_00243AD0((acc_), (acc_), (float *)w); \
        w += 0x10; \
        i--; \
    } while (i >= 0); \
    func_00243B18((float *)(dst_), (acc_), 0.25f); \
}

#define EnvAssistTail(tmp_, anch_, dst_, ascale_) { \
    func_00243B18((tmp_), (float *)(anch_), (ascale_)); \
    func_00243AD0((float *)(dst_), (float *)(dst_), (float *)(tmp_)); \
}

#define EnvWallAssistVec(acc_, tmp_, Sv_, dst_, ascale_) { \
    char *S = (char *)(Sv_); \
    char *anch = *(char **)(S + 0x164) + 0x4A0; \
    char *dst2 = (dst_); \
    EnvAssistLoop((acc_), S, dst2) \
    if (box != 0) { \
        ((union IFAlias *)(dst2 + 0xC))->f = 1.0f; \
        func_002438B8(dst2, (void *)*(int *)(*(char **)(box + 0x15C) + 0xC), dst2); \
    } \
    EnvAssistTail((tmp_), anch, dst2, (ascale_)) \
}

void func_001FCA20(void *arg0, void *arg1, char *arg2, void *arg3, void *arg4) {
    struct {
        AVEC v00, v01, v02;
    } __attribute__((aligned(16))) W;
    float w34;
    TI128 dv04, dv12, dv13;
    float w140, w144, w148, w14C;
    float w150, w154, w158, w15C;
    float w170, w174, w178, w17C;
    TI128 dv18, dv19, dv1A;
    float f50, f54, f58, f5C;
    float f60, f64, f68, f6C;
    float f70, f74, f78, f7C;
    float f80, f84, f88, f8C;
    float f90, f94, f98, f9C;
    float fA0, fA4, fA8, fAC;
    float fB0, fB4, fB8, fBC;
    float fC0, fC4, fC8, fCC;
    float fD0, fD4, fD8, fDC;
    float fE0, fE4, fE8, fEC;
    float fF0, fF4, fF8, fFC;
    float f100, f104, f108, f10C;
    float f110, f114, f118, f11C;
    int w160, w164, w168, w16C;
    int w190, w194, w198;
    float w19C;
    int w1A0, w1A4;
    int bx;
    int w1B0, w1B4, w1B8, w1BC, wFlag, w1C0, w1C4, wPtr20, wAang, w1C8, w1CC, w1D0, w1D8;
    char *me0;
#define v00 W.v00
#define v01 W.v01
#define v02 W.v02
#define v04 (*(AVEC *)&dv04)
#define v12 (*(AVEC *)&dv12)
#define v13 (*(AVEC *)&dv13)
#define v18 (*(AVEC *)&dv18)
#define v19 (*(AVEC *)&dv19)
#define v1A (*(AVEC *)&dv1A)
#define FF(o) FF_##o
#define FI(o) FI_##o
#define FP(o) FP_##o
#define FV(o) FV_##o
#define FF_0x0   v00[0]
#define FF_0x4   v00[1]
#define FF_0x8   v00[2]
#define FP_0     ((void *)v00)
#define FP_0x10  ((void *)v01)
#define FF_0x14  v01[1]
#define FP_0x20  ((void *)v02)
#define FI_0x30  ({ struct SFHome { char *p; } *sf_ = (struct SFHome *)&arg0; (int)sf_->p; })
#define FF_0x34  w34
#define FP_0x40  ((void *)v04)
#define FP_0x50  ((void *)&f50)
#define FF_0x54  f54
#define FV_0x60  ((float *)w60v)
#define FP_0x60  ((void *)w60v)
#define FF_0x60  f60
#define FI_0x60  f60
#define FF_0x64  f64
#define FI_0x64  f64
#define FF_0x68  f68
#define FI_0x68  f68
#define FV_0x70  ((float *)w70v)
#define FP_0x70  ((void *)w70v)
#define FF_0x70  f70
#define FI_0x70  f70
#define FF_0x74  f74
#define FI_0x74  f74
#define FI_0x78  f78
#define FP_0x78  ((void *)&f78)
#define FF_0x7C  f7C
#define FI_0x7C  f7C
#define FV_0x80  ((float *)t80w)
#define FP_0x80  ((void *)t80w)
#define FF_0x80  f80
#define FI_0x80  f80
#define FF_0x84  f84
#define FI_0x84  f84
#define FF_0x88  f88
#define FI_0x88  f88
#define FP_0x90  ((void *)&f90)
#define FF_0x90  f90
#define FF_0x94  f94
#define FF_0x98  f98
#define FP_0xA0  ((void *)&fA0)
#define FF_0xA0  fA0
#define FF_0xA4  fA4
#define FF_0xA8  fA8
#define FP_0xB0  ((void *)&fB0)
#define FF_0xB0  fB0
#define FF_0xB4  fB4
#define FF_0xB8  fB8
#define FP_0xC0  ((void *)&fC0)
#define FF_0xC0  fC0
#define FF_0xC4  fC4
#define FI_0xC4  (((union IFAlias *)&fC4)->i)
#define FF_0xC8  fC8
#define FP_0xD0  ((void *)&fD0)
#define FF_0xD0  fD0
#define FF_0xD4  fD4
#define FF_0xD8  fD8
#define FP_0xE0  ((void *)&fE0)
#define FF_0xE0  fE0
#define FF_0xE4  fE4
#define FF_0xE8  fE8
#define FF_0xF4  fF4
#define FP_0x100 ((void *)&f100)
#define FF_0x100 f100
#define FF_0x104 f104
#define FF_0x108 f108
#define FP_0x110 ((void *)&f110)
#define FI_0x11C f11C
#define FP_0x120 ((void *)v12)
#define FF_0x120 v12[0]
#define FP_0x130 ((void *)v13)
#define FP_0x140 ((void *)&w140)
#define FP_0x150 ((void *)&w150)
#define FP_0x160 ((void *)&w160)
#define FI_0x164 w164
#define FP_0x170 ((void *)&w170)
#define FP_0x180 ((void *)v18)
#define FI_0x190 w190
#define FI_0x194 w194
#define FI_0x198 w198
#define FP_0x198 ((void *)&w198)
#define FF_0x19C w19C
#define FP_0x19C ((void *)&w19C)
#define FP_0x1A0 ((void *)&w1A0)
#define FP_0x1A4 ((void *)&w1A4)
#define FI_0x1A8 arg2
#define box ((char *)bx)
#define boxp ((char *)bx)
#define FI_0x1B0 w1B0
#define FI_0x1B4 w1B4
#define FI_0x1B8 w1B8
#define FI_0x1BC w1BC
#define FI_0x1C0 w1C0
#define FI_0x1C4 w1C4
#define FI_0x1C8 w1C8
#define FI_0x1CC w1CC
#define FI_0x1D0 w1D0
#define FI_0x1D4 w1D4
#define FI_0x1D8 w1D8
    float f20, f21, f22, f23, f24, f25;
    char *t80v;
    char *pv;
    char *t80w;
    char *g90;
    char *w70;
    char *w70v;
    char *w70s;
    char *w60;
    char *w60v;
    char *w20;
    char *w20v;
    char *env;
    int s6, s7;
    void *found;
    char *m;
    char *v1;
    char *S;
    char *boy = (char *)arg1;
    int za;
    char *cagem;
    char *mtx70;
    char *m90a;

    {
    {
    char *Sa = (char *)arg0;
    env = *(char **)(Sa + 0x164);
    v1 = *(char **)(Sa + 0x15C);
    }
    S = *(char **)(env + 0x120);
    f24 = *(float *)(S + 0x110);
    bx = *(int *)(v1 + 0x180);
    FI(0x1B4) = 1;
    FI(0x1B8) = 1;
    FI(0x1B0) = *(int *)(v1 + 0x0);
    za = 0;
    f23 = -*(float *)(v1 + 0x5A4);
    FF(0x34) = -*(float *)(S + 0x130);
    wFlag = 0;
    f21 = *(float *)(S + 0x114);
    FI(0x1C0) = 0;
    f22 = ((struct SFld *)(S + 0x138))->v;
    s6 = *(int *)(v1 + 0x564);
    s7 = *(int *)(v1 + 0x574);
    func_002641D8(FP(0), za, 0x10);
    }

    {
        char *sub;
        if (*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x188) == 0) {
            s7 = 0;
            s6 = 0;
        }
        if (s7 == 0 && s6 == 0) {
            f22 = D_00633850_[0];
        }
        sub = *(char **)((char *)FI(0x30) + 0x15C);
        if (*(int *)(sub + 0x568) == 0) {
            f21 = D_00633850_[0];
        }
        {
            int a1v = FI(0x1B4);
            if ((int)((unsigned long long)*(long long *)(env + 0x18) >> 0x2F) & 1) {
                a1v = 0;
            }
            FI(0x1B4) = a1v;
        }
        if (func_0014B358(2) < *(float *)(sub + 0x560)) {
            FI(0x1B4) = 0;
            FI(0x1B8) = 0;
        }
    }
    GetHeightOfWallFromGObj(FP(0), (void *)FI(0x30));
    {
        char *p10 = (char *)FP(0x10);
        FI(0x1C4) = (int)p10;
        GetRootMatrixByDObj(p10, (void *)FI(0x30));
    }
    w20 = (char *)v02;
    wPtr20 = (int)w20;
    func_00145900(w20, (void *)FI(0x30), 0x2C);
    w20 = 0;
    {
        char *sub = *(char **)((char *)FI(0x30) + 0x15C);
        *(EnvCopy32 *)((char *)arg4 + 0x170) = *(EnvCopy32 *)(sub + 0x180);
    }
    {
        found = (void *)(int)*(long long *)&arg0;
        found = (void *)*(int *)((char *)&w34 + 4);
        found = (void *)*(int *)((char *)&dv04 + 4);
        found = (void *)(int)*(long long *)&f50;
        found = (void *)(int)*(long long *)&f54;
        found = (void *)(int)*(long long *)&f58;
        found = (void *)(int)*(long long *)&f5C;
        found = (void *)(int)*(long long *)&f60;
        found = (void *)(int)*(long long *)&f64;
        found = (void *)(int)*(long long *)&f68;
        found = (void *)(int)*(long long *)&f6C;
    }
    {
        long long ll18 = *(long long *)(env + 0x18);
        long long b20 = *(long long *)(env + 0x20);
        int bit5;
        ll18 &= 0xFFFFFF7FFFFFFFFFLL;
        ll18 &= 0xFFFFFEFFFFFFFFFFLL;
        bit5 = (int)((b20 << 0x1B) >> 0x20) & 1;
        ll18 &= 0xBFFFFFFFFFFFFFFFLL;
        ((union LLAlias *)(env + 0x18))->ll = ll18;
    if (bit5) {
        f25 = 0.0f;
        FI(0x1BC) = 0;
    } else if ((int)((b20 << 0x1C) >> 0x20) & 1) {
        w20v = (char *)&w34 - 20;
        f25 = 100.0f;
        FI(0x1BC) = 0;
    } else {
        f25 = 300.0f;
        FI(0x1BC) = 1;
    }
    }
    if ((FI(0x30) ^ D_00631AE8) == 0) FI(0x1BC) = 0;
    f20 = D_0063144C;
    {
        found = isysGObjSearchFromObjLayoutID(0x2B);
        cagem = (char *)&f54 - 20;
        for (;; found = isysGObjSearchFromObjKindID_begin(found)) {
            if (found == 0) goto L6B4;
            if (*(int *)((char *)found + 0x16C) == 0) continue;
            if (CageFixDL(cagem, (char *)&f50, found) == 0) continue;
            {
                int cp = ContinueCorrectPosition((void *)FI(0x30));
                if (!(RotateAccordingToStick_PatternThree(cp, cagem) < f20)) continue;
            }
            if (FF(0x54) > FF(0x14)) break;
        }
    }
    FI(0x1C0) = (int)found;
    *(int *)((char *)arg4 + 0x160) = (int)found;
L6B4:
    if (FI(0x1C0) != 0) {
        float d;
        w60 = (char *)&f60;
        eBrainProcess((void *)FI(0x30), w60);
        w60 = 0;
        w70v = (char *)&f70;
        w70 = (char *)&f70;
        w70 = (char *)&f74 - 4;
        w60v = (char *)&f60;
        found = (void *)(int)*(long long *)&f74;
        found = (void *)(int)*(long long *)&f78;
        found = (void *)(int)*(long long *)&f7C;
        t80v = (char *)&f80;
        g90 = (char *)(int)*(long long *)&f84;
        g90 = (char *)(int)*(long long *)&f88;
        g90 = (char *)(int)*(long long *)&f8C;
        mtx70 = w70;
        CageFixDL(mtx70, t80v, (void *)FI(0x1C0));
        w70 = (char *)&f70;
        if (FF(0x74) + 50.0f < FF(0x64)) {
            t80w = (char *)&f80;
            *(int *)arg3 |= 0x800000;
        }
        d = FF(0x64) - FF(0x74);
        if (d < 0.0f) {
            d = -d;
            if (d < 100.0f) goto Lmid;
            goto Lnomid;
        }
        if (!(d < 100.0f)) goto Lnomid;
    Lmid:
        *(int *)arg3 |= 0x1000000;
    Lnomid:
        f20 = 100.0f;
        debug_Marker(t80v, 0, 0xFF, 0, f20);
        debug_Marker(mtx70, 0, 0, 0xFF, f20);
    }
    if (s6 != 0) {
        if (EnableMotionOrientUpdate__p4(FI(0x30), 0x300) ||
            EnableMotionOrientUpdate__p4(FI(0x30), 0x500) ||
            EnableMotionOrientUpdate__p4(FI(0x30), 0x600)) {
            f23 = D_00633850_[0];
            FF(0x34) = f23;
        }
    }
    {
        char *g = (char *)FI(0x30);
        char *sub = *(char **)(g + 0x15C);
        if (*(int *)(sub + 0x568) != 0) {
            if (DisableMotionOrientUpdate((int)g, 0x300) ||
                DisableMotionOrientUpdate(FI(0x30), 0x500) ||
                DisableMotionOrientUpdate(FI(0x30), 0x600)) {
                f21 = D_00633850_[0];
            }
        }
    }
    if (s7 != 0 || s6 != 0) {
        char *sub = *(char **)((char *)FI(0x30) + 0x15C);
        if (*(int *)(sub + 0x188) != 0) {
            int f17, f18;
            int ret;
            fzMagnitudefv(arg4, *(int *)(sub + 0x188), sub + 0x180);
            *(float *)((char *)arg4 + 0xC) = 1.0f;
            if (s6 != 0) {
                f17 = 1;
                f18 = 1;
                if (ACTEnvGetTest() != 0) {
                    int gv = FI(0x30);
                    f18 = 0;
                    if (gv ^ (int)D_00631AE4) f18 = f17;
                    if ((gv ^ D_00631AE8) == 0) f17 = 0;
                    gv = 0;
                }
                {
                    char *wb = (char *)&f6C - 12;
                    func_00145900(wb, (void *)FI(0x30), 0x2C);
                    func_00243B18(FP(0x70), arg4, -1.0f);
                    ret = HandCameraCorrect(wb, (float *)&f70);
                }
                if (f18 != 0 && ret >= 0x1F) {
                    *(int *)arg3 |= 0x10;
                }
                if (f17 != 0 && ret < -0x1E) {
                    *(int *)arg3 |= 0x8;
                }
            }
            if (s7 != 0 && f22 < f25) {
                int a;
                func_00243B18(FP(0x70), arg4, -1.0f);
                a = __builtin_abs(HandCameraCorrect(boy, (float *)&f70));
                *(long long *)(env + 0x18) |= 0x0008000000000000LL;
                if (f22 < 60.0f) {
                    if (a < 0x1E) {
                        *(long long *)(env + 0x18) |= 0x0004000000000000LL;
                    }
                }
            }
        }
    }
    if (s6 == 0) {
        char *sub = *(char **)((char *)FI(0x30) + 0x15C);
        if (*(int *)(sub + 0x57C) != 0) {
            if (*(float *)(sub + 0x5E4) < 100.0f) {
                int a;
                a = __builtin_abs(EnvCamAngle(boy, sub + 0x5D0, FP(0x60), -1.0f));
                if (a < 0x28) {
                    long long b18 = *(long long *)(env + 0x18);
                    b18 |= 0x8000LL << 24;
                    b18 |= 0x8000LL << 25;
                    *(long long *)(env + 0x18) = b18;
                }
            }
        }
    }
    if (f22 != D_00633850_[0] && s6 != 0 && FI(0x1B4) != 0) {
        void *st;

        int mv;
        int s18;
        int b1, b2, b3, b6, b6b;
        MotionEntry *mo;
        float t;
        char *gb;

        st = subCommonIdle((void *)FI(0x30));
        {
            int aat = EnvCamAngle(st, arg4, FP(0x60), -1.0f);
            aat = (aat < 0) ? -aat : aat;
            wAang = aat;
        }
        *(int *)((char *)arg4 + 0x130) = *(int *)(*(char **)((char *)arg4 + 0x178) + 0x48);
        s6 = (unsigned char)EnableMotionOrientUpdate__p4(FI(0x30), 0x1000);
        *(int *)((char *)arg4 + 0x13C) = (int)box;
        *(int *)arg3 |= 1;
        if (FF(0x34) < f23) {
            if (FF(0x34) != D_00633854_[0]) FF(0x34) = f23;
        }
        if (f22 < f25) {
            t = FF(0x34);
            if (t < 0.0f) t = D_00633850_[0];
            if (t >= 40.0f) {
                *(long long *)(env + 0x18) |= 0x8000LL << 36;
            }
        }
        if (f22 < 300.0f) {
            t = FF(0x34);
            if (t < 0.0f) t = D_00633850_[0];
            if (t <= 250.0f) {
                *(int *)arg3 |= 2;
            }
        }
        if ((char *)FI(0x30) == (char *)D_00631AE8) {
            if (f22 < 300.0f) {
                if (*(int *)(boxp + 0xC) == 0x11) {
                    if (ExecBoxMoveEndReaction(box) == 7) {
                        int a;
                        float m1 = -1.0f;
                        a = __builtin_abs(EnvCamAngle(boy, arg4, FP(0x60), m1));
                        m1 = 0.0f;
                        if (a < 0x2D) {
                            a = __builtin_abs(EnvCamAngleP(FI(0x1A8), arg4, FP(0x60), -1.0f));
                            if (a < 0x2D) {
                                if (func_00194590(boy, (void *)FI(0x1A8)) < 0x2D) {
                                    ((union LLAlias *)(env + 0x20))->ll |= 0x400000;
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            gb = (char *)FI(0x30);
            if (gb != (char *)D_00631AE8) goto LmvB0;
            mv = 0;
            goto LmvB1;
        LmvB0:
            mv = ForMotionViewer_GetCurrentMotion__p4((int)gb, 0xB000);
        LmvB1:;
        {
            int m2;
            gb = (char *)FI(0x30);
            if (mv != 0) goto LmvEskip;
            if (gb != (char *)D_00631AE8) goto LmvE0;
            m2 = 0;
            goto LmvE1;
        LmvE0:
            m2 = ForMotionViewer_GetCurrentMotion__p4((int)gb, 0xE000);
        LmvE1:
            mv = m2;
            if (mv == 0) {
                gb = (char *)FI(0x30);
                mv = ForMotionViewer_GetCurrentMotion__p4((int)gb, 0xC000);
                {
                    int m4;
                    gb = (char *)FI(0x30);
                    if (mv != 0) goto LmvDskip;
                    if (gb != (char *)D_00631AE8) goto LmvD0;
                    m4 = 0;
                    goto LmvD1;
                LmvD0:
                    m4 = ForMotionViewer_GetCurrentMotion__p4((int)gb, 0xD000);
                LmvD1:
                    mv = m4;
                    if (mv == 0) {
                        gb = (char *)FI(0x30);
                        mv = (D_00631990 == 4) ? EnableMotionOrientUpdate__p4((int)gb, 0x1000)
                             : ForMotionViewer_GetCurrentMotion__p4((int)gb, 0x1000);
                        mv &= 0xFF;
                        if (mv == 0) {
                            mv = ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x3000);
                        }
                    }
                LmvDskip:;
                }
            }
        LmvEskip:;
        }
        }
        if (mv != 0) {
            FF(0x34) = f23;
        }
        {
            gb = (char *)FI(0x30);
            if (gb == (char *)D_00631AE8) {
            if (EnableMotionOrientUpdate__p4((int)gb, 0x7000)) {
                f23 = D_00633850_[0];
                FF(0x34) = f23;
                if (ACTEnvGetTest()) {
                    char *p1 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                    char *p2 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                    if (*(float *)(p2 + 4) + 50.0f < *(float *)(p1 + 4)) {
                        t80v = (char *)&f64 - 4;
                        func_00243B18((float *)t80v, arg4, -1.0f);
                        g90 = (char *)(int)*(long long *)&f90;
                        g90 = (char *)(int)*(long long *)&f94;
                        g90 = (char *)(int)*(long long *)&f98;
                        g90 = (char *)(int)*(long long *)&f9C;
                        m90a = (char *)FP(0x90);
                        _OrientGV(m90a, t80v);
                        {
                            w70 = (char *)&f74 - 4;
                            {
                                char *r1;
                                char *r2;
                                r1 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                                r2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                                func_00243AE8(w70, r1, r2);
                            }
                            FI(0x7C) = 0;
                            func_002438B8(FP(0x80), m90a, w70);
                        }
                        if (f22 < FF(0x88)) {
                            ((union LLAlias *)(env + 0x20))->ll |= 0x100;
                        }
                    }
                }
            }
        }
        }
        {
            gb = (char *)FI(0x30);
            {
                float c40;
                c40 = 40.0f;
                if (f22 < c40) {
                    ((union LLAlias *)(env + 0x18))->ll |= 0x8000LL << 24;
                    if (func_00194590(subCommonIdle(gb), arg4) >= 0x88) {
                        ((union LLAlias *)(env + 0x18))->ll |= 0x8000LL << 25;
                    }
                }
            }
        }
        b6 = 0;
        if (FF(0x34) > 90.0f && FF(0x34) < 110.0f) b6 = (s6 == 0);
        gb = (char *)FI(0x30);
        if (FF(0x34) > 190.0f && FF(0x34) < 210.0f) s18 = 1;
        mo = D_00565060 + *(int *)(*(char **)(gb + 0x15C) + 0x4A0);
        s18 = 1;
        {
            unsigned short m186 = mo->u186;
            if (m186 & 7) {
                f20 = 60.0f;
            } else if ((mo->u188 >> 26) & 1) {
                f20 = 50.0f;
            } else {
                f20 = 40.0f;
            }
        }
        if (f22 < 120.0f && b6 != 0) {
            char *q;
            w60 = (char *)&f68 - 8;
            func_00243B18(w60, arg4, f22);
            func_00243AD0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x770,
                          (void *)FI(0x1C4), w60);
            func_00243B18(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x780,
                          arg4, -1.0f);
            gb = (char *)FI(0x30);
            q = (char *)*(int *)((char *)*(int *)(gb + 0x164) + 0x678);
            *(int *)(q + 0x794) = 0x14;
            *(float *)(q + 0x790) = 40.0f;
            *(int *)((char *)*(int *)((char *)*(int *)(gb + 0x164) + 0x678) + 0x798) = 1;
            ((union IFAlias *)arg3)->i |= 0x40000000;
        }
        if ((char *)FI(0x30) == (char *)D_00631AE8) {
            if (func_0014B2F0((void *)FI(0x30), 0x1A)) {
                char *p1;
                char *p2;
                g90 = (char *)FP(0x60);
                p1 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                p2 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                func_00243AE8(g90, p1, p2);
                FI(0x64) = 0;
                if (func_00243950(g90, subCommonIdle((void *)D_00631AE4)) < 100.0f) {
                    int v5 = 0;
                    if (*(int *)(boxp + 0xC) == 0x11) {
                        int q2 = *(int *)(*(char **)((char *)D_00631AE4 + 0x15C) + 0x0);
                        if (q2 != 0) {
                            v5 = ((int)box != q2);
                        }
                    }
                    if (v5 == 0) s18 = 0;
                }
            }
        }
        b1 = 0;
        if (FF(0x34) > 10.0f && FF(0x34) < 75.0f) b1 = (s6 == 0);
        b2 = 0;
        if (FF(0x34) > 75.0f && FF(0x34) < 150.0f) b2 = (s6 == 0);
        {
            int t150 = 0;
            if (FF(0x34) > 150.0f && FF(0x34) < 250.0f) t150 = 1;
            b3 = t150;
        }
        {
            int t3 = 0;
            if (s6 == 0) t3 = b3;
            if ((FI(0x30) ^ (int)D_00631AE4) != 0) b3 = t3;
        }
        if (f22 < f20 && s18 != 0) {
            long long ll;
            if (b1) {
                if (EnableMotionOrientUpdate__p4(FI(0x30), 0xA00)) {
                    *(int *)((char *)arg3 + 4) |= 0x1000;
                } else {
                    *(int *)((char *)arg3 + 4) |= 0x800;
                }
            }
            if (b2) {
                *(int *)((char *)arg3 + 4) |= 0x1000;
            }
            if (b3) {
                *(int *)((char *)arg3 + 4) |= 0x2000;
            }
            ll = ((union LLAlias *)(env + 0x470))->ll;
            if (ll & 0x7800) {
                if ((int)(ll >> 13) & 1 && *(int *)((char *)FI(0x30) + 0xC) == 4) {
                    EnvPushPlane((float *)w70v, FV(0x80), (void *)FI(0x30), env, arg4, -20.0f, f22);
                } else {
                    EnvPushPlane((float *)w70v, FV(0x80), (void *)FI(0x30), env, arg4, 5.0f, f22);
                }
            }
            if (FF(0x34) > 80.0f && FF(0x34) < 180.0f) {
                if (*(int *)(boxp + 0xC) == 0x11) {
                    *(int *)((char *)arg3 + 4) |= 0x10000;
                } else {
                    *(int *)((char *)arg3 + 4) |= 0x8000;
                }
            }
            if (EnableMotionOrientUpdate__p4(FI(0x30), 0x2000)) {
                if (f23 > 80.0f && f23 < 180.0f) {
                    *(int *)((char *)arg3 + 4) |= 2;
                }
            }
        }
        if (f22 < 50.0f &&
            !((int)(*(long long *)(env + 0x20) << 0x1D >> 0x20) & 1)) {
            int stt;
            int i;
            char *w;
            char *anch;
            char *dst;
            stt = *(int *)(box + 0xC);
            if (stt == 0x10) {
                char *m6;
                float fr = 10.0f;
                if ((char *)FI(0x30) == (char *)D_00631AE4) fr = 30.0f;
                m6 = *(char **)((char *)FI(0x30) + 0x164);
                w70 = (char *)&f74 - 4;
                ((union LLAlias *)(void *)&f70)->ll = *(long long *)&D_0061AD10[0];
                ((union LLAlias *)FP(0x78))->ll = *(long long *)&D_0061AD10[8];
                *(float *)(m6 + 0x550) = *(float *)(m6 + 0x4A0);
                *(float *)(m6 + 0x554) = *(float *)(m6 + 0x4A4);
                *(float *)(m6 + 0x558) = *(float *)(m6 + 0x4A8);
                if ((char *)FI(0x30) == (char *)D_00631AE4) FF(0x70) = -FF(0x70);
                ((union IFAlias *)(w70 + 0xC))->f = 1.0f;
                func_002438B8(m6 + 0x5A0,
                              (void *)*(int *)(*(char **)(box + 0x15C) + 0xC),
                              w70);
                debug_Marker(env + 0x5A0, 0, 0xFF, 0, 100.0f);
                if (RotateAccordingToStick_PatternThree((int)FP(0), env + 0x5A0) < fr * fr) {
                    *(int *)((char *)arg3 + 4) |= 1;
                    *(int *)((char *)arg4 + 0x16C) = (int)box;
                    stt = *(int *)(box + 0xC);
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x11) {
                if (EnableMotionOrientUpdate__p4(FI(0x30), 0xB00)) goto L11e;
                *(int *)((char *)arg3 + 4) |= 0x40000000;
                *(int *)((char *)arg4 + 0x140) = (int)box;
                if (func_001C05B8(box) == 0) goto L11g;
                if (moveBoxAutoMatic((void *)&f70, box, (void *)FI(0x30)) == 0) goto L11m;
                *(int *)((char *)arg3 + 4) |= 0x20000000;
                *(int *)((char *)arg4 + 0x144) = (int)box;
                stt = *(int *)(box + 0xC);
                goto L11d;
            L11e:
                stt = *(int *)(box + 0xC);
                goto L11d;
            L11g:
                stt = *(int *)(box + 0xC);
                goto L11d;
            L11m:
                stt = *(int *)(box + 0xC);
            L11d:;
            }
            if (stt == 0x12) {
                if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x700)) {
                    *(int *)((char *)arg3 + 4) |= 0x80000000;
                    *(int *)((char *)arg4 + 0x148) = (int)box;
                    stt = *(int *)(box + 0xC);
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x17) {
                if (EnableMotionOrientUpdate__p4(FI(0x30), 0x500)) {
                    ((union IFAlias *)((char *)arg3 + 8))->i |= 1;
                    *(int *)((char *)arg4 + 0x150) = FI(0x1B0);
                    *(int *)((char *)arg4 + 0x14C) = (int)box;
                    EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 5.0f);
                    stt = *(int *)(box + 0xC);
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x16) {
                if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x500) == 0) goto L16e;
                if (InitWallLeverGeo(box) == 0) goto L16g;
                ((union IFAlias *)((char *)arg3 + 8))->i |= 2;
                *(int *)((char *)arg4 + 0x14C) = (int)box;
                EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 45.0f);
                func_00243B18(FV(0x70), (float *)arg4, -10.0f);
                func_001945B8(FV(0x70), D_00631450);
                func_00243AD0((float *)((char *)arg4 + 0xF0), (float *)((char *)arg4 + 0xF0), (float *)&f70);
                stt = *(int *)(box + 0xC);
                goto L16d;
            L16e:
                stt = *(int *)(box + 0xC);
                goto L16d;
            L16g:
                stt = *(int *)(box + 0xC);
            L16d:;
            }
            if (stt == 0x18) {
                if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x600) == 0) goto L18e;
                if (func_001C0BE0(box) == 0) goto L18g;
                ((union IFAlias *)((char *)arg3 + 8))->i |= 4;
                *(int *)((char *)arg4 + 0x14C) = (int)box;
                EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 30.0f);
                stt = *(int *)(box + 0xC);
                goto L18d;
            L18e:
                stt = *(int *)(box + 0xC);
                goto L18d;
            L18g:
                stt = *(int *)(box + 0xC);
            L18d:;
            }
            if (stt == 0x19) {
                if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x600)) {
                    if (func_001C0BE0(box)) {
                        ((union IFAlias *)((char *)arg3 + 8))->i |= 8;
                        *(int *)((char *)arg4 + 0x14C) = (int)box;
                        EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 30.0f);
                    }
                }
            }
        }
        if (f22 < 200.0f) {
            int fl40;
            fl40 = 1;
            if (!(f22 < 40.0f)) fl40 = 0;
            if (D_00631990 == 0x54 || D_00631990 == 3 || D_00631990 == 0x2E) {
                if (*(int *)((char *)FI(0x30) + 0xC) == 4) goto Lp1end;
            }
            if (EnableMotionOrientUpdate__p4(FI(0x30), 0x400)) {
                char *dstc = (char *)arg4 + 0xC0;
                w70 = (char *)&f74 - 4;
                ((union IFAlias *)((char *)arg3 + 8))->i =
                    (*(int *)((char *)arg3 + 8) & 0xFFFEFFFF) | (fl40 << 16) | 0x8000;
                *(float *)((char *)arg4 + 0xA0) = *(float *)((char *)arg4 + 0x0);
                *(float *)((char *)arg4 + 0xA4) = *(float *)((char *)arg4 + 0x4);
                *(float *)((char *)arg4 + 0xA8) = *(float *)((char *)arg4 + 0x8);
                EnvPushAvg((float *)&f70, (void *)FI(0x30), dstc, 0x188);
                func_00243B18((float *)w70, (float *)arg4, 30.0f);
                func_00243AD0((float *)dstc, (float *)dstc, (float *)w70);
                *(float *)((char *)arg4 + 0xCC) = 1.0f;
            }
        Lp1end:
            if (EnableMotionOrientUpdate__p4(FI(0x30), 0xC000)) {
                *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x400) | (fl40 << 10);
            }
        }
        {
            MotionEntry *mo2;
            int k;
            float thr;
            me0 = (char *)FI(0x30);
            mo2 = &D_00565060[*(int *)(*(char **)(me0 + 0x15C) + 0x4A0)];
            k = (*(int *)&mo2->u184 << 6) >> 30;
            switch (k) {
            case -1: {
                int r;
                if (D_00631990 == 4) r = EnableMotionOrientUpdate__p4(FI(0x30), 0x1000);
                else r = ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x1000);
                if (r & 0xFF) {
                    thr = 30.0f;
                } else {
                    {
                        char *mp = (char *)D_00565060;
                        mp -= -(*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x4A0) * 0x190);
                        thr = func_001948F0(wAang, ((MotionEntry *)mp)->f17C + 2.0f);
                    }
                }
                thr = (thr < 0.0f) ? 0.0f : ((30.0f < thr) ? 30.0f : thr);
                break;
            }
            case 1:
                thr = 150.0f;
                break;
            default:
                thr = 60.0f;
                break;
            }
            if (f22 < thr) {
                int c130_170, c60_100, c60_150, c60_230;
                float a34 = FF(0x34);
                c130_170 = 0;
                if (130.0f <= a34) {
                    if (a34 < 170.0f) c130_170 = 1;
                }
                c60_100 = 0;
                if (60.0f < FF(0x34)) {
                    if (FF(0x34) < 100.0f) c60_100 = 1;
                }
                c60_150 = 0;
                if (60.0f < FF(0x34)) {
                    if (FF(0x34) < 150.0f) c60_150 = 1;
                }
                c60_230 = 0;
                if (60.0f < FF(0x34)) {
                    if (FF(0x34) < 230.0f) c60_230 = 1;
                }
                if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0xB000)) {
                    *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x100) | (c60_150 << 8);
                } else if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0xE000)) {
                    *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x200) | (c60_150 << 9);
                } else if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0xD000)) {
                    *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x1000) | (c60_150 << 12);
                } else {
                    int r2;
                    if (D_00631990 == 4) r2 = EnableMotionOrientUpdate__p4(FI(0x30), 0x1000);
                    else r2 = ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x1000);
                    if (r2 & 0xFF) {
                        int v = (*(int *)((char *)arg3 + 8) & ~0x2000) | (c60_150 << 13);
                        *(int *)((char *)arg3 + 8) = v;
                        if (((unsigned int)v >> 13) & 1) {
                            char *S16 = (char *)FI(0x30);
                            char *env2 = *(char **)(S16 + 0x164);
                            float ang = FF(0x34);
                            int c2;
                            c2 = (int)*(long long *)&fA0;
                            c2 = (int)*(long long *)&fA4;
                            c2 = (int)*(long long *)&fA8;
                            c2 = (int)*(long long *)&fAC;
                            c2 = (int)*(long long *)&fB0;
                            c2 = (int)*(long long *)&fB4;
                            c2 = (int)*(long long *)&fB8;
                            c2 = (int)*(long long *)&fBC;
                            c2 = (int)*(long long *)&fC0;
                            c2 = (int)*(long long *)&fC4;
                            c2 = (int)*(long long *)&fC8;
                            c2 = (int)*(long long *)&fCC;
                            c2 = (int)*(long long *)&fD0;
                            c2 = (int)*(long long *)&fD4;
                            c2 = (int)*(long long *)&fD8;
                            c2 = (int)*(long long *)&fDC;
                            c2 = *(int *)&fF4;
                            if (S16 == (char *)D_00631AE4 &&
                                ((((CamEntry *)((char *)D_005F2FB8 + D_00631990 * 0x194))->u190 >> 2) & 1) &&
                                (unsigned int)(*(int *)(env2 + 0x30) - 4) < 2) {
                                {
                                    int r;
                                    { char *pd = (char *)&fD0; func_002641D8(pd, 0, 0xC0); pd = 0; }
                                    { char *pd = (char *)&fD0; ActOrientTest(pd, S16, 0x2C); pd = 0; }
                                    FF(0xE0) = FF(0xD0);
                                    FF(0xE8) = FF(0xD8);
                                    FF(0xE4) = FF(0xD4) + 200.0f;
                                    { char *pd = (char *)&fD0; ChangeFieldCollisionDebugMode(pd); pd = 0; }
                                    if (FI(0x164) != 0) {
                                        r = 0;
                                        if (ang + (FF(0xF4) - FF(0xD4)) < 250.0f) goto Lopdone;
                                    }
                                    r = 1;
                                Lopdone:
                                    c2 = r;
                                }
                            } else {
                                c2 = 1;
                            }
                            if ((c2 & 0xFF) == 0) {
                                *(int *)((char *)arg3 + 8) &= ~0x2000;
                            }
                        }
                    } else if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x3000)) {
                        *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x4000) | (c60_150 << 14);
                    } else if (*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x1E4) != 0) {
                        int v = (*(int *)((char *)arg3 + 8) & ~0x80) | (c60_100 << 7);
                        int v2 = v & ~0x40;
                        v2 |= c130_170 << 6;
                        *(int *)((char *)arg3 + 8) = v2;
                        if (*(int *)(box + 0xC) == 0x2B) {
                            *(int *)((char *)arg3 + 8) = (v2 & ~0x40) | (c60_230 << 6);
                        }
                    }
                }
            }
        }
        if (f22 < 50.0f) {
            int a;
            func_00243B18(FP(0x70), arg4, -1.0f);
            a = __builtin_abs(HandCameraCorrect((void *)FI(0x1A8), (float *)&f70));
            if (a < 0x28) {
                if ((char *)FI(0x30) == (char *)D_00631AE4 ||
                    (FF(0x34) > 130.0f && *(int *)(box + 0xC) != 0x10)) {
                    ((union LLAlias *)(env + 0x470))->ll |= 0x8000LL << 44;
                }
            }
        }
        if ((int)(*(unsigned long long *)(env + 0x470) >> 59) & 1) {
            t = FF(0x34);
            if (t < 0.0f) t = D_00633850_[0];
            if (t > 65.0f) {
                if ((float)wAang < 30.0f) {
                    ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 26;
                }
            }
        }
        if (f22 < 60.0f) {
            int c16 = 1;
            if (!((float)wAang < 30.0f)) c16 = 0;
            if (*(int *)(box + 0xC) == 0x35) {
                if (func_0019B948() == 0) {
                    ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 43;
                }
            } else {
                ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 42;
            }
            t = FF(0x34);
            if (t < 0.0f) t = D_00633850_[0];
            if (t > 230.0f) {
                if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x400) == 0 &&
                    ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0x8000) == 0) {
                    int stx = *(int *)(box + 0xC);
                    if (stx != 0x2B) {
                        if (stx != 0x35 && c16 != 0) {
                            if (ForMotionViewer_GetCurrentMotion__p4(FI(0x30), 0xE000)) {
                                ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 44;
                            } else {
                                ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 45;
                            }
                        }
                    }
                }
            }
        }
        {
        char *S6 = (char *)FI(0x30);
        if (*(int *)(S6 + 0xC) == 4) {
            if (*(int *)(*(char **)(*(char **)(S6 + 0x164) + 0x670) + 0x1DC) == 3) {
                if (f22 < 180.0f) {
                    if (*(int *)(*(char **)(S6 + 0x15C) + 0x1E4) != 0) {
                        if (FF(0x34) >= 40.0f && FF(0x34) < 300.0f) {
                            *(int *)((char *)arg3 + 4) |= 0x100000;
                        } else if (FF(0x34) >= 300.0f && FF(0x34) < 500.0f) {
                            *(int *)((char *)arg3 + 4) |= 0x200000;
                        } else if (FF(0x34) >= 500.0f && FF(0x34) < 700.0f) {
                            *(int *)((char *)arg3 + 4) |= 0x400000;
                        }
                    }
                }
            }
        }
        }
    }
    {
    char *mm;
    if (f21 != D_00633850_[0] &&
        (mm = (char *)FI(0x30), *(int *)(*(char **)(mm + 0x15C) + 0x568) != 0) &&
        FI(0x1B8) != 0) {
        void *st;
        int a;
        {
            char *c10 = (char *)arg4 + 0x10;
            FI(0x1C8) = (int)c10;
            CheckFieldContact(c10, mm);
        }
        *(float *)((char *)arg4 + 0x1C) = 1.0f;
        st = subCommonIdle((void *)FI(0x30));
        a = __builtin_abs(EnvCamAngle(st, (void *)FI(0x1C8), FP(0x60), 1.0f));
        if ((char *)FI(0x30) == (char *)D_00631AE4 && (char *)D_00631AE8 != 0) {
            char *pp2;
            float d2;
            float rowf;
            pp2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
            FF(0x60) = *(float *)(pp2 + 0);
            pp2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
            FF(0x64) = *(float *)(pp2 + 4);
            pp2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
            FF(0x68) = *(float *)(pp2 + 8);
            w60 = (char *)&f6C - 12;
            d2 = HandyCamera_TargetMoveType((void *)FI(0x1C4), w60);
            rowf = ((CamEntry *)((char *)D_005F2FB8 + D_00631990 * 0x194))->f180;
            if (d2 < rowf * rowf) {
                func_00243AE8(FP(0xB0), w60, (char *)&f50 - 0x40);
                w70 = (char *)&f74 - 4;
                _OrientGV(w70, (void *)FI(0x1C8));
                ((union IFAlias *)&fBC)->i = 0;
                func_002438B8(FP(0xC0), w70, FP(0xB0));
                if (0.0f < FF(0xC8)) {
                    wFlag = 1;
                }
            }
        }
        if (f21 < 20.0f) {
            if (!(a < 0x2E)) {
                if ((int)(*(long long *)(env + 0x20) << 7 >> 32) & 1) {
                    dispPlane((void *)FI(0x30), (void *)FI(0x1C8));
                    *(long long *)(env + 0x20) &= ~0x2000000;
                }
            }
        }
        if (*(int *)(env + 0x30) == 0x29) {
            *(int *)((char *)arg3 + 4) |= 4;
        }
        if (f21 < f25 && f24 >= 40.0f) {
            *(long long *)(env + 0x18) |= 0x8000LL << 37;
        }
        if (f21 < 300.0f && f24 >= 100.0f) {
            ((union IFAlias *)arg3)->i |= 4;
            *(float *)((char *)arg4 + 0x138) = f21;
        }
        switch (*(unsigned int *)(env + 0x30)) {
        case 2:
            if (f21 < 20.0f && f24 > 180.0f) {
                if ((char *)FI(0x30) == (char *)D_00631AE4) {
                    if (f24 > 900.0f) {
                        *(int *)((char *)arg3 + 8) =
                            (*(int *)((char *)arg3 + 8) & 0xFDFFFFFF) | ((FI(0x1BC) & 1) << 25);
                    } else {
                        *(int *)((char *)arg3 + 8) =
                            (*(int *)((char *)arg3 + 8) & 0xFBFFFFFF) | ((FI(0x1BC) & 1) << 26);
                    }
                } else {
                    *(int *)((char *)arg3 + 8) =
                        (*(int *)((char *)arg3 + 8) & 0xFDFFFFFF) | ((FI(0x1BC) & 1) << 25);
                }
                {
                    if (f24 > 1000.0f) {
                        *(int *)((char *)arg3 + 8) |= 0x1000000;
                    }
                    {
                    char *e8 = (char *)FI(0x1A8);
                    {
                    float cx = ((union IFAlias *)(e8 + 0))->f;
                    float cy = ((union IFAlias *)(e8 + 4))->f;
                    float cz = ((union IFAlias *)(e8 + 8))->f;
                    g90 = (char *)FP(0x60);
                    FF(0x60) = cx;
                    FF(0x64) = cy;
                    FF(0x68) = cz;
                    }
                    }
                }
                func_00243B18(g90, g90, f21);
                f20 = 5.0f;
                {
                char *rmv = (char *)&f74 - 4;
                GetRootMatrixByDObj(rmv, (void *)FI(0x30));
                func_00243AD0((char *)arg4 + 0x40, rmv, g90);
                }
                if (f21 > f20) {
                    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0xF000)) {
                        if ((float)a > 20.0f) {
                            float k15 = 15.0f;
                            float v2 = ((k15 - f21) * f20) / k15;
                            char *p;
                            v2 = (v2 < 0.0f) ? 0.0f : ((v2 > f20) ? f20 : v2);
                            g90 = (char *)FP(0x90);
                            func_00243B18(g90, (void *)FI(0x1C8), -v2);
                            {
                                pv = (char *)&f84 - 4;
                                p = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                func_00243AD0((float *)pv, p, g90);
                            }
                            {
                                int vv;
                                float cx = ((union IFAlias *)&FF(0x80))->f;
                                float cy = ((union IFAlias *)&FF(0x84))->f;
                                float cz = ((union IFAlias *)&FF(0x88))->f;
                                ((union IFAlias *)((char *)arg4 + 0x90))->f = cx;
                                ((union IFAlias *)((char *)arg4 + 0x94))->f = cy;
                                ((union IFAlias *)((char *)arg4 + 0x98))->f = cz;
                                vv = ((union IFAlias *)((char *)arg3 + 8))->i;
                                vv &= 0xFDFFFFFF;
                                vv &= 0xFBFFFFFF;
                                ((union IFAlias *)((char *)arg3 + 0xC))->i |= 0x40;
                                ((union IFAlias *)((char *)arg3 + 8))->i = vv;
                            }
                        }
                    }
                }
            }
            break;
        case 0x70:
            if (f21 < 20.0f && f24 > 1000.0f) {
                *(int *)((char *)arg3 + 8) |= 0x800000;
            }
            break;
        case 1:
        case 0xF:
        case 0x2A:
            if (f21 < 40.0f && f24 > 1000.0f) {
                *(int *)((char *)arg3 + 8) |= 0x800000;
            }
            break;
        case 3:
            if (f21 < 40.0f && f24 > 1000.0f) {
                {
                    int vv3 = (*(int *)((char *)arg3 + 8) & 0xFDFFFFFF) | ((FI(0x1BC) & 1) << 25);
                    *(int *)((char *)arg3 + 8) = vv3 | 0x800000;
                }
                g90 = (char *)FP(0x60);
                {
                    char *e8 = (char *)FI(0x1A8);
                    {
                    float cx = ((union IFAlias *)(e8 + 0))->f;
                    float cy = ((union IFAlias *)(e8 + 4))->f;
                    float cz = ((union IFAlias *)(e8 + 8))->f;
                    FF(0x60) = cx;
                    FF(0x64) = cy;
                    FF(0x68) = cz;
                    }
                }
                func_00243B18(g90, g90, f21 + 10.0f);
                f20 = 5.0f;
                {
                char *rmv = (char *)&f74 - 4;
                GetRootMatrixByDObj(rmv, (void *)FI(0x30));
                func_00243AD0((char *)arg4 + 0x40, rmv, g90);
                }
                if (f21 > f20) {
                    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0xF000)) {
                        if ((float)a > 20.0f) {
                            float k25 = 25.0f;
                            float v2 = ((k25 - f21) * f20) / k25;
                            char *p;
                            v2 = (v2 < 0.0f) ? 0.0f : ((v2 > f20) ? f20 : v2);
                            g90 = (char *)FP(0x90);
                            func_00243B18(g90, (void *)FI(0x1C8), -v2);
                            {
                                pv = (char *)&f84 - 4;
                                p = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                func_00243AD0((float *)pv, p, g90);
                            }
                            {
                                int vv;
                                float cx = ((union IFAlias *)&FF(0x80))->f;
                                float cy = ((union IFAlias *)&FF(0x84))->f;
                                float cz = ((union IFAlias *)&FF(0x88))->f;
                                ((union IFAlias *)((char *)arg4 + 0x90))->f = cx;
                                ((union IFAlias *)((char *)arg4 + 0x94))->f = cy;
                                ((union IFAlias *)((char *)arg4 + 0x98))->f = cz;
                                vv = ((union IFAlias *)((char *)arg3 + 8))->i;
                                vv &= 0xFDFFFFFF;
                                vv &= 0xFF7FFFFF;
                                ((union IFAlias *)((char *)arg3 + 0xC))->i |= 0x40;
                                ((union IFAlias *)((char *)arg3 + 8))->i = vv;
                            }
                        }
                    }
                }
            }
            break;
        }
        if (ACTEnvGetTest()) {
            if (f21 < 40.0f) {
                if (f24 > 1000.0f) {
                    char *sub2;
                    int m4;
                    sub2 = (char *)*(int *)((char *)FI(0x30) + 0x15C); m4 = 0x400000;
                    {
                        *(EnvCopy32 *)((char *)arg4 + 0x190) = *(EnvCopy32 *)(sub2 + 0x180);
                        ((union IFAlias *)arg3)->i |= m4;
                    }
                }
            }
        }
        if (f21 < 40.0f) {
            if (D_00631990 == 0x54 || D_00631990 == 3 || D_00631990 == 0x2E) {
                if (*(int *)((char *)FI(0x30) + 0xC) == 4) goto Lp2end;
            }
            if (DisableMotionOrientUpdate(FI(0x30), 0x400)) {
                if (f24 > 60.0f) {
                    char *dstc;
                    *(float *)((char *)arg4 + 0xA0) = *(float *)((char *)arg4 + 0x10);
                    *(float *)((char *)arg4 + 0xA4) = *(float *)((char *)arg4 + 0x14);
                    *(float *)((char *)arg4 + 0xA8) = *(float *)((char *)arg4 + 0x18);
                    ((union IFAlias *)((char *)arg3 + 8))->i |= 0x20000;
                    if (f21 < 10.0f) {
                        int a2;
                        a2 = __builtin_abs(EnvCamAngle((void *)w20v, (void *)FI(0x1C8), FP(0x60), 1.0f));
                        if (a2 < 0x3C) {
                            *(int *)((char *)arg3 + 8) |= 0x40000;
                        }
                    }
                    dstc = (char *)arg4 + 0xC0;
                    EnvPushAvg(FV(0x60), (void *)FI(0x30), dstc, 0x198);
                    *(float *)((char *)arg4 + 0xCC) = 1.0f;
                }
            }
        Lp2end:
            if (DisableMotionOrientUpdate(FI(0x30), 0xC000)) {
                *(int *)((char *)arg3 + 8) |= 0x800;
            }
        }
        if (f21 < 25.0f) {
            if (FI(0x1BC) != 0 &&
                ((char *)D_00631AE8 == 0 ||
                 *(int *)(*(char **)((char *)D_00631AE8 + 0x164) + 0x30) != 0x6B ||
                 *(int *)(*(char **)((char *)D_00631AE8 + 0x164) + 0x134) != FI(0x30))) {
                if (f24 < 55.0f) {
                    ((union LLAlias *)(env + 0x470))->ll |= 0x20000;
                } else if (f24 < 105.0f) {
                    ((union LLAlias *)(env + 0x470))->ll |= 0x40000;
                } else if (f24 < 205.0f) {
                    ((union LLAlias *)(env + 0x470))->ll |= 0x80000;
                }
            }
        }
        {
            int ccat;
            float rootUpd;
            if ((char *)FI(0x30) == (char *)D_00631AE4 && (char *)D_00631AE8 != 0 &&
                *(int *)(*(char **)((char *)D_00631AE8 + 0x164) + 0x30) != 0x26 &&
                f21 < 200.0f && ACTEnvGetTest() == 0 &&
                DisableMotionOrientUpdate(FI(0x30), 0x7000) == 0 &&
                DisableMotionOrientUpdate(FI(0x30), 0x400) == 0 &&
                func_00194590((void *)FI(0x1C8), (void *)wPtr20) < 0x3C) {
                FI(0x1CC) = 1; rootUpd = -EnableChangeRootUpdateMode((void *)D_00631AE4);
                if (!(f21 < 60.0f)) {
                    FI(0x1CC) = 0;
                }
                m = (char *)&f64 - 4;

                FI(0x1D0) = 1;
                ccat = 0;
                f22 = D_00633850_[0];
                GetRootMatrixByDObj(m, (void *)D_00631AE4);
                w70 = (char *)&f74 - 4;
                GetRootMatrixByDObj(w70, (void *)D_00631AE8);
                w70s = (char *)&f74 - 4;
                if (!(f24 < 55.0f)) {
                    if (f24 < 155.0f) {
                        f22 = 80.0f;
                        ccat = 0x64;
                    } else if (f24 < 255.0f) {
                        f22 = 160.0f;
                        ccat = 0xC8;
                    } else if (f24 < D_00631454) {
                        f22 = 160.0f;
                        ccat = 0x12C;
                    }
                }
                if ((char *)D_00631AE8 != 0 && (char *)D_00631AE4 != 0) {
                    char *p1 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                    m = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                    if (*(float *)(m + 4) + 800.0f < *(float *)(p1 + 4)) {
                        FI(0x1D0) = 0;
                    }
                }
                if (D_00631990 == 7) {
                    GetHeightOfWallFromGObj(FP(0x80), (void *)D_00631AE8);
                    if (ccat == 0xC8) {
                        if (!(f84 - FF(0x4) > 180.0f)) {
                            FI(0x1D0) = 0;
                        }
                        if (FF(0x0) * f80 < 0.0f) {
                            FI(0x1D0) = 0;
                        }
                    }
                }
                if ((int)(*(long long *)(*(char **)((char *)D_00631AE4 + 0x164) + 0x20) << 6 >> 32) & 1) {
                    if (FF(0x14) > 1600.0f) {
                        if ((ccat < 0xC8) == 0) ccat = 0;
                    }
                }
                FI(0x1D8) = (ccat < 0xC8);
                if (!(ccat < 0xC8)) {
                    char *fnd;
                    char *pb;
                    char *pcc;
                    FF(0xA0) = FF(0x0);
                    FF(0xA4) = FF(0x4);
                    FF(0xA8) = FF(0x8);
                    g90 = (char *)FP(0x90);
                    func_00243B18(g90, (void *)FI(0x1C8), f21 + 50.0f);
                    pb = (char *)&fB0;
                    func_00243AD0((float *)pb, FP(0xA0), g90);
                    *(float *)((char *)FP(0x80) + 0x34) = *(float *)((char *)FP(0x80) + 0x34) + f24;
                    _OrientGV(FP(0xC0), (void *)FI(0x1C8));
                    fnd = (char *)(int)*(long long *)&fE0;
                    fnd = (char *)(int)*(long long *)&fE4;
                    fnd = (char *)(int)*(long long *)&fE8;
                    fnd = (char *)(int)*(long long *)&fEC;
                    fnd = (char *)(int)*(long long *)&fF0;
                    fnd = (char *)(int)*(long long *)&fF4;
                    fnd = (char *)(int)*(long long *)&fF8;
                    fnd = (char *)(int)*(long long *)&fFC;
                    fnd = (char *)(int)*(long long *)&f100;
                    fnd = (char *)(int)*(long long *)&f104;
                    fnd = (char *)(int)*(long long *)&f108;
                    fnd = (char *)(int)*(long long *)&f10C;
                    fnd = (char *)(int)*(long long *)&f110;
                    fnd = (char *)(int)*(long long *)&f114;
                    fnd = (char *)(int)*(long long *)&f118;
                    fnd = (char *)(int)*(long long *)&f11C;
                    fnd = (char *)isysGObjSearchFromObjLayoutID(0x11);
                    while (fnd != 0) {
                        if (*(int *)(fnd + 0x16C) != 0 && ExecBoxMoveEndReaction(fnd) != 7) {
                            float d;
                            pcc = (char *)ContinueCorrectPosition(fnd);
                            FF(0x100) = *(float *)(pcc + 0);
                            pcc = (char *)ContinueCorrectPosition(fnd);
                            FF(0x104) = *(float *)(pcc + 4);
                            pcc = (char *)ContinueCorrectPosition(fnd);
                            FF(0x108) = *(float *)(pcc + 8);
                            if (RotateAccordingToStick_PatternThree((int)pb, FP(0x100)) < D_00631458) {
                                d = FF(0xB4) - FF(0x104);
                                if (!(d < 0.0f ? -d > 100.0f : d > 100.0f)) {
                                    func_00243AE8(FP(0x110), (void *)FI(0x1C4), FP(0x100));
                                    ((union IFAlias *)&FI(0x11C))->i = 0;
                                    func_002438B8(FP(0x120), FP(0xC0), FP(0x110));
                                    if (FF(0x120) < -30.0f || FF(0x120) > 40.0f) {
                                        FI(0x1D0) = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        fnd = (char *)isysGObjSearchFromObjKindID_begin(fnd);
                    }
                }
                if (FI(0x1C0) == 0) FI(0x1D0) = 0;
                if (ccat != 0 && f22 < rootUpd) {
                    if (FI(0x1D0) != 0) {
                        char *q;
                        q = (char *)&dv13;
                        q = (char *)*(int *)(q + 4);
                        g90 = (char *)(int)*(long long *)&w140;
                        g90 = (char *)(int)*(long long *)&w144;
                        g90 = (char *)(int)*(long long *)&w148;
                        g90 = (char *)(int)*(long long *)&w14C;
                        g90 = (char *)FP(0x140);
                        GetRootMatrixByDObj(g90, (void *)FI(0x30));
                        pv = (char *)FP(0x130);
                        func_00243B18(pv, (void *)FI(0x1C8), f21);
                        func_00243AD0((char *)arg4 + 0x50, g90, pv);
                        q = (char *)&w150;
                        q = (char *)*(int *)(q + 4);
                        q = (char *)(int)*(long long *)&w154;
                        q = (char *)(int)*(long long *)&w158;
                        q = (char *)(int)*(long long *)&w15C;
                        g90 = (char *)FP(0x160);
                        q = (char *)(int)*(long long *)&w164;
                        q = (char *)(int)*(long long *)&w168;
                        q = (char *)(int)*(long long *)&w16C;
                        GetRootMatrixByDObj(g90, (void *)FI(0x30));
                        pv = (char *)FP(0x150);
                        func_00243B18(pv, (void *)FI(0x1C8), f21 - 30.0f);
                        func_00243AD0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x740,
                                      FP(0x160), FP(0x150));
                        {
                            char *gq = (char *)FI(0x30);
                            q = (char *)*(int *)((char *)*(int *)(gq + 0x164) + 0x678);
                            ((union IFAlias *)(q + 0x750))->f = *(float *)((char *)arg4 + 0x10);
                            *(int *)(q + 0x764) = 0x14;
                            {
                                char *q2 = (char *)*(int *)((char *)*(int *)(gq + 0x164) + 0x678);
                                *(float *)(q + 0x754) = *(float *)((char *)arg4 + 0x14);
                                ((union IFAlias *)(q + 0x758))->f = *(float *)((char *)arg4 + 0x18);
                                ((union IFAlias *)(q + 0x760))->f = 30.0f;
                                *(int *)(q2 + 0x768) = 0;
                            }
                        }
                        ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 46;
                        if (FI(0x1CC) != 0) {
                            if (D_00631990 == 0x62) {
                                char *fnd2 = (char *)isysGObjSearchFromObjLayoutID(0x11);
                                if (fnd2 != 0) {
                                    char *p1 = (char *)ContinueCorrectPosition(fnd2);
                                    char *p2 = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                    if (RotateAccordingToStick_PatternThree((int)p1, p2) < D_0063145C &&
                                        FI(0x1D8) == 0 && ccat < 0x12D) {
                                        char *p1 = (char *)ContinueCorrectPosition(fnd2);
                                        char *p2 = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                        if (*(float *)(p1 + 4) > *(float *)(p2 + 4)) {
                                            float d2;
                                            char *p1 = (char *)ContinueCorrectPosition(fnd2);
                                            char *p2 = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                            d2 = *(float *)(p1 + 4) - *(float *)(p2 + 4);
                                            if (d2 < 0.0f) {
                                                char *p1 = (char *)ContinueCorrectPosition(fnd2);
                                                char *p2 = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                                if (-(*(float *)(p1 + 4) - *(float *)(p2 + 4)) > 100.0f) {
                                                    goto Lcfix;
                                                }
                                                goto Lnofix;
                                            } else {
                                                char *p1 = (char *)ContinueCorrectPosition(fnd2);
                                                char *p2 = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                                if (!((*(float *)(p1 + 4) - *(float *)(p2 + 4)) > 100.0f)) {
                                                    goto Lnofix;
                                                }
                                            }
                                        Lcfix:
                                            func_00243B18(FP(0x170), (void *)FI(0x1C8), -50.0f);
                                            ccat = (int)*(long long *)&w174;
                                            ccat = (int)*(long long *)&w178;
                                            ccat = *(int *)((char *)&dv18 + 4);
                                            ccat = *(int *)((char *)&dv19 + 4);
                                            ccat = *(int *)((char *)&dv1A + 4);
                                            ccat = 0xC8;
                                            func_00243AD0((char *)arg4 + 0x50,
                                                          (void *)ContinueCorrectPosition(fnd2), FP(0x170));
                                        Lnofix:;
                                        }
                                    }
                                }
                            }
                            *(int *)((char *)arg4 + 0x134) = ccat;
                            {
                            long long b478, v478;
                            switch (ccat) {
                            case 0x64:
                                ((union LLAlias *)(env + 0x470))->ll =
                                    *(long long *)(env + 0x470) | (0x8000LL << 48);
                                break;
                            case 0xC8:
                                v478 = *(long long *)(env + 0x478);
                                b478 = 1;
                            Lor478:
                                ((union LLAlias *)(env + 0x478))->ll = v478 | b478;
                                break;
                            case 0x12C:
                                b478 = 2;
                                v478 = *(long long *)(env + 0x478);
                                goto Lor478;
                            default:
                                func_001AD768(D_0061AE10, 0x978);
                                func_00263FF0(D_0061AE10, 0x978, D_00633840);
                                break;
                            }
                            }
                        }
                    }
                }
            }
            if ((char *)D_00631AE8 != 0 && (char *)FI(0x30) == (char *)D_00631AE4 &&
                f21 < 200.0f && f24 > 350.0f && wFlag != 0 && ACTEnvGetTest() == 0) {
                char *p1 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                char *p2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                if (!(HandyCamera_TargetMoveType(p1, p2) < D_00631460)) {
                    if ((char *)D_00631AE8 != 0 && (char *)D_00631AE4 != 0) {
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                        if (*(float *)(p2 + 4) + 800.0f < *(float *)(p1 + 4)) goto Lchain;
                    }
                    if (*(int *)(*(char **)((char *)D_00631AE8 + 0x164) + 0x30) != 4) {
                        float lim2;
                        float rr;
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                        rr = RotateAccordingToStick_PatternThree((int)p1, p2);
                        lim2 = f21 + 100.0f;
                        if (rr < lim2 * lim2) goto Lchain;
                    }
                    {
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                        if (RotateAccordingToStick_PatternThree((int)p1, p2) < D_00631464) {
                            if (EnableChangeRootUpdateMode((void *)D_00631AE8, (void *)D_00631AE4) > 300.0f) {
                                goto Lchain;
                            }
                        }
                    }
                    {
                        char *p80;
                        char *p1;
                        char *p2;
                        p80 = (char *)&dv13;
                        p1 = (char *)ContinueCorrectPosition((void *)D_00631AE8);
                        p2 = (char *)ContinueCorrectPosition((void *)D_00631AE4);
                        func_001947D0(p80, p1, p2);
                    if (func_00194590(p80, (void *)FI(0x1C8)) < 0x50) {
                        FI(0x194) = 0;
                        FI(0x198) = 0;
                        func_001FC520((void *)&FI(0x190), (void *)&FI(0x194),
                                      FP(0x160), FP(0x170), (void *)&FI(0x198));
                        {
                            int idx;
                            char *ca = (char *)arg4 + 0x10;

                            for (idx = 0; 0.0f <= ((float *)FI(0x190))[idx]; idx++) {
                                if (func_001FC6C8((char *)FP(0x140), FP(0x10), (void *)FI(0x1C8),
                                                  f21, ((float *)FI(0x190))[idx])) {
                                    func_00243B18(FP(0x150), ca, -1.0f);
                                    if (FI(0x194) != 0) {
                                        float t0 = ((union IFAlias *)&w160)->f;
                                        float t1 = ((union IFAlias *)&w164)->f;
                                        float t2 = ((union IFAlias *)&w168)->f;
                                        float t3 = w170;
                                        float t4 = w174;
                                        float t5 = w178;
                                        w140 = t0;
                                        w144 = t1;
                                        w148 = t2;
                                        w150 = t3;
                                        w154 = t4;
                                        w158 = t5;
                                    }
                                    if (f21 < 60.0f) {
                                        float t0, t1, t2, t3, t4, t5;
                                        *(unsigned char *)(env + 0x520) = *(unsigned char *)FP(0x198);
                                        t0 = w140;
                                        t1 = w144;
                                        t2 = w148;
                                        t3 = w150;
                                        t4 = w154;
                                        t5 = w158;
                                        *(float *)((char *)arg4 + 0x60) = t0;
                                        *(float *)((char *)arg4 + 0x64) = t1;
                                        *(float *)((char *)arg4 + 0x68) = t2;
                                        *(float *)((char *)arg4 + 0x70) = t3;
                                        *(float *)((char *)arg4 + 0x74) = t4;
                                        *(float *)((char *)arg4 + 0x78) = t5;
                                        ((union LLAlias *)(env + 0x478))->ll |= 0x20;
                                    } else {
                                        char *q;
                                        func_00243B18(FP(0x180), ca, f21 - 30.0f);
                                        func_00243AD0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x7A0,
                                                      FP(0x10), FP(0x180));
                                        {
                                            char *gq2 = (char *)FI(0x30);
                                            q = (char *)*(int *)((char *)*(int *)(gq2 + 0x164) + 0x678);
                                            *(float *)(q + 0x7B0) = *(float *)((char *)arg4 + 0x10);
                                            *(int *)(q + 0x7C4) = 0x14;
                                            *(float *)(q + 0x7B4) = *(float *)((char *)arg4 + 0x14);
                                            *(float *)(q + 0x7B8) = *(float *)((char *)arg4 + 0x18);
                                            *(float *)(q + 0x7C0) = 30.0f;
                                            *(int *)(*(int *)((char *)*(int *)(gq2 + 0x164) + 0x678) + 0x7C8) = 0;
                                        }
                                        ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 48;
                                    }
                                    break;
                                }
                            }

                        }
                    }
                    }
                }
            }
        }
    Lchain:
        if ((*(unsigned int *)((char *)arg3 + 8) >> 23) & 1) {
            if (f21 < 40.0f) goto Lchainbody;
            goto Lafter;
        }
        if (!(f21 < 30.0f)) goto Lafter;
    Lchainbody:
        {
            char *hit;
            char *fnd3;
            char *pp;
            hit = 0;
            {
                float t0 = *(float *)((char *)arg4 + 0x10);
                float t1 = *(float *)((char *)arg4 + 0x14);
                float t2 = *(float *)((char *)arg4 + 0x18);
                w140 = t0;
                w144 = t1;
                w148 = t2;
            }
            func_001945B8(FP(0x140), D_00631468);
            fnd3 = (char *)isysGObjSearchFromObjLayoutID(0x15);
            if (fnd3 != 0) {
                float fth;
                float zero;
                float c70;
                float c100;
                float d20;
                fth = D_0063146C;
                zero = 0.0f;
                c70 = 70.0f;
                c100 = 100.0f;
                g90 = (char *)FP(0x160);
                w70 = (char *)&w154 - 4;
                do {
                if (*(int *)(fnd3 + 0x16C) != 0) {
                    float d;
                    if (InitPendulum(fnd3) == 0) goto Lnext3;
                    GetRootMatrixByDObj(FP(0x170), fnd3);
                    if (!(func_00194590(FP(0x170), (void *)FI(0x1C8)) < 0x2E)) goto Lnext3;
                    GetRootMatrixByDObj(g90, fnd3);
                    func_00243AE8(w70, g90, FP(0));
                    d20 = func_00243950(w70, FP(0x140));
                    if (RotateAccordingToStick_PatternThree((int)FP(0), g90) < fth) {
                        d = FF(0x4) - ((union IFAlias *)&w164)->f;
                        if (d < zero) {
                            if (-d < c70) goto Lc70a;
                            goto Lnext3;
                        } else {
                            if (!(d < c70)) goto Lnext3;
                        }
                    Lc70a:
                        if (d20 < zero ? -d20 < c100 : d20 < c100) {
                            hit = fnd3;
                            goto Lgot3;
                        }
                    }
                }
            Lnext3:
                fnd3 = (char *)isysGObjSearchFromObjKindID_begin(fnd3);
                } while (fnd3 != 0);
            Lgot3:;
            }
            {
                char *cg;
                cg = (char *)FI(0x1C0);
                if (cg != 0) {
                t80v = (char *)FP(0x180);
                pp = (char *)ContinueCorrectPosition(cg);
                func_00243AE8(t80v, pp, (void *)FI(0x1C4));
                v18[1] = 0;
                if (0.0f < func_00243950(t80v, (void *)FI(0x1C8))) {
                    hit = (char *)FI(0x1C0);
                }
                }
            }
            if (hit == 0) goto Lafter;
            ((union LLAlias *)(env + 0x470))->ll |= 0x8000LL << 39;
            *(int *)((char *)arg4 + 0x15C) = (int)hit;
            pp = (char *)ContinueCorrectPosition(hit);
            v1A[0] = *(float *)(pp + 0);
            pp = (char *)ContinueCorrectPosition(hit);
            v1A[1] = *(float *)(pp + 4);
            pp = (char *)ContinueCorrectPosition(hit);
            v1A[2] = *(float *)(pp + 8);
            func_00243B18((void *)v19, (void *)FI(0x1C8), -20.0f);
            func_00243AD0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670) + 0x1C0,
                          (void *)v1A, (void *)v19);
            *(float *)(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670) + 0x1C4) = FF(0x14);
        }
    Lafter:;
    }
    }
    {
    int e30;
    char *g8;
    ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x200);
    {
    me0 = (char *)FI(0x30);
    g8 = (char *)D_00631AE8;
    e30 = *(int *)(env + 0x30);
    if (((int)me0 ^ (int)g8) == 0 && e30 == 0x45) {
        long long ll6;
        float e = -EnableChangeRootUpdateMode((void *)D_00631AE4, me0);
        ll6 = *(long long *)(env + 0x470);
        if ((int)(ll6 << 21 >> 32) & 1) {
            if (e > 5.0f) {
                long long t6 = ll6 | (0x8000LL << 47);
                *(long long *)(env + 0x470) = t6;
                ll6 = t6;
                ((union LLAlias *)(env + 0x478))->ll |= 4;
            }
        }
        if ((int)(ll6 << 20 >> 32) & 1) {
            if (e > 60.0f) {
                if (*(int *)(*(char **)((char *)D_00631AE4 + 0x164) + 0x30) == 0x37) {
                    ((union LLAlias *)(env + 0x478))->ll |= 8;
                }
                ((union LLAlias *)(env + 0x478))->ll |= 0x10;
            }
        }
        if ((int)(ll6 >> 13) & 1) {
            if (e > 195.0f) s6 = 1;
        }
        g8 = (char *)D_00631AE8;
        e30 = *(int *)(env + 0x30);
    }
    }
    if (g8 != 0) {
        ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 30;
    }
    if (*(int *)(env + 0x170) != 0) {
        ((union LLAlias *)(env + 0x470))->ll |= 0x8000LL << 22;
    }
    {
    char *vw;
    vw = (char *)FI(0x30);
    if (vw == (char *)D_00631AE4 &&
        e30 != 0xE) {
        char *w;
        if (*(int *)(env + 0x130) != 0) {
            w = (char *)WeaponHitEffect((void *)*(int *)(env + 0x130), g8, 150.0f);
        } else {
            w = (char *)WeaponHitEffect(vw, g8, 150.0f);
        }
        if (w != 0) {
            char *pp;
            *(int *)((char *)arg4 + 0x158) = (int)w;
            ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 37;
            w60 = (char *)FP(0x60);
            {
                char *pp;
                pp = (char *)ContinueCorrectPosition(w);
                *(float *)(w60 + 0) = *(float *)(pp + 0);
                pp = (char *)ContinueCorrectPosition(w);
                *(float *)(w60 + 4) = *(float *)(pp + 4);
                pp = (char *)ContinueCorrectPosition(w);
                *(float *)(w60 + 8) = *(volatile float *)(pp + 8);
            }
            g90 = (char *)&f74 - 4;
            w70 = (char *)&f64 - 4;
            func_001947D0(g90, w70, FP(0x10));
            if ((func_00194590(g90, (void *)FI(0x1A8)) < 0x2D &&
                 RotateAccordingToStick_PatternThree((int)w70, FP(0x10)) < 6400.0f) ||
                (func_00194590(g90, (void *)FI(0x1A8)) >= 0x2D &&
                 RotateAccordingToStick_PatternThree((int)w70, FP(0x10)) < 900.0f)) {
                ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 36;
                e30 = *(int *)(env + 0x30);
                *(int *)((char *)arg4 + 0x158) = (int)w;
            } else {
                e30 = *(int *)(env + 0x30);
            }
        } else {
            e30 = *(int *)(env + 0x30);
        }
    }
    }
    if ((unsigned int)e30 < 0x3B) {
        if ((unsigned int)e30 >= 0x39) {
            isStopChain((void *)*(int *)(env + 0x180), FP(0x19C), FP(0x1A0), FP(0x1A4));
            if (0.0f < FF(0x19C)) {
                ((union LLAlias *)(env + 0x470))->ll |= 0x8000LL << 37;
            } else {
                ((union LLAlias *)(env + 0x470))->ll |= 0x8000LL << 38;
            }
        }
    }
    }
    v1 = (char *)FI(0x30);
    if (v1 == (char *)D_00631AE4 && (char *)D_00631AE8 != 0) {
        char *h = *(char **)((char *)D_00631AE8 + 0x164);
        if (*(int *)(h + 0x30) == 0x6B) {
            char *g = *(char **)((char *)FI(0x30) + 0x134);
            if (*(int *)(*(char **)(g + 0x164) + 0x30) == 0x64) {
                if (GetDifferenceFromWallUpperPlane(g)) {
                    if (func_00145328((void *)FI(0x30), (void *)D_00631AE8, 0x78, FP(0x60),
                                      200.0f, 400.0f)) {
                        char *b;
                        char *pp;
                        b = (char *)PAIR_GetPosition_BOY((int)(char *)ContinueCorrectPosition(g), 0x21);
                        pp = (char *)ContinueCorrectPosition(b);
                        if (RotateAccordingToStick_PatternThree((int)FP(0x10), pp) < D_00631470) {
                            char *cc = (char *)FI(0x30);
                            ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 38;
                            *(int *)(*(char **)(*(char **)(cc + 0x164) + 0x670) + 0x2E0) = (int)b;
                        }
                    }
                }
            }
        }
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x800) ||
        ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x900)) {
        ((union LLAlias *)(env + 0x470))->ll |= 0x100;
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x800000)) {
        char *q2;
        pv = (char *)&f64 - 4;
        func_00243978(pv, *(char **)((char *)FI(0x30) + 0x15C) + 0x1D0);
        q2 = *(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670);
        *(float *)(q2 + 0x270) = *(float *)w60v;
        *(float *)(q2 + 0x274) = FF(0x64);
        *(float *)(q2 + 0x278) = FF(0x68);
        if (0.0f < func_00243950(subCommonIdle((void *)FI(0x30)), pv)) {
            char *mc;
            mc = (char *)FI(0x30); ((union LLAlias *)(env + 0x470))->ll |= 0x200;
            *(char *)(*(char **)(*(char **)(mc + 0x164) + 0x670) + 0x280) = 0;
        } else {
            char *mc;
            int one;
            { mc = (char *)FI(0x30); one = 1; ((union LLAlias *)(env + 0x470))->ll |= 0x400;
                 *(char *)(*(char **)(*(char **)(mc + 0x164) + 0x670) + 0x280) = (char)one; }
        }
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x40)) {
        ((union LLAlias *)(env + 0x470))->ll |= 0x10;
        debug_assertMessage(D_00633848);
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x50)) {
        *(long long *)(env + 0x470) |= 0x20;
        {
            float *wp = (float *)((char *)((union IFAlias *)((char *)FI(0x30) + 0x15C))->i + 0x644);
            float wv = *wp;
            if ((char *)FI(0x30) == (char *)D_00631AE4 ? (wv > 110.0f) : (wv > 135.0f)) {
                ((union LLAlias *)(env + 0x470))->ll |= 0x40;
                debug_assertMessage(D_0061AE20);
            }
        }
        {
            float *wp = (float *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x644);
            if ((char *)FI(0x30) == (char *)D_00631AE4 ? (*wp < 105.0f) : (*wp < 130.0f)) {
                ((union LLAlias *)(env + 0x470))->ll |= 0x80;
                debug_assertMessage(D_0061AE30);
            }
        }
    }
    if ((char *)FI(0x30) == (char *)D_00631AE4) {
        char *t16;
        char *t30v = 0;
        char *t22v = 0;
        char *t23v = 0;
        float rad = 90.0f;
        {
            MotionEntry *mo3 = &D_00565060[*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x4A0)];
            if (mo3->u186 & 7) {
                rad = 100.0f;
            }
        }
        t16 = (char *)InitTorchGeo((void *)FI(0x30), 200.0f);
        if (t16 != 0) {
            w70 = w70s;
            GetRootMatrixByDObj(w70, t16);
            g90 = w70;
            if (RotateAccordingToStick_PatternThree((int)FP(0), w70) < rad * rad &&
                FF(0x74) < FF(0x4)) {
                if (func_00194840(w70, FP(0), subCommonIdle((void *)FI(0x30)), 0x2D)) {
                    float d = FF(0x74) - FF(0x4);
                    w70 = 0;
                    if (d < 0.0f) {
                        if (-d < 200.0f) goto Lct1;
                        goto Lskip_t1;
                    } else {
                        if (!(d < 200.0f)) goto Lskip_t1;
                    }
                Lct1:
                    if (FF(0x74) < FF(0x4)) {
                        t23v = t16;
                        func_001947D0((char *)arg4 + 0x20, g90, FP(0));
                        t30v = t23v;
                    }
                Lskip_t1:;
                }
            }
        }
        t16 = (char *)LightTorchOn((void *)FI(0x30), 200.0f);
        if (t16 != 0) {
            char *wt;
            int lit = 0;
            char *q1 = *(char **)(*(char **)(t16 + 0x15C) + 0x0);
            if (q1 != 0) {
                int k1 = *(int *)(q1 + 0xC);
                k1 ^= 0x13;
                lit = ((unsigned int)k1 < 1);
            }
            wt = (char *)&f70;
            GetRootMatrixByDObj(wt, t16);
            if (lit == 0 &&
                RotateAccordingToStick_PatternThree((int)FP(0), wt) < D_00631474 &&
                FF(0x74) < FF(0x4)) {
                if (func_00194840(wt, FP(0), subCommonIdle((void *)FI(0x30)), 0x2D)) {
                    float d = FF(0x74) - FF(0x4);
                    if (d < 0.0f) {
                        if (-d < 200.0f) goto Lct2;
                        goto Lskip_t2;
                    } else {
                        if (!(d < 200.0f)) goto Lskip_t2;
                    }
                Lct2:
                    if (FF(0x74) < FF(0x4)) {
                        t22v = t16;
                        func_001947D0((char *)arg4 + 0x30, wt, FP(0));
                        *(int *)((char *)arg4 + 0x168) = (int)t22v;
                    }
                Lskip_t2:;
                }
            }
        }
        if (ACTGame_ConnectHand((void *)FI(0x30)) == 0) {
            char *r2 = (char *)ACTGameCollisionOff((void *)*(int *)(env + 0x140));
            if (r2 != 0) {
                if (TorchGeo(r2) == 0) {
                    if (t30v != 0) {
                        ((union LLAlias *)(env + 0x470))->ll |= 0x4000000;
                    }
                } else {
                    if (t22v != 0) {
                        ((union LLAlias *)(env + 0x470))->ll |= 0x10000000;
                    }
                }
            }
        }
        if (*(int *)(env + 0x170) != 0) {
            char *ln = (char *)_getLine(*(int *)(env + 0x170));
            if (t23v != 0 && ln != 0) {
                if (TorchGeo(ln) == 0) {
                    *(int *)((char *)arg4 + 0x164) = (int)ln;
                    ((union LLAlias *)(env + 0x470))->ll |= 0x8000000;
                }
            }
        }
        {
            char *sub3 = *(char **)((char *)FI(0x30) + 0x15C);
            int ok = 0;
            if (*(int *)(sub3 + 0x578) != 0 && *(float *)(sub3 + 0x5E0) < 50.0f) ok = 1;
            if (ok == 0) {
                ((union LLAlias *)(env + 0x470))->ll |= 8;
            }
        }
    }
    if ((*(unsigned int *)((char *)arg3 + 4) >> 30) & 1) {
        char *mS = (char *)FI(0x30);
        {
        char *q3 = *(char **)(*(char **)(mS + 0x164) + 0x670);
        *(int *)(q3 + 0x2C4) = (int)box;
        moveBoxAutoMatic(q3 + 0x2D0, box, mS);
        }
    }
    w70 = 0;
    return;
#undef FF
#undef FI
#undef FP
#undef v00
#undef v01
#undef v02
#undef m30
#undef v04
#undef v0C
#undef v0D
#undef v0E
#undef v10
#undef v12
#undef v13
#undef work
}

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200848);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200970);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_002009F0);

int func_00200A98(int a0)
{
    unsigned char v0;
    if (D_00631990 == 4) {
        v0 = EnableMotionOrientUpdate(a0, 0x1000);
    } else {
        v0 = ForMotionViewer_GetCurrentMotion(a0, 0x1000);
    }
    return v0 & 0xFF;
}

