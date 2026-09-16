/* libgraph.a member graph002.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

/* The VIF1 reset packet sceGsResetPath writes to the PATH2 FIFO at
   0x10005000: STCYCL cl=4 wl=4, STMASK 0, NOP, STMOD 0, then MSKPATH3 0,
   BASE 0, OFFSET 0, ITOP 0.  VIF codes are register fields, so they are
   spelled in hex.  16-aligned because the shipped code moves the two
   quadwords with lq/sq. */
static unsigned int sceGsResetPathPacket[8] __attribute__((aligned(16))) = {
    0x01000404, 0x20000000, 0x00000000, 0x05000000, 0x06000000, 0x03000000, 0x02000000, 0x04000000};

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceGsResetPath\n"
        "    .type sceGsResetPath, @function\n"
        "    .align 3\n"
        "sceGsResetPath:\n"
        "    lui   $2, 0x1000\n"
        "    addiu $7, $0, 0x1\n"
        "    ori   $2, $2, 0x3C10\n"
        "    lui   $3, 0x1000\n"
        "    sw    $7, 0x0($2)\n"
        "    ori   $3, $3, 0x3C20\n"
        "    addiu $2, $0, 0x2\n"
        "    daddu $4, $0, $0\n"
        "    sw    $2, 0x0($3)\n"
        "    sync\n"
        "    cfc2.ni $4, $vi28\n"
        "    ori   $4, $4, 0x200\n"
        "    ctc2.ni $4, $vi28\n"
        "    sync.p\n"
        "    lui   $5, %hi(sceGsResetPathPacket)\n"
        "    lui   $6, 0x1000\n"
        "    addiu $5, $5, %lo(sceGsResetPathPacket)\n"
        "    ori   $6, $6, 0x5000\n"
        "    lq    $4, 0x0($5)\n"
        "    lui   $3, 0x1000\n"
        "    ori   $3, $3, 0x3000\n"
        "    sq    $4, 0x0($6)\n"
        "    lq    $2, 0x10($5)\n"
        "    sq    $2, 0x0($6)\n"
        "    jr    $31\n"
        "    sw    $7, 0x0($3)\n"
        "    .size sceGsResetPath, . - sceGsResetPath\n"
        "    .set reorder\n"
        "    .set at\n");
