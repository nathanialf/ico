#include "common.h"
#include "a_p_1.h"
#include "DObj.h"
#include "debug.h"
#include "debug_exception.h"
#include "sceneManager.h"
#include "memory.h"
#include "obj_manager.h"
#include "fieldCollision.h"
#include "DisplayP2O.h"
#include "enemyParts.h"
#include "geometryManager.h"
#include "pool.h"
#include "tableSin.h"
#include <stdlib.h>
#include "typedef.h"

typedef struct {
    float m[4];
} __attribute__((aligned(16))) Vec4A_P_1;

/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(int a, int b, int c);
extern char D_004E5670[];

/* static helper the listing places at a_p_1.c lines 156-165, above InitAP1's
 * def line 227, so the name is ours. */
static inline void applyPartOrients(char *g)
{
    char *tbl = D_004E5670;
    Mtx44 m;
    char *q = *(char **)(*(char **)(g + 0x15C) + 0x830);
    int i;

    GetRootMatrix(&m, g);
    for (i = 0; i < 4; i++) {
        _ApplyMatrix((int)(q + 0x20 + i * 0x50), (int)&m, (int)(tbl + i * 0x10));
        _ApplyMatrix((int)(q + 0x30 + i * 0x50), (int)&m, (int)(tbl + i * 0x10));
    }
}

/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);
/* kept local: this TU's uses of _UnitMatrix do not fit the prototype in Matrix.h */
extern void _UnitMatrix(void *m);
/* kept local: this TU's uses of GetSkeltonFocusNode do not fit the prototype in motionManager2.h */
extern int GetSkeltonFocusNode(void *self, int id);
extern void __assert(char *file, int line, char *expr);
extern void *D_0063A438;
extern void *D_0063A44C;
extern char D_0061EE30[];
extern char D_0061EE40[];
extern char D_0063B6C0[];

typedef struct {
    int unk0;    /* 0x00 */
    int unk4;    /* 0x04 */
    int unk8;    /* 0x08 */
    int unkC;    /* 0x0C */
    int unk10;   /* 0x10 */
    int unk14;   /* 0x14 */
    float unk18; /* 0x18 */
    int unk1C;   /* 0x1C */
} AP1Layout;

extern AP1Layout D_0062B588[];
extern char D_004E5550[];
extern char D_004E55A0[];
extern float D_004E56D0[];
extern char InitialColInfo[];

typedef union {
    int i;
    long long ll;
} AP1Flag;

typedef struct {
    long long d[10];
} AP1Part;

typedef struct {
    long long x;
} __attribute__((packed, aligned(4))) AP1PackedLL;

typedef struct {
    AP1PackedLL p; /* 0x00 */
    int attr;      /* 0x08 */
} AP1ColHit;

