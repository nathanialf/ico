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


__attribute__((section(".rodata.0x0055AA90"))) const char D_0055AA90[16] = "src/chain.c";

__attribute__((section(".rodata.0x0055AAA0"))) const char D_0055AAA0[16] = "nearestNode!=-1";

/* String rodata migrated from chain_data.c */
__attribute__((section(".rodata.0x0055AAB0"))) const char D_0055AAB0[16] = "collision!!!\n";
__attribute__((section(".rodata.0x0055AAC0"))) const char D_0055AAC0[32] = "chain_simulate_term_loop\n";
__attribute__((section(".rodata.0x0055AAE0"))) const char D_0055AAE0[32] = "chain_simulate_term_swingready\n";
__attribute__((section(".rodata.0x0055AB00"))) const char D_0055AB00[32] = "chain_simulate_term_swingstart\n";
__attribute__((section(".rodata.0x0055AB28"))) const char D_0055AB28[32] = "chain_simulate_term_moveup\n";
__attribute__((section(".rodata.0x0055AB58"))) const char D_0055AB58[32] = "chain_simulate_term_free\n";
__attribute__((section(".rodata.0x0055AB88"))) const char D_0055AB88[32] = "chain_simulate_hangstart\n";
__attribute__((section(".rodata.0x0055ABA8"))) const char D_0055ABA8[24] = "chain_simulate_term\n";
__attribute__((section(".rodata.0x0055ABC0"))) const char D_0055ABC0[24] = "chain_simulate_stop\n";
__attribute__((section(".rodata.0x0055ABD8"))) const char D_0055ABD8[24] = "chain_simulate_free\n";
__attribute__((section(".rodata.0x0055ABF0"))) const char D_0055ABF0[16] = "time = %f\n";
__attribute__((section(".rodata.0x0055AC00"))) const char D_0055AC00[16] = "rad  = %f\n";
__attribute__((section(".rodata.0x0055AC10"))) const char D_0055AC10[16] = "max  = %f\n";
__attribute__((section(".rodata.0x0055AC20"))) const char D_0055AC20[16] = "maxl = %f\n";
__attribute__((section(".rodata.0x0055AC30"))) const char D_0055AC30[16] = "T    = %f\n";
__attribute__((section(".rodata.0x0055AC40"))) const char D_0055AC40[16] = "d    = %f\n";
__attribute__((section(".rodata.0x0055AC50"))) const char D_0055AC50[16] = "inc  = %d\n";
__attribute__((section(".rodata.0x0055AD28"))) const char D_0055AD28[16] = "plumb = %d\n";
__attribute__((section(".rodata.0x0055AD38"))) const char D_0055AD38[24] = "%f/%f, %d\n";

/* Float rodata migrated from chain_data.c */
__attribute__((section(".rodata.0x0055AB20"))) const float D_0055AB20[2] = { 4.172325e-08f, 1.65f };
__attribute__((section(".rodata.0x0055ACA0"))) const float D_0055ACA0[4] = { 0.0f, 0.0f, -25.0f, 1.0f };
__attribute__((section(".rodata.0x0055ACB0"))) const float D_0055ACB0[4] = { 0.0f, 0.0f, 25.0f, 1.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "鎖の長さが短かすぎます(配置表のY-scaleで指定します)" */
__attribute__((section(".rodata.0x0055AC60"))) const char D_0055AC60[64] = "\272\277\244\316\304\271\244\265\244\254\303\273\244\253\244\271\244\256\244\336\244\271(\307\333\303\326\311\275\244\316Y-scale\244\307\273\330\304\352\244\267\244\336\244\271)";
/* EUC-JP: "[33m鎖の上の壁を見付けることができません。
方向が間違っているか、壁が無いところに置いていませんか?[m
" */
__attribute__((section(".rodata.0x0055ACC0"))) const char D_0055ACC0[104] = "\033[33m\272\277\244\316\276\345\244\316\312\311\244\362\270\253\311\325\244\261\244\353\244\263\244\310\244\254\244\307\244\255\244\336\244\273\244\363\241\243\n\312\375\270\376\244\254\264\326\260\343\244\303\244\306\244\244\244\353\244\253\241\242\312\311\244\254\314\265\244\244\244\310\244\263\244\355\244\313\303\326\244\244\244\306\244\244\244\336\244\273\244\363\244\253?\033[m\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D100);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D3A0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D4F0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D640);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D708);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D7D0);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018D928);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DAC8);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DB90);
INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018DD80);

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
