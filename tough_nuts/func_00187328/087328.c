extern void func_00243B18(int *buf, int *p, float t);
extern void func_001873A0(int *buf, int *p, int *q, int *r, float t1, float t2);

void func_00187328(int *self, int *a1, int *a2, int *a3, float t)
{
    int buf[4];
    func_00243B18(buf, self, -1.0f);
    func_001873A0(buf, a1, a2, a3, t, 0.0f);
}
