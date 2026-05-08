extern void func_0015D348(unsigned int a0, int a1);
extern void func_00203AA0(int a0);

void func_001539B8(volatile unsigned int a0)
{
    volatile int local;
    int *v1 = *(int **)(a0 + 0x164);
    int a1 = v1[0x678 / 4];
    func_0015D348(a0, a1 + 0x7E0);
    func_00203AA0(0);
}
