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


const char D_0055ADE0[40] = "eBrainStatusSet: ebrain area over\n";

const char D_0055AE08[16] = "src/ebrain.c";

const char D_0055AE18[16] = "UseStageNo>0";

const char D_0055AE28[24] = "GeneratorLabel>0";

const char D_005F2FB8[32] = "NULL";

const char D_005F2FD8[32] = "dummy";

const float D_005F2FF8[16] = { 5.356473e+07f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 255.0f, 255.0f, 255.0f, 255.0f, 0.0f, 128.0f, 255.0f };

unsigned int D_00632770 = 0x7F7FFFFF;

unsigned int D_00632780 = 0x00000000;

unsigned int D_00632784 = 0x00000000;

unsigned char D_00632788[8] = { 0 };

const char D_00632790[8] = "0";

const char D_00632798[8] = "0";

const char D_006327A0[8] = "revive";

const char D_006327A8[8] = "error!";

/* Inlined data (Phase 3e) — migrated from ebrain_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630F98 = 3.1415927f;
float D_00630F9C = 250000.0f;
float D_00630FA0 = 250000.0f;

/* Inlined data (Phase 3e) — migrated from ebrain_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* C-referenced data (extern kept, def supplies bytes) */
int D_00632774 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from ebrain_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* C-referenced data (extern kept, def supplies bytes) */
int D_00632778 = 0x00000000;
unsigned int D_0063277C = 0x00000000;

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
extern void func_00194020(char *elem, char *base, int a2, float a, float b);

void func_001909B8(char *base, int n, int a2)
{
    char *p;
    int i = 0;
    if (n < 0) {
        return;
    }
    p = base;
    do {
        func_00194020(p, base, a2, (float)i, (float)(n - i));
        i++;
        p += 0x20;
    } while (i <= n);
}
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
