extern int D_00717758[];

int func_0024BBA8(int a0, int a1)
{
    int old = D_00717758[3];
    *(volatile int *)&D_00717758[4] = a1;
    *(volatile int *)&D_00717758[3] = a0;
    return old;
}
