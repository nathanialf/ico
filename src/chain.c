/* chain.c -- typed sdata / lit4 definitions for this TU.
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


const char D_0055AA90[16] = "src/chain.c";

const char D_0055AAA0[16] = "nearestNode!=-1";

const char D_0055AAB0[16] = "collision!!!\n";

const char D_0055AAC0[32] = "chain_simulate_term_loop\n";

const char D_0055AAE0[32] = "chain_simulate_term_swingready\n";

const char D_0055AB00[32] = "chain_simulate_term_swingstart\n";

const float D_0055AB20[2] = { 4.172325e-08f, 1.65f };

const char D_0055AB28[32] = "chain_simulate_term_moveup\n";

const char D_0055AB58[32] = "chain_simulate_term_free\n";

const char D_0055AB88[32] = "chain_simulate_hangstart\n";

const char D_0055ABA8[24] = "chain_simulate_term\n";

const char D_0055ABC0[24] = "chain_simulate_stop\n";

const char D_0055ABD8[24] = "chain_simulate_free\n";

const char D_0055ABF0[16] = "time = %f\n";

const char D_0055AC00[16] = "rad  = %f\n";

const char D_0055AC10[16] = "max  = %f\n";

const char D_0055AC20[16] = "maxl = %f\n";

const char D_0055AC30[16] = "T    = %f\n";

const char D_0055AC40[16] = "d    = %f\n";

const char D_0055AC50[16] = "inc  = %d\n";

const char D_0055AC60[64] = "\272\277\244\316\304\271\244\265\244\254\303\273\244\253\244\271\244\256\244\336\244\271(\307\333\303\326\311\275\244\316Y-scale\244\307\273\330\304\352\244\267\244\336\244\271)";

const float D_0055ACA0[4] = { 0.0f, 0.0f, -25.0f, 1.0f };

const float D_0055ACB0[4] = { 0.0f, 0.0f, 25.0f, 1.0f };

const char D_0055ACC0[104] = "\033[33m\272\277\244\316\276\345\244\316\312\311\244\362\270\253\311\325\244\261\244\353\244\263\244\310\244\254\244\307\244\255\244\336\244\273\244\363\241\243\n\312\375\270\376\244\254\264\326\260\343\244\303\244\306\244\244\244\353\244\253\241\242\312\311\244\254\314\265\244\244\244\310\244\263\244\355\244\313\303\326\244\244\244\306\244\244\244\336\244\273\244\363\244\253?\033[m\n";

const char D_0055AD28[16] = "plumb = %d\n";

const char D_0055AD38[24] = "%f/%f, %d\n";

#include "matching.h"
/* Inlined data (Phase 3e) — migrated from chain_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* zero-filled buffers */
unsigned int D_0028B0D0[12] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000 };

/* numeric word tables */
unsigned char D_0028B100[64] = { 0 };

#include "include_asm.h"
#include "regpin.h"

extern int D_00632744;

void func_0018CFF0(void) {
    D_00632744 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018CFF8);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D100);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D3A0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D4F0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D640);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D708);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D7D0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D928);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DAC8);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DB90);
extern int D_00632CBC;
extern int D_00633DA0;
extern float D_00630F5C;
extern void func_001A6A30(int a, int b, int c, const char *d);
extern void func_0018D4F0(int a0);

void func_0018DD80(int a0)
{
    char *sub = *(char **)(a0 + 0x15C);
    int *inner = *(int **)(sub + 0x800);
    if (D_00632CBC & 1) {
        D_00633DA0 = D_00633DA0 + 0xA;
        func_001A6A30(0xA, D_00633DA0, 0x0FFFFFFF, D_0055AB88);
    }
    *(float *)((char *)inner + 0x44) = D_00630F5C;
    func_0018D4F0(a0);
}

extern int D_00632CBC;
extern int D_00633DA0;
extern void func_001A6A30(int a, int b, int c, const char *d);

void func_0018DDF0(int a0)
{
    if (D_00632CBC & 1) {
        D_00633DA0 = D_00633DA0 + 0xA;
        func_001A6A30(0xA, D_00633DA0, 0x0FFFFFFF, D_0055ABA8);
    }
    func_0018D4F0(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DE48);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DF00);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DFF8);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018E188);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018E5B0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018EB70);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018ECC8);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018F640);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018F798);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018F8E8);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018FA70);

extern float D_00630F84;

int func_00190298(int a0)
{
    int s0 = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    func_0018D100(a0);
    {
        register int v REG("$2") = 1;
        *(signed char *)(s0 + 0x60) = v;
        return v;
    }
}

void func_001902C8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(char *)(p + 0x60) = 0;
}

void func_001902D8(int *a0, float *a1, float *a2, float *a3)
{
    int *sub = (int *)((int *)a0[0x15C / 4])[0x800 / 4];
    *a1 = *(float *)((char *)sub + 0x30);
    *a2 = *(float *)((char *)sub + 0x34);
    if (*(float *)((char *)sub + 0x48) < *(float *)((char *)sub + 0x34)) {
        *a2 = *(float *)((char *)sub + 0x48);
    }
    *a3 = *(float *)((char *)sub + 0x40);
}

TRAILING_PAD_NOP();

void func_00190318(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(float *)(p + 0x44) = D_00630F84;
}
