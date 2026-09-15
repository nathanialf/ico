/* Vendor SCE library member: libkernl.a(diei.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x101A40..0x101AA0, 2 functions. */
#include "common.h"

/* R5900 opcodes with no C spelling.  This member's uses stand for a
   Sony-internal header this tree cannot name: MAIN.MAP attests archives and
   their members, never a header, so the definition is kept per member. */
#define EI() __asm__ __volatile__(".word 0x42000038" : : : "memory")
/* COP0 Status ($12), bit 16 = interrupts enabled.  Taken as an lvalue: the
   wrappers mask the word in place, and a value-returning form puts the mask
   in a different register than the read. */
#define MFC0_STATUS(dst) __asm__ __volatile__("mfc0 %0, $12" : "=r"(dst))
#define COP0_STATUS_EIE 0x10000

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/diei", DIntr);

int EIntr(void)
{
    int eie;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    EI();
    return eie != 0;
}
