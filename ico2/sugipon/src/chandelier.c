#include "typedef.h"
#include "gobj.h"
#include "matrixDrive.h"
#include "chandelier.h"
#include "DisplayP2O.h"

/* kept local: rope.h does not compile in this TU (too many arguments to function `SetRopeFixPoint') */
extern void SetRopeFixPoint();

inline int InitChandelierGeo(void)
{
    return 0;
}

void ChandelierGeo(GObj *a0)
{
    int obj = isysGObjSearchFromObjKindID_begin(20);
    if (obj != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), GOBJ_SUB(a0)->nodeMtx);
        MatrixDrive_TransMatrix(0.0f, 50.0f, 250.0f);
        SetRopeFixPoint(obj, MatrixDrive_GetMatrix()[3], 0);
    }
}

void ChandelierDL(GObj *a0)
{
    int *s0 = a0->dobj;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment();
        return p2o_DispVU1DObjMulti(s0);
    }
}
