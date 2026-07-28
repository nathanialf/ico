#include "common.h"


extern int D_00632780;
INCLUDE_ASM("asm/nonmatchings/src/enemy-control", EnemyCtrlBeforeFunc);

INCLUDE_ASM("asm/nonmatchings/src/enemy-control", InitEnemyCtrlGeo);

INCLUDE_ASM("asm/nonmatchings/src/enemy-control", IsSelectID_EnemyCtrl);

void func_00192040(void)
{
    D_00632780 = 1;
}

