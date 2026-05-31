/* act-game.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_00630AF8;
extern float D_00630AFC;
extern float D_00630B00;
extern float D_00630B04;
extern float D_00630B08;
extern float D_00630B0C;
extern float D_00630B10;
extern float D_00630B14;
extern float D_00630B18;
extern float D_00630B1C;
extern float D_00630B20;
extern float D_00630B24;
extern float D_00630B28;
extern unsigned int D_0063226C;
extern int D_00632270;
extern const char D_00632280[8];
extern const char D_00632288[8];

unsigned char D_00281B50[64] = { 0 };
float D_002924D4 = 25.0f;
float D_002924D8[26] = {
    60.0f,   50.0f,  5.0f,  90.0f,  90.0f,   2.0f,
     1.5f,  100.0f,  5.0f, 100.0f, 200.0f, 400.0f,
     0.1f, 0.01f, 0.09f, 0.5f, 1.2f, 0.2f,
    400.0f, 150.0f, 150.0f, 3600.0f, 4200.0f,
     20.0f, 30.0f, 105.0f,
};
const char D_00557EE0[32] = "too many view check object";
const char D_00557F00[16] = "src/act-game.c";
const char D_00557F30[16] = "mode=[%d]\n";
const char D_005580C0[16] = "shoal mail\n";
const char D_005580D0[32] = "[%d] [%d] [%d] [%d] [%d]\n";
/* EUC-JP: "並列モーションが増えすぎました（大森）" */
const char D_00558190[40] = "\312\302\316\363\245\342\241\274\245\267\245\347\245\363\244\254\301\375\244\250\244\271\244\256\244\336\244\267\244\277\241\312\302\347\277\271\241\313";
const int D_00564F30[76] = {
    13, 0, 0,  6, 0, 0,  6, 0, 0,  6, 0, 0,
     0, 3, 0, 11, 0, 0,  0, 2, 0,  1, 5, 0,
     0, 1, 0,  0, 3, 0,  0,12, 0,  0, 3, 0,
     4, 7, 0,  0, 5, 0,  0, 9, 0,  0, 8, 0,
     0, 7, 0,  0, 7, 0,  0, 3, 0,  0, 3, 0,
     0, 3, 0,  0,10, 0,  5, 0, 0,  5, 0, 0,
     0, 0, 0, 0,
};
const unsigned int D_005CF2D0[28] = {
    0,          0,          0, 0xFFFFFFFF,
    0,          0x3F800000, 0, 2,
    0x3F800000, 0,          0, 2,
    0,          0x3F800000, 0, 3,
    0,          0x3F800000, 0, 3,
    0,          0x3F800000, 0, 3,
    0,          0x3F800000, 0, 3,
};
const float D_00630AD4    = -1.5707964f;
const float D_00630AD8[1] = { 1.5707964f };
const float D_00630ADC    = 12100.0f;
const float D_00630AE0[1] = { 160000.0f };
const float D_00630AE4    = 0.3f;
const float D_00630AE8[1] = { 0.2f };
const float D_00630AEC    = 22500.0f;
const float D_00630AF0[1] = { 3.14159274f };
const float D_00630AF4    = 25000000.0f;
const char D_00632258[4]    = "0";
float D_0063225C            = 3.4028235e38f;
const char D_00632260[8]    = "BOMB!!\n";
const char D_00632268[4]    = "!!\n";

/* Inlined data (Phase 3e) — migrated from act-game_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from act-game_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_005650C4 = 0x00000013;
unsigned int D_005650C8[24] = { 0xBF800000, 0x00000013, 0xBF800000, 0x00000013, 0xBF800000, 0x00000013, 0xBF800000, 0x00000013, 0x656A626F, 0x732F7463, 0x622F6664, 0x6D2F796F, 0x6F69746F, 0x61622F6E, 0x61747363, 0x2E31646E, 0x00626F6D, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

#include "include_asm.h"
#include "ico/types.h"
#include "regpin.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_00149D60);

/* Matched body inlined from src/cod/049E70.c during TU coalesce. */
extern int *D_00631AE4;
int func_00149E70(int *a0)
{
    int *inner;
    long long val;
    register int ret;
    if (a0 == 0) goto fail;
    if (a0 != D_00631AE4) goto fail;
    inner = (int *)a0[0x164 / 4];
    if (inner == 0) goto fail;
    val = *(long long *)((char *)inner + 0x20);
    ret = (int)((val << 8) >> 32) & 1;
    return ret;
fail:
    ret = 0;
    return ret;
}

