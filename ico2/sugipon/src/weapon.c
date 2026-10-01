#include "debug.h"
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

/* The work record InitWeaponGeo and InitDemoQueensSword allocate and the
   template they initialise it from: 224 bytes, 8-aligned (ROM copies it 32
   bytes at a time with ld/sd pairs).  The fields are the ones this file
   reads; the names are ours. */
typedef struct {
    int kind;            /* 0x00: the switch in InitWeaponGeo */
    int state;           /* 0x04: 2 while the weapon falls from a fumble */
    char *holder;        /* 0x08: the holding object, 0 when none */
    int holderId;        /* 0x0C: -1 when none */
    float hit[4][4];     /* 0x10: checkHit's positions at 0x20, 0x30, 0x40 */
    int count;           /* 0x50 */
    char **objs;         /* 0x54 */
    char *buf;           /* 0x58 */
    char *sword;         /* 0x5C */
    int fumbleTime;      /* 0x60 */
    int fumbleFrame;     /* 0x64 */
    float fumbleSpeed;   /* 0x68 */
    int f6C;             /* 0x6C */
    float fumbleFrom[4]; /* 0x70 */
    float fumbleTo[4];   /* 0x80 */
    float fumbleQuat[4]; /* 0x90 */
    int fumbleSlot;      /* 0xA0: the drop-table row, 0 to 6 */
    int fA4;             /* 0xA4 */
    float fA8;           /* 0xA8 */
    float fAC;           /* 0xAC */
    char *net;           /* 0xB0 */
    char *model0;        /* 0xB4 */
    char *model1;        /* 0xB8 */
    int fBC;             /* 0xBC */
    int offsetMode;      /* 0xC0: SetWeaponOffsetMode */
    int fC4[3];          /* 0xC4 */
    float vD0[4];        /* 0xD0 */
} __attribute__((aligned(8))) WeaponWork;

void torchOnOfWeaponSE(int a0)
{
    ExecuteSEPackage(a0, 0x42);
}

void torchOffOfWeaponSE(int a0)
{
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x43);
}

void weaponHitReactionSE(int a0)
{
    ExecuteSEPackage(a0, 0x44);
}

void weaponFumbleSE(int a0)
{
    ExecuteSEPackage(a0, 0x5C);
}

void weaponStickSE(int a0)
{
    ExecuteSEPackage(a0, 0x5D);
}

/* INTERIM NAME, chosen and not recovered: the PAL listing carries this
   file-static helper at weapon.c:262-265 and inlines it here, so it has no
   census row and no name of its own in any map. */
static inline void releaseWeaponHolder(WeaponWork *w)
{
    if (w->holder != 0) {
        *(int *)(*(char **)(w->holder + 0x15C) + 0x630) = 0;
    }
    w->holderId = -1;
}

void ReleaseWeaponWithFumbleTargetPos(char *g, void *pos, void *quat, void *rot, float t)
{
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;

    releaseWeaponHolder(w);
    w->state = 2;
    w->holder = 0;
    if (rot != 0) {
        CopyQuaternion((char *)p + 0x150, rot);
    }
    w->fumbleTime = (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * t);
    w->fumbleFrame = 0;
    GetRootPosition(w->fumbleFrom, g);
    CopyVector(w->fumbleTo, pos);
    CopyQuaternion(w->fumbleQuat, quat);
    w->fumbleSpeed = (w->fumbleTo[1] - w->fumbleFrom[1]) / t - t * 490.0f;
    weaponFumbleSE((int)g);
}

/* One row of the fumble drop table: a target position and the three angles the
   dropped weapon is turned by, 24 bytes, three rows to a weapon slot. */
typedef struct {
    float x;    /* 0x00 */
    float y;    /* 0x04 */
    float z;    /* 0x08 */
    float rotY; /* 0x0C */
    float rotX; /* 0x10 */
    float rotZ; /* 0x14 */
} FumbleRow;

/* RECONSTRUCTION: the position vector this function builds and hands on. The
   ROM copies it with two ld/sd pairs, so the type is 8-byte aligned; it is
   built by aggregate initialisers, whose stores into the initialiser's
   temporary are what make every component re-read the slot index. */
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) FumbleVec;

extern FumbleRow D_0054A040[][3];

/* INTERIM NAME, chosen and not recovered: the PAL listing carries this file
   static at weapon.c:310-320 and inlines it here, so it has no census row and
   no name of its own in any map. */
