#include "typedef.h"
#include "boyact.h"
#include "debug.h"
#include "gamesys.h"
#include "sceneManager.h"
#include "gobj.h"
#include "obj_manager.h"
#include "girl_act.h"
#include "brain.h"
#include "gflag.h"
#include "layout_action.h"
#include "frameDependSequence.h"
#include "torch.h"
#include <string.h>
#include "geometryManager.h"
#include "chain.h"
#include "act-game.h"
#include "motionOrientManager.h"
#include "motionFileManager.h"
#include "matrixDrive.h"
#include "debug_exception.h"
#include "layout_texture.h"
#include "motionManager.h"
#include "main.h"
#include "enemy_act.h"
#include <libvu0.h>
#include "cage.h"
#include "isys.h"
#include "way_sys.h"
#include "fuzio.h"
#include "pad.h"
#include "weapon.h"
#include "StageAnimation.h"
#include "attackhit.h"
#include "mail-add-data.h"
#include "camera-editor.h"
#include "quaternion.h"
#include "script.h"
#include "commonact.h"
#include "act.h"
#include "gv.h"
#include <assert.h>
#include "poly-flat.h"
#include "fieldCollision.h"
#include "motionManager2.h"
#include "box.h"
#include "include_asm.h"

typedef struct { /* field names derived */
    int a, b, c;
} S12; /* derived name */

/* One word of the boy's actor parameter block at gobj->x15C: the motion code
   writes these slots as float and the evaluator reads them as int, so the word
   itself is a union. */
typedef union BoyVal { /* field names derived */
    int i;
    float f;
} BoyVal; /* derived name */

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* the motion-def row of an actor's current motion */
#define CHAINROW(self) (GOBJ_SUB(self)->ctrl.motion + motionKind) /* derived name */

INCLUDE_ASM(findChainInJump);

/* dir: subBoyCollision passes the motion direction (sub + 0x120); this body
   never reads it */
static int CorrectOrient_RopeCliff(float *out, void *gobj, float *dir)
{
    float pos[4];
    float rpos[4];
    float orient[4];
    float climb[4];
    Act *sub = GOBJ_ACT(gobj);
    void *p;
    int r;
    int a;
    int b;
    float dy;

    switch (sub->actMode) {
    case 3:
        r = 0x78;
        break;
    case 2:
        r = 0x5A;
        break;
    default:
        return 0;
    }
    GetRootProjectionPosOfGObj(pos, gobj);
    p = isysGObjSearchFromObjKindID_begin(21);
    while (p != 0) {
        if (*(int *)((char *)p + 0x16C) != 0) {
            GetRootPosition(rpos, p);
            if (_DistxzSqGV(pos, rpos) < (float)(r * r)) {
                dy = pos[1] - rpos[1];
                if ((dy < 0.0f ? -dy : dy) < 70.0f) {
                    _OrientXZGV(orient, rpos, pos);
                    a = _AbsRotyGV((char *)sub + 0x120, orient);
                    GetChainClimbOrient(climb, p);
                    b = _AbsRotyGV((char *)sub + 0x120, climb);
                    if (a < 0x4B && b < 0x4B) {
                        out[0] = orient[0];
                        out[1] = orient[1];
                        out[2] = orient[2];
                        return 1;
                    }
                }
            }
        }
        p = isysGObjSearchFromObjKindID_next(p);
    }
    return 0;
}

/* The three climb headers (omori/include/b50climb.h, b100climb.h,
   b200climb.h) textually included here, as girl_act.c does with its own
   three: each defines the hand-off's after-routine and act-routine `inline`,
   which the compiler emits at the end of the file in boyact.h's order, and
   the mot-routine plainly, emitted in place.  Their strings come out here,
   in this order, at the head of the TU's .rodata. */
void motBoyHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motBoyHand50\n");
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x5C, isysCurrentGObj);
        }
        if (sub->readyFlags & 1) {
            break;
        }
        _ACTWait(1);
    }
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x5D, isysCurrentGObj);
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(45);
    sub->after = 0;
    while (1) {
        ACTSendMailCorrect(self, 0x47);
        _ACTWait(1);
    }
}

/* the shared "face the girl" prologue the b100climb.h / b200climb.h climb
   motions open with */
static inline void faceGirlFlat(void) /* derived name */
{
    float dir[4];
    void *boy = boyGObj;

    sceVu0SubVector(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));
    dir[1] = 0.0f;
    sceVu0Normalize(dir, dir);
    SetMotionDirection(boy, dir);
}

void motBoyHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int n;

    debug_StdPrintfDummy("enter motBoyHand100\n");
    faceGirlFlat();
    n = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;
    while (1) {
        if (0 < n) {
            n--;
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 0x61, isysCurrentGObj);
            }
            if ((sub->readyFlags & 1) == 0) {
                goto cont;
            }
            goto done;
        }
        break;
    cont:
        _ACTWait(1);
    }
    ACTSendMailCorrect(self, 0x65);
    debug_StdPrintfDummy("%s sync error\n", (void *)self == boyGObj ? "boy" : "girl");
done:
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
    sub->motReq = SetMotionRequest((void *)self, 0x65, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 0xA4, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x62, isysCurrentGObj);
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    sub->motReq = SetMotionRequest((void *)self, 0x65, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x64, isysCurrentGObj);
        }
        if (sub->readyFlags & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->after = 0;
    while (1) {
        ACTSendMailCorrect(self, 0x47);
        _ACTWait(1);
    }
}

void motBoyHand200(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int n;

    debug_StdPrintfDummy("enter motBoyHand200\n");
    faceGirlFlat();
    n = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;
    while (1) {
        if (0 < n) {
            n--;
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 0x66, isysCurrentGObj);
            }
            if ((sub->readyFlags & 1) == 0) {
                goto cont;
            }
            goto done;
        }
        break;
    cont:
        _ACTWait(1);
    }
    ACTSendMailCorrect(self, 0x6A);
    debug_StdPrintfDummy("%s sync error\n", (void *)self == boyGObj ? "boy" : "girl");
done:
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
    sub->motReq = SetMotionRequest((void *)self, 0x66, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    sub->motReq = SetMotionRequest((void *)self, 0x66, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 0xA4, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x67, isysCurrentGObj);
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    sub->motReq = SetMotionRequest((void *)self, 0x66, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x69, isysCurrentGObj);
        }
        if (sub->readyFlags & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->after = 0;
    while (1) {
        ACTSendMailCorrect(self, 0x47);
        _ACTWait(1);
    }
}

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* Each of the two height tests is one source line applying ABSF twice to the
   same height difference, so each re-evaluates the pair of test_CURRENTROOT
   calls.  The second test's body is empty in retail. */
#define BOYGIRL_DY()                                                                               \
    (test_CURRENTROOT(boyGObj)[1] - test_CURRENTROOT(girlGObj)[1]) /* derived name */
#define ABSF(x) ((x) < 0.0f ? -(x) : (x))                          /* derived name */

