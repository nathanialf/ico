extern unsigned int func_002455A8(int a1);
extern int D_00633FF0[];

unsigned int func_0026D128(int *self, int a1)
{
    unsigned int ret;
    D_00633FF0[0] = 0;
    ret = func_002455A8(a1);
    if (ret == 0xFFFFFFFFU) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}
