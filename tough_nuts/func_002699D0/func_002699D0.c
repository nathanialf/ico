extern int func_0026B058(int *self, int a1, int a2, int a3);

int func_002699D0(char *a0, int a1, int a2) {
    unsigned short f;
    int r = func_0026B058((int *)*(int *)(a0 + 0x54), *(short *)(a0 + 0xE), a1, a2);
    long long rl;
    f = *(unsigned short *)(a0 + 0xC);
    if (r == -1) { f &= 0xEFFF; }
    else { rl = r; *(int *)(a0 + 0x50) = (int)rl; f |= 0x1000; }
    *(short *)(a0 + 0xC) = f;
    return r;
}
