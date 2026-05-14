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
__attribute__((section(".sdata.0x00631E10"))) int D_00631E10 = 0x80808080;
__attribute__((section(".sdata.0x00631E14"))) int D_00631E14 = 0x00000000;
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
__attribute__((section(".sdata.0x00631EA0"))) int D_00631EA0 = 0x00000001;
__attribute__((section(".sdata.0x00631EA4"))) int D_00631EA4 = 0x00000000;
__attribute__((section(".sdata.0x00631EA8"))) int D_00631EA8 = 0xFFFFFF00;
__attribute__((section(".sdata.0x00631EAC"))) int D_00631EAC = 0xFFC0C000;
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
__attribute__((section(".sdata.0x00631F10"))) int D_00631F10 = 0x00000080;
__attribute__((section(".sdata.0x00631F14"))) int D_00631F14 = 0x00000000;
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

__attribute__((section(".rodata.0x00555ED8"))) const char D_00555ED8[16] = "src/Texture.c";

__attribute__((section(".rodata.0x005565C8"))) const char D_005565C8[24] = "%8s:SIZE=%3dX%3d";
__attribute__((section(".rodata.0x005565E0"))) const char D_005565E0[24] = "/%d Name:%s x:x%d";
__attribute__((section(".rodata.0x00556620"))) const char D_00556620[48] = "No.              Name   Size MIP IMG CL US";
__attribute__((section(".rodata.0x00556650"))) const char D_00556650[32] = "%03d%18s%7d:%1d/%1d:%s:%s:%s";
__attribute__((section(".rodata.0x00556670"))) const char D_00556670[16] = "   %17s %7d ";
__attribute__((section(".rodata.0x00556680"))) const char D_00556680[24] = "TotalTextureSize";
__attribute__((section(".rodata.0x00556728"))) const char D_00556728[16] = " Fog Strength ";
__attribute__((section(".rodata.0x00556738"))) const char D_00556738[16] = " Fog Far      ";
__attribute__((section(".rodata.0x00556748"))) const char D_00556748[16] = " Fog Near     ";
__attribute__((section(".rodata.0x00556758"))) const char D_00556758[16] = " Fog Offset A ";
__attribute__((section(".rodata.0x00556768"))) const char D_00556768[16] = " Fog Color A  ";
__attribute__((section(".rodata.0x00556778"))) const char D_00556778[16] = " Fog Color B  ";
__attribute__((section(".rodata.0x00556788"))) const char D_00556788[16] = " Fog Color G  ";
__attribute__((section(".rodata.0x00556798"))) const char D_00556798[16] = " Fog Color R  ";
__attribute__((section(".rodata.0x005567A8"))) const char D_005567A8[16] = " Fog On/Off   ";
__attribute__((section(".rodata.0x005567C0"))) const char D_005567C0[16] = "Fog Tool";

