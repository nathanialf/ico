extern int D_00631AE4;
extern char D_00565060[];
extern void func_0014B228(int *self, int x);
extern void func_00165B80(int *self, int a1, int a2);

void func_0015FB60(int *self) {
    int *p, *entry;
    int idx;
    unsigned int v;
    if (D_00631AE4 != 0) {
        func_0014B228(self, 0x1B);
        p = (int *)self[0x15C / 4];
        idx = p[0x4A0 / 4] * 0x190;
        entry = (int *)(D_00565060 + idx);
        v = entry[0x188 / 4];
        if (((v >> 1) & 1) != 0) {
            func_00165B80(self, D_00631AE4, 5);
        }
    }
}
