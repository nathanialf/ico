#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", enemy_Initialize);
extern char D_0063BD38[8];
extern int D_007285A0[];

int enemy_GetPositionTable(int idx, int sub_idx)
{
    register int factor;
    if (idx < 0 || idx >= *(int *)D_0063BD38) return 0;
    factor = 0x6C;
    return *(int *)((char *)D_007285A0 + idx * factor + sub_idx * 4);
}
