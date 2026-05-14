/* BgAnimation.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00631430"))) float D_00631430 = 2.66f;
__attribute__((section(".lit4.0x00631434"))) float D_00631434 = 182.044449f;
__attribute__((section(".lit4.0x00631438"))) float D_00631438 = 182.044449f;
__attribute__((section(".lit4.0x0063143C"))) float D_0063143C = 3.14159274f;
__attribute__((section(".lit4.0x00631440"))) float D_00631440 = 10430.3779f;
__attribute__((section(".lit4.0x00631444"))) float D_00631444 = 0.01f;
__attribute__((section(".lit4.0x00631448"))) float D_00631448 = -3000.0f;
__attribute__((section(".sdata.0x006319F0"))) char D_006319F0[16] = { 0 };
__attribute__((section(".sdata.0x00631C64"))) int D_00631C64 = 0;
__attribute__((section(".sdata.0x006337B0"))) int D_006337B0 = 0;
__attribute__((section(".sdata.0x006337B4"))) unsigned int D_006337B4 = 0x00000001;
__attribute__((section(".sdata.0x006337B8"))) int D_006337B8 = 0;
__attribute__((section(".sdata.0x006337BC"))) int D_006337BC = 0;
__attribute__((section(".sdata.0x006337C0"))) const char D_006337C0[8] = "BGA";
__attribute__((section(".sdata.0x006337C8"))) const char D_006337C8[8] = "FALSE";
__attribute__((section(".sdata.0x006337D0"))) const char D_006337D0[8] = "SDF";
__attribute__((section(".sdata.0x006337D8"))) const char D_006337D8[8] = "0";
__attribute__((section(".sdata.0x006337E0"))) unsigned int D_006337E0 = 0x00000065;
__attribute__((section(".sdata.0x006337E4"))) int D_006337E4 = 0;
__attribute__((section(".sdata.0x006337E8"))) const char D_006337E8[8] = "LWS";
__attribute__((section(".sdata.0x006337F0"))) int D_006337F0 = 0;
__attribute__((section(".sdata.0x006337F4"))) unsigned int D_006337F4 = 0x00000080;
__attribute__((section(".sdata.0x006337F8"))) unsigned int D_006337F8 = 0x00000080;
__attribute__((section(".sdata.0x006337FC"))) unsigned int D_006337FC = 0x00000080;
__attribute__((section(".sdata.0x00633800"))) int D_00633800 = 0x00000080;
__attribute__((section(".sdata.0x00633804"))) int D_00633804 = 0x00000000;
__attribute__((section(".sdata.0x00633808"))) const char D_00633808[8] = "font";

__attribute__((section(".rodata.0x0061A8D8"))) const char D_0061A8D8[24] = "src/BgAnimation.c";

/* String rodata migrated from BgAnimation_data.c */
__attribute__((section(".rodata.0x0061A8C0"))) const char D_0061A8C0[24] = "this is not bga file.\n";
__attribute__((section(".rodata.0x0061A918"))) const char D_0061A918[32] = "this is not sdf camera file.\n";
__attribute__((section(".rodata.0x0061A938"))) const char D_0061A938[32] = "Light Object not exists.\n";
__attribute__((section(".rodata.0x0061A958"))) const char D_0061A958[32] = "Shadow Object not exists.\n";
__attribute__((section(".rodata.0x0061A978"))) const char D_0061A978[32] = "OBJECT FILE \"%s\" NOT EXISTS.\n";
__attribute__((section(".rodata.0x0061A9F8"))) const char D_0061A9F8[40] = "Illegal Envelope Type : %p(%d)\n";
__attribute__((section(".rodata.0x0061AAF0"))) const char D_0061AAF0[32] = "illegal lightning data set.\n";
__attribute__((section(".rodata.0x0061AB10"))) const char D_0061AB10[64] = "Lightning data does not found! maybe, start point < end point.\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "モデルデータファイル[%s]がありません.

" */
__attribute__((section(".rodata.0x0061A998"))) const char D_0061A998[40] = "\245\342\245\307\245\353\245\307\241\274\245\277\245\325\245\241\245\244\245\353[%s]\244\254\244\242\244\352\244\336\244\273\244\363.\n\n";
/* EUC-JP: "不明なパーティクル
" */
__attribute__((section(".rodata.0x0061AA48"))) const char D_0061AA48[24] = "\311\324\314\300\244\312\245\321\241\274\245\306\245\243\245\257\245\353\n";
/* EUC-JP: "PBGAタイプのアニメーションではループのパーティクルは使用できません.
" */
__attribute__((section(".rodata.0x0061AA60"))) const char D_0061AA60[80] = "PBGA\245\277\245\244\245\327\244\316\245\242\245\313\245\341\241\274\245\267\245\347\245\363\244\307\244\317\245\353\241\274\245\327\244\316\245\321\241\274\245\306\245\243\245\257\245\353\244\317\273\310\315\321\244\307\244\255\244\336\244\273\244\363.\n";
