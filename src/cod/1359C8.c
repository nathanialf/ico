extern long long D_0061C300[];
extern int D_00631AE8;
extern void func_0017DF38(int a0, int a1, void *a2, int a3, float a4);

void func_002359C8(int a0) {
    int buf[8];
    long long c = D_0061C300[0];
    long long d = D_0061C300[1];
    buf[0] = a0;
    *(long long *)((char *)buf + 0x10) = c;
    *(long long *)((char *)buf + 0x18) = d;
    func_0017DF38(D_00631AE8, 0, (char *)buf + 0x10, 2, 100.0f);
}
