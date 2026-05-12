extern void func_002591F0(int a0, int a1, int a2, int a3);

int func_0025DEF0(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        func_002591F0(0x42, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}
