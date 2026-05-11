/* motionManager2.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x0063097C"))) float D_0063097C = -0.1f;
__attribute__((section(".lit4.0x00630980"))) float D_00630980 = 0.001f;
__attribute__((section(".sdata.0x00631B50"))) const char D_00631B50[8] = "!!";
__attribute__((section(".sdata.0x00631B58"))) unsigned int D_00631B58 = 0x00000065;
__attribute__((section(".sdata.0x00631B5C"))) unsigned int D_00631B5C = 0x7F7FFFFF;

__attribute__((section(".rodata.0x00553CA0"))) const char D_00553CA0[24] = "src/motionManager2.c";
