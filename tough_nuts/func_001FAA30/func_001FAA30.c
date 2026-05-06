/* func_001FAA30 — set sdata word D_006337B8 to 1, return 1.
 * See ../func_0013B858/notes.md (sibling, same regalloc miss).
 */
extern int D_006337B8;

int func_001FAA30(void)
{
    D_006337B8 = 1;
    return 1;
}