char *InitAP1(char *self, char *arg)
{
    char *p;
    char *d;
    int i;

    p = iosMallocDebug(D_0063A438, 0x280, D_0061EE30, 0xE4);
    *(char **)(*(int *)(self + 0x15C) + 0x830) = p;
    *(int *)p = *(int *)(arg + 0x30);
    *(int *)(p + 0x4) = 1;
    *(int *)(p + 0x16C) = 0;
    *(int *)(p + 0x8) = 7;
    *(int *)(p + 0x168) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(int *)(p + 0x1C8) = 0;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x270) = rand() & 0x1F;
    *(int *)(p + 0x274) = 0;
    *(int *)(p + 0x278) = 1;
    D_004E56D0[2] = D_0062B588[*(int *)p].unk18;
    CopyVector(p + 0x1B0, D_004E56D0);
    _UnitMatrix(p + 0x1F0);
    _UnitMatrix(p + 0x230);
    GetRootQuaternion((int)(p + 0x1D0), (int *)self);
    GetRootPosition(p + 0x1E0, self);
    for (i = 0; i < 4; i++) {
        *(AP1Part *)(p + 0x10 + i * 0x50) = *(AP1Part *)D_004E5550;
    }
    for (i = 0; i < 2; i++) {
        *(AP1ColHit *)(p + 0x150 + i * 0xC) = *(AP1ColHit *)InitialColInfo;
    }
    applyPartOrients(self);
    if (*(int *)(p + 0x4) == 0) {
        d = CSVSYSTEM_InitDObj(7, arg);
        *(char **)(p + 0x194) = d;
        if (*(int *)(d + 0xC) != 0) {
            iosFree(*(int *)(d + 0xC) & 0xFFFFFFF);
        }
        if (*(int *)(*(char **)(p + 0x194) + 0x10) != 0) {
            iosFree(*(int *)(*(char **)(p + 0x194) + 0x10) & 0xFFFFFFF);
        }
        *(int *)(*(char **)(p + 0x194) + 0xC) = 0;
        *(int *)(*(char **)(p + 0x194) + 0x10) = 0;
        *(int *)(*(char **)(p + 0x194) + 0xC) =
            (int)iosMallocDebug(D_0063A44C, 0x100, D_0061EE30, 0x105);
        *(int *)(*(char **)(p + 0x194) + 0x10) =
            (int)iosMallocDebug(D_0063A44C, 0x40, D_0061EE30, 0x105);
        *(int *)(*(char **)(p + 0x194) + 0x8) = 4;
        if (*(int *)(*(char **)(p + 0x194) + 0x870) != 0) {
            iosFree(*(int *)(*(char **)(p + 0x194) + 0x870) & 0xFFFFFFF);
        }
        *(int *)(*(char **)(p + 0x194) + 0x870) =
            (int)iosMallocDebug(D_0063A44C, 0x140, D_0061EE30, 0x105);
        {
            int n;

            for (n = 0; n < 4; n++) {
                ((AP1Flag *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x38))->ll &=
                    ~1;
                ((AP1Flag *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x38))->ll &=
                    ~2;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x40) = 0.0f;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x44) = 0.0f;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x48) = 0.0f;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x4C) = 1.0f;
                ((AP1Flag *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x38))->ll &=
                    ~4;
                *(int *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x30) = 0;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x34) = 1.0f;
                *(short *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x3A) = 0;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x20) = 1.0f;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x24) = 1.0f;
                *(float *)(*(char **)(*(char **)(p + 0x194) + 0x870) + n * 0x50 + 0x28) = 1.0f;
            }
        }
        *(short *)(*(char **)(p + 0x194) + 0x84C) = 2;
        d = CSVSYSTEM_InitDObj(8, arg);
        *(char **)(p + 0x198) = d;
        if (*(int *)(d + 0xC) != 0) {
            iosFree(*(int *)(d + 0xC) & 0xFFFFFFF);
        }
        if (*(int *)(*(char **)(p + 0x198) + 0x10) != 0) {
            iosFree(*(int *)(*(char **)(p + 0x198) + 0x10) & 0xFFFFFFF);
        }
        *(int *)(*(char **)(p + 0x198) + 0xC) = 0;
        *(int *)(*(char **)(p + 0x198) + 0x10) = 0;
        *(int *)(*(char **)(p + 0x198) + 0xC) =
            (int)iosMallocDebug(D_0063A44C, 0x100, D_0061EE30, 0x108);
        *(int *)(*(char **)(p + 0x198) + 0x10) =
            (int)iosMallocDebug(D_0063A44C, 0x40, D_0061EE30, 0x108);
        *(int *)(*(char **)(p + 0x198) + 0x8) = 4;
        if (*(int *)(*(char **)(p + 0x198) + 0x870) != 0) {
            iosFree(*(int *)(*(char **)(p + 0x198) + 0x870) & 0xFFFFFFF);
        }
        *(int *)(*(char **)(p + 0x198) + 0x870) =
            (int)iosMallocDebug(D_0063A44C, 0x140, D_0061EE30, 0x108);
        {
            int n;

            for (n = 0; n < 4; n++) {
                ((AP1Flag *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x38))->ll &=
                    ~1;
                ((AP1Flag *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x38))->ll &=
                    ~2;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x40) = 0.0f;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x44) = 0.0f;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x48) = 0.0f;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x4C) = 1.0f;
                ((AP1Flag *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x38))->ll &=
                    ~4;
                *(int *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x30) = 0;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x34) = 1.0f;
                *(short *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x3A) = 0;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x20) = 1.0f;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x24) = 1.0f;
                *(float *)(*(char **)(*(char **)(p + 0x198) + 0x870) + n * 0x50 + 0x28) = 1.0f;
            }
        }
        *(short *)(*(char **)(p + 0x198) + 0x84C) = 2;
    } else {
        for (i = 0; i < 9; i++) {
            *(int *)(p + 0x170 + i * 4) = GetSkeltonFocusNode(self, *(int *)(D_004E55A0 + i * 4));
            if (*(int *)(p + 0x170 + i * 4) == -1) {
                debug_assertMessage(D_0061EE30, 0x10D, D_0061EE40);
                __assert(D_0061EE30, 0x10D, D_0063B6C0);
            }
        }
        *(int *)(p + 0x198) = 0;
        *(int *)(p + 0x194) = 0;
    }
    *(int *)(p + 0x19C) = InitEnemyEye(0xA, 0, 0xA);
    return p;
}