/* Matched body inlined from src/cod/049EA8.c during TU coalesce. */
void func_00149EA8(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 1;
    ((int *)self[0x57])[0x153] = 1;
    ((int *)self[0x57])[0x152] = 1;
    ((int *)self[0x57])[0x1F] = 1;
}

/* Matched body inlined from src/cod/049ED0.c during TU coalesce. */
void func_00149ED0(int *a0)
{
    ((int *)GOBJ_SUB(a0))[0x544 / 4] = 0;
    ((int *)GOBJ_SUB(a0))[0x54C / 4] = 0;
    ((int *)GOBJ_SUB(a0))[0x548 / 4] = 0;
    ((int *)GOBJ_SUB(a0))[0x7C / 4] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_00149EF4);

/* Matched body inlined from src/cod/049EF8.c during TU coalesce. */
extern unsigned short D_00565060[];
int func_00149EF8(void *a0)
{
    void *p = *((void **) (((char *) a0) + 0x15C));
    int idx = *((int *) (((char *) p) + 0x4A0));
    unsigned short *new_var;
    new_var = D_00565060;
    return ((unsigned short *) (((char *) new_var) + (idx * 0x190)))[0x186 / 2] & 7;
}

typedef struct { char _0[0x188]; int _188; } _E190;

int func_00149F20(char *a, char *b)
{
    Sub15C *sub1 = ((GObj *)(a))->p_15C;
    Sub15C *sub2 = ((GObj *)(b))->p_15C;
    int idx1 = sub1->f_4A0;
    int idx2 = sub2->f_4A0;
    _E190 *e1 = (_E190 *)((char *)D_00565060 + idx1 * 0x190);
    _E190 *e2 = (_E190 *)((char *)D_00565060 + idx2 * 0x190);
    int b1 = ((unsigned int)e1->_188 >> 15) & 1;
    int b2 = ((unsigned int)e2->_188 >> 15) & 1;


    return b1 & b2;
}
extern int D_00561928[][10];
extern void func_00144938(int idx, char *tmp_a, char *tmp_b);
extern void func_001AE4C8(char *self, char *other, int v, char *tmp_a, char *tmp_b);

void func_00149F70(char *self, char *other, int idx)
{
    char tmp_a[0x10];
    char tmp_b[0x10];
    func_00144938(idx, tmp_a, tmp_b);
    func_001AE4C8(self, other, D_00561928[idx][9], tmp_a, tmp_b);
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_00149FF0);
int func_0014A0A8(char *self)
{
    char *sub = *(char **)(self + 0x164);
    if (*(float *)(sub + 0x1D0) <= 20.0f) {
        return 1;
    }
    return 0;
}

/* Matched body inlined from src/cod/04A0D8.c during TU coalesce. */
extern void *D_00631AE8;
long func_0014A0D8(void)
{
    void *a = D_00631AE8;
    if (a == 0) {
        return 0;
    }
    {
        unsigned long *b = *(unsigned long **)((char *)a + 0x164);
        return (b[3] >> 36) & 1;
    }
}

extern int func_00109F10(void *a0, void *a1);

/* The output cell is one the engine reads back as an int elsewhere, so each
 * write may-aliases the int mesh-pointer chain and the dev's build re-reads the
 * chain per component. Storing through the int/float union spells that alias out
 * in the type system (still a single swc1) instead of a per-file
 * -fno-strict-aliasing override. */
typedef union { int i; float f; } IntFloat;

