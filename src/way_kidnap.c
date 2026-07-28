#include "common.h"

typedef struct WpNode { int f0; char _4[0x14]; int f18; char _1C[0x0C]; int f28; char _2C[0x08]; } WpNode;


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

extern WpNode D_004CC1A4;

WpNode *CopyWpPos(WpNode *p)
{
    WpNode *end = &D_004CC1A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0) return q;
        } while (q != end);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayLengthOfGObj_Pos);

WpNode *WayLengthOfGObj_GObj(WpNode *p)
{
    WpNode *end = &D_004CC1A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0 && q->f28 != 0) return q;
        } while (q != end);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromGObj);

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", func_00205900);

