#include "common.h"
#include "DisplayP2O.h"
#include "Light.h"
#include "Matrix.h"
#include "Primitive.h"
#include "clothAnimation.h"
#include "flag.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include <string.h>

/* flag.o's .data opens with the corners (x, y) of each half of a fixed
   four-point flag, one row per id; January's 0x1C-byte .data is flagCfg alone. */
static float flag4PointFix[2][4][4] = {
    {{0.0f, 0.0f, 0.0f, 0.0f},
     {0.48f, 0.02f, 0.0f, 0.0f},
     {0.0f, 0.1f, 0.0f, 0.0f},
     {0.5f, 0.2f, 0.0f, 0.0f}},
    {{0.48f, 0.02f, 0.0f, 0.0f},
     {1.0f, 0.0f, 0.0f, 0.0f},
     {0.5f, 0.2f, 0.0f, 0.0f},
     {1.0f, 0.25f, 0.0f, 0.0f}},
};

/* The January listing puts these rows at flag.c:28-37, inside
   SetFlag4PointFixID's own span and below its def line, with no out-of-line
   body of their own: a helper gcc inlined whole into its single call site
   at line 70. */
static inline void setFlag4PointMesh(char *mesh, char *cl, float k, int id)
{
    float *tbl = flag4PointFix[id][0];
    float *v = *(float **)(mesh + 0x74);
    int n = *(int *)cl;
    int m = *(int *)(cl + 0x8);
    int i;
    int j;
    float a;
    float b;
    float c;
    float d;

    for (i = 0; i < n; i++) {
        a = tbl[0] + (tbl[4] - tbl[0]) * i / (n - 1);
        b = tbl[8] + (tbl[12] - tbl[8]) * i / (n - 1);
        for (j = 0; j < m; j++) {
            c = tbl[1] + (tbl[9] - tbl[1]) * j / (m - 1) + k;
            d = tbl[5] + (tbl[13] - tbl[5]) * j / (m - 1) + k;
            *(float *)((i * m + j) * 0x10 + (int)v + 0x4) = c + (d - c) * i / (n - 1);
            *(float *)((i * m + j) * 0x10 + (int)v) = a + (b - a) * j / (m - 1);
        }
    }
}

void SetFlag4PointFixID(char *self, int a1, int id)
{
    char *w;
    short ang;

    w = *(char **)((char *)GOBJ_SUB(self) + 0x830);
    *(int *)(w + 0x10) = a1;
    _UnitMatrix(MatrixDrive_GetMatrix());
    ang = -a1 * 0x4000;
    MatrixDrive_RotMatrixZ(ang);
    _ApplyMatrix((char *)GOBJ_SUB(self) + 0xA0, MatrixDrive_GetMatrix(),
                 (char *)GOBJ_SUB(self) + 0xA0);
    RotQuaternionZ((char *)GOBJ_SUB(self) + 0xD0, ang);
    setFlag4PointMesh(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), *(char **)(w + 0x8),
                      a1 * 0.25f, id);
    prim_UpdateMesh3D(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), 8, 0);
    prim_UpdateMesh3D(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), 8, 1);
}

extern void *D_0063A438;
extern void *D_0063A44C;
/* the cloth layout rows, 104 bytes each (layout-cloth-def.o) */
extern char layoutClothDef[];
extern int InitClothesNoShade(char *p);

/* the flag's cloth template, copied into every new config; InitFlagGeo below
   sits on the listing's own lines (85-226), fenced from clang-format */
static ClothCfg flagCfg = {8, 50.0f, 10, 0, 0, 0, 5.0f};

