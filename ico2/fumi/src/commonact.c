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

static void ACTSetPositionNoFitting(void *self, float *pos);

void ACTSetPositionNodeWithFitting(void *self, int node, float *pos, float t)
{
    SetDirectRootPositionWithNodePoint(self, node, pos, t);
}

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
            case 304:
                if (q[1] < p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < 200.0f) {
                    ret = 310;
                }
                break;
            case 305:
                if (q[1] > p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < 200.0f) {
                    ret = 310;
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

int _ACTCorrectMsg(GObj *self, int msg, void *param)
{
    float pos[4];
    Act *sk = GOBJ_ACT(self);
    int fast = _ACTGame_GetParamF(2) < GOBJ_SUB(self)->ctrl.groundHeight;

    switch (msg) {
    case 240:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 12) & 1) {
            msg = 384;
            debug_StdPrintfDummy("ignore");
        }
        break;
    case 278:
        if (sk->actMode == 5 && *(int *)((char *)GOBJ_ACT(self)->work + 0x810) == 26) {
            msg = 384;
        }
        break;
    case 277:
        if (sk->actMode == 1 &&
            *(long long *)((char *)GOBJ_ACT(self)->work + 0x810) == 0x1A00000005LL) {
            msg = 384;
        }
        break;
    case 304:
    case 305:
        msg = ChangeMailInLadder(self, msg);
        break;
    case 221:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 8) & 1) {
            msg = 384;
        } else if ((int)(sk->flags20.ll >> 2) & 1) {
            msg = 220;
        }
        break;
    case 222:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 8) & 1) {
            msg = 384;
        }
        break;
    case 212:
        if (GOBJ_WORK(self)->turnTimer != 0) {
            msg = 384;
        } else if ((int)(sk->flags20.ll >> 2) & 1) {
            msg = 214;
        }
        break;
    case 213:
        if (GOBJ_WORK(self)->turnTimer2 != 0) {
            msg = 384;
        } else if ((int)(sk->flags20.ll >> 2) & 1) {
            msg = 215;
        }
        break;
    case 316:
    case 317:
    case 318:
        if (gameover_flag != 0) {
            msg = 384;
        }
        break;
    case 186:
        if (sk->msgBlockTimer != 0) {
            msg = 384;
        }
        break;
    case 159:
        if (fast) {
            msg = 384;
        }
        break;
    case 26:
        if (GOBJ_SUB(self)->ctrl.waterDepth < (self == boyGObj ? 110.0f : 135.0f)) {
            msg = 384;
        }
        /* fallthrough */
    case 199:
        if (self->kind == 4) {
            msg = 204;
            if (self->labelId == 3415) {
                msg = 384;
            }
        }
        break;
    case 200:
        if (self->kind == 4) {
            msg = 204;
            if (self->labelId == 3415) {
                msg = 384;
                if (13 <= sk->frame) {
                    msg = 30;
                    iosOmSendMail(self, 29, param);
                }
            }
        }
        break;
    case 21:
        if (sk->actMode == 62 && param == sk->lastChain) {
            msg = 384;
        }
        if (fast) {
            msg = 384;
        }
        if (IsAbleChainHang(param) == 0) {
            msg = 384;
        }
        break;
    case 20:
        if (IsAbleChainHang(param) == 0) {
            msg = 384;
        }
        break;
    case 7:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->modeBits.word >> 16) & 7) {
            if (sk->heldItem.i != 0) {
                msg = 293;
            }
        }
        break;
    case 10: {
        int iv = (int)GOBJ_SUB(self)->ctrl.fallHeight;
        int flagA = 0;
        int flagB = 0;

        if (120.0f < GOBJ_SUB(self)->ctrl.fallHeight) {
            ACTWay_SetBeginPositionIllegal(self);
            /* disabled in retail: the way-begin-position (WBP) report of the
               landing */
            if (0) {
                debug_StdPrintfDummy("WBP set [landing]\n");
            }
        }
        if (!(((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 19) & 1)) {
            msg = 384;
            break;
        }
        if (iv < 130) {
            iosOmSendMail(self, 56, param);
        }
        if (self == girlGObj && ACTGame_FLAG_TETSUNAGI()) {
            iosOmSendMail(self, 55, param);
            if (iv < 130) {
                iosOmSendMail(self, 54, param);
            }
        }
        if (_ACTGame_GetParamF(2) < (float)iv) {
            flagA = 1;
        } else if (_ACTGame_GetParamF(1) < (float)iv) {
            flagB = 1;
        }
        switch (sk->actMode) {
        case 92:
            flagB = 1;
            break;
        case 93:
            flagA = 1;
            break;
        }
        if (flagA) {
            msg = 43;
        } else if (flagB) {
            msg = 42;
        }
        break;
    }
    case 14:
        debug_StdPrintfDummy("critical hit to boss!!!");
        if (GOBJ_ACT(self)->enemy->bossLife <= 1) {
            msg = 273;
        } else {
            msg = 266;
        }
        break;
    case 13: {
        float d = sk->life - (float)GOBJ_ACT(self)->damage;

        if (self == boyGObj) {
            d = sk->life = 100.0f;
        }
        if (GOBJ_ACT(self)->unguardable != 0) {
            debug_StdPrintfDummy("!!! unable guard flag get\n");
        }
        if (stage_no == 83 || debug_use_new_queen_battle != 0) {
            if (GOBJ_ACT(self)->stoneHit != 0) {
                if (ACTGame_NoWeapon(self) != 0 && sk->actMode != 14) {
                    msg = 102;
                    GOBJ_ACT(self)->enemy->liftLevel = 10;
                    BoySekikaTexScroll();
                    GOBJ_ACT(self)->enemy->stoneHitNoWeapon += 1;
                    break;
                } else {
                    msg = 263;
                    GOBJ_ACT(self)->enemy->stoneHitWeapon += 1;
                    GOBJ_ACT(self)->enemy->liftLevel = 10;
                    break;
                }
            }
        }
        if (_AbsRotyGV(test_CURRENTORIENT(self), GOBJ_ACT(self)->attackDir) < 60 &&
            sk->actMode != 15 && sk->actMode != 20 && GOBJ_ACT(self)->unguardable == 0 &&
            !((int)(sk->flags18.ll >> 46) & 1)) {
            iosOmSendMail(self, 264, param);
            debug_StdPrintfDummy("guard mail\n");
        } else {
            debug_StdPrintfDummy("guard error=[%d][%d][%d][%d]\n",
                                 _AbsRotyGV(test_CURRENTORIENT(self), GOBJ_ACT(self)->attackDir),
                                 sk->actMode, 15, 20);
        }
        if (GOBJ_ACT(self)->stoneHit != 0) {
            GOBJ_ACT(self)->enemy->stoneLevel += 1;
            GOBJ_ACT(self)->enemy->liftLevel = 10;
        }
        if (self->kind == 4 && GOBJ_ACT(self)->enemy->liftKind == 3) {
            if (GOBJ_ACT(self)->enemy->slowTimer <= 0) {
                DamageFunc(self);
                iosPadActRequest(boyPad, 2);
                pos[0] = test_CURRENTROOT(self)[0];
                pos[1] = test_CURRENTROOT(self)[1];
                pos[2] = test_CURRENTROOT(self)[2];
                soundSeDefPlay(382, 0, pos, 1);
            }
            msg = 384;
            GOBJ_ACT(self)->enemy->slowTimer = 60;
            break;
        }
        if (self == boyGObj && *(int *)(param + 0xC) == 17) {
            msg = 384;
            break;
        }
        if (self->kind == 4 && sk->actMode == 16 &&
            (char *)GOBJ_ACT(self)->enemy->clingTarget == (char *)girlGObj) {
            msg = 196;
            break;
        }
        if (self->kind == 4 && GOBJ_ACT(self)->enemy->liftKind != 3 &&
            EnemyGetNSafeParts(self) < 8) {
            msg = 273;
            debug_StdPrintfDummy("die!!!!!!!!!!!\n");
            break;
        }
        if (d < 0.0f) {
            msg = 273;
            if (self == boyGObj) {
                msg = 272;
                sk->life = 100.0f;
            }
            debug_StdPrintfDummy("die!!!!!!!!!!!\n");
            break;
        }
        if (GOBJ_ACT(self)->downHit != 0 || _ACTCharStatus_Check(self, 14) != 0) {
            msg = 272;
            debug_StdPrintfDummy("down!!!!!!!!!!!\n");
            break;
        }
        {
            int dir = GetHitDirIdx(self);

            msg = dir + 268;
            debug_StdPrintfDummy("damage!!!!!!!!!!!  %d\n", dir);
        }
        break;
    }
    }
    return msg;
}

