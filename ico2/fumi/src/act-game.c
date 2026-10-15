#include "typedef.h"
#include "act-game.h"
#include "debug.h"
#include "gamesys.h"
#include "main.h"
#include "sceneManager.h"
#include "act-env.h"
#include "act-wish.h"
#include "girl_act.h"
#include "stage_orient.h"
#include "mail-add-data.h"
#include "script.h"
#include "StageAnimation.h"
#include "clipCollisionManager.h"
#include "matrixDrive.h"
#include "motionManager.h"
#include "motionOrientManager.h"
#include "camera-editor.h"
#include "multiBgaManager.h"
#include "quaternion.h"
#include <stdlib.h>
#include "motionManager2.h"
#include "geometryManager.h"
#include "act-parallel-control.h"
#include "brain.h"
#include <string.h>
#include "gflag.h"
#include "Matrix.h"
#include "debug_exception.h"
#include <libvu0.h>
#include "enemy_act.h"
#include "gobj.h"
#include "act_bird.h"
#include "item.h"
#include "commonact.h"
#include "obj_manager.h"
#include "gv.h"
#include "fieldCollision.h"
#include <assert.h>
#include "poly-flat.h"
#include "act.h"
#include "brain.h"
#include "include_asm.h"

/* weapon.h's WeaponDef, which this TU does not include (CheckWeaponKind
   differs): the weapon kind's motion orient at 0x1C */
typedef struct { /* field names derived */
    char pad0[28];
    int motOrient;
    char pad20[4];
} WeaponEntry; /* derived name */

typedef struct { /* field names derived */
    long long w;
} __attribute__((packed)) U64ag; /* derived name */

/* The 0x190-byte-per-entry motion record table, indexed by the object's
   current motion id (obj->0x15C->0x4A0); the fields this TU reads, named as
   motionOrientManager.h's MotionDef. */
typedef struct { /* field names derived */
    char pad0[336];
    int playMode;
    char pad154[44];
    short priInputBegin;
    short priInputEnd;

    union {
        unsigned int w;

        struct {
            unsigned short lo, hi;
        } h;

        char b;
    } modeBits;

    unsigned int flags;
    unsigned int flags2;
} MotionRec; /* derived name */

extern MotionRec motionKind[];

typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4S; /* derived name */

/* as in boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void SetBoyInfo(GObj *weapon, GObj *item);
/* as in boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void BoyInfoUpdate_StageChange(void);

/* One table: a 100-entry object list, two parallel per-entry int arrays
   (the full view result and the simple one), the entry count and the
   round-robin cursor the loop below advances one entry per frame. */
typedef struct {     /* field names derived */
    GObj *obj[100];  /* 0x000 */
    int view[100];   /* 0x190 */
    int simple[100]; /* 0x320 */
    int num;         /* 0x4B0 */
    int cur;         /* 0x4B4 */
} ActGameViewTbl;    /* derived name */

/* the view table described below, the tail of act-game.o's .bss; no code
   reaches the 0x440 bytes ahead of it */
static ActGameViewTbl actGameView; /* derived name */

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* the motion-play-speed-ratio mode at work+0x54, which
   ACTGame_SetMotionPlaySpeedRatio_Exec dispatches on */
typedef enum { MPSR_OFF, MPSR_ONESHOT, MPSR_HOLD } MpsrMode;

/* self->0x164->0x688, the per-actor motion work block, re-derived at every
   use */
#define ACTWORK(g) ((char *)GOBJ_ACT(g)->work) /* derived name */

/* unprototyped: weapon.h declares CheckWeaponKind(char *), and
   ACTGame_isWeaponCombustible calls it with no argument */
extern int CheckWeaponKind();

/* The actor's orient-request bitfield: three 64-bit request words at
   sub+0x478, each paired with the permission mask 16 bytes further on. */
#define ORQ(s, i) (((ActStatusWord *)((s) + 0x478))[i].q)       /* derived name */
#define ORM(s, i) (((ActStatusWord *)((s) + 0x478))[(i) + 2].q) /* derived name */
#define ORBIT(w, b) ((int)((w) >> (b)) & 1)                     /* derived name */

