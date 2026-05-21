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


const char D_00618DB0[24] = "src/enemyParts.c";

#include "matching.h"
#include "include_asm.h"

extern char D_0061D560[];
extern void func_0010EC98(int);
extern void func_00104508(void *dst, int *src);
extern void func_00102850(void *dst, int *src);
extern int func_001E8B48(int a, void *b, void *c);
extern void func_001118B8(int x);
extern void func_00111FA8(int x, int y, int z);
extern void func_001114D0(int a, int b, int c, int d);
extern void func_0010F630(void);

int func_001CEC30(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x800);
    int idx = *(int *)(p + 8);
    int new_var = 3;
    char *new_var3 = D_0061D560;
    unsigned int *new_var2 = (unsigned int *)((new_var3 + (idx * 0x14)) + 0x10);
    return ((*new_var2) >> 2) & new_var;
}

float func_001CEC60(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x800);
    char *new_var;
    int idx = *(int *)(p + 8);
    new_var = D_0061D560 - (-(idx * 0x14));
    return ((float *)new_var)[2];
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CEC88);

void func_001CED28(int *self)
{
    int local[8];
    func_00104508(local, self);
    func_00102850(&local[4], self);
    func_001E8B48(0x31, local, &local[4]);
    self[0x16C / 4] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", func_001CED80);
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

int func_001CF8D0(int *self)
{
    func_001118B8(self[0]);
    func_00111FA8(1, self[0xD], 0x80);
    func_001114D0(self[3], self[4], self[1] * 2, 1);
    func_0010F630();
    return 1;
}
