/* rope.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006313B0"))) float D_006313B0 = 10430.3779f;
__attribute__((section(".lit4.0x006313B4"))) float D_006313B4 = 10430.3779f;
__attribute__((section(".lit4.0x006313B8"))) float D_006313B8 = 0.01f;
__attribute__((section(".lit4.0x006313BC"))) float D_006313BC = 31.8309879f;
__attribute__((section(".lit4.0x006313C0"))) float D_006313C0 = 10430.3779f;
__attribute__((section(".lit4.0x006313C4"))) float D_006313C4 = 10430.3779f;
__attribute__((section(".lit4.0x006313C8"))) float D_006313C8 = 10430.3779f;
__attribute__((section(".lit4.0x006313CC"))) float D_006313CC = 10430.3779f;
__attribute__((section(".sdata.0x006335C0"))) const char D_006335C0[8] = "0";