/* The pair of hand-link wall probes the debug overlay draws, mirrored into
   the actor work area at +0x540; handClInfoClear is the cleared template
   each frame starts from. */
typedef struct {        /* field names derived */
    unsigned char on;   /* 0x00 */
    unsigned char hit;  /* 0x01 */
    unsigned char attr; /* 0x02 */
    char pad3[13];
    long long orient[2]; /* 0x10 -- GetOrientOfWall's output */
    unsigned char hit2;  /* 0x20 */
    unsigned char attr2; /* 0x21 */
    char pad22[14];
    long long orient2[2]; /* 0x30 */
} HandClInfo;             /* derived name */

static HandClInfo handClInfoClear = {0}; /* derived name */

/* The hand-mode rows the motion record's two hand nibbles index: 16 bytes a
   row, the mode RequestChangeHandMode wants in the last word. */
typedef struct { /* field names derived */
    char pad0[12];
    int mode;
} HandModeRow; /* derived name */

extern HandModeRow motionIKEffKind[];
static void ACTItemWatchMotion(GObj *self);
/* as in boyact.h, which this TU does not include */
extern void PrivInsCamSet(float *pos, float *tgt, GObj *track, int inFrames, int outFrames,
                          float inRate, float blend, unsigned char control);

/* The pending hand-mode command record: two ints at +0x314 (connect) and
   +0x31C (disconnect) of the actor's hand work block. */
typedef struct { /* field names derived */
    int flag;    /* the hand mode set, 0 for none */
    int pri;     /* the priority it was set at */
} HandModeCmd;   /* derived name */

/* as in weapon.h, which this TU does not include (CheckWeaponKind differs) */
extern int GetTorchGObjOfWeapon(GObj *weapon);
extern WeaponEntry weaponKind[];

INCLUDE_ASM(ACTGame_SaveActorInformation);

void ACTGame_DeleteActorInformation(GObj *self)
{
    gamesysObjInfoCls(self->kind, self->labelId);
}

static void EXITDATA_GetNextPosition(int idx, float *pos, float *rot)
{
    exit_no = idx;
    test_nextstage_firstwalk_set(idx, exitData[idx].firstWalk0, exitData[idx].firstWalk1,
                                 exitData[idx].firstWalk2);

    pos[0] = -exitData[idx].pos[0];
    pos[1] = -exitData[idx].pos[1];
    pos[2] = -exitData[idx].pos[2];

    rot[0] = exitData[idx].rot[0];
    rot[1] = exitData[idx].rot[1];
    rot[2] = exitData[idx].rot[2];

    sceVu0ScaleVector(rot, rot, 0.017453292f);
}

void ACTGame_StageChangeGObj(GObj *self, int idx)
{
    float tmp_a[4];
    float tmp_b[4];
    float buf[4];
    Vec4S buf2;
    Vec4S buf3;

    EXITDATA_GetNextPosition(idx, tmp_a, tmp_b);
    if (self->kind == 0x11) {
        memset(buf, 0, 0x10);
        buf[2] = 250.0f;
        _ApplyRyGV(buf, -tmp_b[1]);
        sceVu0AddVector(tmp_a, tmp_a, buf);
    }
    if (self == girlGObj) {
        if (0.0f <= GOBJ_WORK(self)->escortOffset) {
            memset(&buf3, 0, 0x10);
            buf3.z = -GOBJ_WORK(girlGObj)->escortOffset;
            buf2 = buf3;
            _ApplyRyGV(&buf2.x, -tmp_b[1]);
            sceVu0AddVector(tmp_a, tmp_a, &buf2);
        }
    }
    gamesysObjInfoPosNewStageSet(self->labelId, self->kind, exitData[idx].nextStage, tmp_a, tmp_b);
}

/* the first exit whose next stage is this one */
static inline int getExitIndexOfStage(int stage) /* derived name */
{
    int i;

    for (i = 0; i < 261; i++) {
        if (exitData[i].nextStage == stage) {
            return i;
        }
    }
    return 0;
}

