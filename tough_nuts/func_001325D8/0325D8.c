extern int D_0027E4C0[];
extern void func_0013A5B8(int *a0, int *a1, int a2);

void func_001325D8(int *a0, int a1)
{
    a0[1] = 1;
    *(long long *)a0 = (*(long long *)a0 & ~1LL) | (a1 & 1);
    func_0013A5B8(D_0027E4C0, a0, 0);
}
