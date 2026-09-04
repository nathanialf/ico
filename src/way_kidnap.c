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
extern void GetRootPosition(int *buf, int x);
extern float WayLengthOfPos_Pos(int *mtx, int a1);

float WayLengthOfGObj_Pos(int a0, int a1) {
    int buf[4];
    if (a0 == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, a0);
    return WayLengthOfPos_Pos(buf, a1);
}
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfGObj_GObj);
extern int WayPointWithRangeFromPos(int *buf, int zero, float f);

int WayPointWithRangeFromGObj(int a0, float f)
{
    int buf[4];
    if (a0 == 0) {
        return -1;
    }
    GetRootPosition(buf, a0);
    return WayPointWithRangeFromPos(buf, 0, f);
}
int func_00215C68(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", func_00215CA0);
