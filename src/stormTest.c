/* stormTest.c -- typed sdata / lit4 definitions for this TU.
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


const char D_0061A470[16] = "src/stormTest.c";

const char D_0061A480[72] = "\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\263\253\273\317\273\376\244\313\245\307\241\274\245\277\244\316\305\276\301\367\244\254\264\326\244\313\271\347\244\303\244\306\244\244\244\336\244\273\244\363\244\307\244\267\244\277\241\243\n";

const char D_0061A4C8[56] = "\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\244\316\245\307\241\274\245\277\305\276\301\367\244\254\264\326\244\313\271\347\244\303\244\306\244\244\244\336\244\273\244\363\241\243\n";

const char D_0061A558[32] = "delete stream motion manager\n";

const char D_0061A578[32] = "disable automatic delete\n";

const char D_0061A598[64] = "\245\307\241\274\245\277\244\254\244\336\244\300\315\350\244\306\244\244\244\312\244\244\244\316\244\313\245\357\241\274\245\257\245\265\245\244\245\272\244\316\274\350\306\300\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\n";

const char D_0061A5E0[72] = "\245\307\241\274\245\277\244\254\244\336\244\300\315\350\244\306\244\244\244\312\244\244\244\316\244\313\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\244\316\274\350\306\300\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\n";

const char D_0061A628[40] = "\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\244\316\275\252\316\273\244\362\270\241\303\316\n";

const char D_0061A650[24] = "STANDBY %d CHARS %s";

unsigned int D_00631FB0 = 0x00000000;

unsigned int D_00631FB4 = 0x00000000;

unsigned char D_00631FB8[8] = { 0 };

const char D_00631FC0[8] = "stage";

const char D_00631FC8[8] = "event";

const char D_00631FD0[8] = "hara";

const char D_00631FD8[8] = "oomori";

const char D_00631FE0[8] = "horagai";

const char D_00631FE8[8] = "sound";

const char D_00631FF0[8] = "shock";

const char D_00631FF8[8] = "common";

unsigned int D_00633718 = 0x00000000;

unsigned int D_00633720 = 0x00000000;

unsigned int D_0063372C = 0x00000000;

unsigned int D_00633730 = 0x00000000;

unsigned int D_00633738 = 0x00000000;

#include "include_asm.h"
#include "regpin.h"

extern void func_001F0098(int a0);
extern void func_001F0260(int a0, int a1);

void func_001EFA58(void) {}

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFA60);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFD18);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFEE0);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0098);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0260);

void func_001F0540(int a0)
{
    func_001F0098(*(int *)(*(int *)(*(int *)(a0 + 0x15C) + 0x800) + 0x20));
}

void func_001F0550(int a0)
{
    int p = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    func_001F0260(*(int *)(p + 0x20), p + 0x10);
}

INCLUDE_ASM_NOP_PAD(func_001F0564);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0568);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0608);

extern int D_00633714;
extern int D_0063370C;
extern char D_0061A500[];
extern int func_001A6E28(char *a0);

void func_001F0858(void)
{
    if (D_00633714 == 0) {
        return func_001A6E28(D_0061A500);
    }
    D_0063370C = 1;
    return 1;
}

extern void func_00105F00(int p, int q);
extern char D_00275850[];

void func_001F0878(int *self)
{
    register int one REG("$17") = 1;
    register int *p REG("$2");
    volatile int pad;
    p = (int *)self[0x57];
    p[0x11C] = -1;
    p = (int *)self[0x57];
    p[0x198] = one;
    func_00105F00((int)((char *)((int *)self[0x57]) + 0x670), (int)D_00275850);
    p = (int *)self[0x57];
    p[0x154] = one;
}
