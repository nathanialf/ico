/* func_00106AA8 — tail-call wrapper into func_00105F00, struct field +0x590.
 *
 * Same no-TCO failure as func_00106A98 (sibling). See
 * ../func_00106A98/notes.md for the analysis. Original asm tail-jumps
 * with no frame; ee-gcc 2.96 -O2 emits a full prologue/epilogue around
 * a `j func_00105F00` because it doesn't sibling-call.
 */
extern void func_00105F00(void *dst, void *src);

void func_00106AA8(void *dst, char *self)
{
    func_00105F00(dst, *(char **)(self + 0x15C) + 0x590);
}
