extern void func_001FBA80(void);
extern void func_001FBAA8(int a0, int a1, int a2);
extern void func_001FB8B8(void);
extern int D_00555830[];

void func_0011FF30(void)
{
    func_001FBA80();
    func_001FBAA8(2, (int)D_00555830, 4);
    func_001FB8B8();
}
