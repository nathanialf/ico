/* delayslot_queue: func_00244958
 * TU: src/cod/vendor_2418A0.c   ROM addr: 0x00244958
 * Reverted 2026-08-01: matched only under MODERN gas. gcc/inline-asm output
 * leaves `beq a0,v1,<+0x24>` with an UNFILLED delay slot; ROM has `lw v0,0(v0)` in the slot
 * (modern gas hoists it, period ee-as 2.9-991111 leaves nop).
 */
int func_00244958(unsigned int a0) {
    int old = *(volatile int *)0x1000E060;
    if (a0 != 0xFFFFFFFF) {
        *(volatile int *)0x1000E060 = a0;
    }
    return old;
}
