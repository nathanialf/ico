extern char D_006D04B4[];
extern void func_0018CFE0(int a0);

void func_001886D0(int a0)
{
    int masked = a0 & 0xFF;
    D_006D04B4[0] = 1;
    if (masked == 0) {
        return;
    }
    return func_0018CFE0(masked);
}
