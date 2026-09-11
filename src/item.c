#include "common.h"
#include "sugiCommon.h"

extern void ExecuteSEPackage(int a0, int a1);

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
    char *p = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    return *(int *)(p + 4) == 1;
}

extern void debug_StdPrintfDummy(char *fmt, ...);
extern void debug_assert(const char *file, int line);
extern void __assert(const char *file, int line, char *expr);
extern void SetIdentityQuaternion(void *q);
extern void SetRootQuaternion(void *gobj, void *q);
extern void GetRootQuaternion(void *dst, void *gobj);
extern void GetInverseQuaternion(void *dst, void *src);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern char D_0061FA20[];
extern const char D_0061FA48[];
extern char D_0063B8E0[];
extern float D_002907E0[4];

void HoldItem(char *gobj, char *holder)
{
    float q[4];
    float hq[4];
    char *p;

    if (gobj == 0) {
        debug_StdPrintfDummy(D_0061FA20);
        debug_assert(D_0061FA48, 0x164);
        __assert(D_0061FA48, 0x164, D_0063B8E0);
    }
    p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    *(int *)(p + 8) = 0;
    *(int *)(p + 0xC) = 1;
    *(char **)(p + 0x14) = holder;
    *(int *)(*(int *)(gobj + 0x15C) + 0x74) = 0;
    SetIdentityQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150);
    if (IsItemKindBomb(gobj)) {
        SetRootQuaternion(gobj, D_002907E0);
    }
    GetRootQuaternion(q, gobj);
    GetRootQuaternion(hq, holder);
    GetInverseQuaternion(hq, hq);
    MultiQuaternion(p + 0x20, hq, q);
}

extern int stage_DispBgAnimation(void *slot);

/* src/item.c:266-271 in the January-2002 listing: a static helper with no
   out-of-line copy of its own, inlined into uncarriedItemGeo, ItemDL,
   BreakItemFromOutside and BreakItemWithAttackHit (rows 267 to 270).
   The NAME is a reconstruction; the listing carries no symbol for it. */
static inline void setItemDead(char *gobj)
{
    char *w = (char *)*(int *)(gobj + 0x15C);
    char *p = (char *)*(int *)(w + 0x830);

    *(int *)(w + 0x74) = 0;
    *(int *)p = 1;
    *(int *)(gobj + 0x16C) = 0;
}

extern void ClipWall(int arg);
extern float D_004EB500[48];
extern void GetRootPosition(void *a0, char *outer);
extern void SetDirectRootPositionNoFitting();

void avoidInsideOfWall(void *self, int arg)
{
    char *p;
    if (arg == 0)
        return;
    p = (char *)D_004EB500;
    GetRootPosition(p, arg);
    GetRootPosition(p + 0x10, (int)self);
    ClipWall((int)p);
    if (*(int *)(p + 0x88) == 0)
        return;
    SetDirectRootPositionNoFitting(self, p + 0x20);
}

extern void CopyVector(void *dst, void *src);
extern void SetIdentityQuaternion(void *q);
extern float D_004EB4E0[4];

void ReleaseItem(char *gobj)
{
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    avoidInsideOfWall(gobj, *(int *)(p + 0x14));
    *(int *)(p + 8) = 1;
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x10) = 0;
    *(int *)(*(int *)(gobj + 0x15C) + 0x74) = 1;
    CopyVector((char *)*(int *)(gobj + 0x15C) + 0x130, D_004EB4E0);
    SetIdentityQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150);
}

extern void _ScaleVectorXYZ(void *dst, void *src, float k);
extern int D_0028F4C0[];

void ThrowItem(char *gobj, void *vel)
{
    char *p = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    avoidInsideOfWall(gobj, *(int *)(p + 0x14));
    *(int *)(p + 8) = 1;
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x10) = 1;
    _ScaleVectorXYZ(*(char **)(gobj + 0x15C) + 0x130, vel,
                    30.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]));
    SetIdentityQuaternion(*(char **)(gobj + 0x15C) + 0x150);
}