static inline int fumbleTargetBlocked(FumbleVec *p)
{
    char *o;
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

#define FUMBLE_ROW(i, w) (&D_0054A040[(w)->fumbleSlot][i])

int ReleaseWeaponWithFumbleSequential(char *g)
{
    WeaponWork *w = GOBJ_SUB(g)->work;
    FumbleVec a;
    int i;

    for (i = 0; i < 3; i++) {
        a = (FumbleVec){FUMBLE_ROW(i, w)->x, -FUMBLE_ROW(i, w)->y, FUMBLE_ROW(i, w)->z, 1.0f};
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
                         FUMBLE_ROW(i, w)->x, FUMBLE_ROW(i, w)->y, FUMBLE_ROW(i, w)->z);
    {
        FumbleVec pos = {FUMBLE_ROW(i, w)->x, -FUMBLE_ROW(i, w)->y, FUMBLE_ROW(i, w)->z, 1.0f};
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

typedef struct {
    float f00; /* 0x00 */
    float f04; /* 0x04 */
    int w[7];  /* 0x08 */
} WeaponDef;

extern WeaponDef weaponKind[];

/* This file's .data, in the ROM's order; MAIN.MAP names nothing in weapon.o's
   .data, so every name here is ours. */
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
    0,
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    0,
    0.0f,
    0.0f,
    0,
    0,
    0,
    0,
    0,
    {0, 0, 0},
    {0.0f, 0.0f, 0.0f, 1.0f},
};

/* the offsets the two path helpers below set the z of and push along */
static float pathOfsFwd[4] = {0.0f, 0.0f, 1.0f, 1.0f};

static float pathOfsBack[4] = {0.0f, 0.0f, 1.0f, 1.0f};

/* INTERIM NAMES, chosen and not recovered: the PAL listing carries these two
   file-static helpers at weapon.c:362-373 and 375-385 and inlines them here,
   so neither has a census row or a name in any map. */
static inline void addWeaponPathOffset(char *p, char *rp, float d)
{
    float m[16];
    float v[4];
    char *q = p + 0xD0;

    GetMatrixFromQuaternion(m, q);
    pathOfsFwd[2] = d;
    _ApplyMatrix(v, m, pathOfsFwd);
    _AddVectorXYZ(rp, rp, v);
}

static inline void subWeaponPathOffset(char *p, char *rp, float d)
{
    float m[16];
    float v[4];
    char *q = p + 0xD0;

    GetMatrixFromQuaternion(m, q);
    pathOfsBack[2] = -d;
    _ApplyMatrix(v, m, pathOfsBack);
    _AddVectorXYZ(rp, rp, v);
}

int calcDynamicPathGeometry(char *g)
{
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;
    float d = weaponKind[w->kind].f04;
    char *rp = (char *)p + 0xA0;
    float a;
    float b;
    float t;

    addWeaponPathOffset(p, rp, d);
    a = (float)w->fumbleFrame;
    b = (float)w->fumbleTime;
    t = a / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    _InterVectorXYZ(rp, w->fumbleTo, w->fumbleFrom, a / b);
    *(float *)(rp + 4) = w->fumbleFrom[1] + w->fumbleSpeed * t + t * 490.0f * t;
    MultiQuaternion((char *)p + 0xD0, (char *)p + 0xD0, (char *)p + 0x150);
    subWeaponPathOffset(p, rp, d);
    w->fumbleFrame = w->fumbleFrame + 1;
    if (w->fumbleFrame >= w->fumbleTime) {
        w->state = 0;
        CopyVector(rp, w->fumbleTo);
        CopyVector((char *)p + 0x130, ZeroVector);
        CopyQuaternion((char *)p + 0xD0, w->fumbleQuat);
        UpdateRootMatrix(g);
        weaponStickSE((int)g);
        return 1;
    }
    UpdateRootMatrix(g);
    return 0;
}

/* The collision query ClipCollision fills in (reconstruction; names ours):
   192 bytes, its quadword members giving it the 16-byte alignment the ROM's
   template copy relies on (32 bytes at a time with ld/sd pairs). */
typedef struct {
    sceVu0FVECTOR p0;  /* 0x00 start of the swept segment */
    sceVu0FVECTOR p1;  /* 0x10 end of the swept segment */
    char pad20[0x10];  /* 0x20 */
    sceVu0FVECTOR d;   /* 0x30 the clipped travel */
    char pad40[0x10];  /* 0x40 */
    sceVu0FVECTOR hit; /* 0x50 */
    sceVu0FVECTOR dir; /* 0x60 */
    float f70;         /* 0x70 */
    char pad74[0x14];  /* 0x74 */
    int wall;          /* 0x88 */
    char pad8C[0x8];   /* 0x8C */
    int hit94;         /* 0x94 */
    char pad98[0x28];  /* 0x98 */
} CollWork;

/* the query calcDynamicGeometry starts from: all clear but the 0x70 word */
static const CollWork collWorkInit = /* derived name */
    {{0.0f}, {0.0f}, {0}, {0.0f}, {0}, {0.0f}, {0.0f}, 10.0f};

/* the offset the wall test pushes the blade tip along, its z set per test */
static float hitOfs[4] = {0.0f, 0.0f, 1.0f, 1.0f};

/* calcDynamicGeometry's TTY trace, built only when DEBUG is defined; the
   retail build does not define it, so the preprocessor leaves the helper
   without a body.  A parameterless inline whose body is empty is saved as the
   single (use (const_int 0)) flow.c:count_basic_blocks gives a function with
   no insns, so each call emits no byte but leaves that insn until flow (a
   helper with a parameter saves no USE; its parameter move is an insn).  The
   name and the trace text are ours.
   WHAT THE BYTES PIN: the three spill slots at sp+0x23C..0x248 hold gcse PRE
   reaching registers in expression-hash bucket order, which puts gcse's
   max_cuid in a window this body reaches only with three to four more insns
   than its statements give (complete56: none 18 words, three or four hooks
   byte-identical, a hook between 536 and 557 six words); the calls sit in the
   listing's code-free runs 499-516, 580-585 and 590-597.  WHAT THEY CANNOT
   PIN: the trace's text, or its lines inside those runs. */
static __inline__ void dynGeoDebugHook(void)
{
#ifdef DEBUG
    scePrintf("calcDynamicGeometry\n");
#endif
}

void calcDynamicGeometry(char *g)
{
    char *p = *(char **)(g + 0x15C);
    WeaponWork *w = *(WeaponWork **)(p + 0x830);
    char *rp = p + 0xA0;
    float d = weaponKind[w->kind].f04;
    float r = weaponKind[w->kind].f00 - d;
    CollWork cc = collWorkInit;
    int hitA;
    int hitB;

    addWeaponPathOffset(p, rp, d);
    {
        sceVu0FMATRIX m1;
        sceVu0FVECTOR v1;
        sceVu0FMATRIX m2;
        sceVu0FVECTOR v2;
        sceVu0FVECTOR dir1;
        sceVu0FVECTOR dir2;
        sceVu0FVECTOR nrm;
        sceVu0FVECTOR tan;
        sceVu0FVECTOR axis;

        hitA = 0;
        hitB = 0;
        GetMatrixFromQuaternionPos(m1, (p + 0xD0), rp);
        *(float *)(rp + 0x94) =
            *(float *)(rp + 0x94) +
            60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
                (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
        _AddVectorXYZ(rp, rp, rp + 0x90);
        MultiQuaternion((p + 0xD0), rp + 0xB0, (p + 0xD0));
        GetMatrixFromQuaternionPos(m2, (p + 0xD0), rp);

        hitOfs[2] = r;
        _ApplyMatrix(cc.p0, m1, hitOfs);
        _ApplyMatrix(cc.p1, m2, hitOfs);
        CopyVector(v1, cc.p1);
        _SubVector(dir1, cc.p1, cc.p0);

        ClipCollision(&cc);
        if (cc.wall != 0 || cc.hit94 != 0) {
            hitA = 1;
            GetReflectionElement(&cc, 0.7f, 0.7f);
            CopyVector(v1, cc.hit);
            CopyVector(dir1, cc.dir);
            if (36.0f < VectorLengthSquare(cc.d)) {
                if (cc.wall) {
                    GOBJ_SUB(g)->wallAttr = GetWallAttribute(&cc);
                } else {
                    GOBJ_SUB(g)->wallAttr = GetFloorAttribute(&cc);
                }
                weaponHitReactionSE(g);
            }
        }

        hitOfs[2] = -r;
        _ApplyMatrix(cc.p0, m1, hitOfs);
        _ApplyMatrix(cc.p1, m2, hitOfs);
        CopyVector(v2, cc.p1);
        _SubVector(dir2, cc.p1, cc.p0);

        ClipCollision(&cc);
        if (cc.wall != 0 || cc.hit94 != 0) {
            hitB = 1;
            GetReflectionElement(&cc, 0.7f, 0.7f);
            CopyVector(v2, cc.hit);
            CopyVector(dir2, cc.dir);
            if (36.0f < VectorLengthSquare(cc.d)) {
                if (cc.wall) {
                    GOBJ_SUB(g)->wallAttr = GetWallAttribute(&cc);
                } else {
                    GOBJ_SUB(g)->wallAttr = GetFloorAttribute(&cc);
                }
                weaponHitReactionSE(g);
            }
        }

        if (cc.hit94) {
            w->state = 0;
            CopyVector(rp + 0x90, ZeroVector);
            CopyQuaternion((p + 0xD0), IdentityQuaternion);
        } else {
            dynGeoDebugHook();
            if (hitA || hitB) {
                _InterVector(rp + 0x90, dir1, dir2, 0.5f);
                _InterVector(rp, v1, v2, 0.5f);
                *(int *)(rp + 0x9C) = 0;
                *(float *)(rp + 0xC) = 1.0f;
                if (hitA) {
                    _SubVector(tan, dir1, rp + 0x90);
                } else {
                    _SubVector(tan, rp + 0x90, dir2);
                }
                _SubVector(nrm, v1, rp);
                _NormalizeVector(nrm, nrm);
                _OuterProduct(axis, nrm, tan);
                {
                    sceVu0FVECTOR qr;

                    {
                        sceVu0FVECTOR sc = {0.0f, VectorLength(tan), r, 0.0f};

                        _NormalizeVector(sc, sc);
                        SetQuaternionByAxisRotateV(qr, (short)-GetTableArcTan2(sc[1], sc[2]), axis);
                    }
                    CopyQuaternion(rp + 0xB0, qr);
                    MultiQuaternion((p + 0xD0), qr, (p + 0xD0));
                    {
                        sceVu0FMATRIX m3;
                        sceVu0FVECTOR v5;
                        sceVu0FVECTOR v6;
                        float eA;
                        float eB;
                        float e;

                        eA = 0.0f;
                        eB = 0.0f;
                        GetMatrixFromQuaternionPos(m3, (p + 0xD0), rp);
                        hitOfs[2] = r;
                        _ApplyMatrix(v5, m3, hitOfs);
                        if (v5[1] > v1[1]) {
                            eA = v5[1] - v1[1];
                        }
                        hitOfs[2] = -r;
                        _ApplyMatrix(v6, m3, hitOfs);
                        if (v6[1] > v2[1]) {
                            eB = v6[1] - v2[1];
                        }
                        e = (eB < eA) ? eA : eB;
                        if (0.0f < e) {
                            *(float *)(rp + 0x4) = *(float *)(rp + 0x4) - (e + 1.0f);
                            GetSlerpQuaternion(rp + 0xB0, rp + 0xB0, IdentityQuaternion, 0.9f);
                        }
                    }
                }
            }
            dynGeoDebugHook();
            RegularizeQuaternion((p + 0xD0));
            VectorLengthSquare(rp + 0x90);
            dynGeoDebugHook();
        }
        subWeaponPathOffset(p, rp, d);
        UpdateRootMatrix(g);
    }
}

/* INTERIM: a stand-in for SetWeaponOffsetMode, which the PAL listing inlines
   here (its rows at weapon.c:196 and 197 appear inside getGeometry and
   InitWeaponGeo) while keeping its own out-of-line copy at its ROM slot
   further down this file.  The work pointer is read as Sub15C's int field
   f_830, so the chase loads and the offset-mode store share the int alias
   set: the store kills the chase load for gcse and cse2, and InitWeaponGeo's
   loop latch reloads the sub-object pointer on its own, the ROM's second
   `lw $a1,0x15C($s7)` and the register order it decides (measured). */
static inline void setWeaponOffsetMode(char *g, int v)
{
    *(int *)(GOBJ_SUB(g)->work + 0xC0) = v;
}

void getGeometry(char *g)
{
    float pos[4];
    float quat[4];
    Sub15C *p = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)p->work;
    char *rp = (char *)p + 0xA0;

    if (w->holder != 0) {
        char *d = *(char **)(w->holder + 0x15C);
        int n = w->holderId;

        CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(d + 0xC) + n * 0x40);
        MatrixDrive_TransMatrix(7.0f, -3.0f, 0.0f);
        CopyVector(pos, (char *)MatrixDrive_GetMatrix() + 0x30);
        CopyQuaternion(quat, *(char **)(d + 0x10) + n * 0x10);
        if (((int *)(*(char **)(*(char **)(w->holder + 0x15C) + 0x8C) + n * 0x40))[1] == 22) {
            RotQuaternionY(quat, -32768);
        }
        sceVu0SubVector((char *)p + 0x130, pos, rp);
        {
            char *rq = (char *)p + 0xD0;

            DivQuaternion((char *)p + 0x150, quat, rq);
            CopyVector(rp, pos);
            CopyQuaternion(rq, quat);
        }
        UpdateRootMatrix(g);
        setWeaponOffsetMode(g, 0);
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

void WeaponCurPos(char *a0, void *a1, void *a2, void *a3)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    CopyVector(a1, p->hit[1]);
    CopyVector(a2, p->hit[2]);
    CopyVector(a3, p->hit[3]);
}

void WeaponHitEffect(char *a0, void *a1)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    CheckEnemyHit(a1, p->hit[1], p->hit[2], p->hit[3]);
}

void ExecWeaponHitReaction(int a0, int a1, int a2, int a3)
{
    weaponHitReactionSE(a0);
}

/* the blade tip in the sword's own frame */
static float swordTip[4] = {0.0f, 0.0f, 80.0f, 1.0f};

void checkHit(char *g)
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
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), (char *)p + 0xD0, (char *)p + 0xA0);
    MatrixDrive_TransMatrixV((char *)swordTip);
    CopyVector(v0, (char *)MatrixDrive_GetMatrix() + 0x30);
    GetInverseQuaternion(quat, (char *)p + 0x150);
    MultiQuaternion(quat, (char *)p + 0xD0, quat);
    SubVectorXYZ(pos, (char *)p + 0xA0, (char *)p + 0x130);
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), quat, pos);
    MatrixDrive_TransMatrixV((char *)swordTip);
    CopyVector(v1, (char *)MatrixDrive_GetMatrix() + 0x30);
    MatrixDrive_PopMatrix();
    CopyVector(w->hit[1], v0);
    CopyVector(w->hit[2], v1);
    CopyVector(w->hit[3], (char *)p + 0xA0);
}

