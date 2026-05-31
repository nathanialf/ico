extern void func_00243AE8(int *buf, int a, int b);
extern float func_00243950(int *buf, int *buf2);
extern void func_00105FE0(float arg);

void func_00194400(int a, int b)
{
    int buf[4];
    func_00243AE8(buf, a, b);
    buf[1] = 0;
    func_00105FE0(func_00243950(buf, buf));
}
