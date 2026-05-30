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

const char D_0055AEA0[16] = "src/generator.c";

/* String rodata migrated from generator_data.c */
const char D_0055AEB0[32] = "call enemy! = %d (%p : %d)\n";
const char D_0055AED0[24] = "[%8s] %8f %8f %8f %8f\n";
const char D_0055AEE8[16] = "lock! = %d\n";
const char D_0055AEF8[16] = "unlock! = %d\n";

/* Inlined data (Phase 3e) — migrated from generator_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* numeric word tables */
unsigned int D_00564150[24] = { 0x44FBE000, 0x44F32000, 0xC5338000, 0x00000134, 0x44FC8000, 0x44F32000, 0xC5338000, 0x00000135, 0x44504000, 0xC3938000, 0x44D1E000, 0x0000038D, 0x4492C000, 0xC4956000, 0xC2AE0000, 0x0000062D, 0x44678000, 0xC4956000, 0xC4288000, 0x0000062E, 0xC1700000, 0xC478C000, 0xC3340000, 0x00000BFA };

/* Inlined data (Phase 3e) — migrated from generator_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630FA4 = 22500.0f;
float D_00630FA8 = 22500.0f;
float D_00630FAC = 22500.0f;
float D_00630FB0 = 3.1415927f;
float D_00630FB4 = 3.1415927f;
float D_00630FB8 = 3.1415927f;
float D_00630FBC = 3.1415927f;
float D_00630FC0 = 3.1415927f;

#include "include_asm.h"
#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/generator", func_001920A8);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_001921F8);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192478);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_001925E0);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192908);

/* Matched body inlined from src/cod/092B58.c during TU coalesce. */
extern void func_001AE460(int *self);
extern void func_0013FF88(int a0, int a1, int a2);

void func_00192B58(int *self) {
    Obj800 *p = ((Sub15C *)((GObj *)(self))->p_15C)->p_800;
    p->f_50 = 1;
    func_001AE460(self);
    func_0013FF88((int)self, 1, (int)self);
}

INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192B98);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192D20);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192E08);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00192EB8);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_001930B0);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00193600);
INCLUDE_ASM("asm/nonmatchings/src/generator", func_00193730);

void func_00193818(int a0)
{
    *(int *)(*(int *)((int)((GObj *)(a0))->p_15C + 0x800) + 0x8) += 1;
}

void func_00193830(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    *(p + 0xE) = 1;
}
