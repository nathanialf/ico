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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x00630AF0"))) float D_00630AF0 = 3.14159274f;
__attribute__((section(".lit4.0x00630AF4"))) float D_00630AF4 = 2.5e+07f;
__attribute__((section(".lit4.0x00630AF8"))) float D_00630AF8 = 3.14159274f;
__attribute__((section(".lit4.0x00630AFC"))) float D_00630AFC = 2.5e+07f;
__attribute__((section(".lit4.0x00630B00"))) float D_00630B00 = 2.5e+07f;
__attribute__((section(".lit4.0x00630B04"))) float D_00630B04 = 0.1f;
__attribute__((section(".lit4.0x00630B08"))) float D_00630B08 = 0.1f;
__attribute__((section(".lit4.0x00630B0C"))) float D_00630B0C = 0.1f;
__attribute__((section(".lit4.0x00630B10"))) float D_00630B10 = 0.1f;
__attribute__((section(".lit4.0x00630B14"))) float D_00630B14 = 0.1f;
__attribute__((section(".lit4.0x00630B18"))) float D_00630B18 = 0.1f;
__attribute__((section(".lit4.0x00630B1C"))) float D_00630B1C = 0.1f;
__attribute__((section(".lit4.0x00630B20"))) float D_00630B20 = 0.8f;
__attribute__((section(".lit4.0x00630B24"))) float D_00630B24 = 4900.0f;
__attribute__((section(".lit4.0x00630B28"))) float D_00630B28 = 1.57079637f;
__attribute__((section(".sdata.0x00632258"))) unsigned int D_00632258 = 0x00000030;
__attribute__((section(".sdata.0x0063225C"))) unsigned int D_0063225C = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632260"))) const char D_00632260[] = "BOMB!!\n";
__attribute__((section(".sdata.0x00632268"))) unsigned int D_00632268 = 0x000A2121;
__attribute__((section(".sdata.0x0063226C"))) unsigned int D_0063226C = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632270"))) int D_00632270 = 0;
__attribute__((section(".sdata.0x00632274"))) int D_00632274 = 0;
__attribute__((section(".sdata.0x00632278"))) unsigned int _pad_00632278 = 0x00000030;
__attribute__((section(".sdata.0x0063227C"))) int _pad_0063227C = 0;
__attribute__((section(".sdata.0x00632280"))) const char D_00632280[8] = "boy";
__attribute__((section(".sdata.0x00632288"))) const char D_00632288[8] = "girl";

__attribute__((section(".rodata.0x00557F00"))) const char D_00557F00[16] = "src/act-game.c";

__attribute__((section(".rodata.0x00557EE0"))) const char D_00557EE0[32] = "too many view check object";
__attribute__((section(".rodata.0x005581D8"))) const char D_005581D8[16] = "orient null";

/* String rodata migrated from act-game_data.c */
__attribute__((section(".rodata.0x00557F30"))) const char D_00557F30[16] = "mode=[%d]\n";
__attribute__((section(".rodata.0x005580C0"))) const char D_005580C0[16] = "shoal mail\n";
__attribute__((section(".rodata.0x005580D0"))) const char D_005580D0[32] = "[%d] [%d] [%d] [%d] [%d]\n";

/* Float rodata migrated from act-game_data.c */
__attribute__((section(".rodata.0x005581E8"))) const float D_005581E8[2] = { -107374184.0f, 1.8499999f };
