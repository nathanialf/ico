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

/* RECONSTRUCTION, read from the ROM.  A bomb's fuse: the torch object that
   lights it, the frames left to burn, the fuse state (0 unlit, 1 burning,
   2 exploding, 3 spent), where the explosion is centred and its animation
   slot. */
typedef struct {
    char *torch;  /* 0x00 */
    int time;     /* 0x04 */
    int state;    /* 0x08 */
    int padC;     /* 0x0C */
    float pos[4]; /* 0x10 */
    char *anim;   /* 0x20 */
    int animMode; /* 0x24 */
} ItemFuse;

/* RECONSTRUCTION, read from the ROM.  The 160-byte work record InitItemGeo
   allocates and fills from emptyItemWork: the dead flag, the kind (1 a bomb),
   the carry state and holder, the rotation relative to the holder, the
   bobbing spin, the fuse, the explosion's animation slot, the pool drift and
   the wave phase.  8-aligned: the template copy is ld/sd pairs. */
typedef struct {
    int dead;       /* 0x00 */
    int kind;       /* 0x04 */
    int released;   /* 0x08 */
    int held;       /* 0x0C */
    int thrown;     /* 0x10 */
    int holder;     /* 0x14, the holding object: an int, ItemGeo's store
                          of 0 must share the int alias set of the object-sub
                          load after it */
    int pad18[2];   /* 0x18 */
    float rot[4];   /* 0x20 */
    float spin;     /* 0x30 */
    int spinCount;  /* 0x34 */
    int pad38[2];   /* 0x38 */
    ItemFuse fuse;  /* 0x40 */
    int pad68[2];   /* 0x68 */
    int inPool;     /* 0x70 */
    int sleep;      /* 0x74 */
    int pad78[2];   /* 0x78 */
    float drain[4]; /* 0x80 */
    short wave;     /* 0x90 */
    short pad92;    /* 0x92 */
    int pad94[3];   /* 0x94 */
} __attribute__((aligned(8))) ItemWork;

void bombSparkStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x32);
}

void bombSparkSE(int a0)
{
    ExecuteSEPackage(a0, 0x33);
}

void bombExplodeSE(int a0)
{
    ExecuteSEPackage(a0, 0x34);
}

/* src/item.c:346-350 in the January-2002 listing: a static inline predicate
   whose body (the 0x15C/0x830 chain at line 348, the kind test at line 349)
   is inlined into HoldItem, StopItemExplodeAnimationAll and GetBombTorchGObj. */
static inline int IsItemKindBomb(char *gobj)
{
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(gobj)->work;
    return p->kind == 1;
}

extern void __assert(const char *file, int line, char *expr);

void HoldItem(char *gobj, char *holder)
{
    float q[4];
    float hq[4];
    ItemWork *p;

    if (gobj == 0) {
        /* lost sight of the small barrel but is still trying to grab it */
        debug_StdPrintfDummy("小樽を見失ったのにつかもうとしてます。\n");
        debug_assert(__FILE__, 0x164);
        __assert(__FILE__, 0x164, "0");
    }
    p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    p->released = 0;
    p->held = 1;
    p->holder = (int)holder;
    GOBJ_SUB(gobj)->disp = 0;
    SetIdentityQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150);
    if (IsItemKindBomb(gobj)) {
        SetRootQuaternion(gobj, IdentityQuaternion);
    }
    GetRootQuaternion(q, gobj);
    GetRootQuaternion(hq, holder);
    GetInverseQuaternion(hq, hq);
    MultiQuaternion(p->rot, hq, q);
}

/* src/item.c:266-271 in the January-2002 listing: a static helper with no
   out-of-line copy of its own, inlined into uncarriedItemGeo, ItemDL,
   BreakItemFromOutside and BreakItemWithAttackHit (rows 267 to 270).
   The NAME is a reconstruction; the listing carries no symbol for it. */
