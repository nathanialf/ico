extern void func_00180F40(int *buf, int a1, int a2);
extern void func_00181960(int *buf);

void func_00181BC8(int a0)
{
    int buf[28];
    int *v0 = *(int **)((char *)a0 + 0x164);
    func_00180F40(buf, a0, v0[0x140 / 4]);
    func_00181960(buf);
}
