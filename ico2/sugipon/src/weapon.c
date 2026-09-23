#include "common.h"
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

extern int D_0028F4C0[];
/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);

/* INTERIM NAME, chosen and not recovered: the PAL listing carries this
   file-static helper at weapon.c:262-265 and inlines it here, so it has no
   census row and no name of its own in any map. */
static inline void releaseWeaponHolder(char *w)
{
    if (*(char **)(w + 0x8) != 0) {
        *(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(w + 0xC) = -1;
}

void ReleaseWeaponWithFumbleTargetPos(char *g, void *pos, void *quat, void *rot, float t)
{
    Sub15C *p = GOBJ_SUB(g);
    char *w = *(char **)((char *)p + 0x830);

    releaseWeaponHolder(w);
    *(int *)(w + 0x4) = 2;
    *(int *)(w + 0x8) = 0;
    if (rot != 0) {
        CopyQuaternion((char *)p + 0x150, rot);
    }
    *(int *)(w + 0x60) = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * t);
    *(int *)(w + 0x64) = 0;
    GetRootPosition(w + 0x70, g);
    CopyVector(w + 0x80, pos);
    CopyQuaternion(w + 0x90, quat);
    *(float *)(w + 0x68) = (*(float *)(w + 0x84) - *(float *)(w + 0x74)) / t - t * 490.0f;
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
extern const char D_006213A0[];
extern const char D_006213F0[];

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

#define FUMBLE_ROW(i, w) (&D_0054A040[*(int *)((w) + 0xA0)][i])

int ReleaseWeaponWithFumbleSequential(char *g)
{
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    FumbleVec a;
    int i;

    for (i = 0; i < 3; i++) {
        a = (FumbleVec){FUMBLE_ROW(i, w)->x, -FUMBLE_ROW(i, w)->y, FUMBLE_ROW(i, w)->z, 1.0f};
        if (!fumbleTargetBlocked(&a)) {
            break;
        }
        debug_StdPrintfDummy(D_006213A0, *(int *)(w + 0xA0), i);
    }
    debug_StdPrintfDummy(D_006213F0, *(int *)(w + 0xA0), i, FUMBLE_ROW(i, w)->x,
                         FUMBLE_ROW(i, w)->y, FUMBLE_ROW(i, w)->z);
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
    *(int *)(w + 0xA0) = *(int *)(w + 0xA0) + 1;
    if (*(int *)(w + 0xA0) == 7) {
        *(int *)(w + 0xA0) = 0;
        return 1;
    }
    return 0;
}

typedef struct {
    float f00; /* 0x00 */
    float f04; /* 0x04 */
    int w[7];  /* 0x08 */
} WeaponDef;

extern WeaponDef D_00318EB8[];
extern float D_004ED2D0[];
extern float D_004ED2E0[];
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *dst, void *m, void *src);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of _InterVectorXYZ do not fit the prototype in Matrix.h */
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);

/* INTERIM NAMES, chosen and not recovered: the PAL listing carries these two
   file-static helpers at weapon.c:362-373 and 375-385 and inlines them here,
   so neither has a census row or a name in any map. */
static inline void addWeaponPathOffset(char *p, char *rp, float d)
{
    float m[16];
    float v[4];
    char *q = p + 0xD0;

    GetMatrixFromQuaternion(m, q);
    D_004ED2D0[2] = d;
    _ApplyMatrix(v, m, D_004ED2D0);
    _AddVectorXYZ(rp, rp, v);
}

static inline void subWeaponPathOffset(char *p, char *rp, float d)
{
    float m[16];
    float v[4];
    char *q = p + 0xD0;

    GetMatrixFromQuaternion(m, q);
    D_004ED2E0[2] = -d;
    _ApplyMatrix(v, m, D_004ED2E0);
    _AddVectorXYZ(rp, rp, v);
}

