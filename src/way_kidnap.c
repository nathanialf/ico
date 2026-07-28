#include "common.h"


typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;
extern unsigned char D_004CAEC0[];
extern Nd D_004CC1E0[];
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", add_wp_pos);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfPos_Pos);

int WayPointWithRangeFromPos(int a0, int a1)
{
    int *ch = (int *)&D_004CAEC0[a0 * 0x34];
    Nd *node = &D_004CC1E0[a1];
    Nd *old;
    node->f8 = 0;
    old = (Nd *)ch[2];
    ch[2] = (int)node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}

int WayPointWithRangeFromPos2(int dummy, int idx1, int idx2)
{
    int *node_a = (int *)((char *)D_004CC1E0 + idx1 * 0x40);
    int *node_b = (int *)((char *)D_004CC1E0 + idx2 * 0x40);
    int *old = (int *)node_a[3];
    node_a[3] = (int)node_b;
    node_b[2] = (int)node_a;
    node_b[3] = (int)old;
    old[2] = (int)node_b;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", NearestEnemyFromGirl);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", NumOfWpPos);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", CopyWpPos);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfGObj_Pos);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfGObj_GObj);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromGObj);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", func_00205900);

