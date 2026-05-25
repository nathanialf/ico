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


unsigned char D_002757D0[24] = { 0 };

unsigned char D_002F2DC0[53824] = { 0 };

unsigned char D_00300000[65536] = { 0 };

unsigned char D_00310000[131072] = { 0 };

unsigned char D_00330000[65536] = { 0 };

unsigned char D_00340000[65536] = { 0 };

unsigned char D_00350000[65536] = { 0 };

unsigned char D_00360000[124] = { 0 };

unsigned char D_003705E0[68] = { 0 };

unsigned char D_00370D58[62276] = { 0 };

unsigned int D_00390094 = 0x00000000;

unsigned char D_00390098[67468] = { 0 };

unsigned char D_003B0000[1856] = { 0 };

unsigned char D_003B0740[63680] = { 0 };

unsigned char D_003C0000[65712] = { 0 };

unsigned char D_003D00B0[65536] = { 0 };

unsigned char D_003E00B0[65360] = { 0 };

unsigned char D_003F0000[65536] = { 0 };

unsigned char D_00400000[144] = { 0 };

unsigned char D_00400090[65392] = { 0 };

unsigned char D_00410000[65536] = { 0 };

unsigned char D_00420000[160] = { 0 };

unsigned char D_004200A0[65376] = { 0 };

unsigned char D_00430000[65768] = { 0 };

unsigned char D_004400E8[3888] = { 0 };

unsigned char D_00441018[61472] = { 0 };

unsigned int D_00450038 = 0x00000000;

unsigned char D_00450050[280] = { 0 };

unsigned char D_00450168[327636] = { 0 };

unsigned char D_004B2DC0[48] = { 0 };

unsigned char D_004B2DF0[16] = { 0 };

unsigned char D_004B2E00[464] = { 0 };

unsigned int D_004B2FD0[74] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x006328D0, 0x006328C8, 0x006328E0, 0x006328D8, 0x006328F0, 0x006328E8, 0x00613AA0, 0x00613A90, 0x00613A80, 0x00613A70, 0x006328F0, 0x00613AC0, 0x00613AB0, 0x00000000, 0x00613AD0, 0x006328F8, 0x00632908, 0x00632900, 0x006328D8, 0x00613AE0, 0x00632918, 0x00632910, 0x00632988, 0x00632980, 0x00632978, 0x00632970, 0x00632968, 0x00632960, 0x00632958, 0x00632950, 0x00632948, 0x00632940, 0x00632938, 0x00632930, 0x00632928, 0x00632920, 0x00613B20, 0x00613B10, 0x00613B00, 0x00613AF0, 0x006329A0, 0x00632998, 0x00632990, 0x00000000, 0x006329A0, 0x00613B50, 0x00613B40, 0x00613B30, 0x006329A0, 0x006329B0, 0x00613B60, 0x006329A8, 0x006328E8, 0x00613B70, 0x006329B8, 0x006328F0, 0x006329A0, 0x00613B90, 0x00613B80, 0x006329A8, 0x006329E0, 0x006329D8, 0x006329D0, 0x006329C8, 0x006329C0, 0x00000000 };

const char D_00612620[16] = "src/DObj.c";

const float D_00612630[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

const char D_006126B8[24] = "----- MASK LINK -----\n";

const char D_006126D0[24] = "sound partition reset\n";

const char D_006126E8[32] = "sound partition not reset\n";

const char D_00612708[16] = "InitTableSin\n";

const char D_00612718[24] = "InitMatrixDrive\n";

const char D_00612730[16] = "debug_Init\n";

const char D_00612740[24] = "p2o transMicroProgram\n";

const char D_00612758[16] = "InitGSSystem\n";

const char D_00612768[24] = "init debug menu\n";

const char D_00612780[16] = "enable vsync\n";

const char D_00612790[16] = "auto stack %d\n";

const char D_006127A0[32] = "-----------------Enable VSync\n";

const char D_006127C0[40] = "preload %s move %d total %d reset %d\n";

const char D_006127E8[24] = "DFDATAS/COMMON.DF";

const char D_00612800[24] = "stage manager() in\n";

const char D_00612818[16] = "IosCdLock %d\n";

const char D_00612828[24] = "STAGE MANAGER START\n";

const char D_00612840[24] = "out of stage %d\n";

const char D_00612858[56] = "StageManager:unknown msg\n\000\000\000\000\000\000\000stage manager() out\n\000\000\000";

const char D_00612890[16] = "girl nokori";

const char D_006128A0[32] = "\267\322\244\254\244\352ACTIVE\244\307\244\337\244\304\244\253\244\351\244\312\244\253\244\303\244\277";

const char D_006128C0[56] = "\267\322\244\254\244\352\244\337\244\304\244\253\244\351\244\312\244\253\244\303\244\277\244\316\244\307\245\322\245\355\245\244\245\363\244\316\260\314\303\326\244\313\301\343\244\362\307\333\303\326";

const char D_006128F8[40] = "backstage timeLimit gamesys area error\n";

const char D_00612920[16] = "way num %d\n";

const char D_00612930[32] = "%d %d:dist %f calcdist %f\n";

const char D_00612950[24] = "set pos_table %f %f %f\n";

const char D_00612968[16] = "WAY\270\365\312\344\314\265\244\267";

const char D_00612978[48] = "\245\322\245\355\245\244\245\363\312\341\244\336\244\303\244\306\244\244\244\312\244\244\244\316\244\307\245\351\245\363\245\300\245\340\244\307\260\314\303\326\312\321\271\271";

const char D_006129A8[24] = "\245\322\245\355\245\244\245\363\312\341\244\336\244\303\244\306\244\312\244\244";

const char D_006129C0[48] = "\301\343\244\336\244\307\244\316\267\320\317\251\244\254\244\337\244\304\244\253\244\351\244\312\244\244\244\316\244\307\304\276\300\334\301\343\244\313\307\333\303\326";

const char D_006129F0[24] = "set pos %f %f %f\n";

unsigned char D_006319A0[16] = { 0 };

unsigned char D_00631A10[16] = { 0 };

unsigned char D_00631AB0[16] = { 0 };

unsigned char D_00631AC0[16] = { 0 };

unsigned int D_00631B14 = 0x00000000;

unsigned char D_00631B18[8] = { 0 };

unsigned int D_00631B20 = 0x00000000;

unsigned int D_00631B24 = 0x00000000;

const char D_00631B28[8] = "0";

const char D_00631B30[8] = "e";

unsigned int D_00631B38 = 0x00000030;

unsigned int D_00631B3C = 0x00000000;

unsigned int D_00632000 = 0x00000000;

unsigned int D_00632004 = 0x00000000;

unsigned int D_00632834 = 0x00000000;

unsigned int D_0063283C = 0x80000000;

unsigned int D_00632840 = 0x00000000;

unsigned int D_00632844 = 0x00000000;

const char D_00632848[8] = "here\n";

unsigned int D_00632850 = 0x00000000;

unsigned int D_00632854 = 0x00000000;

unsigned int D_00632858 = 0x00000000;

unsigned int D_0063285C = 0x00000000;

unsigned int D_00632860 = 0x00000000;

unsigned int D_00632864 = 0x00000000;

unsigned int D_00632868 = 0x00000000;

unsigned int D_0063286C = 0x00000000;

unsigned char D_00632870[8] = { 0 };

const char D_00632878[8] = "done";

unsigned int D_00632880 = 0x00000000;

unsigned int D_00632884 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from DObj_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

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
