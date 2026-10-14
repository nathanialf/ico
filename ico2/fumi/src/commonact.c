#include "enemy.h"
#include "enemy_act.h"
#include "isys.h"
#include <assert.h>
#include "camera-editor.h"
#include "ebrain.h"

/* prototypes: their order is the inline tail's emission order (gcc emits every
   inline at the end of the object in first-declaration order). They precede
   commonact.h, whose alphabetical list would otherwise fix that order. */
void ACTAcceptMail(GObj *self, int mail);
inline int _ACTMotDirSmzDirect(GObj *self, float *dir);
void WithMailFunc_Idling(GObj *self);
void WithMailFunc_BossDamaged(GObj *self);
void WithMailFunc_FallDead(GObj *self);
void actCommonRevive(GObj *volatile self);
void actCommonReviveAir(GObj *volatile self);
void actCommonPlay(GObj *volatile self);
void actCommonOne(GObj *volatile self);
void actCommonDelete(GObj *volatile self);
void actCommonCatchFire(GObj *volatile self);
void actCommonCatchFireBomb(GObj *volatile self);
void actCommonPutFire(GObj *volatile self);
void actCommonBoxReverbe(GObj *volatile self);
void actCommonItem(GObj *volatile self);
void actCommonClimb(GObj *volatile self);
void actCommonCliffdown(GObj *volatile self);
void actCommonLadderBellow(GObj *volatile self);
void actCommonLadderBellowHang(GObj *volatile self);
void actCommonEdge(GObj *volatile self);
void actCommonDodge(GObj *volatile self);
void actCommonDodgeJump(GObj *volatile self);
void actCommonGuard(GObj *volatile self);
void actCommonFallDamage(GObj *volatile self);
void actCommonDamage(GObj *volatile self);
void actCommonShoal(GObj *volatile self);
void actCommonSwim(GObj *volatile self);
void actCommonLever2(GObj *volatile self);
void actCommonRopeTouchWall(GObj *volatile self);
void actCommonRopeSwing(GObj *volatile self);
void actCommonRopeTurn(GObj *volatile self);
void actCommonRopeDownEnd(GObj *volatile self);
void actCommonRopeJump(GObj *volatile self);
void actCommonRopeJumpBefore(GObj *volatile self);
void actCommonRopeTurnSpecial(GObj *volatile self);
void actCommonRopeClimbEnd2(GObj *volatile self);
void actCommonCornered(GObj *volatile self);
void actCommonLookaround(GObj *volatile self);
void actCommonTurnWarn(GObj *volatile self);
void actCommonTurnStrict(GObj *volatile self);
void actCommonPPipe(GObj *volatile self);
void actCommonHandrail(GObj *volatile self);
void actCommonOneWall(GObj *volatile self);
void motCommonNull(GObj *volatile self);
void motCommonBoxPush(GObj *volatile self);
void motCommonBoxPull(GObj *volatile self);
void motCommonBarPush(GObj *volatile self);
void motCommonBarPull(GObj *volatile self);
void motCommonLadderUp(GObj *volatile self);
void motCommonLadderDown(GObj *volatile self);
void motCommonSlip(GObj *volatile self);
void motCommonRopejumpDircorrect(GObj *volatile self);
void motCommonHangNone(GObj *volatile self);
void motCommonHangWall(GObj *volatile self);
void motCommonHangCliff(GObj *volatile self);
void motCommonRopeTurnSpecialR(GObj *volatile self);
void motCommonRopeTurnSpecialL(GObj *volatile self);
void motCommonTruckLeverLoop(GObj *volatile self);
void motCommonTruckLeverPull(GObj *volatile self);
void motCommonTruckLeverPush(GObj *volatile self);
void funcCommonRopeBefore(GObj *self, int mail, GObj *chain);
void afterCommonRope(GObj *volatile self);
void extraCommonNull(GObj *volatile self);
void extraCommonCall(GObj *volatile self);
void funcCommonWayOn(GObj *self);
void funcCommonSofaWakeup(GObj *self);
int _ACTMotReqResult(GObj *self, int mot);
inline float *test_CURRENTORIENT(GObj *self);
inline float *test_CURRENTROOT(GObj *self);
void StartCorrectPosition(GObj *self, float *pos, float *dir, int mode, float t);
int IsCorrectPosition(GObj *self);
void ControlMotionOrient(int id, int mot);
int FloorIsTruck(GObj *self);
void _ACTMotDir_V(void *self, void *dir);
void ACTMotDirToWall(GObj *self);
void SetCorrectOrientOfChain(void *self);
void actAfterForceRope(GObj *volatile self);
inline void actAfterForceRopeSwing(GObj *volatile self);
static inline void actAfterRopeJump(GObj *volatile self);
static inline void afterCommonRopeCliff(char *self);
static inline void afterCommonRopeTurnSpecial(GObj *volatile self);
inline void actAfterDown(GObj *volatile self);
void afterCommonCling(volatile unsigned int self);
void actAfterSlip(int x);
inline void afterCommonRevive(volatile unsigned int self);
inline void afterCommonStone(GObj *volatile self);
inline void afterCommonBox(GObj *volatile self);
void afterCommonBar(GObj *volatile self);
static inline void actAfterJump(GObj *volatile self);
inline void actAfterFall(GObj *volatile self);
inline void actAfterFly(GObj *volatile self);
static inline void ClipCollisionWithField(ClipWork *work);
inline void afterCommonOneWall(int x);
int ACTCheckFlagAttack(GObj *self);
static inline void afterCommonBecarry(GObj *volatile self);
inline void afterCommonTruckLever(GObj *volatile self);

#include "commonact.h"
#include "debug.h"
#include "gobj.h"
#include "obj_manager.h"
#include "act-env.h"
#include "act.h"
#include "boyact.h"
#include "girl_act.h"
#include "brain.h"
#include "mail-add-data.h"
#include "gflag.h"
#include "Matrix.h"
#include "Primitive.h"
#include "boy.h"
#include "cage.h"
#include "darkVolume.h"
#include "lineManager.h"
#include "motionOrientManager.h"
#include "rotObject.h"
#include "torch.h"
#include <libvu0.h>
#include "geometryManager.h"
#include "typedef.h"
#include "act-game.h"
#include "matrixDrive.h"
#include "sugiCommon.h"
#include "layout_action.h"
#include "script.h"
#include "motionFileManager.h"
#include "GifPacket.h"
#include "st25a.h"
#include <string.h>
#include "gamesys.h"
#include "generator.h"
#include "debug_exception.h"
#include "gv.h"
#include "box.h"
#include "quaternion.h"
#include "main.h"
#include "fieldCollision.h"
#include "chain.h"
#include "motionManager2.h"
#include "weapon.h"
#include "act-way.h"
#include "pad.h"
#include "s_init.h"
#include "clipCollisionManager.h"
#include "layout_texture.h"
#include "flyManager.h"
#include "include_asm.h"

static void DamageFunc(GObj *self);
static void TestCageUpDown(GObj *cage, GObj *gobj);

typedef struct { /* field names derived */
    int a, b, c;
} Blob12; /* derived name */

typedef struct { /* field names derived */
    int w[6];
} SlowrunRec; /* derived name */

void ACTSetPositionWithFitting(void *self, float *pos)
{
    SetDirectRootPosition(self, pos);
}

static void ACTSetPositionNoFitting(void *self, float *pos)
{
    SetDirectRootPositionNoFitting(self, pos);
}

void ACTSetPositionNodeWithFitting(void *self, int node, float *pos, float t)
{
    SetDirectRootPositionWithNodePoint(self, node, pos, t);
}

static int ChangeMailInLadder(GObj *self, int mail)
{
    float p[4];
    float q[4];
    Act *s = GOBJ_ACT(self);
    int ret = mail;
    int flag = 0;
    float lim1;
    float lim2;

    if (boyGObj != 0 && girlGObj != 0) {
        if (self == boyGObj) {
            if (s->actMode == 38) {
                flag = (GOBJ_ACT(girlGObj)->actMode == 38);
            }
        }
        if (self == girlGObj) {
            if (s->actMode == 38) {
                flag = 1;
            }
        }
        if (flag != 0 &&
            _DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 3600.0f) {
            lim1 = self == boyGObj ? 175.0f : 225.0f;
            lim2 = self == boyGObj ? 175.0f : 210.0f;
            if (self == boyGObj) {
                p[0] = test_CURRENTROOT(self)[0];
                p[1] = test_CURRENTROOT(boyGObj)[1];
                p[2] = test_CURRENTROOT(boyGObj)[2];
                q[0] = test_CURRENTROOT(girlGObj)[0];
                q[1] = test_CURRENTROOT(girlGObj)[1];
                q[2] = test_CURRENTROOT(girlGObj)[2];
            } else {
                p[0] = test_CURRENTROOT(girlGObj)[0];
                p[1] = test_CURRENTROOT(girlGObj)[1];
                p[2] = test_CURRENTROOT(girlGObj)[2];
                q[0] = test_CURRENTROOT(boyGObj)[0];
                q[1] = test_CURRENTROOT(boyGObj)[1];
                q[2] = test_CURRENTROOT(boyGObj)[2];
            }
            switch (mail) {
            case 0x14A:
                if (q[1] < p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < lim2) {
                    s->flags18.ll |= (1ULL << 36);
                    ret = 0x150;
                }
                break;
            case 0x14B:
                if (q[1] > p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < lim1) {
                    s->flags18.ll |= (1ULL << 37);
                    ret = 0x150;
                }
                break;
            }
        }
    }
    return ret;
}

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* a static inline used only by _ACTCorrectMsg */
static inline int GetHitDirIdx(GObj *self) /* derived name */
{
    float *p = GOBJ_ACT(self)->attackDir;
    int a = _RotyGV(test_CURRENTORIENT(self), p);

    if (-45 <= a && a <= 45) {
        return 0;
    }
    if (a < -134 || 134 < a) {
        return 1;
    }
    if (46 <= a && a <= 134) {
        return 2;
    }
    if (-134 <= a) {
        if (a <= -46) {
            return 3;
        }
    }
    return 0;
}

INCLUDE_ASM(_ACTCorrectMsg);

