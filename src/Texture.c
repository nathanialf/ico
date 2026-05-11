/* Texture.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631DD0"))) const char D_00631DD0[8] = "0";
__attribute__((section(".sdata.0x00631DD8"))) const char D_00631DD8[8] = "FALSE";
__attribute__((section(".sdata.0x00631DE0"))) const char D_00631DE0[8] = "ICO";
__attribute__((section(".sdata.0x00631DE8"))) const char D_00631DE8[8] = "e";
__attribute__((section(".sdata.0x00631DF0"))) const char D_00631DF0[8] = "%s";
__attribute__((section(".sdata.0x00631DF8"))) const char D_00631DF8[8] = "1:%s\n";
__attribute__((section(".sdata.0x00631E00"))) const char D_00631E00[8] = "%s.tm2";
__attribute__((section(".sdata.0x00631E08"))) char D_00631E08[8] = { 0 };
__attribute__((section(".sdata.0x00631E10"))) unsigned char D_00631E10[8] = { 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00631E18"))) const char D_00631E18[8] = "SELTEX";
__attribute__((section(".sdata.0x00631E20"))) const char D_00631E20[8] = "SCRL-U";
__attribute__((section(".sdata.0x00631E28"))) const char D_00631E28[8] = "SCRL-V";
__attribute__((section(".sdata.0x00631E30"))) const char D_00631E30[8] = "AMP-U ";
__attribute__((section(".sdata.0x00631E38"))) const char D_00631E38[8] = "AMP-V ";
__attribute__((section(".sdata.0x00631E40"))) const char D_00631E40[8] = "CS-BGN";
__attribute__((section(".sdata.0x00631E48"))) const char D_00631E48[8] = "CS-END";
__attribute__((section(".sdata.0x00631E50"))) const char D_00631E50[8] = "CS-SPD";
__attribute__((section(".sdata.0x00631E58"))) const char D_00631E58[8] = "CS-STP";
__attribute__((section(".sdata.0x00631E60"))) const char D_00631E60[8] = "SHINE ";
__attribute__((section(".sdata.0x00631E68"))) const char D_00631E68[8] = "SMPMAG";
__attribute__((section(".sdata.0x00631E70"))) const char D_00631E70[8] = "SMPMIN";
__attribute__((section(".sdata.0x00631E78"))) const char D_00631E78[8] = "TEXFNC";
__attribute__((section(".sdata.0x00631E80"))) const char D_00631E80[8] = "ALPTST";
__attribute__((section(".sdata.0x00631E88"))) const char D_00631E88[8] = "ALPFAI";
__attribute__((section(".sdata.0x00631E90"))) const char D_00631E90[] = "MIPMAPK";
__attribute__((section(".sdata.0x00631E98"))) const char D_00631E98[] = "MIPMAPL";
__attribute__((section(".sdata.0x00631EA0"))) unsigned char D_00631EA0[8] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00631EA8"))) unsigned char D_00631EA8[8] = { 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xC0, 0xC0, 0xFF };
__attribute__((section(".sdata.0x00631EB0"))) const char D_00631EB0[8] = "%s:%d";
__attribute__((section(".sdata.0x00631EB8"))) const char D_00631EB8[8] = "%s:%f";
__attribute__((section(".sdata.0x00631EC0"))) const char D_00631EC0[8] = "C-8";
__attribute__((section(".sdata.0x00631EC8"))) const char D_00631EC8[8] = "C-4";
__attribute__((section(".sdata.0x00631ED0"))) const char D_00631ED0[8] = "D32";
__attribute__((section(".sdata.0x00631ED8"))) const char D_00631ED8[8] = "D24";
__attribute__((section(".sdata.0x00631EE0"))) const char D_00631EE0[8] = "D16";
__attribute__((section(".sdata.0x00631EE8"))) const char D_00631EE8[8] = "NON";
__attribute__((section(".sdata.0x00631EF0"))) const char D_00631EF0[8] = "32";
__attribute__((section(".sdata.0x00631EF8"))) const char D_00631EF8[8] = "24";
__attribute__((section(".sdata.0x00631F00"))) const char D_00631F00[8] = "16";
__attribute__((section(".sdata.0x00631F08"))) const char D_00631F08[8] = "--";
__attribute__((section(".sdata.0x00631F10"))) unsigned char D_00631F10[8] = { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00631F18"))) unsigned int D_00631F18 = 0x00000020;
__attribute__((section(".sdata.0x00631F1C"))) int D_00631F1C = 0;
__attribute__((section(".sdata.0x00631F20"))) char D_00631F20[8] = { 0 };
__attribute__((section(".sdata.0x00631F28"))) const char D_00631F28[8] = "Z";
__attribute__((section(".sdata.0x00631F30"))) const char D_00631F30[8] = "On";
__attribute__((section(".sdata.0x00631F38"))) unsigned int D_00631F38 = 0x0066664F;
__attribute__((section(".sdata.0x00631F3C"))) int D_00631F3C = 0;
__attribute__((section(".sdata.0x00631F40"))) const char D_00631F40[] = "%s : %s";
__attribute__((section(".sdata.0x00631F48"))) const char D_00631F48[] = "%s : %d";
__attribute__((section(".sdata.0x00632C9C"))) int D_00632C9C = 0;
__attribute__((section(".sdata.0x00632CA0"))) int D_00632CA0 = 0;
