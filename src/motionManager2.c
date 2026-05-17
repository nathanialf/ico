/* motionManager2.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_0063097C;
extern float D_00630980;
extern const char D_00631B50[8];
extern unsigned int D_00631B58;
extern unsigned int D_00631B5C;

__attribute__((section(".rodata.0x00553CA0"))) const char D_00553CA0[24] = "src/motionManager2.c";

/* String rodata migrated from motionManager2_data.c */
__attribute__((section(".rodata.0x00553D70"))) const char D_00553D70[64] = "Illegal compress formatID(%d) appeard... ignore.\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "AdjustRootPositionToVerticalSidePlaneOfWallが壁の中に突入させようとしたのでクリップしました
" */
__attribute__((section(".rodata.0x00553CB8"))) const char D_00553CB8[96] = "AdjustRootPositionToVerticalSidePlaneOfWall\244\254\312\311\244\316\303\346\244\313\306\315\306\376\244\265\244\273\244\350\244\246\244\310\244\267\244\277\244\316\244\307\245\257\245\352\245\303\245\327\244\267\244\336\244\267\244\277\n";
/* EUC-JP: "AdjustVerticalSidePlaneOfWall:垂直壁が近接しているので補正位置をその中点としました
" */
__attribute__((section(".rodata.0x00553D18"))) const char D_00553D18[88] = "AdjustVerticalSidePlaneOfWall:\277\342\304\276\312\311\244\254\266\341\300\334\244\267\244\306\244\244\244\353\244\316\244\307\312\344\300\265\260\314\303\326\244\362\244\275\244\316\303\346\305\300\244\310\244\267\244\336\244\267\244\277\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", func_00107B28);
