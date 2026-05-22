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

const char D_0061AFA0[16] = "src/act.c";
const char D_0061AFB0[24] = "intr list is null\n";
const char D_0061AFF0[16] = "LW's coord:";
const char D_0061B000[32] = "POS X:%8.2f Y:%8.2f Z:%8.2f";
const char D_0061B040[24] = "seMail: gobj buff over\n";
const char D_0061B058[16] = "index %d\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "自分のWAYが見付からなかった" */
const char D_0061B068[32] = "\274\253\312\254\244\316WAY\244\254\270\253\311\325\244\253\244\351\244\312\244\253\244\303\244\277";

const char D_0061B088[32] = "srh wp %p group id %d %d\n";
const char D_0061B0A8[16] = "active %d\n";
const char D_0061B0B8[32] = "add no bridge wp %p %d %d\n";
const char D_0061B0D8[24] = "add bridge wp %p %d %d\n";
/* EUC-JP: "見付からないので全WAYPOOINTから アクティブグループで巣許可の一番近いポイントを検索" */
const char D_0061B0F0[88] = "\270\253\311\325\244\253\244\351\244\312\244\244\244\316\244\307\301\264WAYPOOINT\244\253\244\351 \245\242\245\257\245\306\245\243\245\326\245\260\245\353\241\274\245\327\244\307\301\343\265\366\262\304\244\316\260\354\310\326\266\341\244\244\245\335\245\244\245\363\245\310\244\362\270\241\272\367";
/* EUC-JP: "アクティブグループの巣許可のポイントがみつかりません" */
const char D_0061B148[56] = "\245\242\245\257\245\306\245\243\245\326\245\260\245\353\241\274\245\327\244\316\301\343\265\366\262\304\244\316\245\335\245\244\245\363\245\310\244\254\244\337\244\304\244\253\244\352\244\336\244\273\244\363";
const char D_0061B180[48] = "WayPointCreateNewBridge: way group not create\n";
const char D_0061B1B0[16] = "bidir wp:%p\n";
const char D_0061B1C0[16] = "group + create";
const char D_0061B1D0[16] = "search:%p %p\n";
const char D_0061B1E0[24] = "create waypoint %d\n";
const char D_0061B1F8[16] = "63 ( -)  ";
const char D_0061B208[16] = "62 ( -)  ";
const char D_0061B218[16] = "61 ( -)  ";
const char D_0061B228[16] = "60 ( -)  ";
const char D_0061B238[16] = "59 ( -)  ";
const char D_0061B248[16] = "58 ( -)  ";
const char D_0061B258[16] = "57 ( -)  ";
const char D_0061B268[16] = "56 ( -)  ";
const char D_0061B278[16] = "55 ( -)  ";
const char D_0061B288[16] = "54 ( -)  ";
const char D_0061B298[16] = "53 ( -)  ";
const char D_0061B2A8[16] = "52 ( -)  ";
const char D_0061B2B8[16] = "51 ( -)  ";
const char D_0061B2C8[16] = "50 ( -)  ";
const char D_0061B2D8[16] = "49 ( -)  ";
const char D_0061B2E8[16] = "48 ( -)  ";
const char D_0061B2F8[16] = "47 ( -)  ";
const char D_0061B308[16] = "46 ( -)  ";
const char D_0061B318[16] = "45 ( -)  ";
const char D_0061B328[16] = "44 ( -)  ";
const char D_0061B338[16] = "43 ( -)  ";
const char D_0061B348[16] = "42 ( -)  ";
const char D_0061B358[16] = "41 ( -)  ";
const char D_0061B368[16] = "40 ( -)  ";
const char D_0061B378[16] = "39 ( -)  ";
const char D_0061B388[16] = "38 ( -)  ";
const char D_0061B398[16] = "37 ( -)  ";
const char D_0061B3A8[16] = "36 ( -)  ";
const char D_0061B3B8[16] = "35 ( -)  ";
const char D_0061B3C8[16] = "34 ( -)  ";
const char D_0061B3D8[16] = "33 ( -)  ";
const char D_0061B3E8[16] = "32 ( -)  ";
const char D_0061B3F8[16] = "31 ( -)  ";
const char D_0061B408[16] = "30 ( -)  ";
const char D_0061B418[16] = "29 ( -)  ";
const char D_0061B428[16] = "28 ( -)  ";
const char D_0061B438[16] = "27 ( -)  ";
const char D_0061B448[16] = "26 ( -)  ";
const char D_0061B458[16] = "25 ( -)  ";
const char D_0061B468[16] = "24 ( -)  ";
const char D_0061B478[16] = "23 ( -)  ";
const char D_0061B488[16] = "22 ( -)  ";
const char D_0061B498[16] = "21 ( -)  ";
const char D_0061B4A8[16] = "20 ( -)  ";
const char D_0061B4B8[16] = "19 ( -)  ";
const char D_0061B4C8[16] = "18 ( -)  ";
const char D_0061B4D8[16] = "17 ( -)  ";
const char D_0061B4E8[16] = "16 ( -)  ";
const char D_0061B4F8[16] = "15 ( -)  ";
const char D_0061B508[16] = "14 ( -)  ";
const char D_0061B518[16] = "13 ( -)  ";
const char D_0061B528[16] = "12 ( -)  ";
const char D_0061B538[16] = "11 ( -)  ";
const char D_0061B548[16] = "10 ( -)  ";
const char D_0061B558[16] = " 9 ( -)  ";
const char D_0061B568[16] = " 8 ( -)  ";
const char D_0061B578[16] = " 7 ( -)  ";
const char D_0061B588[16] = " 6 ( -)  ";
const char D_0061B598[16] = " 5 ( -)  ";
const char D_0061B5A8[16] = " 4 ( -)  ";
const char D_0061B5B8[16] = " 3 ( -)  ";
const char D_0061B5C8[16] = " 2 ( -)  ";
const char D_0061B5D8[16] = " 1 ( -)  ";
const char D_0061B5E8[16] = " 0 ( -)  ";
const char D_0061B5F8[16] = "% 2d (% 2d) ";
const char D_0061B608[16] = "group + select";
const char D_0061B618[16] = "point + delete\n";
const char D_0061B628[24] = "delete waypoint %d\n";
const char D_0061B640[16] = "point + insert\n";
const char D_0061B650[24] = "insert waypoint %d\n";
const char D_0061B668[16] = "point + nige\n";
const char D_0061B678[24] = "cannot save wp file";
const char D_0061B690[24] = "cannot load wp file\n";
const char D_0061B6A8[24] = "cannot open file";
const char D_0061B6C0[16] = "equn\t\t%s_start\n";
const char D_0061B6D0[48] = "\t%d\t%d\t%s_%d_start\t%s_%d_end\t%d\t%d\t%d\t%d\n";
const char D_0061B700[16] = "equn\t\t%s_end\n";
const char D_0061B710[24] = "equn\t%s_%d_start\n";
const char D_0061B728[24] = "\t\t\t%d\t%d\t%d\t\t%d\t%d\n";
const char D_0061B740[16] = "equn\t%s_%d_end\n";
const char D_0061B750[16] = "save text";
const char D_0061B760[16] = "quick load";
const char D_0061B770[16] = "quick save";
const char D_0061B780[16] = "      + nige";
const char D_0061B790[16] = "      + insert";
const char D_0061B7A0[16] = "point + delete";
const char D_0061B7B0[16] = "      + select";

