/* kanban.c -- typed sdata / lit4 definitions for this TU.
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

extern const char D_00633008[8];
extern const char D_00633010[8];
extern unsigned int D_00633018;
extern int D_0063301C;
extern int D_00633020;
extern int D_00633024;
extern char D_00633028[8];
extern unsigned int D_00633030;
extern unsigned int D_00633034;
extern int D_00633038;
extern int D_0063303C;
extern unsigned int D_00633040;
extern unsigned int D_00633044;
extern int D_00633048;
extern int D_0063304C;
extern int D_00633050;
extern int D_00633054;
extern int D_00633058;
extern int D_0063305C;

__attribute__((section(".rodata.0x00616CA8"))) const char D_00616CA8[24] = "src/kanban.c";

/* String rodata migrated from kanban_data.c */
__attribute__((section(".rodata.0x00616C90"))) const char D_00616C90[24] = "no texture loaded.(%s)\n";
__attribute__((section(".rodata.0x00616CE0"))) const char D_00616CE0[16] = "sync end\n";
__attribute__((section(".rodata.0x00616CF0"))) const char D_00616CF0[16] = "unformatted %d\n";
__attribute__((section(".rodata.0x00616D00"))) const char D_00616D00[32] = "not insert memory card %d\n";
__attribute__((section(".rodata.0x00616D20"))) const char D_00616D20[24] = "%s file not found\n";
__attribute__((section(".rodata.0x00616D38"))) const char D_00616D38[24] = "%s Directory not found\n";
__attribute__((section(".rodata.0x00616D50"))) const char D_00616D50[48] = "segID %d check sum err rom:%d != load:%d\n";
__attribute__((section(".rodata.0x00616D80"))) const char D_00616D80[32] = "%s handler func ret err code\n";
__attribute__((section(".rodata.0x00616DA0"))) const char D_00616DA0[16] = "memory over\n";
__attribute__((section(".rodata.0x00616DB0"))) const char D_00616DB0[32] = "memory card another err %d\n";
__attribute__((section(".rodata.0x00616ED8"))) const char D_00616ED8[16] = "no memoca\n";
__attribute__((section(".rodata.0x00616EE8"))) const char D_00616EE8[16] = "no free\n";
__attribute__((section(".rodata.0x00616F38"))) const char D_00616F38[24] = "load processing\n";
__attribute__((section(".rodata.0x00616F50"))) const char D_00616F50[16] = "case %d\n";
__attribute__((section(".rodata.0x00616F60"))) const char D_00616F60[24] = "McLoad phase:%d  %x\n";
__attribute__((section(".rodata.0x00616F78"))) const char D_00616F78[16] = "phase++\n";
__attribute__((section(".rodata.0x00616F88"))) const char D_00616F88[16] = "through\n";
__attribute__((section(".rodata.0x00616F98"))) const char D_00616F98[24] = "=== LoadGameBlock ===\n";
__attribute__((section(".rodata.0x00616FB0"))) const char D_00616FB0[16] = "case 10\n";
__attribute__((section(".rodata.0x00616FC0"))) const char D_00616FC0[16] = "stage no %d\n";
__attribute__((section(".rodata.0x00617028"))) const char D_00617028[32] = "save game check port %d\n";
__attribute__((section(".rodata.0x00617048"))) const char D_00617048[24] = "sucess :%d %d %d\n";
__attribute__((section(".rodata.0x00617080"))) const char D_00617080[16] = "format 2\n";
__attribute__((section(".rodata.0x00617090"))) const char D_00617090[16] = "unformat 2\n";
__attribute__((section(".rodata.0x006170A0"))) const char D_006170A0[32] = "already exist save data\n";
__attribute__((section(".rodata.0x006170C0"))) const char D_006170C0[32] = "new save. system data making..\n";
__attribute__((section(".rodata.0x006170E0"))) const char D_006170E0[32] = "McSave phase:%d  %x\n";
__attribute__((section(".rodata.0x00617130"))) const char D_00617130[16] = "save error? %d\n";
__attribute__((section(".rodata.0x00617170"))) const char D_00617170[24] = "save complete %d %d\n";
__attribute__((section(".rodata.0x00617188"))) const char D_00617188[16] = "%d %d %d\n";
__attribute__((section(".rodata.0x00617198"))) const char D_00617198[24] = "push start\n";
__attribute__((section(".rodata.0x0062DF08"))) const char D_0062DF08[32] = "end of packet making...\n";

/* String-pool rodata migrated from kanban_data.c */
__attribute__((section(".rodata.0x00623528"))) const char D_00623528[1664] = "Tex_menu01/scei.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/title.tm2\000\000\000\000\000\000\000\000\000\000\000\000Font/font.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/scei_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cursor.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/option.tm2\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/stage.tm2\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/mc01.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/mc02.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/mc04.tm2\000\000\000\000\000\000\000\000\000\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "debug_mcLoadMainBlock:既に設定された数以上のデータを保存してる
" */
__attribute__((section(".rodata.0x00616E18"))) const char D_00616E18[72] = "debug_mcLoadMainBlock:\264\373\244\313\300\337\304\352\244\265\244\354\244\277\277\364\260\312\276\345\244\316\245\307\241\274\245\277\244\362\312\335\302\270\244\267\244\306\244\353\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001AFCC8);
INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001AFE50);
INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001AFF50);
INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B0200);
INCLUDE_ASM("asm/nonmatchings/src/kanban", func_001B0348);
extern int *D_00633E6C;

void func_001B04E0(int *a0)
{
    int *next = (int *)a0[7];
    int *prev = (int *)a0[6];
    if (next == 0) {
        D_00633E6C = prev;
        if (prev != 0) {
            prev[7] = 0;
        }
    } else {
        if (prev != 0) {
            next[6] = (int)prev;
            ((int *)a0[6])[7] = a0[7];
        }
    }
    a0[0] = 0;
}
