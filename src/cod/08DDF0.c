extern int D_00632CBC;
extern int D_00633DA0;
extern char D_0055ABA8[];
extern void func_001A6A30(int a, int b, int c, char *d);
extern void func_0018D4F0(int a0);

void func_0018DDF0(int a0)
{
    if (D_00632CBC & 1) {
        D_00633DA0 = D_00633DA0 + 0xA;
        func_001A6A30(0xA, D_00633DA0, 0x0FFFFFFF, D_0055ABA8);
    }
    func_0018D4F0(a0);
}
