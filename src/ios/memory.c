/* memory.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x006320B0"))) char D_006320B0[8] = { 0 };
__attribute__((section(".sdata.0x006320B8"))) const char D_006320B8[8] = "e";
__attribute__((section(".sdata.0x006320C0"))) const char D_006320C0[8] = "0";
__attribute__((section(".sdata.0x006320C8"))) const char D_006320C8[8] = "align";
__attribute__((section(".sdata.0x006320D0"))) const char D_006320D0[8] = "ALLOC ";
__attribute__((section(".sdata.0x006320D8"))) const char D_006320D8[8] = "%c";
__attribute__((section(".sdata.0x006320E0"))) const char D_006320E0[8] = "\n";
