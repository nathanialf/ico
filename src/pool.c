/* pool.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00553DE0"))) const char D_00553DE0[16] = "src/pool.c";

__attribute__((section(".rodata.0x00553E90"))) const char D_00553E90[32] = "display object = %d";
__attribute__((section(".rodata.0x00553F10"))) const char D_00553F10[24] = "cdrom0:\\IOPRP224.IMG;1";
__attribute__((section(".rodata.0x00553F40"))) const char D_00553F40[24] = "cdrom0:\\SIO2MAN.IRX;1";
__attribute__((section(".rodata.0x00553F58"))) const char D_00553F58[24] = "cdrom0:\\PADMAN.IRX;1";
__attribute__((section(".rodata.0x00553F70"))) const char D_00553F70[24] = "cdrom0:\\MCMAN.IRX;1";
__attribute__((section(".rodata.0x00553F88"))) const char D_00553F88[24] = "cdrom0:\\MCSERV.IRX;1";
__attribute__((section(".rodata.0x00553FA0"))) const char D_00553FA0[24] = "cdrom0:\\LIBSD.IRX;1";
__attribute__((section(".rodata.0x00553FB8"))) const char D_00553FB8[24] = "cdrom0:\\SNDN2DRV.IRX;1";

/* String rodata migrated from pool_data.c */
__attribute__((section(".rodata.0x00553E00"))) const char D_00553E00[40] = "Quaternion stack not initialized.\n";
__attribute__((section(".rodata.0x00553E28"))) const char D_00553E28[32] = "Quaternion stack overflow!!\n";
__attribute__((section(".rodata.0x00553E48"))) const char D_00553E48[40] = "Quaternion stack underflow!!\n";
__attribute__((section(".rodata.0x00553EB0"))) const char D_00553EB0[48] = "-------------------------------- read from CD\n";
__attribute__((section(".rodata.0x00553EE0"))) const char D_00553EE0[24] = "initialize CD device.\n";
__attribute__((section(".rodata.0x00553EF8"))) const char D_00553EF8[24] = "load default module.\n";
__attribute__((section(".rodata.0x00553F28"))) const char D_00553F28[24] = "loading iop modules.\n";

/* Float rodata migrated from pool_data.c */
__attribute__((section(".rodata.0x00553DF0"))) const float D_00553DF0[4] = { 2048.0f, 2048.0f, 0.0f, 0.0f };

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010B2D0);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010B770);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010C0F0);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010C5C0);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010C6C0);
