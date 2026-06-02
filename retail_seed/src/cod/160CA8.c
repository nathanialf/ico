extern int D_0071EB68[];
extern int func_00260BF8(void);

void func_00260CA8(void)
{
    if (D_0071EB68[0] == 0) {
        D_0071EB68[0] = 1;
        return func_00260BF8();
    }
    return 1;
}
