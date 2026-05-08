extern int *func_0014A6B8(int a0);

int func_0017E620(int a0, int b) {
    int *p = func_0014A6B8(a0);
    if (p == 0) return 0;
    return p[0x8/4] == b;
}
