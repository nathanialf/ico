extern int func_0013EB50(int a0);
extern int D_00631AE4;
extern void func_001F40D8(int *a0);

void func_00199A08(void) {
    int *a;
    int *d;
    int *p;
    int *q;
    a = (int *)func_0013EB50(0x2E);
    d = (int *)D_00631AE4;
    p = (int *)d[0x164/4];
    q = (int *)p[0x140/4];
    if (a) {
        int *r = (int *)((int *)a[0x15C/4])[0x800/4];
        r[0x4/4] = r[0x4/4] + 1;
    }
    if (q) {
        func_001F40D8(q);
    }
}
