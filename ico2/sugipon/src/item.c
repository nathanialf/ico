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

typedef union {
    float f[4];
    long long ll[2];
} __attribute__((aligned(16))) Vec16;

extern void *memset(void *p, int c, int n);
extern int GetSkeltonFocusNode(char *obj, int kind);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *m);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);
extern void MatrixDrive_GetTurnZAngleYX(unsigned short *y, unsigned short *x, float vx, float vy,
                                        float vz);
extern void SetDirectRootPosition(char *gobj, void *pos);
extern void RotQuaternionX(void *q, short ang);
extern void RotQuaternionY(void *q, short ang);
extern void CopyQuaternion(void *dst, void *src);
extern char *D_00639EA8;
extern float D_004EB5C0[4];
extern float D_004EB5D0[4];

/* The holder's 0x15C sub-handle is read through the SubHandle union at every
   site in this function: the ROM keeps the three-load chain of line 511 below
   the `q[2] = 0` store, which only happens when the 0x15C read carries alias
   set 0.  `q` itself is a plain four-float scratch, so its store does NOT
   carry alias set 0 and the `rec->f_14` load above it is free to move. */
void carriedItemGeo(char *gobj)
{
    Vec16 pos;
    float q[4] __attribute__((aligned(16)));
    float m[16] __attribute__((aligned(16)));
    Vec16 wpos;
    Vec16 rot;
    Vec16 up;
    unsigned short ang[2];
    Vec16 adj;
    char *rec = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0x604) != 0) {
        int isPlayer = *(char **)(rec + 0x14) == D_00639EA8;
        int node = isPlayer ? 6 : 22;

        if (isPlayer) {
            _ApplyMatrix(
                &pos,
                (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0xC) +
                    GetSkeltonFocusNode(*(char **)(rec + 0x14), node) * 0x40,
                D_004EB5C0);
        } else {
            _ApplyMatrix(
                &pos,
                (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0xC) +
                    GetSkeltonFocusNode(*(char **)(rec + 0x14), node) * 0x40,
                D_004EB5D0);
        }
        CopyQuaternion(
            q, (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0x10) +
                   GetSkeltonFocusNode(*(char **)(rec + 0x14), node) * 0x10);
        if (isPlayer) {
            RotQuaternionX(q, -16384);
        } else {
            RotQuaternionX(q, 16384);
        }
        SetRootQuaternion(gobj, q);
    } else {
        int node = GetSkeltonFocusNode(*(char **)(rec + 0x14), 1);

        CopyVector(
            &wpos,
            (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0xC) +
                GetSkeltonFocusNode(*(char **)(rec + 0x14), 22) * 0x40 + 0x30);
        MatrixDrive_SetTransposeMatrix(
            m, (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0xC) +
                   node * 0x40);
        _ApplyMatrix(q, m, &wpos);
        q[2] = 0.0f;
        _ApplyMatrix(
            &pos,
            (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0xC) +
                node * 0x40,
            q);
        memset(&up, 0, 16);
        up.f[1] = 1.0f;
        sceVu0ApplyMatrix(
            &up,
            (char *)*(int *)((char *)((SubHandle *)(*(char **)(rec + 0x14) + 0x15C))->i + 0xC) +
                GetSkeltonFocusNode(*(char **)(rec + 0x14), 44) * 0x40,
            &up);
        MatrixDrive_GetTurnZAngleYX(&ang[0], &ang[1], up.f[0], up.f[1], up.f[2]);
        CopyQuaternion(&rot, rec + 0x20);
        SetIdentityQuaternion(&adj);
        RotQuaternionY(&adj, -ang[0]);
        RotQuaternionX(&adj, ang[1]);
        MultiQuaternion(&rot, &adj, &rot);
        SetRootQuaternion(gobj, &rot);
    }
    SetDirectRootPosition(gobj, &pos);
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

/* 0x60..0x120 of uncarriedItemGeo's frame and the whole of floatGeo's: the
   192-byte workspace ClipWall / ClipFloor / ClipWallWaveForce / CheckFieldContact
   fill in.  It is the same record avoidInsideOfWall drives through D_004EB500,
   whose +0x88 hit flag and +0x20 result position that function already names. */
