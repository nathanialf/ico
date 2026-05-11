/* staffroll.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x006331A8"))) const char D_006331A8[11] = "0";
__attribute__((section(".sdata.0x006331B3"))) char D_006331B3 = 0;
__attribute__((section(".sdata.0x006331B4"))) int D_006331B4 = 0;
__attribute__((section(".sdata.0x006331B8"))) const char D_006331B8[8] = "Lead: ";
__attribute__((section(".sdata.0x006331C0"))) unsigned int D_006331C0 = 0x00000020;
__attribute__((section(".sdata.0x006331C4"))) unsigned int D_006331C4 = 0x00000430;
__attribute__((section(".sdata.0x006331C8"))) const char D_006331C8[8] = "SL";
__attribute__((section(".sdata.0x006331D0"))) const char D_006331D0[8] = "TH";
__attribute__((section(".sdata.0x006331D8"))) const char D_006331D8[8] = "D2";
__attribute__((section(".sdata.0x006331E0"))) const char D_006331E0[8] = "D1";
__attribute__((section(".sdata.0x006331E8"))) const char D_006331E8[8] = "DE";
__attribute__((section(".sdata.0x006331F0"))) const char D_006331F0[8] = "AT";
__attribute__((section(".sdata.0x006331F8"))) const char D_006331F8[8] = "RO";
__attribute__((section(".sdata.0x00633200"))) const char D_00633200[8] = "WA";
__attribute__((section(".sdata.0x00633208"))) const char D_00633208[8] = "ST";
