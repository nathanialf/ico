/* stormTest.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006313E0"))) float D_006313E0 = 0.181818187f;
__attribute__((section(".lit4.0x006313E4"))) float D_006313E4 = 0.9f;
__attribute__((section(".lit4.0x006313E8"))) float D_006313E8 = 0.1f;
__attribute__((section(".lit4.0x006313EC"))) float D_006313EC = 0.1f;
__attribute__((section(".lit4.0x006313F0"))) float D_006313F0 = 1500.0f;
__attribute__((section(".lit4.0x006313F4"))) float D_006313F4 = 0.1f;
__attribute__((section(".lit4.0x006313F8"))) float D_006313F8 = 182.044449f;
__attribute__((section(".lit4.0x006313FC"))) float D_006313FC = 0.7f;
__attribute__((section(".lit4.0x00631400"))) float D_00631400 = 0.7f;
__attribute__((section(".lit4.0x00631404"))) float D_00631404 = 0.9f;
__attribute__((section(".lit4.0x00631408"))) float D_00631408 = 0.1f;
__attribute__((section(".lit4.0x0063140C"))) float D_0063140C = 0.1f;
__attribute__((section(".lit4.0x00631410"))) float D_00631410 = 0.01f;
__attribute__((section(".lit4.0x00631414"))) float D_00631414 = 0.1f;
__attribute__((section(".lit4.0x00631418"))) float D_00631418 = 0.7f;
__attribute__((section(".lit4.0x0063141C"))) float D_0063141C = 0.8f;
__attribute__((section(".lit4.0x00631420"))) float D_00631420 = 0.02f;
__attribute__((section(".lit4.0x00631424"))) float D_00631424 = 0.05f;
__attribute__((section(".lit4.0x00631428"))) float D_00631428 = 8.99999f;
__attribute__((section(".lit4.0x0063142C"))) float D_0063142C = 8.99999f;

__attribute__((section(".rodata.0x0061A470"))) const char D_0061A470[16] = "src/stormTest.c";

__attribute__((section(".rodata.0x0061A650"))) const char D_0061A650[24] = "STANDBY %d CHARS %s";

/* String rodata migrated from stormTest_data.c */
__attribute__((section(".rodata.0x0061A558"))) const char D_0061A558[32] = "delete stream motion manager\n";
__attribute__((section(".rodata.0x0061A578"))) const char D_0061A578[32] = "disable automatic delete\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "ストリームモーション開始時にデータの転送が間に合っていませんでした。
" */
__attribute__((section(".rodata.0x0061A480"))) const char D_0061A480[72] = "\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\263\253\273\317\273\376\244\313\245\307\241\274\245\277\244\316\305\276\301\367\244\254\264\326\244\313\271\347\244\303\244\306\244\244\244\336\244\273\244\363\244\307\244\267\244\277\241\243\n";
/* EUC-JP: "ストリームモーションのデータ転送が間に合っていません。
" */
__attribute__((section(".rodata.0x0061A4C8"))) const char D_0061A4C8[56] = "\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\244\316\245\307\241\274\245\277\305\276\301\367\244\254\264\326\244\313\271\347\244\303\244\306\244\244\244\336\244\273\244\363\241\243\n";
/* EUC-JP: "データがまだ来ていないのにワークサイズの取得をしようとしました
" */
__attribute__((section(".rodata.0x0061A598"))) const char D_0061A598[64] = "\245\307\241\274\245\277\244\254\244\336\244\300\315\350\244\306\244\244\244\312\244\244\244\316\244\313\245\357\241\274\245\257\245\265\245\244\245\272\244\316\274\350\306\300\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\n";
/* EUC-JP: "データがまだ来ていないのにストリームモーションの取得をしようとしました
" */
__attribute__((section(".rodata.0x0061A5E0"))) const char D_0061A5E0[72] = "\245\307\241\274\245\277\244\254\244\336\244\300\315\350\244\306\244\244\244\312\244\244\244\316\244\313\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\244\316\274\350\306\300\244\362\244\267\244\350\244\246\244\310\244\267\244\336\244\267\244\277\n";
/* EUC-JP: "ストリームモーションの終了を検知
" */
__attribute__((section(".rodata.0x0061A628"))) const char D_0061A628[40] = "\245\271\245\310\245\352\241\274\245\340\245\342\241\274\245\267\245\347\245\363\244\316\275\252\316\273\244\362\270\241\303\316\n";
