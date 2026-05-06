/* func_0012FE08 — array index helper, stride 0x2E8 (variable * 0x2E8).
 *   return (T*)((char*)&D_006812D0 + a0 * 0x2E8);
 *
 * Stride is non-power-of-2 so the original uses `mult` instead of `sll`.
 * Otherwise the same la-macro 64-bit failure as func_00105278.
 */
extern char D_006812D0[];

void *func_0012FE08(int a0)
{
    return &D_006812D0[a0 * 0x2E8];
}
