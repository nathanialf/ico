/* PObj.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633BA8"))) const char D_00633BA8[8] = "%s";
__attribute__((section(".sdata.0x00633BB0"))) const char D_00633BB0[8] = "\x1b[m";
__attribute__((section(".sdata.0x00633BB8"))) const char D_00633BB8[8] = "OBJH";
__attribute__((section(".sdata.0x00633BC0"))) const char D_00633BC0[] = "FALSE";

__attribute__((section(".rodata.0x0062E010"))) const char D_0062E010[16] = "src/PObj.c";

__attribute__((section(".rodata.0x0062E0D8"))) const char D_0062E0D8[16] = "D1_TADR=%08x:";
__attribute__((section(".rodata.0x0062E0E8"))) const char D_0062E0E8[16] = "D1_MADR=%08x:";
__attribute__((section(".rodata.0x0062E118"))) const char D_0062E118[16] = "D2_TADR=%08x:";
__attribute__((section(".rodata.0x0062E128"))) const char D_0062E128[16] = "D2_MADR=%08x:";
__attribute__((section(".rodata.0x0062E5A0"))) const char D_0062E5A0[24] = "TTY: receive error";
__attribute__((section(".rodata.0x0062E658"))) const char D_0062E658[8] = "....";
__attribute__((section(".rodata.0x0062E660"))) const char D_0062E660[8] = "....";
__attribute__((section(".rodata.0x0062E668"))) const char D_0062E668[8] = "all";
__attribute__((section(".rodata.0x0062E670"))) const char D_0062E670[16] = "rom0:UDNL ";
