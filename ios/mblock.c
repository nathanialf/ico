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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".sdata.0x0063203C"))) int D_0063203C = 0;
__attribute__((section(".sdata.0x00632040"))) char D_00632040[8] = { 0 };
__attribute__((section(".sdata.0x00632048"))) char D_00632048[12] = { 0 };
__attribute__((section(".sdata.0x00632054"))) unsigned int D_00632054 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00632058"))) const char D_00632058[8] = "game.";
__attribute__((section(".sdata.0x00632060"))) char D_00632060[8] = { 0 };
__attribute__((section(".sdata.0x00632068"))) int D_00632068 = 0x000A6425;
__attribute__((section(".sdata.0x0063206C"))) int D_0063206C = 0x00000000;
__attribute__((section(".sdata.0x00632070"))) int D_00632070 = 0x332E3325;
__attribute__((section(".sdata.0x00632074"))) int D_00632074 = 0x00000064;
__attribute__((section(".sdata.0x00632078"))) const char D_00632078[8] = "*";
__attribute__((section(".sdata.0x00632088"))) const char D_00632088[8] = "format";
__attribute__((section(".sdata.0x00632090"))) const char D_00632090[8] = "chdir";
__attribute__((section(".sdata.0x00632098"))) const char D_00632098[8] = "getdir";
__attribute__((section(".sdata.0x006320A0"))) const char D_006320A0[8] = "delete";
__attribute__((section(".sdata.0x006320A8"))) const char D_006320A8[8] = "test";

__attribute__((section(".rodata.0x00556C08"))) const char D_00556C08[24] = "ios/mblock.c";
__attribute__((section(".rodata.0x00556C20"))) const char D_00556C20[16] = "boy_blk.ico";
__attribute__((section(".rodata.0x00556C30"))) const char D_00556C30[16] = "icon.sys";
__attribute__((section(".rodata.0x00556C40"))) const char D_00556C40[16] = "BASCUS-97113ico";
__attribute__((section(".rodata.0x00556E10"))) const char D_00556E10[24] = "/BASCUS-97113ico";
__attribute__((section(".rodata.0x00556E80"))) const char D_00556E80[16] = "Unformat";
__attribute__((section(".rodata.0x00556E90"))) const char D_00556E90[16] = "IconBlock save";
__attribute__((section(".rodata.0x00556EA0"))) const char D_00556EA0[24] = "ProductBlock save";
__attribute__((section(".rodata.0x00556EB8"))) const char D_00556EB8[16] = "GameBlock save";
__attribute__((section(".rodata.0x00556EC8"))) const char D_00556EC8[16] = "GameBlock load";
__attribute__((section(".rodata.0x00556ED8"))) const char D_00556ED8[16] = "chdirproduct";
__attribute__((section(".rodata.0x00556EE8"))) const char D_00556EE8[40] = "iosMcManager: recv command %d error.";

/* String rodata migrated from mblock_data.c */
__attribute__((section(".rodata.0x00556C50"))) const char D_00556C50[32] = "iosMcMgrGetInfo: request busy\n";
__attribute__((section(".rodata.0x00556C70"))) const char D_00556C70[32] = "iosMcMgrFormat: request busy\n";
__attribute__((section(".rodata.0x00556C90"))) const char D_00556C90[32] = "iosMcMgrUnformat: request busy\n";
__attribute__((section(".rodata.0x00556CB0"))) const char D_00556CB0[32] = "iosMcMgrWrite: request busy\n";
__attribute__((section(".rodata.0x00556CD0"))) const char D_00556CD0[32] = "iosMcMgrRead: request busy\n";
__attribute__((section(".rodata.0x00556CF0"))) const char D_00556CF0[32] = "sceMcOpen: request busy\n";
__attribute__((section(".rodata.0x00556D10"))) const char D_00556D10[32] = "sceMcClose: request busy\n";
__attribute__((section(".rodata.0x00556D30"))) const char D_00556D30[32] = "iosMcMgrChdir: request busy\n";
__attribute__((section(".rodata.0x00556D50"))) const char D_00556D50[32] = "sceMcGetdir: request busy\n";
__attribute__((section(".rodata.0x00556D70"))) const char D_00556D70[32] = "iosMcMgrMkdir: request busy\n";
__attribute__((section(".rodata.0x00556D90"))) const char D_00556D90[32] = "iosMcMgrDelete: request busy\n";
__attribute__((section(".rodata.0x00556E28"))) const char D_00556E28[24] = "write checkSum: %d\n";
__attribute__((section(".rodata.0x00556E40"))) const char D_00556E40[16] = "call read_func\n";
__attribute__((section(".rodata.0x00556E50"))) const char D_00556E50[32] = "sceMcSeek: request busy\n";
__attribute__((section(".rodata.0x00556E70"))) const char D_00556E70[16] = "done 0 %p\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "iosMcHandlerRead: メモリカードからデータ読めなかった(リクエストの方がサイズ大きい) %d %d
" */
__attribute__((section(".rodata.0x00556DB0"))) const char D_00556DB0[96] = "iosMcHandlerRead: \245\341\245\342\245\352\245\253\241\274\245\311\244\253\244\351\245\307\241\274\245\277\306\311\244\341\244\312\244\253\244\303\244\277(\245\352\245\257\245\250\245\271\245\310\244\316\312\375\244\254\245\265\245\244\245\272\302\347\244\255\244\244) %d %d\n";
