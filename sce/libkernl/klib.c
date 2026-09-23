/* Vendor SCE library member: libkernl.a(klib.o).  MAIN.MAP places this member at
 * the same address as the shipped ELF and its size tiles the run exactly, every
 * boundary a retail function start; VMA 0x100110..0x100990, 136 functions. */
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

SYSCALL_WRAPPER(ResetEE, 1)
SYSCALL_WRAPPER(SetGsCrt, 2)
SYSCALL_WRAPPER(RFU003, 3)
SYSCALL_WRAPPER(Exit, 4)
SYSCALL_WRAPPER(RFU005, 5)
SYSCALL_WRAPPER(LoadExecPS2, 6)
SYSCALL_WRAPPER(ExecPS2, 7)
SYSCALL_WRAPPER(RFU008, 8)
SYSCALL_WRAPPER(RFU009, 9)
SYSCALL_WRAPPER(AddSbusIntcHandler, 10)
SYSCALL_WRAPPER(RemoveSbusIntcHandler, 11)
SYSCALL_WRAPPER(Interrupt2Iop, 12)
SYSCALL_WRAPPER(SetVTLBRefillHandler, 13)
SYSCALL_WRAPPER(SetVCommonHandler, 14)
SYSCALL_WRAPPER(SetVInterruptHandler, 15)
SYSCALL_WRAPPER(AddIntcHandler, 16)
SYSCALL_WRAPPER(AddIntcHandler2, 16)
SYSCALL_WRAPPER(RemoveIntcHandler, 17)
SYSCALL_WRAPPER(AddDmacHandler, 18)
SYSCALL_WRAPPER(AddDmacHandler2, 18)
SYSCALL_WRAPPER(RemoveDmacHandler, 19)

int _EnableIntc()
{
    __asm__ __volatile__("addiu $3, $zero, 20\n\tsyscall 0" : : : "$3", "memory");
}

int _DisableIntc(int a0)
{
    __asm__ __volatile__("addiu $3, $zero, 21\n\tsyscall 0" : : : "$3", "memory");
}

int _EnableDmac(int a0)
{
    __asm__ __volatile__("addiu $3, $zero, 22\n\tsyscall 0" : : : "$3", "memory");
}

int _DisableDmac(int a0)
{
    __asm__ __volatile__("addiu $3, $zero, 23\n\tsyscall 0" : : : "$3", "memory");
}

SYSCALL_WRAPPER(SetAlarm, 252)
SYSCALL_WRAPPER(ReleaseAlarm, 253)
SYSCALL_WRAPPER(_iEnableIntc, -26)
SYSCALL_WRAPPER(_iDisableIntc, -27)
SYSCALL_WRAPPER(_iEnableDmac, -28)
SYSCALL_WRAPPER(_iDisableDmac, -29)
SYSCALL_WRAPPER(iSetAlarm, -254)
SYSCALL_WRAPPER(iReleaseAlarm, -255)
SYSCALL_WRAPPER(CreateThread, 32)
SYSCALL_WRAPPER(DeleteThread, 33)
SYSCALL_WRAPPER(StartThread, 34)
SYSCALL_WRAPPER(ExitThread, 35)
SYSCALL_WRAPPER(ExitDeleteThread, 36)
SYSCALL_WRAPPER(TerminateThread, 37)
SYSCALL_WRAPPER(iTerminateThread, -38)
SYSCALL_WRAPPER(DisableDispatchThread, 39)
SYSCALL_WRAPPER(EnableDispatchThread, 40)
SYSCALL_WRAPPER(ChangeThreadPriority, 41)
SYSCALL_WRAPPER(iChangeThreadPriority, -42)
SYSCALL_WRAPPER(RotateThreadReadyQueue, 43)
SYSCALL_WRAPPER(_iRotateThreadReadyQueue, -44)
SYSCALL_WRAPPER(ReleaseWaitThread, 45)
SYSCALL_WRAPPER(iReleaseWaitThread, -46)
SYSCALL_WRAPPER(GetThreadId, 47)
SYSCALL_WRAPPER(ReferThreadStatus, 48)
SYSCALL_WRAPPER(iReferThreadStatus, -49)
SYSCALL_WRAPPER(SleepThread, 50)
SYSCALL_WRAPPER(WakeupThread, 51)

int _iWakeupThread(void)
{
    __asm__ __volatile__("addiu $3, $zero, -52\n\tsyscall 0" : : : "$3", "memory");
}

SYSCALL_WRAPPER(CancelWakeupThread, 53)
SYSCALL_WRAPPER(iCancelWakeupThread, -54)
SYSCALL_WRAPPER(SuspendThread, 55)

int _iSuspendThread(void)
{
    __asm__ __volatile__("addiu $3, $zero, -56\n\tsyscall 0" : : : "$3", "memory");
}

SYSCALL_WRAPPER(ResumeThread, 57)
SYSCALL_WRAPPER(iResumeThread, -58)
SYSCALL_WRAPPER(JoinThread, 59)
SYSCALL_WRAPPER(RFU060, 60)
SYSCALL_WRAPPER(RFU061, 61)
SYSCALL_WRAPPER(EndOfHeap, 62)
SYSCALL_WRAPPER(RFU063, 63)
SYSCALL_WRAPPER(CreateSema, 64)
SYSCALL_WRAPPER(DeleteSema, 65)
SYSCALL_WRAPPER(SignalSema, 66)

