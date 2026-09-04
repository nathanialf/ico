#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/enemy-control", EnemyCtrlBeforeFunc);
extern int D_0063C2D4;
extern int D_0063C2D8;
extern int D_0063C2DC;

int InitEnemyCtrlGeo(void)
{
    D_0063C2D4 = 0;
    D_0063C2D8 = -1;
    D_0063C2DC = 0;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/enemy-control", IsSelectID_EnemyCtrl);
