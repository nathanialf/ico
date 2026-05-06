void func_00176130(char *p) {
    int local;
    char *q;
    char *sub;
    *(volatile int *)&local = (int)p;
    q = (char *)*(volatile int *)&local;
    sub = *(char **)(q + 0x15C);
    *(int *)(sub + 0x634) = 0;
}