static inline void setItemDead(char *gobj)
{
    char *w = (char *)*(int *)(gobj + 0x15C);
    ItemWork *p = (ItemWork *)*(int *)(w + 0x830);

    *(int *)(w + 0x74) = 0;
    p->dead = 1;
    *(int *)(gobj + 0x16C) = 0;
}

/* item.o's whole .data run, in the order the object emits it. */
static ItemWork emptyItemWork = {0,    0, 0,   0,       0, 0, {0}, {0.0f, 0.0f, 0.0f, 1.0f},
                                 0.0f, 0, {0}, {0, 300}};

/* The velocity a released item starts from. */
static float zeroVelocity[4] = {0.0f, 0.0f, 0.0f, 0.0f};

/* The offset a dropped item is placed at, below the holder's hand. */
static float itemDropOfs[4] = {0.0f, -50.0f, 0.0f, 1.0f};

/* The shared item scratch buffer.  avoidInsideOfWall builds the wall-push
   layout in its first three vectors; the 20.0f at offset 0x70 is the only
   other initialised word of the 192, and nothing in the tree reads it, so the
   buffer's internal shape past the first three vectors is not recovered. */
static float itemWork[12][4] = {
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}, {20.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
};

/* Where a carried item sits relative to the focus node, the boy's hand and
   every other carrier's. */
static float carryOfsPlayer[4] = {-3.3333335f, -27.777779f, 0.0f, 1.0f};

static float carryOfsOther[4] = {-10.0f, -15.0f, 0.0f, 1.0f};

void avoidInsideOfWall(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)itemWork;
    GetRootPosition(p, arg);
    GetRootPosition(p + 0x10, (int)self);
    ClipWall((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    SetDirectRootPositionNoFitting(self, p + 0x20);
}

void ReleaseItem(char *gobj)
{
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    avoidInsideOfWall(gobj, p->holder);
    p->released = 1;
    p->held = 0;
    p->holder = 0;
    p->thrown = 0;
    GOBJ_SUB(gobj)->disp = 1;
    CopyVector((char *)*(int *)(gobj + 0x15C) + 0x130, zeroVelocity);
    SetIdentityQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150);
}

void ThrowItem(char *gobj, void *vel)
{
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(gobj)->work;
    avoidInsideOfWall(gobj, p->holder);
    p->released = 1;
    p->held = 0;
    p->thrown = 1;
    _ScaleVectorXYZ(*(char **)(gobj + 0x15C) + 0x130, vel,
                    30.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]));
    SetIdentityQuaternion(*(char **)(gobj + 0x15C) + 0x150);
}

typedef union {
    float f[4];
    long long ll[2];
} ItemVec;

/* 0xA0: the item record's .data initialiser, copied over the fresh
   allocation.  The listing attributes the block move to line 262. */

typedef struct {
    ItemVec pos;   /* 0x00 */
    ItemVec rot;   /* 0x10 */
    ItemVec scale; /* 0x20 */
    int f_30;      /* 0x30 */
    int f_34;
    int f_38;
    int f_3C;
} ItemLayout;

typedef struct {
    char *p_0;
    int f_4;
    int f_8;
    int f_C;
} ItemParentLink;

