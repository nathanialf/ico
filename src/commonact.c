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
 * land in this same file (per-TU layout); typed
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
__attribute__((section(".sdata.0x006330C8"))) char D_006330C8[8] = { 0 };
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

/* ====================================================================
 * cmn_tail (.text 0x16850C..0x16AE48): commonact's own body after the
 * 11-func dispatch block above. Matched-C bodies inline; unmatched
 * funcs are INCLUDE_ASM'd. Funcs are emitted in .text address order
 * so ee-gcc produces them at the right VMA when this TU is linked.
 * 4-byte nop pads (single-instruction func_<XXX> shims) are absorbed
 * into the preceding function's matching/nonmatching .s by splat —
 * no separate INCLUDE_ASM line is needed for them.
 * ==================================================================== */

#include "include_asm.h"

extern void (*D_006323F4)(int, int);
extern int D_006323BC;
extern int D_00633D08;
extern int D_00633D0C;
extern int D_00633D10;
extern int D_00633D14;
extern int D_00633D18;
extern int D_00633D1C;
extern int D_00633D20;
extern int D_00633D24;
extern int D_00633D28;
extern int D_006AB100[];
extern char D_00632428[];
extern int D_00559430[];
extern void func_00104508(int *dst, int *src);
extern void func_0010A498(int *dst, int *src);
extern void func_00105F00(int a0, int a1);
extern volatile int func_0010F5B8(int a0, int a1, int a2);
extern float func_00105FE0(float f);
extern void func_00167230(int *a0);
extern void func_00167258(int *a0);
extern void func_00169F80(int *a0);
extern void func_0016A058(int *a0);
extern void func_0014A3A8(void);
extern void func_0014B330(int *self, int a1, float a2);
extern void func_001A6E28();   /* K&R: takes (char*) or (int*) or (char*, int) across callers */
extern void func_00243B60(int *dst, int *src);
extern float func_00243950();  /* called with 1 or 2 args across cod stubs */
extern int (*D_006323F0_fp)(int *, int);  /* aliased below — D_006323F0 is also used as fn-ptr */
extern void func_0016A1D8(float *p);

/* func_00168510 */
void func_00168510(int a0, int a1)
{
    D_00633D34 = a1;
    D_006323F0(a0, 9);
    DEFEAT_TCO();
}

/* func_00168534 is a 4-byte nop pad absorbed into the .s for func_00168538. */
void func_00168538(int arg) { D_006323F4(arg, 0xC); }
void func_00168558(int arg) { D_006323F4(arg, 0xD); }
void func_00168578(int arg) { D_006323F4(arg, 0xE); }
void func_00168598(int arg) { D_006323F4(arg, 0xF); }

void func_001685B8(int a0, int a1)
{
    D_00633D34 = a1;
    D_006323F4(a0, 0x10);
    DEFEAT_TCO();
}

/* func_001685DC (4-byte nop pad) absorbed into func_001685E0's .s. */
void func_001685E0(int *self)
{
    int buf[4];
    int *p10 = self + 4;
    func_00243B60(buf, p10);
    D_006323F0((int)self, 1);
    func_00243B60(p10, self + 8);
    D_006323F4((int)self, 0xC);
    func_00243B60(p10, buf);
}

int func_00168650(int a0)
{
    *(int *)&D_006323F0 = (int)&func_00167230;
    *(int *)&D_006323F4 = (int)&func_00167258;
    if (a0 != 0) {
        *(int *)&D_006323F0 = (int)&func_00169F80;
        *(int *)&D_006323F4 = (int)&func_0016A058;
    }
    return 0;
}

/* func_0016868C nop pad. */
void func_00168690(int *self, int a1)
{
    int new_var;
    int *p;
    func_0010F5B8((int) self, a1, 0);
    p = (int *) self[0];
    new_var = 0x14 / 4;
    p[0x10 / 4] = (int) (((char *) p) + p[0x10 / 4]);
    p[0x14 / 4] = (int) (((char *) p) + p[new_var]);
}

/* func_001686D4 nop pad absorbed into func_001686D8's .s. */
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001686D8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001687B8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001688E0);

void func_00168A28(float *self, float a, float b, float c, float d) {
    self[0] = a; self[1] = b; self[2] = c; self[3] = d;
}

