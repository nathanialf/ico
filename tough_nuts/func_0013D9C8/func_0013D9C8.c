extern void func_00100410(void);
extern int func_00100470(int a0);

int func_0013D9C8(int a0)
{
    int v0;
    if (a0 == 0) {
        func_00100410();
        v0 = 0;
    } else {
        v0 = *(int *)(a0 + 0x30);
    }
    return func_00100470(v0);
}