INCLUDE_ASM(ACTGame_SetActors_Debug);

/* Returns a char-width boolean, through an `int` intermediate. */
void ACTGame_TryConnectHand(void)
{
    RequestChangeHandMode(boyGObj, 1, 4, 5, girlGObj, 0, 0);
}

void ACTGame_TryDisconnectHand(void)
{
    RequestChangeHandMode(boyGObj, 1, 4, 0, 0, 0, 0);
}

void ACTGame_DisconnectHand_WithMail(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy("with mail\n");
}

void *floorGObj_ACTCheckCollis_WELL;

void *wallGObj_ACTCheckCollis_WAY;

/* the float is the last parameter */
int ACTCheckView(GObj *self, void *target, void *targetPos, int range, float f)
{
    float pos[4];
    float v[4];
    float d[4];
    float *m;
    int n;

    n = GetSkeltonFocusNode(self, 35) << 6;
    m = (float *)(n + GOBJ_SUB(self)->nodeMtx);
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    if (_DistGV(pos, targetPos) < f) {
        return 1;
    }
    if (range >= 360) {
        return 1;
    }
    /* each arm a three-component vector set; v[3] is zeroed on the next
       line */
    if (*(int *)((char *)self + 0xC) == 4) {
        v[0] = 0.0f;
        v[1] = -1.0f;
        v[2] = 0.0f;
    } else {
        v[0] = 0.0f;
        v[1] = 1.0f;
        v[2] = 0.0f;
    }
    v[3] = 0.0f;
    sceVu0ApplyMatrix(v, (char *)GOBJ_SUB(self)->nodeMtx + n, v);
    sceVu0SubVector(d, targetPos, pos);
    if (0.8f < (v[1] < 0.0f ? -v[1] : v[1])) {
        v[0] = test_CURRENTORIENT(self)[0];
        v[1] = test_CURRENTORIENT(self)[1];
        v[2] = test_CURRENTORIENT(self)[2];
    }
    if (range / 2 < (_RotyGV(v, d) < 0 ? -_RotyGV(v, d) : _RotyGV(v, d))) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM_LIT(ACTGameView_Add);

/* actGameView is one table: a 100-entry object list at +0x000, two parallel
   100-entry int arrays at +0x190 and +0x320, and the entry count at +0x4B0. */
/* The view work record is reached as `self->act->view`, its two chase loads
   read as int. */
void ACTGameView_Loop(GObj *self)
{
    float pos[4];
    int i;

    i = actGameView.cur;
    if (actGameView.simple[i] != 0) {
        GetRootPosition(pos, actGameView.obj[i]);
        actGameView.view[i] = ACTCheckView(self, actGameView.obj[i], pos, 150, 300.0f);
    } else {
        actGameView.view[i] = 0;
    }

    switch (GOBJ_WORK(self)->viewState) {
    case 0:
        if (5000.0f < _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(actGameView.obj[i]))) {
            GOBJ_WORK(self)->viewState = 6;
        } else {
            GOBJ_WORK(self)->viewState = 1;
        }
        break;
    case 1:
        GOBJ_WORK(self)->view.func = ClipWall;
        GOBJ_WORK(self)->view.obj = actGameView.obj[i];
        GOBJ_WORK(self)->view.clip.radius = 0.0f;
        GetSkeltonPosition(GOBJ_WORK(self)->view.clip.pt[0], self, 0x23);
        GetRootPosition(GOBJ_WORK(self)->view.clip.pt[1], actGameView.obj[i]);
        RequestClipCollision(&GOBJ_WORK(self)->view);
        GOBJ_WORK(self)->viewState = 2;
        break;
    case 2:
        if (GOBJ_WORK(self)->view.done != 0) {
            if (GOBJ_WORK(self)->view.clip.wall.elem != 0) {
                GOBJ_WORK(self)->viewState = 6;
            } else {
                GOBJ_WORK(self)->viewState = 3;
            }
        }
        break;
    case 3:
        GOBJ_WORK(self)->view.func = ClipFloor;
        GOBJ_WORK(self)->view.obj = actGameView.obj[i];
        GOBJ_WORK(self)->view.clip.radius = 0.0f;
        GetSkeltonPosition(GOBJ_WORK(self)->view.clip.pt[0], self, 0x23);
        GetRootPosition(GOBJ_WORK(self)->view.clip.pt[1], actGameView.obj[i]);
        RequestClipCollision(&GOBJ_WORK(self)->view);
        GOBJ_WORK(self)->viewState = 4;
        break;
    case 4:
        if (GOBJ_WORK(self)->view.done != 0) {
            if (GOBJ_WORK(self)->view.clip.floor.elem != 0) {
                GOBJ_WORK(self)->viewState = 6;
            } else {
                GOBJ_WORK(self)->viewState = 5;
            }
        }
        break;
    case 5:
        actGameView.simple[i] = 1;
        GOBJ_WORK(self)->viewState = 7;
        break;
    case 6:
        actGameView.simple[i] = 0;
        GOBJ_WORK(self)->viewState = 7;
        break;
    case 7:
        actGameView.cur++;
        if (!(actGameView.cur < actGameView.num)) {
            actGameView.cur = 0;
        }
        GOBJ_WORK(self)->viewState = 0;
        break;
    }
}

