/* a_p_1.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633210"))) const char D_00633210[8] = "e";
__attribute__((section(".sdata.0x00633218"))) const char D_00633218[8] = "SL";
__attribute__((section(".sdata.0x00633220"))) const char D_00633220[8] = "DE";
__attribute__((section(".sdata.0x00633228"))) const char D_00633228[8] = "AT";
__attribute__((section(".sdata.0x00633230"))) const char D_00633230[8] = "JM";
__attribute__((section(".sdata.0x00633238"))) const char D_00633238[8] = "WA";
__attribute__((section(".sdata.0x00633240"))) const char D_00633240[8] = "ST";
__attribute__((section(".sdata.0x00633248"))) const char D_00633248[8] = "--";
__attribute__((section(".sdata.0x00633250"))) const char D_00633250[8] = "SLEEP";
__attribute__((section(".sdata.0x00633258"))) const char D_00633258[8] = "DEAD";
__attribute__((section(".sdata.0x00633260"))) const char D_00633260[8] = "ATTACK";
__attribute__((section(".sdata.0x00633268"))) const char D_00633268[8] = "JUMP";
__attribute__((section(".sdata.0x00633270"))) const char D_00633270[8] = "WALK";
__attribute__((section(".sdata.0x00633278"))) const char D_00633278[8] = "STAND";
