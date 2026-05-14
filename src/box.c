/* box.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00631148"))) float D_00631148 = 0.707f;
__attribute__((section(".lit4.0x0063114C"))) float D_0063114C = 0.707f;
__attribute__((section(".lit4.0x00631150"))) float D_00631150 = 0.0100000007f;
__attribute__((section(".lit4.0x00631154"))) float D_00631154 = 10430.3779f;
__attribute__((section(".lit4.0x00631158"))) float D_00631158 = 0.2f;
__attribute__((section(".lit4.0x0063115C"))) float D_0063115C = 0.318309873f;
__attribute__((section(".lit4.0x00631160"))) float D_00631160 = 0.318309873f;
__attribute__((section(".lit4.0x00631164"))) float D_00631164 = 0.05f;
__attribute__((section(".lit4.0x00631168"))) float D_00631168 = 1.414f;
__attribute__((section(".lit4.0x0063116C"))) float D_0063116C = 70.7000046f;
__attribute__((section(".lit4.0x00631170"))) float D_00631170 = -0.1f;
__attribute__((section(".lit4.0x00631174"))) float D_00631174 = 0.9f;
__attribute__((section(".lit4.0x00631178"))) float D_00631178 = 0.0100000007f;
__attribute__((section(".lit4.0x0063117C"))) float D_0063117C = -0.01f;
__attribute__((section(".lit4.0x00631180"))) float D_00631180 = 0.95f;
__attribute__((section(".lit4.0x00631184"))) float D_00631184 = 20.48f;
__attribute__((section(".lit4.0x00631188"))) float D_00631188 = 0.1f;
__attribute__((section(".lit4.0x0063118C"))) float D_0063118C = 10430.3779f;
__attribute__((section(".lit4.0x00631190"))) float D_00631190 = 0.85f;
__attribute__((section(".lit4.0x00631194"))) float D_00631194 = 0.98f;
__attribute__((section(".lit4.0x00631198"))) float D_00631198 = 0.98f;
__attribute__((section(".lit4.0x0063119C"))) float D_0063119C = 0.05f;
__attribute__((section(".lit4.0x006311A0"))) float D_006311A0 = 100000.0f;
__attribute__((section(".lit4.0x006311A4"))) float D_006311A4 = 0.98f;
__attribute__((section(".lit4.0x006311A8"))) float D_006311A8 = 0.85f;
__attribute__((section(".lit4.0x006311AC"))) float D_006311AC = 0.98f;
__attribute__((section(".sdata.0x00632CC8"))) int D_00632CC8 = 0;
__attribute__((section(".sdata.0x00633288"))) unsigned int D_00633288 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x0063328C"))) int D_0063328C = 0;
__attribute__((section(".sdata.0x00633290"))) const char D_00633290[8] = "%d\n";
__attribute__((section(".sdata.0x00633298"))) const char D_00633298[8] = "tape_b";

__attribute__((section(".rodata.0x006186A0"))) const char D_006186A0[16] = "src/box.c";

__attribute__((section(".rodata.0x00618818"))) const char D_00618818[16] = "b_mantle";
__attribute__((section(".rodata.0x00618828"))) const char D_00618828[16] = "tape_boro";

/* String rodata migrated from box_data.c */
__attribute__((section(".rodata.0x00618640"))) const char D_00618640[40] = "height: %f   dist: %f  ofs: %f %x \n";
__attribute__((section(".rodata.0x006186B0"))) const char D_006186B0[24] = "front pos: %f, %f, %f\n";
__attribute__((section(".rodata.0x006186C8"))) const char D_006186C8[24] = "rear  pos: %f, %f, %f\n";
__attribute__((section(".rodata.0x00618708"))) const char D_00618708[24] = "box die!!!\n";
__attribute__((section(".rodata.0x00618740"))) const char D_00618740[32] = "near wall to %f, %f, %f\n";
__attribute__((section(".rodata.0x00618760"))) const char D_00618760[16] = "BOXREINIT\n";
__attribute__((section(".rodata.0x00618808"))) const char D_00618808[16] = "%f, %f, %f\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "この地形はおかしいです(100cmに区切られていません)
" */
__attribute__((section(".rodata.0x00618668"))) const char D_00618668[56] = "\244\263\244\316\303\317\267\301\244\317\244\252\244\253\244\267\244\244\244\307\244\271(100cm\244\313\266\350\300\332\244\351\244\354\244\306\244\244\244\336\244\273\244\363)\n";
/* EUC-JP: "[36m箱が地面の無いところに初期配置されています。
動作が保証できません(コリジョン定義より前に箱がありませんか?)[m
" */
__attribute__((section(".rodata.0x00618770"))) const char D_00618770[120] = "\033[36m\310\242\244\254\303\317\314\314\244\316\314\265\244\244\244\310\244\263\244\355\244\313\275\351\264\374\307\333\303\326\244\265\244\354\244\306\244\244\244\336\244\271\241\243\n\306\260\272\356\244\254\312\335\276\332\244\307\244\255\244\336\244\273\244\363(\245\263\245\352\245\270\245\347\245\363\304\352\265\301\244\350\244\352\301\260\244\313\310\242\244\254\244\242\244\352\244\336\244\273\244\363\244\253?)\033[m\n";
/* EUC-JP: "箱初期水底配置
" */
__attribute__((section(".rodata.0x006187E8"))) const char D_006187E8[16] = "\310\242\275\351\264\374\277\345\304\354\307\333\303\326\n";
/* EUC-JP: "箱初期通常配置
" */
__attribute__((section(".rodata.0x006187F8"))) const char D_006187F8[16] = "\310\242\275\351\264\374\304\314\276\357\307\333\303\326\n";
