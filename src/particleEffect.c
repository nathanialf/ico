/* particleEffect.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006313A4"))) float D_006313A4 = 4095.0f;
__attribute__((section(".lit4.0x006313A8"))) float D_006313A8 = 0.2f;
__attribute__((section(".lit4.0x006313AC"))) float D_006313AC = 4095.0f;

__attribute__((section(".rodata.0x00619E08"))) const char D_00619E08[24] = "src/particleEffect.c";

__attribute__((section(".rodata.0x00619DF8"))) const char D_00619DF8[16] = "enemy_tex01";

/* String rodata migrated from particleEffect_data.c */
__attribute__((section(".rodata.0x00619DE0"))) const char D_00619DE0[24] = "PARTICLE EFFECT WRONG\n";
__attribute__((section(".rodata.0x00619E20"))) const char D_00619E20[32] = "No more effect... Ignored.\n";