void handoff_heroin(void)
{
    void *boy = boyGObj;

    if (girlGObj != 0) {
        if (GOBJ_SUB(girlGObj)->root.hand0.mode == 6) {
            if (actModeTbl[GOBJ_ACT(boy)->actMode].bit7) {
            } else {
                iosOmSendMail(girlGObj, 0x3E, isysCurrentGObj);
            }
            ACTSendMailCorrect(boy, 0xFA);
        } else if (_DistxzGV(test_CURRENTROOT(boy), test_CURRENTROOT(girlGObj)) < 100.0f &&
                   ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {
            GetHeightOfFieldPlaneDifference(boyGObj, girlGObj);
        }
    }
    if (girlGObj != 0 && GOBJ_SUB(girlGObj)->root.hand0.mode != 6) {
        if (_DistxzGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 100.0f &&
            ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {}
    }
}

static float pinchBoyPos[4]; /* derived name */

static float pinchCameraPos[4]; /* derived name */

static float pinchBoyPosLate[4]; /* derived name */

typedef struct { /* field names derived */
    int a;
    int b;
} CharPos; /* derived name */

/* the wall hit actBoyStart hands the boy and the girl with mail 0x36: the
   ClipWall work record's wall pair and the wall it hit */
static WallCfg sofaWallHit; /* derived name */

static int attrWallHit[3]; /* derived name */

static long long boyInfo[12]; /* derived name */

static void CheckCollisionAttr(void *self)
{
    Sub15C *stage = GOBJ_SUB(self);
    int i;
    int flag = 1;
    int esc = 0;

    if (_ACTGame_GetParamF(2) < stage->ctrl.groundHeight) {
        return;
    }
    if (GOBJ_ACT(self)->actMode == 0x16) {
        return;
    }
    if (gameover_flag != 0) {
        return;
    }
    if (scpBoyControlReadDisable != 0) {
        return;
    }
    for (i = 1; i < 16; i++) {
        if (CheckFloorAttribute(self, i)) {
            int *w = (int *)boyInfo;

            flag = 0;
            if (w[4] < 0) {
                w[4] = i;
                return;
            }
            if (w[4] != i) {
                if (ACTGame_FLAG_TETSUNAGI()) {
                    esc = 1;
                } else if (girlGObj != 0) {
                    if (IsGirlStatusEscortEnable(stage_no, i)) {
                        esc = 1;
                    }
                }
                if (esc) {
                    boyInfo[1] |= 0x800000000LL;
                    RequestStageChange(i, boyGObj, girlGObj, 1.0f, 8.0f);
                } else {
                    RequestStageChange(i, boyGObj, 0, 1.0f, 8.0f);
                }
                itemWatchOff = 1;
            }
        }
    }
    if (flag) {
        ((int *)boyInfo)[4] = 0xFF;
    }
}

typedef struct { /* field names derived */
    int id;      /* 0x00 */
    float f04;
    float f08;
    unsigned char b0C; /* 0x0C */
    unsigned char b0D;
    unsigned char b0E;
    unsigned char b0F;
    float f10; /* 0x10 */
    char pad14[0x20 - 0x14];
    float f20[4]; /* 0x20 */
    float f30[4]; /* 0x30 */
} BgaEntry;       /* derived name */

typedef struct { /* field names derived */
    long long w[12];
} BoyWork; /* derived name */

typedef struct { /* field names derived */
    int w[8];
} BoyKidnapWork; /* derived name */

/* the private insert-camera record, 16-aligned as the programmer's other
   vector records (act-game.c Vec4S, way_sys.c WayClipWork) */
typedef struct {           /* field names derived */
    float pos[4];          /* 0x00, where the camera starts */
    float tgt[4];          /* 0x10, where it moves to */
    struct GObj *track;    /* 0x20, the object the return leg follows, or 0 for pos */
    int inFrames;          /* 0x24, frames of the move to tgt */
    int outFrames;         /* 0x28, frames of the return */
    float inRate;          /* 0x2C, the move's interpolation step */
    float blend;           /* 0x30, InsertCamera_SetDetail's blend */
    unsigned char control; /* 0x34, PrivInsCamChk_Control's answer */
    unsigned char pad35[3];
    int cnt;                               /* 0x38 */
    int on;                                /* 0x3C */
    float cur[4];                          /* 0x40 */
} __attribute__((aligned(16))) PrivInsCam; /* derived name */

static BoyWork boyInfoDefault = {{0, 0, 0xFFFFFFFF}}; /* derived name */

static BoyKidnapWork characterPacketDefault = {{0, 0, 0, 0, 0, -1, -1}}; /* derived name */

static BgaEntry boyBgaTable[] = {
    /* derived name */
    {476, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {477, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {481, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {482, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */

/* PrivInsCam's initial value: subBoyCollision copies it whole into
   privInsCam. */
static PrivInsCam privInsCamDefault = {
    /* derived name */
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0, 0, 0, 0.5f, 0.2f}; /* derived name */

/* boyact.o's two .data globals, the last two quadwords of its .data:
   test_rope_velo, which no code names, and add_rope_vec, the boy's orient
   snapshot SaveBoyOrientForScript writes. */
float test_rope_velo[4] = {0.0f, 0.0f, 0.0f, 0.0f};

float add_rope_vec[4] = {0.0f, 0.0f, 0.0f, 0.0f};

INCLUDE_ASM(UpdateGeo_48);

INCLUDE_ASM(BoyBgaManager);

static unsigned char girlLookStarted; /* derived name */

static unsigned char girlLookInScreen; /* derived name */

static unsigned char weaponLookStarted; /* derived name */

static unsigned char weaponLookInScreen; /* derived name */

static unsigned char girlEscortedInStage; /* derived name */

static unsigned char ableBoyControl; /* derived name */

static unsigned char startWithGirl; /* derived name */

static unsigned char startWaitCancel; /* derived name */

static unsigned char startOnSofa; /* derived name */

static unsigned char sitLayoutDone; /* derived name */

static int sitCount; /* derived name */

static void *beliftGirl; /* derived name */

static void E3_StageStartBoy(void *self)
{
    float buf[4];
    int w1;
    int w2;
    int w3;

    if (startWithGirl != 0) {
        sceVu0ScaleVector(buf, test_CURRENTORIENT(self), 100.0f);
        sceVu0AddVector(buf, buf, test_CURRENTROOT(self));
        SetDirectRootPositionNoFitting(self, buf);
    }
    if (gflagChk(381)) {
        gflagOff(381);
        return;
    }
    if (GetStageStartInfo(self, 0, 0, &w1, &w2, &w3) == 0) {
        return;
    }
    if (startOnSofa != 0) {
        return;
    }
    if (startWaitCancel != 0) {
        return;
    }
    _ACTWait(3);
    GetStageStartInfo(self, 0, 0, &w1, &w2, &w3);
    _ACTWait(w1);
    scpPlayStart(self);
    scpPlayMotReq(self, 8);
    _ACTWait(w2);
    scpPlayEnd(self);
    _ACTWait(w3);
}

extern int fptodp(float v);

INCLUDE_ASM(GetChainSlope);

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differ) */
extern int InsertCameraWorkingFlag;
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differ) */
extern int FixViewInGameCameraFlag;

/* An inline-only static that snapshots the boy's orient where the script
   side reads it, inlined into subBoyControl and subBoyCollision. */
static inline void SaveBoyOrientForScript(void) /* derived name */
{
    void *boy = boyGObj;

    add_rope_vec[0] = test_CURRENTORIENT(boy)[0];
    add_rope_vec[1] = test_CURRENTORIENT(boy)[1];
    add_rope_vec[2] = test_CURRENTORIENT(boy)[2];
}

/* the stick's angle from a direction, which CorrectStickInfo and
   subBoyControl inline */
static inline int correctStick(void *dir, IosPadStick *stick) /* derived name */
{
    float buf[4];

    ConvertStickToAbsCoord(buf, stick);
    return _RotyGV(buf, dir);
}

/* the private-camera gate */
static __inline__ unsigned char boyPrivInsCamInScreen(void) /* derived name */
{
    float scr[4];

    if (PrivInsCamChk_Control() == 0) {
        return 0;
    }
    if (0.0f < IsPointIsInScreen(scr, test_CURRENTROOT(boyGObj))) {
        return 1;
    }
    return 0;
}

/* the stick snap the boy's walk control applies when the camera-relative
   wish and the stick agree closely enough */
static __inline__ int snapStickToCamera(float *stick, float *wish, float *sabs,
                                        float *cam) /* derived name */
{
    int rc;
    int rs;
    int d;

    rc = _RotyGV(cam, wish);
    rs = _RotyGV(stick, sabs);
    if (sabs[0] == 0.0f && sabs[1] == 0.0f && sabs[2] == 0.0f) {
        return 0;
    }
    if (!((rc < 0 ? -rc : rc) < 20)) {
        return 0;
    }
    if ((rs < 0 ? -rs : rs) < 46) {
        return 0;
    }
    d = ((rs < 0 ? -rs : rs) > 90) ? 2 : 4;
    if (rs < 0) {
        d = -d;
    }
    if ((rs < 0 ? -rs : rs) < (d < 0 ? -d : d)) {
        d = rs;
    }
    stick[0] = sabs[0];
    stick[1] = sabs[1];
    stick[2] = sabs[2];
    _ApplyRyGV(stick, (float)d * 3.1415927f / 180.0f);
    return d;
}

int test_rope_slope = 0;

float add_rope_val = 0.0f;

void subBoyControl(GObj *volatile self);

INCLUDE_ASM(subBoyControl);

typedef struct {                      /* field names derived */
    int boyID;                        /* 0x00 */
    int girlID;                       /* 0x04 */
    unsigned long long layoutID : 32; /* 0x08 */
    /* the one-bit flags are declared no wider than short; torch is a
       short */
    unsigned char bit32 : 1;
    unsigned char fire : 1;
    unsigned short torch : 1;
    unsigned char escort : 1;
    char pad10[16];          /* 0x10 */
    void *weapon;            /* 0x20 */
    void *nextWeapon;        /* 0x24 */
    char pad28[0x30 - 0x28]; /* 0x28 */
    float f30;               /* 0x30 */
    float f34;
    float f38;
    char pad3C[4];
    float f40; /* 0x40 */
    float f44;
    float f48;
    char pad4C[4];
    CharPos f50; /* 0x50 */
} BoyInfo;       /* derived name */

#define BOYINFO (*(BoyInfo *)boyInfo) /* derived name */
/* BoyInfo's +0x50 record as the ef-stage return reads it: a flag byte and the
   camera target id at +4 (BoyInfoUpdate_StageChange copies it whole as f50). */
#define BOYEFSTAGE ((unsigned char *)boyInfo + 0x50) /* derived name */

static void InitSwapWeapon(void *self)
{
    Act *sub = GOBJ_ACT(self);
    GObj *info;
    char *p;
    GenGeo *row;

    if (BOYINFO.boyID != 0) {
        BOYINFO.weapon = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
    } else {
        BOYINFO.weapon = 0;
    }
    info = sub->env.swapWeapon;
    BOYINFO.nextWeapon = info;
    p = (char *)gamesysObjInfoGet(info->kind, info->labelId);
    if (p != 0) {
        BOYINFO.f30 = *(float *)(p + 0x10);
        BOYINFO.f34 = *(float *)(p + 0x14);
        BOYINFO.f38 = *(float *)(p + 0x18);
        BOYINFO.f40 = *(float *)(p + 0x20);
        BOYINFO.f44 = *(float *)(p + 0x24);
        BOYINFO.f48 = *(float *)(p + 0x28);
    } else {
        row = &objLayout[info->labelId];
        BOYINFO.f30 = -row->pos[0];
        BOYINFO.f34 = -row->pos[1];
        BOYINFO.f38 = -row->pos[2];
        BOYINFO.f40 = row->rot[0] * 3.1415927f / 180.0f;
        BOYINFO.f44 = row->rot[1] * 3.1415927f / 180.0f;
        BOYINFO.f48 = row->rot[2] * 3.1415927f / 180.0f;
    }
}

static void PutWeapon(void)
{
    char *p = (char *)boyInfo;

    if (*(void **)(p + 0x20) != 0) {
        InitMotionGeoInfo(&GOBJ_SUB(*(void **)(p + 0x20))->root, *(float *)(p + 0x30),
                          *(float *)(p + 0x34), *(float *)(p + 0x38), -*(float *)(p + 0x40),
                          -*(float *)(p + 0x44), -*(float *)(p + 0x48));
        if (CheckWeaponKind(*(void **)(p + 0x20)) == 9) {
            SetWeaponOffsetMode(*(void **)(p + 0x20), 1);
        }
        UpdateRootMatrix(*(void **)(p + 0x20));
    }
}

/* a static helper inlined into SetBoyWeaponGObj and afterBoyTakeWeapon */
static inline int SwapBoyWeapon(void *oldW, void *newW, void *boy) /* derived name */
{
    Act *sub = GOBJ_ACT(boy);

    if (oldW == newW) {
        return 0;
    }
    if (newW == 0) {
        debug_assert(__FILE__, 3007);
        __assert(__FILE__, 3007, "next");
        return 0;
    }
    PickupWeapon(newW, boy, 0x16);
    ((int *)boyInfo)[0] = *(int *)((char *)newW + 0x8);
    *(void **)((char *)sub + 0x150) = newW;
    SetWeaponOffsetMode(newW, 0);

    if (oldW == 0) {
        return 1;
    }
    ReleaseWeapon(oldW);
    PutWeapon();
    gamesysObjInfoPosSetStage(oldW, 0, 0, stage_no);
    debug_StdPrintfDummy("%d -> %d\n", *(int *)((char *)oldW + 0x8), *(int *)((char *)newW + 0x8));
    return 1;
}

/* returns float * here, int * in camera-root.h */
extern float *GetCurrentCameraSet2(void);

static void OtherStageGirlPinchCamera_After(float t)
{
    float buf[4];

    pinchBoyPos[0] = test_CURRENTROOT(boyGObj)[0];
    pinchBoyPos[1] = test_CURRENTROOT(boyGObj)[1];
    pinchBoyPos[2] = test_CURRENTROOT(boyGObj)[2];
    if (_ACTGame_GetParamF(0xE) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f <=
        t) {
        pinchBoyPosLate[0] = test_CURRENTROOT(boyGObj)[0];
        pinchBoyPosLate[1] = test_CURRENTROOT(boyGObj)[1];
        pinchBoyPosLate[2] = test_CURRENTROOT(boyGObj)[2];
        GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
        sceVu0ScaleVector(buf, buf, 500.0f);
        sceVu0AddVector(pinchCameraPos, GetCurrentCameraSet2(), buf);
    } else {
        PrivInsCamSet(test_CURRENTROOT(boyGObj), pinchCameraPos, boyGObj,
                      (60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60,
                      (60 - systemStatus[0] * 10) / systemStatus[1] * 45 / 60, 0.05f, 0.25f, 0);
        GOBJ_WORK(boyGObj)->pinchFrames = 0;
    }
}

INCLUDE_ASM(ACTDispLwsBoyStonize_InQueenStage);

static int characterPacket[8]; /* derived name */

static PrivInsCam privInsCam; /* derived name */

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetDetail(float *pos, float *tgt, int frames, int cutType, int zoom,
                                   int cutBack, float blend);

static void PrivInsCamProcess(void)
{
    float p[4];

    switch (privInsCam.on) {
    case 1:
        privInsCam.cur[0] = privInsCam.pos[0];
        privInsCam.cur[1] = privInsCam.pos[1];
        privInsCam.cur[2] = privInsCam.pos[2];
        privInsCam.cnt = privInsCam.inFrames;
        privInsCam.on = 2;
        break;
    case 2:
        _InterGV(privInsCam.cur, privInsCam.tgt, privInsCam.cur, 1.0f, privInsCam.inRate);
        InsertCamera_SetDetail(GetCurrentCameraSet2(), privInsCam.cur, 5, 1, 2, 0,
                               privInsCam.blend);
        if (--privInsCam.cnt <= 0) {
            privInsCam.on = 3;
        }
        break;
    case 3:
        privInsCam.tgt[0] = privInsCam.cur[0];
        privInsCam.tgt[1] = privInsCam.cur[1];
        privInsCam.tgt[2] = privInsCam.cur[2];
        privInsCam.cnt = privInsCam.outFrames;
        privInsCam.on = 4;
        break;
    case 4:
        if (privInsCam.track != 0) {
            p[0] = test_CURRENTROOT(privInsCam.track)[0];
            p[1] = test_CURRENTROOT(privInsCam.track)[1];
            p[2] = test_CURRENTROOT(privInsCam.track)[2];
        } else {
            p[0] = privInsCam.pos[0];
            p[1] = privInsCam.pos[1];
            p[2] = privInsCam.pos[2];
        }
        _InterGV(privInsCam.cur, p, privInsCam.tgt, (float)privInsCam.cnt,
                 (float)(privInsCam.outFrames - privInsCam.cnt));
        InsertCamera_SetDetail(GetCurrentCameraSet2(), privInsCam.cur, 2, 1, 0, 0,
                               privInsCam.blend);
        if (--privInsCam.cnt <= 0) {
            privInsCam.on = 0;
        }
        break;
    }
}

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void Camctrl_SetTarget(GObj *gobj, GObj *subGObj, int pri);

/* the object kinds the proximity scan below walks, terminated by -1 */
typedef struct { /* field names derived */
    int id[4];
} ObjKindList; /* derived name */

static const ObjKindList collisionKinds = {{4, 47, 62, -1}}; /* derived name */

/* reset the private insert camera to its initial value; only
   subBoyCollision calls it */
static inline void PrivInsCamInit(void) /* derived name */
{
    privInsCam = privInsCamDefault;
}

/* the nearest object of a kind in front of the actor, which ACTSearchGObj,
   subBoyCollision and actBoyAttack inline */
static inline void searchGObj(void *self, int kind, int maxDeg, int *out_id, float *out_vec,
                              float thresh) /* derived name */
{
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjKindID_begin(kind);
    best = maxDeg;
    *out_id = 0;
    for (; node != 0; node = isysGObjSearchFromObjKindID_next(node)) {
        if (*(int *)((char *)node + 0x16C) != 0) {
            float *r1 = test_CURRENTROOT(self);
            if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                int sign;
                int dist;
                float *r4 = test_CURRENTROOT(node);
                sceVu0SubVector(buf, r4, test_CURRENTROOT(self));
                sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(self));
                if (sign < 0) {
                    dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(self));
                } else {
                    dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(self));
                }
                if (dist < best) {
                    best = dist;
                    out_vec[0] = buf[0];
                    out_vec[1] = buf[1];
                    out_vec[2] = buf[2];
                    *out_id = (int)node;
                }
            }
        }
    }
}

/* the DEBUG build's report of subBoyCollision's camera state, built only
   under DEBUG */
static __inline__ void boyCamDebugDisp(int camOn, int looking) /* derived name */
{
#ifdef DEBUG
    scePrintf("boy camera on %d looking %d\n", camOn, looking);
#endif
}

void subBoyCollision(GObj *volatile self);

INCLUDE_ASM(subBoyCollision);

inline void afterBoySwim(GObj *volatile self);

/* the record Act+0x680 points at, with the fields actBoyBelift and actBoySwim
   touch: the lift level and the lifted object, then the floating-box flag, the
   box GObj and the grip point, a four-float vector sceVu0ApplyMatrix takes
   whole (its w set to 1 before the apply) */
typedef struct { /* field names derived */
    char pad0[204];
    int liftLevel; /* 0xCC, the lift level actBoyBelift sets to 10 and clamps */
    char padD0[348];
    void *liftObj; /* 0x22C, the object the boy lifts (actBoyBelift stores the girl) */
    char pad230[144];
    int holdBox; /* 0x2C0, set while the boy holds a floating box */
    GObj *box;   /* 0x2C4 */
    char pad2C8[8];
    float grip[4]; /* 0x2D0 */
} BoyExt;          /* derived name */

#define BOY_EXT(o) (*(BoyExt **)(*(char **)((char *)(o) + 0x164) + 0x680)) /* derived name */

/* GObj's 0x15C slot read through a union (typedef.h: an int handle the
   engine casts to a pointer) */
typedef union { /* field names derived */
    char *sub;
} GObjSubSlot; /* derived name */

#define GOBJ_SUBSLOT(o) (((GObjSubSlot *)((char *)(o) + 0x15C))->sub) /* derived name */

void actBoySwim(GObj *volatile self)
{
    float pos[4];
    Act *sub = GOBJ_ACT(self);
    int padReq = 0;

    BOY_EXT(self)->holdBox = 0;
    sub->after = (void *)afterBoySwim;
    while (1) {
        GObj *box = BOY_EXT(self)->box;

        if (sub->curMot == 0xAD) {
            sub->flags20.ll |= 0x800000000ULL;
        }
        if (BOY_EXT(self)->holdBox) {
            RequestChangeHandMode(self, 0, 3, 1, box, 0, BOY_EXT(self)->grip);
            BOY_EXT(self)->grip[3] = 1.0f;
            sceVu0ApplyMatrix(pos, *(void **)(GOBJ_SUBSLOT(box) + 0xC), BOY_EXT(self)->grip);
            debug_NMarker(pos, 0xFF, 0, 0, 100.0f);
            MoveFloatingBox(box, self,
                            *(char **)(GOBJ_SUBSLOT(self) + 0xC) +
                                GetSkeltonFocusNode(self, 0x13) * 0x40 + 0x30,
                            BOY_EXT(self)->grip, 30.0f);
            if (!(_DistSqGV(test_CURRENTROOT((void *)self), pos) < 4e+04f)) {
                BOY_EXT(self)->holdBox = 0;
            }
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1C0))->a = (int)box;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1C0))->b = -1;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1C0))->c = 0;
            if (!padReq) {
                iosPadActRequest(boyPad, 6);
                padReq = 1;
            }
            if ((int)(sub->flags20.ll >> 35) & 1) {
                if (*(int *)(GOBJ_SUBSLOT(self) + 0x4CC) || *(int *)(GOBJ_SUBSLOT(self) + 0x4C8)) {
                    iosPadActRequest(boyPad, 7);
                }
            }
        } else {
            RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
            padReq = 0;
            ((Sub15C *)GOBJ_SUBSLOT(self))->root.filter = InitialColInfo;
        }
        _ACTWait(1);
    }
}

