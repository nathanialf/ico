extern int D_00631B40;
extern char D_0065FA40[];
extern void func_00105F20(char *base, char *p);

void func_00104F20(void)
{
    int n = D_00631B40 + 1;
    D_00631B40 = n;
    func_00105F20(D_0065FA40, D_0065FA40 + n * 0x40 - 0x40);
}
