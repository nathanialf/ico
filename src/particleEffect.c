/* particleEffect.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00619E08"))) const char D_00619E08[24] = "src/particleEffect.c";

__attribute__((section(".rodata.0x00619DF8"))) const char D_00619DF8[16] = "enemy_tex01";

/* String rodata migrated from particleEffect_data.c */
__attribute__((section(".rodata.0x00619DE0"))) const char D_00619DE0[24] = "PARTICLE EFFECT WRONG\n";
__attribute__((section(".rodata.0x00619E20"))) const char D_00619E20[32] = "No more effect... Ignored.\n";

#include "include_asm.h"

extern void func_00105F00(int a0);
extern int func_0010D830(int a0, int a1);

void func_001E6D68(int a0, int a1, int a2)
{
    func_00105F00(a0);
    return func_0010D830(a0 + 0x10, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E6DA0);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E73A8);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E80D8);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E83F8);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E8598);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E85D8);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E8618);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", func_001E8810);
