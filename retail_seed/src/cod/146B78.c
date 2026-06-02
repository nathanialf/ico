extern int D_00550868[];
extern int D_0055086C[];
extern int func_00100520(int *p);

void func_00246B78(void)
{
    if (D_00550868[0] == -1) {
        int buf[8];
        buf[5] = 0;
        buf[2] = 1;
        buf[1] = 1;
        D_00550868[0] = func_00100520(buf);
        D_0055086C[0] = func_00100520(buf);
    }
}
