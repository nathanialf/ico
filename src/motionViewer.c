/* motionViewer.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633530"))) int D_00633530 = 0;
__attribute__((section(".sdata.0x00633534"))) int D_00633534 = 0;
__attribute__((section(".sdata.0x00633538"))) int D_00633538 = 0;
__attribute__((section(".sdata.0x0063353C"))) int D_0063353C = 0;
__attribute__((section(".sdata.0x00633540"))) int D_00633540 = 0;
__attribute__((section(".sdata.0x00633544"))) int D_00633544 = 0;
__attribute__((section(".sdata.0x00633548"))) int D_00633548 = 0;
__attribute__((section(".sdata.0x0063354C"))) float D_0063354C = 1.0f;
__attribute__((section(".sdata.0x00633550"))) int D_00633550 = 0x80C05434;
__attribute__((section(".sdata.0x00633554"))) int D_00633554 = 0x00000000;
__attribute__((section(".sdata.0x00633558"))) unsigned int D_00633558 = 0x803454C0;
__attribute__((section(".sdata.0x0063355C"))) unsigned int D_0063355C = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00633560"))) int D_00633560 = 0;
__attribute__((section(".sdata.0x00633564"))) unsigned int D_00633564 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00633568"))) int D_00633568 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x0063356C"))) int D_0063356C = 0x00000000;
__attribute__((section(".sdata.0x00633570"))) const char D_00633570[8] = "%c %s";
__attribute__((section(".sdata.0x00633578"))) const char D_00633578[8] = "Depend";
__attribute__((section(".sdata.0x00633580"))) const char D_00633580[] = "RotOnly";
__attribute__((section(".sdata.0x00633588"))) int D_00633588 = 0x203A8320;
__attribute__((section(".sdata.0x0063358C"))) int D_0063358C = 0x00007325;
__attribute__((section(".sdata.0x00633590"))) int D_00633590 = 0;
__attribute__((section(".sdata.0x00633594"))) int D_00633594 = 0;
__attribute__((section(".sdata.0x00633598"))) int D_00633598 = 0;
__attribute__((section(".sdata.0x0063359C"))) short D_0063359C = 0;
__attribute__((section(".sdata.0x0063359E"))) short D_0063359E = 0;
__attribute__((section(".sdata.0x006335A0"))) int D_006335A0 = 0;
__attribute__((section(".sdata.0x006335A4"))) int D_006335A4 = 0;
__attribute__((section(".sdata.0x006335A8"))) int D_006335A8 = 0;
__attribute__((section(".sdata.0x006335AC"))) float D_006335AC = 100.0f;
__attribute__((section(".sdata.0x006335B0"))) int D_006335B0 = 0;
__attribute__((section(".sdata.0x006335B4"))) int D_006335B4 = 0;
__attribute__((section(".sdata.0x006335B8"))) const char D_006335B8[8] = "%d\n";

__attribute__((section(".rodata.0x00619C00"))) const char D_00619C00[24] = "src/motionViewer.c";

__attribute__((section(".rodata.0x00619C18"))) const char D_00619C18[16] = "Motion Viewer";
__attribute__((section(".rodata.0x00619C28"))) const char D_00619C28[32] = "NO MOTION IN THIS STAGE.";
__attribute__((section(".rodata.0x00619C48"))) const char D_00619C48[24] = "Frame : %1.1f/%d";
__attribute__((section(".rodata.0x00619C60"))) const char D_00619C60[24] = "x%1.3f: %1.1f/%d";
__attribute__((section(".rodata.0x00619C78"))) const char D_00619C78[32] = "ORIENT for \"%s\" Frame: %1.1f/%d";
__attribute__((section(".rodata.0x00619C98"))) const char D_00619C98[16] = "  NO ORIENT.";
__attribute__((section(".rodata.0x00619CA8"))) const char D_00619CA8[24] = "NO ORIENT for \"%s\"";
__attribute__((section(".rodata.0x00619D00"))) const char D_00619D00[32] = "Left: Target direct orient.";
__attribute__((section(".rodata.0x00619D20"))) const char D_00619D20[32] = "Left: Target with motion.";
__attribute__((section(".rodata.0x00619D40"))) const char D_00619D40[32] = "Right: Target direct orient.";
__attribute__((section(".rodata.0x00619D60"))) const char D_00619D60[32] = "Right: Target with motion.";
