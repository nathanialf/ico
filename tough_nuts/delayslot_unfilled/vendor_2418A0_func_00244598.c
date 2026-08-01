/* delayslot_queue: func_00244598
 * TU: src/cod/vendor_2418A0.c   ROM addr: 0x00244598
 * Reverted 2026-08-01: matched only under MODERN gas. gcc/inline-asm output
 * leaves `jr ra` with an UNFILLED delay slot; ROM has `sq v1,0(a1)` in the slot
 * (modern gas hoists it, period ee-as 2.9-991111 leaves nop).
 */
extern int D_005506F0[];

void func_00244598(void) {
    typedef unsigned int u128 __attribute__((mode(TI)));
    register int v __asm__("$8");

    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;

    __asm__ __volatile__(
        ".set noreorder\n"
        "cfc2.ni $8, $vi28\n"
        "ori $8, $8, 0x2\n"
        "ctc2.ni $8, $vi28\n"
        "sync.p\n"
        ".set reorder\n"
        : "=r"(v) : : "memory"
    );

    {
        volatile u128 *dst = (volatile u128 *)0x10004000;
        u128 *src = (u128 *)D_005506F0;
        *dst = src[0];
        *dst = src[1];
    }
}