/* The parent-link record CreateLayoutedGObj's caller hands to LinkParentOfDObj:
   two words, 4-aligned (ROM copies it with an ldl/ldr, sdl/sdr pair). */
typedef struct {
    int gobj;  /* 0x0 */
    int index; /* 0x4 */
} QSwordLink;

/* The 64-byte layout record InitDemoQueensSword passes through; only the
   word at 0x30 is ever named here. */
typedef struct {
    char pad00[0x30];
    int kind; /* 0x30 */
    char pad34[0xC];
} __attribute__((aligned(8))) QSwordLayout;

/* the queen's sword offset, its z set per sword */
static float queenSwordOfs[4] = {0.0f, 0.0f, 0.0f, 1.0f};

/* kept local: void * (int, int, int, int, void *, int, int, int) here, char * (int, int, int, int, int, int, int, int) in sceneManager.h */
extern void *CreateLayoutedGObj(int a0, int a1, int a2, int a3, void *lay, int a5, int a6, int a7);
/* kept local: void (void *, void *) here, void (void *, PackedLL_19CAF0 *) in DObj.h */
extern void LinkParentOfDObj(void *gobj, void *link);

void initializeQueenzSword(char *g, int index, QSwordLayout *lay)
{
    WeaponWork *w = GOBJ_SUB(g)->work;
    QSwordLink lnk = {(int)g, index};
    QSwordLayout r;
    QSwordLayout r2;
    int i;
    char *o;
    char *o2;

    r = *lay;
    r.kind = (lay->kind & 0xFF00) ? 5 : 4;

    w->count = 1;
    w->objs = iosMallocDebug(ios_partition_sugipon, 1 * 4, __FILE__, 759);

    for (i = 0; i < 1; i++) {
        queenSwordOfs[2] = weaponKind[w->kind].f00 * (float)i / 0.0f;
        o = CreateLayoutedGObj(10, 75, -1, i == 0, &r, -1, 7, 0);
        LinkParentOfDObj(o, &lnk);
        CopyVector((char *)GOBJ_SUB(o) + 0xA0, queenSwordOfs);
        w->objs[i] = o;
    }

    r2 = *lay;
    r2.kind = 13;
    o2 = CreateLayoutedGObj(46, 11, -1, 0, &r2, -1, 7, 0);
    *(QSwordLink *)(char *)GOBJ_SUB(o2) = lnk;
    w->sword = o2;
}

