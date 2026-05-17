/* memory.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00556F70"))) const char D_00556F70[16] = "<PARTITION>____";
__attribute__((section(".rodata.0x00556F80"))) const char D_00556F80[16] = "<FREE AREA>____";
__attribute__((section(".rodata.0x00557060"))) const char D_00557060[16] = " free memory   ";
__attribute__((section(".rodata.0x00557088"))) const char D_00557088[16] = " del partition ";
__attribute__((section(".rodata.0x005570E0"))) const char D_005570E0[16] = "ios/memory.c";
__attribute__((section(".rodata.0x00557220"))) const char D_00557220[16] = "<ALLOC>________";
__attribute__((section(".rodata.0x005572A8"))) const char D_005572A8[16] = "align%05d";
__attribute__((section(".rodata.0x005572D8"))) const char D_005572D8[16] = "mem:free ";
__attribute__((section(".rodata.0x00557360"))) const char D_00557360[16] = " free memory0  ";
__attribute__((section(".rodata.0x00557390"))) const char D_00557390[16] = " free memory1  ";
__attribute__((section(".rodata.0x005573A0"))) const char D_005573A0[16] = " free memory2  ";
__attribute__((section(".rodata.0x005573F0"))) const char D_005573F0[16] = "mem:addr:$%08x ";
__attribute__((section(".rodata.0x00557400"))) const char D_00557400[16] = "FREEAREA ";
__attribute__((section(".rodata.0x00557410"))) const char D_00557410[16] = "DELETED_MEMORY ";
__attribute__((section(".rodata.0x00557448"))) const char D_00557448[16] = "siz:$%5x ";

/* String rodata migrated from memory_data.c */
__attribute__((section(".rodata.0x00556F50"))) const char D_00556F50[32] = "mem:partition size too small\n";
__attribute__((section(".rodata.0x00556F90"))) const char D_00556F90[40] = "mem:init partition 0x%08x - 0x%08x\n";
__attribute__((section(".rodata.0x00556FB8"))) const char D_00556FB8[32] = "mem:null partition pointer\n";
__attribute__((section(".rodata.0x00556FD8"))) const char D_00556FD8[32] = "mem:illegal partition pointer\n";
__attribute__((section(".rodata.0x00556FF8"))) const char D_00556FF8[40] = "mem: memory lack %dqw > parent:%dqw\n";
__attribute__((section(".rodata.0x00557020"))) const char D_00557020[32] = "mem:set partition 0x%08x\n";
__attribute__((section(".rodata.0x00557040"))) const char D_00557040[32] = "mem:fail init partition\n";
__attribute__((section(".rodata.0x00557070"))) const char D_00557070[24] = "mem:not last partition\n";
__attribute__((section(".rodata.0x00557098"))) const char D_00557098[72] = "MALLOC: REENTER FOR PARTITION \"%s\" SIZE %d\nBEFORE FILE %s LINE %d";
__attribute__((section(".rodata.0x005570F0"))) const char D_005570F0[48] = "IOSMALLOC():\nNULL PARTITION POINTER AT MALLOC\n";
__attribute__((section(".rodata.0x00557120"))) const char D_00557120[32] = "mem:illegal free area pointer\n";
__attribute__((section(".rodata.0x00557140"))) const char D_00557140[40] = "mem: prev block, %08x called at %s\n";
__attribute__((section(".rodata.0x00557168"))) const char D_00557168[24] = "mem:prev magic %s\n";
__attribute__((section(".rodata.0x00557180"))) const char D_00557180[40] = "mem:cur block, %08x called at %s\n";
__attribute__((section(".rodata.0x005571A8"))) const char D_005571A8[24] = "mem:cur magic %s\n";
__attribute__((section(".rodata.0x005571C0"))) const char D_005571C0[40] = "mem: next block, %08x called at %s\n";
__attribute__((section(".rodata.0x005571E8"))) const char D_005571E8[24] = "mem:next magic %s\n";
__attribute__((section(".rodata.0x00557200"))) const char D_00557200[32] = "mem:called by %s of line %d\n";
__attribute__((section(".rodata.0x00557230"))) const char D_00557230[16] = "cur: %8p %s\n";
__attribute__((section(".rodata.0x00557240"))) const char D_00557240[16] = "next:%8p %s\n";
__attribute__((section(".rodata.0x00557250"))) const char D_00557250[24] = "mem:no memory for %d\n";
__attribute__((section(".rodata.0x00557268"))) const char D_00557268[64] = "MALLOC: NO EMEMORY FOR PARTITION \"%s\"\nSIZE %d BYTES (%1.1fM)\n";
__attribute__((section(".rodata.0x005572B8"))) const char D_005572B8[32] = "IOSFILLFREE %s(%d) %p - %p\n";
__attribute__((section(".rodata.0x005572E8"))) const char D_005572E8[24] = "null memory pointer\n";
__attribute__((section(".rodata.0x00557300"))) const char D_00557300[32] = "IOSFREE(): NULL MEMORY POINTER\n";
__attribute__((section(".rodata.0x00557320"))) const char D_00557320[64] = "IOSFREE():\n\tPREV MAGIC: %s\n\t CUR MAGIC: %s\n\tNEXT MAGIC: %s\n";
__attribute__((section(".rodata.0x00557370"))) const char D_00557370[32] = "IOSFREE(): MEMORY LINK MISS\n";
__attribute__((section(".rodata.0x005573B0"))) const char D_005573B0[24] = "IOSFREE(): ALLOC NULL\n";
__attribute__((section(".rodata.0x005573C8"))) const char D_005573C8[16] = "IOSFREE(): ??\n";
__attribute__((section(".rodata.0x005573D8"))) const char D_005573D8[24] = "magic broken :%p\n";
__attribute__((section(".rodata.0x00557420"))) const char D_00557420[40] = "!!! unrecognized memory block !!!\n";
__attribute__((section(".rodata.0x00557458"))) const char D_00557458[24] = "<<< check leak2 >>> %p\n";
__attribute__((section(".rodata.0x00557470"))) const char D_00557470[16] = "%p:ALLOC %s\n";
__attribute__((section(".rodata.0x00557480"))) const char D_00557480[16] = "%p:FREEAREA\n";
__attribute__((section(".rodata.0x00557490"))) const char D_00557490[24] = "%p:DELETED_MEMORY\n";
__attribute__((section(".rodata.0x005574A8"))) const char D_005574A8[40] = "%p:!!! unrecognized block!!!:%s\n";
__attribute__((section(".rodata.0x005574D0"))) const char D_005574D0[48] = "IOSREALLOC():\nNULL MEMORY POINTER AT MALLOC\n";
__attribute__((section(".rodata.0x00557500"))) const char D_00557500[32] = "mem:realloc; not support yet\n";
__attribute__((section(".rodata.0x00557520"))) const char D_00557520[32] = "mem:realloc; not enough memory\n";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138E30);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_001392A8);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_001394F0);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139598);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139A50);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139C30);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139D78);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139FE8);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A0F8);
