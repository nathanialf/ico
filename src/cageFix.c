#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/cageFix", CageFixGeo);
extern int p2o_DispVU1DObjMulti(int a0);
extern int p2o_SetDefaultEnviroment(int a0);

void CageFixDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
int InitCageFixGeo(void)
{
    return 0;
}
