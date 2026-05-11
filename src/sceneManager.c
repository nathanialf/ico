/* sceneManager.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633190"))) const char D_00633190[8] = "0";
__attribute__((section(".sdata.0x00633198"))) int D_00633198 = 0;
__attribute__((section(".sdata.0x0063319C"))) int D_0063319C = 0;
__attribute__((section(".sdata.0x006331A0"))) char D_006331A0[8] = { 0 };

__attribute__((section(".rodata.0x006172E0"))) const char D_006172E0[24] = "src/sceneManager.c";
