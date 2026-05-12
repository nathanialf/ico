/* icoMisc.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632CB0"))) int D_00632CB0 = 0;
__attribute__((section(".sdata.0x00632F88"))) int D_00632F88 = 0x80FFFFFF;
__attribute__((section(".sdata.0x00632F8C"))) int D_00632F8C = 0x00000000;
__attribute__((section(".sdata.0x00632F90"))) const char D_00632F90[8] = "e";
__attribute__((section(".sdata.0x00632F98"))) const char D_00632F98[8] = "%10s";
__attribute__((section(".sdata.0x00632FA0"))) int D_00632FA0 = 0;
__attribute__((section(".sdata.0x00632FA4"))) int D_00632FA4 = 0;
__attribute__((section(".sdata.0x00632FA8"))) int D_00632FA8 = 0;
__attribute__((section(".sdata.0x00632FAC"))) unsigned int D_00632FAC = 0x00000001;
__attribute__((section(".sdata.0x00632FB0"))) int D_00632FB0 = 0;
__attribute__((section(".sdata.0x00632FB4"))) int D_00632FB4 = 0;
__attribute__((section(".sdata.0x00632FB8"))) int D_00632FB8 = 0xFFFFFFFF;
__attribute__((section(".sdata.0x00632FBC"))) int D_00632FBC = 0x00000000;
__attribute__((section(".sdata.0x00632FC0"))) const char D_00632FC0[] = "MOTION1";
__attribute__((section(".sdata.0x00632FC8"))) const char D_00632FC8[] = "MOTION2";
__attribute__((section(".sdata.0x00632FD0"))) const char D_00632FD0[] = "MOTION3";
__attribute__((section(".sdata.0x00632FD8"))) const char D_00632FD8[32] = "%s\n";
__attribute__((section(".sdata.0x00632FF8"))) char D_00632FF8[8] = { 0 };
__attribute__((section(".sdata.0x00633000"))) int D_00633000 = 0x00808080;
__attribute__((section(".sdata.0x00633004"))) int D_00633004 = 0x00000000;

__attribute__((section(".rodata.0x006169B0"))) const char D_006169B0[56] = "partition             total free/all      max free";
__attribute__((section(".rodata.0x006169E8"))) const char D_006169E8[24] = "%8s%8x: %8x/%8x %x";
__attribute__((section(".rodata.0x00616A00"))) const char D_00616A00[16] = "DISK ERROR";
__attribute__((section(".rodata.0x00616A10"))) const char D_00616A10[24] = "IOP BUFF OVER -%d bytes";
__attribute__((section(".rodata.0x00616A28"))) const char D_00616A28[16] = "GObj %d/%d";

/* String rodata migrated from icoMisc_data.c */
__attribute__((section(".rodata.0x00616910"))) const char D_00616910[120] = "DISP_MEMORY_PARTITION_BAR():\n\tINVALID MEMORY FREE AREA INDICATED IN PARTITION \"%s\"\n\tMALLOCED MEMORY'S NEXT_FREE: %p\n";
__attribute__((section(".rodata.0x00616A38"))) const char D_00616A38[24] = "p2o_TransMicroProgram\n";
__attribute__((section(".rodata.0x00616A50"))) const char D_00616A50[24] = "Init Object Light\n";
__attribute__((section(".rodata.0x00616A68"))) const char D_00616A68[24] = "Init Packing Data\n";
__attribute__((section(".rodata.0x00616A80"))) const char D_00616A80[32] = "InitCharFIleManager out\n";
__attribute__((section(".rodata.0x00616AF0"))) const char D_00616AF0[24] = "iosCdvdLoadPackFile\n";
__attribute__((section(".rodata.0x00616B08"))) const char D_00616B08[24] = "InitWayPointSystem\n";
__attribute__((section(".rodata.0x00616B20"))) const char D_00616B20[16] = "MakeFogClut\n";
__attribute__((section(".rodata.0x00616B30"))) const char D_00616B30[24] = "InitParticleEffects\n";
__attribute__((section(".rodata.0x00616B48"))) const char D_00616B48[24] = "InitSceneObjects( %d )\n";
__attribute__((section(".rodata.0x00616C10"))) const char D_00616C10[24] = "Init Stage Animation\n";
__attribute__((section(".rodata.0x00616C28"))) const char D_00616C28[24] = "Init Object Action\n";
__attribute__((section(".rodata.0x00616C40"))) const char D_00616C40[24] = "load time %f sec\n";
