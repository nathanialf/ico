#include "include_asm.h"
#include "matching.h"

typedef struct { float m[4]; } Vec4;
typedef struct { float m[16]; } Mtx44;

extern void func_0010D540(int dst, int src);
extern float func_00118320(int dst, int v);
extern int *func_0010EB60(float f);
extern void func_00118350(int dst, int v, int src);
extern void func_001182F0(int dst, int src);
extern void func_0010DCF8(int dst, int p, int src);
extern void func_0010DDB8(int dst, int a, int b);
extern char D_004BEB00[];
extern char D_00275890[];

extern int *func_0013A0F8(int tag, int size, int name, int id);
extern int func_00264D60(void);
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

struct Tmpl50 { long long b[10]; };
struct Tmpl12 { long long ll; int w; } __attribute__((packed, aligned(4)));
struct E32 { char _0[0x18]; float f18; char _1c[4]; };
struct Bec { char _0[8]; float f8; };

/* Sub-object allocated for this->m194 / this->m198 (see func_0019F310). */
struct Sub {
    char _0[0x8];
    int f8;          /* 0x8  = 4 */
    int fC;          /* 0xC  child ptr */
    int f10;         /* 0x10 child ptr */
    char _14[0x804];
    short f818;      /* 0x818 = 2 */
    char _81a[0x26];
    int f840;        /* 0x840 entry-array ptr */
};
struct Obj {
    char _0[0x10];
    struct Tmpl50 t50[4];     /* 0x10 */
    struct Tmpl12 t12[2];     /* 0x150 */
    char _168[0x2C];
    struct Sub *m194;         /* 0x194 */
    struct Sub *m198;         /* 0x198 */
};
#define M194 (((struct Obj *)this)->m194)
#define M198 (((struct Obj *)this)->m198)

extern const char FN8550[] __asm__("D_00618550");
extern const char A33210[] __asm__("D_00633210");
extern const char D_00618560[32];

