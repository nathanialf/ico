/* StageAnimation.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00631A10"))) char D_00631A10[16] = { 0 };
__attribute__((section(".sdata.0x00631D88"))) const char D_00631D88[8] = "0";
__attribute__((section(".sdata.0x00631D90"))) const char D_00631D90[8] = "BGA";
__attribute__((section(".sdata.0x00631D98"))) const char D_00631D98[8] = "e";
__attribute__((section(".sdata.0x00631DA0"))) const char D_00631DA0[8] = "PSMT8";
__attribute__((section(".sdata.0x00631DA8"))) const char D_00631DA8[8] = "PSMT4";
__attribute__((section(".sdata.0x00631DB0"))) const char D_00631DB0[] = "PSMCT32";
__attribute__((section(".sdata.0x00631DB8"))) const char D_00631DB8[] = "PSMCT24";
__attribute__((section(".sdata.0x00631DC0"))) const char D_00631DC0[] = "PSMCT16";
__attribute__((section(".sdata.0x00631DC8"))) const char D_00631DC8[8] = "NONE";

__attribute__((section(".rodata.0x00555BF8"))) const char D_00555BF8[24] = "src/StageAnimation.c";

__attribute__((section(".rodata.0x00612348"))) const char D_00612348[48] = "object/sdf/demo/conte06/d6.smb";
__attribute__((section(".rodata.0x00612378"))) const char D_00612378[48] = "object/sdf/demo/conte09/d9.smb";
__attribute__((section(".rodata.0x006123A8"))) const char D_006123A8[48] = "object/sdf/demo/conte09a/d9a.smb";
__attribute__((section(".rodata.0x00612498"))) const char D_00612498[48] = "object/sdf/demo/conte13/d13.smb";
__attribute__((section(".rodata.0x006124C8"))) const char D_006124C8[48] = "object/sdf/demo/conte06/e3d6.smb";

/* String rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x00555BB0"))) const char D_00555BB0[32] = "Bga Object Already %d %d %d\n";
__attribute__((section(".rodata.0x00555BD0"))) const char D_00555BD0[40] = "stage_MakeGObj:can't alloc gobj %d\n";
__attribute__((section(".rodata.0x00555C10"))) const char D_00555C10[40] = "Too much Stage Animation Objects.\n";
__attribute__((section(".rodata.0x00555C38"))) const char D_00555C38[48] = "stage_ApplyData:Data is not registered. \n\n%s\n";
__attribute__((section(".rodata.0x00555CF8"))) const char D_00555CF8[40] = "Max Bga = %d // Max DObj %d\n";
__attribute__((section(".rodata.0x00555D78"))) const char D_00555D78[56] = "stage_CheckAnimationFinish:illegal Animation No.\n";
__attribute__((section(".rodata.0x00555DB0"))) const char D_00555DB0[48] = "stage_ContinueAnimation:illegal Animation No.\n";

/* Float rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x00555B70"))) const float D_00555B70[16] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };

/* String-pool rodata migrated from StageAnimation_data.c */
__attribute__((section(".rodata.0x006123D8"))) const char D_006123D8[96] = "object/sdf/demo/conte09a/d9b.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12/d12.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
__attribute__((section(".rodata.0x00612438"))) const char D_00612438[96] = "object/sdf/demo/conte12x/d12x.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000object/sdf/demo/conte12x/d12y.smb\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
