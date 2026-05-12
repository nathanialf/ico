/* attackhit.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632DBC"))) int D_00632DBC = 0;

__attribute__((section(".rodata.0x0055A518"))) const char D_0055A518[16] = "src/attackhit.c";

__attribute__((section(".rodata.0x0055A528"))) const char D_0055A528[16] = "gop!=NULL";

/* String rodata migrated from attackhit_data.c */
__attribute__((section(".rodata.0x0055A4B0"))) const char D_0055A4B0[16] = "flag ok\n";
__attribute__((section(".rodata.0x0055A4C0"))) const char D_0055A4C0[16] = "group ok\n";
__attribute__((section(".rodata.0x0055A4D0"))) const char D_0055A4D0[16] = "invincible ok\n";
__attribute__((section(".rodata.0x0055A4E0"))) const char D_0055A4E0[16] = "geometry ok\n";
__attribute__((section(".rodata.0x0055A4F0"))) const char D_0055A4F0[16] = "id equal error\n";
__attribute__((section(".rodata.0x0055A500"))) const char D_0055A500[24] = "mail send ok [%d]\n";
__attribute__((section(".rodata.0x0055A538"))) const char D_0055A538[48] = "brainStatusDefaultSet: brain target area over\n";

/* Float rodata migrated from attackhit_data.c */
__attribute__((section(".rodata.0x0055A5A8"))) const float D_0055A5A8[2] = { 89128.96f, 0.955f };