void actBoyWalk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        if (ACTGame_FLAG_TETSUNAGI()) {
            float gp[4];
            float bp[4];
            float d;
            float ratio;

            GetSkeltonPosition(bp, boyGObj, 2);
            GetSkeltonPosition(gp, girlGObj, 0x12);
            d = _DistGV((float *)gp, (float *)bp);
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 < sub->modeFrame &&
                80.0f < d) {
                d = (d - 80.0f) / 10.0f;
                d = d < 0.0f ? 0.0f : (1.0f < d ? 1.0f : d);
                ratio = 0.9 - d * 0.2;
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)self, ratio, 2);
            }
        }
        _ACTWait(1);
    }
}

void actBoyRun(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        if (ACTGame_FLAG_TETSUNAGI()) {
            float gp[4];
            float bp[4];
            float d;
            float ratio;

            GetSkeltonPosition(bp, boyGObj, 2);
            GetSkeltonPosition(gp, girlGObj, 0x12);
            d = _DistGV((float *)gp, (float *)bp);
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 < sub->modeFrame &&
                90.0f < d) {
                d = (d - 90.0f) / 10.0f;
                d = d < 0.0f ? 0.0f : (1.0f < d ? 1.0f : d);
                ratio = 0.7 - d * 0.2;
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)self, ratio, 2);
            }
        }
        _ACTWait(1);
    }
}

