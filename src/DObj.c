/* DObj.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00612620"))) const char D_00612620[16] = "src/DObj.c";

__attribute__((section(".rodata.0x006127E8"))) const char D_006127E8[24] = "DFDATAS/COMMON.DF";
__attribute__((section(".rodata.0x00612890"))) const char D_00612890[16] = "girl nokori";

/* String rodata migrated from DObj_data.c */
__attribute__((section(".rodata.0x006126B8"))) const char D_006126B8[24] = "----- MASK LINK -----\n";
__attribute__((section(".rodata.0x006126D0"))) const char D_006126D0[24] = "sound partition reset\n";
__attribute__((section(".rodata.0x006126E8"))) const char D_006126E8[32] = "sound partition not reset\n";
__attribute__((section(".rodata.0x00612708"))) const char D_00612708[16] = "InitTableSin\n";
__attribute__((section(".rodata.0x00612718"))) const char D_00612718[24] = "InitMatrixDrive\n";
__attribute__((section(".rodata.0x00612730"))) const char D_00612730[16] = "debug_Init\n";
__attribute__((section(".rodata.0x00612740"))) const char D_00612740[24] = "p2o transMicroProgram\n";
__attribute__((section(".rodata.0x00612758"))) const char D_00612758[16] = "InitGSSystem\n";
__attribute__((section(".rodata.0x00612768"))) const char D_00612768[24] = "init debug menu\n";
__attribute__((section(".rodata.0x00612780"))) const char D_00612780[16] = "enable vsync\n";
__attribute__((section(".rodata.0x00612790"))) const char D_00612790[16] = "auto stack %d\n";
__attribute__((section(".rodata.0x006127A0"))) const char D_006127A0[32] = "-----------------Enable VSync\n";
__attribute__((section(".rodata.0x006127C0"))) const char D_006127C0[40] = "preload %s move %d total %d reset %d\n";
__attribute__((section(".rodata.0x00612800"))) const char D_00612800[24] = "stage manager() in\n";
__attribute__((section(".rodata.0x00612818"))) const char D_00612818[16] = "IosCdLock %d\n";
__attribute__((section(".rodata.0x00612828"))) const char D_00612828[24] = "STAGE MANAGER START\n";
__attribute__((section(".rodata.0x00612840"))) const char D_00612840[24] = "out of stage %d\n";
__attribute__((section(".rodata.0x006128F8"))) const char D_006128F8[40] = "backstage timeLimit gamesys area error\n";
__attribute__((section(".rodata.0x00612920"))) const char D_00612920[16] = "way num %d\n";
__attribute__((section(".rodata.0x00612930"))) const char D_00612930[32] = "%d %d:dist %f calcdist %f\n";
__attribute__((section(".rodata.0x00612950"))) const char D_00612950[24] = "set pos_table %f %f %f\n";
__attribute__((section(".rodata.0x006129F0"))) const char D_006129F0[24] = "set pos %f %f %f\n";

/* Float rodata migrated from DObj_data.c */
__attribute__((section(".rodata.0x00612630"))) const float D_00612630[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

/* String-pool rodata migrated from DObj_data.c */
__attribute__((section(".rodata.0x00612858"))) const char D_00612858[56] = "StageManager:unknown msg\n\000\000\000\000\000\000\000stage manager() out\n\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "繋がりACTIVEでみつからなかった" */
__attribute__((section(".rodata.0x006128A0"))) const char D_006128A0[32] = "\267\322\244\254\244\352ACTIVE\244\307\244\337\244\304\244\253\244\351\244\312\244\253\244\303\244\277";
/* EUC-JP: "繋がりみつからなかったのでヒロインの位置に巣を配置" */
__attribute__((section(".rodata.0x006128C0"))) const char D_006128C0[56] = "\267\322\244\254\244\352\244\337\244\304\244\253\244\351\244\312\244\253\244\303\244\277\244\316\244\307\245\322\245\355\245\244\245\363\244\316\260\314\303\326\244\313\301\343\244\362\307\333\303\326";
/* EUC-JP: "WAY候補無し" */
__attribute__((section(".rodata.0x00612968"))) const char D_00612968[16] = "WAY\270\365\312\344\314\265\244\267";
/* EUC-JP: "ヒロイン捕まっていないのでランダムで位置変更" */
__attribute__((section(".rodata.0x00612978"))) const char D_00612978[48] = "\245\322\245\355\245\244\245\363\312\341\244\336\244\303\244\306\244\244\244\312\244\244\244\316\244\307\245\351\245\363\245\300\245\340\244\307\260\314\303\326\312\321\271\271";
/* EUC-JP: "ヒロイン捕まってない" */
__attribute__((section(".rodata.0x006129A8"))) const char D_006129A8[24] = "\245\322\245\355\245\244\245\363\312\341\244\336\244\303\244\306\244\312\244\244";
/* EUC-JP: "巣までの経路がみつからないので直接巣に配置" */
__attribute__((section(".rodata.0x006129C0"))) const char D_006129C0[48] = "\301\343\244\336\244\307\244\316\267\320\317\251\244\254\244\337\244\304\244\253\244\351\244\312\244\244\244\316\244\307\304\276\300\334\301\343\244\313\307\333\303\326";

#include "include_asm.h"

extern int D_00632010;
extern int func_0013A0F8(int a0, int a1, int *a2, int a3);
extern void func_00103120(int v, int *self);

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019E648);
INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019EB88);
INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019ED30);

void func_0019EF10(int *self) {
    int v = func_0013A0F8(D_00632010, self[0x88/4] << 6, (int*)D_00612620, 0x14C);
    self[0x90/4] = v;
    func_00103120(v, self);
}

INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019EF58);
INCLUDE_ASM("asm/nonmatchings/src/DObj", func_0019F310);
