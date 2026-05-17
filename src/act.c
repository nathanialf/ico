/* act.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x0061AFA0"))) const char D_0061AFA0[16] = "src/act.c";

__attribute__((section(".rodata.0x0061AFF0"))) const char D_0061AFF0[16] = "LW's coord:";
__attribute__((section(".rodata.0x0061B000"))) const char D_0061B000[32] = "POS X:%8.2f Y:%8.2f Z:%8.2f";
__attribute__((section(".rodata.0x0061B1C0"))) const char D_0061B1C0[16] = "group + create";
__attribute__((section(".rodata.0x0061B1F8"))) const char D_0061B1F8[16] = "63 ( -)  ";
__attribute__((section(".rodata.0x0061B208"))) const char D_0061B208[16] = "62 ( -)  ";
__attribute__((section(".rodata.0x0061B218"))) const char D_0061B218[16] = "61 ( -)  ";
__attribute__((section(".rodata.0x0061B228"))) const char D_0061B228[16] = "60 ( -)  ";
__attribute__((section(".rodata.0x0061B238"))) const char D_0061B238[16] = "59 ( -)  ";
__attribute__((section(".rodata.0x0061B248"))) const char D_0061B248[16] = "58 ( -)  ";
__attribute__((section(".rodata.0x0061B258"))) const char D_0061B258[16] = "57 ( -)  ";
__attribute__((section(".rodata.0x0061B268"))) const char D_0061B268[16] = "56 ( -)  ";
__attribute__((section(".rodata.0x0061B278"))) const char D_0061B278[16] = "55 ( -)  ";
__attribute__((section(".rodata.0x0061B288"))) const char D_0061B288[16] = "54 ( -)  ";
__attribute__((section(".rodata.0x0061B298"))) const char D_0061B298[16] = "53 ( -)  ";
__attribute__((section(".rodata.0x0061B2A8"))) const char D_0061B2A8[16] = "52 ( -)  ";
__attribute__((section(".rodata.0x0061B2B8"))) const char D_0061B2B8[16] = "51 ( -)  ";
__attribute__((section(".rodata.0x0061B2C8"))) const char D_0061B2C8[16] = "50 ( -)  ";
__attribute__((section(".rodata.0x0061B2D8"))) const char D_0061B2D8[16] = "49 ( -)  ";
__attribute__((section(".rodata.0x0061B2E8"))) const char D_0061B2E8[16] = "48 ( -)  ";
__attribute__((section(".rodata.0x0061B2F8"))) const char D_0061B2F8[16] = "47 ( -)  ";
__attribute__((section(".rodata.0x0061B308"))) const char D_0061B308[16] = "46 ( -)  ";
__attribute__((section(".rodata.0x0061B318"))) const char D_0061B318[16] = "45 ( -)  ";
__attribute__((section(".rodata.0x0061B328"))) const char D_0061B328[16] = "44 ( -)  ";
__attribute__((section(".rodata.0x0061B338"))) const char D_0061B338[16] = "43 ( -)  ";
__attribute__((section(".rodata.0x0061B348"))) const char D_0061B348[16] = "42 ( -)  ";
__attribute__((section(".rodata.0x0061B358"))) const char D_0061B358[16] = "41 ( -)  ";
__attribute__((section(".rodata.0x0061B368"))) const char D_0061B368[16] = "40 ( -)  ";
__attribute__((section(".rodata.0x0061B378"))) const char D_0061B378[16] = "39 ( -)  ";
__attribute__((section(".rodata.0x0061B388"))) const char D_0061B388[16] = "38 ( -)  ";
__attribute__((section(".rodata.0x0061B398"))) const char D_0061B398[16] = "37 ( -)  ";
__attribute__((section(".rodata.0x0061B3A8"))) const char D_0061B3A8[16] = "36 ( -)  ";
__attribute__((section(".rodata.0x0061B3B8"))) const char D_0061B3B8[16] = "35 ( -)  ";
__attribute__((section(".rodata.0x0061B3C8"))) const char D_0061B3C8[16] = "34 ( -)  ";
__attribute__((section(".rodata.0x0061B3D8"))) const char D_0061B3D8[16] = "33 ( -)  ";
__attribute__((section(".rodata.0x0061B3E8"))) const char D_0061B3E8[16] = "32 ( -)  ";
__attribute__((section(".rodata.0x0061B3F8"))) const char D_0061B3F8[16] = "31 ( -)  ";
__attribute__((section(".rodata.0x0061B408"))) const char D_0061B408[16] = "30 ( -)  ";
__attribute__((section(".rodata.0x0061B418"))) const char D_0061B418[16] = "29 ( -)  ";
__attribute__((section(".rodata.0x0061B428"))) const char D_0061B428[16] = "28 ( -)  ";
__attribute__((section(".rodata.0x0061B438"))) const char D_0061B438[16] = "27 ( -)  ";
__attribute__((section(".rodata.0x0061B448"))) const char D_0061B448[16] = "26 ( -)  ";
__attribute__((section(".rodata.0x0061B458"))) const char D_0061B458[16] = "25 ( -)  ";
__attribute__((section(".rodata.0x0061B468"))) const char D_0061B468[16] = "24 ( -)  ";
__attribute__((section(".rodata.0x0061B478"))) const char D_0061B478[16] = "23 ( -)  ";
__attribute__((section(".rodata.0x0061B488"))) const char D_0061B488[16] = "22 ( -)  ";
__attribute__((section(".rodata.0x0061B498"))) const char D_0061B498[16] = "21 ( -)  ";
__attribute__((section(".rodata.0x0061B4A8"))) const char D_0061B4A8[16] = "20 ( -)  ";
__attribute__((section(".rodata.0x0061B4B8"))) const char D_0061B4B8[16] = "19 ( -)  ";
__attribute__((section(".rodata.0x0061B4C8"))) const char D_0061B4C8[16] = "18 ( -)  ";
__attribute__((section(".rodata.0x0061B4D8"))) const char D_0061B4D8[16] = "17 ( -)  ";
__attribute__((section(".rodata.0x0061B4E8"))) const char D_0061B4E8[16] = "16 ( -)  ";
__attribute__((section(".rodata.0x0061B4F8"))) const char D_0061B4F8[16] = "15 ( -)  ";
__attribute__((section(".rodata.0x0061B508"))) const char D_0061B508[16] = "14 ( -)  ";
__attribute__((section(".rodata.0x0061B518"))) const char D_0061B518[16] = "13 ( -)  ";
__attribute__((section(".rodata.0x0061B528"))) const char D_0061B528[16] = "12 ( -)  ";
__attribute__((section(".rodata.0x0061B538"))) const char D_0061B538[16] = "11 ( -)  ";
__attribute__((section(".rodata.0x0061B548"))) const char D_0061B548[16] = "10 ( -)  ";
__attribute__((section(".rodata.0x0061B558"))) const char D_0061B558[16] = " 9 ( -)  ";
__attribute__((section(".rodata.0x0061B568"))) const char D_0061B568[16] = " 8 ( -)  ";
__attribute__((section(".rodata.0x0061B578"))) const char D_0061B578[16] = " 7 ( -)  ";
__attribute__((section(".rodata.0x0061B588"))) const char D_0061B588[16] = " 6 ( -)  ";
__attribute__((section(".rodata.0x0061B598"))) const char D_0061B598[16] = " 5 ( -)  ";
__attribute__((section(".rodata.0x0061B5A8"))) const char D_0061B5A8[16] = " 4 ( -)  ";
__attribute__((section(".rodata.0x0061B5B8"))) const char D_0061B5B8[16] = " 3 ( -)  ";
__attribute__((section(".rodata.0x0061B5C8"))) const char D_0061B5C8[16] = " 2 ( -)  ";
__attribute__((section(".rodata.0x0061B5D8"))) const char D_0061B5D8[16] = " 1 ( -)  ";
__attribute__((section(".rodata.0x0061B5E8"))) const char D_0061B5E8[16] = " 0 ( -)  ";
__attribute__((section(".rodata.0x0061B5F8"))) const char D_0061B5F8[16] = "% 2d (% 2d) ";
__attribute__((section(".rodata.0x0061B608"))) const char D_0061B608[16] = "group + select";
__attribute__((section(".rodata.0x0061B678"))) const char D_0061B678[24] = "cannot save wp file";
__attribute__((section(".rodata.0x0061B6A8"))) const char D_0061B6A8[24] = "cannot open file";
__attribute__((section(".rodata.0x0061B750"))) const char D_0061B750[16] = "save text";
__attribute__((section(".rodata.0x0061B760"))) const char D_0061B760[16] = "quick load";
__attribute__((section(".rodata.0x0061B770"))) const char D_0061B770[16] = "quick save";
__attribute__((section(".rodata.0x0061B780"))) const char D_0061B780[16] = "      + nige";
__attribute__((section(".rodata.0x0061B790"))) const char D_0061B790[16] = "      + insert";
__attribute__((section(".rodata.0x0061B7A0"))) const char D_0061B7A0[16] = "point + delete";
__attribute__((section(".rodata.0x0061B7B0"))) const char D_0061B7B0[16] = "      + select";

/* String rodata migrated from act_data.c */
__attribute__((section(".rodata.0x0061AFB0"))) const char D_0061AFB0[24] = "intr list is null\n";
__attribute__((section(".rodata.0x0061B040"))) const char D_0061B040[24] = "seMail: gobj buff over\n";
__attribute__((section(".rodata.0x0061B058"))) const char D_0061B058[16] = "index %d\n";
__attribute__((section(".rodata.0x0061B088"))) const char D_0061B088[32] = "srh wp %p group id %d %d\n";
__attribute__((section(".rodata.0x0061B0A8"))) const char D_0061B0A8[16] = "active %d\n";
__attribute__((section(".rodata.0x0061B0B8"))) const char D_0061B0B8[32] = "add no bridge wp %p %d %d\n";
__attribute__((section(".rodata.0x0061B0D8"))) const char D_0061B0D8[24] = "add bridge wp %p %d %d\n";
__attribute__((section(".rodata.0x0061B180"))) const char D_0061B180[48] = "WayPointCreateNewBridge: way group not create\n";
__attribute__((section(".rodata.0x0061B1B0"))) const char D_0061B1B0[16] = "bidir wp:%p\n";
__attribute__((section(".rodata.0x0061B1D0"))) const char D_0061B1D0[16] = "search:%p %p\n";
__attribute__((section(".rodata.0x0061B1E0"))) const char D_0061B1E0[24] = "create waypoint %d\n";
__attribute__((section(".rodata.0x0061B618"))) const char D_0061B618[16] = "point + delete\n";
__attribute__((section(".rodata.0x0061B628"))) const char D_0061B628[24] = "delete waypoint %d\n";
__attribute__((section(".rodata.0x0061B640"))) const char D_0061B640[16] = "point + insert\n";
__attribute__((section(".rodata.0x0061B650"))) const char D_0061B650[24] = "insert waypoint %d\n";
__attribute__((section(".rodata.0x0061B668"))) const char D_0061B668[16] = "point + nige\n";
__attribute__((section(".rodata.0x0061B690"))) const char D_0061B690[24] = "cannot load wp file\n";
__attribute__((section(".rodata.0x0061B6C0"))) const char D_0061B6C0[16] = "equn\t\t%s_start\n";
__attribute__((section(".rodata.0x0061B6D0"))) const char D_0061B6D0[48] = "\t%d\t%d\t%s_%d_start\t%s_%d_end\t%d\t%d\t%d\t%d\n";
__attribute__((section(".rodata.0x0061B700"))) const char D_0061B700[16] = "equn\t\t%s_end\n";
__attribute__((section(".rodata.0x0061B710"))) const char D_0061B710[24] = "equn\t%s_%d_start\n";
__attribute__((section(".rodata.0x0061B728"))) const char D_0061B728[24] = "\t\t\t%d\t%d\t%d\t\t%d\t%d\n";
__attribute__((section(".rodata.0x0061B740"))) const char D_0061B740[16] = "equn\t%s_%d_end\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "自分のWAYが見付からなかった" */
__attribute__((section(".rodata.0x0061B068"))) const char D_0061B068[32] = "\274\253\312\254\244\316WAY\244\254\270\253\311\325\244\253\244\351\244\312\244\253\244\303\244\277";
/* EUC-JP: "見付からないので全WAYPOOINTから アクティブグループで巣許可の一番近いポイントを検索" */
__attribute__((section(".rodata.0x0061B0F0"))) const char D_0061B0F0[88] = "\270\253\311\325\244\253\244\351\244\312\244\244\244\316\244\307\301\264WAYPOOINT\244\253\244\351 \245\242\245\257\245\306\245\243\245\326\245\260\245\353\241\274\245\327\244\307\301\343\265\366\262\304\244\316\260\354\310\326\266\341\244\244\245\335\245\244\245\363\245\310\244\362\270\241\272\367";
/* EUC-JP: "アクティブグループの巣許可のポイントがみつかりません" */
__attribute__((section(".rodata.0x0061B148"))) const char D_0061B148[56] = "\245\242\245\257\245\306\245\243\245\326\245\260\245\353\241\274\245\327\244\316\301\343\265\366\262\304\244\316\245\335\245\244\245\363\245\310\244\254\244\337\244\304\244\253\244\352\244\336\244\273\244\363";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/act", func_00202148);
INCLUDE_ASM("asm/nonmatchings/src/act", func_00202208);
INCLUDE_ASM("asm/nonmatchings/src/act", func_002025E0);
INCLUDE_ASM("asm/nonmatchings/src/act", func_002027C8);
INCLUDE_ASM("asm/nonmatchings/src/act", func_00202A60);
INCLUDE_ASM("asm/nonmatchings/src/act", func_00203130);

void func_00203910(void) {}

INCLUDE_ASM("asm/nonmatchings/src/act", func_00203918);
