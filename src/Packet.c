/* Packet.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630A3C"))) float D_00630A3C = 0.99f;
__attribute__((section(".lit4.0x00630A40"))) float D_00630A40 = 16777215.0f;
__attribute__((section(".lit4.0x00630A44"))) float D_00630A44 = -16777215.0f;
__attribute__((section(".lit4.0x00630A48"))) float D_00630A48 = 0.5019608f;
__attribute__((section(".lit4.0x00630A4C"))) float D_00630A4C = 0.5019608f;
__attribute__((section(".lit4.0x00630A50"))) float D_00630A50 = 0.5019608f;
__attribute__((section(".sdata.0x00631CD0"))) char D_00631CD0[8] = { 0 };
__attribute__((section(".sdata.0x00631CD8"))) const char D_00631CD8[8] = "%02x";
__attribute__((section(".sdata.0x00631CE0"))) const char D_00631CE0[8] = " ";
__attribute__((section(".sdata.0x00631CE8"))) const char D_00631CE8[8] = "%12f ";
__attribute__((section(".sdata.0x00631CF0"))) const char D_00631CF0[8] = "\n";
__attribute__((section(".sdata.0x00631CF8"))) const char D_00631CF8[8] = "0";
__attribute__((section(".sdata.0x00631D00"))) const char D_00631D00[8] = " (%d)\n";
__attribute__((section(".sdata.0x00631D08"))) const char D_00631D08[8] = "e";
__attribute__((section(".sdata.0x00631D10"))) const char D_00631D10[8] = "%s";
__attribute__((section(".sdata.0x00631D18"))) const char D_00631D18[8] = "%s_l";
__attribute__((section(".sdata.0x00631D20"))) const char D_00631D20[8] = "%s_ref";
__attribute__((section(".sdata.0x00632D28"))) int D_00632D28 = 0;
