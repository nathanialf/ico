extern int func_00245660(int a1, int a2);
extern int D_00633FF0[];

int func_0026EC68(int *self, int a1, int a2)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_00245660(a1, a2);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}
