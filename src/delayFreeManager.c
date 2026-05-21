/* delayFreeManager.c -- typed sdata / lit4 definitions for this TU.
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

/* sdata defs co-located with %gp_rel consumers moved to gitignored
 * delayFreeManager_data.c sidecar (memory lit4_gp_rel_extern). */
extern int D_00631B20, D_00631B24;
extern const char D_00631B28[8];

__attribute__((section(".rodata.0x00553AB8"))) const char D_00553AB8[24] = "src/delayFreeManager.c";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102558);
INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_001025E8);
INCLUDE_ASM("asm/nonmatchings/src/delayFreeManager", func_00102680);

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "VSYNC_TIMING    : <ESC>[33m%s<ESC>[m<LF>" */
__attribute__((section(".rodata.0x005538A0"))) const char D_005538A0[32] = "VSYNC_TIMING    : \033[33m%s\033[m\n";
/* ASCII preview: "FRAME_STEP      : <ESC>[33m%d<ESC>[m<LF>" */
__attribute__((section(".rodata.0x005538C0"))) const char D_005538C0[32] = "FRAME_STEP      : \033[33m%d\033[m\n";
/* ASCII preview: "SYSTEM_FRAMERATE: <ESC>[33m%d<ESC>[m<LF>" */
__attribute__((section(".rodata.0x005538E0"))) const char D_005538E0[32] = "SYSTEM_FRAMERATE: \033[33m%d\033[m\n";
/* ASCII preview: "<ESC>[33mERROR!!! TOO MANY DELAY FREE LIST ENTRY!!! EXIT...<ESC>[m<LF>" */
__attribute__((section(".rodata.0x00553A78"))) const char D_00553A78[64] = "\033[33mERROR!!! TOO MANY DELAY FREE LIST ENTRY!!! EXIT...\033[m\n";
