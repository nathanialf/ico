/* func_001B0A58 — set sdata word D_00633024 to 1, return 1.
 * See ../func_0013B858/notes.md (sibling, same regalloc miss).
 */
extern int D_00633024;

int func_001B0A58(void)
{
    D_00633024 = 1;
    return 1;
}
