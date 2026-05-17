/* generator.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00632798[8];
extern const char D_006327A0[8];
extern const char D_006327A8[8];
extern int D_006327B0;
extern int D_006327B4;
extern const char D_006327B8[8];
extern const char D_006327C0[8];
extern const char D_006327C8[8];
extern const char D_006327D0[8];
extern const char D_006327D8[8];
extern const char D_006327E0[8];
extern const char D_006327E8[8];
extern const char D_006327F0[];
extern unsigned int D_006327F8;
extern int D_006327FC;
extern const char D_00632800[8];
extern unsigned int D_00632808;
extern int D_0063280C;
extern char D_00632810[8];
extern const char D_00632820[8];
extern float D_00632828[2];
extern int D_00632830;
extern int D_00632834;
extern unsigned int D_00632838;
extern unsigned int D_0063283C;
extern int D_00632840;
extern int D_00632844;
extern const char D_00632848[8];
extern int D_00632850;

__attribute__((section(".rodata.0x0055AEA0"))) const char D_0055AEA0[16] = "src/generator.c";

/* String rodata migrated from generator_data.c */
__attribute__((section(".rodata.0x0055AEB0"))) const char D_0055AEB0[32] = "call enemy! = %d (%p : %d)\n";
__attribute__((section(".rodata.0x0055AED0"))) const char D_0055AED0[24] = "[%8s] %8f %8f %8f %8f\n";
__attribute__((section(".rodata.0x0055AEE8"))) const char D_0055AEE8[16] = "lock! = %d\n";
__attribute__((section(".rodata.0x0055AEF8"))) const char D_0055AEF8[16] = "unlock! = %d\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192478);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_001925E0);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192908);

/* Matched body inlined from src/cod/092B58.c during TU coalesce. */
extern void func_001AE460(int *self);
extern void func_0013FF88(int a0, int a1, int a2);

void func_00192B58(int *self) {
    int *p = (int *)((int *)self[0x15C/4])[0x800/4];
    p[0x50/4] = 1;
    func_001AE460(self);
    func_0013FF88((int)self, 1, (int)self);
}

INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192B98);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192D20);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192E08);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192EB8);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_001930B0);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00193600);
