/* girl_brain_main.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632450"))) unsigned char D_00632450[16] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x49, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00632460"))) const char D_00632460[8] = "DIRECT";
__attribute__((section(".sdata.0x00632468"))) unsigned char D_00632468[16] = { 0x46, 0x41, 0x4C, 0x53, 0x45, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00632478"))) const char D_00632478[8] = "WAIT";
__attribute__((section(".sdata.0x00632480"))) const char D_00632480[8] = "END";
__attribute__((section(".sdata.0x00632488"))) const char D_00632488[8] = "IDLE";
