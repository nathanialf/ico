struct Vec0013B7E0
{
    float x;
    int z0;
    float y;
    int z1;
} __attribute__((aligned(8)));

void func_0013B7E0(int *a0, float *a1)
void func_0013B7E0(int *a0, float *a1)
{
{
    struct Vec0013B7E0 v;
    struct Vec0013B7E0 v;
    struct Vec0013B7E0 t;
    struct Vec0013B7E0 t;
    unsigned char buf[0x40];
    unsigned char buf[0x40];
    t.x = a1[0xC / 4];
    t.x = a1[0xC / 4];
    t.z0 = 0;
    t.z0 = 0;
    t.y = -a1[0x10 / 4];
    t.y = -a1[0x10 / 4];
    t.z1 = 0;
    t.z1 = 0;
    v = t;
    v = t;
    func_002439B0(buf, (unsigned char *) D_00631970 + 0x80);
    func_002439B0(buf, (unsigned char *) D_00631970 + 0x80);
    func_002438B8(a0, buf, &v);
    func_002438B8(a0, buf, &v);
}
}
