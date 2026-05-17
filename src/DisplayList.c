/* DisplayList.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x0061AB88"))) const char D_0061AB88[24] = "src/DisplayList.c";

/* String rodata migrated from DisplayList_data.c */
__attribute__((section(".rodata.0x0061ABA0"))) const char D_0061ABA0[40] = "dl_PushPriority:Stack Overflow.\n";
__attribute__((section(".rodata.0x0061ABC8"))) const char D_0061ABC8[40] = "dl_PopPriority:Stack Underflow.\n";

/* String-pool rodata migrated from DisplayList_data.c */
__attribute__((section(".rodata.0x0061ABF0"))) const char D_0061ABF0[80] = "dldma %d\n\000\000\000\000\000\000\000dl_CheckDLOverflow:Display List Buffer [%d] Full.\n\000\000\000\000\000\000\000\000\000\000\000\000\000";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB4C4);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB4C8);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB5E0);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB658);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB768);
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB7F8);
