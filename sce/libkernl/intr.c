/* Vendor SCE library member: libkernl.a(intr.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100A08..0x100D68, 13 functions. */
#include "common.h"
#include <eekernel.h>

/* EE syscall leaf wrappers.  This member's uses stand for a Sony-internal
   header this tree cannot name: MAIN.MAP attests archives and their members,
   never a header, so the definitions are kept per member.  Body is the
   four-instruction leaf `addiu $3,$zero,NUM; syscall 0; jr $31; nop`, the
   last two supplied by gcc's epilogue. */
#define SYSCALL_WRAPPER(name, num)                                                                 \
    void name(void)                                                                                \
    {                                                                                              \
        __asm__ __volatile__("addiu $3, $zero, " #num "\n\tsyscall 0" : : : "$3", "memory");       \
    }
/* The same leaf issued INLINE, for the members that act on its result.
   `dst` is bound to $v0 because that is where the kernel ABI leaves the
   result; a plain "=r" output would let gcc pick a register the kernel
   never writes.  Operand binding, not a scheduling pin. */
#define SYSCALL_INLINE(num, dst)                                                                   \
    do {                                                                                           \
        register int __sc_ret __asm__("$2");                                                       \
        __asm__ __volatile__("addiu $3, $zero, " #num "\n\tsyscall 0"                              \
                             : "=r"(__sc_ret)                                                      \
                             :                                                                     \
                             : "$3", "memory");                                                    \
        (dst) = __sc_ret;                                                                          \
    } while (0)
/* R5900 opcodes with no C spelling.  This member's uses stand for a
   Sony-internal header this tree cannot name: MAIN.MAP attests archives and
   their members, never a header, so the definition is kept per member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")
/* COP0 Status ($12), bit 16 = interrupts enabled.  Taken as an lvalue: the
   wrappers mask the word in place, and a value-returning form puts the mask
   in a different register than the read. */
#define MFC0_STATUS(dst) __asm__ __volatile__("mfc0 %0, $12" : "=r"(dst))
#define COP0_STATUS_EIE 0x10000

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

void iEnableIntc(void)
{
    _iEnableIntc();
    SYNC();
}

void iDisableIntc(void)
{
    _iDisableIntc();
    SYNC();
}

void iEnableDmac(void)
{
    _iEnableDmac();
    SYNC();
}

void iDisableDmac(void)
{
    _iDisableDmac();
    SYNC();
}

/* intr.o's own file static setup (initsys.o holds the global of the name); the
   census names it and InitAlarm calls it. */
static void setup(int num, int addr)
{
    __asm__ __volatile__("addiu $3, $zero, 116\n\tsyscall 0" : : : "$3", "memory");
}

/* syscall 90 is Copy(dst, src, len); the leaf ignores its arguments, the
   kernel reads them out of $a0..$a2. */
void Copy(char *dst, char *src, int len)
{
    __asm__ __volatile__("addiu $3, $zero, 90\n\tsyscall 0" : : : "$3", "memory");
}

int kCopy(int *dst, int *src, unsigned int n)
{
    unsigned int i;
    n >>= 2;
    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }
    return 0;
}

/* The same leaf as SYSCALL_WRAPPER, spelled out because this one takes an
   argument and returns the kernel's $v0: syscall 91 is GetEntryAddress(num). */
int GetEntryAddress(int num)
{
    __asm__ __volatile__("addiu $3, $zero, 91\n\tsyscall 0" : : : "$3", "memory");
}

extern int D_0028F470[];
extern char D_0028ED10[];
extern char D_0028F450[];

void InitAlarm(void)
{
    unsigned int i;

    if (*(volatile int *)0x10001810 & 0x100)
        return;
    setup(D_0028F470[0], D_0028F470[1]);
    Copy((char *)0x80076000, D_0028ED10, 0x740);
    Copy((char *)0x82000, D_0028F450, 0x20);
    FlushCache(0);
    FlushCache(2);
    setup(D_0028F470[2], D_0028F470[3]);
    for (i = 2; i < 8; i++) {
        setup(D_0028F470[i * 2], GetEntryAddress(D_0028F470[i * 2]));
    }
}
