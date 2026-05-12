extern void func_002591F0(int a0, int a1, int a2, int a3);

int func_0025E280(unsigned int a0, unsigned long long a1, unsigned int a2)
{
    int ret = -1;
    if (a0 < 2 && a2 <= 0x1FFFFF && (a1 & 0xFF000000) == 0) {
        func_002591F0(0x4F, (int)a1, a2, a0);
        ret = 0;
    }
    return ret;
}
