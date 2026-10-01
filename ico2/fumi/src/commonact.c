#include "enemy.h"
#include "enemy_act.h"
#include "isys.h"
#include <assert.h>
#include "camera-editor.h"
#include "ebrain.h"

/* prototypes: their order is the inline tail's emission order (gcc emits every
   inline at the end of the object in first-declaration order). They precede
   commonact.h, whose alphabetical list would otherwise fix that order. */
void ACTAcceptMail(GObj *a0, int a1);
inline int _ACTMotDirSmzDirect(char *a0, float *a1);
void WithMailFunc_Idling(GObj *a0);
void WithMailFunc_BossDamaged(GObj *a0);
void WithMailFunc_FallDead(GObj *a0);
void actCommonRevive(GObj *volatile a0);
void actCommonReviveAir(GObj *volatile a0);
void actCommonPlay(GObj *volatile a0);
void actCommonOne(GObj *volatile a0);
void actCommonDelete(GObj *volatile a0);
void actCommonCatchFire(GObj *volatile a0);
void actCommonCatchFireBomb(GObj *volatile a0);
void actCommonPutFire(GObj *volatile a0);
void actCommonBoxReverbe(GObj *volatile a0);
void actCommonItem(GObj *volatile a0);
void actCommonClimb(GObj *volatile a0);
void actCommonCliffdown(GObj *volatile a0);
void actCommonLadderBellow(GObj *volatile a0);
void actCommonLadderBellowHang(GObj *volatile a0);
void actCommonEdge(GObj *volatile a0);
void actCommonDodge(GObj *volatile a0);
void actCommonDodgeJump(GObj *volatile a0);
void actCommonGuard(GObj *volatile a0);
void actCommonFallDamage(GObj *volatile a0);
void actCommonDamage(GObj *volatile a0);
void actCommonShoal(GObj *volatile a0);
void actCommonSwim(GObj *volatile a0);
void actCommonLever2(GObj *volatile a0);
void actCommonRopeTouchWall(GObj *volatile a0);
void actCommonRopeSwing(GObj *volatile a0);
void actCommonRopeTurn(GObj *volatile a0);
void actCommonRopeDownEnd(GObj *volatile a0);
void actCommonRopeJump(GObj *volatile a0);
void actCommonRopeJumpBefore(GObj *volatile a0);
void actCommonRopeTurnSpecial(GObj *volatile a0);
void actCommonRopeClimbEnd2(GObj *volatile a0);
void actCommonCornered(GObj *volatile a0);
void actCommonLookaround(GObj *volatile a0);
void actCommonTurnWarn(GObj *volatile a0);
void actCommonTurnStrict(GObj *volatile a0);
void actCommonPPipe(GObj *volatile a0);
void actCommonHandrail(GObj *volatile a0);
void actCommonOneWall(GObj *volatile a0);
void motCommonNull(GObj *volatile a0);
void motCommonBoxPush(GObj *volatile a0);
void motCommonBoxPull(GObj *volatile a0);
void motCommonBarPush(GObj *volatile a0);
void motCommonBarPull(GObj *volatile a0);
void motCommonLadderUp(GObj *volatile a0);
void motCommonLadderDown(GObj *volatile a0);
void motCommonSlip(GObj *volatile a0);
void motCommonRopejumpDircorrect(GObj *volatile a0);
void motCommonHangNone(GObj *volatile a0);
void motCommonHangWall(GObj *volatile a0);
void motCommonHangCliff(GObj *volatile a0);
void motCommonRopeTurnSpecialR(GObj *volatile a0);
void motCommonRopeTurnSpecialL(GObj *volatile a0);
void motCommonTruckLeverLoop(GObj *volatile a0);
void motCommonTruckLeverPull(GObj *volatile a0);
void motCommonTruckLeverPush(GObj *volatile a0);
void funcCommonRopeBefore(GObj *a0, int a1, int a2);
void afterCommonRope(GObj *volatile a0);
void extraCommonNull(GObj *volatile a0);
void extraCommonCall(GObj *volatile a0);
void funcCommonWayOn(GObj *a0);
void funcCommonSofaWakeup(GObj *a0);
int _ACTMotReqResult(GObj *a0, int a1);
inline float *test_CURRENTORIENT(GObj *a0);
inline float *test_CURRENTROOT(GObj *a0);
void StartCorrectPosition(GObj *a0, float *pos, float *dir, int mode, float t);
int IsCorrectPosition(GObj *a0);
void ControlMotionOrient(int a0, int a1);
int FloorIsTruck(GObj *a0);
void _ACTMotDir_V(void *a0, void *a1);
void ACTMotDirToWall(GObj *a0);
void SetCorrectOrientOfChain(void *a0);
void actAfterForceRope(GObj *volatile a0);
inline void actAfterForceRopeSwing(GObj *volatile a0);
inline void actAfterRopeJump(GObj *volatile a0);
inline void afterCommonRopeCliff(char *a0);
inline void afterCommonRopeTurnSpecial(GObj *volatile a0);
inline void actAfterDown(GObj *volatile a0);
void afterCommonCling(volatile unsigned int a0);
void actAfterSlip(int x);
inline void afterCommonRevive(volatile unsigned int a0);
inline void afterCommonStone(GObj *volatile a0);
inline void afterCommonBox(GObj *volatile a0);
void afterCommonBar(GObj *volatile a0);
inline void actAfterJump(GObj *volatile a0);
inline void actAfterFall(GObj *volatile a0);
inline void actAfterFly(GObj *volatile a0);
inline void ClipCollisionWithField(char *a0);
inline void afterCommonOneWall(int x);
int ACTCheckFlagAttack(GObj *a0);
inline void afterCommonBecarry(GObj *volatile a0);
inline void afterCommonTruckLever(GObj *volatile a0);

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

typedef struct { /* field names derived */
    int a, b, c;
} Blob12; /* derived name */

typedef struct { /* field names derived */
    int w[6];
} SlowrunRec; /* derived name */

void ACTSetPositionWithFitting(void *a0, float *pos)
{
    SetDirectRootPosition(a0, pos);
}

void ACTSetPositionNoFitting(void *a0, float *pos)
{
    SetDirectRootPositionNoFitting(a0, pos);
}

void ACTSetPositionNodeWithFitting(int a0, int a1, int a2, float a3)
{
    SetDirectRootPositionWithNodePoint(a0, a1, a2, a3);
}

