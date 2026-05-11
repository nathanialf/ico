/* charFileManager.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x0063201C"))) int D_0063201C = 0;
__attribute__((section(".sdata.0x00632020"))) int D_00632020 = 0;
__attribute__((section(".sdata.0x00632030"))) int D_00632030 = 0;
__attribute__((section(".sdata.0x00632038"))) int D_00632038 = 0;
__attribute__((section(".sdata.0x00632194"))) int D_00632194 = 0;
__attribute__((section(".sdata.0x00632198"))) char D_00632198[8] = { 0 };
__attribute__((section(".sdata.0x006321A0"))) char D_006321A0[8] = { 0 };
__attribute__((section(".sdata.0x006321A8"))) char D_006321A8[8] = { 0 };
__attribute__((section(".sdata.0x00632244"))) int D_00632244 = 0;
__attribute__((section(".sdata.0x00632248"))) const char D_00632248[8] = "first\n";
__attribute__((section(".sdata.0x00632250"))) const char D_00632250[8] = "set\n";
__attribute__((section(".sdata.0x00632898"))) char D_00632898[8] = { 0 };
__attribute__((section(".sdata.0x006328A0"))) const char D_006328A0[8] = "e";
__attribute__((section(".sdata.0x006328A8"))) const char D_006328A8[8] = "0";
__attribute__((section(".sdata.0x006328B0"))) const char D_006328B0[8] = "FALSE";
__attribute__((section(".sdata.0x006328B8"))) char D_006328B8[8] = { 0 };

__attribute__((section(".rodata.0x00612A70"))) const char D_00612A70[24] = "src/charFileManager.c";

__attribute__((section(".data.0x004D42B0"))) const char D_004D42B0[48] = "object/sdf/boy/model/skelton.skb";
__attribute__((section(".rodata.0x00613A70"))) const char D_00613A70[16] = "Hide-High";
__attribute__((section(".rodata.0x00613A80"))) const char D_00613A80[16] = "Hide-Low";
__attribute__((section(".rodata.0x00613A90"))) const char D_00613A90[16] = "Through-High";
__attribute__((section(".rodata.0x00613AA0"))) const char D_00613AA0[16] = "Through-Low";
__attribute__((section(".rodata.0x00613AB0"))) const char D_00613AB0[16] = "High-Deco";
__attribute__((section(".rodata.0x00613AC0"))) const char D_00613AC0[16] = "Low-Deco";
__attribute__((section(".rodata.0x00613AD0"))) const char D_00613AD0[16] = "Variable";
__attribute__((section(".rodata.0x00613AE0"))) const char D_00613AE0[16] = "Double+Wide";
__attribute__((section(".rodata.0x00613AF0"))) const char D_00613AF0[16] = "Negative-High";
__attribute__((section(".rodata.0x00613B00"))) const char D_00613B00[16] = "Positive-High";
__attribute__((section(".rodata.0x00613B10"))) const char D_00613B10[16] = "Negative-Low";
__attribute__((section(".rodata.0x00613B20"))) const char D_00613B20[16] = "Positive-Low";
__attribute__((section(".rodata.0x00613B30"))) const char D_00613B30[16] = "Light+Ambient";
__attribute__((section(".rodata.0x00613B40"))) const char D_00613B40[16] = "AmbientOnly";
__attribute__((section(".rodata.0x00613B50"))) const char D_00613B50[16] = "LightOnly";
__attribute__((section(".rodata.0x00613B60"))) const char D_00613B60[16] = "Material";
__attribute__((section(".rodata.0x00613B70"))) const char D_00613B70[16] = "ExceptCharacter";
__attribute__((section(".rodata.0x00613B80"))) const char D_00613B80[16] = "IgnoreCarryZ";
__attribute__((section(".rodata.0x00613B90"))) const char D_00613B90[16] = "CarryZOnly";
