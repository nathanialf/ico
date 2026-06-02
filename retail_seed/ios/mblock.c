/* mblock.c -- typed sdata / lit4 definitions for this TU.
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

const char D_00556C08[24] = "ios/mblock.c";
const char D_00556C20[16] = "boy_blk.ico";
const char D_00556C30[16] = "icon.sys";
const char D_00556C40[16] = "BASCUS-97113ico";
const char D_00556C50[32] = "iosMcMgrGetInfo: request busy\n";
const char D_00556C70[32] = "iosMcMgrFormat: request busy\n";
const char D_00556C90[32] = "iosMcMgrUnformat: request busy\n";
const char D_00556CB0[32] = "iosMcMgrWrite: request busy\n";
const char D_00556CD0[32] = "iosMcMgrRead: request busy\n";
const char D_00556CF0[32] = "sceMcOpen: request busy\n";
const char D_00556D10[32] = "sceMcClose: request busy\n";
const char D_00556D30[32] = "iosMcMgrChdir: request busy\n";
const char D_00556D50[32] = "sceMcGetdir: request busy\n";
const char D_00556D70[32] = "iosMcMgrMkdir: request busy\n";
const char D_00556D90[32] = "iosMcMgrDelete: request busy\n";
const char D_00556DB0[96] = "iosMcHandlerRead: \245\341\245\342\245\352\245\253\241\274\245\311\244\253\244\351\245\307\241\274\245\277\306\311\244\341\244\312\244\253\244\303\244\277(\245\352\245\257\245\250\245\271\245\310\244\316\312\375\244\254\245\265\245\244\245\272\302\347\244\255\244\244) %d %d\n";
const char D_00556E10[24] = "/BASCUS-97113ico";
const char D_00556E28[24] = "write checkSum: %d\n";
const char D_00556E40[16] = "call read_func\n";
const char D_00556E50[32] = "sceMcSeek: request busy\n";
const char D_00556E70[16] = "done 0 %p\n";
const char D_00556E80[16] = "Unformat";
const char D_00556E90[16] = "IconBlock save";
const char D_00556EA0[24] = "ProductBlock save";
const char D_00556EB8[16] = "GameBlock save";
const char D_00556EC8[16] = "GameBlock load";
const char D_00556ED8[16] = "chdirproduct";
const char D_00556EE8[40] = "iosMcManager: recv command %d error.";
int D_0063203C = 0;
char D_00632040[8] = { 0 };
char D_00632048[12] = { 0 };
unsigned int D_00632054 = 0xFFFFFFFF;
const char D_00632058[8] = "game.";
char D_00632060[8] = { 0 };
int D_00632068 = 0x000A6425;
int D_0063206C = 0x00000000;
int D_00632070 = 0x332E3325;
int D_00632074 = 0x00000064;
const char D_00632078[8] = "*";
const char D_00632088[8] = "format";
const char D_00632090[8] = "chdir";
const char D_00632098[8] = "getdir";
const char D_006320A0[8] = "delete";
const char D_006320A8[8] = "test";
