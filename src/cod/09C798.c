extern unsigned short D_006327FC;
extern int D_00633DE4;
extern int D_00633DE0;

void func_0019C798(void)
{
    int a0;
    int v;
    D_006327FC += 0x7D0;
    D_00633DE4 += 0x1000;
    a0 = D_00633DE0;
    if (a0 > 0) {
        v = a0 - 1;
        D_00633DE0 = v;
        if (v < 0) D_00633DE0 = 0;
    }
}
