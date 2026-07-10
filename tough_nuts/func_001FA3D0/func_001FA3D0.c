#include "common.h"
#include "ico/types.h"

extern int  D_0070A8C0[];
extern void adpcmPauseRequest(short *p, int doubled_idx);

void GetDitchPosition(void)
{
    int i;
    for (i = 0; i < 0xB0; i += 0x58) {
        int *p = (int *)((char *)D_0070A8C0 + i);
        if (*p != 0) {
            int v = *(int *)((char *)p + 0x38);
            if (v == 0x20000) goto call0;
            if (v != 0x40000) goto skip;
            adpcmPauseRequest((short *)p, 2);
        call0:
            adpcmPauseRequest((short *)p, 0);
        skip: ;
        }
    }
}

int DebugActOrientFlag(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x2C);
    p += a1;
    return *(short *)((char *)p + 0x3C);
}

int ACTGetEnvironment(char *a0) {
    char *p = *(char **)(a0 + 0x2C);
    return *(short *)(p + 0x3C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", ACTSetEnvAllmighty);

void GetSofaPosition(void) {
}

void GetCollisCenterPositionSimple(void) {
}

extern int inflate_stored(void *a0, int a1, int a2);

int CheckWallAttributeEdegWall(void *a0, int *a1) {
    inflate_stored(a0, a1[3], 0x5C000);
    return 1;
}

void func_001FA070(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA078);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA130);

extern float D_0062D9D8_[] __asm__("D_0062D9D8");
#define D_0062D9D8 (D_0062D9D8_[0])
extern int D_00629DE8;
extern int *D_00629DE4;
extern float D_00629730;
extern void func_00260568(void *a0, int a1, int a2);
extern float func_00149D00(int a0);
extern void GetHeightOfWallFromGObj(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void func_001443B8(void *a0, void *a1, int a2);
extern void *isysGObjSearchFromObjLayoutID();
extern void *isysGObjSearchFromObjKindID_begin(void *a0);
extern void CageFixDL(void *a0, void *a1, void *a2);
extern int ContinueCorrectPosition(void *a0);
extern float RotateAccordingToStick_PatternThree(int a0, void *a1);
extern void eBrainProcess(void *a0, void *a1);
extern void debug_Marker(void *a0, int a1, int a2, int a3, float a4);
extern int DisableMotionOrientUpdate(int a0, int a1);
extern void fzMagnitudefv(void *a0, int a1, void *a2);
extern int ACTEnvGetTest(void);
extern void func_00240038(float *a0, float *a1, float a2);
extern int HandCameraCorrect(void *a0, void *a1);
extern float D_0062D9DC_[] __asm__("D_0062D9DC");
#define D_0062D9DC (D_0062D9DC_[0])
typedef struct {
    char pad0[0x17C];
    float f17C;
    int i180;
    unsigned short u184, u186;
    unsigned int u188;
    unsigned int u18C;
} MotionEntry;  /* 0x190 stride */
extern MotionEntry D_0055DA10[];
extern int D_00629C90;
extern void *subCommonIdle(void *a0);
extern int ExecBoxMoveEndReaction(void *a0);
extern int func_00191D90(void *a0, void *a1);
extern int ForMotionViewer_GetCurrentMotion(int a0, int a1);
extern int EnableMotionOrientUpdate(int a0, int a1);
extern void _OrientGV(void *a0, void *a1);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void func_0023FDD8(void *a0, void *a1, void *a2);
extern void func_0023FFF0(float *a0, float *a1, float *a2);
extern int func_00149CA0(void *a0, int a1);
extern float func_0023FE70(void *a0, void *a1);
extern int GetBoxGlobalHoldPoint(void *a0);
extern int moveBoxAutoMatic(void *a0, void *a1, void *a2);
extern int InitWallLeverGeo(void *a0);
extern int func_001BDF68(void *a0);
extern char D_006138D0[];
extern MotionEntry D_005EBC48[];
extern float func_001920F0(int a0, float a1);
extern void ActOrientTest(void *a0, void *a1, int a2);
extern int ChangeFieldCollisionDebugMode(void *a0);
extern int QueenInqDead(void);
extern void CheckFieldContact(void *a0);
extern void dispPlane(void *a0, void *a1);
extern int ForMotionViewer_GetCurrentAnimationFrame(int a0, int a1);
extern float EnableChangeRootUpdateMode();
extern void func_00191FD0();
extern float HandyCamera_TargetMoveType(void *a0, void *a1);
extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern char D_0062D9C8[];
extern char D_006139D0[];
extern float D_004C6EC0[];
extern float D_004C6ED0[];
extern float D_004C6EE0[];
extern float D_004C6EF0[];
extern float D_004C6F00[];
extern char D_004C6F10[];
extern char D_004C6F20[];
extern float D_004C6F30[];
extern float D_00629734;
extern float D_00629738;
extern float D_0062973C;
extern float D_00629740;
extern float D_00629744;
extern float D_00629748;
extern float D_0062974C;
extern int func_001FA078(void *a0, void *a1, void *a2, float f12, float f13);
extern void func_00191DB8(void *a0, float f12);
extern float D_00629750;
extern float D_00629754;
extern float D_00629758;
extern float D_0062975C;
extern void isStopChain(void *a0, void *a1, void *a2, void *a3);
extern int GetDifferenceFromWallUpperPlane(void *a0);
extern int func_00143DE0(void *a0, void *a1, int a2, void *a3, float f12, float f13);
extern int *PAIR_GetPosition_BOY(int a0, int a1);
extern void *WeaponHitEffect(void *a0, float radius);
extern int func_00192040(void *a0, void *a1, void *a2, int a3);
extern void func_0023FE98(void *a0, void *a1);
extern void debug_assertMessage();
extern void *InitTorchGeo(void *a0, float radius);
extern void *LightTorchOn(void *a0, float radius);
extern int TorchGeo(void *a0);
extern void *_getLine();
extern int ACTGame_ConnectHand(void *a0);
extern void *ACTGameCollisionOff(void *a0);
extern char D_0062D9D0[];
extern char D_006139E0[];
extern char D_006139F0[];

typedef struct {
    long long a, b, c, d;
} __attribute__((packed)) EnvCopy32;

typedef float AVEC[4] __attribute__((aligned(16)));

union LLAlias { long long ll; };
union PFAlias { char *p; float f; };
union IFAlias { int i; float f; };

static inline void EnvGetPos(float *dst, void *obj) {
    char *pp;
    pp = (char *)ContinueCorrectPosition(obj);
    dst[0] = *(float *)(pp + 0);
    pp = (char *)ContinueCorrectPosition(obj);
    dst[1] = *(float *)(pp + 4);
    pp = (char *)ContinueCorrectPosition(obj);
    dst[2] = *(float *)(pp + 8);
}

static inline int EnvCamAngle(void *tgt, void *refsrc, void *buf, float k) {
    func_00240038(buf, refsrc, k);
    return HandCameraCorrect(tgt, buf);
}

static inline int EnvCamAngleP(int *tgtp, void *refsrc, void *buf, float k) {
    func_00240038(buf, refsrc, k);
    return HandCameraCorrect((void *)*tgtp, buf);
}

static inline float EnvSlotDist(int p, float *q) {
    return RotateAccordingToStick_PatternThree(p, q);
}




static inline int EnvPushPlane(float *tA, float *tB, void *Sv, char *env, void *a4v, float kf, float dist)
{
    float *dst = (float *)(env + 0x580);
    float k;
    GetRootMatrixByDObj(tA, Sv);
    k = dist - kf;
    func_00240038(tB, (float *)a4v, -k);
    func_0023FFF0(dst, tA, tB);
    return 0;
}


static inline int EnvOrientProbe(char *buf, void *Sv, float ang)
{
    func_00260568(buf, 0, 0xC0);
    ActOrientTest(buf, Sv, 0x2C);
    *(float *)(buf + 0x10) = *(float *)(buf + 0x0);
    *(float *)(buf + 0x18) = *(float *)(buf + 0x8);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x4) + 200.0f;
    ChangeFieldCollisionDebugMode(buf);
    {
        int r;
        if (*(int *)(buf + 0x94) != 0) {
            r = 0;
            if (ang + (*(float *)(buf + 0x24) - *(float *)(buf + 0x4)) < 250.0f) goto Lopdone;
        }
        r = 1;
    Lopdone:
        return r;
    }
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
        func_0023FFF0(acc, acc, (float *)w);
        w += 0x10;
        i--;
    } while (i >= 0);
    func_00240038((float *)dstc, acc, 0.25f);
    return 0;
}

static inline void EnvHeadPushVec(float *acc, void *Sv, void *a4v)
{
    char *S = (char *)Sv;
    char *dstc = (char *)a4v + 0xC0;
    char *head;
    char *w;
    int i;
    head = *(char **)(((union PFAlias *)(S + 0x15C))->p + 0x188);
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    w = head;
    i = 3;
Lac6:
    func_0023FFF0(acc, acc, (float *)w);
    w += 0x10;
    i--;
    if (i >= 0) goto Lac6;
    func_00240038((float *)dstc, acc, 0.25f);
    *(float *)((char *)a4v + 0xCC) = 1.0f;
}

static inline int EnvAssistLoop(float *acc, char *S, char *dst)
{
    char *head;
    char *w;
    int i;
    head = *(char **)(((union PFAlias *)(S + 0x15C))->p + 0x178);
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    i = 3;
    w = head;
    do {
        func_0023FFF0(acc, acc, (float *)w);
        w += 0x10;
        i--;
    } while (i >= 0);
    func_00240038((float *)dst, acc, 0.25f);
    return 0;
}

