/* cdvd.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630900"))) float D_00630900 = 1.23456776f;
__attribute__((section(".lit4.0x00630904"))) float D_00630904 = -100000.0f;
__attribute__((section(".lit4.0x00630908"))) float D_00630908 = 100000.0f;
__attribute__((section(".lit4.0x0063090C"))) float D_0063090C = 0.01f;
__attribute__((section(".lit4.0x00630910"))) float D_00630910 = 0.01f;
__attribute__((section(".lit4.0x00630914"))) float D_00630914 = 0.01f;
__attribute__((section(".lit4.0x00630918"))) float D_00630918 = 0.01f;
__attribute__((section(".lit4.0x0063091C"))) float D_0063091C = 0.01f;
__attribute__((section(".lit4.0x00630920"))) float D_00630920 = 0.01f;
__attribute__((section(".lit4.0x00630924"))) float D_00630924 = 0.01f;
__attribute__((section(".lit4.0x00630928"))) float D_00630928 = 0.01f;
__attribute__((section(".lit4.0x0063092C"))) float D_0063092C = 0.01f;
__attribute__((section(".sdata.0x00631A00"))) char D_00631A00[16] = { 0 };
__attribute__((section(".sdata.0x00631AB0"))) char D_00631AB0[16] = { 0 };
__attribute__((section(".sdata.0x00631AC0"))) char D_00631AC0[16] = { 0 };
__attribute__((section(".sdata.0x00631AD0"))) char D_00631AD0[16] = { 0 };
__attribute__((section(".sdata.0x00631AE0"))) int D_00631AE0 = 0;
__attribute__((section(".sdata.0x00631F50"))) int D_00631F50 = 0;
__attribute__((section(".sdata.0x00631F54"))) int D_00631F54 = 0;
__attribute__((section(".sdata.0x00631F58"))) unsigned char D_00631F58[8] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00631F60"))) unsigned int D_00631F60 = 0x00000002;
__attribute__((section(".sdata.0x00631F64"))) int D_00631F64 = 0;
__attribute__((section(".sdata.0x00631F68"))) const char D_00631F68[8] = "0";
__attribute__((section(".sdata.0x00631F70"))) const char D_00631F70[8] = "\\%s;1";
__attribute__((section(".sdata.0x00631F78"))) const char D_00631F78[] = "handler";
__attribute__((section(".sdata.0x00631F80"))) const char D_00631F80[8] = "n=%d\n";
__attribute__((section(".sdata.0x00631F88"))) const char D_00631F88[] = "out %d\n";
__attribute__((section(".sdata.0x00631F90"))) char D_00631F90[8] = { 0 };
__attribute__((section(".sdata.0x00631F98"))) const char D_00631F98[8] = "load";
__attribute__((section(".sdata.0x00631FA0"))) int D_00631FA0 = 0;
__attribute__((section(".sdata.0x00631FA4"))) int D_00631FA4 = 0;
__attribute__((section(".sdata.0x00631FA8"))) int D_00631FA8 = 0;
__attribute__((section(".sdata.0x00631FAC"))) int D_00631FAC = 0;
__attribute__((section(".sdata.0x00631FB0"))) int D_00631FB0 = 0;
__attribute__((section(".sdata.0x00631FB4"))) int D_00631FB4 = 0;
__attribute__((section(".sdata.0x00631FB8"))) char D_00631FB8[8] = { 0 };
__attribute__((section(".sdata.0x00631FC0"))) const char D_00631FC0[8] = "stage";
__attribute__((section(".sdata.0x00631FC8"))) const char D_00631FC8[8] = "event";
__attribute__((section(".sdata.0x00631FD0"))) const char D_00631FD0[8] = "hara";
__attribute__((section(".sdata.0x00631FD8"))) const char D_00631FD8[8] = "oomori";
__attribute__((section(".sdata.0x00631FE0"))) const char D_00631FE0[] = "horagai";
__attribute__((section(".sdata.0x00631FE8"))) const char D_00631FE8[8] = "sound";
__attribute__((section(".sdata.0x00631FF0"))) const char D_00631FF0[8] = "shock";
__attribute__((section(".sdata.0x00631FF8"))) const char D_00631FF8[8] = "common";
__attribute__((section(".sdata.0x00632854"))) int D_00632854 = 0;
__attribute__((section(".sdata.0x00632858"))) int D_00632858 = 0;
__attribute__((section(".sdata.0x0063285C"))) int D_0063285C = 0;
__attribute__((section(".sdata.0x00632860"))) int D_00632860 = 0;
__attribute__((section(".sdata.0x00632864"))) int D_00632864 = 0;
__attribute__((section(".sdata.0x00632868"))) int D_00632868 = 0;
__attribute__((section(".sdata.0x0063286C"))) int D_0063286C = 0;
__attribute__((section(".sdata.0x00632870"))) char D_00632870[8] = { 0 };
__attribute__((section(".sdata.0x00632878"))) const char D_00632878[8] = "done";
__attribute__((section(".sdata.0x00632880"))) int D_00632880 = 0;
__attribute__((section(".sdata.0x00632884"))) int D_00632884 = 0;
__attribute__((section(".sdata.0x00632888"))) char D_00632888[8] = { 0 };
__attribute__((section(".sdata.0x00632890"))) const char D_00632890[8] = "%d\n";