extern char D_004E55D0[];
/* kept local: this TU's uses of GetMatrixFromQuaternion do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternion(int dst, int src);
/* kept local: this TU's uses of MultiQuaternion do not fit the prototype in quaternion.h */
extern void MultiQuaternion(int dst, int a, int b);
/* kept local: this TU's uses of SetQuaternionByAxisRotateV do not fit the prototype in quaternion.h */
extern void SetQuaternionByAxisRotateV(int dst, int p, int src);
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(int a, int b, int c);
/* kept local: this TU's uses of _InnerProduct do not fit the prototype in Matrix.h */
extern float _InnerProduct(int dst, int v);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(int dst, int src);
/* kept local: this TU's uses of _OuterProduct do not fit the prototype in Matrix.h */
extern void _OuterProduct(int dst, int v, int src);

void yAxisRotFitting(int *self, int arg2)
{
    Vec4A_P_1 l0;
    Vec4A_P_1 l10;
    Mtx44 m20;
    Vec4A_P_1 l60;
    Vec4A_P_1 l70;
    int *r;
    float f;

    GetRootQuaternion((int)&l70, self);
    GetMatrixFromQuaternion((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_004E55D0);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        SetRootQuaternion((int)self, (int)&l70);
    }
}

/* kept local: this TU's uses of ZUnitVector do not fit the prototype in matrixDrive.h */
extern char ZUnitVector[];

void zAxisRotFitting(int *self, int arg2)
{
    Vec4A_P_1 l0;
    Vec4A_P_1 l10;
    Mtx44 m20;
    Vec4A_P_1 l60;
    Vec4A_P_1 l70;
    int *r;
    float f;

    GetRootQuaternion((int)&l70, self);
    GetMatrixFromQuaternion((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)ZUnitVector);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        SetRootQuaternion((int)self, (int)&l70);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/a_p_1", fitToCol);

/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *src, float s);
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of VectorLength do not fit the prototype in matrixDrive.h */
extern float VectorLength(void *v);

typedef union {
    int i;
    float f;
} AP1Val;

int walkMot(char *a0)
{
    Vec4A_P_1 pos;
    Vec4A_P_1 v;
    Mtx44 m;
    Mtx44 tm;
    Vec4A_P_1 out;
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 1);
    int i;
    int n;

    if (ret != -1)
        return ret;

    GetRootPosition(&pos, a0);
    GetRootMatrix(&m, a0);
    _ApplyMatrix((int)&v, (int)&m, (int)(p + 0x1B0));
    n = 0;
    for (i = 0; i < 4; i++) {
        if (*(int *)(p + 0x10 + i * 0x50) == 0) {
            n++;
        }
    }
    _ScaleVector(&v, &v, ((float)n * 0.25f + 0.5f) * 0.5f);
    _ScaleVector(*(char **)(a0 + 0x15C) + 0x130, *(char **)(a0 + 0x15C) + 0x130, 0.8f);
    _AddVectorXYZ(*(char **)(a0 + 0x15C) + 0x130, *(char **)(a0 + 0x15C) + 0x130, &v);
    MatrixDrive_SetTransposeMatrix(&tm, &m);
    _ApplyMatrix((int)&out, (int)&tm, (int)(*(char **)(a0 + 0x15C) + 0x130));
    ((AP1Val *)(p + 0x1C4))->f = out.m[0];
    ((AP1Val *)(p + 0x1C0))->f = VectorLength(*(char **)(a0 + 0x15C) + 0x130) * 0.1f;
    _AddVectorXYZ(&pos, &pos, *(char **)(a0 + 0x15C) + 0x130);
    SetRootPosition(a0, &pos);
    *(int *)(p + 0x1C8) = 0;
    return 1;
}

/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of CheckWallAttribute do not fit the prototype in motionManager2.h */
extern int CheckWallAttribute(void *gobj, int mask);
/* kept local: this TU's uses of CheckFloorAttribute do not fit the prototype in motionManager2.h */
extern int CheckFloorAttribute(void *gobj, int mask);
/* kept local: this TU's uses of CheckFieldContact do not fit the prototype in motionManager2.h */
extern int CheckFieldContact(void *col, void *gobj, void *pos, float r);
extern int D_0028F4C0[];
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
extern char D_004E57A0[];
extern char D_004E57C0[];

