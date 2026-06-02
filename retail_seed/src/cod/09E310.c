extern int func_002407C0(int *a, int *b);

int func_0019E310(int a0_unused, int *a1, char *a2) {
    long long buf[4];
    func_002407C0((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}
