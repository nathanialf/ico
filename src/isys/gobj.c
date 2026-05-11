/* gobj.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632008"))) int D_00632008 = 0;
__attribute__((section(".sdata.0x006321C0"))) char D_006321C0[8] = { 0 };
__attribute__((section(".sdata.0x006321C8"))) unsigned int D_006321C8 = 0x00000030;
__attribute__((section(".sdata.0x006321CC"))) int D_006321CC = 0;
__attribute__((section(".sdata.0x006321D0"))) int D_006321D0 = 0;
__attribute__((section(".sdata.0x006321D4"))) int D_006321D4 = 0;
__attribute__((section(".sdata.0x006321D8"))) int D_006321D8 = 0;

__attribute__((section(".rodata.0x00557A10"))) const char D_00557A10[16] = "isys/gobj.c";
