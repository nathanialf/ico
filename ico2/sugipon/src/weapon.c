#include "debug.h"
#include "box.h"
#include "sugiCommon.h"
#include "weapon.h"
#include "memory.h"
#include "gobj.h"
#include "act-game.h"
#include "DisplayP2O.h"
#include "GifPacket.h"
#include "StageAnimation.h"
#include "enemy.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "lineManager.h"
#include "motionManager2.h"
#include "particleEffect.h"
#include "quaternion.h"
#include "tableSin.h"
#include "torch.h"
#include <libvu0.h>
#include <math.h>
#include <string.h>
#include "Matrix.h"
#include "matrixDrive.h"
#include "main.h"
#include "fieldCollision.h"
#include "ios.h"
#include "sceneManager.h"
#include "DObj.h"
#include "include_asm.h"

static void calcDynamicGeometry(struct GObj *g);

/* The work record InitWeaponGeo and InitDemoQueensSword allocate and the
   template they initialise it from: 176 bytes, 8-aligned.  The fields are the
   ones this file reads. */
typedef struct {       /* field names derived */
    int kind;          /* 0x00: the switch in InitWeaponGeo */
    int state;         /* 0x04: 2 while the weapon falls from a fumble */
    GObj *holder;      /* 0x08: the holding object, 0 when none */
    int holderId;      /* 0x0C: -1 when none */
    float hit[4][4];   /* 0x10: checkHit's positions at 0x20, 0x30, 0x40 */
    int count;         /* 0x50 */
    GObj **objs;       /* 0x54, the torch objects the weapon carries */
    char *buf;         /* 0x58 */
    GObj *sword;       /* 0x5C */
    int fumbleTime;    /* 0x60 */
    int fumbleFrame;   /* 0x64 */
    float fumbleSpeed; /* 0x68 */
    char pad6C[4];
    float fumbleFrom[4];                  /* 0x70 */
    float fumbleTo[4];                    /* 0x80 */
    float fumbleQuat[4];                  /* 0x90 */
    int fumbleSlot;                       /* 0xA0: the drop-table row, 0 to 6 */
    int bladeOn;                          /* 0xA4: the laser blade is out */
    float bladeLength;                    /* 0xA8: the blade's drawn length */
    float bladeTimer;                     /* 0xAC: frames the blade has been growing */
} __attribute__((aligned(8))) WeaponWork; /* derived name */

INCLUDE_ASM(torchOnOfWeaponSE);

INCLUDE_ASM(torchOffOfWeaponSE);

void weaponHitReactionSE(GObj *g);

INCLUDE_ASM(weaponHitReactionSE);

INCLUDE_ASM(weaponFumbleSE);

INCLUDE_ASM(weaponStickSE);

static inline void releaseWeaponHolder(WeaponWork *w) /* derived name */
{
    if (w->holder != 0) {
        w->holder->dobj->ctrl.pickedWeapon = 0;
    }
    w->holderId = -1;
}

void ReleaseWeaponWithFumbleTargetPos(GObj *g, void *pos, void *quat, void *rot, float t)
{
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;

    releaseWeaponHolder(w);
    w->state = 2;
    w->holder = 0;
    if (rot != 0) {
        CopyQuaternion(p->root.itemQuat, rot);
    }
    w->fumbleTime = (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * t);
    w->fumbleFrame = 0;
    GetRootPosition(w->fumbleFrom, g);
    CopyVector(w->fumbleTo, pos);
    CopyQuaternion(w->fumbleQuat, quat);
    w->fumbleSpeed = (w->fumbleTo[1] - w->fumbleFrom[1]) / t - t * 490.0f;
    weaponFumbleSE(g);
}

/* the position vector this function builds and hands on: 8-byte aligned,
   built by aggregate initialisers */
typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(8))) FumbleVec; /* derived name */

static inline int fumbleTargetBlocked(FumbleVec *p) /* derived name */
{
    GObj *o;
    FumbleVec tmp;

    for (o = isysGObjSearchFromObjKindID_begin(17); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        float dx;
        float dz;

        GetRootPosition(&tmp, o);
        dx = tmp.x - p->x;
        if (((dx < 0.0f) ? -dx : dx) <= 50.0f) {
            dz = tmp.z - p->z;
            if (((dz < 0.0f) ? -dz : dz) <= 50.0f) {
                return 1;
            }
        }
    }
    return 0;
}

/* declared here: ico2/omori/src/attackhit.c declares the table with its
   own record and includes weapon.h */
extern WeaponDef weaponKind[];
/* declared here as three rows to a weapon slot, the way it is read; the
   definition (weapon-fumble-def) is the flat row array */
extern FumbleRow weaponFumbleGeo[][3];

