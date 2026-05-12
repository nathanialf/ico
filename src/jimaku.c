/* jimaku.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632514"))) int D_00632514 = 0;
__attribute__((section(".sdata.0x00632518"))) int D_00632518 = 0x00000001;
__attribute__((section(".sdata.0x0063251C"))) int D_0063251C = 0x00000000;
__attribute__((section(".sdata.0x00632520"))) int D_00632520 = 0x80808080;
__attribute__((section(".sdata.0x00632524"))) int D_00632524 = 0x00000000;
__attribute__((section(".sdata.0x00632528"))) int D_00632528 = 0x00000030;
__attribute__((section(".sdata.0x0063252C"))) int D_0063252C = 0x00000000;
__attribute__((section(".sdata.0x00632530"))) int D_00632530 = 0x0064253E;
__attribute__((section(".sdata.0x00632534"))) int D_00632534 = 0x00000000;
__attribute__((section(".sdata.0x00632538"))) int D_00632538 = 0x00642520;
__attribute__((section(".sdata.0x0063253C"))) int D_0063253C = 0x00000000;
__attribute__((section(".sdata.0x00632540"))) int D_00632540 = 0x0000000A;
__attribute__((section(".sdata.0x00632544"))) int D_00632544 = 0x00000000;
__attribute__((section(".sdata.0x00632548"))) char D_00632548[8] = { 0 };
__attribute__((section(".sdata.0x00632550"))) int D_00632550 = 0x00000000;
__attribute__((section(".sdata.0x00632554"))) int D_00632554 = 0x00000000;
__attribute__((section(".sdata.0x00632558"))) int D_00632558 = 0x65736572;
__attribute__((section(".sdata.0x0063255C"))) int D_0063255C = 0x00000A74;
__attribute__((section(".sdata.0x00632560"))) int D_00632560 = 0x0A746968;
__attribute__((section(".sdata.0x00632564"))) int D_00632564 = 0x00000000;
__attribute__((section(".sdata.0x00632568"))) int D_00632568 = 0x65657266;
__attribute__((section(".sdata.0x0063256C"))) int D_0063256C = 0x0000000A;
__attribute__((section(".sdata.0x00632570"))) int D_00632570 = 0x6C696166;
__attribute__((section(".sdata.0x00632574"))) int D_00632574 = 0x0000000A;
__attribute__((section(".sdata.0x00632578"))) int D_00632578 = 0x253A7665;
__attribute__((section(".sdata.0x0063257C"))) int D_0063257C = 0x00000A66;
__attribute__((section(".sdata.0x00632580"))) int D_00632580 = 0x20747364;
__attribute__((section(".sdata.0x00632584"))) int D_00632584 = 0x000A7025;
__attribute__((section(".sdata.0x00632588"))) int D_00632588 = 0x70253E2D;
__attribute__((section(".sdata.0x0063258C"))) int D_0063258C = 0x0000000A;
__attribute__((section(".sdata.0x00632590"))) char D_00632590[8] = { 0 };

__attribute__((section(".rodata.0x00559B88"))) const char D_00559B88[16] = "src/jimaku.c";

__attribute__((section(".rodata.0x00559B68"))) const char D_00559B68[16] = "jimaku%02d.tm2";
__attribute__((section(".rodata.0x00559B98"))) const char D_00559B98[40] = "jimakuManager: recv command %d error.";

/* String rodata migrated from jimaku_data.c */
__attribute__((section(".rodata.0x00559B78"))) const char D_00559B78[16] = "already exist\n";
__attribute__((section(".rodata.0x00559BC0"))) const char D_00559BC0[16] = "GetWay_begin\n";
__attribute__((section(".rodata.0x00559BD0"))) const char D_00559BD0[16] = "gid t:%d m:%d\n";
__attribute__((section(".rodata.0x00559BE0"))) const char D_00559BE0[16] = "same_group\n";
__attribute__((section(".rodata.0x00559C30"))) const char D_00559C30[16] = "wp:%p %p\n";
__attribute__((section(".rodata.0x00559C40"))) const char D_00559C40[16] = "gid:%d %d\n";
__attribute__((section(".rodata.0x00559C50"))) const char D_00559C50[16] = "direction:%d\n";
__attribute__((section(".rodata.0x00559C60"))) const char D_00559C60[16] = "skip wp\n";
__attribute__((section(".rodata.0x00559C70"))) const char D_00559C70[32] = "delete guide point at avoid\n";
__attribute__((section(".rodata.0x00559C90"))) const char D_00559C90[16] = "left way %d\n";
__attribute__((section(".rodata.0x00559CA0"))) const char D_00559CA0[16] = "right way %d\n";
__attribute__((section(".rodata.0x00559CB0"))) const char D_00559CB0[16] = "up way %d\n";
__attribute__((section(".rodata.0x00559CC0"))) const char D_00559CC0[32] = "delete guide point group:%d\n";
__attribute__((section(".rodata.0x00559D08"))) const char D_00559D08[16] = "short cut 2:%p\n";
__attribute__((section(".rodata.0x00559D18"))) const char D_00559D18[24] = "delete guide point\n";
__attribute__((section(".rodata.0x00559D80"))) const char D_00559D80[16] = "goal wp1\n";
__attribute__((section(".rodata.0x00559D90"))) const char D_00559D90[16] = "bilist:%p\n";

/* String-pool rodata migrated from jimaku_data.c */
__attribute__((section(".rodata.0x00559BF0"))) const char D_00559BF0[64] = "other_group\n\000\000\000\000gid:%d = tgid:%d, mgid:%d\n\000\000\000\000\000\000!!cant reach!!\n";
__attribute__((section(".rodata.0x00559CE0"))) const char D_00559CE0[40] = "illigal way \000\000\000\000WGROUP STAT OTHER\n\000\000\000\000\000";
__attribute__((section(".rodata.0x00559D30"))) const char D_00559D30[80] = "short cut 1:%p\n\000WGROUP STAT SAME\n\000\000\000\000\000\000\000wp %p myway %p pos %p\n\000\000wgroup stat:%d\n";