/* Two static helpers the listing places at a_p_1.c lines 283-292 and 156-165,
 * above the def lines of fitToCol and InitAP1, so both names are ours. */
static inline int clipAndTakeHit(AP1ColHit *dst, char *col)
{
    ClipCollision(col);
    if (*(int *)(col + 0x88) != 0) {
        dst->attr = *(int *)(col + 0x88);
        dst->p = *(AP1PackedLL *)(col + 0x80);
        return 1;
    }
    if (*(int *)(col + 0x94) != 0) {
        dst->attr = *(int *)(col + 0x94);
        dst->p = *(AP1PackedLL *)(col + 0x8C);
        return 1;
    }
    return 0;
}

int rolling(char *a0)
{
    AP1ColHit info;

    if (*(int *)(*(char **)(a0 + 0x15C)) != 0) {
        UnlinkParentOfDObj(a0);
    }
    ((AP1Val *)(*(char **)(a0 + 0x15C) + 0x134))->f +=
        60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f *
        (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
    _AddVectorXYZ(*(char **)(a0 + 0x15C) + 0xA0, *(char **)(a0 + 0x15C) + 0xA0,
                  *(char **)(a0 + 0x15C) + 0x130);
    {
        char *col = D_004E57A0;
        CopyVector(col, *(char **)(a0 + 0x15C) + 0x1F0);
        CopyVector(col + 0x10, *(char **)(a0 + 0x15C) + 0xA0);
        *(float *)(col + 4) -= 50.0f;
        if (clipAndTakeHit(&info, col)) {
            CopyVector(*(char **)(a0 + 0x15C) + 0xA0, D_004E57C0);
            CopyVector(*(char **)(a0 + 0x15C) + 0x130, ZeroVector);
            yAxisRotFitting((int *)a0, (int)(D_004E57C0 + 0x80));
            LinkParentOfDObj(a0, &info);
            UpdateRootMatrix(a0);
            applyPartOrients(a0);
            {
                char *col = D_004E57A0;
                if (*(int *)(col + 0x88) != 0) {
                    *(int *)(*(char **)(a0 + 0x15C) + 0x5F8) = GetWallAttribute(col);
                }
                if (CheckWallAttribute(a0, 0x50) != 0) {
                    if (GetPoolGlobalHeight(*(int *)(col + 0x80)) <
                        *(float *)(*(char **)(a0 + 0x15C) + 0xA4) + 50.0f) {
                        iosOmSendMail(a0, 0x26, a0);
                    }
                }
            }
            {
                char *col = D_004E57A0;
                if (*(int *)(col + 0x94) != 0) {
                    *(int *)(*(char **)(a0 + 0x15C) + 0x5F8) = GetFloorAttribute(col);
                    if (CheckFloorAttribute(a0, 0x50) != 0) {
                        if (GetPoolGlobalHeight(*(int *)(col + 0x8C)) <
                            *(float *)(*(char **)(a0 + 0x15C) + 0xA4) + 50.0f) {
                            iosOmSendMail(a0, 0x26, a0);
                        }
                    }
                }
            }
            return 0;
        }
    }
    {
        char *col = D_004E57A0;
        *(float *)(col + 0x14) += 500.0f;
        ClipFloor(col);
        if (CheckFieldContact(col, a0, *(char **)(a0 + 0x15C) + 0xA0, 50.0f) == 2) {
            CopyVector(*(char **)(a0 + 0x15C) + 0x130, ZeroVector);
            iosOmSendMail(a0, 0x1A, a0);
        }
    }
    return -1;
}

extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_RotMatrixX(int ang);
extern void MatrixDrive_RotMatrixY(int ang);
extern void MatrixDrive_RotMatrixZ(int ang);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
extern void MatrixDrive_TurnXObjectMatrixYZ(float x, float y, float z);
extern void CopyMatrix(void *dst, void *src);
extern void _MulMatrix(void *dst, void *a, void *b);
extern void _SubVector(void *dst, void *a, void *b);
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
extern float _GetLength(void *a, void *b);
extern void ExecuteSEPackage(void *self, int id);
extern void _AttackCenter(void *self, int a1, void *v, int a3, float r, int a5);
extern char D_004E55E0[];
extern char D_004E5860[];
extern char D_004E58A0[];
extern const Vec4A_P_1 D_0061EE60;

/* static helper the listing places at a_p_1.c lines 628-631, above
 * calcSubMission's def line 637, so the name is ours: the law of cosines for
 * the two arm segments, one named local per listing line. */
static inline short armCosine(float a, float b, float c)
{
    float aa = a * a;
    float bb = b * b;
    float cc = c * c;

    return (short)(int)GetTableArcCos((aa + bb - cc) / (2.0f * a * b));
}

void calcSubMission(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x830);
    Vec4A_P_1 base;
    Vec4A_P_1 axis;
    Vec4A_P_1 rq;
    Mtx44 tm;
    Vec4A_P_1 q;
    Vec4A_P_1 w;
    Vec4A_P_1 dir;
    Vec4A_P_1 v;
    Vec4A_P_1 v2;
    Mtx44 rm;
    Vec4A_P_1 lv;
    Vec4A_P_1 save;
    Vec4A_P_1 save2;
    Vec4A_P_1 atk;
    int i;
    int ang;

    CopyMatrix(MatrixDrive_GetMatrix(), p + 0x1F0);
    MatrixDrive_RotMatrixZ(0x4000);
    MatrixDrive_RotMatrixX(0x4000);
    CopyVector(&base, (char *)MatrixDrive_GetMatrix() + 0x30);
    GetRootQuaternion((int)&rq, (int *)self);
    _ApplyMatrix((int)&axis, (int)MatrixDrive_GetMatrix(), (int)D_004E55E0);
    MatrixDrive_SetTransposeMatrix(&tm, MatrixDrive_GetMatrix());

    for (i = 0; i < 4; i++) {
        char *part = p + 0x10 + i * 0x50;
        float len;

        switch (*(int *)part) {
        case 1: {
            float t = (float)*(int *)(part + 4) / 10.0f;

            CopyVector(&w, part + 0x20);
            w.m[1] -= (t < 0.5f) ? t * 2.0f * 20.0f : (1.0f - t) * 2.0f * 20.0f;
            _ApplyMatrix((int)&q, (int)(p + 0x230), (int)&w);
            _InterVectorXYZ(part + 0x10, &q, part + 0x10, t);
            if ((*(int *)(part + 4) += 1) >= 10) {
                *(int *)part = 0;
            }
            break;
        }
        case 2: {
            float t = (float)*(int *)(part + 4) / 10.0f;

            MatrixDrive_PushMatrix();
            _UnitMatrix(MatrixDrive_GetMatrix());
            {
                float f = t * 49152.0f + -32768.0f;

                MatrixDrive_RotMatrixY((short)(i == 0 ? -f : f));
            }
            _ApplyMatrix((int)&v, (int)MatrixDrive_GetMatrix(), (int)(part + 0x20));
            v.m[3] = 1.0f;
            _ApplyMatrix((int)&dir, (int)(p + 0x230), (int)&v);
            _InterVectorXYZ(part + 0x10, &dir, part + 0x10, t);
            MatrixDrive_PopMatrix();
            if ((*(int *)(part + 4) += 1) >= 10) {
                ExecuteSEPackage(self, 0x68);
                CopyVector(part + 0x20, D_004E5670 + i * 0x10);
                *(int *)part = 1;
                *(int *)(part + 4) = 0;
            }
            break;
        }
        }

        MatrixDrive_PushMatrix();

        len = _GetLength(&base, part + 0x10);
        ang = armCosine(len, 50.0f, 50.0f);
        _SubVector(&dir, part + 0x10, &base);
        _NormalizeVector((int)&dir, (int)&dir);

        if (*(int *)part == 2) {
            _OuterProduct((int)&w, (int)&dir, (int)&axis);
        } else {
            _OuterProduct((int)&w, (int)&dir, (int)&axis);
        }
        _ApplyMatrix((int)&lv, (int)&tm, (int)&dir);
        MatrixDrive_TurnXObjectMatrixYZ(lv.m[0], lv.m[1], lv.m[2]);

        _ScaleVector(&v, &dir, 50.0f);
        SetQuaternionByAxisRotateV((int)&q, (short)-ang, (int)&w);
        GetMatrixFromQuaternion((int)&rm, (int)&q);
        _ApplyMatrix((int)&v, (int)&rm, (int)&v);
        _AddVectorXYZ(part + 0x30, &base, &v);

        CopyVector(&save, (char *)MatrixDrive_GetMatrix() + 0x30);
        _MulMatrix(MatrixDrive_GetMatrix(), &rm, MatrixDrive_GetMatrix());
        CopyVector((char *)MatrixDrive_GetMatrix() + 0x30, &save);

        if (*(int *)(p + 4) != 0) {
            _MulMatrix(*(char **)(*(char **)(self + 0x15C) + 0xC) +
                           (*(int *)(p + 0x174 + i * 8) << 6),
                       MatrixDrive_GetMatrix(), D_004E5860);
        } else {
            _MulMatrix(*(char **)(*(char **)(p + 0x194) + 0xC) + (i << 6), MatrixDrive_GetMatrix(),
                       D_004E5860);
        }

        _ScaleVector(&v2, &dir, 50.0f);
        SetQuaternionByAxisRotateV((int)&q, (short)ang, (int)&w);
        GetMatrixFromQuaternion((int)&rm, (int)&q);
        _ApplyMatrix((int)&v2, (int)&rm, (int)&v2);
        _AddVectorXYZ(part + 0x40, part + 0x30, &v2);

        _MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), D_004E58A0);

        CopyVector(&save2, (char *)MatrixDrive_GetMatrix() + 0x30);
        _MulMatrix(MatrixDrive_GetMatrix(), &rm, MatrixDrive_GetMatrix());
        _MulMatrix(MatrixDrive_GetMatrix(), &rm, MatrixDrive_GetMatrix());
        CopyVector((char *)MatrixDrive_GetMatrix() + 0x30, &save2);

        if (*(int *)part == 2) {
            atk = D_0061EE60;
            _ApplyMatrix((int)&atk, (int)MatrixDrive_GetMatrix(), (int)&atk);
            _AttackCenter(self, -1, &atk, 0, 30.0f, 0);
        }

        if (*(int *)(p + 4) != 0) {
            _MulMatrix(*(char **)(*(char **)(self + 0x15C) + 0xC) +
                           (*(int *)(p + 0x178 + i * 8) << 6),
                       MatrixDrive_GetMatrix(), D_004E5860);
        } else {
            _MulMatrix(*(char **)(*(char **)(p + 0x198) + 0xC) + (i << 6), MatrixDrive_GetMatrix(),
                       D_004E5860);
        }

        MatrixDrive_PopMatrix();
    }
}

