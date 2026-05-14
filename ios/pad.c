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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".sdata.0x00632140"))) const char D_00632140[8] = "pad:4\n";
__attribute__((section(".sdata.0x00632148"))) const char D_00632148[8] = "pad:7\n";
__attribute__((section(".sdata.0x00632188"))) unsigned int D_00632188 = 0x00000030;
__attribute__((section(".sdata.0x0063218C"))) unsigned int D_0063218C = 0x00000001;
__attribute__((section(".sdata.0x00632190"))) int D_00632190 = 0;

__attribute__((section(".rodata.0x005576B8"))) const char D_005576B8[24] = "ios/pad.c";
__attribute__((section(".rodata.0x00557840"))) const char D_00557840[32] = "pad:checking controler... ";

/* String rodata migrated from pad_data.c */
__attribute__((section(".rodata.0x005575F0"))) const char D_005575F0[24] = "pad:port:%d slot:%d %s\n";
__attribute__((section(".rodata.0x00557608"))) const char D_00557608[16] = "pad:?%d\n";
__attribute__((section(".rodata.0x00557618"))) const char D_00557618[16] = "phase %d\n";
__attribute__((section(".rodata.0x00557628"))) const char D_00557628[16] = "pad id:%d\n";
__attribute__((section(".rodata.0x00557638"))) const char D_00557638[16] = "pad: exid %d\n";
__attribute__((section(".rodata.0x00557648"))) const char D_00557648[24] = "pad:default 0x%x\n";
__attribute__((section(".rodata.0x00557660"))) const char D_00557660[16] = "pad:%03x\n";
__attribute__((section(".rodata.0x00557670"))) const char D_00557670[32] = "pad:switch to ANALOG mode\n";
__attribute__((section(".rodata.0x00557690"))) const char D_00557690[40] = "pad:switch to PRESSURE SENSE mode\n";
__attribute__((section(".rodata.0x00557808"))) const char D_00557808[16] = "pad:init error\n";
__attribute__((section(".rodata.0x00557818"))) const char D_00557818[40] = "ERROR: scePadPortOpen port%d slot%d\n";
__attribute__((section(".rodata.0x00557860"))) const char D_00557860[24] = "port:%d, slot:%d\n";
__attribute__((section(".rodata.0x00557878"))) const char D_00557878[24] = "voice error? %d\n";
