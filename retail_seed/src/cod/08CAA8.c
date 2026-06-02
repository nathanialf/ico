extern volatile int D_006D06C0[];

void func_0018CAA8(int a0, int a1, int a2)
{
    if (a2 < D_006D06C0[2]) {
        return;
    }
    D_006D06C0[0] = a0;
    D_006D06C0[2] = a2;
    D_006D06C0[1] = a1;
}
