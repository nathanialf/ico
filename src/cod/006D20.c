extern void func_00105F00(int a, int b);
extern void func_00105F90(int a, int b, int c);

void func_00106D20(int a0, int *a1)
{
    int *p = (int *)a1[0x15C / 4];
    func_00105F00(a0, (int)((char *)p + 0x130));
    func_00105F90(a0, a0, (int)((char *)p + 0xA0));
}
