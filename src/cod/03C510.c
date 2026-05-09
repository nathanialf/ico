extern int func_0013D098(int a0);

void func_0013C510(int *a0, int a1, int a2, int a3)
{
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)&func_0013D098;
    }
    a0[2] = a2;
    a0[3] = a3;
}