/* The per-weapon CSV model-id pair table, 40 bytes a row. */
typedef struct {
    int model0; /* 0x00 */
    int model1; /* 0x04 */
    char pad08[0x20];
} WeaponCsvEntry;

extern WeaponCsvEntry D_002A79B8[];

typedef float WeaponVec[4] __attribute__((aligned(8)));

/* kept local: char * (int, void *) here, char * (int, float *) in DObj.h */
extern char *CSVSYSTEM_InitDObj(int modelId, void *lay);

void *InitWeaponGeo(char *g, QSwordLayout *lay)
{
    WeaponWork *w = iosMallocDebug(ios_partition_sugipon, 0xE0, __FILE__, 820);
    int i;

    GOBJ_SUB(g)->work = (int)w;

    *w = swordWorkTemplate;
    w->kind = lay->kind & 0xFF;

    for (i = 0; i < GOBJ_SUB(g)->nodeNum; i++) {
        switch (w->kind) {
        case 0:
            break;

        case 1: {
            QSwordLink lnk = {(int)g, i};
            WeaponVec v = {0.0f, 0.0f, weaponKind[w->kind].f00, 1.0f};
            char *o;
            QSwordLayout r = *lay;

            r.kind = (lay->kind & 0xFF00) != 0;
            o = CreateLayoutedGObj(10, 75, -1, 1, &r, -1, 7, 1);
            LinkParentOfDObj(o, &lnk);
            CopyVector(*(char **)(o + 0x15C) + 0xA0, v);
            SetTorchLife(o, (60 - systemStatus[0] * 10) / systemStatus[1] * 15,
                         (60 - systemStatus[0] * 10) / systemStatus[1] * 3);
            w->count = 1;
            w->objs = iosMallocDebug(ios_partition_sugipon, 1 * 4, __FILE__, 848);
            w->objs[0] = o;
            w->buf = iosMallocDebug(ios_partition_sugipon, 0x160, __FILE__, 856);
            break;
        }

        case 5:
            initializeQueenzSword(g, i, lay);
            w->buf = iosMallocDebug(ios_partition_sugipon, 0x160, __FILE__, 861);
            break;

        case 7:
            w->buf = iosMallocDebug(ios_partition_sugipon, 0x160, __FILE__, 865);
            break;

        case 8:
        case 9:
            w->buf = iosMallocDebug(ios_partition_sugipon, 0x160, __FILE__, 870);
            w->net = iosMallocDebug(ios_partition_sugipon, 8, __FILE__, 871);
            w->model0 = CSVSYSTEM_InitDObj(
                D_002A79B8[((SubHandle *)(g + 0x15C))->sub->accessary].model0, lay);
            w->model1 = CSVSYSTEM_InitDObj(
                D_002A79B8[((SubHandle *)(g + 0x15C))->sub->accessary].model1, lay);
            CopyQuaternion(*(char **)(g + 0x15C) + 0xD0, *(char **)(g + 0x15C) + 0x60);
            UpdateRootMatrix(g);
            setWeaponOffsetMode(g, 1);
            break;

        default:
            w->buf = iosMallocDebug(ios_partition_sugipon, 0x160, __FILE__, 884);
            break;
        }
    }
    return w;
}

