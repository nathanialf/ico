extern void func_001A6E28(char *p, int a1);
extern char D_0055AEE8[];

void func_00193CE8(int *self)
{
    int *p;
    p = (int *)self[0x164 / 4];
    func_001A6E28(D_0055AEE8, self[0x8 / 4]);
    *(long long *)((char *)p + 0x18) = *(long long *)((char *)p + 0x18) | 0x400000000LL;
}
