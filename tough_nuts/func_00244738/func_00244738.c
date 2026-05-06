/* func_00244738 — read-modify-write a single sdata word.
 *   tmp = D_00550738;
 *   D_00550738 = a0;
 *   return tmp;
 *
 * The original uses one `lui $v1` shared by both `lw` and `sw` —
 * i.e. `lui+lw %lo` and `sw %lo` both index off the same `$v1`,
 * with the load happening before the store. ee-gcc 2.96 -O2 instead
 * splits the `la` into a separate `addiu` + uses two registers, so
 * the encoding diverges. See ../func_00105278/notes.md for the
 * la-macro 64-bit family this belongs to.
 */
extern int D_00550738;

int func_00244738(int a0)
{
    int tmp = D_00550738;
    D_00550738 = a0;
    return tmp;
}
