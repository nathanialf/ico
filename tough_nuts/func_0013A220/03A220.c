extern int func_00100540(int a0, int *a1);

void func_0013A220(int *a0)
{
    int *a1 = (int *)a0[0x10 / 4];
    int v0;
    int new_a0;
    if (a1 == 0) {
        return;
    }
    v0 = a1[0x44 / 4];
    new_a0 = a0[0x2C / 4];
    a0[0x10 / 4] = v0;
    __asm__ __volatile__("sw $0, 0x44(%0)" : : "r"(a1));
    return func_00100540(new_a0, a1);
}
