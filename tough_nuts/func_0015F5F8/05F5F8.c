/* src/cod/05F5F8.c — func_0015F5F8 */

void func_0015F5F8(volatile unsigned int a0)
{
    volatile int local;
    char *p = (char *)*(int *)(a0 + 0x164);
    long long v0 = *(long long *)(p + 0x20);
    long long v1 = *(long long *)(p + 0x18);
    v0 = (v0 & ~0x2000000LL) | 0x40000;
    v1 &= ~((long long)0x10000 << 32);
    *(long long *)(p + 0x20) = v0;
    *(long long *)(p + 0x18) = v1;
}
