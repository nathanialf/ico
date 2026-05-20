extern void func_00168AE0(int *self, int *p, int arg2, int arg3);
extern void func_001182F0(int *out, int *in);

void func_00107DD8(int *self, int *p, int *cfg)
{
    int *obj = (int *)cfg[0];
    int sh = cfg[1] << 6;
    int *p15c = (int *)obj[0x15C / 4];
    int v_c = p15c[0xC / 4];

    func_00168AE0(self, p, cfg[2], v_c + sh);
    p[1] = 0;
    func_001182F0(p, p);
}