int ChangeMailInLadder(GObj *a0, int a1)
{
    float p[4];
    float q[4];
    Act *s = GOBJ_ACT(a0);
    int ret = a1;
    int flag = 0;
    float lim1;
    float lim2;

    if ((char *)boyGObj != 0 && (char *)girlGObj != 0) {
        if (a0 == boyGObj) {
            if (s->actMode == 0x26) {
                flag = (GOBJ_ACT(girlGObj)->actMode == 0x26);
            }
        }
        if (a0 == girlGObj) {
            if (s->actMode == 0x26) {
                flag = 1;
            }
        }
        if (flag != 0 &&
            _DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 3600.0f) {
            lim1 = a0 == boyGObj ? 175.0f : 225.0f;
            lim2 = a0 == boyGObj ? 175.0f : 210.0f;
            if (a0 == boyGObj) {
                p[0] = test_CURRENTROOT(a0)[0];
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
            switch (a1) {
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

void DamageFunc(char *a0);
extern int IsAbleChainHang(char *a0);
extern int EnemyGetNSafeParts(char *a0);
/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* a static inline used only by _ACTCorrectMsg */
static inline int GetHitDirIdx(GObj *self) /* derived name */
{
    char *p = (char *)GOBJ_ACT(self) + 0x1C0;
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
    case 309:
        if (!(((int)(sk->flags18.ll >> 53) & 1) &&
              GOBJ_WORK(self)->fallDamageHeight < GOBJ_SUB(self)->ctrl.groundHeight)) {
            msg = 418;
        }
        break;
    case 42:
        if (!(((int)(sk->flags18.ll >> 53) & 1) &&
              GOBJ_WORK(self)->fallDamageHeight < GOBJ_SUB(self)->ctrl.groundHeight)) {
            msg = 418;
        }
        break;
    case 259:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 9) & 1) {
            msg = 418;
        }
        break;
    case 298:
        if (sk->actMode == 5 && *(int *)((char *)GOBJ_ACT(self)->work + 0x900) == 26) {
            msg = 418;
        }
        break;
    case 297:
        if (sk->actMode == 1 &&
            *(long long *)((char *)GOBJ_ACT(self)->work + 0x900) == 0x1A00000005LL) {
            msg = 418;
        }
        break;
    case 330:
    case 331:
        msg = ChangeMailInLadder(self, msg);
        break;
    case 240:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 5) & 1) {
            msg = 418;
        } else if ((int)(sk->flags20.ll >> 14) & 1) {
            msg = 239;
        }
        break;
    case 241:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 5) & 1) {
            msg = 418;
        }
        break;
    case 231:
        if (GOBJ_WORK(self)->turnTimer != 0) {
            msg = 418;
        } else if ((int)(sk->flags20.ll >> 14) & 1) {
            msg = 233;
        }
        break;
    case 232:
        if (GOBJ_WORK(self)->turnTimer2 != 0) {
            msg = 418;
        } else if ((int)(sk->flags20.ll >> 14) & 1) {
            msg = 234;
        }
        break;
    case 348:
    case 349:
    case 350:
        if (gameover_flag != 0) {
            msg = 418;
        }
        break;
    case 205:
        if (sk->msgBlockTimer != 0) {
            msg = 418;
        }
        break;
    case 174:
        if (fast) {
            msg = 418;
        }
        if (((int)(sk->flags18.ll >> 53) & 1) &&
            GOBJ_SUB(self)->ctrl.groundHeight < GOBJ_WORK(self)->fallDamageHeight) {
            msg = 418;
        }
        break;
    case 26:
        if (GOBJ_SUB(self)->ctrl.waterDepth < (self == boyGObj ? 110.0f : 135.0f)) {
            msg = 418;
        }
        /* fallthrough */
    case 218:
        if (self->kind == 4) {
            msg = 223;
            if ((int)(sk->flags20.ll >> 30) & 1) {
                msg = 418;
            }
        }
        break;
    case 219:
        if (self->kind == 4) {
            msg = 223;
            if ((int)(sk->flags20.ll >> 30) & 1) {
                msg = 418;
                if (13 <= sk->frame) {
                    msg = 30;
                    iosOmSendMail(self, 29, param);
                }
            }
        }
        break;
    case 21:
        if (sk->actMode == 62 && param == sk->lastChain) {
            msg = 418;
        }
        if (fast) {
            msg = 418;
        }
        if (IsAbleChainHang(param) == 0) {
            msg = 418;
        }
        if (((int)(sk->flags18.ll >> 53) & 1) &&
            GOBJ_SUB(self)->ctrl.groundHeight < GOBJ_WORK(self)->fallDamageHeight) {
            msg = 418;
        }
        break;
    case 20:
        if (IsAbleChainHang(param) == 0) {
            msg = 418;
        }
        if (((int)(sk->flags18.ll >> 53) & 1) &&
            GOBJ_SUB(self)->ctrl.groundHeight < GOBJ_WORK(self)->fallDamageHeight) {
            msg = 418;
        }
        break;
    case 7:
        if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->modeBits.word >> 19) & 7) {
            if (sk->heldItem.i != 0) {
                msg = 315;
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
        if (!(((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags.word >> 25) & 1)) {
            msg = 418;
            break;
        }
        if (iv < 130) {
            iosOmSendMail(self, 59, param);
        }
        if (self == girlGObj && ACTGame_FLAG_TETSUNAGI()) {
            iosOmSendMail(self, 58, param);
            if (iv < 130) {
                iosOmSendMail(self, 57, param);
            }
        }
        if (*(int *)((char *)GOBJ_ACT(self)->work + 0x900) == 38) {
            iosOmSendMail(self, 60, self);
        }
        if (_ACTGame_GetParamF(2) < (float)iv) {
            flagA = 1;
        } else if (_ACTGame_GetParamF(1) < (float)iv) {
            flagB = 1;
        }
        switch (sk->actMode) {
        case 95:
            flagB = 1;
            break;
        case 96:
            flagA = 1;
            break;
        }
        if (flagA) {
            msg = 44;
        } else if (flagB) {
            msg = 43;
        }
        if (*(int *)((char *)GOBJ_ACT(self)->work + 0x900) == 21) {
            iosOmSendMail(self, 56, param);
            if (msg == 43) {
                iosOmSendMail(self, 55, param);
            }
        }
        break;
    }
    case 14:
        debug_StdPrintfDummy("critical hit to boss!!!");
        if (GOBJ_ACT(self)->enemy->bossLife <= 1) {
            msg = 293;
        } else {
            msg = 285;
        }
        break;
    case 13: {
        float d = sk->life - (float)GOBJ_ACT(self)->damage;

        if (self == boyGObj || self == girlGObj) {
            d = sk->life = 100.0f;
        }
        if (GOBJ_ACT(self)->unguardable != 0) {
            debug_StdPrintfDummy("!!! unable guard flag get\n");
        }
        if (stage_no == 85 || debug_use_new_queen_battle != 0) {
            if (GOBJ_ACT(self)->stoneHit != 0) {
                if (ACTGame_NoWeapon(self) != 0 && sk->actMode != 14) {
                    msg = 110;
                    GOBJ_ACT(self)->enemy->liftLevel = 10;
                    BoySekikaTexScroll();
                    GOBJ_ACT(self)->enemy->count2A8 += 1;
                    break;
                } else {
                    msg = 282;
                    GOBJ_ACT(self)->enemy->count2AC += 1;
                    GOBJ_ACT(self)->enemy->liftLevel = 10;
                    break;
                }
            }
        }
        if (_AbsRotyGV(test_CURRENTORIENT(self), (void *)((int)GOBJ_ACT(self) + 0x1C0)) < 60 &&
            sk->actMode != 15 && sk->actMode != 20 && GOBJ_ACT(self)->unguardable == 0 &&
            !((int)(sk->flags18.ll >> 51) & 1)) {
            iosOmSendMail(self, 283, param);
            debug_StdPrintfDummy("guard mail\n");
        } else {
            debug_StdPrintfDummy(
                "guard error=[%d][%d][%d][%d]\n",
                _AbsRotyGV(test_CURRENTORIENT(self), (void *)((int)GOBJ_ACT(self) + 0x1C0)),
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
            msg = 418;
            GOBJ_ACT(self)->enemy->slowTimer = 60;
            break;
        }
        if (self == boyGObj && *(int *)(param + 0xC) == 17) {
            msg = 418;
            break;
        }
        if (self->kind == 4 && sk->actMode == 16 &&
            (char *)GOBJ_ACT(self)->enemy->clingTarget == (char *)girlGObj) {
            msg = 215;
            break;
        }
        if (self->kind == 4 && GOBJ_ACT(self)->enemy->liftKind != 3 &&
            EnemyGetNSafeParts(self) < 8) {
            msg = 293;
            debug_StdPrintfDummy("die!!!!!!!!!!!\n");
            break;
        }
        if (d < 0.0f) {
            msg = 293;
            if (self == boyGObj) {
                msg = 291;
                sk->life = 100.0f;
            }
            debug_StdPrintfDummy("die!!!!!!!!!!!\n");
            break;
        }
        if (GOBJ_ACT(self)->downHit != 0 || _ACTCharStatus_Check(self, 16) != 0) {
            msg = 291;
            debug_StdPrintfDummy("down!!!!!!!!!!!\n");
            break;
        }
        {
            int dir = GetHitDirIdx(self);

            msg = dir + 287;
            debug_StdPrintfDummy("damage!!!!!!!!!!!  %d\n", dir);
        }
        break;
    }
    }
    return msg;
}

typedef struct { /* field names derived */
    float x, y, z;
} IntrVec3; /* derived name */

typedef struct { /* field names derived */
    IntrVec3 a;
    float aw;
    IntrVec3 b;
    float bw;
} IntrOrient; /* derived name */

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

int ACTGetOrientFromIntrK(char *self, int k, void *buf, int arg)
{
    IntrOrient *out = (IntrOrient *)buf;
    Act *s = GOBJ_ACT(self);
    IntrVec3 tmp;
    int ret = intrMotion[k];

    *out = *(IntrOrient *)((char *)s + 0x620);
    switch (k) {
    case 140:
        out->b = ((IntrOrient *)((char *)GOBJ_ACT(self)->work + 0x480))->b;
        break;
    case 305:
        out->a = ((IntrOrient *)((char *)GOBJ_ACT(self)->work + 0x480))->a;
        break;
    case 298:
        *(char **)((char *)s + 0x30) = GetMailAdditionalData(self, arg);
        tmp = *(IntrVec3 *)(*(char **)((char *)GOBJ_ACT(self) + 0x30));
        out->b = ((IntrOrient *)((char *)s + 0x620))->b = tmp;
        break;
    case 54:
        *(char **)((char *)s + 0x30) = GetMailAdditionalData(self, arg);
        tmp = *(IntrVec3 *)(*(char **)((char *)GOBJ_ACT(self) + 0x30));
        out->a = out->b = ((IntrOrient *)((char *)s + 0x620))->a =
            ((IntrOrient *)((char *)s + 0x620))->b = tmp;
        s->sofaObj = *(int *)&tmp;
        GetSofaPosition(self, (char *)s->sofaObj);
        break;
    case 145:
        out->a = *(IntrVec3 *)((char *)GOBJ_ACT(self)->work + 0x3D8);
        break;
    case 144:
        out->a = *(IntrVec3 *)((char *)GOBJ_ACT(self)->work + 0x3CC);
        break;
    case 114:
    case 115:
    case 116:
    case 117:
        out->b = ((IntrOrient *)((char *)s + 0x620))->a;
        break;
    case 45:
        return GOBJ_ACT(self)->enemy->jumpOrient;
    case 63:
        if (s->actMode == 0x4A) {
            ret = 272;
        }
        break;
    case 378:
    case 379:
    case 380:
        out->b = out->a = ((IntrOrient *)((char *)s + 0x640))->b;
        break;
    case 381:
        *out = *(IntrOrient *)((char *)s + 0x640) =
            *(IntrOrient *)((char *)GOBJ_ACT(boyGObj) + 0x640);
        break;
    case 382:
    case 383:
    case 384:
        *out = *(IntrOrient *)((char *)s + 0x640);
        break;
    case 385:
    case 386:
        *out = *(IntrOrient *)((char *)s + 0x660);
        *(IntrOrient *)((char *)s + 0x620) = *out;
        break;
    case 205:
    case 206:
    case 207:
        if (self == (char *)boyGObj) {
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
        out->a = ((IntrOrient *)((char *)GOBJ_ACT(boyGObj) + 0x620))->b;
        *(IntrOrient *)((char *)s + 0x620) = *out;
        break;
    case 89:
    case 399:
    case 403:
        out->a = ((IntrOrient *)((char *)GOBJ_ACT(boyGObj) + 0x620))->b;
        *(IntrOrient *)((char *)s + 0x620) = *out;
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
        out->a = *(IntrVec3 *)((char *)GOBJ_ACT(self)->enemy + 0x350);
        break;
    default:
        ret = intrMotion[k];
        break;
    }
    return ret;
}

void ACTRunIntrCorrect(GObj *a0, IntrMail *a1, IntrMail *a2)
{
    char *rec;
    Act *s = GOBJ_ACT(a0);
    inline void setIntrFlags(void) /* derived name */
    {
        IntrMail *p;

        for (p = a1; p != 0 && (short)p->kind != 429; p++) {
            p->flags |= 0x40000;
        }
    }
    inline void correctIntrList(void) /* derived name */
    {
        IntrMail *ip;
        IntrMail *q;

        for (q = a2; q != 0 && (short)q->kind != 429; q++) {
            if (q->mode == -1) {
                for (ip = a1; ip != 0 && (short)ip->kind != 429; ip++) {
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
    rec = (char *)&motionKind[GOBJ_SUB(a0)->ctrl.motion];
    if (rec[399] & 1) {
        actIntrList[10].flags |= 0x40000;
    } else {
        actIntrList[10].flags &= ~0x40000;
    }
    if (s->actMode == 26) {
        if (s->modeFrame < ((60 - systemStatus[0] * 10) / systemStatus[1]) / 3) {
            actIntrList[371].flags |= 0x40000;
        } else {
            actIntrList[371].flags &= ~0x40000;
        }
    }
}

void WithMailFunc_WayBeginPosError(void *a0)
{
    /* disabled in retail: the way-begin-position (WBP) report */
    if (0) {
        debug_StdPrintfDummy("WBP set [with mail]\n");
    }
    ACTWay_SetBeginPositionIllegal(a0);
}

/* a0 is void * here, int in weapon.h */
extern void ExecWeaponHitReaction(void *a0);

void WithMailFunc_AttackFail(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    char *p = (char *)s->intrData;
    int v = p != 0 ? *(int *)p : s->wallWord;
    if (a0 == boyGObj) {
        char *t = (char *)s->weapon;
        if (t != 0) {
            GOBJ_SUB(t)->ctrl.wallAttr = v;
            ExecWeaponHitReaction(t);
        }
    }
}

/* as in weapon.h, which this TU does not include (ExecWeaponHitReaction differs) */
extern int ReleaseWeaponWithFumbleSequential(char *g);

void WithMailFunc_AttackRejectInQueen(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    void *w = (void *)s->weapon;
    if (w != 0) {
        ReleaseWeaponWithFumbleSequential(w);
        s->weapon = 0;
    }
    if (stage_no == 0x55 || debug_use_new_queen_battle != 0) {
        void *e = isysGObjSearchFromObjKindID_begin(54);
        if (e != 0) {
            iosOmSendMail(e, 0xD, a0);
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

/* The ClipWall work buffer as this function reads it.  RsWork below is the
   other view of the same 0xC0-byte record and disagrees at 0x80 (two floats
   there, the hit object at 0x88) where this one reads the hit object at 0x80
   and the hit flag at 0x88; what ClipWall writes has not been established,
   so the two views are kept apart. */
typedef struct { /* field names derived */
    char pad0[112];
    float f70;
    char pad74[12];
    int f80;
    char pad84[4];
    int f88;
    char pad8C[52];
} RopeWallWork; /* derived name */

int CollisCheckInRope(void *a0, GObj *chain)
{
    /* whether p is a box (kind 0x11), as a char */
    inline char ropeWallIsBox(char *p) /* derived name */
    {
        if (p != 0 && *(int *)(p + 0xC) == 0x11) {
            return 1;
        }
        return 0;
    }

    RopeWallWork work;
    float mid[4];
    float p[4];
    float dir[4];
    float tmp[4];
    float n51[4];
    float n47[4];
    int rv = 0;

    sceVu0ScaleVector(dir, test_CURRENTORIENT(a0), 15.0f);
    GetSkeltonPosition(n51, a0, 51);
    GetSkeltonPosition(n47, a0, 47);
    sceVu0AddVector(mid, n51, n47);
    sceVu0ScaleVector(mid, mid, 0.5f);
    p[0] = mid[0];
    p[2] = mid[2];
    p[1] = mid[1] + 10.0f;
    sceVu0ScaleVector(tmp, dir, -1.0f);
    sceVu0AddVector(&work, p, tmp);
    sceVu0ScaleVector(tmp, dir, 1.0f);
    sceVu0AddVector((char *)&work + 0x10, p, tmp);
    work.f70 = 10.0f;
    ClipWall(&work);
    if (work.f88 != 0) {
        if (ropeWallIsBox((char *)work.f80))
            rv = 2;
        else
            rv = 1;
    } else {
        SwapGV(&work, (char *)&work + 0x10);
        ClipWall(&work);
        if (work.f88 != 0) {
            if (ropeWallIsBox((char *)work.f80))
                rv = 2;
            else
                rv = 1;
        }
    }
    return rv;
}

typedef struct { /* field names derived */
    char pad0[860];
    int f35C;
} RopeSubObj; /* derived name */

typedef struct { /* field names derived */
    char pad0[148];
    int f94;
    char pad98[40];
} RopeFloorWork; /* derived name */

static inline int chainFloorHit(GObj *a0, void *w) /* derived name */
{
    if (((motionKind + GOBJ_SUB(a0)->ctrl.motion)->flags.word >> 4) & 1) {
        GetSkeltonPosition((float *)w, a0, 0x2C);
        GetSkeltonPosition((float *)((char *)w + 0x10), a0, 0x33);
        *(float *)((char *)w + 0x14) -= 5.0f;
        ClipFloor(w);
        if (((RopeFloorWork *)w)->f94 != 0) {
            return 1;
        }
    }
    return 0;
}

inline void afterCommonRope(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    debug_StdPrintfDummy("common rope after func\n");
    ReleaseChain(s->chain, a0);
    {
        GObj *g = a0;
        *(int *)((int)s + 0x194) = s->chain;
        GOBJ_SUB(g)->root.ropeState = 0;
    }
}

inline void actAfterForceRope(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    if (s->chain == 0) {
        debug_assert("src/commonact.c", 1531);
        __assert("src/commonact.c", 1531, "ROPE_GOBJ!=NULL");
    }
    UnLockChainGeo(s->chain);
}

void actCommonRope(GObj *volatile a0)
{
    Act *s;
    float dir[4];
    float ori[4];
    float hand[4];
    RopeFloorWork work;
    int step;
    int nsteps;
    int total;
    int roty;

    nsteps = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) / 3;
    total = nsteps;
    step = -1;
    s = GOBJ_ACT(a0);
    GetCorrectOrientOfChain(dir, (void *)a0);
    ori[0] = *(float *)((char *)test_CURRENTORIENT(a0) + 0);
    ori[1] = *(float *)((char *)test_CURRENTORIENT(a0) + 4);
    ori[2] = *(float *)((char *)test_CURRENTORIENT(a0) + 8);
    roty = _RotyGV(dir, ori);
    if ((int)s->after == 0) {
        GetRootPositionHandExtra(a0, hand);
        step = 0;
        HoldChain(s->chain, a0, hand);
    }
    *(int *)((char *)s + 0x14) = (int)afterCommonRope;
    *(int *)((char *)s + 0x18) = (int)actAfterForceRope;
    LockChainGeo(s->chain);
    _ACTWait(1);
    debug_StdPrintfDummy("enter actCommonRope\n");
    while (1) {
        UnLockChainGeo(s->chain);
        ChainGeo(s->chain);
        LockChainGeo(s->chain);
        switch (CollisCheckInRope((void *)a0, s->chain)) {
        case 1:
            ACTSendMailCorrect(a0, 0xA8);
            break;
        case 2:
            ACTSendMailCorrect(a0, 0xA7);
            break;
        }
        if (chainFloorHit(a0, &work)) {
            ACTSendMailCorrect(a0, 0xA9);
        }
        if (step >= 0) {
            if (step == nsteps) {
                SetMotionDirection(a0, dir);
            } else if (step < nsteps) {
                ((float *)&work)[0] = ori[0];
                ((float *)&work)[1] = ori[1];
                ((float *)&work)[2] = ori[2];
                _ApplyRyGV(&work, (float)(roty * step / total) * 3.1415927f / 180.0f);
                SetMotionDirection(a0, &work);
            }
            step++;
        }
        if (CheckChainClimbablePos(s->chain)) {
            GetChainClimbOrient((char *)GOBJ_ACT(a0)->enemy + 0x330, s->chain);
            GetRootPosition((float *)((char *)GOBJ_ACT(a0)->enemy + 0x340), (void *)s->chain);
            GetChainClimbCollision((char *)GOBJ_ACT(a0)->enemy + 0x350, s->chain);
            ((RopeSubObj *)(char *)GOBJ_ACT(a0)->enemy)->f35C = s->chain;
            ActSendMail_WithAdditionalData((char *)a0, 0x98, (void *)a0,
                                           *(char **)(*(char **)((char *)a0 + 0x164) + 0x680) +
                                               0x330);
        }
        _ACTWait(1);
    }
}

/* a file-static copy of SetCorrectOrientOfChain, defined later in this file,
   which this caller inlines */
static inline void setCorrectOrientOfChain_inl(void *a0) /* derived name */
{
    float local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}

void motCommonRopeTurnR(GObj *volatile a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(a0)) / 3.1415927f * 180.0f);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        i++;
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base + deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(a0, dir);
        deg += 5;
        if (i % wait == 0) {
            setCorrectOrientOfChain_inl((void *)a0);
            ACTSendMailCorrect(a0, 0x150);
        }
        _ACTWait(1);
    }
}

void motCommonRopeTurnL(GObj *volatile a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(a0)) / 3.1415927f * 180.0f);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        i++;
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base - deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(a0, dir);
        deg += 5;
        if (i % wait == 0) {
            setCorrectOrientOfChain_inl((void *)a0);
            ACTSendMailCorrect(a0, 0x150);
        }
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    float x, y, z;
} ClimbVec3; /* derived name */

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} ClimbVec4; /* derived name */

typedef struct { /* field names derived */
    sceVu0FVECTOR v0;
    float v1[4];
    ClimbVec3 v2;
    int obj;
} ClimbEndRec; /* derived name */

void actCommonRopeClimbEnd1(GObj *volatile a0)
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

    c = *(ClimbEndRec *)(char *)GOBJ_ACT(a0)->intrData;
    isCage = *(int *)(c.obj + 0xC) == 0x2C;
    flag = 0;
    GOBJ_SUB(boyGObj)->root.ropeState = 0;
    dir.f[0] = c.v0[0];
    dir.f[1] = c.v0[1];
    dir.f[2] = c.v0[2];
    sceVu0ScaleVector(&dir, &dir, -1.0f);
    if (_AbsRotyGV(&dir, test_CURRENTORIENT(a0)) < 10) {
        flag = 1;
    } else {
        back = -5;
        while (1) {
            if (isCage) {
                TestCageUpDown(c.obj, (void *)a0);
            }
            if (GOBJ_SUB(a0)->ctrl.motion == 118) {
                break;
            }
            _ACTWait(1);
        }
        i = 0;
        r = _RotyGV(&dir, test_CURRENTORIENT(a0));
        step = (r > -1) ? step : back;
        n = r / step;
        n = (n < 0) ? -n : n;
        GetSkeltonPosition(pos, a0, 22);
        pos[0] = c.v1[0];
        pos[2] = c.v1[2];
        while (i < n) {
            i++;
            ori[0] = *(float *)((char *)test_CURRENTORIENT(a0) + 0);
            ori[1] = *(float *)((char *)test_CURRENTORIENT(a0) + 4);
            ori[2] = *(float *)((char *)test_CURRENTORIENT(a0) + 8);
            _ApplyRyGV(ori, (float)step * 3.1415927f / 180.0f);
            SetMotionDirection(a0, ori);
            if (0 < step) {
                ACTSendMailCorrect(a0, 0xA0);
            } else {
                ACTSendMailCorrect(a0, 0xA1);
            }
            SetChainRootUpdateMode(a0, 3, pos);
            _ACTWait(1);
        }
        if (GOBJ_SUB(a0)->ctrl.motion != 118) {
            do {
                ACTSendMailCorrect(a0, 0x150);
                _ACTWait(1);
            } while (GOBJ_SUB(a0)->ctrl.motion != 118);
        }
    }
    SetMotionDirection(a0, dir.f);
    while (1) {
        ACTSendMailCorrect(a0, 0x99);
        if (flag) {
            ACTSendMailCorrect(a0, 0x9A);
        }
        GetSkeltonPosition(hand, a0, 22);
        GetSkeltonPosition(foot, a0, 6);
        base[0] = c.v1[0];
        base[1] = c.v1[1];
        base[2] = c.v1[2];
        if (isCage) {
            TestCageUpDown(c.obj, (void *)a0);
        }
        *(ClimbVec3 *)((char *)GOBJ_ACT(a0)->enemy + 0x350) = c.v2;
        if (hand[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(a0, 0x9B);
        }
        if (foot[1] - base[1] < 10.0f) {
            ACTSendMailCorrect(a0, 0x9C);
        }
        _ACTWait(1);
    }
}

typedef union { /* field names derived */
    char *p;
    float *f;
} CagePtr; /* derived name */

void actCommonRopeCliff(GObj *volatile a0)
{
    float dst[4];
    float root[4];
    float cur[4];
    float p[4];
    Act *s = GOBJ_ACT(a0);
    int n = ((60 - systemStatus[0] * 10) / systemStatus[1]) / 2;
    float y;
    int i = 0;

    s->flags18.afterProc = afterCommonRopeCliff;
    ((CagePtr *)(((CagePtr *)((char *)boyGObj + 0x15C))->p + 0x420))->p = 0;
    dst[0] = GOBJ_ACT(a0)->enemy->ropeCliffX;
    dst[1] = GOBJ_ACT(a0)->enemy->ropeCliffY;
    dst[2] = GOBJ_ACT(a0)->enemy->ropeCliffZ;
    GetRootPosition(root, (void *)a0);
    while (1) {
        i++;
        if (i <= n) {
            _InterGV(cur, root, dst, (float)i, (float)(n - i));
            SetDirectRootPositionNoFitting((void *)a0, cur);
        }
        if (GOBJ_SUB(a0)->ctrl.motion == 118) {
            y = test_CURRENTROOT((void *)a0)[1];
            SetChainRootUpdateMode(boyGObj, 3, (float *)((char *)GOBJ_ACT(a0)->enemy + 0x1D0));
            p[0] = test_CURRENTROOT((void *)a0)[0];
            p[1] = test_CURRENTROOT((void *)a0)[1];
            p[2] = test_CURRENTROOT((void *)a0)[2];
            p[1] = y + 5.0f;
            SetDirectRootPositionNoFitting((void *)a0, p);
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

void TestCageUpDown(int cage, GObj *gobj)
{
    inline void initCage(char *o) /* derived name */
    {
        int n;

        cageUpDown.cnt = 0;
        cageUpDown.lim = (float)*motionTable[*(int *)(((CagePtr *)(o + 0x15C))->p + 0x4A0)];
        n = GetSkeltonFocusNode(o, 35);
        cageUpDown.a[0] =
            *(float *)(*(char **)(((CagePtr *)(o + 0x15C))->p + 0xC) + n * 0x40 + 0x30);
        cageUpDown.a[1] =
            *(float *)(*(char **)(((CagePtr *)(o + 0x15C))->p + 0xC) + n * 0x40 + 0x34);
        cageUpDown.a[2] =
            *(float *)(*(char **)(((CagePtr *)(o + 0x15C))->p + 0xC) + n * 0x40 + 0x38);
        cageUpDown.b[0] = cageUpDown.a[0];
        cageUpDown.b[2] = cageUpDown.a[2];
        cageUpDown.b[1] = cageUpDown.a[1] + 200.0f;
    }

    inline void cageMove(char *o, float *dst, float *lo, float *hi, float *res, float x, float y,
                         float z) /* derived name */
    {
        dst[0] = x;
        dst[1] = y;
        dst[2] = z;
        GetCageChainPoint(lo, hi, (void *)cage);
        _InterGV(dst, lo, hi, dst[1] - lo[1], hi[1] - dst[1]);
        sceVu0ScaleVector(res, test_CURRENTORIENT(o), -20.0f);
        sceVu0AddVector(res, dst, res);
        ACTSetPositionNodeWithFitting((int)o, 0x23, (int)res, 1.0f);
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

    GetCageChainPoint(vB, vC, (void *)cage);
    *(int *)(((CagePtr *)((char *)boyGObj + 0x15C))->p + 0x420) = 0;
    switch (mot) {
    case 0x78:
        putRoot(vE, vB, vC, 1);
        chainUpdate(vG, vH, vB, vC);
        break;
    case 0x77:
        if (GOBJ_ACT(gobj)->actMode == 0x3F) {
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

typedef struct { /* field names derived */
    float x, y;
} RsVec2; /* derived name */

typedef struct { /* field names derived */
    RsVec2 xy;
    void *obj;
} RsHit; /* derived name */

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} RsVec4; /* derived name */

typedef struct { /* field names derived */
    char pad0[816];
    char f330[16];
    float f340;
    float f344;
    float f348;
    char f34C[4];
    RsHit f350;
    int f35C;
} RsSub; /* derived name */

typedef struct { /* field names derived */
    char pad0[128];
    RsVec2 h80;
    int f88;
    char pad8C[52];
} RsWork; /* derived name */

static inline unsigned char ropeSpecialWallHit(RsVec4 *p1, RsHit *hit) /* derived name */
{
    sceVu0FVECTOR va = {0.0f, 0.0f, -20.0f, 1.0f};
    sceVu0FVECTOR vb = {0.0f, 0.0f, 20.0f, 1.0f};
    RsWork work;
    int i;

    for (i = 0; i < 4; i++) {
        sceVu0UnitMatrix((void *)MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(p1->f[0], p1->f[1] + 0.0f, p1->f[2]);
        MatrixDrive_RotMatrixY((short)((float)i * 0.7853982f * 32768.0f / 3.1415927f));
        sceVu0ApplyMatrix(&work, (void *)MatrixDrive_GetMatrix(), va);
        sceVu0ApplyMatrix((char *)&work + 0x10, (void *)MatrixDrive_GetMatrix(), vb);
        ClipWall(&work);
        if (work.f88 != 0) {
            hit->xy = work.h80;
            hit->obj = (void *)work.f88;
            return 1;
        }
    }
    return 0;
}

void actCommonRopeSpecial(GObj *volatile a0)
{
    Act *s;
    RsHit hit;
    RsVec4 p1;
    RsVec4 p2;
    RsVec4 pos;
    int cage;
    unsigned char found;

    s = GOBJ_ACT(a0);
    cage = s->cageObj;
    if (cage != 0) {
        *(int *)((char *)GOBJ_ACT(a0)->work + 0x400) = cage;
    } else {
        cage = (int)GOBJ_WORK(a0)->ropeCage;
    }
    if (*(int *)((char *)GOBJ_ACT(a0)->work + 0x900) == 4 ||
        *(int *)((char *)GOBJ_ACT(a0)->work + 0x900) == 5) {
        GetSkeltonPosition((float *)((char *)GOBJ_ACT(a0)->work + 0x410), a0, 35);
    } else {
        GetSkeltonPosition((float *)((char *)GOBJ_ACT(a0)->work + 0x410), a0, 22);
    }
    GetCageChainPoint(p1.f, p2.f, (void *)cage);
    found = ropeSpecialWallHit(&p1, &hit);
    GOBJ_SUB(a0)->root.ropeState = 0;
    while (1) {
        if (GOBJ_SUB(a0)->ctrl.motion == 118) {
            *(long long *)((char *)s + 0x20) &= ~(1ULL << 11);
        }
        GetSkeltonPosition(pos.f, a0, 35);
        GetCageChainPoint(p1.f, p2.f, (void *)cage);
        if (debug_font_flag & 1) {
            debug_Printf(10, 120, 0xFFFFFFF, "%d, %d\n",
                         (int)*(float *)((char *)test_CURRENTROOT((void *)a0) + 4), (int)p2.f[1]);
        }
        if (*(float *)((char *)test_CURRENTROOT((void *)a0) + 4) > p2.f[1] - 30.0f) {
            ACTSendMailCorrect(a0, 0xC7);
        }
        if (found && pos.f[1] < p1.f[1] + 60.0f) {
            ((RsSub *)(char *)GOBJ_ACT(a0)->enemy)->f35C = cage;
            GetOrientOfWall(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x330, hit.obj,
                            &hit);
            ((RsSub *)(char *)GOBJ_ACT(a0)->enemy)->f340 = p1.f[0];
            ((RsSub *)(char *)GOBJ_ACT(a0)->enemy)->f344 = p1.f[1];
            ((RsSub *)(char *)GOBJ_ACT(a0)->enemy)->f348 = p1.f[2];
            ((RsSub *)(char *)GOBJ_ACT(a0)->enemy)->f344 -= 100.0f;
            ((RsSub *)(char *)GOBJ_ACT(a0)->enemy)->f350 = hit;
            ActSendMail_WithAdditionalData((char *)a0, 0xB0, (void *)a0,
                                           (char *)GOBJ_ACT(a0)->enemy + 0x330);
        }
        TestCageUpDown(cage, (void *)a0);
        _ACTWait(1);
    }
}

void lever_nego1(void *a0, void *a1)
{
    int m = *(int *)((char *)a1 + 0xC);
    if (m < 0x16) {
        return;
    }
    if (m < 0x18) {
        goto lever;
    }
    if (m >= 0x1A) {
        return;
    }
    SetWallLeverWithNodePoint(a1, a0, 0x16);
    return;
lever:
    SetFloorLeverWithNodePoint(a1, a0, 0x16);
}

void SetDirectRootPositionXZ(void *a0, void *a1)
{
    void *ret = test_CURRENTROOT(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    SetDirectRootPositionNoFitting(a0, a1);
}

/* a file-static copy of ACTMotDirToWall, defined below, which actCommonLever
   inlines */
static inline void actMotDirToWall(char *a0) /* derived name */
{
    float local[4];
    sceVu0ScaleVector(local, *(char **)(a0 + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(a0, local);
}

static inline void correctLeverHoldPoint(void *a0, char *lev) /* derived name */
{
    float w[4];
    if (*(int *)(lev + 0xC) >= 0x16) {
        if (*(int *)(lev + 0xC) < 0x18) {
            GetFloorLeverGlobalHoldPoint(w, lev);
        } else if (*(int *)(lev + 0xC) < 0x1A) {
            GetWallLeverGlobalHoldPoint(w, lev);
            debug_StdPrintfDummy("%f, %f, %f\n", w[0], w[1], w[2]);
        }
    }
    SetDirectRootPositionNoFittingWithNodePointXZ(a0, 0x16, w, 0.2f);
}

void actCommonLever(GObj *volatile a0)
{
    float p[4];
    Act *s = GOBJ_ACT(a0);
    char *lev = *(char **)((char *)s + 0x5FC);

    GOBJ_WORK(a0)->leverTimer = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 5;
    p[0] = s->pullPos[0];
    p[1] = s->pullPos[1];
    p[2] = s->pullPos[2];
    p[1] = test_CURRENTROOT((void *)a0)[1];
    SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 0x2C, s->pullPos, 1.0f);
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(a0)->ctrl.frameFlag2 != 0) {
                correctLeverHoldPoint((void *)a0, lev);
            }
            if (GOBJ_SUB(a0)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}

void EBRAIN_SEND_MES(void *a0, int a1)
{
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        eBrainSendMes(a0, a1);
}

inline void actCommonPlay(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter actCommonPlay\n");
    _ACTWait(0);
}

void DamageFunc(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    debug_StdPrintfDummy("damage\n");
    if (a0 != (char *)girlGObj) {
        s->life -= (float)GOBJ_ACT(a0)->damage;
    }
    if (*(int *)(a0 + 0xC) == 4) {
        EnemyBattleWork *b;
        EBRAIN_SEND_MES(a0, 5);
        b = GOBJ_ACT(a0)->enemy;
        EnemyDeleteParticle(a0, (char *)b + 0xE0, (char *)b + 0xF0);
    }
}

void DownFunc(char *a0)
{
    DamageFunc(a0);
    if (*(int *)(a0 + 0xC) == 1) {
        EBRAIN_SEND_MES((void *)GOBJ_ACT(a0)->attacker, 6);
    }
}

inline void actCommonDamage(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter actCommonDamage\n");
    SetMotionDirection(a0, (char *)GOBJ_ACT(a0) + 0x1C0);
    DamageFunc((char *)a0);
    if (GOBJ_ACT(a0)->enemy->liftKind == 3) {
        _ACTWait(360);
    }
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

void actCommonDown(GObj *volatile a0)
{
    float v[4];
    Act *s = GOBJ_ACT(a0);
    int notDamage = s->intrKind != 0x37 && s->intrKind != 0x38;

    debug_StdPrintfDummy("enter actCommonDown\n");
    *(int *)((char *)s + 0x18) = (int)actAfterDown;
    if (notDamage) {
        if ((char *)a0 == (char *)boyGObj) {
            brainAddLevelGirl(1000.0f);
        }
        if ((char *)a0 == (char *)girlGObj) {
            sceVu0ScaleVector(v, (char *)GOBJ_ACT(a0) + 0x1C0, -1.0f);
            SetMotionDirection(a0, v);
        } else {
            SetMotionDirection(a0, (char *)GOBJ_ACT(a0) + 0x1C0);
        }
        DownFunc((char *)a0);
    }
    GOBJ_ACT(a0)->enemy->liftLevel = 0x10;
    while (1) {
        if (a0->kind != 4) {
            GOBJ_ACT(a0)->hit = 1;
        }
        ACTSendMailCorrect(a0, 0xC7);
        if (GOBJ_ACT(a0)->enemy->liftLevel <= 0) {
            ACTSendMailCorrect(a0, 0x124);
        }
        _ACTWait(1);
    }
}

extern void enemySetParticleDie(void *root, void *dir);
extern void EnemySetfDisappearAll(GObj *volatile a0);

void actCommonDie(GObj *volatile a0)
{
    /* a helper defined at the head of this body */
    inline void dieNotifyObjects(void) /* derived name */
    {
        void *g;

        if (a0->labelId == 0xEAD) {
            gamesysObjInfoCls(4, 0xEAD);
            gamesysObjInfoCls(0x21, 0xEAE);
        }
        g = isysGObjSearchFromObjKindID_begin(0x2F);
        if (g == 0) {
            g = isysGObjSearchFromObjKindID_begin(0x41);
        }
        if (a0->kind == 4 && g != 0) {
            iosOmSendMail(g, 0x12, a0);
        }
    }
    Act *s = GOBJ_ACT(a0);
    int cnt = 0;
    float t;
    int corpse;

    if (s->intrKind == 0x2C) {
        corpse = 1;
    } else {
        corpse = 0;
    }
    debug_StdPrintfDummy("enter actCommonDie\n");
    SetMotionDirection(a0, (char *)GOBJ_ACT(a0) + 0x1C0);
    DownFunc((char *)a0);
    GOBJ_ACT(a0)->hit = 1;
    dieNotifyObjects();
    if (a0->labelId == 0xEAD) {
        ResetReviveCountEnemy(a0);
    }
    while (1) {
        if (corpse) {
            ACTSetPositionWithFitting((void *)a0, test_CURRENTROOT((void *)a0));
        }
        if (a0->kind == 4) {
            _ACTWait(1);
            enemySetParticleDie(test_CURRENTROOT((void *)a0), (char *)GOBJ_ACT(a0) + 0x1C0);
            EnemySetfDisappearAll(a0);
            actEnemyFlagOnDead(a0);
            ACTGame_DeleteActorInformation(a0);
            for (t = 0.0f; t < (float)(((60 - systemStatus[0] * 10) / systemStatus[1]) * 6);
                 t += GOBJ_WORK(a0)->disappearSpeed) {
                float d = (t + t - (float)(((60 - systemStatus[0] * 10) / systemStatus[1]) * 6)) /
                          (float)(((60 - systemStatus[0] * 10) / systemStatus[1]) * 6);
                if (d < 0.01f) {
                    d = 0.01f;
                }
                SetEnemyDissolve(a0, d);
                if ((int)((long long)s->flags20.ll >> 22) & 1) {
                    t += 10.0f;
                }
                _ACTWait(1);
            }
            actEnemyHyde(a0);
            _ACTWait(0);
        }
        if (a0 == (int)((char *)boyGObj) || a0 == (int)((char *)girlGObj)) {
            if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 2 < cnt) {
                ACT_LAYOUT_GAMEOVER();
                _ACTWait(0);
            }
        }
        cnt++;
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[540];
    int f21C;
    int f220;
} ClingSub; /* derived name */

void actCommonCling(GObj *volatile a0)
{
    int no;
    int mot;

    int Cling(int idx, int m)
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
        SetMotionNodeFixModeParameter((void *)a0, (void *)m, r->mode, r->node, q, r->pos[0],
                                      r->pos[1], r->pos[2], 1.0f);
        return r->motion;
    }

    no = (int)(_GetRandom() * 10.0f) % 15;
    mot = ((ClingSub *)GOBJ_ACT(a0)->enemy)->f21C;

    ((ClingSub *)GOBJ_ACT(a0)->enemy)->f220 = mot;
    ACTGameCollisionOff(a0);
    Cling(no, mot);
    _ACTWait(0);
}

void actCommonSlip(GObj *volatile a0)
{
    float dir[4];
    float v2[4];
    float v3[4];

    if (*(unsigned char *)((char *)GOBJ_ACT(a0)->enemy + 0x280) == 0) {
        dir[0] = GOBJ_ACT(a0)->enemy->slipDirX;
        dir[1] = GOBJ_ACT(a0)->enemy->slipDirY;
        dir[2] = GOBJ_ACT(a0)->enemy->slipDirZ;
    } else {
        sceVu0ScaleVector(dir, (float *)((char *)GOBJ_ACT(a0)->enemy + 0x270), -1.0f);
    }
    v2[0] = GOBJ_ACT(a0)->enemy->slipDirX;
    v2[1] = GOBJ_ACT(a0)->enemy->slipDirY;
    v2[2] = GOBJ_ACT(a0)->enemy->slipDirZ;
    sceVu0ScaleVector(v3, (float *)((char *)GOBJ_ACT(a0)->enemy + 0x270), 30.0f);
    v3[1] = -20.0f;
    while (1) {
        SetMotionDirectionSmooze(a0, dir, 3.0f);
        _ACTWait(1);
    }
}

void actCommonStoneDead(GObj *volatile a0)
{
    float center[4];
    float dir[4];
    Act *s = GOBJ_ACT(a0);

    if (s->intrKind == 0x22) {
        SetBoyStonizedVisual(a0);
        GetGameOverEffectCenterPosition(center);
        _OrientXZGV(dir, center, test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, dir);
    } else {
        ACTSetPositionWithFitting((void *)a0, test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, (char *)GOBJ_ACT(a0) + 0x1C0);
        a0->drawMask = 0;
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

inline void actCommonRevive(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonRevive\n");
    ACTGameCollisionOff(a0);
    ((ReviveSub *)s)->f14 = (int)afterCommonRevive;
    SetDirectRootPositionNoFitting((void *)a0, (char *)s + 0x170);
    EnemySetfAppearAll((void *)a0);
    for (;;) {
        ResetEnemyPositionInfo((void *)a0);
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[20];
    int f14;
    char pad18[52];
    int f4C;
} StoneSub; /* derived name */

void actCommonStone(GObj *volatile a0)
{
    StoneSub *s = (StoneSub *)(char *)GOBJ_ACT(a0);

    s->f14 = (int)afterCommonStone;
    *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x2A0) = 0;
    while (1) {
        if (debug_font_flag & 1) {
            debug_Printf(10, 170, 0xFFFFFFF, "count =(%d)\n", GOBJ_ACT(a0)->enemy->liftLevel);
        }
        if (debug_font_flag & 1) {
            debug_Printf(10, 180, 0xFFFFFFF, "level =(%d)\n", GOBJ_ACT(a0)->enemy->stoneLevel);
        }
        switch (GOBJ_ACT(a0)->enemy->stoneLevel) {
        case 0:
        case 1:
            break;
        case 2:
            _ACTParaStatus_Set(a0, 0x26);
            break;
        default:
            _ACTParaStatus_Set(a0, 0x27);
            break;
        }
        if (GOBJ_ACT(a0)->enemy->liftLevel < 0) {
            ACTSendMailCorrect(a0, 0xC7);
            GOBJ_ACT(a0)->enemy->stoneLevel = 0;
        }
        if (s->f4C >= 0x3D && GOBJ_ACT(a0)->enemy->stoneLevel >= 3) {
            ACT_LAYOUT_GAMEOVER();
            _ACTWait(0);
        }
        ACTSendMailCorrect(a0, 0x70);
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[592];
    int f250, f254, f258, f25C;
} SofaObj; /* derived name */

void actCommonSofa(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    SetDirectRootPositionNoFitting((void *)a0, s->sofaPos);
    ((SofaObj *)GOBJ_ACT(a0)->enemy)->f250 = 0;
    ((SofaObj *)GOBJ_ACT(a0)->enemy)->f258 = 0;
    ((SofaObj *)GOBJ_ACT(a0)->enemy)->f25C = 0;
    *(void **)((char *)s + 0x160) = *(void **)((char *)s + 0x61C);
    while (1) {
        GOBJ_WORK(a0)->sofaTimer = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 3;
        GOBJ_WORK(a0)->sofaRestTimer = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 10;
        if (((SofaObj *)GOBJ_ACT(a0)->enemy)->f250 > ((SofaObj *)GOBJ_ACT(a0)->enemy)->f254) {
            ACTSendMailCorrect(a0, 0x73);
        }
        ((SofaObj *)GOBJ_ACT(a0)->enemy)->f250 += 1;
        _ACTWait(1);
    }
}

void BoxBarSoundOn(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    switch (s->actMode) {
    case 0x31:
        ExecBoxMoveStartReaction(s->box, (int)s->pushDir);
        break;
    case 0x33:
        ExecRotObjectMoveStartReaction(s->barObj);
        break;
    }
}

void BoxBarSoundOff(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    switch (s->actMode) {
    case 0x31:
        ExecBoxMoveEndReaction(s->box);
        break;
    case 0x33:
        ExecRotObjectMoveEndReaction(s->barObj);
        break;
    }
}

void _boxbar_set_sound(GObj *a0, int mode)
{
    switch (GOBJ_ACT(a0)->enemy->boxBarSound) {
    case 0:
        if (mode == 1) {
            BoxBarSoundOn((char *)a0);
            GOBJ_ACT(a0)->enemy->boxBarSound = 1;
        }
        break;
    case 1:
        if (mode == 0 || mode == 2) {
            BoxBarSoundOff((char *)a0);
            GOBJ_ACT(a0)->enemy->boxBarSound = mode;
        } else {
            BoxBarSoundOn((char *)a0);
        }
        break;
    case 2:
        if (mode == 0) {
            GOBJ_ACT(a0)->enemy->boxBarSound = 0;
        }
        if (mode == 3) {
            BoxBarSoundOn((char *)a0);
            GOBJ_ACT(a0)->enemy->boxBarSound = 1;
        }
        break;
    }
}

typedef void (*BoxAfterFn)(volatile int);
extern void GetBoxHoldPoint(void *hold, char *box, void *self);
extern void AlignBox(char *box, float f);
extern int MoveBoxWithHoldPoint(char *box, void *hold, void *self, int node, void *dir);

/* The third view of the same 0xC0-byte ClipWall work buffer (RopeWallWork
   above and RsWork below are the other two).  This one reads the two vectors
   at 0x00 and 0x10, the height at 0x70 and the hit flag at 0x88; the views
   are kept apart for the reason given at RopeWallWork. */
typedef struct { /* field names derived */
    float p[4];
    float q[4];
    char pad20[80];
    float f70;
    char pad74[20];
    int f88;
    char pad8C[52];
} BoxWallWork; /* derived name */

/* the height is an int */
static inline int boxWallCheck(GObj *a0, char *box, float dist, int h) /* derived name */
{
    BoxWallWork w;
    float t[4];
    Act *s = GOBJ_ACT(a0);

    GetRootPosition(w.p, box);
    GetRootPosition(w.q, box);
    sceVu0ScaleVector(t, (char *)s + 0x4B0, dist);
    sceVu0AddVector(w.q, w.q, t);
    w.f70 = h;
    w.p[1] += 10.0f;
    w.q[1] += 10.0f;
    ClipWall(&w);
    if (w.f88 == 0) {
        return 0;
    }
    return 1;
}

void actCommonBox(GObj *volatile a0)
{
    char *box;
    /* a helper defined at the head of this body */
    inline void addGirlLevelForBox(char *b) /* derived name */
    {
        if ((char *)girlGObj != 0 && *(char **)((char *)GOBJ_SUB(girlGObj)) == b) {
            brainAddLevelGirl(1000.0f);
        }
    }
    Act *s = GOBJ_ACT(a0);
    char *sub;
    float hold[4];

    *(BoxAfterFn *)((char *)s + 0x14) = afterCommonBox;
    box = s->holdBoxObj;
    if (stage_no == 0x10) {
        sub = *(char **)((char *)GOBJ_SUB(box));
        if (sub != 0) {
            if (*(int *)(sub + 0xC) == 0x11) {
                box = sub;
            }
        }
    }
    ((Act *)(char *)s)->box = box;
    actMotDirToWall((char *)a0);
    sceVu0ScaleVector(GOBJ_WORK(a0)->boxDir, s->wallOrient, -1.0f);
    while (1) {
        int had = (int)s->pushDir != 0;
        int f2 = 0;
        int miss = 0;
        int flag = 0;
        unsigned char isTruck = IsThisBoxTruck(box);

        addGirlLevelForBox(box);
        GetBoxHoldPoint(hold, box, (void *)a0);
        if (!isTruck) {
            if (boxWallCheck(a0, box, 100.0f, 48)) {
                ACTSendMailCorrect(a0, 0xC7);
                miss = 1;
            }
            if (s->pushDir == 0xFFFFFFFF) {
                if (boxWallCheck(a0, box, 150.0f, 48)) {
                    miss = 1;
                }
            }
        }
        if (!miss && (isTruck == 0 ? *(int *)((char *)GOBJ_SUB(a0) + 0x608)
                                   : GOBJ_SUB(a0)->ctrl.frameFlag1)) {
            f2 = 1;
            if ((int)s->pushDir == 1 && boxWallCheck(a0, box, -25.0f, 30)) {
                miss = 1;
            } else {
                float dir[4];
                unsigned char ok;
                if (s->pushDir == 0xFFFFFFFF) {
                    dir[0] = s->wallOrient[0];
                    dir[1] = s->wallOrient[1];
                    dir[2] = s->wallOrient[2];
                } else {
                    sceVu0ScaleVector(dir, (char *)s + 0x4B0, -1.0f);
                }
                if (!isTruck) {
                    debug_StdPrintfDummy("A\n");
                    AlignBox(box, 100.0f);
                }
                ok = MoveBoxWithHoldPoint(box, hold, (void *)a0, 22, dir);
                if (ok) {
                    flag = 1;
                } else {
                    miss = 1;
                }
            }
        }
        if (GetMotionFrameFlag2((void *)a0)) {
            float pos[4];
            GetBoxGlobalHoldPoint(pos, box, hold);
            SetDirectRootPositionNoFittingWithNodePointXZ(
                (void *)a0, 22, pos, GOBJ_SUB(a0)->ctrl.frameFlag1 != 0 ? 1.0f : 0.3f);
        }
        if (!had) {
            _boxbar_set_sound(a0, 0);
            if (!isTruck) {
                debug_StdPrintfDummy("B\n");
            }
        } else if (f2) {
            _boxbar_set_sound(a0, 1);
        }
        if (flag) {
            _boxbar_set_sound(a0, 3);
        }
        if (miss) {
            _boxbar_set_sound(a0, 2);
        }
        if (!isTruck && GetBoxMode(box) == 0) {
            s->flags20.ll |= (1ULL << 40);
            s->flags20.ll |= (1ULL << 41);
        }
        _ACTWait(1);
    }
}

inline void afterCommonBar(GObj *volatile a0)
{
    debug_StdPrintfDummy("reset\n");
    GOBJ_SUB(a0)->root.filter = InitialColInfo;
    _boxbar_set_sound(a0, 0);
}

typedef struct { /* field names derived */
    char pad0[448];
    int f1C0;
    int f1C4;
    int f1C8;
} BarHold; /* derived name */

void actCommonBar(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    char *bar;
    float pos[4];
    float ori[4];
    float hold[4];
    float hold2[4];

    bar = (char *)s->barObj;
    actMotDirToWall((char *)a0);
    pos[0] = *(float *)((char *)test_CURRENTROOT((void *)a0) + 0);
    pos[1] = *(float *)((char *)test_CURRENTROOT((void *)a0) + 4);
    pos[2] = *(float *)((char *)test_CURRENTROOT((void *)a0) + 8);
    ori[0] = *(float *)((char *)test_CURRENTORIENT(a0) + 0);
    ori[1] = *(float *)((char *)test_CURRENTORIENT(a0) + 4);
    ori[2] = *(float *)((char *)test_CURRENTORIENT(a0) + 8);
    GetRotObjectHoldPoint(hold, hold2, (char *)GOBJ_ACT(a0)->work + 0x8B0, (void *)a0);
    (int)GOBJ_SUB(s) = (int)bar;
    s->after = (void *)afterCommonBar;
    debug_StdPrintfDummy("set %p\n", bar);
    ((BarHold *)(int)GOBJ_SUB(a0))->f1C0 = (int)bar;
    ((BarHold *)(int)GOBJ_SUB(a0))->f1C4 = -1;
    ((BarHold *)(int)GOBJ_SUB(a0))->f1C8 = 0;
    while (1) {
        int had = (int)s->pushDir != 0;
        int lit = 0;
        int miss = 0;
        int flag = 0;
        if (GetMotionFrameFlag1((void *)a0)) {
            float dir[4];
            float up[4];
            int node = GetSkeltonFocusNode((void *)a0, 32);
            unsigned char ok;
            lit = 1;
            CopyVector(dir, (char *)GOBJ_SUB(a0)->nodeMtx + node * 64 + 0x30);
            if (s->pushDir == 0xFFFFFFFF) {
                sceVu0ScaleVector(up, test_CURRENTORIENT(a0), -1.0f);
            } else {
                up[0] = *(float *)((char *)test_CURRENTORIENT(a0) + 0);
                up[1] = *(float *)((char *)test_CURRENTORIENT(a0) + 4);
                up[2] = *(float *)((char *)test_CURRENTORIENT(a0) + 8);
            }
            ok = MoveRotObjectWithHoldPoint(bar, hold, (void *)a0, dir, up);
            if (ok) {
                flag = 1;
            } else {
                miss = 1;
            }
        }
        if (GetMotionFrameFlag2((void *)a0)) {
            GetRotObjectGlobalHoldGeometry(pos, ori, bar, hold, hold2);
            SetDirectRootPositionNoFittingWithNodePoint((void *)a0, 0x20, pos, lit ? 1.0f : 0.3f);
            SetMotionDirection(a0, ori);
        }
        if (!had) {
            _boxbar_set_sound(a0, 0);
        } else if (lit && !miss) {
            _boxbar_set_sound(a0, 1);
        }
        if (flag) {
            _boxbar_set_sound(a0, 3);
        }
        if (miss) {
            _boxbar_set_sound(a0, 2);
        }
        _ACTWait(1);
    }
}

void funcCommonJumpDircorrect(GObj *a0)
{
    SetMotionDirection(a0, GOBJ_WORK(a0)->padWish);
}

void funcCommonFallDircorrect(GObj *a0)
{
    SetMotionDirection(a0, GOBJ_WORK(a0)->fallDir);
}

void correctJumpOrientByChain(GObj *a0)
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

    pos[0] = test_CURRENTROOT((void *)a0)[0];
    pos[1] = test_CURRENTROOT((void *)a0)[1];
    pos[2] = test_CURRENTROOT((void *)a0)[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(a0));

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
    _OrientXZGV(dir, out, test_CURRENTROOT((void *)a0));
    t = ang * 20.0f / 300.0f;
    if (t < 0.0f) {
        t = 0.0f;
    } else if (20.0f < t) {
        t = 20.0f;
    }
    SetMotionDirectionSmooze(a0, dir, t);
}

typedef union { /* field names derived */
    unsigned long long ll;
    void *p;
} ActFlagJ; /* derived name */

typedef struct { /* field names derived */
    char pad0[398];
    unsigned short f18E;
} MotRecJ; /* derived name */

void actCommonJump(GObj *volatile a0)
{
    float dir[4];
    Act *s = GOBJ_ACT(a0);
    int chk = 0;
    int hit = 0;
    int n;

    ((ActFlagJ *)((char *)s + 0x18))->ll &= ~(1ULL << 55);
    ((ActFlagJ *)((char *)s + 0x18))->p = (void *)actAfterJump;
    if (s->intrKind == 0x52) {
        GOBJ_WORK(a0)->jumpTimer = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 10;
    }
    if (s->intrKind == 0x105) {
        ((ActFlagJ *)((char *)s + 0x18))->ll |= (1ULL << 55);
        if ((char *)a0 == (char *)girlGObj && (char *)boyGObj != 0) {
            _OrientXZGV(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)a0));
            SetMotionDirection(a0, dir);
        }
    }
    ((ActFlagJ *)((char *)s + 0x18))->ll &= ~(1ULL << 56);
    if (s->intrKind == 0xC5) {
        SetMotionDirection(a0, GOBJ_WORK(a0)->boyOrient);
        ((ActFlagJ *)((char *)s + 0x18))->ll |= (1ULL << 56);
    }
    n = *(int *)((char *)GOBJ_ACT(a0)->work + 0x900);
    if (n < 4) {
        if (0 < n) {
            switch ((unsigned int)s->intrKind) {
            case 0xBF:
            case 0xC0:
                chk = 1;
                break;
            case 0xBD:
                if (0.1f < s->stickMag) {
                    chk = 1;
                }
                break;
            }
            if (chk != 0) {
                correctJumpOrientByChain(a0);
            }
        }
    }
    while (1) {
        if (((MotRecJ *)&motionKind[GOBJ_SUB(a0)->ctrl.motion])->f18E & 1) {
            hit = 1;
        }
        if (hit != 0 && motionKind[GOBJ_SUB(a0)->ctrl.motion].playMode == 1) {
            GOBJ_SUB(a0)->root.move[0] = GOBJ_SUB(a0)->root.move[2] = 0.0f;
        }
        ACTSendMailCorrect(a0, 0xBD);
        _ACTWait(1);
    }
}

extern float GetDifferenceFromLowerField(GObj *volatile a0, int node);

/* The 0x15C slot is the engine's sub-object handle, read here as the SubHandle
 * union the way geometryManager.c's SUBOF reads it; the other readers use
 * GOBJ_SUB's int view. */
#define FALL_SUB(o) ((Sub15C *)((SubHandle *)((char *)(o) + 0x15C))->p) /* derived name */

/* A static inline that actCommonFall and flyCoreLoop call: whether the
 * actor has been stuck on a step for `need` hits.  flyCoreLoop passes a
 * motion that is not 418 and needs three hits where actCommonFall needs
 * two. */
static inline int IsFallStuckOnStep(GObj *a0, int state, int mot, int need,
                                    int time) /* derived name */
{
    Act *s = GOBJ_ACT(a0);
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

void actCommonFall(GObj *volatile a0)
{
    float pa[4];
    float pb[4];
    float hit[4];
    float lo[4];
    float hi[4];
    Act *s = GOBJ_ACT(a0);
    int noVel;
    int wasHigh;
    int slowed;
    unsigned int mot;
    float d;
    char *p;
    int keep;
    int n;

    wasHigh = 0;
    noVel = 0;
    slowed = 0;
    ((Act *)(char *)s)->flags18.afterProc = (void (*)(char *))actAfterFall;
    if (stageData[stage_no].flag3) {
        keep = FALL_SUB(a0)->ctrl.floorAttr & 0xF;
        debug_StdPrintfDummy("0x%8x -> 0x%8x\n", FALL_SUB(a0)->ctrl.floorAttr, keep);
        FALL_SUB(a0)->ctrl.floorAttr = 0;
        FALL_SUB(a0)->ctrl.floorAttr = keep;
    } else {
        FALL_SUB(a0)->ctrl.floorAttr = 0;
    }
    mot = (unsigned int)s->intrKind;
    switch (mot) {
    case 226:
        if (*(int *)((char *)GOBJ_ACT(a0)->work + 0x900) == 34 ||
            *(int *)((char *)GOBJ_ACT(a0)->work + 0x900) == 28 ||
            *(int *)((char *)GOBJ_ACT(a0)->work + 0x900) == 30) {
            FALL_SUB(a0)->root.move[0] = 0;
            noVel = 1;
            FALL_SUB(a0)->root.move[1] = 0;
            FALL_SUB(a0)->root.move[2] = 0;
        }
        break;
    case 329:
        SetMotionDirection(a0, GOBJ_WORK(a0)->handrailOrient);
        break;
    case 166:
        FALL_SUB(a0)->root.move[0] = 0;
        FALL_SUB(a0)->root.move[1] = 0;
        FALL_SUB(a0)->root.move[2] = 0;
        break;
    case 24:
        FALL_SUB(a0)->root.move[0] = 0;
        FALL_SUB(a0)->root.move[1] = 0;
        FALL_SUB(a0)->root.move[2] = 0;
        wasHigh = 1;
        noVel = 1;
        break;
    case 49:
        sceVu0ScaleVector(&FALL_SUB(a0)->root.move[0], test_CURRENTORIENT(a0), -5.0f);
        FALL_SUB(a0)->root.move[1] = 3.0f;
        wasHigh = 1;
        ((ActStatus *)((char *)s + 0x18))->ll |= (1ULL << 53);
        GOBJ_WORK(a0)->fallDamageHeight = 200.0f;
        break;
    case 48:
        GetSkeltonPosition(pa, s->intrArg, 44);
        GetSkeltonPosition(pb, a0, 44);
        lo[0] = pb[0];
        lo[1] = pb[1];
        lo[2] = pb[2];
        if (ACTCheckCollis_WAY(40.0f, pa, pb, 0, hit)) {
            lo[0] = pa[0];
            lo[1] = pa[1];
            lo[2] = pa[2];
            ACTSetPositionNoFitting(a0, pa);
        }
        hi[0] = lo[0];
        hi[1] = lo[1];
        hi[2] = lo[2];
        lo[1] = lo[1] - 100.0f;
        hi[1] = hi[1] + 100.0f;
        if (ACTCheckCollis_WELL(lo, hi, 0, hit, 0.0f)) {
            hit[1] = hit[1] - 105.0f;
            ACTSetPositionNoFitting(a0, hit);
        }
        break;
    case 316:
        d = GetDifferenceFromLowerField(a0, 44);
        wasHigh = 1;
        ((ActStatus *)((char *)s + 0x18))->ll |= (1ULL << 53);
        FALL_SUB(a0)->root.move[0] = 0;
        FALL_SUB(a0)->root.move[1] = 0;
        FALL_SUB(a0)->root.move[2] = 0;
        if (d < 800.0f) {
            GOBJ_WORK(a0)->fallDamageHeight = 900.0f;
        } else {
            if (*(int *)((char *)GOBJ_ACT(a0)->work + 0x900) != 38) {
                p = (char *)GOBJ_ACT(a0)->intrData;
                if (p != 0 && 100.0f < *(float *)p && *(float *)p < 500.0f) {
                    GOBJ_WORK(a0)->fallDamageHeight = *(float *)p;
                    break;
                }
            }
            GOBJ_WORK(a0)->fallDamageHeight = 500.0f;
        }
        break;
    default:
        if (mot == 7 && *(int *)((char *)GOBJ_ACT(a0)->work + 0x950) == 259) {
            FALL_SUB(a0)->root.move[0] = 0;
            FALL_SUB(a0)->root.move[1] = 0;
            FALL_SUB(a0)->root.move[2] = 0;
            noVel = 1;
        }
        n = *(int *)((char *)GOBJ_ACT(a0)->work + 0x900);
        if (19 <= n) {
            if (22 <= n) {
                if (n < 29) {
                    if (27 <= n) {
                        FALL_SUB(a0)->root.move[0] = 0;
                        FALL_SUB(a0)->root.move[1] = 0;
                        FALL_SUB(a0)->root.move[2] = 0;
                        noVel = 1;
                    }
                }
            } else {
                wasHigh = 1;
            }
        }
        if ((char *)a0 == (char *)girlGObj && mot == 7 &&
            *(int *)((char *)GOBJ_ACT(a0)->work + 0x900) == 21) {
            slowed = 1;
            FALL_SUB(a0)->root.move[1] = 0;
        }
        if ((unsigned char)IsFallStuckOnStep(a0, 5, 418, 2, 60)) {
            ((Act *)(char *)s)->flags20.ll |= (1ULL << 42);
        }
        break;
    }
    while (1) {
        if (s->modeFrame < ((60 - systemStatus[0] * 10) / systemStatus[1]) / 6) {
            if (wasHigh) {
                ((ActStatus *)((char *)s + 0x18))->ll |= (1ULL << 52);
            }
            if (noVel) {
                FALL_SUB(a0)->root.move[0] = FALL_SUB(a0)->root.move[2] = 0.0f;
            }
            if (slowed) {
                FALL_SUB(a0)->root.move[0] *= 0.8;
                FALL_SUB(a0)->root.move[2] *= 0.8;
            }
        }
        ACTSendMailCorrect(a0, 314);
        _ACTWait(1);
    }
}

/* the sub-object's fly-limit flag at 0x654 */
typedef struct { /* field names derived */
    char pad0[1620];
    int limit;
} FlyLimitSub; /* derived name */

/* raises the flag that ResetFlyLimit clears */
static inline void SetFlyLimit(int a0) /* derived name */
{
    ((FlyLimitSub *)FALL_SUB(a0))->limit = 1;
}

/* used by flyCoreLoop and actAfterFly */
static inline void ResetFlyLimit(int a0) /* derived name */
{
    ((FlyLimitSub *)FALL_SUB(a0))->limit = 0;
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

static void debugDispFlyLimit(float *pos, float y0, float y1)
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

void debugDispSphere(void *a0, void *a1, float f)
{
    MatrixDrive_PushMatrix();
    _UnitMatrix(MatrixDrive_GetMatrix());
    gif_StartPacketPri(0xB);
    MatrixDrive_TransMatrixV(a0);
    prim_DispWireSphere(f, a1, 4, 4);
    gif_EndPacket();
    MatrixDrive_PopMatrix();
}

/* the fly has run for more than 180 seconds */
static inline unsigned char IsFlyTimeOver(int a0) /* derived name */
{
    if ((60 - systemStatus[0] * 10) / systemStatus[1] * 180 < GOBJ_WORK(a0)->carryGirlFrames) {
        return 1;
    }
    return 0;
}

/* no header declares it */
extern void GetRootMotionMatrix(void *m, char *obj);
/* no header declares it */
extern float GetEnemyFlyXZAccel(int a0);
/* no header declares it; this call passes the position's address */
extern void SetDarkVolumeEffect(float *pos, float size);
/* info is void * here, FlyLimitInfo * in flyManager.h */
extern int GetFlyLimitHeight(void *info, void *pos);

/* GetFlyLimitHeight's result, as flyManager.c fills it */
typedef struct { /* field names derived */
    float floorY;
    float limitY;
    float limitOfs;
    int flags;
} FlyLimit; /* derived name */

/* The 0xC0-byte ClipWall/ClipFloor work record as the fly code reads it (the
   other views of it in this TU are kept apart for the reason given at
   RopeWallWork).  The vectors are FlyPt, 8-byte aligned. */
typedef struct { /* field names derived */
    FlyPt v[7];  /* 0x00 from, 0x10 to, 0x20 the hit position */
    float rad;
    char pad74[20];
    int wall;
    char pad8C[8];
    int floor;
    char pad98[40];
} FlyClip; /* derived name */

/* the clip request at 0x690 of the actor record */
typedef struct { /* field names derived */
    int done;
    char pad4[12];
    FlyClip w;
    int fD0;
    void (*func)();
} FlyClipReq; /* derived name */

void flyCoreLoop(GObj *a0, GObj *target, int a2)
{
    Act *act = GOBJ_ACT(a0);
    float lenSq;
    float spd;
    unsigned long stuck = a2 && IsFallStuckOnStep(a0, 6, debug_fly_limit_test ? 29 : 30, 3, 600);
    int flags = 0;
    int ringidx;
    int landCnt = 0;
    short ang = 0;
    int landed = 0;
    float off[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float acc = 0.0f;
    float emgpos[4];
    int needInit = 1;
    int mode = 0;
    float fc = 0.0f;
    float ring[5][4];
    float mat[4][4];
    int wait = 0;
    int dbg = 0; /* local debug switch, see the test after spd below */
    int cnt104 = 0;
    float root[4];
    int cnt114 = 0;
    float vC0[4];
    float dir[4];
    int ringcnt = 0;
    for (ringidx = 0; ringidx < 5; ringidx++) {
        CopyVector(ring[ringidx], ZeroPoint);
    }
    ringidx = 0;
    if (stuck) {
        debug_StdPrintfDummy("\x1b[36mEMERGENCY WITH DANGER LOOP\x1b[m\n");
        flags |= 1;
        SetFlyLimit((int)a0);
    }
    if (stage_no == 86 || stage_no == 3 || stage_no == 46) {
        emgpos[0] = GOBJ_WORK(a0)->emgPosX;
        emgpos[1] = GOBJ_WORK(a0)->emgPosY;
        emgpos[2] = GOBJ_WORK(a0)->emgPosZ;
    }
    while (1) {
        int getLandOffset(float *out, float *pos, short ang, float h)
        {
            FlyClip w;

            memset(&w, 0, 0xC0);
            _UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_TransMatrixV((char *)pos);
            MatrixDrive_RotMatrixY(ang);
            MatrixDrive_TransMatrix(0.0f, 0.0f, h);
            CopyVector(w.v[1].f, (char *)MatrixDrive_GetMatrix() + 0x30);
            CopyVector(w.v[0].f, pos);
            w.v[0].f[3] = w.v[1].f[3] = 1.0f;
            w.v[0].f[1] -= 50.0f;
            w.v[1].f[1] -= 50.0f;
            ClipWall(&w);
            if (w.wall) {
                return 0;
            }
            CopyVector(w.v[0].f, w.v[1].f);
            w.v[1].f[1] += 100.0f;
            ClipFloor(&w);
            if (w.floor) {
                _SubVectorXYZ(out, w.v[2].f, pos);
                return 1;
            }
            return 0;
        }

        inline void RequestFlyClip(FlyClipReq * req, void (*func)()) /* derived name */
        {
            req->func = func;
            req->w.rad = 50.0f;
            CopyVector(req->w.v[0].f, mat[3]);
            CopyVector(req->w.v[1].f, root);
            req->fD0 = 0;
            RequestClipCollision((int *)req);
        }

        inline void FlyStep(void) /* derived name */
        {
            if (needInit) {
                RequestFlyClip((FlyClipReq *)((char *)act + 0x690),
                               a2 ? ClipCollisionWithField : ClipCollision);
                needInit = 0;
            } else if (((FlyClipReq *)((char *)act + 0x690))->done) {
                if (((FlyClipReq *)((char *)act + 0x690))->w.wall ||
                    ((FlyClipReq *)((char *)act + 0x690))->w.floor) {
                    if (10000.0f < VectorLengthSquare(dir)) {
                        acc = -1.0f;
                    } else if (0.0f < vC0[1]) {
                        acc = 1.0f;
                    } else {
                        acc = -1.0f;
                    }
                } else {
                    acc = calcFlyAccel(root, mat[3]);
                }
                RequestFlyClip((FlyClipReq *)((char *)act + 0x690),
                               a2 ? ClipCollisionWithField : ClipCollision);
            }
            {
                FlyLimit info;

                if (GetFlyLimitHeight(&info, mat[3])) {
                    if (debug_fly_limit_test) {
                        int save = debug_font_flag;

                        debugDispFlyLimit(mat[3], info.limitY, info.floorY);
                        debug_font_flag = 1;
                        debug_Printf(10, 160, 0xFFFFFF00, "[%s] %4d %4d %4d", "limit",
                                     (int)info.floorY, (int)info.limitY, (int)info.limitOfs);
                        debug_font_flag = save;
                    }
                    if (lenSq < 90000.0f && (info.floorY < root[1] || root[1] < info.limitY)) {
                        FlyClip w = {{{{0.0f}}}, 50.0f};

                        CopyVector(w.v[0].f, mat[3]);
                        w.v[0].f[1] += 100.0f;
                        _ApplyMatrix(w.v[1].f, mat, ZUnitVector);
                        w.v[1].f[1] = 0.0f;
                        _NormalizeVector(w.v[1].f, w.v[1].f);
                        _ScaleVectorXYZ(w.v[1].f, w.v[1].f, 200.0f);
                        _AddVectorXYZ(w.v[1].f, w.v[0].f, w.v[1].f);
                        ClipWall(&w);
                        if (w.wall) {
                            MatrixDrive_PushMatrix();
                            CopyMatrix(MatrixDrive_GetMatrix(), mat);
                            if (stage_no == 19 || stage_no == 28) {
                                MatrixDrive_RotMatrixY(-24576);
                            } else {
                                MatrixDrive_RotMatrixY(4096);
                            }
                            _ApplyMatrix(dir, MatrixDrive_GetMatrix(), ZUnitVector);
                            dir[1] = 0.0f;
                            _NormalizeVector(dir, dir);
                            MatrixDrive_PopMatrix();
                            SetMotionDirection(a0, dir);
                            acc = -1.0f;
                        } else if (info.floorY < root[1]) {
                            acc = 1.0f;
                            mode = 1;
                            fc = info.floorY;
                        } else {
                            acc = -1.0f;
                            mode = 2;
                            fc = info.limitY;
                        }
                        if (debug_fly_limit_test) {
                            static int col[4] = {0, 255, 128, 128};
                            debugDispSphere(mat[3], col, 100.0f);
                        }
                    } else {
                        _ACTMotDirSmzDirect((char *)a0, dir);
                    }
                    if (info.limitY > mat[3][1]) {
                        acc = clampUnit((info.limitY - mat[3][1]) * 0.05f);
                    }
                } else if (mode == 0) {
                    _NormalizeVector(dir, dir);
                    _ACTMotDirSmzDirect((char *)a0, dir);
                } else {
                    acc = clampUnit((root[1] - mat[3][1]) * 0.005f);
                    if (360000.0f < lenSq) {
                        mode = 0;
                    }
                    if (mode == 1) {
                        acc = 1.0f;
                        if (fc < mat[3][1]) {
                            mode = 0;
                        }
                    } else {
                        acc = -1.0f;
                        if (mat[3][1] < fc) {
                            mode = 0;
                        }
                    }
                    if (debug_fly_limit_test) {
                        static int col[4] = {0, 0, 128, 128};
                        debugDispSphere(mat[3], col, 100.0f);
                    }
                }
            }
        }

        GOBJ_SUB(a0)->root.fieldWall = a2;
        GetRootMotionMatrix(mat, (char *)a0);
        if (target) {
            GetRootPosition(root, target);
            if (stage_no == 86 || stage_no == 3 || stage_no == 46) {
                root[0] = emgpos[0];
                root[1] = emgpos[1];
                root[2] = emgpos[2];
            }
            if (stuck) {
                root[1] += -100.0f;
            } else {
                root[1] += GOBJ_SUB(target)->root.projHeight;
                if ((60 - systemStatus[0] * 10) / systemStatus[1] < landCnt++ || !landed) {
                    landed = getLandOffset(off, root, ang, 100.0f);
                    if (!landed) {
                        ang += 4096;
                    }
                    landCnt = 0;
                }
                if (landed) {
                    _AddVectorXYZ(root, root, off);
                }
                root[1] -= 10.0f;
            }
            if (debug_fly_limit_test) {
                static int col[4] = {0, 128, 255, 128};
                debugDispSphere(root, col, 10.0f);
            }
        } else {
            CopyVector(root, ZeroPoint);
        }
        _SubVector(vC0, root, mat[3]);
        CopyVector(dir, vC0);
        dir[1] = 0.0f;
        lenSq = VectorLengthSquare(dir);
        spd = distance_squared(root, mat[3]);
        /* a local debug switch, off: print the distance */
        if (dbg) {
            debug_StdPrintfDummy("%1.1f ", lenSq);
        }
        if (stuck) {
            int completeEmergency(void)
            {
                if (debug_fly_limit_test) {
                    debug_StdPrintfDummy("EMERGENCY COMPLETE CHECK : SPEEDSQ:%f LENSQ:%f\n",
                                         VectorLengthSquare((char *)GOBJ_SUB(a0) + 0x130), spd);
                }
                if (stage_no != 86 && stage_no != 3 && stage_no != 46) {
                    if (VectorLengthSquare((char *)GOBJ_SUB(a0) + 0x130) < 50.0f && spd < 1000.0f) {
                        return 1;
                    }
                } else {
                    if (VectorLengthSquare((char *)GOBJ_SUB(a0) + 0x130) < 300.0f &&
                        spd < 7000.0f) {
                        cnt104 = 0;
                        return 1;
                    }
                }
                return 0;
            }

            int y = 30;

            if (flags & 2)
                debug_PrintfDummy(10, y += 10, 0x80FF0080, "EMERGENCY BY NOMOVE");
            if (flags & 4)
                debug_PrintfDummy(10, y += 10, 0x80FF0080, "EMERGENCY BY TIMEOUT");
            if (flags & 1)
                debug_PrintfDummy(10, y += 10, 0x80FF0080, "EMERGENCY BY DANGER LOOP");
            acc = calcVertAccel(root, mat[3]);
            _ACTMotDirSmzDirect((char *)a0, dir);
            if (stage_no != 86 && stage_no != 3 && stage_no != 46) {
                SetDarkVolumeEffect(mat[3], 100.0f);
            }
            if (completeEmergency()) {
                ResetFlyLimit((int)a0);
                debug_StdPrintfDummy("%p complete.\n", a0);
                stuck = 0;
            }
        } else {
            int emergencyCheck(void)
            {
                float prev[4];
                float mx;
                float d;
                int i;

                if (wait == 0) {
                    mx = 0.0f;
                    CopyVector(prev, ring[ringidx]);
                    CopyVector(ring[ringidx], mat[3]);
                    if (ringcnt < 5) {
                        for (i = 0; i < ringcnt; i++) {
                            d = distance_squared(ring[0], ring[i]);
                            if (mx < d) {
                                mx = d;
                            }
                        }
                    } else {
                        for (i = 0; i < 5; i++) {
                            d = distance_squared(prev, ring[i]);
                            if (debug_fly_limit_test) {
                                debug_StdPrintfDummy("%1.1f ", d);
                            }
                            if (mx < d) {
                                mx = d;
                            }
                        }
                    }
                    ringcnt = ringcnt + 1;
                    ringidx = ringidx + 1;
                    if (ringidx == 5) {
                        ringidx = 0;
                    }
                    if (debug_fly_limit_test) {
                        debug_StdPrintfDummy("EMERGENCY CHECK %d(%d): MAX: %f\n", cnt114, ringcnt,
                                             mx);
                    }
                    if (ringcnt >= 5 && mx < 10000.0f) {
                        debug_StdPrintfDummy("\x1b[36mEMERGENCY WITH NO MOVE\x1b[m\n");
                        flags |= 2;
                        return 1;
                    }
                    if (debug_fly_limit_test == 0 && IsFlyTimeOver((int)a0)) {
                        debug_StdPrintfDummy("\x1b[36mEMERGENCY WITH TIME OUT\x1b[m\n");
                        flags |= 4;
                        return 1;
                    }
                }
                wait = wait + 1;
                if (wait == 30) {
                    wait = 0;
                }
                return 0;
            }

            FlyStep();
            if (a2 && ((int)(act->flags20.ll >> 21) & 1) == 0 && emergencyCheck()) {
                SetFlyLimit((int)a0);
                stuck = 1;
            }
        }
        _ScaleVectorXYZ((char *)GOBJ_SUB(a0) + 0x130, (char *)GOBJ_SUB(a0) + 0x130, 0.92f);
        if (((int)(act->flags20.ll >> 21) & 1) == 0) {
            FlyPt v = {{0.0f, 0.0f,
                        stage_no == 86 || stage_no == 3 || stage_no == 46
                            ? 3.0f
                            : (a2 ? GetEnemyFlyXZAccel((int)a0) : 1.0f),
                        0.0f}};

            _ApplyMatrix(&v, mat, &v);
            v.f[1] = 0.0f;
            _AddVectorXYZ((char *)GOBJ_SUB(a0) + 0x130, (char *)GOBJ_SUB(a0) + 0x130, &v);
            GOBJ_SUB(a0)->root.move[1] += acc * 2.0f;
        }
        if ((stage_no == 86 || stage_no == 3 || stage_no == 46) &&
            (60 - systemStatus[0] * 10) / systemStatus[1] * 10 < cnt104) {
            SetFlyLimit((int)a0);
            stuck = 1;
        }
        act->flags18.ll = (act->flags18.ll & ~(1ULL << 57)) | (stuck << 57);
        _ACTWait(1);
        cnt114++;
        cnt104++;
    }
}

typedef struct { /* field names derived */
    char pad0[1528];
    int f5F8;
} FlyCtlJ; /* derived name */

void actCommonFly(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    GObj *target;
    char *gen = 0;

    ((ActFlagJ *)((char *)s + 0x18))->ll &= ~(1ULL << 57);
    ((ActFlagJ *)((char *)s + 0x18))->p = (void *)actAfterFly;

    ((FlyCtlJ *)(char *)GOBJ_SUB(a0))->f5F8 = 0;

    if (IsEnemyBrainToGenerator(a0, &gen)) {
        target = gen;
    } else if (IsEnemyBrainToBoy(a0) && (char *)boyGObj != 0) {
        target = boyGObj;
    } else if ((char *)girlGObj != 0) {
        target = girlGObj;
    } else if ((char *)boyGObj != 0) {
        target = boyGObj;
    } else {
        target = 0;
    }

    SetEnemyFootPrintSwitch(a0, 0);

    flyCoreLoop(a0, target,
                ((char *)girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 0x6F &&
                 GOBJ_ACT(girlGObj)->carrier == a0) ||
                    debug_fly_limit_test != 0);
}

typedef struct { /* field names derived */
    char pad0[656];
    int f290;
    int f294;

    union {
        unsigned long long ll;
        int i[2];
    } f298;
} LadderWork; /* derived name */

#define LADW ((LadderWork *)*(int *)(a0->act + 0x680)) /* derived name */

void actCommonLadder(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
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
    char *o;

    if (s->edgePos[3] != 0.0f) {
        pos[0] = test_CURRENTROOT((void *)a0)[0];
        pos[1] = test_CURRENTROOT((void *)a0)[1];
        pos[2] = test_CURRENTROOT((void *)a0)[2];
        pos[0] = s->edgePos[0];
        pos[2] = s->edgePos[2];
        s->edgePos[3] = 0.0f;
    }
    LADW->f290 = 0;
    LADW->f294 = 0;
    LADW->f298.ll &= ~1ULL;
    LADW->f298.ll &= ~2ULL;
    LADW->f298.ll &= ~4ULL;
    if (a0 == (int)((char *)boyGObj)) {
        GOBJ_ACT(a0)->hit = 1;
    }
    if (mot == 0x7F || mot == 0x80 || mot == 0x7B) {
        while (1) {
            if (a0 == (int)((char *)boyGObj) && GOBJ_SUB(a0)->ctrl.animFrame > 40.0f) {
                break;
            }
            if (motionKind[GOBJ_SUB(a0)->ctrl.motion].playMode == 1) {
                break;
            }
            _ACTWait(1);
        }
    }
    while (1) {
        uf22 = (int)GetDifferenceFromWallUpperField((void *)a0, 22);
        uf6 = (int)GetDifferenceFromWallUpperField((void *)a0, 6);
        lf52 = (int)GetDifferenceFromLastField((void *)a0, 52);
        lf48 = (int)GetDifferenceFromLastField((void *)a0, 48);
        up22 = (int)GetDifferenceFromWallUpperPlane((void *)a0, 22);
        up6 = (int)GetDifferenceFromWallUpperPlane((void *)a0, 6);
        lp52 = (int)GetDifferenceFromWallLowerPlane((void *)a0, 52);
        lp48 = (int)GetDifferenceFromWallLowerPlane((void *)a0, 48);
        LADW->f290 = 0;
        LADW->f294 = 0;
        LADW->f298.ll &= ~4ULL;
        LADW->f298.ll |= 1ULL;
        LADW->f298.ll |= 2ULL;
        if ((uf22 - up22 < 0 ? up22 - uf22 : uf22 - up22) < 30) {
            if (uf22 < 10) {
                LADW->f290 = 1;
            }
            if (uf6 < 10) {
                LADW->f290 = 2;
            }
        } else {
            if (up22 < 40) {
                LADW->f298.ll &= ~1ULL;
            }
            if (up6 < 40) {
                LADW->f298.ll &= ~1ULL;
            }
        }
        if ((lf52 - lp52 < 0 ? lp52 - lf52 : lf52 - lp52) < 30) {
            if (lf52 >= -9) {
                LADW->f294 = 1;
            }
            if (lf48 >= -9) {
                LADW->f294 = 2;
            }
        } else {
            if (lp52 >= 31) {
                LADW->f298.ll |= 4ULL;
            }
            if (lp48 >= 31) {
                LADW->f298.ll |= 4ULL;
            }
        }
        if (s->pushDir == 0xFFFFFFFF && ((int)((long long)LADW->f298.ll >> 2) & 1)) {
            ACTSendMailCorrect(a0, 0x8E);
            if (a0 != (int)((char *)boyGObj)) {
                ACTSendMailCorrect(a0, 0x8F);
            }
        }
        if (a0 == (int)((char *)boyGObj) && (char *)girlGObj != 0 &&
            GOBJ_ACT(girlGObj)->actMode == 0x26) {
            if (_DistSqGV(test_CURRENTROOT((void *)a0), test_CURRENTROOT(girlGObj)) < 3600.0f) {
                ACTSendMailCorrect(a0, 0x31);
            }
        }
        if (a0 == (int)((char *)boyGObj) || a0 == (int)((char *)girlGObj)) {
            pos[0] = test_CURRENTROOT((void *)a0)[0];
            pos[1] = test_CURRENTROOT((void *)a0)[1];
            pos[2] = test_CURRENTROOT((void *)a0)[2];
            for (o = (char *)isysGObjSearchFromObjKindID_begin(4); o != 0;
                 o = (char *)isysGObjSearchFromObjKindID_next(o)) {
                if (*(int *)(o + 0x16C) != 0) {
                    if (GOBJ_ACT(o)->actMode == 0x26 &&
                        _DistSqGV(pos, test_CURRENTROOT(o)) < 6400.0f) {
                        ACTSendMailCorrect(a0, 0x31);
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
inline void actCommonCliffdown(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonCliffdown\n");
    SetMotionDirection(a0, s->cliffOrient);
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonShoal(GObj *volatile a0)
{
    debug_StdPrintfDummy("act main shoal\n");
    _ACTWait(0);
}

inline void actCommonSwim(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter actCommonSwim\n");
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonDodge(GObj *volatile a0)
{
    float dir[4];
    int id = 0;
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonDodge\n");
    if (a0->kind == 1) {
        ACTSearchEnemy((void *)a0, &id, dir);
    } else {
        _OrientXZGV(s->dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, s->dir);
    }
    while (1) {
        if (id != 0) {
            SetMotionDirectionWithLimit((void *)a0, dir, 10.0f, 90.0f);
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonGuard(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonGuard\n");
    SetMotionDirection(a0, (char *)GOBJ_ACT(a0) + 0x1C0);
    if (a0->kind == 4) {
        EBRAIN_SEND_MES((void *)a0, 6);
        ACTGame_LwsEffect_Guard((void *)a0);
    }
    iosOmSendMail(boyGObj, 0x11C, a0);
    if (s->intrKind == 0x11A) {
        ACTSetPositionWithFitting((void *)a0, test_CURRENTROOT((void *)a0));
    }
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

#undef LADW

typedef struct { /* field names derived */
    char pad0[32];
    float _20, _24, _28;
    char pad2C[68];
    float _70;
    char pad74[12];
    int _80;
    char pad84[4];
    int _88;
    int _8c;
    char pad90[4];
    int _94;
    int _98;
    char pad9C[36];
} EdgeHangWork; /* derived name */

void actCommonEdgeHang(GObj *volatile a0)
{
    EdgeHangWork work;
    float p1[4];
    float p2[4];

    ACTAdjustPlane(a0, GOBJ_ACT(a0)->work + 0x8B0);
    while (1) {
        if (CheckWallAttributeEdegWall((void *)a0) == 0) {
            ACTSendMailCorrect(a0, 0xE2);
        }
        if (-GOBJ_SUB(a0)->ctrl.cliffDepth > 250.0f) {
            ACTSendMailCorrect(a0, 0x18);
        }
        if (stageData[stage_no].flag2) {
            memset(&work, 0, 0xC0);
            GetSkeltonPosition((float *)&work, a0, 0x2C);
            GetSkeltonPosition(p1, a0, 0x33);
            GetSkeltonPosition(p2, a0, 0x2F);
            sceVu0AddVector((char *)&work + 0x10, p1, p2);
            sceVu0ScaleVector((char *)&work + 0x10, (char *)&work + 0x10, 0.5f);
            ClipFloor(&work);
            if (work._94 != 0) {
                ACTSendMailCorrect(a0, 0xE2);
            }
        }
        _ACTWait(1);
    }
}

inline void motCommonHangNone(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter motCommonHang None\n");
    _ACTWait(0);
}

inline void motCommonHangWall(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter motCommonHang Wall\n");
    _ACTWait(0);
}

inline void motCommonHangCliff(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter motCommonHang Cliff\n");
    _ACTWait(0);
}

inline void motCommonNull(GObj *volatile a0)
{
    debug_StdPrintfDummy("enter motCommonNull\n");
    for (;;) {
        _ACTWait(1);
    }
}

void funcCommonBeginReady(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->readyFlags |= 1;
    debug_StdPrintfDummy("ready begin %s to %s\n", a2 == (char *)boyGObj ? "boy" : "girl",
                         a0 == (char *)boyGObj ? "boy" : "girl");
}

void funcCommonEndReady(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->readyFlags |= 2;
    debug_StdPrintfDummy("ready end %s to %s\n", a2 == (char *)boyGObj ? "boy" : "girl",
                         a0 == (char *)boyGObj ? "boy" : "girl");
}

void funcCommonEndExec(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->readyFlags |= 8;
    debug_StdPrintfDummy("exec end %s to %s\n", a2 == (char *)boyGObj ? "boy" : "girl",
                         a0 == (char *)boyGObj ? "boy" : "girl");
}

void funcCommonError(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->readyFlags |= 0x10;
    debug_StdPrintfDummy("????error %s to %s\n", a2 == (char *)boyGObj ? "boy" : "girl",
                         a0 == (char *)boyGObj ? "boy" : "girl");
}

int SetMotionDirectionSmooze(GObj *a0, float *dir, float s)
{
    float v[4];
    Act *sub = GOBJ_ACT(a0);
    int ret = 0;
    int r;

    if (s < 0.0f) {
        return 0;
    }
    s = s * 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    if (dir[0] == 0.0f && dir[1] == 0.0f && dir[2] == 0.0f) {}
    if (((motionKind + GOBJ_SUB(a0)->ctrl.motion)->flags.word >> 6) & 1 &&
        *(long long *)((char *)sub->work + 0x900) == 0x1A00000005LL) {
        s = 30.0f;
    }
    if ((int)(sub->flags20.ll >> 33) & 1) {
        s = ((ActWork *)sub->work)->lockedMaxRotate;
    }
    r = _RotyGV(test_CURRENTORIENT(a0), dir);
    if ((float)(r < 0 ? -r : r) < s) {
        ret = 1;
        v[0] = dir[0];
        v[1] = dir[1];
        v[2] = dir[2];
    } else if (r > 0) {
        v[0] = test_CURRENTORIENT(a0)[0];
        v[1] = test_CURRENTORIENT(a0)[1];
        v[2] = test_CURRENTORIENT(a0)[2];
        _ApplyRyGV(v, -s * 3.1415927f / 180.0f);
    } else {
        v[0] = test_CURRENTORIENT(a0)[0];
        v[1] = test_CURRENTORIENT(a0)[1];
        v[2] = test_CURRENTORIENT(a0)[2];
        _ApplyRyGV(v, s * 3.1415927f / 180.0f);
    }
    SetMotionDirection(a0, v);
    return ret;
}

/* motionOrientManager.h declares none of the motion tables */
extern MotOriName motionOriKind[];

void _ACTDebugPrint(GObj *a0)
{
    Act *sub;
    char *w;

    if (a0 == 0) {
        return;
    }
    sub = GOBJ_ACT(a0);
    if ((char *)sub == 0) {
        return;
    }
    w = (char *)GOBJ_SUB(a0) + 0x470;
    if (w == 0) {
        return;
    }
    if (debug_font_flag & 1) {
        debug_Printf(30, 90, 0xFFFFFFF, " ori  = [%s]\n", motionOriKind[*(int *)(w + 0xD0)].s);
        if (debug_font_flag & 1) {
            debug_Printf(30, 100, 0xFFFFFFF, " mot  = [%s]\n",
                         (motionKind + GOBJ_SUB(a0)->ctrl.motion)->name);
            if (debug_font_flag & 1) {
                debug_Printf(30, 110, 0xFFFFFFF, " mode = [%s]\n", actModeTbl[sub->actMode].name);
                if (debug_font_flag & 1) {
                    debug_Printf(30, 120, 0xFFFFFFF, "frame = [%f]\n",
                                 GOBJ_SUB(a0)->ctrl.animFrame);
                    if (debug_font_flag & 1) {
                        debug_Printf(30, 130, 0xFFFFFFF, "maxry = [%d]\n",
                                     a0 == girlGObj && (void *)girlControlMode != 0
                                         ? (motionKind + GOBJ_SUB(a0)->ctrl.motion)->girlDirFrames
                                         : (motionKind + GOBJ_SUB(a0)->ctrl.motion)->dirFrames);
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
                                                     GOBJ_SUB(a0)->ctrl.wallAttr);
                                        if (debug_font_flag & 1) {
                                            debug_Printf(30, 180, 0xFFFFFFF, "bttype= [%d]\n",
                                                         GOBJ_ACT(a0)->enemy->battleType);
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

void ACTSendMailCorrect(GObj *a0, int a1)
{
    Act *s = GOBJ_ACT(a0);
    if ((a1 == 0xB5 || a1 == 0xBA) && a0->kind == 1) {
        long long f = (long long)s->wish2.ll;
        if (((int)(f >> 5) & 1) && ((int)((long long)s->wish4.ll >> 5) & 1)) {
            a1 = 0xB6;
        } else if ((int)(f >> 3) & 1) {
            a1 = ((int)((long long)s->wish4.ll >> 3) & 1) ? 0xB7 : a1;
        }
    }
    iosOmSendMail(a0, a1, a0);
}

void _ACTCommonMailTest(GObj *self, int a1, int a2, int a3)
{
    Act *s;
    int ret = 0;
    unsigned int m;

    s = GOBJ_ACT(self);
    if (self == boyGObj) {
        if (optionControlType == 1 ? (s->padTrg & 8) != 0 : (s->padNow & 8) == 0) {
            handoff_heroin();
        }
    }
    m = (unsigned int)s->actMode;
    switch (m) {
    case 1:
    case 2:
    case 3:
    case 14:
    case 79:
    case 116:
        ret = 1;
        break;
    case 36:
        if (self == boyGObj || self == girlGObj) {
            ret = 1;
        }
        break;
    case 29:
        ret = self == girlGObj;
        break;
    case 15:
    case 20:
    case 21:
        ret = self == boyGObj;
        break;
    }
    if (((motionKind + GOBJ_SUB(self)->ctrl.motion)->flags2.word >> 1) & 1) {
        ret = 1;
    }
    if (ret) {
        if (0.1f < s->stickMag && (unsigned int)(s->stickAngle + 45) < 91) {
            ACTSendMailCorrect(self, 0x14C);
        }
        if (0.1f < s->stickMag && !((unsigned int)(s->stickAngle + 134) < 269) &&
            !(s->actMode == 3 && ((int)(s->flags18.ll >> 44) & 1))) {
            ACTSendMailCorrect(self, 0x14D);
            if (((int)(s->flags20.ll >> 18) & 1) && !((int)(s->flags18.ll >> 44) & 1)) {
                ACTSendMailCorrect(self, 0xBC);
            }
        }
        if (0.1f < s->stickMag && (unsigned int)(s->stickAngle - 46) < 89) {
            ACTSendMailCorrect(self, 0x14E);
        }
        if (0.1f < s->stickMag && !(s->stickAngle < -134) && s->stickAngle < -45) {
            ACTSendMailCorrect(self, 0x14F);
        }
        if (0.1f < s->stickMag && (s->stickMag < 0.99f || (s->padNow & 0x20)) && !(a2 < 4)) {
            ACTSendMailCorrect(self, 0xB5);
        }
        /* the negated conjunct is the 0xB5 guard's whole predicate, repeated;
           it emits a real (dead) branch, so it is in the shipped code. */
        if (0.1f < s->stickMag &&
            !(0.1f < s->stickMag && (s->stickMag < 0.99f || (s->padNow & 0x20))) && !(a3 < 4)) {
            ACTSendMailCorrect(self, 0xBA);
        }
        if (!(0.1f < s->stickMag) && 0 < a1) {
            ACTSendMailCorrect(self, 0xC7);
        }
    }
    if (s->actMode == 0x49) {
        if (0.1f < s->stickMag && (s->stickMag < 0.99f || (s->padNow & 0x20)) && !(a2 < 4)) {
            ACTSendMailCorrect(self, 0xB5);
        }
        /* the negated conjunct is the 0xB5 guard's whole predicate, repeated;
           it emits a real (dead) branch, so it is in the shipped code. */
        if (0.1f < s->stickMag &&
            !(0.1f < s->stickMag && (s->stickMag < 0.99f || (s->padNow & 0x20))) && !(a3 < 4)) {
            ACTSendMailCorrect(self, 0xBA);
        }
    }
}

int E3_LeverCheck(GObj *a0)
{
    float buf[3];
    buf[0] = *(float *)((char *)test_CURRENTORIENT((char *)GOBJ_SUB(a0)->root.wall.o.obj) + 0x0);
    buf[1] = *(float *)((char *)test_CURRENTORIENT((char *)GOBJ_SUB(a0)->root.wall.o.obj) + 0x4);
    buf[2] = *(float *)((char *)test_CURRENTORIENT((char *)GOBJ_SUB(a0)->root.wall.o.obj) + 0x8);
    _ApplyRyGV(buf, -1.5707964f);
    return _RotyGV(test_CURRENTORIENT(a0), buf) < 0 ? -_RotyGV(test_CURRENTORIENT(a0), buf) < 0x2D
                                                    : _RotyGV(test_CURRENTORIENT(a0), buf) < 45;
}

extern SlowrunRec motionOrient[];

typedef struct { /* field names derived */
    char pad0[396];
    unsigned char f18C;
    char pad18D[7];
} CarryMot; /* derived name */

static __inline__ unsigned char requestBecarryMotion(char *self, int mot, int wait,
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

void actCommonBecarry(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    int cur = -1;
    char *g;
    int old;
    unsigned char done;
    unsigned long long fl;

    g = *(char **)((char *)s + 0x144);
    ACTGameCollisionOff((volatile int *)a0);
    ((ActFlagJ *)((char *)s + 0x18))->p = (void *)afterCommonBecarry;
    ((ActFlagJ *)((char *)s + 0x18))->ll &= ~(1ULL << 46);
    _ACTWait(1);
    while (1) {
        _ACTCharStatus_Set(a0, 9, -1.0f, 0);
        old = cur;
        cur = GOBJ_SUB(g)->ctrl.motion;
        if (old != cur) {
            done =
                requestBecarryMotion((char *)a0, cur, (GOBJ_ACT(g)->actMode == 103) ? 30 : 0, 2118);
            if (!done) {
                ((ActFlagJ *)((char *)s + 0x18))->ll |= (1ULL << 46);
            }
        }
        if (6 <= s->modeFrame) {
            if (actModeTbl[GOBJ_ACT(g)->actMode].carried ||
                (fl = ((CarryMot *)&motionKind[GOBJ_SUB(g)->ctrl.motion])->f18C, fl >> 7)) {
                afterCommonCarry((int)g);
                debug_StdPrintfDummy("girl becarry error");
            }
        }
        if (actModeTbl[GOBJ_ACT(boyGObj)->actMode].keepHand == 0) {
            ACTGame_DisconnectHand();
        }
        if (debug_font_flag & 1) {
            debug_Printf(100, 150, 0xFFFFFFF, "[%s]\n",
                         (motionKind + GOBJ_SUB(girlGObj)->ctrl.motion)->name);
        }
        if (debug_font_flag & 1) {
            debug_Printf(
                100, 160, 0xFFFFFFF, "[%s]\n",
                motionKind[*(int *)(*(char **)(*(char **)((char *)s + 0x144) + 0x15C) + 0x4A0)]
                    .name);
        }
        if (debug_font_flag & 1) {
            debug_Printf(
                100, 170, 0xFFFFFFF, "[%s]\n",
                actModeTbl[*(int *)(*(char **)(*(char **)((char *)s + 0x144) + 0x164) + 0x34)]
                    .name);
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

    if (mot != 1147 && mot2 != 1147) {
        motionOrient[n1].w[2] = mot;
        motionOrient[n2].w[2] = mot2;
        for (i = n3; i < n4; i++) {
            motionOrient[i].w[0] = mot;
        }
    }
}

void subCommonIdle(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
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
        cur = GOBJ_SUB(a0)->ctrl.motion;
        if (((char *)a0 == (char *)boyGObj && scpBoyControlReadDisable != 0) ||
            GOBJ_WORK(a0)->noInterpTimer > 0 || ((int)(s->flags20.ll >> 44) & 1)) {
            timer = 0;
            ACTSendMailCorrect(a0, 180);
        } else if (s->actMode != 1 && s->actMode != 69) {
            timer = 0;
        } else if ((int)(s->flags18.ll >> 62) & 1) {
            timer = 0;
            ACTSendMailCorrect(a0, 180);
        } else {
            if ((char *)a0 == (char *)boyGObj && ACTGame_FLAG_TETSUNAGI()) {
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
                        ACTSendMailCorrect(a0, 179);
                    }
                } else {
                    if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < timer) {
                        SetIdleMotionRange(k, idlingDef[base].motion[k], idlingDef[base].motion[k]);
                        ACTSendMailCorrect(a0, 179);
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
                    if ((char *)a0 == (char *)girlGObj && nxt == m0) {
                        nxt = idlingDef[0].motion[k];
                    }
                    SetIdleMotionRange(k, idlingDef[found].motion[k], nxt);
                    ACTSendMailCorrect(a0, 179);
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

void actCommonTurn(GObj *volatile a0)
{
    float q[4];
    float o[4];
    Act *s = GOBJ_ACT(a0);
    float *t = s->turnDir;
    int d;

    while (1) {
        GetRootMotionOrient(q, a0);
        d = _RotyGV(s->turnDir, q);
        debug_Arrow(100.0f, test_CURRENTROOT((void *)a0), s->turnDir, 0, 0, 0xFF);
        if (a0 == (int)((char *)girlGObj)) {
            GetSkeltonOrient(o, a0, 1);
            if (_AbsRotyGV(t, o) < 60) {
                if (s->stickMag != 0.0f) {
                    ACTSendMailCorrect(a0, 0xF0);
                }
                ACTSendMailCorrect(a0, 0xF1);
            }
        } else {
            if ((d < 0 ? -d : d) < 15) {
                ACTSendMailCorrect(a0, 0xF1);
            }
        }
        switch ((unsigned int)s->intrKind) {
        case 0xE7:
        case 0xE9:
            GOBJ_WORK(a0)->turnTimer = (60 - systemStatus[0] * 10) / systemStatus[1];
            break;
        case 0xE8:
        case 0xEA:
            GOBJ_WORK(a0)->turnTimer2 = (60 - systemStatus[0] * 10) / systemStatus[1];
            break;
        }
        _ACTWait(1);
    }
}

void actCommonBackhand(GObj *volatile a0)
{
    float v[4];
    float dir[4];
    float pos[4];
    int frame;

    _OrientXZGV(dir, test_CURRENTROOT((void *)a0), test_CURRENTROOT(girlGObj));
    SetMotionDirection(a0, dir);
    v[0] = test_CURRENTORIENT(girlGObj)[0];
    v[1] = test_CURRENTORIENT(girlGObj)[1];
    v[2] = test_CURRENTORIENT(girlGObj)[2];
    while (1) {
        sceVu0ScaleVector(pos, v, 50.0f);
        sceVu0AddVector(pos, test_CURRENTROOT(girlGObj), pos);
        SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, pos, 0.2f);
        if (GOBJ_SUB(a0)->ctrl.motion == 0xBD) {
            _OrientXZGV(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT((void *)a0));
            SetMotionDirection(a0, dir);
        }
        /* the frame budget is computed and dropped */
        frame = (0x3C - systemStatus[0] * 10) / systemStatus[1];
        _ACTWait(1);
    }
}

typedef union { /* field names derived */
    int i;
    float f;
} IntFloatSR; /* derived name */

void actCommonSlowrun(GObj *volatile a0)
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
        if (((motionKind + GOBJ_SUB(girlGObj)->ctrl.motion)->flags.word >> 29) & 1) {
            SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, p[0], 0.2f);
        } else {
            SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, p[0], 0.1f);
        }
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[20];
    int f14;
} TruckLeverWork; /* derived name */

void actCommonTruckLever(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    char *lev = (char *)s->pullObj;

    ((TruckLeverWork *)s)->f14 = (int)afterCommonTruckLever;
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(a0)->ctrl.frameFlag2 != 0) {
                correctLeverHoldPoint((void *)a0, lev);
            }
            if (GOBJ_SUB(a0)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}

void ACT_LAYOUT_GAMEOVER(void)
{
    if (gameover_layout_flag == 0) {
        gameover_layout_flag = 1;
        lt_switch_layout(62);
    }
}

void ACTAdjustPlane(GObj *a0, void *a1)
{
    AdjustRootPositionToVerticalSidePlaneOfWall(a0, a1, 30.0f);
}

inline void ACTAcceptMail(GObj *a0, int a1)
{
    if (a1 == 0xB1) {
        GOBJ_WORK(a0)->mailB1Timer = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 10;
    }
}

inline int _ACTMotDirSmzDirect(char *a0, float *a1)
{
    Act *s = GOBJ_ACT(a0);

    s->dir[0] = a1[0];
    s->dir[1] = a1[1];
    s->dir[2] = a1[2];
    return SetMotionDirectionSmooze(
        (int)a0, a1,
        (float)(a0 == (char *)girlGObj && (void *)girlControlMode != 0
                    ? (motionKind + GOBJ_SUB(a0)->ctrl.motion)->girlDirFrames
                    : (motionKind + GOBJ_SUB(a0)->ctrl.motion)->dirFrames));
}

inline void WithMailFunc_Idling(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    int k = s->actKind;
    int mot = GOBJ_SUB(a0)->ctrl.motion;

    SetIdleMotionRange(k, mot, mot);
}

inline void WithMailFunc_BossDamaged(GObj *a0)
{
    EnemyBattleWork *m = GOBJ_ACT(a0)->enemy;
    m->bossLife -= 1;
}

inline void WithMailFunc_FallDead(GObj *a0)
{
    float v[4];
    Sub15C *s = GOBJ_SUB(a0);
    v[0] = s->root.plane.f[0];
    v[1] = s->root.plane.f[1];
    v[2] = s->root.plane.f[2];
    sceVu0Normalize(v, v);
    if ((double)FSqrt(v[0] * v[0] + v[2] * v[2]) > 0.3) {
        v[1] = 0.0f;
        sceVu0Normalize(v, v);
        SetMotionDirection(a0, v);
    }
}

inline void actCommonReviveAir(GObj *volatile a0)
{
    SetDirectRootPositionNoFitting((void *)a0, (char *)GOBJ_ACT(a0) + 0x170);
    EnemySetfAppearAll((void *)a0);
    for (;;) {
        ACTSendMailCorrect(a0, 0xE2);
        _ACTWait(1);
    }
}

inline void actCommonOne(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    if (s->intrKind == 0x1A0) {
        if (*(int *)((char *)s + 0x138) & 1) {
            s->soundWait = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 5;
        }
    }
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonDelete(GObj *volatile a0)
{
    _ACTWait(0);
}

/* as in weapon.h, which this TU does not include (ExecWeaponHitReaction differs) */
extern void LightTorchOnOfWeapon(char *a0);

inline void actCommonCatchFire(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    int lit = 0;

    SetMotionDirection(a0, s->torchOrient);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOnOfWeapon((void *)s->weapon);
            lit = 1;
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonCatchFireBomb(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    int lit = 0;

    SetMotionDirection(a0, s->torchOrient);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOn(s->bombObj);
            lit = 1;
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonPutFire(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    int lit = 0;

    SetMotionDirection(a0, s->torchRevOrient);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOn(s->torchRevObj);
            lit = 1;
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonBoxReverbe(GObj *volatile a0)
{
    _ACTWait(40);
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonItem(GObj *volatile a0)
{
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonClimb(GObj *volatile a0)
{
    ACTAdjustPlane(a0, GOBJ_ACT(a0)->work + 0x8B0);
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    float x, y, z;
} Vec3f; /* derived name */

inline void actCommonLadderBellow(GObj *volatile a0)
{
    float hit[4];
    float p[4];
    float q[4];
    float dir[4];
    int attr[4];

    while (1) {
        GetSkeltonPosition(p, a0, 0x2C);
        sceVu0ScaleVector(dir, test_CURRENTORIENT(a0), 50.0f);
        sceVu0AddVector(q, p, dir);
        if (ACTCheckCollis_CI((int)p, (int)q, attr, (char *)hit) != 0) {
            if (CompareAttribute(attr[0], 0x3000) != 0) {
                ACTSendMailCorrect(a0, 0x91);
                *(Vec3f *)((char *)GOBJ_ACT(a0)->work + 0x3D8) = *(Vec3f *)hit;
            }
            if (CompareAttribute(attr[0], 0x400) != 0) {
                ACTSendMailCorrect(a0, 0x90);
                *(Vec3f *)((char *)GOBJ_ACT(a0)->work + 0x3CC) = *(Vec3f *)hit;
            }
        }
        ACTSendMailCorrect(a0, 0xE2);
        _ACTWait(1);
    }
}

inline void actCommonLadderBellowHang(GObj *volatile a0)
{
    for (;;) {
        if (!CheckWallAttribute((void *)a0, 0x3000) && !CheckWallAttribute((void *)a0, 0x400)) {
            ACTSendMailCorrect(a0, 0xE2);
        }
        _ACTWait(1);
    }
}

inline void actCommonEdge(GObj *volatile a0)
{
    for (;;) {
        ACTSendMailCorrect(a0, 0x150);
        if (-GOBJ_SUB(a0)->ctrl.cliffDepth > 250.0f) {
            ACTSendMailCorrect(a0, 0x18);
        }
        _ACTWait(1);
    }
}

inline void actCommonDodgeJump(GObj *volatile a0)
{
    float buf[4];
    int id = 0;
    Act *s = GOBJ_ACT(a0);

    if (a0->kind == 1) {
        ACTSearchEnemy((void *)a0, &id, buf);
    } else {
        _OrientXZGV(s->dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, s->dir);
    }
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonFallDamage(GObj *volatile a0)
{
    if ((char *)a0 == (char *)boyGObj) {
        brainAddLevelGirl(1000.0f);
    }
    for (;;) {
        if ((char *)a0 == (char *)boyGObj && (char *)girlGObj != 0) {
            brainSetSpMode();
            iosOmSendMail(girlGObj, 0x3D, a0);
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonLever2(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    char *lev = (char *)s->pullObj;

    SetDirectRootPositionXZ((void *)a0, s->pullPos);
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            /* an empty guard: the frame flag is re-read and nothing is done */
            if (GOBJ_SUB(a0)->ctrl.frameFlag2 != 0) {}
            if (GOBJ_SUB(a0)->ctrl.frameFlag1 != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}

inline void actCommonRopeTouchWall(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    while (1) {
        if (((0x3C - systemStatus[0] * 10) / systemStatus[1]) / 2 < s->modeFrame) {
            ACTSendMailCorrect(a0, 0xAA);
        }
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[24];
    int f18;
} RopeSwingWork; /* derived name */

inline void actCommonRopeSwing(GObj *volatile a0)
{
    float q[4];
    Act *s = GOBJ_ACT(a0);

    LockChainGeo(s->chain);
    ((RopeSwingWork *)s)->f18 = (int)actAfterForceRopeSwing;
    GetCorrectOrientOfChain(q, (void *)a0);
    s->ropeSwingX = q[0];
    s->ropeSwingY = q[1];
    s->ropeSwingZ = q[2];
    PlumbOrientUpdateChain(s->chain, q);
    _ACTWait(1);
    while (1) {
        switch (CollisCheckInRope((void *)a0, s->chain)) {
        case 1:
            ACTSendMailCorrect(a0, 0xA8);
            break;
        case 2:
            ACTSendMailCorrect(a0, 0xA7);
            break;
        }
        UnLockChainGeo(s->chain);
        ChainGeo(s->chain);
        LockChainGeo(s->chain);
        SetMotionDirection(a0, q);
        _ACTWait(1);
    }
}

inline void actCommonRopeTurn(GObj *volatile a0)
{
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[32];
    float _20, _24, _28;
    char pad2C[68];
    float _70;
    char pad74[12];
    int _80;
    char pad84[4];
    int _88;
    int _8c;
    char pad90[4];
    int _94;
    int _98;
    char pad9C[36];
} FloorWork; /* derived name */

static inline int isRopeDownEndOnFloor(GObj *self) /* derived name */
{
    FloorWork work;
    MotionDef *rec = &motionKind[GOBJ_SUB(self)->ctrl.motion];

    if ((rec->flags.word >> 4) & 1) {
        GetSkeltonPosition((float *)&work, self, 0x2C);
        GetSkeltonPosition((float *)((char *)&work + 0x10), self, 0x33);
        *(float *)((char *)&work + 0x14) = *(float *)((char *)&work + 0x14) - 5.0f;
        ClipFloor(&work);
        if (work._94 != 0) {
            return 1;
        }
    }
    return 0;
}

inline void actCommonRopeDownEnd(GObj *volatile a0)
{
    while (1) {
        if (isRopeDownEndOnFloor(a0)) {
            ACTSendMailCorrect(a0, 0xA9);
        }
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[304];
    int f130;
    int f134;
    int f138;
} RopeJumpWork; /* derived name */

inline void actCommonRopeJump(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    *(int *)((char *)s + 0x18) = (int)actAfterRopeJump;
    if (s->intrKind == 0xA7) {
        ((RopeJumpWork *)(int)GOBJ_SUB(a0))->f130 = 0;
        ((RopeJumpWork *)(int)GOBJ_SUB(a0))->f134 = 0;
        ((RopeJumpWork *)(int)GOBJ_SUB(a0))->f138 = 0;
    }
    for (;;) {
        ACTSendMailCorrect(a0, 0xBD);
        _ACTWait(1);
    }
}

inline void actCommonRopeJumpBefore(GObj *volatile a0)
{
    for (;;) {
        ACTSendMailCorrect(a0, 0xBD);
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[24];
    int f18;
} RopeTurnSpWork; /* derived name */

inline void actCommonRopeTurnSpecial(GObj *volatile a0)
{
    Vec4u base;
    float p0[4];
    float p1[4];
    float out[4];

    ((RopeTurnSpWork *)(char *)GOBJ_ACT(a0))->f18 = (int)afterCommonRopeTurnSpecial;
    base.f[0] = GOBJ_SUB(a0)->root.holdPoint[0];
    base.f[1] = GOBJ_SUB(a0)->root.holdPoint[1];
    base.f[2] = GOBJ_SUB(a0)->root.holdPoint[2];
    while (1) {
        GetCageChainPoint(p0, p1, GOBJ_WORK(a0)->ropeCage);
        _InterGV(out, p0, p1, base.f[1] - p0[1], p1[1] - base.f[1]);
        out[1] = base.f[1];
        SetChainRootUpdateMode(a0, 3, out);
        _ACTWait(1);
    }
}

inline void actCommonRopeClimbEnd2(GObj *volatile a0)
{
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonCornered(GObj *volatile a0)
{
    float v[4];

    sceVu0ScaleVector(v, test_CURRENTORIENT(a0), -1.0f);
    SetMotionDirection(a0, v);
    for (;;) {
        _ACTCharStatus_Set(a0, 3, -1.0f, 0);
        _ACTWait(1);
    }
}

inline void actCommonLookaround(GObj *volatile a0)
{
    for (;;) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonTurnWarn(GObj *volatile a0)
{
    float q[4];
    Act *s = GOBJ_ACT(a0);
    int prev = s->curMot;

    while (1) {
        int d;

        if (s->curMot != 0x10D) {
            prev = s->curMot;
        } else {
            *(int *)((char *)s + 0x130) =
                SetMotionRequest((void *)a0, prev, *(MotOriReq *)((char *)s + 0x620));
        }
        GetRootMotionOrient(q, a0);
        d = _RotyGV((char *)GOBJ_ACT(a0)->work + 0x3F0, q);
        if ((d < 0 ? -d : d) < 0xF) {
            ACTSendMailCorrect(a0, 0xF5);
        }
        _ACTWait(1);
    }
}

inline void actCommonTurnStrict(GObj *volatile a0)
{
    float q[4];
    float *t = GOBJ_ACT(a0)->turnDir;

    for (;;) {
        int d;

        GetRootMotionOrient(q, a0);
        d = _RotyGV(t, q);
        if ((d < 0 ? -d : d) < 0xF) {
            ACTSendMailCorrect(a0, 0xF4);
        }
        _ACTWait(1);
    }
}

inline void actCommonPPipe(GObj *volatile a0)
{
    _ACTWait(0);
}

inline void actCommonHandrail(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    GOBJ_WORK(a0)->handrailOrient[0] = s->wallOrient[0];
    GOBJ_WORK(a0)->handrailOrient[1] = s->wallOrient[1];
    GOBJ_WORK(a0)->handrailOrient[2] = s->wallOrient[2];
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonOneWall(GObj *volatile a0)
{
    GOBJ_ACT(a0)->after = (void *)afterCommonOneWall;
    _ACTWait(0);
}

inline void motCommonBoxPush(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    *(int *)((char *)s + 0x38) = 1;
    while (1) {
        if (IsThisBoxTruck(s->box) == 0) {
            SetMotionDirection(a0, GOBJ_WORK(a0)->boxDir);
        } else {
            actMotDirToWall((char *)a0);
        }
        _ACTWait(1);
    }
}

inline void motCommonBoxPull(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    s->pushDir = -1;
    while (1) {
        if (IsThisBoxTruck(s->box) == 0) {
            SetMotionDirection(a0, GOBJ_WORK(a0)->boxDir);
        } else {
            actMotDirToWall((char *)a0);
        }
        _ACTWait(1);
    }
}

inline void motCommonBarPush(GObj *volatile a0)
{
    *(int *)((int)GOBJ_ACT(a0) + 0x38) = 1;
    _ACTWait(0);
}

inline void motCommonBarPull(GObj *volatile a0)
{
    char *g = (char *)a0;
    GOBJ_ACT(g)->pushDir = 0xFFFFFFFFu;
    _ACTWait(0);
}

typedef struct { /* field names derived */
    char pad0[56];
    int f38;
} LadderMotWork; /* derived name */

inline void motCommonLadderUp(GObj *volatile a0)
{
    LadderMotWork *s = (LadderMotWork *)(char *)GOBJ_ACT(a0);

    while (1) {
        s->f38 = 1;
        switch (GOBJ_ACT(a0)->enemy->ladderUpStep) {
        case 1:
            ACTSendMailCorrect(a0, 0x89);
        case 2:
            ACTSendMailCorrect(a0, 0x8A);
            break;
        }
        _ACTWait(1);
    }
}

typedef struct { /* field names derived */
    char pad0[56];
    unsigned int f38;
} LadderDownMotWork; /* derived name */

inline void motCommonLadderDown(GObj *volatile a0)
{
    LadderDownMotWork *s = (LadderDownMotWork *)(char *)GOBJ_ACT(a0);

    while (1) {
        s->f38 = -1;
        switch (GOBJ_ACT(a0)->enemy->ladderDownStep) {
        case 1:
            ACTSendMailCorrect(a0, 0x89);
        case 2:
            ACTSendMailCorrect(a0, 0x8A);
            break;
        }
        _ACTWait(1);
    }
}

inline void motCommonSlip(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);

    while (1) {
        long long f = (long long)s->wish1.ll;

        if (!((((int)(f >> 16) & 1) && ((int)((long long)s->wish3.ll >> 16) & 1)) ||
              (((int)(f >> 17) & 1) && ((int)((long long)s->wish3.ll >> 17) & 1)))) {
            ACTSendMailCorrect(a0, 0xC7);
        }
        _ACTWait(1);
    }
}

inline void motCommonRopejumpDircorrect(GObj *volatile a0)
{
    float v[4];
    Act *s = GOBJ_ACT(a0);

    v[0] = s->ropeSwingX;
    v[1] = s->ropeSwingY;
    v[2] = s->ropeSwingZ;
    if (s->intrKind == 0xBE) {
        sceVu0ScaleVector(v, v, -1.0f);
    }
    for (;;) {
        SetMotionDirection(a0, v);
        _ACTWait(1);
    }
}

inline void motCommonRopeTurnSpecialR(GObj *volatile a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(a0)) / 3.1415927f * 180.0f);
    Act *s = GOBJ_ACT(a0);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base + deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(a0, dir);
        if (i++ % wait == 0 && !(0.1f < s->stickMag)) {
            ACTSendMailCorrect(a0, 0xAC);
        }
        deg += 5;
        _ACTWait(1);
    }
}

inline void motCommonRopeTurnSpecialL(GObj *volatile a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT(a0)) / 3.1415927f * 180.0f);
    Act *s = GOBJ_ACT(a0);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base - deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(a0, dir);
        if (i++ % wait == 0 && !(0.1f < s->stickMag)) {
            ACTSendMailCorrect(a0, 0xAC);
        }
        deg += 5;
        _ACTWait(1);
    }
}

inline void motCommonTruckLeverLoop(GObj *volatile a0)
{
    int sw = GOBJ_ACT(a0)->pullObj;

    _ACTWait(6);
    SetSwitchState(sw, 0);
    debug_StdPrintfDummy("loop");
    _ACTWait(0);
}

inline void motCommonTruckLeverPull(GObj *volatile a0)
{
    int sw = GOBJ_ACT(a0)->pullObj;
    _ACTWait(30);
    SetSwitchState(sw, -1);
    debug_StdPrintfDummy("pull");
    _ACTWait(0);
}

inline void motCommonTruckLeverPush(GObj *volatile a0)
{
    int sw = GOBJ_ACT(a0)->pullObj;
    _ACTWait(30);
    SetSwitchState(sw, 1);
    debug_StdPrintfDummy("push");
    _ACTWait(0);
}

inline void funcCommonRopeBefore(GObj *a0, int a1, int a2)
{
    GOBJ_ACT(a0)->chain = a2;
}

inline void extraCommonNull(GObj *volatile a0)
{
    for (;;) {
        _ACTWait(1);
    }
}

inline void extraCommonCall(GObj *volatile a0)
{
    if ((char *)girlGObj) {
        iosOmSendMail(girlGObj, 0x44, isysCurrentGObj);
    }
    for (;;) {
        _ACTWait(1);
    }
}

inline void funcCommonWayOn(GObj *a0)
{
    if (a0 == girlGObj) {
        girlcalled = 1;
    }
}

inline void funcCommonSofaWakeup(GObj *a0)
{
    GOBJ_ACT(a0)->enemy->sofaWake = 0;
}

inline int _ACTMotReqResult(GObj *a0, int a1)
{
    Act *s = GOBJ_ACT(a0);
    char *r = SetMotionRequest(a0, a1, *(MotOriReq *)((char *)s + 0x620));
    *(char **)((char *)s + 0x130) = r;
    return *(int *)(r + 0xC) != 0;
}

/* StartCorrectPosition and IsCorrectPosition precede test_CURRENTORIENT and
   test_CURRENTROOT, so their calls to the two accessors stay calls. */
typedef union { /* field names derived */
    unsigned long long ll;
    int i;
} CorrFlag; /* derived name */

inline void StartCorrectPosition(GObj *a0, float *pos, float *dir, int mode, float t)
{
    GOBJ_ACT(a0)->enemy->corrPosX = test_CURRENTROOT(a0)[0];
    GOBJ_ACT(a0)->enemy->corrPosY = test_CURRENTROOT(a0)[1];
    GOBJ_ACT(a0)->enemy->corrPosZ = test_CURRENTROOT(a0)[2];
    GOBJ_ACT(a0)->enemy->corrDirX = test_CURRENTORIENT(a0)[0];
    GOBJ_ACT(a0)->enemy->corrDirY = test_CURRENTORIENT(a0)[1];
    GOBJ_ACT(a0)->enemy->corrDirZ = test_CURRENTORIENT(a0)[2];
    GOBJ_ACT(a0)->enemy->corrDstX = pos[0];
    GOBJ_ACT(a0)->enemy->corrDstY = pos[1];
    GOBJ_ACT(a0)->enemy->corrDstZ = pos[2];
    if (dir != 0) {
        GOBJ_ACT(a0)->enemy->corrDstDirX = dir[0];
        GOBJ_ACT(a0)->enemy->corrDstDirY = dir[1];
        GOBJ_ACT(a0)->enemy->corrDstDirZ = dir[2];
    }
    GOBJ_ACT(a0)->enemy->corrFrames = (int)t;
    GOBJ_ACT(a0)->enemy->corrCount = 0;
    ((CorrFlag *)((char *)GOBJ_ACT(a0)->enemy + 0xB8))->i = mode;
    ((CorrFlag *)((char *)GOBJ_ACT(a0)->enemy + 0xB8))->ll |= (1ULL << 32);
}

inline int IsCorrectPosition(GObj *a0)
{
    unsigned long long v = GOBJ_ACT(a0)->enemy->corrFlags;
    return (int)v & 1;
}

/* the orient and the position these two accessors hand back */
static char commonOrient[16]; /* derived name */

static float commonPos[4]; /* derived name */

inline float *test_CURRENTORIENT(GObj *a0)
{
    if (a0 != boyGObj && a0 != girlGObj && a0->kind != 4) {
        GetRootOrient(commonOrient, a0);
        return commonOrient;
    }
    {
        float *p = (char *)GOBJ_ACT(a0) + 0xF0;
        _GetMotionDirection(p, a0);
        return p;
    }
}

inline float *test_CURRENTROOT(GObj *a0)
{
    float buf[4];
    float *p;
    float v;

    switch (a0->kind) {
    case 1:
    case 2:
    case 4:
        p = (float *)(char *)GOBJ_ACT(a0);
        p = (float *)((char *)p + 0x100);
        GetRootPosition(p, a0);
        return p;
    case 0x2C:
        if (GetCageChainPoint(commonPos, buf, a0) == 0) {
            v = 3.40282347e+38f; /* FLT_MAX */
            commonPos[0] = v;
            commonPos[1] = v;
            commonPos[2] = v;
        }
        return commonPos;
    default:
        GetRootPosition(commonPos, a0);
        return commonPos;
    }
}

inline void ControlMotionOrient(int a0, int a1)
{
    motionOrient[a0].w[2] = a1;
}

inline int FloorIsTruck(GObj *a0)
{
    char *p = *(char **)((int)GOBJ_SUB(a0));
    if (p != 0) {
        if (*(int *)(p + 0xC) == 0x11) {
            if (IsThisBoxTruck(p) == 7) {
                return 1;
            }
        }
    }
    return 0;
}

inline void _ACTMotDir_V(void *a0, void *a1)
{
    float local[4];
    sceVu0ScaleVector(local, a1, -1.0f);
    SetMotionDirection(a0, local);
}

inline void ACTMotDirToWall(GObj *a0)
{
    float local[4];
    sceVu0ScaleVector(local, GOBJ_ACT(a0)->wallOrient, -1.0f);
    SetMotionDirection(a0, local);
}

inline void SetCorrectOrientOfChain(void *a0)
{
    float local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}

inline void actAfterForceRopeSwing(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    if (s->chain == 0) {
        debug_assert("src/commonact.c", 1653);
        __assert("src/commonact.c", 1653, "ROPE_GOBJ!=NULL");
    }
    UnLockChainGeo(s->chain);
}

inline void actAfterRopeJump(GObj *volatile a0)
{
    char *g = (char *)a0;
    GOBJ_ACT(g)->flags20.ll |= (1ULL << 31);
}

inline void afterCommonRopeCliff(char *a0)
{
    char *volatile local = a0;
    char *g = *(char **)((char *)boyGObj + 0x15C);
    *(int *)(g + 0x420) = 0;
}

inline void afterCommonRopeTurnSpecial(GObj *volatile a0)
{
    char *g = (char *)a0;
    GOBJ_SUB(g)->root.ropeState = 0;
}

inline void actAfterDown(GObj *volatile a0)
{
    GOBJ_WORK(a0)->downTimer = ((0x3C - systemStatus[0] * 10) / systemStatus[1]) * 0x82 / 0x3C;
}

inline void afterCommonCling(volatile unsigned int a0)
{
    ACTGameCollisionOn(a0);
}

inline void actAfterSlip(int x)
{
    volatile int local = x;
}

inline void afterCommonRevive(volatile unsigned int a0)
{
    ACTGameCollisionOn(a0);
}

inline void afterCommonStone(GObj *volatile a0)
{
    GObj *g1 = a0;
    GObj *g2 = a0;
    GOBJ_ACT(g1)->enemy->stonePair = -1;
    GOBJ_ACT(g2)->enemy->word2A4 = 0;
}

inline void afterCommonBox(GObj *volatile a0)
{
    _boxbar_set_sound(a0, 0);
}

inline void actAfterJump(GObj *volatile a0)
{
    char *g = (char *)a0;
    GOBJ_ACT(g)->flags20.ll |= (1ULL << 31);
}

inline void actAfterFall(GObj *volatile a0)
{
    Act *s = GOBJ_ACT(a0);
    unsigned long long st = *(unsigned long long *)((int)s + 0x20) & ~(1ULL << 42);
    unsigned long long fl = *(unsigned long long *)((int)s + 0x18) & ~(1ULL << 53);
    *(unsigned long long *)((int)s + 0x18) = fl;
    *(unsigned long long *)((int)s + 0x20) = st | (1ULL << 31);
}

typedef struct { /* field names derived */
    char pad0[32];
    unsigned long long status;
} FlySub; /* derived name */

inline void actAfterFly(GObj *volatile a0)
{
    FlySub *s = (FlySub *)(int)GOBJ_ACT(a0);
    s->status |= 0x200;
    SetEnemyFootPrintSwitch(a0, 1);
    ResetFlyLimit(a0);
}

inline void ClipCollisionWithField(char *a0)
{
    int tmp[4];
    sceVu0CopyVector(tmp, a0 + 0x10);
    ClipWallField(a0);
    sceVu0CopyVector(a0 + 0x10, a0 + 0x20);
    ClipFloor(a0);
    sceVu0CopyVector(a0 + 0x10, tmp);
}

inline void afterCommonOneWall(int x)
{
    volatile int local = x;
}

inline int ACTCheckFlagAttack(GObj *a0)
{
    return GOBJ_ACT(a0)->actMode == 0xF;
}

typedef struct { /* field names derived */
    char pad0[116];
    int coll;
} BecSub; /* derived name */

inline void afterCommonBecarry(GObj *volatile a0)
{
    SetKidnapInfo(-1, -1);
    ((BecSub *)(int)GOBJ_SUB(a0))->coll = 1;
    ACTGameCollisionOn(a0);
    gflagOff(393);
}

inline void afterCommonTruckLever(GObj *volatile a0)
{
    char *g = (char *)a0;
    SetSwitchState(GOBJ_ACT(g)->pullObj, 0);
}
