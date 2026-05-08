extern int D_006A6F30[];
extern int func_00100410(void);
extern void func_001003B0(int a, int b);

void func_0013D440(int *a0, int a1)
{
    int *v;
    if (a0 == 0) {
        v = (int *)D_006A6F30[func_00100410()];
    } else {
        v = a0;
    }
    v[0x18 / 4] = a1;
    func_001003B0(v[0x30 / 4], a1);
}