/* String rodata migrated from Texture_data.c */
__attribute__((section(".rodata.0x005563F0"))) const char D_005563F0[64] = "TEXTURE BROKEN. \"%s\"\n    I:%d C:%d iadr:%p cadr:%p hadr:%p\n";
__attribute__((section(".rodata.0x005564E0"))) const char D_005564E0[48] = "tex_TransTexture:INVALID TEXTURE ID. %d/%d\n";
__attribute__((section(".rodata.0x00556580"))) const char D_00556580[72] = "illegal user space data [%s] Clut Scroll (color:%d start:%d end:%d)\n";
__attribute__((section(".rodata.0x005567D0"))) const char D_005567D0[16] = "Fog %s => %s\n";
__attribute__((section(".rodata.0x005567E0"))) const char D_005567E0[16] = "Fog %s => %d\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "tex_loadImage:判別できないテクスチャフォーマットです.
" */
__attribute__((section(".rodata.0x00555EA0"))) const char D_00555EA0[56] = "tex_loadImage:\310\275\312\314\244\307\244\255\244\312\244\244\245\306\245\257\245\271\245\301\245\343\245\325\245\251\241\274\245\336\245\303\245\310\244\307\244\271.\n";
/* EUC-JP: "tex_loadImage:テクスチャのサイズが大きすぎます.
" */
__attribute__((section(".rodata.0x00555EE8"))) const char D_00555EE8[56] = "tex_loadImage:\245\306\245\257\245\271\245\301\245\343\244\316\245\265\245\244\245\272\244\254\302\347\244\255\244\271\244\256\244\336\244\271.\n";
/* EUC-JP: "DIRECTでもCLUTでもないテクスチャタイプが指定されました.
" */
__attribute__((section(".rodata.0x00556010"))) const char D_00556010[64] = "DIRECT\244\307\244\342CLUT\244\307\244\342\244\312\244\244\245\306\245\257\245\271\245\301\245\343\245\277\245\244\245\327\244\254\273\330\304\352\244\265\244\354\244\336\244\267\244\277.\n";
/* EUC-JP: "tex_transTM2:ミップマップテクスチャの枚数が多すぎます.
" */
__attribute__((section(".rodata.0x00556050"))) const char D_00556050[56] = "tex_transTM2:\245\337\245\303\245\327\245\336\245\303\245\327\245\306\245\257\245\271\245\301\245\343\244\316\313\347\277\364\244\254\302\277\244\271\244\256\244\336\244\271.\n";
/* EUC-JP: "テクスチャが壊れています."%s"I:%d C:%d iadr:%p cadr:%p hadr:%p
" */
__attribute__((section(".rodata.0x00556088"))) const char D_00556088[72] = "\245\306\245\257\245\271\245\301\245\343\244\254\262\365\244\354\244\306\244\244\244\336\244\271.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n";
/* EUC-JP: "tex_makeTexturePacket:テクスチャのユーザースペースフォーマットが異常です.'%s'
" */
__attribute__((section(".rodata.0x005563A0"))) const char D_005563A0[80] = "tex_makeTexturePacket:\245\306\245\257\245\271\245\301\245\343\244\316\245\346\241\274\245\266\241\274\245\271\245\332\241\274\245\271\245\325\245\251\241\274\245\336\245\303\245\310\244\254\260\333\276\357\244\307\244\271.'%s'\n";
/* EUC-JP: "[31mパスの違う同名のテクスチャを読み込もうとしました.
" */
__attribute__((section(".rodata.0x00556430"))) const char D_00556430[56] = "\033[31m\245\321\245\271\244\316\260\343\244\246\306\261\314\276\244\316\245\306\245\257\245\271\245\301\245\343\244\362\306\311\244\337\271\376\244\342\244\246\244\310\244\267\244\336\244\267\244\277.\n";
/* EUC-JP: "テクスチャが多すぎます.テクスチャリスト領域を増やしてください
" */
__attribute__((section(".rodata.0x00556478"))) const char D_00556478[64] = "\245\306\245\257\245\271\245\301\245\343\244\254\302\277\244\271\244\256\244\336\244\271.\245\306\245\257\245\271\245\301\245\343\245\352\245\271\245\310\316\316\260\350\244\362\301\375\244\344\244\267\244\306\244\257\244\300\244\265\244\244\n";
/* EUC-JP: "テクスチャ "%s" がみつかりません.
" */
__attribute__((section(".rodata.0x005564B8"))) const char D_005564B8[40] = "\245\306\245\257\245\271\245\301\245\343 \"%s\" \244\254\244\337\244\304\244\253\244\352\244\336\244\273\244\363.\n";
/* EUC-JP: "tex_TransTexture:テクスチャの転送に失敗しました. %d
" */
__attribute__((section(".rodata.0x00556510"))) const char D_00556510[56] = "tex_TransTexture:\245\306\245\257\245\271\245\301\245\343\244\316\305\276\301\367\244\313\274\272\307\324\244\267\244\336\244\267\244\277. %d\n";
/* EUC-JP: "tex_TransTexture:テクスチャの転送に失敗しました. %d:%s
" */
__attribute__((section(".rodata.0x00556548"))) const char D_00556548[56] = "tex_TransTexture:\245\306\245\257\245\271\245\301\245\343\244\316\305\276\301\367\244\313\274\272\307\324\244\267\244\336\244\267\244\277. %d:%s\n";
