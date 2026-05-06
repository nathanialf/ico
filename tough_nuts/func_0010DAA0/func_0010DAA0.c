/* func_0010DAA0 — array index helper, stride 16.
 *   return &D_00660A40[D_00631B7C];   // stride 0x10
 *
 * See ../func_00105278/notes.md — same `la` macro 64-bit expansion
 * failure (lui/daddiu/daddu vs original lui/addiu/addu, plus a
 * scheduling difference).
 */
extern int D_00631B7C;
extern int D_00660A40[];

int *func_0010DAA0(void)
{
    return &D_00660A40[D_00631B7C * 4];   /* stride 16 = 4 words */
}