/* clang-format off */
char *InitFlagGeo(char *self, char *arg)
{
    char *p = iosMallocDebug(D_0063A438, 20, __FILE__, __LINE__);
    Vec4Flag v[4];
    char *mesh;
    Vec4Flag *q;
    char *ent = layoutClothDef + *(int *)(arg + 0x30) * 104;
    float k = *(float *)(ent + 0x60) / (float)*(int *)(ent + 0x5C);
    float d;
    int type, i, j;
    char *cl = iosMallocDebug(D_0063A438, 56, __FILE__, __LINE__);
    *(ClothCfg *)cl = flagCfg;
    *(float *)(cl + 0x18) = *(float *)(ent + 0x64);
    *(int *)(cl + 0x1C) = -1;
    *(int *)(cl + 0x0) = *(int *)(ent + 0x58);
    *(int *)(cl + 0x8) = *(int *)(ent + 0x5C);

    mesh = iosMallocDebug(D_0063A438, *(int *)(cl + 0x0) * 48, __FILE__, __LINE__);
    ((FlagNodeWord *)(cl + 0x10))->i = (int)mesh;
    /* a union member store (alias set 0): the ROM's schedule keeps it, and
       line 126's store, ahead of every ent load below */
    v[0].m[0] = *(float *)(ent + 0x20);
    v[0].m[1] = -*(float *)(ent + 0x24);
    v[0].m[2] = *(float *)(ent + 0x28);
    v[0].m[3] = 1.0f;

    v[1].m[0] = *(float *)(ent + 0x2C);
    v[1].m[1] = -*(float *)(ent + 0x30);
    v[1].m[2] = *(float *)(ent + 0x34);
    v[1].m[3] = 1.0f;

    v[2].m[0] = *(float *)(ent + 0x38);
    v[2].m[1] = -*(float *)(ent + 0x3C);
    v[2].m[2] = *(float *)(ent + 0x40);
    v[2].m[3] = 1.0f;

    v[3].m[0] = *(float *)(ent + 0x44);
    v[3].m[1] = -*(float *)(ent + 0x48);
    v[3].m[2] = *(float *)(ent + 0x4C);
    v[3].m[3] = 1.0f;

    *(int *)(p + 0x10) = 0;
    type = *(int *)(ent + 0x50) & 0xF;
    *(int *)(p + 0x0) = type;
    switch (type) {
    case 1:
    case 2:
        FLAG_ALLOC_NODES((char *)((GObjSubSlot *)(self + 0x15C))->handle, *(int *)(cl + 0x8) - 1);
        CopyVector((char *)((GObjSubSlot *)(self + 0x15C))->handle + 0xA0, ZeroPoint);
        CopyVector(mesh + 0x10, &v[0]);
        CopyVector(mesh + 0x20, &v[1]);
        *(int *)mesh = -1;
        *(float *)(mesh + 4) = k;
        *(int *)(p + 4) = InitClothes(cl);
        break;
        /* 132-133 read the 0x15C slot through GObjSubSlot, as cage.c and
           girlForceField.c do: an alias-set-0 read, so each store in the
           block forces the re-read the ROM does and the buffer words keep
           their pointer types; the other slot reads here are GOBJ_SUB's */
    case 0:
        *(char **)(cl + 0x14) = iosMallocDebug(D_0063A438, strlen(ent) + 1, __FILE__, __LINE__);
        strcpy(*(char **)(cl + 0x14), ent);


        _InterVectorXYZ((char *)GOBJ_SUB(self) + 0xA0, &v[0], &v[1], 0.5f);
        _SubVectorXYZ(&v[0], &v[0], (char *)GOBJ_SUB(self) + 0xA0);
        _SubVectorXYZ(&v[1], &v[1], (char *)GOBJ_SUB(self) + 0xA0);

        d = GetPointDistance(&v[0], &v[1]);
        *(float *)(cl + 4) = d / (float)*(int *)(cl + 0x0);



        for (i = 0; i < *(int *)(cl + 0x0); i++) {
            _InterVector(mesh + 0x10 + i * 48, &v[0], &v[1],
                         (float)i / (float)(*(int *)(cl + 0x0) - 1));
            *(int *)(mesh + i * 48) = -1;
            *(float *)(mesh + i * 48 + 4) = k;
        }

        *(int *)(p + 4) = InitClothes(cl);
        break;




    case 4:
        *(char **)(cl + 0x14) = iosMallocDebug(D_0063A438, strlen(ent) + 1, __FILE__, __LINE__);
        strcpy(*(char **)(cl + 0x14), ent);
        /* 179 and 191 index v, the walking pointer being loop.c's giv (the
           ROM initialises it after gcse's preheader insertions); 191 and 196
           count with j, which the ROM keeps in a register of its own apart
           from i's */
        CopyVector((char *)GOBJ_SUB(self) + 0xA0, ZeroPoint);
        for (i = 0; i < 4; i++)
            _AddVectorXYZ((char *)GOBJ_SUB(self) + 0xA0, (char *)GOBJ_SUB(self) + 0xA0, &v[i]);
        _ScaleVectorXYZ((char *)GOBJ_SUB(self) + 0xA0, (char *)GOBJ_SUB(self) + 0xA0, 0.25f);
        ((FlagNodeWord *)((char *)GOBJ_SUB(self) + 0xAC))->f = 1.0f;
        for (i = 0, q = v; i < 4; i++, q++)
            _SubVectorXYZ(q, q, (char *)GOBJ_SUB(self) + 0xA0);

        d = GetPointDistance(&v[0], &v[1]);
        *(float *)(cl + 4) = d / (float)(*(int *)(cl + 0x0) - 1);



        for (j = 0; j < 4; j++)
            CopyVector(mesh + 0x10 + j * 48, &v[j]);

        k = GetPointDistance(&v[0], &v[2]);
        d = GetPointDistance(&v[1], &v[3]);
        for (j = 0; j < *(int *)(cl + 0x0); j++) {
            *(int *)(mesh + j * 48) = -1;
            *(float *)(mesh + j * 48 + 4) = (k + (d - k) * j / (float)(*(int *)(cl + 0x0) - 1)) / (float)(*(int *)(cl + 0x8) - 1);
        }


        *(int *)(p + 4) = InitClothesNoShade(cl);
        break;
    }



    *(int *)(p + 8) = (int)cl;




    if (*(int *)((char *)GOBJ_SUB(self) + 0x70) != 0) {

        *(int *)(p + 0xC) = 1;
    } else { *(int *)(p + 0xC) = 0; }

    *(int *)((char *)GOBJ_SUB(self) + 0x74) = 0;

    *(int *)(*(char **)((char *)GOBJ_SUB(self) + 0x870) + 0x0) = *(int *)(*(char **)((char *)GOBJ_SUB(self) + 0x870) + 0x4) = *(int *)(*(char **)((char *)GOBJ_SUB(self) + 0x870) + 0x8) = 0;
    ((FlagNodeWord *)(*(char **)((char *)GOBJ_SUB(self) + 0x870) + 0x20))->f = ((FlagNodeWord *)(*(char **)((char *)GOBJ_SUB(self) + 0x870) + 0x24))->f = ((FlagNodeWord *)(*(char **)((char *)GOBJ_SUB(self) + 0x870) + 0x28))->f = 1.0f;

    SetIdentityQuaternion((char *)GOBJ_SUB(self) + 0xD0);

    return p;
}

