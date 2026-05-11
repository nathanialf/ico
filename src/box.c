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
 * land in this same file (parappa2-style layout); typed
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
