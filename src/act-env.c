/* act-env.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x0063144C"))) float D_0063144C = 4900.0f;
__attribute__((section(".lit4.0x00631450"))) float D_00631450 = 1.57079637f;
__attribute__((section(".lit4.0x00631454"))) float D_00631454 = 355.0f;
__attribute__((section(".lit4.0x00631458"))) float D_00631458 = 10000.0f;
__attribute__((section(".lit4.0x0063145C"))) float D_0063145C = 22500.0f;
__attribute__((section(".lit4.0x00631460"))) float D_00631460 = 10000.0f;
__attribute__((section(".lit4.0x00631464"))) float D_00631464 = 40000.0f;
__attribute__((section(".lit4.0x00631468"))) float D_00631468 = 1.57079637f;
__attribute__((section(".lit4.0x0063146C"))) float D_0063146C = 4900.0f;
__attribute__((section(".lit4.0x00631470"))) float D_00631470 = 22500.0f;
__attribute__((section(".lit4.0x00631474"))) float D_00631474 = 12100.0f;
__attribute__((section(".lit4.0x00631478"))) float D_00631478 = 3.14159274f;
__attribute__((section(".lit4.0x0063147C"))) float D_0063147C = 10000.0f;
__attribute__((section(".lit4.0x00631480"))) float D_00631480 = 40000.0f;
__attribute__((section(".sdata.0x00631990"))) char D_00631990[16] = { 0 };
__attribute__((section(".sdata.0x006319A0"))) char D_006319A0[16] = { 0 };
__attribute__((section(".sdata.0x006319B0"))) char D_006319B0[16] = { 0 };
__attribute__((section(".sdata.0x00633840"))) const char D_00633840[8] = "0";
__attribute__((section(".sdata.0x00633848"))) const char D_00633848[8] = "water\n";
__attribute__((section(".sdata.0x00633850"))) unsigned int D_00633850 = 0x7F7FFFFF;
__attribute__((section(".sdata.0x0063385C"))) int D_0063385C = 0;
__attribute__((section(".sdata.0x00633860"))) int D_00633860 = 0;
__attribute__((section(".sdata.0x00633864"))) int D_00633864 = 0;
__attribute__((section(".sdata.0x00633868"))) unsigned int D_00633868 = 0x7F7FFFFF;

__attribute__((section(".rodata.0x0061AE10"))) const char D_0061AE10[16] = "src/act-env.c";

__attribute__((section(".rodata.0x0061AD20"))) const char D_0061AD20[16] = "climb_50  ";
__attribute__((section(".rodata.0x0061AD30"))) const char D_0061AD30[16] = "climb_100 ";
__attribute__((section(".rodata.0x0061AD40"))) const char D_0061AD40[16] = "climb_200 ";
__attribute__((section(".rodata.0x0061AD50"))) const char D_0061AD50[16] = "climb_300 ";
__attribute__((section(".rodata.0x0061AD60"))) const char D_0061AD60[16] = "hold_box  ";
__attribute__((section(".rodata.0x0061AD70"))) const char D_0061AD70[16] = "hang_hand ";
__attribute__((section(".rodata.0x0061AD80"))) const char D_0061AD80[16] = "hang_breas";
__attribute__((section(".rodata.0x0061AD90"))) const char D_0061AD90[16] = "ladder_up ";
__attribute__((section(".rodata.0x0061ADA0"))) const char D_0061ADA0[16] = "ladder_dow";
__attribute__((section(".rodata.0x0061ADB0"))) const char D_0061ADB0[16] = "down_cliff";
__attribute__((section(".rodata.0x0061ADC0"))) const char D_0061ADC0[16] = "walk_wall";
__attribute__((section(".rodata.0x0061ADD0"))) const char D_0061ADD0[16] = "walk_stair";
__attribute__((section(".rodata.0x0061ADE0"))) const char D_0061ADE0[16] = "pulledup_50 ";
__attribute__((section(".rodata.0x0061ADF0"))) const char D_0061ADF0[16] = "pulledup_100";
__attribute__((section(".rodata.0x0061AE00"))) const char D_0061AE00[16] = "pulledup_200";

/* String rodata migrated from act-env_data.c */
__attribute__((section(".rodata.0x0061AE20"))) const char D_0061AE20[16] = "enter water\n";
__attribute__((section(".rodata.0x0061AEB0"))) const char D_0061AEB0[32] = "--b-- %p:act brain del %p\n";
__attribute__((section(".rodata.0x0061AED0"))) const char D_0061AED0[32] = "--b-- %p:act brain NULL %p\n";
__attribute__((section(".rodata.0x0061AEF0"))) const char D_0061AEF0[32] = "--m-- %p:act main del %p\n";
__attribute__((section(".rodata.0x0061AF10"))) const char D_0061AF10[32] = "--m-- %p:act main NULL %p\n";
__attribute__((section(".rodata.0x0061AF30"))) const char D_0061AF30[32] = "--t-- %p:act mot del %p\n";
__attribute__((section(".rodata.0x0061AF50"))) const char D_0061AF50[32] = "--t-- %p:act mot NULL %p\n";
__attribute__((section(".rodata.0x0061AF70"))) const char D_0061AF70[16] = "acst[%p]\n";
__attribute__((section(".rodata.0x0061AF80"))) const char D_0061AF80[16] = "    [%d]\n";
__attribute__((section(".rodata.0x0061AF90"))) const char D_0061AF90[16] = "lval[%p]\n";

/* Float rodata migrated from act-env_data.c */
__attribute__((section(".rodata.0x0061AD10"))) const float D_0061AD10[4] = { 3e+01f, 0.0f, -5e+01f, 0.0f };

/* String-pool rodata migrated from act-env_data.c */
__attribute__((section(".rodata.0x0061AE30"))) const char D_0061AE30[32] = "exit water\n\000\000\000\000\000WBP <<begin>>\n\000";