/* the motion each interrupt kind requests, indexed by the kind */
static int intrMotion[432] = {
    0,   0,   0,   0,   0,   0,   117, 117, 61,  0,   1,   0,   0,   0,   0,   222, 223, 0,   0,
    0,   84,  85,  0,   164, 119, 168, 172, 1,   20,  22,  23,  0,   0,   0,   136, 0,   -1,  -1,
    148, 270, -1,  126, 125, 165, 166, 0,   0,   0,   121, 120, 152, 153, 154, 266, 267, 149, 149,
    4,   1,   4,   5,   0,   0,   0,   0,   63,  64,  65,  0,   0,   0,   1,   0,   1,   0,   114,
    13,  8,   1,   105, 1,   0,   104, 115, 116, 16,  14,  1,   112, 113, 94,  101, 1,   0,   0,
    0,   1,   1,   0,   0,   0,   1,   1,   0,   0,   0,   1,   0,   0,   21,  136, 137, 138, 0,
    68,  69,  70,  1,   87,  88,  87,  167, 167, 71,  72,  73,  74,  75,  77,  76,  78,  79,  79,
    81,  80,  127, 128, 129, 130, 126, 123, 124, 131, 117, 126, 155, 155, 85,  203, 204, 205, 206,
    207, 158, 157, 129, 130, 208, 210, 209, 212, 211, 201, 164, 202, 213, 214, 215, 83,  82,  0,
    0,   164, 0,   84,  213, 207, 216, 0,   6,   7,   8,   9,   10,  14,  15,  13,  16,  19,  24,
    25,  27,  27,  26,  28,  29,  30,  186, 1,   1,   2,   40,  41,  12,  1,   43,  43,  44,  51,
    50,  50,  52,  49,  48,  118, 148, 174, 8,   0,   172, 1,   173, 174, 166, 57,  58,  118, 200,
    89,  260, 53,  223, 222, 225, 224, 225, 224, 223, 222, 13,  8,   226, 223, 222, 226, 226, 0,
    66,  67,  1,   13,  1,   0,   261, 118, 0,   0,   0,   270, 270, 263, 31,  270, 11,  12,  11,
    1,   8,   1,   0,   218, 219, 220, 221, 32,  33,  34,  35,  36,  37,  38,  39,  139, 139, 140,
    150, 151, 141, 142, 143, 144, 146, 147, 148, 0,   61,  59,  54,  55,  56,  62,  155, 156, 131,
    169, 170, 61,  61,  132, 133, 134, 135, 61,  117, 117, 122, 118, 94,  95,  96,  95,  97,  98,
    99,  90,  59,  60,  91,  92,  93,  158, 159, 160, 161, 162, 163, 164, 0,   0,   0,   271, 272,
    245, 246, 243, 192, 193, 194, 195, 198, 198, 197, 196, 199, 227, 236, 237, 228, 229, 230, 231,
    232, 233, 229, 240, 8,   1,   241, 247, 248, 248, 249, 250, 251, 252, 253, 255, 256, 175, 176,
    177, 175, 176, 177, 178, 179, 179, 180, 180, 0,   0,   181, 182, 183, 184, 185, 105, 187, 1,
    188, 189, 190, 191, 189, 118, 1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   17,  18,  262, 0,   0,   0}; /* derived name */

int ACTGetOrientFromIntrK(GObj *self, int k, MotOriReq *out, int arg)
{
    Act *s = GOBJ_ACT(self);
    MotOriTarget tmp;
    int ret = intrMotion[k];

    *out = s->env.motOriReq;
    switch (k) {
    case 140:
        out->b = GOBJ_WORK(self)->cliffReq.b;
        break;
    case 305:
        out->a = GOBJ_WORK(self)->cliffReq.a;
        break;
    case 298:
        *(char **)((char *)s + 0x30) = GetMailAdditionalData(self, arg);
        tmp = *(MotOriTarget *)(*(char **)((char *)GOBJ_ACT(self) + 0x30));
        out->b = s->env.motOriReq.b = tmp;
        break;
    case 54:
        *(char **)((char *)s + 0x30) = GetMailAdditionalData(self, arg);
        tmp = *(MotOriTarget *)(*(char **)((char *)GOBJ_ACT(self) + 0x30));
        out->a = out->b = s->env.motOriReq.a = s->env.motOriReq.b = tmp;
        s->env.sofaObj.obj = tmp.obj;
        GetSofaPosition(self, s->env.sofaObj.obj);
        break;
    case 145:
        out->a = GOBJ_WORK(self)->bellowWall3000;
        break;
    case 144:
        out->a = GOBJ_WORK(self)->bellowWall400;
        break;
    case 114:
    case 115:
    case 116:
    case 117:
        out->b = s->env.motOriReq.a;
        break;
    case 45:
        return GOBJ_ACT(self)->enemy->jumpOrient;
    case 63:
        if (s->actMode == 74) {
            ret = 272;
        }
        break;
    case 378:
    case 379:
    case 380:
        out->b = out->a = s->env.cliffContact.b;
        break;
    case 381:
        *out = s->env.cliffContact = GOBJ_ACT(boyGObj)->env.cliffContact;
        break;
    case 382:
    case 383:
    case 384:
        *out = s->env.cliffContact;
        break;
    case 385:
    case 386:
        *out = s->env.supportReq;
        s->env.motOriReq = *out;
        break;
    case 205:
    case 206:
    case 207:
        if (self == boyGObj) {
            if (ACTGame_NoWeapon(self)) {
                ret = 42;
            } else {
                ret = ACTGame_GetMotOrientFromWeapon(s->weapon);
            }
        }
        break;
    case 72:
    case 74:
    case 338:
        ret = s->orientMot;
        break;
    case 81:
        ret = s->orientMot;
        out->a = GOBJ_ACT(boyGObj)->env.motOriReq.b;
        s->env.motOriReq = *out;
        break;
    case 89:
    case 399:
    case 403:
        out->a = GOBJ_ACT(boyGObj)->env.motOriReq.b;
        s->env.motOriReq = *out;
        break;
    case 416:
        ret = 0;
        if (s->soundMot != 0 && !((int)(s->flags20.ll >> 13) & 1)) {
            ret = s->soundMot;
            s->soundMot = 0;
        }
        break;
    case 152:
    case 155:
    case 156:
        out->a = *(MotOriTarget *)&GOBJ_ACT(self)->enemy->climbCol;
        break;
    default:
        ret = intrMotion[k];
        break;
    }
    return ret;
}

INCLUDE_ASM(ACTRunIntrCorrect);

void WithMailFunc_WayBeginPosError(void *self)
{
    /* disabled in retail: the way-begin-position (WBP) report */
    if (0) {
        debug_StdPrintfDummy("WBP set [with mail]\n");
    }
    ACTWay_SetBeginPositionIllegal(self);
}

void WithMailFunc_AttackFail(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    char *p = (char *)s->intrData;
    int v = p != 0 ? *(int *)p : s->env.wallWord;
    if (self == boyGObj) {
        GObj *t = s->weapon;
        if (t != 0) {
            GOBJ_SUB(t)->ctrl.wallAttr = v;
            ExecWeaponHitReaction(t);
        }
    }
}

INCLUDE_ASM(WithMailFunc_AttackRejectInQueen);

void GetCorrectOrientOfChain(void *buf, void *obj)
{
    float q[4];
    int deg;

    if (GetChainDirCorrectVal(GOBJ_ACT(obj)->chain, &deg) != 0) {
        memset(q, 0, 16);
        q[2] = 1.0f;
        _ApplyRyGV(q, (float)RoundDegGV(
                          deg + AlignDegGV(RoundDegGV((int)(_GetDirection(test_CURRENTORIENT(obj)) /
                                                            3.1415927f * 180.0f) -
                                                      deg))) *
                          3.1415927f / 180.0f);
        ((float *)buf)[0] = q[0];
        ((float *)buf)[1] = q[1];
        ((float *)buf)[2] = q[2];
    } else {
        ((float *)buf)[0] = *(float *)((char *)test_CURRENTORIENT(obj) + 0);
        ((float *)buf)[1] = *(float *)((char *)test_CURRENTORIENT(obj) + 4);
        ((float *)buf)[2] = *(float *)((char *)test_CURRENTORIENT(obj) + 8);
    }
}

static int CollisCheckInRope(void *self, GObj *chain)
{
    /* whether p is a box (kind 0x11), as a char */
    inline char ropeWallIsBox(char *p) /* derived name */
    {
        if (p != 0 && *(int *)(p + 0xC) == 0x11) {
            return 1;
        }
        return 0;
    }

    ClipWork work;
    float mid[4];
    float p[4];
    float dir[4];
    float tmp[4];
    float n51[4];
    float n47[4];
    int rv = 0;

    sceVu0ScaleVector(dir, test_CURRENTORIENT(self), 15.0f);
    GetSkeltonPosition(n51, self, 51);
    GetSkeltonPosition(n47, self, 47);
    sceVu0AddVector(mid, n51, n47);
    sceVu0ScaleVector(mid, mid, 0.5f);
    p[0] = mid[0];
    p[2] = mid[2];
    p[1] = mid[1] + 10.0f;
    sceVu0ScaleVector(tmp, dir, -1.0f);
    sceVu0AddVector(work.pt[0], p, tmp);
    sceVu0ScaleVector(tmp, dir, 1.0f);
    sceVu0AddVector(work.pt[1], p, tmp);
    work.radius = 10.0f;
    ClipWall(&work);
    if (work.wall.elem != 0) {
        if (ropeWallIsBox((char *)work.wall.o.obj))
            rv = 2;
        else
            rv = 1;
    } else {
        SwapGV(work.pt[0], work.pt[1]);
        ClipWall(&work);
        if (work.wall.elem != 0) {
            if (ropeWallIsBox((char *)work.wall.o.obj))
                rv = 2;
            else
                rv = 1;
        }
    }
    return rv;
}

static inline int chainFloorHit(GObj *self, ClipWork *w) /* derived name */
{
    if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 4) & 1) {
        GetSkeltonPosition(w->pt[0], self, 44);
        GetSkeltonPosition(w->pt[1], self, 51);
        w->pt[1][1] -= 5.0f;
        ClipFloor(w);
        if (w->floor.elem != 0) {
            return 1;
        }
    }
    return 0;
}

