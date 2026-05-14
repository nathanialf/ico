/* rotObject.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x006335C8"))) int D_006335C8 = 0x00000000;
__attribute__((section(".sdata.0x006335CC"))) int D_006335CC = 0x00000000;
__attribute__((section(".sdata.0x006335D0"))) int D_006335D0 = 0x000A7325;
__attribute__((section(".sdata.0x006335D4"))) int D_006335D4 = 0x00000000;
__attribute__((section(".sdata.0x006335D8"))) int D_006335D8 = 0;
__attribute__((section(".sdata.0x006335DC"))) int D_006335DC = 0;
__attribute__((section(".sdata.0x006335E8"))) const char D_006335E8[8] = "YES";
__attribute__((section(".sdata.0x006335F0"))) unsigned int D_006335F0 = 0x00004F4E;
__attribute__((section(".sdata.0x006335F4"))) int D_006335F4 = 0;
__attribute__((section(".sdata.0x006335F8"))) int D_006335F8 = 0;

/* String-pool rodata migrated from rotObject_data.c */
__attribute__((section(".rodata.0x00619FC8"))) const char D_00619FC8[120] = "src/rotObject.c\000GetRotObjectHoldPoint\000\000\000\t%f, %f, %f\n\000\000\000\000MoveRotObjectWithHoldPoint\000\000\000\000\000\000GetRotObjectGlobalHoldGeometry\000";
