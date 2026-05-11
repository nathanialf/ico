/* DisplayList.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631C4C"))) int D_00631C4C = 0;
__attribute__((section(".sdata.0x00631C50"))) int D_00631C50 = 0;
__attribute__((section(".sdata.0x0063378C"))) int D_0063378C = 0;
__attribute__((section(".sdata.0x00633790"))) int D_00633790 = 0;
__attribute__((section(".sdata.0x00633794"))) int D_00633794 = 0;
__attribute__((section(".sdata.0x00633798"))) int D_00633798 = 0;
__attribute__((section(".sdata.0x0063379C"))) int D_0063379C = 0;
__attribute__((section(".sdata.0x006337A0"))) char D_006337A0[8] = { 0 };
__attribute__((section(".sdata.0x006337A8"))) char D_006337A8 = 0;
__attribute__((section(".sdata.0x006337A9"))) char D_006337A9 = 0;
__attribute__((section(".sdata.0x006337AA"))) char D_006337AA = 0;
__attribute__((section(".sdata.0x006337AB"))) unsigned char D_006337AB = 0x00;
__attribute__((section(".sdata.0x006337AC"))) int _pad_006337AC = 0;
__attribute__((section(".sdata.0x00633810"))) char D_00633810[8] = { 0 };
__attribute__((section(".sdata.0x00633818"))) int D_00633818 = 0x534C4146;
__attribute__((section(".sdata.0x0063381C"))) int D_0063381C = 0x00000045;
__attribute__((section(".sdata.0x00633820"))) int D_00633820 = 0x00000065;
__attribute__((section(".sdata.0x00633824"))) int D_00633824 = 0;

__attribute__((section(".rodata.0x0061AB88"))) const char D_0061AB88[24] = "src/DisplayList.c";
