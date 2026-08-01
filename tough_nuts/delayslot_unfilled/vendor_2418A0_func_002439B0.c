/* delayslot_queue: func_002439B0
 * TU: src/cod/vendor_2418A0.c   ROM addr: 0x002439B0
 * Reverted 2026-08-01: matched only under MODERN gas. gcc/inline-asm output
 * leaves `jr ra` with an UNFILLED delay slot; ROM has `sq t3,48(a0)` in the slot
 * (modern gas hoists it, period ee-as 2.9-991111 leaves nop).
 */
void func_002439B0(void *a0, void *a1) {
    VU0_LSGP(lq, 8, 0x0, 5);
    VU0_LSGP(lq, 9, 0x10, 5);
    VU0_LSGP(lq, 10, 0x20, 5);
    VU0_LSGP(lq, 11, 0x30, 5);
    VU0_REG("pextlw $12, $9, $8");
    VU0_REG("pextuw $13, $9, $8");
    VU0_REG("pextlw $14, $11, $10");
    VU0_REG("pextuw $15, $11, $10");
    VU0_REG("pcpyld $8, $14, $12");
    VU0_REG("pcpyud $9, $12, $14");
    VU0_REG("pcpyld $10, $15, $13");
    VU0_REG("pcpyud $11, $13, $15");
    VU0_LSGP(sq, 8, 0x0, 4);
    VU0_LSGP(sq, 9, 0x10, 4);
    VU0_LSGP(sq, 10, 0x20, 4);
    VU0_LSGP(sq, 11, 0x30, 4);
}

