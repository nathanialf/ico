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

/* The 160-byte work record InitItemGeo allocates and fills from
   emptyItemWork: the dead flag, the kind (1 a bomb), the carry state and
   holder, the rotation relative to the holder, the bobbing spin, the fuse,
   the explosion's animation slot, the pool drift and the wave phase.
   8-aligned. */
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
    short wave;                         /* 0x90 */
    short pad92;                        /* 0x92 */
    int pad94[3];                       /* 0x94 */
} __attribute__((aligned(8))) ItemWork; /* derived name */

static void bombSparkStartSE(GObj *gobj)
{
    ExecuteSEPackage(gobj, 50);
}

static void bombSparkSE(GObj *gobj)
{
    ExecuteSEPackage(gobj, 51);
}

static void bombExplodeSE(GObj *gobj)
{
    ExecuteSEPackage(gobj, 52);
}

/* whether the item is a bomb; HoldItem, StopItemExplodeAnimationAll and
   GetBombTorchGObj use it */
static inline int IsItemKindBomb(GObj *gobj) /* derived name */
{
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(gobj)->work;
    return p->kind == 1;
}

void HoldItem(GObj *gobj, GObj *holder)
{
    float q[4];
    float hq[4];
    ItemWork *p;

    if (gobj == 0) {
        /* lost sight of the small barrel but is still trying to grab it */
        debug_StdPrintfDummy("小樽を見失ったのにつかもうとしてます。\n");
        debug_assert(__FILE__, 356);
        __assert(__FILE__, 356, "0");
    }
    p = GOBJ_SUB(gobj)->work;
    p->released = 0;
    p->held = 1;
    p->holder = (int)holder;
    GOBJ_SUB(gobj)->disp = 0;
    SetIdentityQuaternion(GOBJ_SUB(gobj)->root.itemQuat);
    if (IsItemKindBomb(gobj)) {
        SetRootQuaternion(gobj, IdentityQuaternion);
    }
    GetRootQuaternion(q, gobj);
    GetRootQuaternion(hq, holder);
    GetInverseQuaternion(hq, hq);
    MultiQuaternion(p->rot, hq, q);
}

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

/* Where a carried item sits relative to the focus node, the boy's hand and
   every other carrier's. */
static float carryOfsPlayer[4] = {-3.3333335f, -27.777779f, 0.0f, 1.0f}; /* derived name */

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

void ThrowItem(GObj *gobj, void *vel);

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

char *InitItemGeo(GObj *gobj, ItemLayout *layout)
{
    ObjNode link;
    ItemLayout lay;
    Sub15C *w = GOBJ_SUB(gobj);
    ItemWork *p = iosMallocDebug(ios_partition_sugipon, sizeof(ItemWork), __FILE__, 446);

    GOBJ_SUB(gobj)->work = p;
    *p = emptyItemWork;
    p->kind = layout->kind;
    w->colRotate = 0;
    if (p->kind == 1) {
        ItemWork *rec = GOBJ_SUB(gobj)->work;
        GObj *g;

        link.obj = gobj;
        link.node = 0;
        lay = *layout;
        lay.kind = 2;
        g = CreateLayoutedGObj(10, 75, -1, 1, &lay, -1, 7, 0);
        SetTorchChainReactionFlag(g, 1);
        LinkParentOfDObj(g, &link);
        CopyVector(GOBJ_SUB(g)->root.pos, itemDropOfs);
        rec->fuse.torch = g;
        rec->fuse.time =
            (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 300.0f);
    }
    gamesysObjInfoCls(gobj->kind, gobj->labelId);
    return (char *)p;
}

/* The holder's display object is read again at every site through the
   SubHandle union, then its node matrices (64 bytes a node) and quaternions
   (16 bytes a node); q is a plain four-float scratch. */
