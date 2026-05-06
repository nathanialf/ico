/* func_0013B748 — array index helper, stride 0x200, return D_002811C0[i].
 *   return *(int*)((char*)&D_002811C0 + (a1 << 9));
 *
 * Same la-macro 64-bit failure as func_00105278. The function
 * dereferences word 0 of the indexed entry; func_0013B760 (sibling)
 * dereferences word 1 (offset +4).
 */
extern char D_002811C0[];

int func_0013B748(int a0, int a1)
{
    return *(int *)&D_002811C0[a1 * 0x200];
}
