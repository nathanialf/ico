#include "common.h"

#include "ico/types.h"

extern void SetChainParentGObj(char *self, int val);
extern int isysGObjSearchFromObjKindID_begin();

void RopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjKindID_begin(0x15);
    if (v0 != 0) {
        return SetChainParentGObj(v0, a0);
    }
}
extern int p2o_DispVU1DObjMulti(int a0);
extern int p2o_SetDefaultEnviroment(int a0);

void RopeFixDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
int InitRopeFixGeo(void)
{
    return 0;
}
