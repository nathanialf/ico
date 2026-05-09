extern void func_00245318(int *self, int a1, int a2);

void func_002451D0(int *self, int flag)
{
    int *p;
    int tag;
    func_00245318(self, 2, 3);
    p = (int *)self[0];
    self[0] = (int)((char *)p + 4);
    self[3] = (int)p;
    tag = flag ? 0xD0000000 : 0x50000000;
    *p = tag;
}
