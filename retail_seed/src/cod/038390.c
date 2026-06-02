extern void func_00136678(int self, int p, int sz);
extern int D_00280C60[];

int func_00138390(int *self)
{
    int idx = self[0x8 / 4];
    func_00136678((int)self, (int)((char *)D_00280C60 + idx * 0x18C), 0x18C);
    return self[0x10 / 4];
}
