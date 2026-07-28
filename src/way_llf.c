#include "common.h"



extern unsigned char D_004CAEC0[];
extern void debug_assertMessage(char *fmt, ...);
extern char D_0061B1B0[];
INCLUDE_ASM("asm/nonmatchings/src/way_llf", InitWayPointSystem);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", CreateWayGroup);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", CreateTempWayGroup);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", DeleteWayGroup);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", CloseWayGroup);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", CreateWayPoint);

int AddWayPoint(int *self, int which) {
    if (self == 0) {
        return 0;
    }
    debug_assertMessage(D_0061B1B0, self);
    if (which == 0) {
        return self[0x8 / 4];
    }
    return self[0xC / 4];
}

INCLUDE_ASM("asm/nonmatchings/src/way_llf", AddWayPointTop);

int InsertWayPointAfter(int idx)
{
    char *base = &D_004CAEC0[idx * 0x34];
    return (*((int *)((&D_004CAEC0[idx * 0x34]) + 0x28))) != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_llf", DeleteWayPoint);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", WayGroup_begin);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", WayGroup_next);

INCLUDE_ASM("asm/nonmatchings/src/way_llf", WayBridge_begin);