/* func_00168A3C nop pad. */
int func_00168A40(int a0) {
    if (*(int *)(a0 + 0x88) == 0) return 0;
    return *(int *)(a0 + 0x98);
}

/* func_00168A5C nop pad. */
int func_00168A60(int a0) {
    if (*(int *)(a0 + 0x94) == 0) return 0;
    return *(int *)(a0 + 0x98);
}

/* func_00168A7C nop pad absorbed into func_00168A80's .s. */
int func_00168A80(unsigned int a, unsigned int b)
{
    int i;
    if ((a & b) == 0) return 0;
    for (i = 0; i < 8; i++) {
        unsigned int da = (a >> (i * 4)) & 0xF;
        unsigned int db = (b >> (i * 4)) & 0xF;
        if (da != 0 && db != 0 && da == db) return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00168AE0);

float func_00168BA0(int a0) { return func_00243950(a0) + *(float *)(a0 + 0xC); }

/* func_00168BCC nop pad. */
float func_00168BD0(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}

/* func_00168C14 nop pad. */
float func_00168C18(float *a0, float *a1) {
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}

void func_00168C58(void) {
    int tmp;
    D_00633D08 = 0;
    tmp = *(volatile int *)0x10000000;
    D_00633D0C = 0;
    D_00633D18 = tmp;
    DEFEAT_TCO();
    D_00633D10 = 0;
    D_00633D14 = 0;
    D_00633D1C = 0;
    D_00633D20 = 0;
    D_00633D24 = 0;
    D_00633D28 = 0;
}

int func_00168C88(int a0, int a1) {
    int v = D_006AB100[a1 & 0xF];
    if (v != 0) { func_00105F00(a0, v); return 0; }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00168CC8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00168DA8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00168ED0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169020);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169190);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001692F0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169440);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169580);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001696C0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169800);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169968);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169AA8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169BD0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169D18);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169E58);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00169F80);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016A058);

void func_0016A130(void) {
    D_006323BC = 1;
    /* Cast away the (int) prototype so gcc doesn't emit `daddu $a0,$0,$0`
     * to set up an arg the original call didn't pass. The implementation
     * happens to read $a0 but the original cross-TU caller didn't bother
     * to clear it. */
    ((void (*)(void))func_001683C8)();
    D_006323BC = 0;
}

/* func_0016A154 nop pad. */
int func_0016A158(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    func_00243B60(buf, a0);
    func_00243B60(buf + 4, a1);
    ((int (*)(int *, int))D_006323F0)(buf, 1);
    return buf[34];
}

void func_0016A1B8(int *self) {
    int v0 = self[4];
    int v1 = self[5];
    self[4] = (int)((char *)self + v0);
    self[5] = (int)((char *)self + v1);
}

/* func_0016A1D4 nop pad absorbed into func_0016A1D8's .s. */
extern char D_00632418[];
extern char D_00632420[];
extern int func_00263FB0(float f);

void func_0016A1D8(float *p)
{
    int i = 3;
    do {
        int s = func_00263FB0(*p);
        func_001A6E28(D_00632418, s);
        p++;
        i--;
    } while (i >= 0);
    func_001A6E28(D_00632420);
}

void func_0016A240(int *p) {
    int i = 0;
    do {
        func_001A6E28(D_00632428, i);
        i++;
        func_0016A1D8(p);
        p = (int *)((char *)p + 0x10);
    } while (i < 4);
}

/* func_0016A29C nop pad. */
float func_0016A2A0(float x, float y) { return func_00105FE0(x*x + y*y); }
/* func_0016A2C4 nop pad. */
float func_0016A2C8(float x, float y, float z) { return func_00105FE0(x*x + y*y + z*z); }
/* func_0016A2F4 nop pad. */
float func_0016A2F8(int a0) { return func_00105FE0(func_00243950(a0, a0)); }

/* func_0016A31C nop pad absorbed into func_0016A320's .s. */
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016A320);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016A3B0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016A460);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016A5F0);

void func_0016A678(void) {
    func_0014A3A8();
    func_001A6E28(D_00559430);
}

/* func_0016A69C nop pad absorbed into func_0016A6A0's .s. */
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016A6A0);
/* func_0016AC0C nop pad (between A6A0 and AC10). */
extern int D_0028A890[];
extern void func_00182890(int *p);

void func_0016AC10(void)
{
    func_00182890(D_0028A890);
}

