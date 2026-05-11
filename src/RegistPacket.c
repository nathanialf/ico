/* RegistPacket.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006309D0"))) float D_006309D0 = 0.99f;
__attribute__((section(".sdata.0x00631970"))) char D_00631970[16] = { 0 };
__attribute__((section(".sdata.0x00631980"))) char D_00631980[16] = { 0 };
__attribute__((section(".sdata.0x00631D48"))) const char D_00631D48[8] = "0";
__attribute__((section(".sdata.0x00631D50"))) int D_00631D50 = 0;
__attribute__((section(".sdata.0x00631D54"))) int D_00631D54 = 0;
__attribute__((section(".sdata.0x00631D58"))) char D_00631D58 = 0;
__attribute__((section(".sdata.0x00631D59"))) char D_00631D59 = 0;
__attribute__((section(".sdata.0x00631D5A"))) char D_00631D5A = 0;
__attribute__((section(".sdata.0x00631D5B"))) unsigned char D_00631D5B = 0x00;
__attribute__((section(".sdata.0x00631D5C"))) int _pad_00631D5C = 0;
__attribute__((section(".sdata.0x00631D60"))) int D_00631D60 = 0x00000053;
__attribute__((section(".sdata.0x00631D64"))) int D_00631D64 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00631D68"))) const char D_00631D68[8] = "On";
__attribute__((section(".sdata.0x00631D70"))) unsigned int D_00631D70 = 0x0066664F;
__attribute__((section(".sdata.0x00631D74"))) int D_00631D74 = 0;
__attribute__((section(".sdata.0x00631D78"))) const char D_00631D78[] = "%s : %s";
__attribute__((section(".sdata.0x00631D80"))) const char D_00631D80[] = "%s : %d";
__attribute__((section(".sdata.0x00632D04"))) int D_00632D04 = 0;

__attribute__((section(".rodata.0x00555650"))) const char D_00555650[24] = "src/RegistPacket.c";

__attribute__((section(".rodata.0x00555A68"))) const char D_00555A68[24] = " Shadow Blend 1/64 ";
__attribute__((section(".rodata.0x00555A80"))) const char D_00555A80[24] = " Shadow Blend 1/16 ";
__attribute__((section(".rodata.0x00555A98"))) const char D_00555A98[24] = " Shadow Blend 1/4  ";
__attribute__((section(".rodata.0x00555AB0"))) const char D_00555AB0[24] = " Shadow Blend 1/1  ";
__attribute__((section(".rodata.0x00555AC8"))) const char D_00555AC8[24] = " Shadow Color B    ";
__attribute__((section(".rodata.0x00555AE0"))) const char D_00555AE0[24] = " Shadow Color G    ";
__attribute__((section(".rodata.0x00555AF8"))) const char D_00555AF8[24] = " Shadow Color R    ";
__attribute__((section(".rodata.0x00555B10"))) const char D_00555B10[24] = " Shadow Depth      ";
__attribute__((section(".rodata.0x00555B30"))) const char D_00555B30[16] = "Shadow Tool";
