extern int D_00631AE4;
extern void func_001E9588(int *p);
extern void func_00104508(int *buf, int *p);
extern float func_001C8D08(int x, int *buf, float t);

void func_001E9810(int *self)
{
    int buf[4];
    int *p15c, *q;
    int *base;
    float result;
    func_001E9588(self);
    base = (int *)D_00631AE4;
    p15c = (int *)self[0x57];
    q = (int *)p15c[0x200];
    func_00104508(buf, base);
    result = func_001C8D08(q[0], buf, 200.0f);
    if (result > 0.0f) {
        *(float *)((char *)((int *)base[0x57]) + 0x618) = result;
    }
}
