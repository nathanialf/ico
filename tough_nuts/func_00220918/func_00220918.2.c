/* func_00220918 (st08a) — count-4 seed, derived 2026-06-19.
 *
 * BREAKTHROUGH over the prior count-10/6 seed: the dev idiom comes straight
 * from the MATCHED siblings actSt05dDoor2UpChk (st05d) and actSt07ChanEvent
 * (st07a):
 *     GObj { char pad[0xB4]; int *unkB4; }   // here also unkB0 at 0xB0
 *     D_004CC7C0[1] = (int)handler;          // int array, (int) cast
 *     s->unkB4 = D_004CC7C0;                  // int* field
 * In st05d's ROM gcc REORDERS this to unkB4-first with the array store sunk
 * into the BoxBarSoundOn delay slot.
 *
 * For func_00220918 the extra `D_0062A894 = 1` and `s->unkB0 = 0` stores shift
 * the schedule: unkB0 takes the call delay, the array store lands at slot 15.
 * This seed (unkB0-first) reproduces the ENTIRE function byte-identically
 * EXCEPT the array store `sw v1,4(v0)` is hoisted to slot 11 (expected: 15),
 * with the gp store one slot off — real_count = 4, diff is one instruction.
 *
 * PROVEN irreducible in clean C (mapped the full reachable codegen space,
 * ~10 states): the array store carries actSt05eSolar's ONLY reference, so it
 * must be source-EARLY for the breadth-first %hi/%hi/%lo/%lo la (achieved) but
 * source-LATE for the correct store schedule — mutually exclusive. Permuter-
 * class: needs a non-source-equivalent split of the actSt05eSolar
 * materialization from its store. Seed the permuter with THIS shape.
 *
 * (D_0062A894 and D_004CCAA0 are distinct named globals -> gcc proves no-alias,
 * so gp-store position is free; the earlier "gp/array coupling" theory was wrong.)
 */
#include "common.h"

extern int D_0062A894;

typedef struct GObj {
    char pad[0xB0];
    int *unkB0;
    int *unkB4;
} GObj;

extern int D_004CCAA0[];
extern void actSt05eSolar(void);
extern void BoxBarSoundOn(int a0, int a1);
extern void _ACTWait(int);

void func_00220918(volatile int a0) {
    GObj *s = (GObj *)*(int *)(a0 + 0x164);
    s->unkB0 = 0;
    D_004CCAA0[1] = (int)actSt05eSolar;
    D_0062A894 = 1;
    s->unkB4 = D_004CCAA0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}
