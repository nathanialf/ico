extern int D_00631B7C;
extern int D_00660A40[];
extern void func_0010D838(int *a0, int *a1);

void func_0010D408(void)
{
    int *p = &D_00660A40[D_00631B7C * 4];
    func_0010D838(p, p);
}
