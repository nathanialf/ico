/* girl_brain_main.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632450"))) int D_00632450 = 0x00000030;
__attribute__((section(".sdata.0x00632454"))) int D_00632454 = 0x00000000;
__attribute__((section(".sdata.0x00632458"))) int D_00632458 = 0x00494949;
__attribute__((section(".sdata.0x0063245C"))) int D_0063245C = 0x00000000;
__attribute__((section(".sdata.0x00632460"))) const char D_00632460[8] = "DIRECT";
__attribute__((section(".sdata.0x00632468"))) int D_00632468 = 0x534C4146;
__attribute__((section(".sdata.0x0063246C"))) int D_0063246C = 0x00000045;
__attribute__((section(".sdata.0x00632470"))) int D_00632470 = 0x00000058;
__attribute__((section(".sdata.0x00632474"))) int D_00632474 = 0x00000000;
__attribute__((section(".sdata.0x00632478"))) const char D_00632478[8] = "WAIT";
__attribute__((section(".sdata.0x00632480"))) const char D_00632480[8] = "END";
__attribute__((section(".sdata.0x00632488"))) const char D_00632488[8] = "IDLE";

__attribute__((section(".rodata.0x00559528"))) const char D_00559528[32] = "src/girl_brain_main.c.inc";
__attribute__((section(".rodata.0x00559548"))) const char D_00559548[16] = "SAMEGROUP";
__attribute__((section(".rodata.0x00559558"))) const char D_00559558[24] = "OTHERGROUP";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "敵の数が多すぎます" */
__attribute__((section(".rodata.0x00559510"))) const char D_00559510[24] = "\305\250\244\316\277\364\244\254\302\277\244\271\244\256\244\336\244\271";
