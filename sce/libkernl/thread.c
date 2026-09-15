/* Vendor SCE library member: libkernl.a(thread.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100D68..0x1010C8, 5 functions. */
#include "common.h"

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

typedef struct {
    unsigned char code;
    unsigned char id;
} KernEvent;

typedef struct {
    int f0;
    int widx;
    KernEvent ent[512];
} KernEventRing;

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/thread", topThread);
INCLUDE_ASM("asm/nonmatchings/sce/libkernl/thread", InitThread);

extern int D_0028F4B0[];
extern int D_0063CB50[];
extern KernEventRing D_0063CB58;
extern int _iWakeupThread(void);
extern void iSignalSema(int handle);

int iWakeupThread(int id)
{
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iWakeupThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (D_0028F4B0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_0063CB58.widx & 0x1FF;
    D_0063CB58.widx = i + 1;
    D_0063CB58.ent[i].code = 0;
    D_0063CB58.ent[i].id = r;
    iSignalSema(D_0063CB50[0]);
    return r;
}

int iRotateThreadReadyQueue(int id)
{
    int i;
    if ((unsigned int)id >= 0x80) {
        goto fail;
    }
    if (D_0028F4B0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_0063CB58.widx & 0x1FF;
    D_0063CB58.widx = i + 1;
    D_0063CB58.ent[i].code = 1;
    D_0063CB58.ent[i].id = id;
    iSignalSema(D_0063CB50[0]);
    return id;
}

extern int _iSuspendThread(void);

int iSuspendThread(int id)
{
    int r;
    int i;
    SYSCALL_INLINE(-0x2F, r);
    if (r != id) {
        return _iSuspendThread();
    }
    if ((unsigned int)r >= 0x100) {
        goto fail;
    }
    if (D_0028F4B0[0] != 0) {
        goto post;
    }
fail:
    return -1;
post:
    i = D_0063CB58.widx & 0x1FF;
    D_0063CB58.widx = i + 1;
    D_0063CB58.ent[i].code = 2;
    D_0063CB58.ent[i].id = r;
    iSignalSema(D_0063CB50[0]);
    return r;
}
