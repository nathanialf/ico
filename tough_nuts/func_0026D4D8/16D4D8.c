extern int D_00633FF0;
extern int func_00245680(int *p, int *q);

int func_0026D4D8(int *self, int *x, int *y)
{
    int ret;
    D_00633FF0 = 0;
    ret = func_00245680(x, y);
    if (ret == -1) {
        if (D_00633FF0 != 0) {
            *self = D_00633FF0;
        }
    }
    return ret;
}
