typedef struct { float m[4]; } Vec4;
typedef struct { float m[16]; } Mtx44;
extern void func_00105F00(int a, int b);
extern void func_00102858(int *self);
extern void func_00105F20(int a, int b);
extern void func_00104508(int p, int *self);
extern void func_00102850(int p, int *self);
extern void func_0010E0B8(int dst, short v);
extern void func_0010E1F8(int dst, short v);
extern void func_0010DEC0(int dst, int a, int b);
extern void func_00118648(int a, int b, int c);
extern void func_001184B8(int a, int b, int c, float f);
extern void func_0010DA78(int a, int b, int c, float f);
extern void func_001185D0(int a, int b, int c);
extern float D_004BEE10[];
extern char D_004BEE20[];
extern float D_00631128;
void func_001BA090(int *self)
{
    int *sub = (int *)self[0x15C / 4];
    char *p = (char *)sub[0x800 / 4];
    Vec4 l0;
    Vec4 l10;
    Mtx44 l20;
    float f3;

    func_00105F00((int)((char *)sub + 0x1F0), (int)((char *)sub + 0xA0));
    func_00102858(self);
    func_00105F20((int)(p + 0x230), ((int *)self[0x15C / 4])[0xC / 4]);

    f3 = (float)*(int *)(p + 0x270) * 0.03125f;
    D_004BEE10[1] = (f3 < 0.5f)
                  ? (f3 + f3) * 5.0f + -10.0f
                  : ((1.0f - f3) + (1.0f - f3)) * 5.0f + -10.0f;
    D_004BEE10[1] = D_004BEE10[1] - *(float *)(p + 0x1C8) * 25.0f;
    D_004BEE10[2] = *(float *)(p + 0x1C8) * 50.0f;

    func_00104508((int)&l0, self);
    func_00102850((int)&l10, self);
    func_0010E0B8((int)&l10, (int)(*(float *)(p + 0x1C8) * 8192.0f));
    func_0010E0B8((int)&l10, (int)(*(float *)(p + 0x1C0) * 4096.0f));
    func_0010DEC0((int)&l20, (int)&l10, (int)&l0);
    func_00118648((int)&l0, (int)&l20, (int)D_004BEE10);
    func_0010E1F8((int)&l10, (int)(-*(float *)(p + 0x1C4) * 2048.0f));

    {
        char *q1d0 = p + 0x1D0;
        char *q1e0 = p + 0x1E0;
        char *q1f0 = p + 0x1F0;
        func_001184B8((int)q1e0, (int)&l0, (int)q1e0, 0.5f);
        func_0010DA78((int)q1d0, (int)&l10, (int)q1d0, D_00631128);
        func_0010DEC0((int)q1f0, (int)q1d0, (int)q1e0);
        func_001185D0(((int *)self[0x15C / 4])[0xC / 4], (int)q1f0, (int)D_004BEE20);
    }
}
