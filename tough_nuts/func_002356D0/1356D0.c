extern int D_00631AE4;
extern void func_0017CD18(int x, float a, float b, float c, float d, float e, float f);
extern void func_00203AA0(int x);

void func_002356D0(int x)
{
    int *p;
    p = (int *)((int *)D_00631AE4)[0x15C/4];
    p[0x4E8/4] = 1;
    p = (int *)((int *)D_00631AE4)[0x15C/4];
    p[0x4E8/4] = 0;
    func_0017CD18(x, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    func_00203AA0(0x3C);
}
