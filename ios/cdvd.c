/* cdvd.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".data.0x005524E0"))) const char D_005524E0[4] = "P*U";
__attribute__((section(".rodata.0x005567F0"))) const char D_005567F0[16] = "SCUS_971.13";
__attribute__((section(".rodata.0x00556818"))) const char D_00556818[16] = "ios/cdvd.c";
__attribute__((section(".rodata.0x005569B0"))) const char D_005569B0[16] = "skip !!!!";
__attribute__((section(".rodata.0x00556A10"))) const char D_00556A10[16] = "DFDATAS/%s";
__attribute__((section(".rodata.0x00556A20"))) const char D_00556A20[16] = "DFDATAS/DATA.DF";
__attribute__((section(".rodata.0x00556A30"))) const char D_00556A30[24] = "CD MANAGER START";
__attribute__((section(".rodata.0x00556A48"))) const char D_00556A48[40] = "iosMcManager: recv command %d error.";
__attribute__((section(".rodata.0x0062EA90"))) const char D_0062EA90[40] = "libpad: Module version mismatch ";
__attribute__((section(".rodata.0x0062EB40"))) const char D_0062EB40[8] = "ERROR";
__attribute__((section(".rodata.0x0062EB48"))) const char D_0062EB48[8] = "STABLE";
__attribute__((section(".rodata.0x0062EB50"))) const char D_0062EB50[8] = "EXECCMD";
__attribute__((section(".rodata.0x0062EB58"))) const char D_0062EB58[16] = "FINDCTP1";
__attribute__((section(".rodata.0x0062EB70"))) const char D_0062EB70[16] = "DISCONNECT";
__attribute__((section(".rodata.0x0062EB80"))) const char D_0062EB80[8] = "BUSY";
__attribute__((section(".rodata.0x0062EB88"))) const char D_0062EB88[8] = "FAILED";
__attribute__((section(".rodata.0x0062EB90"))) const char D_0062EB90[16] = "COMPLETE";
__attribute__((section(".rodata.0x0062EC40"))) const char D_0062EC40[40] = "The size of work area is too small";
__attribute__((section(".rodata.0x0062EC68"))) const char D_0062EC68[32] = "work area size is too small";
__attribute__((section(".rodata.0x0062EC88"))) const char D_0062EC88[72] = "image buffer needs to be aligned to 64byte boundary(0x%08x)";
__attribute__((section(".rodata.0x0062ECE8"))) const char D_0062ECE8[32] = "the second field is missing";
__attribute__((section(".rodata.0x0062ED18"))) const char D_0062ED18[24] = "vertical size > 2800";
__attribute__((section(".rodata.0x0062ED30"))) const char D_0062ED30[40] = "_chroma_format needs to be 1: 420";
__attribute__((section(".rodata.0x0062ED58"))) const char D_0062ED58[32] = "Unsupported profile/level";
__attribute__((section(".rodata.0x0062ED78"))) const char D_0062ED78[48] = "_sequenceScalableExtension() is not implemented";
__attribute__((section(".rodata.0x0062EDA8"))) const char D_0062EDA8[24] = "Unknown Extension";
__attribute__((section(".rodata.0x0062EDC0"))) const char D_0062EDC0[56] = "_pictureSpatialScalableExtension is not supported";
__attribute__((section(".rodata.0x0062EDF8"))) const char D_0062EDF8[56] = "_pictureTemporalScalableExtension is not supported";
__attribute__((section(".rodata.0x0062EE30"))) const char D_0062EE30[40] = "Invalid modion type -- ignored(%d)";
__attribute__((section(".rodata.0x0062EE58"))) const char D_0062EE58[32] = "(a) invalid motion_type(%d)-0";
__attribute__((section(".rodata.0x0062EE78"))) const char D_0062EE78[32] = "(b) invalid motion_type(%d)-1";
__attribute__((section(".rodata.0x0062EE98"))) const char D_0062EE98[32] = "(c) invalid motion_type(%d)-2";
__attribute__((section(".rodata.0x0062EEB8"))) const char D_0062EEB8[24] = "intra && skip MB";
__attribute__((section(".rodata.0x0062EED0"))) const char D_0062EED0[32] = "Error code detected(BDEC)";
__attribute__((section(".rodata.0x0062EEF0"))) const char D_0062EEF0[56] = "Invalid macroblock_address_increment code(0x%08x)";
__attribute__((section(".rodata.0x0062EF28"))) const char D_0062EF28[32] = "= Skip to the next picture =";
__attribute__((section(".rodata.0x0062EF48"))) const char D_0062EF48[40] = "slice_start_code(0x%08x) out of range";
__attribute__((section(".rodata.0x0062EF70"))) const char D_0062EF70[32] = "_sliceA0(): error happens";
__attribute__((section(".rodata.0x0062EF90"))) const char D_0062EF90[32] = "Too many macroblocks in picture";
__attribute__((section(".rodata.0x0062EFB0"))) const char D_0062EFB0[48] = "skiped macroblock in I picure is not allowed";
__attribute__((section(".rodata.0x0062EFE0"))) const char D_0062EFE0[32] = "Invalid macroblock_type code: 0";
__attribute__((section(".rodata.0x0062F000"))) const char D_0062F000[40] = "load_chroma_intra_quantizer_matrix == 1";
__attribute__((section(".rodata.0x0062F028"))) const char D_0062F028[48] = "load_chroma_non_intra_quantizer_matrix == 1";
__attribute__((section(".rodata.0x0062F058"))) const char D_0062F058[32] = "odd number of field pictures";
__attribute__((section(".rodata.0x0062F078"))) const char D_0062F078[32] = "unknown picture sutructure";
__attribute__((section(".rodata.0x0062F2C0"))) const char D_0062F2C0[8] = "acosf";
__attribute__((section(".rodata.0x0062F2C8"))) const char D_0062F2C8[8] = "asinf";
__attribute__((section(".rodata.0x0062F2D0"))) const char D_0062F2D0[8] = "atan2f";
__attribute__((section(".rodata.0x0062F2D8"))) const char D_0062F2D8[8] = "fmodf";
__attribute__((section(".rodata.0x0062FD80"))) const char D_0062FD80[16] = "C";
__attribute__((section(".rodata.0x0062FDB0"))) const char D_0062FDB0[24] = "0123456789abcdef";
__attribute__((section(".rodata.0x0062FDC8"))) const char D_0062FDC8[8] = "(null)";
__attribute__((section(".rodata.0x0062FDD0"))) const char D_0062FDD0[24] = "0123456789ABCDEF";
__attribute__((section(".rodata.0x0062FDE8"))) const char D_0062FDE8[40] = "bug in vfprintf: bad base";
__attribute__((section(".rodata.0x0062FFA0"))) const char D_0062FFA0[8] = "Inf";
__attribute__((section(".rodata.0x0062FFA8"))) const char D_0062FFA8[8] = "NaN";
__attribute__((section(".rodata.0x0062FFB0"))) const char D_0062FFB0[24] = "0123456789abcdef";
__attribute__((section(".rodata.0x0062FFC8"))) const char D_0062FFC8[8] = "(null)";
__attribute__((section(".rodata.0x0062FFD0"))) const char D_0062FFD0[24] = "0123456789ABCDEF";
__attribute__((section(".rodata.0x00630000"))) const char D_00630000[8] = "e";
__attribute__((section(".rodata.0x00630008"))) const char D_00630008[8] = "0";
__attribute__((section(".rodata.0x00630010"))) const char D_00630010[16] = ".";
__attribute__((section(".rodata.0x00630600"))) const char D_00630600[16] = "Infinity";
__attribute__((section(".rodata.0x00630610"))) const char D_00630610[8] = "NaN";
__attribute__((section(".rodata.0x00630618"))) const char D_00630618[8] = "0";
__attribute__((section(".rodata.0x00630690"))) const char D_00630690[8] = ".";
__attribute__((section(".rodata.0x00630698"))) const char D_00630698[8] = "C";

/* String rodata migrated from cdvd_data.c */
__attribute__((section(".rodata.0x00556800"))) const char D_00556800[24] = "wait insert ico disk\n";
__attribute__((section(".rodata.0x00556828"))) const char D_00556828[56] = "iosCdvdMgrSearchFile: warning filename length over\n";
__attribute__((section(".rodata.0x005568C0"))) const char D_005568C0[24] = "file %s not found\n";
__attribute__((section(".rodata.0x005568D8"))) const char D_005568D8[16] = "read done\n";
__attribute__((section(".rodata.0x005568E8"))) const char D_005568E8[40] = "temp_loadfunc::%s  (size:%d)(segid=%d)\n";
__attribute__((section(".rodata.0x00556910"))) const char D_00556910[16] = "try load %s\n";
__attribute__((section(".rodata.0x00556920"))) const char D_00556920[64] = "------------------------------------------------files %d -----\n";
__attribute__((section(".rodata.0x00556960"))) const char D_00556960[32] = "file id %s %d time %f read %d \n";
__attribute__((section(".rodata.0x00556980"))) const char D_00556980[24] = "inflate time %f\n";
__attribute__((section(".rodata.0x00556998"))) const char D_00556998[24] = "load time %d %f Sec\n";
__attribute__((section(".rodata.0x005569C0"))) const char D_005569C0[16] = "RING %d\n";
__attribute__((section(".rodata.0x005569D0"))) const char D_005569D0[40] = "iosCdvdHandlerReadInflate size %d\n";
__attribute__((section(".rodata.0x005569F8"))) const char D_005569F8[24] = "Decompression error\n";
__attribute__((section(".rodata.0x00556A70"))) const char D_00556A70[16] = "** %d %s %p\n";
__attribute__((section(".rodata.0x00556A80"))) const char D_00556A80[24] = "%s lsn:%d handler:%p\n";
__attribute__((section(".rodata.0x00556A98"))) const char D_00556A98[40] = "lsn %d cnt %d size %d buf %p %s\n";
__attribute__((section(".rodata.0x00556AC0"))) const char D_00556AC0[40] = "lsn %d cnt %d size %d iopbuf %p %s\n";
__attribute__((section(".rodata.0x00556AE8"))) const char D_00556AE8[24] = "cd read error %d\n";

