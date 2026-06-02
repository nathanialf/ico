#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/enemy-control", EnemyCtrlBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/enemy-control", InitEnemyCtrlGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/enemy-control", IsSelectID_EnemyCtrl);

extern int D_0062AA58;

void func_0018F940(void) {
    D_0062AA58 = 1;
}
