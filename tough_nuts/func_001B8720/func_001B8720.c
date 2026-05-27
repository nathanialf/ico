typedef struct { float m[16]; } Mtx44;
extern int *func_0013A0F8(int tag, int size, int name, int id);
extern void func_00264D60(void);
extern void func_00118678(int dst);
extern int *func_0019F310(int n, int *arg1);
extern void func_00139598(int x);
extern int func_00109F10(int *self, int v);
extern void func_001AD748(int a, int b, int c);
extern void func_00263FF0(int a, int b, int c);
extern int func_001CEF90(int a, int b, int c);
extern void func_00105F00(int a, int b);
extern void func_00102850(int p, int *self);
extern void func_00104508(int p, int *self);
extern void func_00104140(int dst, int *self);
extern void func_00118648(int a, int b, int c);
extern int D_00632010;
extern int D_00632024;
extern char D_004BEC00[];
extern int D_00623468[];
extern char D_004BEA80[];
extern char D_00282660[];
extern char D_004BEBA0[];
extern int D_004BEAD0[];
extern const char D_00618550[16];
extern const char D_00618560[32];
extern const char D_00633210[8];
struct Tmpl50 { long long b[10]; };
struct Tmpl12 { long long ll; int w; } __attribute__((packed, aligned(4)));
struct E32 { char _0[0x18]; float f18; char _1c[4]; };
int *func_001B8720(int *self, int *arg1)
{
int *func_001B8720(int *self, int *arg1)
{
    Mtx44 mtx;
    int *this = func_0013A0F8(D_00632010, 0x280, (int)D_00618550, 0xE4);
    int i;

    this[0x4 / 4] = 1;
    this[0x16C / 4] = 0;
    this[0x168 / 4] = 0;
    this[0x1C4 / 4] = 0;
    this[0x1C8 / 4] = 0;
    this[0x1C0 / 4] = 0;
    ((int *)self[0x15C / 4])[0x800 / 4] = (int)this;
    this[0x0 / 4] = arg1[0x30 / 4];
    this[0x8 / 4] = 7;
    func_00264D60();
    *(float *)(D_004BEC00 + 0x8) =
        ((struct E32 *)D_00623468)[this[0x0 / 4]].f18;
    this[0x278 / 4] = 1;
    this[0x274 / 4] = 0;
    this[0x270 / 4] = (int)self[0x15C / 4] & 0x1F;
    func_00105F00((int)((char *)this + 0x1B0), (int)D_004BEC00);
    func_00118678((int)((char *)this + 0x1F0));
    func_00118678((int)((char *)this + 0x230));
    func_00102850((int)((char *)this + 0x1D0), self);
    func_00104508((int)((char *)this + 0x1E0), self);

    for (i = 0; i < 4; i++) {
        *(struct Tmpl50 *)((char *)this + 0x10 + i * 0x50) =
            *(struct Tmpl50 *)D_004BEA80;
    }
    {
        char *dst = (char *)this + 0x150;
        for (i = 1; i >= 0; i--) {
            *(struct Tmpl12 *)dst = *(struct Tmpl12 *)D_00282660;
            dst += 0xC;
        }
    }
    {
        char *node = (char *)((int *)self[0x15C / 4])[0x800 / 4] + 0x20;
        char *bb = D_004BEBA0;
        func_00104140((int)&mtx, self);
        for (i = 3; i >= 0; i--) {
            func_00118648((int)node, (int)&mtx, (int)bb);
            func_00118648((int)(node + 0x10), (int)&mtx, (int)bb);
            bb += 0x10;
            node += 0x50;
        }
    }

    if (this[0x4 / 4] == 0) {
        int *o;
        char *base;
        o = func_0019F310(5, arg1);
        this[0x194 / 4] = (int)o;
        if (o[0xC / 4] != 0) {
            func_00139598(o[0xC / 4] & 0xFFFFFFF);
        }
        o = (int *)this[0x194 / 4];
        if (o[0x10 / 4] != 0) {
            func_00139598(o[0x10 / 4] & 0xFFFFFFF);
        }
        o = (int *)this[0x194 / 4];
        o[0x10 / 4] = 0;
        o[0xC / 4] = 0;
        ((int *)this[0x194 / 4])[0xC / 4] =
            (int)func_0013A0F8(D_00632024, 0x100, (int)D_00618550, 0x105);
        o = (int *)this[0x194 / 4];
        o[0x10 / 4] = (int)func_0013A0F8(D_00632024, 0x40, (int)D_00618550, 0x105);
        o[0x8 / 4] = 4;
        if (o[0x840 / 4] != 0) {
            func_00139598(o[0x840 / 4] & 0xFFFFFFF);
        }
        ((int *)this[0x194 / 4])[0x840 / 4] =
            (int)func_0013A0F8(D_00632024, 0x140, (int)D_00618550, 0x105);
        for (i = 3; i >= 0; i--) {
            base = (char *)((int *)this[0x194 / 4])[0x840 / 4] + i * 0x50;
            *(volatile long long *)(base + 0x38) &= -2;
            base = (char *)((int *)this[0x194 / 4])[0x840 / 4] + i * 0x50;
            *(volatile long long *)(base + 0x38) &= -3;
            base = (char *)((int *)this[0x194 / 4])[0x840 / 4] + i * 0x50;
            *(int *)(base + 0x40) = 0;
            *(int *)(base + 0x44) = 0;
            *(volatile long long *)(base + 0x38) &= -5;
            *(int *)(base + 0x48) = 0;
            *(float *)(base + 0x4C) = 1.0f;
            base = (char *)((int *)this[0x194 / 4])[0x840 / 4] + i * 0x50;
            *(float *)(base + 0x28) = 1.0f;
            *(int *)(base + 0x30) = 0;
            *(float *)(base + 0x34) = 1.0f;
            *(short *)(base + 0x3A) = 0;
            *(float *)(base + 0x20) = 1.0f;
            *(float *)(base + 0x24) = 1.0f;
        }
        *(short *)((char *)(int *)this[0x194 / 4] + 0x818) = 2;

        o = func_0019F310(6, arg1);
        this[0x198 / 4] = (int)o;
        if (o[0xC / 4] != 0) {
            func_00139598(o[0xC / 4] & 0xFFFFFFF);
        }
        o = (int *)this[0x198 / 4];
        if (o[0x10 / 4] != 0) {
            func_00139598(o[0x10 / 4] & 0xFFFFFFF);
        }
        o = (int *)this[0x198 / 4];
        o[0x10 / 4] = 0;
        o[0xC / 4] = 0;
        ((int *)this[0x198 / 4])[0xC / 4] =
            (int)func_0013A0F8(D_00632024, 0x100, (int)D_00618550, 0x108);
        o = (int *)this[0x198 / 4];
        o[0x10 / 4] = (int)func_0013A0F8(D_00632024, 0x40, (int)D_00618550, 0x108);
        o[0x8 / 4] = 4;
        if (o[0x840 / 4] != 0) {
            func_00139598(o[0x840 / 4] & 0xFFFFFFF);
        }
        ((int *)this[0x198 / 4])[0x840 / 4] =
            (int)func_0013A0F8(D_00632024, 0x140, (int)D_00618550, 0x108);
        for (i = 3; i >= 0; i--) {
            base = (char *)((int *)this[0x198 / 4])[0x840 / 4] + i * 0x50;
            *(volatile long long *)(base + 0x38) &= -2;
            base = (char *)((int *)this[0x198 / 4])[0x840 / 4] + i * 0x50;
            *(volatile long long *)(base + 0x38) &= -3;
            base = (char *)((int *)this[0x198 / 4])[0x840 / 4] + i * 0x50;
            *(int *)(base + 0x40) = 0;
            *(int *)(base + 0x44) = 0;
            *(volatile long long *)(base + 0x38) &= -5;
            *(int *)(base + 0x48) = 0;
            *(float *)(base + 0x4C) = 1.0f;
            base = (char *)((int *)this[0x198 / 4])[0x840 / 4] + i * 0x50;
            *(float *)(base + 0x28) = 1.0f;
            *(int *)(base + 0x30) = 0;
            *(float *)(base + 0x34) = 1.0f;
            *(short *)(base + 0x3A) = 0;
            *(float *)(base + 0x20) = 1.0f;
            *(float *)(base + 0x24) = 1.0f;
        }
        *(short *)((char *)(int *)this[0x198 / 4] + 0x818) = 2;
    } else {
        int neg1 = -1;
        int *q = D_004BEAD0;
        int *out = (int *)((char *)this + 0x170);
        KEEP_LIVE(neg1);
        for (i = 8; i >= 0; i--) {
            int r = func_00109F10(self, q[0]);
            out[0] = r;
            if (r == neg1) {
                func_001AD748((int)D_00618550, 0x10D, (int)D_00618560);
                func_00263FF0((int)D_00618550, 0x10D, (int)D_00633210);
            }
            out++;
            q++;
        }
        this[0x198 / 4] = 0;
        this[0x194 / 4] = 0;
    }

    this[0x19C / 4] = func_001CEF90(0xA, 0, 0xA);
    return this;
}
