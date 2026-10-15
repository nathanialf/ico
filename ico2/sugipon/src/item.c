#include "sugiCommon.h"
#include "item.h"
#include "DObj.h"
#include "debug.h"
#include "gamesys.h"
#include "sceneManager.h"
#include "memory.h"
#include "gobj.h"
#include "attackhit.h"
#include "DisplayP2O.h"
#include "StageAnimation.h"
#include "box.h"
#include "frameDependSequence.h"
#include "motionManager2.h"
#include "particleEffect.h"
#include "pool.h"
#include "stageMultiBgaManager.h"
#include "torch.h"
#include <libvu0.h>
#include "geometryManager.h"
#include "typedef.h"
#include "ios.h"
#include "Matrix.h"
#include "tableSin.h"
#include <string.h>
#include "matrixDrive.h"
#include "quaternion.h"
#include "main.h"
#include "fieldCollision.h"
#include "debug_exception.h"

static void uncarriedItemGeo(struct GObj *gobj);

#include <assert.h>
#include "include_asm.h"

/* A bomb's fuse: the torch object that lights it, the frames left to burn,
   the fuse state (0 unlit, 1 burning, 2 exploding, 3 spent), where the
   explosion is centred and its animation slot. */
typedef struct {       /* field names derived */
    GObj *torch;       /* 0x00 */
    int time;          /* 0x04 */
    int state;         /* 0x08 */
    int padC;          /* 0x0C */
    float pos[4];      /* 0x10 */
    BgaPlayNode *anim; /* 0x20 */
    int animMode;      /* 0x24 */
} ItemFuse;            /* derived name */

/* The 144-byte work record InitItemGeo allocates and fills from
   emptyItemWork: the dead flag, the kind (1 a bomb), the carry state and
   holder, the rotation relative to the holder, the bobbing spin, the fuse,
   the explosion's animation slot and the pool drift.  8-aligned. */
typedef struct {                        /* field names derived */
    int dead;                           /* 0x00 */
    int kind;                           /* 0x04 */
    int released;                       /* 0x08 */
    int held;                           /* 0x0C */
    int thrown;                         /* 0x10 */
    int holder;                         /* 0x14, the holding object */
    int pad18[2];                       /* 0x18 */
    float rot[4];                       /* 0x20 */
    float spin;                         /* 0x30 */
    int spinCount;                      /* 0x34 */
    int pad38[2];                       /* 0x38 */
    ItemFuse fuse;                      /* 0x40 */
    int pad68[2];                       /* 0x68 */
    int inPool;                         /* 0x70 */
    int sleep;                          /* 0x74 */
    int pad78[2];                       /* 0x78 */
    float drain[4];                     /* 0x80 */
} __attribute__((aligned(8))) ItemWork; /* derived name */

static void bombSparkStartSE(GObj *gobj)
{
    ExecuteSEPackage(gobj, 50);
}

/* whether the item is a bomb; HoldItem, StopItemExplodeAnimationAll and
   GetBombTorchGObj use it */
static inline int IsItemKindBomb(GObj *gobj) /* derived name */
{
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(gobj)->work;
    return p->kind == 1;
}

INCLUDE_ASM(HoldItem);

/* mark the item dead; uncarriedItemGeo, ItemDL, BreakItemFromOutside and
   BreakItemWithAttackHit use it */
static inline void setItemDead(GObj *gobj) /* derived name */
{
    Sub15C *w = GOBJ_SUB(gobj);
    ItemWork *p = (ItemWork *)*(int *)&w->work;

    w->disp = 0;
    p->dead = 1;
    gobj->active = 0;
}

static ItemWork emptyItemWork = {0,    0, 0,   0,       0, 0, {0}, {0.0f, 0.0f, 0.0f, 1.0f},
                                 0.0f, 0, {0}, {0, 300}}; /* derived name */

/* The velocity a released item starts from. */
static float zeroVelocity[4] = {0.0f, 0.0f, 0.0f, 0.0f}; /* derived name */

/* The offset a dropped item is placed at, below the holder's hand. */
static float itemDropOfs[4] = {0.0f, -50.0f, 0.0f, 1.0f}; /* derived name */

/* The clip avoidInsideOfWall runs from the holder to the item, a ClipWork's
   192 bytes with the radius 20 at 0x70.  The ROM places it 8-aligned in
   .data, so it is not the 16-aligned ClipWork itself. */
static float itemWork[12][4] = {
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}, {20.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
}; /* derived name */

/* Where a carried item sits relative to the focus node. */
static float carryOfsOther[4] = {-10.0f, -15.0f, 0.0f, 1.0f}; /* derived name */

static void avoidInsideOfWall(void *self, GObj *arg)
{
    ClipWork *p;
    if (arg == 0)
        return;
    p = (ClipWork *)itemWork;
    GetRootPosition(p->pt[0], arg);
    GetRootPosition(p->pt[1], self);
    ClipWall(p);
    if (p->wall.elem == 0)
        return;
    SetDirectRootPositionNoFitting(self, p->pt[2]);
}

void ReleaseItem(GObj *gobj)
{
    ItemWork *p = GOBJ_SUB(gobj)->work;
    avoidInsideOfWall(gobj, p->holder);
    p->released = 1;
    p->held = 0;
    p->holder = 0;
    p->thrown = 0;
    GOBJ_SUB(gobj)->disp = 1;
    CopyVector(GOBJ_SUB(gobj)->root.move, zeroVelocity);
    SetIdentityQuaternion(GOBJ_SUB(gobj)->root.itemQuat);
}

INCLUDE_ASM(ThrowItem);

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} ItemVec; /* derived name */

