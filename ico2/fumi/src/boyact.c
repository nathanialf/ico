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
INCLUDE_ASM(CorrectOrient_RopeCliff);

/* The three climb headers (omori/include/b50climb.h, b100climb.h,
   b200climb.h) textually included here, as girl_act.c does with its own
   three: each defines the hand-off's after-routine and act-routine `inline`,
   which the compiler emits at the end of the file in boyact.h's order, and
   the mot-routine plainly, emitted in place.  Their strings come out here,
   in this order, at the head of the TU's .rodata. */
INCLUDE_ASM_LIT(afterBoyHand50);

INCLUDE_ASM_LIT(actBoyHand50);

INCLUDE_ASM(motBoyHand50);

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

INCLUDE_ASM_LIT(actBoyHand100);

INCLUDE_ASM(motBoyHand100);

INCLUDE_ASM_LIT(actBoyHand200);

INCLUDE_ASM(motBoyHand200);

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* Each of the two height tests is one source line applying ABSF twice to the
   same height difference, so each re-evaluates the pair of test_CURRENTROOT
   calls.  The second test's body is empty in retail. */
#define BOYGIRL_DY()                                                                               \
    (test_CURRENTROOT(boyGObj)[1] - test_CURRENTROOT(girlGObj)[1]) /* derived name */
#define ABSF(x) ((x) < 0.0f ? -(x) : (x))                          /* derived name */

INCLUDE_ASM(handoff_heroin);

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

INCLUDE_ASM(CheckCollisionAttr);

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

static BoyWork boyInfoDefault = {{0, 0, 0xFFFFFFFF}}; /* derived name */

static BoyKidnapWork characterPacketDefault = {{0}}; /* derived name */

