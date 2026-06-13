extern void func_0025EBD8(void *in, void *out);
extern int func_00260310(int a0, int a1, int a2, int a3);

int func_0025F748(int a0) {
    struct { int a, b, c, pad; long long d; } out;
    long long t = a0;
    long long d;
    int hi, a3;
    func_0025EBD8(&t, &out);
    d = out.d;
    hi = (int)((d << 2) >> 32);
    a3 = hi | 1;
    if ((d & 0x3FFFFFFF) == 0) a3 = hi;
    return func_00260310(out.a, out.b, out.c, a3);
}
