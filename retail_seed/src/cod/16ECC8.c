extern int func_002455A0(int a1, int a2, int a3);
extern int D_00633FF0[];

int func_0026ECC8(int *self, int a1, int a2, int a3)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_002455A0(a1, a2, a3);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}
