#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", Draw2DLine);

int Draw2DLineSeg_Start(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1];
}

int Draw2DLineSeg_Loop(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0] == 0;
}

int Draw2DLineG(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0x12] == 2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", _getLine);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", DrawLineG);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1310);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1438);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1470);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D1508);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lineManager", func_001D15C0);
