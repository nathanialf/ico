#include "typedef.h"
#include "cageFix.h"
#include "DisplayP2O.h"

inline int InitCageFixGeo(void)
{
    return 0;
}

void CageFixGeo(GObj *a0)
{
    char *g = isysGObjSearchFromObjKindID_begin(44);
    if (g != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(a0)->nodeMtx);
        SetCageFixGeometry(g, MatrixDrive_GetMatrix() + 0x30, GOBJ_SUB(a0)->nodeQuat);
    }
}

void CageFixDL(GObj *a0)
{
    int *s0 = a0->dobj;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment();
        return p2o_DispVU1DObjMulti(s0);
    }
}
