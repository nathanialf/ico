/* act-env.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x0063144C"))) float D_0063144C = 4900.0f;
__attribute__((section(".lit4.0x00631450"))) float D_00631450 = 1.57079637f;
__attribute__((section(".lit4.0x00631454"))) float D_00631454 = 355.0f;
__attribute__((section(".lit4.0x00631458"))) float D_00631458 = 10000.0f;
__attribute__((section(".lit4.0x0063145C"))) float D_0063145C = 22500.0f;
__attribute__((section(".lit4.0x00631460"))) float D_00631460 = 10000.0f;
__attribute__((section(".lit4.0x00631464"))) float D_00631464 = 40000.0f;
__attribute__((section(".lit4.0x00631468"))) float D_00631468 = 1.57079637f;
__attribute__((section(".lit4.0x0063146C"))) float D_0063146C = 4900.0f;
__attribute__((section(".lit4.0x00631470"))) float D_00631470 = 22500.0f;
__attribute__((section(".lit4.0x00631474"))) float D_00631474 = 12100.0f;
__attribute__((section(".lit4.0x00631478"))) float D_00631478 = 3.14159274f;
__attribute__((section(".lit4.0x0063147C"))) float D_0063147C = 10000.0f;
__attribute__((section(".lit4.0x00631480"))) float D_00631480 = 40000.0f;
__attribute__((section(".sdata.0x00631990"))) char D_00631990[16] = { 0 };
__attribute__((section(".sdata.0x006319A0"))) char D_006319A0[16] = { 0 };
__attribute__((section(".sdata.0x006319B0"))) char D_006319B0[16] = { 0 };
__attribute__((section(".sdata.0x00633840"))) const char D_00633840[8] = "0";
__attribute__((section(".sdata.0x00633848"))) const char D_00633848[8] = "water\n";
__attribute__((section(".sdata.0x00633850"))) unsigned int D_00633850 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00633854"))) unsigned int D_00633854 = 0xFF7FFFFF;
__attribute__((section(".sdata.0x00633858"))) int _pad_00633858 = 0;
__attribute__((section(".sdata.0x0063385C"))) int D_0063385C = 0;
__attribute__((section(".sdata.0x00633860"))) int D_00633860 = 0;
__attribute__((section(".sdata.0x00633864"))) int D_00633864 = 0;
__attribute__((section(".sdata.0x00633868"))) unsigned int D_00633868 = 0x7F7FFFFF;