#define FUMBLE_ROW(i, w) (&weaponFumbleGeo[(w)->fumbleSlot][i]) /* derived name */

int ReleaseWeaponWithFumbleSequential(GObj *g)
{
    WeaponWork *w = GOBJ_SUB(g)->work;
    FumbleVec a;
    int i;

    for (i = 0; i < 3; i++) {
        a = (FumbleVec){FUMBLE_ROW(i, w)->pos[0], -FUMBLE_ROW(i, w)->pos[1],
                        FUMBLE_ROW(i, w)->pos[2], 1.0f};
        if (!fumbleTargetBlocked(&a)) {
            break;
        }
        /* "point %d, candidate %d overlaps a box; checking the next candidate" */
        debug_StdPrintfDummy(
            "    第%dポイントの第%d候補は箱と重なっています。次の候補をチェックします\n",
            w->fumbleSlot, i);
    }
    /* "decided: point %d, candidate %d" */
    debug_StdPrintfDummy("決定: 第%dポイント 第%d候補 %f, %f, %f\n", w->fumbleSlot, i,
                         FUMBLE_ROW(i, w)->pos[0], FUMBLE_ROW(i, w)->pos[1],
                         FUMBLE_ROW(i, w)->pos[2]);
    {
        FumbleVec pos = {FUMBLE_ROW(i, w)->pos[0], -FUMBLE_ROW(i, w)->pos[1],
                         FUMBLE_ROW(i, w)->pos[2], 1.0f};
        float quat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        float rot[4] = {0.0f, 0.0f, 0.0f, 1.0f};

        RotQuaternionY(quat, (short)(FUMBLE_ROW(i, w)->rotY * 182.04445f));
        RotQuaternionX(quat, (short)(-FUMBLE_ROW(i, w)->rotX * 182.04445f));
        RotQuaternionZ(quat, (short)(FUMBLE_ROW(i, w)->rotZ * 182.04445f));
        RotQuaternionX(rot, 8192);
        ReleaseWeaponWithFumbleTargetPos(g, &pos, quat, rot, 2.0f);
    }
    w->fumbleSlot = w->fumbleSlot + 1;
    if (w->fumbleSlot == 7) {
        w->fumbleSlot = 0;
        return 1;
    }
    return 0;
}

static WeaponWork swordWorkTemplate = {
    0,
    0,
    0,
    -1,
    {{0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f}},
    0,
    0,
    0,
    0,
    0,
    0,
    0.0f,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    0,
    0.0f,
    0.0f,
}; /* derived name */

/* the offsets the two path helpers below set the z of and push along */
static float pathOfsFwd[4] = {0.0f, 0.0f, 1.0f, 1.0f}; /* derived name */

static float pathOfsBack[4] = {0.0f, 0.0f, 1.0f, 1.0f}; /* derived name */

static inline void addWeaponPathOffset(Sub15C *p, struct MotRoot *rp, float d) /* derived name */
{
    float m[16];
    float v[4];
    float *q = p->root.quat;

    GetMatrixFromQuaternion(m, q);
    pathOfsFwd[2] = d;
    _ApplyMatrix(v, m, pathOfsFwd);
    _AddVectorXYZ(rp->pos, rp->pos, v);
}

static inline void subWeaponPathOffset(Sub15C *p, struct MotRoot *rp, float d) /* derived name */
{
    float m[16];
    float v[4];
    float *q = p->root.quat;

    GetMatrixFromQuaternion(m, q);
    pathOfsBack[2] = -d;
    _ApplyMatrix(v, m, pathOfsBack);
    _AddVectorXYZ(rp->pos, rp->pos, v);
}

static int calcDynamicPathGeometry(GObj *g)
{
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;
    float d = weaponKind[w->kind].grip;
    struct MotRoot *rp = &p->root;
    float a;
    float b;
    float t;

    addWeaponPathOffset(p, rp, d);
    a = (float)w->fumbleFrame;
    b = (float)w->fumbleTime;
    t = a / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    _InterVectorXYZ(rp->pos, w->fumbleTo, w->fumbleFrom, a / b);
    rp->pos[1] = w->fumbleFrom[1] + w->fumbleSpeed * t + t * 490.0f * t;
    MultiQuaternion(p->root.quat, p->root.quat, p->root.itemQuat);
    subWeaponPathOffset(p, rp, d);
    w->fumbleFrame = w->fumbleFrame + 1;
    if (w->fumbleFrame >= w->fumbleTime) {
        w->state = 0;
        CopyVector(rp->pos, w->fumbleTo);
        CopyVector(p->root.move, ZeroVector);
        CopyQuaternion(p->root.quat, w->fumbleQuat);
        UpdateRootMatrix(g);
        weaponStickSE(g);
        return 1;
    }
    UpdateRootMatrix(g);
    return 0;
}