extern int iosMallocDebug(int handle, int size, const char *file, int line);
extern int D_0063A438;
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
extern void SetTorchChainReactionFlag(char *gobj, int flag);
extern void LinkParentOfDObj(void *gobj, void *link);
extern void gamesysObjInfoCls(int kind, int no);
extern float D_004EB4F0[4];

typedef union {
    float f[4];
    long long ll[2];
} ItemVec;

typedef union {
    int i;
    char *p;
} SubHandle;

/* 0xA0: the item record's .data initialiser, copied over the fresh
   allocation.  The listing attributes the block move to line 262. */
typedef struct {
    ItemVec v[10];
} ItemWorkImage;

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

extern ItemWorkImage D_004EB440;

char *InitItemGeo(char *gobj, ItemLayout *layout)
{
    ItemParentLink link;
    ItemLayout lay;
    char *w = (char *)*(int *)(gobj + 0x15C);
    char *p = (char *)iosMallocDebug(D_0063A438, 0xA0, D_0061FA48, 446);

    *(char **)((char *)*(int *)(gobj + 0x15C) + 0x830) = p;
    *(ItemWorkImage *)p = D_004EB440;
    *(int *)(p + 4) = layout->f_30;
    *(int *)(w + 0x78) = 0;
    if (*(int *)(p + 4) == 1) {
        char *rec = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
        char *g;

        link.p_0 = gobj;
        link.f_4 = 0;
        lay = *layout;
        lay.f_30 = 2;
        g = CreateLayoutedGObj(10, 0x4B, -1, 1, &lay, -1, 7, 0);
        SetTorchChainReactionFlag(g, 1);
        LinkParentOfDObj(g, &link);
        CopyVector((char *)*(int *)(g + 0x15C) + 0xA0, D_004EB4F0);
        *(char **)(rec + 0x40) = g;
        *(int *)(rec + 0x44) =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 300.0f);
    }
    gamesysObjInfoCls(*(int *)(gobj + 0xC), *(int *)(gobj + 8));
    return p;
}

extern void *memset(void *p, int c, int n);
extern void RotQuaternionY(void *q, short ang);
extern void CopyQuaternion(void *dst, void *src);

INCLUDE_ASM("asm/nonmatchings/src/item", carriedItemGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", floatGeo);
INCLUDE_ASM("asm/nonmatchings/src/item", uncarriedItemGeo);

extern void StopSEPackage(void *gobj);
extern int IsTorchLightOn(char *torch);
extern void stage_SetLoopFlag(int anim, int flag);
extern void stage_SetFrameStep(int anim, int step);
extern void LightTorchOff(char *torch);
extern void stage_KillPlayBgAnimationIfOverMaxCount(int anim, int flag);
extern char *stage_MakePlayBgAnimation(int anim);
extern void _CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind);

