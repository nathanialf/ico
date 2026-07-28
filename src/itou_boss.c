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

extern int D_0055B030;
extern int D_0055BD40;
extern char D_0055C178[];
extern char D_0055C188[];
extern void *D_00632010;
extern signed char D_006D35F0[];
extern void actInitialize();
extern void actInitialize_ext_charcter(void *a0);
extern void apply_matrix_w1(void *a0, void *a1);
extern void debug_assertMessage(char *msg, int n);
extern int func_0013A0F8(void *ptr, int a1, char *file, int line);
extern void func_00243B60(void *a0, void *a1);

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", gene_enemy);

extern unsigned char D_006D35E0[];

void BossCtrlGeo(void) {
    D_006D35E0[0] = 1;
}

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", func_00198338);

