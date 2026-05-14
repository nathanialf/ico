/* geometryManager.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631B30"))) const char D_00631B30[8] = "e";
__attribute__((section(".sdata.0x00631B38"))) unsigned int D_00631B38 = 0x00000030;
__attribute__((section(".sdata.0x00631B3C"))) int D_00631B3C = 0;
__attribute__((section(".sdata.0x00631B40"))) char D_00631B40[8] = { 0 };

__attribute__((section(".rodata.0x00553AD0"))) const char D_00553AD0[24] = "src/geometryManager.c";

/* String rodata migrated from geometryManager_data.c */
__attribute__((section(".rodata.0x00553AE8"))) const char D_00553AE8[96] = "Fatal error! Geometry localize function called with GObj\n    that already have parent.\nExit...\n";
__attribute__((section(".rodata.0x00553B48"))) const char D_00553B48[48] = "TOO MANY CHARACTERS EXIST ON THIS STAGE(>64)\n";
__attribute__((section(".rodata.0x00553B78"))) const char D_00553B78[24] = "InitKeyInput2() in\n";
__attribute__((section(".rodata.0x00553B90"))) const char D_00553B90[16] = "PadInit\n";
__attribute__((section(".rodata.0x00553BA0"))) const char D_00553BA0[24] = "InitKeyInput2() out\n";
__attribute__((section(".rodata.0x00553BB8"))) const char D_00553BB8[24] = "signal to main\n";
__attribute__((section(".rodata.0x00553BE0"))) const char D_00553BE0[48] = "Adjust Motion Height To Field. --------------\n";

/* Float rodata migrated from geometryManager_data.c */
__attribute__((section(".rodata.0x00553C10"))) const float D_00553C10[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00553C20"))) const float D_00553C20[4] = { 0.0f, 0.0f, 5.0f, 0.0f };
__attribute__((section(".rodata.0x00553C30"))) const float D_00553C30[4] = { 5.0f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00553C70"))) const float D_00553C70[4] = { 1e+01f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00553C90"))) const float D_00553C90[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
