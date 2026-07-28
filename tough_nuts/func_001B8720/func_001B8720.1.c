/* a_p_1.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern const char D_00633210[8];
extern const char D_00633218[8];
extern const char D_00633220[8];
extern const char D_00633228[8];
extern const char D_00633230[8];
extern const char D_00633238[8];
extern const char D_00633240[8];
extern const char D_00633248[8];
extern const char D_00633250[8];
extern const char D_00633258[8];
extern const char D_00633260[8];
extern const char D_00633268[8];
extern const char D_00633270[8];
extern const char D_00633278[8];

const char D_00618550[16] = "src/a_p_1.c";

/* String rodata migrated from a_p_1_data.c */
const char D_00618560[32] = "--- WARNING!! ----\n";

/* Float rodata migrated from a_p_1_data.c */
const float D_00618580[4] = { 5e+01f, 0.0f, 0.0f, 1.0f };

/* lit4 migrated from a_p_1_data.c — 0x461C4000 == 10000.0f */
const float D_0063112C = 10000.0f;
const float D_00631130[1] = { 10000.0f };

/* data migrated from a_p_1_data.c (plain defs, no section attr —
 * mutable types >8 bytes default to .data under -G 8). */

extern int func_001B94B0(int *self);
extern void func_001BA7E8(int *self);
extern void func_001BA838(int *self);
extern void func_001BA880(int *self);
extern void func_001BA928(int *self);

typedef void (*FsmFn)(int *);
typedef struct { FsmFn a; FsmFn b; } FsmPair;

/* State vtable indexed by `a1 * 2`; reader at func_001BA668. */
FsmFn D_004BEE60[16] = {
    0, func_001BA7E8,
    0, (FsmFn)func_001B94B0,
    0, func_001BA838,
    func_001BA880, func_001BA928,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
};

/* Two 4x4 transforms (identity + translation rows). */
float D_004BEEA0[32] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, -20.0f, 30.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, -10.0f, 35.0f, 1.0f,
};

/* 4x4 uniform 2.0 scale. */
float D_004BEF20[16] = {
    2.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 2.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 2.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

/* Pointer table into the D_0063322X string-extern block above. */
char *D_004BEF60[8] = {
    (char *)D_00633240,
    (char *)D_00633238,
    (char *)D_00633230,
    (char *)D_00633228,
    (char *)D_00633220,
    (char *)D_00633218,
    0,
    0,
};

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "蜘蛛の抜けによる落下死リクエスト
" */
/* EUC-JP: "蜘蛛の抜けによる落下死リクエスト\n" */
const char D_00618590[40] = "\303\330\351\341\244\316\310\264\244\261\244\313\244\350\244\353\315\356\262\274\273\340\245\352\245\257\245\250\245\271\245\310\n";
/* EUC-JP: "既に死んでいるので起こしません
" */
/* EUC-JP: "既に死んでいるので起こしません\n" */
const char D_006185B8[32] = "\264\373\244\313\273\340\244\363\244\307\244\244\244\353\244\316\244\307\265\257\244\263\244\267\244\336\244\273\244\363\n";
/* EUC-JP: "強制死亡
" */
/* EUC-JP: "強制死亡\n" */
const char D_006185D8[16] = "\266\257\300\251\273\340\313\264\n";

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

void func_001B8CE0(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    func_00102850((int)&l70, self);
    func_0010D540((int)&m20, (int)&l70);
    func_00118648((int)&l0, (int)&m20, (int)D_004BEB00);
    f = func_00118320((int)&l0, arg2);
    r = func_0010EB60(f);
    if (r != 0) {
        func_00118350((int)&l10, arg2, (int)&l0);
        func_001182F0((int)&l10, (int)&l10);
        func_0010DCF8((int)&l60, (int)r, (int)&l10);
        func_0010DDB8((int)&l70, (int)&l60, (int)&l70);
        func_00102870((int)self, (int)&l70);
    }
}

void func_001B8DC8(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    func_00102850((int)&l70, self);
    func_0010D540((int)&m20, (int)&l70);
    func_00118648((int)&l0, (int)&m20, (int)D_00275890);
    f = func_00118320((int)&l0, arg2);
    r = func_0010EB60(f);
    if (r != 0) {
        func_00118350((int)&l10, arg2, (int)&l0);
        func_001182F0((int)&l10, (int)&l10);
        func_0010DCF8((int)&l60, (int)r, (int)&l10);
        func_0010DDB8((int)&l70, (int)&l60, (int)&l70);
        func_00102870((int)self, (int)&l70);
    }
}
extern void func_001183B8(int a, int b, int c);
extern void func_00118490(int a, int b, int c, float f);
extern void func_0010D838(int dst, int src);
extern int func_0010EC08(float a, float b);
extern char D_004BEB20[];
extern char D_004BEB60[];
extern char D_004BEC10[];
extern char D_004BEC30[];
extern float D_00631118;

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B8EB0);
extern void func_00104140(int dst, int *self);
extern void func_001183D0(int dst, int src, float f);
extern void func_00118388(int dst, int src, int v);
extern void func_00105E70(int dst, int src);
extern float func_00106000(int src);
extern void func_00104478(int *self, int src);
extern float D_0063111C;
extern float D_00631120;

