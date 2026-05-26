/* spider.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_006313D0;
extern float D_006313D4;
extern float D_006313D8;
extern float D_006313DC;

const char D_0061A040[16] = "src/spider.c";

/* EUC-JP: "親のいる蜘蛛グループを起こそうとしました。これは無効です\n" */
const char D_0061A050[64] = "\277\306\244\316\244\244\244\353\303\330\351\341\245\260\245\353\241\274\245\327\244\362\265\257\244\263\244\275\244\246\244\310\244\267\244\336\244\267\244\277\241\243\244\263\244\354\244\317\314\265\270\372\244\307\244\271\n";

/* EUC-JP: "蜘蛛グループを起こそうとしましたが、表に親が書かれていません。これは無効です\n" */
const char D_0061A090[80] = "\303\330\351\341\245\260\245\353\241\274\245\327\244\362\265\257\244\263\244\275\244\246\244\310\244\267\244\336\244\267\244\277\244\254\241\242\311\275\244\313\277\306\244\254\275\361\244\253\244\354\244\306\244\244\244\336\244\273\244\363\241\243\244\263\244\354\244\317\314\265\270\372\244\307\244\271\n";

/* EUC-JP: "蜘蛛のターゲットをヒロインにせよと言う命令がありましたが\nこのステージにヒロインはいません。\n" */
const char D_0061A0E0[96] = "\303\330\351\341\244\316\245\277\241\274\245\262\245\303\245\310\244\362\245\322\245\355\245\244\245\363\244\313\244\273\244\350\244\310\270\300\244\246\314\277\316\341\244\254\244\242\244\352\244\336\244\267\244\277\244\254\n\244\263\244\316\245\271\245\306\241\274\245\270\244\313\245\322\245\355\245\244\245\363\244\317\244\244\244\336\244\273\244\363\241\243\n";

const char D_0061A140[16] = "entry %d\n";

const char D_0061A150[32] = "entry revived %d\n";

const char D_0061A188[16] = "%c SE:%s AI:%s";

const char D_0061A198[16] = "restore: %p\n";

const char D_0061A1A8[16] = "     WAKE: %s\n";

const char D_0061A1B8[16] = "    ALIVE: %d\n";

const char D_0061A1C8[16] = "   REVIVE: %d\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA278);
INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA3E0);
INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA480);
INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA5E8);
INCLUDE_ASM("asm/nonmatchings/src/spider", func_001EA9C8);
