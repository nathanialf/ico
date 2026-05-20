/* geometryManager.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00631B30[8];
extern unsigned int D_00631B38;
extern int D_00631B3C;
extern char D_00631B40[8];

__attribute__((section(".rodata.0x00553AD0"))) const char D_00553AD0[24] = "src/geometryManager.c";

/* String rodata migrated from geometryManager_data.c */
__attribute__((section(".rodata.0x00553AE8"))) const char D_00553AE8[96] = "Fatal error! Geometry localize function called with GObj\n    that already have parent.\nExit...\n";
__attribute__((section(".rodata.0x00553B48"))) const char D_00553B48[48] = "TOO MANY CHARACTERS EXIST ON THIS STAGE(>64)\n";
__attribute__((section(".rodata.0x00553B78"))) const char D_00553B78[24] = "InitKeyInput2() in\n";
__attribute__((section(".rodata.0x00553B90"))) const char D_00553B90[16] = "PadInit\n";
__attribute__((section(".rodata.0x00553BA0"))) const char D_00553BA0[24] = "InitKeyInput2() out\n";
__attribute__((section(".rodata.0x00553BB8"))) const char D_00553BB8[24] = "signal to main\n";
__attribute__((section(".rodata.0x00553BE0"))) const char D_00553BE0[48] = "Adjust Motion Height To Field. --------------\n";

/* Float rodata migrated from geometryManager_data.c */
__attribute__((section(".rodata.0x00553C10"))) const float D_00553C10[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00553C20"))) const float D_00553C20[4] = { 0.0f, 0.0f, 5.0f, 0.0f };
__attribute__((section(".rodata.0x00553C30"))) const float D_00553C30[4] = { 5.0f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00553C70"))) const float D_00553C70[4] = { 1e+01f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00553C90"))) const float D_00553C90[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

#include "include_asm.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00102E08);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00102FA0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103018);

/* Matched body inlined from src/cod/003110.c during TU coalesce. */
extern void func_00105F00(int a0, int a1);
void func_00103110(int a0, int a1)
{
    func_00105F00(a0, *(int *)(a1 + 0x15C) + 0x130);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_0010311C);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103120);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001031E0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001032A8);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103370);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001034B8);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103AD0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103B48);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103C48);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103D50);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00103F00);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001040C0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104140);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001041C0);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104240);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104360);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104478);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104508);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104590);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104638);
extern void func_00105E70(char *dst, char *src);
extern void func_002438E8(char *dst, char *src, int m);

void func_00104698(char *dst, char *src)
{
    char tmp[0x40];
    func_00105E70(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    func_00105F00((int)dst, (int)(tmp + 0x30));
}

void func_001046F0(char *dst, char *outer)
{
    char *src = *(char **)(outer + 0x15C);
    char tmp[0x40];
    func_00105E70(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    func_00105F00((int)dst, (int)(tmp + 0x30));
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104748);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104818);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001048C8);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00104940);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_001049C0);

/* Matched body inlined from src/cod/004A38.c during TU coalesce. */
extern int D_0065F940[];
int *func_00104A38(void) {
    return D_0065F940;
}

TRAILING_PAD_NOP();
