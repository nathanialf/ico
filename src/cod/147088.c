extern int D_00550864[];
extern int func_00100520(int *buf);

void func_00247088(void)
{
    if (D_00550864[0] == -1) {
        int buf[16];
        buf[1] = 1;
        buf[2] = 1;
        buf[5] = 0;
        D_00550864[0] = func_00100520(buf);
    }
}
