/* src/cod/0651C8.c — func_001651C8 */

extern char D_002A4C48[];

void func_001651C8(int *a0)
{
    char *base = D_002A4C48 + a0[2] * 0x4C;
    *(int *)(base + 0x48) &= ~0x200000;
}