/* Float rodata migrated from cdvd_data.c */
__attribute__((section(".rodata.0x00630890"))) const float D_00630890[2] = { 1.3105224e-06f, 1.75f };

/* String-pool rodata migrated from cdvd_data.c */
__attribute__((section(".rodata.0x00556860"))) const char D_00556860[96] = "iosCdvdMgrSearchFile: warning iosCdvdSrhBuff over\n\000\000\000\000\000\000\nCan't alloc cd stream buff %d \n\000\000\000\000\000\000\000";

#include "include_asm.h"

extern int D_0027E4C0[];
extern void func_0013A5B8(int *a0, int a1, int a2);
extern int func_0024DA80(int a0);
extern int func_0024D7B0(void);
extern void func_0024A1E0(int a0);

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001312F0);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131480);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131560);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001315A8);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131780);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131818);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00131C90);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132038);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001320E8);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001321C8);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132388);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001325D8);

void func_00132610(int a0)
{
    *(int *)(a0 + 0x4) = 2;
    func_0013A5B8(D_0027E4C0, a0, 0);
}

INCLUDE_ASM_NOP_PAD(func_0013262C);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132630);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132930);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132B90);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132DC0);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00132FF0);

void func_001331D8(int a0)
{
    int *s0 = (int *) a0;
    int v0;
    do { s0[0xC / 4] = 0; } while (0);
    v0 = func_0024DA80(a0);
    if (v0 == 0)
    {
        s0[0xC / 4] = func_0024D7B0();
    }
    return func_0024A1E0(s0[0x160 / 4]);
}

INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_00133218);
INCLUDE_ASM("asm/nonmatchings/ios/cdvd", func_001332B8);
