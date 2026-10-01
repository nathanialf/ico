#include "typedef.h"
#include "gobj.h"
#include "chain.h"
#include "ropeFix.h"
#include "DisplayP2O.h"

inline int InitRopeFixGeo(void)
{
    return 0;
}

void RopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjKindID_begin(21);
    if (v0 != 0) {
        return SetChainParentGObj(v0, a0);
    }
}

void RopeFixDL(GObj *a0)
{
    int *s0 = a0->dobj;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment();
        return p2o_DispVU1DObjMulti(s0);
    }
}
