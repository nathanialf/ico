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
void actCommonEdgeHang(GObj *volatile self);
void actCommonDodge(GObj *volatile self);
void actCommonDodgeJump(GObj *volatile self);
void actCommonGuard(GObj *volatile self);
void actCommonFallDamage(GObj *volatile self);
void actCommonDamage(GObj *volatile self);
void actCommonDown(GObj *volatile self);
void actCommonShoal(GObj *volatile self);
void actCommonSwim(GObj *volatile self);
void actCommonTruckLever(GObj *volatile self);
void actCommonLever2(GObj *volatile self);
void actCommonRopeTouchWall(GObj *volatile self);
void actCommonRopeSwing(GObj *volatile self);
void actCommonRopeTurn(GObj *volatile self);
void actCommonRopeDownEnd(GObj *volatile self);
void actCommonRopeJump(GObj *volatile self);
void actCommonRopeJumpBefore(GObj *volatile self);
void actCommonRopeClimbEnd2(GObj *volatile self);
void actCommonCornered(GObj *volatile self);
void actCommonLookaround(GObj *volatile self);
void actCommonTurn(GObj *volatile self);
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
static inline void afterCommonRopeCliff(GObj *self);
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

static int ChangeMailInLadder(GObj *self, int mail)
{
    float p[4];
    float q[4];
    int ret = mail;
    int flag = 0;

    if (boyGObj != 0 && girlGObj != 0) {
        if (self == boyGObj) {
            if (GOBJ_ACT(self)->actMode == 38) {
                flag = (GOBJ_ACT(girlGObj)->actMode == 38);
            }
        }
        if (self == girlGObj) {
            if (GOBJ_ACT(self)->actMode == 38) {
                flag = 1;
            }
        }
        if (flag != 0 &&
            _DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 3600.0f) {
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
            case 295:
                if (q[1] < p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < 200.0f) {
                    ret = 301;
                }
                break;
            case 296:
                if (q[1] > p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < 200.0f) {
                    ret = 301;
                }
                break;
            }
        }
    }
    return ret;
}

/* motionOrientManager.h declares none of the motion tables */

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

/* the motion each interrupt kind requests, indexed by the kind: 372 words in this build */
INCLUDE_ASM(intrMotion);

INCLUDE_ASM(ACTGetOrientFromIntrK);

void ACTRunIntrCorrect(GObj *self, IntrMail *intr, IntrMail *corr)
{
    Act *s = GOBJ_ACT(self);
    inline void setIntrFlags(void) /* derived name */
    {
        IntrMail *p;

        for (p = intr; p != 0 && (short)p->kind != 376; p++) {
            p->flags |= 0x40000;
        }
    }
    inline void correctIntrList(void) /* derived name */
    {
        IntrMail *ip;
        IntrMail *q;

        for (q = corr; q != 0 && (short)q->kind != 376; q++) {
            if (q->mode == -1) {
                for (ip = intr; ip != 0 && (short)ip->kind != 376; ip++) {
                    if (ip->kind == q->kind) {
                        ip->flags &= ~0x40000;
                        debug_StdPrintfDummy("off!!\n");
                    }
                }
            }
        }
    }

    setIntrFlags();
    correctIntrList();
    if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 19) & 1) {
        actIntrList[10].flags |= 0x40000;
    } else {
        actIntrList[10].flags &= ~0x40000;
    }
    if (s->actMode == 26) {
        if (s->modeFrame < ((60 - systemStatus[0] * 10) / systemStatus[1]) / 3) {
            actIntrList[340].flags |= 0x40000;
        } else {
            actIntrList[340].flags &= ~0x40000;
        }
    }
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

inline void afterCommonRope(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    debug_StdPrintfDummy("common rope after func\n");
    ReleaseChain(s->chain, self);
    {
        GObj *g = self;
        *(int *)((int)s + 0x184) = (int)s->chain;
        GOBJ_SUB(g)->root.ropeState = 0;
    }
}

inline void actAfterForceRope(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    if (s->chain == 0) {
        debug_assert("src/commonact.c", 1267);
        __assert("src/commonact.c", 1267, "ROPE_GOBJ!=NULL");
    }
    UnLockChainGeo(s->chain);
}

void actCommonRope(GObj *volatile self)
{
    Act *s;
    float dir[4];
    float ori[4];
    float hand[4];
    float rot[4];
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
            ACTSendMailCorrect(self, 152);
            break;
        case 2:
            ACTSendMailCorrect(self, 151);
            break;
        }
        if (step >= 0) {
            if (step == nsteps) {
                SetMotionDirection(self, dir);
            } else if (step < nsteps) {
                rot[0] = ori[0];
                rot[1] = ori[1];
                rot[2] = ori[2];
                _ApplyRyGV(rot, (float)(roty * step / total) * 3.1415927f / 180.0f);
                SetMotionDirection(self, rot);
            }
            step++;
        }
        if (CheckChainClimbablePos(s->chain)) {
            GetChainClimbOrient(GOBJ_ACT(self)->enemy->climbOrient, s->chain);
            GetRootPosition(GOBJ_ACT(self)->enemy->climbPos, (void *)s->chain);
            GetChainClimbCollision(&GOBJ_ACT(self)->enemy->climbCol, s->chain);
            GOBJ_ACT(self)->enemy->climbObj = s->chain;
            ActSendMail_WithAdditionalData(self, 138, (void *)self,
                                           GOBJ_ACT(self)->enemy->climbOrient);
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
    Act *s = GOBJ_ACT(self);
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
        if (i % wait == 0 && !(0.1f < s->stick.mag)) {
            setCorrectOrientOfChain((void *)self);
            ACTSendMailCorrect(self, 301);
        }
        _ACTWait(1);
    }
}

