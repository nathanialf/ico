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
#include "include_asm.h"

/* InitFlagGeo builds a cloth from the laid-out object's row of layoutClothDef
   (attackCheckBoundary.h): its corners, the cloth type in the low four bits,
   the rows and columns, the length shared out over the columns and the fall. */

/* the flag's cloth template, copied into every new config; InitFlagGeo
   passes __LINE__, so its lines below are kept out of clang-format */
static ClothCfg flagCfg = {8, 50.0f, 10, 0, 0, 0, 5.0f}; /* derived name */

/* clang-format off */
INCLUDE_ASM(InitFlagGeo);

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
