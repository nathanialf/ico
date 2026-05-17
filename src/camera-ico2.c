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
extern float D_00630EF0;
extern float D_00630EF4;
extern float D_00630EF8;
extern float D_00630EFC;
extern float D_006326E0;
extern unsigned int D_006326E4;
extern char D_006326E8[8];
extern const char D_006326F0[16];
extern unsigned int D_00632700;
extern int D_00632704;
extern const char D_00632708[];
extern const char D_00632710[];
extern const char D_00632718[];
extern const char D_00632720[];
extern unsigned int D_00632728;
extern unsigned int D_0063272C;
extern int D_00632730;
extern int D_00632734;
extern int D_00632CF8;

__attribute__((section(".rodata.0x0055A940"))) const char D_0055A940[24] = "src/camera-ico2.c";

__attribute__((section(".rodata.0x0055AA50"))) const char D_0055AA50[16] = "%d,%d,%d %d";

/* String rodata migrated from camera-ico2_data.c */
__attribute__((section(".rodata.0x0055A9A8"))) const char D_0055A9A8[32] = "camera data version = [%d]\n";
__attribute__((section(".rodata.0x0055A9C8"))) const char D_0055A9C8[24] = "n_group[%d], n_pin[%d]\n";
__attribute__((section(".rodata.0x0055AA28"))) const char D_0055AA28[40] = "illegal camera data version [%d]\n";

/* Float rodata migrated from camera-ico2_data.c */
__attribute__((section(".rodata.0x0055AA60"))) const float D_0055AA60[4] = { 0.0f, -2e+02f, -5e+02f, 0.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "[%s]が見つかりません
" */
__attribute__((section(".rodata.0x0055A958"))) const char D_0055A958[24] = "[%s]\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\n";
/* EUC-JP: "１ステージに登録できるカメラセットは、最大[%d]個です。" */
__attribute__((section(".rodata.0x0055A970"))) const char D_0055A970[56] = "\243\261\245\271\245\306\241\274\245\270\244\313\305\320\317\277\244\307\244\255\244\353\245\253\245\341\245\351\245\273\245\303\245\310\244\317\241\242\272\307\302\347[%d]\270\304\244\307\244\271\241\243";
/* EUC-JP: "カメラデータのバージョンに異常があります。大森まで知らせてください
" */
__attribute__((section(".rodata.0x0055A9E0"))) const char D_0055A9E0[72] = "\245\253\245\341\245\351\245\307\241\274\245\277\244\316\245\320\241\274\245\270\245\347\245\363\244\313\260\333\276\357\244\254\244\242\244\352\244\336\244\271\241\243\302\347\277\271\244\336\244\307\303\316\244\351\244\273\244\306\244\257\244\300\244\265\244\244\n";

#include "include_asm.h"
#include "regpin.h"

/* Matched body inlined from src/cod/0886D0.c during TU coalesce. */
extern char D_006D04B4[];
extern void func_0018CFE0(int a0);
void func_001886D0(int a0)
{
    register char *p REG("$2") = D_006D04B4;
    register int one REG("$3") = 1;
    int masked = a0 & 0xFF;
    *p = (char)one;
    if (masked == 0) {
        return;
    }
    return func_0018CFE0(masked);
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
