/* func_0018CFD0 — set sdata byte D_00633D8D to 1, return 1.
 * See ../func_0013B858/notes.md (sibling, same regalloc miss).
 */
extern unsigned char D_00633D8D;

int func_0018CFD0(void)
{
    D_00633D8D = 1;
    return 1;
}
