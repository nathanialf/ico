extern void func_00105F00(int p, int q);
extern char D_00275850[];

void func_001F0878(int *self)
{
    int *p;
    p = (int *)self[0x15C / 4];
    p[0x470 / 4] = -1;
    p = (int *)self[0x15C / 4];
    p[0x660 / 4] = 1;
    func_00105F00((int)((char *)((int *)self[0x15C / 4]) + 0x670), (int)D_00275850);
    p = (int *)self[0x15C / 4];
    p[0x550 / 4] = 1;
}
