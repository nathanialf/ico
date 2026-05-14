/* rope.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006313B0"))) float D_006313B0 = 10430.3779f;
__attribute__((section(".lit4.0x006313B4"))) float D_006313B4 = 10430.3779f;
__attribute__((section(".lit4.0x006313B8"))) float D_006313B8 = 0.01f;
__attribute__((section(".lit4.0x006313BC"))) float D_006313BC = 31.8309879f;
__attribute__((section(".lit4.0x006313C0"))) float D_006313C0 = 10430.3779f;
__attribute__((section(".lit4.0x006313C4"))) float D_006313C4 = 10430.3779f;
__attribute__((section(".lit4.0x006313C8"))) float D_006313C8 = 10430.3779f;
__attribute__((section(".lit4.0x006313CC"))) float D_006313CC = 10430.3779f;
__attribute__((section(".sdata.0x006335C0"))) const char D_006335C0[8] = "0";

__attribute__((section(".rodata.0x00619EE0"))) const char D_00619EE0[16] = "src/rope.c";

/* String rodata migrated from rope_data.c */
__attribute__((section(".rodata.0x00619FB8"))) const char D_00619FB8[16] = "HOLD ROPE\n";

/* Float rodata migrated from rope_data.c */
__attribute__((section(".rodata.0x00619F30"))) const float D_00619F30[4] = { 0.0f, 0.0f, -1e+01f, 1.0f };
__attribute__((section(".rodata.0x00619F40"))) const float D_00619F40[4] = { 0.0f, 0.0f, 1e+01f, 1.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "ロープの長さが短すぎます。表のscale-yを変更してください。
" */
__attribute__((section(".rodata.0x00619EF0"))) const char D_00619EF0[64] = "\245\355\241\274\245\327\244\316\304\271\244\265\244\254\303\273\244\271\244\256\244\336\244\271\241\243\311\275\244\316scale-y\244\362\312\321\271\271\244\267\244\306\244\257\244\300\244\265\244\244\241\243\n";
/* EUC-JP: "[33m鎖の上の壁を見付けることができません。
方向が間違っているか、壁が無いところに置いていませんか?[m
" */
__attribute__((section(".rodata.0x00619F50"))) const char D_00619F50[104] = "\033[33m\272\277\244\316\276\345\244\316\312\311\244\362\270\253\311\325\244\261\244\353\244\263\244\310\244\254\244\307\244\255\244\336\244\273\244\363\241\243\n\312\375\270\376\244\254\264\326\260\343\244\303\244\306\244\244\244\353\244\253\241\242\312\311\244\254\314\265\244\244\244\310\244\263\244\355\244\313\303\326\244\244\244\306\244\244\244\336\244\273\244\363\244\253?\033[m\n";
