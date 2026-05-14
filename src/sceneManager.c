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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".sdata.0x00633190"))) const char D_00633190[8] = "0";
__attribute__((section(".sdata.0x00633198"))) int D_00633198 = 0;
__attribute__((section(".sdata.0x0063319C"))) int D_0063319C = 0;
__attribute__((section(".sdata.0x006331A0"))) char D_006331A0[8] = { 0 };

__attribute__((section(".rodata.0x006172E0"))) const char D_006172E0[24] = "src/sceneManager.c";

/* String rodata migrated from sceneManager_data.c */
__attribute__((section(".rodata.0x006172F8"))) const char D_006172F8[16] = "Parentize \"%s\"\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: ""%s"の親子関係づけをしようとしましたが、自分を親にしようとしています。
" */
__attribute__((section(".rodata.0x00617298"))) const char D_00617298[72] = "\"%s\"\244\316\277\306\273\322\264\330\267\270\244\305\244\261\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\244\254\241\242\274\253\312\254\244\362\277\306\244\313\244\267\244\350\244\246\244\310\244\267\244\306\244\244\244\336\244\271\241\243\n";
/* EUC-JP: ""%s"の親子関係づけをしようとしましたが、親が見つかりません。
" */
__attribute__((section(".rodata.0x00617308"))) const char D_00617308[64] = "\"%s\"\244\316\277\306\273\322\264\330\267\270\244\305\244\261\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\244\254\241\242\277\306\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\241\243\n";
