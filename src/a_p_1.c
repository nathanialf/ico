/* a_p_1.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633210"))) const char D_00633210[8] = "e";
__attribute__((section(".sdata.0x00633218"))) const char D_00633218[8] = "SL";
__attribute__((section(".sdata.0x00633220"))) const char D_00633220[8] = "DE";
__attribute__((section(".sdata.0x00633228"))) const char D_00633228[8] = "AT";
__attribute__((section(".sdata.0x00633230"))) const char D_00633230[8] = "JM";
__attribute__((section(".sdata.0x00633238"))) const char D_00633238[8] = "WA";
__attribute__((section(".sdata.0x00633240"))) const char D_00633240[8] = "ST";
__attribute__((section(".sdata.0x00633248"))) const char D_00633248[8] = "--";
__attribute__((section(".sdata.0x00633250"))) const char D_00633250[8] = "SLEEP";
__attribute__((section(".sdata.0x00633258"))) const char D_00633258[8] = "DEAD";
__attribute__((section(".sdata.0x00633260"))) const char D_00633260[8] = "ATTACK";
__attribute__((section(".sdata.0x00633268"))) const char D_00633268[8] = "JUMP";
__attribute__((section(".sdata.0x00633270"))) const char D_00633270[8] = "WALK";
__attribute__((section(".sdata.0x00633278"))) const char D_00633278[8] = "STAND";

__attribute__((section(".rodata.0x00618550"))) const char D_00618550[16] = "src/a_p_1.c";

/* String rodata migrated from a_p_1_data.c */
__attribute__((section(".rodata.0x00618560"))) const char D_00618560[32] = "--- WARNING!! ----\n";

/* Float rodata migrated from a_p_1_data.c */
__attribute__((section(".rodata.0x00618580"))) const float D_00618580[4] = { 5e+01f, 0.0f, 0.0f, 1.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "蜘蛛の抜けによる落下死リクエスト
" */
__attribute__((section(".rodata.0x00618590"))) const char D_00618590[40] = "\303\330\351\341\244\316\310\264\244\261\244\313\244\350\244\353\315\356\262\274\273\340\245\352\245\257\245\250\245\271\245\310\n";
/* EUC-JP: "既に死んでいるので起こしません
" */
__attribute__((section(".rodata.0x006185B8"))) const char D_006185B8[32] = "\264\373\244\313\273\340\244\363\244\307\244\244\244\353\244\316\244\307\265\257\244\263\244\267\244\336\244\273\244\363\n";
/* EUC-JP: "強制死亡
" */
__attribute__((section(".rodata.0x006185D8"))) const char D_006185D8[16] = "\266\257\300\251\273\340\313\264\n";
