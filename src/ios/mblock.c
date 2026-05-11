/* mblock.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x0063203C"))) int D_0063203C = 0;
__attribute__((section(".sdata.0x00632040"))) char D_00632040[8] = { 0 };
__attribute__((section(".sdata.0x00632048"))) char D_00632048[12] = { 0 };
__attribute__((section(".sdata.0x00632054"))) unsigned int D_00632054 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00632058"))) const char D_00632058[8] = "game.";
__attribute__((section(".sdata.0x00632060"))) char D_00632060[8] = { 0 };
__attribute__((section(".sdata.0x00632068"))) unsigned char D_00632068[16] = { 0x25, 0x64, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x33, 0x2E, 0x33, 0x64, 0x00, 0x00, 0x00 };
__attribute__((section(".sdata.0x00632078"))) const char D_00632078[8] = "*";
__attribute__((section(".sdata.0x00632080"))) const char D_00632080[] = "done 1\n";
__attribute__((section(".sdata.0x00632088"))) const char D_00632088[8] = "format";
__attribute__((section(".sdata.0x00632090"))) const char D_00632090[8] = "chdir";
__attribute__((section(".sdata.0x00632098"))) const char D_00632098[8] = "getdir";
__attribute__((section(".sdata.0x006320A0"))) const char D_006320A0[8] = "delete";
__attribute__((section(".sdata.0x006320A8"))) const char D_006320A8[8] = "test";