int calcDynamicPathGeometry(char *g)
{
    Sub15C *p = GOBJ_SUB(g);
    char *w = *(char **)((char *)p + 0x830);
    float d = D_00318EB8[*(int *)w].f04;
    char *rp = (char *)p + 0xA0;
    float a;
    float b;
    float t;

    addWeaponPathOffset(p, rp, d);
    a = (float)*(int *)(w + 0x64);
    b = (float)*(int *)(w + 0x60);
    t = a / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    _InterVectorXYZ(rp, w + 128, w + 112, a / b);
    *(float *)(rp + 4) = *(float *)(w + 0x74) + *(float *)(w + 0x68) * t + t * 490.0f * t;
    MultiQuaternion((char *)p + 0xD0, (char *)p + 0xD0, (char *)p + 0x150);
    subWeaponPathOffset(p, rp, d);
    *(int *)(w + 0x64) = *(int *)(w + 0x64) + 1;
    if (*(int *)(w + 0x64) >= *(int *)(w + 0x60)) {
        *(int *)(w + 0x4) = 0;
        CopyVector(rp, w + 128);
        CopyVector((char *)p + 0x130, ZeroVector);
        CopyQuaternion((char *)p + 0xD0, w + 144);
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
    char pad70[0x18];  /* 0x70 */
    int wall;          /* 0x88 */
    char pad8C[0x8];   /* 0x8C */
    int hit94;         /* 0x94 */
    char pad98[0x28];  /* 0x98 */
} CollWork;

extern CollWork D_00621420;
extern float D_004ED2F0[];
extern void ClipCollision(void *cc);
extern void GetReflectionElement(void *cc, float a, float b);
extern int GetWallAttribute(void *cc);
extern int GetFloorAttribute(void *cc);
extern float VectorLengthSquare(void *v);
extern float VectorLength(void *v);
extern void _SubVector(void *dst, void *a, void *b);
extern void _InterVector(void *dst, void *a, void *b, float t);
extern void _NormalizeVector(void *dst, void *src);
extern void _OuterProduct(void *dst, void *a, void *b);

/* Compiled-out debug hook (our name), the construct sugipon's own
   clothAnimation.c carries as chainDebugOld and clothFixDebug: it inlines to
   nothing and emits no byte, but each call leaves one real insn until flow.
   WHAT THE BYTES PIN: the three spill slots at sp+0x23C..0x248 hold gcse PRE
   reaching registers in expression-hash bucket order, which puts gcse's
   max_cuid in a window this body reaches only with three to four more insns
   than its statements give (complete56: none 18 words, three or four hooks
   byte-identical, a hook between 536 and 557 six words); the calls sit in the
   listing's code-free runs 499-516, 580-585 and 590-597.  WHAT THEY CANNOT
   PIN: that the developer's debug code was this construct, or its lines. */
static __inline__ void dynGeoDebugHook(void) {}

void calcDynamicGeometry(char *g)
{
    char *p = *(char **)(g + 0x15C);
    char *w = *(char **)(p + 0x830);
    char *rp = p + 0xA0;
    float d = D_00318EB8[*(int *)w].f04;
    float r = D_00318EB8[*(int *)w].f00 - d;
    CollWork cc = D_00621420;
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
        *(float *)(rp + 0x94) = *(float *)(rp + 0x94) +
                                60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f *
                                    (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
        _AddVectorXYZ(rp, rp, rp + 0x90);
        MultiQuaternion((p + 0xD0), rp + 0xB0, (p + 0xD0));
        GetMatrixFromQuaternionPos(m2, (p + 0xD0), rp);

        D_004ED2F0[2] = r;
        _ApplyMatrix(cc.p0, m1, D_004ED2F0);
        _ApplyMatrix(cc.p1, m2, D_004ED2F0);
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
                    *(int *)(*(char **)(g + 0x15C) + 0x5F4) = GetWallAttribute(&cc);
                } else {
                    *(int *)(*(char **)(g + 0x15C) + 0x5F4) = GetFloorAttribute(&cc);
                }
                weaponHitReactionSE(g);
            }
        }

        D_004ED2F0[2] = -r;
        _ApplyMatrix(cc.p0, m1, D_004ED2F0);
        _ApplyMatrix(cc.p1, m2, D_004ED2F0);
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
                    *(int *)(*(char **)(g + 0x15C) + 0x5F4) = GetWallAttribute(&cc);
                } else {
                    *(int *)(*(char **)(g + 0x15C) + 0x5F4) = GetFloorAttribute(&cc);
                }
                weaponHitReactionSE(g);
            }
        }

        if (cc.hit94) {
            *(int *)(w + 0x4) = 0;
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
                        D_004ED2F0[2] = r;
                        _ApplyMatrix(v5, m3, D_004ED2F0);
                        if (v5[1] > v1[1]) {
                            eA = v5[1] - v1[1];
                        }
                        D_004ED2F0[2] = -r;
                        _ApplyMatrix(v6, m3, D_004ED2F0);
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

/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix(void *dst, void *src);
/* kept local: this TU's uses of MatrixDrive_GetMatrix do not fit the prototype in matrixDrive.h */
extern void *MatrixDrive_GetMatrix(void);
/* kept local: this TU's uses of MatrixDrive_TransMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrix(float x, float y, float z);

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
    *(int *)(GOBJ_SUB(g)->f_830 + 0xC0) = v;
}

void getGeometry(char *g)
{
    float pos[4];
    float quat[4];
    Sub15C *p = GOBJ_SUB(g);
    char *w = *(char **)((char *)p + 0x830);
    char *rp = (char *)p + 0xA0;

    if (*(char **)(w + 0x8) != 0) {
        char *d = *(char **)(*(char **)(w + 0x8) + 0x15C);
        int n = *(int *)(w + 0xC);

        CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(d + 0xC) + n * 0x40);
        MatrixDrive_TransMatrix(7.0f, -3.0f, 0.0f);
        CopyVector(pos, (char *)MatrixDrive_GetMatrix() + 0x30);
        CopyQuaternion(quat, *(char **)(d + 0x10) + n * 0x10);
        if (((int *)(*(char **)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x8C) + n * 0x40))[1] ==
            22) {
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
        switch (*(int *)(w + 0x4)) {
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
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    CopyVector(a1, p + 0x20);
    CopyVector(a2, p + 0x30);
    CopyVector(a3, p + 0x40);
}

void WeaponHitEffect(char *a0, void *a1)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    CheckEnemyHit(a1, p + 0x20, p + 0x30, p + 0x40);
}

void ExecWeaponHitReaction(int a0, int a1, int a2, int a3)
{
    weaponHitReactionSE(a0);
}

extern char D_004ED300[];
/* kept local: this TU's uses of MatrixDrive_PushMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PushMatrix(void);
/* kept local: this TU's uses of MatrixDrive_PopMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PopMatrix(void);
/* kept local: this TU's uses of MatrixDrive_TransMatrixV do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrixV(char *v);
/* kept local: this TU's uses of SubVectorXYZ do not fit the prototype in matrixDrive.h */
extern void SubVectorXYZ(void *dst, void *a, void *b);

void checkHit(char *g)
{
    float pos[4];
    float quat[4];
    float v0[4];
    float v1[4];
    Sub15C *p = GOBJ_SUB(g);
    char *w = *(char **)((char *)p + 0x830);

    if (*(char **)(w + 0x8) == 0) {
        return;
    }
    MatrixDrive_PushMatrix();
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), (char *)p + 0xD0, (char *)p + 0xA0);
    MatrixDrive_TransMatrixV(D_004ED300);
    CopyVector(v0, (char *)MatrixDrive_GetMatrix() + 0x30);
    GetInverseQuaternion(quat, (char *)p + 0x150);
    MultiQuaternion(quat, (char *)p + 0xD0, quat);
    SubVectorXYZ(pos, (char *)p + 0xA0, (char *)p + 0x130);
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), quat, pos);
    MatrixDrive_TransMatrixV(D_004ED300);
    CopyVector(v1, (char *)MatrixDrive_GetMatrix() + 0x30);
    MatrixDrive_PopMatrix();
    CopyVector(w + 0x20, v0);
    CopyVector(w + 0x30, v1);
    CopyVector(w + 0x40, (char *)p + 0xA0);
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

