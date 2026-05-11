/* FileManager.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631B90"))) const char D_00631B90[8] = ";1";
__attribute__((section(".sdata.0x00631B98"))) const char D_00631B98[8] = "FALSE";
__attribute__((section(".sdata.0x00631BA0"))) char D_00631BA0[8] = { 0 };
__attribute__((section(".sdata.0x00631BA8"))) int D_00631BA8 = 0;
__attribute__((section(".sdata.0x00631BAC"))) int D_00631BAC = 0;
__attribute__((section(".sdata.0x00631BB0"))) char D_00631BB0[8] = { 0 };
__attribute__((section(".sdata.0x00631BB8"))) int D_00631BB8 = 0;
__attribute__((section(".sdata.0x00631BBC"))) int D_00631BBC = 0;
__attribute__((section(".sdata.0x00631BC0"))) float D_00631BC0 = 1.0f;
__attribute__((section(".sdata.0x00631BC4"))) float D_00631BC4 = 1.0f;
__attribute__((section(".sdata.0x00631BC8"))) float D_00631BC8 = 1000.0f;
__attribute__((section(".sdata.0x0063200C"))) int D_0063200C = 0;
__attribute__((section(".sdata.0x00632018"))) int D_00632018 = 0;
__attribute__((section(".sdata.0x0063202C"))) int D_0063202C = 0;
__attribute__((section(".sdata.0x00632034"))) int D_00632034 = 0;

__attribute__((section(".rodata.0x00554040"))) const char D_00554040[24] = "src/FileManager.c";

__attribute__((section(".rodata.0x00554720"))) const char D_00554720[32] = "LID:%3d / FADE%d:%3.0f(%d)";
__attribute__((section(".rodata.0x005547A0"))) const char D_005547A0[32] = "object/stagesetting/%s.ssb";
__attribute__((section(".rodata.0x00554A40"))) const char D_00554A40[24] = " AntiLevel1          ";
__attribute__((section(".rodata.0x00554A58"))) const char D_00554A58[24] = " AntiLevel0          ";
__attribute__((section(".rodata.0x00554A70"))) const char D_00554A70[24] = " Motion Blur         ";
__attribute__((section(".rodata.0x00554A88"))) const char D_00554A88[24] = " DepthField Width    ";
__attribute__((section(".rodata.0x00554AA0"))) const char D_00554AA0[24] = " DepthField Start    ";
__attribute__((section(".rodata.0x00554AB8"))) const char D_00554AB8[24] = " DepthField Level    ";
__attribute__((section(".rodata.0x00554AD0"))) const char D_00554AD0[24] = " Feedback Effect A   ";
__attribute__((section(".rodata.0x00554AE8"))) const char D_00554AE8[24] = " Feedback Effect B   ";
__attribute__((section(".rodata.0x00554B00"))) const char D_00554B00[24] = " Feedback Effect G   ";
__attribute__((section(".rodata.0x00554B18"))) const char D_00554B18[24] = " Feedback Effect R   ";
__attribute__((section(".rodata.0x00554B30"))) const char D_00554B30[24] = " Feedback Effect     ";
__attribute__((section(".rodata.0x00554B48"))) const char D_00554B48[24] = " Post Effect         ";
__attribute__((section(".rodata.0x00554B60"))) const char D_00554B60[24] = " Def Tex Sample Mode ";
__attribute__((section(".rodata.0x00554B78"))) const char D_00554B78[24] = " Zoom Offset         ";
__attribute__((section(".rodata.0x00554B90"))) const char D_00554B90[24] = " HighLight Color B   ";
__attribute__((section(".rodata.0x00554BA8"))) const char D_00554BA8[24] = " HighLight Color G   ";
__attribute__((section(".rodata.0x00554BC0"))) const char D_00554BC0[24] = " HighLight Color R   ";
__attribute__((section(".rodata.0x00554BE0"))) const char D_00554BE0[24] = "StageSetting Tool";
__attribute__((section(".rodata.0x00554C28"))) const char D_00554C28[16] = "Save Settings";
__attribute__((section(".rodata.0x00554C38"))) const char D_00554C38[16] = "Load Settings";
__attribute__((section(".rodata.0x00554C48"))) const char D_00554C48[16] = "Other Settings";
__attribute__((section(".rodata.0x00554C58"))) const char D_00554C58[16] = "Fog Tool";
__attribute__((section(".rodata.0x00554C68"))) const char D_00554C68[16] = "Shadow Tool";
__attribute__((section(".rodata.0x00554C78"))) const char D_00554C78[16] = "Light Tool";
