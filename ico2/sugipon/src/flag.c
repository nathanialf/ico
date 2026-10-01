#include "flag.h"
#include "ios.h"
#include "attackCheckBoundary.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "Light.h"
#include "Matrix.h"
#include "Primitive.h"
#include "clothAnimation.h"
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
static inline void setFlag4PointMesh(Mesh3D *mesh, char *cl, float k, int id)
{
    float *tbl = flag4PointFix[id][0];
    Prim3DVec *v = mesh->st;
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
            v[i * m + j].y = c + (d - c) * i / (n - 1);
            v[i * m + j].x = a + (b - a) * j / (m - 1);
        }
    }
}

void SetFlag4PointFixID(GObj *self, int a1, int id)
{
    char *w;
    short ang;

    w = GOBJ_SUB(self)->work;
    *(int *)(w + 0x10) = a1;
    _UnitMatrix(MatrixDrive_GetMatrix());
    ang = -a1 * 0x4000;
    MatrixDrive_RotMatrixZ(ang);
    _ApplyMatrix((char *)GOBJ_SUB(self) + 0xA0, MatrixDrive_GetMatrix(),
                 (char *)GOBJ_SUB(self) + 0xA0);
    RotQuaternionZ(GOBJ_SUB(self)->root.quat, ang);
    setFlag4PointMesh(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), *(char **)(w + 0x8),
                      a1 * 0.25f, id);
    prim_UpdateMesh3D(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), 8, 0);
    prim_UpdateMesh3D(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), 8, 1);
}

/* InitFlagGeo builds a cloth from the laid-out object's row of layoutClothDef
   (attackCheckBoundary.h): its corners, the cloth type in the low four bits,
   the rows and columns, the length shared out over the columns and the fall. */

/* the flag's cloth template, copied into every new config; InitFlagGeo below
   sits on the listing's own lines (85-226), fenced from clang-format */
static ClothCfg flagCfg = {8, 50.0f, 10, 0, 0, 0, 5.0f};