/* the nearest enemy in front of the actor, which ACTSearchEnemy and
   actBoyAttack inline */
static inline void searchEnemy(void *self, int *out_id, float *out_vec) /* derived name */
{
    searchGObj(self, (*(int *)((char *)self + 0xC) ^ 1) ? 1 : 4, 0x5A, out_id, out_vec, 300.0f);
}

void actBoyAttack(GObj *volatile self)
{
    char *sub = (char *)GOBJ_ACT(self);
    int mot = *(int *)((char *)sub + 0x10);
    float vec[4];

    *(unsigned long long *)(sub + 0x20) |= 0x100000000ULL;
    *(int *)((char *)sub + 0x450) = mot;
    debug_StdPrintfDummy("attack sub id [%d]\n", mot);
    debug_StdPrintfDummy("enter actBoyAttack\n");
    _ACTWait(2);
    searchEnemy((void *)self, (int *)((char *)sub + 0x188), vec);
    while (1) {
        if (*(int *)((char *)sub + 0x188)) {
            if (ACTGame_NoWeapon(self)) {
                SetMotionDirectionWithLimit((void *)self, vec, 5.0f, 45.0f);
            } else {
                SetMotionDirectionWithLimit((void *)self, vec, 10.0f, 90.0f);
            }
        }
        ACTSendMailCorrect(self, 0xC7);
        BoyAttackCenter(self);
        _ACTWait(1);
    }
}