void actCommonRope(GObj *volatile self)
{
    Act *s;
    float dir[4];
    float ori[4];
    float hand[4];
    ClipWork work;
    int step;
    int nsteps;
    int total;
    int roty;

    nsteps = ((60 - systemStatus[0] * 10) / systemStatus[1]) / 3;
    total = nsteps;
    step = -1;
    s = GOBJ_ACT(self);
    GetCorrectOrientOfChain(dir, (void *)self);
    ori[0] = *(float *)((char *)test_CURRENTORIENT(self) + 0);
    ori[1] = *(float *)((char *)test_CURRENTORIENT(self) + 4);
    ori[2] = *(float *)((char *)test_CURRENTORIENT(self) + 8);
    roty = _RotyGV(dir, ori);
    if ((int)s->after == 0) {
        GetRootPositionHandExtra(self, hand);
        step = 0;
        HoldChain(s->chain, self, hand);
    }
    s->after = afterCommonRope;
    *(int *)((char *)s + 0x18) = (int)actAfterForceRope;
    LockChainGeo(s->chain);
    _ACTWait(1);
    debug_StdPrintfDummy("enter actCommonRope\n");
    while (1) {
        UnLockChainGeo(s->chain);
        ChainGeo(s->chain);
        LockChainGeo(s->chain);
        switch (CollisCheckInRope((void *)self, s->chain)) {
        case 1:
            ACTSendMailCorrect(self, 0xA8);
            break;
        case 2:
            ACTSendMailCorrect(self, 0xA7);
            break;
        }
        if (chainFloorHit(self, &work)) {
            ACTSendMailCorrect(self, 0xA9);
        }
        if (step >= 0) {
            if (step == nsteps) {
                SetMotionDirection(self, dir);
            } else if (step < nsteps) {
                work.pt[0][0] = ori[0];
                work.pt[0][1] = ori[1];
                work.pt[0][2] = ori[2];
                _ApplyRyGV(work.pt[0], (float)(roty * step / total) * 3.1415927f / 180.0f);
                SetMotionDirection(self, work.pt[0]);
            }
            step++;
        }
        if (CheckChainClimbablePos(s->chain)) {
            GetChainClimbOrient(GOBJ_ACT(self)->enemy->climbOrient, s->chain);
            GetRootPosition(GOBJ_ACT(self)->enemy->climbPos, (void *)s->chain);
            GetChainClimbCollision(&GOBJ_ACT(self)->enemy->climbCol, s->chain);
            GOBJ_ACT(self)->enemy->climbObj = s->chain;
            ActSendMail_WithAdditionalData(self, 0x98, (void *)self,
                                           *(char **)(*(char **)((char *)self + 0x164) + 0x680) +
                                               0x330);
        }
        _ACTWait(1);
    }
}

/* the turn to the chain's corrected orient, which SetCorrectOrientOfChain
   and the rope turns inline */
static inline void setCorrectOrientOfChain(void *self) /* derived name */
{
    float local[4];
    GetCorrectOrientOfChain(local, self);
    SetMotionDirection(self, local);
}

void motCommonRopeTurnR(GObj *volatile self)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(self)) / 3.1415927f * 180.0f);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        i++;
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base + deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)self), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(self, dir);
        deg += 5;
        if (i % wait == 0) {
            setCorrectOrientOfChain((void *)self);
            ACTSendMailCorrect(self, 0x150);
        }
        _ACTWait(1);
    }
}

void motCommonRopeTurnL(GObj *volatile self)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(self)) / 3.1415927f * 180.0f);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        i++;
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base - deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)self), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(self, dir);
        deg += 5;
        if (i % wait == 0) {
            setCorrectOrientOfChain((void *)self);
            ACTSendMailCorrect(self, 0x150);
        }
        _ACTWait(1);
    }
}

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} ClimbVec4; /* derived name */

typedef struct { /* field names derived */
    sceVu0FVECTOR v0;
    float v1[4];
    ClimbCol climbCol; /* the wall the climb held */
    GObj *obj;         /* the chain or cage climbed */
} ClimbEndRec;         /* derived name */

