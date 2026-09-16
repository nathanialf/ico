#include "common.h"
#include "typedef.h"
#include "gobj.h"
#include "chain.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
int InitRopeFixGeo(void);
int InitRopeFixGeo(void);
/* kept local: this TU's uses of p2o_DispVU1DObjMulti do not fit the prototype in DisplayP2O.h */
extern int p2o_DispVU1DObjMulti(int a0);
/* kept local: this TU's uses of p2o_SetDefaultEnviroment do not fit the prototype in DisplayP2O.h */
extern int p2o_SetDefaultEnviroment(int a0);

inline int InitRopeFixGeo(void)
{
    return 0;
}

void RopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjKindID_begin(0x15);
    if (v0 != 0) {
        return SetChainParentGObj(v0, a0);
    }
}

void RopeFixDL(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        p2o_SetDefaultEnviroment(a0);
        return p2o_DispVU1DObjMulti((int)s0);
    }
}
