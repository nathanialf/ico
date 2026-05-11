/* fieldCollision.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x006323C7"))) unsigned char D_006323C7 = 0xFF;
__attribute__((section(".sdata.0x006323C8"))) char D_006323C8[8] = { 0 };
__attribute__((section(".sdata.0x006323D0"))) const char D_006323D0[8] = "e";
__attribute__((section(".sdata.0x006323D8"))) const char D_006323D8[8] = " COL: ";
__attribute__((section(".sdata.0x006323E0"))) const char D_006323E0[8] = " MAT: ";
__attribute__((section(".sdata.0x006323E8"))) const char D_006323E8[8] = "GOBJ: ";
__attribute__((section(".sdata.0x006323F0"))) unsigned int D_006323F0 = 0x00167230;
__attribute__((section(".sdata.0x006323F4"))) unsigned int D_006323F4 = 0x00167258;
__attribute__((section(".sdata.0x006323F8"))) char D_006323F8[8] = { 0 };
__attribute__((section(".sdata.0x00632400"))) const char D_00632400[8] = "%2d ";
__attribute__((section(".sdata.0x00632408"))) const char D_00632408[8] = "\n";
__attribute__((section(".sdata.0x00632410"))) const char D_00632410[8] = "0";
__attribute__((section(".sdata.0x00632418"))) const char D_00632418[] = "%10.3f ";
__attribute__((section(".sdata.0x00632420"))) const char D_00632420[8] = "\n";
__attribute__((section(".sdata.0x00632428"))) const char D_00632428[8] = "[%d]: ";
__attribute__((section(".sdata.0x00632430"))) const char D_00632430[8] = "boy";
__attribute__((section(".sdata.0x00632438"))) const char D_00632438[8] = "girl";
__attribute__((section(".sdata.0x00632440"))) int D_00632440 = 0x000000D7;
__attribute__((section(".sdata.0x00632444"))) int D_00632444 = 0x000000E2;
__attribute__((section(".sdata.0x00632448"))) int D_00632448 = 0x000000D8;
__attribute__((section(".sdata.0x0063244C"))) int D_0063244C = 0x000000E3;

__attribute__((section(".rodata.0x005591F0"))) const char D_005591F0[24] = "src/fieldCollision.c";

__attribute__((section(".rodata.0x00559240"))) const char D_00559240[16] = "W :%4d %2d";
__attribute__((section(".rodata.0x00559250"))) const char D_00559250[16] = "WR:%4d %2d";
__attribute__((section(".rodata.0x00559260"))) const char D_00559260[16] = "F :%4d %2d";
__attribute__((section(".rodata.0x00559270"))) const char D_00559270[16] = "FR:%4d %2d";
__attribute__((section(".rodata.0x005592D0"))) const char D_005592D0[16] = "%8f %8f %8f";