int iSignalSema(int handle)
{
    __asm__ __volatile__("addiu $3, $zero, -67\n\tsyscall 0" : : : "$3", "memory");
}

SYSCALL_WRAPPER(WaitSema, 68)
SYSCALL_WRAPPER(PollSema, 69)
SYSCALL_WRAPPER(iPollSema, -70)
SYSCALL_WRAPPER(ReferSemaStatus, 71)
SYSCALL_WRAPPER(iReferSemaStatus, -72)
SYSCALL_WRAPPER(RFU073, 73)
SYSCALL_WRAPPER(SetOsdConfigParam, 74)
SYSCALL_WRAPPER(GetOsdConfigParam, 75)
SYSCALL_WRAPPER(GetGsHParam, 76)
SYSCALL_WRAPPER(GetGsVParam, 77)
SYSCALL_WRAPPER(SetGsHParam, 78)
SYSCALL_WRAPPER(SetGsVParam, 79)
SYSCALL_WRAPPER(RFU080_CreateEventFlag, 80)
SYSCALL_WRAPPER(RFU081_DeleteEventFlag, 81)
SYSCALL_WRAPPER(RFU082_SetEventFlag, 82)
SYSCALL_WRAPPER(RFU083_iSetEventFlag, -83)
SYSCALL_WRAPPER(RFU084_ClearEventFlag, 84)
SYSCALL_WRAPPER(RFU085_iClearEventFlag, -85)
SYSCALL_WRAPPER(RFU086_WaitEvnetFlag, 86)
SYSCALL_WRAPPER(RFU087_PollEvnetFlag, 87)
SYSCALL_WRAPPER(RFU088_iPollEvnetFlag, -88)
SYSCALL_WRAPPER(RFU089_ReferEventFlagStatus, 89)
SYSCALL_WRAPPER(RFU090_iReferEventFlagStatus, -90)
SYSCALL_WRAPPER(RFU091, 91)
SYSCALL_WRAPPER(EnableIntcHandler, 92)
SYSCALL_WRAPPER(iEnableIntcHandler, -92)
SYSCALL_WRAPPER(DisableIntcHandler, 93)
SYSCALL_WRAPPER(iDisableIntcHandler, -93)
SYSCALL_WRAPPER(EnableDmacHandler, 94)
SYSCALL_WRAPPER(iEnableDmacHandler, -94)
SYSCALL_WRAPPER(DisableDmacHandler, 95)
SYSCALL_WRAPPER(iDisableDmacHandler, -95)
SYSCALL_WRAPPER(KSeg0, 96)
SYSCALL_WRAPPER(EnableCache, 97)
SYSCALL_WRAPPER(DisableCache, 98)
SYSCALL_WRAPPER(GetCop0, 99)
SYSCALL_WRAPPER(FlushCache, 100)
SYSCALL_WRAPPER(CpuConfig, 102)
SYSCALL_WRAPPER(iGetCop0, -103)
SYSCALL_WRAPPER(iFlushCache, -104)
SYSCALL_WRAPPER(iCpuConfig, -106)
SYSCALL_WRAPPER(sceSifStopDma, 107)
SYSCALL_WRAPPER(SetCPUTimerHandler, 108)
SYSCALL_WRAPPER(SetCPUTimer, 109)
SYSCALL_WRAPPER(SetOsdConfigParam2, 110)
SYSCALL_WRAPPER(GetOsdConfigParam2, 111)
SYSCALL_WRAPPER(GsGetIMR, 112)
SYSCALL_WRAPPER(iGsGetIMR, -112)
SYSCALL_WRAPPER(GsPutIMR, 113)
SYSCALL_WRAPPER(iGsPutIMR, -113)
SYSCALL_WRAPPER(SetPgifHandler, 114)
SYSCALL_WRAPPER(SetVSyncFlag, 115)
SYSCALL_WRAPPER(RFU116, 116)
SYSCALL_WRAPPER(_print, 117)
SYSCALL_WRAPPER(sceSifDmaStat, 118)
SYSCALL_WRAPPER(isceSifDmaStat, -118)
SYSCALL_WRAPPER(sceSifSetDma, 119)
SYSCALL_WRAPPER(isceSifSetDma, -119)
SYSCALL_WRAPPER(sceSifSetDChain, 120)
SYSCALL_WRAPPER(isceSifSetDChain, -120)
SYSCALL_WRAPPER(sceSifSetReg, 121)
SYSCALL_WRAPPER(sceSifGetReg, 122)
SYSCALL_WRAPPER(ExecOSD, 123)

void Deci2Call(int req, void *args)
{
    __asm__ __volatile__("addiu $3, $zero, 124\n\tsyscall 0" : : : "$3", "memory");
}

SYSCALL_WRAPPER(PSMode, 125)
SYSCALL_WRAPPER(MachineType, 126)
SYSCALL_WRAPPER(GetMemorySize, 127)
