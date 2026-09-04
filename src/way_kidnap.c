#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", add_wp_pos);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfPos_Pos);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromPos);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromPos2);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", NearestEnemyFromGirl);
extern int D_0063BD60;

int NumOfWpPos(void) {
    return D_0063BD60;
}
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", CopyWpPos);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfGObj_Pos);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfGObj_GObj);
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromGObj);
int func_00215C68(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", func_00215CA0);