/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix(void *dst, void *src);
/* kept local: this TU's uses of RotQuaternionX do not fit the prototype in quaternion.h */
extern void RotQuaternionX(void *q, short ang);
/* kept local: this TU's uses of RotQuaternionZ do not fit the prototype in quaternion.h */
extern void RotQuaternionZ(void *q, short ang);
/* kept local: this TU's uses of GetMatrixFromQuaternionPos do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
/* kept local: this TU's uses of _InterVectorXYZ do not fit the prototype in Matrix.h */
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
/* kept local: this TU's uses of GetSlerpQuaternion do not fit the prototype in quaternion.h */
extern void GetSlerpQuaternion(void *dst, void *a, void *b, float t);
/* kept local: this TU's uses of _MulMatrix do not fit the prototype in Matrix.h */
extern void _MulMatrix(void *dst, void *a, void *b);
extern float D_004E58E0[];
extern float D_004E58F0[];

void updateMatrix(char *a0)
{
    float pos[4];
    float quat[4];
    float mtx[16];
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    CopyVector(*(char **)(a0 + 0x15C) + 0x1F0, *(char **)(a0 + 0x15C) + 0xA0);
    UpdateRootMatrix(a0);
    CopyMatrix(p + 0x230, *(void **)(*(char **)(a0 + 0x15C) + 0xC));

    D_004E58E0[1] = ((float)*(int *)(p + 0x270) * 0.03125f < 0.5f)
                        ? ((float)*(int *)(p + 0x270) * 0.03125f) * 2.0f * 5.0f + -10.0f
                        : (1.0f - (float)*(int *)(p + 0x270) * 0.03125f) * 2.0f * 5.0f + -10.0f;
    D_004E58E0[1] -= *(float *)(p + 0x1C8) * 25.0f;
    D_004E58E0[2] = *(float *)(p + 0x1C8) * 50.0f;

    GetRootPosition(pos, a0);
    GetRootQuaternion((int)quat, (int *)a0);

    RotQuaternionX(quat, (short)(*(float *)(p + 0x1C8) * 8192.0f));
    RotQuaternionX(quat, (short)(*(float *)(p + 0x1C0) * 4096.0f));
    GetMatrixFromQuaternionPos(mtx, quat, pos);
    _ApplyMatrix((int)pos, (int)mtx, (int)D_004E58E0);
    RotQuaternionZ(quat, (short)(-*(float *)(p + 0x1C4) * 2048.0f));
    _InterVectorXYZ(p + 0x1E0, pos, p + 0x1E0, 0.5f);
    GetSlerpQuaternion(p + 0x1D0, quat, p + 0x1D0, 0.1f);
    GetMatrixFromQuaternionPos(p + 0x1F0, p + 0x1D0, p + 0x1E0);
    _MulMatrix(*(void **)(*(char **)(a0 + 0x15C) + 0xC), p + 0x1F0, D_004E58F0);
}

