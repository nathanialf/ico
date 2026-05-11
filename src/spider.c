/* spider.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006313D0"))) float D_006313D0 = 3.14159274f;
__attribute__((section(".lit4.0x006313D4"))) float D_006313D4 = 10000.0f;
__attribute__((section(".lit4.0x006313D8"))) float D_006313D8 = 0.9f;
__attribute__((section(".lit4.0x006313DC"))) float D_006313DC = 1000000.0f;
