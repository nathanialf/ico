/* enemy.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00618CF0"))) const char D_00618CF0[16] = "src/enemy.c";

__attribute__((section(".rodata.0x00618D00"))) const char D_00618D00[16] = "enemy_sprite";

/* String rodata migrated from enemy_data.c */
__attribute__((section(".rodata.0x00618D40"))) const char D_00618D40[40] = "CAN'T ALLOCATE ENEMY'S PARTICLE MEMORY\n";

/* String-pool rodata migrated from enemy_data.c */
__attribute__((section(".rodata.0x0061DA78"))) const char D_0061DA78[104] = "+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000+\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "敵兵のパーティクルのメモリを確保できません
" */
__attribute__((section(".rodata.0x00618D10"))) const char D_00618D10[48] = "\305\250\312\274\244\316\245\321\241\274\245\306\245\243\245\257\245\353\244\316\245\341\245\342\245\352\244\362\263\316\312\335\244\307\244\255\244\336\244\273\244\363\n";

#include "include_asm.h"

extern unsigned short D_00633398;
extern unsigned short D_0063339A;
extern int D_00633394;
extern int D_006333AC;
extern int D_006325B4;
extern char D_006333B8[];
extern void func_0010D530(int *self);
extern void func_0010E158(int *self, short y);
extern void func_0010E0B8(int *self, short y);
extern void func_001E8AB8(int x);
extern void func_0018CAA8(int x, int y, int z);
extern void func_001A6E28(char *p);

INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CBE88);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CC048);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CC470);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CC838);

void func_001CCA70(int *self)
{
    func_0010D530(self);
    func_0010E158(self, -D_00633398);
    func_0010E0B8(self, -D_0063339A);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CCAC0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CCD98);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CCFD0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD0B8);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD2B0);

void func_001CD490(void)
{
    func_001E8AB8(D_00633394);
    D_00633394 = -1;
    func_0018CAA8(D_006333AC, 0, 3);
    D_006325B4 = 0;
    func_001A6E28(D_006333B8);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD4D8);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD5C0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CD9B0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CDB28);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CDE30);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE028);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE220);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE3C0);
INCLUDE_ASM("asm/nonmatchings/src/enemy", func_001CE5F8);
extern int func_00165F88(int *self);
extern void func_001BB7E0(void);
extern void func_001CE5F8(int *self);

void func_001CE690(int *self)
{
    char *sub = *(char **)((char *)self + 0x164);
    unsigned long long flag = *(unsigned long long *)(sub + 0x18);
    if (((flag >> 33) & 1) == 0) return;
    func_001BB7E0();
    if (func_00165F88(self) != 0) return;
    func_001CE5F8(self);
}
