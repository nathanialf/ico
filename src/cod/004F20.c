extern int D_00631B40;
extern char D_0065FA40[];
extern void func_00105F20(char *a0, char *a1);

void func_00104F20(void)
{
    int i = ++D_00631B40;
    func_00105F20(&D_0065FA40[i * 64], &D_0065FA40[i * 64 - 64]);
}