char *InitItemGeo(char *gobj, ItemLayout *layout)
{
    ItemParentLink link;
    ItemLayout lay;
    char *w = (char *)*(int *)(gobj + 0x15C);
    ItemWork *p = iosMallocDebug(ios_partition_sugipon, 0xA0, __FILE__, 446);

    *(ItemWork **)((char *)*(int *)(gobj + 0x15C) + 0x830) = p;
    *p = emptyItemWork;
    p->kind = layout->f_30;
    *(int *)(w + 0x78) = 0;
    if (p->kind == 1) {
        ItemWork *rec = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
        char *g;

        link.p_0 = gobj;
        link.f_4 = 0;
        lay = *layout;
        lay.f_30 = 2;
        g = CreateLayoutedGObj(10, 0x4B, -1, 1, &lay, -1, 7, 0);
        SetTorchChainReactionFlag(g, 1);
        LinkParentOfDObj(g, &link);
        CopyVector((char *)*(int *)(g + 0x15C) + 0xA0, itemDropOfs);
        rec->fuse.torch = g;
        rec->fuse.time =
            (int)((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f * 300.0f);
    }
    gamesysObjInfoCls(*(int *)(gobj + 0xC), *(int *)(gobj + 8));
    return (char *)p;
}

/* The holder's 0x15C sub-handle is read through the SubHandle union at every
   site in this function: the ROM keeps the three-load chain of line 511 below
   the `q[2] = 0` store, which only happens when the 0x15C read carries alias
   set 0.  `q` itself is a plain four-float scratch, so its store does NOT
   carry alias set 0 and the `rec->f_14` load above it is free to move. */
void carriedItemGeo(char *gobj)
{
    Vec16 pos;
    sceVu0FVECTOR q;
    sceVu0FMATRIX m;
    Vec16 wpos;
    Vec16 rot;
    Vec16 up;
    unsigned short ang[2];
    Vec16 adj;
    ItemWork *rec = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0x604) != 0) {
        int isPlayer = (char *)rec->holder == girlGObj;
        int node = isPlayer ? 6 : 22;

        if (isPlayer) {
            _ApplyMatrix(
                &pos,
                (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0xC) +
                    GetSkeltonFocusNode((char *)rec->holder, node) * 0x40,
                carryOfsPlayer);
        } else {
            _ApplyMatrix(
                &pos,
                (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0xC) +
                    GetSkeltonFocusNode((char *)rec->holder, node) * 0x40,
                carryOfsOther);
        }
        CopyQuaternion(
            q, (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0x10) +
                   GetSkeltonFocusNode((char *)rec->holder, node) * 0x10);
        if (isPlayer) {
            RotQuaternionX(q, -16384);
        } else {
            RotQuaternionX(q, 16384);
        }
        SetRootQuaternion(gobj, q);
    } else {
        int node = GetSkeltonFocusNode((char *)rec->holder, 1);

        CopyVector(&wpos,
                   (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0xC) +
                       GetSkeltonFocusNode((char *)rec->holder, 22) * 0x40 + 0x30);
        MatrixDrive_SetTransposeMatrix(
            m, (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0xC) +
                   node * 0x40);
        _ApplyMatrix(q, m, &wpos);
        q[2] = 0.0f;
        _ApplyMatrix(
            &pos,
            (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0xC) +
                node * 0x40,
            q);
        memset(&up, 0, 16);
        up.f[1] = 1.0f;
        sceVu0ApplyMatrix(
            &up,
            (char *)*(int *)((char *)((SubHandle *)((char *)rec->holder + 0x15C))->i + 0xC) +
                GetSkeltonFocusNode((char *)rec->holder, 44) * 0x40,
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

/* 0x004FB970: seven 32-byte records indexed by the item kind, holding the
   stage-BgAnimation ids this TU entries when an item breaks.  0x3CC is the
   "no animation" sentinel.  Field names are offset-derived. */
typedef struct ItemBreakRec {
    int f_0;
    int f_4;
    int f_8;
    int f_C;
    int f_10;
    int f_14;
    int f_18;
    int f_1C;
} ItemBreakRec;

extern ItemBreakRec itemKind[];

/* src/item.c:184-215 in the January-2002 listing: a static helper with no
   out-of-line copy, inlined into BreakItemFromOutside (rows 185-193, 214) and
   BreakItemWithAttackHit (same rows).  Listing lines 195-213 emit nothing in
   either host.  The NAME is a reconstruction. */
static inline int entryBreakBgAnimation(int id, float *pos, float *dir, int arg)
{
    float rot[4];
    float d[4];

    if (id != 0x3CC) {
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

/* 0x60..0x120 of uncarriedItemGeo's frame and the whole of floatGeo's: the
   192-byte workspace ClipWall / ClipFloor / ClipWallWaveForce / CheckFieldContact
   fill in.  It is the same record avoidInsideOfWall drives through itemWork,
   whose +0x88 hit flag and +0x20 result position that function already names. */
/* The per-frame step this TU derives from the frame-rate pair at systemStatus;
   ThrowItem and InitItemGeo spell the same integer quotient out. */
#define ITEM_DT (60.0f / (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]))

typedef struct DObjLink {
    char *p_0;
    int f_4;
} DObjLink;

/* kept local: this TU's bytes only come out with its own view of ClipWork, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct ClipWorkItem {
    float from[4]; /* 0x00 */
    float to[4];   /* 0x10 */
    float pos[4];  /* 0x20 */
    float f_30[4]; /* 0x30 */
    float f_40[4]; /* 0x40 */
    float f_50[4]; /* 0x50 */
    float f_60[4]; /* 0x60 */
    float radius;  /* 0x70 */
    int f_74;
    int f_78;
    int f_7C;
    int f_80;
    int f_84;
    int wallHit;   /* 0x88 */
    DObjLink f_8C; /* 0x8C */
    int floorHit;  /* 0x94 */
    int f_98;
    int f_9C;
    float plane[4]; /* 0xA0 */
    float f_B0[4];  /* 0xB0 */
} ClipWorkItem;

/* src/item.c:135-178 in the January-2002 listing: a static helper with no
   out-of-line copy, inlined only into uncarriedItemGeo's wall-hit arm.
   The NAME is a reconstruction; the listing carries no symbol for it. */
static inline int breakItemOnWallHit(char *gobj, float len, float *pos, float *vel)
{
    float rot[4];
    float d[4];
    float sv[4];
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (5.0f < len) {
        int id = itemKind[p->kind].f_0;

        if (id != 0x3CC) {
            memset(&rot, 0, 16);
            rot[3] = 1.0f;
            CopyVector(d, vel);
            d[1] = 0.0f;
            _NormalizeVector(d, d);
            RotQuaternionY(&rot, GetTableArcTan2(d[0], d[2]));
            _ScaleVectorXYZ(sv, vel, 0.3f);
            EntryStageMultiBgaManagerSensitiveWithStay(id, pos, &rot, sv, itemKind[p->kind].f_4);
            SetParticleEffect(10, pos, &rot);
        }
        if ((itemKind + p->kind)->f_1C & 1) {
            ExecuteSEPackage((int)gobj, 0x27);
            return 1;
        }
        ExecuteSEPackage((int)gobj, 0x25);
    }
    return 0;
}

/* src/item.c:218-242 in the January-2002 listing: a static helper with no
   out-of-line copy, inlined only into uncarriedItemGeo's floor-hit arm.  It
   calls entryBreakBgAnimation (rows 186-193).  The NAME is a reconstruction. */
static inline int breakItemOnFloorHit(char *gobj, float len, float *pos, float *vel)
{
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (10.0f < len) {
        entryBreakBgAnimation(itemKind[p->kind].f_8, pos, vel, itemKind[p->kind].f_C);
        if ((itemKind + p->kind)->f_1C & 1) {
            ExecuteSEPackage((int)gobj, 0x2B);
            return 1;
        }
    }
    if (p->thrown == 0) {
        p->thrown = 1;
        ExecuteSEPackage((int)gobj, 0x30);
        return 0;
    }
    if (5.0f < len) {
        ExecuteSEPackageWithVolumeRate((int)gobj, 0x26, 20.0f < len ? 1.0f : len * 0.05f);
    }
    return 0;
}

void uncarriedItemGeo(char *gobj)
{
    DObjLink link; /* 0x00 */
    float pos[4];  /* 0x10 */
    float npos[4]; /* 0x20 */
    float vel[4];  /* 0x30 */
    ItemWork *p;   /* 0x40 */

    void floatGeo(float t)
    {
        ClipWorkItem w;

        _ScaleVector(vel, vel, t);
        _AddVectorXYZ(vel, vel, p->drain);
        GetSlerpQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150,
                           (char *)*(int *)(gobj + 0x15C) + 0x150, IdentityQuaternion, t);
        RegularizeQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150);
        CopyVector(w.from, pos);
        CopyVector(w.to, w.from);
        w.radius = 200.0f;
        ClipWallWaveForce(&w);
        if (w.wallHit != 0) {
            float d = GetDistanceFromPlane(w.plane, w.from);

            d += w.radius;
            if (0.0f < d) {
                float k = 1.0f / (d + 50.0f);

                vel[0] += w.plane[0] * 100.0f * k;
                vel[2] += w.plane[2] * 100.0f * k;
            }
        }
    }

    float q[4];      /* 0x50 */
    ClipWorkItem cw; /* 0x60 */
    int linked = 0;
    float len0;
    float len;
    float spd;
    float grav;

    p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    *(int *)((char *)*(int *)(gobj + 0x15C) + 0x5F4) = 0;
    *(int *)((char *)*(int *)(gobj + 0x15C) + 0x5F8) = 0;
    CopyVector(vel, (char *)*(int *)(gobj + 0x15C) + 0x130);
    len0 = VectorLength(vel);
    UnlinkParentOfDObj(gobj);
    GetRootPosition(pos, gobj);
    vel[1] += ITEM_DT * 0.5f * ITEM_DT;
    if (p->inPool == 1) {
        float d = pos[1] - *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640);

        if (d < 0.0f ? -d < 20.0f : d < 20.0f) {
            float r = (d + 20.0f) / 40.0f;

            vel[1] -= ITEM_DT * 0.5f * ITEM_DT * 1.2f * r;
            floatGeo(1.0f - r * 0.08f);
            if (p->wave == 0) {
                CopyVector(q, pos);
                q[1] = *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640);
                EntryStageMultiBgaManager(0x1EC, q, IdentityQuaternion);
            }
        } else if (0.0f < d) {
            vel[1] -= ITEM_DT * 0.5f * ITEM_DT * 1.2f;
            floatGeo(0.92f);
        }
        vel[1] += GetTableSin(p->wave) * 0.1f;
        p->wave += 0x400;
    }
    sceVu0AddVector(npos, pos, vel);
    GetRootQuaternion(q, gobj);
    MultiQuaternion(q, (char *)*(int *)(gobj + 0x15C) + 0x150, q);
    RegularizeQuaternion(q);
    SetRootQuaternion(gobj, q);
    CopyVector(cw.from, pos);
    CopyVector(cw.to, npos);
    cw.radius = 20.0f;
    ClipWall((int)&cw);
    if (cw.wallHit != 0) {
        *(int *)((char *)*(int *)(gobj + 0x15C) + 0x5F4) = GetWallAttribute(&cw);
        GetReflectionElement(&cw, 0.8f, 0.8f);
        CopyVector(npos, cw.f_50);
        CopyVector(vel, cw.f_60);
        if (breakItemOnWallHit(gobj, VectorLength(cw.f_30), npos, vel)) {
            setItemDead(gobj);
        }
    }
    CopyVector(cw.from, pos);
    CopyVector(cw.to, pos);
    cw.from[1] -= 20.0f;
    cw.to[1] += 20.0f;
    ClipFloor(&cw);
    if (cw.floorHit != 0) {
        CopyVector(pos, cw.pos);
        pos[1] -= 20.0f;
    }
    CopyVector(cw.from, pos);
    CopyVector(cw.to, npos);
    cw.from[1] += 20.0f;
    cw.to[1] += 20.0f;
    ClipFloor(&cw);
    if (cw.floorHit != 0) {
        float axis[4];

        *(int *)((char *)*(int *)(gobj + 0x15C) + 0x5F8) = GetFloorAttribute(&cw);
        GetReflectionElement(&cw, 0.8f, 0.7f);
        CopyVector(npos, cw.f_50);
        CopyVector(vel, cw.f_60);
        npos[1] -= 20.0f;
        sceVu0OuterProduct(axis, cw.plane, cw.f_40);
        SetQuaternionByAxisRotate((char *)*(int *)(gobj + 0x15C) + 0x150,
                                  (short)(int)(-VectorLength(cw.f_40) * 521.5189209f), axis[0],
                                  axis[1], axis[2]);
        len = VectorLength(cw.f_30);
        if (breakItemOnFloorHit(gobj, len, npos, vel)) {
            setItemDead(gobj);
        }
        linked = 2;
        link = cw.f_8C;
    } else {
        CopyVector(cw.to, pos);
        CopyVector(cw.from, pos);
        cw.from[1] -= 20.0f;
        cw.to[1] += 20.0f;
        cw.radius = 0;
        ClipFloor(&cw);
        if (cw.floorHit != 0) {
            float n[4];
            float sv[4];

            CopyVector(npos, cw.pos);
            npos[1] = cw.pos[1] - 21.0f;
            cw.plane[3] = 0;
            linked = 1;
            CopyVector(n, cw.plane);
            sceVu0ScaleVector(sv, n, GetDistanceFromPlane(cw.plane, vel) * -2.0f);
            AddVectorXYZ(vel, vel, sv);
            link = cw.f_8C;
        } else {
            cw.to[1] += 10000.0f;
            ClipFloor(&cw);
            if (CheckFieldContact(&cw, gobj, npos, 20.0f) == 2) {
                if (p->inPool != 1) {
                    *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640) =
                        GetPoolGlobalHeight(cw.f_8C.p_0);
                    GetPoolGlobalDrainVector(p->drain, cw.f_8C.p_0);
                }
                *(float *)((char *)*(int *)(gobj + 0x15C) + 0x644) =
                    cw.pos[1] - *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640);
                p->inPool = 1;
            }
        }
    }
    spd = VectorLength(vel);
    grav = ITEM_DT * 0.5f * ITEM_DT;
    if (len0 + (grav + grav) < spd) {
        CopyVector(npos, pos);
        p->released = 0;
        /* emergency stop 2 */
        debug_StdPrintfDummy("緊急停止2(%f←%f)\n", spd, len0);
        p->holder = 0;
        p->sleep = 0;
    }
    if (LimitExistGeometry(npos, vel)) {
        p->released = 0;
        p->holder = 0;
        p->sleep = 0;
        /* emergency stop 3 */
        debug_StdPrintfDummy("緊急停止3\n");
    }
    npos[3] = 1.0f;
    SetDirectRootPosition(gobj, npos);
    CopyVector((char *)*(int *)(gobj + 0x15C) + 0x130, vel);
    if (p->holder != 0) {
        if (VectorLengthSquare(vel) > 100.0f) {
            _AttackCenter((char *)p->holder, 0x12, npos, 0, 20.0f, (int)gobj);
        }
    }
    if (p->sleep != 0) {
        p->sleep = p->sleep - 1;
    }
    if (linked != 0) {
        if (p->spin < 8.0f && p->sleep == 0) {
            int n = p->spinCount + 1;

            p->spinCount = n;
            if (n >= 6) {
                p->spinCount = 0;
                p->released = 0;
                /* vibration sleep */
                debug_StdPrintfDummy("振動睡眠\n");
            }
            p->spin = spd;
        } else {
            p->spin = 0;
            p->spinCount = 0;
        }
    }
    {
        float v = p->spin;

        if (v < spd) {
            v = spd;
        }
        p->spin = v;
    }
    if (p->released == 0 && linked != 0) {
        LinkParentOfDObj(gobj, &link);
    }
}

