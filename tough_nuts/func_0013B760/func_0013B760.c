/* func_0013B760 — array index helper, stride 0x200, return field at +4.
 *   return *(int*)((char*)&D_002811C0 + (a1 << 9) + 4);
 *
 * Sibling of func_0013B748; +4 instead of +0. Same la-macro 64-bit
 * failure. See ../func_00105278/notes.md.
 */
extern char D_002811C0[];

int func_0013B760(int a0, int a1)
{
    return *(int *)&D_002811C0[a1 * 0x200 + 4];
}
