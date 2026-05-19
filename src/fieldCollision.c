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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern unsigned char D_006323C7;
extern char D_006323C8[8];
extern const char D_006323D0[8];
extern const char D_006323D8[8];
extern const char D_006323E0[8];
extern const char D_006323E8[8];
extern unsigned int D_006323F0;
extern unsigned int D_006323F4;
extern char D_006323F8[8];
extern const char D_00632400[8];
extern const char D_00632408[8];
extern const char D_00632410[8];
extern const char D_00632418[];
extern const char D_00632420[8];
extern const char D_00632428[8];
extern const char D_00632430[8];
extern const char D_00632438[8];
extern int D_00632440;
extern int D_00632444;
extern int D_00632448;
extern int D_0063244C;

__attribute__((section(".rodata.0x005591F0"))) const char D_005591F0[24] = "src/fieldCollision.c";

__attribute__((section(".rodata.0x00559240"))) const char D_00559240[16] = "W :%4d %2d";
__attribute__((section(".rodata.0x00559250"))) const char D_00559250[16] = "WR:%4d %2d";
__attribute__((section(".rodata.0x00559260"))) const char D_00559260[16] = "F :%4d %2d";
__attribute__((section(".rodata.0x00559270"))) const char D_00559270[16] = "FR:%4d %2d";
__attribute__((section(".rodata.0x005592D0"))) const char D_005592D0[16] = "%8f %8f %8f";

/* String rodata migrated from fieldCollision_data.c */
__attribute__((section(".rodata.0x005592E0"))) const char D_005592E0[24] = "cl:src is not inside\n";
__attribute__((section(".rodata.0x005592F8"))) const char D_005592F8[24] = "cl:dst is not outside\n";
__attribute__((section(".rodata.0x00559310"))) const char D_00559310[16] = "cl:no hit??\n";
__attribute__((section(".rodata.0x00559320"))) const char D_00559320[24] = "src:%8f %8f %8f\n";
__attribute__((section(".rodata.0x00559338"))) const char D_00559338[24] = "dst:%8f %8f %8f\n";
__attribute__((section(".rodata.0x00559350"))) const char D_00559350[24] = "%02d: src:%8f dst:%8f\n";
__attribute__((section(".rodata.0x00559400"))) const char D_00559400[32] = "MakeExitAttributeIndex() %d\n";
__attribute__((section(".rodata.0x00559420"))) const char D_00559420[16] = "attr EXIT%2d\n";
__attribute__((section(".rodata.0x00559430"))) const char D_00559430[16] = "--disconnect--\n";
__attribute__((section(".rodata.0x00559440"))) const char D_00559440[24] = "girl after func\n";
__attribute__((section(".rodata.0x00559458"))) const char D_00559458[24] = "enter actGirlHand50\n";
__attribute__((section(".rodata.0x00559470"))) const char D_00559470[24] = "girl error flg get\n";
__attribute__((section(".rodata.0x00559488"))) const char D_00559488[24] = "enter motGirlHand50\n";
__attribute__((section(".rodata.0x005594A0"))) const char D_005594A0[24] = "enter actGirlHand100\n";
__attribute__((section(".rodata.0x005594B8"))) const char D_005594B8[24] = "enter motGirlHand100\n";
__attribute__((section(".rodata.0x005594D0"))) const char D_005594D0[24] = "enter actGirlHand200\n";
__attribute__((section(".rodata.0x005594E8"))) const char D_005594E8[24] = "enter motGirlHand200\n";
__attribute__((section(".rodata.0x00559500"))) const char D_00559500[16] = "%s sync error\n";

/* String-pool rodata migrated from fieldCollision_data.c */
__attribute__((section(".rodata.0x00559208"))) const char D_00559208[56] = "TOO MANY COLLISION DEPEND GOBJS\n\000\000\000\000\000\000\000\000%s%d(%d)\n\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "壁が無いのにGetOrientOfWallが呼ばれました
" */
__attribute__((section(".rodata.0x00559368"))) const char D_00559368[48] = "\312\311\244\254\314\265\244\244\244\316\244\313GetOrientOfWall\244\254\270\306\244\320\244\354\244\336\244\267\244\277\n";
/* EUC-JP: "DOBJ無しのオブジェクトに対してGetOrientOfWallが呼ばれました
" */
__attribute__((section(".rodata.0x00559398"))) const char D_00559398[72] = "DOBJ\314\265\244\267\244\316\245\252\245\326\245\270\245\247\245\257\245\310\244\313\302\320\244\267\244\306GetOrientOfWall\244\254\270\306\244\320\244\354\244\336\244\267\244\277\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166028);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166118);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166258);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_001667E0);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166A10);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166BB0);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166E10);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167230);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167258);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167278);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167280);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167528);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167760);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_001677D0);