extern void *D_0063A438;
extern const char D_006214E0[];
extern float D_004ED310[];
extern void *CreateLayoutedGObj(int a0, int a1, int a2, int a3, void *lay, int a5, int a6, int a7);
extern void LinkParentOfDObj(void *gobj, void *link);

void initializeQueenzSword(char *g, int index, QSwordLayout *lay)
{
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    QSwordLink lnk = {(int)g, index};
    QSwordLayout r;
    QSwordLayout r2;
    int i;
    char *o;
    char *o2;

    r = *lay;
    r.kind = (lay->kind & 0xFF00) ? 5 : 4;

    *(int *)(w + 0x50) = 1;
    *(int **)(w + 0x54) = iosMallocDebug(D_0063A438, 1 * 4, D_006214E0, 759);

    for (i = 0; i < 1; i++) {
        D_004ED310[2] = D_00318EB8[*(int *)w].f00 * (float)i / 0.0f;
        o = CreateLayoutedGObj(10, 75, -1, i == 0, &r, -1, 7, 0);
        LinkParentOfDObj(o, &lnk);
        CopyVector((char *)GOBJ_SUB(o) + 0xA0, D_004ED310);
        (*(int **)(w + 0x54))[i] = (int)o;
    }

    r2 = *lay;
    r2.kind = 13;
    o2 = CreateLayoutedGObj(46, 11, -1, 0, &r2, -1, 7, 0);
    *(QSwordLink *)(char *)GOBJ_SUB(o2) = lnk;
    *(char **)(w + 0x5C) = o2;
}

