/* charFileManager.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x0063201C"))) int D_0063201C = 0;
__attribute__((section(".sdata.0x00632020"))) int D_00632020 = 0;
__attribute__((section(".sdata.0x00632030"))) int D_00632030 = 0;
__attribute__((section(".sdata.0x00632038"))) int D_00632038 = 0;
__attribute__((section(".sdata.0x00632194"))) int D_00632194 = 0;
__attribute__((section(".sdata.0x00632198"))) char D_00632198[8] = { 0 };
__attribute__((section(".sdata.0x006321A0"))) char D_006321A0[8] = { 0 };
__attribute__((section(".sdata.0x006321A8"))) char D_006321A8[8] = { 0 };
__attribute__((section(".sdata.0x00632244"))) int D_00632244 = 0;
__attribute__((section(".sdata.0x00632248"))) const char D_00632248[8] = "first\n";
__attribute__((section(".sdata.0x00632250"))) const char D_00632250[8] = "set\n";
__attribute__((section(".sdata.0x00632898"))) char D_00632898[8] = { 0 };
__attribute__((section(".sdata.0x006328A0"))) const char D_006328A0[8] = "e";
__attribute__((section(".sdata.0x006328A8"))) const char D_006328A8[8] = "0";
__attribute__((section(".sdata.0x006328B0"))) const char D_006328B0[8] = "FALSE";
__attribute__((section(".sdata.0x006328B8"))) char D_006328B8[8] = { 0 };