void dispLaserSword(char *g, float t)
{
    WeaponWork *w = GOBJ_SUB(g)->work;

    p2o_DispVU1(g);
    if (1.0f < t) {
        CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(g)->nodeMtx);
        MatrixDrive_TransMatrix(0.0f, 0.0f, 7.5f);
        MatrixDrive_ScaleMatrix(1.0f, 1.0f, t / 100.0f);
        CopyMatrix(*(void **)(w->model0 + 0xC), MatrixDrive_GetMatrix());
        p2o_DispVU1DObj(w->model0);
        MatrixDrive_TransMatrix(*(float *)(w->net + 0x0) * 0.1f, *(float *)(w->net + 0x4) * 0.1f,
                                0.0f);
        CopyMatrix(*(void **)(w->model1 + 0xC), MatrixDrive_GetMatrix());
        p2o_DispVU1DObj(w->model1);
    }
}

/* the insect net's line colour and its handle, end to end */
static int netColor[4] = {128, 128, 128, 128};

static float netHandleStart[4] = {0.0f, 0.0f, -50.0f, 1.0f};

static float netHandleEnd[4] = {0.0f, 0.0f, 100.0f, 1.0f};

typedef struct {
    float f[4];
} __attribute__((aligned(16))) NetVec;

void dispInsectNet(char *g)
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