/* The work record InitWeaponGeo allocates and the .rodata template it is
   initialised from: 224 bytes, 8-aligned (ROM copies it 32 bytes at a time
   with ld/sd pairs). */
typedef struct {
    double d[28];
} DemoQueenSwordWork;

extern DemoQueenSwordWork D_004ED1F0;

/* The per-weapon CSV model-id pair table, 40 bytes a row. */
typedef struct {
    int model0; /* 0x00 */
    int model1; /* 0x04 */
    char pad08[0x20];
} WeaponCsvEntry;

extern WeaponCsvEntry D_002A79B8[];

typedef float WeaponVec[4] __attribute__((aligned(8)));

extern char *CSVSYSTEM_InitDObj(int modelId, void *lay);

void *InitWeaponGeo(char *g, QSwordLayout *lay)
{
    char *w = iosMallocDebug(D_0063A438, 0xE0, D_006214E0, 820);
    int i;

    GOBJ_SUB(g)->f_830 = (int)w;

    *(DemoQueenSwordWork *)w = D_004ED1F0;
    *(int *)w = lay->kind & 0xFF;

    for (i = 0; i < GOBJ_SUB(g)->f_8; i++) {
        switch (*(int *)w) {
        case 0:
            break;

        case 1: {
            QSwordLink lnk = {(int)g, i};
            WeaponVec v = {0.0f, 0.0f, D_00318EB8[*(int *)w].f00, 1.0f};
            char *o;
            QSwordLayout r = *lay;

            r.kind = (lay->kind & 0xFF00) != 0;
            o = CreateLayoutedGObj(10, 75, -1, 1, &r, -1, 7, 1);
            LinkParentOfDObj(o, &lnk);
            CopyVector(*(char **)(o + 0x15C) + 0xA0, v);
            SetTorchLife(o, (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 15,
                         (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 3);
            *(int *)(w + 0x50) = 1;
            *(char ***)(w + 0x54) = iosMallocDebug(D_0063A438, 1 * 4, D_006214E0, 848);
            (*(char ***)(w + 0x54))[0] = o;
            *(char **)(w + 0x58) = iosMallocDebug(D_0063A438, 0x160, D_006214E0, 856);
            break;
        }

        case 5:
            initializeQueenzSword(g, i, lay);
            *(char **)(w + 0x58) = iosMallocDebug(D_0063A438, 0x160, D_006214E0, 861);
            break;

        case 7:
            *(char **)(w + 0x58) = iosMallocDebug(D_0063A438, 0x160, D_006214E0, 865);
            break;

        case 8:
        case 9:
            *(char **)(w + 0x58) = iosMallocDebug(D_0063A438, 0x160, D_006214E0, 870);
            *(char **)(w + 0xB0) = iosMallocDebug(D_0063A438, 8, D_006214E0, 871);
            *(char **)(w + 0xB4) =
                CSVSYSTEM_InitDObj(D_002A79B8[*(int *)(*(char **)(g + 0x15C) + 0x844)].model0, lay);
            *(char **)(w + 0xB8) =
                CSVSYSTEM_InitDObj(D_002A79B8[*(int *)(*(char **)(g + 0x15C) + 0x844)].model1, lay);
            CopyQuaternion(*(char **)(g + 0x15C) + 0xD0, *(char **)(g + 0x15C) + 0x60);
            UpdateRootMatrix(g);
            setWeaponOffsetMode(g, 1);
            break;

        default:
            *(char **)(w + 0x58) = iosMallocDebug(D_0063A438, 0x160, D_006214E0, 884);
            break;
        }
    }
    return w;
}

/* kept local: this TU's uses of MatrixDrive_ScaleMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);

void dispLaserSword(char *g, float t)
{
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);

    p2o_DispVU1(g);
    if (1.0f < t) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(void **)((char *)GOBJ_SUB(g) + 0xC));
        MatrixDrive_TransMatrix(0.0f, 0.0f, 7.5f);
        MatrixDrive_ScaleMatrix(1.0f, 1.0f, t / 100.0f);
        CopyMatrix(*(void **)(*(char **)(w + 0xB4) + 0xC), MatrixDrive_GetMatrix());
        p2o_DispVU1DObj(*(void **)(w + 0xB4));
        MatrixDrive_TransMatrix(*(float *)(*(char **)(w + 0xB0) + 0x0) * 0.1f,
                                *(float *)(*(char **)(w + 0xB0) + 0x4) * 0.1f, 0.0f);
        CopyMatrix(*(void **)(*(char **)(w + 0xB8) + 0xC), MatrixDrive_GetMatrix());
        p2o_DispVU1DObj(*(void **)(w + 0xB8));
    }
}

extern char D_004ED320[];
extern char D_004ED330[];
extern char D_004ED340[];

typedef struct {
    float f[4];
} __attribute__((aligned(16))) NetVec;

void dispInsectNet(char *g)
{
    int i;

    CopyMatrix(MatrixDrive_GetMatrix(), *(void **)((char *)GOBJ_SUB(g) + 0xC));
    gif_StartPacketPri(11);
    gif_SetZTest(1);
    gif_SetZWrite(1);
    gif_SetAlpha(1, 7, 128);
    DrawLineG(D_004ED330, D_004ED320, D_004ED340, D_004ED320, 0);
    for (i = 0; i <= 65535; i += 4096) {
        NetVec p = {
            {GetTableCos((short)i) * 30.0f, 0.0f, GetTableSin((short)i) * 30.0f + 130.0f, 1.0f}};
        NetVec q = {{GetTableCos((short)(i + 4096)) * 30.0f, 0.0f,
                     GetTableSin((short)(i + 4096)) * 30.0f + 130.0f, 1.0f}};

        DrawLineG(&p, D_004ED320, &q, D_004ED320, 0);
    }
    gif_EndPacket();
}

extern char *matrixptr;
/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *p);
/* kept local: this TU's uses of _UnitMatrix do not fit the prototype in Matrix.h */
extern void _UnitMatrix(void *m);

void dispBlur(char *g)
{
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);

    if (D_00318EB8[*(int *)w].w[3] != -1) {
        char *e = (char *)D_00318EB8 + *(int *)w * 36;
        void *s = *(void **)(w + 0x58);
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
    if (*(int *)w == 8) {
        if (12.0f < *(float *)(w + 0xA8)) {
            _UnitMatrix(MatrixDrive_GetMatrix());
            gif_StartPacketPri(2);
            gif_SetAlpha(1, 5, 128);
        }
        gif_EndPacket();
    }
}

/* kept local: this TU's uses of _OuterProduct do not fit the prototype in Matrix.h */
extern void _OuterProduct(void *dst, void *a, void *b);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *src);
/* kept local: this TU's uses of _InnerProduct do not fit the prototype in Matrix.h */
extern float _InnerProduct(void *a, void *b);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float s);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *src, float s);
/* kept local: this TU's uses of _InterVector do not fit the prototype in Matrix.h */
extern void _InterVector(void *dst, void *a, void *b, float t);
/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of ZUnitVector do not fit the prototype in matrixDrive.h */
extern float ZUnitVector[];

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
    char *w = *(char **)((char *)e + 0x830);
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
    if (D_00318EB8[*(int *)w].w[3] == -1) {
        return;
    }
    base = *(char **)(w + 0x58);
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
    if (*(int *)w >= 10) {
        return;
    }
    if (*(int *)w < 8) {
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

extern void *D_00639EA4;
extern int D_0028F4D4[];
/* kept local: this TU's uses of _Sqrt do not fit the prototype in Matrix.h */
extern float _Sqrt(float x);

typedef struct {
    char pad00[0x190]; /* 0x000 */
    unsigned int f190; /* 0x190 */
} WeaponEnemyPara;     /* 0x194 */

extern WeaponEnemyPara D_0055FE58[];

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
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
    int kind;
    int i;
    int n;
    float t;
    float a;

    getGeometry(g);
    checkHit(g);

    kind = *(int *)w;
    *(int *)(w + 0xA4) = 0;
    if (*(int *)w >= 10 || kind < 8) {
        if (*(int *)(w + 0x4) == 1 ||
            (*(char **)(w + 0x8) != 0 &&
             ((((WeaponEnemyPara *)(*(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x4A0) *
                                        0x194 +
                                    (char *)D_0055FE58))
                   ->f190 >>
               4) &
              1))) {
            calcBlur(g, *(float *)((char *)D_00318EB8 + kind * 36));
            *(int *)(w + 0xA4) = 1;
        }
    } else {
        *(float *)((char *)D_00318EB8 + kind * 36) = 40.0f;
        for (i = 0; i < 2; i++) {
            ((float *)*(char **)(w + 0xB0))[i] = random_signed_b();
        }
        if (*(char **)(w + 0x8) != 0) {
            if (*(char **)(w + 0x8) == D_00639EA4 && ACTGame_FLAG_TETSUNAGI_VISUAL()) {
                *(float *)((char *)D_00318EB8 + *(int *)w * 36) = 270.0f;
            }
            if (*(float *)(w + 0xAC) >= 30.0f) {
                *(float *)(w + 0xA8) +=
                    (*(float *)((char *)D_00318EB8 + *(int *)w * 36) - *(float *)(w + 0xA8)) * 0.4f;
            } else {
                *(float *)(w + 0xAC) = *(float *)(w + 0xAC) + 1.0f;
                if (*(float *)(w + 0xAC) == 29.0f) {
                    ExecuteDirectSE(g, 0x101E7);
                }
            }
        } else {
            *(float *)(w + 0xA8) += (0.0f - *(float *)(w + 0xA8)) * 0.1f;
            *(float *)(w + 0xAC) = 0.0f;
        }
        calcBlur(g, *(float *)(w + 0xA8));
        *(int *)(w + 0xA4) = 1;
        t = *(float *)(w + 0xA8);
        stage_SetLoopFlag(473, 1);
        if (t > 1.0f) {
            n = (int)stage_PlayBgAnimation(473, (float)*(int *)(w + 0xBC),
                                           *(char **)((char *)GOBJ_SUB(g) + 0xC) + 0x30,
                                           IdentityQuaternion);
            if (D_0028F4D4[0] == 0) {
                *(int *)(w + 0xBC) = n;
            }
        } else {
            stage_PlayBgAnimation(473, 0.0f, *(char **)((char *)GOBJ_SUB(g) + 0xC) + 0x30,
                                  IdentityQuaternion);
            *(int *)(w + 0xBC) = 0;
        }
        stage_SetLoopFlag(473, 0);
    }

    GetRootMatrix(MatrixDrive_GetMatrix(), g);
    CopyVector(w + 0xD0, (char *)MatrixDrive_GetMatrix() + 0x30);
    if (*(int *)(w + 0xC0) != 0) {
        float v[4] = {0.0f, 0.0f, 1.0f, 0.0f};

        v[3] = 0.0f;
        sceVu0ApplyMatrix(v, MatrixDrive_GetMatrix(), v);
        a = -atan2f(v[1], _Sqrt(1.0f - v[1] * v[1]));
        ((WeaponMatrix *)MatrixDrive_GetMatrix())->f[3][1] -=
            GetTableSin((short)(a * 10430.378f)) * 70.0f;
        CopyMatrix(*(char **)((char *)GOBJ_SUB(g) + 0xC), MatrixDrive_GetMatrix());
    }
}

