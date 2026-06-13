extern void func_00254800(int *a0, int a1);

void func_00254930(int *a0, int a1) {
    long long v = (long long)(a1 << 3) + *(long long *)(a0 + 6);
    int sum = a0[2] + (int)((v << 29) >> 32);
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = v;
    a0[3] = sum;
    if ((unsigned int)sum >= (unsigned int)a0[9]) {
        a0[3] = sum - a0[0xA];
    }
    func_00254800(a0, 0);
}