/* the motion each interrupt kind requests, indexed by the kind */
static int intrMotion[388] = {
    0,   0,   0,   0,   0,   0,   104, 104, 54,  0,   1,   0,   0,   0,   0,   194, 195, 0,   0,
    0,   76,  77,  0,   143, 106, 147, 151, 1,   17,  19,  20,  0,   0,   0,   118, 0,   -1,  -1,
    129, 236, -1,  110, 144, 145, 0,   0,   0,   108, 107, 132, 133, 134, 232, 233, 4,   1,   4,
    0,   0,   0,   56,  57,  58,  0,   0,   0,   1,   0,   1,   0,   101, 12,  7,   1,   94,  1,
    0,   102, 103, 15,  13,  1,   84,  91,  1,   0,   0,   0,   1,   1,   0,   0,   0,   1,   1,
    0,   0,   0,   1,   0,   0,   18,  118, 119, 120, 0,   61,  62,  63,  1,   79,  80,  79,  146,
    146, 64,  65,  66,  67,  69,  68,  70,  71,  71,  73,  72,  111, 112, 113, 114, 110, 115, 110,
    135, 135, 77,  175, 176, 177, 178, 179, 137, 113, 114, 180, 182, 181, 184, 183, 174, 143, 185,
    186, 187, 75,  74,  0,   0,   0,   76,  185, 179, 188, 0,   5,   6,   7,   8,   9,   13,  14,
    12,  15,  16,  21,  23,  23,  22,  24,  1,   1,   2,   34,  35,  11,  1,   37,  37,  38,  45,
    44,  44,  46,  43,  42,  105, 129, 153, 7,   0,   151, 1,   152, 153, 145, 51,  52,  105, 173,
    81,  227, 47,  195, 194, 197, 196, 197, 196, 195, 194, 12,  7,   198, 195, 194, 198, 198, 0,
    59,  60,  1,   12,  1,   0,   228, 105, 0,   0,   0,   236, 236, 229, 25,  236, 10,  11,  10,
    1,   7,   1,   0,   190, 191, 192, 193, 26,  27,  28,  29,  30,  31,  32,  33,  121, 121, 122,
    130, 131, 123, 124, 125, 126, 128, 129, 0,   54,  53,  48,  49,  50,  55,  135, 136, 115, 148,
    149, 54,  54,  116, 117, 54,  104, 104, 109, 84,  85,  86,  85,  87,  88,  89,  82,  53,  83,
    137, 138, 139, 140, 141, 142, 143, 0,   0,   0,   237, 238, 168, 171, 171, 170, 169, 172, 199,
    208, 209, 200, 201, 202, 203, 204, 205, 201, 212, 7,   1,   213, 214, 215, 215, 216, 217, 218,
    219, 220, 222, 223, 154, 155, 156, 154, 155, 156, 157, 158, 158, 159, 159, 0,   0,   160, 161,
    162, 94,  163, 1,   164, 165, 166, 167, 165, 105, 1,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0}; /* derived name */

