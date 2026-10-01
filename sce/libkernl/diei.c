/* libkernl.a(diei.o) */
#include <eekernel.h>

/* R5900 opcodes with no C spelling.  Defined in this member. */
#define EI() __asm__ __volatile__(".word 0x42000038" : : : "memory")
/* COP0 Status ($12), bit 16 = interrupts enabled.  Taken as an lvalue: the
   wrappers mask the word in place. */
#define MFC0_STATUS(dst) __asm__ __volatile__("mfc0 %0, $12" : "=r"(dst))
#define COP0_STATUS_EIE 0x10000
#define DI() __asm__ __volatile__(".word 0x42000039" : : : "memory")
#define SYNCP() __asm__ __volatile__("sync.p" : : : "memory")

int DIntr(void)
{
    int eie;
    int st;

    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        do {
            DI();
            SYNCP();
            MFC0_STATUS(st);
            st &= COP0_STATUS_EIE;
        } while (st);
    }
    return eie != 0;
}

int EIntr(void)
{
    int eie;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    EI();
    return eie != 0;
}