void dispBlur(char *g)
{
    WeaponWork *w = GOBJ_SUB(g)->work;

    if (weaponKind[w->kind].w[3] != -1) {
        char *e = (char *)weaponKind + w->kind * 36;
        void *s = w->buf;
        GifColor c = {e[0x18], e[0x19], e[0x1A], e[0x1B]};

        _SetCurrentMatrix(matrixptr + 0x100);
        gif_StartPacketPri(2);
        switch (*(int *)(e + 0x14)) {
        case 0:
        default:
            gif_SetAlpha(1, 7, 128);
            break;
        case 1:
            gif_SetAlpha(1, 5, 128);
            break;
        case 2:
            gif_SetAlpha(1, 6, 128);
            break;
        }
        gif_SetZTest(1);
        gif_SetZWrite(1);
        gif_DrawStripF(s, c, 22, 1);
        gif_EndPacket();
    }
    if (w->kind == 8) {
        if (12.0f < w->fA8) {
            _UnitMatrix(MatrixDrive_GetMatrix());
            gif_StartPacketPri(2);
            gif_SetAlpha(1, 5, 128);
        }
        gif_EndPacket();
    }
}

void calcBlur(char *g, float t)
{
    float q1[4];   /* 0x00 */
    float q2[4];   /* 0x10 */
    float d[4];    /* 0x20 */
    float p[4];    /* 0x30 */
    float m[4][4]; /* 0x40 */
    float n[4];    /* 0x80 */
    float a[4];    /* 0x90 */
    float b[4];    /* 0xA0 */
    float sub[4];  /* 0xB0 */
    float tmp[4];  /* 0xC0 */
    Sub15C *e = GOBJ_SUB(g);
    WeaponWork *w = (WeaponWork *)e->work;
    char *base;
    char *vtx;
    char *q;
    char *dst1;
    char *dst2;
    char *pd;
    int h;
    int i;
    int j;
    int k;
    float ang;
    float r;

    GetInverseQuaternion(q1, (char *)e + 0x150);
    MultiQuaternion(q1, (char *)e + 0xD0, q1);
    SubVectorXYZ(d, (char *)e + 0xA0, (char *)e + 0x130);
    if (weaponKind[w->kind].w[3] == -1) {
        return;
    }
    base = w->buf;
    GetMatrixFromQuaternion(m, q1);
    _ApplyMatrix(a, m, ZUnitVector);
    GetMatrixFromQuaternion(m, (char *)e + 0xD0);
    _ApplyMatrix(b, m, ZUnitVector);
    _OuterProduct(n, b, a);
    _NormalizeVector(n, n);
    ang = acosf(_InnerProduct(a, b)) * 10430.378f;
    _ScaleVectorXYZ(a, a, t);
    a[3] = 1.0f;
    for (i = 0; i < 11; i++) {
        float rr = (float)i / 10.0f;

        SetQuaternionByAxisRotateVWithNoRegularize(q2, (short)(ang * (float)i / 10.0f), n);
        sceVu0InterVector(p, (char *)e + 0xA0, d, rr);
        GetMatrixFromQuaternionPos(m, q2, p);
        CopyVector(base + i * 32, (char *)m + 0x30);
        sceVu0ApplyMatrix(base + (i * 32 + 0x10), m, a);
    }
    if (w->kind >= 10) {
        return;
    }
    if (w->kind < 8) {
        return;
    }
    if (t > 12.0f) {
        h = SetParticleEffect(50, (char *)e + 0xA0, IdentityQuaternion);
        if (h != -1) {
            pd = GetParticleEffectData(h);
            vtx = *(char **)(pd + 0x24);
            q = *(char **)(pd + 0x28);
            dst1 = *(char **)(q + 0x190);
            dst2 = *(char **)(q + 0x194);
            ExecParticleEffect(h);
            for (j = 0; j < *(int *)(pd + 0x30); j++) {
                k = j * 10 / *(int *)(pd + 0x30);
                r = random_unit();
                _InterVector(vtx + 0x10, base + (k + 1) * 32, base + ((k + 1) * 32 + 16), r);
                _InterVector(tmp, base + k * 32, base + (k * 32 + 16), r);
                _SubVector(sub, vtx + 0x10, tmp);
                _ScaleVector(
                    vtx + 0x20, sub,
                    *(float *)(*(char **)(pd + 0x20) + 0x10) *
                        (*(float *)(*(char **)(pd + 0x20) + 0x14) * random_signed() + 1.0f));
                sceVu0CopyVector(dst1, vtx + 0x10);
                dst1 += 0x20;
                sceVu0CopyVector(dst2, vtx + 0x10);
                dst2 += 0x20;
                vtx += 0x70;
            }
        }
    }
}

