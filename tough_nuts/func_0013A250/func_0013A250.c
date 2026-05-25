extern const char D_00557540[];
extern const char D_00557550[];
extern const char D_006320E8[];
extern int D_006A6990[];
extern void func_001A6E28(const char *fmt, ...);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);
extern int func_00100520(int *p);

void func_0013A250(int *self, int a1, int a2)
{
    int ret;
    self[0x4 / 4] = 0;
    self[0x8 / 4] = 0;
    self[0x10 / 4] = 0;
    self[0x1C / 4] = 0;
    self[0x0 / 4] = a1;
    self[0x18 / 4] = a2;
    self[0x24 / 4] = 1;
    self[0xC / 4] = a2;
    ret = func_00100520((int *)((char *) self + 0x14));
    self[0x2C / 4] = ret;
    if (ret < 0)
    {
        func_001AD768(D_00557540, 0x78);
        func_00263FF0(D_00557540, 0x78, D_006320E8);
    }
    {
        int idx = self[0x2C / 4];
        D_006A6990[idx] = (int) self;
        func_001A6E28(D_00557550, idx, self);
    }
}
