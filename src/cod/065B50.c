extern int D_00632390;

void func_00165B50(int *self, int a1, int *a2)
{
    int *p;
    int q;
    p = (int *)((int *)self[0x164 / 4])[0x670 / 4];
    p[0x200 / 4] = a1;
    if (a2 != 0) {
        q = *a2;
    } else {
        q = D_00632390;
    }
    p = (int *)((int *)self[0x164 / 4])[0x670 / 4];
    p[0x20C / 4] = q;
}