void func_0016AC20(int *self) {
    int v = ((int *)self[0x164/4])[0x30/4];
    if (v == 10) {
        func_0014B330(self, 5, 1.5f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016AC50);

/* String rodata migrated from commonact_data.c */
__attribute__((section(".rodata.0x00558848"))) const char D_00558848[24] = "common rope after func\n";
__attribute__((section(".rodata.0x00558880"))) const char D_00558880[32] = "enter actCommonRope\n";
__attribute__((section(".rodata.0x005588C0"))) const char D_005588C0[24] = "enter actCommonPlay\n";
__attribute__((section(".rodata.0x005588D8"))) const char D_005588D8[24] = "enter actCommonDamage\n";
__attribute__((section(".rodata.0x005588F0"))) const char D_005588F0[24] = "enter actCommonDown\n";
__attribute__((section(".rodata.0x00558908"))) const char D_00558908[24] = "enter actCommonDie\n";
__attribute__((section(".rodata.0x00558960"))) const char D_00558960[24] = "enter actCommonRevive\n";
__attribute__((section(".rodata.0x00558978"))) const char D_00558978[16] = "count =(%d)\n";
__attribute__((section(".rodata.0x00558988"))) const char D_00558988[16] = "level =(%d)\n";
__attribute__((section(".rodata.0x00558998"))) const char D_00558998[16] = "0x%8x -> 0x%8x\n";
__attribute__((section(".rodata.0x00558A90"))) const char D_00558A90[48] = "EMERGENCY COMPLETE CHECK : SPEEDSQ:%f LENSQ:%f\n";
__attribute__((section(".rodata.0x00558B10"))) const char D_00558B10[40] = "EMERGENCY CHECK %d(%d): MAX: %f\n";
__attribute__((section(".rodata.0x00558B80"))) const char D_00558B80[32] = "enter actCommonCliffdown\n";
__attribute__((section(".rodata.0x00558BA0"))) const char D_00558BA0[16] = "act main shoal\n";
__attribute__((section(".rodata.0x00558BB0"))) const char D_00558BB0[24] = "enter actCommonSwim\n";
__attribute__((section(".rodata.0x00558BC8"))) const char D_00558BC8[24] = "enter actCommonDodge\n";
__attribute__((section(".rodata.0x00558BE0"))) const char D_00558BE0[24] = "enter actCommonGuard\n";
__attribute__((section(".rodata.0x00558BF8"))) const char D_00558BF8[32] = "enter motCommonHang None\n";
__attribute__((section(".rodata.0x00558C18"))) const char D_00558C18[32] = "enter motCommonHang Wall\n";
__attribute__((section(".rodata.0x00558C38"))) const char D_00558C38[32] = "enter motCommonHang Cliff\n";
__attribute__((section(".rodata.0x00558C58"))) const char D_00558C58[24] = "enter motCommonNull\n";
__attribute__((section(".rodata.0x00558C70"))) const char D_00558C70[24] = "ready begin %s to %s\n";
__attribute__((section(".rodata.0x00558C88"))) const char D_00558C88[24] = "ready end %s to %s\n";
__attribute__((section(".rodata.0x00558CA0"))) const char D_00558CA0[24] = "exec end %s to %s\n";
__attribute__((section(".rodata.0x00558CB8"))) const char D_00558CB8[24] = "????error %s to %s\n";
__attribute__((section(".rodata.0x00558CD0"))) const char D_00558CD0[16] = " ori  = [%s]\n";
__attribute__((section(".rodata.0x00558CE0"))) const char D_00558CE0[16] = " mot  = [%s]\n";
__attribute__((section(".rodata.0x00558CF0"))) const char D_00558CF0[16] = " mode = [%s]\n";
__attribute__((section(".rodata.0x00558D00"))) const char D_00558D00[16] = "frame = [%f]\n";
__attribute__((section(".rodata.0x00558D10"))) const char D_00558D10[16] = "maxry = [%d]\n";
__attribute__((section(".rodata.0x00558D20"))) const char D_00558D20[16] = " file = [%s]\n";
__attribute__((section(".rodata.0x00558D30"))) const char D_00558D30[16] = " life = [%d]\n";
__attribute__((section(".rodata.0x00558D40"))) const char D_00558D40[24] = "   dw = [%d] [%d]\n";
__attribute__((section(".rodata.0x00558D58"))) const char D_00558D58[24] = "   dc = [%d] [%d]\n";
__attribute__((section(".rodata.0x00558D70"))) const char D_00558D70[16] = "wattr = [%x]\n";
__attribute__((section(".rodata.0x00558D80"))) const char D_00558D80[16] = "bttype= [%d]\n";
__attribute__((section(".rodata.0x00558DA8"))) const char D_00558DA8[16] = "timer=%2d/%2d\n";

/* Float rodata migrated from commonact_data.c */
__attribute__((section(".rodata.0x005588A0"))) const float D_005588A0[4] = { 0.0f, 0.0f, -2e+01f, 1.0f };
__attribute__((section(".rodata.0x005588B0"))) const float D_005588B0[4] = { 0.0f, 0.0f, 2e+01f, 1.0f };
__attribute__((section(".rodata.0x005589D0"))) const float D_005589D0[48] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5e+01f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00558DB8"))) const float D_00558DB8[2] = { 4.172325e-08f, 1.65f };

/* girl_brain_{main,attract}.c.inc carry the rodata + chunk-1 function
 * bodies for the two .c.inc TUs whose __FILE__ anchors live at
 * D_00559528 and D_00559620. They are NOT standalone .c files; they
 * are inline-included here so commonact.o absorbs their symbols. */
#include "girl_brain_main.c.inc"     /* gbm chunk 1: 0x16AE48..0x16D707 */
#include "girl_brain_attract.c.inc"  /* gba chunk 1: 0x16D708..0x16E90F */

/* ====================================================================
 * gbm chunk 2 (.text 0x16E910..0x16EE07) — 3 funcs whose original
 * __FILE__ was "src/girl_brain_main.c.inc". `#line` makes the
 * preprocessor report that __FILE__ for any code inside this region,
 * matching what the original SCEI source emitted.
 * ==================================================================== */
#line 1 "src/girl_brain_main.c.inc"

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016E910);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016EB68);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016EC78);

