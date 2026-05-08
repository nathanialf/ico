extern void func_002591F0(int a0, int a1, int a2, int a3);

int func_0025E0C0(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x10) {
        func_002591F0(0x49, a0, 0, 0);
        ret = 0;
    }
    return ret;
}