void motCommonRopeTurnL(GObj *volatile self)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(self)) / 3.1415927f * 180.0f);
    Act *s = GOBJ_ACT(self);
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
        if (i % wait == 0 && !(0.1f < s->stick.mag)) {
            setCorrectOrientOfChain((void *)self);
            ACTSendMailCorrect(self, 301);
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
    int step = 5;
    int i;
    long back;
    int n;
    int r;

    c = *(ClimbEndRec *)(char *)GOBJ_ACT(self)->intrData;
    GOBJ_SUB(boyGObj)->root.ropeState = 0;
    back = -5;
    while (GOBJ_SUB(self)->ctrl.motion != 125) {
        _ACTWait(1);
    }
    i = 0;
    GetSkeltonPosition(pos, self, 22);
    ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.holdPoint[0] = pos[0];
    ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.holdPoint[1] = pos[1];
    ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.holdPoint[2] = pos[2];
    ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.ropeState = 1;
    dir.f[0] = c.v0[0];
    dir.f[1] = c.v0[1];
    dir.f[2] = c.v0[2];
    sceVu0ScaleVector(&dir, &dir, -1.0f);
    r = _RotyGV(dir.f, test_CURRENTORIENT(self));
    step = (r > -1) ? step : back;
    n = r / step;
    n = (n < 0) ? -n : n;
    while (i < n) {
        i++;
        ori[0] = *(float *)((char *)test_CURRENTORIENT(self) + 0);
        ori[1] = *(float *)((char *)test_CURRENTORIENT(self) + 4);
        ori[2] = *(float *)((char *)test_CURRENTORIENT(self) + 8);
        _ApplyRyGV(ori, (float)step * 3.1415927f / 180.0f);
        SetMotionDirection(self, ori);
        _ACTWait(1);
    }
    SetMotionDirection(self, dir.f);
    while (1) {
        ACTSendMailCorrect(self, 139);
        GetSkeltonPosition(hand, self, 22);
        GetSkeltonPosition(foot, self, 6);
        base[0] = c.v1[0];
        base[1] = c.v1[1];
        base[2] = c.v1[2];
        if (c.obj->kind == 42) {
            TestCageUpDown(c.obj, (void *)self);
        }
        GOBJ_ACT(self)->enemy->climbCol = c.climbCol;
        if (hand[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(self, 140);
        }
        if (foot[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(self, 141);
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
    int n = ((60 - systemStatus[0] * 10) / systemStatus[1]) / 10;
    int i = 0;

    ((CagePtr *)(((CagePtr *)((char *)boyGObj + 0x15C))->p + 0x410))->p = 0;
    dst[0] = GOBJ_ACT(self)->enemy->ropeCliffX;
    dst[1] = GOBJ_ACT(self)->enemy->ropeCliffY;
    dst[2] = GOBJ_ACT(self)->enemy->ropeCliffZ;
    GetRootPosition(root, (void *)self);
    while (1) {
        if (i++ <= n) {
            _InterGV(cur, root, dst, (float)i, (float)(n - i));
            SetDirectRootPosition((void *)self, cur);
        }
        if (GOBJ_SUB(self)->ctrl.motion == 125) {
            p[0] = test_CURRENTROOT((void *)self)[0];
            p[1] = test_CURRENTROOT((void *)self)[1];
            p[2] = test_CURRENTROOT((void *)self)[2];
            p[1] = p[1] + 5.0f;
            SetDirectRootPosition((void *)self, p);
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
    inline void initCage(GObj * o, int down) /* derived name */
    {
        int n;

        cageUpDown.cnt = 0;
        cageUpDown.lim = (float)*motionTable[*(int *)(((CagePtr *)&o->dobj)->p + 0x490)];
        n = GetSkeltonFocusNode(o, 35);
        cageUpDown.a[0] = *(float *)(*(char **)(((CagePtr *)&o->dobj)->p + 0xC) + n * 0x40 + 0x30);
        cageUpDown.a[1] = *(float *)(*(char **)(((CagePtr *)&o->dobj)->p + 0xC) + n * 0x40 + 0x34);
        cageUpDown.a[2] = *(float *)(*(char **)(((CagePtr *)&o->dobj)->p + 0xC) + n * 0x40 + 0x38);
        cageUpDown.b[0] = cageUpDown.a[0];
        cageUpDown.b[2] = cageUpDown.a[2];
        if (down) {
            cageUpDown.b[1] = cageUpDown.a[1] - 100.0f;
        } else {
            cageUpDown.b[1] = cageUpDown.a[1] + 200.0f;
        }
    }

    inline void cageMove(GObj * o, float *dst, float *lo, float *hi, float *res, float x, float y,
                         float z) /* derived name */
    {
        dst[0] = x;
        dst[1] = y;
        dst[2] = z;
        GetCageChainPoint(lo, hi, cage);
        dst[0] = lo[0];
        dst[2] = lo[2];
        sceVu0ScaleVector(res, test_CURRENTORIENT(o), -15.0f);
        sceVu0AddVector(res, dst, res);
        SetDirectRootPositionNoFittingWithNodePoint(o, 35, res, 1.0f);
    }

    float vA[4];
    float vB[4];
    float vC[4];
    float vD[4];
    float vE[4];
    float vF[4];
    float vG[4];
    float vH[4];
    int mot = *(int *)(((CagePtr *)((char *)gobj + 0x15C))->p + 0x490);
    int n;

    GetCageChainPoint(vB, vC, cage);
    *(int *)(((CagePtr *)((char *)boyGObj + 0x15C))->p + 0x410) = 0;
    switch (mot) {
    case 127:
        break;
    case 126:
        if (GOBJ_ACT(gobj)->actMode == 63) {
            if (cageUpDown.last != mot) {
                initCage(gobj, 1);
            }
            _InterGV(vA, cageUpDown.a, cageUpDown.b, (float)cageUpDown.cnt,
                     (float)(cageUpDown.lim - cageUpDown.cnt));
            cageMove(gobj, vF, vG, vH, vE, vA[0], vA[1], vA[2]);
            cageUpDown.cnt = cageUpDown.cnt + 1;
        } else {
            if (cageUpDown.last != mot) {
                initCage(gobj, 1);
            }
            _InterGV(vA, cageUpDown.a, cageUpDown.b, (float)cageUpDown.cnt,
                     (float)(cageUpDown.lim - cageUpDown.cnt));
            vA[1] = vA[1] < vB[1] ? vB[1] : (vC[1] < vA[1] ? vC[1] : vA[1]);
            cageMove(gobj, vF, vG, vH, vE, vA[0], vA[1], vA[2]);
            cageUpDown.cnt = cageUpDown.cnt + 1;
        }
        break;
    case 128:
    case 129:
        if (cageUpDown.last != mot) {
            initCage(gobj, 0);
        }
        _InterGV(vA, cageUpDown.a, cageUpDown.b, (float)cageUpDown.cnt,
                 (float)(cageUpDown.lim - cageUpDown.cnt));
        vA[1] = vA[1] < vB[1] ? vB[1] : (vC[1] < vA[1] ? vC[1] : vA[1]);
        cageMove(gobj, vF, vG, vH, vE, vA[0], vA[1], vA[2]);
        cageUpDown.cnt = cageUpDown.cnt + 1;
        break;
    default:
        n = GetSkeltonFocusNode(boyGObj, 22);
        vA[0] = *(float *)(*(char **)(((CagePtr *)&boyGObj->dobj)->p + 0xC) + n * 0x40 + 0x30);
        vA[1] = *(float *)(*(char **)(((CagePtr *)&boyGObj->dobj)->p + 0xC) + n * 0x40 + 0x34);
        vA[0] = vB[0];
        vA[2] = vB[2];
        ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.holdPoint[0] = vA[0];
        ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.holdPoint[1] = vA[1];
        ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.holdPoint[2] = vA[2];
        ((SubHandle *)((char *)boyGObj + 0x15C))->sub->root.ropeState = 1;
        break;
    }
    cageUpDown.last = mot;
}

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} RsVec4; /* derived name */

void actCommonRopeSpecial(GObj *volatile self)
{
    unsigned char ropeSpecialWallHit(RsVec4 * p1, ClimbCol * hit) /* derived name */
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

    Act *s;
    ClimbCol hit;
    RsVec4 p1;
    RsVec4 p2;
    RsVec4 pos;
    GObj *cage;
    unsigned char found;

    s = GOBJ_ACT(self);
    cage = s->env.cageObj.obj;
    GetCageChainPoint(p1.f, p2.f, cage);
    found = ropeSpecialWallHit(&p1, &hit);
    GOBJ_SUB(self)->root.ropeState = 0;
    while (1) {
        if (GOBJ_SUB(self)->ctrl.motion == 125) {
            s->flags18.ll &= ~(1ULL << 63);
        }
        GetSkeltonPosition(pos.f, self, 35);
        GetCageChainPoint(p1.f, p2.f, cage);
        if (debug_font_flag & 1) {
            debug_Printf(10, 120, 0xFFFFFFF, "%d, %d\n",
                         (int)*(float *)((char *)test_CURRENTROOT((void *)self) + 4), (int)p2.f[1]);
        }
        if (*(float *)((char *)test_CURRENTROOT((void *)self) + 4) > p2.f[1] - 30.0f) {
            ACTSendMailCorrect(self, 177);
        }
        if (found && pos.f[1] < p1.f[1] + 10.0f) {
            GOBJ_ACT(self)->enemy->climbObj = cage;
            GetOrientOfWall(GOBJ_ACT(self)->enemy->climbOrient, hit.wall, &hit.wallSrc);
            GOBJ_ACT(self)->enemy->climbPos[0] = p1.f[0];
            GOBJ_ACT(self)->enemy->climbPos[1] = p1.f[1];
            GOBJ_ACT(self)->enemy->climbPos[2] = p1.f[2];
            GOBJ_ACT(self)->enemy->climbPos[1] -= 100.0f;
            GOBJ_ACT(self)->enemy->climbCol = hit;
            ActSendMail_WithAdditionalData(self, 158, (void *)self,
                                           GOBJ_ACT(self)->enemy->climbOrient);
        }
        TestCageUpDown(cage, (void *)self);
        _ACTWait(1);
    }
}

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
    SetDirectRootPosition(self, pos); /* this build's call (PAL's skips the fitting) */
}

/* the turn away from the wall, which ACTMotDirToWall and the lever, box,
   bar and truck functions inline */
static inline void actMotDirToWall(GObj *self) /* derived name */
{
    float local[4];
    sceVu0ScaleVector(local, *(char **)((char *)self + 0x164) + 0x4A0, -1.0f);
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
        }
    }
    SetDirectRootPositionWithNodePoint(self, 22, w,
                                       0.2f); /* this build has no ...NoFittingWithNodePointXZ */
}

/* the truck lever's hold point: as correctLeverHoldPoint, without the fitting */
static inline void correctTruckLeverHoldPoint(GObj *self, GObj *lev) /* derived name */
{
    float w[4];
    if (lev->kind >= 22) {
        if (lev->kind < 24) {
            GetFloorLeverGlobalHoldPoint(w, lev);
        } else if (lev->kind < 26) {
            GetWallLeverGlobalHoldPoint(w, lev);
        }
    }
    SetDirectRootPositionNoFittingWithNodePoint(self, 22, w, 0.2f);
}

void actCommonLever(GObj *volatile self)
{
    float p[4];
    Act *s = GOBJ_ACT(self);
    GObj *lev = s->env.pullObj;

    p[0] = s->env.pullPos[0];
    p[1] = s->env.pullPos[1];
    p[2] = s->env.pullPos[2];
    p[1] = test_CURRENTROOT((void *)self)[1];
    SetDirectRootPositionNoFitting((void *)self, s->env.pullPos);
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

INCLUDE_ASM_LIT(actCommonPlay);

inline void actCommonDamage(GObj *volatile self)
{
    debug_StdPrintfDummy("enter actCommonDamage\n");
    SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
    DamageFunc(self);
    if (GOBJ_ACT(self)->enemy->liftKind == 3) {
        _ACTWait(360);
    }
    for (;;) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actCommonDown(GObj *volatile self)
{
    float v[4];
    Act *s = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actCommonDown\n");
    s->flags18.afterProc = actAfterDown;
    if (self == girlGObj) {
        sceVu0ScaleVector(v, GOBJ_ACT(self)->attackDir, -1.0f);
        SetMotionDirection(self, v);
    } else {
        SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
    }
    DownFunc(self);
    while (1) {
        if (self->kind != 4) {
            GOBJ_ACT(self)->hit = 1;
        }
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

void actCommonDie(GObj *volatile self)
{
    /* a helper defined at the head of this body */
    inline void dieNotifyObjects(void) /* derived name */
    {
        void *g;

        if (self->labelId == 3246) {
            gamesysObjInfoCls(4, 3246);
            gamesysObjInfoCls(33, 3247);
        }
        g = isysGObjSearchFromObjKindID_begin(45);
        if (g == 0) {
            g = isysGObjSearchFromObjKindID_begin(62);
        }
        if (self->kind == 4 && g != 0) {
            iosOmSendMail(g, 18, self);
        }
    }
    Act *s = GOBJ_ACT(self);
    int cnt = 0;
    float t;

    debug_StdPrintfDummy("enter actCommonDie\n");
    SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
    DownFunc(self);
    GOBJ_ACT(self)->hit = 1;
    dieNotifyObjects();
    while (1) {
        if (self->kind == 4) {
            _ACTWait(1);
            enemySetParticleDie(test_CURRENTROOT((void *)self), GOBJ_ACT(self)->attackDir);
            EnemySetfDisappearAll(self);
            actEnemyFlagOnDead(self);
            ACTGame_DeleteActorInformation(self);
            for (t = 0.0f; t < (float)(((60 - systemStatus[0] * 10) / systemStatus[1]) * 6);
                 t += GOBJ_WORK(self)->disappearSpeed) {
                float d = (t + t - (float)(((60 - systemStatus[0] * 10) / systemStatus[1]) * 6)) /
                          (float)(((60 - systemStatus[0] * 10) / systemStatus[1]) * 6);
                if (d < 0.01f) {
                    d = 0.01f;
                }
                SetEnemyDissolve(self, d);
                if ((int)((long long)s->flags20.ll >> 6) & 1) {
                    t += 10.0f;
                }
                _ACTWait(1);
            }
            actEnemyHyde(self);
            _ACTWait(0);
        }
        if (self == boyGObj || self == girlGObj) {
            if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 2 < cnt) {
                lt_switch_layout(58);
                _ACTWait(0);
            }
        }
        cnt++;
        _ACTWait(1);
    }
}

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
            debug_assert("src/commonact.c", 2220);
            __assert("src/commonact.c", 2220,
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
    ACTGameCollisionOff((void *)self);
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

INCLUDE_ASM_LIT(actCommonRevive);

typedef struct { /* field names derived */
    char pad0[20];
    int after; /* 0x14, Act's after function */
} ReviveSub;   /* derived name */

typedef struct { /* field names derived */
    char pad0[20];
    int after; /* 0x14, Act's after function */
    char pad18[48];
    int modeFrame; /* 0x48, Act's frames since the mode changed */
} StoneSub;        /* derived name */

void actCommonStone(GObj *volatile self)
{
    StoneSub *s = (StoneSub *)(char *)GOBJ_ACT(self);

    s->after = (int)afterCommonStone;
    *(int *)(*(char **)(*(char **)((char *)self + 0x164) + 0x650) + 0x2A0) = 0;
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
            _ACTParaStatus_Set(self, 33);
            break;
        default:
            _ACTParaStatus_Set(self, 34);
            break;
        }
        if (GOBJ_ACT(self)->enemy->liftLevel < 0) {
            ACTSendMailCorrect(self, 177);
            GOBJ_ACT(self)->enemy->stoneLevel = 0;
        }
        if (s->modeFrame >= 61 && GOBJ_ACT(self)->enemy->stoneLevel >= 3) {
            lt_switch_layout(58);
        }
        ACTSendMailCorrect(self, 103);
        _ACTWait(1);
    }
}

INCLUDE_ASM(func_00153E00);

INCLUDE_ASM(func_00153E38);

static void BoxBarSoundOn(GObj *self);
static void BoxBarSoundOff(GObj *self);
static void _boxbar_set_sound(GObj *self, int mode);

INCLUDE_ASM(_boxbar_set_sound);

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

/* Sub15C's root.filter (0x1B0), set word by word to the bar the actor
   holds; afterCommonBar resets it */
typedef struct { /* field names derived */
    char pad0[432];
    int filterObj;
    int filterNode;
    int filterElem;
} BarHold; /* derived name */

inline void afterCommonBar(GObj *volatile self)
{
    debug_StdPrintfDummy("reset\n");
    GOBJ_SUB(self)->root.filter = InitialColInfo;
    _boxbar_set_sound(self, 0);
}

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

void actCommonJump(GObj *volatile self)
{
    float dir[4];
    Act *s = GOBJ_ACT(self);
    int chk = 0;
    int n;

    if (s->intrKind == 236) {
        if (self == girlGObj && boyGObj != 0) {
            _OrientXZGV(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)self));
            SetMotionDirection(self, dir);
        }
    }
    n = s->lastActMode;
    if (n < 4) {
        if (0 < n) {
            switch ((unsigned int)s->intrKind) {
            case 172:
            case 173:
                chk = 1;
                break;
            case 171:
                if (0.1f < s->stick.mag) {
                    chk = 1;
                }
                break;
            }
            if (chk != 0) {
                correctJumpOrientByChain(self);
            }
        }
    }
    while (1) {
        ACTSendMailCorrect(self, 171);
        _ACTWait(1);
    }
}

/* The 0x15C slot is the engine's sub-object handle, read here as the SubHandle
 * union the way geometryManager.c's SUBOF reads it; the other readers use
 * GOBJ_SUB's int view. */
#define FALL_SUB(o) ((Sub15C *)((SubHandle *)((char *)(o) + 0x15C))->p) /* derived name */

void actCommonFall(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    int noVel;
    int wasHigh;
    unsigned int mot;
    int n;

    wasHigh = 0;
    noVel = 0;
    FALL_SUB(self)->ctrl.floorAttr = 0;
    mot = (unsigned int)s->intrKind;
    switch (mot) {
    case 150:
        FALL_SUB(self)->root.move[0] = 0;
        FALL_SUB(self)->root.move[1] = 0;
        FALL_SUB(self)->root.move[2] = 0;
        break;
    case 24:
        FALL_SUB(self)->root.move[0] = 0;
        FALL_SUB(self)->root.move[1] = 0;
        FALL_SUB(self)->root.move[2] = 0;
        wasHigh = 1;
        noVel = 1;
        break;
    case 47:
        sceVu0ScaleVector(&FALL_SUB(self)->root.move[0], test_CURRENTORIENT(self), -5.0f);
        FALL_SUB(self)->root.move[1] = 3.0f;
        wasHigh = 1;
        break;
    default:
        n = s->lastActMode;
        if (n < 29) {
            if (27 <= n) {
                FALL_SUB(self)->root.move[0] = 0;
                FALL_SUB(self)->root.move[1] = 0;
                FALL_SUB(self)->root.move[2] = 0;
                noVel = 1;
            }
        }
        break;
    }
    while (1) {
        if (s->modeFrame < ((60 - systemStatus[0] * 10) / systemStatus[1]) / 6) {
            if (wasHigh) {
                ((ActStatus *)((char *)s + 0x18))->ll |= (1ULL << 46);
            }
            if (noVel) {
                FALL_SUB(self)->root.move[0] = FALL_SUB(self)->root.move[2] = 0.0f;
            }
        }
        ACTSendMailCorrect(self, 283);
        _ACTWait(1);
    }
}

INCLUDE_ASM(func_00154C48);

INCLUDE_ASM(actCommonFly);

INCLUDE_ASM(actCommonLadder);

typedef struct { /* field names derived */
    char pad0[398];
    unsigned short f18E;
} MotRecJ; /* derived name */

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

/* two marker colours (R, G, B, A) func_00154C48 draws with, after cageUpDown */
INCLUDE_ASM(D_0026AD30);

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} FlyPt; /* derived name */

typedef struct { /* field names derived */
    char pad0[1528];
    int f5F8;
} FlyCtlJ; /* derived name */

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

/* inline tail members, defined here: their strings come between the
   flyCoreLoop unit's and funcCommonBeginReady's in .rodata, while their code
   goes to the end of the object */
INCLUDE_ASM_LIT(actCommonCliffdown);

inline void actCommonShoal(GObj *volatile self)
{
    debug_StdPrintfDummy("act main shoal\n");
    _ACTWait(0);
}

inline void actCommonSwim(GObj *volatile self)
{
    debug_StdPrintfDummy("enter actCommonSwim\n");
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonDodge(GObj *volatile self)
{
    float dir[4];
    int id = 0;
    Act *s = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actCommonDodge\n");
    if (self->kind == 1) {
        ACTSearchEnemy((void *)self, &id, dir);
    } else {
        _OrientXZGV(s->dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)self));
        SetMotionDirection(self, s->dir);
    }
    while (1) {
        if (id != 0) {
            SetMotionDirectionWithLimit((void *)self, dir, 10.0f, 90.0f);
        }
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

#undef LADW

inline void actCommonGuard(GObj *volatile self)
{
    debug_StdPrintfDummy("enter actCommonGuard\n");
    SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
    if (self->kind == 4) {
        EBRAIN_SEND_MES((void *)self, 6);
        ACTGame_LwsEffect_Guard((void *)self);
    }
    iosOmSendMail(boyGObj, 257, self);
    for (;;) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void motCommonHangNone(GObj *volatile self)
{
    debug_StdPrintfDummy("enter motCommonHang None\n");
    _ACTWait(0);
}

inline void motCommonHangWall(GObj *volatile self)
{
    debug_StdPrintfDummy("enter motCommonHang Wall\n");
    _ACTWait(0);
}

inline void motCommonHangCliff(GObj *volatile self)
{
    debug_StdPrintfDummy("enter motCommonHang Cliff\n");
    _ACTWait(0);
}

inline void motCommonNull(GObj *volatile self)
{
    debug_StdPrintfDummy("enter motCommonNull\n");
    for (;;) {
        _ACTWait(1);
    }
}

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

int SetMotionDirectionSmooze(GObj *self, float *dir, float s)
{
    float v[4];
    int ret = 0;
    int r;

    if (s < 0.0f) {
        return 0;
    }
    s = s * 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    if (dir[0] == 0.0f && dir[1] == 0.0f && dir[2] == 0.0f) {}
    r = _RotyGV(test_CURRENTORIENT(self), dir);
    if ((float)(r < 0 ? -r : r) < s) {
        ret = 1;
        v[0] = dir[0];
        v[1] = dir[1];
        v[2] = dir[2];
    } else if (r > 0) {
        v[0] = test_CURRENTORIENT(self)[0];
        v[1] = test_CURRENTORIENT(self)[1];
        v[2] = test_CURRENTORIENT(self)[2];
        _ApplyRyGV(v, -s * 3.1415927f / 180.0f);
    } else {
        v[0] = test_CURRENTORIENT(self)[0];
        v[1] = test_CURRENTORIENT(self)[1];
        v[2] = test_CURRENTORIENT(self)[2];
        _ApplyRyGV(v, s * 3.1415927f / 180.0f);
    }
    SetMotionDirection(self, v);
    return ret;
}

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
    w = (char *)GOBJ_SUB(self) + 0x460;
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
                                     (motionKind + GOBJ_SUB(self)->ctrl.motion)->dirFrames);
                        if (debug_font_flag & 1) {
                            debug_Printf(30, 140, 0xFFFFFFF, " file = [%s]\n",
                                         (motionKind + GOBJ_SUB(self)->ctrl.motion)->path);
                        }
                        if (debug_font_flag & 1) {
                            debug_Printf(30, 150, 0xFFFFFFF, " life = [%d]\n", (int)sub->life);
                            if (debug_font_flag & 1) {
                                debug_Printf(30, 160, 0xFFFFFFF, "   dw = [%d] [%d]\n",
                                             (int)*(float *)((char *)sub->motReq + 0x138),
                                             (int)-*(float *)((char *)sub->motReq + 0x130));
                                if (debug_font_flag & 1) {
                                    debug_Printf(30, 170, 0xFFFFFFF, "   dc = [%d] [%d]\n",
                                                 (int)*(float *)((char *)sub->motReq + 0x114),
                                                 (int)*(float *)((char *)sub->motReq + 0x110));
                                    if (debug_font_flag & 1) {
                                        debug_Printf(30, 180, 0xFFFFFFF, "wattr = [%x]\n",
                                                     GOBJ_SUB(self)->ctrl.wallAttr);
                                        if (debug_font_flag & 1) {
                                            debug_Printf(30, 190, 0xFFFFFFF, "bttype= [%d]\n",
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
    if ((mail == 163 || mail == 168) && self->kind == 1) {
        unsigned long long f = s->wish1.ll;
        if (((int)(f >> 54) & 1) && ((int)(s->wish3.ll >> 22) & 1)) {
            mail = 164;
        } else if ((int)(f >> 52) & 1) {
            mail = ((int)(s->wish3.ll >> 20) & 1) ? 165 : mail;
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

INCLUDE_ASM(actCommonBecarry);

INCLUDE_ASM(func_001564C0);

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
        SetDirectRootPosition(obj, v);
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
        SetDirectRootPositionNoFittingWithNodePoint((void *)self, 6, pos, 0.2f);
        if (GOBJ_SUB(self)->ctrl.motion == 196) {
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

void actCommonSlowrun(GObj *volatile self)
{
    float p[2][4];

    while (1) {
        int i1;
        int i2;

        i1 = GetSkeltonFocusNode(girlGObj, 22);
        i2 = GetSkeltonFocusNode(boyGObj, 6);
        ((IntFloatSR *)p[0])[0].f = *(float *)((i1 << 6) + GOBJ_SUB(girlGObj)->nodeMtx + 0x30);
        ((IntFloatSR *)p[0])[1].f = *(float *)((i1 << 6) + GOBJ_SUB(girlGObj)->nodeMtx + 0x34);
        ((IntFloatSR *)p[0])[2].f = *(float *)((i1 << 6) + GOBJ_SUB(girlGObj)->nodeMtx + 0x38);
        ((IntFloatSR *)p[1])[0].f = *(float *)((i2 << 6) + GOBJ_SUB(boyGObj)->nodeMtx + 0x30);
        ((IntFloatSR *)p[1])[1].f = *(float *)((i2 << 6) + GOBJ_SUB(boyGObj)->nodeMtx + 0x34);
        ((IntFloatSR *)p[1])[2].f = *(float *)((i2 << 6) + GOBJ_SUB(boyGObj)->nodeMtx + 0x38);
        if (((motionKind + GOBJ_SUB(girlGObj)->ctrl.motion)->flags.word >> 15) & 1) {
            SetDirectRootPositionNoFittingWithNodePoint((void *)self, 6, p[0], 0.2f);
        } else {
            SetDirectRootPositionNoFittingWithNodePoint((void *)self, 6, p[0], 0.1f);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(_ACTMotDirSmzDirect);

INCLUDE_ASM(WithMailFunc_Idling);

INCLUDE_ASM(WithMailFunc_BossDamaged);

INCLUDE_ASM(actCommonRevive);

INCLUDE_ASM(actCommonReviveAir);

INCLUDE_ASM(actCommonPlay);

INCLUDE_ASM(actCommonOne);

INCLUDE_ASM(actCommonDelete);

typedef struct { /* field names derived */
    char pad0[20];
    int after;    /* 0x14, Act's after function */
} TruckLeverWork; /* derived name */

INCLUDE_ASM(actCommonStoneDead);

INCLUDE_ASM(actCommonSofa);

INCLUDE_ASM(actCommonCatchFire);

INCLUDE_ASM(actCommonCatchFireBomb);

INCLUDE_ASM(actCommonPutFire);

INCLUDE_ASM(actCommonBoxReverbe);

INCLUDE_ASM(actCommonClimb);

INCLUDE_ASM(actCommonCliffdown);

INCLUDE_ASM(actCommonLadderBellow);

inline void actCommonLadderBellowHang(GObj *volatile self)
{
    for (;;) {
        if (!CheckWallAttribute((void *)self, 0x3000) && !CheckWallAttribute((void *)self, 0x400)) {
            ACTSendMailCorrect(self, 202);
        }
        _ACTWait(1);
    }
}

inline void actCommonEdge(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect(self, 301);
        if (-GOBJ_SUB(self)->ctrl.cliffDepth > 250.0f) {
            ACTSendMailCorrect(self, 24);
        }
        _ACTWait(1);
    }
}

inline void actCommonEdgeHang(GObj *volatile self)
{
    while (1) {
        if (CheckWallAttribute(self, 0x1000) == 0) {
            ACTSendMailCorrect(self, 202);
        }
        if (-GOBJ_SUB(self)->ctrl.cliffDepth > 250.0f) {
            ACTSendMailCorrect(self, 24);
        }
        _ACTWait(1);
    }
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
    char pad0[288];
    int moveX; /* 0x120, Sub15C's root.move, held word by word */
    int moveY;
    int moveZ;
} RopeJumpWork; /* derived name */

typedef struct { /* field names derived */
    char pad0[24];
    int f18;
} RopeTurnSpWork; /* derived name */

typedef struct { /* field names derived */
    char pad0[52];
    int pushDir; /* 0x34, Act's pushDir: 1 up the ladder */
} LadderMotWork; /* derived name */

typedef struct { /* field names derived */
    char pad0[52];
    unsigned int pushDir; /* 0x34, Act's pushDir: -1 down the ladder */
} LadderDownMotWork;      /* derived name */

inline void motCommonTruckLeverLoop(GObj *volatile self)
{
    GObj *sw = GOBJ_ACT(self)->env.pullObj;

    _ACTWait(6);
    SetSwitchState(sw, 0);
    debug_StdPrintfDummy("loop");
    _ACTWait(0);
}

inline void motCommonTruckLeverPull(GObj *volatile self)
{
    GObj *sw = GOBJ_ACT(self)->env.pullObj;
    _ACTWait(30);
    SetSwitchState(sw, -1);
    debug_StdPrintfDummy("pull");
    _ACTWait(0);
}

inline void motCommonTruckLeverPush(GObj *volatile self)
{
    GObj *sw = GOBJ_ACT(self)->env.pullObj;
    _ACTWait(30);
    SetSwitchState(sw, 1);
    debug_StdPrintfDummy("push");
    _ACTWait(0);
}

/* StartCorrectPosition and IsCorrectPosition precede test_CURRENTORIENT and
   test_CURRENTROOT, so their calls to the two accessors stay calls. */
typedef union { /* field names derived */
    unsigned long long ll;
    int i;
} CorrFlag; /* derived name */

/* the orient and the position these two accessors hand back */
static sceVu0FVECTOR commonOrient; /* derived name */

static sceVu0FVECTOR commonPos; /* derived name */

static inline void actAfterRopeJump(GObj *volatile self)
{
    char *g = (char *)self;
    GOBJ_ACT(g)->flags20.ll |= (1ULL << 31);
}

static inline void afterCommonRopeCliff(GObj *self)
{
    char *volatile local = (char *)self;
    char *g = *(char **)((char *)boyGObj + 0x15C);
    *(int *)(g + 0x420) = 0;
}

static inline void afterCommonRopeTurnSpecial(GObj *volatile self)
{
    char *g = (char *)self;
    GOBJ_SUB(g)->root.ropeState = 0;
}

typedef struct { /* field names derived */
    char pad0[32];
    unsigned long long status;
} FlySub; /* derived name */

static inline void ClipCollisionWithField(ClipWork *work)
{
    int tmp[4];
    sceVu0CopyVector(tmp, work->pt[1]);
    ClipWallField(work);
    sceVu0CopyVector(work->pt[1], work->pt[2]);
    ClipFloor(work);
    sceVu0CopyVector(work->pt[1], tmp);
}

typedef struct { /* field names derived */
    char pad0[116];
    int coll;
} BecSub; /* derived name */

static inline void afterCommonBecarry(GObj *volatile self)
{
    SetKidnapInfo(-1, -1);
    ((BecSub *)(int)GOBJ_SUB(self))->coll = 1;
    ACTGameCollisionOn((void *)self);
    gflagOff(393);
}

inline void actCommonDodgeJump(GObj *volatile self)
{
    float buf[4];
    int id = 0;
    Act *s = GOBJ_ACT(self);

    if (self->kind == 1) {
        ACTSearchEnemy((void *)self, &id, buf);
    } else {
        _OrientXZGV(s->dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)self));
        SetMotionDirection(self, s->dir);
    }
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonFallDamage(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actCommonTruckLever(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    GObj *lev = s->env.pullObj;

    ((TruckLeverWork *)s)->after = (int)afterCommonTruckLever;
    actMotDirToWall(self);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(self)->ctrl.frameFlag2 != 0) {
                correctTruckLeverHoldPoint((void *)self, lev);
            }
            if (GOBJ_SUB(self)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)self, lev);
            }
        }
        _ACTWait(1);
    }
}

inline void actCommonLever2(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    GObj *lev = s->env.pullObj;

    SetDirectRootPositionXZ((void *)self, s->env.pullPos);
    actMotDirToWall(self);
    while (1) {
        if (lev != 0) {
            /* an empty guard: the frame flag is re-read and nothing is done */
            if (GOBJ_SUB(self)->ctrl.frameFlag2 != 0) {}
            if (GOBJ_SUB(self)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)self, lev);
            }
        }
        _ACTWait(1);
    }
}

inline void actCommonRopeTouchWall(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    while (1) {
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) / 2 < s->modeFrame) {
            ACTSendMailCorrect(self, 153);
        }
        _ACTWait(1);
    }
}

inline void actCommonRopeSwing(GObj *volatile self)
{
    float q[4];
    Act *s = GOBJ_ACT(self);

    LockChainGeo(s->chain);
    ((RopeSwingWork *)s)->f18 = (int)actAfterForceRopeSwing;
    GetCorrectOrientOfChain(q, (void *)self);
    s->ropeSwingX = q[0];
    s->ropeSwingY = q[1];
    s->ropeSwingZ = q[2];
    PlumbOrientUpdateChain(s->chain, q);
    _ACTWait(1);
    while (1) {
        switch (CollisCheckInRope((void *)self, s->chain)) {
        case 1:
            ACTSendMailCorrect(self, 152);
            break;
        case 2:
            ACTSendMailCorrect(self, 151);
            break;
        }
        UnLockChainGeo(s->chain);
        ChainGeo(s->chain);
        LockChainGeo(s->chain);
        SetMotionDirection(self, q);
        _ACTWait(1);
    }
}

inline void actCommonRopeTurn(GObj *volatile self)
{
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonRopeDownEnd(GObj *volatile self)
{
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonRopeJump(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    if (s->intrKind == 151) {
        ((RopeJumpWork *)(int)GOBJ_SUB(self))->moveX = 0;
        ((RopeJumpWork *)(int)GOBJ_SUB(self))->moveY = 0;
        ((RopeJumpWork *)(int)GOBJ_SUB(self))->moveZ = 0;
    }
    _ACTWait(0);
}

inline void actCommonRopeJumpBefore(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect(self, 171);
        _ACTWait(1);
    }
}

inline void actCommonRopeClimbEnd2(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actCommonCornered(GObj *volatile self)
{
    float v[4];

    sceVu0ScaleVector(v, test_CURRENTORIENT(self), -1.0f);
    SetMotionDirection(self, v);
    for (;;) {
        _ACTCharStatus_Set(self, 1, -1.0f, 0);
        _ACTWait(1);
    }
}

inline void actCommonLookaround(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actCommonTurn(GObj *volatile self)
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
                ACTSendMailCorrect(self, 217);
            }
        } else {
            if ((d < 0 ? -d : d) < 15) {
                ACTSendMailCorrect(self, 217);
            }
        }
        _ACTWait(1);
    }
}

inline void actCommonTurnWarn(GObj *volatile self)
{
    float q[4];
    Act *s = GOBJ_ACT(self);
    int prev = s->curMot;

    while (1) {
        int d;

        if (s->curMot != 224) {
            prev = s->curMot;
        } else {
            s->motReq = SetMotionRequest((void *)self, prev, s->env.motOriReq);
        }
        GetRootMotionOrient(q, self);
        d = _RotyGV(&GOBJ_WORK(self)->hideDirX, q);
        if ((d < 0 ? -d : d) < 15) {
            ACTSendMailCorrect(self, 221);
        }
        _ACTWait(1);
    }
}

inline void actCommonTurnStrict(GObj *volatile self)
{
    float q[4];
    float *t = GOBJ_ACT(self)->env.turnDir.f;

    for (;;) {
        int d;

        GetRootMotionOrient(q, self);
        d = _RotyGV(t, q);
        if ((d < 0 ? -d : d) < 15) {
            ACTSendMailCorrect(self, 220);
        }
        _ACTWait(1);
    }
}

inline void actCommonPPipe(GObj *volatile self)
{
    _ACTWait(0);
}

inline void actCommonHandrail(GObj *volatile self)
{
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonOneWall(GObj *volatile self)
{
    GOBJ_ACT(self)->after = (void *)afterCommonOneWall;
    _ACTWait(0);
}

inline void motCommonBoxPush(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    s->pushDir = 1;
    while (1) {
        actMotDirToWall(self);
        _ACTWait(1);
    }
}

inline void motCommonBoxPull(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    s->pushDir = -1;
    while (1) {
        actMotDirToWall(self);
        _ACTWait(1);
    }
}

inline void motCommonBarPush(GObj *volatile self)
{
    GOBJ_ACT(self)->pushDir = 1;
    _ACTWait(0);
}

inline void motCommonBarPull(GObj *volatile self)
{
    char *g = (char *)self;
    GOBJ_ACT(g)->pushDir = 0xFFFFFFFFu;
    _ACTWait(0);
}

inline void motCommonLadderUp(GObj *volatile self)
{
    LadderMotWork *s = (LadderMotWork *)(char *)GOBJ_ACT(self);

    while (1) {
        s->pushDir = 1;
        switch (GOBJ_ACT(self)->enemy->ladderUpStep) {
        case 1:
            ACTSendMailCorrect(self, 126);
        case 2:
            ACTSendMailCorrect(self, 127);
            break;
        }
        _ACTWait(1);
    }
}

inline void motCommonLadderDown(GObj *volatile self)
{
    LadderDownMotWork *s = (LadderDownMotWork *)(char *)GOBJ_ACT(self);

    while (1) {
        s->pushDir = -1;
        switch (GOBJ_ACT(self)->enemy->ladderDownStep) {
        case 1:
            ACTSendMailCorrect(self, 126);
        case 2:
            ACTSendMailCorrect(self, 127);
            break;
        }
        _ACTWait(1);
    }
}

inline void motCommonSlip(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    while (1) {
        long long f = (long long)s->wish1.ll;

        if (!((((int)(f >> 6) & 1) && ((int)(s->wish2.ll >> 38) & 1)) ||
              (((int)(f >> 7) & 1) && ((int)(s->wish2.ll >> 39) & 1)))) {
            ACTSendMailCorrect(self, 177);
        }
        _ACTWait(1);
    }
}

inline void motCommonRopejumpDircorrect(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);

    for (;;) {
        SetMotionDirection(self, &s->ropeSwingX);
        _ACTWait(1);
    }
}

inline void funcCommonRopeBefore(GObj *self, int mail, GObj *chain)
{
    GOBJ_ACT(self)->chain = chain;
}

inline void extraCommonNull(GObj *volatile self)
{
    for (;;) {
        _ACTWait(1);
    }
}

inline void extraCommonCall(GObj *volatile self)
{
    if (girlGObj) {
        iosOmSendMail(girlGObj, 62, isysCurrentGObj);
    }
    for (;;) {
        _ACTWait(1);
    }
}

inline void funcCommonWayOn(GObj *self)
{
    if (self == girlGObj) {
        girlcalled = 1;
    }
}

inline void funcCommonSofaWakeup(GObj *self)
{
    GOBJ_ACT(self)->enemy->sofaWake = 0;
}

inline int _ACTMotReqResult(GObj *self, int mot)
{
    Act *s = GOBJ_ACT(self);
    char *r = SetMotionRequest(self, mot, s->env.motOriReq);
    s->motReq = r;
    return *(int *)(r + 0xC) != 0;
}

inline void StartCorrectPosition(GObj *self, float *pos, float *dir, int mode, float t)
{
    GOBJ_ACT(self)->enemy->corrPosX = test_CURRENTROOT(self)[0];
    GOBJ_ACT(self)->enemy->corrPosY = test_CURRENTROOT(self)[1];
    GOBJ_ACT(self)->enemy->corrPosZ = test_CURRENTROOT(self)[2];
    GOBJ_ACT(self)->enemy->corrDirX = test_CURRENTORIENT(self)[0];
    GOBJ_ACT(self)->enemy->corrDirY = test_CURRENTORIENT(self)[1];
    GOBJ_ACT(self)->enemy->corrDirZ = test_CURRENTORIENT(self)[2];
    GOBJ_ACT(self)->enemy->corrDstX = pos[0];
    GOBJ_ACT(self)->enemy->corrDstY = pos[1];
    GOBJ_ACT(self)->enemy->corrDstZ = pos[2];
    if (dir != 0) {
        GOBJ_ACT(self)->enemy->corrDstDirX = dir[0];
        GOBJ_ACT(self)->enemy->corrDstDirY = dir[1];
        GOBJ_ACT(self)->enemy->corrDstDirZ = dir[2];
    }
    GOBJ_ACT(self)->enemy->corrFrames = (int)t;
    GOBJ_ACT(self)->enemy->corrCount = 0;
    ((CorrFlag *)((char *)GOBJ_ACT(self)->enemy + 0xB8))->i = mode;
    ((CorrFlag *)((char *)GOBJ_ACT(self)->enemy + 0xB8))->ll |= (1ULL << 32);
}

inline int IsCorrectPosition(GObj *self)
{
    unsigned long long v = GOBJ_ACT(self)->enemy->corrFlags;
    return (int)v & 1;
}

inline float *test_CURRENTORIENT(GObj *self)
{
    if (self != boyGObj && self != girlGObj && self->kind != 4) {
        GetRootOrient(commonOrient, self);
        return commonOrient;
    }
    {
        float *p = GOBJ_ACT(self)->jump;
        _GetMotionDirection(p, self);
        return p;
    }
}

inline float *test_CURRENTROOT(GObj *self)
{
    float buf[4];
    float *p;

    switch (self->kind) {
    case 1:
    case 2:
    case 4:
        p = (float *)(char *)GOBJ_ACT(self);
        p = (float *)((char *)p + 0xE0);
        GetRootPosition(p, self);
        return p;
    case 42:
        GetCageChainPoint(commonPos, buf, self);
        return commonPos;
    default:
        GetRootPosition(commonPos, self);
        return commonPos;
    }
}

inline void ControlMotionOrient(int id, int mot)
{
    motionOrient[id].w[2] = mot;
}

inline void _ACTMotDir_V(void *self, void *dir)
{
    float local[4];
    sceVu0ScaleVector(local, dir, -1.0f);
    SetMotionDirection(self, local);
}

inline void ACTMotDirToWall(GObj *self)
{
    actMotDirToWall(self);
}

inline void SetCorrectOrientOfChain(void *self)
{
    setCorrectOrientOfChain(self);
}

inline void actAfterForceRopeSwing(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    if (s->chain == 0) {
        debug_assert("src/commonact.c", 1386);
        __assert("src/commonact.c", 1386, "ROPE_GOBJ!=NULL");
    }
    UnLockChainGeo(s->chain);
}

inline void actAfterDown(GObj *volatile self)
{
    GOBJ_WORK(self)->downTimer = ((60 - systemStatus[0] * 10) / systemStatus[1]) * 130 / 60;
}

inline void afterCommonCling(volatile unsigned int self)
{
    ACTGameCollisionOn((void *)self);
}

inline void actAfterSlip(int x)
{
    volatile int local = x;
}

inline void afterCommonRevive(volatile unsigned int self)
{
    ACTGameCollisionOn((void *)self);
}

inline void afterCommonStone(GObj *volatile self)
{
    GObj *g1 = self;
    GObj *g2 = self;
    GOBJ_ACT(g1)->enemy->stonePair = -1;
    GOBJ_ACT(g2)->enemy->word2A4 = 0;
}

inline void afterCommonBox(GObj *volatile self)
{
    _boxbar_set_sound(self, 0);
}

/* the fly's after function (actCommonFly stores it); this build has no
   actAfterJump or actAfterFall copy */
inline void actAfterFly(GObj *volatile self)
{
    char *g = (char *)self;
    GOBJ_ACT(g)->flags18.ll |= (1ULL << 61);
}

inline void afterCommonOneWall(int x)
{
    volatile int local = x;
}

inline int ACTCheckFlagAttack(GObj *self)
{
    return GOBJ_ACT(self)->actMode == 15;
}

inline void afterCommonTruckLever(GObj *volatile self)
{
    char *g = (char *)self;
    SetSwitchState(GOBJ_ACT(g)->env.pullObj, 0);
}
