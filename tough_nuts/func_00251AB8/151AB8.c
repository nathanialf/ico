extern int D_005524A8[100];
extern int D_005525C0[100];
extern void func_002525E8(int a0, int a1);

void func_00251AB8(int a0, int a1, int a2)
{
    int v;
    int t;
    v = a2 + 0x13;
    t = a2 + 0x22;
    if (v > -1) t = v;
    t = (t >> 4) << 4;
    D_005524A8[0] = a1;
    D_005525C0[0] = t;
    func_002525E8(a1, t);
}
