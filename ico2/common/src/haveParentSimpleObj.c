#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
int InitParentSimpleObjGeo(void);
int InitParentSimpleObjGeo(void);
/* kept local: this TU's uses of UpdateRootMatrix do not fit the prototype in geometryManager.h */
extern void UpdateRootMatrix();
/* kept local: this TU's uses of p2o_DispVU1 do not fit the prototype in DisplayP2O.h */
extern void p2o_DispVU1();

inline int InitParentSimpleObjGeo(void)
{
    return 0;
}

void ParentSimpleObjGeo(int a0, int a1, int a2, int a3)
{
    UpdateRootMatrix(a0, a1, a2, a3);
}

void ParentSimpleObjDL(int a0, int a1, int a2, int a3)
{
    p2o_DispVU1(a0, a1, a2, a3);
}
