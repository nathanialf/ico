/* pad.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632140"))) const char D_00632140[8] = "pad:4\n";
__attribute__((section(".sdata.0x00632148"))) const char D_00632148[8] = "pad:7\n";
__attribute__((section(".sdata.0x00632150"))) const char D_00632150[] = "pad:41\n";
__attribute__((section(".sdata.0x00632158"))) const char D_00632158[] = "pad:42\n";
__attribute__((section(".sdata.0x00632160"))) const char D_00632160[] = "pad:70\n";
__attribute__((section(".sdata.0x00632168"))) const char D_00632168[] = "pad:71\n";
__attribute__((section(".sdata.0x00632170"))) const char D_00632170[] = "pad:72\n";
__attribute__((section(".sdata.0x00632178"))) const char D_00632178[] = "pad:75\n";
__attribute__((section(".sdata.0x00632180"))) const char D_00632180[] = "pad:76\n";
__attribute__((section(".sdata.0x00632188"))) unsigned int D_00632188 = 0x00000030;
__attribute__((section(".sdata.0x0063218C"))) unsigned int D_0063218C = 0x00000001;
__attribute__((section(".sdata.0x00632190"))) int D_00632190 = 0;

__attribute__((section(".rodata.0x005576B8"))) const char D_005576B8[24] = "ios/pad.c";
__attribute__((section(".rodata.0x00557840"))) const char D_00557840[32] = "pad:checking controler... ";
