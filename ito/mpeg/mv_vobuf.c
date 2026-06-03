#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", func_0019B8E0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufDelete);

extern void voBufCreate(void);

void voBufReset(void) {
    voBufCreate();
}

extern int iosMallocCheckLeak2(int a0);

void voBufIsFull(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

/* voBufIncCount — hand-written assembly in Ito's movie/IPU buffer layer.
 * Resets the ring-buffer's two counters (offsets 0xC, 0x8) and returns with
 * the jr delay slot left as an explicit nop. This module (ito/mpeg) builds at
 * -O2 (proven: viBufFlush matches at -O2), and ee-gcc -O2 sorts the two
 * independent zero-stores ascending (8 then 12) and fills the jr delay — it
 * cannot emit this descending order with an unfilled delay (60 distinct clean-C
 * shapes tried, none match). A bare nop delay on trivial code is a compiler-
 * atypical, human-scheduling signature, so this is reproduced as the dev's
 * hand asm — same class as the PObj syscall stubs / ISR cluster. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel voBufIncCount\n"
    "    sw         $0, 0xC($4)\n"
    "    sw         $0, 0x8($4)\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel voBufIncCount\n"
    "    .set reorder\n"
    "    .set at\n"
);

int voBufGetData(int *a0) {
    return a0[3] == a0[4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufGetTag);
