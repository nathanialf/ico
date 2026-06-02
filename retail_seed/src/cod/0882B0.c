extern int D_00631AE4;
extern void func_00104508(int a0, int a1);
extern void func_00154D20(int a0, int a1);

void func_001882B0(int a0, int a1)
{
    if (a1 == D_00631AE4) {
        func_00154D20(a0, a1);
    } else {
        func_00104508(a0, a1);
    }
}
