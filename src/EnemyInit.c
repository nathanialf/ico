#include "common.h"



extern int D_00710FA0[];
extern char D_00633828[8];
extern int D_004C7710[];
int enemy_Initialize(void)
{
    int idx = D_004C7710[0];
    int adj_cur = D_004C7710[4] - 0x80000;
    int end_off = (D_004C7710 + idx)[1];
    return (end_off - adj_cur) >> 4;
}

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", enemy_GetPositionTable);

int func_001FBF88(int idx, int sub_idx)
{
    register int factor;
    if (idx < 0 || idx >= *(int *)D_00633828) return 0;
    factor = 0x6C;
    return *(int *)((char *)D_00710FA0 + idx * factor + sub_idx * 4);
}

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", func_001FBFC8);

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", func_001FC040);

