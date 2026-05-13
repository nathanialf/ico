extern void func_00100890(int *flag, long long *result);

long long func_00245410(void)
{
    int flag;
    long long result;
    flag = 0;
    func_00100890(&flag, &result);
    *(volatile int *)0x1000F000 = 4;
    while ((*(volatile int *)0x1000F000 & 4) == 0 && flag == 0) {}
    *(volatile int *)0x1000F000 = 4;
    return result;
}
