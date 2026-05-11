/* message.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632004"))) int D_00632004 = 0;
__attribute__((section(".sdata.0x006320E8"))) const char D_006320E8[8] = "0";
__attribute__((section(".sdata.0x006320F0"))) const char D_006320F0[8] = "%p\n";
__attribute__((section(".sdata.0x006320F8"))) const char D_006320F8[8] = "%d %d\n";
__attribute__((section(".sdata.0x00632100"))) const char D_00632100[] = "evt:%d\n";
__attribute__((section(".sdata.0x00632108"))) char D_00632108[8] = { 0 };
__attribute__((section(".sdata.0x00632110"))) int D_00632110 = 0x00000001;
__attribute__((section(".sdata.0x00632114"))) int D_00632114 = 0x00000000;
__attribute__((section(".sdata.0x00632118"))) const char D_00632118[8] = "ERROR";
__attribute__((section(".sdata.0x00632120"))) const char D_00632120[8] = "STABLE";
__attribute__((section(".sdata.0x00632128"))) const char D_00632128[] = "EXECCMD";
__attribute__((section(".sdata.0x00632130"))) char D_00632130[8] = { 0 };
__attribute__((section(".sdata.0x00632138"))) const char D_00632138[] = "FINDPAD";

__attribute__((section(".rodata.0x00557540"))) const char D_00557540[16] = "ios/message.c";
__attribute__((section(".rodata.0x005575D0"))) const char D_005575D0[16] = "FINDCTP1";
__attribute__((section(".rodata.0x005575E0"))) const char D_005575E0[16] = "DISCONNECT";