static void ACTGame_LwsEffectProcess(GObj *self)
{
    BgaDisp *m = GOBJ_ACT(self)->enemy->lwsEffect;
    if (m != 0) {
        DispMultiBgaManagerWithKind(0x1B1, m, 1);
    }
}

/* both absolute values are written as `((x) < 0 ? -(x) : (x))` */
int _ACTGame_SearchGObj(GObj *self, GObj *tgt, float range, float height, int angle, float *out)
{
    float buf[4];
    int n;

    if (!(_DistxzSqGV(test_CURRENTROOT(self), test_CURRENTROOT(tgt)) < range * range)) {
        return 0;
    }
    if ((test_CURRENTROOT(self)[1] - test_CURRENTROOT(tgt)[1] < 0.0f
             ? -(test_CURRENTROOT(self)[1] - test_CURRENTROOT(tgt)[1])
             : test_CURRENTROOT(self)[1] - test_CURRENTROOT(tgt)[1]) < height) {
        sceVu0SubVector(buf, test_CURRENTROOT(tgt), test_CURRENTROOT(self));
        n = _RotyGV(buf, test_CURRENTORIENT(self)) < 0 ? -_RotyGV(buf, test_CURRENTORIENT(self))
                                                       : _RotyGV(buf, test_CURRENTORIENT(self));
        if (n < angle) {
            out[0] = buf[0];
            out[1] = buf[1];
            out[2] = buf[2];
            return 1;
        }
    }
    return 0;
}

int ACTLookTarget_Exec(GObj *self)
{
    float pos[4];
    Act *s = GOBJ_ACT(self);
    GObj *t = s->lookTarget;
    int rv;
    int b0;

    if (debug_font_flag & 1) {
        debug_Printf(10, 170, 0x0FFFFFFF, "mode=[%d]\n", GOBJ_SUB(self)->root.lookMode);
    }
    rv = 0;
    if (s->lookPri == 0) {
        GOBJ_SUB(self)->root.lookMode = 0;
    } else {
        if (t == 0) {
            pos[0] = s->lookPosX;
            pos[1] = s->lookPosY;
            pos[2] = s->lookPosZ;
        } else if (t == boyGObj) {
            /* the boy's skeleton position read in place */
            int idx = GetSkeltonFocusNode(t, 35) << 6;
            pos[0] = *(float *)(idx + *(int *)(((IntFloat *)&t->dobj)->i + 0xC) + 0x30);
            pos[1] = *(float *)(idx + *(int *)(((IntFloat *)&t->dobj)->i + 0xC) + 0x34);
            pos[2] = *(float *)(idx + *(int *)(((IntFloat *)&t->dobj)->i + 0xC) + 0x38);
        } else {
            GetRootPosition(pos, t);
        }
        b0 = s->lookMode;
        rv = 1;
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x390))->f = pos[0];
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x394))->f = pos[1];
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x398))->f = pos[2];
        GOBJ_SUB(self)->root.lookMode = b0;
    }
    return rv;
}