static BgaEntry boyBgaTable[] = {
    /* derived name */
    {416, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {417, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {421, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {422, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */

/* boyact.o's two .data globals, the last two quadwords of its .data:
   test_rope_velo, which no code names, and add_rope_vec, the boy's orient
   snapshot SaveBoyOrientForScript writes. */
float test_rope_velo[4] = {0.0f, 0.0f, 0.0f, 0.0f};

float add_rope_vec[4] = {0.0f, 0.0f, 0.0f, 0.0f};

static void BoyBgaManager(void *self, int id, void *dst)
{
    /* UpdateGeo is a GNU nested function: it reads `self` out of
       BoyBgaManager's frame through the static chain. */
    void UpdateGeo(BgaEntry * p)
    {
        float dir[4];
        float tmp[4];
        void *obj;

        if (p->b0F != 0) {
            dir[0] = test_CURRENTORIENT(self)[0];
            dir[1] = test_CURRENTORIENT(self)[1];
            dir[2] = test_CURRENTORIENT(self)[2];
        } else {
            obj = isysGObjSearchFromObjKindID_begin(46);
            _OrientXZGV(dir, test_CURRENTROOT(obj), test_CURRENTROOT(self));
        }
        sceVu0ScaleVector(dir, dir, p->f10);
        ActGame_GetOrientQ(p->f30, dir, 0);
        sceVu0ScaleVector(tmp, test_CURRENTORIENT(self), p->f08);
        sceVu0AddVector(p->f20, test_CURRENTROOT(self), tmp);
        sceVu0ScaleVector(tmp, test_CURRENTORIENT(self), p->f04);
        _ApplyRyGV(tmp, 1.5707964f);
        sceVu0AddVector(p->f20, p->f20, tmp);
        p->f20[1] += (float)p->b0D;
    }
    BgaEntry *p;
    int i;
    int v;
    int r;

    for (i = 0; 0 <= boyBgaTable[i].id; i++) {
        if (boyBgaTable[i].id == id) {
            p = &boyBgaTable[i];
            goto found;
        }
    }
    debug_assert(__FILE__, 1543);
    __assert(__FILE__, 1543, "0");
    p = 0;
found:
    v = *(int *)dst;
    if (v < 0) {
        return;
    }
    if (p->b0C != 0) {
        UpdateGeo(p);
        goto reload;
    }
    if (v == 0) {
        UpdateGeo(p);
    reload:
        v = *(int *)dst;
    }
    r = (int)stage_PlayBgAnimation(p->id, (float)v, p->f20, p->f30);
    if (p->b0E == 0) {
        *(int *)dst = r;
    } else if (0 <= r) {
        *(int *)dst = r;
    }
}

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

INCLUDE_ASM(E3_StageStartBoy);

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

INCLUDE_ASM(subBoyControl);

/* subBoyControl's countdown, set to a fifth of a second of frames */
static int boyControlWait = 0; /* derived name */

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

INCLUDE_ASM(InitSwapWeapon);

static void PutWeapon(void);

INCLUDE_ASM(PutWeapon);

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

INCLUDE_ASM(OtherStageGirlPinchCamera_After);

INCLUDE_ASM(ACTDispLwsBoyStonize_InQueenStage);

static int characterPacket[8]; /* derived name */

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void Camctrl_SetTarget(GObj *gobj, GObj *subGObj, int pri);

/* the object kinds the proximity scan below walks, terminated by -1 */
typedef struct { /* field names derived */
    int id[4];
} ObjKindList; /* derived name */

static const ObjKindList collisionKinds = {{4, 46, 61, -1}}; /* derived name */

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

INCLUDE_ASM(actBoySwim);

INCLUDE_ASM(actBoyWalk);

INCLUDE_ASM(actBoyRun);

/* the nearest enemy in front of the actor, which ACTSearchEnemy and
   actBoyAttack inline */
static inline void searchEnemy(void *self, int *out_id, float *out_vec) /* derived name */
{
    searchGObj(self, (*(int *)((char *)self + 0xC) ^ 1) ? 1 : 4, 0x5A, out_id, out_vec, 300.0f);
}

INCLUDE_ASM_LIT(actBoyFall);

INCLUDE_ASM(actBoyAttack);

INCLUDE_ASM(actBoyTakeWeaponReady);

/* sub->0x14 is the actor's "after" callback slot: actBoyTakeWeapon arms it with
   afterBoyTakeWeapon and calls it through the slot once the motion frame passes
   the swap point, so it is written and read as a function pointer. */
typedef void (*BoyAfterFunc)(GObj *volatile a0);

INCLUDE_ASM(actBoyTakeWeapon);

INCLUDE_ASM(func_001520E8);

#define BOY_WALL(o) ((char *)GOBJ_ACT(o)->work) /* derived name */
#define BOY_GIRL_DY()                                                                              \
    (test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1]) /* derived name */

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

INCLUDE_ASM_LIT(actBoyCall);

INCLUDE_ASM_LIT(actBoyItemAfter);

INCLUDE_ASM(ditch_check_heroin_position);

INCLUDE_ASM(actBoyPullupReady);

/* the boy is hauling the girl up: moving while the stick is pushed between
   0.1 and 0.99 of its range, or further with button 0x20 held */
#define BOY_PULLUP_MOVING(sub) /* derived name */                                                  \
    (0.1f < (sub)->stick.mag && ((sub)->stick.mag < 0.99f || ((sub)->pad.now & 0x20)))

INCLUDE_ASM(actBoyPullupGo);

extern void InsertCamera_Set(float *pos, float *tgt, int frames);

INCLUDE_ASM(actBoyBelift);

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

INCLUDE_ASM(actBoyRescueReady);

INCLUDE_ASM(actBoyDitch3mReady);

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int frames, int cutType);

INCLUDE_ASM_LIT(RequestStageChangeKidnapEnd);

INCLUDE_ASM(SetStatusBoy_OtherStageGirlPinch);

void *gopp_subBoyControl;

INCLUDE_ASM(actBoyStart);

INCLUDE_ASM_LIT(afterBoySwim);

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

INCLUDE_ASM(CorrectStickInfo);

INCLUDE_ASM(GetBoyWeaponGObj);

INCLUDE_ASM(actBoyStand);

INCLUDE_ASM(actBoyHang);

INCLUDE_ASM(actBoyBHang);

INCLUDE_ASM(actBoyFall);

INCLUDE_ASM(actBoyCall);

INCLUDE_ASM(actBoyItem);

INCLUDE_ASM(actBoyItemAfter);

INCLUDE_ASM(actBoyCliffHesitate);

INCLUDE_ASM(actBoyHangBefore);

INCLUDE_ASM(actBoyReadyMove);

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

INCLUDE_ASM(BoyInfoUpdate_StageChange);

INCLUDE_ASM(IsBoyStatus_EnemyMustWait);

INCLUDE_ASM(IsGirlEscortedInNextStage);

INCLUDE_ASM(IsGirlEscortedInCurrentStage);

INCLUDE_ASM(GetSaveSofaLayoutID);

INCLUDE_ASM(OnGirlEscortFlag);

INCLUDE_ASM(SetBoyWeaponGObj);

INCLUDE_ASM(RequestStageChangeKidnapEnd);

INCLUDE_ASM(GetEfStageCameraTargetID);

INCLUDE_ASM(IsBackFromEfStage);

INCLUDE_ASM(GetbufpCharacterPacket);

INCLUDE_ASM(GetsizeCharacterPacket);

INCLUDE_ASM(MakeCharacterPacket);

INCLUDE_ASM(ReadCharacterPacket);

INCLUDE_ASM(ACTSearchGObj);

INCLUDE_ASM(afterBoySwim);

INCLUDE_ASM(actBoyJump);

INCLUDE_ASM(afterBoyTakeWeapon);

INCLUDE_ASM(afterBoyHangG3M);

INCLUDE_ASM(subBoyBrainMain);

INCLUDE_ASM(SetBoyInfo);

INCLUDE_ASM(GetBoyRootPositionForCamera);

INCLUDE_ASM(Boy_Init);
