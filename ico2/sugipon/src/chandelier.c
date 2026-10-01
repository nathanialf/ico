#include "typedef.h"
#include "gobj.h"
#include "matrixDrive.h"
#include "chandelier.h"

/* kept local: rope.h does not compile in this TU (too many arguments to function `SetRopeFixPoint') */
extern void SetRopeFixPoint();
/* kept local: int (int) here, void (void *) in DisplayP2O.h */
extern int p2o_DispVU1DObjMulti(int a0);
/* kept local: int (int) here, void (void) in DisplayP2O.h */
extern int p2o_SetDefaultEnviroment(int a0);

inline int InitChandelierGeo(void)
{
    return 0;
}

void ChandelierGeo(char *a0)
{
    int obj = isysGObjSearchFromObjKindID_begin(20);
    if (obj != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), GOBJ_SUB(a0)->f_C);
        MatrixDrive_TransMatrix(0.0f, 50.0f, 250.0f);
        SetRopeFixPoint(obj, MatrixDrive_GetMatrix() + 0x30, 0);
    }
}

void ChandelierDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
