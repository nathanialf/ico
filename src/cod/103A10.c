extern int func_0013FF88(int *self, int a, int b);

int func_00203A10(int *self, int a1, int a2)
{
    int *p = (int *)self[0x164 / 4];
    if (p[0x12C / 4] != 0)
        goto ret0;
    p[0x12C / 4] = (int)self;
    p[0x130 / 4] = a2;
    func_0013FF88(self, a2, a1);
    return 1;
ret0:
    return 0;
}
