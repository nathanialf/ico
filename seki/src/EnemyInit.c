#include "common.h"

extern int D_004C3850[];

int enemy_Initialize(void) {
    int idx = D_004C3850[0];
    int sub = D_004C3850[4] + 0xFFF80000;
    return ((&D_004C3850[idx])[1] - sub) >> 4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", enemy_GetPositionTable);

extern char D_0062BB18[8];
extern int D_0070A850[];

int func_001F8BF0(int idx, int sub_idx)
{
    register int factor;
    if (idx < 0 || idx >= *(int *)D_0062BB18) return 0;
    factor = 0x6C;
    return *(int *)((char *)D_0070A850 + idx * factor + sub_idx * 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", func_001F8C30);

extern void func_001F8C30(void);

void func_001F8CA8(void) {
    func_001F8C30();
}
