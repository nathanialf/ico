/* ios/inflate.c — __FILE__ anchor at .rodata 0x00556B00 */

const char D_00556B00[16] = "ios/inflate.c";
const char D_00556B10[32] = " incomplete literal tree\n";
const char D_00556B30[32] = " incomplete distance tree\n";
const char D_00556B50[24] = "read func not entry\n";
const char D_00556B68[48] = "iosSifAllocIopHeapDebug: %s %d not alloc\n";
const char D_00556B98[24] = "SgSndn2RemoteInit()\n";
const char D_00556BB0[32] = "allocate IOP heap memory - \n";
const char D_00556BD0[24] = "iosInitialize()\n";
const char D_00556BE8[16] = "stat mot";
const char D_00556BF8[16] = "demo mot";

/* .sdata — five 4-byte zero slots. The middle two (0x..2C, 0x..34) are
 * 4-aligned VMAs but extent == typed size == 4, so ee-gcc's forced
 * .align 3 lands them on their own VMA without shifting siblings. */
unsigned char D_00632028[4] = { 0 };
unsigned int  D_0063202C    = 0x00000000;
unsigned char D_00632030[4] = { 0 };
unsigned int  D_00632034    = 0x00000000;
unsigned char D_00632038[4] = { 0 };

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001336C0);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00133E88);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001345D0);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001348F0);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00134B50);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135468);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001354B8);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135580);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135A48);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135AD8);
