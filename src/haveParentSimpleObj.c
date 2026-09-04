#include "common.h"

extern void UpdateRootMatrix();

void ParentSimpleObjGeo(int a0, int a1, int a2, int a3)
{
    UpdateRootMatrix(a0, a1, a2, a3);
}
extern void p2o_DispVU1();

void ParentSimpleObjDL(int a0, int a1, int a2, int a3)
{
    p2o_DispVU1(a0, a1, a2, a3);
}
int InitParentSimpleObjGeo(void)
{
    return 0;
}
