/* spiderGroupManager.c -- typed sdata / lit4 definitions for this TU.
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

extern int D_006335FC;
extern int D_00633600;
extern int D_00633604;
extern int D_00633608;
extern int D_0063360C;
extern int D_00633610;
extern int D_00633614;
extern unsigned int D_00633618;
extern int D_0063361C;
extern unsigned int D_00633620;
extern unsigned int D_00633624;
extern unsigned int D_00633628;
extern unsigned int D_0063362C;
extern int D_00633630;
extern int D_00633634;
extern int D_00633638;
extern int D_0063363C;
extern float D_00633640;
extern float D_00633644;
extern float D_00633648[2];
extern int D_00633650;
extern int D_00633654;
extern char D_00633658[8];
extern float D_00633660[2];
extern int D_00633668;
extern int D_0063366C;
extern int D_00633670;
extern int D_00633674;
extern int D_00633678;
extern int D_0063367C;
extern char D_00633680[8];
extern unsigned int D_00633688;
extern unsigned int D_0063368C;
extern int D_00633690;
extern int D_00633694;
extern int D_00633698;
extern int D_0063369C;
extern int D_006336A0;
extern int D_006336A4;
extern unsigned int D_006336A8;
extern int D_006336AC;
extern int D_006336B0;
extern int D_006336B4;
extern int D_006336B8;
extern int D_006336BC;
extern const char D_006336C0[8];
extern const char D_006336C8[8];
extern const char D_006336D0[8];
extern const char D_006336D8[];
extern int D_006336E0;
extern unsigned int D_006336E4;
extern const char D_006336E8[8];
extern const char D_006336F0[8];
extern const char D_006336F8[];
extern const char D_00633700[8];
extern int D_00633708;
extern int D_0063370C;
extern int D_00633710;
extern int D_00633714;
extern int D_00633718;
extern int D_0063371C;

__attribute__((section(".rodata.0x0061A1F8"))) const char D_0061A1F8[32] = "src/spiderGroupManager.c";

__attribute__((section(".rodata.0x0061A288"))) const char D_0061A288[16] = "COUNTER %d/%d";
__attribute__((section(".rodata.0x0061A298"))) const char D_0061A298[16] = "REMAIN %d";
__attribute__((section(".rodata.0x0061A2A8"))) const char D_0061A2A8[24] = "NO GROUP WAKEUPED";
__attribute__((section(".rodata.0x0061A340"))) const char D_0061A340[16] = "MBLUR %d";
__attribute__((section(".rodata.0x0061A350"))) const char D_0061A350[16] = "BLUR R: %d";
__attribute__((section(".rodata.0x0061A360"))) const char D_0061A360[16] = "BLUR G: %d";
__attribute__((section(".rodata.0x0061A370"))) const char D_0061A370[16] = "BLUR B: %d";
__attribute__((section(".rodata.0x0061A380"))) const char D_0061A380[16] = "BLUR BASE: %d";
__attribute__((section(".rodata.0x0061A390"))) const char D_0061A390[16] = "NOEFFECT";
__attribute__((section(".rodata.0x0061A3A0"))) const char D_0061A3A0[16] = "SBLUR+DEPTH";
__attribute__((section(".rodata.0x0061A3B0"))) const char D_0061A3B0[16] = "GLOW+DEPTH";
__attribute__((section(".rodata.0x0061A3C0"))) const char D_0061A3C0[16] = "BLSBLUR+DEPTH";
__attribute__((section(".rodata.0x0061A3D0"))) const char D_0061A3D0[16] = "NO ACTION";
__attribute__((section(".rodata.0x0061A3E0"))) const char D_0061A3E0[16] = "BLUR: %s";
__attribute__((section(".rodata.0x0061A418"))) const char D_0061A418[24] = "FEED: %s";

/* String rodata migrated from spiderGroupManager_data.c */
__attribute__((section(".rodata.0x0061A1D8"))) const char D_0061A1D8[32] = "LOCK %p for LABEL %d, ID:%d\n";
__attribute__((section(".rodata.0x0061A218"))) const char D_0061A218[88] = "No valid enemy layout data for spider.\n(Lack of enemy layout for spider revive.)\n";
__attribute__((section(".rodata.0x0061A270"))) const char D_0061A270[24] = "UNLOCK %p: (id:%d)\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", func_001EB488);
INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", func_001EB5C8);
INCLUDE_ASM("asm/nonmatchings/src/spiderGroupManager", func_001EB7C0);
