extern void func_001CE768(int self, int a, int p, int b);

void func_0015F650(volatile unsigned int self)
{
    volatile int local;
    int *p = (int *)((int *)self)[0x164 / 4];
    *(long long *)((char *)p + 0x20) = *(long long *)((char *)p + 0x20) | 1;
    func_001CE768((int)self, 1, (int)p, 1);
    ((int *)((int *)self)[0x15C / 4])[0x654 / 4] = 0;
}
