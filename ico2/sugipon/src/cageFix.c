#include "typedef.h"
#include "cageFix.h"
#include "cage.h"
#include "gobj.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"

inline int InitCageFixGeo(void)
{
    return 0;
}

void CageFixGeo(GObj *a0)
{
    GObj *g = isysGObjSearchFromObjKindID_begin(44);
    if (g != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(a0)->nodeMtx);
        SetCageFixGeometry(g, MatrixDrive_GetMatrix()[3], GOBJ_SUB(a0)->nodeQuat);
    }
}

void CageFixDL(GObj *a0)
{
    Sub15C *d = a0->dobj;
    if (d->disp != 0) {
        p2o_SetDefaultEnviroment();
        p2o_DispVU1DObjMulti(d);
    }
}
