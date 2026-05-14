/* attackCheckBoundary.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633280"))) char D_00633280[7] = { 0 };
__attribute__((section(".sdata.0x00633287"))) char D_00633287 = 0;

__attribute__((section(".rodata.0x006185E8"))) const char D_006185E8[32] = "src/attackCheckBoundary.c";

/* Float rodata migrated from attackCheckBoundary_data.c */
__attribute__((section(".rodata.0x0061E730"))) const float D_0061E730[6] = { 0.0f, -8e+01f, 15.0f, 0.0f, 1.8e+02f, 0.0f };

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: " - 剣で切られた
" */
__attribute__((section(".rodata.0x00618608"))) const char D_00618608[24] = " - \267\365\244\307\300\332\244\351\244\354\244\277\n";
/* EUC-JP: " - きれない
" */
__attribute__((section(".rodata.0x00618620"))) const char D_00618620[16] = " - \244\255\244\354\244\312\244\244\n";
