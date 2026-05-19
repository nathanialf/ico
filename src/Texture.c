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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */


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

#include "matching.h"
#include "include_asm.h"

extern void func_001FBAA8(int a0, int a1, int a2);
extern void func_001FB8B8(void);
extern void func_0012CEF8(void);

INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012AED0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012AFC0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012B1C0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012B850);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BA68);

void func_0012BBE8(int a0)
{
    func_001FBAA8(2, a0 + 0x58, 5);
    func_001FB8B8();
}

INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BC0C);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BC10);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012BEB0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C050);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C3D0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C610);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C6F0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012C8F8);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012CB70);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012CEF8);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012D218);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012D370);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012D4A0);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DA48);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DE00);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DE80);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012DF98);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012E0D8);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012E528);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012E940);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012F818);
INCLUDE_ASM("asm/nonmatchings/src/Texture", func_0012FCE0);

void func_0012FD30(void) {
    func_0012CEF8();
    DEFEAT_TCO();
}
