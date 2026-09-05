#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
int InitParentSimpleObjGeo(void);
int InitParentSimpleObjGeo(void);
extern void UpdateRootMatrix();
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
