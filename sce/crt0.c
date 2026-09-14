/* crt0: the SDK start-up module.  MAIN.MAP puts crt0.o(.text) at the head
 * of .text and SRCFILE.TXT attributes these instructions to
 * /usr/local/sce/ee/lib/crt0.s.  One object, so the partition is trivial;
 * the January link built a 0xC8-byte crt0 against this run of 0x110, so no
 * size tiling is claimed. */
#include "common.h"

INCLUDE_ASM("asm/nonmatchings/sce/crt0", func_00100000);
INCLUDE_ASM("asm/nonmatchings/sce/crt0", _start);
INCLUDE_ASM("asm/nonmatchings/sce/crt0", _exit);
INCLUDE_ASM("asm/nonmatchings/sce/crt0", _root);