int func_001B94B0(int *self)
{
    char *p = (char *)(((int *)self[0x15C / 4])[0x800 / 4]);
    int ret = func_001B8EB0(self, 1);
    Vec4 l0;
    Vec4 l10;
    Mtx44 l20;
    Mtx44 l60;
    Vec4 lA0;
    int i;
    int k;
    float r;

    if (ret != -1) {
        return ret;
    }

    func_00104508((int)&l0, self);
    func_00104140((int)&l20, self);
    func_00118648((int)&l10, (int)&l20, (int)(p + 0x1B0));

    i = 0;
    for (k = 0; k < 4; k++) {
        if (*(int *)(p + 0x10 + k * 0x50) == 0) {
            i++;
        }
    }
    func_001183D0((int)&l10, (int)&l10, ((float)i * 0.25f + 0.5f) * 0.5f);

    func_001183D0((int)((char *)self[0x15C / 4] + 0x130),
                  (int)((char *)self[0x15C / 4] + 0x130), D_0063111C);
    func_00118388((int)((char *)self[0x15C / 4] + 0x130),
                  (int)((char *)self[0x15C / 4] + 0x130), (int)&l10);

    func_00105E70((int)&l60, (int)&l20);
    func_00118648((int)&lA0, (int)&l60, (int)((char *)self[0x15C / 4] + 0x130));

    *(float *)(p + 0x1C4) = lA0.m[0];
    MEM_BARRIER();
    r = func_00106000((int)((char *)self[0x15C / 4] + 0x130));
    *(volatile float *)(p + 0x1C0) = r * D_00631120;

    func_00118388((int)&l0, (int)&l0,
                  (int)((char *)(*(volatile int *)((char *)self + 0x15C)) + 0x130));
    func_00104478(self, (int)&l0);
    *(int *)(p + 0x1C8) = 0;
    return 1;
}
extern void func_0019F530(void);
extern void func_001685E0(int dst);
extern void func_0019F4E8(int *self, int buf);
extern int func_00168A40(int dst);
extern int func_00168A60(int dst);
extern int func_0010A068(int *self, int sel);
extern int func_0010A048(int *self, int sel);
extern float func_0010D078(int x);
extern void func_0013FF88(int *self, int a, int b);
extern void func_00168538(int dst);
extern int func_00106390(int dst, int *self, int v, float f);
extern int D_00274EC0[];
extern char D_004BECD0[];
extern char D_004BECF0[];
extern char D_004BEBA0[];
extern char D_00275850[];

struct Frame12 {
    long long ll;
    int w;
} __attribute__((packed));

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B9638);

extern float func_00118510(int a, int b);
extern void func_001183A0(int a, int b, int c);
extern int func_00105570(float a, float b, float c);
extern void func_00105268(void);
extern void func_00104F20(void);
extern void func_00104FC0(int a);
extern void func_001D12A8(int self, int n);
extern void func_00181BF8(int self, int a1, int a2, int a3, float f);
extern char D_004BEB10[];
extern char D_004BED90[];
extern char D_004BEDD0[];
extern float D_00631124;

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B99B0);

extern void func_00105F00(int a, int b);
extern void func_00102858(int *self);
extern void func_00105F20(int a, int b);
extern void func_0010E0B8(int dst, short v);
extern void func_0010E1F8(int dst, short v);
extern void func_0010DEC0(int dst, int a, int b);
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
    D_004BEE10[1] = ((float)*(int *)(p + 0x270) * 0.03125f < 0.5f)
                  ? ((float)*(int *)(p + 0x270) * 0.03125f + f3) * 5.0f + -10.0f
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

extern void func_00104508(int p, int *self);
extern void func_00102850(int p, int *self);
extern void func_001CFA20(int x);
extern void func_001B7FE8(int a, int b, int c, int d, int e, int f, int g, int h);
extern int D_00623468[];

void func_001BA2E0(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    func_00104508((int)((char *)p + 0x1E0), self);
    func_00102850((int)((char *)p + 0x1D0), self);
    func_001CFA20(p[0x19C / 4]);
}

extern void func_001B99B0(int *self);
extern int func_00105278(void);
extern int func_001CF930(int a, int b, float f);
extern const float D_0063112C_a __asm__("D_0063112C");
extern const float D_00631130_a __asm__("D_00631130");
extern void func_00105038(int a);
extern void func_00104F48(int a);
extern void func_001A6E28(int a);

