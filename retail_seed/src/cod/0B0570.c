extern int D_00706110[];

void func_001B0570(void)
{
    int *p = D_00706110;
    int i = 0x1D;
    do {
        if (p[0] != 0) {
            p[3] |= 1;
        }
        i--;
        p += 8;
    } while (i >= 0);
}
