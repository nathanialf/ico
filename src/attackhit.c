#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/attackhit", inner_check);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", MakeAttackPack_Actor);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCheckSameGroup);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackMail);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCheckHit);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackGenerate);
void EnemyAttackCenter(void) {}
void BoyAttackCenter(void) {}
INCLUDE_ASM("asm/nonmatchings/src/attackhit", CommonAttackCenter);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", _AttackCenter);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCenter_WithDir);