INCLUDE_ASM(ACTParaStatus_Clear);

INCLUDE_ASM(ACTParaStatus_Exec);

void _ACTCharStatus_Clear(void *self)
{
    Act *s = GOBJ_ACT(self);
    int old = s->statusOther;
    int *sel;
    int *g;
    float nearest;
    float d;

    memset((char *)s + 0x58, 0, 0x38);
    if (self == (char *)boyGObj || self == ((char *)girlGObj)) {
        nearest = 3.40282347e+38f; /* FLT_MAX */
        sel = 0;
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            d = _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(g));
            if (actEnemyFlagCheckActive(g)) {
                if (d < nearest) {
                    sel = g;
                    nearest = d;
                }
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        *(int **)((char *)s + 0x7C) = sel;
        if (self == (char *)boyGObj) {
            if (old != 0 && s->frame % ((60 - systemStatus[0] * 10) / systemStatus[1] * 2) != 0) {
                s->statusOther = old;
            }
        }
    }
}

/* The play-speed ratio's debug override, built only when DEBUG is defined:
   the debug build can fix the ratio from the debugger before it is applied;
   the retail build leaves the helper without a body. */
static __inline__ void speedRatioDebugOverride(float *ratio) /* derived name */
{
#ifdef DEBUG
    if (dbgSpeedRatioFix) {
        *ratio = dbgSpeedRatio;
    }
#endif
}

void GetSkeltonOrient(float *out, void *obj, int node)
{
    int n = GetSkeltonFocusNode(obj, node);
    if (((GObj *)obj)->kind == 4) {
        *(int *)((char *)out + 0x0) = 0;
        ((IntFloat *)((char *)out + 0x4))->f = -1.0f;
        *(int *)((char *)out + 0x8) = 0;
    } else {
        *(int *)((char *)out + 0x0) = 0;
        ((IntFloat *)((char *)out + 0x4))->f = 1.0f;
        *(int *)((char *)out + 0x8) = 0;
    }
    *(int *)((char *)out + 0xC) = 0;
    sceVu0ApplyMatrix(out, (char *)(GOBJ_SUB(obj)->nodeMtx + (n << 6)), out);
}

/* the bird broadcast, between GetSkeltonPosition and
   ACTGame_InnerVelocityUpdate */
static inline void actGame_SendMailToBirds(GObj *self) /* derived name */
{
    float other[4];
    float mine[4];
    GObj *bird;
    int mail;

    Act *s = GOBJ_ACT(self);
    bird = isysGObjSearchFromObjKindID_begin(32);
    mail = 423;
    if (s->actMode == 3) {
        mail = 424;
    }
    GetRootPosition(mine, self);
    while (bird != 0) {
        GetRootPosition(other, bird);
        if (_DistSqGV((int *)mine, other) < 160000.0f) {
            _ACTSendMailToBird(bird, mail, self);
        }
        bird = isysGObjSearchFromObjKindID_next(bird);
    }
}

/* The speed is computed before the parameter block is fetched, both hops of
   that fetch going through one pointer variable; the pos stores go through
   it and the two thresholds test the speed itself. */
