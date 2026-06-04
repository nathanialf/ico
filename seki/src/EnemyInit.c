#include "common.h"

extern int D_004C3850[];

int enemy_Initialize(void) {
    int idx = D_004C3850[0];
    int sub = D_004C3850[4] + 0xFFF80000;
    return ((&D_004C3850[idx])[1] - sub) >> 4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", enemy_GetPositionTable);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", func_001F8BF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", func_001F8C30);

extern void func_001F8C30(void);

void func_001F8CA8(void) {
    func_001F8C30();
}
