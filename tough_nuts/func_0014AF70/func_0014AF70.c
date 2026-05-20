/* act-parallel-control.c -- typed sdata / lit4 definitions for this TU.
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
 */

/* __FILE__ anchor — migrated out of the trailing 32 bytes of
 * src/act-game_data.c's D_00558190[72] packed blob. */
__attribute__((section(".rodata.0x005581B8"))) const char D_005581B8[32] = "src/act-parallel-control.c";

/* String + float rodata in apc's range (between apc and boyact
 * anchors). Migrated out of src/act-game.c and src/boyact.c. */
__attribute__((section(".rodata.0x005581D8"))) const char D_005581D8[16] = "orient null";
__attribute__((section(".rodata.0x005581E8"))) const float D_005581E8[2] = { -107374184.0f, 1.8499999f };
__attribute__((section(".rodata.0x005581F0"))) const char D_005581F0[16] = "boy after func\n";
__attribute__((section(".rodata.0x00558200"))) const char D_00558200[24] = "enter actBoyHand50\n";
__attribute__((section(".rodata.0x00558218"))) const char D_00558218[24] = "boy error flg get\n";
__attribute__((section(".rodata.0x00558230"))) const char D_00558230[24] = "enter motBoyHand50\n";
__attribute__((section(".rodata.0x00558248"))) const char D_00558248[24] = "enter actBoyHand100\n";
__attribute__((section(".rodata.0x00558260"))) const char D_00558260[16] = "boy error\n";
__attribute__((section(".rodata.0x00558270"))) const char D_00558270[24] = "enter motBoyHand100\n";
__attribute__((section(".rodata.0x00558288"))) const char D_00558288[16] = "%s sync error\n";
__attribute__((section(".rodata.0x00558298"))) const char D_00558298[24] = "enter actBoyHand200\n";
__attribute__((section(".rodata.0x005582B0"))) const char D_005582B0[24] = "enter motBoyHand200\n";

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

extern int func_001F40C8();   /* K&R-style: 3 cod stubs declared this with conflicting signatures (int, int*, void); kept un-prototyped to match all call shapes */
extern int func_001E69D8(int a0);
extern void func_001D26C8(int a0);
extern int func_001AE830(int *buf);
extern void func_0019CBB8(int a0, int a1, int a2, int *buf);
extern void func_00145638(int *self);
extern int D_006AA968[];  /* array decl (not int*): keeps gcc on lui+addiu, not gp_rel — D_006AA968 lives at 0x006AA968, far outside the GP window */
extern int D_002E4E00[];
extern int D_00631990;
extern char D_006124F8[];
extern float D_002924B0[];

/* Intra-TU forward decls so calls type-check before the definitions
 * appear later in the file (and so the func_0014BD88(self) call site
 * in func_0014B1D0 — original asm sets up $a0 with self — matches
 * even though func_0014BD88's body ignores its arg). */
extern void func_0014BD88(int *self);
extern void func_0014BC30(int *a, int b, int c);

extern int D_006AA4B0[];

unsigned int func_0014AF70(int target)
{
    int count = *(int *)((char *)D_006AA4B0 + 0x4B0);
    int *p;
    int i;
    if (count <= 0) return 0;
    p = D_006AA4B0;
    i = 0;
    do {
        if (*p == target) {
            return *(unsigned char *)((char *)p + 0x190);
        }
        i++;
        p++;
    } while (i < count);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014AFB8);

int func_0014B000(int a0)
{
    char *base;
    int idx;
    int rv;
    if (a0 == 0) goto done;
    base = D_006124F8;
    MATERIALIZE(base);
    idx = func_001F40C8(a0);
    base += idx * 0x24;
    rv = *(int *)(base + 0x1C);
    goto end;
done:
    rv = 0;
end:
    return rv;
}

int func_0014B048(int *a0)
{
    int *q;
    int ret = 0;
    q = (int *)((int *)a0[0x164 / 4])[0x140 / 4];
    if (q == 0 || func_001F40C8(q) == 0) {
        ret = 1;
    }
    return ret;
}

int func_0014B090(void) {
    return func_001F40C8() == 1;
}