/* ====================================================================
 * gba chunk 2 (.text 0x16EE08..0x175CDC) — bulk of girl_brain_attract.
 * Matched-C bodies inline; rest is INCLUDE_ASM.
 * ==================================================================== */
#line 1 "src/girl_brain_attract.c.inc"

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016EE08);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016F2A8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016F410);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016F9A8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016FC48);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00170438);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001706E0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00170950);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00170C20);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00170ED8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001712C8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001718F0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00171AB0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00171BC8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00171E48);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00173060);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00173170);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00173268);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001733D0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001734D8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001736B8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00173820);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00174D78);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00174F00);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175098);

extern int D_006ABDE0[100];

void func_001752D0(int *self)
{
    int *p;
    p = (int *)self[0x59];
    D_006ABDE0[0] = 0;
    D_006ABDE0[1] = 0;
    if (p[0xC] != 0x45) {
        *(long long *)((char *)p + 0x20) &= ~0x200LL;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175308);
/* func_0017534C nop pad absorbed into func_00175350's .s. */
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175350);

extern void func_00203AA0(int a0);
/* D_00559AB8 / D_00559AD0 are defined earlier in girl_brain_attract.c.inc */

void func_00175640(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    func_001A6E28(D_00559AB8);
    s0[0x30 / 4] = 0x2;
    func_00203AA0(0);
}

/* func_00175684 nop pad. */

void func_00175688(volatile unsigned int a0)
{
    volatile int local;
    int new_var;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    func_001A6E28(D_00559AD0);
    s0[0x30 / 4] = 0x3;
    new_var = 0;
    func_00203AA0(new_var);
}

/* func_001756CC nop pad absorbed into func_001756D0's .s. */
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001756D0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175800);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001758F8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175A98);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175B58);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00175C18);

void func_00175C70(int x) {
    char *p = (char *)D_00631AE8;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        char *q = *(char **)(sub + 0x678);
        *(int *)(q + 0x3C0) = x;
    }
}

void func_00175C90(void) {
    char *p = (char *)D_00631AE8;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        char *q = *(char **)(sub + 0x678);
        *(int *)(q + 0x3C0) = 0;
    }
}

void func_00175CB0(int a0)
{
    volatile int local = a0;
    int v0 = local;
    int v1 = *(int *)(v0 + 0x164);
    *(int *)(v1 + 0x33C) = 0;
    func_00203AA0(0);
}

#line 480 "src/commonact.c"