void resetPositionInfo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    GetRootPosition(p + 0x1E0, a0);
    GetRootQuaternion(p + 0x1D0, a0);
    ResetEnemyEye(*(int *)(p + 0x19C));
}

extern int (*motFuncList[][2])(char *);
/* kept local: this TU's uses of MatrixDrive_GetMatrix do not fit the prototype in matrixDrive.h */
extern void *MatrixDrive_GetMatrix(void);
/* kept local: this TU's uses of _MulMatrix do not fit the prototype in Matrix.h */
extern void _MulMatrix(void *dst, void *a, void *b);
/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix(void *dst, void *src);
/* kept local: this TU's uses of MatrixDrive_RotMatrixZ do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixZ(int ang);
/* kept local: this TU's uses of MatrixDrive_RotMatrixX do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixX(int ang);
extern char D_004E5970[];
extern char D_004E59F0[];
extern char D_0061EE70[];

/* static helper the listing places at a_p_1.c lines 889-891, expanded only
 * into AP1Geo, so this name is ours. */
static inline void stepAP1BlinkTimer(char *g)
{
    char *q = (char *)*(int *)(*(int *)(g + 0x15C) + 0x830);
    int t = *(int *)(q + 0x270) + 1;

    *(int *)(q + 0x270) = t;
    if (t > 32) {
        *(int *)(q + 0x270) = 0;
    }
}

