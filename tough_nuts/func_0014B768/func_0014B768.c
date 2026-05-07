extern void func_001D26C8(int a0);

void func_0014B768(int a0)
{
    int *s0 = *(int **)((char *)a0 + 0x164);
    int *p = (int *)s0[0x170 / 4];
    if (p != 0) {
        func_001D26C8((int)p);
        s0[0x174 / 4] = 0;
        s0[0x170 / 4] = 0;
    }
}
