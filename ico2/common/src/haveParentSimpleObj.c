#include "haveParentSimpleObj.h"
#include "geometryManager.h"
#include "DisplayP2O.h"

inline int InitParentSimpleObjGeo(void)
{
    return 0;
}

void ParentSimpleObjGeo(GObj *self)
{
    UpdateRootMatrix(self);
}

void ParentSimpleObjDL(GObj *self)
{
    p2o_DispVU1(self);
}
