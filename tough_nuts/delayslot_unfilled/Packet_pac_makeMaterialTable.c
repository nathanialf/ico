/* delayslot_queue: pac_makeMaterialTable
 * TU: src/Packet.c   ROM addr: 0x0011A2A8
 * Reverted 2026-08-01: matched only under MODERN gas. gcc leaves the
 * `j debug_assertMessage` tail call with an UNFILLED delay slot; ROM has
 * `lw a2,4(v0)` in the slot. Period ee-as 2.9-991111 leaves nop.
 */
void pac_makeMaterialTable(int a0)
{
    register char *base = D_00672FD0;
    (*(volatile int * volatile *)(base + 0x24))[0] = 0;
    (*(volatile int * volatile *)(base + 0x24))[1] = (a0 << 16) | 0x6C008000;
    {
        volatile int *p = *(volatile int * volatile *)(base + 0x24);
        debug_assertMessage(D_005551A0, p[0], p[1], (int *)p, a0);
    }
}

/* NOTE (revert bookkeeping): while this function was matched, Packet.c also
 * defined its assert string:
 *   const char D_005551A0[0x20] = "VIFUNPACK :%08x %08x (%p:%d)\n";
 * On revert, splat migrated that rodata into the stub .s
 * (asm/nonmatchings/src/Packet/pac_makeMaterialTable.s dlabel D_005551A0),
 * so the C definition was REMOVED and D_005551C0 was moved after the
 * pac_makeMaterialTableLine INCLUDE_ASM to keep .o section order == VMA
 * order. When re-matching, restore the C def in its original slot (between
 * D_00555190 and D_005551C0) and move D_005551C0 back. */
