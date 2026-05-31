/* camera-ico2.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_00630ED8;
extern float D_00630EDC;
extern float D_00630EE0;
extern float D_00630EE4;
extern float D_00630EE8;
extern float D_00630EEC;
extern float D_006326E0;
extern int D_00632CF8;

unsigned int D_00280FC0[60] = { 0x78057805, 0x78057805, 0x78057805, 0x78057805, 0x78057805, 0x78057805, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x0000001E, 0x00000005, 0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080, 0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000 };

float D_0028AF50[8] = { 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 52.0f, 0.0f, 0.0f };

unsigned int D_0028AF70[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_0028AFB0[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x43B40000, 0x42340000, 0x00000001, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_0028AFF0[56] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x428C0000, 0x00000100, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

const char D_0055A940[24] = "src/camera-ico2.c";

/* EUC-JP: "[%s]が見つかりません\n" */
const char D_0055A958[24] = "[%s]\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\n";

/* EUC-JP: "１ステージに登録できるカメラセットは、最大[%d]個です。" */
const char D_0055A970[56] = "\243\261\245\271\245\306\241\274\245\270\244\313\305\320\317\277\244\307\244\255\244\353\245\253\245\341\245\351\245\273\245\303\245\310\244\317\241\242\272\307\302\347[%d]\270\304\244\307\244\271\241\243";

const char D_0055A9A8[32] = "camera data version = [%d]\n";

const char D_0055A9C8[24] = "n_group[%d], n_pin[%d]\n";

/* EUC-JP: "カメラデータのバージョンに異常があります。大森まで知らせてください\n" */
const char D_0055A9E0[72] = "\245\253\245\341\245\351\245\307\241\274\245\277\244\316\245\320\241\274\245\270\245\347\245\363\244\313\260\333\276\357\244\254\244\242\244\352\244\336\244\271\241\243\302\347\277\271\244\336\244\307\303\316\244\351\244\273\244\306\244\257\244\300\244\265\244\244\n";

const char D_0055AA28[40] = "illegal camera data version [%d]\n";

const char D_0055AA50[16] = "%d,%d,%d %d";

const float D_0055AA60[4] = { 0.0f, -2e+02f, -5e+02f, 0.0f };

const double D_0055AB48 = 6.283185307179586;

const double D_0055AB50 = 3.1415927410125732;

const double D_0055AB78 = 6.283185307179586;

const double D_0055AB80 = 3.1415927410125732;

unsigned int D_006326E4 = 0x7F7FFFFF;

unsigned char D_006326E8[8] = { 0 };

const char D_006326F0[16] = "0";

unsigned int D_00632700 = 0x00000002;

unsigned int D_00632704 = 0x00000000;

const char D_00632708[8] = "FREECAM";

const char D_00632710[8] = "GAMECAM";

const char D_00632718[8] = "HANDCAM";

const char D_00632720[8] = "PATHCAM";

unsigned int D_00632728 = 0x00000001;

unsigned int D_0063272C = 0x00000003;

unsigned int D_00632730 = 0x00000000;

unsigned int D_00632734 = 0x00000000;

unsigned int D_00632738 = 0x00000000;

unsigned int D_0063273C = 0x00000000;

unsigned int D_00632CB4 = 0x00000000;

unsigned int D_00632CC4 = 0x00000000;

unsigned int D_00632D30 = 0x00000000;

unsigned int D_00632D34 = 0x00000000;

unsigned int D_00632D38 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from camera-ico2_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from camera-ico2_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630EF0 = 3.1415927f;
float D_00630EF4 = 3.1415927f;
float D_00630EF8 = 3.1415927f;
float D_00630EFC = 3.1415927f;
float D_00630F00 = -0.2f;
float D_00630F04 = 0.1f;
float D_00630F08 = 3.1415927f;
float D_00630F0C = 0.6f;
float D_00630F10 = -0.01f;
float D_00630F14 = -0.05f;
float D_00630F18 = -0.15f;
float D_00630F1C = -0.01f;
float D_00630F20 = -0.05f;
float D_00630F24 = -0.15f;
float D_00630F28 = -0.01f;
float D_00630F2C = -0.2f;
float D_00630F30 = -0.3f;
float D_00630F34 = -0.05f;
float D_00630F38 = -0.15f;
float D_00630F3C = -1.5707964f;
float D_00630F40 = -0.01f;
float D_00630F44 = -0.05f;
float D_00630F48 = -0.15f;
float D_00630F4C = -0.01f;
float D_00630F50 = -0.05f;
float D_00630F54 = -0.15f;
float D_00630F58 = -1.5707964f;
float D_00630F5C = -0.05f;
float D_00630F60 = 0.675f;
float D_00630F64 = 3.1415927f;
float D_00630F68 = 0.2f;
float D_00630F6C = 3.1415927f;
float D_00630F70 = 3.1415927f;
float D_00630F74 = -0.2f;
float D_00630F78 = 0.1f;
float D_00630F7C = -0.2f;
float D_00630F80 = 0.1f;
float D_00630F84 = 0.1f;
float D_00630F88 = -0.1f;
float D_00630F8C = 3.1415927f;
float D_00630F90 = -0.2f;
float D_00630F94 = 0.1f;

/* Inlined data (Phase 3e) — migrated from camera-ico2_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* pointer / address tables */
void *D_002810B0[8] = { (void *)0x005575E0, (void *)0x00632138, (void *)0x005575D0, (void *)0x00632130, (void *)0x00632130, (void *)0x00632128, (void *)0x00632120, (void *)0x00632118 };

#include "include_asm.h"
#include "regpin.h"

/* Matched body inlined from src/cod/0886D0.c during TU coalesce. */
extern char D_006D04B4[];
extern void func_0018CFE0(int a0);
void func_001886D0(int a0)
{
    char *p = D_006D04B4;
    int one = 1;
    int masked = a0 & 0xFF;
    *p = (char)one;
    if (masked == 0) {
        return;
    }
    func_0018CFE0(masked);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001886F4);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001886F8);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188C98);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00188E30);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_001897A8);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189AC8);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189B88);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_00189D68);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018A400);

/* Matched body inlined from src/cod/08B098.c during TU coalesce. */
extern float D_006326E0;
void func_0018B098(float val) {
    D_006326E0 = val;
}

/* Matched body inlined from src/cod/08B0A0.c during TU coalesce. */
extern int D_00633D64;
int func_0018B0A0(void) {
    return D_00633D64;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B0A8);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B180);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", func_0018B248);

/* Matched body inlined from src/cod/08B2F8.c during TU coalesce. */
extern int D_00633D74;
void func_0018B2F8(void) {
    D_00633D74 = 0;
}