void execBombGeo(char *gobj)
{
    float v[4];
    char *rec = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    char *q = rec + 0x40;

    switch (*(int *)(q + 8)) {
    default:
    case 0:
        if (IsTorchLightOn(*(char **)q)) {
            *(int *)(q + 8) = 1;
            bombSparkStartSE((int)gobj);
            bombSparkSE((int)gobj);
            *(int *)(rec + 0x64) = 1;
        }
        break;
    case 1:
        CopyVector(v, D_004EB4F0);
        v[1] = D_004EB4F0[1] *
               (((float)*(int *)(q + 4) *
                     (1.0f /
                      ((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 300.0f)) +
                 1.0f) *
                0.5f);
        CopyVector(((SubHandle *)(*(char **)q + 0x15C))->p + 0xA0, v);
        *(int *)(q + 4) = *(int *)(q + 4) - 1;
        if (*(int *)(q + 4) == 0) {
            *(int *)(q + 8) = 2;
        }
        break;
    case 2:
        *(int *)(rec + 0x64) = 0;
        stage_SetLoopFlag(0x1FF, 0);
        stage_SetFrameStep(0x1FF, 1);
        GetRootPosition(q + 0x10, gobj);
        _AttackCenter(gobj, 0x11, (float *)(q + 0x10), 0, 200.0f, 0);
        LightTorchOff(*(char **)q);
        *(int *)(*(char **)q + 0x16C) = 0;
        *(int *)(rec + 8) = 0;
        StopSEPackage(gobj);
        bombExplodeSE((int)gobj);
        stage_KillPlayBgAnimationIfOverMaxCount(0x1FF, 1);
        *(char **)(q + 0x20) = stage_MakePlayBgAnimation(0x1FF);
        *(float *)(*(char **)(q + 0x20) + 4) = 1.0f;
        _CopyVector(*(char **)(q + 0x20) + 0x20, q + 0x10);
        CopyQuaternion(*(char **)(q + 0x20) + 0x30, D_002907E0);
        *(int *)(q + 8) = 3;
        *(int *)(*(int *)(gobj + 0x15C) + 0x74) = 0;
        break;
    case 3:
        *(int *)(rec + 8) = 0;
        break;
    case 4:
        break;
    }
}

extern void carriedItemGeo(char *gobj);
extern void uncarriedItemGeo(char *gobj);
extern void execBombGeo(char *gobj);
extern int GetBoxMode(char *gobj);
extern void UpdateRootMatrix(void *gobj);

void ItemGeo(char *gobj)
{
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    if (*(int *)p == 1) {
        return;
    }
    if (*(int *)(p + 0xC) != 0) {
        carriedItemGeo(gobj);
    } else if (*(int *)(p + 8) != 0) {
        int held = *(int *)(*(int *)(gobj + 0x15C) + 0x74);
        *(int *)(*(int *)(gobj + 0x15C) + 0x74) = 0;
        uncarriedItemGeo(gobj);
        if (held != 0) {
            *(int *)(*(int *)(gobj + 0x15C) + 0x74) = 1;
        }
    } else {
        char *owner = *(char **)*(int *)(gobj + 0x15C);
        if (owner != 0) {
            if (*(int *)(owner + 0xC) == 0x11) {
                if (GetBoxMode(owner) == 2) {
                    *(int *)(p + 0x14) = 0;
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

extern void p2o_DispVU1(void *gobj);
extern int D_0028F4D4[];

/* src/item.c:919-932 in the listing: a second static helper with no
   out-of-line copy, inlined only into ItemDL (rows 920, 922, 929, 931).
   The NAME is a reconstruction. */
static inline void checkBombExplodeEnd(char *gobj)
{
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    char *q = p + 0x40;

    if (*(int *)(q + 8) == 3) {
        if (stage_DispBgAnimation(p + 0x60) != 0) {
            *(int *)(q + 8) = 4;
            setItemDead(gobj);
        }
    }
}

void ItemDL(char *gobj)
{
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (IsItemKindBomb(gobj)) {
        checkBombExplodeEnd(gobj);
    }
    if (*(int *)p == 1) {
        return;
    }
    if (IsItemKindBomb(gobj)) {
        char *q = p + 0x40;
        int mode = *(int *)(q + 8);

        if (mode >= 2) {
            return;
        }
        if (mode == 1) {
            if (D_0028F4D4[0] != 0) {
                if (*(int *)(q + 0x24) != 0) {
                    StopSEPackage(gobj);
                    *(int *)(q + 0x24) = 0;
                }
            } else if (*(int *)(q + 0x24) == 0) {
                bombSparkSE((int)gobj);
                *(int *)(q + 0x24) = mode;
            }
        }
    }
    p2o_DispVU1(gobj);
}

extern void _NormalizeVector(void *dst, void *src);
extern short GetTableArcTan2(float x, float z);
extern void EntryStageMultiBgaManagerWithStay(int id, void *pos, void *rot, int arg);

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

extern ItemBreakRec D_004FB970[];

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

extern float D_0028FEF0[4];

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
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (IsItemKindBomb(gobj)) {
        *(int *)(p + 0x48) = 2;
    } else {
        GetRootPosition(pos, gobj);
        entryBreakBgAnimation(D_004FB970[*(int *)(p + 4)].f_10, pos, D_0028FEF0, 0);
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
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(a0 + 0x16C) != 0) {
        if (*(long long *)(p + 8) == 0) {
            if (*(int *)(p + 0x48) < 2) {
                r = 1;
            }
        }
    }
    return r;
}

int GetItemKind(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4);
}

int GetCharHeldItem(char *a0)
{
    char *w;
    if (a0 == 0)
        return -1;
    w = *(char **)(*(char **)(a0 + 0x164) + 0x154);
    if (w == 0)
        return -1;
    return *(int *)(*(char **)(*(char **)(w + 0x15C) + 0x830) + 4);
}

int IsItemHoldable(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) == 0;
}

int IsBombExplode(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x48) == 2;
}

void *GetBombTorchGObj(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (IsItemKindBomb(a0)) {
        return *(void **)(p + 0x40);
    }
    return 0;
}

extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *g);

/* INTERIM stand-in: CheckCarryableItem is a real TU function with its own ROM
   slot (matched above), but the compiler inlines it into the four Revive
   walkers.  Delete it and mark the real definition `inline` once this TU is
   C-complete. */
static inline int CheckCarryableItemInline(char *a0)
{
    int r = 0;
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(a0 + 0x16C) != 0) {
        if (*(long long *)(p + 8) == 0) {
            if (*(int *)(p + 0x48) < 2) {
                r = 1;
            }
        }
    }
    return r;
}

