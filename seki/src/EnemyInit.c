#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", enemy_Initialize);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", enemy_GetPositionTable);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", func_001F8BF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/EnemyInit", func_001F8C30);

extern void func_001F8C30(void);

void func_001F8CA8(void) {
    func_001F8C30();
}
