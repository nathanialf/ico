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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern int D_00633530;
extern int D_00633534;
extern int D_00633538;
extern int D_0063353C;
extern int D_00633540;
extern int D_00633544;
extern int D_00633548;
extern float D_0063354C;
extern int D_00633550;
extern int D_00633554;
extern unsigned int D_00633558;
extern unsigned int D_0063355C;
extern int D_00633560;
extern unsigned int D_00633564;
extern int D_00633568;
extern int D_0063356C;
extern const char D_00633570[8];
extern const char D_00633578[8];
extern const char D_00633580[];
extern int D_00633588;
extern int D_0063358C;
extern int D_00633590;
extern int D_00633594;
extern int D_00633598;
extern short D_0063359C;
extern short D_0063359E;
extern int D_006335A0;
extern int D_006335A4;
extern int D_006335A8;
extern float D_006335AC;
extern int D_006335B0;
extern int D_006335B4;
extern const char D_006335B8[8];

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

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E4D90);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E4F40);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E50C8);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E54E0);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E5848);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E5AF8);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E5F78);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E6788);
