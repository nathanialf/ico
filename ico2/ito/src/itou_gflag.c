#include "itou_gflag.h"

/* kept local: itou_boss.h does not compile in this TU (too many arguments to function `itou_boss_gflag_init') */
extern void itou_boss_gflag_init();

void itouGFlagInit(int a0, int a1, int a2, int a3)
{
    itou_boss_gflag_init(a0, a1, a2, a3);
}

void itouGflagLoad(int a0, int a1, int a2, int a3)
{
    itou_boss_gflag_init(a0, a1, a2, a3);
}

void itouGflagSave(void) {}
