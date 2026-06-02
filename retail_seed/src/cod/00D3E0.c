extern int D_00631B7C;
extern int D_00660A40[];
extern void func_0010DDB8(int *a0, int *a1, int a2);

void func_0010D3E0(int a0)
{
    int *p = &D_00660A40[D_00631B7C * 4];
    func_0010DDB8(p, p, a0);
}
