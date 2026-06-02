/* src/cod/0AE3E8.c — func_001AE3E8 */

extern long long D_004B3D10[];

void func_001AE3E8(void)
{
    long long mask = -3LL;
    long long *p = (long long *)D_004B3D10;
    int i = 0xB5;
    do {
        *p &= mask;
        p = (long long *)((char *)p + 0x40);
        i--;
    } while (i >= 0);
}
