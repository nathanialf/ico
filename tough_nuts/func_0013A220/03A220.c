extern int func_00100540(int a0, int *a1);

void func_0013A220(int *a0)
{
    int *v1 = a0;
    int *a1;
    int v0;
    int new_a0;
    a1 = (int *)v1[0x10 / 4];
    if (((int *)v1[0x10 / 4]) == 0) {
        return;
    }
    v0 = a1[0x44 / 4];
    new_a0 = v1[0x2C / 4];
    v1[0x10 / 4] = v0;
    ((int *)v1[0x10 / 4])[0x44 / 4] = 0;
    return func_00100540(new_a0, a1);
}
