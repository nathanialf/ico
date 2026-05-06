/* func_0012FE60 — array index helper, stride 0x2E8 (D_00681538 base).
 *   return (T*)((char*)&D_00681538 + a0 * 0x2E8);
 *
 * Sibling of func_0012FE08 (different base). Same la-macro 64-bit + mult
 * failure. See ../func_00105278/notes.md.
 */
extern char D_00681538[];

void *func_0012FE60(int a0)
{
    return &D_00681538[a0 * 0x2E8];
}