typedef struct {
    char pad00[0x190]; /* 0x000 */
    unsigned int f190; /* 0x190 */
} WeaponEnemyPara;     /* 0x194 */

extern WeaponEnemyPara motionKind[];

/* The MatrixDrive matrix, viewed as the union of float and int arrays this
   codebase uses for VU0 data.  The union member reference is what puts the
   0x34 store in alias set 0, which is why the following gobj-extension load
   stays behind it instead of hoisting above the store (measured: 6 -> 3). */
typedef union {
    float f[4][4];
    int i[4][4];
} WeaponMatrix;

void WeaponGeo(char *g)
{
    WeaponWork *w = GOBJ_SUB(g)->work;
    int kind;
    int i;
    int n;
    float t;
    float a;

    getGeometry(g);
    checkHit(g);

    kind = w->kind;
    w->fA4 = 0;
    if (w->kind >= 10 || kind < 8) {
        if (w->state == 1 ||
            (w->holder != 0 &&
             ((((WeaponEnemyPara *)(*(int *)(*(char **)(w->holder + 0x15C) + 0x4A0) * 0x194 +
                                    (char *)motionKind))
                   ->f190 >>
               4) &
              1))) {
            calcBlur(g, *(float *)((char *)weaponKind + kind * 36));
            w->fA4 = 1;
        }
    } else {
        *(float *)((char *)weaponKind + kind * 36) = 40.0f;
        for (i = 0; i < 2; i++) {
            ((float *)w->net)[i] = random_signed_b();
        }
        if (w->holder != 0) {
            if (w->holder == boyGObj && ACTGame_FLAG_TETSUNAGI_VISUAL()) {
                *(float *)((char *)weaponKind + w->kind * 36) = 270.0f;
            }
            if (w->fAC >= 30.0f) {
                w->fA8 += (*(float *)((char *)weaponKind + w->kind * 36) - w->fA8) * 0.4f;
            } else {
                w->fAC = w->fAC + 1.0f;
                if (w->fAC == 29.0f) {
                    ExecuteDirectSE(g, 0x101E7);
                }
            }
        } else {
            w->fA8 += (0.0f - w->fA8) * 0.1f;
            w->fAC = 0.0f;
        }
        calcBlur(g, w->fA8);
        w->fA4 = 1;
        t = w->fA8;
        stage_SetLoopFlag(473, 1);
        if (t > 1.0f) {
            n = (int)stage_PlayBgAnimation(473, (float)w->fBC, (char *)GOBJ_SUB(g)->nodeMtx + 0x30,
                                           IdentityQuaternion);
            if (systemStatus[5] == 0) {
                w->fBC = n;
            }
        } else {
            stage_PlayBgAnimation(473, 0.0f, (char *)GOBJ_SUB(g)->nodeMtx + 0x30,
                                  IdentityQuaternion);
            w->fBC = 0;
        }
        stage_SetLoopFlag(473, 0);
    }

    GetRootMatrix(MatrixDrive_GetMatrix(), g);
    CopyVector(w->vD0, (char *)MatrixDrive_GetMatrix() + 0x30);
    if (w->offsetMode != 0) {
        float v[4] = {0.0f, 0.0f, 1.0f, 0.0f};

        v[3] = 0.0f;
        sceVu0ApplyMatrix(v, MatrixDrive_GetMatrix(), v);
        a = -atan2f(v[1], _Sqrt(1.0f - v[1] * v[1]));
        ((WeaponMatrix *)MatrixDrive_GetMatrix())->f[3][1] -=
            GetTableSin((short)(a * 10430.378f)) * 70.0f;
        CopyMatrix((char *)GOBJ_SUB(g)->nodeMtx, MatrixDrive_GetMatrix());
    }
}

void WeaponDL(char *g)
{
    WeaponWork *w = GOBJ_SUB(g)->work;

    switch (w->kind) {
    default:
        p2o_SetDefaultEnviroment();
        p2o_DispVU1(g);
        break;
    case 7:
        dispInsectNet(g);
        break;
    case 8:
    case 9:
        dispLaserSword(g, w->fA8);
        break;
    case 0:
        break;
    }
    if (w->fA4 != 0) {
        dispBlur(g);
    }
}

