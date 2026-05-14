/* gobj.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".sdata.0x00632008"))) int D_00632008 = 0;
__attribute__((section(".sdata.0x006321C0"))) char D_006321C0[8] = { 0 };
__attribute__((section(".sdata.0x006321C8"))) unsigned int D_006321C8 = 0x00000030;
__attribute__((section(".sdata.0x006321CC"))) int D_006321CC = 0;
__attribute__((section(".sdata.0x006321D0"))) int D_006321D0 = 0;
__attribute__((section(".sdata.0x006321D4"))) int D_006321D4 = 0;
__attribute__((section(".sdata.0x006321D8"))) int D_006321D8 = 0;

__attribute__((section(".rodata.0x00557A10"))) const char D_00557A10[16] = "isys/gobj.c";

/* String rodata migrated from gobj_data.c */
__attribute__((section(".rodata.0x00557A20"))) const char D_00557A20[16] = "isys:null GObj\n";
__attribute__((section(".rodata.0x00557A30"))) const char D_00557A30[40] = "isys:not enough memory for GObj\n";
__attribute__((section(".rodata.0x00557A58"))) const char D_00557A58[16] = "isys:null GObj\n";
__attribute__((section(".rodata.0x00557A68"))) const char D_00557A68[24] = "gobj dl added to tail\n";
__attribute__((section(".rodata.0x00557A80"))) const char D_00557A80[16] = "no_entry %p\n";
__attribute__((section(".rodata.0x00557A90"))) const char D_00557A90[16] = "add to head %p\n";
__attribute__((section(".rodata.0x00557AA0"))) const char D_00557AA0[16] = "add to tail %p\n";
__attribute__((section(".rodata.0x00557AB0"))) const char D_00557AB0[16] = "GObjLinkDL in\n";
__attribute__((section(".rodata.0x00557AC0"))) const char D_00557AC0[16] = "GObjLinkDL out\n";
