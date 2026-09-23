#include "common.h"

/* prototypes: their order is the inline tail's emission order (gcc emits every
   inline at the end of the object in first-declaration order). They precede
   commonact.h, whose alphabetical list would otherwise fix that order. */
void ACTAcceptMail(char *a0, int a1);
int _ACTMotDirSmzDirect(char *a0, float *a1);
void WithMailFunc_Idling(char *a0);
void WithMailFunc_BossDamaged(char *a0);
void WithMailFunc_FallDead(char *a0);
void actCommonRevive(volatile int a0);
void actCommonReviveAir(volatile int a0);
void actCommonPlay(volatile int a0);
void actCommonOne(volatile int a0);
void actCommonDelete(volatile int a0);
void actCommonCatchFire(volatile int a0);
void actCommonCatchFireBomb(volatile int a0);
void actCommonPutFire(volatile int a0);
void actCommonBoxReverbe(volatile int a0);
void actCommonItem(volatile int a0);
void actCommonClimb(volatile int a0);
void actCommonCliffdown(volatile int a0);
void actCommonLadderBellow(volatile int a0);
void actCommonLadderBellowHang(volatile int a0);
void actCommonEdge(volatile int a0);
void actCommonDodge(volatile int a0);
void actCommonDodgeJump(volatile int a0);
void actCommonGuard(volatile int a0);
void actCommonFallDamage(volatile int a0);
void actCommonDamage(volatile int a0);
void actCommonShoal(volatile int a0);
void actCommonSwim(volatile int a0);
void actCommonLever2(volatile int a0);
void actCommonRopeTouchWall(volatile int a0);
void actCommonRopeSwing(volatile int a0);
void actCommonRopeTurn(volatile int a0);
void actCommonRopeDownEnd(volatile int a0);
void actCommonRopeJump(volatile int a0);
void actCommonRopeJumpBefore(volatile int a0);
void actCommonRopeTurnSpecial(volatile int a0);
void actCommonRopeClimbEnd2(volatile int a0);
void actCommonCornered(volatile int a0);
void actCommonLookaround(volatile int a0);
void actCommonTurnWarn(volatile int a0);
void actCommonTurnStrict(volatile int a0);
void actCommonPPipe(volatile int a0);
void actCommonHandrail(volatile int a0);
void actCommonOneWall(volatile int a0);
void motCommonNull(volatile int a0);
void motCommonBoxPush(volatile int a0);
void motCommonBoxPull(volatile int a0);
void motCommonBarPush(volatile int a0);
void motCommonBarPull(volatile int a0);
void motCommonLadderUp(volatile int a0);
void motCommonLadderDown(volatile int a0);
void motCommonSlip(volatile int a0);
void motCommonRopejumpDircorrect(volatile int a0);
void motCommonHangNone(volatile int a0);
void motCommonHangWall(volatile int a0);
void motCommonHangCliff(volatile int a0);
void motCommonRopeTurnSpecialR(volatile int a0);
void motCommonRopeTurnSpecialL(volatile int a0);
void motCommonTruckLeverLoop(volatile int a0);
void motCommonTruckLeverPull(volatile int a0);
void motCommonTruckLeverPush(volatile int a0);
void funcCommonRopeBefore(char *a0, int a1, int a2);
void afterCommonRope(volatile int a0);
void extraCommonNull(volatile int a0);
void extraCommonCall(volatile int a0);
void funcCommonWayOn(void *a0);
void funcCommonSofaWakeup(char *a0);
int _ACTMotReqResult(char *a0, int a1);
void *test_CURRENTORIENT(char *a0);
void *test_CURRENTROOT(void *a0);
void StartCorrectPosition(char *a0, float *pos, float *dir, int mode, float t);
int IsCorrectPosition(char *a0);
void ControlMotionOrient(int a0, int a1);
int FloorIsTruck(void *a0);
void _ACTMotDir_V(void *a0, void *a1);
void ACTMotDirToWall(char *a0);
void SetCorrectOrientOfChain(void *a0);
void actAfterForceRope(volatile int a0);
void actAfterForceRopeSwing(volatile int a0);
void actAfterRopeJump(volatile int a0);
void afterCommonRopeCliff(char *a0);
void afterCommonRopeTurnSpecial(volatile int a0);
void actAfterDown(volatile int a0);
void afterCommonCling(volatile unsigned int a0);
void actAfterSlip(int x);
void afterCommonRevive(volatile unsigned int a0);
void afterCommonStone(volatile int a0);
void afterCommonBox(volatile int a0);
void afterCommonBar(volatile int a0);
void actAfterJump(volatile int a0);
void actAfterFall(volatile int a0);
void actAfterFly(volatile int a0);
void ClipCollisionWithField(char *a0);
void afterCommonOneWall(int x);
int ACTCheckFlagAttack(char *a0);
void afterCommonBecarry(volatile int a0);
void afterCommonTruckLever(volatile int a0);

#include "commonact.h"
#include "debug.h"
#include "gobj.h"
#include "obj_manager.h"
#include "act-env.h"
#include "act.h"
#include "boyact.h"
#include "brain.h"
#include "mail-add-data.h"
#include "gflag.h"
#include "Matrix.h"
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

typedef struct {
    int a, b, c;
} Blob12;

typedef struct {
    int w[6];
} SlowrunRec;

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

extern char *D_00639EA4;
extern char *D_00639EA8;
/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(void *a, void *b);

int ChangeMailInLadder(char *a0, int a1)
{
    float p[4];
    float q[4];
    Act *s = GOBJ_ACT(a0);
    int ret = a1;
    int flag = 0;
    float lim1;
    float lim2;

    if (D_00639EA4 != 0 && D_00639EA8 != 0) {
        if (a0 == D_00639EA4) {
            if (s->unk34 == 0x26) {
                flag = (GOBJ_ACT(D_00639EA8)->unk34 == 0x26);
            }
        }
        if (a0 == D_00639EA8) {
            if (s->unk34 == 0x26) {
                flag = 1;
            }
        }
        if (flag != 0 &&
            _DistxzSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) < 3600.0f) {
            lim1 = a0 == D_00639EA4 ? 175.0f : 225.0f;
            lim2 = a0 == D_00639EA4 ? 175.0f : 210.0f;
            if (a0 == D_00639EA4) {
                p[0] = ((float *)test_CURRENTROOT(a0))[0];
                p[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
                p[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
                q[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                q[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                q[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
            } else {
                p[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                p[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                p[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
                q[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
                q[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
                q[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            }
            switch (a1) {
            case 0x14A:
                if (q[1] < p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < lim2) {
                    *(unsigned long long *)((char *)s + 0x18) |= (1ULL << 36);
                    ret = 0x150;
                }
                break;
            case 0x14B:
                if (q[1] > p[1] && (q[1] - p[1] < 0.0f ? -(q[1] - p[1]) : q[1] - p[1]) < lim1) {
                    *(unsigned long long *)((char *)s + 0x18) |= (1ULL << 37);
                    ret = 0x150;
                }
                break;
            }
        }
    }
    return ret;
}

extern int _RotyGV(void *a0, void *a1);
extern int _AbsRotyGV(void *a0, void *a1);
void DamageFunc(char *a0);

typedef struct {
    char _0[0x188];
    unsigned int f188;
    unsigned int f18C;
    char _190[4];
} CorrMotRec;

/* The TU's .rodata run is VMA 0x00552CB8..0x00553320. The object emits the
 * part from actCommonFall's 0.8 at 0x00552EE8 to WithMailFunc_FallDead's 0.3
 * at 0x00553318, strings as literals; the head 0x00552CB8..0x00552EE8 stays in
 * the blob behind these labels, since its owners include inline tail members
 * (funcCommonRopeBefore, SetCorrectOrientOfChain, actCommonPlay,
 * actCommonDamage, actCommonRevive) still defined at their text positions, and
 * a literal emits where its function is defined. Spell these as literals once
 * those members sit at their listing positions:
 *   D_00552CB8 critical hit to boss!!!
 *   D_00552CD0 !!! unable guard flag get\n
 *   D_00552CF0 guard mail\n
 *   D_00552D00 guard error=[%d][%d][%d][%d]\n
 *   D_00552D20 die!!!!!!!!!!!\n
 *   D_00552D30 down!!!!!!!!!!!\n
 *   D_00552D48 damage!!!!!!!!!!!  %d\n */
extern char D_00552CB8[];
extern char D_00552CD0[];
extern char D_00552CF0[];
extern char D_00552D00[];
extern char D_00552D20[];
extern char D_00552D30[];
extern char D_00552D48[];
extern int stage_no;
extern int D_00639EAC;
extern int D_00639EB4;
extern int D_0063B210;
extern int IsAbleChainHang(char *a0);
extern void BoySekikaTexScroll(void);
extern int EnemyGetNSafeParts(char *a0);
extern char D_0055FE58[];

/* lines 625-631: a static inline used only by _ACTCorrectMsg */
static inline int GetHitDirIdx(char *self)
{
    char *p = *(char **)(self + 0x164) + 0x1C0;
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

int _ACTCorrectMsg(char *self, int msg, void *param)
{
    float pos[4];
    char *sk = (char *)*(int *)(self + 0x164);
    int fast = _ACTGame_GetParamF(2) < *(float *)(*(char **)(self + 0x15C) + 0x560);

    switch (msg) {
    case 309:
        if (!(((int)(*(unsigned long long *)(sk + 0x18) >> 53) & 1) &&
              *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x338) <
                  *(float *)(*(char **)(self + 0x15C) + 0x560))) {
            msg = 418;
        }
        break;
    case 42:
        if (!(((int)(*(unsigned long long *)(sk + 0x18) >> 53) & 1) &&
              *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x338) <
                  *(float *)(*(char **)(self + 0x15C) + 0x560))) {
            msg = 418;
        }
        break;
    case 259:
        if ((((CorrMotRec *)(D_0055FE58 + *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
                 ->f18C >>
             9) &
            1) {
            msg = 418;
        }
        break;
    case 298:
        if (*(int *)(sk + 0x34) == 5 &&
            *(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x900) == 26) {
            msg = 418;
        }
        break;
    case 297:
        if (*(int *)(sk + 0x34) == 1 &&
            *(long long *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x900) ==
                0x1A00000005LL) {
            msg = 418;
        }
        break;
    case 330:
    case 331:
        msg = ChangeMailInLadder(self, msg);
        break;
    case 240:
        if ((((CorrMotRec *)(D_0055FE58 + *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
                 ->f18C >>
             5) &
            1) {
            msg = 418;
        } else if ((int)(*(unsigned long long *)(sk + 0x20) >> 14) & 1) {
            msg = 239;
        }
        break;
    case 241:
        if ((((CorrMotRec *)(D_0055FE58 + *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
                 ->f18C >>
             5) &
            1) {
            msg = 418;
        }
        break;
    case 231:
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x384) != 0) {
            msg = 418;
        } else if ((int)(*(unsigned long long *)(sk + 0x20) >> 14) & 1) {
            msg = 233;
        }
        break;
    case 232:
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x388) != 0) {
            msg = 418;
        } else if ((int)(*(unsigned long long *)(sk + 0x20) >> 14) & 1) {
            msg = 234;
        }
        break;
    case 348:
    case 349:
    case 350:
        if (D_00639EB4 != 0) {
            msg = 418;
        }
        break;
    case 205:
        if (*(int *)(sk + 0x50) != 0) {
            msg = 418;
        }
        break;
    case 174:
        if (fast) {
            msg = 418;
        }
        if (((int)(*(unsigned long long *)(sk + 0x18) >> 53) & 1) &&
            *(float *)(*(char **)(self + 0x15C) + 0x560) <
                *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x338)) {
            msg = 418;
        }
        break;
    case 26:
        if (*(float *)(*(char **)(self + 0x15C) + 0x644) < (self == D_00639EA4 ? 110.0f : 135.0f)) {
            msg = 418;
        }
        /* fallthrough */
    case 218:
        if (*(int *)(self + 0xC) == 4) {
            msg = 223;
            if ((int)(*(unsigned long long *)(sk + 0x20) >> 30) & 1) {
                msg = 418;
            }
        }
        break;
    case 219:
        if (*(int *)(self + 0xC) == 4) {
            msg = 223;
            if ((int)(*(unsigned long long *)(sk + 0x20) >> 30) & 1) {
                msg = 418;
                if (13 <= *(int *)(sk + 0x10)) {
                    msg = 30;
                    iosOmSendMail(self, 29, (int)param);
                }
            }
        }
        break;
    case 21:
        if (*(int *)(sk + 0x34) == 62 && param == *(char **)(sk + 0x194)) {
            msg = 418;
        }
        if (fast) {
            msg = 418;
        }
        if (IsAbleChainHang(param) == 0) {
            msg = 418;
        }
        if (((int)(*(unsigned long long *)(sk + 0x18) >> 53) & 1) &&
            *(float *)(*(char **)(self + 0x15C) + 0x560) <
                *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x338)) {
            msg = 418;
        }
        break;
    case 20:
        if (IsAbleChainHang(param) == 0) {
            msg = 418;
        }
        if (((int)(*(unsigned long long *)(sk + 0x18) >> 53) & 1) &&
            *(float *)(*(char **)(self + 0x15C) + 0x560) <
                *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x338)) {
            msg = 418;
        }
        break;
    case 7:
        if ((((CorrMotRec *)(D_0055FE58 + *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
                 ->f188 >>
             19) &
            7) {
            if (*(int *)(sk + 0x180) != 0) {
                msg = 315;
            }
        }
        break;
    case 10: {
        int iv = (int)*(float *)(*(char **)(self + 0x15C) + 0x55C);
        int flagA = 0;
        int flagB = 0;

        if (120.0f < *(float *)(*(char **)(self + 0x15C) + 0x55C)) {
            ACTWay_SetBeginPositionIllegal(self);
        }
        if (!((((CorrMotRec *)(D_0055FE58 + *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
                   ->f18C >>
               25) &
              1)) {
            msg = 418;
            break;
        }
        if (iv < 130) {
            iosOmSendMail(self, 59, (int)param);
        }
        if (self == D_00639EA8 && ACTGame_FLAG_TETSUNAGI()) {
            iosOmSendMail(self, 58, (int)param);
            if (iv < 130) {
                iosOmSendMail(self, 57, (int)param);
            }
        }
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x900) == 38) {
            iosOmSendMail(self, 60, (int)self);
        }
        if (_ACTGame_GetParamF(2) < (float)iv) {
            flagA = 1;
        } else if (_ACTGame_GetParamF(1) < (float)iv) {
            flagB = 1;
        }
        switch (*(int *)(sk + 0x34)) {
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
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x900) == 21) {
            iosOmSendMail(self, 56, (int)param);
            if (msg == 43) {
                iosOmSendMail(self, 55, (int)param);
            }
        }
        break;
    }
    case 14:
        debug_StdPrintfDummy(D_00552CB8);
        if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x20C) <= 1) {
            msg = 293;
        } else {
            msg = 285;
        }
        break;
    case 13: {
        float d = *(float *)(sk + 0x1E0) - (float)*(int *)(*(int *)(self + 0x164) + 0x1D0);

        if (self == D_00639EA4 || self == D_00639EA8) {
            d = *(float *)(sk + 0x1E0) = 100.0f;
        }
        if (*(signed char *)(*(int *)(self + 0x164) + 0x1DB) != 0) {
            debug_StdPrintfDummy(D_00552CD0);
        }
        if (stage_no == 85 || D_0063B210 != 0) {
            if (*(signed char *)(*(int *)(self + 0x164) + 0x1D9) != 0) {
                if (ACTGame_NoWeapon(self) != 0 && *(int *)(sk + 0x34) != 14) {
                    msg = 110;
                    *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0xCC) = 10;
                    BoySekikaTexScroll();
                    *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x2A8) += 1;
                    break;
                } else {
                    msg = 282;
                    *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x2AC) += 1;
                    *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0xCC) = 10;
                    break;
                }
            }
        }
        if (_AbsRotyGV(test_CURRENTORIENT(self), (void *)(*(int *)(self + 0x164) + 0x1C0)) < 60 &&
            *(int *)(sk + 0x34) != 15 && *(int *)(sk + 0x34) != 20 &&
            *(signed char *)(*(int *)(self + 0x164) + 0x1DB) == 0 &&
            !((int)(*(unsigned long long *)(sk + 0x18) >> 51) & 1)) {
            iosOmSendMail(self, 283, (int)param);
            debug_StdPrintfDummy(D_00552CF0);
        } else {
            debug_StdPrintfDummy(
                D_00552D00,
                _AbsRotyGV(test_CURRENTORIENT(self), (void *)(*(int *)(self + 0x164) + 0x1C0)),
                *(int *)(sk + 0x34), 15, 20);
        }
        if (*(signed char *)(*(int *)(self + 0x164) + 0x1D9) != 0) {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x29C) += 1;
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0xCC) = 10;
        }
        if (*(int *)(self + 0xC) == 4 &&
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x1E4) == 3) {
            if (*(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x228) <= 0) {
                DamageFunc(self);
                iosPadActRequest(D_00639EAC, 2);
                pos[0] = ((float *)test_CURRENTROOT(self))[0];
                pos[1] = ((float *)test_CURRENTROOT(self))[1];
                pos[2] = ((float *)test_CURRENTROOT(self))[2];
                soundSeDefPlay(382, 0, pos, 1);
            }
            msg = 418;
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x228) = 60;
            break;
        }
        if (self == D_00639EA4 && *(int *)(param + 0xC) == 17) {
            msg = 418;
            break;
        }
        if (*(int *)(self + 0xC) == 4 && *(int *)(sk + 0x34) == 16 &&
            *(char **)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x220) == D_00639EA8) {
            msg = 215;
            break;
        }
        if (*(int *)(self + 0xC) == 4 &&
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x680) + 0x1E4) != 3 &&
            EnemyGetNSafeParts(self) < 8) {
            msg = 293;
            debug_StdPrintfDummy(D_00552D20);
            break;
        }
        if (d < 0.0f) {
            msg = 293;
            if (self == D_00639EA4) {
                msg = 291;
                *(float *)(sk + 0x1E0) = 100.0f;
            }
            debug_StdPrintfDummy(D_00552D20);
            break;
        }
        if (*(signed char *)(*(int *)(self + 0x164) + 0x1D8) != 0 ||
            _ACTCharStatus_Check(self, 16) != 0) {
            msg = 291;
            debug_StdPrintfDummy(D_00552D30);
            break;
        }
        {
            int dir = GetHitDirIdx(self);

            msg = dir + 287;
            debug_StdPrintfDummy(D_00552D48, dir);
        }
        break;
    }
    }
    return msg;
}

typedef struct {
    float x, y, z;
} IntrVec3;

