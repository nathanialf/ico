#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", add_wp_pos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayLengthOfPos_Pos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayPointWithRangeFromPos);

typedef struct WayNode { char _0[8]; struct WayNode *prev; struct WayNode *next; char _10[0x30]; } WayNode;
extern WayNode D_004C7CF0[];

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", CopyWpPos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayLengthOfGObj_Pos);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayLengthOfGObj_GObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", WayPointWithRangeFromGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_kidnap", func_00202D68);