void AP1Geo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    float d;

    switch (*(int *)(p + 8)) {
    default:
        if (*(int *)(p + 0x274) < 10) {
            *(int *)(p + 0x274) = *(int *)(p + 0x274) + 1;
            resetPositionInfo(a0);
        }
        *(int *)(p + 8) = motFuncList[*(int *)(p + 8)][1](a0);
        stepAP1BlinkTimer(a0);
        break;

    case 5:
        *(int *)(p + 8) = 4;
        break;

    case 4:
        *(int *)(p + 8) = 6;
        break;

    case 6:
        *(int *)(a0 + 0x16C) = 0;
        break;

    case 7:
        break;
    }
    updateMatrix(a0);
    calcSubMission(a0);
    _MulMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)(a0 + 0x15C) + 0xC), D_004E5970);
    UpdateEnemyEye(*(int *)(p + 0x19C), MatrixDrive_GetMatrix(), 1.0f);
    if (*(int *)(p + 4) != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)(a0 + 0x15C) + 0xC));
        MatrixDrive_RotMatrixZ(0x4000);
        MatrixDrive_RotMatrixX(0x4000);
        _MulMatrix(*(void **)(*(char **)(a0 + 0x15C) + 0xC), MatrixDrive_GetMatrix(), D_004E59F0);
    }
    d = *(float *)(*(char **)(a0 + 0x15C) + 0x54) -
        *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0xC) + 0x34);
    if ((d < 0.0f) ? ((d = -d) > 10000.0f) : (d > 10000.0f)) {
        *(int *)(*(char **)(a0 + 0x15C) + 0x5F8) = 0x800;
        debug_StdPrintfDummy(D_0061EE70);
    }
}

void AP1DL(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(int *)(p + 8) < 5) {
        if (*(int *)(p + 0x278) != 0) {
            p2o_SetDefaultEnviroment();
            p2o_DispVU1(a0);
            if (*(int *)(p + 4) == 0) {
                p2o_DispVU1DObjMulti(*(int *)(p + 0x194));
                p2o_DispVU1DObjMulti(*(int *)(p + 0x198));
            }
            DispEnemyEye(*(int *)(p + 0x19C));
        }
    }
}

