#include "common.h"




extern void ExecFrameDependSequence(int a0);
extern void playSEConditionID(int a0, int a1);
extern void func_00190430(char *self, int val);
extern int isysGObjSearchFromObjLayoutID();
void RopeFixGeo(void) {}

INCLUDE_ASM("asm/nonmatchings/src/ropeFix", RopeFixDL);

void InitRopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjLayoutID(0x15);
    if (v0 != 0) {
        return func_00190430(v0, a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/ropeFix", func_001E98C8);

int func_001E9910(void)
{
    return 0;
}

void func_001E9918(int a0)
{
    playSEConditionID(a0, 0x33);
}

void func_001E9920(int a0)
{
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x38);
}

INCLUDE_ASM("asm/nonmatchings/src/ropeFix", func_001E9950);