/* the query calcDynamicGeometry starts from: all clear but the radius */
static const ClipWork collWorkInit = {{{0.0f}}, {{0.0f}}, 10.0f}; /* derived name */

/* the offset the wall test pushes the blade tip along, its z set per test */
static float hitOfs[4] = {0.0f, 0.0f, 1.0f, 1.0f}; /* derived name */

/* calcDynamicGeometry's TTY trace, built only when DEBUG is defined */
static __inline__ void dynGeoDebugHook(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("calcDynamicGeometry\n");
#endif
}

INCLUDE_ASM(calcDynamicGeometry);

static void getGeometry(GObj *g)
{
    float pos[4];
    float quat[4];
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;
    struct MotRoot *rp = &p->root;

    if (w->holder != 0) {
        Sub15C *d = w->holder->dobj;
        int n = w->holderId;

        CopyMatrix(MatrixDrive_GetMatrix(), (char *)d->nodeMtx + n * 64);
        MatrixDrive_TransMatrix(7.0f, -3.0f, 0.0f);
        CopyVector(pos, MatrixDrive_GetMatrix()[3]);
        CopyQuaternion(quat, (char *)d->nodeQuat + n * 16);
        if (GOBJ_SUB(w->holder)->skel[n].kind == 22) {
            RotQuaternionY(quat, -32768);
        }
        sceVu0SubVector(p->root.move, pos, rp->pos);
        {
            float *rq = p->root.quat;

            DivQuaternion(p->root.itemQuat, quat, rq);
            CopyVector(rp->pos, pos);
            CopyQuaternion(rq, quat);
        }
        UpdateRootMatrix(g);
    } else {
        switch (w->state) {
        default:
            break;
        case 1:
            calcDynamicGeometry(g);
            break;
        case 2:
            calcDynamicPathGeometry(g);
            break;
        }
    }
}

void WeaponCurPos(GObj *self, void *center, void *from, void *to)
{
    WeaponWork *p = GOBJ_SUB(self)->work;
    CopyVector(center, p->hit[1]);
    CopyVector(from, p->hit[2]);
    CopyVector(to, p->hit[3]);
}

void WeaponHitEffect(GObj *self, void *enemy)
{
    WeaponWork *p = GOBJ_SUB(self)->work;
    CheckEnemyHit(enemy, p->hit[1], p->hit[2], p->hit[3]);
}

void ExecWeaponHitReaction(GObj *self)
{
    weaponHitReactionSE(self);
}

/* the blade tip in the sword's own frame */
static float swordTip[4] = {0.0f, 0.0f, 80.0f, 1.0f}; /* derived name */

static void checkHit(GObj *g)
{
    float pos[4];
    float quat[4];
    float v0[4];
    float v1[4];
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;

    if (w->holder == 0) {
        return;
    }
    MatrixDrive_PushMatrix();
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), p->root.quat, p->root.pos);
    MatrixDrive_TransMatrixV((char *)swordTip);
    CopyVector(v0, MatrixDrive_GetMatrix()[3]);
    GetInverseQuaternion(quat, p->root.itemQuat);
    MultiQuaternion(quat, p->root.quat, quat);
    SubVectorXYZ(pos, p->root.pos, p->root.move);
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), quat, pos);
    MatrixDrive_TransMatrixV((char *)swordTip);
    CopyVector(v1, MatrixDrive_GetMatrix()[3]);
    MatrixDrive_PopMatrix();
    CopyVector(w->hit[1], v0);
    CopyVector(w->hit[2], v1);
    CopyVector(w->hit[3], p->root.pos);
}

