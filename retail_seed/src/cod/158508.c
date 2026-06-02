extern int func_00258450(int *a, int b);
extern int func_00258470(int *a, int b);

int func_00258508(int *self, int a1)
{
    int ret = func_00258450(self, a1);
    func_00258470(self, a1);
    return ret;
}
