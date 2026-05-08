extern int func_002591F0(int a, int b, int c, int d);

int func_0025E198(unsigned int a0, unsigned int a1)
{
    int ret = -1;
    if (a0 < 0x10) {
        if (a1 <= 0x1FFFFF) {
            func_002591F0(0x4D, (int)a0, (int)a1, 0);
            ret = 0;
        }
    }
    return ret;
}
