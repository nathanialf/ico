/* func_0010DAB8 — array index helper, stride 16.
 *   return &D_00660A30[D_00631B7C];   // stride 0x10
 *
 * Sibling of func_0010DAA0 — same la-macro 64-bit failure mode.
 * See ../func_00105278/notes.md.
 */
extern int D_00631B7C;
extern int D_00660A30[];

int *func_0010DAB8(void)
{
    return &D_00660A30[D_00631B7C * 4];   /* stride 16 = 4 words */
}