void execBombGeo(char *gobj)
{
    float v[4];
    ItemWork *rec = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    ItemFuse *q = &rec->fuse;

    switch (q->state) {
    default:
    case 0:
        if (IsTorchLightOn(q->torch)) {
            q->state = 1;
            bombSparkStartSE((int)gobj);
            bombSparkSE((int)gobj);
            rec->fuse.animMode = 1;
        }
        break;
    case 1:
        CopyVector(v, itemDropOfs);
        v[1] =
            itemDropOfs[1] *
            (((float)q->time * (1.0f / ((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) /
                                        60.0f * 300.0f)) +
              1.0f) *
             0.5f);
        CopyVector(((SubHandle *)(q->torch + 0x15C))->p + 0xA0, v);
        q->time = q->time - 1;
        if (q->time == 0) {
            q->state = 2;
        }
        break;
    case 2:
        rec->fuse.animMode = 0;
        stage_SetLoopFlag(511, 0);
        stage_SetFrameStep(0x1FF, 1);
        GetRootPosition(q->pos, gobj);
        _AttackCenter(gobj, 0x11, q->pos, 0, 200.0f, 0);
        LightTorchOff(q->torch);
        *(int *)(q->torch + 0x16C) = 0;
        rec->released = 0;
        StopSEPackage(gobj);
        bombExplodeSE((int)gobj);
        stage_KillPlayBgAnimationIfOverMaxCount(0x1FF, 1);
        q->anim = stage_MakePlayBgAnimation(0x1FF);
        *(float *)(q->anim + 4) = 1.0f;
        _CopyVector(q->anim + 0x20, q->pos);
        CopyQuaternion(q->anim + 0x30, IdentityQuaternion);
        q->state = 3;
        GOBJ_SUB(gobj)->disp = 0;
        break;
    case 3:
        rec->released = 0;
        break;
    case 4:
        break;
    }
}