/* the queen's sword offset, its z set per sword */
static float queenSwordOfs[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

INCLUDE_ASM(initializeQueenzSword);

typedef float WeaponVec[4] __attribute__((aligned(8))); /* derived name */

INCLUDE_ASM(InitWeaponGeo);

static void dispLaserSword(GObj *g, float t);

/* the insect net's line colour and its handle, end to end */
static int netColor[4] = {128, 128, 128, 128}; /* derived name */

static float netHandleStart[4] = {0.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static float netHandleEnd[4] = {0.0f, 0.0f, 100.0f, 1.0f}; /* derived name */

typedef struct { /* field names derived */
    float f[4];
} __attribute__((aligned(16))) NetVec; /* derived name */

void WeaponGeo(GObj *g)
{
    getGeometry(g);
    checkHit(g);
}

void dispInsectNet(GObj *g)
{
    int i;

    CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(g)->nodeMtx);
    gif_StartPacketPri(11);
    gif_SetZTest(1);
    gif_SetZWrite(1);
    gif_SetAlpha(1, 7, 128);
    DrawLineG((int *)netHandleStart, netColor, (int *)netHandleEnd, netColor, 0);
    for (i = 0; i <= 65535; i += 4096) {
        NetVec p = {
            {GetTableCos((short)i) * 30.0f, 0.0f, GetTableSin((short)i) * 30.0f + 130.0f, 1.0f}};
        NetVec q = {{GetTableCos((short)(i + 4096)) * 30.0f, 0.0f,
                     GetTableSin((short)(i + 4096)) * 30.0f + 130.0f, 1.0f}};

        DrawLineG(&p, netColor, &q, netColor, 0);
    }
    gif_EndPacket();
}

static void dispBlur(GObj *g);
static void calcBlur(GObj *g, float t);
/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

/* The MatrixDrive matrix, viewed as the union of float and int arrays this
   codebase uses for VU0 data. */
typedef union { /* field names derived */
    float f[4][4];
    int i[4][4];
} WeaponMatrix; /* derived name */

INCLUDE_ASM(WeaponDL);

void PickupWeapon(GObj *self, GObj *holder, int focus)
{
    WeaponWork *p = GOBJ_SUB(self)->work;

    p->holder = holder;
    p->holderId = GetSkeltonFocusNode(holder, focus);
    GOBJ_SUB(holder)->ctrl.pickedWeapon = self;
}

GObj *CheckSwapableWeapon(GObj *self, float dist)
{
    GObj *found = 0;
    float best = dist * dist;
    GObj *g = isysGObjSearchFromObjKindID_begin(14);
    float pos[4];
    float d;

    GetRootPosition(pos, self);

    for (; g != 0; g = isysGObjSearchFromObjKindID_next(g)) {
        WeaponWork *w;
        float *wp;

        if (g == self)
            continue;

        w = GOBJ_SUB(g)->work;
        if (w->kind == 0)
            continue;

        if (w->holder != 0)
            continue;

        if (g->active == 0)
            continue;

        wp = (float *)((char *)GOBJ_SUB(g)->nodeMtx + 48);
        d = distance_squared(pos, wp);
        if (d < best) {
            found = g;
            best = d;
        }
    }
    return found;
}

void ReleaseWeapon(GObj *self)
{
    WeaponWork *p = GOBJ_SUB(self)->work;
    if (p->holder) {
        p->holder->dobj->ctrl.pickedWeapon = 0;
    }
    p->holder = 0;
    p->holderId = -1;
    p->state = 0;
}

int CheckWeaponKind(GObj *self)
{
    return ((WeaponWork *)GOBJ_SUB(self)->work)->kind;
}

INCLUDE_ASM(LightTorchOnOfWeapon);

INCLUDE_ASM(LightTorchOnOfWeaponWithNoSE);

void LightTorchOffOfWeapon(GObj *self)
{
    WeaponWork *p = GOBJ_SUB(self)->work;
    int i;

    for (i = 0; i < p->count; i++) {
        LightTorchOff(p->objs[i]);
    }
}

GObj *GetTorchGObjOfWeapon(GObj *self)
{
    WeaponWork *p = GOBJ_SUB(self)->work;
    if (p->count) {
        return p->objs[0];
    }
    return 0;
}

/* ReleaseWeapon's body is expanded in place here.  LightTorchOnOfWeapon and
 * LightTorchOnOfWeaponWithNoSE come from one source body. */
void ReleaseWeaponWithFumble(GObj *self, float *move, float *quat)
{
    Sub15C *e = GOBJ_SUB(self);
    WeaponWork *w = (WeaponWork *)e->work;
    struct MotRoot *root = &e->root;

    if (w->holder) {
        w->holder->dobj->ctrl.pickedWeapon = 0;
    }
    w->holder = 0;
    w->holderId = -1;
    w->state = 1;

    if (quat) {
        CopyQuaternion(root->itemQuat, quat);
    }
    CopyVector(root->move, move);
    root->move[3] = 0.0f;
}

int InitWeaponFumbleSequence(GObj *self)
{
    ((WeaponWork *)GOBJ_SUB(self)->work)->fumbleSlot = 0;
    return 1;
}

float GetWeaponWeight(GObj *self)
{
    return (float)weaponKind[((WeaponWork *)GOBJ_SUB(self)->work)->kind].weight;
}

void SetWeaponTorchChainReactionFlagAll(int flag)
{
    GObj *g;
    WeaponWork *w;
    int i;

    for (g = isysGObjSearchFromObjKindID_begin(14); g; g = isysGObjSearchFromObjKindID_next(g)) {
        w = GOBJ_SUB(g)->work;
        if (w->kind == 1) {
            for (i = 0; i < w->count; i++) {
                SetTorchChainReactionFlag(w->objs[i], flag);
            }
        }
    }
}

INCLUDE_ASM(InitDemoQueensSword);

INCLUDE_ASM(ExecDemoQueensSword);
