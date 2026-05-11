/* Light.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006309D4"))) float D_006309D4 = 0.3333f;
__attribute__((section(".lit4.0x006309D8"))) float D_006309D8 = 0.3333f;
__attribute__((section(".lit4.0x006309DC"))) float D_006309DC = 0.1f;
__attribute__((section(".lit4.0x006309E0"))) float D_006309E0 = 3.14159274f;
__attribute__((section(".lit4.0x006309E4"))) float D_006309E4 = 2.09439516f;
__attribute__((section(".lit4.0x006309E8"))) float D_006309E8 = 4.18879032f;
__attribute__((section(".lit4.0x006309EC"))) float D_006309EC = 3.14159274f;
__attribute__((section(".lit4.0x006309F0"))) float D_006309F0 = 3.14159274f;
__attribute__((section(".lit4.0x006309F4"))) float D_006309F4 = -3.14159274f;
__attribute__((section(".lit4.0x006309F8"))) float D_006309F8 = 3.14159274f;
__attribute__((section(".lit4.0x006309FC"))) float D_006309FC = -3.14159274f;
__attribute__((section(".lit4.0x00630A00"))) float D_00630A00 = 3.14159274f;
__attribute__((section(".lit4.0x00630A04"))) float D_00630A04 = -3.14159274f;
__attribute__((section(".lit4.0x00630A08"))) float D_00630A08 = 3.14159274f;
__attribute__((section(".lit4.0x00630A0C"))) float D_00630A0C = 2.09439516f;
__attribute__((section(".lit4.0x00630A10"))) float D_00630A10 = 1.2f;
__attribute__((section(".lit4.0x00630A14"))) float D_00630A14 = 0.01f;
__attribute__((section(".lit4.0x00630A18"))) float D_00630A18 = 0.01f;
__attribute__((section(".lit4.0x00630A1C"))) float D_00630A1C = 1.01f;
__attribute__((section(".lit4.0x00630A20"))) float D_00630A20 = 0.99f;
__attribute__((section(".lit4.0x00630A24"))) float D_00630A24 = 0.01f;
__attribute__((section(".lit4.0x00630A28"))) float D_00630A28 = 0.01f;
__attribute__((section(".lit4.0x00630A2C"))) float D_00630A2C = 1.01f;
__attribute__((section(".lit4.0x00630A30"))) float D_00630A30 = 0.99f;
__attribute__((section(".lit4.0x00630A34"))) float D_00630A34 = 0.3333f;
__attribute__((section(".lit4.0x00630A38"))) float D_00630A38 = 0.3333f;
__attribute__((section(".sdata.0x00631960"))) char D_00631960[16] = { 0 };
__attribute__((section(".sdata.0x00631C70"))) char D_00631C70[8] = { 0 };
__attribute__((section(".sdata.0x00631C78"))) const char D_00631C78[8] = "0";
__attribute__((section(".sdata.0x00631C80"))) const char D_00631C80[8] = "OBJ";
__attribute__((section(".sdata.0x00631C88"))) unsigned int D_00631C88 = 0x00584946;
__attribute__((section(".sdata.0x00631C8C"))) int D_00631C8C = 0;
__attribute__((section(".sdata.0x00631C90"))) int D_00631C90 = 0;
__attribute__((section(".sdata.0x00631C94"))) int D_00631C94 = 0;
__attribute__((section(".sdata.0x00631C98"))) const char D_00631C98[8] = "r:";
__attribute__((section(".sdata.0x00631CA0"))) const char D_00631CA0[8] = "g:";
__attribute__((section(".sdata.0x00631CA8"))) const char D_00631CA8[8] = "b:";
__attribute__((section(".sdata.0x00631CB0"))) const char D_00631CB0[8] = "COL ";
__attribute__((section(".sdata.0x00631CB8"))) const char D_00631CB8[8] = "%s%11f";
__attribute__((section(".sdata.0x00631CC0"))) const char D_00631CC0[8] = "VEC ";
__attribute__((section(".sdata.0x00631CC8"))) const char D_00631CC8[8] = "AMB ";
__attribute__((section(".sdata.0x00632D4C"))) int D_00632D4C = 0;
__attribute__((section(".sdata.0x00632D50"))) int D_00632D50 = 0;
__attribute__((section(".sdata.0x00632D54"))) int D_00632D54 = 0;

__attribute__((section(".rodata.0x00554CA8"))) const char D_00554CA8[16] = "src/Light.c";

__attribute__((section(".rodata.0x00554D70"))) const char D_00554D70[64] = "PUSH R2 SELECT LIGHT (%d/3) ('SELECT'RETURN MENU)";
__attribute__((section(".rodata.0x00554DD0"))) const char D_00554DD0[24] = "(addr 0x%08x <fl) : ";
__attribute__((section(".rodata.0x00554DE8"))) const char D_00554DE8[24] = "(addr 0x%08x <%2d>) : ";