int ACTGetOrientFromIntrK(GObj *self, int k, MotOriReq *out, int arg)
{
    Act *s = GOBJ_ACT(self);
    MotOriTarget tmp;
    int ret = intrMotion[k];

    *out = s->env.motOriReq;
    switch (k) {
    case 285:
        out->a = GOBJ_WORK(self)->cliffReq;
        break;
    case 278:
        *(char **)((char *)s + 0x2C) = GetMailAdditionalData(self, arg);
        tmp = *(MotOriTarget *)(*(char **)((char *)GOBJ_ACT(self) + 0x2C));
        out->b = s->env.motOriReq.b = tmp;
        break;
    case 53:
        *(char **)((char *)s + 0x2C) = GetMailAdditionalData(self, arg);
        tmp = *(MotOriTarget *)(*(char **)((char *)GOBJ_ACT(self) + 0x2C));
        out->a = out->b = s->env.motOriReq.a = s->env.motOriReq.b = tmp;
        s->env.sofaObj.obj = tmp.obj;
        GetSofaPosition(self, s->env.sofaObj.obj);
        break;
    case 133:
        out->a = GOBJ_WORK(self)->bellowWall3000;
        break;
    case 132:
        out->a = GOBJ_WORK(self)->bellowWall400;
        break;
    case 106:
    case 107:
    case 108:
    case 109:
        out->b = s->env.motOriReq.a;
        break;
    case 44:
        return GOBJ_ACT(self)->enemy->jumpOrient;
    case 59:
        if (s->actMode == 74) {
            ret = 238;
        }
        break;
    case 346:
    case 347:
    case 348:
        out->b = out->a = s->env.cliffContact.b;
        break;
    case 349:
        *out = s->env.cliffContact = GOBJ_ACT(boyGObj)->env.cliffContact;
        break;
    case 350:
    case 351:
    case 352:
        *out = s->env.cliffContact;
        break;
    case 353:
    case 354:
        *out = s->env.supportReq;
        s->env.motOriReq = *out;
        break;
    case 186:
    case 187:
    case 188:
        if (self == boyGObj) {
            if (ACTGame_NoWeapon(self)) {
                ret = 36;
            } else {
                ret = ACTGame_GetMotOrientFromWeapon(s->weapon);
            }
        }
        break;
    case 67:
    case 69:
    case 312:
        ret = s->orientMot;
        break;
    case 76:
        ret = s->orientMot;
        out->a = GOBJ_ACT(boyGObj)->env.motOriReq.b;
        s->env.motOriReq = *out;
        break;
    case 365:
    case 369:
        out->a = GOBJ_ACT(boyGObj)->env.motOriReq.b;
        s->env.motOriReq = *out;
        break;
    case 382:
        if (s->soundMot != 0) {
            ret = s->soundMot;
            s->soundMot = 0;
        } else {
            ret = 0;
        }
        break;
    case 140:
    case 142:
    case 143:
        out->a = *(MotOriTarget *)&GOBJ_ACT(self)->enemy->climbCol;
        break;
    default:
        ret = intrMotion[k];
        break;
    }
    return ret;
}

