/* item.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633420"))) unsigned int D_00633420 = 0x00000030;
__attribute__((section(".sdata.0x00633424"))) unsigned int D_00633424 = 0x00000142;
__attribute__((section(".sdata.0x00633428"))) unsigned int D_00633428 = 0x00000189;
__attribute__((section(".sdata.0x0063342C"))) unsigned int D_0063342C = 0x0000018A;
__attribute__((section(".sdata.0x00633430"))) char D_00633430[8] = { 0 };
__attribute__((section(".sdata.0x00633438"))) int D_00633438 = 0;
