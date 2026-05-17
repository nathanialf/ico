/* Primitive.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00555490"))) const char D_00555490[16] = "src/Primitive.c";

/* String rodata migrated from Primitive_data.c */
__attribute__((section(".rodata.0x005554B0"))) const char D_005554B0[32] = "too large mesh packet. %d\n";
__attribute__((section(".rodata.0x00555500"))) const char D_00555500[72] = "Particle Object too big (%d particles). (must be under %d particles)\n";
__attribute__((section(".rodata.0x00555548"))) const char D_00555548[48] = "prim_InitParticle:illegal texture no. %s:%d\n";

/* Float rodata migrated from Primitive_data.c */
__attribute__((section(".rodata.0x005554E0"))) const float D_005554E0[4] = { 1024.0f, 1024.0f, 0.0f, 1.0f };
__attribute__((section(".rodata.0x005554F0"))) const float D_005554F0[4] = { 3071.0f, 3071.0f, 0.0f, 16777215.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "prim_DispParticle:指定したテクスチャ番号が異常です. %s:%d
" */
__attribute__((section(".rodata.0x00555578"))) const char D_00555578[64] = "prim_DispParticle:\273\330\304\352\244\267\244\277\245\306\245\257\245\271\245\301\245\343\310\326\271\346\244\254\260\333\276\357\244\307\244\271. %s:%d\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C028);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C2B8);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C500);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C868);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011CBF8);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011CE90);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D2E8);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D590);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D658);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D730);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D800);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D9A0);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011DD08);