typedef struct {
    IntrVec3 a;
    float aw;
    IntrVec3 b;
    float bw;
} IntrOrient;

/* the motion each interrupt kind requests, indexed by the kind; MAIN.MAP
   names no symbol in commonact.o's .data, so this name is ours */
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
    0,   0,   0,   0,   0,   0,   0,   0,   17,  18,  262, 0,   0,   0};

extern int ACTGame_GetMotOrientFromWeapon(int a0);

int ACTGetOrientFromIntrK(char *self, int k, void *buf, int arg)
{
    IntrOrient *out = (IntrOrient *)buf;
    char *s = *(char **)(self + 0x164);
    IntrVec3 tmp;
    int ret = intrMotion[k];

    *out = *(IntrOrient *)(s + 0x620);
    switch (k) {
    case 140:
        out->b = ((IntrOrient *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x480))->b;
        break;
    case 305:
        out->a = ((IntrOrient *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x480))->a;
        break;
    case 298:
        *(char **)(s + 0x30) = GetMailAdditionalData(self, arg);
        tmp = *(IntrVec3 *)(*(char **)(*(char **)(self + 0x164) + 0x30));
        out->b = ((IntrOrient *)(s + 0x620))->b = tmp;
        break;
    case 54:
        *(char **)(s + 0x30) = GetMailAdditionalData(self, arg);
        tmp = *(IntrVec3 *)(*(char **)(*(char **)(self + 0x164) + 0x30));
        out->a = out->b = ((IntrOrient *)(s + 0x620))->a = ((IntrOrient *)(s + 0x620))->b = tmp;
        *(int *)(s + 0x61C) = *(int *)&tmp;
        GetSofaPosition(self, *(char **)(s + 0x61C));
        break;
    case 145:
        out->a = *(IntrVec3 *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x3D8);
        break;
    case 144:
        out->a = *(IntrVec3 *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x3CC);
        break;
    case 114:
    case 115:
    case 116:
    case 117:
        out->b = ((IntrOrient *)(s + 0x620))->a;
        break;
    case 45:
        return *(int *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0xC0);
    case 63:
        if (*(int *)(s + 0x34) == 0x4A) {
            ret = 272;
        }
        break;
    case 378:
    case 379:
    case 380:
        out->b = out->a = ((IntrOrient *)(s + 0x640))->b;
        break;
    case 381:
        *out = *(IntrOrient *)(s + 0x640) = *(IntrOrient *)(*(char **)(D_00639EA4 + 0x164) + 0x640);
        break;
    case 382:
    case 383:
    case 384:
        *out = *(IntrOrient *)(s + 0x640);
        break;
    case 385:
    case 386:
        *out = *(IntrOrient *)(s + 0x660);
        *(IntrOrient *)(s + 0x620) = *out;
        break;
    case 205:
    case 206:
    case 207:
        if (self == D_00639EA4) {
            if (ACTGame_NoWeapon(self)) {
                ret = 42;
            } else {
                ret = ACTGame_GetMotOrientFromWeapon(*(int *)(s + 0x150));
            }
        }
        break;
    case 72:
    case 74:
    case 338:
        ret = *(int *)(s + 0x44);
        break;
    case 81:
        ret = *(int *)(s + 0x44);
        out->a = ((IntrOrient *)(*(char **)(D_00639EA4 + 0x164) + 0x620))->b;
        *(IntrOrient *)(s + 0x620) = *out;
        break;
    case 89:
    case 399:
    case 403:
        out->a = ((IntrOrient *)(*(char **)(D_00639EA4 + 0x164) + 0x620))->b;
        *(IntrOrient *)(s + 0x620) = *out;
        break;
    case 416:
        ret = 0;
        if (*(int *)(s + 0x134) != 0 && !((int)(*(unsigned long long *)(s + 0x20) >> 13) & 1)) {
            ret = *(int *)(s + 0x134);
            *(int *)(s + 0x134) = 0;
        }
        break;
    case 152:
    case 155:
    case 156:
        out->a = *(IntrVec3 *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x350);
        break;
    default:
        ret = intrMotion[k];
        break;
    }
    return ret;
}

extern char D_0055FE58[];
extern char D_0063A710[];
extern int D_0028F4C0[];

/* The actor mail record ico2/fumi/src/act.c reconstructs as IntrMail: a
 * 0x18-byte entry with the id at 0x10 and the flag word at 0x14. */
typedef struct IntrRec {
    void *f0;
    void *f4;
    void (*handler)(char *self, int id, void *arg);
    void (*f0C)(char *self, int id, void *arg);
    unsigned short kind;
    short f12;
    unsigned int f14;
} IntrRec;

extern IntrRec D_002A7E08[];

void ACTRunIntrCorrect(char *a0, IntrRec *a1, IntrRec *a2)
{
    char *rec;
    char *s = *(char **)(a0 + 0x164);
    inline void setIntrFlags(void)
    {
        IntrRec *p;

        for (p = a1; p != 0 && (short)p->kind != 429; p++) {
            p->f14 |= 0x40000;
        }
    }
    inline void correctIntrList(void)
    {
        IntrRec *ip;
        IntrRec *q;

        for (q = a2; q != 0 && (short)q->kind != 429; q++) {
            if (q->f12 == -1) {
                for (ip = a1; ip != 0 && (short)ip->kind != 429; ip++) {
                    if (ip->kind == q->kind) {
                        ip->f14 &= ~0x40000;
                        debug_StdPrintfDummy(D_0063A710);
                    }
                }
            }
        }
    }

    setIntrFlags();
    correctIntrList();
    rec = D_0055FE58 + *(int *)(*(char **)(a0 + 0x15C) + 0x4A0) * 404;
    if (rec[399] & 1) {
        D_002A7E08[10].f14 |= 0x40000;
    } else {
        D_002A7E08[10].f14 &= ~0x40000;
    }
    if (*(int *)(s + 0x34) == 26) {
        if (*(int *)(s + 0x4C) < ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 3) {
            D_002A7E08[371].f14 |= 0x40000;
        } else {
            D_002A7E08[371].f14 &= ~0x40000;
        }
    }
}

void WithMailFunc_WayBeginPosError(void *a0)
{
    ACTWay_SetBeginPositionIllegal(a0);
}

/* kept local: this TU's uses of ExecWeaponHitReaction do not fit the prototype in weapon.h */
extern void ExecWeaponHitReaction(void *a0);

void WithMailFunc_AttackFail(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    char *p = *(char **)((char *)s + 0x30);
    int v = p != 0 ? *(int *)p : *(int *)((char *)s + 0x5E0);
    if (a0 == D_00639EA4) {
        char *t = *(char **)((char *)s + 0x150);
        if (t != 0) {
            GOBJ_SUB(t)->f_5F4 = v;
            ExecWeaponHitReaction(t);
        }
    }
}

extern int stage_no;
extern int D_0063B210;
/* kept local: this TU does not include weapon.h; the ROM proves the int return (the callee sets $2 to 1 or 0 on its two exits). */
extern int ReleaseWeaponWithFumbleSequential(void *a0);

void WithMailFunc_AttackRejectInQueen(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    void *w = *(void **)((char *)s + 0x150);
    if (w != 0) {
        ReleaseWeaponWithFumbleSequential(w);
        s->f_150 = 0;
    }
    if (stage_no == 0x55 || D_0063B210 != 0) {
        void *e = isysGObjSearchFromObjKindID_begin(54);
        if (e != 0) {
            iosOmSendMail(e, 0xD, (int)a0);
        }
    }
}

/* kept local: this TU's uses of GetChainDirCorrectVal do not fit the prototype in chain.h */
extern int GetChainDirCorrectVal(int chain, int *out);
extern void *memset(void *dst, int c, int n);
/* kept local: this TU's uses of _GetDirection do not fit the prototype in gv.h */
extern float _GetDirection(void *p);
/* kept local: this TU's uses of RoundDegGV do not fit the prototype in gv.h */
extern int RoundDegGV(int deg);
/* kept local: this TU's uses of AlignDegGV do not fit the prototype in gv.h */
extern int AlignDegGV(int deg);
/* kept local: this TU's uses of _ApplyRyGV do not fit the prototype in gv.h */
extern void _ApplyRyGV(void *a0, float a1);

void GetCorrectOrientOfChain(void *buf, void *obj)
{
    float q[4];
    int deg;

    if (GetChainDirCorrectVal(GOBJ_ACT(obj)->f_190, &deg) != 0) {
        memset(q, 0, 16);
        q[2] = 1.0f;
        _ApplyRyGV(
            q, (float)RoundDegGV(deg + AlignDegGV(RoundDegGV(
                                           (int)(_GetDirection(test_CURRENTORIENT((char *)obj)) /
                                                 3.1415927f * 180.0f) -
                                           deg))) *
                   3.1415927f / 180.0f);
        ((float *)buf)[0] = q[0];
        ((float *)buf)[1] = q[1];
        ((float *)buf)[2] = q[2];
    } else {
        ((float *)buf)[0] = *(float *)((char *)test_CURRENTORIENT((char *)obj) + 0);
        ((float *)buf)[1] = *(float *)((char *)test_CURRENTORIENT((char *)obj) + 4);
        ((float *)buf)[2] = *(float *)((char *)test_CURRENTORIENT((char *)obj) + 8);
    }
}

/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *a0);
/* kept local: this TU's uses of SwapGV do not fit the prototype in gv.h */
extern void SwapGV(void *a0, void *a1);

/* reconstruction: the ClipWall work buffer as this function reads it. RsWork
   below is the other view of the same 0xC0-byte record and disagrees at 0x80
   (two floats there, the hit object at 0x88) where this one reads the hit
   object at 0x80 and the hit flag at 0x88; what ClipWall writes has not been
   established, so the two views are kept apart rather than merged. */
typedef struct {
    char _00[0x70];
    float f70;
    char _74[0x0C];
    int f80;
    char _84[0x04];
    int f88;
    char _8C[0x34];
} RopeWallWork;

int CollisCheckInRope(void *a0, int chain)
{
    /* reconstruction: the name is ours. The narrow return type is what the ROM
       proves: with an int the two inlined copies both cross-jump and the flag
       store-flags to xori/sltu. */
    inline char ropeWallIsBox(char *p)
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

    sceVu0ScaleVector(dir, test_CURRENTORIENT((char *)a0), 15.0f);
    GetSkeltonPosition(n51, (char *)a0, 51);
    GetSkeltonPosition(n47, (char *)a0, 47);
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

/* kept local: this TU's uses of GetRootPositionHandExtra do not fit the prototype in chain.h */
extern void GetRootPositionHandExtra(void *a0, void *out);
/* kept local: this TU's uses of HoldChain do not fit the prototype in chain.h */
extern void HoldChain(int chain, void *a0, void *pos);
/* kept local: this TU's uses of LockChainGeo do not fit the prototype in chain.h */
extern void LockChainGeo(int a0);
/* kept local: this TU's uses of UnLockChainGeo do not fit the prototype in chain.h */
extern void UnLockChainGeo(int a0);
/* kept local: this TU's uses of ChainGeo do not fit the prototype in chain.h */
extern void ChainGeo(int a0);
/* kept local: this TU's uses of CheckChainClimbablePos do not fit the prototype in chain.h */
extern int CheckChainClimbablePos(int chain);
/* kept local: this TU's uses of GetChainClimbOrient do not fit the prototype in chain.h */
extern void GetChainClimbOrient(void *out, int chain);
/* kept local: this TU's uses of GetChainClimbCollision do not fit the prototype in chain.h */
extern void GetChainClimbCollision(void *out, int chain);
/* kept local: this TU's uses of ClipFloor do not fit the prototype in fieldCollision.h */
extern void ClipFloor(void *a0);
extern char D_00552DB0[];
extern char D_0055FE58[];
extern int D_0028F4C0[];
/* kept local: this TU's uses of _RotyGV do not fit the prototype in gv.h */
extern int _RotyGV(void *a0, void *a1);
/* kept local: this TU's uses of SetMotionDirection do not fit the prototype in motionManager2.h */
extern void SetMotionDirection();

typedef struct {
    char _0[0x35C];
    int f35C;
} RopeSubObj;

typedef struct {
    char _00[0x94];
    int f94;
    char _98[0x28];
} RopeFloorWork;

typedef struct {
    char _0[0x18C];
    unsigned int f18C;
    char _190[4];
} RopeMotRec;

static inline int chainFloorHit(char *a0, void *w)
{
    if ((((RopeMotRec *)D_0055FE58)[GOBJ_SUB(a0)->f_4A0].f18C >> 4) & 1) {
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

void actCommonRope(volatile int a0)
{
    char *s;
    float dir[4];
    float ori[4];
    float hand[4];
    RopeFloorWork work;
    int step;
    int nsteps;
    int total;
    int roty;

    nsteps = ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 3;
    total = nsteps;
    step = -1;
    s = *(char **)(a0 + 0x164);
    GetCorrectOrientOfChain(dir, (void *)a0);
    ori[0] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 0);
    ori[1] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 4);
    ori[2] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 8);
    roty = _RotyGV(dir, ori);
    if (*(int *)(s + 0x14) == 0) {
        GetRootPositionHandExtra((void *)a0, hand);
        step = 0;
        HoldChain(*(int *)(s + 0x190), (void *)a0, hand);
    }
    *(int *)(s + 0x14) = (int)afterCommonRope;
    *(int *)(s + 0x18) = (int)actAfterForceRope;
    LockChainGeo(*(int *)(s + 0x190));
    _ACTWait(1);
    debug_StdPrintfDummy(D_00552DB0);
    while (1) {
        UnLockChainGeo(*(int *)(s + 0x190));
        ChainGeo(*(int *)(s + 0x190));
        LockChainGeo(*(int *)(s + 0x190));
        switch (CollisCheckInRope((void *)a0, *(int *)(s + 0x190))) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0xA8);
            break;
        case 2:
            ACTSendMailCorrect((char *)a0, 0xA7);
            break;
        }
        if (chainFloorHit((char *)a0, &work)) {
            ACTSendMailCorrect((char *)a0, 0xA9);
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
        if (CheckChainClimbablePos(*(int *)(s + 0x190))) {
            GetChainClimbOrient(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x330,
                                *(int *)(s + 0x190));
            GetRootPosition((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x340),
                            (void *)*(int *)(s + 0x190));
            GetChainClimbCollision(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x350,
                                   *(int *)(s + 0x190));
            ((RopeSubObj *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f35C = *(int *)(s + 0x190);
            ActSendMail_WithAdditionalData((char *)a0, 0x98, (void *)a0,
                                           *(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x330);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of debug_Arrow do not fit the prototype in camera-editor.h */
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines SetCorrectOrientOfChain (line 1410) here, so it is `inline`
   in the dev's TU; while this tail still has asm members a deferred inline
   would land at the object end instead of at its ROM slot, so the public body
   later in this file stays a plain definition and this caller uses the static
   stand-in.  Collapses to one `inline` definition at layout. */
static inline void setCorrectOrientOfChain_inl(void *a0)
{
    int local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}

void motCommonRopeTurnR(volatile int a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT((char *)a0)) / 3.1415927f * 180.0f);
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
            ACTSendMailCorrect((char *)a0, 0x150);
        }
        _ACTWait(1);
    }
}

void motCommonRopeTurnL(volatile int a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT((char *)a0)) / 3.1415927f * 180.0f);
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
            ACTSendMailCorrect((char *)a0, 0x150);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of _AbsRotyGV do not fit the prototype in gv.h */
extern int _AbsRotyGV(void *a0, void *a1);
/* kept local: this TU's uses of SetChainRootUpdateMode do not fit the prototype in chain.h */
extern void SetChainRootUpdateMode(void *a0, int mode, float *p);

typedef struct {
    float x, y, z;
} ClimbVec3;

typedef union {
    float f[4];
    long long ll[2];
} ClimbVec4;

typedef struct {
    float v0[4] __attribute__((aligned(16)));
    float v1[4];
    ClimbVec3 v2;
    int obj;
} ClimbEndRec;

void actCommonRopeClimbEnd1(volatile int a0)
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

    c = *(ClimbEndRec *)*(char **)(*(char **)(a0 + 0x164) + 0x30);
    isCage = *(int *)(c.obj + 0xC) == 0x2C;
    flag = 0;
    GOBJ_SUB(D_00639EA4)->f_420 = 0;
    dir.f[0] = c.v0[0];
    dir.f[1] = c.v0[1];
    dir.f[2] = c.v0[2];
    sceVu0ScaleVector(&dir, &dir, -1.0f);
    if (_AbsRotyGV(&dir, test_CURRENTORIENT((char *)a0)) < 10) {
        flag = 1;
    } else {
        back = -5;
        while (1) {
            if (isCage) {
                TestCageUpDown(c.obj, (void *)a0);
            }
            if (GOBJ_SUB(a0)->f_4A0 == 118) {
                break;
            }
            _ACTWait(1);
        }
        i = 0;
        r = _RotyGV(&dir, test_CURRENTORIENT((char *)a0));
        step = (r > -1) ? step : back;
        n = r / step;
        n = (n < 0) ? -n : n;
        GetSkeltonPosition(pos, (char *)a0, 22);
        pos[0] = c.v1[0];
        pos[2] = c.v1[2];
        while (i < n) {
            i++;
            ori[0] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 0);
            ori[1] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 4);
            ori[2] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 8);
            _ApplyRyGV(ori, (float)step * 3.1415927f / 180.0f);
            SetMotionDirection(a0, ori);
            if (0 < step) {
                ACTSendMailCorrect((char *)a0, 0xA0);
            } else {
                ACTSendMailCorrect((char *)a0, 0xA1);
            }
            SetChainRootUpdateMode((void *)a0, 3, pos);
            _ACTWait(1);
        }
        if (GOBJ_SUB(a0)->f_4A0 != 118) {
            do {
                ACTSendMailCorrect((char *)a0, 0x150);
                _ACTWait(1);
            } while (GOBJ_SUB(a0)->f_4A0 != 118);
        }
    }
    SetMotionDirection(a0, &dir);
    while (1) {
        ACTSendMailCorrect((char *)a0, 0x99);
        if (flag) {
            ACTSendMailCorrect((char *)a0, 0x9A);
        }
        GetSkeltonPosition(hand, (char *)a0, 22);
        GetSkeltonPosition(foot, (char *)a0, 6);
        base[0] = c.v1[0];
        base[1] = c.v1[1];
        base[2] = c.v1[2];
        if (isCage) {
            TestCageUpDown(c.obj, (void *)a0);
        }
        *(ClimbVec3 *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x350) = c.v2;
        if (hand[1] - base[1] < 10.0f) {
            ACTSendMailCorrect((char *)a0, 0x9B);
        }
        if (foot[1] - base[1] < 10.0f) {
            ACTSendMailCorrect((char *)a0, 0x9C);
        }
        _ACTWait(1);
    }
}

