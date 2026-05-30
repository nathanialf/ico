/* fieldCollision.c -- typed sdata / lit4 definitions for this TU.
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

extern unsigned char D_006323C7;
extern char D_006323C8[8];
extern const char D_006323D0[8];
extern const char D_006323D8[8];
extern const char D_006323E0[8];
extern const char D_006323E8[8];
extern unsigned int D_006323F0;
extern unsigned int D_006323F4;
extern char D_006323F8[8];
extern const char D_00632418[];
extern const char D_00632420[8];
extern const char D_00632428[8];
extern const char D_00632430[8];
extern const char D_00632438[8];
extern int D_00632440;
extern int D_00632444;
extern int D_00632448;
extern int D_0063244C;

const char D_005591F0[24] = "src/fieldCollision.c";

const char D_00559208[56] = "TOO MANY COLLISION DEPEND GOBJS\n\000\000\000\000\000\000\000\000%s%d(%d)\n\000\000\000\000\000\000";

const char D_00559240[16] = "W :%4d %2d";

const char D_00559250[16] = "WR:%4d %2d";

const char D_00559260[16] = "F :%4d %2d";

const char D_00559270[16] = "FR:%4d %2d";

const char D_005592D0[16] = "%8f %8f %8f";

const char D_005592E0[24] = "cl:src is not inside\n";

const char D_005592F8[24] = "cl:dst is not outside\n";

const char D_00559310[16] = "cl:no hit??\n";

const char D_00559320[24] = "src:%8f %8f %8f\n";

const char D_00559338[24] = "dst:%8f %8f %8f\n";

const char D_00559350[24] = "%02d: src:%8f dst:%8f\n";

/* EUC-JP: "壁が無いのにGetOrientOfWallが呼ばれました\n" */
const char D_00559368[48] = "\312\311\244\254\314\265\244\244\244\316\244\313GetOrientOfWall\244\254\270\306\244\320\244\354\244\336\244\267\244\277\n";

/* EUC-JP: "DOBJ無しのオブジェクトに対してGetOrientOfWallが呼ばれました\n" */
const char D_00559398[72] = "DOBJ\314\265\244\267\244\316\245\252\245\326\245\270\245\247\245\257\245\310\244\313\302\320\244\267\244\306GetOrientOfWall\244\254\270\306\244\320\244\354\244\336\244\267\244\277\n";

const char D_00559400[32] = "MakeExitAttributeIndex() %d\n";

const char D_00559420[16] = "attr EXIT%2d\n";

const char D_00559430[16] = "--disconnect--\n";

const char D_00559440[24] = "girl after func\n";

const char D_00559458[24] = "enter actGirlHand50\n";

const char D_00559470[24] = "girl error flg get\n";

const char D_00559488[24] = "enter motGirlHand50\n";

const char D_005594A0[24] = "enter actGirlHand100\n";

const char D_005594B8[24] = "enter motGirlHand100\n";

const char D_005594D0[24] = "enter actGirlHand200\n";

const char D_005594E8[24] = "enter motGirlHand200\n";

const char D_00559500[16] = "%s sync error\n";

const char D_00632400[8] = "%2d ";

unsigned int D_00632408[2] = { 0x0000000A, 0x00000000 };

const char D_00632410[8] = "0";

#include "include_asm.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166028);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166118);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166258);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_001667E0);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166A10);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166BB0);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00166E10);
extern void func_00166E10(int *self);

void func_00167230(int *self_arg)
{
    register int *self __asm__("$2") = self_arg;
    register long long val __asm__("$3");

    *(int *)((char *)self + 0xB0) = 0;
    *(int *)((char *)self + 0x94) = 0;
    *(int *)((char *)self + 0x88) = 0;
    __asm__ volatile("ldl %0, %%gp_rel(D_006323C7)($28)" : "=r"(val));
    __asm__ volatile("ldr %0, %%gp_rel(D_006323C0)($28)" : "+r"(val));
    __asm__ volatile("sdl %1, 0x87(%0)" : : "r"(self), "r"(val) : "memory");
    __asm__ volatile("sdr %1, 0x80(%0)" : : "r"(self), "r"(val) : "memory");
    NOP();
    func_00166E10(self);
}

void func_00167258(int *self_arg)
{
    register int *self __asm__("$2") = self_arg;
    register long long val __asm__("$3");

    *(int *)((char *)self + 0x94) = 0;
    __asm__ volatile("ldl %0, %%gp_rel(D_006323C7)($28)" : "=r"(val));
    __asm__ volatile("ldr %0, %%gp_rel(D_006323C0)($28)" : "+r"(val));
    __asm__ volatile("sdl %1, 0x93(%0)" : : "r"(self), "r"(val) : "memory");
    __asm__ volatile("sdr %1, 0x8C(%0)" : : "r"(self), "r"(val) : "memory");
    NOP();
    func_00166E10(self);
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167278);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167280);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_00167528);
extern int func_00263FB0(float f);
extern void func_001A6E28(const char *fmt, int a, int b, int c);
void func_00167760(float *vec)
{
    return func_001A6E28(D_005592D0, func_00263FB0(vec[0]),
                         func_00263FB0(vec[1]), func_00263FB0(vec[2]));
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", func_001677D0);
