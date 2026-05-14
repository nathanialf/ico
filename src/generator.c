/* generator.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632798"))) const char D_00632798[8] = "0";
__attribute__((section(".sdata.0x006327A0"))) const char D_006327A0[8] = "revive";
__attribute__((section(".sdata.0x006327A8"))) const char D_006327A8[8] = "error!";
__attribute__((section(".sdata.0x006327B0"))) int D_006327B0 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x006327B4"))) int D_006327B4 = 0x00000000;
__attribute__((section(".sdata.0x006327B8"))) const char D_006327B8[8] = "EAT";
__attribute__((section(".sdata.0x006327C0"))) const char D_006327C0[8] = "STEP";
__attribute__((section(".sdata.0x006327C8"))) const char D_006327C8[8] = "GROOM";
__attribute__((section(".sdata.0x006327D0"))) const char D_006327D0[8] = "FLY S";
__attribute__((section(".sdata.0x006327D8"))) const char D_006327D8[8] = "FLY";
__attribute__((section(".sdata.0x006327E0"))) const char D_006327E0[8] = "FLY E1";
__attribute__((section(".sdata.0x006327E8"))) const char D_006327E8[8] = "FLY E2";
__attribute__((section(".sdata.0x006327F0"))) const char D_006327F0[] = "barr %d";
__attribute__((section(".sdata.0x006327F8"))) unsigned int D_006327F8 = 0x80808080;
__attribute__((section(".sdata.0x006327FC"))) int D_006327FC = 0;
__attribute__((section(".sdata.0x00632800"))) const char D_00632800[8] = "%s";
__attribute__((section(".sdata.0x00632808"))) unsigned int D_00632808 = 0x00000001;
__attribute__((section(".sdata.0x0063280C"))) int D_0063280C = 0;
__attribute__((section(".sdata.0x00632810"))) char D_00632810[8] = { 0 };
__attribute__((section(".sdata.0x00632820"))) const char D_00632820[8] = "%s\n";
__attribute__((section(".sdata.0x00632828"))) float D_00632828[2] = { -7.688999e-06f, 0.0f };
__attribute__((section(".sdata.0x00632830"))) int D_00632830 = 0;
__attribute__((section(".sdata.0x00632834"))) int D_00632834 = 0;
__attribute__((section(".sdata.0x00632838"))) unsigned int D_00632838 = 0x00000003;
__attribute__((section(".sdata.0x0063283C"))) unsigned int D_0063283C = 0x80000000;
__attribute__((section(".sdata.0x00632840"))) int D_00632840 = 0;
__attribute__((section(".sdata.0x00632844"))) int D_00632844 = 0;
__attribute__((section(".sdata.0x00632848"))) const char D_00632848[8] = "here\n";
__attribute__((section(".sdata.0x00632850"))) int D_00632850 = 0;

__attribute__((section(".rodata.0x0055AEA0"))) const char D_0055AEA0[16] = "src/generator.c";

/* String rodata migrated from generator_data.c */
__attribute__((section(".rodata.0x0055AEB0"))) const char D_0055AEB0[32] = "call enemy! = %d (%p : %d)\n";
__attribute__((section(".rodata.0x0055AED0"))) const char D_0055AED0[24] = "[%8s] %8f %8f %8f %8f\n";
__attribute__((section(".rodata.0x0055AEE8"))) const char D_0055AEE8[16] = "lock! = %d\n";
__attribute__((section(".rodata.0x0055AEF8"))) const char D_0055AEF8[16] = "unlock! = %d\n";