void actBoyTakeWeaponReady(GObj *volatile self)
{
    float w[4];
    float p[4];
    float dir[4];
    GObj *obj;
    int first = 1;
    int n = 0;

    obj = GOBJ_ACT(self)->env.swapWeapon;
    w[0] = test_CURRENTROOT(obj)[0];
    w[1] = test_CURRENTROOT(obj)[1];
    w[2] = test_CURRENTROOT(obj)[2];
    while (1) {
        p[0] = test_CURRENTROOT((void *)self)[0];
        p[1] = test_CURRENTROOT((void *)self)[1];
        p[2] = test_CURRENTROOT((void *)self)[2];
        _OrientXZGV(dir, w, p);
        if (first) {
            SetMotionDirection((void *)self, dir);
            first = 0;
        } else if (_AbsRotyGV(test_CURRENTORIENT((void *)self), dir) < 0x1E) {
            _ACTMotDirSmzDirect((void *)self, dir);
        } else {
            ACTSendMailCorrect(self, 0xCC);
        }
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 2 < n++) {
            ACTSendMailCorrect(self, 0xCC);
        }
        _ACTWait(1);
    }
}

/* sub->0x14 is the actor's "after" callback slot: actBoyTakeWeapon arms it with
   afterBoyTakeWeapon and calls it through the slot once the motion frame passes
   the swap point, so it is written and read as a function pointer. */
typedef void (*BoyAfterFunc)(GObj *volatile a0);

void actBoyTakeWeapon(GObj *volatile self)
{
    float p[4];
    float dir[4];
    Act *sub = GOBJ_ACT(self);
    int picked = 0;
    int put = 0;

    InitSwapWeapon((void *)self);
    *(BoyAfterFunc *)((char *)sub + 0x14) = afterBoyTakeWeapon;
    p[0] = test_CURRENTROOT(BOYINFO.nextWeapon)[0];
    p[1] = test_CURRENTROOT(BOYINFO.nextWeapon)[1];
    p[2] = test_CURRENTROOT(BOYINFO.nextWeapon)[2];
    _OrientXZGV(dir, p, test_CURRENTROOT((void *)self));
    SetMotionDirection((void *)self, dir);
    while (1) {
        if (GOBJ_SUB(self)->ctrl.motion == 0xE6) {
            if (15.0f < GOBJ_SUB(self)->ctrl.animFrame && GOBJ_SUB(self)->ctrl.animFrame < 48.0f &&
                !picked) {
                PickupWeapon(BOYINFO.nextWeapon, (void *)self, 6);
                picked = 1;
            }
            if (30.0f < GOBJ_SUB(self)->ctrl.animFrame && !put) {
                if (BOYINFO.weapon != 0) {
                    ReleaseWeapon(BOYINFO.weapon);
                    ExecuteSEPackage(BOYINFO.weapon, 0x50);
                }
                PutWeapon();
                put = 1;
            }
            if (48.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        } else {
            if (16.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        }
        ACTSendMailCorrect(self, 0xC7);
        _ACTWait(1);
    }
}

#define BOY_WALL(o) ((char *)GOBJ_ACT(o)->work) /* derived name */

INCLUDE_ASM(actBoyCliffHesitate);

#define BOY_GIRL_DY()                                                                              \
    (test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1]) /* derived name */

static void ACTSendMail_PULLUP_GO(void)
{
    GObj *g = boyGObj;
    Act *sub = GOBJ_ACT(g);

    switch (sub->env.cliffSel) {
    case 0x64:
        ACTSendMailCorrect(g, 0x4A);
        sub->orientMot = 0x6B;
        break;
    case 0xC8:
        ACTSendMailCorrect(g, 0x4A);
        sub->orientMot = 0x6D;
        break;
    case 0x12C:
        if (GOBJ_ACT(girlGObj)->actMode != 0x50) {
            break;
        }
        if (!(300.0f < (BOY_GIRL_DY() < 0.0f ? -BOY_GIRL_DY() : BOY_GIRL_DY()))) {
            ACTSendMailCorrect(g, 0x4A);
            sub->orientMot = 0x6F;
        } else if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x52, isysCurrentGObj);
        }
        break;
    }
}

/* the pull-up start mail, inlined into actBoyPullupGo */
static inline void ACTSendMail_PULLUP_START(void) /* derived name */
{
    Act *sub = GOBJ_ACT(boyGObj);

    switch (sub->env.cliffSel) {
    case 0x64:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 0x65;
        break;
    case 0xC8:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 0x66;
        break;
    case 0x12C:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 0x67;
        break;
    }
}