/* func_0014B0B4 is a 4-byte nop pad absorbed into func_0014B0B8's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B0B8);

void func_0014B150(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(volatile int *)(sub + 0x9C) = 0;
    *(volatile int *)(sub + 0x98) = 0;
    KEEP_LIVE_MEM(sub);
    *(int *)(sub + 0xA0) = 0;
}

/* func_0014B164 is a 4-byte nop pad absorbed into func_0014B168's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B168);

void func_0014B1D0(int *self)
{
    int *q = (int *)self[0x59];
    int *p;
    func_0014BD88(self);
    func_00145638(self);
    p = (int *)self[0x59];
    func_0014BC30((int *)p[0x19E], q[0x24], 0);
    q[0x25] = q[0x24];
}

void func_0014B228(char *self, int bit) {
    char *sub = *(char **)(self + 0x164);
    *(int *)(sub + 0x90) |= (1 << bit);
}

int func_0014B248(char *self, int bit) {
    char *sub = *(char **)(self + 0x164);
    return (*(int *)(sub + 0x90) >> bit) & 1;
}

TRAILING_PAD_NOP();

void func_0014B260(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(volatile long long *)(sub + 0x60) = 0;
    *(volatile long long *)(sub + 0x58) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B270);

int func_0014B2F0(char *a0, int a1)
{
    char *p;
    long long val;
    int mask;
    register int ret REG("$2");
    p = *(char **)(a0 + 0x164);
    ret = 0;
    if (p == 0) goto end;
    ret = 1;
    val = *(long long *)(p + 0x58);
    mask = 1 << a1;
    if ((val & mask) == 0) ret = 0;
end:
    return ret;
}

void func_0014B318(void) {}

void func_0014B320(char *self, float val) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x678);
    *(float *)(p + 0x334) = val;
}

void func_0014B330(char *self, unsigned int x, float f) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    if (x >= *(unsigned int *)(p + 0x54)) {
        *(unsigned int *)(p + 0x54) = x;
        DEFEAT_TCO();
        *(float *)(p + 0x58) = f;
    }
}

float func_0014B358(int idx)
{
    return D_002924B0[idx];
}

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B370);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B430);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B4C8);

void func_0014B580(int a0)
{
    int rc = func_001E69D8(1);
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x1B8) = rc;
}

/* func_0014B5B4 is a 4-byte nop pad absorbed into func_0014B5B8's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B5B8);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B660);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B708);

void func_0014B768(int a0)
{
    int *s0 = *((int **)(((char *)a0) + 0x164));
    int *p = (int *)s0[0x170 / 4];
    if (p != 0) {
        func_001D26C8((int)p);
        s0[0x174 / 4] = (s0[0x170 / 4] = 0);
    }
}

/* func_0014B7A4 is a 4-byte nop pad absorbed into func_0014B7A8's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B7A8);
extern int D_006325B4;

int func_0014B800(char *self)
{
    char *sub = *(char **)(self + 0x164);
    if (*(int *)(sub + 0x30) == 0x35) goto ret1;
    {
        char *other = *(char **)(sub + 0x678);
        if (*(int *)(other + 0x394) == 0) goto ret0;
        if (D_006325B4 == 0) goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}
/* func_0014B83C is a 4-byte nop pad absorbed into func_0014B840's matching .s. */

int func_0014B840(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x30) == 0x6B;
}

int func_0014B858(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x30) == 0x64;
}

/* func_0014B86C is a 4-byte nop pad absorbed into func_0014B870's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B870);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B970);

void func_0014BB00(int a0)
{
    int v = *(int *)(*(int *)(a0 + 0x164) + 0x670);
    *(float *)(v + 0x58) = 1.0f;
    *(int *)(v + 0x54) = 0;
}

/* func_0014BB1C is a 4-byte nop pad absorbed into func_0014BB20's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014BB20);

void func_0014BBF0(int a0)
{
    int buf[4];
    int v0 = func_001AE830(buf);
    func_0019CBB8(a0, D_00631990, v0, buf);
}

/* func_0014BC2C is a 4-byte nop pad absorbed into func_0014BC30's .s. */
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014BC30);

void func_0014BD88(int *unused)
{
    int *dst = D_006AA968;
    char *src = (char *)D_002E4E00;
    int i = 0x46;
    (void)unused;
    do {
        *dst = *(int *)src;
        i--;
        src += 0x94;
        dst++;
    } while (i >= 0);
}

int *func_0014BDC8(void) {
    return D_006AA968;
}

int func_0014BDD8(int a0, int a1)
{
    int v = a0 ? 9 : 1;
    return a1 ? (v | 4) : v;
}

void func_0014BDF0(void) {}

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014BDF8);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014CEE8);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014D6B0);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014D868);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014E300);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014E488);