void ItemGeo(char *gobj)
{
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
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
        char *owner = *(char **)*(int *)(gobj + 0x15C);
        if (owner != 0) {
            if (*(int *)(owner + 0xC) == 0x11) {
                if (GetBoxMode(owner) == 2) {
                    p->holder = 0;
                    ThrowItem(gobj, (char *)*(int *)(owner + 0x15C) + 0x130);
                }
            }
        }
    }
    UpdateRootMatrix(gobj);
    if (IsItemKindBomb(gobj)) {
        execBombGeo(gobj);
    }
}

/* src/item.c:919-932 in the listing: a second static helper with no
   out-of-line copy, inlined only into ItemDL (rows 920, 922, 929, 931).
   The NAME is a reconstruction. */
static inline void checkBombExplodeEnd(char *gobj)
{
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    ItemFuse *q = &p->fuse;

    if (q->state == 3) {
        if (stage_DispBgAnimation(&p->fuse.anim) != 0) {
            q->state = 4;
            setItemDead(gobj);
        }
    }
}

void ItemDL(char *gobj)
{
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

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
                bombSparkSE((int)gobj);
                q->animMode = mode;
            }
        }
    }
    p2o_DispVU1(gobj);
}

/* INTERIM stand-in: GetItemKind is a real TU function with its own ROM slot
   (matched below), but the compiler inlines it into BreakItemFromOutside.
   Delete it and mark the real definition `inline` once this TU is C-complete. */
