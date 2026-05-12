/* commonact.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x00630C4C"))) float D_00630C4C = 0.3f;
__attribute__((section(".lit4.0x00630C50"))) float D_00630C50 = 0.3f;
__attribute__((section(".lit4.0x00630C54"))) float D_00630C54 = 0.1f;
__attribute__((section(".lit4.0x00630C58"))) float D_00630C58 = 10000.0f;
__attribute__((section(".lit4.0x00630C5C"))) float D_00630C5C = 0.005f;
__attribute__((section(".lit4.0x00630C60"))) float D_00630C60 = 90000.0f;
__attribute__((section(".lit4.0x00630C64"))) float D_00630C64 = 0.05f;
__attribute__((section(".lit4.0x00630C68"))) float D_00630C68 = 0.005f;
__attribute__((section(".lit4.0x00630C6C"))) float D_00630C6C = 360000.0f;
__attribute__((section(".lit4.0x00630C70"))) float D_00630C70 = 10000.0f;
__attribute__((section(".lit4.0x00630C74"))) float D_00630C74 = 0.005f;
__attribute__((section(".lit4.0x00630C78"))) float D_00630C78 = 0.92f;
__attribute__((section(".lit4.0x00630C7C"))) float D_00630C7C = 3.14159274f;
__attribute__((section(".lit4.0x00630C80"))) float D_00630C80 = 3.14159274f;
__attribute__((section(".lit4.0x00630C84"))) float D_00630C84 = 0.1f;
__attribute__((section(".lit4.0x00630C88"))) float D_00630C88 = 0.1f;
__attribute__((section(".lit4.0x00630C8C"))) float D_00630C8C = 0.1f;
__attribute__((section(".lit4.0x00630C90"))) float D_00630C90 = 0.1f;
__attribute__((section(".lit4.0x00630C94"))) float D_00630C94 = 0.1f;
__attribute__((section(".lit4.0x00630C98"))) float D_00630C98 = 0.99f;
__attribute__((section(".lit4.0x00630C9C"))) float D_00630C9C = 0.1f;
__attribute__((section(".lit4.0x00630CA0"))) float D_00630CA0 = 0.99f;
__attribute__((section(".lit4.0x00630CA4"))) float D_00630CA4 = 0.1f;
__attribute__((section(".lit4.0x00630CA8"))) float D_00630CA8 = 0.1f;
__attribute__((section(".lit4.0x00630CAC"))) float D_00630CAC = 0.99f;
__attribute__((section(".lit4.0x00630CB0"))) float D_00630CB0 = 0.1f;
__attribute__((section(".lit4.0x00630CB4"))) float D_00630CB4 = 0.99f;
__attribute__((section(".lit4.0x00630CB8"))) float D_00630CB8 = -1.57079637f;
__attribute__((section(".lit4.0x00630CBC"))) float D_00630CBC = 4225.0f;
__attribute__((section(".lit4.0x00630CC0"))) float D_00630CC0 = 0.2f;
__attribute__((section(".lit4.0x00630CC4"))) float D_00630CC4 = 0.2f;
__attribute__((section(".lit4.0x00630CC8"))) float D_00630CC8 = 0.1f;
__attribute__((section(".lit4.0x00630CCC"))) float D_00630CCC = 0.2f;
__attribute__((section(".lit4.0x00630CD0"))) float D_00630CD0 = 0.1f;
__attribute__((section(".lit4.0x00630CD4"))) float D_00630CD4 = 3.14159274f;
__attribute__((section(".lit4.0x00630CD8"))) float D_00630CD8 = 0.1f;
__attribute__((section(".lit4.0x00630CDC"))) float D_00630CDC = 3.14159274f;
__attribute__((section(".sdata.0x006322F8"))) const char D_006322F8[] = "set %p\n";
__attribute__((section(".sdata.0x00632300"))) unsigned int D_00632300 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632304"))) unsigned int D_00632304 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632308"))) const char D_00632308[8] = "%1.1f ";
__attribute__((section(".sdata.0x00632310"))) const char D_00632310[8] = "boy";
__attribute__((section(".sdata.0x00632318"))) const char D_00632318[8] = "girl";
__attribute__((section(".sdata.0x00632320"))) const char D_00632320[8] = "[%s]\n";
__attribute__((section(".sdata.0x00632328"))) const char D_00632328[8] = "loop";
__attribute__((section(".sdata.0x00632330"))) const char D_00632330[8] = "pull";
__attribute__((section(".sdata.0x00632338"))) const char D_00632338[8] = "push";
__attribute__((section(".sdata.0x00632340"))) int D_00632340 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x00632344"))) int D_00632344 = 0x00000000;
__attribute__((section(".sdata.0x00632348"))) const char D_00632348[8] = "PICKUP";
__attribute__((section(".sdata.0x00632350"))) const char D_00632350[8] = "ATTACK";
__attribute__((section(".sdata.0x00632358"))) const char D_00632358[8] = "CLING";
__attribute__((section(".sdata.0x00632360"))) const char D_00632360[] = "TO_GENE";
__attribute__((section(".sdata.0x00632368"))) const char D_00632368[] = "TO_GIRL";
__attribute__((section(".sdata.0x00632370"))) const char D_00632370[8] = "TO_BOY";
__attribute__((section(".sdata.0x00632378"))) const char D_00632378[8] = "AWAIT";
__attribute__((section(".sdata.0x00632380"))) const char D_00632380[8] = "IDLE";
__attribute__((section(".sdata.0x00632388"))) const char D_00632388[8] = "START";
__attribute__((section(".sdata.0x00632508"))) char D_00632508[8] = { 0 };
__attribute__((section(".sdata.0x00632510"))) unsigned int D_00632510 = 0x00000078;
__attribute__((section(".sdata.0x00632DB4"))) int D_00632DB4 = 0;
__attribute__((section(".sdata.0x00633060"))) int D_00633060 = 0x00000001;
__attribute__((section(".sdata.0x00633064"))) int D_00633064 = 0x00000000;
__attribute__((section(".sdata.0x00633068"))) const char D_00633068[8] = "game.";
__attribute__((section(".sdata.0x00633070"))) int D_00633070 = 0;
__attribute__((section(".sdata.0x00633074"))) int D_00633074 = 0;
__attribute__((section(".sdata.0x00633078"))) int D_00633078 = 0;
__attribute__((section(".sdata.0x0063307C"))) int D_0063307C = 0;
__attribute__((section(".sdata.0x00633080"))) unsigned int D_00633080 = 0x00000001;
__attribute__((section(".sdata.0x00633084"))) int D_00633084 = 0;
__attribute__((section(".sdata.0x00633088"))) int D_00633088 = 0;
__attribute__((section(".sdata.0x0063308C"))) int D_0063308C = 0;
__attribute__((section(".sdata.0x00633090"))) int D_00633090 = 0;
__attribute__((section(".sdata.0x00633094"))) int D_00633094 = 0;
__attribute__((section(".sdata.0x00633098"))) unsigned int D_00633098 = 0x00000001;
__attribute__((section(".sdata.0x0063309C"))) int D_0063309C = 0;
__attribute__((section(".sdata.0x006330A0"))) int D_006330A0 = 0;
__attribute__((section(".sdata.0x006330A4"))) int D_006330A4 = 0;
__attribute__((section(".sdata.0x006330A8"))) unsigned int D_006330A8 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x006330AC"))) unsigned int D_006330AC = 0x00000001;
__attribute__((section(".sdata.0x006330B0"))) char D_006330B0[8] = { 0 };
__attribute__((section(".sdata.0x006330B8"))) const char D_006330B8[] = "1 to 2\n";
__attribute__((section(".sdata.0x006330C0"))) const char D_006330C0[] = "2 to 1\n";
__attribute__((section(".sdata.0x006330C8"))) char D_006330C8[8] = { 0 };
__attribute__((section(".sdata.0x006330D0"))) const char D_006330D0[] = "chk:%d\n";
__attribute__((section(".sdata.0x006330D8"))) const char D_006330D8[] = "case 4\n";
__attribute__((section(".sdata.0x006330E0"))) int D_006330E0 = 0;
__attribute__((section(".sdata.0x006330E4"))) int D_006330E4 = 0;
__attribute__((section(".sdata.0x006330E8"))) const char D_006330E8[8] = "fail\n";
__attribute__((section(".sdata.0x006330F0"))) int D_006330F0 = 0;
__attribute__((section(".sdata.0x006330F4"))) int D_006330F4 = 0;
__attribute__((section(".sdata.0x006330F8"))) int D_006330F8 = 0x20808080;
__attribute__((section(".sdata.0x006330FC"))) int D_006330FC = 0x00000000;
__attribute__((section(".sdata.0x00633100"))) unsigned int D_00633100 = 0x2040FF40;
__attribute__((section(".sdata.0x00633104"))) unsigned int D_00633104 = 0x00000001;
__attribute__((section(".sdata.0x00633108"))) int D_00633108 = 0;
__attribute__((section(".sdata.0x0063310C"))) int D_0063310C = 0;
__attribute__((section(".sdata.0x00633110"))) char D_00633110[8] = { 0 };
__attribute__((section(".sdata.0x00633118"))) unsigned int D_00633118 = 0x000A6425;
__attribute__((section(".sdata.0x0063311C"))) int D_0063311C = 0;
__attribute__((section(".sdata.0x00633120"))) int D_00633120 = 0;
__attribute__((section(".sdata.0x00633124"))) int D_00633124 = 0;
__attribute__((section(".sdata.0x00633128"))) int D_00633128 = 0;
__attribute__((section(".sdata.0x0063312C"))) unsigned int D_0063312C = 0x000000FF;
__attribute__((section(".sdata.0x00633130"))) int D_00633130 = 0;

__attribute__((section(".rodata.0x00558860"))) const char D_00558860[16] = "src/commonact.c";

__attribute__((section(".rodata.0x00558870"))) const char D_00558870[16] = "ROPE_GOBJ!=NULL";
__attribute__((section(".rodata.0x00558920"))) const char D_00558920[64] = "index>=ClingDataID_cling_start && index<ClingDataID_cling_end";
__attribute__((section(".rodata.0x00558AC0"))) const char D_00558AC0[24] = "EMERGENCY BY NOMOVE";
__attribute__((section(".rodata.0x00558AD8"))) const char D_00558AD8[24] = "EMERGENCY BY TIMEOUT";
__attribute__((section(".rodata.0x00558AF0"))) const char D_00558AF0[32] = "EMERGENCY BY DANGER LOOP";
__attribute__((section(".rodata.0x00558D90"))) const char D_00558D90[24] = "girl becarry error";
__attribute__((section(".rodata.0x00558DC0"))) const char D_00558DC0[16] = "IRREGULAR";
__attribute__((section(".rodata.0x00558DD0"))) const char D_00558DD0[16] = "BODYSLAM";
__attribute__((section(".rodata.0x00558DE0"))) const char D_00558DE0[16] = "SHOULDER";
__attribute__((section(".rodata.0x00558DF0"))) const char D_00558DF0[16] = "BODYGUARD";
__attribute__((section(".rodata.0x00558E00"))) const char D_00558E00[16] = "FIND_GIRL";

#include "matching.h"

extern void (*D_006323F0)(int a0, int a1);
extern int D_00633D34;

void func_001683A8(int a0)
{
    D_006323F0(a0, 0);
    DEFEAT_TCO();
}

void func_001683C8(int arg)
{
    D_006323F0(arg, 1);
}

void func_001683E8(int arg)
{
    D_006323F0(arg, 2);
}

void func_00168408(int arg)
{
    D_006323F0(arg, 6);
}

void func_00168428(int arg)
{
    D_006323F0(arg, 7);
}

void func_00168448(int arg)
{
    D_006323F0(arg, 3);
}

void func_00168468(int arg)
{
    D_006323F0(arg, 5);
}

void func_00168488(int arg)
{
    D_006323F0(arg, 0xA);
}

void func_001684A8(int arg)
{
    D_006323F0(arg, 0xB);
}

void func_001684C8(int arg)
{
    D_006323F0(arg, 4);
}

void func_001684E8(int a0, int a1)
{
    D_00633D34 = a1;
    D_006323F0(a0, 8);
    DEFEAT_TCO();
}
