/* fightSound.c -- typed sdata / lit4 definitions for this TU.
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

/* D_00632784 is gp_rel-reached by func_00191F50; D_00632788/90 sit in
 * the same neighborhood so extern them too (memory lit4_gp_rel_extern). */
extern int D_00632784;
extern char D_00632788[8];
extern const char D_00632790[8];

__attribute__((section(".rodata.0x0055AE88"))) const char D_0055AE88[24] = "src/fightSound.c";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/fightSound", func_00191F50);
