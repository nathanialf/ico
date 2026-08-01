/* delayslot_queue: EnemySetfDisappearAll
 * TU: src/enemy.c   ROM addr: 0x001CE6F0
 * Reverted 2026-08-01: matched only under MODERN gas. gcc leaves the
 * `j InitMotionOrient` tail call with an UNFILLED delay slot; ROM has
 * `sw zero,0x3BC(v0)` in the slot (modern gas hoists it, period
 * ee-as 2.9-991111 leaves nop). Re-match goal: a source shape where gcc
 * itself fills the slot (or emits the filled noreorder sequence).
 */
void EnemySetfDisappearAll(int *self)
{
    register int *alias;
    alias = self;

    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x2B0) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x310) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x3B8) = 0;
    *(int volatile *)((char *)*(int * volatile *)((char *)alias + 0x15C) + 0x3BC) = 0;
    InitMotionOrient(self);
}
