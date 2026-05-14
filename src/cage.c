/* cage.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006311E4"))) float D_006311E4 = 0.995f;
__attribute__((section(".lit4.0x006311E8"))) float D_006311E8 = 10430.3779f;
__attribute__((section(".lit4.0x006311EC"))) float D_006311EC = 2730.0f;
__attribute__((section(".lit4.0x006311F0"))) float D_006311F0 = 10430.3779f;
__attribute__((section(".lit4.0x006311F4"))) float D_006311F4 = 0.01f;
__attribute__((section(".lit4.0x006311F8"))) float D_006311F8 = 1e-06f;
__attribute__((section(".lit4.0x006311FC"))) float D_006311FC = 0.8f;
__attribute__((section(".lit4.0x00631200"))) float D_00631200 = 0.98f;

__attribute__((section(".rodata.0x00618848"))) const char D_00618848[16] = "src/cage.c";
