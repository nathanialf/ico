/* func_0019E1C0 — set struct field at +0xB8 to 1, return 1.
 * See ../func_0013B858/notes.md (sibling, same regalloc miss).
 */
int func_0019E1C0(int *self)
{
    self[46] = 1;   /* +0xB8 == word index 0x2E */
    return 1;
}
