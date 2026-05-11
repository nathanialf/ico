/* camera-editor.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632028"))) int D_00632028 = 0;
__attribute__((section(".sdata.0x00632614"))) unsigned int D_00632614 = 0x030E27E0;
__attribute__((section(".sdata.0x00632618"))) const char D_00632618[8] = "a.txt";
__attribute__((section(".sdata.0x00632620"))) const char D_00632620[8] = "0";
__attribute__((section(".sdata.0x00632628"))) int D_00632628 = 0x0000FBA1;
__attribute__((section(".sdata.0x0063262C"))) int D_0063262C = 0x00000000;
__attribute__((section(".sdata.0x00632630"))) int D_00632630 = 0x0000DFA1;
__attribute__((section(".sdata.0x00632634"))) int D_00632634 = 0x00000000;
__attribute__((section(".sdata.0x00632638"))) float D_00632638[2] = { 3.00393677f, 0.0f };
__attribute__((section(".sdata.0x00632640"))) float D_00632640[2] = { 3.00393677f, 0.0f };
__attribute__((section(".sdata.0x00632648"))) const char D_00632648[8] = "   @";
__attribute__((section(".sdata.0x00632650"))) float D_00632650[2] = { 3.00393677f, 0.0f };
__attribute__((section(".sdata.0x00632658"))) const char D_00632658[8] = " \b\b@";
__attribute__((section(".sdata.0x00632660"))) const char D_00632660[8] = "   @";
__attribute__((section(".sdata.0x00632668"))) float D_00632668[2] = { 2.03137255f, 0.0f };
__attribute__((section(".sdata.0x00632670"))) const char D_00632670[8] = ">> %s";
__attribute__((section(".sdata.0x00632678"))) const char D_00632678[8] = "   %s";
__attribute__((section(".sdata.0x00632680"))) const char D_00632680[8] = "group";
__attribute__((section(".sdata.0x00632688"))) const char D_00632688[] = "width-x";
__attribute__((section(".sdata.0x00632690"))) const char D_00632690[] = "width-y";
__attribute__((section(".sdata.0x00632698"))) const char D_00632698[] = "width-z";
__attribute__((section(".sdata.0x006326A0"))) const char D_006326A0[] = ">>%s %d";
__attribute__((section(".sdata.0x006326A8"))) const char D_006326A8[8] = "ON ";
__attribute__((section(".sdata.0x006326B0"))) const char D_006326B0[8] = "OFF";
__attribute__((section(".sdata.0x006326B8"))) const char D_006326B8[] = "  %s %d";
__attribute__((section(".sdata.0x006326C0"))) const char D_006326C0[8] = "onoff";
__attribute__((section(".sdata.0x006326C8"))) const char D_006326C8[8] = "view";
__attribute__((section(".sdata.0x006326D0"))) int D_006326D0 = 0;
__attribute__((section(".sdata.0x006326D4"))) int D_006326D4 = 0;
__attribute__((section(".sdata.0x006326D8"))) char D_006326D8[8] = { 0 };

__attribute__((section(".rodata.0x0055A5C0"))) const char D_0055A5C0[24] = "src/camera-editor.c";

__attribute__((section(".rodata.0x0055A630"))) const char D_0055A630[16] = "ico2Data/%s";
__attribute__((section(".rodata.0x0055A6A8"))) const char D_0055A6A8[40] = "error---cannot open save camera data";
__attribute__((section(".rodata.0x0055A830"))) const char D_0055A830[16] = "center-x";
__attribute__((section(".rodata.0x0055A840"))) const char D_0055A840[16] = "center-y";
__attribute__((section(".rodata.0x0055A850"))) const char D_0055A850[16] = "center-z";
__attribute__((section(".rodata.0x0055A880"))) const char D_0055A880[16] = "camera-x";
__attribute__((section(".rodata.0x0055A890"))) const char D_0055A890[16] = "camera-y";
__attribute__((section(".rodata.0x0055A8A0"))) const char D_0055A8A0[16] = "camera-z";
__attribute__((section(".rodata.0x0055A8B0"))) const char D_0055A8B0[16] = "target-x";
__attribute__((section(".rodata.0x0055A8C0"))) const char D_0055A8C0[16] = "target-y";
__attribute__((section(".rodata.0x0055A8D0"))) const char D_0055A8D0[16] = "target-z";