typedef union {
    char *p;
    float *f;
} CagePtr;

extern void afterCommonRopeCliff(char *a0);
/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(void *dst, void *a, void *b, float ta, float tb);
/* kept local: this TU's uses of SetChainRootUpdateMode do not fit the prototype in chain.h */
extern void SetChainRootUpdateMode(void *a0, int mode, float *p);

void actCommonRopeCliff(volatile int a0)
{
    float dst[4];
    float root[4];
    float cur[4];
    float p[4];
    Act *s = GOBJ_ACT(a0);
    int n = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 2;
    float y;
    int i = 0;

    s->afterProc = afterCommonRopeCliff;
    ((CagePtr *)(((CagePtr *)(D_00639EA4 + 0x15C))->p + 0x420))->p = 0;
    dst[0] = *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x1C0);
    dst[1] = *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x1C4);
    dst[2] = *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x1C8);
    GetRootPosition(root, (void *)a0);
    while (1) {
        i++;
        if (i <= n) {
            _InterGV(cur, root, dst, (float)i, (float)(n - i));
            SetDirectRootPositionNoFitting((void *)a0, cur);
        }
        if (*(int *)(*(char **)(a0 + 0x15C) + 0x4A0) == 118) {
            y = ((float *)test_CURRENTROOT((void *)a0))[1];
            SetChainRootUpdateMode(D_00639EA4, 3,
                                   (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1D0));
            p[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
            p[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            p[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
            p[1] = y + 5.0f;
            SetDirectRootPositionNoFitting((void *)a0, p);
        }
        _ACTWait(1);
    }
}

/* SU-E BEGIN TestCageUpDown */
extern int *D_004EB758[];
/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(void *dst, void *a, void *b, float ta, float tb);
/* kept local: this TU's uses of GetSkeltonFocusNode do not fit the prototype in motionManager2.h */
extern int GetSkeltonFocusNode(void *a0, void *a1);

typedef struct {
    float a[4];
    float b[4];
    int cnt;
    int lim;
    int last;
} CageUD;

/* the cage up-down interpolation record TestCageUpDown keeps between frames
   (start, goal, frame count, limit, last motion); MAIN.MAP names no symbol
   in commonact.o's .data, so this name is ours */
static CageUD cageUpDown = {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0, 0, -1};

void TestCageUpDown(int cage, char *gobj)
{
    inline void initCage(char *o)
    {
        int n;

        cageUpDown.cnt = 0;
        cageUpDown.lim = (float)*D_004EB758[*(int *)(((CagePtr *)(o + 0x15C))->p + 0x4A0)];
        n = GetSkeltonFocusNode(o, (void *)0x23);
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
                         float z)
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

    inline void putRoot(float *pos, float *lo, float *hi, int clamp)
    {
        float lim;
        float low;
        float d;

        lim = 50.0f;
        if (stage_no == 8) {
            lim = 80.0f;
        }
        pos[0] = ((float *)test_CURRENTROOT(gobj))[0];
        pos[1] = ((float *)test_CURRENTROOT(gobj))[1];
        pos[2] = ((float *)test_CURRENTROOT(gobj))[2];
        low = lo[1] + lim;
        d = ((CagePtr *)(gobj + 0x15C))->f[81];
        pos[1] = pos[1] + d;
        if (clamp) {
            pos[1] = pos[1] < low ? low : (hi[1] < pos[1] ? hi[1] : pos[1]);
        }
        SetDirectRootPositionNoFitting(D_00639EA4, pos);
    }

    inline void chainUpdate(float *sk, float *out, float *lo, float *hi)
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
    int mot = *(int *)(((CagePtr *)(gobj + 0x15C))->p + 0x4A0);

    GetCageChainPoint(vB, vC, (void *)cage);
    *(int *)(((CagePtr *)(D_00639EA4 + 0x15C))->p + 0x420) = 0;
    switch (mot) {
    case 0x78:
        putRoot(vE, vB, vC, 1);
        chainUpdate(vG, vH, vB, vC);
        break;
    case 0x77:
        if (GOBJ_ACT(gobj)->unk34 == 0x3F) {
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
            GetSkeltonPosition((float *)(*(char **)(*(char **)(gobj + 0x164) + 0x688) + 0x410),
                               gobj, 22);
        }
        _InterGV(vD, vB, vC,
                 *(float *)(*(char **)(*(char **)(gobj + 0x164) + 0x688) + 0x414) - vB[1],
                 vC[1] - *(float *)(*(char **)(*(char **)(gobj + 0x164) + 0x688) + 0x414));
        SetChainRootUpdateMode(gobj, 3, vD);
        break;
    }
    cageUpDown.last = mot;
}

/* SU-E END TestCageUpDown */

/* kept local: this TU's uses of GetOrientOfWall do not fit the prototype in fieldCollision.h */
extern void GetOrientOfWall(void *out, void *obj, void *pos);
extern char D_00552DD0[];
extern char D_00552DE0[];
extern char D_0063A718[];
extern int D_0063B13C;

typedef struct {
    float x, y;
} RsVec2;

typedef struct {
    RsVec2 xy;
    void *obj;
} RsHit;

typedef union {
    float f[4];
    long long ll[2];
} RsVec4;

typedef struct {
    char _0[0x330];
    char f330[0x10];
    float f340;
    float f344;
    float f348;
    char f34C[4];
    RsHit f350;
    int f35C;
} RsSub;

typedef struct {
    char _00[0x80];
    RsVec2 h80;
    int f88;
    char _8C[0x34];
} RsWork;

static inline unsigned char ropeSpecialWallHit(RsVec4 *p1, RsHit *hit)
{
    RsVec4 va;
    RsVec4 vb;
    RsWork work;
    int i;

    va = *(RsVec4 *)D_00552DD0;
    vb = *(RsVec4 *)D_00552DE0;
    for (i = 0; i < 4; i++) {
        sceVu0UnitMatrix((void *)MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(p1->f[0], p1->f[1] + 0.0f, p1->f[2]);
        MatrixDrive_RotMatrixY((short)((float)i * 0.7853982f * 32768.0f / 3.1415927f));
        sceVu0ApplyMatrix(&work, (void *)MatrixDrive_GetMatrix(), &va);
        sceVu0ApplyMatrix((char *)&work + 0x10, (void *)MatrixDrive_GetMatrix(), &vb);
        ClipWall(&work);
        if (work.f88 != 0) {
            hit->xy = work.h80;
            hit->obj = (void *)work.f88;
            return 1;
        }
    }
    return 0;
}

void actCommonRopeSpecial(volatile int a0)
{
    char *s;
    RsHit hit;
    RsVec4 p1;
    RsVec4 p2;
    RsVec4 pos;
    int cage;
    unsigned char found;

    s = *(char **)(a0 + 0x164);
    cage = *(int *)(s + 0x610);
    if (cage != 0) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x400) = cage;
    } else {
        cage = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x400);
    }
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) == 4 ||
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) == 5) {
        GetSkeltonPosition((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x410),
                           (char *)a0, 35);
    } else {
        GetSkeltonPosition((float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x410),
                           (char *)a0, 22);
    }
    GetCageChainPoint(p1.f, p2.f, (void *)cage);
    found = ropeSpecialWallHit(&p1, &hit);
    GOBJ_SUB(a0)->f_420 = 0;
    while (1) {
        if (GOBJ_SUB(a0)->f_4A0 == 118) {
            *(long long *)(s + 0x20) &= ~(1ULL << 11);
        }
        GetSkeltonPosition(pos.f, (char *)a0, 35);
        GetCageChainPoint(p1.f, p2.f, (void *)cage);
        if (D_0063B13C & 1) {
            debug_Printf(10, 120, 0xFFFFFFF, D_0063A718,
                         (int)*(float *)((char *)test_CURRENTROOT((void *)a0) + 4), (int)p2.f[1]);
        }
        if (*(float *)((char *)test_CURRENTROOT((void *)a0) + 4) > p2.f[1] - 30.0f) {
            ACTSendMailCorrect((char *)a0, 0xC7);
        }
        if (found && pos.f[1] < p1.f[1] + 60.0f) {
            ((RsSub *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f35C = cage;
            GetOrientOfWall(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x330, hit.obj, &hit);
            ((RsSub *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f340 = p1.f[0];
            ((RsSub *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f344 = p1.f[1];
            ((RsSub *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f348 = p1.f[2];
            ((RsSub *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f344 -= 100.0f;
            ((RsSub *)*(char **)(*(char **)(a0 + 0x164) + 0x680))->f350 = hit;
            ActSendMail_WithAdditionalData((char *)a0, 0xB0, (void *)a0,
                                           *(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x330);
        }
        TestCageUpDown(cage, (void *)a0);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of SetFloorLeverWithNodePoint do not fit the prototype in box.h */
extern void SetFloorLeverWithNodePoint(void *a0, void *a1, int a2);
/* kept local: this TU's uses of SetWallLeverWithNodePoint do not fit the prototype in box.h */
extern void SetWallLeverWithNodePoint(void *a0, void *a1, int a2);

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

typedef struct {
    char _0[0x394];
    int f394;
} LeverAnim;

extern char D_00552DF0[];
/* kept local: this TU's uses of GetFloorLeverGlobalHoldPoint do not fit the prototype in box.h */
extern void GetFloorLeverGlobalHoldPoint(void *out, void *lev);
/* kept local: this TU's uses of GetWallLeverGlobalHoldPoint do not fit the prototype in box.h */
extern void GetWallLeverGlobalHoldPoint(void *out, void *lev);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTMotDirToWall (lines 1307-1312) into actCommonLever, so it
   is `inline` in the dev's TU; while this tail still has asm members a deferred
   inline would land at the object end instead of at its ROM slot, so the public
   body below stays a plain definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void actMotDirToWall(char *a0)
{
    int local[4];
    sceVu0ScaleVector(local, *(char **)(a0 + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(a0, local);
}

static inline void correctLeverHoldPoint(void *a0, char *lev)
{
    float w[4];
    if (*(int *)(lev + 0xC) >= 0x16) {
        if (*(int *)(lev + 0xC) < 0x18) {
            GetFloorLeverGlobalHoldPoint(w, lev);
        } else if (*(int *)(lev + 0xC) < 0x1A) {
            GetWallLeverGlobalHoldPoint(w, lev);
            debug_StdPrintfDummy(D_00552DF0, w[0], w[1], w[2]);
        }
    }
    SetDirectRootPositionNoFittingWithNodePointXZ(a0, 0x16, w, 0.2f);
}

void actCommonLever(volatile int a0)
{
    float p[4];
    Act *s = GOBJ_ACT(a0);
    char *lev = *(char **)((char *)s + 0x5FC);

    ((LeverAnim *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f394 =
        ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 5;
    p[0] = *(float *)((char *)s + 0x5A0);
    p[1] = *(float *)((char *)s + 0x5A4);
    p[2] = *(float *)((char *)s + 0x5A8);
    p[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 0x2C, (char *)s + 0x5A0, 1.0f);
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(a0)->f_604 != 0) {
                correctLeverHoldPoint((void *)a0, lev);
            }
            if (GOBJ_SUB(a0)->f_600 != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of eBrainSendMes do not fit the prototype in ebrain.h */
extern void eBrainSendMes(void *a0);

void EBRAIN_SEND_MES(void *a0, int a1)
{
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        eBrainSendMes(a0);
}

extern char D_0063A720[];
/* kept local: this TU's uses of EnemyDeleteParticle do not fit the prototype in enemy.h */
extern void EnemyDeleteParticle(void *a0, void *a1, void *a2);

void DamageFunc(char *a0)
{
    int s = *(int *)(a0 + 0x164);
    debug_StdPrintfDummy(D_0063A720);
    if (a0 != D_00639EA8) {
        *(float *)(s + 0x1E0) -= (float)GOBJ_ACT(a0)->f_1D0;
    }
    if (*(int *)(a0 + 0xC) == 4) {
        char *b;
        EBRAIN_SEND_MES(a0, 5);
        b = *(char **)(*(char **)(a0 + 0x164) + 0x680);
        EnemyDeleteParticle(a0, b + 0xE0, b + 0xF0);
    }
}

void DownFunc(char *a0)
{
    DamageFunc(a0);
    if (*(int *)(a0 + 0xC) == 1) {
        EBRAIN_SEND_MES(*(void **)(*(char **)(a0 + 0x164) + 0x1B0), 6);
    }
}

extern char D_00552E30[];

void actCommonDown(volatile int a0)
{
    float v[4];
    Act *s = GOBJ_ACT(a0);
    int notDamage = *(int *)((char *)s + 0xD8) != 0x37 && *(int *)((char *)s + 0xD8) != 0x38;

    debug_StdPrintfDummy(D_00552E30);
    *(int *)((char *)s + 0x18) = (int)actAfterDown;
    if (notDamage) {
        if ((char *)a0 == D_00639EA4) {
            brainAddLevelGirl(1000.0f);
        }
        if ((char *)a0 == D_00639EA8) {
            sceVu0ScaleVector(v, *(char **)(a0 + 0x164) + 0x1C0, -1.0f);
            SetMotionDirection(a0, v);
        } else {
            SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
        }
        DownFunc((char *)a0);
    }
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC) = 0x10;
    while (1) {
        if (*(int *)(a0 + 0xC) != 4) {
            GOBJ_ACT(a0)->f_1DA = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC) <= 0) {
            ACTSendMailCorrect((char *)a0, 0x124);
        }
        _ACTWait(1);
    }
}

extern char D_00552E48[];
extern void debug_StdPrintfDummy();
extern void DownFunc(char *a0);
extern void gamesysObjInfoCls(int a0, int a1);
extern void *isysGObjSearchFromObjKindID_begin(int a0);
extern void ResetReviveCountEnemy(volatile int a0);
extern void enemySetParticleDie(void *root, void *dir);
extern void EnemySetfDisappearAll(volatile int a0);
extern void actEnemyFlagOnDead(volatile int a0);
extern void ACTGame_DeleteActorInformation(volatile int a0);
extern void SetEnemyDissolve(volatile int a0, float d);
extern void actEnemyHyde(volatile int a0);

void actCommonDie(volatile int a0)
{
    /* SRCFILE.TXT puts these rows (commonact.c:2619-2631) after the 2650
       statement, inside actCommonDie's own 2616-2700 span, which is the
       inlined body of a helper defined at the head of this body. */
    inline void dieNotifyObjects(void)
    {
        void *g;

        if (*(int *)(a0 + 8) == 0xEAD) {
            gamesysObjInfoCls(4, 0xEAD);
            gamesysObjInfoCls(0x21, 0xEAE);
        }
        g = isysGObjSearchFromObjKindID_begin(0x2F);
        if (g == 0) {
            g = isysGObjSearchFromObjKindID_begin(0x41);
        }
        if (*(int *)(a0 + 0xC) == 4 && g != 0) {
            iosOmSendMail(g, 0x12, a0);
        }
    }
    char *s = *(char **)(a0 + 0x164);
    int cnt = 0;
    float t;
    int corpse;

    if (*(int *)(s + 0xD8) == 0x2C) {
        corpse = 1;
    } else {
        corpse = 0;
    }
    debug_StdPrintfDummy(D_00552E48);
    SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
    DownFunc((char *)a0);
    *(char *)(*(char **)(a0 + 0x164) + 0x1DA) = 1;
    dieNotifyObjects();
    if (*(int *)(a0 + 8) == 0xEAD) {
        ResetReviveCountEnemy(a0);
    }
    while (1) {
        if (corpse) {
            ACTSetPositionWithFitting((void *)a0, test_CURRENTROOT((void *)a0));
        }
        if (*(int *)(a0 + 0xC) == 4) {
            _ACTWait(1);
            enemySetParticleDie(test_CURRENTROOT((void *)a0), *(char **)(a0 + 0x164) + 0x1C0);
            EnemySetfDisappearAll(a0);
            actEnemyFlagOnDead(a0);
            ACTGame_DeleteActorInformation(a0);
            for (t = 0.0f; t < (float)(((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 6);
                 t += *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x334)) {
                float d = (t + t - (float)(((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 6)) /
                          (float)(((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 6);
                if (d < 0.01f) {
                    d = 0.01f;
                }
                SetEnemyDissolve(a0, d);
                if ((int)(*(long long *)(s + 0x20) >> 22) & 1) {
                    t += 10.0f;
                }
                _ACTWait(1);
            }
            actEnemyHyde(a0);
            _ACTWait(0);
        }
        if (a0 == (int)D_00639EA4 || a0 == (int)D_00639EA8) {
            if (((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 2 < cnt) {
                ACT_LAYOUT_GAMEOVER();
                _ACTWait(0);
            }
        }
        cnt++;
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of RotQuaternionX do not fit the prototype in quaternion.h */
extern void RotQuaternionX(float *q, short a);
/* kept local: this TU's uses of RotQuaternionY do not fit the prototype in quaternion.h */
extern void RotQuaternionY(float *q, short a);
/* kept local: this TU's uses of RotQuaternionZ do not fit the prototype in quaternion.h */
extern void RotQuaternionZ(float *q, short a);
/* kept local: this TU's uses of SetMotionNodeFixModeParameter do not fit the prototype in motionManager2.h */
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q, float x,
                                          float y, float z, float w);
extern char D_00552D90[];
extern char D_00552E60[];
extern void debug_assert(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);

typedef struct {
    int rot[3];
    float f0C;
    float f10;
    float f14;
    int f18;
    int f1C;
    int f20;
} ClingRec;

extern ClingRec D_002BC4C0[];

typedef struct {
    char _0[0x21C];
    int f21C;
    int f220;
} ClingSub;

void actCommonCling(volatile int a0)
{
    int no;
    int mot;

    int Cling(int idx, int m)
    {
        float q[4];
        ClingRec *r;
        int i;
        int v;

        r = &D_002BC4C0[idx];
        memset(q, 0, 16);
        q[3] = 1.0f;
        if (!((unsigned int)idx < 15)) {
            debug_assert(D_00552D90, 0xAAD);
            __assert(D_00552D90, 0xAAD, D_00552E60);
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
        SetMotionNodeFixModeParameter((void *)a0, (void *)m, r->f18, r->f20, q, r->f0C, r->f10,
                                      r->f14, 1.0f);
        return r->f1C;
    }

    no = (int)(_GetRandom() * 10.0f) % 15;
    mot = ((ClingSub *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f21C;

    ((ClingSub *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f220 = mot;
    ACTGameCollisionOff(a0);
    Cling(no, mot);
    _ACTWait(0);
}

void actCommonSlip(volatile int a0)
{
    float dir[4];
    float v2[4];
    float v3[4];

    if (*(unsigned char *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x280) == 0) {
        dir[0] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270);
        dir[1] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x274);
        dir[2] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x278);
    } else {
        sceVu0ScaleVector(dir, (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270),
                          -1.0f);
    }
    v2[0] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270);
    v2[1] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x274);
    v2[2] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x278);
    sceVu0ScaleVector(v3, (float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x270), 30.0f);
    v3[1] = -20.0f;
    while (1) {
        SetMotionDirectionSmooze(a0, dir, 3.0f);
        _ACTWait(1);
    }
}

extern int enable_game_pause;
extern int D_0063AA08;
/* kept local: this TU's uses of _OrientXZGV do not fit the prototype in gv.h */
extern void _OrientXZGV(void *out, void *a, void *b);

void actCommonStoneDead(volatile int a0)
{
    float center[4];
    float dir[4];
    Act *s = GOBJ_ACT(a0);

    if (*(int *)((char *)s + 0xD8) == 0x22) {
        SetBoyStonizedVisual(a0);
        GetGameOverEffectCenterPosition(center);
        _OrientXZGV(dir, center, test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, dir);
    } else {
        ACTSetPositionWithFitting((void *)a0, test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
        *(int *)(a0 + 0x50) = 0;
    }
    enable_game_pause = 0;
    D_0063AA08 = 1;
    _ACTWait(300);
    ACT_LAYOUT_GAMEOVER();
    _ACTWait(0);
}

extern char D_00552EB8[];
extern char D_00552EC8[];

typedef struct {
    char _0[0x14];
    int f14;
    char _18[0x34];
    int f4C;
} StoneSub;

void actCommonStone(volatile int a0)
{
    StoneSub *s = (StoneSub *)*(char **)(a0 + 0x164);

    s->f14 = (int)afterCommonStone;
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x2A0) = 0;
    while (1) {
        if (D_0063B13C & 1) {
            debug_Printf(10, 170, 0xFFFFFFF, D_00552EB8,
                         *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC));
        }
        if (D_0063B13C & 1) {
            debug_Printf(10, 180, 0xFFFFFFF, D_00552EC8,
                         *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C));
        }
        switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C)) {
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
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xCC) < 0) {
            ACTSendMailCorrect((char *)a0, 0xC7);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C) = 0;
        }
        if (s->f4C >= 0x3D && *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x29C) >= 3) {
            ACT_LAYOUT_GAMEOVER();
            _ACTWait(0);
        }
        ACTSendMailCorrect((char *)a0, 0x70);
        _ACTWait(1);
    }
}

typedef struct {
    char _0[0x250];
    int f250, f254, f258, f25C;
} SofaObj;

typedef struct {
    char _0[0x3A0];
    int f3A0, f3A4;
} SofaAnim;

void actCommonSofa(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    SetDirectRootPositionNoFitting((void *)a0, (char *)s + 0x5B0);
    ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f250 = 0;
    ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f258 = 0;
    ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f25C = 0;
    *(void **)((char *)s + 0x160) = *(void **)((char *)s + 0x61C);
    while (1) {
        ((SofaAnim *)*(int *)(*(int *)(a0 + 0x164) + 0x688))->f3A0 =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 3;
        ((SofaAnim *)*(int *)(*(int *)(a0 + 0x164) + 0x688))->f3A4 =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
        if (((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f250 >
            ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f254) {
            ACTSendMailCorrect((char *)a0, 0x73);
        }
        ((SofaObj *)*(int *)(*(int *)(a0 + 0x164) + 0x680))->f250 += 1;
        _ACTWait(1);
    }
}

void BoxBarSoundOn(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    switch (s->unk34) {
    case 0x31:
        ExecBoxMoveStartReaction(*(int *)((char *)s + 0x158), *(int *)((char *)s + 0x38));
        break;
    case 0x33:
        ExecRotObjectMoveStartReaction(*(int *)((char *)s + 0x5F8));
        break;
    }
}

void BoxBarSoundOff(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    switch (s->unk34) {
    case 0x31:
        ExecBoxMoveEndReaction(*(int *)((char *)s + 0x158));
        break;
    case 0x33:
        ExecRotObjectMoveEndReaction(*(int *)((char *)s + 0x5F8));
        break;
    }
}

void _boxbar_set_sound(int a0, int mode)
{
    switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310)) {
    case 0:
        if (mode == 1) {
            BoxBarSoundOn((char *)a0);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = 1;
        }
        break;
    case 1:
        if (mode == 0 || mode == 2) {
            BoxBarSoundOff((char *)a0);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = mode;
        } else {
            BoxBarSoundOn((char *)a0);
        }
        break;
    case 2:
        if (mode == 0) {
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = 0;
        }
        if (mode == 3) {
            BoxBarSoundOn((char *)a0);
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x310) = 1;
        }
        break;
    }
}

extern void afterCommonBox(volatile int a0);
typedef void (*BoxAfterFn)(volatile int);
extern void brainAddLevelGirl(float f);
extern void GetBoxHoldPoint(void *hold, char *box, void *self);
extern void sceVu0AddVector(void *out, void *a, void *b);
extern void ACTSendMailCorrect(char *a0, int a1);
extern void AlignBox(char *box, float f);
extern int MoveBoxWithHoldPoint(char *box, void *hold, void *self, int node, void *dir);
extern void GetBoxGlobalHoldPoint(void *out, char *box, void *hold);
extern int GetBoxMode(char *box);
extern char D_0063A728[];
extern char D_0063A730[];

/* reconstruction: the third view of the same 0xC0-byte ClipWall work buffer
   (RopeWallWork above and RsWork below are the other two). This one reads the
   two vectors at 0x00 and 0x10, the height at 0x70 and the hit flag at 0x88;
   the views are kept apart for the reason given at RopeWallWork. */
typedef struct {
    float p[4];
    float q[4];
    char _20[0x50];
    float f70;
    char _74[0x14];
    int f88;
    char _8C[0x34];
} BoxWallWork;

/* The height is an int: the ROM materialises 48.0f and 30.0f at the 0x70 store
   inside each inlined copy, which only happens when the constant reaches that
   store through a conversion integrate.c can fold there. A float parameter is
   copied into a pseudo at the top of the inlined body instead, and loop.c then
   hoists the 30.0f copy out of the loop into a fourth callee-saved FP register
   the ROM does not save. */
static inline int boxWallCheck(int a0, char *box, float dist, int h)
{
    BoxWallWork w;
    float t[4];
    char *s = *(char **)(a0 + 0x164);

    GetRootPosition(w.p, box);
    GetRootPosition(w.q, box);
    sceVu0ScaleVector(t, s + 0x4B0, dist);
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

void actCommonBox(volatile int a0)
{
    char *box;
    /* SRCFILE.TXT puts commonact.c:3276-3280 after the 3316 rows and before
       the 3322 rows, inside actCommonBox's own span: an inlined helper
       defined at the head of this body, above the 3284 chase. */
    inline void addGirlLevelForBox(char *b)
    {
        if (D_00639EA8 != 0 && *(char **)(*(char **)(D_00639EA8 + 0x15C)) == b) {
            brainAddLevelGirl(1000.0f);
        }
    }
    char *s = *(char **)(a0 + 0x164);
    char *sub;
    float hold[4];

    *(BoxAfterFn *)(s + 0x14) = afterCommonBox;
    box = *(char **)(s + 0x5F4);
    if (stage_no == 0x10) {
        sub = *(char **)(*(char **)(box + 0x15C));
        if (sub != 0) {
            if (*(int *)(sub + 0xC) == 0x11) {
                box = sub;
            }
        }
    }
    ((Act *)s)->box = box;
    actMotDirToWall((char *)a0);
    sceVu0ScaleVector(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x530, s + 0x4B0, -1.0f);
    while (1) {
        int had = *(int *)(s + 0x38) != 0;
        int f2 = 0;
        int miss = 0;
        int flag = 0;
        unsigned char isTruck = IsThisBoxTruck(box);

        addGirlLevelForBox(box);
        GetBoxHoldPoint(hold, box, (void *)a0);
        if (!isTruck) {
            if (boxWallCheck(a0, box, 100.0f, 48)) {
                ACTSendMailCorrect((char *)a0, 0xC7);
                miss = 1;
            }
            if (*(unsigned int *)(s + 0x38) == 0xFFFFFFFF) {
                if (boxWallCheck(a0, box, 150.0f, 48)) {
                    miss = 1;
                }
            }
        }
        if (!miss && (isTruck == 0 ? *(int *)(*(char **)(a0 + 0x15C) + 0x608)
                                   : *(int *)(*(char **)(a0 + 0x15C) + 0x600))) {
            f2 = 1;
            if (*(int *)(s + 0x38) == 1 && boxWallCheck(a0, box, -25.0f, 30)) {
                miss = 1;
            } else {
                float dir[4];
                unsigned char ok;
                if (*(unsigned int *)(s + 0x38) == 0xFFFFFFFF) {
                    dir[0] = *(float *)(s + 0x4B0);
                    dir[1] = *(float *)(s + 0x4B4);
                    dir[2] = *(float *)(s + 0x4B8);
                } else {
                    sceVu0ScaleVector(dir, s + 0x4B0, -1.0f);
                }
                if (!isTruck) {
                    debug_StdPrintfDummy(D_0063A728);
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
                (void *)a0, 22, pos, *(int *)(*(char **)(a0 + 0x15C) + 0x600) != 0 ? 1.0f : 0.3f);
        }
        if (!had) {
            _boxbar_set_sound(a0, 0);
            if (!isTruck) {
                debug_StdPrintfDummy(D_0063A730);
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
            *(unsigned long long *)(s + 0x20) |= (1ULL << 40);
            *(unsigned long long *)(s + 0x20) |= (1ULL << 41);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of GetMotionFrameFlag1 do not fit the prototype in motionManager2.h */
extern int GetMotionFrameFlag1(void *a0);
/* kept local: this TU's uses of GetMotionFrameFlag2 do not fit the prototype in motionManager2.h */
extern int GetMotionFrameFlag2(void *a0);
extern char D_0063A740[];

typedef struct {
    char _0[0x1C0];
    int f1C0;
    int f1C4;
    int f1C8;
} BarHold;

void actCommonBar(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    char *bar;
    float pos[4];
    float ori[4];
    float hold[4];
    float hold2[4];

    bar = *(char **)((char *)s + 0x5F8);
    actMotDirToWall((char *)a0);
    pos[0] = *(float *)((char *)test_CURRENTROOT((void *)a0) + 0);
    pos[1] = *(float *)((char *)test_CURRENTROOT((void *)a0) + 4);
    pos[2] = *(float *)((char *)test_CURRENTROOT((void *)a0) + 8);
    ori[0] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 0);
    ori[1] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 4);
    ori[2] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 8);
    GetRotObjectHoldPoint(hold, hold2, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x8B0,
                          (void *)a0);
    (int)GOBJ_SUB(s) = (int)bar;
    s->f_14 = (int)afterCommonBar;
    debug_StdPrintfDummy(D_0063A740, bar);
    ((BarHold *)(int)GOBJ_SUB(a0))->f1C0 = (int)bar;
    ((BarHold *)(int)GOBJ_SUB(a0))->f1C4 = -1;
    ((BarHold *)(int)GOBJ_SUB(a0))->f1C8 = 0;
    while (1) {
        int had = *(int *)((char *)s + 0x38) != 0;
        int lit = 0;
        int miss = 0;
        int flag = 0;
        if (GetMotionFrameFlag1((void *)a0)) {
            float dir[4];
            float up[4];
            int node = GetSkeltonFocusNode((void *)a0, (void *)0x20);
            unsigned char ok;
            lit = 1;
            CopyVector(dir, *(char **)((char *)GOBJ_SUB(a0) + 0xC) + node * 64 + 0x30);
            if (s->f_38 == 0xFFFFFFFF) {
                sceVu0ScaleVector(up, test_CURRENTORIENT((char *)a0), -1.0f);
            } else {
                up[0] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 0);
                up[1] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 4);
                up[2] = *(float *)((char *)test_CURRENTORIENT((char *)a0) + 8);
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

void funcCommonJumpDircorrect(char *a0)
{
    SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x350);
}

void funcCommonFallDircorrect(char *a0)
{
    SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x360);
}

extern float D_0063A748[];
/* kept local: this TU's uses of GetMatrixDirectionToZ do not fit the prototype in gv.h */
extern void GetMatrixDirectionToZ(void *m, void *orient);
/* kept local: this TU's uses of GetChainHangRange do not fit the prototype in chain.h */
extern float GetChainHangRange(void *o);
/* kept local: this TU's uses of GetChainLength do not fit the prototype in chain.h */
extern float GetChainLength(void *o);

void correctJumpOrientByChain(char *a0)
{
    float out[4];
    float mtx[16];
    float pos[4];
    float p[4];
    float q[4];
    float dir[4];
    char *o;
    float t;
    float best = D_0063A748[0];
    float ang = 0.0f;

    pos[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
    pos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    pos[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(a0));

    for (o = isysGObjSearchFromObjKindID_begin(21); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (*(int *)(o + 0x16C) == 0) {
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
    if (best == D_0063A748[0]) {
        return;
    }
    _OrientXZGV(dir, out, test_CURRENTROOT((void *)a0));
    t = ang * 20.0f / 300.0f;
    if (t < 0.0f) {
        t = 0.0f;
    } else if (20.0f < t) {
        t = 20.0f;
    }
    SetMotionDirectionSmooze((int)a0, dir, t);
}

typedef union {
    unsigned long long ll;
    void *p;
} ActFlagJ;

typedef struct {
    char _0[0x18E];
    unsigned short f18E;
} MotRecJ;

void actCommonJump(volatile int a0)
{
    float dir[4];
    Act *s = GOBJ_ACT(a0);
    int chk = 0;
    int hit = 0;
    int n;

    ((ActFlagJ *)((char *)s + 0x18))->ll &= ~(1ULL << 55);
    ((ActFlagJ *)((char *)s + 0x18))->p = (void *)actAfterJump;
    if (*(int *)((char *)s + 0xD8) == 0x52) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3B4) =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
    }
    if (*(int *)((char *)s + 0xD8) == 0x105) {
        ((ActFlagJ *)((char *)s + 0x18))->ll |= (1ULL << 55);
        if ((char *)a0 == D_00639EA8 && D_00639EA4 != 0) {
            _OrientXZGV(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
            SetMotionDirection(a0, dir);
        }
    }
    ((ActFlagJ *)((char *)s + 0x18))->ll &= ~(1ULL << 56);
    if (*(int *)((char *)s + 0xD8) == 0xC5) {
        SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x510);
        ((ActFlagJ *)((char *)s + 0x18))->ll |= (1ULL << 56);
    }
    n = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900);
    if (n < 4) {
        if (0 < n) {
            switch ((unsigned int)*(int *)((char *)s + 0xD8)) {
            case 0xBF:
            case 0xC0:
                chk = 1;
                break;
            case 0xBD:
                if (0.1f < *(float *)((char *)s + 0x34C)) {
                    chk = 1;
                }
                break;
            }
            if (chk != 0) {
                correctJumpOrientByChain((char *)a0);
            }
        }
    }
    while (1) {
        if (((MotRecJ *)(D_0055FE58 + GOBJ_SUB(a0)->f_4A0 * 0x194))->f18E & 1) {
            hit = 1;
        }
        if (hit != 0 && *(int *)(D_0055FE58 + GOBJ_SUB(a0)->f_4A0 * 0x194 + 0x150) == 1) {
            GOBJ_SUB(a0)->f_130 = GOBJ_SUB(a0)->f_138 = 0.0f;
        }
        ACTSendMailCorrect((char *)a0, 0xBD);
        _ACTWait(1);
    }
}

extern const StgPre D_005F5D50[];
extern int stage_no;
extern int D_0028F4C0[];
extern char *D_00639EA8;
extern void debug_StdPrintfDummy();
extern void *test_CURRENTORIENT(char *a0);
extern void _ACTWait(int a0);
extern char D_00552ED8[];
extern void actAfterFall(volatile int a0);
extern int ACTCheckCollis_WELL(float *a0, float *a1, int a2, float *a3, float rad);
extern float GetDifferenceFromLowerField(volatile int a0, int node);
extern void sceVu0ScaleVector(void *dst, void *src, float s);

/* The 0x15C slot is the engine's sub-object handle, read here as the SubHandle
 * union the way geometryManager.c's SUBOF reads it: the union read may-alias
 * the float stores to the velocity, so each arm re-walks the slot between them
 * as the ROM does.  GOBJ_SUB's int view is what the other readers need (the
 * union view changes st04a's finishCallBackFunc), so this view stays local. */
#define FALL_SUB(o) ((Sub15C *)((SubHandle *)((o) + 0x15C))->p)

/* lines 3732-3749 of the January-2002 listing, a static inline that
 * actCommonFall and flyCoreLoop call.  The listing puts the copies of its
 * constant arguments (the state and the time) on the definition line, where
 * the inliner emits them, and the ROM multiplies by that copy of the time
 * while the literal 60s of the rate and the division share one hoisted
 * register.  flyCoreLoop's copy proves the motion test and the count: it
 * passes a motion that is not 418 (so the q[10] compare survives) and needs
 * three hits where actCommonFall needs two. */
static inline int IsFallStuckOnStep(int a0, int state, int mot, int need, int time)
{
    char *s = *(char **)(a0 + 0x164);
    int *q;
    int i, n, d;

    for (i = 0, n = 1, q = (int *)(*(char **)(s + 0x688) + 0x928); i < 10; i++, q++) {
        if (q[-10] == state && (mot == 418 || mot == q[10])) {
            if (n >= need) {
                d = *(int *)(s + 0x10) - *q;

                if (d < time * ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60) {
                    return 1;
                }
                break;
            }
            n++;
        }
    }
    /* the not-found path returns the count variable, cleared: the ROM's
       in-place n test and n++ in both callers depend on this set of n */
    n = 0;
    return n;
}

void actCommonFall(volatile int a0)
{
    float pa[4];
    float pb[4];
    float hit[4];
    float lo[4];
    float hi[4];
    char *s = *(char **)(a0 + 0x164);
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
    ((Act *)s)->afterProc = (void (*)(char *))actAfterFall;
    if (D_005F5D50[stage_no].flag3) {
        keep = FALL_SUB(a0)->f_5F8 & 0xF;
        debug_StdPrintfDummy(D_00552ED8, FALL_SUB(a0)->f_5F8, keep);
        FALL_SUB(a0)->f_5F8 = 0;
        FALL_SUB(a0)->f_5F8 = keep;
    } else {
        FALL_SUB(a0)->f_5F8 = 0;
    }
    mot = *(unsigned int *)(s + 0xD8);
    switch (mot) {
    case 226:
        if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) == 34 ||
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) == 28 ||
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) == 30) {
            FALL_SUB(a0)->f_130 = 0;
            noVel = 1;
            FALL_SUB(a0)->f_134 = 0;
            FALL_SUB(a0)->f_138 = 0;
        }
        break;
    case 329:
        SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x4C0);
        break;
    case 166:
        FALL_SUB(a0)->f_130 = 0;
        FALL_SUB(a0)->f_134 = 0;
        FALL_SUB(a0)->f_138 = 0;
        break;
    case 24:
        FALL_SUB(a0)->f_130 = 0;
        FALL_SUB(a0)->f_134 = 0;
        FALL_SUB(a0)->f_138 = 0;
        wasHigh = 1;
        noVel = 1;
        break;
    case 49:
        sceVu0ScaleVector(&FALL_SUB(a0)->f_130, test_CURRENTORIENT((char *)a0), -5.0f);
        FALL_SUB(a0)->f_134 = 3.0f;
        wasHigh = 1;
        ((ActStatus *)(s + 0x18))->ll |= (1ULL << 53);
        *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x338) = 200.0f;
        break;
    case 48:
        GetSkeltonPosition(pa, *(char **)(s + 0x2C), 44);
        GetSkeltonPosition(pb, (char *)a0, 44);
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
        ((ActStatus *)(s + 0x18))->ll |= (1ULL << 53);
        FALL_SUB(a0)->f_130 = 0;
        FALL_SUB(a0)->f_134 = 0;
        FALL_SUB(a0)->f_138 = 0;
        if (d < 800.0f) {
            *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x338) = 900.0f;
        } else {
            if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) != 38) {
                p = *(char **)(*(char **)(a0 + 0x164) + 0x30);
                if (p != 0 && 100.0f < *(float *)p && *(float *)p < 500.0f) {
                    *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x338) = *(float *)p;
                    break;
                }
            }
            *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x338) = 500.0f;
        }
        break;
    default:
        if (mot == 7 && *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x950) == 259) {
            FALL_SUB(a0)->f_130 = 0;
            FALL_SUB(a0)->f_134 = 0;
            FALL_SUB(a0)->f_138 = 0;
            noVel = 1;
        }
        n = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900);
        if (19 <= n) {
            if (22 <= n) {
                if (n < 29) {
                    if (27 <= n) {
                        FALL_SUB(a0)->f_130 = 0;
                        FALL_SUB(a0)->f_134 = 0;
                        FALL_SUB(a0)->f_138 = 0;
                        noVel = 1;
                    }
                }
            } else {
                wasHigh = 1;
            }
        }
        if ((char *)a0 == D_00639EA8 && mot == 7 &&
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x900) == 21) {
            slowed = 1;
            FALL_SUB(a0)->f_134 = 0;
        }
        if ((unsigned char)IsFallStuckOnStep(a0, 5, 418, 2, 60)) {
            ((Act *)s)->flags20.ll |= (1ULL << 42);
        }
        break;
    }
    while (1) {
        if (*(int *)(s + 0x4C) < ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 6) {
            if (wasHigh) {
                ((ActStatus *)(s + 0x18))->ll |= (1ULL << 52);
            }
            if (noVel) {
                FALL_SUB(a0)->f_130 = FALL_SUB(a0)->f_138 = 0.0f;
            }
            if (slowed) {
                FALL_SUB(a0)->f_130 *= 0.8;
                FALL_SUB(a0)->f_138 *= 0.8;
            }
        }
        ACTSendMailCorrect((char *)a0, 314);
        _ACTWait(1);
    }
}

/* SU-E END actCommonFall */

/* reconstruction: the sub-object's fly-limit flag at 0x654.  A field
   reference, not a cast-dereference: flyCoreLoop's ROM keeps the actor
   argument's frame load available across the store (gcse moves it onto the
   other arm of the join), which alias analysis allows only when the store is
   a struct member and the frame slot a scalar. */
typedef struct {
    char _0[0x654];
    int limit;
} FlyLimitSub;

/* line 3962: raises the flag that ResetFlyLimit clears */
static inline void SetFlyLimit(int a0)
{
    ((FlyLimitSub *)FALL_SUB(a0))->limit = 1;
}

/* lines 3965-3968, used by flyCoreLoop and actAfterFly */
static inline void ResetFlyLimit(int a0)
{
    ((FlyLimitSub *)FALL_SUB(a0))->limit = 0;
}

/* lines 3979-3984: clamp to -1..1 */
static inline float clampUnit(float x)
{
    if (1.0f < x) {
        x = 1.0f;
    }
    if (x < -1.0f) {
        x = -1.0f;
    }
    return x;
}

/* line 3988: the vertical pull toward the target height */
static inline float calcVertAccel(float *a, float *b)
{
    return clampUnit((a[1] - b[1]) * 0.005f);
}

/* lines 3992-4002: the vertical pull with a term for the horizontal distance */
static inline float calcFlyAccel(float *a, float *b)
{
    float d[4];
    float h;

    _SubVector(d, a, b);
    h = d[1];
    d[1] = 0.0f;
    h += -VectorLength(d) * (stage_no == 86 || stage_no == 3 || stage_no == 46 ? 2.5f : 0.5f);
    return clampUnit(h * 0.005f);
}

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of prim_DispWireSphere do not fit the prototype in Primitive.h */
extern void prim_DispWireSphere(float a3, void *a0, int a1, int a2);

/* reconstruction: the flight-limit marker colour (R, G, B, A), the first of
   the four colour records at the head of commonact's .data colour run */
static int flyLimitCol[4] = {128, 192, 255, 128};

typedef union {
    float f[4];
    long long ll[2];
} FlyPt;

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

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);

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

/* lines 4049-4052: the fly has run for more than 180 seconds */
static inline unsigned char IsFlyTimeOver(int a0)
{
    if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 180 <
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x39C)) {
        return 1;
    }
    return 0;
}

