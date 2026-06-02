extern void func_00263520(void *a0, void *a1);
extern int func_00263410(void *a0);

int func_00263F48(float f12)
{
    int o[4];
    float in[4];
    in[0] = f12;
    func_00263520(in, o);
    o[1] = (o[1] == 0);
    return func_00263410(o);
}
