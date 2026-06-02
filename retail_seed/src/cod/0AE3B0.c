/* src/cod/0AE3B0.c — func_001AE3B0 */

extern long long D_004B3D10[];

void func_001AE3B0(void)
{
    long long mask = -2LL;
    long long *p = (long long *)D_004B3D10;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}
