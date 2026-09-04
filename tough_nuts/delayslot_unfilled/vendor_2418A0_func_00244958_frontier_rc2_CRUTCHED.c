/* sceDmaPutStallAddr — frontier shape, round 3 (2026-08-16).
 * MEASURED: real_count 2 / diff_sites 2, instruction count == ROM's 10.
 * gcc's OWN reorg fills the beq delay slot with this NON-volatile
 * register-form load; the B1 store is cprop-folded to the ROM's $at macro.
 * NOT COMMITTABLE: `*p = old;` is a zero-code dead store (banned crutch).
 * Residual: `lw a1,0(v0)` vs ROM `lw v0,0(v0)`, and `daddu v0,a1,zero`
 * vs ROM `nop` — both because the write-back keeps p live past the load.
 */
unsigned int sceDmaPutStallAddr(unsigned int a0) {
    unsigned int *p = (unsigned int *)0x1000E060;
    unsigned int old = *p;
    *p = old;
    if (a0 != 0xFFFFFFFFu) {
        *p = a0;
    }
    return old;
}
