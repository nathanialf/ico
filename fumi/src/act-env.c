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
extern float fzMagnitudefv(void *a0, int a1, void *a2);
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

static inline float EnvSlotDist(int p, float *q) {
    return RotateAccordingToStick_PatternThree(p, q);
}




static inline int EnvPushPlane(float *tA, float *tB, void *Sv, char *env, void *a4v, float kf, float dist)
{
    float k;
    GetRootMatrixByDObj(tA, Sv);
    k = dist - kf;
    func_00240038(tB, (float *)a4v, -k);
    func_0023FFF0((float *)(env + 0x580), tA, tB);
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
    if (*(int *)(buf + 0x94) != 0) {
        if (ang + (*(float *)(buf + 0x24) - *(float *)(buf + 0x4)) < 250.0f) {
            return 0;
        }
        return 1;
    }
    return 1;
}

static inline int EnvPushAvg(float *acc, void *Sv, char *dstc, int woff)
{
    char *S = (char *)Sv;
    char *w;
    int i;
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    w = *(char **)(*(char **)(S + 0x15C) + woff);
    i = 3;
Lavg:
    func_0023FFF0(acc, acc, (float *)w);
    w += 0x10;
    i--;
    if (i >= 0) goto Lavg;
    func_00240038((float *)dstc, acc, 0.25f);
    return 0;
}

static inline void EnvHeadPushVec(float *acc, void *Sv, void *a4v)
{
    char *S = (char *)Sv;
    char *dstc = (char *)a4v + 0xC0;
    char *w;
    int i;
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    w = *(char **)(*(char **)(S + 0x15C) + 0x188);
    i = 3;
Lac6:
    func_0023FFF0(acc, acc, (float *)w);
    w += 0x10;
    i--;
    if (i >= 0) goto Lac6;
    func_00240038((float *)dstc, acc, 0.25f);
    *(float *)((char *)a4v + 0xCC) = 1.0f;
}

static inline int EnvWallAssistVec(float *acc, float *tmp, void *Sv, int *boxp, char *dst, float ascale)
{
    char *S = (char *)Sv;
    char *anch;
    char *w;
    int i;
    anch = *(char **)(S + 0x164) + 0x4A0;
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    w = *(char **)(*(char **)(S + 0x15C) + 0x178);
    i = 3;
Lacc:
    func_0023FFF0(acc, acc, (float *)w);
    w += 0x10;
    i--;
    if (i >= 0) goto Lacc;
    func_00240038((float *)dst, acc, 0.25f);
    if (*boxp != 0) {
        *(float *)(dst + 0xC) = 1.0f;
        func_0023FDD8(dst, (void *)*(int *)(*(char **)(*boxp + 0x15C) + 0xC), dst);
    }
    func_00240038(tmp, (float *)anch, ascale);
    func_0023FFF0((float *)dst, (float *)dst, tmp);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA3D0);


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