/* rodata migrated from act_data.c — plain defs, no section attr. */

/* 4 × 24-byte fixed-width log lines packed contiguously
 * (one EUC-JP + three ASCII), kept as one symbol matching the
 * original. C string concatenation joins all four; explicit
 * \0 escapes pad each block to its 24-byte slot.
 * EUC-JP: "ルートがありません\n" (route not found) */
const char D_0061AE50[96] =
    "\245\353\241\274\245\310\244\254\244\242\244\352\244\336\244\273\244\363\n\0\0\0\0\0"
    "WBP set [height]\n\0\0\0\0\0\0\0"
    "WBP recheck first\0\0\0\0\0\0\0"
    "WBP recheck second\0\0\0\0\0";

const int D_0061AFC8[6] = { 0, 1, 0, 1, 0, 0 };
const unsigned char D_0061AFE0[16] = {
    0x20, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00,
    0xFF, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00,
};
const int D_0061B020[8] = { 0x80, 0x80, 0x80, 0x80, 0x00, 0x40, 0xFF, 0x80 };

/* lit4 migrated from act_data.c — typed floats, no section attr. */
const float D_00631478[1] = { 3.14159274f };       /* π */
const float D_0063147C    = 10000.0f;
const float D_00631480[1] = { 40000.0f };
const float D_00631484    = 0.001f;
const float D_00631488[1] = { 10000.0f };
const float D_0063148C    = 10000.0f;
const float D_00631490[1] = { 10000.0f };
const float D_00631494    = 10000.0f;
const float D_00631498[1] = { 1.0e10f };

/* sdata migrated from act_data.c — natural .sdata defaults preserve VMA.
 * D_00632274 stays in the sidecar (has 8-byte _pad_00632278 trailing
 * gap that the migrator can only emit when the parent is sidecar-side). */
int D_00632DAC = 0;
unsigned char D_00632DB0[4] = { 0 };
int D_0063385C = 0;
unsigned char D_00633860[4] = { 0 };
int D_00633864 = 0;
float D_00633868[1] = { 3.4028235e38f };           /* FLT_MAX */
int D_0063386C = 0;

/* data migrated from act_data.c — small typed entries. Giant blobs
 * (D_002B0000/D_002C0000/D_002D0000 = 64KB each, D_002E0000 = ~20KB,
 * D_004CAEE8 = ~19KB) remain in the auto-regenerated sidecar. */

/* 11 floats: initial 1.0 scale {x,y,z} + 8 zero pad fields. */
float D_002A4C48[11] = {
    1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
/* D_002A4C74, D_002E4D64, D_004CAE8C, D_004CC1A4 remain in the
 * sidecar — each scalar's data extent runs to the next symbol's VMA
 * (covering a trailing _pad_<VMA> gap chunk), and the migrator can
 * only emit that pad when the parent symbol is also sidecar-side. */

int D_004CAE10[4] = { 75, -75, 0, 0 };
int D_004CAE20[27] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0,
};
float D_004CAEA0[8] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    3.4028235e38f, 3.4028235e38f,                  /* FLT_MAX, FLT_MAX */
};
unsigned char D_004CAEC8[16] = { 0 };
unsigned char D_004CAEE0[8] = { 0 };
unsigned char D_004CC1A0[4] = { 0 };

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/act", func_00202148);
INCLUDE_ASM("asm/nonmatchings/src/act", func_00202208);
INCLUDE_ASM("asm/nonmatchings/src/act", func_002025E0);
INCLUDE_ASM("asm/nonmatchings/src/act", func_002027C8);
INCLUDE_ASM("asm/nonmatchings/src/act", func_00202A60);
INCLUDE_ASM("asm/nonmatchings/src/act", func_00203130);

void func_00203910(void) {}

INCLUDE_ASM("asm/nonmatchings/src/act", func_00203918);