static int pullup_check_heroin_position(void)
{
    float buf[4];
    float p1[4];
    float p2[4];
    GObj *g = boyGObj;
    Act *s = GOBJ_ACT(g);

    if (girlControlMode != 0 && s->env.cliffSel == 300) {
        switch (GOBJ_ACT(girlGObj)->actMode) {
        case 4:
            GetSkeltonPosition(p1, girlGObj, 0x16);
            GetSkeltonPosition(p2, boyGObj, 6);
            if (_DistSqGV(p1, p2) < 3600.0f) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x59, isysCurrentGObj);
                }
            }
            return 0;
        case 0x51:
            ACTSendMailCorrect(boyGObj, 0x58);
            return 0;
        default:
            return 0;
        }
    }
    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, s->env.cliffOrient) &&
        _DistxzGV(s->env.cliffStepPos, test_CURRENTROOT(girlGObj)) < 100.0f &&
        ((unsigned int)(GOBJ_ACT(girlGObj)->flags18.ll >> 54) & 1) &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 450.0f))) {
        return 1;
    }
    return 0;
}

static int ditch_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, (float *)((char *)s + 0x4C0)) &&
        _DistxzGV((char *)s + 0x510, test_CURRENTROOT(girlGObj)) < 31.0f &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 200.0f))) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM(actBoyPullupReady);

/* the boy is hauling the girl up: moving while the stick is pushed between
   0.1 and 0.99 of its range, or further with button 0x20 held */
#define BOY_PULLUP_MOVING(sub) /* derived name */                                                  \
    (0.1f < (sub)->stick.mag && ((sub)->stick.mag < 0.99f || ((sub)->pad.now & 0x20)))

void actBoyPullupGo(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    ACTSendMail_PULLUP_START();
    while (1) {
        if (PAIR_IsStatus_GIRL_PULL() == 0) {
            ACTSendMailCorrect(self, 0x4B);
        } else {
            if (0.1f < sub->stick.mag && !BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 0x4C);
            } else if (BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 0x4D);
            } else {
                ACTSendMailCorrect(self, 0x4E);
            }
        }
        _ACTWait(1);
    }
}

extern void InsertCamera_Set(float *pos, float *tgt, int frames);

void actBoyBelift(GObj *volatile self)
{
    /* the quaternion is reached through a union, the form actEnemyKidnapEnd
       (enemy_act.c) gives the same memset-and-w=1 idiom */
    union { /* field names derived */
        float f[4];
    } q;

    float cam[4];
    float boypos[4];
    float p[4];
    float girlpos[4];
    float dir[4];
    float ofs[4];
    float hit[4];
    GObj *girl = GOBJ_ACT(self)->intrArg;
    float ratio;
    int mode;
    int lv;
    float dist;

    memset(&q, 0, 0x10);
    q.f[3] = 1.0f;
    ratio = 1.0f;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        ratio = 0.2f;
    }
    mode = GOBJ_ACT(girl)->enemy->liftKind == 3 ? 0 : 2;
    BOY_EXT(self)->liftObj = girl;
    beliftGirl = girl;
    BOY_EXT(self)->liftLevel = 10;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        RotQuaternionX(q.f, 0x4000);
    }
    SetMotionNodeFixModeParameter((void *)self, girl, mode, 0x16, q.f, 0.0f, 0.0f, 0.0f, ratio);
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    _ACTWait(1);
    while (1) {
        if (GOBJ_ACT(girl)->enemy->liftKind == 3 && (unsigned int)GOBJ_ACT(girl)->actMode == 0x61) {
            lv = BOY_EXT(self)->liftLevel;
            lv = lv < 0 ? 0 : (10.0f < lv ? 10.0f : lv);
            lv = lv * 0.5f;
            dist = lv * 100.0f + 500.0f;
            GetSkeltonPosition(boypos, boyGObj, 0x23);
            GetSkeltonPosition(girlpos, girl, 0x23);
            _OrientXZGV(dir, girlpos, boypos);
            sceVu0ScaleVector(ofs, dir, -dist);
            sceVu0AddVector(p, ofs, boypos);
            if (_DistSqGV(p, cam) < 2500.0f) {
                _InterGV(p, cam, p, 1.0f, 1.0f);
            } else {
                _MoveGV(p, cam, p, 50.0f);
            }
            if (ACTCheckCollis_WF(50.0f, girlpos, p, 0, hit)) {
                p[0] = hit[0];
                p[1] = hit[1];
                p[2] = hit[2];
            }
            cam[0] = p[0];
            cam[1] = p[1];
            cam[2] = p[2];
            GetSkeltonPosition(girlpos, boyGObj, 0x2C);
            sceVu0ScaleVector(p, p, -1.0f);
            sceVu0ScaleVector(girlpos, girlpos, -1.0f);
            InsertCamera_Set(p, girlpos, (60 - systemStatus[0] * 10) / systemStatus[1] / 6);
        }
        switch ((unsigned int)GOBJ_ACT(girl)->actMode) {
        case 0x61:
        case 0x62:
            break;
        default:
            ACTSendMailCorrect(self, 0xE2);
            debug_StdPrintfDummy("enemy error body slam[%s]\n",
                                 actModeTbl[(unsigned int)GOBJ_ACT(girl)->actMode].name);
            break;
        }
        _ACTWait(1);
    }
}

/* The walk order the boy is executing: sub->0x30 points at the request record
   the caller filled in, and actBoyReadyMove works on a private copy of it. */
typedef struct { /* field names derived */
    float pos[4];
    float dir[4];
    float range;
    int frames;
    int fix;
    int _2C;
} __attribute__((aligned(16))) BoyMoveOrder; /* derived name */

void actBoyReadyMove(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    BoyMoveOrder ord = *(BoyMoveOrder *)((char *)GOBJ_ACT(self)->intrData);

    while (1) {
        if ((((void *)self == girlGObj && girlControlMode != 0)
                 ? (GOBJ_SUB(self)->ctrl.motion + motionKind)->girlDirFrames
                 : (GOBJ_SUB(self)->ctrl.motion + motionKind)->dirFrames) == 0) {
            SetMotionDirectionSmooze(self, ord.dir, 10.0f);
        } else {
            _ACTMotDirSmzDirect((void *)self, ord.dir);
        }
        if (ord.fix) {
            sub->wish3.ll |= 0x80000;
            sub->wish3.ll |= 0x40;
        }
        if (ord.frames-- < 0) {
            ACTSendMailCorrect(self, 0x10A);
        }
        if (_DistxzSqGV(test_CURRENTROOT((void *)self), &ord) < ord.range * ord.range) {
            ACTSendMailCorrect(self, 0x10A);
        }
        if (0.1f < sub->stick.mag && 100 < _AbsRotyGV(ord.dir, (char *)sub + 0x120)) {
            ACTSendMailCorrect(self, 0x10A);
        }
        _ACTWait(1);
    }
}

