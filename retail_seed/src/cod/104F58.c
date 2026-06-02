extern void func_00104508(int *buf, int a);
extern float func_00204200(int *buf, int b);

float func_00204F58(int a0, int a1)
{
    int buf[4];
    if (a0 == 0) {
        return -1.0f;
    }
    func_00104508(buf, a0);
    return func_00204200(buf, a1);
}