int *func_001B8720(int *self, int *arg1)
{
    Mtx44 mtx;
    int *this = func_0013A0F8(D_00632010, 0x280, (int)FN8550, 0xE4);
    int i;

    register int a30 REG("$3") = arg1[0x30 / 4];
    int sc = self[0x15C / 4];
    this[0x4 / 4] = 1;
    this[0x16C / 4] = 0;
    this[0x168 / 4] = 0;
    this[0x1C4 / 4] = 0;
    this[0x1C8 / 4] = 0;
    this[0x1C0 / 4] = 0;
    ((int *)sc)[0x800 / 4] = (int)this;
    this[0x0 / 4] = a30;
    this[0x8 / 4] = 7;
    {
        int r264 = func_00264D60();
        char *eb = (char *)D_00623468;
        float f18;
        int eidx = this[0x0 / 4] * 0x20;
        __asm__("addu %0, %0, %1" : "+r"(eb) : "r"(eidx));
        f18 = ((struct E32 *)eb)->f18;
        this[0x278 / 4] = 1;
        this[0x274 / 4] = 0;
        this[0x270 / 4] = r264 & 0x1F;
        ((struct Bec *)D_004BEC00)->f8 = f18;
    }
    func_00105F00((int)((char *)this + 0x1B0), (int)D_004BEC00);
    func_00118678((int)((char *)this + 0x1F0));
    func_00118678((int)((char *)this + 0x230));
    func_00102850((int)((char *)this + 0x1D0), self);
    func_00104508((int)((char *)this + 0x1E0), self);

    for (i = 0; i < 4; i++) {
        ((struct Obj *)this)->t50[i] = *(struct Tmpl50 *)D_004BEA80;
    }
    {
        register struct Tmpl12 *dst REG("$2");
        __asm__ __volatile__("addiu %0, %1, 0x150" : "=r"(dst) : "r"((char *)this));
        for (i = 1; i >= 0; i--) {
            *dst = *(struct Tmpl12 *)D_00282660;
            dst++;
        }
    }
    {
        register char *node REG("$16") = (char *)((int *)self[0x15C / 4])[0x800 / 4] + 0x20;
        char *bb;
        int k;
        {
            register char *bbt REG("$3") = D_004BEBA0;
            ANCHOR(bbt);
            bb = bbt;
        }
        func_00104140((int)&mtx, self);
        for (k = 3; k >= 0; k--) {
            func_00118648((int)node, (int)&mtx, (int)bb);
            func_00118648((int)(node + 0x10), (int)&mtx, (int)bb);
            bb += 0x10;
            node += 0x50;
        }
    }

    if (this[0x4 / 4] == 0) {
        struct Sub *o;
        register char *base REG("$4");
        int off;
        register int ek REG("$7");
        register struct Sub *mm REG("$3");
        o = (struct Sub *)func_0019F310(5, arg1);
        M194 = o;
        if (o->fC != 0) {
            func_00139598(o->fC & 0xFFFFFFF);
        }
        {
            register struct Sub *m REG("$6") = M194;
            if (m->f10 != 0) {
                func_00139598(m->f10 & 0xFFFFFFF);
            }
            m->f10 = 0;
            m->fC = 0;
        }
        M194->fC = (int)func_0013A0F8(D_00632024, 0x100, (int)FN8550, 0x105);
        M194->f10 = (int)func_0013A0F8(D_00632024, 0x40, (int)FN8550, 0x105);
        M194->f8 = 4;
        if (M194->f840 != 0) {
            func_00139598(M194->f840 & 0xFFFFFFF);
        }
        {
            int r = (int)func_0013A0F8(D_00632024, 0x140, (int)FN8550, 0x105);
            register struct Sub *m REG("$6") = M194;
            m->f840 = r;
        }
        off = 0; ek = 3;
        do {
            ek--;
            mm = M194; base = (char *)off + (int)mm->f840;
            *(volatile long long *)(base + 0x38) &= -2;
            MEM_BARRIER();
            mm = M194; base = (char *)off + (int)mm->f840;
            *(volatile long long *)(base + 0x38) &= -3;
            MEM_BARRIER();
            mm = M194; base = (char *)off + (int)mm->f840;
            *(int *)(base + 0x40) = 0;
            *(int *)(base + 0x44) = 0;
            { register long long v5 REG("$6"); v5 = *(volatile long long *)(base + 0x38); v5 &= -5; *(volatile long long *)(base + 0x38) = v5; }
            *(int *)(base + 0x48) = 0;
            *(float *)(base + 0x4C) = 1.0f;
            base = (char *)off + (int)M194->f840;
            *(float *)(base + 0x28) = 1.0f;
            *(int *)(base + 0x30) = 0;
            *(float *)(base + 0x34) = 1.0f;
            *(short *)(base + 0x3A) = 0;
            *(float *)(base + 0x24) = 1.0f;
            *(float *)(base + 0x20) = 1.0f;
            off += 0x50;
        } while (ek >= 0);
        M194->f818 = 2;

        o = (struct Sub *)func_0019F310(6, arg1);
        M198 = o;
        if (o->fC != 0) {
            func_00139598(o->fC & 0xFFFFFFF);
        }
        {
            register struct Sub *m REG("$6") = M198;
            if (m->f10 != 0) {
                func_00139598(m->f10 & 0xFFFFFFF);
            }
            m->f10 = 0;
            m->fC = 0;
        }
        M198->fC = (int)func_0013A0F8(D_00632024, 0x100, (int)FN8550, 0x108);
        M198->f10 = (int)func_0013A0F8(D_00632024, 0x40, (int)FN8550, 0x108);
        M198->f8 = 4;
        if (M198->f840 != 0) {
            func_00139598(M198->f840 & 0xFFFFFFF);
        }
        {
            int r = (int)func_0013A0F8(D_00632024, 0x140, (int)FN8550, 0x108);
            register struct Sub *m REG("$6") = M198;
            m->f840 = r;
        }
        off = 0; ek = 3;
        do {
            ek--;
            mm = M198; base = (char *)off + (int)mm->f840;
            *(volatile long long *)(base + 0x38) &= -2;
            MEM_BARRIER();
            mm = M198; base = (char *)off + (int)mm->f840;
            *(volatile long long *)(base + 0x38) &= -3;
            MEM_BARRIER();
            mm = M198; base = (char *)off + (int)mm->f840;
            *(int *)(base + 0x40) = 0;
            *(int *)(base + 0x44) = 0;
            { register long long v5 REG("$6"); v5 = *(volatile long long *)(base + 0x38); v5 &= -5; *(volatile long long *)(base + 0x38) = v5; }
            *(int *)(base + 0x48) = 0;
            *(float *)(base + 0x4C) = 1.0f;
            base = (char *)off + (int)M198->f840;
            *(float *)(base + 0x28) = 1.0f;
            *(int *)(base + 0x30) = 0;
            *(float *)(base + 0x34) = 1.0f;
            *(short *)(base + 0x3A) = 0;
            *(float *)(base + 0x24) = 1.0f;
            *(float *)(base + 0x20) = 1.0f;
            off += 0x50;
        } while (ek >= 0);
        M198->f818 = 2;
    } else {
        int neg1 = -1;
        int *q = D_004BEAD0;
        int *out = (int *)((char *)this + 0x170);
        for (i = 8; i >= 0; i--) {
            int r = func_00109F10(self, q[0]);
            out[0] = r;
            if (r == neg1) {
                func_001AD748((int)FN8550, 0x10D, (int)D_00618560);
                func_00263FF0((int)FN8550, 0x10D, (int)A33210);
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