/* clang-format on */

void FlagGeo(char *self)
{
    char *gd;
    char *o;

    gd = *(char **)((char *)GOBJ_SUB(self) + 0x830);
    o = *(char **)(gd + 0x4);
    if (*(char **)((char *)GOBJ_SUB(self)) != 0 &&
        *(int *)(*(char **)((char *)GOBJ_SUB(self)) + 0x16C) == 0) {
        return;
    }
    GetRootMatrix(MatrixDrive_GetMatrix(), self);
    switch (*(int *)gd) {
    case 0:
    case 1:
        GetClothAnimation(*(void **)(*(char **)(o + 0x4) + 0x4),
                          *(void **)(*(char **)(o + 0x4) + 0x8), 0, MatrixDrive_GetMatrix(),
                          *(int *)(gd + 0x8), *(int *)(gd + 0xC),
                          *(int *)(gd + 0xC) != 0 ? self : 0, 0);
        break;
    case 2:
        GetClothAnimation(*(void **)(*(char **)(o + 0x4) + 0x4),
                          *(void **)(*(char **)(o + 0x4) + 0x8), 0, MatrixDrive_GetMatrix(),
                          *(int *)(gd + 0x8), *(int *)(gd + 0xC),
                          *(int *)(gd + 0xC) != 0 ? self : 0, 1);
        break;
    case 4:
        GetClothAnimationFix4Points(*(void **)(*(char **)(o + 0x4) + 0x4),
                                    *(void **)(*(char **)(o + 0x4) + 0x8), *(int *)(gd + 0x8),
                                    MatrixDrive_GetMatrix());
        break;
    }
}

void FlagDL(char *self)
{
    Vec4Flag l0;
    Vec4Flag l10;
    Vec4Flag l20;
    Vec4Flag l30;
    Vec4Flag l40;
    char *gd;
    char *o;
    char *base;
    char *m;
    int i;
    int n;

    gd = *(char **)((char *)GOBJ_SUB(self) + 0x830);
    o = *(char **)(gd + 0x4);
    if (*(char **)((char *)GOBJ_SUB(self)) != 0 &&
        *(int *)(*(char **)((char *)GOBJ_SUB(self)) + 0x16C) == 0) {
        return;
    }
    switch (*(int *)gd) {
    case 1:
    case 2:
        n = *(int *)(*(char **)(gd + 0x8) + 0x8);
        base = *(char **)(*(char **)(*(char **)(o + 0x4) + 0x4));
        memset(&l0, 0, 0x10);
        l0.m[3] = 1.0f;
        memset(&l10, 0, 0x10);
        l10.m[1] = 1.0f;
        for (i = 1; i < n; i++) {
            _SubVector(&l20, base + i * 0x10, base + (i * 0x10 - 0x10));
            _NormalizeVector(&l30, &l20);
            GetDifferencialQuaternionWithNoRegularize(&l40, &l30, &l10);
            MultiQuaternion(&l0, &l40, &l0);
            CopyVector(&l10, &l30);
            GetMatrixFromQuaternionPos(*(char **)((char *)GOBJ_SUB(self) + 0xC) + (i * 0x40 - 0x40),
                                       &l0, base + (i * 0x10 - 0x10));
        }
        p2o_DispVU1Multi(self);
        break;
    case 0:
        light_MakeLightMatrix((char *)GOBJ_SUB(self), 0);
        m = (char *)GOBJ_SUB(self)->p_874;
        DispClothMesh(*(char **)(o + 0x4), m + 0x40, m);
        break;
    case 4:
        light_MakeLightMatrix((char *)GOBJ_SUB(self), 0);
        m = (char *)GOBJ_SUB(self)->p_874;
        DispClothMesh(*(char **)(o + 0x4), m + 0x40, m);
        break;
    }
}
