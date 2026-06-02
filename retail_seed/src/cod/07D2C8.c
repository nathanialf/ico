extern int func_0017E188(void);
extern float func_001EA108(int a0);
extern void func_001A6E28(int *p);
extern int D_00559EA8[];

float func_0017D2C8(void)
{
    int v = func_0017E188();
    if (v != 0) {
        return func_001EA108(v);
    }
    func_001A6E28(D_00559EA8);
    return 0.0f;
}