void func_001BA330(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int state = p[0x8 / 4];

    switch (state) {
    default:
        if (p[0x274 / 4] < 10) {
            p[0x274 / 4] = p[0x274 / 4] + 1;
            func_001BA2E0(self);
            state = p[0x8 / 4];
        }
        {
            char *vp = (char *)D_004BEE60;
            vp += state * 8;
            p[0x8 / 4] = ((int (*)(int *))((FsmPair *)vp)->b)(self);
        }
        {
            int *pp = (int *)((int *)self[0x15C / 4])[0x800 / 4];
            int t = pp[0x270 / 4] + 1;
            pp[0x270 / 4] = t;
            if (t >= 0x21) {
                pp[0x270 / 4] = 0;
            }
        }
        break;
    case 5:
        p[0x8 / 4] = 4;
        break;
    case 4:
        p[0x8 / 4] = 6;
        break;
    case 6:
        self[0x16C / 4] = 0;
        break;
    case 7:
        break;
    }

    func_001BA090(self);
    func_001B99B0(self);
    {
        int r = func_00105278();
        func_001185D0(r, ((int *)self[0x15C / 4])[0xC / 4], (int)D_004BEEA0);
    }
    {
        int r = func_00105278();
        func_001CF930(p[0x19C / 4], r, 1.0f);
    }
    if (p[0x4 / 4] != 0) {
        int r3 = func_00105278();
        func_00105F20(r3, ((int *)self[0x15C / 4])[0xC / 4]);
        func_00105038(0x4000);
        func_00104F48(0x4000);
        {
            int *sub = (int *)self[0x15C / 4];
            int r4 = func_00105278();
            func_001185D0(sub[0xC / 4], r4, (int)D_004BEF20);
        }
    }
    {
        int *sub = (int *)self[0x15C / 4];
        float diff = *(float *)((char *)sub + 0x54)
                   - *(float *)((char *)((int *)sub[0xC / 4]) + 0x34);
        if (diff < 0.0f) {
            diff = -diff;
            MEM_BARRIER();
            if (D_0063112C_a < diff) {
                goto hit;
            }
            return;
        }
        MEM_BARRIER();
        if (!(D_00631130_a < diff)) {
            return;
        }
    hit:
        *(int *)((char *)sub + 0x5F8) = 0x800;
        func_001A6E28((int)D_00618590);
    }
}

extern void func_0010ECD8(void);
extern void func_0010ECB8(int *self);
extern void func_0010ECA0(int x);
extern void func_001CF998(int x);

void func_001BA530(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    if (p[0x8 / 4] >= 5) {
        return;
    }
    if (p[0x278 / 4] == 0) {
        return;
    }
    func_0010ECD8();
    func_0010ECB8(self);
    if (p[0x4 / 4] == 0) {
        func_0010ECA0(p[0x194 / 4]);
        func_0010ECA0(p[0x198 / 4]);
    }
    func_001CF998(p[0x19C / 4]);
}

int func_001BA5C0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x0);
}

void func_001BA5D0(char *self, int val) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)(p + 0x278) = val;
}

extern void func_0010E158(int dst, int v);
extern void func_0010D878(int dst);
extern void func_00102870(int self, int src);
extern void func_001BA090(int *self);

int func_001BA5E0(int *self, int a1)
{
    int buf[4];
    short s = (short)a1;
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int x = p[0x8 / 4];
    if (x < 6) {
        if (x >= 2) {
            goto ret0;
        }
    }
    func_00102850((int)buf, self);
    func_0010E158((int)buf, s);
    func_0010D878((int)buf);
    func_00102870((int)self, (int)buf);
    func_001BA090(self);
    return 1;
ret0:
    return 0;
}

int func_001BA668(int *self, int a1)
{
    void (*fn)(int *);
    int *p;
    fn = (void (*)(int *))D_004BEE60[a1 * 2];
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    p[0x8 / 4] = a1;
    if (fn != 0) {
        fn(self);
    }
    return 1;
}

int func_001BA6B0(int *self)
{
    int x = ((int *)((int *)self[0x15C/4])[0x800/4])[0x8/4];
    if (x < 6) {
        if (x >= 2) {
            return 0;
        }
    }
    ((int (*)())func_001BA668)();
    return 1;
}

int func_001BA6F0(int *self, int a1, int a2)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int x = p[0x8 / 4];
    int ok;
    if (x < 6) {
        if (x >= 2) {
            ok = 0;
            goto check;
        }
    }
    ((void (*)(int *))func_001BA668)(self);
    ok = 1;
check:
    if (ok == 0) {
        goto ret0;
    }
    {
        char *sub = (char *)self[0x15C / 4];
        char *q = *(char **)(sub + 0x800);
        func_00118648((int)(sub + 0x130), (int)(q + 0x230), a2);
    }
    return 1;
ret0:
    return 0;
}

void func_001BA770(int *self)
{
  int *entry = (int *) (((char *) D_00623468) - (-(self[0x30 / 4] * 32)));
  func_001B7FE8(0x3D, entry[0xC / 4], -1, 0, (int) self, -1, 7, 1);
  asm __volatile__("" : : : "memory");
}
