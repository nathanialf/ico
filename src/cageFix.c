#include "common.h"

#include "ico/types.h"

/* header prototypes (order fixes the inline tail) */
int InitCageFixGeo(void);
extern int p2o_DispVU1DObjMulti(int a0);
extern int p2o_SetDefaultEnviroment(int a0);
inline int InitCageFixGeo(void)
{
    return 0;
}
void CageFixGeo(char *a0) {
    char *g = isysGObjSearchFromObjKindID_begin(0x2C);
    if (g != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(*(char **)(a0 + 0x15C) + 0xC));
        SetCageFixGeometry(g, MatrixDrive_GetMatrix() + 0x30, *(int *)(*(char **)(a0 + 0x15C) + 0x10));
    }
}
void CageFixDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
