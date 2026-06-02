/* cage.c -- typed sdata / lit4 definitions for this TU.
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

/* lit4 defs live in the gitignored cage_data.c sidecar so the cage.o
 * doesn't co-locate them with INCLUDE_ASM consumers that reach them
 * via %gp_rel (memory lit4_gp_rel_extern). */
extern float D_006311E4, D_006311E8, D_006311EC, D_006311F0;
extern float D_006311F4, D_006311F8, D_006311FC, D_00631200;

const char D_00618848[16] = "src/cage.c";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/cage", func_001C2338);
INCLUDE_ASM("asm/nonmatchings/src/cage", func_001C2760);
INCLUDE_ASM("asm/nonmatchings/src/cage", func_001C28D0);