static inline int EnvAssistTail(float *tmp, char *anch, char *dst, float ascale)
{
    func_00240038(tmp, (float *)anch, ascale);
    func_0023FFF0((float *)dst, (float *)dst, tmp);
    return 0;
}

#define EnvWallAssistVec(acc_, tmp_, Sv_, dst_, ascale_) { \
    char *S = (char *)(Sv_); \
    char *anch = *(char **)(S + 0x164) + 0x4A0; \
    char *dst2 = (dst_); \
    EnvAssistLoop((acc_), S, dst2); \
    if (box != 0) { \
        *(float *)(dst2 + 0xC) = 1.0f; \
        func_0023FDD8(dst2, (void *)*(int *)(*(char **)(box + 0x15C) + 0xC), dst2); \
    } \
    EnvAssistTail((tmp_), anch, dst2, (ascale_)); \
}

void func_001FA3D0(void *arg0, void *arg1, int arg2, void *arg3, void *arg4) {
    struct {
        AVEC v00, v01, v02;
        struct { int gobj; float ang; int pad8, padC; } m30;
        AVEC v04, v05, v06, v07, v08, v09, v0A, v0B, v0C, v0D, v0E, v0F;
        AVEC v10, v11, v12, v13, v14, v15, v16;
        float v17[8];
        int work[8];
    } __attribute__((aligned(16))) W;
    int w1B0, w1B4, w1B8, w1BC, w1C0, w1C4, w1C8, w1CC, w1D0, w1D4, w1D8, w1DC;
#define v00 W.v00
#define v01 W.v01
#define v02 W.v02
#define m30 W.m30
#define v04 W.v04
#define v05 W.v05
#define v06 W.v06
#define v07 W.v07
#define v08 W.v08
#define v09 W.v09
#define v0A W.v0A
#define v0B W.v0B
#define v0C W.v0C
#define v0D W.v0D
#define v0E W.v0E
#define v0F W.v0F
#define v10 W.v10
#define v11 W.v11
#define v12 W.v12
#define v13 W.v13
#define v14 W.v14
#define v15 W.v15
#define v16 W.v16
#define v17 W.v17
#define work W.work
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
#define FI_0x30  m30.gobj
#define FF_0x34  m30.ang
#define FP_0x40  ((void *)v04)
#define FP_0x50  ((void *)v05)
#define FF_0x54  v05[1]
#define FV_0x60  v06
#define FP_0x60  ((void *)v06)
#define FF_0x60  v06[0]
#define FI_0x60  v06[0]
#define FF_0x64  v06[1]
#define FI_0x64  v06[1]
#define FF_0x68  v06[2]
#define FI_0x68  v06[2]
#define FV_0x70  v07
#define FP_0x70  ((void *)v07)
#define FF_0x70  v07[0]
#define FI_0x70  v07[0]
#define FF_0x74  v07[1]
#define FI_0x74  v07[1]
#define FI_0x78  v07[2]
#define FP_0x78  ((void *)&v07[2])
#define FF_0x7C  v07[3]
#define FI_0x7C  v07[3]
#define FV_0x80  v08
#define FP_0x80  ((void *)v08)
#define FF_0x80  v08[0]
#define FI_0x80  v08[0]
#define FF_0x84  v08[1]
#define FI_0x84  v08[1]
#define FF_0x88  v08[2]
#define FI_0x88  v08[2]
#define FP_0x90  ((void *)v09)
#define FF_0x90  v09[0]
#define FF_0x94  v09[1]
#define FF_0x98  v09[2]
#define FP_0xA0  ((void *)v0A)
#define FF_0xA0  v0A[0]
#define FF_0xA4  v0A[1]
#define FF_0xA8  v0A[2]
#define FP_0xB0  ((void *)v0B)
#define FF_0xB0  v0B[0]
#define FF_0xB4  v0B[1]
#define FF_0xB8  v0B[2]
#define FP_0xC0  ((void *)v0C)
#define FF_0xC0  v0C[0]
#define FF_0xC4  v0C[1]
#define FI_0xC4  v0C[1]
#define FF_0xC8  v0C[2]
#define FP_0xD0  ((void *)v0D)
#define FF_0xD0  v0D[0]
#define FF_0xD4  v0D[1]
#define FF_0xD8  v0D[2]
#define FP_0xE0  ((void *)v0E)
#define FF_0xE0  v0E[0]
#define FF_0xE4  v0E[1]
#define FF_0xE8  v0E[2]
#define FF_0xF4  v0F[1]
#define FP_0x100 ((void *)v10)
#define FF_0x100 v10[0]
#define FF_0x104 v10[1]
#define FF_0x108 v10[2]
#define FP_0x110 ((void *)v11)
#define FI_0x11C v11[3]
#define FP_0x120 ((void *)v12)
#define FF_0x120 v12[0]
#define FP_0x130 ((void *)v13)
#define FP_0x140 ((void *)v14)
#define FP_0x150 ((void *)v15)
#define FP_0x160 ((void *)v16)
#define FI_0x164 (*(int *)&v16[1])
#define FP_0x170 ((void *)v17)
#define FI_0x190 work[0]
#define FI_0x194 work[1]
#define FI_0x198 work[2]
#define FP_0x198 ((void *)&work[2])
#define FF_0x19C (*(float *)&work[3])
#define FP_0x19C ((void *)&work[3])
#define FP_0x1A0 ((void *)&work[4])
#define FP_0x1A4 ((void *)&work[5])
#define FI_0x1A8 work[6]
#define FI_0x1AC work[7]
#define box bx
#define boxp bx
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
#define FI_0x1DC w1DC
    float f20, f21, f22, f23, f24, f25;
    char *w70;
    char *g90;
    char *t80v;
    char *bx;
    char *env;
    int s6, s7;
    void *found;
    char *m;
    char *v1;
    char *S;
    char *boy = (char *)arg1;
    int za;

    {
        char *S0 = (char *)arg0;
        env = *(char **)(S0 + 0x164);
        v1 = *(char **)(S0 + 0x15C);
        FI(0x1A8) = arg2;
    }
    S = *(char **)(env + 0x110);
    FI(0x1AC) = *(int *)(v1 + 0x170);
    za = 0;
    FI(0x1B8) = 1;
    FI(0x1B4) = 1;
    FI(0x1B0) = *(int *)(v1 + 0x0);
    f24 = *(float *)(S + 0x110);
    f23 = -*(float *)(v1 + 0x594);
    *(volatile int *)&FI(0x30) = (int)arg0;
    FI(0x1C0) = 0;
    f22 = *(float *)(S + 0x138);
    FF(0x34) = -*(float *)(S + 0x130);
    s7 = *(int *)(v1 + 0x564);
    f21 = *(float *)(S + 0x114);
    s6 = *(int *)(v1 + 0x554);
    do { func_00260568(FP(0), za, 0x10); } while (0);
    bx = (char *)*(int *)&work[7];

    {
        char *sub;
        if (*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x178) == 0) {
            s7 = 0;
            s6 = 0;
        }
        if (s7 == 0 && s6 == 0) {
            f22 = D_0062D9D8;
        }
        sub = *(char **)((char *)FI(0x30) + 0x15C);
        if (*(int *)(sub + 0x558) == 0) {
            f21 = D_0062D9D8;
        }
        {
            int a1v = FI(0x1B4);
            if ((int)((unsigned long long)*(long long *)(env + 0x18) >> 0x2F) & 1) {
                a1v = 0;
            }
            FI(0x1B4) = a1v;
        }
        if (func_00149D00(2) < *(float *)(sub + 0x550)) {
            FI(0x1B4) = 0;
            FI(0x1B8) = 0;
        }
    }
    GetHeightOfWallFromGObj(FP(0), (void *)FI(0x30));
    FI(0x1C4) = (int)FP(0x10);
    GetRootMatrixByDObj(FP(0x10), (void *)FI(0x30));
    func_001443B8(FP(0x20), (void *)FI(0x30), 0x2C);
    {
        char *sub = *(char **)((char *)*(volatile int *)&FI(0x30) + 0x15C);
        *(EnvCopy32 *)((char *)arg4 + 0x170) = *(EnvCopy32 *)(sub + 0x170);
    }
    {
        long long ll18 = *(long long *)(env + 0x18);
        ll18 &= 0xFFFFFF7FFFFFFFFFLL;
        ll18 &= 0xFFFFFEFFFFFFFFFFLL;
        ll18 &= 0xDFFFFFFFFFFFFFFFLL;
        *(long long *)(env + 0x18) = ll18;
    }
    if ((int)(((long long)(*(long long *)(env + 0x20) << 0x1E)) >> 0x20) & 1) {
        f25 = 100.0f;
        FI(0x1BC) = 0;
    } else {
        f25 = 300.0f;
        FI(0x1BC) = 1;
    }
    if ((FI(0x30) ^ D_00629DE8) == 0) FI(0x1BC) = 0;
    f20 = D_00629730;
    found = isysGObjSearchFromObjLayoutID(0x2B, FI(0x1BC));
    {
        char *cage = (char *)FP(0x40);
        goto L650;
L648:
        found = isysGObjSearchFromObjKindID_begin(found);
L650:
        if (found == 0) goto L6B4;
        if (*(int *)((char *)found + 0x16C) == 0) goto L648;
        CageFixDL(cage, FP(0x50), found);
        {
            int cp = ContinueCorrectPosition((void *)FI(0x30));
            if (!(RotateAccordingToStick_PatternThree(cp, cage) < f20)) goto L648;
        }
    }
    if (!(FF(0x54) > FF(0x14))) goto L648;
    FI(0x1C0) = (int)found;
    *(int *)((char *)arg4 + 0x160) = (int)found;
