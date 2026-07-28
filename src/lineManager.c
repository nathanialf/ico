#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLine);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLineSeg_Start);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLineSeg_Loop);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLineG);

int _getLine(int a0)
{
    int new_var2;
    int v1 = *((int *)((*((int *)(a0 + 0x15C))) + 0x800));
    int new_var;
    int new_var3;
    int new_var4;
    new_var2 = v1 + 0x4;
    new_var3 = *((int *)new_var2);
    new_var4 = new_var3 == 1;
    if (new_var4) {
        new_var = *((int *)(v1 + 0x40));
        return new_var;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/lineManager", DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", DrawLineG);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D3F78);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D40A0);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D40D8);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D4170);

INCLUDE_ASM("asm/nonmatchings/src/lineManager", func_001D4228);

