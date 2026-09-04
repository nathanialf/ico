extern void __unpack_d(void *in, void *out);
extern int __make_fp(int a0, int a1, int a2, int a3);

int dptofp(int a0) {
    struct { int a, b, c, pad; long long d; } out;
    long long t = a0;
    long long d;
    int hi, a3;
    __unpack_d(&t, &out);
    d = out.d;
    hi = (int)((d << 2) >> 32);
    a3 = hi | 1;
    if ((d & 0x3FFFFFFF) == 0) a3 = hi;
    return __make_fp(out.a, out.b, out.c, a3);
}