L6B4:
    if (FI(0x1C0) != 0) {
        float d;
        eBrainProcess((void *)FI(0x30), FP(0x60));
        w70 = (char *)FP(0x70);
        g90 = w70;
        t80v = (char *)FP(0x80);
        CageFixDL(g90, t80v, (void *)FI(0x1C0));
        if (FF(0x74) + 50.0f < FF(0x64)) {
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
        debug_Marker(FP(0x80), 0, 0xFF, 0, f20);
        debug_Marker(g90, 0, 0, 0xFF, f20);
    }
    if (s6 != 0) {
        if (EnableMotionOrientUpdate(FI(0x30), 0x300) ||
            EnableMotionOrientUpdate(FI(0x30), 0x500) ||
            EnableMotionOrientUpdate(FI(0x30), 0x600)) {
            f23 = D_0062D9D8;
            FF(0x34) = f23;
        }
    }
    {
        char *g = (char *)FI(0x30);
        char *sub = *(char **)(g + 0x15C);
        if (*(int *)(sub + 0x558) != 0) {
            if (DisableMotionOrientUpdate((int)g, 0x300) ||
                DisableMotionOrientUpdate(FI(0x30), 0x500) ||
                DisableMotionOrientUpdate(FI(0x30), 0x600)) {
                f21 = D_0062D9D8;
            }
        }
    }
    if (s7 != 0 || s6 != 0) {
        char *sub = *(char **)((char *)FI(0x30) + 0x15C);
        if (*(int *)(sub + 0x178) != 0) {
            int f17, f18;
            int ret;
            fzMagnitudefv(arg4, *(int *)(sub + 0x178), sub + 0x170);
            *(float *)((char *)arg4 + 0xC) = 1.0f;
            if (s6 != 0) {
                f17 = 1;
                f18 = 1;
                if (ACTEnvGetTest() != 0) {
                    int gv = FI(0x30);
                    f18 = 0;
                    if (gv ^ (int)D_00629DE4) f18 = f17;
                    if ((gv ^ D_00629DE8) == 0) f17 = 0;
                }
                func_001443B8(FP(0x60), (void *)FI(0x30), 0x2C);
                ret = EnvCamAngle(FP(0x60), arg4, FP(0x70), -1.0f);
                if (f18 != 0 && ret >= 0x1F) {
                    *(int *)arg3 |= 0x10;
                }
                if (f17 != 0 && ret < -0x1E) {
                    *(int *)arg3 |= 0x8;
                }
            }
            if (s7 != 0 && f22 < f25) {
                int a;
                a = __builtin_abs(EnvCamAngle(boy, arg4, FP(0x70), -1.0f));
                *(long long *)(env + 0x18) |= 0x0004000000000000LL;
                if (f22 < 60.0f) {
                    if (a < 0x1E) {
                        *(long long *)(env + 0x18) |= 0x0002000000000000LL;
                    }
                }
            }
        }
    }
    if (s6 == 0) {
        char *sub = *(char **)((char *)FI(0x30) + 0x15C);
        if (*(int *)(sub + 0x56C) != 0) {
            if (*(float *)(sub + 0x5D4) < 100.0f) {
                int a;
                a = __builtin_abs(EnvCamAngle(boy, sub + 0x5C0, FP(0x60), -1.0f));
                if (a < 0x28) {
                    long long b18 = *(long long *)(env + 0x18);
                    b18 |= 0x8000LL << 24;
                    b18 |= 0x8000LL << 25;
                    *(long long *)(env + 0x18) = b18;
                }
            }
        }
    }
    if (f22 != D_0062D9D8 && s6 != 0 && FI(0x1B4) != 0) {
        void *st;
        int aang;
        int mv;
        int s18;
        int b1, b2, b3, b6, b6b;
        MotionEntry *mo;
        float t;

        st = subCommonIdle((void *)FI(0x30));
        aang = __builtin_abs(EnvCamAngle(st, arg4, FP(0x60), -1.0f));
        *(int *)((char *)arg4 + 0x130) = *(int *)(*(char **)((char *)arg4 + 0x178) + 0x48);
        s6 = (unsigned char)EnableMotionOrientUpdate(FI(0x30), 0x1000);
        *(int *)((char *)arg4 + 0x13C) = (int)box;
        *(int *)arg3 |= 1;
        if (FF(0x34) < f23) {
            if (FF(0x34) != D_0062D9DC) FF(0x34) = f23;
        }
        if (f22 < f25) {
            t = FF(0x34);
            if (t < 0.0f) t = D_0062D9D8;
            if (t >= 40.0f) {
                *(long long *)(env + 0x18) |= 0x8000LL << 35;
            }
        }
        if (f22 < 300.0f) {
            t = FF(0x34);
            if (t < 0.0f) t = D_0062D9D8;
            if (t <= 250.0f) {
                *(int *)arg3 |= 2;
            }
        }
        if ((char *)FI(0x30) == (char *)D_00629DE8) {
            if (f22 < 300.0f) {
                if (*(int *)(boxp + 0xC) == 0x11) {
                    if (ExecBoxMoveEndReaction(box) == 7) {
                        int a;
                        a = __builtin_abs(EnvCamAngle(boy, arg4, FP(0x60), -1.0f));
                        if (a < 0x2D) {
                            a = __builtin_abs(EnvCamAngleP(&FI(0x1A8), arg4, FP(0x60), -1.0f));
                            if (a < 0x2D) {
                                if (func_00191D90(boy, (void *)FI(0x1A8)) < 0x2D) {
                                    ((union LLAlias *)(env + 0x20))->ll |= 0x8000;
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            char *gb = (char *)FI(0x30);
            if (gb != (char *)D_00629DE8) goto LmvB0;
            mv = 0;
            goto LmvB1;
        LmvB0:
            mv = ForMotionViewer_GetCurrentMotion((int)gb, 0xB000);
        LmvB1:;
        }
        {
            int m2;
            char *gb = (char *)FI(0x30);
            if (mv != 0) goto LmvEskip;
            if (gb != (char *)D_00629DE8) goto LmvE0;
            m2 = 0;
            goto LmvE1;
        LmvE0:
            m2 = ForMotionViewer_GetCurrentMotion((int)gb, 0xE000);
        LmvE1:
            mv = m2;
            if (mv == 0) {
                mv = ForMotionViewer_GetCurrentMotion(FI(0x30), 0xC000);
                {
                    int m4;
                    char *gb2 = (char *)FI(0x30);
                    if (mv != 0) goto LmvDskip;
                    if (gb2 != (char *)D_00629DE8) goto LmvD0;
                    m4 = 0;
                    goto LmvD1;
                LmvD0:
                    m4 = ForMotionViewer_GetCurrentMotion((int)gb2, 0xD000);
                LmvD1:
                    mv = m4;
                    if (mv == 0) {
                        mv = (D_00629C90 == 4) ? EnableMotionOrientUpdate(FI(0x30), 0x1000)
                             : ForMotionViewer_GetCurrentMotion(FI(0x30), 0x1000);
                        mv &= 0xFF;
                        if (mv == 0) {
                            mv = ForMotionViewer_GetCurrentMotion(FI(0x30), 0x3000);
                        }
                    }
                LmvDskip:;
                }
            }
        LmvEskip:;
        }
        if (mv != 0) {
            FF(0x34) = f23;
        }
        {
            if ((char *)FI(0x30) == (char *)D_00629DE8) {
            if (EnableMotionOrientUpdate(FI(0x30), 0x7000)) {
                f23 = D_0062D9D8;
                FF(0x34) = f23;
                if (ACTEnvGetTest()) {
                    char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                    char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                    if (*(float *)(p2 + 4) + 50.0f < *(float *)(p1 + 4)) {
                        func_00240038(FP(0x60), arg4, -1.0f);
                        g90 = (char *)FP(0x90);
                        _OrientGV(g90, FP(0x60));
                        {
                            w70 = (char *)FP(0x70);
                            {
                                char *r1 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                                char *r2 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                                func_00240008(w70, r1, r2);
                            }
                            FI(0x7C) = 0;
                            func_0023FDD8(FP(0x80), g90, w70);
                        }
                        if (f22 < FF(0x88)) {
                            *(long long *)(env + 0x20) |= 0x20;
                        }
                    }
                }
            }
        }
        }
        {
            char *gb = (char *)*(volatile int *)&FI(0x30);
            *(float *)(env + 0x170) = FF(0x34);
            *(int *)(env + 0x174) = *(int *)(*(char **)(gb + 0x15C) + 0x5E4);
            if (f22 < 40.0f) {
                *(long long *)(env + 0x18) |= 0x8000LL << 24;
                if (func_00191D90(subCommonIdle(gb), arg4) >= 0x88) {
                    *(long long *)(env + 0x18) |= 0x8000LL << 25;
                }
            }
        }
        b6 = 0;
        if (FF(0x34) > 90.0f && FF(0x34) < 110.0f) b6 = (s6 == 0);
        if (FF(0x34) > 190.0f && FF(0x34) < 210.0f) s18 = 1;
        mo = &D_0055DA10[*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x490)];
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
            func_00240038(FP(0x60), arg4, f22);
            func_0023FFF0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x750,
                          (void *)FI(0x1C4), FP(0x60));
            func_00240038(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x760,
                          arg4, -1.0f);
            q = *(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678);
            *(int *)(q + 0x774) = 0x14;
            *(float *)(q + 0x770) = 40.0f;
            *(int *)(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x778) = 1;
            *(int *)arg3 |= 0x40000000;
        }
        if ((char *)FI(0x30) == (char *)D_00629DE8) {
            if (func_00149CA0((void *)FI(0x30), 0x1A)) {
                char *p1;
                char *p2;
                p1 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                p2 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                func_00240008(FP(0x60), p1, p2);
                FI(0x64) = 0;
                if (func_0023FE70(FP(0x60), subCommonIdle((void *)D_00629DE4)) < 100.0f) {
                    int v5 = 0;
                    if (*(int *)(boxp + 0xC) == 0x11) {
                        int q2 = *(int *)(*(char **)((char *)D_00629DE4 + 0x15C) + 0x0);
                        if (q2 != 0) {
                            q2 ^= (int)box;
                            v5 = (q2 != 0);
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
        b3 = (FF(0x34) > 150.0f && FF(0x34) < 250.0f);
        {
            int t3 = 0;
            if (s6 == 0) t3 = b3;
            if ((FI(0x30) ^ (int)D_00629DE4) != 0) b3 = t3;
        }
        if (f22 < f20 && s18 != 0) {
            long long ll;
            if (b1) {
                if (EnableMotionOrientUpdate(FI(0x30), 0xA00)) {
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
            ll = *(long long *)(env + 0x470);
            if (ll & 0x7800) {
                if ((int)(ll << 19 >> 32) & 1 && *(int *)((char *)FI(0x30) + 0xC) == 4) {
                    EnvPushPlane(FV(0x70), FV(0x80), (void *)FI(0x30), env, arg4, -20.0f, f22);
                } else {
                    EnvPushPlane(FV(0x70), FV(0x80), (void *)FI(0x30), env, arg4, 5.0f, f22);
                }
            }
            if (FF(0x34) > 80.0f && FF(0x34) < 180.0f) {
                if (*(int *)(boxp + 0xC) == 0x11) {
                    *(int *)((char *)arg3 + 4) |= 0x10000;
                } else {
                    *(int *)((char *)arg3 + 4) |= 0x8000;
                }
            }
            if (EnableMotionOrientUpdate(FI(0x30), 0x2000)) {
                if (f23 > 80.0f && f23 < 180.0f) {
                    *(int *)((char *)arg3 + 4) |= 2;
                }
            }
        }
        if (f22 < 50.0f) {
            int stt;
            int i;
            char *w;
            char *anch;
            char *dst;
            stt = *(int *)(box + 0xC);
            if (stt == 0x10) {
                char *m6;
                float fr = 10.0f;
                if ((char *)FI(0x30) == (char *)D_00629DE4) fr = 30.0f;
                m6 = *(char **)((char *)FI(0x30) + 0x164);
                ((union LLAlias *)FP(0x70))->ll = *(long long *)&D_006138D0[0];
                ((union LLAlias *)FP(0x78))->ll = *(long long *)&D_006138D0[8];
                *(float *)(m6 + 0x550) = *(float *)(m6 + 0x4A0);
                *(float *)(m6 + 0x554) = *(float *)(m6 + 0x4A4);
                *(float *)(m6 + 0x558) = *(float *)(m6 + 0x4A8);
                if ((char *)FI(0x30) == (char *)D_00629DE4) FF(0x70) = -FF(0x70);
                FF(0x7C) = 1.0f;
                func_0023FDD8(m6 + 0x5A0,
                              (void *)*(int *)(*(char **)(box + 0x15C) + 0xC),
                              FP(0x70));
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
                if (EnableMotionOrientUpdate(FI(0x30), 0xB00) == 0) {
                    *(int *)((char *)arg3 + 4) |= 0x40000000;
                    *(int *)((char *)arg4 + 0x140) = (int)box;
                    if (GetBoxGlobalHoldPoint(box)) {
                        if (moveBoxAutoMatic(FP(0x70), box, (void *)FI(0x30))) {
                            *(int *)((char *)arg3 + 4) |= 0x20000000;
                            *(int *)((char *)arg4 + 0x144) = (int)box;
                            stt = *(int *)(box + 0xC);
                        } else {
                            stt = *(int *)(box + 0xC);
                        }
                    } else {
                        stt = *(int *)(box + 0xC);
                    }
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x12) {
                if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0x700)) {
                    *(int *)((char *)arg3 + 4) |= 0x80000000;
                    *(int *)((char *)arg4 + 0x148) = (int)box;
                    stt = *(int *)(box + 0xC);
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x17) {
                if (EnableMotionOrientUpdate(FI(0x30), 0x500)) {
                    *(int *)((char *)arg3 + 8) |= 1;
                    *(int *)((char *)arg4 + 0x150) = FI(0x1B0);
                    *(int *)((char *)arg4 + 0x14C) = (int)box;
                    EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 5.0f);
                    stt = *(int *)(box + 0xC);
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x16) {
                if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0x500)) {
                    if (InitWallLeverGeo(box)) {
                        *(int *)((char *)arg3 + 8) |= 2;
                        *(int *)((char *)arg4 + 0x14C) = (int)box;
                        EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 5.0f);
                        stt = *(int *)(box + 0xC);
                    } else {
                        stt = *(int *)(box + 0xC);
                    }
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x18) {
                if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0x600)) {
                    if (func_001BDF68(box)) {
                        *(int *)((char *)arg3 + 8) |= 4;
                        *(int *)((char *)arg4 + 0x14C) = (int)box;
                        EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 30.0f);
                        stt = *(int *)(box + 0xC);
                    } else {
                        stt = *(int *)(box + 0xC);
                    }
                } else {
                    stt = *(int *)(box + 0xC);
                }
            }
            if (stt == 0x19) {
                if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0x600)) {
                    if (func_001BDF68(box)) {
                        *(int *)((char *)arg3 + 8) |= 8;
                        *(int *)((char *)arg4 + 0x14C) = (int)box;
                        EnvWallAssistVec(FV(0x80), FV(0x70), (void *)FI(0x30), (char *)arg4 + 0xF0, 30.0f);
                    }
                }
            }
        }
        if (f22 < 40.0f) {
            if (EnableMotionOrientUpdate(FI(0x30), 0x400)) {
                char *dstc = (char *)arg4 + 0xC0;
                float *res = FV(0x70);
                ((union IFAlias *)((char *)arg3 + 8))->i |= 0x8000;
                *(float *)((char *)arg4 + 0xA0) = *(float *)((char *)arg4 + 0x0);
                *(float *)((char *)arg4 + 0xA4) = *(float *)((char *)arg4 + 0x4);
                *(float *)((char *)arg4 + 0xA8) = *(float *)((char *)arg4 + 0x8);
                EnvPushAvg(FV(0x70), (void *)FI(0x30), dstc, 0x178);
                func_00240038(res, (float *)arg4, 30.0f);
                func_0023FFF0((float *)dstc, (float *)dstc, res);
                *(float *)((char *)arg4 + 0xCC) = 1.0f;
            }
            if (EnableMotionOrientUpdate(FI(0x30), 0xC000)) {
                *(int *)((char *)arg3 + 8) |= 0x400;
            }
        }
        {
            MotionEntry *mo2 = &D_0055DA10[*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x490)];
            int k = (*(int *)&mo2->u184 << 6) >> 30;
            float thr;
            switch (k) {
            case -1: {
                int r;
                if (D_00629C90 == 4) r = EnableMotionOrientUpdate(FI(0x30), 0x1000);
                else r = ForMotionViewer_GetCurrentMotion(FI(0x30), 0x1000);
                if (r & 0xFF) {
                    thr = 30.0f;
                } else {
                    {
                        char *mp = (char *)D_0055DA10;
                        mp -= -(*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x490) * 0x190);
                        thr = func_001920F0(aang, ((MotionEntry *)mp)->f17C + 2.0f);
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
                c130_170 = 0;
                if (FF(0x34) >= 130.0f && FF(0x34) < 170.0f) c130_170 = 1;
                c60_100 = 0;
                if (FF(0x34) > 60.0f && FF(0x34) < 100.0f) c60_100 = 1;
                c60_150 = 0;
                if (FF(0x34) > 60.0f && FF(0x34) < 150.0f) c60_150 = 1;
                c60_230 = 0;
                if (FF(0x34) > 60.0f && FF(0x34) < 230.0f) c60_230 = 1;
                if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0xB000)) {
                    *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x100) | (c60_150 << 8);
                } else if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0xE000)) {
                    *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x200) | (c60_150 << 9);
                } else if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0xD000)) {
                    *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x1000) | (c60_150 << 12);
                } else {
                    int r2;
                    if (D_00629C90 == 4) r2 = EnableMotionOrientUpdate(FI(0x30), 0x1000);
                    else r2 = ForMotionViewer_GetCurrentMotion(FI(0x30), 0x1000);
                    if (r2 & 0xFF) {
                        int v = (*(int *)((char *)arg3 + 8) & ~0x2000) | (c60_150 << 13);
                        *(int *)((char *)arg3 + 8) = v;
                        if (((unsigned int)v >> 13) & 1) {
                            char *S16 = (char *)FI(0x30);
                            char *env2 = *(char **)(S16 + 0x164);
                            float ang = FF(0x34);
                            int c2;
                            if (S16 == (char *)D_00629DE4 &&
                                ((((MotionEntry *)((char *)D_005EBC48 + D_00629C90 * 0x190))->u18C >> 2) & 1) &&
                                (unsigned int)(*(int *)(env2 + 0x30) - 4) < 2) {
                                c2 = EnvOrientProbe((char *)FP(0xD0), S16, ang);
                            } else {
                                c2 = 1;
                            }
                            if ((c2 & 0xFF) == 0) {
                                *(int *)((char *)arg3 + 8) &= ~0x2000;
                            }
                        }
                    } else if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0x3000)) {
                        *(int *)((char *)arg3 + 8) = (*(int *)((char *)arg3 + 8) & ~0x4000) | (c60_150 << 14);
                    } else if (*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x1D4) != 0) {
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
            a = __builtin_abs(EnvCamAngleP(&FI(0x1A8), arg4, FP(0x70), -1.0f));
            if (a < 0x28) {
                if ((char *)FI(0x30) == (char *)D_00629DE4 ||
                    (FF(0x34) > 130.0f && *(int *)(box + 0xC) != 0x10)) {
                    *(long long *)(env + 0x470) |= 0x8000LL << 43;
                }
            }
        }
        if ((int)(*(unsigned long long *)(env + 0x470) >> 58) & 1) {
            t = FF(0x34);
            if (t < 0.0f) t = D_0062D9D8;
            if (t > 65.0f) {
                if ((float)aang < 30.0f) {
                    *(long long *)(env + 0x468) |= 0x8000LL << 26;
                }
            }
        }
        if (f22 < 60.0f) {
            int c16 = 1;
            if (!((float)aang < 30.0f)) c16 = 0;
            if (*(int *)(box + 0xC) == 0x35) {
                if (QueenInqDead() == 0) {
                    *(long long *)(env + 0x468) |= 0x8000LL << 43;
                }
            } else {
                *(long long *)(env + 0x468) |= 0x8000LL << 42;
            }
            t = FF(0x34);
            if (t < 0.0f) t = D_0062D9D8;
            if (t > 230.0f) {
                if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0x400) == 0 &&
                    ForMotionViewer_GetCurrentMotion(FI(0x30), 0x8000) == 0) {
                    int stx = *(int *)(box + 0xC);
                    if (stx != 0x2B) {
                        if (stx != 0x35 && c16 != 0) {
                            if (ForMotionViewer_GetCurrentMotion(FI(0x30), 0xE000)) {
                                *(long long *)(env + 0x468) |= 0x8000LL << 44;
                            } else {
                                *(long long *)(env + 0x468) |= 0x8000LL << 45;
                            }
                        }
                    }
                }
            }
        }
        if (*(int *)((char *)FI(0x30) + 0xC) == 4) {
            if (*(int *)(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670) + 0x1DC) == 3) {
                if (f22 < 180.0f) {
                    if (*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x1D4) != 0) {
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
    if (f21 != D_0062D9D8 && *(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x558) != 0 &&
        FI(0x1B8) != 0) {
        void *st;
        int a;
        {
            char *c10 = (char *)arg4 + 0x10;
            FI(0x1C8) = (int)c10;
            FI(0x1DC) = (int)c10;
            CheckFieldContact(c10);
        }
        *(float *)((char *)arg4 + 0x1C) = 1.0f;
        st = subCommonIdle((void *)FI(0x30));
        a = __builtin_abs(EnvCamAngle(st, (void *)FI(0x1C8), FP(0x60), 1.0f));
        if (f21 < 20.0f) {
            if (!(a < 0x2E)) {
                if ((int)(*(long long *)(env + 0x20) << 14 >> 32) & 1) {
                    dispPlane((void *)FI(0x30), (void *)FI(0x1C8));
                    *(long long *)(env + 0x20) &= ~0x40000;
                }
            }
        }
        if (*(int *)(env + 0x30) == 0x29) {
            *(int *)((char *)arg3 + 4) |= 4;
        }
        if (f21 < f25 && f24 >= 40.0f) {
            *(long long *)(env + 0x18) |= 0x8000LL << 36;
        }
        if (f21 < 300.0f && f24 >= 100.0f) {
            ((union IFAlias *)arg3)->i |= 4;
            *(float *)((char *)arg4 + 0x138) = f21;
        }
        switch (*(unsigned int *)(env + 0x30)) {
        case 2:
            if (f21 < 20.0f && f24 > 180.0f) {
                if ((char *)FI(0x30) == (char *)D_00629DE4) {
                    if (f24 > 900.0f) {
                        *(int *)((char *)arg3 + 8) =
                            (*(int *)((char *)arg3 + 8) & 0xFEFFFFFF) | ((FI(0x1BC) & 1) << 24);
                    } else {
                        *(int *)((char *)arg3 + 8) =
                            (*(int *)((char *)arg3 + 8) & 0xFDFFFFFF) | ((FI(0x1BC) & 1) << 25);
                    }
                } else {
                    *(int *)((char *)arg3 + 8) =
                        (*(int *)((char *)arg3 + 8) & 0xFEFFFFFF) | ((FI(0x1BC) & 1) << 24);
                }
                {
                    char *e8;
                    if (f24 > 1000.0f) {
                        ((union IFAlias *)((char *)arg3 + 8))->i |= 0x800000;
                        e8 = (char *)FI(0x1A8);
                    } else {
                        e8 = (char *)FI(0x1A8);
                    }
                    g90 = (char *)FP(0x60);
                    {
                    float cy = ((union IFAlias *)(e8 + 4))->f;
                    float cz = ((union IFAlias *)(e8 + 8))->f;
                    float cx = ((union IFAlias *)(e8 + 0))->f;
                    FF(0x60) = cx;
                    FF(0x64) = cy;
                    FF(0x68) = cz;
                    }
                }
                func_00240038(g90, g90, f21);
                f20 = 5.0f;
                GetRootMatrixByDObj(FP(0x70), (void *)FI(0x30));
                func_0023FFF0((char *)arg4 + 0x40, FP(0x70), g90);
                if (f21 > f20) {
                    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0xF000)) {
                        if ((float)a > 20.0f) {
                            float k15 = 15.0f;
                            float v2 = ((k15 - f21) * f20) / k15;
                            char *p;
                            v2 = (v2 < 0.0f) ? 0.0f : ((v2 > f20) ? f20 : v2);
                            g90 = (char *)FP(0x90);
                            func_00240038(g90, (void *)FI(0x1C8), -v2);
                            {
                                t80v = (char *)FP(0x80);
                                p = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                func_0023FFF0((float *)t80v, p, g90);
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
                                vv &= 0xFEFFFFFF;
                                vv &= 0xFDFFFFFF;
                                ((union IFAlias *)((char *)arg3 + 0xC))->i |= 0x10;
                                ((union IFAlias *)((char *)arg3 + 8))->i = vv;
                            }
                        }
                    }
                }
            }
            break;
        case 0x70:
            if (f21 < 20.0f && f24 > 1000.0f) {
                *(int *)((char *)arg3 + 8) |= 0x400000;
            }
            break;
        case 1:
        case 0xF:
        case 0x2A:
            if (f21 < 40.0f && f24 > 1000.0f) {
                *(int *)((char *)arg3 + 8) |= 0x400000;
            }
            break;
        case 3:
            if (f21 < 40.0f && f24 > 1000.0f) {
                char *e8 = (char *)FI(0x1A8);
                g90 = (char *)FP(0x60);
                *(int *)((char *)arg3 + 8) =
                    ((*(int *)((char *)arg3 + 8) & 0xFEFFFFFF) | ((FI(0x1BC) & 1) << 24)) | 0x400000;
                {
                    float cy = ((union IFAlias *)(e8 + 4))->f;
                    float cz = ((union IFAlias *)(e8 + 8))->f;
                    float cx = ((union IFAlias *)(e8 + 0))->f;
                    FF(0x60) = cx;
                    FF(0x64) = cy;
                    FF(0x68) = cz;
                }
                func_00240038(g90, g90, f21 + 10.0f);
                f20 = 5.0f;
                GetRootMatrixByDObj(FP(0x70), (void *)FI(0x30));
                func_0023FFF0((char *)arg4 + 0x40, FP(0x70), g90);
                if (f21 > f20) {
                    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0xF000)) {
                        if ((float)a > 20.0f) {
                            float k25 = 25.0f;
                            float v2 = ((k25 - f21) * f20) / k25;
                            char *p;
                            v2 = (v2 < 0.0f) ? 0.0f : ((v2 > f20) ? f20 : v2);
                            g90 = (char *)FP(0x90);
                            func_00240038(g90, (void *)FI(0x1C8), -v2);
                            {
                                t80v = (char *)FP(0x80);
                                p = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                func_0023FFF0((float *)t80v, p, g90);
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
                                vv &= 0xFEFFFFFF;
                                vv &= 0xFFBFFFFF;
                                ((union IFAlias *)((char *)arg3 + 0xC))->i |= 0x10;
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
                    char *sub2 = *(char **)((char *)FI(0x30) + 0x15C);
                    { char *dd=(char*)arg4+0x190,*ss=sub2+0x170;
                      *(long long*)(dd+0)=*(long long*)(ss+0); *(long long*)(dd+8)=*(long long*)(ss+8);
                      *(long long*)(dd+16)=*(long long*)(ss+16); *(long long*)(dd+24)=*(long long*)(ss+24); }
                    *(int *)arg3 |= 0x400000;
                }
            }
        }
        if (f21 < 40.0f) {
            if (DisableMotionOrientUpdate(FI(0x30), 0x400)) {
                if (f24 > 60.0f) {
                    char *dstc;
                    *(float *)((char *)arg4 + 0xA0) = *(float *)((char *)arg4 + 0x10);
                    *(float *)((char *)arg4 + 0xA4) = *(float *)((char *)arg4 + 0x14);
                    *(float *)((char *)arg4 + 0xA8) = *(float *)((char *)arg4 + 0x18);
                    ((union IFAlias *)((char *)arg3 + 8))->i |= 0x10000;
                    if (f21 < 10.0f) {
                        int a2;
                        a2 = __builtin_abs(EnvCamAngle(FP(0x20), (void *)FI(0x1C8), FP(0x60), 1.0f));
                        if (a2 < 0x3C) {
                            *(int *)((char *)arg3 + 8) |= 0x20000;
                        }
                    }
                    dstc = (char *)arg4 + 0xC0;
                    EnvPushAvg(FV(0x60), (void *)FI(0x30), dstc, 0x188);
                    *(float *)((char *)arg4 + 0xCC) = 1.0f;
                }
            }
            if (DisableMotionOrientUpdate(FI(0x30), 0xC000)) {
                *(int *)((char *)arg3 + 8) |= 0x800;
            }
        }
        if (f21 < 25.0f) {
            if (FI(0x1BC) != 0) {
                if (f24 < 55.0f) {
                    *(long long *)(env + 0x470) |= 0x20000;
                } else if (f24 < 105.0f) {
                    *(long long *)(env + 0x470) |= 0x40000;
                } else if (f24 < 205.0f) {
                    *(long long *)(env + 0x470) |= 0x80000;
                }
            }
        }
        {
            int ccat;
            if ((char *)FI(0x30) == (char *)D_00629DE4 && (char *)D_00629DE8 != 0 &&
                *(int *)(*(char **)((char *)D_00629DE8 + 0x164) + 0x30) != 0x26 &&
                f21 < 200.0f && ACTEnvGetTest() == 0 &&
                DisableMotionOrientUpdate(FI(0x30), 0x7000) == 0 &&
                DisableMotionOrientUpdate(FI(0x30), 0x400) == 0) {
                do { FI(0x1CC) = 1; f23 = -EnableChangeRootUpdateMode((void *)D_00629DE4); } while (0);
                if (!(f21 < 60.0f)) {
                    FI(0x1CC) = 0;
                }
                FI(0x1D4) = (int)FP(0x60);
                ccat = 0;
                f22 = D_0062D9D8;
                GetRootMatrixByDObj(FP(0x60), (void *)D_00629DE4);
                FI(0x1D0) = 1;
                GetRootMatrixByDObj(FP(0x70), (void *)D_00629DE8);
                if (!(f24 < 55.0f)) {
                    if (f24 < 155.0f) {
                        f22 = 80.0f;
                        ccat = 0x64;
                    } else if (f24 < 255.0f) {
                        f22 = 160.0f;
                        ccat = 0xC8;
                    } else if (f24 < D_00629734) {
                        f22 = 160.0f;
                        ccat = 0x12C;
                    }
                }
                if ((char *)D_00629DE8 != 0 && (char *)D_00629DE4 != 0) {
                    char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                    char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                    if (*(float *)(p2 + 4) + 800.0f < *(float *)(p1 + 4)) {
                        FI(0x1D0) = 0;
                    }
                }
                if (D_00629C90 == 7) {
                    GetHeightOfWallFromGObj(FP(0x80), (void *)D_00629DE8);
                    if (ccat == 0xC8) {
                        if (!(FF(0x84) - FF(0x4) > 180.0f)) {
                            FI(0x1D0) = 0;
                        }
                        if (FF(0x0) * FF(0x80) < 0.0f) {
                            FI(0x1D0) = 0;
                        }
                    }
                }
                if ((int)(*(long long *)(*(char **)((char *)D_00629DE4 + 0x164) + 0x20) << 13 >> 32) & 1) {
                    if (FF(0x14) > 1600.0f) {
                        if ((ccat < 0xC8) == 0) ccat = 0;
                    }
                }
                FI(0x1D8) = (ccat < 0xC8);
                if (!(ccat < 0xC8)) {
                    char *fnd;
                    FF(0xA0) = FF(0x0);
                    FF(0xA4) = FF(0x4);
                    FF(0xA8) = FF(0x8);
                    g90 = (char *)FP(0x90);
                    func_00240038(g90, (void *)FI(0x1C8), f21 + 50.0f);
                    func_0023FFF0(FP(0xB0), FP(0xA0), g90);
                    FF(0xB4) = FF(0xB4) + f24;
                    _OrientGV(FP(0xC0), (void *)FI(0x1C8));
                    fnd = (char *)isysGObjSearchFromObjLayoutID(0x11);
                    while (fnd != 0) {
                        if (*(int *)(fnd + 0x16C) != 0 && ExecBoxMoveEndReaction(fnd) != 7) {
                            float d;
                            EnvGetPos((float *)FP(0x100), fnd);
                            if (RotateAccordingToStick_PatternThree((int)FP(0xB0), FP(0x100)) < D_00629738) {
                                d = FF(0xB4) - FF(0x104);
                                if (d < 0.0f) d = -d;
                                if (!(d > 100.0f)) {
                                    func_00240008(FP(0x110), (void *)FI(0x1C4), FP(0x100));
                                    ((union IFAlias *)&FI(0x11C))->i = 0;
                                    func_0023FDD8(FP(0x120), FP(0xC0), FP(0x110));
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
                if (ccat != 0 && f22 < f23) {
                    if (EnvSlotDist(FI(0x1D4), FV(0x70)) < D_0062973C &&
                        FI(0x1D0) != 0) {
                        char *q;
                        GetRootMatrixByDObj(FP(0x140), (void *)FI(0x30));
                        func_00240038(FP(0x130), (void *)FI(0x1C8), f21);
                        func_0023FFF0((char *)arg4 + 0x50, FP(0x140), FP(0x130));
                        GetRootMatrixByDObj(FP(0x160), (void *)FI(0x30));
                        func_00240038(FP(0x150), (void *)FI(0x1C8), f21 - 30.0f);
                        func_0023FFF0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x720,
                                      FP(0x160), FP(0x150));
                        {
                            char *gq = (char *)FI(0x30);
                            q = *(char **)(*(char **)(gq + 0x164) + 0x678);
                            *(float *)(q + 0x730) = *(float *)((char *)arg4 + 0x10);
                            *(int *)(q + 0x744) = 0x14;
                            *(float *)(q + 0x734) = *(float *)((char *)arg4 + 0x14);
                            *(float *)(q + 0x740) = 30.0f;
                            *(float *)(q + 0x738) = *(float *)((char *)arg4 + 0x18);
                            *(int *)(*(char **)(((union PFAlias *)(gq + 0x164))->p + 0x678) + 0x748) = 0;
                        }
                        ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 46;
                        if (FI(0x1CC) != 0) {
                            if (D_00629C90 == 0x62) {
                                char *fnd2 = (char *)isysGObjSearchFromObjLayoutID(0x11);
                                if (fnd2 != 0) {
                                    char *p1 = (char *)ContinueCorrectPosition(fnd2);
                                    char *p2 = (char *)ContinueCorrectPosition((void *)FI(0x30));
                                    if (RotateAccordingToStick_PatternThree((int)p1, p2) < D_00629740 &&
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
                                            func_00240038(FP(0x170), (void *)FI(0x1C8), -50.0f);
                                            ccat = 0xC8;
                                            func_0023FFF0((char *)arg4 + 0x50,
                                                          (void *)ContinueCorrectPosition(fnd2), FP(0x170));
                                        Lnofix:;
                                        }
                                    }
                                }
                            }
                            do { *(int *)((char *)arg4 + 0x134) = ccat; } while (0);
                            {
                            long long b470;
                            switch (ccat) {
                            case 0x64:
                                b470 = 0x8000LL << 47;
                            Lor470:
                                do { *(long long *)(env + 0x470) |= b470; } while (0);
                                break;
                            case 0xC8:
                                b470 = 0x8000LL << 48;
                                goto Lor470;
                            case 0x12C:
                                ((union LLAlias *)(env + 0x478))->ll |= 1;
                                break;
                            default:
                                func_001AAD00(D_006139D0, 0x917);
                                func_00260380(D_006139D0, 0x917, D_0062D9C8);
                                break;
                            }
                            }
                        }
                    }
                }
            }
            if ((char *)D_00629DE8 != 0 && (char *)FI(0x30) == (char *)D_00629DE4 &&
                f21 < 200.0f && f24 > 350.0f && ACTEnvGetTest() == 0) {
                char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                if (!(HandyCamera_TargetMoveType(p1, p2) < D_00629744)) {
                    if ((char *)D_00629DE8 != 0 && (char *)D_00629DE4 != 0) {
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                        if (*(float *)(p2 + 4) + 800.0f < *(float *)(p1 + 4)) goto Lchain;
                    }
                    if (*(int *)(*(char **)((char *)D_00629DE8 + 0x164) + 0x30) != 4) {
                        float lim2;
                        float rr;
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                        rr = RotateAccordingToStick_PatternThree((int)p1, p2);
                        lim2 = f21 + 100.0f;
                        if (rr < lim2 * lim2) goto Lchain;
                    }
                    {
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                        if (RotateAccordingToStick_PatternThree((int)p1, p2) < D_00629748) {
                            if (EnableChangeRootUpdateMode((void *)D_00629DE8, (void *)D_00629DE4) > 300.0f) {
                                goto Lchain;
                            }
                        }
                    }
                    {
                        char *p80 = (char *)FP(0x80);
                        char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE8);
                        char *p2 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                        func_00191FD0(p80, p1, p2);
                    if (func_00191D90(p80, (void *)FI(0x1C8)) < 0x50) {
                        int c16b;
                        int *pt = (int *)&FI(0x190);
                        int *pf = (int *)&FI(0x194);
                        int *pc = (int *)&FI(0x198);
                        FI(0x190) = (int)D_004C6EC0;
                        FI(0x194) = 0;
                        FI(0x198) = 0;
                        {
                            char *q1;
                            char *q2;
                            if ((char *)D_00629DE4 == 0) goto Lc0;
                            if ((char *)D_00629DE8 == 0) goto Lc0;
                            if (D_00629C90 != 8) goto Lc0;
                            q1 = *(char **)(*(char **)((char *)D_00629DE4 + 0x15C) + 0x0);
                            q2 = *(char **)(*(char **)((char *)D_00629DE8 + 0x15C) + 0x0);
                            if (q1 != 0 && *(int *)(q1 + 0xC) == 0x2B) { c16b = 1; goto Lcd; }
                            if (q2 == 0) goto Lc0;
                            if (*(int *)(q2 + 0xC) == 0x2B) { c16b = 2; goto Lcd; }
                        Lc0:
                            c16b = 0;
                        Lcd: ;
                        }
                        if (c16b != 0) {
                            char *p1 = (char *)ContinueCorrectPosition((void *)D_00629DE4);
                            if (D_0062974C < *(float *)(p1 + 4)) {
                                *pt = (int)D_004C6ED0;
                            } else {
                                if (c16b == 1) {
                                    *pt = (int)D_004C6EE0;
                                    {
                                        float t2 = D_004C6F00[2];
                                        float t1 = D_004C6F00[1];
                                        FF(0xB0) = D_004C6F00[0];
                                        FF(0xB4) = t1;
                                        FF(0xB8) = t2;
                                    }
                                    func_00191FD0(FP(0xC0), D_004C6F10);
                                    *pc = c16b;
                                } else {
                                    *pt = (int)D_004C6EF0;
                                    {
                                        float t2 = D_004C6F30[2];
                                        float t1 = D_004C6F30[1];
                                        FF(0xB0) = D_004C6F30[0];
                                        FF(0xB4) = t1;
                                        FF(0xB8) = t2;
                                    }
                                    func_00191FD0(FP(0xC0), D_004C6F20);
                                }
                                *pf = 1;
                            }
                        }
                        {
                            int idx;
                            g90 = (char *)FP(0x90);
                            for (idx = 0; 0.0f <= ((float *)FI(0x190))[idx]; idx++) {
                                if (func_001FA078(g90, FP(0x10), (void *)FI(0x1C8),
                                                  f21, ((float *)FI(0x190))[idx])) {
                                    func_00240038(FP(0xA0), (void *)FI(0x1DC), -1.0f);
                                    if (FI(0x194) != 0) {
                                        FF(0x90) = FF(0xB0);
                                        FF(0x94) = FF(0xB4);
                                        FF(0x98) = FF(0xB8);
                                        FF(0xA0) = FF(0xC0);
                                        FF(0xA4) = FF(0xC4);
                                        FF(0xA8) = FF(0xC8);
                                    }
                                    if (f21 < 60.0f) {
                                        *(unsigned char *)(env + 0x520) = *(unsigned char *)FP(0x198);
                                        *(float *)((char *)arg4 + 0x60) = FF(0x90);
                                        *(float *)((char *)arg4 + 0x64) = FF(0x94);
                                        *(float *)((char *)arg4 + 0x68) = FF(0x98);
                                        *(float *)((char *)arg4 + 0x70) = FF(0xA0);
                                        *(float *)((char *)arg4 + 0x74) = FF(0xA4);
                                        *(float *)((char *)arg4 + 0x78) = FF(0xA8);
                                        ((union LLAlias *)(env + 0x478))->ll |= 8;
                                    } else {
                                        char *q;
                                        func_00240038(FP(0xD0), (void *)FI(0x1DC), f21 - 30.0f);
                                        func_0023FFF0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x678) + 0x780,
                                                      FP(0x10), FP(0xD0));
                                        {
                                            char *gq2 = (char *)FI(0x30);
                                            q = *(char **)(*(char **)(gq2 + 0x164) + 0x678);
                                            *(float *)(q + 0x790) = *(float *)((char *)arg4 + 0x10);
                                            *(int *)(q + 0x7A4) = 0x14;
                                            *(float *)(q + 0x794) = *(float *)((char *)arg4 + 0x14);
                                            *(float *)(q + 0x7A0) = 30.0f;
                                            *(float *)(q + 0x798) = *(float *)((char *)arg4 + 0x18);
                                            *(int *)(*(char **)(((union PFAlias *)(gq2 + 0x164))->p + 0x678) + 0x7A8) = 0;
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
        if ((*(unsigned int *)((char *)arg3 + 8) >> 22) & 1) {
            if (f21 < 40.0f) goto Lchainbody;
            goto Lafter;
        }
        if (!(f21 < 30.0f)) goto Lafter;
    Lchainbody:
        {
            char *hit;
            char *fnd3;
            char *pp;
            char *p90;
            p90 = (char *)FP(0x90);
            hit = 0;
            FF(0x90) = *(float *)((char *)arg4 + 0x10);
            FF(0x94) = *(float *)((char *)arg4 + 0x14);
            FF(0x98) = *(float *)((char *)arg4 + 0x18);
            func_00191DB8(p90, D_00629750);
            fnd3 = (char *)isysGObjSearchFromObjLayoutID(0x15);
            if (fnd3 != 0) {
                float zero;
                float c70;
                float c100;
                float d20;
                f24 = D_00629754;
                zero = 0.0f;
                c70 = 70.0f;
                c100 = 100.0f;
                g90 = (char *)FP(0xB0);
                w70 = (char *)FP(0xA0);
            Lhead3:
                if (*(int *)(fnd3 + 0x16C) != 0) {
                    float d;
                    GetRootMatrixByDObj(g90, fnd3);
                    func_00240008(w70, g90, FP(0));
                    d20 = func_0023FE70(w70, p90);
                    if (RotateAccordingToStick_PatternThree((int)FP(0), g90) < f24) {
                        d = FF(0x4) - FF(0xB4);
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
                if (fnd3 != 0) goto Lhead3;
            Lgot3:;
            }
            {
                char *cnd = (char *)FI(0x1C0);
                if (cnd != 0) {
                t80v = (char *)FP(0xC0);
                pp = (char *)ContinueCorrectPosition(cnd);
                func_00240008(t80v, pp, (void *)FI(0x1C4));
                FI(0xC4) = 0;
                if (0.0f < func_0023FE70(t80v, (void *)FI(0x1C8))) {
                    hit = (char *)FI(0x1C0);
                }
                }
            }
            if (hit != 0) {
                ((union LLAlias *)(env + 0x470))->ll |= 0x8000LL << 38;
                *(int *)((char *)arg4 + 0x15C) = (int)hit;
                EnvGetPos((float *)FP(0xE0), hit);
                func_00240038(FP(0xD0), (void *)FI(0x1C8), -20.0f);
                func_0023FFF0(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670) + 0x1C0,
                              FP(0xE0), FP(0xD0));
                *(float *)(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670) + 0x1C4) = FF(0x14);
            }
        }
    Lafter:;
    }
    ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x200);
    if ((char *)FI(0x30) == (char *)D_00629DE8 && *(int *)(env + 0x30) == 0x45) {
        long long ll6;
        float e = -EnableChangeRootUpdateMode((void *)D_00629DE4, (void *)FI(0x30));
        ll6 = *(long long *)(env + 0x470);
        if ((int)(ll6 << 21 >> 32) & 1) {
            if (e > 5.0f) {
                long long t6 = ll6 | (0x8000LL << 46);
                *(long long *)(env + 0x470) = t6;
                ll6 = t6;
                *(long long *)(env + 0x478) |= 2;
            }
        }
        if ((int)(ll6 << 20 >> 32) & 1) {
            if (e > 60.0f) {
                if (*(int *)(*(char **)((char *)D_00629DE4 + 0x164) + 0x30) == 0x37) {
                    *(long long *)(env + 0x478) |= 4;
                }
            }
        }
        if ((int)(ll6 << 19 >> 32) & 1) {
            if (e > 195.0f) s6 = 1;
        }
    }
    if ((char *)D_00629DE8 != 0) {
        *(long long *)(env + 0x468) |= 0x8000LL << 30;
    }
    if (*(int *)(env + 0x160) != 0) {
        *(long long *)(env + 0x470) |= 0x8000LL << 22;
    }
    {
    char *me = (char *)*(volatile int *)&FI(0x30);
    if (me == (char *)*(void *volatile *)&D_00629DE4 &&
        *(int *)(env + 0x30) != 0xE) {
        char *w;
        if (*(int *)(env + 0x130) != 0) {
            w = (char *)WeaponHitEffect((void *)*(int *)(env + 0x130), 150.0f);
        } else {
            w = (char *)WeaponHitEffect(me, 150.0f);
        }
        if (w != 0) {
            char *pp;
            *(int *)((char *)arg4 + 0x158) = (int)w;
            ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 37;
            EnvGetPos((float *)FP(0x60), w);
            func_00191FD0(FP(0x70), FP(0x60), FP(0x10));
            if ((func_00191D90(FP(0x70), (void *)FI(0x1A8)) < 0x2D &&
                 RotateAccordingToStick_PatternThree((int)FP(0x60), FP(0x10)) < 6400.0f) ||
                (func_00191D90(FP(0x70), (void *)FI(0x1A8)) >= 0x2D &&
                 RotateAccordingToStick_PatternThree((int)FP(0x60), FP(0x10)) < 900.0f)) {
                ((union LLAlias *)(env + 0x468))->ll |= 0x8000LL << 36;
                *(int *)((char *)arg4 + 0x158) = (int)w;
            }
        }
    }
    }
    if ((unsigned int)*(int *)(env + 0x30) < 0x3B) {
        if ((unsigned int)*(int *)(env + 0x30) >= 0x39) {
            isStopChain((void *)*(int *)(env + 0x180), FP(0x19C), FP(0x1A0), FP(0x1A4));
            if (0.0f < FF(0x19C)) {
                *(long long *)(env + 0x470) |= 0x8000LL << 36;
            } else {
                *(long long *)(env + 0x470) |= 0x8000LL << 37;
            }
        }
    }
    if ((char *)FI(0x30) == (char *)D_00629DE4 && (char *)D_00629DE8 != 0) {
        char *me3 = (char *)*(volatile int *)&FI(0x30);
        if (*(int *)(*(char **)((char *)D_00629DE8 + 0x164) + 0x30) == 0x6B) {
            char *g = *(char **)(me3 + 0x124);
            if (*(int *)(*(char **)(g + 0x164) + 0x30) == 0x64) {
                if (GetDifferenceFromWallUpperPlane(g)) {
                    if (func_00143DE0((void *)FI(0x30), (void *)D_00629DE8, 0x78, FP(0x60),
                                      200.0f, 400.0f)) {
                        char *b;
                        char *pp;
                        b = (char *)PAIR_GetPosition_BOY((int)FP(0x10), 0x21);
                        pp = (char *)ContinueCorrectPosition(b);
                        if (RotateAccordingToStick_PatternThree((int)FP(0x10), pp) < D_00629758) {
                            do { *(long long *)(env + 0x468) |= 0x8000LL << 38; } while (0);
                            *(int *)(*(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670) + 0x2E0) = (int)b;
                        }
                    }
                }
            }
        }
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x800) ||
        ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x900)) {
        *(long long *)(env + 0x470) |= 0x100;
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x800000)) {
        char *q2;
        func_0023FE98(FP(0x60), *(char **)((char *)FI(0x30) + 0x15C) + 0x1C0);
        q2 = *(char **)(*(char **)((char *)FI(0x30) + 0x164) + 0x670);
        *(float *)(q2 + 0x270) = FF(0x60);
        *(float *)(q2 + 0x274) = FF(0x64);
        *(float *)(q2 + 0x278) = FF(0x68);
        if (0.0f < func_0023FE70(subCommonIdle((void *)FI(0x30)), FP(0x60))) {
            char *mc;
            do { mc = (char *)FI(0x30); *(long long *)(env + 0x470) |= 0x200; } while (0);
            *(char *)(*(char **)(*(char **)(mc + 0x164) + 0x670) + 0x280) = 0;
        } else {
            char *mc;
            int one;
            do { mc = (char *)FI(0x30); one = 1; *(long long *)(env + 0x470) |= 0x400; } while (0);
            *(char *)(*(char **)(*(char **)(mc + 0x164) + 0x670) + 0x280) = (char)one;
        }
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x40)) {
        *(long long *)(env + 0x470) |= 0x10;
        debug_assertMessage(D_0062D9D0);
    }
    if (ForMotionViewer_GetCurrentAnimationFrame(FI(0x30), 0x50)) {
        char *mc5;
        char *de4;
        do { mc5 = (char *)FI(0x30); de4 = (char *)D_00629DE4; *(long long *)(env + 0x470) |= 0x20; } while (0);
        {
            float *wp = (float *)(*(char **)(mc5 + 0x15C) + 0x634);
            float w = *wp;
            if (mc5 == de4 ? (w > 110.0f) : (w > 135.0f)) {
                *(long long *)(env + 0x470) |= 0x40;
                debug_assertMessage(D_006139E0);
            }
        }
        {
            float *wp = (float *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x634);
            if ((char *)FI(0x30) == (char *)D_00629DE4 ? (*wp < 105.0f) : (*wp < 130.0f)) {
                *(long long *)(env + 0x470) |= 0x80;
                debug_assertMessage(D_006139F0);
            }
        }
    }
    if ((char *)FI(0x30) == (char *)D_00629DE4) {
        char *t16;
        char *t30v = 0;
        char *t22v = 0;
        char *t23v = 0;
        float rad = 90.0f;
        {
            MotionEntry *mo3 = &D_0055DA10[*(int *)(*(char **)((char *)FI(0x30) + 0x15C) + 0x490)];
            if (mo3->u186 & 7) {
                rad = 100.0f;
            }
        }
        t16 = (char *)InitTorchGeo((void *)FI(0x30), 200.0f);
        if (t16 != 0) {
            w70 = (char *)FP(0x70);
            GetRootMatrixByDObj((g90 = w70), t16);
            if (RotateAccordingToStick_PatternThree((int)FP(0), w70) < rad * rad &&
                FF(0x74) < FF(0x4)) {
                if (func_00192040(w70, FP(0), subCommonIdle((void *)FI(0x30)), 0x2D)) {
                    float d = FF(0x74) - FF(0x4);
                    if (d < 0.0f) {
                        if (-d < 200.0f) goto Lct1;
                        goto Lskip_t1;
                    } else {
                        if (!(d < 200.0f)) goto Lskip_t1;
                    }
                Lct1:
                    if (FF(0x74) < FF(0x4)) {
                        t23v = t16;
                        func_00191FD0((char *)arg4 + 0x20, g90, FP(0));
                        t30v = t23v;
                    }
                Lskip_t1:;
                }
            }
        }
        t16 = (char *)LightTorchOn((void *)FI(0x30), 200.0f);
        if (t16 != 0) {
            int lit = 0;
            char *q1 = *(char **)(*(char **)(t16 + 0x15C) + 0x0);
            if (q1 != 0) {
                int k1 = *(int *)(q1 + 0xC);
                k1 ^= 0x13;
                lit = ((unsigned int)k1 < 1);
            }
            GetRootMatrixByDObj(FP(0x70), t16);
            if (lit == 0 &&
                RotateAccordingToStick_PatternThree((int)FP(0), FP(0x70)) < D_0062975C &&
                FF(0x74) < FF(0x4)) {
                if (func_00192040(FP(0x70), FP(0), subCommonIdle((void *)FI(0x30)), 0x2D)) {
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
                        func_00191FD0((char *)arg4 + 0x30, FP(0x70), FP(0));
                        *(int *)((char *)arg4 + 0x168) = (int)t22v;
                    }
                Lskip_t2:;
                }
            }
        }
        if (ACTGame_ConnectHand((void *)FI(0x30)) == 0) {
            char *r2 = (char *)ACTGameCollisionOff((void *)*(int *)(env + 0x130));
            if (r2 != 0) {
                if (TorchGeo(r2) == 0) {
                    if (t30v != 0) {
                        *(long long *)(env + 0x470) |= 0x4000000;
                    }
                } else {
                    if (t22v != 0) {
                        *(long long *)(env + 0x470) |= 0x10000000;
                    }
                }
            }
        }
        if (*(int *)(env + 0x160) != 0) {
            char *ln = (char *)_getLine((void *)*(int *)(env + 0x160));
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
            if (*(int *)(sub3 + 0x568) != 0 && *(float *)(sub3 + 0x5D0) < 50.0f) ok = 1;
            if (ok == 0) {
                *(long long *)(env + 0x470) |= 8;
            }
        }
    }
    if ((*(unsigned int *)((char *)arg3 + 4) >> 30) & 1) {
        char *g = (char *)*(volatile int *)&FI(0x30);
        char *q3 = *(char **)(*(char **)(g + 0x164) + 0x670);
        *(int *)(q3 + 0x2C4) = (int)box;
        moveBoxAutoMatic(q3 + 0x2D0, box, g);
    }
    return;
#undef FF
#undef FI
#undef FP
#undef v00
#undef v01
#undef v02
#undef m30
#undef v04
#undef v05
#undef v06
#undef v07
#undef v08
#undef v09
#undef v0A
#undef v0B
#undef v0C
#undef v0D
#undef v0E
#undef v0F
#undef v10
#undef v11
#undef v12
#undef v13
#undef v14
#undef v15
#undef v16
#undef v17
#undef work
}



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE0A8);

extern int *D_00629DE4;

extern char D_006138D0[];

/* parked: needs real matching (unaligned ld offset / struct shape).
 * See tough_nuts/func_001FE1D0/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE250);

extern int D_00629C90;
extern int EnableMotionOrientUpdate(int a0, int a1);
extern int ForMotionViewer_GetCurrentMotion(int a0, int a1);

int func_001FE2F8(int a0) {
    if (D_00629C90 == 4) {
        return (unsigned char)EnableMotionOrientUpdate(a0, 0x1000);
    }
    return (unsigned char)ForMotionViewer_GetCurrentMotion(a0, 0x1000);
}
