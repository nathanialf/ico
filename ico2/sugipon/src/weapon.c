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

INCLUDE_ASM(ReleaseWeaponWithFumbleTargetPos);

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

INCLUDE_ASM(ReleaseWeaponWithFumbleSequential);

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

INCLUDE_ASM(calcDynamicPathGeometry);

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

INCLUDE_ASM(getGeometry);

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

static void initializeQueenzSword(GObj *g, int index, SObjSimpleSetting *lay)
{
    WeaponWork *w = GOBJ_SUB(g)->work;
    ObjNode lnk = {g, index};
    SObjSimpleSetting r;
    SObjSimpleSetting r2;
    int i;
    GObj *o;
    GObj *o2;

    r = *lay;
    r.obj = (lay->obj & 0xFF00) ? 5 : 4;

    w->count = 1;
    w->objs = iosMallocDebug(ios_partition_sugipon, 1 * 4, __FILE__, 711);

    for (i = 0; i < 1; i++) {
        queenSwordOfs[2] = weaponKind[w->kind].length * (float)i / 0.0f;
        o = CreateLayoutedGObj(10, 69, -1, i == 0, &r, -1, 7, 0);
        LinkParentOfDObj(o, &lnk);
        CopyVector(GOBJ_SUB(o)->root.pos, queenSwordOfs);
        w->objs[i] = o;
    }

    r2 = *lay;
    r2.obj = 13;
    o2 = CreateLayoutedGObj(45, 9, -1, 0, &r2, -1, 7, 0);
    GOBJ_SUB(o2)->parent = lnk;
    w->sword = o2;
}

typedef float WeaponVec[4] __attribute__((aligned(8))); /* derived name */

INCLUDE_ASM(InitWeaponGeo);

void WeaponGeo(GObj *g)
{
    getGeometry(g);
    checkHit(g);
}

/* the insect net's line colour and its handle, end to end */
static int netColor[4] = {128, 128, 128, 128}; /* derived name */

static float netHandleStart[4] = {0.0f, 0.0f, -50.0f, 1.0f}; /* derived name */

static float netHandleEnd[4] = {0.0f, 0.0f, 100.0f, 1.0f}; /* derived name */

typedef struct { /* field names derived */
    float f[4];
} __attribute__((aligned(16))) NetVec; /* derived name */

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

INCLUDE_ASM(WeaponDL);

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

/* The MatrixDrive matrix, viewed as the union of float and int arrays this
   codebase uses for VU0 data. */
typedef union { /* field names derived */
    float f[4][4];
    int i[4][4];
} WeaponMatrix; /* derived name */

INCLUDE_ASM(PickupWeapon);

INCLUDE_ASM(CheckSwapableWeapon);

INCLUDE_ASM(ReleaseWeapon);

INCLUDE_ASM(CheckWeaponKind);

INCLUDE_ASM(LightTorchOnOfWeapon);

INCLUDE_ASM(LightTorchOnOfWeaponWithNoSE);

INCLUDE_ASM(LightTorchOffOfWeapon);

INCLUDE_ASM(GetTorchGObjOfWeapon);

/* ReleaseWeapon's body is expanded in place here.  LightTorchOnOfWeapon and
 * LightTorchOnOfWeaponWithNoSE come from one source body. */
INCLUDE_ASM(ReleaseWeaponWithFumble);

INCLUDE_ASM(InitWeaponFumbleSequence);

INCLUDE_ASM(GetWeaponWeight);

INCLUDE_ASM(SetWeaponTorchChainReactionFlagAll);

INCLUDE_ASM(InitDemoQueensSword);

INCLUDE_ASM(ExecDemoQueensSword);