void actBoyRescueReady(GObj *volatile self)
{
    GObj *g = GOBJ_ACT(self)->enemy->rescueObj;
    float p[4];
    float q[4];
    float step[4];
    float dir[4];
    float tmp[4];
    float np[4];

    union { /* field names derived */
        float f[4];
        long long ll[2];
    } pts[2];

    int cnt = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    int rest, hp, r;
    int n1, n2;
    char *hold;
    int u = 0;
    int gm = GOBJ_SUB(girlGObj)->ctrl.motion;
    int t;

    p[0] = test_CURRENTROOT((void *)self)[0];
    p[1] = test_CURRENTROOT((void *)self)[1];
    p[2] = test_CURRENTROOT((void *)self)[2];
    q[0] = test_CURRENTROOT(g)[0];
    q[1] = test_CURRENTROOT(g)[1];
    q[2] = test_CURRENTROOT(g)[2];
    _OrientXZGV(dir, q, p);
    sceVu0ScaleVector(tmp, dir, -60.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueBoyPos, q, tmp);
    sceVu0ScaleVector(tmp, dir, 0.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueGirlPos, q, tmp);
    GOBJ_ACT(self)->enemy->rescueGirlPos[1] += 50.0f;
    SetMotionDirection((void *)self, dir);
    sceVu0SubVector(step, GOBJ_ACT(self)->enemy->rescueBoyPos, (float *)p);
    sceVu0ScaleVector(step, step, 1.0f / (float)cnt);
    t = 1;
    rest = cnt;
    while (1) {
        if (0 < rest) {
            sceVu0AddVector(np, test_CURRENTROOT((void *)self), step);
            np[1] = test_CURRENTROOT((void *)self)[1];
            SetDirectRootPositionNoFitting((void *)self, np);
        }
        rest--;
        if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1 ||
            (GOBJ_SUB(self)->ctrl.ctrlFlags & 0x16) || GOBJ_SUB(self)->ctrl.frameEnd != 0) {
            hold = (char *)GOBJ_ACT(girlGObj)->carrier;
            hp = GOBJ_ACT(hold)->modeFrame;
            r = 0;
            /* n1 takes systemStatus[0] and is not read on this path */
            n1 = systemStatus[0];
            ACTGame_ConnectHand();
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 <= hp) {
                r = hp * ((60 - systemStatus[0] * 10) / systemStatus[1] * 3) /
                    ((60 - systemStatus[0] * 10) / systemStatus[1] * 10);
            }
            /* the quotient is not read */
            if (0 <= r) {
                r = (60 - systemStatus[0] * 10) / systemStatus[1];
            }
            if (gameover_flag == 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x15D, isysCurrentGObj);
                }
            }
            n1 = GetSkeltonFocusNode(girlGObj, 0x16);
            n2 = GetSkeltonFocusNode(boyGObj, 6);
            pts[0].f[0] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x30);
            pts[0].f[1] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x34);
            pts[0].f[2] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x38);
            pts[1].f[0] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x30);
            pts[1].f[1] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x34);
            pts[1].f[2] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x38);
            SetDirectRootPositionNoFittingWithNodePoint((void *)self, 6, pts[0].f, 0.05f);
            u = t++;
        }
        if (gm == 641) {
            if ((u / 30) & 1) {
                ACTSendMailCorrect(self, 0x160);
            } else {
                ACTSendMailCorrect(self, 0x15F);
            }
        } else {
            if ((u / 15) & 1) {
                ACTSendMailCorrect(self, 0x160);
            } else {
                ACTSendMailCorrect(self, 0x15F);
            }
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(actBoyDitch3mReady);

void actBoyRescueGirlBhang(GObj *volatile self)
{
    float tgt[4];
    float mv[4];
    float boy[4];
    float girl[4];
    Act *sub = GOBJ_ACT(self);
    int mode;
    int connect = 1;

    *(void **)((char *)sub + 0x18) = (void *)afterBoyRescueGirlBhang;
    while (1) {
        mode = 0;
        switch (GOBJ_ACT(girlGObj)->actMode) {
        case 0x1C:
            mode = 1;
            break;
        case 0x1D:
            mode = 2;
            if ((60 - systemStatus[0] * 10) / systemStatus[1] / 2 < sub->modeFrame) {
                if (connect) {
                    ACTGame_ConnectHand();
                    connect = 0;
                }
            }
            break;
        }
        if (mode != 0) {
            if (sub->modeFrame < 0xA) {
                boy[0] = test_CURRENTROOT(boyGObj)[0];
                boy[1] = test_CURRENTROOT(boyGObj)[1];
                boy[2] = test_CURRENTROOT(boyGObj)[2];
                girl[0] = test_CURRENTROOT(girlGObj)[0];
                girl[1] = test_CURRENTROOT(girlGObj)[1];
                girl[2] = test_CURRENTROOT(girlGObj)[2];
                tgt[0] = girl[0];
                tgt[2] = girl[2];
                tgt[1] = boy[1];
                _MoveGV(mv, boy, tgt, 5.0f);
                SetRootPosition((void *)self, mv);
            }
        }
        if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1) {
            if (mode == 1) {
                ACTSendMailCorrect(self, 0x15B);
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
                }
                GOBJ_ACT(girlGObj)->orientMot = 0x66;
            }
            if (mode == 2) {
                ACTSendMailCorrect(self, 0x15B);
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x40, isysCurrentGObj);
                }
            }
        }
        if (mode == 0) {
            ACTSendMailCorrect(self, 0xC7);
        }
        _ACTWait(1);
    }
}

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int frames, int cutType);

void SetStatusBoy_OtherStageGirlPinch(void)
{
    float buf[4];
    float cam[4];
    float pos[4];
    GObj *g = boyGObj;
    ActWork *w;
    float a;
    float b;
    float t;
    int frames;

    a = _ACTGame_GetParamF(0xD);
    b = _ACTGame_GetParamF(0xE);
    t = a * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f +
        b * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
    ExecuteSEPackage(0, 0x7F);
    GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
    w = GOBJ_WORK(g);
    frames = (int)t;
    w->pinchFrames = frames;
    w->pinchPosX = buf[0];
    w->pinchPosY = buf[1];
    w->pinchPosZ = buf[2];
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    pos[0] = test_CURRENTROOT(boyGObj)[0];
    pos[1] = test_CURRENTROOT(boyGObj)[1];
    pos[2] = test_CURRENTROOT(boyGObj)[2];
    InsertCamera_SetNoraml(cam, pos, frames, 0);
}

void *gopp_subBoyControl;