/* clang-format off */
char *InitFlagGeo(char *self, char *arg)
{
    char *p = iosMallocDebug(ios_partition_sugipon, 20, __FILE__, __LINE__);
    Vec4Flag v[4];
    char *mesh;
    Vec4Flag *q;
    const LayoutClothDef *ent = &layoutClothDef[*(int *)(arg + 0x30)];
    float k = ent->length / (float)ent->count;
    float d;
    int type, i, j;
    char *cl = iosMallocDebug(ios_partition_sugipon, 56, __FILE__, __LINE__);
    *(ClothCfg *)cl = flagCfg;
    *(float *)(cl + 0x18) = ent->weight;
    *(int *)(cl + 0x1C) = -1;
    *(int *)(cl + 0x0) = ent->rows;
    *(int *)(cl + 0x8) = ent->count;

    mesh = iosMallocDebug(ios_partition_sugipon, *(int *)(cl + 0x0) * 48, __FILE__, __LINE__);
    ((FlagNodeWord *)(cl + 0x10))->i = (int)mesh;
    /* a union member store (alias set 0): the ROM's schedule keeps it, and
       line 126's store, ahead of every ent load below */
    v[0].m[0] = ent->pt[0][0];
    v[0].m[1] = -ent->pt[0][1];
    v[0].m[2] = ent->pt[0][2];
    v[0].m[3] = 1.0f;

    v[1].m[0] = ent->pt[1][0];
    v[1].m[1] = -ent->pt[1][1];
    v[1].m[2] = ent->pt[1][2];
    v[1].m[3] = 1.0f;

    v[2].m[0] = ent->pt[2][0];
    v[2].m[1] = -ent->pt[2][1];
    v[2].m[2] = ent->pt[2][2];
    v[2].m[3] = 1.0f;

    v[3].m[0] = ent->pt[3][0];
    v[3].m[1] = -ent->pt[3][1];
    v[3].m[2] = ent->pt[3][2];
    v[3].m[3] = 1.0f;

    *(int *)(p + 0x10) = 0;
    type = ent->kind & 0xF;
    *(int *)(p + 0x0) = type;
    switch (type) {
    case 1:
    case 2:
        FLAG_ALLOC_NODES(((SubHandle *)(self + 0x15C))->sub, *(int *)(cl + 0x8) - 1);
        CopyVector(((SubHandle *)(self + 0x15C))->p + 0xA0, ZeroPoint);
        CopyVector(mesh + 0x10, &v[0]);
        CopyVector(mesh + 0x20, &v[1]);
        *(int *)mesh = -1;
        *(float *)(mesh + 4) = k;
        *(int *)(p + 4) = InitClothes(cl);
        break;
        /* 132-133 read the 0x15C slot through SubHandle, as cage.c and
           girlForceField.c do: an alias-set-0 read, so each store in the
           block forces the re-read the ROM does and the buffer words keep
           their pointer types; the other slot reads here are GOBJ_SUB's */
    case 0:
        *(char **)(cl + 0x14) = iosMallocDebug(ios_partition_sugipon, strlen(ent->name) + 1, __FILE__, __LINE__);
        strcpy(*(char **)(cl + 0x14), ent->name);


        _InterVectorXYZ(GOBJ_SUB(self)->root.pos, &v[0], &v[1], 0.5f);
        _SubVectorXYZ(&v[0], &v[0], GOBJ_SUB(self)->root.pos);
        _SubVectorXYZ(&v[1], &v[1], GOBJ_SUB(self)->root.pos);

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
        *(char **)(cl + 0x14) = iosMallocDebug(ios_partition_sugipon, strlen(ent->name) + 1, __FILE__, __LINE__);
        strcpy(*(char **)(cl + 0x14), ent->name);
        /* 179 and 191 index v, the walking pointer being loop.c's giv (the
           ROM initialises it after gcse's preheader insertions); 191 and 196
           count with j, which the ROM keeps in a register of its own apart
           from i's */
        CopyVector(GOBJ_SUB(self)->root.pos, ZeroPoint);
        for (i = 0; i < 4; i++)
            _AddVectorXYZ(GOBJ_SUB(self)->root.pos, GOBJ_SUB(self)->root.pos, &v[i]);
        _ScaleVectorXYZ(GOBJ_SUB(self)->root.pos, GOBJ_SUB(self)->root.pos, 0.25f);
        ((FlagNodeWord *)((char *)GOBJ_SUB(self) + 0xAC))->f = 1.0f;
        for (i = 0, q = v; i < 4; i++, q++)
            _SubVectorXYZ(q, q, GOBJ_SUB(self)->root.pos);

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




    if (GOBJ_SUB(self)->colData != 0) {

        *(int *)(p + 0xC) = 1;
    } else { *(int *)(p + 0xC) = 0; }

    GOBJ_SUB(self)->disp = 0;

    GOBJ_SUB(self)->nodes->rot[0] = GOBJ_SUB(self)->nodes->rot[1] = GOBJ_SUB(self)->nodes->rot[2] = 0;
    ((FlagNodeWord *)&GOBJ_SUB(self)->nodes->scale[0])->f = ((FlagNodeWord *)&GOBJ_SUB(self)->nodes->scale[1])->f = ((FlagNodeWord *)&GOBJ_SUB(self)->nodes->scale[2])->f = 1.0f;

    SetIdentityQuaternion(GOBJ_SUB(self)->root.quat);

    return p;
}

/* clang-format on */

void FlagGeo(GObj *self)
{
    char *gd;
    char *o;

    gd = GOBJ_SUB(self)->work;
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

void FlagDL(GObj *self)
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

    gd = GOBJ_SUB(self)->work;
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
            GetMatrixFromQuaternionPos((char *)GOBJ_SUB(self)->nodeMtx + (i * 0x40 - 0x40), &l0,
                                       base + (i * 0x10 - 0x10));
        }
        p2o_DispVU1Multi(self);
        break;
    case 0:
        light_MakeLightMatrix(GOBJ_SUB(self), 0);
        m = (char *)GOBJ_SUB(self)->lightMtx;
        DispClothMesh(*(char **)(o + 0x4), m + 0x40, m);
        break;
    case 4:
        light_MakeLightMatrix(GOBJ_SUB(self), 0);
        m = (char *)GOBJ_SUB(self)->lightMtx;
        DispClothMesh(*(char **)(o + 0x4), m + 0x40, m);
        break;
    }
}
