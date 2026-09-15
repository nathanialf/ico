/* Vendor SCE library member: libkernl.a(intr.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100A08..0x100D68, 13 functions. */
#include "common.h"
#include "syscall.h"
#include "r5900.h"

extern void DIntr(void);

int DisableIntc(int a0)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _DisableIntc(a0);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

extern int _EnableIntc();

int EnableIntc(int a0)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _EnableIntc(a0);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

int DisableDmac(int a0)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _DisableDmac(a0);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

int EnableDmac(int a0)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _EnableDmac(a0);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

extern void _iEnableIntc();

void iEnableIntc(void)
{
    _iEnableIntc();
    SYNC();
}

extern void _iDisableIntc();

void iDisableIntc(void)
{
    _iDisableIntc();
    SYNC();
}

extern void _iEnableDmac();

void iEnableDmac(void)
{
    _iEnableDmac();
    SYNC();
}

extern void _iDisableDmac();

void iDisableDmac(void)
{
    _iDisableDmac();
    SYNC();
}

/* intr.o's own file static setup (initsys.o holds the global of the name); the
   census names it and InitAlarm calls it. */
static void setup(void)
{
    __asm__ __volatile__("addiu $3, $zero, 116\n\tsyscall 0" : : : "$3", "memory");
}

SYSCALL_WRAPPER(Copy, 90)

int kCopy(int *dst, int *src, unsigned int n)
{
    unsigned int i;
    n >>= 2;
    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }
    return 0;
}

SYSCALL_WRAPPER(GetEntryAddress, 91)
INCLUDE_ASM("asm/nonmatchings/sce/libkernl/intr", InitAlarm);
