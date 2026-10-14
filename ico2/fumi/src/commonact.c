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

INCLUDE_ASM(ACTSetPositionNoFitting);

INCLUDE_ASM(ACTSetPositionNodeWithFitting);

INCLUDE_ASM(ChangeMailInLadder);

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

INCLUDE_ASM(func_00155B58);

/* the motion each interrupt kind requests, indexed by the kind */
static int intrMotion[392] = {
    0,   0,   0,   0,   0,   0,   105, 105, 55,  0,   1,   0,   0,   0,   0,   196, 197, 0,   0,
    0,   77,  78,  0,   145, 107, 149, 153, 1,   17,  19,  20,  0,   0,   0,   120, 0,   -1,  -1,
    131, 238, -1,  112, 111, 146, 147, 0,   0,   0,   109, 108, 134, 135, 136, 234, 235, 4,   1,
    4,   0,   0,   0,   57,  58,  59,  0,   0,   0,   1,   0,   1,   0,   102, 12,  7,   1,   95,
    1,   0,   103, 104, 15,  13,  1,   85,  92,  1,   0,   0,   0,   1,   1,   0,   0,   0,   1,
    1,   0,   0,   0,   1,   0,   0,   18,  120, 121, 122, 0,   62,  63,  64,  1,   80,  81,  80,
    148, 148, 65,  66,  67,  68,  70,  69,  71,  72,  72,  74,  73,  113, 114, 115, 116, 112, 117,
    105, 112, 137, 137, 78,  177, 178, 179, 180, 181, 139, 115, 116, 182, 184, 183, 186, 185, 176,
    145, 187, 188, 189, 76,  75,  0,   0,   0,   77,  187, 181, 190, 0,   5,   6,   7,   8,   9,
    13,  14,  12,  15,  16,  21,  22,  24,  24,  23,  25,  1,   1,   2,   35,  36,  11,  1,   38,
    38,  39,  46,  45,  45,  47,  44,  43,  106, 131, 155, 7,   0,   153, 1,   154, 155, 147, 52,
    53,  106, 175, 82,  229, 48,  197, 196, 199, 198, 199, 198, 197, 196, 12,  7,   200, 197, 196,
    200, 200, 0,   60,  61,  1,   12,  1,   0,   230, 106, 0,   0,   0,   238, 238, 231, 26,  238,
    10,  11,  10,  1,   7,   1,   0,   192, 193, 194, 195, 27,  28,  29,  30,  31,  32,  33,  34,
    123, 123, 124, 132, 133, 125, 126, 127, 128, 130, 131, 0,   55,  54,  49,  50,  51,  56,  137,
    138, 117, 150, 151, 55,  55,  118, 119, 55,  105, 105, 110, 106, 85,  86,  87,  86,  88,  89,
    90,  83,  54,  84,  139, 140, 141, 142, 143, 144, 145, 0,   0,   0,   239, 240, 170, 173, 173,
    172, 171, 174, 201, 210, 211, 202, 203, 204, 205, 206, 207, 203, 214, 7,   1,   215, 216, 217,
    217, 218, 219, 220, 221, 222, 224, 225, 156, 157, 158, 156, 157, 158, 159, 160, 160, 161, 161,
    0,   0,   162, 163, 164, 95,  165, 1,   166, 167, 168, 169, 167, 106, 1,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}; /* derived name */

INCLUDE_ASM(ACTRunIntrCorrect);

void WithMailFunc_WayBeginPosError(void *self)
{
    /* disabled in retail: the way-begin-position (WBP) report */
    if (0) {
        debug_StdPrintfDummy("WBP set [with mail]\n");
    }
    ACTWay_SetBeginPositionIllegal(self);
}

INCLUDE_ASM(WithMailFunc_AttackFail);

INCLUDE_ASM(WithMailFunc_AttackRejectInQueen);

void GetCorrectOrientOfChain(void *buf, void *obj);

INCLUDE_ASM(GetCorrectOrientOfChain);

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

INCLUDE_ASM_LIT(afterCommonRope);

INCLUDE_ASM_LIT(actAfterForceRope);

INCLUDE_ASM(actCommonRope);

/* the turn to the chain's corrected orient, which SetCorrectOrientOfChain
   and the rope turns inline */
static inline void setCorrectOrientOfChain(void *self) /* derived name */
{
    float local[4];
    GetCorrectOrientOfChain(local, self);
    SetMotionDirection(self, local);
}

INCLUDE_ASM(motCommonRopeTurnR);

