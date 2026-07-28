#include "common.h"



extern void InitMotionOrient();
extern void func_0010F630();
void before_DrawPolygon(int a0, int a1, int a2, int a3)
{
    func_0010F630(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", after_DrawPolygon);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", _IsInScreen2);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", before_DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", after_DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", DrawPolygon);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", do_DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", IsPointIsInScreen);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", func_00196E78);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", func_00196F78);

void func_00197078(int a0, int a1, int a2, int a3)
{
    InitMotionOrient(a0, a1, a2, a3);
}

