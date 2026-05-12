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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x00630F00"))) float D_00630F00 = -0.2f;
__attribute__((section(".lit4.0x00630F04"))) float D_00630F04 = 0.1f;
__attribute__((section(".lit4.0x00630F08"))) float D_00630F08 = 3.14159274f;
__attribute__((section(".lit4.0x00630F0C"))) float D_00630F0C = 0.6f;
__attribute__((section(".lit4.0x00630F10"))) float D_00630F10 = -0.01f;
__attribute__((section(".lit4.0x00630F14"))) float D_00630F14 = -0.05f;
__attribute__((section(".lit4.0x00630F18"))) float D_00630F18 = -0.15f;
__attribute__((section(".lit4.0x00630F1C"))) float D_00630F1C = -0.01f;
__attribute__((section(".lit4.0x00630F20"))) float D_00630F20 = -0.05f;
__attribute__((section(".lit4.0x00630F24"))) float D_00630F24 = -0.15f;
__attribute__((section(".lit4.0x00630F28"))) float D_00630F28 = -0.01f;
__attribute__((section(".lit4.0x00630F2C"))) float D_00630F2C = -0.2f;
__attribute__((section(".lit4.0x00630F30"))) float D_00630F30 = -0.3f;
__attribute__((section(".lit4.0x00630F34"))) float D_00630F34 = -0.05f;
__attribute__((section(".lit4.0x00630F38"))) float D_00630F38 = -0.15f;
__attribute__((section(".lit4.0x00630F3C"))) float D_00630F3C = -1.57079637f;
__attribute__((section(".lit4.0x00630F40"))) float D_00630F40 = -0.01f;
__attribute__((section(".lit4.0x00630F44"))) float D_00630F44 = -0.05f;
__attribute__((section(".lit4.0x00630F48"))) float D_00630F48 = -0.15f;
__attribute__((section(".lit4.0x00630F4C"))) float D_00630F4C = -0.01f;
__attribute__((section(".lit4.0x00630F50"))) float D_00630F50 = -0.05f;
__attribute__((section(".lit4.0x00630F54"))) float D_00630F54 = -0.15f;
__attribute__((section(".lit4.0x00630F58"))) float D_00630F58 = -1.57079637f;
__attribute__((section(".lit4.0x00630F5C"))) float D_00630F5C = -0.05f;
__attribute__((section(".lit4.0x00630F60"))) float D_00630F60 = 0.675f;
__attribute__((section(".lit4.0x00630F64"))) float D_00630F64 = 3.14159274f;
__attribute__((section(".lit4.0x00630F68"))) float D_00630F68 = 0.2f;
__attribute__((section(".lit4.0x00630F6C"))) float D_00630F6C = 3.14159274f;
__attribute__((section(".lit4.0x00630F70"))) float D_00630F70 = 3.14159274f;
__attribute__((section(".lit4.0x00630F74"))) float D_00630F74 = -0.2f;
__attribute__((section(".lit4.0x00630F78"))) float D_00630F78 = 0.1f;
__attribute__((section(".lit4.0x00630F7C"))) float D_00630F7C = -0.2f;
__attribute__((section(".lit4.0x00630F80"))) float D_00630F80 = 0.1f;
__attribute__((section(".lit4.0x00630F84"))) float D_00630F84 = 0.1f;
__attribute__((section(".lit4.0x00630F88"))) float D_00630F88 = -0.1f;
__attribute__((section(".lit4.0x00630F8C"))) float D_00630F8C = 3.14159274f;
__attribute__((section(".lit4.0x00630F90"))) float D_00630F90 = -0.2f;
__attribute__((section(".lit4.0x00630F94"))) float D_00630F94 = 0.1f;
__attribute__((section(".lit4.0x00630F98"))) float D_00630F98 = 3.14159274f;
__attribute__((section(".sdata.0x00632758"))) int D_00632758 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x0063275C"))) int D_0063275C = 0x00000000;
__attribute__((section(".sdata.0x00632760"))) const char D_00632760[8] = "0";
__attribute__((section(".sdata.0x00632768"))) unsigned int D_00632768 = 0x000A6425;
__attribute__((section(".sdata.0x0063276C"))) unsigned int D_0063276C = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632770"))) unsigned int D_00632770 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632CBC"))) int D_00632CBC = 0;
__attribute__((section(".sdata.0x00632D94"))) int D_00632D94 = 0;

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
