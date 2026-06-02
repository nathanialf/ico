extern int func_00245590(int a1);
extern int D_00633FF0[];

int func_0026EC10(int *self, int a1)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_00245590(a1);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}
