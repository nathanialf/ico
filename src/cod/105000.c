extern void func_00104508(int *buf, int x);
extern int func_00204410(int *buf, int zero, float f);

int func_00205000(int a0, float f)
{
    int buf[4];
    if (a0 == 0) {
        return -1;
    }
    func_00104508(buf, a0);
    return func_00204410(buf, 0, f);
}