void WeaponDL(char *g)
{
    char *w = *(char **)((char *)GOBJ_SUB(g) + 0x830);

    switch (*(int *)w) {
    default:
        p2o_SetDefaultEnviroment();
        p2o_DispVU1(g);
        break;
    case 7:
        dispInsectNet(g);
        break;
    case 8:
    case 9:
        dispLaserSword(g, *(float *)(w + 0xA8));
        break;
    case 0:
        break;
    }
    if (*(int *)(w + 0xA4) != 0) {
        dispBlur(g);
    }
}

void PickupWeapon(char *a0, char *a1, int a2)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);

    *(char **)(p + 0x8) = a1;
    *(int *)(p + 0xC) = GetSkeltonFocusNode(a1, a2);
    GOBJ_SUB(a1)->f_630 = (int)a0;
}

extern int stage_no;

char *CheckSwapableWeapon(char *a0, float dist)
{
    char *found = 0;
    float best = dist * dist;
    char *g = (char *)isysGObjSearchFromObjKindID_begin(14);
    float pos[4];
    float d;

    GetRootPosition(pos, a0);

    for (; g != 0; g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *w;
        char *wp;

        if (g == a0)
            continue;

        w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
        if (*(int *)w == 0)
            continue;

        if (*(int *)(w + 0x8) != 0)
            continue;

        if (*(int *)(g + 0x16C) == 0)
            continue;

        wp = w + 0xD0;
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
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    if (*(char **)(p + 0x8)) {
        *(int *)(*(char **)(*(char **)(p + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(p + 0x8) = 0;
    *(int *)(p + 0xC) = -1;
    *(int *)(p + 0x4) = 0;
}

int CheckWeaponKind(char *a0)
{
    return *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830));
}

void LightTorchOnOfWeapon(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    int i;

    if (*(int *)(p + 0x50)) {
        torchOnOfWeaponSE(**(int **)(p + 0x54));
    }
    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOn(*(int *)(*(char **)(p + 0x54) + i * 4));
    }
}

void LightTorchOnOfWeaponWithNoSE(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    int i;

    if (*(int *)(p + 0x50)) {
        torchOnOfWeaponSE(**(int **)(p + 0x54));
    }
    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOn(*(int *)(*(char **)(p + 0x54) + i * 4));
    }
}

void LightTorchOffOfWeapon(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    int i;

    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOff(*(char **)(*(char **)(p + 0x54) + i * 4));
    }
}

