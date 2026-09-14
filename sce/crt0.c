/* crt0: the SDK start-up module.  MAIN.MAP puts crt0.o(.text) at the head
 * of .text and SRCFILE.TXT attributes these instructions to
 * /usr/local/sce/ee/lib/crt0.s.  One object, so the partition is trivial;
 * the January link built a 0xC8-byte crt0 against this run of 0x110, so no
 * size tiling is claimed. */
#include "common.h"

/* The eight zero bytes the listing labels <_start-0x8>: crt0.s's pre-entry pad,
 * not a function.  Emitted here as data so the ROM run starts at the same
 * address and the dashboard stops counting a function that never existed. */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        ".global D_00100000\n"
        "D_00100000:\n"
        "    .word 0, 0\n"
        "    .set reorder\n"
        "    .set at\n");

INCLUDE_ASM("asm/nonmatchings/sce/crt0", _start);
INCLUDE_ASM("asm/nonmatchings/sce/crt0", _exit);
INCLUDE_ASM("asm/nonmatchings/sce/crt0", _root);
