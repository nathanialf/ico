extern void func_00243B70(int *p, int q, float t);
extern void func_00243B18(int *p, int *q, float t);

void func_001999A8(int *self, int a1, float t)
{
    func_00243B70(self, a1, t);
    func_00243B18(self, self, t);
    func_00243B18(self + 0x10/4, self + 0x10/4, t);
    func_00243B18(self + 0x20/4, self + 0x20/4, t);
}