/* The per-frame step this TU derives from the frame-rate pair at D_0028F4C0;
   ThrowItem and InitItemGeo spell the same integer quotient out. */
#define ITEM_DT (60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]))

typedef struct DObjLink {
    char *p_0;
    int f_4;
} DObjLink;

typedef struct ClipWork {
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
} ClipWork;

extern void _ScaleVector(void *dst, void *src, float k);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void AddVectorXYZ(void *dst, void *a, void *b);
extern void GetSlerpQuaternion(void *dst, void *a, void *b, float t);
extern void RegularizeQuaternion(void *q);
extern void ClipWallWaveForce(void *w);
extern void ClipFloor(void *w);
extern float GetDistanceFromPlane(void *plane, void *v);
extern float VectorLength(void *v);
extern float VectorLengthSquare(void *v);
extern void UnlinkParentOfDObj(void *gobj);
extern int GetWallAttribute(void *w);
extern int GetFloorAttribute(void *w);
extern void GetReflectionElement(void *w, float a, float b);
extern int CheckFieldContact(void *w, char *gobj, void *pos, float r);
extern float GetPoolGlobalHeight(char *field);
extern void GetPoolGlobalDrainVector(void *dst, char *field);
extern int LimitExistGeometry(void *pos, void *vel);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0ScaleVector(void *dst, void *src, float k);
extern void sceVu0OuterProduct(void *dst, void *a, void *b);
extern void SetQuaternionByAxisRotate(void *q, short ang, float x, float y, float z);
extern void EntryStageMultiBgaManager(int id, void *pos, void *rot);
extern void EntryStageMultiBgaManagerSensitiveWithStay(int id, void *pos, void *rot, void *vel,
                                                       int arg);
extern void SetParticleEffect(int kind, void *pos, void *rot);
extern void ExecuteSEPackageWithVolumeRate(int gobj, int id, float rate);
extern int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind);
extern float GetTableSin(short a);
extern char D_0061FA58[];
extern char D_0061FA70[];
extern char D_0061FA80[];

/* src/item.c:135-178 in the January-2002 listing: a static helper with no
   out-of-line copy, inlined only into uncarriedItemGeo's wall-hit arm.
   The NAME is a reconstruction; the listing carries no symbol for it. */
