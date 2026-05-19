/* ebrain.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x0055AE08"))) const char D_0055AE08[16] = "src/ebrain.c";

__attribute__((section(".rodata.0x0055AE18"))) const char D_0055AE18[16] = "UseStageNo>0";
__attribute__((section(".rodata.0x0055AE28"))) const char D_0055AE28[24] = "GeneratorLabel>0";
__attribute__((section(".rodata.0x005F2FB8"))) const char D_005F2FB8[32] = "NULL";
__attribute__((section(".rodata.0x005F2FD8"))) const char D_005F2FD8[32] = "dummy";

/* String rodata migrated from ebrain_data.c */
__attribute__((section(".rodata.0x0055ADE0"))) const char D_0055ADE0[40] = "eBrainStatusSet: ebrain area over\n";

/* Float rodata migrated from ebrain_data.c */
__attribute__((section(".rodata.0x005F2FF8"))) const float D_005F2FF8[16] = { 5.356473e+07f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 255.0f, 255.0f, 255.0f, 255.0f, 0.0f, 128.0f, 255.0f };

/* Single-float rodata migrated from ebrain_data.c */

#include "include_asm.h"

void func_00190698(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(char *)(p + 0xCD) = 0;
}

unsigned char func_001906A8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(unsigned char *)(p + 0xCD);
}

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001906B8);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001907E0);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001909B8);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190A48);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190B30);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190D70);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190F30);

extern int D_00632778;
extern int D_00632774;
extern int D_00633DAC;
extern int D_00633DB0;
extern int D_006D0710[];

void func_001918A8(void)
{
    int *p = D_006D0710;
    int i;
    D_00632778 = 0;
    D_00632774 = 0;
    D_00633DAC = 0;
    p = (int *)((char *)p + 0x37C);
    D_00633DB0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001918EC);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001918F0);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001919A0);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00191AA0);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00191B70);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00191C80);

extern int D_00633DB4;
extern int D_00633DB8;
extern int D_00633DBC;
extern int D_006D0B90[];

int func_00191D08(void)
{
    D_00633DB4 = 0;
    D_00633DB8 = -1;
    D_00633DBC = 0;
    return 0;
}

int func_00191D20(int a0)
{
    if (D_00633DB8 < 0) goto init;
    if (a0 != D_00633DB8) goto append;
    return 1;
init:
    D_00633DB8 = a0;
    return 1;
append:
    D_006D0B90[D_00633DB4] = a0;
    D_00633DB4++;
    return 0;
}
