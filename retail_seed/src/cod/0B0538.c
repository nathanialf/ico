extern int D_00706110[];
extern int D_00633E6C;
extern int D_00633E70;

void func_001B0538(void)
{
    int i;
    for (i = 0x1D; i >= 0; i--) {
        D_00706110[i * 8] = 0;
    }
    D_00633E6C = 0;
    D_00633E70 = 0;
}
