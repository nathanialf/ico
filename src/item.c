/* item.c -- typed sdata / lit4 definitions for this TU.
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


/* EUC-JP: "小樽を見失ったのにつかもうとしてます。\n" */
const char D_00618F40[40] = "\276\256\303\256\244\362\270\253\274\272\244\303\244\277\244\316\244\313\244\304\244\253\244\342\244\246\244\310\244\267\244\306\244\336\244\271\241\243\n";

const char D_00618F68[16] = "src/item.c";

/* EUC-JP: "緊急停止2(%f←%f)\n" */
const char D_00618F78[24] = "\266\333\265\336\304\344\273\3372(%f\242\253%f)\n";

/* EUC-JP: "緊急停止3\n" */
const char D_00618F90[16] = "\266\333\265\336\304\344\273\3373\n";

/* EUC-JP: "振動睡眠\n" */
const char D_00618FA0[16] = "\277\266\306\260\277\347\314\262\n";

/* EUC-JP: "爆発アニメーション停止処理予定\n" */
const char D_00618FC8[32] = "\307\372\310\257\245\242\245\313\245\341\241\274\245\267\245\347\245\363\304\344\273\337\275\350\315\375\315\275\304\352\n";

const char D_00618FE8[16] = "GAMEMODE LOW0";

const char D_00618FF8[16] = "GAMEMODE LOW";

const char D_00619008[16] = "GAMEMODE HIGH";

const char D_00619018[16] = "DEMO MODE";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/item", func_001D2550);
INCLUDE_ASM("asm/nonmatchings/src/item", func_001D2650);
INCLUDE_ASM("asm/nonmatchings/src/item", func_001D26C8);
INCLUDE_ASM("asm/nonmatchings/src/item", func_001D2738);
INCLUDE_ASM("asm/nonmatchings/src/item", func_001D27A8);
