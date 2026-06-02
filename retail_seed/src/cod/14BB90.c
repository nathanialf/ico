extern int D_00717758[];

int func_0024BB90(int a0, int a1)
{
    int old = D_00717758[5];
    *(volatile int *)&D_00717758[6] = a1;
    *(volatile int *)&D_00717758[5] = a0;
    return old;
}