static inline int GetItemKindInline(char *gobj)
{
    return *(int *)((char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830) + 4);
}

int BreakItemFromOutside(char *gobj)
{
    float pos[4];
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (IsItemKindBomb(gobj)) {
        p->fuse.state = 2;
    } else {
        GetRootPosition(pos, gobj);
        entryBreakBgAnimation(itemKind[p->kind].f_10, pos, ZeroVector, 0);
        ExecuteSEPackage((int)gobj, 0x2B);
        if (GetItemKindInline(gobj) == 6) {
            _AttackCenter(gobj, 0x11, pos, 0, 200.0f, 0);
        }
        setItemDead(gobj);
    }
    return 0;
}

int CheckCarryableItem(char *a0)
{
    int r = 0;
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(a0)->work;
    if (*(int *)(a0 + 0x16C) != 0) {
        if (*(long long *)&p->released == 0) {
            if (p->fuse.state < 2) {
                r = 1;
            }
        }
    }
    return r;
}

int GetItemKind(char *a0)
{
    return *(int *)((char *)GOBJ_SUB(a0)->work + 4);
}

int GetCharHeldItem(char *a0)
{
    char *w;
    if (a0 == 0)
        return -1;
    w = *(char **)(*(char **)(a0 + 0x164) + 0x154);
    if (w == 0)
        return -1;
    return *(int *)((char *)GOBJ_SUB(w)->work + 4);
}

