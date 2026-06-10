#include "common.h"

typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", add_wp_pos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayLengthOfPos_Pos);

extern char D_004C6FF0[];
extern Nd D_004C7CF0[];

int WayPointWithRangeFromPos(int a0, int a1)
{
    int *ch = (int *)&D_004C6FF0[a0 * 0x34];
    Nd *node = &D_004C7CF0[a1];
    Nd *old;
    node->f8 = 0;
    old = (Nd *)ch[2];
    ch[2] = (int)node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}

typedef struct WayNode { char _0[8]; struct WayNode *prev; struct WayNode *next; char _10[0x30]; } WayNode;

int WayPointWithRangeFromPos2(int a0, int a1, int a2) {
    WayNode *A = &D_004C7CF0[a1];
    WayNode *B = &D_004C7CF0[a2];
    WayNode *old = A->next;
    A->next = B;
    B->prev = A;
    B->next = old;
    old->prev = B;
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", NearestEnemyFromGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", NumOfWpPos);

typedef struct WpNode { int f0; char pad[0x30]; } WpNode;
extern WpNode D_004C7CBC;

WpNode *CopyWpPos(WpNode *p)
{
    WpNode *end = &D_004C7CBC;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0) return q;
        } while (q != end);
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayLengthOfGObj_Pos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayLengthOfGObj_GObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayPointWithRangeFromGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", func_00202D68);
