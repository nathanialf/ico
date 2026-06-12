/* func_00246608 — parked near-miss (best differ rc8/rc9, ninja FAILS).
 * Apply into common/src/PObj.c replacing the INCLUDE_ASM line.
 * Needs: extern char D_FFFFF[]; extern int D_0070F600[]; extern int D_0054AB34[];
 *
 * Busy-wait delay loop. ROM: init `lui %hi(D_FFFFF)` only (i=0x100000), loop
 * `addiu i,i,%lo(D_FFFFF)` (=-1) each iter until i==-1. The decrement carries a
 * %lo(D_FFFFF) RELOCATION inside the loop (D_FFFFF=0xFFFFF, absolute, config/
 * undefined_syms_auto.aug6.txt). A literal `i-- / i=0x100000` form is byte-equal
 * to the relocs BUT ninja still fails — there is ALSO a real regalloc diff: the
 * final `sw zero, D_0054AB34` uses $v0 in ROM, $v1 when built (the loop counter
 * lands in the wrong reg). Reproducing `addiu i,i,%lo(D_FFFFF)` (reloc, not
 * literal) inside the loop while keeping the counter in $v0 is the open problem;
 * `(int)D_FFFFF` adds the full 0xFFFFF, `& 0xFFFF` emits andi+addu (rc11). */
extern char D_FFFFF[];
extern int D_0070F600[];
extern int D_0054AB34[];

int func_00246608(void) {
    int i;
    int ret;
    int val;
    goto no_delay;
    again:
    i = (int)D_FFFFF;
    L:
    i--;
    __asm__("nop\nnop\nnop\nnop");
    if (i != -1) goto L;
    no_delay:
    ret = func_002427A8(D_0070F600, 0x80000003, 0);
    if (ret < 0) return -1;
    val = D_0070F600[0x24 / 4];
    if (val == 0) goto again;
    D_0054AB34[0] = 0;
    return 0;
}