int IsItemHoldable(char *a0)
{
    return *(int *)((char *)GOBJ_SUB(a0)->work) == 0;
}

int IsBombExplode(char *a0)
{
    return *(int *)((char *)GOBJ_SUB(a0)->work + 0x48) == 2;
}

void *GetBombTorchGObj(char *a0)
{
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(a0)->work;
    if (IsItemKindBomb(a0)) {
        return p->fuse.torch;
    }
    return 0;
}

/* INTERIM stand-in: CheckCarryableItem is a real TU function with its own ROM
   slot (matched above), but the compiler inlines it into the four Revive
   walkers.  Delete it and mark the real definition `inline` once this TU is
   C-complete. */
static inline int CheckCarryableItemInline(char *a0)
{
    int r = 0;
    ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(a0)->work;
    if (*(int *)(a0 + 0x16C) != 0) {
        if (*(long long *)&p->released == 0) {
            if (p->fuse.state < 2) {
                r = 1;
            }
        }
    }
    return r;
}

int ReviveAllCarryableItems(void)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (CheckCarryableItemInline(g)) {
            ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(g)->work;
            UnlinkParentOfDObj(g);
            p->released = 1;
            p->sleep = 0;
        }
    }
    return 1;
}

int ReviveCarryableItemsWithBoundary(void *center, float radius)
{
    char *g;
    float pos[4];
    float r2 = radius * radius;

    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        GetRootPosition(pos, g);
        if (distance_squared(pos, center) < r2) {
            if (CheckCarryableItemInline(g)) {
                ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(g)->work;
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
    char *g;

    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        short ang = random_unit() * 65536.0f;

        if (CheckCarryableItemInline(g)) {
            ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(g)->work;
            UnlinkParentOfDObj(g);
            p->released = 1;
            p->sleep = 0;
        }
        *(float *)((char *)*(int *)(g + 0x15C) + 0x130) = horz * GetTableSin(ang);
        *(float *)((char *)*(int *)(g + 0x15C) + 0x134) = up * random_unit();
        *(float *)((char *)*(int *)(g + 0x15C) + 0x138) = horz * GetTableCos(ang);
    }
    return 1;
}

int CheckItemDead(char *a0)
{
    int r = 0;
    if (*(int *)((char *)GOBJ_SUB(a0)->work) == 1 || *(int *)(a0 + 0x16C) == 0) {
        r = 1;
    }
    return r;
}

/* explosion animation stop handling planned.  It is a named object, not a
   literal at the use site: the compiler emits it after execBombGeo's switch
   table, which is where the ROM has it. */
static const char bombAnimStopMsg[] = "爆発アニメーション停止処理予定\n";

void StopItemExplodeAnimationAll(void)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(g)->work;
        if (IsItemKindBomb(g)) {
            if (p->fuse.state == 3) {
                if (stage_DispBgAnimation(&p->fuse.anim) == 0) {
                    debug_StdPrintfDummy(bombAnimStopMsg);
                }
            }
        }
    }
}

int BreakItemWithAttackHit(char *gobj, float *dir)
{
    float pos[4];
    ItemWork *p = (ItemWork *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (!IsItemKindBomb(gobj)) {
        GetRootPosition(pos, gobj);
        if (entryBreakBgAnimation(itemKind[p->kind].f_14, pos, dir, itemKind[p->kind].f_18)) {
            ExecuteSEPackage((int)gobj, 0x2B);
            setItemDead(gobj);
        }
    }
    return 0;
}

int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(19); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (CheckCarryableItemInline(g)) {
            ItemWork *p = (ItemWork *)(char *)GOBJ_SUB(g)->work;
            UnlinkParentOfDObj(g);
            p->released = 1;
            p->sleep = nonSleepFrame;
        }
    }
    return 1;
}
