/* Primitive.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630A54"))) float D_00630A54 = 6.28318548f;
__attribute__((section(".lit4.0x00630A58"))) float D_00630A58 = 10430.3779f;
__attribute__((section(".lit4.0x00630A5C"))) float D_00630A5C = 6.28318548f;
__attribute__((section(".lit4.0x00630A60"))) float D_00630A60 = 10430.3779f;
__attribute__((section(".lit4.0x00630A64"))) float D_00630A64 = 4095.0f;
__attribute__((section(".lit4.0x00630A68"))) float D_00630A68 = 3.14159274f;
__attribute__((section(".lit4.0x00630A6C"))) float D_00630A6C = 10430.3779f;
__attribute__((section(".lit4.0x00630A70"))) float D_00630A70 = 1.41421354f;
__attribute__((section(".lit4.0x00630A74"))) float D_00630A74 = 1.41421354f;
__attribute__((section(".lit4.0x00630A78"))) float D_00630A78 = 3.14159274f;
__attribute__((section(".lit4.0x00630A7C"))) float D_00630A7C = 10430.3779f;
__attribute__((section(".lit4.0x00630A80"))) float D_00630A80 = 3.14159274f;
__attribute__((section(".lit4.0x00630A84"))) float D_00630A84 = 10430.3779f;
__attribute__((section(".lit4.0x00630A88"))) float D_00630A88 = 1e-05f;
__attribute__((section(".lit4.0x00630A8C"))) float D_00630A8C = 0.01f;
__attribute__((section(".lit4.0x00630A90"))) float D_00630A90 = -2047.0f;
__attribute__((section(".lit4.0x00630A94"))) float D_00630A94 = 3.14159274f;
__attribute__((section(".lit4.0x00630A98"))) float D_00630A98 = 0.2f;
__attribute__((section(".sdata.0x00631C54"))) int D_00631C54 = 0;
__attribute__((section(".sdata.0x00631C58"))) int D_00631C58 = 0;
__attribute__((section(".sdata.0x00631D28"))) const char D_00631D28[8] = "0";
__attribute__((section(".sdata.0x00631D30"))) const char D_00631D30[8] = "%s";
__attribute__((section(".sdata.0x00631D38"))) const char D_00631D38[8] = "FALSE";
__attribute__((section(".sdata.0x00631D40"))) char D_00631D40[8] = { 0 };
__attribute__((section(".sdata.0x00632CA4"))) int D_00632CA4 = 0;
__attribute__((section(".sdata.0x00632CA8"))) int D_00632CA8 = 0;
__attribute__((section(".sdata.0x00632CAC"))) int D_00632CAC = 0;
__attribute__((section(".sdata.0x00632D2C"))) int D_00632D2C = 0;
__attribute__((section(".sdata.0x00632D80"))) int D_00632D80 = 0;
__attribute__((section(".sdata.0x00632D84"))) int D_00632D84 = 0;

__attribute__((section(".rodata.0x00555490"))) const char D_00555490[16] = "src/Primitive.c";

/* String rodata migrated from Primitive_data.c */
__attribute__((section(".rodata.0x005554B0"))) const char D_005554B0[32] = "too large mesh packet. %d\n";
__attribute__((section(".rodata.0x00555500"))) const char D_00555500[72] = "Particle Object too big (%d particles). (must be under %d particles)\n";
__attribute__((section(".rodata.0x00555548"))) const char D_00555548[48] = "prim_InitParticle:illegal texture no. %s:%d\n";

/* Float rodata migrated from Primitive_data.c */
__attribute__((section(".rodata.0x005554E0"))) const float D_005554E0[4] = { 1024.0f, 1024.0f, 0.0f, 1.0f };
__attribute__((section(".rodata.0x005554F0"))) const float D_005554F0[4] = { 3071.0f, 3071.0f, 0.0f, 16777215.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "prim_DispParticle:指定したテクスチャ番号が異常です. %s:%d
" */
__attribute__((section(".rodata.0x00555578"))) const char D_00555578[64] = "prim_DispParticle:\273\330\304\352\244\267\244\277\245\306\245\257\245\271\245\301\245\343\310\326\271\346\244\254\260\333\276\357\244\307\244\271. %s:%d\n";
