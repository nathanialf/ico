/* vsprintf — parked near-miss (INCOMPLETE). Command builder.
 * The `F65130Cmd` struct is NOT reconstructed and the original seed used
 * register pins ($7/$8, retired crutches). Recover the struct field offsets
 * (f00, f08=0x7FFFFFFF, f0C=0x208, f10, f14=0x7FFFFFFF, f54) from the asm and
 * drop the pins before this will build. D_0054D504 is declared in the TU;
 * func_00262D00 is a still-INCLUDE_ASM sibling. */
void vsprintf(int a0) {
    F65130Cmd cmd;
    cmd.f00 = a0;
    cmd.f08 = 0x7FFFFFFF;
    cmd.f0C = 0x208;
    cmd.f10 = a0;
    cmd.f14 = 0x7FFFFFFF;
    cmd.f54 = D_0054D504[0];
    func_00262D00(&cmd);
    *(char *)cmd.f00 = 0;
}
