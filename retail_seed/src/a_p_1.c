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

/* lit4 migrated from a_p_1_data.c â 0x461C4000 == 10000.0f */
const float D_0063112C = 10000.0f;
const float D_00631130[1] = { 10000.0f };

/* data migrated from a_p_1_data.c (plain defs, no section attr â
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

/* EUC-JP debug strings â re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "èèã®æãã«ããè½ä¸æ­»ãªã¯ã¨ã¹ã
" */
/* EUC-JP: "èèã®æãã«ããè½ä¸æ­»ãªã¯ã¨ã¹ã\n" */
const char D_00618590[40] = "\303\330\351\341\244\316\310\264\244\261\244\313\244\350\244\353\315\356\262\274\273\340\245\352\245\257\245\250\245\271\245\310\n";
/* EUC-JP: "æ¢ã«æ­»ãã§ããã®ã§èµ·ããã¾ãã
" */
/* EUC-JP: "æ¢ã«æ­»ãã§ããã®ã§èµ·ããã¾ãã\n" */
const char D_006185B8[32] = "\264\373\244\313\273\340\244\363\244\307\244\244\244\353\244\316\244\307\265\257\244\263\244\267\244\336\244\273\244\363\n";
/* EUC-JP: "å¼·å¶æ­»äº¡
" */
/* EUC-JP: "å¼·å¶æ­»äº¡\n" */
const char D_006185D8[16] = "\266\257\300\251\273\340\313\264\n";

#include "include_asm.h"
#include "ico/types.h"
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
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B8720);

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

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001B94B0);
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
    int *sub = (int *)((GObj *)(self))->p_15C;
    char *p = (char *)((Sub15C *)(sub))->p_800;
    Vec4 l0;
    Vec4 l10;
    Mtx44 l20;
    float f3;

    func_00105F00((int)((char *)sub + 0x1F0), (int)((char *)sub + 0xA0));
    func_00102858(self);
    func_00105F20((int)(p + 0x230), ((int *)((GObj *)(self))->p_15C)[0xC / 4]);

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
        func_001185D0(((int *)((GObj *)(self))->p_15C)[0xC / 4], (int)q1f0, (int)D_004BEE20);
    }
}

extern void func_00104508(int p, int *self);
extern void func_00102850(int p, int *self);
extern void func_001CFA20(int x);
extern void func_001B7FE8(int a, int b, int c, int d, int e, int f, int g, int h);
extern int D_00623468[];

void func_001BA2E0(int *self)
{
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    func_00104508((int)((char *)p + 0x1E0), self);
    func_00102850((int)((char *)p + 0x1D0), self);
    func_001CFA20(p->f_19C);
}

extern void func_001B99B0(int *self);
extern int func_00105278(void);
extern int func_001CF930(int a, int b, float f);
extern const float D_0063112C_a __asm__("D_0063112C");
extern const float D_00631130_a __asm__("D_00631130");
extern void func_00105038(int a);
extern void func_00104F48(int a);
extern void func_001A6E28(int a);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", func_001BA330);

extern void func_0010ECD8(void);
extern void func_0010ECB8(int *self);
extern void func_0010ECA0(int x);
extern void func_001CF998(int x);

void func_001BA530(int *self)
{
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    if (p->f_8 >= 5) {
        return;
    }
    if (p->f_278 == 0) {
        return;
    }
    func_0010ECD8();
    func_0010ECB8(self);
    if (p->f_4 == 0) {
        func_0010ECA0(p->f_194);
        func_0010ECA0(p->f_198);
    }
    func_001CF998(p->f_19C);
}

int func_001BA5C0(char *self) {
    Sub15C *sub = ((GObj *)(self))->p_15C;
    Obj800 *p = ((Sub15C *)(sub))->p_800;
    return p->f_0;
}

void func_001BA5D0(char *self, int val) {
    Sub15C *sub = ((GObj *)(self))->p_15C;
    Obj800 *p = ((Sub15C *)(sub))->p_800;
    p->f_278 = val;
}

extern void func_0010E158(int dst, int v);
extern void func_0010D878(int dst);
extern void func_00102870(int self, int src);
extern void func_001BA090(int *self);

int func_001BA5E0(int *self, int a1)
{
    int buf[4];
    short s = (short)a1;
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    int x = p->f_8;
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
    int x = ((int *)((int *)((GObj *)(self))->p_15C)[0x800/4])[0x8/4];
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
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    int x = p->f_8;
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
        Sub15C *sub = ((GObj *)(self))->p_15C;
        Obj800 *q = ((Sub15C *)(sub))->p_800;
        func_00118648((int)((char *)sub + 0x130), (int)((char *)q + 0x230), a2);
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


/* === BEGIN recovered struct shapes (tools/place_struct_shapes.py) === */
/* Field layouts mined from load/store access patterns; SPARSE
 * (only touched offsets, no padding). Unused typedefs — they add
 * no symbol and cannot affect codegen. Cast as ((S_<VMA> *)D_<VMA>).
 */

typedef struct {
    unsigned int     f_0;  /* 0x0  x3 */
    unsigned int     f_4;  /* 0x4  x2 */
} S_004BEE60;  /* stride 0x8, 5 accesses */

/* === END recovered struct shapes === */
