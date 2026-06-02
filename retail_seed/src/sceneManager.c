/* sceneManager.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00633190[8];
extern int D_00633198;
extern int D_0063319C;
extern char D_006331A0[8];

/* EUC-JP: ""%s"の親子関係づけをしようとしましたが、自分を親にしようとしています。\n" */
const char D_00617298[72] = "\"%s\"\244\316\277\306\273\322\264\330\267\270\244\305\244\261\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\244\254\241\242\274\253\312\254\244\362\277\306\244\313\244\267\244\350\244\246\244\310\244\267\244\306\244\244\244\336\244\271\241\243\n";

/* String rodata migrated from sceneManager_data.c */
const char D_006172E0[24] = "src/sceneManager.c";

/* String rodata migrated from sceneManager_data.c */
const char D_006172F8[16] = "Parentize \"%s\"\n";

/* String rodata migrated from sceneManager_data.c */
/* EUC-JP: ""%s"の親子関係づけをしようとしましたが、親が見つかりません。\n" */
const char D_00617308[64] = "\"%s\"\244\316\277\306\273\322\264\330\267\270\244\305\244\261\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\244\254\241\242\277\306\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/sceneManager", func_001B7B88);
