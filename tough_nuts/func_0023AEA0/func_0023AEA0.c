extern int func_0017E188(int a0);

void func_0023AEA0(int a0)
{
    volatile int local = a0;
    int v0;
    v0 = func_0017E188(0x1B5);
    *(int *)(v0 + 0x16C) = 1;
    v0 = func_0017E188(0x1B6);
    *(int *)(v0 + 0x16C) = 0;
}
