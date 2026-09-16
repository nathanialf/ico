#include "common.h"
#include "typedef.h"
#include "gobj.h"
#include "matrixDrive.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
int InitChandelierGeo(void);
int InitChandelierGeo(void);
/* kept local: the declaration in matrixDrive.h changes this TU codegen */
extern void CopyMatrix();
/* kept local: this TU's uses of SetRopeFixPoint do not fit the prototype in rope.h */
extern void SetRopeFixPoint();
/* kept local: this TU's uses of p2o_DispVU1DObjMulti do not fit the prototype in DisplayP2O.h */
extern int p2o_DispVU1DObjMulti(int a0);
/* kept local: this TU's uses of p2o_SetDefaultEnviroment do not fit the prototype in DisplayP2O.h */
extern int p2o_SetDefaultEnviroment(int a0);

inline int InitChandelierGeo(void)
{
    return 0;
}

void ChandelierGeo(char *a0)
{
    int obj = isysGObjSearchFromObjKindID_begin(0x14);
    if (obj != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(int *)(*(char **)(a0 + 0x15C) + 0xC));
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
