/* Light.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_006309D4;
extern float D_006309D8;
extern float D_006309DC;
extern float D_006309E0;
extern float D_006309E4;
extern float D_006309E8;
extern float D_006309EC;
extern float D_006309F0;
extern float D_006309F4;
extern float D_006309F8;
extern float D_006309FC;
extern float D_00630A00;
extern float D_00630A04;
extern float D_00630A08;
extern float D_00630A0C;
extern float D_00630A10;
extern float D_00630A14;
extern float D_00630A18;
extern float D_00630A1C;
extern float D_00630A20;
extern float D_00630A24;
extern float D_00630A28;
extern float D_00630A2C;
extern float D_00630A30;
extern float D_00630A34;
extern float D_00630A38;
extern char D_00631960[16];
extern char D_00631C70[8];
extern const char D_00631C78[8];
extern const char D_00631C80[8];
extern unsigned int D_00631C88;
extern int D_00631C8C;
extern int D_00631C90;
extern int D_00631C94;
extern const char D_00631C98[8];
extern const char D_00631CA0[8];
extern const char D_00631CA8[8];
extern const char D_00631CB0[8];
extern const char D_00631CB8[8];
extern const char D_00631CC0[8];
extern const char D_00631CC8[8];
extern int D_00632D4C;
extern int D_00632D50;
extern int D_00632D54;

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "Light:NULLになってんで\n" */
const char D_00554C90[24] = "Light:NULL\244\313\244\312\244\303\244\306\244\363\244\307\n";
const char D_00554CA8[16] = "src/Light.c";

/* EUC-JP: "AmbientVolume:NULLになってんで\n" */
const char D_00554CB8[32] = "AmbientVolume:NULL\244\313\244\312\244\303\244\306\244\363\244\307\n";
const char D_00554CD8[32] = "Flat Lights already exist.\n";
const char D_00554CF8[40] = "Added Light is illegal.\n";
const float D_00554D20[4] = { 0.0f, 0.0f, -1e+02f, 1.0f };
const float D_00554D30[4] = { 1e+01f, 0.0f, -25.0f, 1.0f };
const float D_00554D40[4] = { -1e+01f, 0.0f, -25.0f, 1.0f };
const char D_00554D70[64] = "PUSH R2 SELECT LIGHT (%d/3) ('SELECT'RETURN MENU)";
const char D_00554DD0[24] = "(addr 0x%08x <fl) : ";
const char D_00554DE8[24] = "(addr 0x%08x <%2d>) : ";
const char D_00554E48[24] = ":::VIFCODE:UNPACK\n";
const char D_00554E60[24] = ":::VIFCODE:CAL/CNT END\n";
const char D_00554E78[32] = ":::VIFCODE:CAL/CNT-UNPACK\n";
const char D_00554E98[32] = ":::GIFTAG:NLOOP=%d(S:%d)\n";
const char D_00554EB8[24] = ":::PACKET:%s\n";
const float D_00554ED0[4] = { 3e+02f, 3e+02f, 3e+02f, 0.0f };
const float D_005D19E8[12] = { 0.0f, 0.0f, 0.0f, 0.0f, 255.0f, 2e+02f, 1.8e+02f, 1.5e+03f, 128.0f, 1e+02f, 9e+01f, 7.5e+02f };

#include "include_asm.h"
#include "matching.h"
#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00114FC8);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115068);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115108);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115410);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115878);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115ED8);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115FB8);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_001165A8);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00116888);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00116C08);

/* Matched body inlined from src/cod/017750.c during TU coalesce.
 * D_00631C70 already extern'd above (as char[8]); reference via
 * pointer cast to avoid type clash. D_00633C30/34 not in the
 * extern'd set so declare locally. */
extern int D_00633C30;
extern int D_00633C34;
void func_00117750(void) {
    D_00633C30 = 0;
    D_00633C34 = 0;
    *(int *)D_00631C70 = 0;
}

/* Matched body inlined from src/cod/017760.c during TU coalesce. */
void func_00117760(void) {}

extern int D_00633C38;
extern void func_00114FC8(char *node);

void func_00117768(void)
{
    char *p = (char *)D_00633C30;
    while (p != 0) {
        short v = *(short *)(p + 0x44);
        if (v < 4) {
            if (v >= 2) {
                char *node = p;
                p = *(char **)(p + 0x4C);
                func_00114FC8(node);
                continue;
            }
        }
        p = *(char **)(p + 0x4C);
    }
    D_00633C38 = 0;
}
extern void func_00115068(char *node);

void func_001177C8(void)
{
    char *p = (char *)D_00633C34;
    while (p != 0) {
        int v = *(int *)(p + 0x90);
        if (v < 3) {
            if (v >= 0) {
                char *node = p;
                p = *(char **)(p + 0x98);
                func_00115068(node);
                continue;
            }
        }
        p = *(char **)(p + 0x98);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117820);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_0011788C);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117890);
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117950);

/* Matched body inlined from src/cod/017C20.c during TU coalesce. */
void func_00117C20(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0103BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(a3, 22);
    VU0_MTC1(a3, 0);
    VU0_NOREORDER_END();
}

/* Matched body inlined from src/cod/017C40.c during TU coalesce. */
void func_00117C40(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}

TRAILING_PAD_NOP();

/* Matched body inlined from src/cod/017C60.c during TU coalesce. */
void func_00117C60(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}

TRAILING_PAD_NOP();

/* Matched body inlined from src/cod/017C80.c during TU coalesce. */
void func_00117C80(void)
{
    VU0_REG("vsqi.xyzw $vf4, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf5, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf6, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf7, ($vi15++)");
    VU0_NOP();
}

/* Matched body inlined from src/cod/017C98.c during TU coalesce. */
void func_00117C98(void)
{
    VU0_REG("vlqd.xyzw $vf7, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf6, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf5, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf4, (--$vi15)");
    VU0_NOP();
}

/* Matched body inlined from src/cod/017CB0.c during TU coalesce. */
void func_00117CB0(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 7, 8, w);
    VU0_NOP();
}

TRAILING_PAD_NOP();

/* Matched body inlined from src/cod/017CD0.c during TU coalesce. */
void func_00117CD0(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V2OP(vmove.xyzw, 7, 8);
    VU0_NOP();
}

/* Matched body inlined from src/cod/017CE0.c during TU coalesce. */
void func_00117CE0(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_NOP();
}

TRAILING_PAD_NOP();
INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117CF0);
