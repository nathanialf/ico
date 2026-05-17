/* enemyParts.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00618DB0"))) const char D_00618DB0[24] = "src/enemyParts.c";

#include "include_asm.h"

extern void func_0010EC98(int);

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CEF90);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF288);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF548);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF6C0);

int func_001CF770(int *a0)
{
    func_0010EC98(a0[1]);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CF790);
