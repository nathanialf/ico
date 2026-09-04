#include "common.h"

extern void SetChainParentGObj(char *self, int val);
extern int isysGObjSearchFromObjKindID_begin();

void RopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjKindID_begin(0x15);
    if (v0 != 0) {
        return SetChainParentGObj(v0, a0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/ropeFix", RopeFixDL);
int InitRopeFixGeo(void)
{
    return 0;
}
