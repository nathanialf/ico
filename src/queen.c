/* queen.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x0063106C"))) float D_0063106C = 0.98f;
__attribute__((section(".lit4.0x00631070"))) float D_00631070 = 0.9f;
__attribute__((section(".lit4.0x00631074"))) float D_00631074 = 0.001f;
__attribute__((section(".lit4.0x00631078"))) float D_00631078 = 0.05235988f;
__attribute__((section(".lit4.0x0063107C"))) float D_0063107C = 0.08726647f;
__attribute__((section(".lit4.0x00631080"))) float D_00631080 = 0.122173056f;
__attribute__((section(".lit4.0x00631084"))) float D_00631084 = 0.02f;
__attribute__((section(".lit4.0x00631088"))) float D_00631088 = 0.05f;
__attribute__((section(".lit4.0x0063108C"))) float D_0063108C = 6.28318548f;
__attribute__((section(".lit4.0x00631090"))) float D_00631090 = 3.14159274f;
__attribute__((section(".lit4.0x00631094"))) float D_00631094 = 6.28318548f;
__attribute__((section(".lit4.0x00631098"))) float D_00631098 = -3.14159274f;
__attribute__((section(".lit4.0x0063109C"))) float D_0063109C = 6.28318548f;
__attribute__((section(".lit4.0x006310A0"))) float D_006310A0 = 6.28318548f;
__attribute__((section(".lit4.0x006310A4"))) float D_006310A4 = 3.14159274f;
__attribute__((section(".lit4.0x006310A8"))) float D_006310A8 = 6.28318548f;
__attribute__((section(".lit4.0x006310AC"))) float D_006310AC = -3.14159274f;
__attribute__((section(".lit4.0x006310B0"))) float D_006310B0 = 6.28318548f;
__attribute__((section(".lit4.0x006310B4"))) float D_006310B4 = 6.28318548f;
__attribute__((section(".lit4.0x006310B8"))) float D_006310B8 = 3.14159274f;
__attribute__((section(".lit4.0x006310BC"))) float D_006310BC = 6.28318548f;
__attribute__((section(".lit4.0x006310C0"))) float D_006310C0 = -3.14159274f;
__attribute__((section(".lit4.0x006310C4"))) float D_006310C4 = 6.28318548f;
__attribute__((section(".lit4.0x006310C8"))) float D_006310C8 = 5000.0f;
__attribute__((section(".lit4.0x006310CC"))) float D_006310CC = 2340.57153f;
__attribute__((section(".lit4.0x006310D0"))) float D_006310D0 = 10430.3779f;

__attribute__((section(".rodata.0x0055C690"))) const char D_0055C690[16] = "src/queen.c";

__attribute__((section(".rodata.0x0055C620"))) const char D_0055C620[40] = "n_enemy_max:%d n_enemy:%d counter:%d";
__attribute__((section(".rodata.0x0055C658"))) const char D_0055C658[24] = "queen_ball_scr";
__attribute__((section(".rodata.0x0055C6C8"))) const char D_0055C6C8[16] = "damage:%d";
__attribute__((section(".rodata.0x0055CEB0"))) const char D_0055CEB0[32] = "../ito/include/mv_defs.h";
__attribute__((section(".rodata.0x0055CF10"))) const char D_0055CF10[32] = "../ito/include/mv_defs.h";
__attribute__((section(".rodata.0x0055CF30"))) const char D_0055CF30[16] = "p != NULL";
__attribute__((section(".rodata.0x0055CF70"))) const char D_0055CF70[40] = "sceMpegGetPicture() decode error";
__attribute__((section(".rodata.0x0055CFA8"))) const char D_0055CFA8[32] = "../ito/include/mv_defs.h";
__attribute__((section(".rodata.0x0055CFC8"))) const char D_0055CFC8[16] = "p != NULL";

/* String rodata migrated from queen_data.c */
__attribute__((section(".rodata.0x0055C5C0"))) const char D_0055C5C0[16] = "queen attacked\n";
__attribute__((section(".rodata.0x0055C5D0"))) const char D_0055C5D0[16] = "enemy dead %p\n";
__attribute__((section(".rodata.0x0055C648"))) const char D_0055C648[16] = "queen dead\n";
__attribute__((section(".rodata.0x0055C6A0"))) const char D_0055C6A0[24] = "queen barrier attacked\n";
__attribute__((section(".rodata.0x0055C6D8"))) const char D_0055C6D8[16] = "mail %d\n";
__attribute__((section(".rodata.0x0055C6E8"))) const char D_0055C6E8[24] = "queen ball attacked\n";
__attribute__((section(".rodata.0x0055C720"))) const char D_0055C720[32] = "queen barrier damaged\n";
__attribute__((section(".rodata.0x0055CD98"))) const char D_0055CD98[16] = "movie pause\n";
__attribute__((section(".rodata.0x0055CDA8"))) const char D_0055CDA8[16] = "D_CTRL %x\n";
__attribute__((section(".rodata.0x0055CDB8"))) const char D_0055CDB8[24] = "open movie file %s\n";
__attribute__((section(".rodata.0x0055CDD0"))) const char D_0055CDD0[32] = "create video decode thread\n";
__attribute__((section(".rodata.0x0055CDF0"))) const char D_0055CDF0[16] = "start thread\n";
__attribute__((section(".rodata.0x0055CE00"))) const char D_0055CE00[16] = "add intc\n";
__attribute__((section(".rodata.0x0055CE10"))) const char D_0055CE10[24] = "add intc failed\n";
__attribute__((section(".rodata.0x0055CE28"))) const char D_0055CE28[16] = "add dmac\n";
__attribute__((section(".rodata.0x0055CE38"))) const char D_0055CE38[24] = "add dmac failed\n";
__attribute__((section(".rodata.0x0055CE50"))) const char D_0055CE50[24] = "sceGsGetIMR() %lx\n";
__attribute__((section(".rodata.0x0055CE68"))) const char D_0055CE68[16] = "dmac %d %d\n";
__attribute__((section(".rodata.0x0055CE78"))) const char D_0055CE78[16] = "intc %d %d\n";
__attribute__((section(".rodata.0x0055CE88"))) const char D_0055CE88[24] = "movie init failed\n";
__attribute__((section(".rodata.0x0055CEA0"))) const char D_0055CEA0[16] = "movie end\n";
__attribute__((section(".rodata.0x0055CF40"))) const char D_0055CF40[24] = "pts buffer overflow\n";
__attribute__((section(".rodata.0x0055CF58"))) const char D_0055CF58[24] = "decode thread: aborted\n";
__attribute__((section(".rodata.0x0055CF98"))) const char D_0055CF98[16] = "movie %d x %d\n";

/* Float rodata migrated from queen_data.c */
__attribute__((section(".rodata.0x0055C2C0"))) const float D_0055C2C0[12] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.0f };
__attribute__((section(".rodata.0x0055C2F0"))) const float D_0055C2F0[66] = { 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f };
__attribute__((section(".rodata.0x0055C3F8"))) const float D_0055C3F8[12] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
__attribute__((section(".rodata.0x0055C428"))) const float D_0055C428[12] = { 3.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
__attribute__((section(".rodata.0x0055C458"))) const float D_0055C458[12] = { 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f };
__attribute__((section(".rodata.0x0055C488"))) const float D_0055C488[12] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.0f };
__attribute__((section(".rodata.0x0055C4B8"))) const float D_0055C4B8[66] = { 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f };
__attribute__((section(".rodata.0x0055C700"))) const float D_0055C700[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
__attribute__((section(".rodata.0x0055C740"))) const float D_0055C740[4] = { 2.5e+02f, 1.5e+02f, 2e+02f, 0.0f };
__attribute__((section(".rodata.0x0055C750"))) const float D_0055C750[4] = { 1e+02f, 1.2e+02f, 115.0f, 0.0f };
