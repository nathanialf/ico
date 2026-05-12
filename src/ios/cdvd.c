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
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

__attribute__((section(".lit4.0x00630900"))) float D_00630900 = 1.23456776f;
__attribute__((section(".lit4.0x00630904"))) float D_00630904 = -100000.0f;
__attribute__((section(".lit4.0x00630908"))) float D_00630908 = 100000.0f;
__attribute__((section(".lit4.0x0063090C"))) float D_0063090C = 0.01f;
__attribute__((section(".lit4.0x00630910"))) float D_00630910 = 0.01f;
__attribute__((section(".lit4.0x00630914"))) float D_00630914 = 0.01f;
__attribute__((section(".lit4.0x00630918"))) float D_00630918 = 0.01f;
__attribute__((section(".lit4.0x0063091C"))) float D_0063091C = 0.01f;
__attribute__((section(".lit4.0x00630920"))) float D_00630920 = 0.01f;
__attribute__((section(".lit4.0x00630924"))) float D_00630924 = 0.01f;
__attribute__((section(".lit4.0x00630928"))) float D_00630928 = 0.01f;
__attribute__((section(".lit4.0x0063092C"))) float D_0063092C = 0.01f;
__attribute__((section(".sdata.0x00631A00"))) char D_00631A00[16] = { 0 };
__attribute__((section(".sdata.0x00631AB0"))) char D_00631AB0[16] = { 0 };
__attribute__((section(".sdata.0x00631AC0"))) char D_00631AC0[16] = { 0 };
__attribute__((section(".sdata.0x00631AD0"))) char D_00631AD0[16] = { 0 };
__attribute__((section(".sdata.0x00631AE0"))) int D_00631AE0 = 0;
__attribute__((section(".sdata.0x00631F50"))) int D_00631F50 = 0;
__attribute__((section(".sdata.0x00631F54"))) int D_00631F54 = 0;
__attribute__((section(".sdata.0x00631F58"))) int D_00631F58 = 0x00000001;
__attribute__((section(".sdata.0x00631F5C"))) int D_00631F5C = 0x00000000;
__attribute__((section(".sdata.0x00631F60"))) unsigned int D_00631F60 = 0x00000002;
__attribute__((section(".sdata.0x00631F64"))) int D_00631F64 = 0;
__attribute__((section(".sdata.0x00631F68"))) const char D_00631F68[8] = "0";
__attribute__((section(".sdata.0x00631F70"))) const char D_00631F70[8] = "\\%s;1";
__attribute__((section(".sdata.0x00631F78"))) const char D_00631F78[] = "handler";
__attribute__((section(".sdata.0x00631F80"))) const char D_00631F80[8] = "n=%d\n";
__attribute__((section(".sdata.0x00631F88"))) const char D_00631F88[] = "out %d\n";
__attribute__((section(".sdata.0x00631F90"))) char D_00631F90[8] = { 0 };
__attribute__((section(".sdata.0x00631F98"))) const char D_00631F98[8] = "load";
__attribute__((section(".sdata.0x00631FA0"))) int D_00631FA0 = 0;
__attribute__((section(".sdata.0x00631FA4"))) int D_00631FA4 = 0;
__attribute__((section(".sdata.0x00631FA8"))) int D_00631FA8 = 0;
__attribute__((section(".sdata.0x00631FAC"))) int D_00631FAC = 0;
__attribute__((section(".sdata.0x00631FB0"))) int D_00631FB0 = 0;
__attribute__((section(".sdata.0x00631FB4"))) int D_00631FB4 = 0;
__attribute__((section(".sdata.0x00631FB8"))) char D_00631FB8[8] = { 0 };
__attribute__((section(".sdata.0x00631FC0"))) const char D_00631FC0[8] = "stage";
__attribute__((section(".sdata.0x00631FC8"))) const char D_00631FC8[8] = "event";
__attribute__((section(".sdata.0x00631FD0"))) const char D_00631FD0[8] = "hara";
__attribute__((section(".sdata.0x00631FD8"))) const char D_00631FD8[8] = "oomori";
__attribute__((section(".sdata.0x00631FE0"))) const char D_00631FE0[] = "horagai";
__attribute__((section(".sdata.0x00631FE8"))) const char D_00631FE8[8] = "sound";
__attribute__((section(".sdata.0x00631FF0"))) const char D_00631FF0[8] = "shock";
__attribute__((section(".sdata.0x00631FF8"))) const char D_00631FF8[8] = "common";
__attribute__((section(".sdata.0x00632854"))) int D_00632854 = 0;
__attribute__((section(".sdata.0x00632858"))) int D_00632858 = 0;
__attribute__((section(".sdata.0x0063285C"))) int D_0063285C = 0;
__attribute__((section(".sdata.0x00632860"))) int D_00632860 = 0;
__attribute__((section(".sdata.0x00632864"))) int D_00632864 = 0;
__attribute__((section(".sdata.0x00632868"))) int D_00632868 = 0;
__attribute__((section(".sdata.0x0063286C"))) int D_0063286C = 0;
__attribute__((section(".sdata.0x00632870"))) char D_00632870[8] = { 0 };
__attribute__((section(".sdata.0x00632878"))) const char D_00632878[8] = "done";
__attribute__((section(".sdata.0x00632880"))) int D_00632880 = 0;
__attribute__((section(".sdata.0x00632884"))) int D_00632884 = 0;
__attribute__((section(".sdata.0x00632888"))) char D_00632888[8] = { 0 };
__attribute__((section(".sdata.0x00632890"))) const char D_00632890[8] = "%d\n";

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
