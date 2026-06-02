extern int *func_00187990(int *a0);

int func_00187908(int *a0)
{
    int *p = func_00187990(a0);
    int *q = func_00187990(a0);
    return p[0x3C / 4] - q[0x38 / 4];
}
