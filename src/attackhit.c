#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/attackhit", inner_check);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", MakeAttackPack_Actor);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCheckSameGroup);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackMail);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCheckHit);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackGenerate);
void EnemyAttackCenter(void) {}
void BoyAttackCenter(void) {}
void CommonAttackCenter(char *a0) {
    char pack[0x80];
    MakeAttackPack_Actor(pack, a0, *(int *)(*(char **)(a0 + 0x164) + 0x150));
    AttackGenerate(pack);
}
INCLUDE_ASM("asm/nonmatchings/src/attackhit", _AttackCenter);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCenter_WithDir);
