extern void func_00243B18(int *buf, int p, float v);
extern void func_00106AB8(int self, int *buf);

void func_0015F2D8(int *self)
{
    int buf[4];
    func_00243B18(buf, (int)((char *)self[0x164 / 4] + 0x4A0), -1.0f);
    func_00106AB8((int)self, buf);
}
