/* DObj.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x006310D4"))) float D_006310D4 = 0.333f;
__attribute__((section(".lit4.0x006310D8"))) float D_006310D8 = 3.14159274f;
__attribute__((section(".lit4.0x006310DC"))) float D_006310DC = 1e+07f;
__attribute__((section(".lit4.0x006310E0"))) float D_006310E0 = 0.000111111112f;
__attribute__((section(".lit4.0x006310E4"))) float D_006310E4 = 0.01f;
__attribute__((section(".lit4.0x006310E8"))) float D_006310E8 = 0.000111111112f;
__attribute__((section(".lit4.0x006310EC"))) float D_006310EC = 0.001f;
__attribute__((section(".lit4.0x006310F0"))) float D_006310F0 = 0.001f;
__attribute__((section(".lit4.0x006310F4"))) float D_006310F4 = 1e+07f;
__attribute__((section(".lit4.0x006310F8"))) float D_006310F8 = 0.8f;
__attribute__((section(".lit4.0x006310FC"))) float D_006310FC = 3.14159274f;
__attribute__((section(".lit4.0x00631100"))) float D_00631100 = 3.14159274f;
__attribute__((section(".lit4.0x00631104"))) float D_00631104 = 0.05f;
__attribute__((section(".lit4.0x00631108"))) float D_00631108 = 0.025f;
__attribute__((section(".lit4.0x0063110C"))) float D_0063110C = 0.4f;
__attribute__((section(".lit4.0x00631110"))) float D_00631110 = 3.14159274f;
__attribute__((section(".lit4.0x00631114"))) float D_00631114 = 3.14159274f;
__attribute__((section(".lit4.0x00631118"))) float D_00631118 = 10000.0f;
__attribute__((section(".lit4.0x0063111C"))) float D_0063111C = 0.8f;
__attribute__((section(".lit4.0x00631120"))) float D_00631120 = 0.1f;
__attribute__((section(".lit4.0x00631124"))) float D_00631124 = 2500.0f;
__attribute__((section(".lit4.0x00631128"))) float D_00631128 = 0.1f;
__attribute__((section(".lit4.0x0063112C"))) float D_0063112C = 10000.0f;
__attribute__((section(".lit4.0x00631130"))) float D_00631130 = 10000.0f;
__attribute__((section(".lit4.0x00631134"))) float D_00631134 = 0.05f;
__attribute__((section(".lit4.0x00631138"))) float D_00631138 = 10000.0f;
__attribute__((section(".lit4.0x0063113C"))) float D_0063113C = 10000.0f;
__attribute__((section(".lit4.0x00631140"))) float D_00631140 = 0.2f;
__attribute__((section(".lit4.0x00631144"))) float D_00631144 = 0.2f;
__attribute__((section(".sdata.0x00632024"))) int D_00632024 = 0;

__attribute__((section(".rodata.0x00612620"))) const char D_00612620[16] = "src/DObj.c";

__attribute__((section(".rodata.0x006127E8"))) const char D_006127E8[24] = "DFDATAS/COMMON.DF";
__attribute__((section(".rodata.0x00612890"))) const char D_00612890[16] = "girl nokori";

/* String rodata migrated from DObj_data.c */
__attribute__((section(".rodata.0x006126B8"))) const char D_006126B8[24] = "----- MASK LINK -----\n";
__attribute__((section(".rodata.0x006126D0"))) const char D_006126D0[24] = "sound partition reset\n";
__attribute__((section(".rodata.0x006126E8"))) const char D_006126E8[32] = "sound partition not reset\n";
__attribute__((section(".rodata.0x00612708"))) const char D_00612708[16] = "InitTableSin\n";
__attribute__((section(".rodata.0x00612718"))) const char D_00612718[24] = "InitMatrixDrive\n";
__attribute__((section(".rodata.0x00612730"))) const char D_00612730[16] = "debug_Init\n";
__attribute__((section(".rodata.0x00612740"))) const char D_00612740[24] = "p2o transMicroProgram\n";
__attribute__((section(".rodata.0x00612758"))) const char D_00612758[16] = "InitGSSystem\n";
__attribute__((section(".rodata.0x00612768"))) const char D_00612768[24] = "init debug menu\n";
__attribute__((section(".rodata.0x00612780"))) const char D_00612780[16] = "enable vsync\n";
__attribute__((section(".rodata.0x00612790"))) const char D_00612790[16] = "auto stack %d\n";
__attribute__((section(".rodata.0x006127A0"))) const char D_006127A0[32] = "-----------------Enable VSync\n";
__attribute__((section(".rodata.0x006127C0"))) const char D_006127C0[40] = "preload %s move %d total %d reset %d\n";
__attribute__((section(".rodata.0x00612800"))) const char D_00612800[24] = "stage manager() in\n";
__attribute__((section(".rodata.0x00612818"))) const char D_00612818[16] = "IosCdLock %d\n";
__attribute__((section(".rodata.0x00612828"))) const char D_00612828[24] = "STAGE MANAGER START\n";
__attribute__((section(".rodata.0x00612840"))) const char D_00612840[24] = "out of stage %d\n";
__attribute__((section(".rodata.0x006128F8"))) const char D_006128F8[40] = "backstage timeLimit gamesys area error\n";
__attribute__((section(".rodata.0x00612920"))) const char D_00612920[16] = "way num %d\n";
__attribute__((section(".rodata.0x00612930"))) const char D_00612930[32] = "%d %d:dist %f calcdist %f\n";
__attribute__((section(".rodata.0x00612950"))) const char D_00612950[24] = "set pos_table %f %f %f\n";
__attribute__((section(".rodata.0x006129F0"))) const char D_006129F0[24] = "set pos %f %f %f\n";

/* Float rodata migrated from DObj_data.c */
__attribute__((section(".rodata.0x00612630"))) const float D_00612630[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

/* String-pool rodata migrated from DObj_data.c */
__attribute__((section(".rodata.0x00612858"))) const char D_00612858[56] = "StageManager:unknown msg\n\000\000\000\000\000\000\000stage manager() out\n\000\000\000";