void PickupWeapon(char *a0, char *a1, int a2)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;

    p->holder = a1;
    p->holderId = GetSkeltonFocusNode(a1, a2);
    GOBJ_SUB(a1)->pickedWeapon = (int)a0;
}

char *CheckSwapableWeapon(char *a0, float dist)
{
    char *found = 0;
    float best = dist * dist;
    char *g = (char *)isysGObjSearchFromObjKindID_begin(14);
    float pos[4];
    float d;

    GetRootPosition(pos, a0);

    for (; g != 0; g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        WeaponWork *w;
        char *wp;

        if (g == a0)
            continue;

        w = GOBJ_SUB(g)->work;
        if (w->kind == 0)
            continue;

        if (w->holder != 0)
            continue;

        if (*(int *)(g + 0x16C) == 0)
            continue;

        wp = w->vD0;
        if (stage_no == 4 && *(int *)(g + 0x8) != 0x80)
            continue;

        d = distance_squared(pos, wp);
        if (d < best) {
            found = g;
            best = d;
        }
    }
    return found;
}

void ReleaseWeapon(char *a0)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    if (p->holder) {
        *(int *)(*(char **)(p->holder + 0x15C) + 0x630) = 0;
    }
    p->holder = 0;
    p->holderId = -1;
    p->state = 0;
}

int CheckWeaponKind(char *a0)
{
    return ((WeaponWork *)GOBJ_SUB(a0)->work)->kind;
}

void LightTorchOnOfWeapon(char *a0)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    int i;

    if (p->count) {
        torchOnOfWeaponSE((int)p->objs[0]);
    }
    for (i = 0; i < p->count; i++) {
        LightTorchOn(p->objs[i]);
    }
}

void LightTorchOnOfWeaponWithNoSE(char *a0)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    int i;

    if (p->count) {
        torchOnOfWeaponSE((int)p->objs[0]);
    }
    for (i = 0; i < p->count; i++) {
        LightTorchOn(p->objs[i]);
    }
}

void LightTorchOffOfWeapon(char *a0)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    int i;

    for (i = 0; i < p->count; i++) {
        LightTorchOff(p->objs[i]);
    }
}

int GetTorchGObjOfWeapon(char *a0)
{
    WeaponWork *p = GOBJ_SUB(a0)->work;
    if (p->count) {
        return (int)p->objs[0];
    }
    return 0;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * ReleaseWeapon's lines 262-265 here, so ReleaseWeapon is a public `inline` of
 * the deferred tail; its body is expanded in place until the tail's asm
 * members are C, when it collapses into a call.  LightTorchOnOfWeapon and
 * LightTorchOnOfWeaponWithNoSE are one source body (both symbols carry
 * weapon.c:173-177); their shared form is decided at layout. */
void ReleaseWeaponWithFumble(char *a0, void *a1, void *a2)
{
    Sub15C *e = GOBJ_SUB(a0);
    WeaponWork *w = (WeaponWork *)e->work;
    char *f = (char *)e + 0xA0;

    if (w->holder) {
        *(int *)(*(char **)(w->holder + 0x15C) + 0x630) = 0;
    }
    w->holder = 0;
    w->holderId = -1;
    w->state = 1;

    if (a2) {
        CopyQuaternion((char *)e + 0x150, a2);
    }
    CopyVector((char *)e + 0x130, a1);
    *(int *)(f + 0x9C) = 0;
}

int InitWeaponFumbleSequence(char *a0)
{
    ((WeaponWork *)GOBJ_SUB(a0)->work)->fumbleSlot = 0;
    return 1;
}

float GetWeaponWeight(char *a0)
{
    return (float)weaponKind[((WeaponWork *)GOBJ_SUB(a0)->work)->kind].w[1];
}

void SetWeaponTorchChainReactionFlagAll(int a0)
{
    char *g;
    WeaponWork *w;
    int i;

    for (g = isysGObjSearchFromObjKindID_begin(14); g; g = isysGObjSearchFromObjKindID_next(g)) {
        w = GOBJ_SUB(g)->work;
        if (w->kind == 1) {
            for (i = 0; i < w->count; i++) {
                SetTorchChainReactionFlag(w->objs[i], a0);
            }
        }
    }
}

void *InitDemoQueensSword(char *a0, void *a1)
{
    WeaponWork *w;
    int i;

    w = (WeaponWork *)iosMallocDebug(ios_partition_sugipon, 0xE0, __FILE__, 802);
    (WeaponWork *)GOBJ_SUB(a0)->work = w;
    *w = swordWorkTemplate;
    for (i = 0; i < GOBJ_SUB(a0)->nodeNum; i++) {
        initializeQueenzSword(a0, i, a1);
    }
    return w;
}

void ExecDemoQueensSword(char *a0)
{
    Sub15C *e = GOBJ_SUB(a0);
    char *p = *(char **)((char *)e + 0x830);
    *(int *)(*(char **)(p + 0x5C) + 0x16C) = e->disp;
}

void SetWeaponOffsetMode(char *a0, int a1)
{
    *(int *)(GOBJ_SUB(a0)->work + 0xC0) = a1;
}
