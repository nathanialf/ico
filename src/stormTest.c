/* stormTest.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006313E0"))) float D_006313E0 = 0.181818187f;
__attribute__((section(".lit4.0x006313E4"))) float D_006313E4 = 0.9f;
__attribute__((section(".lit4.0x006313E8"))) float D_006313E8 = 0.1f;
__attribute__((section(".lit4.0x006313EC"))) float D_006313EC = 0.1f;
__attribute__((section(".lit4.0x006313F0"))) float D_006313F0 = 1500.0f;
__attribute__((section(".lit4.0x006313F4"))) float D_006313F4 = 0.1f;
__attribute__((section(".lit4.0x006313F8"))) float D_006313F8 = 182.044449f;
__attribute__((section(".lit4.0x006313FC"))) float D_006313FC = 0.7f;
__attribute__((section(".lit4.0x00631400"))) float D_00631400 = 0.7f;
__attribute__((section(".lit4.0x00631404"))) float D_00631404 = 0.9f;
__attribute__((section(".lit4.0x00631408"))) float D_00631408 = 0.1f;
__attribute__((section(".lit4.0x0063140C"))) float D_0063140C = 0.1f;
__attribute__((section(".lit4.0x00631410"))) float D_00631410 = 0.01f;
__attribute__((section(".lit4.0x00631414"))) float D_00631414 = 0.1f;
__attribute__((section(".lit4.0x00631418"))) float D_00631418 = 0.7f;
__attribute__((section(".lit4.0x0063141C"))) float D_0063141C = 0.8f;
__attribute__((section(".lit4.0x00631420"))) float D_00631420 = 0.02f;
__attribute__((section(".lit4.0x00631424"))) float D_00631424 = 0.05f;
__attribute__((section(".lit4.0x00631428"))) float D_00631428 = 8.99999f;
__attribute__((section(".lit4.0x0063142C"))) float D_0063142C = 8.99999f;

__attribute__((section(".rodata.0x0061A470"))) const char D_0061A470[16] = "src/stormTest.c";

__attribute__((section(".rodata.0x0061A650"))) const char D_0061A650[24] = "STANDBY %d CHARS %s";
