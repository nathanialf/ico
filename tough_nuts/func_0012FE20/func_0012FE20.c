/* func_0012FE20 — array index helper, stride 0x2E8 (variable * 0x2E8).
 *   return (T*)((char*)&D_006812D0 + a0 * 0x2E8);
 *
 * Identical body to func_0012FE08 (different entry point). Same
 * la-macro 64-bit + mult failure mode. See ../func_00105278/notes.md.
 */
extern char D_006812D0[];

void *func_0012FE20(int a0)
{
    return &D_006812D0[a0 * 0x2E8];
}
