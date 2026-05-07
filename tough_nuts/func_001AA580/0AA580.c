extern int D_00632C80;
extern void func_00247608(int a0);

int func_001AA580(void)
{
    int a0 = D_00632C80;
    if (a0 == -1) {
        return 0;
    }
    D_00632C80 = -1;
    func_00247608(a0);
    D_00632C80 = -1;
    return 0;
}
