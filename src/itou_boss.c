#include "common.h"


extern int D_00631990;
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", effect_end_func);

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", func_00198000);

int bossCtrlBeforeFunc(void)
{
    int v = D_00631990;
    int r = 0;
    if (v == 0x54) goto yes;
    if (v == 3) goto yes;
    if (v != 0x2E) goto no;
yes:
    r = 1;
no:
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", BossEnemyFunc);

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", gene_enemy);

extern unsigned char D_006D35E0[];

void BossCtrlGeo(void) {
    D_006D35E0[0] = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", func_00198338);

