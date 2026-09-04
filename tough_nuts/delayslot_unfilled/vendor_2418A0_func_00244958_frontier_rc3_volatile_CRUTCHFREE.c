/* sceDmaPutStallAddr — CRUTCH-FREE frontier, round 4 (2026-08-16).
 * ORACLE (match_diff vs real TU splice): real_count 3 / diff_sites 3,
 * and the built stream is a PURE PERMUTATION of ROM's 10 instructions
 * (scheduling.moved: lw v0,0(v0) + the slot nop; hint: moved@dbr).
 * Every insn byte-identical to ROM; only the lw sits BEFORE the beq with
 * a nop in the slot, instead of IN the slot with the nop after jr.
 * Blocker (source-verified, ee/gcc reorg.c:270 + resource.c:223): reorg's
 * resource_conflicts_p vetoes any trial insn whose resources carry
 * volatil=1, so the volatile load can never be placed in a delay slot by
 * gcc, and the one period assembler fills nothing.
 * This is the dev's source: the aug6 prototype twin func_00240E78 is
 * byte-matched with this exact body (aug6's default assembler ee-as 2.96
 * performs the fill there).
 * The previous rc2/sites2 shape (non-volatile + `*p = old;` write-back) is
 * crutched (zero-code dead store) and lives at
 * tough_nuts/delayslot_unfilled/vendor_2418A0_func_00244958_frontier_rc2_CRUTCHED.c
 */
unsigned int sceDmaPutStallAddr(unsigned int a0) {
    volatile unsigned int *p = (volatile unsigned int *)0x1000E060;
    unsigned int old = *p;
    if (a0 != 0xFFFFFFFFu) {
        *p = a0;
    }
    return old;
}