static void ACTGame_InnerVelocityUpdate(GObj *self)
{
    float pos[4];
    int slow;
    int stop;
    int nomove;
    char *p;
    float speed;

    slow = 0;
    stop = 0;
    pos[0] = test_CURRENTROOT(self)[0];
    pos[1] = test_CURRENTROOT(self)[1];
    pos[2] = test_CURRENTROOT(self)[2];
    sceVu0SubVector((char *)GOBJ_ACT(self)->work + 0x3F0, pos,
                    (char *)GOBJ_ACT(self)->work + 0x3E0);
    speed = FSqrt(GOBJ_WORK(self)->velX * GOBJ_WORK(self)->velX +
                  GOBJ_WORK(self)->velY * GOBJ_WORK(self)->velY +
                  GOBJ_WORK(self)->velZ * GOBJ_WORK(self)->velZ);
    p = (char *)GOBJ_ACT(self);
    p = (char *)*(int *)(p + 0x678);
    *(float *)(p + 0x400) = speed;
    *(float *)(p + 0x3E0) = pos[0];
    *(float *)(p + 0x3E4) = pos[1];
    *(float *)(p + 0x3E8) = pos[2];
    if (speed < 6.0f) {
        slow = 1;
    }
    if (speed < 2.0f) {
        stop = 1;
    }
    if (slow != 0) {
        GOBJ_WORK(self)->slowFrames += 1;
    } else {
        GOBJ_WORK(self)->slowFrames = 0;
    }
    if (stop != 0) {
        GOBJ_WORK(self)->stopFrames += 1;
    } else {
        GOBJ_WORK(self)->stopFrames = 0;
    }
    if (4 <= GOBJ_WORK(self)->slowFrames) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x408))->q |= 1ULL << 32;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x408))->q &= ~(1ULL << 32);
    }
    if (4 <= GOBJ_WORK(self)->stopFrames) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x408))->q |= 1ULL << 33;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x408))->q &= ~(1ULL << 33);
    }
    nomove = 0;
    if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->flags >> 13) & 1) {
        if (GOBJ_WORK(self)->speed < 4.0f) {
            nomove = 1;
        }
    }
    if (nomove != 0) {
        GOBJ_WORK(self)->noMoveFrames += 1;
    } else {
        GOBJ_WORK(self)->noMoveFrames = 0;
    }
    if (GOBJ_WORK(self)->noMoveFrames > (60 - systemStatus[0] * 10) / systemStatus[1] * 5) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x410))->q |= 1ULL << 32;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x410))->q &= ~(1ULL << 32);
    }
}

INCLUDE_ASM(ACTGame_BeforeFunc);

/* OR the 16 pending-request bytes into the live request bytes. */
static inline void actEnv_OrRequestBytes(unsigned char *dst, unsigned char *src) /* derived name */
{
    int i;

    for (i = 15; i >= 0; i--, dst++, src++) {
        *dst |= *src;
    }
}

/* masks the 16-byte request-flag block in place */
static inline void andRequestFlags(char *d, char *m) /* derived name */
{
    int i;
    for (i = 15; i >= 0; i--) {
        *d = *d & *m;
        d++;
        m++;
    }
}

INCLUDE_ASM(FunctionAboutClingedStatus);

INCLUDE_ASM(ACTEnvGetTest);

INCLUDE_ASM(ActOrientTest);

INCLUDE_ASM(GetGirlHandlinkClInfo);

INCLUDE_ASM(hand_able_connect_267);

INCLUDE_ASM(ACTGame_CommonLoop);

inline void GetGirlPositionAtThisStage(float *pos)
{
    float buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(pos, stage_no, id, buf);
}

INCLUDE_ASM(GetTarget_280);

INCLUDE_ASM(ACTLookTargetSystem_Exec);

INCLUDE_ASM(ACTItemThrow_301);

INCLUDE_ASM(ACTItemWatchMotion);

INCLUDE_ASM(ACTGame_InsertCamera_GirlIsPinch);

INCLUDE_ASM(updateHMC_314);

INCLUDE_ASM(RequestChangeHandMode);

INCLUDE_ASM(ACTNotNeedCameraOffset);

INCLUDE_ASM(ACTGameCollisionOn);

INCLUDE_ASM(ACTGameCollisionOff);

INCLUDE_ASM(ACTGame_CheckItemMotion);

INCLUDE_ASM(ACTGame_CheckHandMotion);

INCLUDE_ASM(ACTGame_StageChangeGObjID);

INCLUDE_ASM(ACTGame_StageChangeGObjDirect);