INCLUDE_ASM(motCommonRopeTurnL);

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

INCLUDE_ASM(actCommonRopeClimbEnd1);

typedef union { /* field names derived */
    char *p;
    float *f;
} CagePtr; /* derived name */

INCLUDE_ASM(actCommonRopeCliff);

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

INCLUDE_ASM(TestCageUpDown);

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

INCLUDE_ASM(actCommonLever);

static void EBRAIN_SEND_MES(void *enemy, int mes)
{
    if (enemy && *(int *)((char *)enemy + 0xC) == 4)
        eBrainSendMes(enemy, mes);
}

INCLUDE_ASM_LIT(actCommonPlay);

INCLUDE_ASM(DamageFunc);

INCLUDE_ASM(DownFunc);

INCLUDE_ASM_LIT(actCommonDamage);

INCLUDE_ASM(actCommonDown);

INCLUDE_ASM(actCommonDie);

INCLUDE_ASM(Cling_176);

INCLUDE_ASM(actCommonCling);

INCLUDE_ASM(actCommonSlip);

INCLUDE_ASM(actCommonStoneDead);

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

INCLUDE_ASM_LIT(actCommonRevive);

INCLUDE_ASM(actCommonStone);

INCLUDE_ASM(BoxBarSoundOn);

INCLUDE_ASM(BoxBarSoundOff);

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

typedef struct { /* field names derived */
    char pad0[448];
    int f1C0;
    int f1C4;
    int f1C8;
} BarHold; /* derived name */

INCLUDE_ASM_LIT(afterCommonBar);

INCLUDE_ASM(actCommonBar);

INCLUDE_ASM(funcCommonJumpDircorrect);

INCLUDE_ASM(funcCommonFallDircorrect);

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

INCLUDE_ASM(col_268);

INCLUDE_ASM(col_269);

INCLUDE_ASM(col_270);

INCLUDE_ASM(getLandOffset_265);

INCLUDE_ASM(completeEmergency_280);

INCLUDE_ASM(emergencyCheck_284);

INCLUDE_ASM(flyCoreLoop);

typedef struct { /* field names derived */
    char pad0[1528];
    int f5F8;
} FlyCtlJ; /* derived name */

INCLUDE_ASM(actCommonFly);

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

INCLUDE_ASM(actCommonLadder);

/* inline tail members, defined here: their strings come between the
   flyCoreLoop unit's and funcCommonBeginReady's in .rodata, while their code
   goes to the end of the object */
#undef LADW

INCLUDE_ASM_LIT(actCommonCliffdown);

INCLUDE_ASM_LIT(actCommonShoal);

INCLUDE_ASM_LIT(actCommonSwim);

INCLUDE_ASM_LIT(actCommonDodge);

INCLUDE_ASM_LIT(actCommonGuard);

INCLUDE_ASM(actCommonEdgeHang);

INCLUDE_ASM_LIT(motCommonHangNone);

INCLUDE_ASM_LIT(motCommonHangWall);

INCLUDE_ASM_LIT(motCommonHangCliff);

INCLUDE_ASM_LIT(motCommonNull);

INCLUDE_ASM(funcCommonBeginReady);

INCLUDE_ASM(funcCommonEndReady);

INCLUDE_ASM(funcCommonEndExec);

INCLUDE_ASM(funcCommonError);

INCLUDE_ASM(SetMotionDirectionSmooze);

/* motionOrientManager.h declares none of the motion tables */
extern MotOriName motionOriKind[];

INCLUDE_ASM(_ACTDebugPrint);

INCLUDE_ASM(ACTSendMailCorrect);

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

INCLUDE_ASM_LIT(motCommonTruckLeverLoop);

INCLUDE_ASM_LIT(motCommonTruckLeverPull);

INCLUDE_ASM_LIT(motCommonTruckLeverPush);

INCLUDE_ASM_LIT(test_CURRENTROOT);

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

INCLUDE_ASM(FloorIsTruck);

INCLUDE_ASM(_ACTMotDir_V);

INCLUDE_ASM(ACTMotDirToWall);

INCLUDE_ASM(SetCorrectOrientOfChain);

INCLUDE_ASM(actAfterForceRope);

INCLUDE_ASM(actAfterForceRopeSwing);

INCLUDE_ASM(actAfterRopeJump);

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

INCLUDE_ASM(afterCommonOneWall);

INCLUDE_ASM(ACTCheckFlagAttack);

INCLUDE_ASM(afterCommonTruckLever);