void actCommonRopeClimbEnd1(GObj *volatile self)
{
    ClimbEndRec c;
    ClimbVec4 dir;
    float pos[4];
    float ori[4];
    float hand[4];
    float foot[4];
    float base[4];
    int flag;
    int step = 5;
    int isCage;
    int i;
    long back;
    int n;
    int r;

    c = *(ClimbEndRec *)(char *)GOBJ_ACT(self)->intrData;
    isCage = c.obj->kind == 44;
    flag = 0;
    GOBJ_SUB(boyGObj)->root.ropeState = 0;
    dir.f[0] = c.v0[0];
    dir.f[1] = c.v0[1];
    dir.f[2] = c.v0[2];
    sceVu0ScaleVector(&dir, &dir, -1.0f);
    if (_AbsRotyGV(&dir, test_CURRENTORIENT(self)) < 10) {
        flag = 1;
    } else {
        back = -5;
        while (1) {
            if (isCage) {
                TestCageUpDown(c.obj, (void *)self);
            }
            if (GOBJ_SUB(self)->ctrl.motion == 118) {
                break;
            }
            _ACTWait(1);
        }
        i = 0;
        r = _RotyGV(dir.f, test_CURRENTORIENT(self));
        step = (r > -1) ? step : back;
        n = r / step;
        n = (n < 0) ? -n : n;
        GetSkeltonPosition(pos, self, 22);
        pos[0] = c.v1[0];
        pos[2] = c.v1[2];
        while (i < n) {
            i++;
            ori[0] = *(float *)((char *)test_CURRENTORIENT(self) + 0);
            ori[1] = *(float *)((char *)test_CURRENTORIENT(self) + 4);
            ori[2] = *(float *)((char *)test_CURRENTORIENT(self) + 8);
            _ApplyRyGV(ori, (float)step * 3.1415927f / 180.0f);
            SetMotionDirection(self, ori);
            if (0 < step) {
                ACTSendMailCorrect(self, 0xA0);
            } else {
                ACTSendMailCorrect(self, 0xA1);
            }
            SetChainRootUpdateMode(self, 3, pos);
            _ACTWait(1);
        }
        if (GOBJ_SUB(self)->ctrl.motion != 118) {
            do {
                ACTSendMailCorrect(self, 0x150);
                _ACTWait(1);
            } while (GOBJ_SUB(self)->ctrl.motion != 118);
        }
    }
    SetMotionDirection(self, dir.f);
    while (1) {
        ACTSendMailCorrect(self, 0x99);
        if (flag) {
            ACTSendMailCorrect(self, 0x9A);
        }
        GetSkeltonPosition(hand, self, 22);
        GetSkeltonPosition(foot, self, 6);
        base[0] = c.v1[0];
        base[1] = c.v1[1];
        base[2] = c.v1[2];
        if (isCage) {
            TestCageUpDown(c.obj, (void *)self);
        }
        GOBJ_ACT(self)->enemy->climbCol = c.climbCol;
        if (hand[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(self, 0x9B);
        }
        if (foot[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(self, 0x9C);
        }
        _ACTWait(1);
    }
}

typedef union { /* field names derived */
    char *p;
    float *f;
} CagePtr; /* derived name */

void actCommonRopeCliff(GObj *volatile self)
{
    float dst[4];
    float root[4];
    float cur[4];
    float p[4];
    Act *s = GOBJ_ACT(self);
    int n = ((60 - systemStatus[0] * 10) / systemStatus[1]) / 2;
    float y;
    int i = 0;

    s->flags18.afterProc = afterCommonRopeCliff;
    ((CagePtr *)(((CagePtr *)((char *)boyGObj + 0x15C))->p + 0x420))->p = 0;
    dst[0] = GOBJ_ACT(self)->enemy->ropeCliffX;
    dst[1] = GOBJ_ACT(self)->enemy->ropeCliffY;
    dst[2] = GOBJ_ACT(self)->enemy->ropeCliffZ;
    GetRootPosition(root, (void *)self);
    while (1) {
        i++;
        if (i <= n) {
            _InterGV(cur, root, dst, (float)i, (float)(n - i));
            SetDirectRootPositionNoFitting((void *)self, cur);
        }
        if (GOBJ_SUB(self)->ctrl.motion == 118) {
            y = test_CURRENTROOT((void *)self)[1];
            SetChainRootUpdateMode(boyGObj, 3, (float *)((char *)GOBJ_ACT(self)->enemy + 0x1D0));
            p[0] = test_CURRENTROOT((void *)self)[0];
            p[1] = test_CURRENTROOT((void *)self)[1];
            p[2] = test_CURRENTROOT((void *)self)[2];
            p[1] = y + 5.0f;
            SetDirectRootPositionNoFitting((void *)self, p);
        }
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    float a[4];
    float b[4];
    int cnt;
    int lim;
    int last;
} CageUD; /* derived name */

/* the cage up-down interpolation record TestCageUpDown keeps between frames
   (start, goal, frame count, limit, last motion) */
static CageUD cageUpDown = {
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0, 0, -1}; /* derived name */

static void TestCageUpDown(GObj *cage, GObj *gobj)
{
    inline void initCage(GObj * o) /* derived name */
    {
        int n;

        cageUpDown.cnt = 0;
        cageUpDown.lim = (float)*motionTable[*(int *)(((CagePtr *)&o->dobj)->p + 0x4A0)];
        n = GetSkeltonFocusNode(o, 35);
        cageUpDown.a[0] = *(float *)(*(char **)(((CagePtr *)&o->dobj)->p + 0xC) + n * 0x40 + 0x30);
        cageUpDown.a[1] = *(float *)(*(char **)(((CagePtr *)&o->dobj)->p + 0xC) + n * 0x40 + 0x34);
        cageUpDown.a[2] = *(float *)(*(char **)(((CagePtr *)&o->dobj)->p + 0xC) + n * 0x40 + 0x38);
        cageUpDown.b[0] = cageUpDown.a[0];
        cageUpDown.b[2] = cageUpDown.a[2];
        cageUpDown.b[1] = cageUpDown.a[1] + 200.0f;
    }

    inline void cageMove(GObj * o, float *dst, float *lo, float *hi, float *res, float x, float y,
                         float z) /* derived name */
    {
        dst[0] = x;
        dst[1] = y;
        dst[2] = z;
        GetCageChainPoint(lo, hi, cage);
        _InterGV(dst, lo, hi, dst[1] - lo[1], hi[1] - dst[1]);
        sceVu0ScaleVector(res, test_CURRENTORIENT(o), -20.0f);
        sceVu0AddVector(res, dst, res);
        ACTSetPositionNodeWithFitting(o, 0x23, res, 1.0f);
    }

    inline void putRoot(float *pos, float *lo, float *hi, int clamp) /* derived name */
    {
        float lim;
        float low;
        float d;

        lim = 50.0f;
        if (stage_no == 8) {
            lim = 80.0f;
        }
        pos[0] = test_CURRENTROOT(gobj)[0];
        pos[1] = test_CURRENTROOT(gobj)[1];
        pos[2] = test_CURRENTROOT(gobj)[2];
        low = lo[1] + lim;
        d = ((CagePtr *)((char *)gobj + 0x15C))->f[81];
        pos[1] = pos[1] + d;
        if (clamp) {
            pos[1] = pos[1] < low ? low : (hi[1] < pos[1] ? hi[1] : pos[1]);
        }
        SetDirectRootPositionNoFitting(boyGObj, pos);
    }

    inline void chainUpdate(float *sk, float *out, float *lo, float *hi) /* derived name */
    {
        GetSkeltonPosition(sk, gobj, 22);
        _InterGV(out, lo, hi, sk[1] - lo[1], hi[1] - sk[1]);
        SetChainRootUpdateMode(gobj, 2, out);
    }

    float vA[4];
    float vB[4];
    float vC[4];
    float vD[4];
    float vE[4];
    float vF[4];
    float vG[4];
    float vH[4];
    int mot = *(int *)(((CagePtr *)((char *)gobj + 0x15C))->p + 0x4A0);

    GetCageChainPoint(vB, vC, cage);
    *(int *)(((CagePtr *)((char *)boyGObj + 0x15C))->p + 0x420) = 0;
    switch (mot) {
    case 0x78:
        putRoot(vE, vB, vC, 1);
        chainUpdate(vG, vH, vB, vC);
        break;
    case 0x77:
        if (GOBJ_ACT(gobj)->actMode == 63) {
            putRoot(vE, vB, vC, 0);
            chainUpdate(vE, vF, vB, vC);
        } else {
            putRoot(vE, vB, vC, 1);
            chainUpdate(vE, vF, vB, vC);
        }
        break;
    case 0x79:
    case 0x7A:
        if (cageUpDown.last != mot) {
            initCage(gobj);
        }
        _InterGV(vA, cageUpDown.a, cageUpDown.b, (float)cageUpDown.cnt,
                 (float)(cageUpDown.lim - cageUpDown.cnt));
        vA[1] = vA[1] < vB[1] ? vB[1] : (vC[1] < vA[1] ? vC[1] : vA[1]);
        cageMove(gobj, vF, vG, vH, vE, vA[0], vA[1], vA[2]);
        cageUpDown.cnt = cageUpDown.cnt + 1;
        chainUpdate(vE, vF, vB, vC);
        break;
    default:
        if (cageUpDown.last != mot) {
            GetSkeltonPosition((float *)((char *)GOBJ_ACT(gobj)->work + 0x410), gobj, 22);
        }
        _InterGV(vD, vB, vC, GOBJ_WORK(gobj)->handPosY - vB[1], vC[1] - GOBJ_WORK(gobj)->handPosY);
        SetChainRootUpdateMode(gobj, 3, vD);
        break;
    }
    cageUpDown.last = mot;
}

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} RsVec4; /* derived name */

static inline unsigned char ropeSpecialWallHit(RsVec4 *p1, ClimbCol *hit) /* derived name */
{
    sceVu0FVECTOR va = {0.0f, 0.0f, -20.0f, 1.0f};
    sceVu0FVECTOR vb = {0.0f, 0.0f, 20.0f, 1.0f};
    ClipWork work;
    int i;

    for (i = 0; i < 4; i++) {
        sceVu0UnitMatrix((void *)MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(p1->f[0], p1->f[1] + 0.0f, p1->f[2]);
        MatrixDrive_RotMatrixY((short)((float)i * 0.7853982f * 32768.0f / 3.1415927f));
        sceVu0ApplyMatrix(work.pt[0], (void *)MatrixDrive_GetMatrix(), va);
        sceVu0ApplyMatrix(work.pt[1], (void *)MatrixDrive_GetMatrix(), vb);
        ClipWall(&work);
        if (work.wall.elem != 0) {
            hit->wallSrc = work.wall.o;
            hit->wall = work.wall.elem;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM(actCommonRopeSpecial);

static void lever_nego1(GObj *self, GObj *lev)
{
    int m = lev->kind;
    if (m < 22) {
        return;
    }
    if (m < 24) {
        goto lever;
    }
    if (m >= 26) {
        return;
    }
    SetWallLeverWithNodePoint(lev, self, 0x16);
    return;
lever:
    SetFloorLeverWithNodePoint(lev, self, 0x16);
}

static void SetDirectRootPositionXZ(void *self, void *pos)
{
    void *ret = test_CURRENTROOT(self);
    *(float *)((char *)pos + 4) = *(float *)((char *)ret + 4);
    SetDirectRootPositionNoFitting(self, pos);
}

/* the turn away from the wall, which ACTMotDirToWall and the lever, box,
   bar and truck functions inline */
static inline void actMotDirToWall(GObj *self) /* derived name */
{
    float local[4];
    sceVu0ScaleVector(local, *(char **)((char *)self + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(self, local);
}

static inline void correctLeverHoldPoint(GObj *self, GObj *lev) /* derived name */
{
    float w[4];
    if (lev->kind >= 22) {
        if (lev->kind < 24) {
            GetFloorLeverGlobalHoldPoint(w, lev);
        } else if (lev->kind < 26) {
            GetWallLeverGlobalHoldPoint(w, lev);
            debug_StdPrintfDummy("%f, %f, %f\n", w[0], w[1], w[2]);
        }
    }
    SetDirectRootPositionNoFittingWithNodePointXZ(self, 0x16, w, 0.2f);
}

void actCommonLever(GObj *volatile self)
{
    float p[4];
    Act *s = GOBJ_ACT(self);
    GObj *lev = s->env.pullObj;

    GOBJ_WORK(self)->leverTimer = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 5;
    p[0] = s->env.pullPos[0];
    p[1] = s->env.pullPos[1];
    p[2] = s->env.pullPos[2];
    p[1] = test_CURRENTROOT((void *)self)[1];
    SetDirectRootPositionNoFittingWithNodePointXZ((void *)self, 0x2C, s->env.pullPos, 1.0f);
    actMotDirToWall(self);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(self)->ctrl.frameFlag2 != 0) {
                correctLeverHoldPoint((void *)self, lev);
            }
            if (GOBJ_SUB(self)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)self, lev);
            }
        }
        _ACTWait(1);
    }
}

static void EBRAIN_SEND_MES(void *enemy, int mes)
{
    if (enemy && *(int *)((char *)enemy + 0xC) == 4)
        eBrainSendMes(enemy, mes);
}

static void DamageFunc(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    debug_StdPrintfDummy("damage\n");
    if (self != girlGObj) {
        s->life -= (float)GOBJ_ACT(self)->damage;
    }
    if (self->kind == 4) {
        EnemyBattleWork *b;
        EBRAIN_SEND_MES(self, 5);
        b = GOBJ_ACT(self)->enemy;
        EnemyDeleteParticle(self, b->hitDir, b->hitNodes);
    }
}

static void DownFunc(GObj *self)
{
    DamageFunc(self);
    if (self->kind == 1) {
        EBRAIN_SEND_MES((void *)GOBJ_ACT(self)->attacker, 6);
    }
}

void actCommonDown(GObj *volatile self)
{
    float v[4];
    Act *s = GOBJ_ACT(self);
    int notDamage = s->intrKind != 55 && s->intrKind != 56;

    debug_StdPrintfDummy("enter actCommonDown\n");
    *(int *)((char *)s + 0x18) = (int)actAfterDown;
    if (notDamage) {
        if (self == boyGObj) {
            brainAddLevelGirl(1000.0f);
        }
        if (self == girlGObj) {
            sceVu0ScaleVector(v, GOBJ_ACT(self)->attackDir, -1.0f);
            SetMotionDirection(self, v);
        } else {
            SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
        }
        DownFunc(self);
    }
    GOBJ_ACT(self)->enemy->liftLevel = 16;
    while (1) {
        if (self->kind != 4) {
            GOBJ_ACT(self)->hit = 1;
        }
        ACTSendMailCorrect(self, 0xC7);
        if (GOBJ_ACT(self)->enemy->liftLevel <= 0) {
            ACTSendMailCorrect(self, 0x124);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(actCommonDie);

void actCommonCling(GObj *volatile self)
{
    int no;
    int tgt;

    int Cling(int idx, int target)
    {
        float q[4];
        ClingRec *r;
        int i;
        int v;

        r = &clingData[idx];
        memset(q, 0, 16);
        q[3] = 1.0f;
        if (!((unsigned int)idx < 15)) {
            debug_assert("src/commonact.c", 2733);
            __assert("src/commonact.c", 2733,
                     "index>=ClingDataID_cling_start && index<ClingDataID_cling_end");
        }
        for (i = 0; i < 3; i++) {
            v = (r->rot[i] << 15) / 180;
            if (v != 0) {
                switch (i) {
                case 0:
                    RotQuaternionX(q, v);
                    break;
                case 1:
                    RotQuaternionY(q, v);
                    break;
                case 2:
                    RotQuaternionZ(q, v);
                    break;
                }
            }
        }
        SetMotionNodeFixModeParameter((void *)self, (void *)target, r->mode, r->node, q, r->pos[0],
                                      r->pos[1], r->pos[2], 1.0f);
        return r->motion;
    }

    no = (int)(_GetRandom() * 10.0f) % 15;
    tgt = GOBJ_ACT(self)->enemy->clingReq;

    GOBJ_ACT(self)->enemy->clingTarget = tgt;
    ACTGameCollisionOff(self);
    Cling(no, tgt);
    _ACTWait(0);
}

void actCommonSlip(GObj *volatile self)
{
    float dir[4];
    float v2[4];
    float v3[4];

    if (*(unsigned char *)((char *)GOBJ_ACT(self)->enemy + 0x280) == 0) {
        dir[0] = GOBJ_ACT(self)->enemy->slipDirX;
        dir[1] = GOBJ_ACT(self)->enemy->slipDirY;
        dir[2] = GOBJ_ACT(self)->enemy->slipDirZ;
    } else {
        sceVu0ScaleVector(dir, (float *)((char *)GOBJ_ACT(self)->enemy + 0x270), -1.0f);
    }
    v2[0] = GOBJ_ACT(self)->enemy->slipDirX;
    v2[1] = GOBJ_ACT(self)->enemy->slipDirY;
    v2[2] = GOBJ_ACT(self)->enemy->slipDirZ;
    sceVu0ScaleVector(v3, (float *)((char *)GOBJ_ACT(self)->enemy + 0x270), 30.0f);
    v3[1] = -20.0f;
    while (1) {
        SetMotionDirectionSmooze(self, dir, 3.0f);
        _ACTWait(1);
    }
}

void actCommonStoneDead(GObj *volatile self)
{
    float center[4];
    float dir[4];
    Act *s = GOBJ_ACT(self);

    if (s->intrKind == 34) {
        SetBoyStonizedVisual(self);
        GetGameOverEffectCenterPosition(center);
        _OrientXZGV(dir, center, test_CURRENTROOT((void *)self));
        SetMotionDirection(self, dir);
    } else {
        ACTSetPositionWithFitting((void *)self, test_CURRENTROOT((void *)self));
        SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
        self->drawMask = 0;
    }
    enable_game_pause = 0;
    scpBoyControlReadDisable = 1;
    _ACTWait(300);
    ACT_LAYOUT_GAMEOVER();
    _ACTWait(0);
}

typedef struct { /* field names derived */
    char pad0[20];
    int f14;
} ReviveSub; /* derived name */

typedef struct { /* field names derived */
    char pad0[20];
    int f14;
    char pad18[52];
    int f4C;
} StoneSub; /* derived name */

void actCommonStone(GObj *volatile self)
{
    StoneSub *s = (StoneSub *)(char *)GOBJ_ACT(self);

    s->f14 = (int)afterCommonStone;
    *(int *)(*(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A0) = 0;
    while (1) {
        if (debug_font_flag & 1) {
            debug_Printf(10, 170, 0xFFFFFFF, "count =(%d)\n", GOBJ_ACT(self)->enemy->liftLevel);
        }
        if (debug_font_flag & 1) {
            debug_Printf(10, 180, 0xFFFFFFF, "level =(%d)\n", GOBJ_ACT(self)->enemy->stoneLevel);
        }
        switch (GOBJ_ACT(self)->enemy->stoneLevel) {
        case 0:
        case 1:
            break;
        case 2:
            _ACTParaStatus_Set(self, 0x26);
            break;
        default:
            _ACTParaStatus_Set(self, 0x27);
            break;
        }
        if (GOBJ_ACT(self)->enemy->liftLevel < 0) {
            ACTSendMailCorrect(self, 0xC7);
            GOBJ_ACT(self)->enemy->stoneLevel = 0;
        }
        if (s->f4C >= 0x3D && GOBJ_ACT(self)->enemy->stoneLevel >= 3) {
            ACT_LAYOUT_GAMEOVER();
            _ACTWait(0);
        }
        ACTSendMailCorrect(self, 0x70);
        _ACTWait(1);
    }
}

void actCommonSofa(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    SetDirectRootPositionNoFitting((void *)self, s->env.sofaPos);
    GOBJ_ACT(self)->enemy->sofaWake = 0;
    GOBJ_ACT(self)->enemy->dirSmoothFrames = 0;
    GOBJ_ACT(self)->enemy->dirSmoothFrames2 = 0;
    *(void **)((char *)s + 0x160) = *(void **)((char *)s + 0x61C);
    while (1) {
        GOBJ_WORK(self)->sofaTimer = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 3;
        GOBJ_WORK(self)->sofaRestTimer = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 10;
        if (GOBJ_ACT(self)->enemy->sofaWake > GOBJ_ACT(self)->enemy->sofaWakeTime) {
            ACTSendMailCorrect(self, 0x73);
        }
        GOBJ_ACT(self)->enemy->sofaWake += 1;
        _ACTWait(1);
    }
}

static void BoxBarSoundOn(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    switch (s->actMode) {
    case 0x31:
        ExecBoxMoveStartReaction(s->box, (int)s->pushDir);
        break;
    case 0x33:
        ExecRotObjectMoveStartReaction(s->env.barObj);
        break;
    }
}

static void BoxBarSoundOff(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    switch (s->actMode) {
    case 0x31:
        ExecBoxMoveEndReaction(s->box);
        break;
    case 0x33:
        ExecRotObjectMoveEndReaction(s->env.barObj);
        break;
    }
}

static void _boxbar_set_sound(GObj *self, int mode)
{
    switch (GOBJ_ACT(self)->enemy->boxBarSound) {
    case 0:
        if (mode == 1) {
            BoxBarSoundOn(self);
            GOBJ_ACT(self)->enemy->boxBarSound = 1;
        }
        break;
    case 1:
        if (mode == 0 || mode == 2) {
            BoxBarSoundOff(self);
            GOBJ_ACT(self)->enemy->boxBarSound = mode;
        } else {
            BoxBarSoundOn(self);
        }
        break;
    case 2:
        if (mode == 0) {
            GOBJ_ACT(self)->enemy->boxBarSound = 0;
        }
        if (mode == 3) {
            BoxBarSoundOn(self);
            GOBJ_ACT(self)->enemy->boxBarSound = 1;
        }
        break;
    }
}

typedef void (*BoxAfterFn)(volatile int);

/* the height is an int */
static inline int boxWallCheck(GObj *self, GObj *box, float dist, int h) /* derived name */
{
    ClipWork w;
    float t[4];
    Act *s = GOBJ_ACT(self);

    GetRootPosition(w.pt[0], box);
    GetRootPosition(w.pt[1], box);
    sceVu0ScaleVector(t, s->env.wallOrient, dist);
    sceVu0AddVector(w.pt[1], w.pt[1], t);
    w.radius = h;
    w.pt[0][1] += 10.0f;
    w.pt[1][1] += 10.0f;
    ClipWall(&w);
    if (w.wall.elem == 0) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM(actCommonBox);

typedef struct { /* field names derived */
    char pad0[448];
    int f1C0;
    int f1C4;
    int f1C8;
} BarHold; /* derived name */

INCLUDE_ASM(actCommonBar);

void funcCommonJumpDircorrect(GObj *self)
{
    SetMotionDirection(self, GOBJ_WORK(self)->padWish);
}

void funcCommonFallDircorrect(GObj *self)
{
    SetMotionDirection(self, GOBJ_WORK(self)->fallDir);
}

static void correctJumpOrientByChain(GObj *self)
{
    float out[4];
    float mtx[16];
    float pos[4];
    float p[4];
    float q[4];
    float dir[4];
    GObj *o;
    float t;
    float best = 3.40282347e+38f; /* FLT_MAX */
    float ang = 0.0f;

    pos[0] = test_CURRENTROOT((void *)self)[0];
    pos[1] = test_CURRENTROOT((void *)self)[1];
    pos[2] = test_CURRENTROOT((void *)self)[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(self));

    for (o = isysGObjSearchFromObjKindID_begin(21); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (o->active == 0) {
            continue;
        }
        GetRootPosition(p, o);
        sceVu0SubVector(q, p, pos);
        q[3] = 0.0f;
        sceVu0ApplyMatrix(q, mtx, q);
        if (q[2] < 0.0f || 1000.0f < q[2]) {
            continue;
        }
        if (GetChainHangRange(o) < (q[0] < 0.0f ? -q[0] : q[0])) {
            continue;
        }
        if (pos[1] < p[1]) {
            continue;
        }
        if (p[1] + GetChainLength(o) + 200.0f < pos[1]) {
            continue;
        }
        ang = q[0];
        best = q[2];
        if (ang < 0.0f)
            ang = -ang;
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
    }
    if (best == 3.40282347e+38f) {
        return;
    }
    _OrientXZGV(dir, out, test_CURRENTROOT((void *)self));
    t = ang * 20.0f / 300.0f;
    if (t < 0.0f) {
        t = 0.0f;
    } else if (20.0f < t) {
        t = 20.0f;
    }
    SetMotionDirectionSmooze(self, dir, t);
}

typedef struct { /* field names derived */
    char pad0[398];
    unsigned short f18E;
} MotRecJ; /* derived name */

INCLUDE_ASM(actCommonJump);

/* The 0x15C slot is the engine's sub-object handle, read here as the SubHandle
 * union the way geometryManager.c's SUBOF reads it; the other readers use
 * GOBJ_SUB's int view. */
#define FALL_SUB(o) ((Sub15C *)((SubHandle *)((char *)(o) + 0x15C))->p) /* derived name */

/* A static inline that actCommonFall and flyCoreLoop call: whether the
 * actor has been stuck on a step for `need` hits.  flyCoreLoop passes a
 * motion that is not 418 and needs three hits where actCommonFall needs
 * two. */
static inline int IsFallStuckOnStep(GObj *self, int state, int mot, int need,
                                    int time) /* derived name */
{
    Act *s = GOBJ_ACT(self);
    int *q;
    int i, n, d;

    for (i = 0, n = 1, q = (int *)((char *)s->work + 0x928); i < 10; i++, q++) {
        if (q[-10] == state && (mot == 418 || mot == q[10])) {
            if (n >= need) {
                d = s->frame - *q;

                if (d < time * ((60 - systemStatus[0] * 10) / systemStatus[1]) / 60) {
                    return 1;
                }
                break;
            }
            n++;
        }
    }
    /* the not-found path returns the count variable, cleared */
    n = 0;
    return n;
}

INCLUDE_ASM(actCommonFall);

/* the sub-object's fly-limit flag at 0x654 */
typedef struct { /* field names derived */
    char pad0[1620];
    int limit;
} FlyLimitSub; /* derived name */

/* raises the flag that ResetFlyLimit clears */
static inline void SetFlyLimit(GObj *self) /* derived name */
{
    ((FlyLimitSub *)FALL_SUB(self))->limit = 1;
}

/* used by flyCoreLoop and actAfterFly */
static inline void ResetFlyLimit(GObj *self) /* derived name */
{
    ((FlyLimitSub *)FALL_SUB(self))->limit = 0;
}

/* clamp to -1..1 */
static inline float clampUnit(float x) /* derived name */
{
    if (1.0f < x) {
        x = 1.0f;
    }
    if (x < -1.0f) {
        x = -1.0f;
    }
    return x;
}

/* the vertical pull toward the target height */
static inline float calcVertAccel(float *a, float *b) /* derived name */
{
    return clampUnit((a[1] - b[1]) * 0.005f);
}

/* the vertical pull with a term for the horizontal distance */
static inline float calcFlyAccel(float *a, float *b) /* derived name */
{
    float d[4];
    float h;

    _SubVector(d, a, b);
    h = d[1];
    d[1] = 0.0f;
    h += -VectorLength(d) * (stage_no == 86 || stage_no == 3 || stage_no == 46 ? 2.5f : 0.5f);
    return clampUnit(h * 0.005f);
}

/* the flight-limit marker colour (R, G, B, A), the first of the four colour
   records at the head of commonact's .data colour run */
static int flyLimitCol[4] = {128, 192, 255, 128}; /* derived name */

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} FlyPt; /* derived name */

void debugDispFlyLimit(float *pos, float y0, float y1)
{
    MatrixDrive_PushMatrix();
    {
        FlyPt a = {{pos[0], y0, pos[2], 1.0f}};
        FlyPt b = {{pos[0], y1, pos[2], 1.0f}};

        _UnitMatrix(MatrixDrive_GetMatrix());
        gif_StartPacketPri(11);
        DrawLineG(&b, flyLimitCol, &a, flyLimitCol, 0);
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(&a);
        prim_DispWireSphere(10.0f, flyLimitCol, 4, 4);
        MatrixDrive_PopMatrix();
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(&b);
        prim_DispWireSphere(10.0f, flyLimitCol, 4, 4);
        MatrixDrive_PopMatrix();
        gif_EndPacket();
    }
    MatrixDrive_PopMatrix();
}

static void debugDispSphere(void *pos, void *col, float r)
{
    MatrixDrive_PushMatrix();
    _UnitMatrix(MatrixDrive_GetMatrix());
    gif_StartPacketPri(0xB);
    MatrixDrive_TransMatrixV(pos);
    prim_DispWireSphere(r, col, 4, 4);
    gif_EndPacket();
    MatrixDrive_PopMatrix();
}

/* the fly has run for more than 180 seconds */
static inline unsigned char IsFlyTimeOver(int self) /* derived name */
{
    if ((60 - systemStatus[0] * 10) / systemStatus[1] * 180 < GOBJ_WORK(self)->carryGirlFrames) {
        return 1;
    }
    return 0;
}

static void flyCoreLoop(GObj *self, GObj *target, int checkStuck);

INCLUDE_ASM(col_277);

INCLUDE_ASM(col_278);

INCLUDE_ASM(col_279);

INCLUDE_ASM(getLandOffset_265);

INCLUDE_ASM(completeEmergency_280);

INCLUDE_ASM(emergencyCheck_284);

INCLUDE_ASM(flyCoreLoop);

typedef struct { /* field names derived */
    char pad0[1528];
    int f5F8;
} FlyCtlJ; /* derived name */

void actCommonFly(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    GObj *target;
    GObj *gen = 0;

    s->flags18.ll &= ~(1ULL << 57);
    s->flags18.afterProc = actAfterFly;

    ((FlyCtlJ *)(char *)GOBJ_SUB(self))->f5F8 = 0;

    if (IsEnemyBrainToGenerator(self, &gen)) {
        target = gen;
    } else if (IsEnemyBrainToBoy(self) && boyGObj != 0) {
        target = boyGObj;
    } else if (girlGObj != 0) {
        target = girlGObj;
    } else if (boyGObj != 0) {
        target = boyGObj;
    } else {
        target = 0;
    }

    SetEnemyFootPrintSwitch(self, 0);

    flyCoreLoop(self, target,
                (girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 111 &&
                 GOBJ_ACT(girlGObj)->carrier == self) ||
                    debug_fly_limit_test != 0);
}

typedef struct { /* field names derived */
    char pad0[656];
    int upEnd;   /* 0x290, 1 or 2 when the field above ends by node 22 or 6 */
    int downEnd; /* 0x294, 1 or 2 when the field below ends by node 52 or 48 */

    union {
        unsigned long long ll;
        int i[2];
    } moveFlags; /* 0x298 */
} LadderWork;    /* derived name */

#define LADW ((LadderWork *)*(int *)(self->act + 0x680)) /* derived name */

void actCommonLadder(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    int mot = s->intrMot;
    float pos[4];
    int uf22;
    int uf6;
    int lf52;
    int lf48;
    int up22;
    int up6;
    int lp52;
    int lp48;
    GObj *o;

    if (s->env.edgePos[3] != 0.0f) {
        pos[0] = test_CURRENTROOT((void *)self)[0];
        pos[1] = test_CURRENTROOT((void *)self)[1];
        pos[2] = test_CURRENTROOT((void *)self)[2];
        pos[0] = s->env.edgePos[0];
        pos[2] = s->env.edgePos[2];
        s->env.edgePos[3] = 0.0f;
    }
    LADW->upEnd = 0;
    LADW->downEnd = 0;
    LADW->moveFlags.ll &= ~1ULL;
    LADW->moveFlags.ll &= ~2ULL;
    LADW->moveFlags.ll &= ~4ULL;
    if (self == boyGObj) {
        GOBJ_ACT(self)->hit = 1;
    }
    if (mot == 127 || mot == 128 || mot == 123) {
        while (1) {
            if (self == boyGObj && GOBJ_SUB(self)->ctrl.animFrame > 40.0f) {
                break;
            }
            if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1) {
                break;
            }
            _ACTWait(1);
        }
    }
    while (1) {
        uf22 = (int)GetDifferenceFromWallUpperField((void *)self, 22);
        uf6 = (int)GetDifferenceFromWallUpperField((void *)self, 6);
        lf52 = (int)GetDifferenceFromLastField((void *)self, 52);
        lf48 = (int)GetDifferenceFromLastField((void *)self, 48);
        up22 = (int)GetDifferenceFromWallUpperPlane((void *)self, 22);
        up6 = (int)GetDifferenceFromWallUpperPlane((void *)self, 6);
        lp52 = (int)GetDifferenceFromWallLowerPlane((void *)self, 52);
        lp48 = (int)GetDifferenceFromWallLowerPlane((void *)self, 48);
        LADW->upEnd = 0;
        LADW->downEnd = 0;
        LADW->moveFlags.ll &= ~4ULL;
        LADW->moveFlags.ll |= 1ULL;
        LADW->moveFlags.ll |= 2ULL;
        if ((uf22 - up22 < 0 ? up22 - uf22 : uf22 - up22) < 30) {
            if (uf22 < 10) {
                LADW->upEnd = 1;
            }
            if (uf6 < 10) {
                LADW->upEnd = 2;
            }
        } else {
            if (up22 < 40) {
                LADW->moveFlags.ll &= ~1ULL;
            }
            if (up6 < 40) {
                LADW->moveFlags.ll &= ~1ULL;
            }
        }
        if ((lf52 - lp52 < 0 ? lp52 - lf52 : lf52 - lp52) < 30) {
            if (lf52 >= -9) {
                LADW->downEnd = 1;
            }
            if (lf48 >= -9) {
                LADW->downEnd = 2;
            }
        } else {
            if (lp52 >= 31) {
                LADW->moveFlags.ll |= 4ULL;
            }
            if (lp48 >= 31) {
                LADW->moveFlags.ll |= 4ULL;
            }
        }
        if (s->pushDir == 0xFFFFFFFF && ((int)((long long)LADW->moveFlags.ll >> 2) & 1)) {
            ACTSendMailCorrect(self, 0x8E);
            if (self != boyGObj) {
                ACTSendMailCorrect(self, 0x8F);
            }
        }
        if (self == boyGObj && girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 38) {
            if (_DistSqGV(test_CURRENTROOT((void *)self), test_CURRENTROOT(girlGObj)) < 3600.0f) {
                ACTSendMailCorrect(self, 0x31);
            }
        }
        if (self == boyGObj || self == girlGObj) {
            pos[0] = test_CURRENTROOT((void *)self)[0];
            pos[1] = test_CURRENTROOT((void *)self)[1];
            pos[2] = test_CURRENTROOT((void *)self)[2];
            for (o = isysGObjSearchFromObjKindID_begin(4); o != 0;
                 o = isysGObjSearchFromObjKindID_next(o)) {
                if (o->active != 0) {
                    if (GOBJ_ACT(o)->actMode == 38 &&
                        _DistSqGV(pos, test_CURRENTROOT(o)) < 6400.0f) {
                        ACTSendMailCorrect(self, 0x31);
                        break;
                    }
                }
            }
        }
        _ACTWait(1);
    }
}

/* inline tail members, defined here: their strings come between the
   flyCoreLoop unit's and funcCommonBeginReady's in .rodata, while their code
   goes to the end of the object */
#undef LADW

INCLUDE_ASM(actCommonEdgeHang);

void funcCommonBeginReady(char *self, int mail, char *from)
{
    GOBJ_ACT(self)->readyFlags |= 1;
    debug_StdPrintfDummy("ready begin %s to %s\n", from == (char *)boyGObj ? "boy" : "girl",
                         self == (char *)boyGObj ? "boy" : "girl");
}

void funcCommonEndReady(char *self, int mail, char *from)
{
    GOBJ_ACT(self)->readyFlags |= 2;
    debug_StdPrintfDummy("ready end %s to %s\n", from == (char *)boyGObj ? "boy" : "girl",
                         self == (char *)boyGObj ? "boy" : "girl");
}

void funcCommonEndExec(char *self, int mail, char *from)
{
    GOBJ_ACT(self)->readyFlags |= 8;
    debug_StdPrintfDummy("exec end %s to %s\n", from == (char *)boyGObj ? "boy" : "girl",
                         self == (char *)boyGObj ? "boy" : "girl");
}

void funcCommonError(char *self, int mail, char *from)
{
    GOBJ_ACT(self)->readyFlags |= 0x10;
    debug_StdPrintfDummy("????error %s to %s\n", from == (char *)boyGObj ? "boy" : "girl",
                         self == (char *)boyGObj ? "boy" : "girl");
}

INCLUDE_ASM(SetMotionDirectionSmooze);

/* motionOrientManager.h declares none of the motion tables */
extern MotOriName motionOriKind[];

void _ACTDebugPrint(GObj *self)
{
    Act *sub;
    char *w;

    if (self == 0) {
        return;
    }
    sub = GOBJ_ACT(self);
    if ((char *)sub == 0) {
        return;
    }
    w = (char *)GOBJ_SUB(self) + 0x470;
    if (w == 0) {
        return;
    }
    if (debug_font_flag & 1) {
        debug_Printf(30, 90, 0xFFFFFFF, " ori  = [%s]\n", motionOriKind[*(int *)(w + 0xD0)].s);
        if (debug_font_flag & 1) {
            debug_Printf(30, 100, 0xFFFFFFF, " mot  = [%s]\n",
                         (motionKind + GOBJ_SUB(self)->ctrl.motion)->name);
            if (debug_font_flag & 1) {
                debug_Printf(30, 110, 0xFFFFFFF, " mode = [%s]\n", actModeTbl[sub->actMode].name);
                if (debug_font_flag & 1) {
                    debug_Printf(30, 120, 0xFFFFFFF, "frame = [%f]\n",
                                 GOBJ_SUB(self)->ctrl.animFrame);
                    if (debug_font_flag & 1) {
                        debug_Printf(30, 130, 0xFFFFFFF, "maxry = [%d]\n",
                                     self == girlGObj && (void *)girlControlMode != 0
                                         ? (motionKind + GOBJ_SUB(self)->ctrl.motion)->girlDirFrames
                                         : (motionKind + GOBJ_SUB(self)->ctrl.motion)->dirFrames);
                        if (debug_font_flag & 1) {
                            debug_Printf(30, 140, 0xFFFFFFF, " life = [%d]\n", (int)sub->life);
                            if (debug_font_flag & 1) {
                                debug_Printf(30, 150, 0xFFFFFFF, "   dw = [%d] [%d]\n",
                                             (int)*(float *)((char *)sub->motReq + 0x138),
                                             (int)-*(float *)((char *)sub->motReq + 0x130));
                                if (debug_font_flag & 1) {
                                    debug_Printf(30, 160, 0xFFFFFFF, "   dc = [%d] [%d]\n",
                                                 (int)*(float *)((char *)sub->motReq + 0x114),
                                                 (int)*(float *)((char *)sub->motReq + 0x110));
                                    if (debug_font_flag & 1) {
                                        debug_Printf(30, 170, 0xFFFFFFF, "wattr = [%x]\n",
                                                     GOBJ_SUB(self)->ctrl.wallAttr);
                                        if (debug_font_flag & 1) {
                                            debug_Printf(30, 180, 0xFFFFFFF, "bttype= [%d]\n",
                                                         GOBJ_ACT(self)->enemy->battleType);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ACTSendMailCorrect(GObj *self, int mail)
{
    Act *s = GOBJ_ACT(self);
    if ((mail == 0xB5 || mail == 0xBA) && self->kind == 1) {
        long long f = (long long)s->wish2.ll;
        if (((int)(f >> 5) & 1) && ((int)((long long)s->wish4.ll >> 5) & 1)) {
            mail = 0xB6;
        } else if ((int)(f >> 3) & 1) {
            mail = ((int)((long long)s->wish4.ll >> 3) & 1) ? 0xB7 : mail;
        }
    }
    iosOmSendMail(self, mail, self);
}

INCLUDE_ASM(_ACTCommonMailTest);

int E3_LeverCheck(GObj *self)
{
    float buf[3];
    buf[0] = *(float *)((char *)test_CURRENTORIENT(GOBJ_SUB(self)->root.wall.o.obj) + 0x0);
    buf[1] = *(float *)((char *)test_CURRENTORIENT(GOBJ_SUB(self)->root.wall.o.obj) + 0x4);
    buf[2] = *(float *)((char *)test_CURRENTORIENT(GOBJ_SUB(self)->root.wall.o.obj) + 0x8);
    _ApplyRyGV(buf, -1.5707964f);
    return _RotyGV(test_CURRENTORIENT(self), buf) < 0 ? -_RotyGV(test_CURRENTORIENT(self), buf) < 45
                                                      : _RotyGV(test_CURRENTORIENT(self), buf) < 45;
}

extern SlowrunRec motionOrient[];

typedef struct { /* field names derived */
    char pad0[396];
    unsigned char f18C;
    char pad18D[7];
} CarryMot; /* derived name */

static __inline__ unsigned char requestBecarryMotion(GObj *self, int mot, int wait,
                                                     int n) /* derived name */
{
    Act *sub = GOBJ_ACT(self);
    const BecPair *tbl = pairMotion;
    const BecPair *end = tbl + 31;
    const BecPair *p;
    int save0;
    int save1;

    for (p = tbl; p != end; p++) {
        if (p->mot == mot) {
            break;
        }
    }
    if (p != end) {
        save0 = motionOrient[n].w[2];
        save1 = motionOrient[n].w[4];
        motionOrient[n].w[2] = p->req;
        motionOrient[n].w[4] = wait;
        SetMotionRequest(self, 268, *(MotOriReq *)((char *)sub + 0x620));
        motionOrient[n].w[2] = save0;
        motionOrient[n].w[4] = save1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM(actCommonBecarry);

static inline void SetIdleMotionRange(int k, int mot, int mot2) /* derived name */
{
    int n1 = actDataTbl[k].orientRow;
    int n2 = actDataTbl[k].orientRow2;
    int n3 = actDataTbl[k].orientFirst;
    int n4 = actDataTbl[k].orientEnd;
    int i;

    if (mot != 1147 && mot2 != 1147) {
        motionOrient[n1].w[2] = mot;
        motionOrient[n2].w[2] = mot2;
        for (i = n3; i < n4; i++) {
            motionOrient[i].w[0] = mot;
        }
    }
}

void subCommonIdle(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    int k = s->actKind;
    int m0 = actDataTbl[k].idleMotion;
    int timer = 0;
    int same = 0;
    int sameHand = 0;
    int i;
    int j;
    int base;
    int lim;
    int n;
    int cur;
    int idx;
    int found;
    int nxt;

    for (i = 0; i < 9; i++) {
        if (idlingDef[i].motion[k] == m0) {
            same++;
        } else {
            break;
        }
    }
    for (i = 9; i < 10; i++) {
        if (idlingDef[i].motion[k] == m0) {
            sameHand++;
        } else {
            break;
        }
    }
    while (1) {
        cur = GOBJ_SUB(self)->ctrl.motion;
        if ((self == boyGObj && scpBoyControlReadDisable != 0) ||
            GOBJ_WORK(self)->noInterpTimer > 0 || ((int)(s->flags20.ll >> 44) & 1)) {
            timer = 0;
            ACTSendMailCorrect(self, 180);
        } else if (s->actMode != 1 && s->actMode != 69) {
            timer = 0;
        } else if ((int)(s->flags18.ll >> 62) & 1) {
            timer = 0;
            ACTSendMailCorrect(self, 180);
        } else {
            if (self == boyGObj && ACTGame_FLAG_TETSUNAGI()) {
                base = 9;
                lim = 10;
                n = sameHand;
            } else {
                base = 0;
                lim = 9;
                n = same;
            }
            if (cur == m0) {
                if (!((s->flags20.ll >> 45) & 1)) {
                    timer = timer + 1;
                }
                if (n > 0) {
                    if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 350 / 60 * (n + 1) <
                        timer) {
                        idx = base + n;
                        if (idx >= lim || idlingDef[idx].motion[k] == 1147) {
                            idx = base;
                        }
                        SetIdleMotionRange(k, idlingDef[idx].motion[k], idlingDef[idx].motion[k]);
                        ACTSendMailCorrect(self, 179);
                    }
                } else {
                    if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < timer) {
                        SetIdleMotionRange(k, idlingDef[base].motion[k], idlingDef[base].motion[k]);
                        ACTSendMailCorrect(self, 179);
                    }
                }
            } else {
                found = -1;
                timer = 0;
                for (j = base; j < lim; j++) {
                    if (cur == idlingDef[j].motion[k]) {
                        found = j;
                    }
                }
                if (found < 0) {
                    timer = 0;
                } else {
                    if (found + 1 < lim) {
                        nxt = idlingDef[found + 1].motion[k];
                    } else {
                        nxt = m0;
                    }
                    if (nxt == 1147) {
                        nxt = m0;
                    }
                    if (self == girlGObj && nxt == m0) {
                        nxt = idlingDef[0].motion[k];
                    }
                    SetIdleMotionRange(k, idlingDef[found].motion[k], nxt);
                    ACTSendMailCorrect(self, 179);
                }
            }
        }
        _ACTWait(1);
    }
}

void ContinueCorrectPosition(void *obj)
{
    float v[4];

    (GOBJ_ACT(obj)->enemy->corrCount)++;
    if (GOBJ_ACT(obj)->enemy->corrCount <= GOBJ_ACT(obj)->enemy->corrFrames) {
        if (obj == (char *)girlGObj) {
            if (debug_font_flag & 1) {
                debug_Printf(100, 100, 0xFFFFFFF, "timer=%2d/%2d\n",
                             GOBJ_ACT(obj)->enemy->corrCount, GOBJ_ACT(obj)->enemy->corrFrames);
            }
        }
        _InterGV(v, (void *)((int)GOBJ_ACT(obj)->enemy + 0x70),
                 (void *)((int)GOBJ_ACT(obj)->enemy + 0x90), (float)GOBJ_ACT(obj)->enemy->corrCount,
                 (float)(GOBJ_ACT(obj)->enemy->corrFrames - GOBJ_ACT(obj)->enemy->corrCount));
        SetDirectRootPositionNoFitting(obj, v);
        if (*(int *)((int)GOBJ_ACT(obj)->enemy + 0xB8) == 1) {
            _InterGV(v, (void *)((int)GOBJ_ACT(obj)->enemy + 0x80),
                     (void *)((int)GOBJ_ACT(obj)->enemy + 0xA0),
                     (float)GOBJ_ACT(obj)->enemy->corrCount,
                     (float)(GOBJ_ACT(obj)->enemy->corrFrames - GOBJ_ACT(obj)->enemy->corrCount));
            sceVu0Normalize(v, v);
            SetMotionDirection(obj, v);
        }
    } else {
        *(long long *)((int)GOBJ_ACT(obj)->enemy + 0xB8) &= 0xFFFFFFFEFFFFFFFFLL;
    }
}

void actCommonTurn(GObj *volatile self)
{
    float q[4];
    float o[4];
    Act *s = GOBJ_ACT(self);
    float *t = s->env.turnDir.f;
    int d;

    while (1) {
        GetRootMotionOrient(q, self);
        d = _RotyGV(s->env.turnDir.f, q);
        debug_Arrow(100.0f, test_CURRENTROOT((void *)self), s->env.turnDir.f, 0, 0, 0xFF);
        if (self == girlGObj) {
            GetSkeltonOrient(o, self, 1);
            if (_AbsRotyGV(t, o) < 60) {
                if (s->stick.mag != 0.0f) {
                    ACTSendMailCorrect(self, 0xF0);
                }
                ACTSendMailCorrect(self, 0xF1);
            }
        } else {
            if ((d < 0 ? -d : d) < 15) {
                ACTSendMailCorrect(self, 0xF1);
            }
        }
        switch ((unsigned int)s->intrKind) {
        case 0xE7:
        case 0xE9:
            GOBJ_WORK(self)->turnTimer = (60 - systemStatus[0] * 10) / systemStatus[1];
            break;
        case 0xE8:
        case 0xEA:
            GOBJ_WORK(self)->turnTimer2 = (60 - systemStatus[0] * 10) / systemStatus[1];
            break;
        }
        _ACTWait(1);
    }
}

void actCommonBackhand(GObj *volatile self)
{
    float v[4];
    float dir[4];
    float pos[4];
    int frame;

    _OrientXZGV(dir, test_CURRENTROOT((void *)self), test_CURRENTROOT(girlGObj));
    SetMotionDirection(self, dir);
    v[0] = test_CURRENTORIENT(girlGObj)[0];
    v[1] = test_CURRENTORIENT(girlGObj)[1];
    v[2] = test_CURRENTORIENT(girlGObj)[2];
    while (1) {
        sceVu0ScaleVector(pos, v, 50.0f);
        sceVu0AddVector(pos, test_CURRENTROOT(girlGObj), pos);
        SetDirectRootPositionNoFittingWithNodePointXZ((void *)self, 6, pos, 0.2f);
        if (GOBJ_SUB(self)->ctrl.motion == 0xBD) {
            _OrientXZGV(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT((void *)self));
            SetMotionDirection(self, dir);
        }
        /* the frame budget is computed and dropped */
        frame = (60 - systemStatus[0] * 10) / systemStatus[1];
        _ACTWait(1);
    }
}

typedef union { /* field names derived */
    int i;
    float f;
} IntFloatSR; /* derived name */

INCLUDE_ASM(actCommonSlowrun);

typedef struct { /* field names derived */
    char pad0[20];
    int f14;
} TruckLeverWork; /* derived name */

void actCommonTruckLever(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    GObj *lev = s->env.pullObj;

    ((TruckLeverWork *)s)->f14 = (int)afterCommonTruckLever;
    actMotDirToWall(self);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(self)->ctrl.frameFlag2 != 0) {
                correctLeverHoldPoint((void *)self, lev);
            }
            if (GOBJ_SUB(self)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)self, lev);
            }
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(ACT_LAYOUT_GAMEOVER);

void ACTAdjustPlane(GObj *self, void *wall)
{
    AdjustRootPositionToVerticalSidePlaneOfWall(self, wall, 30.0f);
}

typedef struct { /* field names derived */
    float x, y, z;
} Vec3f; /* derived name */

typedef struct { /* field names derived */
    char pad0[24];
    int f18;
} RopeSwingWork; /* derived name */

static inline int isRopeDownEndOnFloor(GObj *self) /* derived name */
{
    ClipWork work;
    MotionDef *rec = &motionKind[GOBJ_SUB(self)->ctrl.motion];

    if ((rec->flags.word >> 4) & 1) {
        GetSkeltonPosition(work.pt[0], self, 0x2C);
        GetSkeltonPosition(work.pt[1], self, 0x33);
        work.pt[1][1] = work.pt[1][1] - 5.0f;
        ClipFloor(&work);
        if (work.floor.elem != 0) {
            return 1;
        }
    }
    return 0;
}

typedef struct { /* field names derived */
    char pad0[304];
    int f130;
    int f134;
    int f138;
} RopeJumpWork; /* derived name */

typedef struct { /* field names derived */
    char pad0[24];
    int f18;
} RopeTurnSpWork; /* derived name */

typedef struct { /* field names derived */
    char pad0[56];
    int f38;
} LadderMotWork; /* derived name */

typedef struct { /* field names derived */
    char pad0[56];
    unsigned int f38;
} LadderDownMotWork; /* derived name */

/* StartCorrectPosition and IsCorrectPosition precede test_CURRENTORIENT and
   test_CURRENTROOT, so their calls to the two accessors stay calls. */
typedef union { /* field names derived */
    unsigned long long ll;
    int i;
} CorrFlag; /* derived name */

/* the orient and the position these two accessors hand back */
static float commonOrient[4]; /* derived name */

static float commonPos[4]; /* derived name */

typedef struct { /* field names derived */
    char pad0[32];
    unsigned long long status;
} FlySub; /* derived name */

typedef struct { /* field names derived */
    char pad0[116];
    int coll;
} BecSub; /* derived name */

inline void afterCommonTruckLever(GObj *volatile self)
{
    char *g = (char *)self;
    SetSwitchState(GOBJ_ACT(g)->env.pullObj, 0);
}

INCLUDE_ASM(ACTAcceptMail);

INCLUDE_ASM(_ACTMotDirSmzDirect);

INCLUDE_ASM(WithMailFunc_Idling);

INCLUDE_ASM(WithMailFunc_BossDamaged);

INCLUDE_ASM(WithMailFunc_FallDead);

INCLUDE_ASM(actCommonRevive);

INCLUDE_ASM(actCommonReviveAir);

INCLUDE_ASM(actCommonPlay);

INCLUDE_ASM(actCommonOne);

INCLUDE_ASM(actCommonDelete);

INCLUDE_ASM(actCommonCatchFire);

INCLUDE_ASM(actCommonCatchFireBomb);

INCLUDE_ASM(actCommonPutFire);

INCLUDE_ASM(actCommonBoxReverbe);

INCLUDE_ASM(actCommonItem);

INCLUDE_ASM(actCommonClimb);

INCLUDE_ASM(actCommonCliffdown);

INCLUDE_ASM(actCommonLadderBellow);

INCLUDE_ASM(actCommonLadderBellowHang);

INCLUDE_ASM(actCommonEdge);

INCLUDE_ASM(actCommonDodge);

INCLUDE_ASM(actCommonDodgeJump);

INCLUDE_ASM(actCommonGuard);

INCLUDE_ASM(actCommonFallDamage);

INCLUDE_ASM(actCommonDamage);

INCLUDE_ASM(actCommonShoal);

INCLUDE_ASM(actCommonSwim);

INCLUDE_ASM(actCommonLever2);

INCLUDE_ASM(actCommonRopeTouchWall);

INCLUDE_ASM(actCommonRopeSwing);

INCLUDE_ASM(actCommonRopeTurn);

INCLUDE_ASM(actCommonRopeDownEnd);

INCLUDE_ASM(actCommonRopeJump);

INCLUDE_ASM(actCommonRopeJumpBefore);

INCLUDE_ASM(actCommonRopeTurnSpecial);

INCLUDE_ASM(actCommonRopeClimbEnd2);

INCLUDE_ASM(actCommonCornered);

INCLUDE_ASM(actCommonLookaround);

INCLUDE_ASM(actCommonTurnWarn);

INCLUDE_ASM(actCommonTurnStrict);

INCLUDE_ASM(actCommonPPipe);

INCLUDE_ASM(actCommonHandrail);

INCLUDE_ASM(actCommonOneWall);

INCLUDE_ASM(motCommonNull);

INCLUDE_ASM(motCommonBoxPush);

INCLUDE_ASM(motCommonBoxPull);

INCLUDE_ASM(motCommonBarPush);

INCLUDE_ASM(motCommonBarPull);

INCLUDE_ASM(motCommonLadderUp);

INCLUDE_ASM(motCommonLadderDown);

INCLUDE_ASM(motCommonSlip);

INCLUDE_ASM(motCommonRopejumpDircorrect);

INCLUDE_ASM(motCommonHangNone);

INCLUDE_ASM(motCommonHangWall);

INCLUDE_ASM(motCommonHangCliff);

INCLUDE_ASM(motCommonRopeTurnSpecialR);

INCLUDE_ASM(motCommonRopeTurnSpecialL);

INCLUDE_ASM(motCommonTruckLeverLoop);

INCLUDE_ASM(motCommonTruckLeverPull);

INCLUDE_ASM(motCommonTruckLeverPush);

INCLUDE_ASM(funcCommonRopeBefore);

INCLUDE_ASM(afterCommonRope);

INCLUDE_ASM(extraCommonNull);

INCLUDE_ASM(extraCommonCall);

INCLUDE_ASM(funcCommonWayOn);

INCLUDE_ASM(funcCommonSofaWakeup);

INCLUDE_ASM(_ACTMotReqResult);

INCLUDE_ASM(test_CURRENTORIENT);

INCLUDE_ASM(test_CURRENTROOT);

INCLUDE_ASM(StartCorrectPosition);

INCLUDE_ASM(IsCorrectPosition);

INCLUDE_ASM(ControlMotionOrient);

INCLUDE_ASM(FloorIsTruck);

INCLUDE_ASM(_ACTMotDir_V);

INCLUDE_ASM(ACTMotDirToWall);

INCLUDE_ASM(SetCorrectOrientOfChain);

INCLUDE_ASM(actAfterForceRope);

INCLUDE_ASM(actAfterForceRopeSwing);

INCLUDE_ASM(actAfterRopeJump);

INCLUDE_ASM(afterCommonRopeCliff);

INCLUDE_ASM(afterCommonRopeTurnSpecial);

INCLUDE_ASM(actAfterDown);

INCLUDE_ASM(afterCommonCling);

INCLUDE_ASM(actAfterSlip);

INCLUDE_ASM(afterCommonRevive);

INCLUDE_ASM(afterCommonStone);

INCLUDE_ASM(afterCommonBox);

INCLUDE_ASM(afterCommonBar);

INCLUDE_ASM(actAfterJump);

INCLUDE_ASM(actAfterFall);

INCLUDE_ASM(actAfterFly);

INCLUDE_ASM(ClipCollisionWithField);

INCLUDE_ASM(afterCommonOneWall);

INCLUDE_ASM(ACTCheckFlagAttack);

INCLUDE_ASM(afterCommonBecarry);
