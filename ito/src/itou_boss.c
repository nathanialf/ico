#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", effect_end_func);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", bossCtrlBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", BossEnemyFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", gene_enemy);

extern unsigned char D_006CCE50[];

void BossCtrlGeo(void) {
    D_006CCE50[0] = 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/itou_boss", itou_boss_gflag_init);

void InqCapsuleGhostBossStage(void) {
}
