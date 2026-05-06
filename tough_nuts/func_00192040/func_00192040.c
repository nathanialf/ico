/* func_00192040 — set sdata word D_00632780 to 1, return 1.
 * See ../func_0013B858/notes.md (sibling, same regalloc miss).
 */
extern int D_00632780;

int func_00192040(void)
{
    D_00632780 = 1;
    return 1;
}
