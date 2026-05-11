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

__attribute__((section(".rodata.0x00556F70"))) const char D_00556F70[16] = "<PARTITION>____";
__attribute__((section(".rodata.0x00556F80"))) const char D_00556F80[16] = "<FREE AREA>____";
__attribute__((section(".rodata.0x00557060"))) const char D_00557060[16] = " free memory   ";
__attribute__((section(".rodata.0x00557088"))) const char D_00557088[16] = " del partition ";
__attribute__((section(".rodata.0x005570E0"))) const char D_005570E0[16] = "ios/memory.c";
__attribute__((section(".rodata.0x00557220"))) const char D_00557220[16] = "<ALLOC>________";
__attribute__((section(".rodata.0x005572A8"))) const char D_005572A8[16] = "align%05d";
__attribute__((section(".rodata.0x005572D8"))) const char D_005572D8[16] = "mem:free ";
__attribute__((section(".rodata.0x00557360"))) const char D_00557360[16] = " free memory0  ";
__attribute__((section(".rodata.0x00557390"))) const char D_00557390[16] = " free memory1  ";
__attribute__((section(".rodata.0x005573A0"))) const char D_005573A0[16] = " free memory2  ";
__attribute__((section(".rodata.0x005573F0"))) const char D_005573F0[16] = "mem:addr:$%08x ";
__attribute__((section(".rodata.0x00557400"))) const char D_00557400[16] = "FREEAREA ";
__attribute__((section(".rodata.0x00557410"))) const char D_00557410[16] = "DELETED_MEMORY ";
__attribute__((section(".rodata.0x00557448"))) const char D_00557448[16] = "siz:$%5x ";
