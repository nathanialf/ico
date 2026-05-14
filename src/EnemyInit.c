/* EnemyInit.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633828"))) char D_00633828[8] = { 0 };
__attribute__((section(".sdata.0x00633830"))) const char D_00633830[8] = "%s=on\n";

__attribute__((section(".rodata.0x0061AC70"))) const char D_0061AC70[16] = "src/EnemyInit.c";

/* String rodata migrated from EnemyInit_data.c */
__attribute__((section(".rodata.0x0061AC80"))) const char D_0061AC80[16] = "isys:null GObj\n";
__attribute__((section(".rodata.0x0061AC90"))) const char D_0061AC90[16] = "camera gop:%x\n";
__attribute__((section(".rodata.0x0061ACA0"))) const char D_0061ACA0[16] = "first entry\n";
__attribute__((section(".rodata.0x0061ACB0"))) const char D_0061ACB0[24] = "entry into head\n";
__attribute__((section(".rodata.0x0061ACC8"))) const char D_0061ACC8[24] = "entry into tail\n";
__attribute__((section(".rodata.0x0061ACE0"))) const char D_0061ACE0[24] = "LinkCameraDL in\n";
__attribute__((section(".rodata.0x0061ACF8"))) const char D_0061ACF8[24] = "LinkCameraDL out\n";
