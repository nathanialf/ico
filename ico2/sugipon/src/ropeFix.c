#include "typedef.h"
#include "gobj.h"
#include "chain.h"
#include "ropeFix.h"
#include "DisplayP2O.h"

inline int InitRopeFixGeo(void)
{
    return 0;
}

void RopeFixGeo(GObj *fix)
{
    GObj *chain = isysGObjSearchFromObjKindID_begin(21);
    if (chain != 0) {
        SetChainParentGObj(chain, fix);
    }
}

void RopeFixDL(GObj *fix)
{
    Sub15C *sub = fix->dobj;
    if (sub->disp != 0) {
        p2o_SetDefaultEnviroment();
        p2o_DispVU1DObjMulti(sub);
    }
}
