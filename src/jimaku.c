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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

/* D_00632514 is gp_rel-reached by a jimaku func; def lives in
 * gitignored jimaku_data.c sidecar (memory lit4_gp_rel_extern). */
extern int D_00632514;
extern int D_00632518;
extern int D_0063251C;
extern int D_00632520;
extern int D_00632524;
extern int D_00632528;
extern int D_0063252C;
extern int D_00632530;
extern int D_00632534;
extern int D_00632538;
extern int D_0063253C;
extern int D_00632540;
extern int D_00632544;
extern char D_00632548[8];
extern int D_00632550;
extern int D_00632554;
extern int D_00632558;
extern int D_0063255C;
extern int D_00632560;
extern int D_00632564;
extern int D_00632568;
extern int D_0063256C;
extern int D_00632570;
extern int D_00632574;
extern int D_00632578;
extern int D_0063257C;
extern int D_00632580;
extern int D_00632584;
extern int D_00632588;
extern int D_0063258C;
extern char D_00632590[8];

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

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_00176808);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_001769D0);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_00176AA0);