extern void UnlinkParentOfDObj(void *dobj);

int ReviveAllCarryableItems(void)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(0x13); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (CheckCarryableItemInline(g)) {
            char *p = *(char **)(*(char **)(g + 0x15C) + 0x830);
            UnlinkParentOfDObj(g);
            *(int *)(p + 8) = 1;
            *(int *)(p + 0x74) = 0;
        }
    }
    return 1;
}

int ReviveCarryableItemsWithBoundary(void *center, float radius)
{
    char *g;
    float pos[4];
    float r2 = radius * radius;

    for (g = isysGObjSearchFromObjKindID_begin(0x13); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        GetRootPosition(pos, g);
        if (distance_squared(pos, center) < r2) {
            if (CheckCarryableItemInline(g)) {
                char *p = *(char **)(*(char **)(g + 0x15C) + 0x830);
                UnlinkParentOfDObj(g);
                *(int *)(p + 8) = 1;
                *(int *)(p + 0x74) = 0;
            }
        }
    }
    return 1;
}

extern float GetTableSin(short a);
extern float GetTableCos(short a);

int ReviveAllCarryableItemsWithRandomVelocity(float up, float horz)
{
    char *g;

    for (g = isysGObjSearchFromObjKindID_begin(0x13); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        short ang = random_unit() * 65536.0f;

        if (CheckCarryableItemInline(g)) {
            char *p = *(char **)(*(char **)(g + 0x15C) + 0x830);
            UnlinkParentOfDObj(g);
            *(int *)(p + 8) = 1;
            *(int *)(p + 0x74) = 0;
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
    if (*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) == 1 || *(int *)(a0 + 0x16C) == 0) {
        r = 1;
    }
    return r;
}

extern void debug_StdPrintfDummy(char *fmt, ...);
extern char D_0061FAA8[];

void StopItemExplodeAnimationAll(void)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(0x13); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        char *p = *(char **)(*(char **)(g + 0x15C) + 0x830);
        if (IsItemKindBomb(g)) {
            if (*(int *)(p + 0x48) == 3) {
                if (stage_DispBgAnimation(p + 0x60) == 0) {
                    debug_StdPrintfDummy(D_0061FAA8);
                }
            }
        }
    }
}

int BreakItemWithAttackHit(char *gobj, float *dir)
{
    float pos[4];
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (!IsItemKindBomb(gobj)) {
        GetRootPosition(pos, gobj);
        if (entryBreakBgAnimation(D_004FB970[*(int *)(p + 4)].f_14, pos, dir,
                                  D_004FB970[*(int *)(p + 4)].f_18)) {
            ExecuteSEPackage((int)gobj, 0x2B);
            setItemDead(gobj);
        }
    }
    return 0;
}

int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame)
{
    char *g;
    for (g = isysGObjSearchFromObjKindID_begin(0x13); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (CheckCarryableItemInline(g)) {
            char *p = *(char **)(*(char **)(g + 0x15C) + 0x830);
            UnlinkParentOfDObj(g);
            *(int *)(p + 8) = 1;
            *(int *)(p + 0x74) = nonSleepFrame;
        }
    }
    return 1;
}
