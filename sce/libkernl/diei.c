/* Vendor SCE library member: libkernl.a(diei.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x101A40..0x101AA0, 2 functions. */
#include "common.h"
#include "syscall.h"
#include "r5900.h"

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/diei", DIntr);

int EIntr(void)
{
    int eie;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    EI();
    return eie != 0;
}