void ACTRunIntrCorrect(GObj *self, IntrMail *intr, IntrMail *corr)
{
    Act *s = GOBJ_ACT(self);
    inline void setIntrFlags(void) /* derived name */
    {
        IntrMail *p;

        for (p = intr; p != 0 && (short)p->kind != 392; p++) {
            p->flags |= 0x40000;
        }
    }
    inline void correctIntrList(void) /* derived name */
    {
        IntrMail *ip;
        IntrMail *q;

        for (q = corr; q != 0 && (short)q->kind != 392; q++) {
            if (q->mode == -1) {
                for (ip = intr; ip != 0 && (short)ip->kind != 392; ip++) {
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
    if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 18) & 1) {
        actIntrList[10].flags |= 0x40000;
    } else {
        actIntrList[10].flags &= ~0x40000;
    }
    if (s->actMode == 26) {
        if (s->modeFrame < ((60 - systemStatus[0] * 10) / systemStatus[1]) / 3) {
            actIntrList[348].flags |= 0x40000;
        } else {
            actIntrList[348].flags &= ~0x40000;
        }
    }
}

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

void WithMailFunc_AttackRejectInQueen(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    GObj *w = s->weapon;
    if (w != 0) {
        ReleaseWeaponWithFumbleSequential(w);
        s->weapon = 0;
    }
    if (stage_no == 83 || debug_use_new_queen_battle != 0) {
        void *e = isysGObjSearchFromObjKindID_begin(53);
        if (e != 0) {
            iosOmSendMail(e, 13, self);
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
    if ((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word & 1) {
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

INCLUDE_ASM_LIT(afterCommonRope);

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
            ACTSendMailCorrect(self, 154);
            break;
        case 2:
            ACTSendMailCorrect(self, 153);
            break;
        }
        if (chainFloorHit(self, &work)) {
            ACTSendMailCorrect(self, 155);
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
            ActSendMail_WithAdditionalData(self, 140, (void *)self,
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
            ACTSendMailCorrect(self, 310);
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
            ACTSendMailCorrect(self, 310);
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
    while (GOBJ_SUB(self)->ctrl.motion != 116) {
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
        ACTSendMailCorrect(self, 141);
        GetSkeltonPosition(hand, self, 22);
        GetSkeltonPosition(foot, self, 6);
        base[0] = c.v1[0];
        base[1] = c.v1[1];
        base[2] = c.v1[2];
        if (c.obj->kind == 43) {
            TestCageUpDown(c.obj, (void *)self);
        }
        GOBJ_ACT(self)->enemy->climbCol = c.climbCol;
        if (hand[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(self, 142);
        }
        if (foot[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(self, 143);
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
            SetDirectRootPositionNoFitting((void *)self, cur);
        }
        if (GOBJ_SUB(self)->ctrl.motion == 116) {
            p[0] = test_CURRENTROOT((void *)self)[0];
            p[1] = test_CURRENTROOT((void *)self)[1];
            p[2] = test_CURRENTROOT((void *)self)[2];
            p[1] = p[1] + 5.0f;
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
        _InterGV(dst, lo, hi, dst[1] - lo[1], hi[1] - dst[1]);
        sceVu0ScaleVector(res, test_CURRENTORIENT(o), -15.0f);
        sceVu0AddVector(res, dst, res);
        ACTSetPositionNodeWithFitting(o, 0x23, res, 1.0f);
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
    case 118:
        break;
    case 117:
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
    case 119:
    case 120:
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
        vA[2] = *(float *)(*(char **)(((CagePtr *)&boyGObj->dobj)->p + 0xC) + n * 0x40 + 0x38);
        _InterGV(vA, vB, vC, vA[1] - vB[1], vC[1] - vA[1]);
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

void actCommonRopeSpecial(GObj *volatile self)
{
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
        if (GOBJ_SUB(self)->ctrl.motion == 116) {
            *(long long *)((char *)s + 0x20) &= ~(1ULL << 1);
        }
        GetSkeltonPosition(pos.f, self, 35);
        GetCageChainPoint(p1.f, p2.f, cage);
        if (debug_font_flag & 1) {
            debug_Printf(10, 120, 0xFFFFFFF, "%d, %d\n",
                         (int)*(float *)((char *)test_CURRENTROOT((void *)self) + 4), (int)p2.f[1]);
        }
        if (*(float *)((char *)test_CURRENTROOT((void *)self) + 4) > p2.f[1] - 30.0f) {
            ACTSendMailCorrect(self, 180);
        }
        if (found && pos.f[1] < p1.f[1] + 10.0f) {
            GOBJ_ACT(self)->enemy->climbObj = cage;
            GetOrientOfWall(GOBJ_ACT(self)->enemy->climbOrient, hit.wall, &hit.wallSrc);
            GOBJ_ACT(self)->enemy->climbPos[0] = p1.f[0];
            GOBJ_ACT(self)->enemy->climbPos[1] = p1.f[1];
            GOBJ_ACT(self)->enemy->climbPos[2] = p1.f[2];
            GOBJ_ACT(self)->enemy->climbPos[1] -= 100.0f;
            GOBJ_ACT(self)->enemy->climbCol = hit;
            ActSendMail_WithAdditionalData(self, 161, (void *)self,
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
    SetDirectRootPositionNoFitting(self, pos);
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
    /* this build has no ...NoFittingWithNodePointXZ (0x1561B0 jal 0x102A10) */
    SetDirectRootPositionNoFittingWithNodePoint(self, 22, w, 0.2f);
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

INCLUDE_ASM_LIT(actCommonPlay);

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

INCLUDE_ASM_LIT(actCommonDamage);

void actCommonDown(GObj *volatile self)
{
    float v[4];
    Act *s = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actCommonDown\n");
    s->flags18.afterProc = actAfterDown;
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
    while (1) {
        if (self->kind != 4) {
            GOBJ_ACT(self)->hit = 1;
        }
        ACTSendMailCorrect(self, 180);
        _ACTWait(1);
    }
}

void actCommonDie(GObj *volatile self)
{
    /* a helper defined at the head of this body */
    inline void dieNotifyObjects(void) /* derived name */
    {
        void *g;

        if (self->labelId == 3415) {
            gamesysObjInfoCls(4, 3415);
            gamesysObjInfoCls(33, 3416);
        }
        g = isysGObjSearchFromObjKindID_begin(46);
        if (g == 0) {
            g = isysGObjSearchFromObjKindID_begin(63);
        }
        if (self->kind == 4 && g != 0) {
            iosOmSendMail(g, 18, self);
        }
    }
    Act *s = GOBJ_ACT(self);
    int cnt = 0;
    float t;
    int corpse;

    if (s->intrKind == 43) {
        corpse = 1;
    } else {
        corpse = 0;
    }
    debug_StdPrintfDummy("enter actCommonDie\n");
    SetMotionDirection(self, GOBJ_ACT(self)->attackDir);
    DownFunc(self);
    GOBJ_ACT(self)->hit = 1;
    dieNotifyObjects();
    while (1) {
        if (corpse) {
            ACTSetPositionWithFitting((void *)self, test_CURRENTROOT((void *)self));
        }
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
                if ((int)((long long)s->flags20.ll >> 8) & 1) {
                    t += 10.0f;
                }
                _ACTWait(1);
            }
            actEnemyHyde(self);
            _ACTWait(0);
        }
        if (self == boyGObj || self == girlGObj) {
            if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 2 < cnt) {
                ACT_LAYOUT_GAMEOVER();
                _ACTWait(0);
            }
        }
        cnt++;
        _ACTWait(1);
    }
}

INCLUDE_ASM(Cling_173);

INCLUDE_ASM(actCommonCling);

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

INCLUDE_ASM_LIT(actCommonRevive);

typedef struct { /* field names derived */
    char pad0[20];
    int after; /* 0x14, Act's after function */
} ReviveSub;   /* derived name */

typedef struct { /* field names derived */
    char pad0[20];
    int after; /* 0x14, Act's after function */
    char pad18[48];
    int modeFrame; /* 0x48, Act's frames since the mode changed (actCommonStone 0x156CA0) */
} StoneSub;        /* derived name */

void actCommonStone(GObj *volatile self)
{
    StoneSub *s = (StoneSub *)(char *)GOBJ_ACT(self);

    s->after = (int)afterCommonStone;
    *(int *)(*(char **)(*(char **)((char *)self + 0x164) + 0x670) + 0x2A0) = 0;
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
            ACTSendMailCorrect(self, 180);
            GOBJ_ACT(self)->enemy->stoneLevel = 0;
        }
        if (s->modeFrame >= 61 && GOBJ_ACT(self)->enemy->stoneLevel >= 3) {
            ACT_LAYOUT_GAMEOVER();
            _ACTWait(0);
        }
        ACTSendMailCorrect(self, 104);
        _ACTWait(1);
    }
}

static void BoxBarSoundOn(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    switch (s->actMode) {
    case 49:
        ExecBoxMoveStartReaction(s->box, (int)s->pushDir);
        break;
    case 51:
        ExecRotObjectMoveStartReaction(s->env.barObj);
        break;
    }
}

static void BoxBarSoundOff(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    switch (s->actMode) {
    case 49:
        ExecBoxMoveEndReaction(s->box);
        break;
    case 51:
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

void actCommonBox(GObj *volatile self)
{
    GObj *box;
    /* a helper defined at the head of this body */
    inline void addGirlLevelForBox(GObj * b) /* derived name */
    {
        if (girlGObj != 0 && GOBJ_SUB(girlGObj)->parent.obj == b) {
            brainAddLevelGirl(1000.0f);
        }
    }
    Act *s = GOBJ_ACT(self);
    GObj *sub;
    float hold[4];
    int dbg = 0; /* local debug switch, see the test after the hold point below */

    s->after = afterCommonBox;
    box = s->env.holdBoxObj;
    if (stage_no == 16) {
        sub = GOBJ_SUB(box)->parent.obj;
        if (sub != 0) {
            if (sub->kind == 17) {
                box = sub;
            }
        }
    }
    ((Act *)(char *)s)->box = box;
    actMotDirToWall(self);
    while (1) {
        int had = (int)s->pushDir != 0;
        int f2 = 0;
        int miss = 0;
        int flag = 0;
        unsigned char isTruck = IsThisBoxTruck(box);

        addGirlLevelForBox(box);
        GetBoxHoldPoint(hold, box, self);
        if (!isTruck) {
            if (boxWallCheck(self, box, 100.0f, 48)) {
                ACTSendMailCorrect(self, 180);
                miss = 1;
            }
            if (s->pushDir == 0xFFFFFFFF) {
                if (boxWallCheck(self, box, 150.0f, 48)) {
                    miss = 1;
                }
            }
        }
        if (!miss && (isTruck == 0 ? *(int *)((char *)GOBJ_SUB(self) + 0x5F8)
                                   : GOBJ_SUB(self)->ctrl.frameFlag1)) {
            f2 = 1;
            if ((int)s->pushDir == 1 && boxWallCheck(self, box, -25.0f, 30)) {
                miss = 1;
            } else {
                float dir[4];
                unsigned char ok;
                if (s->pushDir == 0xFFFFFFFF) {
                    dir[0] = s->env.wallOrient[0];
                    dir[1] = s->env.wallOrient[1];
                    dir[2] = s->env.wallOrient[2];
                } else {
                    sceVu0ScaleVector(dir, s->env.wallOrient, -1.0f);
                }
                if (!isTruck) {
                    AlignBox(box, 100.0f);
                }
                ok = MoveBoxWithHoldPoint(box, hold, self, 22, dir);
                if (ok) {
                    flag = 1;
                } else {
                    miss = 1;
                }
            }
        }
        if (GetMotionFrameFlag2((void *)self)) {
            float pos[4];
            GetBoxGlobalHoldPoint(pos, box, hold);
            SetDirectRootPositionNoFittingWithNodePoint(
                (void *)self, 22, pos, GOBJ_SUB(self)->ctrl.frameFlag1 != 0 ? 1.0f : 0.3f);
            /* a local debug switch, off: mark the global hold point. The
               August TRFILE (3132-3136) and the PAL listing (3379-3383) have
               five code-less lines here, this block's length; the text is
               derived. */
            if (dbg) {
                debug_NMarker(pos, 255, 0, 0, 100.0f);
            }
        }
        if (!had) {
            _boxbar_set_sound(self, 0);
            if (!isTruck) {
                AlignBox(box, 100.0f);
            }
        } else if (f2) {
            _boxbar_set_sound(self, 1);
        }
        if (flag) {
            _boxbar_set_sound(self, 3);
        }
        if (miss) {
            _boxbar_set_sound(self, 2);
        }
        if (!isTruck && GetBoxMode(box) == 0) {
            s->flags20.ll |= (1ULL << 16);
            s->flags20.ll |= (1ULL << 17);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM_LIT(afterCommonBar);

/* Sub15C's root.filter (0x1B0, actCommonBar 0x15746C sw s1,432(v1)), set word
   by word to the bar the actor holds; afterCommonBar resets it */
typedef struct { /* field names derived */
    char pad0[432];
    int filterObj;
    int filterNode;
    int filterElem;
} BarHold; /* derived name */

void actCommonBar(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    GObj *bar;
    float pos[4];
    float ori[4];
    float hold[4];
    float hold2[4];

    bar = s->env.barObj;
    actMotDirToWall(self);
    pos[0] = *(float *)((char *)test_CURRENTROOT((void *)self) + 0);
    pos[1] = *(float *)((char *)test_CURRENTROOT((void *)self) + 4);
    pos[2] = *(float *)((char *)test_CURRENTROOT((void *)self) + 8);
    ori[0] = *(float *)((char *)test_CURRENTORIENT(self) + 0);
    ori[1] = *(float *)((char *)test_CURRENTORIENT(self) + 4);
    ori[2] = *(float *)((char *)test_CURRENTORIENT(self) + 8);
    GetRotObjectHoldPoint(hold, hold2, &GOBJ_WORK(self)->intrReq.a.wall, (void *)self);
    s->bar = bar;
    s->after = (void *)afterCommonBar;
    debug_StdPrintfDummy("set %p\n", bar);
    ((BarHold *)(int)GOBJ_SUB(self))->filterObj = (int)bar;
    ((BarHold *)(int)GOBJ_SUB(self))->filterNode = -1;
    ((BarHold *)(int)GOBJ_SUB(self))->filterElem = 0;
    while (1) {
        int had = (int)s->pushDir != 0;
        int lit = 0;
        int miss = 0;
        int flag = 0;
        if (GetMotionFrameFlag1((void *)self)) {
            float dir[4];
            float up[4];
            int node = GetSkeltonFocusNode((void *)self, 32);
            unsigned char ok;
            lit = 1;
            CopyVector(dir, (char *)GOBJ_SUB(self)->nodeMtx + node * 64 + 0x30);
            if (s->pushDir == 0xFFFFFFFF) {
                sceVu0ScaleVector(up, test_CURRENTORIENT(self), -1.0f);
            } else {
                up[0] = *(float *)((char *)test_CURRENTORIENT(self) + 0);
                up[1] = *(float *)((char *)test_CURRENTORIENT(self) + 4);
                up[2] = *(float *)((char *)test_CURRENTORIENT(self) + 8);
            }
            ok = MoveRotObjectWithHoldPoint(bar, hold, (void *)self, dir, up);
            if (ok) {
                flag = 1;
            } else {
                miss = 1;
            }
        }
        if (GetMotionFrameFlag2((void *)self)) {
            GetRotObjectGlobalHoldGeometry(pos, ori, bar, hold, hold2);
            SetDirectRootPositionNoFittingWithNodePoint((void *)self, 0x20, pos, lit ? 1.0f : 0.3f);
            SetMotionDirection(self, ori);
        }
        if (!had) {
            _boxbar_set_sound(self, 0);
        } else if (lit && !miss) {
            _boxbar_set_sound(self, 1);
        }
        if (flag) {
            _boxbar_set_sound(self, 3);
        }
        if (miss) {
            _boxbar_set_sound(self, 2);
        }
        _ACTWait(1);
    }
}

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

void actCommonJump(GObj *volatile self)
{
    float dir[4];
    Act *s = GOBJ_ACT(self);
    int chk = 0;
    int n;

    if (s->intrKind == 242) {
        if (self == girlGObj && boyGObj != 0) {
            _OrientXZGV(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)self));
            SetMotionDirection(self, dir);
        }
    }
    n = *(int *)((char *)GOBJ_ACT(self)->work + 0x810);
    if (n < 4) {
        if (0 < n) {
            switch ((unsigned int)s->intrKind) {
            case 175:
            case 176:
                chk = 1;
                break;
            case 174:
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
        ACTSendMailCorrect(self, 174);
        _ACTWait(1);
    }
}

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

    for (i = 0, n = 1, q = (int *)((char *)s->work + 0x838); i < 10; i++, q++) {
        if (q[-10] == state && (mot == 384 || mot == q[10])) {
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

void actCommonFall(GObj *volatile self)
{
    float pa[4];
    float pb[4];
    float hit[4];
    float lo[4];
    float hi[4];
    Act *s = GOBJ_ACT(self);
    int noVel;
    int wasHigh;
    unsigned int mot;
    int keep;
    int n;

    wasHigh = 0;
    noVel = 0;
    ((Act *)(char *)s)->flags18.afterProc = actAfterFall;
    if (stageData[stage_no].flag3) {
        keep = FALL_SUB(self)->ctrl.floorAttr & 0xF;
        debug_StdPrintfDummy("0x%8x -> 0x%8x\n", FALL_SUB(self)->ctrl.floorAttr, keep);
        FALL_SUB(self)->ctrl.floorAttr = 0;
        FALL_SUB(self)->ctrl.floorAttr = keep;
    } else {
        FALL_SUB(self)->ctrl.floorAttr = 0;
    }
    mot = (unsigned int)s->intrKind;
    switch (mot) {
    case 152:
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
    case 48:
        sceVu0ScaleVector(&FALL_SUB(self)->root.move[0], test_CURRENTORIENT(self), -5.0f);
        FALL_SUB(self)->root.move[1] = 3.0f;
        wasHigh = 1;
        break;
    case 47:
        GetSkeltonPosition(pa, s->intrArg, 44);
        GetSkeltonPosition(pb, self, 44);
        lo[0] = pb[0];
        lo[1] = pb[1];
        lo[2] = pb[2];
        if (ACTCheckCollis_WAY(40.0f, pa, pb, 0, hit)) {
            lo[0] = pa[0];
            lo[1] = pa[1];
            lo[2] = pa[2];
            SetRootPosition(self, pa);
        }
        hi[0] = lo[0];
        hi[1] = lo[1];
        hi[2] = lo[2];
        lo[1] = lo[1] - 100.0f;
        hi[1] = hi[1] + 100.0f;
        if (ACTCheckCollis_WELL(lo, hi, 0, 0.0f, hit)) {
            hit[1] = hit[1] - 105.0f;
            SetRootPosition(self, hit);
        }
        break;
    default:
        n = *(int *)((char *)GOBJ_ACT(self)->work + 0x810);
        if (19 <= n) {
            if (22 <= n) {
                if (n < 29) {
                    if (27 <= n) {
                        FALL_SUB(self)->root.move[0] = 0;
                        FALL_SUB(self)->root.move[1] = 0;
                        FALL_SUB(self)->root.move[2] = 0;
                        noVel = 1;
                    }
                }
            } else {
                wasHigh = 1;
            }
        }
        if ((unsigned char)IsFallStuckOnStep(self, 5, 384, 2, 60)) {
            ((Act *)(char *)s)->flags20.ll |= (1ULL << 18);
        }
        break;
    }
    while (1) {
        if (s->modeFrame < ((60 - systemStatus[0] * 10) / systemStatus[1]) / 6) {
            if (wasHigh) {
                ((ActStatus *)((char *)s + 0x18))->ll |= (1ULL << 47);
            }
            if (noVel) {
                FALL_SUB(self)->root.move[0] = FALL_SUB(self)->root.move[2] = 0.0f;
            }
        }
        ACTSendMailCorrect(self, 292);
        _ACTWait(1);
    }
}

/* the sub-object's fly-limit flag at 0x644 (flyCoreLoop 0x158F9C sw zero,1604(v0)) */
typedef struct { /* field names derived */
    char pad0[1604];
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
    h += -VectorLength(d) * (stage_no == 84 || stage_no == 3 || stage_no == 46 ? 2.5f : 0.5f);
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

INCLUDE_ASM(col_274);

INCLUDE_ASM(getLandOffset_262);

INCLUDE_ASM(getAvoidCollisionFlyLevel);

INCLUDE_ASM(emergencyCheck_281);

INCLUDE_ASM(flyCoreLoop);

/* Sub15C's ctrl.floorAttr (0x5E8, actCommonFly 0x159174 sw zero,1512(v0)) */
typedef struct { /* field names derived */
    char pad0[1512];
    int floorAttr;
} FlyCtlJ; /* derived name */

void actCommonFly(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    GObj *target;
    GObj *gen = 0;

    s->flags18.afterProc = actAfterFly;

    ((FlyCtlJ *)(char *)GOBJ_SUB(self))->floorAttr = 0;

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
                (girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 107 &&
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

#define LADW ((LadderWork *)*(int *)(self->act + 0x670)) /* derived name */

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
    if (mot == 111 || mot == 112) {
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
            ACTSendMailCorrect(self, 131);
        }
        if (self == boyGObj && girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 38) {
            if (_DistSqGV(test_CURRENTROOT((void *)self), test_CURRENTROOT(girlGObj)) < 3600.0f) {
                ACTSendMailCorrect(self, 48);
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
                        ACTSendMailCorrect(self, 48);
                        break;
                    }
                }
            }
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM_LIT(actCommonCliffdown);

INCLUDE_ASM_LIT(actCommonShoal);

INCLUDE_ASM_LIT(actCommonSwim);

INCLUDE_ASM_LIT(actCommonDodge);

INCLUDE_ASM_LIT(actCommonGuard);

/* inline tail members, defined here: their strings come between the
   flyCoreLoop unit's and funcCommonBeginReady's in .rodata, while their code
   goes to the end of the object */
#undef LADW

void actCommonEdgeHang(GObj *volatile self)
{
    ClipWork work;
    float p1[4];
    float p2[4];

    ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.a.wall);
    while (1) {
        if (CheckWallAttributeEdegWall(self) == 0) {
            ACTSendMailCorrect(self, 207);
        }
        if (-GOBJ_SUB(self)->ctrl.cliffDepth > 250.0f) {
            ACTSendMailCorrect(self, 24);
        }
        if (stageData[stage_no].flag2) {
            memset(&work, 0, 0xC0);
            GetSkeltonPosition(work.pt[0], self, 44);
            GetSkeltonPosition(p1, self, 51);
            GetSkeltonPosition(p2, self, 47);
            sceVu0AddVector(work.pt[1], p1, p2);
            sceVu0ScaleVector(work.pt[1], work.pt[1], 0.5f);
            ClipFloor(&work);
            if (work.floor.elem != 0) {
                ACTSendMailCorrect(self, 207);
            }
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM_LIT(motCommonHangNone);

INCLUDE_ASM_LIT(motCommonHangWall);

INCLUDE_ASM_LIT(motCommonHangCliff);

INCLUDE_ASM_LIT(motCommonNull);

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
    if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 9) & 1 &&
        *(long long *)((char *)GOBJ_ACT(self)->work + 0x810) == 0x1A00000005LL) {
        s = 30.0f;
    }
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
    if ((mail == 166 || mail == 171) && self->kind == 1) {
        unsigned long long f = s->wish0.ll;
        if (((int)(f >> 60) & 1) && ((int)(s->wish2.ll >> 60) & 1)) {
            mail = 167;
        } else if ((int)(f >> 58) & 1) {
            mail = ((int)(s->wish2.ll >> 58) & 1) ? 168 : mail;
        }
    }
    iosOmSendMail(self, mail, self);
}

void _ACTCommonMailTest(GObj *self, int stopCnt, int walkCnt, int runCnt)
{
    Act *s;
    int ret = 0;
    unsigned int m;

    s = GOBJ_ACT(self);
    if (s->pad.trg & 8) {
        handoff_heroin();
    }
    m = (unsigned int)s->actMode;
    switch (m) {
    case 1:
    case 2:
    case 3:
    case 14:
    case 76:
    case 112:
        ret = 1;
        break;
    case 36:
    case 15:
    case 20:
    case 21:
        ret = self == boyGObj;
        break;
    }
    if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 30) & 1) {
        ret = 1;
    }
    if (ret) {
        if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
            ACTSendMailCorrect(self, 306);
        }
        if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269) &&
            !(s->actMode == 3 && ((int)(s->flags18.ll >> 39) & 1))) {
            ACTSendMailCorrect(self, 307);
            if (((int)(s->flags20.ll >> 4) & 1) && !((int)(s->flags18.ll >> 39) & 1)) {
                ACTSendMailCorrect(self, 173);
            }
        }
        if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
            ACTSendMailCorrect(self, 308);
        }
        if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
            ACTSendMailCorrect(self, 309);
        }
        if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)) &&
            !(walkCnt < 4)) {
            ACTSendMailCorrect(self, 166);
        }
        /* the negated conjunct is the walk guard's whole predicate, repeated;
           it emits a real (dead) branch, so it is in the shipped code. */
        if (0.1f < s->stick.mag &&
            !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) &&
            !(runCnt < 4)) {
            ACTSendMailCorrect(self, 171);
        }
        if (!(0.1f < s->stick.mag) && 0 < stopCnt) {
            ACTSendMailCorrect(self, 180);
        }
    }
    if (s->actMode == 73) {
        if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)) &&
            !(walkCnt < 4)) {
            ACTSendMailCorrect(self, 166);
        }
        /* the negated conjunct is the walk guard's whole predicate, repeated;
           it emits a real (dead) branch, so it is in the shipped code. */
        if (0.1f < s->stick.mag &&
            !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) &&
            !(runCnt < 4)) {
            ACTSendMailCorrect(self, 171);
        }
    }
}

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
    const BecPair *end = tbl + 33;
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
        SetMotionRequest(self, 234, *(MotOriReq *)((char *)sub + 0x610));
        motionOrient[n].w[2] = save0;
        motionOrient[n].w[4] = save1;
        return 1;
    }
    return 0;
}

void actCommonBecarry(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    int cur = -1;
    GObj *g;
    int old;
    unsigned char done;
    int n;
    float p[4];
    float q[4];
    float pos[4];
    float o[4];
    float v[4];

    g = s->carrier;
    s->flags18.ll &= ~(1ULL << 41);
    n = (int)((50.0f - _DistxzGV(test_CURRENTROOT(g), test_CURRENTROOT((void *)self))) / 5.0f);
    n = n < 0 ? -n : n;
    _ACTWait(1);
    while (1) {
        _ACTCharStatus_Set(self, 9, -1.0f, 0);
        old = cur;
        cur = GOBJ_SUB(g)->ctrl.motion;
        if (old != cur) {
            done = requestBecarryMotion(self, cur, (GOBJ_ACT(g)->actMode == 100) ? 30 : 0, 1793);
            if (!done) {
                s->flags18.ll |= (1ULL << 41);
            }
        }
        if (6 <= s->modeFrame) {
            if (actModeTbl[GOBJ_ACT(g)->actMode].carried ||
                motionKind[GOBJ_SUB(g)->ctrl.motion].flags.bits.carried) {
                afterCommonCarry(g);
                debug_StdPrintfDummy("girl becarry error");
            }
        }
        switch (GOBJ_SUB(self)->ctrl.motion) {
        case 620:
        case 622:
            if (n > 0) {
                n--;
                p[0] = test_CURRENTROOT((void *)self)[0];
                p[1] = test_CURRENTROOT((void *)self)[1];
                p[2] = test_CURRENTROOT((void *)self)[2];
                q[0] = test_CURRENTROOT(g)[0];
                q[1] = test_CURRENTROOT(g)[1];
                q[2] = test_CURRENTROOT(g)[2];
                o[0] = test_CURRENTORIENT(g)[0];
                o[1] = test_CURRENTORIENT(g)[1];
                o[2] = test_CURRENTORIENT(g)[2];
                sceVu0ScaleVector(v, o, 5.0f);
                sceVu0AddVector(pos, p, v);
                SetDirectRootPositionNoFitting((void *)self, pos);
            } else if (GOBJ_SUB(self)->ctrl.animFrame < 20.0f) {
                _OrientXZGV(q, test_CURRENTROOT(girlGObj), test_CURRENTROOT(g));
                SetMotionDirection(g, q);
            }
            break;
        }
        if (debug_font_flag & 1) {
            debug_Printf(100, 150, 0xFFFFFFF, "[%s]\n",
                         (motionKind + GOBJ_SUB(girlGObj)->ctrl.motion)->name);
        }
        if (debug_font_flag & 1) {
            debug_Printf(100, 160, 0xFFFFFFF, "[%s]\n",
                         motionKind[GOBJ_SUB(s->carrier)->ctrl.motion].name);
        }
        if (debug_font_flag & 1) {
            debug_Printf(100, 170, 0xFFFFFFF, "[%s]\n",
                         actModeTbl[GOBJ_ACT(s->carrier)->actMode].name);
        }
        _ACTWait(1);
    }
}

static inline void SetIdleMotionRange(int k, int mot, int mot2) /* derived name */
{
    int n1 = actDataTbl[k].orientRow;
    int n2 = actDataTbl[k].orientRow2;
    int n3 = actDataTbl[k].orientFirst;
    int n4 = actDataTbl[k].orientEnd;
    int i;

    if (mot != 1088 && mot2 != 1088) {
        motionOrient[n1].w[2] = mot;
        motionOrient[n2].w[2] = mot2;
        for (i = n3; i < n4; i++) {
            motionOrient[i].w[0] = mot;
        }
    }
}

INCLUDE_ASM(subCommonIdle);

INCLUDE_ASM(ContinueCorrectPosition);

INCLUDE_ASM(actCommonTurn);

INCLUDE_ASM(actCommonBackhand);

typedef union { /* field names derived */
    int i;
    float f;
} IntFloatSR; /* derived name */

INCLUDE_ASM(actCommonSlowrun);

typedef struct { /* field names derived */
    char pad0[20];
    int f14;
} TruckLeverWork; /* derived name */

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

INCLUDE_ASM_LIT(motCommonTruckLeverLoop);

INCLUDE_ASM_LIT(motCommonTruckLeverPull);

INCLUDE_ASM_LIT(motCommonTruckLeverPush);

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
static sceVu0FVECTOR commonOrient; /* derived name */

static sceVu0FVECTOR commonPos; /* derived name */

typedef struct { /* field names derived */
    char pad0[32];
    unsigned long long status;
} FlySub; /* derived name */

typedef struct { /* field names derived */
    char pad0[116];
    int coll;
} BecSub; /* derived name */

INCLUDE_ASM(_ACTMotDirSmzDirect);

INCLUDE_ASM(WithMailFunc_Idling);

INCLUDE_ASM(WithMailFunc_BossDamaged);

INCLUDE_ASM(WithMailFunc_FallDead);

INCLUDE_ASM(actCommonRevive);

INCLUDE_ASM(actCommonReviveAir);

INCLUDE_ASM(actCommonPlay);

INCLUDE_ASM(actCommonOne);

INCLUDE_ASM(actCommonDelete);

INCLUDE_ASM(actCommonSofa);

INCLUDE_ASM(actCommonCatchFire);

INCLUDE_ASM(actCommonCatchFireBomb);

INCLUDE_ASM(actCommonPutFire);

INCLUDE_ASM(actCommonBoxReverbe);

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

INCLUDE_ASM(actCommonTruckLever);

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

INCLUDE_ASM(_ACTMotDir_V);

INCLUDE_ASM(ACTMotDirToWall);

INCLUDE_ASM(SetCorrectOrientOfChain);

INCLUDE_ASM(actAfterForceRope);

INCLUDE_ASM(actAfterForceRopeSwing);

INCLUDE_ASM(actAfterDown);

INCLUDE_ASM(afterCommonCling);

INCLUDE_ASM(actAfterSlip);

INCLUDE_ASM(afterCommonRevive);

INCLUDE_ASM(afterCommonStone);

INCLUDE_ASM(afterCommonBox);

INCLUDE_ASM(afterCommonBar);

INCLUDE_ASM(actAfterFall);

INCLUDE_ASM(actAfterFly);

INCLUDE_ASM(afterCommonOneWall);

INCLUDE_ASM(ACTCheckFlagAttack);

INCLUDE_ASM(afterCommonTruckLever);
