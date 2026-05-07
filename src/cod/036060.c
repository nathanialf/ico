extern int D_00632048;
extern int func_00139598(int a0);

void func_00136060(int *a0)
{
    if ((unsigned int)a0[1] < 0x2001) {
        int tmp = D_00632048;
        D_00632048 = (int)a0;
        a0[3] = tmp;
        return;
    }
    return func_00139598(*a0);
}