static void carriedItemGeo(GObj *gobj)
{
    Vec16 pos;
    sceVu0FVECTOR q;
    sceVu0FMATRIX m;
    Vec16 wpos;
    Vec16 rot;
    Vec16 up;
    unsigned short ang[2];
    Vec16 adj;
    ItemWork *rec = GOBJ_SUB(gobj)->work;

    if (((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->ctrl.frameFlag2 != 0) {
        int isPlayer = (GObj *)rec->holder == girlGObj;
        int node = isPlayer ? 6 : 22;

        if (isPlayer) {
            _ApplyMatrix(&pos,
                         (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeMtx +
                             GetSkeltonFocusNode((GObj *)rec->holder, node) * 64,
                         carryOfsPlayer);
        } else {
            _ApplyMatrix(&pos,
                         (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeMtx +
                             GetSkeltonFocusNode((GObj *)rec->holder, node) * 64,
                         carryOfsOther);
        }
        CopyQuaternion(q, (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeQuat +
                              GetSkeltonFocusNode((GObj *)rec->holder, node) * 16);
        if (isPlayer) {
            RotQuaternionX(q, -16384);
        } else {
            RotQuaternionX(q, 16384);
        }
        SetRootQuaternion(gobj, q);
    } else {
        int node = GetSkeltonFocusNode((GObj *)rec->holder, 1);

        CopyVector(&wpos, (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeMtx +
                              GetSkeltonFocusNode((GObj *)rec->holder, 22) * 64 + 48);
        MatrixDrive_SetTransposeMatrix(
            m, (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeMtx + node * 64);
        _ApplyMatrix(q, m, &wpos);
        q[2] = 0.0f;
        _ApplyMatrix(
            &pos, (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeMtx + node * 64, q);
        memset(&up, 0, 16);
        up.f[1] = 1.0f;
        sceVu0ApplyMatrix(&up,
                          (char *)((SubHandle *)&((GObj *)rec->holder)->dobj)->sub->nodeMtx +
                              GetSkeltonFocusNode((GObj *)rec->holder, 44) * 64,
                          &up);
        MatrixDrive_GetTurnZAngleYX(&ang[0], &ang[1], up.f[0], up.f[1], up.f[2]);
        CopyQuaternion(&rot, rec->rot);
        SetIdentityQuaternion(&adj);
        RotQuaternionY(&adj, -ang[0]);
        RotQuaternionX(&adj, ang[1]);
        MultiQuaternion(&rot, &adj, &rot);
        SetRootQuaternion(gobj, &rot);
    }
    SetDirectRootPosition(gobj, &pos);
}

/* start the break animation of a broken item; BreakItemFromOutside and
   BreakItemWithAttackHit use it */
static inline int entryBreakBgAnimation(int id, float *pos, float *dir, int arg) /* derived name */
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
        EntryStageMultiBgaManagerWithStay(id, pos, &rot, arg);
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
            EntryStageMultiBgaManagerSensitiveWithStay(id, pos, &rot, sv,
                                                       itemKind[p->kind].stayMode);
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
        entryBreakBgAnimation(itemKind[p->kind].breakAnim, pos, vel, itemKind[p->kind].breakMode);
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

INCLUDE_ASM(floatGeo_75);
INCLUDE_ASM(uncarriedItemGeo);

static void execBombGeo(GObj *gobj);

INCLUDE_ASM(execBombGeo);

void ItemGeo(GObj *gobj)
{
    ItemWork *p = GOBJ_SUB(gobj)->work;
    if (p->dead == 1) {
        return;
    }
    if (p->held != 0) {
        carriedItemGeo(gobj);
    } else if (p->released != 0) {
        int held = GOBJ_SUB(gobj)->disp;
        GOBJ_SUB(gobj)->disp = 0;
        uncarriedItemGeo(gobj);
        if (held != 0) {
            GOBJ_SUB(gobj)->disp = 1;
        }
    } else {
        GObj *owner = GOBJ_SUB(gobj)->parent.obj;
        if (owner != 0) {
            if (owner->kind == 17) {
                if (GetBoxMode(owner) == 2) {
                    p->holder = 0;
                    ThrowItem(gobj, GOBJ_SUB(owner)->root.move);
                }
            }
        }
    }
    UpdateRootMatrix(gobj);
    if (IsItemKindBomb(gobj)) {
        execBombGeo(gobj);
    }
}

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

void ItemDL(GObj *gobj)
{
    ItemWork *p = GOBJ_SUB(gobj)->work;

    if (IsItemKindBomb(gobj)) {
        checkBombExplodeEnd(gobj);
    }
    if (p->dead == 1) {
        return;
    }
    if (IsItemKindBomb(gobj)) {
        ItemFuse *q = &p->fuse;
        int mode = q->state;

        if (mode >= 2) {
            return;
        }
        if (mode == 1) {
            if (systemStatus[5] != 0) {
                if (q->animMode != 0) {
                    StopSEPackage(gobj);
                    q->animMode = 0;
                }
            } else if (q->animMode == 0) {
                bombSparkSE(gobj);
                q->animMode = mode;
            }
        }
    }
    p2o_DispVU1(gobj);
}

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

int CheckCarryableItem(GObj *gobj)
{
    return CheckCarryableItemInline(gobj);
}

int GetItemKind(GObj *gobj)
{
    return GetItemKindInline(gobj);
}

int GetCharHeldItem(GObj *chara)
{
    GObj *w;
    if (chara == 0)
        return -1;
    w = GOBJ_ACT(chara)->curItem;
    if (w == 0)
        return -1;
    return ((ItemWork *)GOBJ_SUB(w)->work)->kind;
}

int IsItemHoldable(GObj *gobj)
{
    ItemWork *p = GOBJ_SUB(gobj)->work;

    return p->dead == 0;
}

int IsBombExplode(GObj *gobj)
{
    ItemWork *p = GOBJ_SUB(gobj)->work;

    return p->fuse.state == 2;
}

void *GetBombTorchGObj(GObj *item)
{
    ItemWork *p = GOBJ_SUB(item)->work;
    if (IsItemKindBomb(item)) {
        return p->fuse.torch;
    }
    return 0;
}

int ReviveAllCarryableItems(void)
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (CheckCarryableItemInline(g)) {
            ItemWork *p = (ItemWork *)GOBJ_SUB(g)->work;
            UnlinkParentOfDObj(g);
            p->released = 1;
            p->sleep = 0;
        }
    }
    return 1;
}

int ReviveCarryableItemsWithBoundary(void *center, float radius)
{
    GObj *g;
    float pos[4];
    float r2 = radius * radius;

    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        GetRootPosition(pos, g);
        if (distance_squared(pos, center) < r2) {
            if (CheckCarryableItemInline(g)) {
                ItemWork *p = (ItemWork *)GOBJ_SUB(g)->work;
                UnlinkParentOfDObj(g);
                p->released = 1;
                p->sleep = 0;
            }
        }
    }
    return 1;
}

int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz)
{
    GObj *g;

    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        short ang = random_unit() * 65536.0f;

        if (CheckCarryableItemInline(g)) {
            ItemWork *p = (ItemWork *)GOBJ_SUB(g)->work;
            UnlinkParentOfDObj(g);
            p->released = 1;
            p->sleep = 0;
        }
        GOBJ_SUB(g)->root.move[0] = horz * GetTableSin(ang);
        GOBJ_SUB(g)->root.move[1] = up * random_unit();
        GOBJ_SUB(g)->root.move[2] = horz * GetTableCos(ang);
    }
    return 1;
}

int CheckItemDead(GObj *gobj)
{
    int r = 0;
    ItemWork *p = GOBJ_SUB(gobj)->work;

    if (p->dead == 1 || gobj->active == 0) {
        r = 1;
    }
    return r;
}

/* explosion animation stop handling planned */
static const char bombAnimStopMsg[] = "爆発アニメーション停止処理予定\n"; /* derived name */

void StopItemExplodeAnimationAll(void)
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        ItemWork *p = (ItemWork *)GOBJ_SUB(g)->work;
        if (IsItemKindBomb(g)) {
            if (p->fuse.state == 3) {
                if (stage_DispBgAnimation(&p->fuse.anim) == 0) {
                    debug_StdPrintfDummy(bombAnimStopMsg);
                }
            }
        }
    }
}

INCLUDE_ASM(BreakItemWithAttackHit);

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