int GetAP1SpecType(char *a0)
{
    return **(int **)(*(char **)(a0 + 0x15C) + 0x830);
}

void SetAP1VisualState(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x278) = a1;
}

/* kept local: this TU's uses of RotQuaternionY do not fit the prototype in quaternion.h */
extern void RotQuaternionY(int q, int ang);
/* kept local: this TU's uses of RegularizeQuaternion do not fit the prototype in quaternion.h */
extern void RegularizeQuaternion(int q);

int AP1Turn(char *a0, short a1)
{
    Vec4A_P_1 q;
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2)
            goto out;
    }
    GetRootQuaternion((int)&q, (int *)a0);
    RotQuaternionY((int)&q, a1);
    RegularizeQuaternion((int)&q);
    SetRootQuaternion((int)a0, (int)&q);
    updateMatrix(a0);
    return 1;
out:
    return 0;
}

extern int (*motFuncList[][2])(char *);

int AP1MotReqForce(char *a0, int a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    *(int *)(p + 8) = a1;
    if (motFuncList[a1][0] != 0) {
        motFuncList[a1][0](a0);
    }
    return 1;
}

int AP1MotReq(char *a0, int a1)
{
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2)
            return 0;
    }
    AP1MotReqForce(a0, a1);
    return 1;
}

int AP1JumpReq(char *a0, int a1, void *a2)
{
    int flag;
    char *p = *(char **)(a0 + 0x15C);
    char *q = *(char **)(p + 0x830);
    if (*(int *)(q + 8) < 6) {
        if (*(int *)(q + 8) >= 2) {
            flag = 0;
            goto check;
        }
    }
    AP1MotReqForce(a0, a1);
    flag = 1;
check:
    if (flag != 0) {
        char *pp = *(char **)(a0 + 0x15C);
        char *qq = *(char **)(pp + 0x830);
        _ApplyMatrix((int)(pp + 0x130), (int)(qq + 0x230), (int)a2);
        return 1;
    }
    return 0;
}

char *MakeAP1GObj(char *a0)
{
    return CreateLayoutedGObj(0x3E, D_0062B588[*(int *)(a0 + 0x30)].unkC, -1, 0, a0, 0, 7, 1);
}

extern int D_004E5520[];

int GetAP1Mode(char *a0)
{
    return D_004E5520[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)];
}

int standMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 0);
    if (ret != -1)
        return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(int *)(p + 0x1C8) = 0;
    return 0;
}

int rollingMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = rolling(a0);
    if (ret != -1)
        return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(int *)(p + 0x1C8) = 0;
    return 2;
}

extern int D_00639EA4;
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);

typedef struct {
    int state;     /* 0x00 */
    float frame;   /* 0x04 */
    int unk8[6];   /* 0x08 */
    Vec4A_P_1 vec; /* 0x20 */
} AP1MotCtrl;

/* Two static helpers the listing places at a_p_1.c lines 384-393 (the census
 * gap between 353 and 397), expanded twice each into attackMotInit and
 * attackMot; neither is emitted out of line, so both names are ours. */
static inline void setAP1MotCtrlState(AP1MotCtrl *m, int state)
{
    m->state = state;
    m->frame = 0.0f;
}

static inline void setAP1MotCtrlVector(AP1MotCtrl *m, Vec4A_P_1 *v)
{
    CopyVector(&m->vec, v);
    setAP1MotCtrlState(m, 0);
}

void attackMotInit(char *a0)
{
    Vec4A_P_1 pos;
    Mtx44 mtx;
    Vec4A_P_1 dir;
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    GetRootPosition(&pos, (void *)D_00639EA4);
    MatrixDrive_SetTransposeMatrix(&mtx, p + 0x230);
    _ApplyMatrix((int)&dir, (int)&mtx, (int)&pos);
    setAP1MotCtrlVector((AP1MotCtrl *)(p + 0x10), &dir);
    setAP1MotCtrlVector((AP1MotCtrl *)(p + 0x60), &dir);
}

int attackMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 0);
    if (ret != -1)
        return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(float *)(p + 0x1C8) += 0.05f;
    if (*(float *)(p + 0x1C8) > 1.0f) {
        setAP1MotCtrlState((AP1MotCtrl *)(p + 0x10), 2);
        setAP1MotCtrlState((AP1MotCtrl *)(p + 0x60), 2);
        return 0;
    }
    return 3;
}
