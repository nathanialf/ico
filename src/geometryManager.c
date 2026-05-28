/* geometryManager.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00631B30[8];
extern unsigned int D_00631B38;
extern int D_00631B3C;
extern char D_00631B40[8];

unsigned int D_00275830[8] = { 0x00000007, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

/* String rodata migrated from geometryManager_data.c */
const char D_00553AD0[24] = "src/geometryManager.c";

/* String rodata migrated from geometryManager_data.c */
const char D_00553AE8[96] = "Fatal error! Geometry localize function called with GObj\n    that already have parent.\nExit...\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553B48[48] = "TOO MANY CHARACTERS EXIST ON THIS STAGE(>64)\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553B78[24] = "InitKeyInput2() in\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553B90[16] = "PadInit\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553BA0[24] = "InitKeyInput2() out\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553BB8[24] = "signal to main\n";

/* String rodata migrated from geometryManager_data.c */
const char D_00553BE0[48] = "Adjust Motion Height To Field. --------------\n";

/* String rodata migrated from geometryManager_data.c */
const float D_00553C10[4] = { 0.0f, 5.0f, 0.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C20[4] = { 0.0f, 0.0f, 5.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C30[4] = { 5.0f, 0.0f, 0.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C70[4] = { 1e+01f, 0.0f, 0.0f, 0.0f };

/* String rodata migrated from geometryManager_data.c */
const float D_00553C90[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

#include "include_asm.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00102E08);
extern void func_002438B8(int *self, int v, char *p);
extern void func_00243978(int *out, int *src);

void func_00102FA0(int *self, int *other, char *p)
{
    func_00105F00((int)self, (int)p);
    {
        char *sub = *(char **)((char *)other + 0x15C);
        char *a = *(char **)sub;
        if (a != 0) {
            char *inner_struct = *(char **)(a + 0x15C);
            int inner_field = *(int *)(inner_struct + 0xC);
            int idx = *(int *)(sub + 0x4);
            func_002438B8(self, inner_field + (idx << 6), p);
        }
    }
    *(int *)((char *)self + 0x4) = 0;
    func_00243978(self, self);
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103018);

/* Matched body inlined from src/cod/003110.c during TU coalesce. */
extern void func_00105F00(int a0, int a1);
void func_00103110(int a0, int a1)
{
    func_00105F00(a0, *(int *)(a1 + 0x15C) + 0x130);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_0010311C);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103120);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001031E0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001032A8);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103370);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001034B8);
extern void func_00105F20(void *dst, void *src);
extern void func_00105E70(char *dst, char *src);
void func_00103AD0(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = *(char **)(obj + 0x15C);
    func_00105F20(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    func_00105E70((char *)buf, (char *)buf);
    func_002438B8((int *)(*(char **)((char *)self + 0x15C) + 0x520), (int)buf,
                  *(char **)((char *)self + 0x15C) + 0x520);
    func_00243978((int *)(*(char **)((char *)self + 0x15C) + 0x520),
                  (int *)(*(char **)((char *)self + 0x15C) + 0x520));
    *(int *)(*(char **)((char *)self + 0x15C) + 0x52C) = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103B48);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103C48);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103D50);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103F00);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001040C0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104140);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001041C0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104240);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104360);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104478);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104508);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104590);

extern float D_00630904;
extern float D_00630908;

int func_00104638(float *vals, int *flags)
{
    float lo = D_00630904;
    int ret = 0;
    int i;
    for (i = 2; i >= 0; i--) {
        register float v REG("$f0") = *vals;
        if (v < lo) {
            *vals = lo;
            ret = 1;
            *flags = 0;
        } else {
            MEM_BARRIER();
            if (v > D_00630908) {
                *vals = D_00630908;
                ret = 1;
                *flags = 0;
            }
        }
        flags++;
        vals++;
    }
    return ret;
}
extern void func_00105E70(char *dst, char *src);
extern void func_002438E8(char *dst, char *src, int m);

void func_00104698(char *dst, char *src)
{
    char tmp[0x40];
    func_00105E70(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    func_00105F00((int)dst, (int)(tmp + 0x30));
}

void func_001046F0(char *dst, char *outer)
{
    char *src = *(char **)(outer + 0x15C);
    char tmp[0x40];
    func_00105E70(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    func_00105F00((int)dst, (int)(tmp + 0x30));
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104748);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104818);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001048C8);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104940);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001049C0);

/* Matched body inlined from src/cod/004A38.c during TU coalesce. */
extern int D_0065F940[];
int *func_00104A38(void) {
    return D_0065F940;
}

TRAILING_PAD_NOP();
