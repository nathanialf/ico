extern void func_002591F0(int a, int b, int c, int d);

int func_0025AC18(int a0, int a1, int a2, int a3, int t0, int t1, int t2)
{
    int packed1 = (a1 << 24) | (a2 << 16) | ((a3 & 0xFF) << 8) | t0;
    int packed2 = (t1 << 24) | t2;
    func_002591F0(4, a0, packed1, packed2);
    return 0;
}
