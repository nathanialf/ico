/* func_0013F878 — set struct field at +0x18 to 1, return 1.
 * See ../func_0013B858/notes.md for the regalloc failure mode (sibling).
 */
int func_0013F878(int *self)
{
    self[6] = 1;   /* +0x18 == word index 6 */
    return 1;
}