typedef struct ItemLayout { /* field names derived */
    ItemVec pos;            /* 0x00 */
    ItemVec rot;            /* 0x10 */
    ItemVec scale;          /* 0x20 */
    int kind; /* 0x30, the item kind; the torch InitItemGeo lights is made as kind 2 */
    char pad34[12];
} ItemLayout; /* derived name */

INCLUDE_ASM(InitItemGeo);

/* The holder's display object is read again at every site through the
   SubHandle union, then its node matrices (64 bytes a node) and quaternions
   (16 bytes a node); q is a plain four-float scratch. */
INCLUDE_ASM(carriedItemGeo);

/* start the break animation of a broken item; BreakItemFromOutside and
   BreakItemWithAttackHit use it */
static inline int entryBreakBgAnimation(int id, float *pos, float *dir) /* derived name */
{
    float rot[4];
    float d[4];

    if (id != 972) {
        memset(&rot, 0, 16);
        rot[3] = 1.0f;
        CopyVector(d, dir);
        d[1] = 0.0f;
        _NormalizeVector(d, d);
        RotQuaternionY(&rot, GetTableArcTan2(d[0], d[2]));
        EntryStageMultiBgaManager(id, pos, &rot);
        return 1;
    }
    return 0;
}

/* the per-frame step from the frame-rate pair at systemStatus; ThrowItem
   and InitItemGeo spell the same integer quotient out */
#define ITEM_DT (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1])) /* derived name */

/* the wall-hit arm of uncarriedItemGeo */
static inline int breakItemOnWallHit(GObj *gobj, float len, float *pos,
                                     float *vel) /* derived name */
{
    float rot[4];
    float d[4];
    float sv[4];
    ItemWork *p = GOBJ_SUB(gobj)->work;

    if (5.0f < len) {
        int id = itemKind[p->kind].stayAnim;

        if (id != 972) {
            memset(&rot, 0, 16);
            rot[3] = 1.0f;
            CopyVector(d, vel);
            d[1] = 0.0f;
            _NormalizeVector(d, d);
            RotQuaternionY(&rot, GetTableArcTan2(d[0], d[2]));
            _ScaleVectorXYZ(sv, vel, 0.3f);
            EntryStageMultiBgaManagerSensitive(id, pos, &rot, sv);
            SetParticleEffect(10, pos, &rot);
        }
        if ((itemKind + p->kind)->flags & 1) {
            ExecuteSEPackage(gobj, 39);
            return 1;
        }
        ExecuteSEPackage(gobj, 37);
    }
    return 0;
}

/* the floor-hit arm of uncarriedItemGeo; it calls entryBreakBgAnimation */
static inline int breakItemOnFloorHit(GObj *gobj, float len, float *pos,
                                      float *vel) /* derived name */
{
    ItemWork *p = GOBJ_SUB(gobj)->work;

    if (10.0f < len) {
        entryBreakBgAnimation(itemKind[p->kind].breakAnim, pos, vel);
        if ((itemKind + p->kind)->flags & 1) {
            ExecuteSEPackage(gobj, 43);
            return 1;
        }
    }
    if (p->thrown == 0) {
        p->thrown = 1;
        ExecuteSEPackage(gobj, 48);
        return 0;
    }
    if (5.0f < len) {
        ExecuteSEPackageWithVolumeRate(gobj, 38, 20.0f < len ? 1.0f : len * 0.05f);
    }
    return 0;
}

INCLUDE_ASM(uncarriedItemGeo);

INCLUDE_ASM(execBombGeo);

INCLUDE_ASM(ItemGeo);

/* ItemDL's check for the end of a bomb's explosion */
static inline void checkBombExplodeEnd(GObj *gobj) /* derived name */
{
    ItemWork *p = GOBJ_SUB(gobj)->work;
    ItemFuse *q = &p->fuse;

    if (q->state == 3) {
        if (stage_DispBgAnimation(&p->fuse.anim) != 0) {
            q->state = 4;
            setItemDead(gobj);
        }
    }
}

INCLUDE_ASM(ItemDL);

/* the body of GetItemKind, which BreakItemFromOutside inlines and
   GetItemKind calls */
static inline int GetItemKindInline(GObj *gobj) /* derived name */
{
    ItemWork *p = GOBJ_SUB(gobj)->work;

    return p->kind;
}

INCLUDE_ASM(BreakItemFromOutside);

/* the body of CheckCarryableItem, which the four Revive walkers inline and
   CheckCarryableItem calls */
static inline int CheckCarryableItemInline(GObj *gobj) /* derived name */
{
    int r = 0;
    ItemWork *p = GOBJ_SUB(gobj)->work;
    if (gobj->active != 0) {
        if (*(long long *)&p->released == 0) {
            if (p->fuse.state < 2) {
                r = 1;
            }
        }
    }
    return r;
}

INCLUDE_ASM(CheckCarryableItem);

INCLUDE_ASM(GetItemKind);

INCLUDE_ASM(IsItemHoldable);

INCLUDE_ASM(IsBombExplode);

INCLUDE_ASM(GetBombTorchGObj);

INCLUDE_ASM(ReviveAllCarryableItems);

INCLUDE_ASM(ReviveCarryableItemsWithBoundary);

INCLUDE_ASM(ReviveAllCarryableItemsWithRandomVelocity);

INCLUDE_ASM(CheckItemDead);

/* explosion animation stop handling planned */
static const char bombAnimStopMsg[] = "爆発アニメーション停止処理予定\n"; /* derived name */

INCLUDE_ASM(StopItemExplodeAnimationAll);

int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame)
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (CheckCarryableItemInline(g)) {
            ItemWork *p = (ItemWork *)GOBJ_SUB(g)->work;
            UnlinkParentOfDObj(g);
            p->released = 1;
            p->sleep = nonSleepFrame;
        }
    }
    return 1;
}
