#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", MakeAttackPack_Actor);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCheckSameGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackMail);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCheckHit);

extern int D_0062A8E0;

void AttackGenerate(void) {
    D_0062A8E0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", EnemyAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", BoyAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", CommonAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCenter_WithDir);

void func_0017F0D0(void) {
}

void func_0017F0D8(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F110);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F2A0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F450);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F470);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F4C8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F518);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F670);
