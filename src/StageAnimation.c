/* StageAnimation.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631A10"))) char D_00631A10[16] = { 0 };
__attribute__((section(".sdata.0x00631D88"))) const char D_00631D88[8] = "0";
__attribute__((section(".sdata.0x00631D90"))) const char D_00631D90[8] = "BGA";
__attribute__((section(".sdata.0x00631D98"))) const char D_00631D98[8] = "e";
__attribute__((section(".sdata.0x00631DA0"))) const char D_00631DA0[8] = "PSMT8";
__attribute__((section(".sdata.0x00631DA8"))) const char D_00631DA8[8] = "PSMT4";
__attribute__((section(".sdata.0x00631DB0"))) const char D_00631DB0[] = "PSMCT32";
__attribute__((section(".sdata.0x00631DB8"))) const char D_00631DB8[] = "PSMCT24";
__attribute__((section(".sdata.0x00631DC0"))) const char D_00631DC0[] = "PSMCT16";
__attribute__((section(".sdata.0x00631DC8"))) const char D_00631DC8[8] = "NONE";