extern int D_0063B234;
extern void ClipCollisionWithField(char *a0);
/* kept local: this TU does not include fieldCollision.h */
extern void ClipCollision(int *self);
/* kept local: no header declares it */
extern void GetRootMotionMatrix(void *m, char *obj);
/* kept local: no header declares it */
extern float GetEnemyFlyXZAccel(int a0);
/* kept local: no header declares it; the ROM passes the position's address */
extern void SetDarkVolumeEffect(float *pos, float size);
/* kept local: flyManager.h leaves FlyLimitInfo to its includer */
extern int GetFlyLimitHeight(void *info, void *pos);
/* "limit" and "%1.1f ": commonact's .sdata run is carved only as far as
   afterCommonBar's literal, so these two short strings stay on the blob's
   labels until the run's other owners are C and it can be carved whole */
extern char D_0063A750[];
extern char D_0063A758[];

/* reconstruction: GetFlyLimitHeight's result, as flyManager.c fills it */
typedef struct {
    float floorY;
    float limitY;
    float limitOfs;
    int flags;
} FlyLimit;

/* reconstruction: the 0xC0-byte ClipWall/ClipFloor work record as the fly
   code reads it (the other views of it in this TU are kept apart for the
   reason given at RopeWallWork).  The vectors are FlyPt: the ROM copies
   FlyStep's initialised record with ld/sd pairs, so the record is 8-byte
   aligned, and its one initialiser element before the radius is what keeps
   gcc from clearing it and storing the radius (mostly_zeros_p). */
