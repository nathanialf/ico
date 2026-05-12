/* src/cod/065270.c — func_00165270 */

extern char D_002A4C48[];

void func_00165270(int *a0)
{
    char *base = D_002A4C48 + a0[2] * 0x4C;
    *(int *)(base + 0x48) |= 0x40000;
}