int GetTorchGObjOfWeapon(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    if (*(int *)(p + 0x50)) {
        return **(int **)(p + 0x54);
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
    char *w = *(char **)((char *)e + 0x830);
    char *f = (char *)e + 0xA0;

    if (*(char **)(w + 0x8)) {
        *(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(w + 0x8) = 0;
    *(int *)(w + 0xC) = -1;
    *(int *)(w + 0x4) = 1;

    if (a2) {
        CopyQuaternion((char *)e + 0x150, a2);
    }
    CopyVector((char *)e + 0x130, a1);
    *(int *)(f + 0x9C) = 0;
}

int InitWeaponFumbleSequence(char *a0)
{
    *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0xA0) = 0;
    return 1;
}

float GetWeaponWeight(char *a0)
{
    return (float)D_00318EB8[*(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830))].w[1];
}

void SetWeaponTorchChainReactionFlagAll(int a0)
{
    char *g;
    char *w;
    int i;

    for (g = isysGObjSearchFromObjKindID_begin(14); g; g = isysGObjSearchFromObjKindID_next(g)) {
        w = *(char **)((char *)GOBJ_SUB(g) + 0x830);
        if (*(int *)w == 1) {
            for (i = 0; i < *(int *)(w + 0x50); i++) {
                SetTorchChainReactionFlag(*(char **)(*(char **)(w + 0x54) + i * 4), a0);
            }
        }
    }
}

extern void initializeQueenzSword(char *gobj, int index, QSwordLayout *a2);

void *InitDemoQueensSword(char *a0, void *a1)
{
    DemoQueenSwordWork *w;
    int i;

    w = (DemoQueenSwordWork *)iosMallocDebug(D_0063A438, 0xE0, D_006214E0, 802);
    *(DemoQueenSwordWork **)((char *)GOBJ_SUB(a0) + 0x830) = w;
    *w = D_004ED1F0;
    for (i = 0; i < GOBJ_SUB(a0)->f_8; i++) {
        initializeQueenzSword(a0, i, a1);
    }
    return w;
}

void ExecDemoQueensSword(char *a0)
{
    Sub15C *e = GOBJ_SUB(a0);
    char *p = *(char **)((char *)e + 0x830);
    *(int *)(*(char **)(p + 0x5C) + 0x16C) = e->f_74;
}

void SetWeaponOffsetMode(char *a0, int a1)
{
    *(int *)(GOBJ_SUB(a0)->f_830 + 0xC0) = a1;
}