typedef struct {
    FlyPt v[7]; /* 0x00 from, 0x10 to, 0x20 the hit position */
    float rad;
    char _74[0x14];
    int wall;
    char _8C[0x8];
    int floor;
    char _98[0x28];
} FlyClip;

/* reconstruction: the clip request at 0x690 of the actor record */
typedef struct {
    int done;
    char _04[0xC];
    FlyClip w;
    int fD0;
    void (*func)();
} FlyClipReq;

void flyCoreLoop(char *a0, char *target, int a2)
{
    char *act = (char *)GOBJ_ACT(a0);
    float lenSq;
    float spd;
    unsigned long stuck = a2 && IsFallStuckOnStep((int)a0, 6, D_0063B234 ? 29 : 30, 3, 600);
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
        emgpos[0] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x8A0);
        emgpos[1] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x8A4);
        emgpos[2] = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x8A8);
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

        inline void RequestFlyClip(FlyClipReq * req, void (*func)())
        {
            req->func = func;
            req->w.rad = 50.0f;
            CopyVector(req->w.v[0].f, mat[3]);
            CopyVector(req->w.v[1].f, root);
            req->fD0 = 0;
            RequestClipCollision((int *)req);
        }

        inline void FlyStep(void)
        {
            if (needInit) {
                RequestFlyClip((FlyClipReq *)(act + 0x690),
                               a2 ? ClipCollisionWithField : ClipCollision);
                needInit = 0;
            } else if (((FlyClipReq *)(act + 0x690))->done) {
                if (((FlyClipReq *)(act + 0x690))->w.wall ||
                    ((FlyClipReq *)(act + 0x690))->w.floor) {
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
                RequestFlyClip((FlyClipReq *)(act + 0x690),
                               a2 ? ClipCollisionWithField : ClipCollision);
            }
            {
                FlyLimit info;

                if (GetFlyLimitHeight(&info, mat[3])) {
                    if (D_0063B234) {
                        int save = D_0063B13C;

                        debugDispFlyLimit(mat[3], info.limitY, info.floorY);
                        D_0063B13C = 1;
                        debug_Printf(10, 160, 0xFFFFFF00, "[%s] %4d %4d %4d", D_0063A750,
                                     (int)info.floorY, (int)info.limitY, (int)info.limitOfs);
                        D_0063B13C = save;
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
                            SetMotionDirection((char *)a0, dir);
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
                        if (D_0063B234) {
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
                    if (D_0063B234) {
                        static int col[4] = {0, 0, 128, 128};
                        debugDispSphere(mat[3], col, 100.0f);
                    }
                }
            }
        }

        *(int *)((char *)GOBJ_SUB(a0) + 0x3C0) = a2;
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
                root[1] += GOBJ_SUB(target)->f_270;
                if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] < landCnt++ || !landed) {
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
            if (D_0063B234) {
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
        /* Local debug switch, off. What the bytes pin: flyCoreLoop reached
           gcse with 796 to 803 real insns (802 with this block, 791 without
           it), the extra insns sit in fly-only code and are gone from the
           final words, and no named declaration was added (the listing's
           numbered nested names). A switch set to 0 outside the loop is
           exactly that: cse cannot carry the constant across the loop label,
           gcse's last constant propagation folds the test and the next jump
           pass deletes the guarded call. The listing leaves listing rows
           4345 to 4350 code-free here. What the bytes cannot pin: the text,
           the switch's name and what the guarded line printed; the print
           follows emergencyCheck's own "%1.1f " distance print. */
        if (dbg) {
            debug_StdPrintfDummy(D_0063A758, lenSq);
        }
        if (stuck) {
            int completeEmergency(void)
            {
                if (D_0063B234) {
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
                            if (D_0063B234) {
                                debug_StdPrintfDummy(D_0063A758, d);
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
                    if (D_0063B234) {
                        debug_StdPrintfDummy("EMERGENCY CHECK %d(%d): MAX: %f\n", cnt114, ringcnt,
                                             mx);
                    }
                    if (ringcnt >= 5 && mx < 10000.0f) {
                        debug_StdPrintfDummy("\x1b[36mEMERGENCY WITH NO MOVE\x1b[m\n");
                        flags |= 2;
                        return 1;
                    }
                    if (D_0063B234 == 0 && IsFlyTimeOver((int)a0)) {
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
            if (a2 && ((int)(*(unsigned long long *)(act + 0x20) >> 21) & 1) == 0 &&
                emergencyCheck()) {
                SetFlyLimit((int)a0);
                stuck = 1;
            }
        }
        _ScaleVectorXYZ((char *)GOBJ_SUB(a0) + 0x130, (char *)GOBJ_SUB(a0) + 0x130, 0.92f);
        if (((int)(*(unsigned long long *)(act + 0x20) >> 21) & 1) == 0) {
            FlyPt v = {{0.0f, 0.0f,
                        stage_no == 86 || stage_no == 3 || stage_no == 46
                            ? 3.0f
                            : (a2 ? GetEnemyFlyXZAccel((int)a0) : 1.0f),
                        0.0f}};

            _ApplyMatrix(&v, mat, &v);
            v.f[1] = 0.0f;
            _AddVectorXYZ((char *)GOBJ_SUB(a0) + 0x130, (char *)GOBJ_SUB(a0) + 0x130, &v);
            GOBJ_SUB(a0)->f_134 += acc * 2.0f;
        }
        if ((stage_no == 86 || stage_no == 3 || stage_no == 46) &&
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10 < cnt104) {
            SetFlyLimit((int)a0);
            stuck = 1;
        }
        *(unsigned long long *)(act + 0x18) =
            (*(unsigned long long *)(act + 0x18) & ~(1ULL << 57)) | (stuck << 57);
        _ACTWait(1);
        cnt114++;
        cnt104++;
    }
}

extern int D_0063B234;
/* kept local: this TU's uses of IsEnemyBrainToGenerator do not fit the prototype in enemy_act.h */
extern int IsEnemyBrainToGenerator(volatile int a0, char **gen);
/* kept local: this TU's uses of IsEnemyBrainToBoy do not fit the prototype in enemy_act.h */
extern int IsEnemyBrainToBoy(volatile int a0);
/* kept local: this TU's uses of SetEnemyFootPrintSwitch do not fit the prototype in enemy.h */
extern void SetEnemyFootPrintSwitch();

typedef struct {
    char _0[0x5F8];
    int f5F8;
} FlyCtlJ;

void actCommonFly(volatile int a0)
{
    char *s = (char *)*(int *)(a0 + 0x164);
    char *target;
    char *gen = 0;

    ((ActFlagJ *)(s + 0x18))->ll &= ~(1ULL << 57);
    ((ActFlagJ *)(s + 0x18))->p = (void *)actAfterFly;

    ((FlyCtlJ *)(char *)GOBJ_SUB(a0))->f5F8 = 0;

    if (IsEnemyBrainToGenerator(a0, &gen)) {
        target = gen;
    } else if (IsEnemyBrainToBoy(a0) && D_00639EA4 != 0) {
        target = D_00639EA4;
    } else if (D_00639EA8 != 0) {
        target = D_00639EA8;
    } else if (D_00639EA4 != 0) {
        target = D_00639EA4;
    } else {
        target = 0;
    }

    SetEnemyFootPrintSwitch(a0, 0);

    flyCoreLoop(a0, target,
                (D_00639EA8 != 0 && GOBJ_ACT(D_00639EA8)->unk34 == 0x6F &&
                 GOBJ_ACT(D_00639EA8)->f_144 == a0) ||
                    D_0063B234 != 0);
}

/* kept local: this TU's uses of GetDifferenceFromWallUpperField do not fit the prototype in motionManager2.h */
extern float GetDifferenceFromWallUpperField(void *a0, int node);
/* kept local: this TU's uses of GetDifferenceFromLastField do not fit the prototype in motionManager2.h */
extern float GetDifferenceFromLastField(void *a0, int node);
/* kept local: this TU's uses of GetDifferenceFromWallUpperPlane do not fit the prototype in motionManager2.h */
extern float GetDifferenceFromWallUpperPlane(void *a0, int node);
/* kept local: this TU's uses of GetDifferenceFromWallLowerPlane do not fit the prototype in motionManager2.h */
extern float GetDifferenceFromWallLowerPlane(void *a0, int node);
/* kept local: this TU's uses of _DistSqGV do not fit the prototype in gv.h */
extern float _DistSqGV(void *a, void *b);

typedef struct {
    char _0[0x290];
    int f290;
    int f294;

    union {
        unsigned long long ll;
        int i[2];
    } f298;
} LadderWork;

typedef struct {
    char _0[0x150];
    int f150;
    char _154[0x40];
} LadMotRec;

/* the motion table is an array of LadMotRec; this TU's other members declare
   the symbol as char[], so it is indexed here through a one-member array view */
typedef struct {
    LadMotRec m[1];
} LadMotTbl;

#define LADW ((LadderWork *)*(int *)(*(int *)(a0 + 0x164) + 0x680))

void actCommonLadder(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int mot = *(int *)((char *)s + 0x3C);
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

    if (*(float *)((char *)s + 0x57C) != 0.0f) {
        pos[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
        pos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
        pos[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
        pos[0] = *(float *)((char *)s + 0x570);
        pos[2] = *(float *)((char *)s + 0x578);
        *(float *)((char *)s + 0x57C) = 0.0f;
    }
    LADW->f290 = 0;
    LADW->f294 = 0;
    LADW->f298.ll &= ~1ULL;
    LADW->f298.ll &= ~2ULL;
    LADW->f298.ll &= ~4ULL;
    if (a0 == (int)D_00639EA4) {
        GOBJ_ACT(a0)->f_1DA = 1;
    }
    if (mot == 0x7F || mot == 0x80 || mot == 0x7B) {
        while (1) {
            if (a0 == (int)D_00639EA4 && GOBJ_SUB(a0)->f_4AC > 40.0f) {
                break;
            }
            if (((LadMotTbl *)D_0055FE58)->m[GOBJ_SUB(a0)->f_4A0].f150 == 1) {
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
        if (s->f_38 == 0xFFFFFFFF && ((int)((long long)LADW->f298.ll >> 2) & 1)) {
            ACTSendMailCorrect((char *)a0, 0x8E);
            if (a0 != (int)D_00639EA4) {
                ACTSendMailCorrect((char *)a0, 0x8F);
            }
        }
        if (a0 == (int)D_00639EA4 && D_00639EA8 != 0 && GOBJ_ACT(D_00639EA8)->unk34 == 0x26) {
            if (_DistSqGV(test_CURRENTROOT((void *)a0), test_CURRENTROOT(D_00639EA8)) < 3600.0f) {
                ACTSendMailCorrect((char *)a0, 0x31);
            }
        }
        if (a0 == (int)D_00639EA4 || a0 == (int)D_00639EA8) {
            pos[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
            pos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            pos[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
            for (o = (char *)isysGObjSearchFromObjKindID_begin(4); o != 0;
                 o = (char *)isysGObjSearchFromObjKindID_next(o)) {
                if (*(int *)(o + 0x16C) != 0) {
                    if (GOBJ_ACT(o)->unk34 == 0x26 &&
                        _DistSqGV(pos, test_CURRENTROOT(o)) < 6400.0f) {
                        ACTSendMailCorrect((char *)a0, 0x31);
                        break;
                    }
                }
            }
        }
        _ACTWait(1);
    }
}

/* inline tail members defined where the listing puts them (4761..4838 and,
   after actCommonEdgeHang, 4967..4994): their strings emit here, between the
   flyCoreLoop unit's and funcCommonBeginReady's, as the ROM's .rodata has
   them, while their code still emits at the end of the object */
inline void actCommonCliffdown(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonCliffdown\n");
    SetMotionDirection(a0, (char *)s + 0x4C0);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonShoal(volatile int a0)
{
    debug_StdPrintfDummy("act main shoal\n");
    _ACTWait(0);
}

inline void actCommonSwim(volatile int a0)
{
    debug_StdPrintfDummy("enter actCommonSwim\n");
    for (;;) {
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of SetMotionDirectionWithLimit do not fit the prototype in motionManager2.h */
extern void SetMotionDirectionWithLimit(void *a0, float *dir, float lo, float hi);

inline void actCommonDodge(volatile int a0)
{
    float dir[4];
    int id = 0;
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonDodge\n");
    if (*(int *)(a0 + 0xC) == 1) {
        ACTSearchEnemy((void *)a0, &id, dir);
    } else {
        _OrientXZGV((char *)s + 0x120, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, (char *)s + 0x120);
    }
    while (1) {
        if (id != 0) {
            SetMotionDirectionWithLimit((void *)a0, dir, 10.0f, 90.0f);
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonGuard(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actCommonGuard\n");
    SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
    if (*(int *)(a0 + 0xC) == 4) {
        EBRAIN_SEND_MES((void *)a0, 6);
        ACTGame_LwsEffect_Guard((void *)a0);
    }
    iosOmSendMail(D_00639EA4, 0x11C, a0);
    if (*(int *)((char *)s + 0xD8) == 0x11A) {
        ACTSetPositionWithFitting((void *)a0, (float *)test_CURRENTROOT((void *)a0));
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

#undef LADW

extern const StgPre D_005F5D50[];

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    int _80;
    char _84[0x04];
    int _88;
    int _8c;
    char _90[0x04];
    int _94;
    int _98;
    char _9c[0x24];
} EdgeHangWork;

void actCommonEdgeHang(volatile int a0)
{
    EdgeHangWork work;
    float p1[4];
    float p2[4];

    ACTAdjustPlane(a0, *(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x8B0);
    while (1) {
        if (CheckWallAttributeEdegWall((void *)a0) == 0) {
            ACTSendMailCorrect((char *)a0, 0xE2);
        }
        if (-GOBJ_SUB(a0)->f_5E8 > 250.0f) {
            ACTSendMailCorrect((char *)a0, 0x18);
        }
        if (D_005F5D50[stage_no].flag2) {
            memset(&work, 0, 0xC0);
            GetSkeltonPosition((float *)&work, (char *)a0, 0x2C);
            GetSkeltonPosition(p1, (char *)a0, 0x33);
            GetSkeltonPosition(p2, (char *)a0, 0x2F);
            sceVu0AddVector((char *)&work + 0x10, p1, p2);
            sceVu0ScaleVector((char *)&work + 0x10, (char *)&work + 0x10, 0.5f);
            ClipFloor(&work);
            if (work._94 != 0) {
                ACTSendMailCorrect((char *)a0, 0xE2);
            }
        }
        _ACTWait(1);
    }
}

inline void motCommonHangNone(volatile int a0)
{
    debug_StdPrintfDummy("enter motCommonHang None\n");
    _ACTWait(0);
}

inline void motCommonHangWall(volatile int a0)
{
    debug_StdPrintfDummy("enter motCommonHang Wall\n");
    _ACTWait(0);
}

inline void motCommonHangCliff(volatile int a0)
{
    debug_StdPrintfDummy("enter motCommonHang Cliff\n");
    _ACTWait(0);
}

inline void motCommonNull(volatile int a0)
{
    debug_StdPrintfDummy("enter motCommonNull\n");
    for (;;) {
        _ACTWait(1);
    }
}

extern char D_0063A760[];
extern char D_0063A768[];

void funcCommonBeginReady(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->f_E0 |= 1;
    debug_StdPrintfDummy("ready begin %s to %s\n", a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}

void funcCommonEndReady(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->f_E0 |= 2;
    debug_StdPrintfDummy("ready end %s to %s\n", a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}

void funcCommonEndExec(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->f_E0 |= 8;
    debug_StdPrintfDummy("exec end %s to %s\n", a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}

void funcCommonError(char *a0, int a1, char *a2)
{
    GOBJ_ACT(a0)->f_E0 |= 0x10;
    debug_StdPrintfDummy("????error %s to %s\n", a2 == D_00639EA4 ? D_0063A760 : D_0063A768,
                         a0 == D_00639EA4 ? D_0063A760 : D_0063A768);
}

typedef struct {
    char _0[0x18C];
    unsigned int f18C;
    char _190[0x04];
} MotRecSm;

int SetMotionDirectionSmooze(int a0, float *dir, float s)
{
    float v[4];
    Act *sub = GOBJ_ACT(a0);
    int ret = 0;
    int r;

    if (s < 0.0f) {
        return 0;
    }
    s = s * 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    if (dir[0] == 0.0f && dir[1] == 0.0f && dir[2] == 0.0f) {}
    if ((((MotRecSm *)(D_0055FE58 + GOBJ_SUB(a0)->f_4A0 * 0x194))->f18C >> 6) & 1 &&
        *(long long *)(*(char **)((char *)sub + 0x688) + 0x900) == 0x1A00000005LL) {
        s = 30.0f;
    }
    if ((int)(*(unsigned long long *)((char *)sub + 0x20) >> 33) & 1) {
        s = *(float *)(*(char **)((char *)sub + 0x688) + 0x344);
    }
    r = _RotyGV(test_CURRENTORIENT((char *)a0), dir);
    if ((float)(r < 0 ? -r : r) < s) {
        ret = 1;
        v[0] = dir[0];
        v[1] = dir[1];
        v[2] = dir[2];
    } else if (r > 0) {
        v[0] = ((float *)test_CURRENTORIENT((char *)a0))[0];
        v[1] = ((float *)test_CURRENTORIENT((char *)a0))[1];
        v[2] = ((float *)test_CURRENTORIENT((char *)a0))[2];
        _ApplyRyGV(v, -s * 3.1415927f / 180.0f);
    } else {
        v[0] = ((float *)test_CURRENTORIENT((char *)a0))[0];
        v[1] = ((float *)test_CURRENTORIENT((char *)a0))[1];
        v[2] = ((float *)test_CURRENTORIENT((char *)a0))[2];
        _ApplyRyGV(v, s * 3.1415927f / 180.0f);
    }
    SetMotionDirection(a0, v);
    return ret;
}

extern char D_005577F4[];
extern char D_005D1278[];
extern char D_0055FF18[];
extern void *D_00639EA0;

typedef struct {
    char _0[0xC2];
    short fC2;
} MotNameRecDP;

typedef struct {
    char _0[0x186];
    short f186;
} MotRecDP;

void _ACTDebugPrint(char *a0)
{
    char *sub;
    char *w;

    if (a0 == 0) {
        return;
    }
    sub = *(char **)(a0 + 0x164);
    if (sub == 0) {
        return;
    }
    w = (char *)GOBJ_SUB(a0) + 0x470;
    if (w == 0) {
        return;
    }
    if (D_0063B13C & 1) {
        debug_Printf(30, 90, 0xFFFFFFF, " ori  = [%s]\n", D_005D1278 + *(int *)(w + 0xD0) * 32);
        if (D_0063B13C & 1) {
            debug_Printf(30, 100, 0xFFFFFFF, " mot  = [%s]\n",
                         D_0055FF18 + GOBJ_SUB(a0)->f_4A0 * 0x194);
            if (D_0063B13C & 1) {
                debug_Printf(30, 110, 0xFFFFFFF, " mode = [%s]\n",
                             D_005577F4 + *(int *)(sub + 0x34) * 0x50);
                if (D_0063B13C & 1) {
                    debug_Printf(30, 120, 0xFFFFFFF, "frame = [%f]\n", GOBJ_SUB(a0)->f_4AC);
                    if (D_0063B13C & 1) {
                        debug_Printf(
                            30, 130, 0xFFFFFFF, "maxry = [%d]\n",
                            a0 == D_00639EA8 && D_00639EA0 != 0
                                ? ((MotNameRecDP *)(D_0055FF18 + GOBJ_SUB(a0)->f_4A0 * 0x194))->fC2
                                : ((MotRecDP *)(D_0055FE58 + GOBJ_SUB(a0)->f_4A0 * 0x194))->f186);
                        if (D_0063B13C & 1) {
                            debug_Printf(30, 140, 0xFFFFFFF, " life = [%d]\n",
                                         (int)*(float *)(sub + 0x1E0));
                            if (D_0063B13C & 1) {
                                debug_Printf(30, 150, 0xFFFFFFF, "   dw = [%d] [%d]\n",
                                             (int)*(float *)(*(char **)(sub + 0x130) + 0x138),
                                             (int)-*(float *)(*(char **)(sub + 0x130) + 0x130));
                                if (D_0063B13C & 1) {
                                    debug_Printf(30, 160, 0xFFFFFFF, "   dc = [%d] [%d]\n",
                                                 (int)*(float *)(*(char **)(sub + 0x130) + 0x114),
                                                 (int)*(float *)(*(char **)(sub + 0x130) + 0x110));
                                    if (D_0063B13C & 1) {
                                        debug_Printf(30, 170, 0xFFFFFFF, "wattr = [%x]\n",
                                                     GOBJ_SUB(a0)->f_5F4);
                                        if (D_0063B13C & 1) {
                                            debug_Printf(
                                                30, 180, 0xFFFFFFF, "bttype= [%d]\n",
                                                *(int *)(*(char **)(*(char **)(a0 + 0x164) +
                                                                    0x680) +
                                                         0x1EC));
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

void ACTSendMailCorrect(char *a0, int a1)
{
    Act *s = GOBJ_ACT(a0);
    if ((a1 == 0xB5 || a1 == 0xBA) && *(int *)(a0 + 0xC) == 1) {
        long long f = *(long long *)((char *)s + 0x488);
        if (((int)(f >> 5) & 1) && ((int)(*(long long *)((char *)s + 0x498) >> 5) & 1)) {
            a1 = 0xB6;
        } else if ((int)(f >> 3) & 1) {
            a1 = ((int)(*(long long *)((char *)s + 0x498) >> 3) & 1) ? 0xB7 : a1;
        }
    }
    iosOmSendMail(a0, a1, (int)a0);
}

extern int CurrentTargetGObj;

typedef struct {
    char _0[0x190];
    unsigned int f190;
    char _194[0];
} MtMotRec;

void _ACTCommonMailTest(char *self, int a1, int a2, int a3)
{
    char *s;
    int ret = 0;
    unsigned int m;

    s = *(char **)(self + 0x164);
    if (self == D_00639EA4) {
        if (CurrentTargetGObj == 1 ? (*(int *)(s + 0x2E4) & 8) != 0
                                   : (*(int *)(s + 0x2E0) & 8) == 0) {
            handoff_heroin();
        }
    }
    m = *(unsigned int *)(s + 0x34);
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
        if (self == D_00639EA4 || self == D_00639EA8) {
            ret = 1;
        }
        break;
    case 29:
        ret = self == D_00639EA8;
        break;
    case 15:
    case 20:
    case 21:
        ret = self == D_00639EA4;
        break;
    }
    if ((((MtMotRec *)D_0055FE58)[GOBJ_SUB(self)->f_4A0].f190 >> 1) & 1) {
        ret = 1;
    }
    if (ret) {
        if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) + 45) < 91) {
            ACTSendMailCorrect(self, 0x14C);
        }
        if (0.1f < *(float *)(s + 0x34C) && !((unsigned int)(*(int *)(s + 0x340) + 134) < 269) &&
            !(*(int *)(s + 0x34) == 3 && ((int)(*(unsigned long long *)(s + 0x18) >> 44) & 1))) {
            ACTSendMailCorrect(self, 0x14D);
            if (((int)(*(unsigned long long *)(s + 0x20) >> 18) & 1) &&
                !((int)(*(unsigned long long *)(s + 0x18) >> 44) & 1)) {
                ACTSendMailCorrect(self, 0xBC);
            }
        }
        if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
            ACTSendMailCorrect(self, 0x14E);
        }
        if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
            *(int *)(s + 0x340) < -45) {
            ACTSendMailCorrect(self, 0x14F);
        }
        if (0.1f < *(float *)(s + 0x34C) &&
            (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20)) && !(a2 < 4)) {
            ACTSendMailCorrect(self, 0xB5);
        }
        /* the negated conjunct is the 0xB5 guard's whole predicate, repeated;
           it emits a real (dead) branch, so it is in the shipped code. */
        if (0.1f < *(float *)(s + 0x34C) &&
            !(0.1f < *(float *)(s + 0x34C) &&
              (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20))) &&
            !(a3 < 4)) {
            ACTSendMailCorrect(self, 0xBA);
        }
        if (!(0.1f < *(float *)(s + 0x34C)) && 0 < a1) {
            ACTSendMailCorrect(self, 0xC7);
        }
    }
    if (*(int *)(s + 0x34) == 0x49) {
        if (0.1f < *(float *)(s + 0x34C) &&
            (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20)) && !(a2 < 4)) {
            ACTSendMailCorrect(self, 0xB5);
        }
        /* the negated conjunct is the 0xB5 guard's whole predicate, repeated;
           it emits a real (dead) branch, so it is in the shipped code. */
        if (0.1f < *(float *)(s + 0x34C) &&
            !(0.1f < *(float *)(s + 0x34C) &&
              (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20))) &&
            !(a3 < 4)) {
            ACTSendMailCorrect(self, 0xBA);
        }
    }
}

int E3_LeverCheck(char *a0)
{
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)test_CURRENTORIENT(*(char **)((char *)GOBJ_SUB(a0) + 0x180)) + 0x0);
    buf[1] = *(float *)((char *)test_CURRENTORIENT(*(char **)((char *)GOBJ_SUB(a0) + 0x180)) + 0x4);
    buf[2] = *(float *)((char *)test_CURRENTORIENT(*(char **)((char *)GOBJ_SUB(a0) + 0x180)) + 0x8);
    _ApplyRyGV(buf, -1.5707964f);
    return _RotyGV(test_CURRENTORIENT(a0), buf) < 0 ? -_RotyGV(test_CURRENTORIENT(a0), buf) < 0x2D
                                                    : _RotyGV(test_CURRENTORIENT(a0), buf) < 45;
}

extern void afterCommonCarry(volatile int a0);
extern SlowrunRec D_002ADD60[];
extern char D_0063A770[];

typedef struct {
    int _0[9];
    char name[0x20];
    int f44;
    int f48;
    unsigned int b0 : 1;
    unsigned int _b1 : 5;
    unsigned int b6 : 1;
    unsigned int _b7 : 25;
} CarryRec;

extern CarryRec D_005577D0[];

typedef struct {
    char _0[0x18C];
    unsigned char f18C;
    char _18D[7];
} CarryMot;

typedef struct {
    int mot;
    int req;
} BecPair;

extern BecPair D_005D3DF8[];

static __inline__ unsigned char requestBecarryMotion(char *self, int mot, int wait, int n)
{
    char *sub = *(char **)(self + 0x164);
    BecPair *tbl = D_005D3DF8;
    BecPair *end = tbl + 31;
    BecPair *p;
    int save0;
    int save1;

    for (p = tbl; p != end; p++) {
        if (p->mot == mot) {
            break;
        }
    }
    if (p != end) {
        save0 = D_002ADD60[n].w[2];
        save1 = D_002ADD60[n].w[4];
        D_002ADD60[n].w[2] = p->req;
        D_002ADD60[n].w[4] = wait;
        SetMotionRequest(self, 268, *(MotOriReq *)(sub + 0x620));
        D_002ADD60[n].w[2] = save0;
        D_002ADD60[n].w[4] = save1;
        return 1;
    }
    return 0;
}

void actCommonBecarry(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    int cur = -1;
    char *g;
    int old;
    unsigned char done;
    unsigned long long fl;

    g = *(char **)(s + 0x144);
    ACTGameCollisionOff((volatile int *)a0);
    ((ActFlagJ *)(s + 0x18))->p = (void *)afterCommonBecarry;
    ((ActFlagJ *)(s + 0x18))->ll &= ~(1ULL << 46);
    _ACTWait(1);
    while (1) {
        _ACTCharStatus_Set((char *)a0, 9, -1.0f, 0);
        old = cur;
        cur = *(int *)(*(char **)(g + 0x15C) + 0x4A0);
        if (old != cur) {
            done = requestBecarryMotion(
                (char *)a0, cur, (*(int *)(*(char **)(g + 0x164) + 0x34) == 103) ? 30 : 0, 2118);
            if (!done) {
                ((ActFlagJ *)(s + 0x18))->ll |= (1ULL << 46);
            }
        }
        if (6 <= *(int *)(s + 0x4C)) {
            if (D_005577D0[*(int *)(*(char **)(g + 0x164) + 0x34)].b0 ||
                (fl = ((CarryMot *)D_0055FE58)[*(int *)(*(char **)(g + 0x15C) + 0x4A0)].f18C,
                 fl >> 7)) {
                afterCommonCarry((int)g);
                debug_StdPrintfDummy("girl becarry error");
            }
        }
        if (D_005577D0[*(int *)(*(char **)(D_00639EA4 + 0x164) + 0x34)].b6 == 0) {
            ACTGame_DisconnectHand();
        }
        if (D_0063B13C & 1) {
            debug_Printf(100, 150, 0xFFFFFFF, (int)D_0063A770,
                         D_0055FF18 + *(int *)(*(char **)(D_00639EA8 + 0x15C) + 0x4A0) * 0x194);
        }
        if (D_0063B13C & 1) {
            debug_Printf(100, 160, 0xFFFFFFF, (int)D_0063A770,
                         D_0055FF18 +
                             *(int *)(*(char **)(*(char **)(s + 0x144) + 0x15C) + 0x4A0) * 0x194);
        }
        if (D_0063B13C & 1) {
            debug_Printf(
                100, 170, 0xFFFFFFF, (int)D_0063A770,
                D_005577D0[*(int *)(*(char **)(*(char **)(s + 0x144) + 0x164) + 0x34)].name);
        }
        _ACTWait(1);
    }
}

typedef struct {
    int w[5];
} IdleRangeRec;

extern IdleRangeRec D_002A7DC8[];

static inline void SetIdleMotionRange(int k, int mot, int mot2)
{
    int n1 = D_002A7DC8[k].w[1];
    int n2 = D_002A7DC8[k].w[2];
    int n3 = D_002A7DC8[k].w[3];
    int n4 = D_002A7DC8[k].w[4];
    int i;

    if (mot != 1147 && mot2 != 1147) {
        D_002ADD60[n1].w[2] = mot;
        D_002ADD60[n2].w[2] = mot2;
        for (i = n3; i < n4; i++) {
            D_002ADD60[i].w[0] = mot;
        }
    }
}

extern int D_0055F7A0[][3];

void subCommonIdle(volatile int a0)
{
    char *s = *(char **)(a0 + 0x164);
    int k = *(int *)(s + 0x48);
    int m0 = D_002A7DC8[k].w[0];
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
        if (D_0055F7A0[i][k] == m0) {
            same++;
        } else {
            break;
        }
    }
    for (i = 9; i < 10; i++) {
        if (D_0055F7A0[i][k] == m0) {
            sameHand++;
        } else {
            break;
        }
    }
    while (1) {
        cur = *(int *)(*(char **)(a0 + 0x15C) + 0x4A0);
        if (((char *)a0 == D_00639EA4 && D_0063AA08 != 0) ||
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x38C) > 0 ||
            ((int)(*(unsigned long long *)(s + 0x20) >> 44) & 1)) {
            timer = 0;
            ACTSendMailCorrect((char *)a0, 180);
        } else if (*(int *)(s + 0x34) != 1 && *(int *)(s + 0x34) != 69) {
            timer = 0;
        } else if ((int)(*(unsigned long long *)(s + 0x18) >> 62) & 1) {
            timer = 0;
            ACTSendMailCorrect((char *)a0, 180);
        } else {
            if ((char *)a0 == D_00639EA4 && ACTGame_FLAG_TETSUNAGI()) {
                base = 9;
                lim = 10;
                n = sameHand;
            } else {
                base = 0;
                lim = 9;
                n = same;
            }
            if (cur == m0) {
                if (!((*(unsigned long long *)(s + 0x20) >> 45) & 1)) {
                    timer = timer + 1;
                }
                if (n > 0) {
                    if (((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 350 / 60 * (n + 1) < timer) {
                        idx = base + n;
                        if (idx >= lim || D_0055F7A0[idx][k] == 1147) {
                            idx = base;
                        }
                        SetIdleMotionRange(k, D_0055F7A0[idx][k], D_0055F7A0[idx][k]);
                        ACTSendMailCorrect((char *)a0, 179);
                    }
                } else {
                    if (((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 3 < timer) {
                        SetIdleMotionRange(k, D_0055F7A0[base][k], D_0055F7A0[base][k]);
                        ACTSendMailCorrect((char *)a0, 179);
                    }
                }
            } else {
                found = -1;
                timer = 0;
                for (j = base; j < lim; j++) {
                    if (cur == D_0055F7A0[j][k]) {
                        found = j;
                    }
                }
                if (found < 0) {
                    timer = 0;
                } else {
                    if (found + 1 < lim) {
                        nxt = D_0055F7A0[found + 1][k];
                    } else {
                        nxt = m0;
                    }
                    if (nxt == 1147) {
                        nxt = m0;
                    }
                    if ((char *)a0 == D_00639EA8 && nxt == m0) {
                        nxt = D_0055F7A0[0][k];
                    }
                    SetIdleMotionRange(k, D_0055F7A0[found][k], nxt);
                    ACTSendMailCorrect((char *)a0, 179);
                }
            }
        }
        _ACTWait(1);
    }
}

void ContinueCorrectPosition(void *obj)
{
    float v[4];

    (*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4))++;
    if (*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4) <=
        *(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB0)) {
        if (obj == D_00639EA8) {
            if (D_0063B13C & 1) {
                debug_Printf(100, 100, 0xFFFFFFF, "timer=%2d/%2d\n",
                             *(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4),
                             *(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB0));
            }
        }
        _InterGV(v, (void *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0x70),
                 (void *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0x90),
                 (float)*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4),
                 (float)(*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB0) -
                         *(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4)));
        SetDirectRootPositionNoFitting(obj, v);
        if (*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB8) == 1) {
            _InterGV(v, (void *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0x80),
                     (void *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xA0),
                     (float)*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4),
                     (float)(*(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB0) -
                             *(int *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB4)));
            sceVu0Normalize(v, v);
            SetMotionDirection(obj, v);
        }
    } else {
        *(long long *)(*(int *)(*(int *)((char *)obj + 0x164) + 0x680) + 0xB8) &=
            0xFFFFFFFEFFFFFFFFLL;
    }
}

void actCommonTurn(volatile int a0)
{
    float q[4];
    float o[4];
    Act *s = GOBJ_ACT(a0);
    char *t = (char *)s + 0x5C0;
    int d;

    while (1) {
        GetRootMotionOrient(q, a0);
        d = _RotyGV((char *)s + 0x5C0, q);
        debug_Arrow(100.0f, test_CURRENTROOT((void *)a0), (char *)s + 0x5C0, 0, 0, 0xFF);
        if (a0 == (int)D_00639EA8) {
            GetSkeltonOrient(o, a0, 1);
            if (_AbsRotyGV(t, o) < 60) {
                if (*(float *)((char *)s + 0x34C) != 0.0f) {
                    ACTSendMailCorrect((char *)a0, 0xF0);
                }
                ACTSendMailCorrect((char *)a0, 0xF1);
            }
        } else {
            if ((d < 0 ? -d : d) < 15) {
                ACTSendMailCorrect((char *)a0, 0xF1);
            }
        }
        switch (*(unsigned int *)((char *)s + 0xD8)) {
        case 0xE7:
        case 0xE9:
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x384) =
                (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
            break;
        case 0xE8:
        case 0xEA:
            *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x388) =
                (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
            break;
        }
        _ACTWait(1);
    }
}

void actCommonBackhand(volatile int a0)
{
    float v[4];
    float dir[4];
    float pos[4];
    int frame;

    _OrientXZGV(dir, test_CURRENTROOT((void *)a0), test_CURRENTROOT(D_00639EA8));
    SetMotionDirection(a0, dir);
    v[0] = ((float *)test_CURRENTORIENT(D_00639EA8))[0];
    v[1] = ((float *)test_CURRENTORIENT(D_00639EA8))[1];
    v[2] = ((float *)test_CURRENTORIENT(D_00639EA8))[2];
    while (1) {
        sceVu0ScaleVector(pos, v, 50.0f);
        sceVu0AddVector(pos, test_CURRENTROOT(D_00639EA8), pos);
        SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, pos, 0.2f);
        if (GOBJ_SUB(a0)->f_4A0 == 0xBD) {
            _OrientXZGV(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT((void *)a0));
            SetMotionDirection(a0, dir);
        }
        /* ROM-proven vestigial: the shipped code still computes this frame
           budget and drops it -- only D_0028F4C0[1]'s load and gcc's
           divide-by-zero trap survive (SRCFILE line 6205), which is
           mechanically unreachable without the division. */
        frame = (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1];
        _ACTWait(1);
    }
}

typedef union {
    int i;
    float f;
} IntFloatSR;

typedef struct {
    char _0[0x182];
    short f182;
    short f184;
    short f186;
    char _188[4];
    unsigned int f18C;
    char _190[4];
} MotRecSR;

void actCommonSlowrun(volatile int a0)
{
    float p[2][4];

    while (1) {
        int i1;
        int i2;

        i1 = GetSkeltonFocusNode(D_00639EA8, (void *)0x16);
        i2 = GetSkeltonFocusNode(D_00639EA4, (void *)6);
        ((IntFloatSR *)p[0])[0].f = *(float *)((i1 << 6) + GOBJ_SUB(D_00639EA8)->f_C + 0x30);
        ((IntFloatSR *)p[0])[1].f = *(float *)((i1 << 6) + GOBJ_SUB(D_00639EA8)->f_C + 0x34);
        ((IntFloatSR *)p[0])[2].f = *(float *)((i1 << 6) + GOBJ_SUB(D_00639EA8)->f_C + 0x38);
        ((IntFloatSR *)p[1])[0].f = *(float *)((i2 << 6) + GOBJ_SUB(D_00639EA4)->f_C + 0x30);
        ((IntFloatSR *)p[1])[1].f = *(float *)((i2 << 6) + GOBJ_SUB(D_00639EA4)->f_C + 0x34);
        ((IntFloatSR *)p[1])[2].f = *(float *)((i2 << 6) + GOBJ_SUB(D_00639EA4)->f_C + 0x38);
        if ((((MotRecSR *)(D_0055FE58 + GOBJ_SUB(D_00639EA8)->f_4A0 * 0x194))->f18C >> 29) & 1) {
            SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, p[0], 0.2f);
        } else {
            SetDirectRootPositionNoFittingWithNodePointXZ((void *)a0, 6, p[0], 0.1f);
        }
        _ACTWait(1);
    }
}

typedef struct {
    char _0[0x14];
    int f14;
} TruckLeverWork;

void actCommonTruckLever(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    char *lev = *(char **)((char *)s + 0x5FC);

    ((TruckLeverWork *)s)->f14 = (int)afterCommonTruckLever;
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            if (GOBJ_SUB(a0)->f_604 != 0) {
                correctLeverHoldPoint((void *)a0, lev);
            }
            if (GOBJ_SUB(a0)->f_600 != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}

extern int D_00639EB8;

void ACT_LAYOUT_GAMEOVER(void)
{
    if (D_00639EB8 == 0) {
        D_00639EB8 = 1;
        lt_switch_layout(62);
    }
}

/* kept local: this TU's uses of AdjustRootPositionToVerticalSidePlaneOfWall do not fit the prototype in motionManager2.h */
extern void AdjustRootPositionToVerticalSidePlaneOfWall(int a0, int a1, float a2);

void ACTAdjustPlane(int a0, int a1)
{
    AdjustRootPositionToVerticalSidePlaneOfWall(a0, a1, 30.0f);
}

inline void ACTAcceptMail(char *a0, int a1)
{
    if (a1 == 0xB1) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3C4) =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
    }
}

inline int _ACTMotDirSmzDirect(char *a0, float *a1)
{
    Act *s = GOBJ_ACT(a0);

    s->f_120 = a1[0];
    s->f_124 = a1[1];
    s->f_128 = a1[2];
    return SetMotionDirectionSmooze(
        (int)a0, a1,
        (float)(a0 == D_00639EA8 && D_00639EA0 != 0
                    ? ((MotRecSR *)(D_0055FE58 + GOBJ_SUB(a0)->f_4A0 * 0x194))->f182
                    : ((MotRecSR *)(D_0055FE58 + GOBJ_SUB(a0)->f_4A0 * 0x194))->f186));
}

inline void WithMailFunc_Idling(char *a0)
{
    Act *s = GOBJ_ACT(a0);
    int k = *(int *)((char *)s + 0x48);
    int mot = GOBJ_SUB(a0)->f_4A0;

    SetIdleMotionRange(k, mot, mot);
}

inline void WithMailFunc_BossDamaged(char *a0)
{
    char *m = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    *(int *)(m + 0x20C) -= 1;
}

inline void WithMailFunc_FallDead(char *a0)
{
    float v[4];
    Sub15C *s = GOBJ_SUB(a0);
    v[0] = *(float *)((char *)s + 0x1D0);
    v[1] = *(float *)((char *)s + 0x1D4);
    v[2] = *(float *)((char *)s + 0x1D8);
    sceVu0Normalize(v, v);
    if ((double)FSqrt(v[0] * v[0] + v[2] * v[2]) > 0.3) {
        v[1] = 0.0f;
        sceVu0Normalize(v, v);
        SetMotionDirection(a0, v);
    }
}

extern char D_00552EA0[];
/* kept local: this TU's uses of EnemySetfAppearAll do not fit the prototype in enemy.h */
extern void EnemySetfAppearAll(void *a0);
/* kept local: this TU's uses of ResetEnemyPositionInfo do not fit the prototype in enemy.h */
extern void ResetEnemyPositionInfo(void *a0);

typedef struct {
    char _0[0x14];
    int f14;
} ReviveSub;

inline void actCommonRevive(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    debug_StdPrintfDummy(D_00552EA0);
    ACTGameCollisionOff(a0);
    ((ReviveSub *)s)->f14 = (int)afterCommonRevive;
    SetDirectRootPositionNoFitting((void *)a0, (char *)s + 0x170);
    EnemySetfAppearAll((void *)a0);
    for (;;) {
        ResetEnemyPositionInfo((void *)a0);
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonReviveAir(volatile int a0)
{
    SetDirectRootPositionNoFitting((void *)a0, *(char **)(a0 + 0x164) + 0x170);
    EnemySetfAppearAll((void *)a0);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xE2);
        _ACTWait(1);
    }
}

extern char D_00552E00[];

inline void actCommonPlay(volatile int a0)
{
    debug_StdPrintfDummy(D_00552E00);
    _ACTWait(0);
}

inline void actCommonOne(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    if (*(int *)((char *)s + 0xD8) == 0x1A0) {
        if (*(int *)((char *)s + 0x138) & 1) {
            s->f_13A = ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 5;
        }
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonDelete(volatile int a0)
{
    _ACTWait(0);
}

/* kept local: this TU's uses of LightTorchOnOfWeapon do not fit the prototype in weapon.h */
extern void LightTorchOnOfWeapon(void *a0);

inline void actCommonCatchFire(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int lit = 0;

    SetMotionDirection(a0, (char *)s + 0x4D0);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOnOfWeapon(*(void **)((char *)s + 0x150));
            lit = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonCatchFireBomb(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int lit = 0;

    SetMotionDirection(a0, (char *)s + 0x4D0);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOn(*(void **)((char *)s + 0x614));
            lit = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonPutFire(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    int lit = 0;

    SetMotionDirection(a0, (char *)s + 0x4E0);
    for (;;) {
        if (GetMotionFrameFlag1((void *)a0) && !lit) {
            LightTorchOn(*(void **)((char *)s + 0x618));
            lit = 1;
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonBoxReverbe(volatile int a0)
{
    _ACTWait(40);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonItem(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonClimb(volatile int a0)
{
    ACTAdjustPlane(a0, *(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x8B0);
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of CompareAttribute do not fit the prototype in fieldCollision.h */
extern int CompareAttribute(unsigned int a, unsigned int b);

typedef struct {
    float x, y, z;
} Vec3f;

inline void actCommonLadderBellow(volatile int a0)
{
    float hit[4];
    float p[4];
    float q[4];
    float dir[4];
    int attr[4];

    while (1) {
        GetSkeltonPosition(p, (char *)a0, 0x2C);
        sceVu0ScaleVector(dir, test_CURRENTORIENT((char *)a0), 50.0f);
        sceVu0AddVector(q, p, dir);
        if (ACTCheckCollis_CI((int)p, (int)q, attr, (char *)hit) != 0) {
            if (CompareAttribute(attr[0], 0x3000) != 0) {
                ACTSendMailCorrect((char *)a0, 0x91);
                *(Vec3f *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3D8) = *(Vec3f *)hit;
            }
            if (CompareAttribute(attr[0], 0x400) != 0) {
                ACTSendMailCorrect((char *)a0, 0x90);
                *(Vec3f *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3CC) = *(Vec3f *)hit;
            }
        }
        ACTSendMailCorrect((char *)a0, 0xE2);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of CheckWallAttribute do not fit the prototype in motionManager2.h */
extern int CheckWallAttribute(void *a0, int a1);

inline void actCommonLadderBellowHang(volatile int a0)
{
    for (;;) {
        if (!CheckWallAttribute((void *)a0, 0x3000) && !CheckWallAttribute((void *)a0, 0x400)) {
            ACTSendMailCorrect((char *)a0, 0xE2);
        }
        _ACTWait(1);
    }
}

inline void actCommonEdge(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0x150);
        if (-GOBJ_SUB(a0)->f_5E8 > 250.0f) {
            ACTSendMailCorrect((char *)a0, 0x18);
        }
        _ACTWait(1);
    }
}

inline void actCommonDodgeJump(volatile int a0)
{
    float buf[4];
    int id = 0;
    Act *s = GOBJ_ACT(a0);

    if (*(int *)(a0 + 0xC) == 1) {
        ACTSearchEnemy((void *)a0, &id, buf);
    } else {
        _OrientXZGV((char *)s + 0x120, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT((void *)a0));
        SetMotionDirection(a0, (char *)s + 0x120);
    }
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonFallDamage(volatile int a0)
{
    if ((char *)a0 == D_00639EA4) {
        brainAddLevelGirl(1000.0f);
    }
    for (;;) {
        if ((char *)a0 == D_00639EA4 && D_00639EA8 != 0) {
            brainSetSpMode();
            iosOmSendMail(D_00639EA8, 0x3D, a0);
        }
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

extern char D_00552E18[];

inline void actCommonDamage(volatile int a0)
{
    debug_StdPrintfDummy(D_00552E18);
    SetMotionDirection(a0, *(char **)(a0 + 0x164) + 0x1C0);
    DamageFunc((char *)a0);
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1E4) == 3) {
        _ACTWait(360);
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonLever2(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);
    char *lev = *(char **)((char *)s + 0x5FC);

    SetDirectRootPositionXZ((void *)a0, (char *)s + 0x5A0);
    actMotDirToWall((char *)a0);
    while (1) {
        if (lev != 0) {
            /* ROM-proven vestigial: an empty guard. SRCFILE line 2443 emits
               exactly this dead volatile re-read and nothing else; retail
               dropped the body (actCommonLever keeps correctLeverHoldPoint
               here). */
            if (GOBJ_SUB(a0)->f_604 != 0) {}
            if (GOBJ_SUB(a0)->f_600 != 0) {
                lever_nego1((void *)a0, lev);
            }
        }
        _ACTWait(1);
    }
}

inline void actCommonRopeTouchWall(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    while (1) {
        if (((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 2 < *(int *)((char *)s + 0x4C)) {
            ACTSendMailCorrect((char *)a0, 0xAA);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of PlumbOrientUpdateChain do not fit the prototype in chain.h */
extern void PlumbOrientUpdateChain(int a0, float *q);

typedef struct {
    char _0[0x18];
    int f18;
} RopeSwingWork;

inline void actCommonRopeSwing(volatile int a0)
{
    float q[4];
    Act *s = GOBJ_ACT(a0);

    LockChainGeo(s->f_190);
    ((RopeSwingWork *)s)->f18 = (int)actAfterForceRopeSwing;
    GetCorrectOrientOfChain(q, (void *)a0);
    *(float *)((char *)s + 0x1A0) = q[0];
    *(float *)((char *)s + 0x1A4) = q[1];
    *(float *)((char *)s + 0x1A8) = q[2];
    PlumbOrientUpdateChain(s->f_190, q);
    _ACTWait(1);
    while (1) {
        switch (CollisCheckInRope((void *)a0, s->f_190)) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0xA8);
            break;
        case 2:
            ACTSendMailCorrect((char *)a0, 0xA7);
            break;
        }
        UnLockChainGeo(s->f_190);
        ChainGeo(s->f_190);
        LockChainGeo(s->f_190);
        SetMotionDirection(a0, q);
        _ACTWait(1);
    }
}

inline void actCommonRopeTurn(volatile int a0)
{
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    int _80;
    char _84[0x04];
    int _88;
    int _8c;
    char _90[0x04];
    int _94;
    int _98;
    char _9c[0x24];
} FloorWork;

static inline int isRopeDownEndOnFloor(char *self)
{
    FloorWork work;
    char *rec = D_0055FE58 + GOBJ_SUB(self)->f_4A0 * 0x194;

    if ((*(unsigned int *)(rec + 0x18C) >> 4) & 1) {
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

inline void actCommonRopeDownEnd(volatile int a0)
{
    while (1) {
        if (isRopeDownEndOnFloor((char *)a0)) {
            ACTSendMailCorrect((char *)a0, 0xA9);
        }
        _ACTWait(1);
    }
}

typedef struct {
    char _0[0x130];
    int f130;
    int f134;
    int f138;
} RopeJumpWork;

inline void actCommonRopeJump(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    *(int *)((char *)s + 0x18) = (int)actAfterRopeJump;
    if (*(int *)((char *)s + 0xD8) == 0xA7) {
        ((RopeJumpWork *)(int)GOBJ_SUB(a0))->f130 = 0;
        ((RopeJumpWork *)(int)GOBJ_SUB(a0))->f134 = 0;
        ((RopeJumpWork *)(int)GOBJ_SUB(a0))->f138 = 0;
    }
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xBD);
        _ACTWait(1);
    }
}

inline void actCommonRopeJumpBefore(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xBD);
        _ACTWait(1);
    }
}

typedef struct {
    char _0[0x18];
    int f18;
} RopeTurnSpWork;

inline void actCommonRopeTurnSpecial(volatile int a0)
{
    Vec4u base;
    float p0[4];
    float p1[4];
    float out[4];

    ((RopeTurnSpWork *)*(char **)(a0 + 0x164))->f18 = (int)afterCommonRopeTurnSpecial;
    base.f[0] = *(float *)((int)GOBJ_SUB(a0) + 0x410);
    base.f[1] = *(float *)((int)GOBJ_SUB(a0) + 0x414);
    base.f[2] = *(float *)((int)GOBJ_SUB(a0) + 0x418);
    while (1) {
        GetCageChainPoint(p0, p1, *(void **)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x400));
        _InterGV(out, p0, p1, base.f[1] - p0[1], p1[1] - base.f[1]);
        out[1] = base.f[1];
        SetChainRootUpdateMode((void *)a0, 3, out);
        _ACTWait(1);
    }
}

inline void actCommonRopeClimbEnd2(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonCornered(volatile int a0)
{
    float v[4];

    sceVu0ScaleVector(v, test_CURRENTORIENT((char *)a0), -1.0f);
    SetMotionDirection(a0, v);
    for (;;) {
        _ACTCharStatus_Set((char *)a0, 3, -1.0f, 0);
        _ACTWait(1);
    }
}

inline void actCommonLookaround(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((char *)a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actCommonTurnWarn(volatile int a0)
{
    float q[4];
    Act *s = GOBJ_ACT(a0);
    int prev = *(int *)((char *)s + 0x40);

    while (1) {
        int d;

        if (*(int *)((char *)s + 0x40) != 0x10D) {
            prev = *(int *)((char *)s + 0x40);
        } else {
            *(int *)((char *)s + 0x130) =
                SetMotionRequest((void *)a0, prev, *(MotOriReq *)((char *)s + 0x620));
        }
        GetRootMotionOrient(q, a0);
        d = _RotyGV(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3F0, q);
        if ((d < 0 ? -d : d) < 0xF) {
            ACTSendMailCorrect((char *)a0, 0xF5);
        }
        _ACTWait(1);
    }
}

inline void actCommonTurnStrict(volatile int a0)
{
    float q[4];
    char *t = *(char **)(a0 + 0x164) + 0x5C0;

    for (;;) {
        int d;

        GetRootMotionOrient(q, a0);
        d = _RotyGV(t, q);
        if ((d < 0 ? -d : d) < 0xF) {
            ACTSendMailCorrect((char *)a0, 0xF4);
        }
        _ACTWait(1);
    }
}

inline void actCommonPPipe(volatile int a0)
{
    _ACTWait(0);
}

typedef struct {
    char _0[0x4C0];
    float f4C0;
    float f4C4;
    float f4C8;
} HandrailNode;

inline void actCommonHandrail(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    ((HandrailNode *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f4C0 =
        *(float *)((char *)s + 0x4B0);
    ((HandrailNode *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f4C4 =
        *(float *)((char *)s + 0x4B4);
    ((HandrailNode *)*(char **)(*(char **)(a0 + 0x164) + 0x688))->f4C8 =
        *(float *)((char *)s + 0x4B8);
    for (;;) {
        _ACTWait(1);
    }
}

inline void actCommonOneWall(volatile int a0)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x14) = (int)afterCommonOneWall;
    _ACTWait(0);
}

/* kept local: this TU's uses of IsThisBoxTruck do not fit the prototype in box.h */
extern int IsThisBoxTruck(void *a0);

inline void motCommonBoxPush(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    *(int *)((char *)s + 0x38) = 1;
    while (1) {
        if (IsThisBoxTruck(*(void **)((char *)s + 0x158)) == 0) {
            SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x530);
        } else {
            actMotDirToWall((char *)a0);
        }
        _ACTWait(1);
    }
}

inline void motCommonBoxPull(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    s->f_38 = -1;
    while (1) {
        if (IsThisBoxTruck(*(void **)((char *)s + 0x158)) == 0) {
            SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x530);
        } else {
            actMotDirToWall((char *)a0);
        }
        _ACTWait(1);
    }
}

inline void motCommonBarPush(volatile int a0)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x38) = 1;
    _ACTWait(0);
}

inline void motCommonBarPull(volatile int a0)
{
    char *g = (char *)a0;
    GOBJ_ACT(g)->f_38 = 0xFFFFFFFFu;
    _ACTWait(0);
}

typedef struct {
    char _0[0x38];
    int f38;
} LadderMotWork;

inline void motCommonLadderUp(volatile int a0)
{
    LadderMotWork *s = (LadderMotWork *)*(char **)(a0 + 0x164);

    while (1) {
        s->f38 = 1;
        switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x290)) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0x89);
        case 2:
            ACTSendMailCorrect((char *)a0, 0x8A);
            break;
        }
        _ACTWait(1);
    }
}

typedef struct {
    char _0[0x38];
    unsigned int f38;
} LadderDownMotWork;

inline void motCommonLadderDown(volatile int a0)
{
    LadderDownMotWork *s = (LadderDownMotWork *)*(char **)(a0 + 0x164);

    while (1) {
        s->f38 = -1;
        switch (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x294)) {
        case 1:
            ACTSendMailCorrect((char *)a0, 0x89);
        case 2:
            ACTSendMailCorrect((char *)a0, 0x8A);
            break;
        }
        _ACTWait(1);
    }
}

inline void motCommonSlip(volatile int a0)
{
    Act *s = GOBJ_ACT(a0);

    while (1) {
        long long f = *(long long *)((char *)s + 0x480);

        if (!((((int)(f >> 16) & 1) && ((int)(*(long long *)((char *)s + 0x490) >> 16) & 1)) ||
              (((int)(f >> 17) & 1) && ((int)(*(long long *)((char *)s + 0x490) >> 17) & 1)))) {
            ACTSendMailCorrect((char *)a0, 0xC7);
        }
        _ACTWait(1);
    }
}

inline void motCommonRopejumpDircorrect(volatile int a0)
{
    float v[4];
    Act *s = GOBJ_ACT(a0);

    v[0] = *(float *)((char *)s + 0x1A0);
    v[1] = *(float *)((char *)s + 0x1A4);
    v[2] = *(float *)((char *)s + 0x1A8);
    if (*(int *)((char *)s + 0xD8) == 0xBE) {
        sceVu0ScaleVector(v, v, -1.0f);
    }
    for (;;) {
        SetMotionDirection(a0, v);
        _ACTWait(1);
    }
}

inline void motCommonRopeTurnSpecialR(volatile int a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT((char *)a0)) / 3.1415927f * 180.0f);
    Act *s = GOBJ_ACT(a0);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base + deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(a0, dir);
        if (i++ % wait == 0 && !(0.1f < *(float *)((char *)s + 0x34C))) {
            ACTSendMailCorrect((char *)a0, 0xAC);
        }
        deg += 5;
        _ACTWait(1);
    }
}

inline void motCommonRopeTurnSpecialL(volatile int a0)
{
    int i = 0;
    int base = (int)(_GetDirection(test_CURRENTORIENT((char *)a0)) / 3.1415927f * 180.0f);
    Act *s = GOBJ_ACT(a0);
    float dir[4];
    int wait = 18, deg = 0;

    while (1) {
        memset(dir, 0, 16);
        dir[2] = 1.0f;
        _ApplyRyGV(dir, (float)RoundDegGV(base - deg) * 3.1415927f / 180.0f);
        debug_Arrow(200.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        SetMotionDirection(a0, dir);
        if (i++ % wait == 0 && !(0.1f < *(float *)((char *)s + 0x34C))) {
            ACTSendMailCorrect((char *)a0, 0xAC);
        }
        deg += 5;
        _ACTWait(1);
    }
}

extern char D_0063A778[];
/* kept local: this TU's uses of SetSwitchState do not fit the prototype in box.h */
extern void SetSwitchState(int a0, int a1);

inline void motCommonTruckLeverLoop(volatile int a0)
{
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);

    _ACTWait(6);
    SetSwitchState(sw, 0);
    debug_StdPrintfDummy(D_0063A778);
    _ACTWait(0);
}

extern char D_0063A780[];

inline void motCommonTruckLeverPull(volatile int a0)
{
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);
    _ACTWait(30);
    SetSwitchState(sw, -1);
    debug_StdPrintfDummy(D_0063A780);
    _ACTWait(0);
}

extern char D_0063A788[];

inline void motCommonTruckLeverPush(volatile int a0)
{
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);
    _ACTWait(30);
    SetSwitchState(sw, 1);
    debug_StdPrintfDummy(D_0063A788);
    _ACTWait(0);
}

inline void funcCommonRopeBefore(char *a0, int a1, int a2)
{
    GOBJ_ACT(a0)->f_190 = a2;
}

extern char D_00552D78[];
/* kept local: this TU's uses of ReleaseChain do not fit the prototype in chain.h */
extern void ReleaseChain(int a0, int a1);

inline void afterCommonRope(volatile int a0)
{
    int s = *(int *)(a0 + 0x164);
    debug_StdPrintfDummy(D_00552D78);
    ReleaseChain(*(int *)(s + 0x190), a0);
    {
        int g = a0;
        *(int *)(s + 0x194) = *(int *)(s + 0x190);
        GOBJ_SUB(g)->f_420 = 0;
    }
}

inline void extraCommonNull(volatile int a0)
{
    for (;;) {
        _ACTWait(1);
    }
}

extern int D_0063A61C;

inline void extraCommonCall(volatile int a0)
{
    if (D_00639EA8) {
        iosOmSendMail(D_00639EA8, 0x44, D_0063A61C);
    }
    for (;;) {
        _ACTWait(1);
    }
}

extern int girlcalled;

inline void funcCommonWayOn(void *a0)
{
    if (a0 == D_00639EA8) {
        girlcalled = 1;
    }
}

inline void funcCommonSofaWakeup(char *a0)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x250) = 0;
}

inline int _ACTMotReqResult(char *a0, int a1)
{
    Act *s = GOBJ_ACT(a0);
    char *r = SetMotionRequest(a0, a1, *(MotOriReq *)((char *)s + 0x620));
    *(char **)((char *)s + 0x130) = r;
    return *(int *)(r + 0xC) != 0;
}

/* StartCorrectPosition and IsCorrectPosition precede test_CURRENTORIENT and
   test_CURRENTROOT, as the listing has them (5928 and 5987 before 6245 and
   6259): a call after an inline's definition is inlined, and the ROM calls */
typedef union {
    unsigned long long ll;
    int i;
} CorrFlag;

inline void StartCorrectPosition(char *a0, float *pos, float *dir, int mode, float t)
{
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x70) =
        ((float *)test_CURRENTROOT(a0))[0];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x74) =
        ((float *)test_CURRENTROOT(a0))[1];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x78) =
        ((float *)test_CURRENTROOT(a0))[2];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x80) =
        ((float *)test_CURRENTORIENT(a0))[0];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x84) =
        ((float *)test_CURRENTORIENT(a0))[1];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x88) =
        ((float *)test_CURRENTORIENT(a0))[2];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x90) = pos[0];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x94) = pos[1];
    *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0x98) = pos[2];
    if (dir != 0) {
        *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xA0) = dir[0];
        *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xA4) = dir[1];
        *(float *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xA8) = dir[2];
    }
    *(int *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB0) = (int)t;
    *(int *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB4) = 0;
    ((CorrFlag *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB8))->i = mode;
    ((CorrFlag *)((char *)*(int *)(*(int *)(a0 + 0x164) + 0x680) + 0xB8))->ll |= (1ULL << 32);
}

inline int IsCorrectPosition(char *a0)
{
    unsigned long long v = *(unsigned int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xBC);
    return (int)v & 1;
}

/* .bss, owned by commonact.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order: the orient and the position
   these two accessors hand back. */
static char commonOrient[16];

static float commonPos[4];

/* kept local: this TU's uses of _GetMotionDirection do not fit the prototype in motionManager2.h */
extern void _GetMotionDirection(void *a0, void *a1);

inline void *test_CURRENTORIENT(char *a0)
{
    if (a0 != D_00639EA4 && a0 != D_00639EA8 && *(int *)(a0 + 0xC) != 4) {
        GetRootOrient(commonOrient, a0);
        return commonOrient;
    }
    {
        char *p = *(char **)(a0 + 0x164) + 0xF0;
        _GetMotionDirection(p, a0);
        return p;
    }
}

extern float D_0063A790[];

inline void *test_CURRENTROOT(void *a0)
{
    float buf[4];
    float *p;
    float v;

    switch (*(int *)((char *)a0 + 0xC)) {
    case 1:
    case 2:
    case 4:
        p = (float *)*(char **)((char *)a0 + 0x164);
        p = (float *)((char *)p + 0x100);
        GetRootPosition(p, a0);
        return p;
    case 0x2C:
        if (GetCageChainPoint(commonPos, buf, a0) == 0) {
            v = D_0063A790[0];
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
    D_002ADD60[a0].w[2] = a1;
}

inline int FloorIsTruck(void *a0)
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
    int local[4];
    sceVu0ScaleVector(local, a1, -1.0f);
    SetMotionDirection(a0, local);
}

inline void ACTMotDirToWall(char *a0)
{
    int local[4];
    sceVu0ScaleVector(local, *(char **)(a0 + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(a0, local);
}

inline void SetCorrectOrientOfChain(void *a0)
{
    int local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}

extern char D_00552DA0[];

inline void actAfterForceRope(volatile int a0)
{
    int s = *(int *)(a0 + 0x164);
    if (*(int *)(s + 0x190) == 0) {
        debug_assert(D_00552D90, 0x5FB);
        __assert(D_00552D90, 0x5FB, D_00552DA0);
    }
    UnLockChainGeo(*(int *)(s + 0x190));
}

inline void actAfterForceRopeSwing(volatile int a0)
{
    int s = *(int *)(a0 + 0x164);
    if (*(int *)(s + 0x190) == 0) {
        debug_assert(D_00552D90, 0x675);
        __assert(D_00552D90, 0x675, D_00552DA0);
    }
    UnLockChainGeo(*(int *)(s + 0x190));
}

inline void actAfterRopeJump(volatile int a0)
{
    char *g = (char *)a0;
    *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) |= (1ULL << 31);
}

inline void afterCommonRopeCliff(char *a0)
{
    char *volatile local = a0;
    char *g = *(char **)(D_00639EA4 + 0x15C);
    *(int *)(g + 0x420) = 0;
}

inline void afterCommonRopeTurnSpecial(volatile int a0)
{
    char *g = (char *)a0;
    GOBJ_SUB(g)->f_420 = 0;
}

inline void actAfterDown(volatile int a0)
{
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x37C) =
        ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0x82 / 0x3C;
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

inline void afterCommonStone(volatile int a0)
{
    int g1 = a0;
    int g2 = a0;
    *(int *)(*(int *)(*(int *)(g1 + 0x164) + 0x680) + 0x2A0) = -1;
    *(int *)(*(int *)(*(int *)(g2 + 0x164) + 0x680) + 0x2A4) = 0;
}

inline void afterCommonBox(volatile int a0)
{
    _boxbar_set_sound(a0, 0);
}

extern Blob12 InitialColInfo;

inline void afterCommonBar(volatile int a0)
{
    debug_StdPrintfDummy("reset\n");
    *(Blob12 *)((char *)GOBJ_SUB(a0) + 0x1C0) = InitialColInfo;
    _boxbar_set_sound(a0, 0);
}

inline void actAfterJump(volatile int a0)
{
    char *g = (char *)a0;
    *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) |= (1ULL << 31);
}

inline void actAfterFall(volatile int a0)
{
    int s = *(int *)(a0 + 0x164);
    unsigned long long st = *(unsigned long long *)(s + 0x20) & ~(1ULL << 42);
    unsigned long long fl = *(unsigned long long *)(s + 0x18) & ~(1ULL << 53);
    *(unsigned long long *)(s + 0x18) = fl;
    *(unsigned long long *)(s + 0x20) = st | (1ULL << 31);
}

/* kept local: this TU's uses of SetEnemyFootPrintSwitch do not fit the prototype in enemy.h */
extern void SetEnemyFootPrintSwitch(int a0, int a1);

typedef struct {
    char _0[0x20];
    unsigned long long status;
} FlySub;

inline void actAfterFly(volatile int a0)
{
    FlySub *s = (FlySub *)*(int *)(a0 + 0x164);
    s->status |= 0x200;
    SetEnemyFootPrintSwitch(a0, 1);
    ResetFlyLimit(a0);
}

/* kept local: this TU's uses of ClipWallField do not fit the prototype in fieldCollision.h */
extern void ClipWallField(void *a0);

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

inline int ACTCheckFlagAttack(char *a0)
{
    return GOBJ_ACT(a0)->unk34 == 0xF;
}

typedef struct {
    char _0[0x74];
    int coll;
} BecSub;

inline void afterCommonBecarry(volatile int a0)
{
    SetKidnapInfo(-1, -1);
    ((BecSub *)(int)GOBJ_SUB(a0))->coll = 1;
    ACTGameCollisionOn(a0);
    gflagOff(393);
}

inline void afterCommonTruckLever(volatile int a0)
{
    char *g = (char *)a0;
    SetSwitchState(GOBJ_ACT(g)->f_5FC, 0);
}
