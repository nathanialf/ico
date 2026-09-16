#include "common.h"

/* kept local: this TU's uses of itou_boss_gflag_init do not fit the prototype in itou_boss.h */
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
