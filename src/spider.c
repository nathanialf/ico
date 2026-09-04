#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/spider", InitSpiderLayoutGeo);
INCLUDE_ASM("asm/nonmatchings/src/spider", WakeUpLayoutedSpiders);
INCLUDE_ASM("asm/nonmatchings/src/spider", CallSpidersToReviveEnemy);
INCLUDE_ASM("asm/nonmatchings/src/spider", SpiderLayoutGeo);
INCLUDE_ASM("asm/nonmatchings/src/spider", DispAllMemberOfSpider);
INCLUDE_ASM("asm/nonmatchings/src/spider", SetSpiderGroupReviveStatus);
INCLUDE_ASM("asm/nonmatchings/src/spider", DeadAllSpiders);
INCLUDE_ASM("asm/nonmatchings/src/spider", GetAliveSpiders);
INCLUDE_ASM("asm/nonmatchings/src/spider", DeleteSpiderFromLayoutGroup);
INCLUDE_ASM("asm/nonmatchings/src/spider", GetNearestOfLayoutSpiders);
INCLUDE_ASM("asm/nonmatchings/src/spider", CheckSpidersInsideOfReviveRange);
int RestoreSpiderLayoutGeo(void)
{
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/spider", RestoreSpiderLayoutExtGeo);
INCLUDE_ASM("asm/nonmatchings/src/spider", MemorySpiderLayout);
INCLUDE_ASM("asm/nonmatchings/src/spider", WakeUpSpidersFromGenerator);
INCLUDE_ASM("asm/nonmatchings/src/spider", DeleteAllSpidersOfLayoutGroup);
INCLUDE_ASM("asm/nonmatchings/src/spider", SleepSpiderGroup);
INCLUDE_ASM("asm/nonmatchings/src/spider", WakeupSpiderGroup);
