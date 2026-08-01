/* delayslot_queue: func_00243B70
 * TU: src/cod/vendor_2418A0.c   ROM addr: 0x00243B70
 * Reverted 2026-08-01: matched only under MODERN gas. gcc/inline-asm output
 * leaves `jr ra` with an UNFILLED delay slot; ROM has `sq t1,48(a0)` in the slot
 * (modern gas hoists it, period ee-as 2.9-991111 leaves nop).
 */
void func_00243B70(void *a0, void *a1) {
    QCOPY64_PARALLEL_NO_NOP("$a2", "$a3", "$t0", "$t1");
}