void actBoyStart(GObj *self)
{
    char *work;
    void *g;

    girlEscortedInStage = BOYINFO.escort;
    BOYINFO.escort = 0;

    ((int *)boyInfo)[4] = -1;

    ableBoyControl = 0;
    startWithGirl = 0;
    startWaitCancel = 0;
    startOnSofa = 0;
    sitLayoutDone = 0;

    sitCount = 0;
    debug_StdPrintfDummy("actBoyStart:%p\n", self);

    work = actInitialize(self);
    *(void **)(work + 0x68C) = attrWallHit;

    GetRootPosition(work + 0x110, (void *)self);

    actInitialize_ext_charcter(self);
    actInitialize_only_charcter(self);
    actInitialize_geo(self);

    GOBJ_ACT(self)->enemy->sofaWakeTime =
        (int)(_ACTGame_GetParamF(0x21) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) /
              60.0f);
    ACTGame_LwsEffectInit(self);

    *(int *)(work + 0x180) = 0;
    *(int *)(work + 0x184) = 0;

    gopp_subBoyControl = 0;
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init(self);

    _ACTWait(1);

    CurrentTargetGObj = (void *)self;

    *(float *)(work + 0x1E0) = _ACTGame_GetParamF(0x13);
    *(int *)(work + 0x48) = 0;

    if (BOYINFO.boyID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
        if (g != 0) {
            PickupWeapon(g, (void *)self, 0x16);
            *(void **)(work + 0x150) = g;
            if (BOYINFO.torch) {
                LightTorchOnOfWeaponWithNoSE(g);
            }
        } else {
            BOYINFO.boyID = 0;
        }
    }

    if (BOYINFO.girlID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.girlID);
        if (g != 0) {
            ACTSendMailCorrect(self, 0x35);
            *(void **)(work + 0x184) = *(void **)(work + 0x154) = g;
        } else {
            BOYINFO.girlID = 0;
        }
        startWithGirl = 1;
    }

    if (BOYINFO.layoutID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.layoutID);
        if (g != 0) {
            Vec16 p0 = {{0.0f, 0.0f, -50.0f, 1.0f}};
            Vec16 p1 = {{0.0f, 0.0f, 50.0f, 1.0f}};
            ClipWork cw;

            CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(g)->nodeMtx);
            MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
            sceVu0ApplyMatrix(cw.pt[0], MatrixDrive_GetMatrix(), &p0);
            sceVu0ApplyMatrix(cw.pt[1], MatrixDrive_GetMatrix(), &p1);
            cw.radius = 0.0f;
            ClipWall(&cw);
            if (cw.wall.elem == 0) {
                /* "!!! cannot find the sofa's wall !!!" */
                debug_StdPrintfDummy("！！！ソファの壁を見付けることができません！！！\n");
            } else {
                startOnSofa = 1;
                sitLayoutDone = 1;
                sofaWallHit.o = cw.wall.o;
                sofaWallHit.elem = cw.wall.elem;
                scpBoyControlReadDisable = 0;
                ActSendMail_WithAdditionalData((void *)self, 0x36, (void *)self, &sofaWallHit);
                if (BOYINFO.bit32 && girlGObj != 0) {
                    ActSendMail_WithAdditionalData(girlGObj, 0x36, girlGObj, &sofaWallHit);
                }
            }
        } else {
            BOYINFO.layoutID = 0;
        }
    }

    startWaitCancel = 0;

    *(void **)(work + 0xD0) = &actIntrList[74];

    actCreateSubThread(subBoyBrainMain, 20);
    gopp_subBoyControl = (void *)actCreateSubThread(subBoyControl, 21);
    actCreateSubThread(subBoyCollision, 21);
    actCreateSubThread(subCommonIdle, 21);

    *(void **)(work + 0xD4) = &actIntrList[79];
    ACTSendMailCorrect(self, 0xC7);

    _ACTWait(1);

    if (BOYINFO.fire && girlGObj != 0) {
        iosOmSendMail(girlGObj, 0x3F, self);
        debug_StdPrintfDummy("hand connect start\n");
    }
    _ACTWait(0);
}

static inline unsigned char IsBoyStatus_SupportGB(void) /* derived name */
{
    unsigned int st = (unsigned int)GOBJ_ACT(girlGObj)->actMode;
    if (st < 0x6B) {
        if (st >= 0x68) {
            return 1;
        }
    }
    return 0;
}

typedef struct { /* field names derived */
    CharPos pos; /* 0x00 */
    int boyID;   /* 0x08 */
    int girlID;  /* 0x0C */
    int f10;     /* 0x10 */
    int f14;
    int f18;
    unsigned int b1C : 8; /* 0x1C */
    unsigned int b1D : 8;
    unsigned int h1E : 16; /* 0x1E */
} CharacterPacket;         /* derived name */

static int boyActUnusedWord = -1; /* derived name */

inline void afterBoyHangG3M(int x)
{
    volatile int local = x;
}

inline void afterBoyRescueGirlBhang(GObj *volatile self)
{
    ACTGame_DisconnectHand();
}

inline void subBoyBrainMain(int arg)
{
    volatile int local = arg;
    while (1) {
        _ACTWait(1);
    }
}

inline void SetBoyInfo(GObj *weapon, GObj *item)
{
    int n;
    int i;
    if (weapon != 0) {
        ((int *)boyInfo)[0] = weapon->labelId;
    } else {
        ((int *)boyInfo)[0] = 0;
    }
    i = 0;
    n = 1;
    if (item != i) {
        ((int *)boyInfo)[n] = item->labelId;
    } else {
        ((int *)boyInfo)[n] = i;
    }
}

inline void GetBoyRootPositionForCamera(float *out, GObj *gobj)
{
    float buf[4];
    GObj *g = boyGObj;
    Act *sub;

    sub = GOBJ_ACT(g);
    GetRootPosition(buf, g);
    if (_DistSqGV(buf, (char *)sub + 0x110) < 40000.0f) {
        out[0] = sub->camRootX;
        out[1] = sub->camRootY;
        out[2] = sub->camRootZ;
    } else {
        GetRootPosition((char *)sub + 0x110, g);
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}

inline void Boy_Init(void)
{
    *(BoyWork *)boyInfo = boyInfoDefault;
    *(BoyKidnapWork *)characterPacket = characterPacketDefault;
}

INCLUDE_ASM(CorrectStickInfo);

INCLUDE_ASM(GetBoyWeaponGObj);

INCLUDE_ASM(actBoyStand);

INCLUDE_ASM(actBoyHang);

INCLUDE_ASM(actBoyBHang);

INCLUDE_ASM(actBoyFall);

INCLUDE_ASM(actBoyCall);

INCLUDE_ASM(actBoyHangBefore);

INCLUDE_ASM(actBoyBeslam);

INCLUDE_ASM(actBoyRescueSrc);

INCLUDE_ASM(actBoySupportGBBegin);

INCLUDE_ASM(actBoySupportGBLoop);

INCLUDE_ASM(actBoySupportGBEnd);

INCLUDE_ASM(actBoySupportBGBegin);

INCLUDE_ASM(actBoyDitch3mExec);

INCLUDE_ASM(actBoyHangG3M);

INCLUDE_ASM(IsAbleBoyControl);

INCLUDE_ASM(actBoyHand50);

INCLUDE_ASM(afterBoyHand50);

INCLUDE_ASM(actBoyHand100);

INCLUDE_ASM(afterBoyHand100);

INCLUDE_ASM(actBoyHand200);

INCLUDE_ASM(afterBoyHand200);

INCLUDE_ASM(ACTSearchEnemy);

INCLUDE_ASM(DeleteBoyWeapon);

INCLUDE_ASM(isLiftBoyEnable);

INCLUDE_ASM(SetKidnapInfo);

INCLUDE_ASM(GetKidnapInfo);

INCLUDE_ASM(PrivInsCamSet);

INCLUDE_ASM(BoyInfoUpdate_StageChange);

INCLUDE_ASM(IsBoyStatus_EnemyMustWait);

INCLUDE_ASM(IsGirlEscortedInNextStage);

INCLUDE_ASM(IsGirlEscortedInCurrentStage);

INCLUDE_ASM(GetSaveSofaLayoutID);

INCLUDE_ASM(OnGirlEscortFlag);

INCLUDE_ASM(SetBoyWeaponGObj);

INCLUDE_ASM(IsBoyStatus_NotDanger);

INCLUDE_ASM(RequestStageChangeKidnapEnd);

INCLUDE_ASM(GetEfStageCameraTargetID);

INCLUDE_ASM(IsBackFromEfStage);

INCLUDE_ASM(PrivInsCamChk);

INCLUDE_ASM(PrivInsCamChk_Control);

INCLUDE_ASM(GetbufpCharacterPacket);

INCLUDE_ASM(GetsizeCharacterPacket);

INCLUDE_ASM(MakeCharacterPacket);

INCLUDE_ASM(ReadCharacterPacket);

INCLUDE_ASM(ACTSearchGObj);

INCLUDE_ASM(afterBoySwim);

INCLUDE_ASM(actBoyJump);

INCLUDE_ASM(afterBoyTakeWeapon);
