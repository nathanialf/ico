/* BgAnimation.c -- typed sdata / lit4 definitions for this TU.
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


const char D_0061A8C0[24] = "this is not bga file.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A8D8[24] = "src/BgAnimation.c";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A918[32] = "this is not sdf camera file.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A938[32] = "Light Object not exists.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A958[32] = "Shadow Object not exists.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A978[32] = "OBJECT FILE \"%s\" NOT EXISTS.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A998[40] = "\245\342\245\307\245\353\245\307\241\274\245\277\245\325\245\241\245\244\245\353[%s]\244\254\244\242\244\352\244\336\244\273\244\363.\n\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061A9F8[40] = "Illegal Envelope Type : %p(%d)\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061AA48[24] = "\311\324\314\300\244\312\245\321\241\274\245\306\245\243\245\257\245\353\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061AA60[80] = "PBGA\245\277\245\244\245\327\244\316\245\242\245\313\245\341\241\274\245\267\245\347\245\363\244\307\244\317\245\353\241\274\245\327\244\316\245\321\241\274\245\306\245\243\245\257\245\353\244\317\273\310\315\321\244\307\244\255\244\336\244\273\244\363.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061AAF0[32] = "illegal lightning data set.\n";

/* String rodata migrated from BgAnimation_data.c */
const char D_0061AB10[64] = "Lightning data does not found! maybe, start point < end point.\n";

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337BC = 0x00000000;

/* String rodata migrated from BgAnimation_data.c */
const char D_006337C0[8] = "BGA";

/* String rodata migrated from BgAnimation_data.c */
const char D_006337C8[8] = "FALSE";

/* String rodata migrated from BgAnimation_data.c */
const char D_006337D0[8] = "SDF";

/* String rodata migrated from BgAnimation_data.c */
const char D_006337D8[8] = "0";

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337E0 = 0x00000065;

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337E4 = 0x00000000;

/* String rodata migrated from BgAnimation_data.c */
const char D_006337E8[8] = "LWS";

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337F0 = 0x00000000;

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337F4 = 0x00000080;

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337F8 = 0x00000080;

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_006337FC = 0x00000080;

/* String rodata migrated from BgAnimation_data.c */
unsigned int D_00633800[2] = { 0x00000080, 0x00000000 };

/* String rodata migrated from BgAnimation_data.c */
const char D_00633808[8] = "font";

/* String rodata migrated from BgAnimation_data.c */
unsigned char D_00633810[8] = { 0 };

/* String rodata migrated from BgAnimation_data.c */
const char D_00633818[12] = "FALSE\000\000\000e";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F6E28);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F71D0);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F74E8);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F77A0);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F7D70);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F8038);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F8398);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F8600);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F88C0);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F8B90);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F9348);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F9418);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F9680);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F99A0);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F9DD8);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA030);

extern int D_00633F64;
extern int D_006337B0;
extern int D_006337B8;
extern int D_00710BE0[];
extern void func_001185A8(void *dst, void *src);

void func_001FA590(void) {
    D_00633F64 = 0;
}

int func_001FA598(void *p)
{
    int v = D_00633F64;
    if (v != 0) {
        func_001185A8(p, D_00710BE0);
        v = D_00633F64;
    } else {
        D_006337B0 = 0;
    }
    return v != 0 && D_006337B8 == 0;
}

INCLUDE_ASM_NOP_PAD(func_001FA5DC);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA5E0);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA658);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA6D8);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA760);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA7F8);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA898);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA910);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001FA998);
