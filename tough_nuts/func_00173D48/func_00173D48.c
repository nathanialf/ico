/* CLEAN seed — proven byte-identical to ROM when assembled by the PERIOD
 * assembler (tools/cc/ee-gcc2.9-991111/bin/as). The trailing __asm__ barrier
 * in the old seed was a CRUTCH and has been removed; this is the dev shape.
 *
 * gcc 2.9-991111 -O2 emits exactly:
 *   subu sp,32 ; sd ra,16 ; sw a0,0 ; jal Exec ; nop ; ld ra,16 ; jr ra ; addu sp,32
 * == ROM. The ONLY thing that breaks the match is the ASSEMBLER: jimaku is a
 * mixed TU whose INCLUDE_ASM siblings use splat's %gp_rel, which BOTH period
 * ee-as builds (2.96 and 2.9-991111) reject ("Bad expression"), so the TU
 * falls back to modern mips-linux-gnu-as, which over-fills the jal delay slot
 * with the preceding `sw a0` (ROM leaves it nop). See notes.md. NOT a source
 * floor — blocked on assembler parity until jimaku's %gp_rel siblings are
 * matched (then `use_old_as jimaku` works) or old-as learns %gp_rel. */
extern void ACTLookTargetSystem_Exec(void);
void func_00173D48(void *a0) {
    void *volatile q = a0;
    ACTLookTargetSystem_Exec();
}
