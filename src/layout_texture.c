/* layout_texture.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00633178[8];
extern const char D_00633180[8];
extern int D_00633188;
extern unsigned int D_0063318C;

__attribute__((section(".rodata.0x00617218"))) const char D_00617218[24] = "src/layout_texture.c";

/* String rodata migrated from layout_texture_data.c */
__attribute__((section(".rodata.0x00617200"))) const char D_00617200[24] = "no texture loaded.(%s)\n";
__attribute__((section(".rodata.0x00617260"))) const char D_00617260[56] = "try layout index=[%d] model_id=[%d]------------\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "ステージ情報にエクセルのデータを使用します.
" */
__attribute__((section(".rodata.0x00617230"))) const char D_00617230[48] = "\245\271\245\306\241\274\245\270\276\360\312\363\244\313\245\250\245\257\245\273\245\353\244\316\245\307\241\274\245\277\244\362\273\310\315\321\244\267\244\336\244\271.\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B6CD0);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B6E58);
INCLUDE_ASM("asm/nonmatchings/src/layout_texture", func_001B6FD8);
