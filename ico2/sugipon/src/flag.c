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

/* InitFlagGeo builds a cloth from the laid-out object's row of layoutClothDef
   (attackCheckBoundary.h): the line between its first two corners, the
   cloth type, the rows and columns, the length shared out over the columns
   and the fall.  Types 1 and 2 hang a node chain from the line's ends,
   type 0 a textured cloth along it; every type gets its clothes from
   InitClothes. */

/* the flag's cloth template, copied into every new config; InitFlagGeo
   passes __LINE__, so its lines below are kept out of clang-format (aug6's
   TRFILE puts its opening brace on line 30, its first allocation on
   line 31) */
static ClothCfg flagCfg = {8, 50.0f, 10, 0, 0, 0, 5.0f}; /* derived name */

/* clang-format off */
char *InitFlagGeo(char *self, char *arg)
{
    char *p = iosMallocDebug(ios_partition_sugipon, 16, __FILE__, __LINE__);
    Vec4Flag v[2];
    char *mesh;

    const LayoutClothDef *ent = &layoutClothDef[*(int *)(arg + 0x30)];
    float k = ent->length / (float)ent->count;
    float d;
    int type, i;
    ClothCfg *cl = iosMallocDebug(ios_partition_sugipon, 56, __FILE__, __LINE__);
    *cl = flagCfg;
    cl->weight = ent->weight;
    cl[1].num = -1;
    cl->num = ent->rows;
    cl->div = ent->count;

    mesh = iosMallocDebug(ios_partition_sugipon, cl->num * 48, __FILE__, __LINE__);
    ((FlagNodeWord *)&cl->anchors)->i = (int)mesh;
    /* the first two corners of the layout entry, with y negated and w set
       to 1 */
    v[0].m[0] = ent->pt[0][0];
    v[0].m[1] = -ent->pt[0][1];
    v[0].m[2] = ent->pt[0][2];
    v[0].m[3] = 1.0f;

    v[1].m[0] = ent->pt[1][0];
    v[1].m[1] = -ent->pt[1][1];
    v[1].m[2] = ent->pt[1][2];
    v[1].m[3] = 1.0f;

    type = ent->kind;
    *(int *)(p + 0x0) = type;
    switch (type) {
    case 1:
    case 2:
        FLAG_ALLOC_NODES(((SubHandle *)(self + 0x15C))->sub, cl->div - 1);
        CopyVector(((SubHandle *)(self + 0x15C))->p + 0xA0, ZeroPoint);
        CopyVector(mesh + 0x10, &v[0]);
        CopyVector(mesh + 0x20, &v[1]);
        *(int *)mesh = -1;
        *(float *)(mesh + 4) = k;
        break;
        /* types 1 and 2 above reach the 0x15C slot through SubHandle, as
           cage.c and girlForceField.c do; the other slot reads here are
           GOBJ_SUB's.  Type 0 hangs the cloth along the line between the
           two corners. */
    case 0:
        cl->tex = iosMallocDebug(ios_partition_sugipon, strlen(ent->name) + 1, __FILE__, __LINE__);
        strcpy(cl->tex, ent->name);


        _InterVectorXYZ(GOBJ_SUB(self)->root.pos, &v[0], &v[1], 0.5f);
        _SubVectorXYZ(&v[0], &v[0], GOBJ_SUB(self)->root.pos);
        _SubVectorXYZ(&v[1], &v[1], GOBJ_SUB(self)->root.pos);

        d = GetPointDistance(&v[0], &v[1]);
        cl->segLength = d / (float)cl->num;



        for (i = 0; i < cl->num; i++) {
            _InterVector(mesh + 0x10 + i * 48, &v[0], &v[1],
                         (float)i / (float)(cl->num - 1));
            *(int *)(mesh + i * 48) = -1;
            *(float *)(mesh + i * 48 + 4) = k;
        }

        break;
    }



    *(int *)(p + 4) = (int)InitClothes(cl);
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
    FlagWork *gd;
    ClothSet *o;

    gd = GOBJ_SUB(self)->work;
    o = gd->clothes;
    if (*(char **)((char *)GOBJ_SUB(self)) != 0 &&
        *(int *)(*(char **)((char *)GOBJ_SUB(self)) + 0x16C) == 0) {
        return;
    }
    GetRootMatrix(MatrixDrive_GetMatrix(), self);
    /* types 0 and 1 hang the cloth from its anchors, type 2 pins the far end
       of each row as well (GetClothAnimation's last argument); a flag that
       collides is its own wall owner, and the collision flag goes in the
       wall-count slot the callee recomputes */
    switch (gd->type) {
    case 0:
    case 1:
        GetClothAnimation(o->rec->pos, o->rec->vel, 0, MatrixDrive_GetMatrix(), gd->cfg,
                          gd->collide, gd->collide != 0 ? (int)self : 0, 0);
        break;
    case 2:
        GetClothAnimation(o->rec->pos, o->rec->vel, 0, MatrixDrive_GetMatrix(), gd->cfg,
                          gd->collide, gd->collide != 0 ? (int)self : 0, 1);
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
    FlagWork *gd;
    ClothSet *o;
    char *base;
    char *m;
    int i;
    int n;

    gd = GOBJ_SUB(self)->work;
    o = gd->clothes;
    if (*(char **)((char *)GOBJ_SUB(self)) != 0 &&
        *(int *)(*(char **)((char *)GOBJ_SUB(self)) + 0x16C) == 0) {
        return;
    }
    /* types 1 and 2 turn the cloth's first row into the object's node
       matrices and draw the nodes; type 0 draws the cloth mesh */
    switch (gd->type) {
    case 1:
    case 2:
        n = gd->cfg->div;
        base = (char *)o->rec->pos[0];
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
        DispClothMesh(o->rec, m + 0x40, m);
        break;
    }
}
