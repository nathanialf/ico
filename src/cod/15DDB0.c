extern void func_002591F0(int a0, int a1, int a2, int a3);

int func_0025DDB0(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        func_002591F0(0x3F, a0, 0, 0);
        ret = 0;
    }
    return ret;
}