static inline int breakItemOnWallHit(char *gobj, float len, float *pos, float *vel)
{
    float rot[4];
    float d[4];
    float sv[4];
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (5.0f < len) {
        int id = D_004FB970[*(int *)(p + 4)].f_0;

        if (id != 0x3CC) {
            memset(&rot, 0, 16);
            rot[3] = 1.0f;
            CopyVector(d, vel);
            d[1] = 0.0f;
            _NormalizeVector(d, d);
            RotQuaternionY(&rot, GetTableArcTan2(d[0], d[2]));
            _ScaleVectorXYZ(sv, vel, 0.3f);
            EntryStageMultiBgaManagerSensitiveWithStay(id, pos, &rot, sv,
                                                       D_004FB970[*(int *)(p + 4)].f_4);
            SetParticleEffect(10, pos, &rot);
        }
        if ((D_004FB970 + *(int *)(p + 4))->f_1C & 1) {
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
    char *p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);

    if (10.0f < len) {
        entryBreakBgAnimation(D_004FB970[*(int *)(p + 4)].f_8, pos, vel,
                              D_004FB970[*(int *)(p + 4)].f_C);
        if ((D_004FB970 + *(int *)(p + 4))->f_1C & 1) {
            ExecuteSEPackage((int)gobj, 0x2B);
            return 1;
        }
    }
    if (*(int *)(p + 0x10) == 0) {
        *(int *)(p + 0x10) = 1;
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
    char *p;       /* 0x40 */

    void floatGeo(float t)
    {
        ClipWork w;

        _ScaleVector(vel, vel, t);
        _AddVectorXYZ(vel, vel, p + 0x80);
        GetSlerpQuaternion((char *)*(int *)(gobj + 0x15C) + 0x150,
                           (char *)*(int *)(gobj + 0x15C) + 0x150, D_002907E0, t);
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

    float q[4];  /* 0x50 */
    ClipWork cw; /* 0x60 */
    int linked = 0;
    float len0;
    float len;
    float spd;
    float grav;

    p = (char *)*(int *)(*(int *)(gobj + 0x15C) + 0x830);
    *(int *)((char *)*(int *)(gobj + 0x15C) + 0x5F4) = 0;
    *(int *)((char *)*(int *)(gobj + 0x15C) + 0x5F8) = 0;
    CopyVector(vel, (char *)*(int *)(gobj + 0x15C) + 0x130);
    len0 = VectorLength(vel);
    UnlinkParentOfDObj(gobj);
    GetRootPosition(pos, gobj);
    vel[1] += ITEM_DT * 0.5f * ITEM_DT;
    if (*(int *)(p + 0x70) == 1) {
        float d = pos[1] - *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640);

        if (d < 0.0f ? -d < 20.0f : d < 20.0f) {
            float r = (d + 20.0f) / 40.0f;

            vel[1] -= ITEM_DT * 0.5f * ITEM_DT * 1.2f * r;
            floatGeo(1.0f - r * 0.08f);
            if (*(short *)(p + 0x90) == 0) {
                CopyVector(q, pos);
                q[1] = *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640);
                EntryStageMultiBgaManager(0x1EC, q, D_002907E0);
            }
        } else if (0.0f < d) {
            vel[1] -= ITEM_DT * 0.5f * ITEM_DT * 1.2f;
            floatGeo(0.92f);
        }
        vel[1] += GetTableSin(*(short *)(p + 0x90)) * 0.1f;
        *(short *)(p + 0x90) += 0x400;
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
                if (*(int *)(p + 0x70) != 1) {
                    *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640) =
                        GetPoolGlobalHeight(cw.f_8C.p_0);
                    GetPoolGlobalDrainVector(p + 0x80, cw.f_8C.p_0);
                }
                *(float *)((char *)*(int *)(gobj + 0x15C) + 0x644) =
                    cw.pos[1] - *(float *)((char *)*(int *)(gobj + 0x15C) + 0x640);
                *(int *)(p + 0x70) = 1;
            }
        }
    }
    spd = VectorLength(vel);
    grav = ITEM_DT * 0.5f * ITEM_DT;
    if (len0 + (grav + grav) < spd) {
        CopyVector(npos, pos);
        *(int *)(p + 8) = 0;
        debug_StdPrintfDummy(D_0061FA58, spd, len0);
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x74) = 0;
    }
    if (LimitExistGeometry(npos, vel)) {
        *(int *)(p + 8) = 0;
        *(int *)(p + 0x14) = 0;
        *(int *)(p + 0x74) = 0;
        debug_StdPrintfDummy(D_0061FA70);
    }
    npos[3] = 1.0f;
    SetDirectRootPosition(gobj, npos);
    CopyVector((char *)*(int *)(gobj + 0x15C) + 0x130, vel);
    if (*(int *)(p + 0x14) != 0) {
        if (VectorLengthSquare(vel) > 100.0f) {
            _AttackCenter(*(char **)(p + 0x14), 0x12, npos, 0, 20.0f, (int)gobj);
        }
    }
    if (*(int *)(p + 0x74) != 0) {
        *(int *)(p + 0x74) = *(int *)(p + 0x74) - 1;
    }
    if (linked != 0) {
        if (*(float *)(p + 0x30) < 8.0f && *(int *)(p + 0x74) == 0) {
            int n = *(int *)(p + 0x34) + 1;

            *(int *)(p + 0x34) = n;
            if (n >= 6) {
                *(int *)(p + 0x34) = 0;
                *(int *)(p + 8) = 0;
                debug_StdPrintfDummy(D_0061FA80);
            }
            *(float *)(p + 0x30) = spd;
        } else {
            *(float *)(p + 0x30) = 0;
            *(int *)(p + 0x34) = 0;
        }
    }
    {
        float v = *(float *)(p + 0x30);

        if (v < spd) {
            v = spd;
        }
        *(float *)(p + 0x30) = v;
    }
    if (*(int *)(p + 8) == 0 && linked != 0) {
        LinkParentOfDObj(gobj, &link);
    }
}

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
