/* delayslot_queue: func_00243B60
 * TU: src/cod/vendor_2418A0.c   ROM addr: 0x00243B60
 * Reverted 2026-08-01: matched only under MODERN gas. gcc/inline-asm output
 * leaves `jr ra` with an UNFILLED delay slot; ROM has `sq a2,0(a0)` in the slot
 * (modern gas hoists it, period ee-as 2.9-991111 leaves nop).
 */
void func_00243B60(void *a0, void *a1) {
    QCOPY16_NO_NOP("$a2");
}