INCLUDE_ASM(ACTGame_FLAG_LIFEPINCH);

INCLUDE_ASM(ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM(GetSkeltonPosition);

INCLUDE_ASM(SetDirectRootPositionWithNodePointLimit);

INCLUDE_ASM(ACTGameView_Init);

INCLUDE_ASM(ACTCharctrl_Lock);

INCLUDE_ASM(ACTCharctrl_Unlock);

INCLUDE_ASM(ACTGame_ConnectHand);

INCLUDE_ASM(ACTGame_DisconnectHand);

INCLUDE_ASM(PAIR_GetPosition_BOY);

INCLUDE_ASM(PAIR_IsStatus_BOY_PULL);

INCLUDE_ASM(PAIR_IsStatus_GIRL_PULL);

INCLUDE_ASM(PAIR_IsStatus_BOY_WAIT);

INCLUDE_ASM(PAIR_GetPosition_BOY_DITCH);

INCLUDE_ASM(PAIR_IsStatus_BOY_DITCH);

INCLUDE_ASM(ACTGame_isHangChain);

INCLUDE_ASM(ACTGame_isWeaponEnableCatchfire);

INCLUDE_ASM(ACTCheckCollis_WF);

INCLUDE_ASM(ACTCheckCollis_W);

INCLUDE_ASM(ACTCheckCollis_CI);

INCLUDE_ASM(ACTCheckCollis_WELL);

INCLUDE_ASM(ACTCheckCollis_WAY);

INCLUDE_ASM(ACTCheckViewCl);

INCLUDE_ASM(ACTGameView_FirstSet);

INCLUDE_ASM(ACTGameView_Add);

INCLUDE_ASM(ACTGameView_Check);

INCLUDE_ASM(ACTGameViewSimple_Check);

INCLUDE_ASM(ACTGame_GetMotOrientFromWeapon);

INCLUDE_ASM(ACTGame_NoWeapon);

INCLUDE_ASM(ACTGame_isWeaponCombustible);

INCLUDE_ASM(ACTGame_GetNearestGObj);

INCLUDE_ASM(ACTLookTarget_Init);

INCLUDE_ASM(_ACTLookTarget_Set);

INCLUDE_ASM(ACTParaStatus_Init);

INCLUDE_ASM(_ACTParaStatus_Set);

INCLUDE_ASM(_ACTParaStatus_Check);

INCLUDE_ASM(_ACTCharStatus_Init);

INCLUDE_ASM(_ACTCharStatus_Set);

INCLUDE_ASM(_ACTCharStatus_Check);

INCLUDE_ASM(_ACTCharStatus_Exec);

INCLUDE_ASM(_ACTSetEnemyDisappearSpeed);

INCLUDE_ASM(ACTGame_SetMotionPlaySpeedRatio_Reserve);

INCLUDE_ASM(_ACTGame_GetParamF);

INCLUDE_ASM(ACTGame_GetCurrentCallStatus);

INCLUDE_ASM(ACTGame_CheckPriInputFrame);

INCLUDE_ASM(ACTGame_SendSoundMail);

INCLUDE_ASM(ACTGame_LwsEffectInit);

INCLUDE_ASM(ACTGame_LwsEffect_Guard);

INCLUDE_ASM(ActGame_GetOrientQ);

INCLUDE_ASM(_GetRootObjectOrient);

INCLUDE_ASM(ACTItemForceDrop);

INCLUDE_ASM(GetOtherStageGirlOrient);

INCLUDE_ASM(ACTChkAttackIgnore_BOY);

INCLUDE_ASM(ACTChkAttackIgnore_GIRL);

INCLUDE_ASM(ACTChkAttackIgnore_ENEMY);

INCLUDE_ASM(ACTCheckCollis_VIEW);

INCLUDE_ASM(ACTCheckViewClDetail);

INCLUDE_ASM(ACTGame_SetMotionPlaySpeedRatio_Clear);

INCLUDE_ASM(ACTGame_SetMotionPlaySpeedRatio_Exec);
