extern void func_00109F28(int *self);

void func_001C2170(int *self)
{
    int *p;
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    func_00109F28(self);
    p[0x14 / 4] = 0;
    p[0x10 / 4] = 1;
    ((int *)self[0x15C / 4])[0x62C / 4] = 0;
}
