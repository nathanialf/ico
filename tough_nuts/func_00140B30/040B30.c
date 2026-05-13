extern int func_00140A20(int *p, int idx2, int val);

void func_00140B30(int *self, int idx, int val)
{
    int *p = (int *)self[0xB];
    int idx2 = idx * 2;
    ((short *)((char *)p + 0x40))[idx2 + 1] = val;
    ((short *)((char *)p + 0x3C))[idx2] = val;
    func_00140A20(p, idx2, val);
}