void func_0014A100(float *dst, char *obj, void *a2)
{
    int idx = func_00109F10(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A178);

/* Matched body inlined from src/cod/04A2B0.c during TU coalesce. */
extern int D_006AA4B0[];
void func_0014A2B0(void) {
    int *p = D_006AA4B0;
    *(int *)((char *)p + 0x4B0) = 0;
    *(int *)((char *)p + 0x4B4) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A2C4);

/* Matched body inlined from src/cod/04A2C8.c during TU coalesce. */
void func_0014A2C8(char *a0)
{
    long long mask1 = ~((long long)0x800 << 32);
    long long mask2 = ~((long long)0x1000 << 32);
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    *p = *p & mask1 & mask2;
}

/* Matched body inlined from src/cod/04A308.c during TU coalesce. */
void func_0014A308(char *a0)
{
    long long *p = (long long *)(*(int *)(a0 + 0x164) + 0x18);
    long long v1 = (long long)0x8000 << 28;
    long long v2 = (long long)0x8000 << 29;
    *p = *p | v1 | v2;
}

extern void func_00149D60(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void func_0014A330(void)
{
    char *s = *(char **)((char *)D_00631AE8 + 0x164);
    func_00149D60(D_00631AE8, 0, 4, 6, D_00631AE4, 0, 0);
    func_00149D60(D_00631AE4, 1, 4, 5, D_00631AE8, 0, 0);
    *(long long *)(s + 0x18) |= (long long)0x8000 << 21;
}
void func_0014A3A8(void)
{
    char *s = *(char **)((char *)D_00631AE8 + 0x164);
    func_00149D60(D_00631AE8, 0, 4, 0, 0, 0, 0);
    func_00149D60(D_00631AE4, 1, 4, 0, 0, 0, 0);
    *(long long *)(s + 0x18) &= ~((long long)0x8000 << 21);
}

/* Matched body inlined from src/cod/04A430.c during TU coalesce. */
void func_0014A430(float *a0, float *a1)
{
    float *q = (float *)D_00631AE4[0x59];
    a0[0] = q[0x4F0/4];
    a0[1] = q[0x4F4/4];
    a0[2] = q[0x4F8/4];
    a1[0] = q[0x4B0/4];
    a1[1] = q[0x4B4/4];
    a1[2] = q[0x4B8/4];
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A46C);
int func_0014A470(void)
{
    int *player = D_00631AE4;
    unsigned int state = *(int *)(*(char **)((char *)player + 0x164) + 0x30);
    void *o;
    unsigned long *b;
    unsigned long bit;
    int rv;
    if (state == 0) {
        goto ret0;
    }
    if (state < 4) {
        goto lt4;
    }
    if (state >= 0x4D) {
        goto ret0;
    }
    if (state < 0x4B) {
        rv = 0;
        goto end;
    }
    return 1;
lt4:
    o = D_00631AE8;
    if (o != 0) {
        goto bittest;
    }
    bit = 0;
    goto merge;
bittest:
    b = *(unsigned long **)((char *)o + 0x164);
    bit = (b[3] >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
end:
    return rv;
}
int func_0014A4E0(void)
{
    void *g = D_00631AE8;
    char *a = *(char **)((char *)g + 0x164);
    unsigned int type = *(int *)(a + 0x30);
    unsigned long bit;
    int rv;
    if (type == 0x45) {
        return 1;
    }
    if (type >= 0x46) {
        goto upper;
    }
    if (type >= 4) {
        goto ret0;
    }
    if (type == 0) {
        goto ret0;
    }
    if (g != 0) {
        goto bittest;
    }
    bit = 0;
    goto merge;
upper:
    if (type >= 0x4F) {
        goto ret0;
    }
    if (type < 0x4D) {
        goto ret0;
    }
    return 1;
bittest:
    bit = (*(unsigned long *)(a + 0x18) >> 36) & 1;
merge:
    if (bit & 0xFF) {
        return 1;
    }
ret0:
    rv = 0;
    return rv;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A560);

/* Matched body inlined from src/cod/04A5C0.c during TU coalesce. */
void func_0014A5C0(float *a0, float *a1)
{
    float *q = (float *)D_00631AE4[0x59];
    a0[0] = q[0x500/4];
    a0[1] = q[0x504/4];
    a0[2] = q[0x508/4];
    a1[0] = q[0x510/4];
    a1[1] = q[0x514/4];
    a1[2] = q[0x518/4];
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A5FC);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A600);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A6B8);

/* Matched body inlined from src/cod/04A700.c during TU coalesce. */
extern int func_0014B090(void);
extern int func_001F4228(int *self);
int func_0014A700(int *self)
{
    unsigned long new_var;
    int ret = 0;
    new_var = func_0014B090();
    if (new_var != 0)
    {
        ret = func_001F4228(self);
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A748);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A850);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014A980);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014AA28);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014AB30);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014AC78);
INCLUDE_ASM("asm/nonmatchings/src/act-game", func_0014ADF8);

/* Single-float rodata migrated from act-game_data.c */
