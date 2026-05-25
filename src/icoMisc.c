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
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */

extern int D_00632CB0;
extern int D_00632F88;
extern int D_00632F8C;
extern const char D_00632F90[8];
extern const char D_00632F98[8];
extern int D_00632FA0;
extern int D_00632FA4;
extern int D_00632FA8;
extern unsigned int D_00632FAC;
extern int D_00632FB0;
extern int D_00632FB4;
extern int D_00632FB8;
extern int D_00632FBC;
extern const char D_00632FC0[];
extern const char D_00632FC8[];
extern const char D_00632FD0[];
extern const char D_00632FD8[32];
extern char D_00632FF8[8];
extern int D_00633000;
extern int D_00633004;

const char D_00616910[120] = "DISP_MEMORY_PARTITION_BAR():\n\tINVALID MEMORY FREE AREA INDICATED IN PARTITION \"%s\"\n\tMALLOCED MEMORY'S NEXT_FREE: %p\n";
const char D_006169B0[56] = "partition             total free/all      max free";
const char D_006169E8[24] = "%8s%8x: %8x/%8x %x";
const char D_00616A00[16] = "DISK ERROR";
const char D_00616A10[24] = "IOP BUFF OVER -%d bytes";
const char D_00616A28[16] = "GObj %d/%d";
const char D_00616A38[24] = "p2o_TransMicroProgram\n";
const char D_00616A50[24] = "Init Object Light\n";
const char D_00616A68[24] = "Init Packing Data\n";
const char D_00616A80[32] = "InitCharFIleManager out\n";
const char D_00616AA0[80] = "\033[33m\244\263\244\316\245\271\245\306\241\274\245\270\244\317\301\260\244\316\245\271\245\306\241\274\245\270\244\310\260\333\244\312\244\353\245\342\241\274\245\267\245\347\245\363\245\273\245\260\245\341\245\363\245\310\244\362\273\310\315\321\244\267\244\336\244\271\241\243\033[m\n";
const char D_00616AF0[24] = "iosCdvdLoadPackFile\n";
const char D_00616B08[24] = "InitWayPointSystem\n";
const char D_00616B20[16] = "MakeFogClut\n";
const char D_00616B30[24] = "InitParticleEffects\n";
const char D_00616B48[24] = "InitSceneObjects( %d )\n";
const char D_00616B60[64] = "\"\033[33m%s\033[m\"\244\254\270\306\244\326\245\321\241\274\245\306\245\243\245\257\245\353\"\033[33m%s\033[m\"\244\317\261\312\265\327\310\257\300\270\244\307\244\271\n";
const char D_00616BA0[112] = "\033[36m\306\260\272\356\244\317\244\265\244\273\244\336\244\271\244\254\302\263\244\261\244\306\244\244\244\353\244\310\245\341\245\342\245\352\244\316\n\273\361\270\273\244\362\277\251\244\244\244\304\244\257\244\267\244\336\244\271\n\245\353\241\274\245\327\244\307\244\317\244\312\244\244\244\342\244\316\244\313\245\307\241\274\245\277\244\362\275\244\300\265\244\267\244\306\244\257\244\300\244\265\244\244\033[m\n";
const char D_00616C10[24] = "Init Stage Animation\n";
const char D_00616C28[24] = "Init Object Action\n";
const char D_00616C40[24] = "load time %f sec\n";
const char D_00616C58[40] = "\244\253\244\363\244\320\244\363\245\257\245\250\245\271\245\310\245\334\245\303\245\257\245\271\245\252\241\274\245\320\241\274\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AEA68);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AF050);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AF190);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AF4A0);
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AF9C8);
