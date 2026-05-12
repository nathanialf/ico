/* kanban.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633008"))) const char D_00633008[8] = "/";
__attribute__((section(".sdata.0x00633010"))) const char D_00633010[8] = "0";
__attribute__((section(".sdata.0x00633018"))) unsigned int D_00633018 = 0x7F808080;
__attribute__((section(".sdata.0x0063301C"))) int D_0063301C = 0;
__attribute__((section(".sdata.0x00633020"))) int D_00633020 = 0;
__attribute__((section(".sdata.0x00633024"))) int D_00633024 = 0;
__attribute__((section(".sdata.0x00633028"))) char D_00633028[8] = { 0 };
__attribute__((section(".sdata.0x00633030"))) unsigned int D_00633030 = 0x00706F00;
__attribute__((section(".sdata.0x00633034"))) unsigned int D_00633034 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00633038"))) int D_00633038 = 0;
__attribute__((section(".sdata.0x0063303C"))) int D_0063303C = 0;
__attribute__((section(".sdata.0x00633040"))) unsigned int D_00633040 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00633044"))) unsigned int D_00633044 = 0x00000001;
__attribute__((section(".sdata.0x00633048"))) int D_00633048 = 0;
__attribute__((section(".sdata.0x0063304C"))) int D_0063304C = 0;
__attribute__((section(".sdata.0x00633050"))) int D_00633050 = 0;
__attribute__((section(".sdata.0x00633054"))) int D_00633054 = 0;
__attribute__((section(".sdata.0x00633058"))) int D_00633058 = 0;
__attribute__((section(".sdata.0x0063305C"))) int D_0063305C = 0;

__attribute__((section(".rodata.0x00616CA8"))) const char D_00616CA8[24] = "src/kanban.c";

/* String rodata migrated from kanban_data.c */
__attribute__((section(".rodata.0x00616C90"))) const char D_00616C90[24] = "no texture loaded.(%s)\n";
__attribute__((section(".rodata.0x00616CE0"))) const char D_00616CE0[16] = "sync end\n";
__attribute__((section(".rodata.0x00616CF0"))) const char D_00616CF0[16] = "unformatted %d\n";
__attribute__((section(".rodata.0x00616D00"))) const char D_00616D00[32] = "not insert memory card %d\n";
__attribute__((section(".rodata.0x00616D20"))) const char D_00616D20[24] = "%s file not found\n";
__attribute__((section(".rodata.0x00616D38"))) const char D_00616D38[24] = "%s Directory not found\n";
__attribute__((section(".rodata.0x00616D50"))) const char D_00616D50[48] = "segID %d check sum err rom:%d != load:%d\n";
__attribute__((section(".rodata.0x00616D80"))) const char D_00616D80[32] = "%s handler func ret err code\n";
__attribute__((section(".rodata.0x00616DA0"))) const char D_00616DA0[16] = "memory over\n";
__attribute__((section(".rodata.0x00616DB0"))) const char D_00616DB0[32] = "memory card another err %d\n";
__attribute__((section(".rodata.0x00616ED8"))) const char D_00616ED8[16] = "no memoca\n";
__attribute__((section(".rodata.0x00616EE8"))) const char D_00616EE8[16] = "no free\n";
__attribute__((section(".rodata.0x00616F38"))) const char D_00616F38[24] = "load processing\n";
__attribute__((section(".rodata.0x00616F50"))) const char D_00616F50[16] = "case %d\n";
__attribute__((section(".rodata.0x00616F60"))) const char D_00616F60[24] = "McLoad phase:%d  %x\n";
__attribute__((section(".rodata.0x00616F78"))) const char D_00616F78[16] = "phase++\n";
__attribute__((section(".rodata.0x00616F88"))) const char D_00616F88[16] = "through\n";
__attribute__((section(".rodata.0x00616F98"))) const char D_00616F98[24] = "=== LoadGameBlock ===\n";
__attribute__((section(".rodata.0x00616FB0"))) const char D_00616FB0[16] = "case 10\n";
__attribute__((section(".rodata.0x00616FC0"))) const char D_00616FC0[16] = "stage no %d\n";
__attribute__((section(".rodata.0x00617028"))) const char D_00617028[32] = "save game check port %d\n";
__attribute__((section(".rodata.0x00617048"))) const char D_00617048[24] = "sucess :%d %d %d\n";
__attribute__((section(".rodata.0x00617080"))) const char D_00617080[16] = "format 2\n";
__attribute__((section(".rodata.0x00617090"))) const char D_00617090[16] = "unformat 2\n";
__attribute__((section(".rodata.0x006170A0"))) const char D_006170A0[32] = "already exist save data\n";
__attribute__((section(".rodata.0x006170C0"))) const char D_006170C0[32] = "new save. system data making..\n";
__attribute__((section(".rodata.0x006170E0"))) const char D_006170E0[32] = "McSave phase:%d  %x\n";
__attribute__((section(".rodata.0x00617130"))) const char D_00617130[16] = "save error? %d\n";
__attribute__((section(".rodata.0x00617170"))) const char D_00617170[24] = "save complete %d %d\n";
__attribute__((section(".rodata.0x00617188"))) const char D_00617188[16] = "%d %d %d\n";
__attribute__((section(".rodata.0x00617198"))) const char D_00617198[24] = "push start\n";
__attribute__((section(".rodata.0x0062DF08"))) const char D_0062DF08[32] = "end of packet making...\n";

/* String-pool rodata migrated from kanban_data.c */
__attribute__((section(".rodata.0x00623528"))) const char D_00623528[1664] = "Tex_menu01/scei.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/title.tm2\000\000\000\000\000\000\000\000\000\000\000\000Font/font.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/scei_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/title_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/pause_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/yesno_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cursor.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips1_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/tips2_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX/conti_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p1.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p2.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p3.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p4.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p5.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000TEX2/cont2_p6.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/option.tm2\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/stage.tm2\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/mc01.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/mc02.tm2\000\000\000\000\000\000\000\000\000\000\000\000\000Tex_menu01/mc04.tm2\000\000\000\000\000\000\000\000\000\000\000\000";
