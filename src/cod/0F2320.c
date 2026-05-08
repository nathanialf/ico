extern int func_00176DE0(int a, int b, int c, int d);

void func_001F2320(volatile unsigned int self)
{
    volatile int local;
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = func_00176DE0((int)((char *)s + 0x10), (int)((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}
