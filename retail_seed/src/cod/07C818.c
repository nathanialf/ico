/* src/cod/07C818.c — func_0017C818 */

extern void func_0014A308(char *a0);

void func_0017C818(char *a0)
{
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    *p &= ~((long long)0x400 << 32);
    return func_0014A308(a0);
}
