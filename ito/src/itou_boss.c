#include "common.h"

extern unsigned char D_006CCE50[];
extern void func_00260568(void *a0, int a1, int a2);

void effect_end_func(void) {
    func_00260568(D_006CCE50, 0, 0xD50);
}

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
