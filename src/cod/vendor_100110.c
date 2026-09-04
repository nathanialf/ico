#include "common.h"

#include "syscall.h"
#include "r5900.h"

typedef struct {
    unsigned char code;
    unsigned char id;
} KernEvent;
typedef struct {
    int f0;
    int widx;
    KernEvent ent[512];
} KernEventRing;

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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _EnableIntc);
int _DisableIntc(int a0) {
    __asm__ __volatile__("addiu $3, $zero, 21\n\tsyscall 0" : : : "$3", "memory");
}
int _EnableDmac(int a0) {
    __asm__ __volatile__("addiu $3, $zero, 22\n\tsyscall 0" : : : "$3", "memory");
}
int _DisableDmac(int a0) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iWakeupThread);
SYSCALL_WRAPPER(CancelWakeupThread, 53)
SYSCALL_WRAPPER(iCancelWakeupThread, -54)
SYSCALL_WRAPPER(SuspendThread, 55)
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iSuspendThread);
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iSignalSema);
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", Deci2Call);
SYSCALL_WRAPPER(PSMode, 125)
SYSCALL_WRAPPER(MachineType, 126)
SYSCALL_WRAPPER(GetMemorySize, 127)
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", setup);
extern void setup();

void InitSysCall(void) {
    int i = 0x80;
    do {
        setup(i, 0);
        i++;
    } while (i < 0x100);
}
extern void InitAlarm(void);
extern void func_00100E40(void);

void _InitSys(void) {
    InitSysCall();
    InitAlarm();
    func_00100E40();
}
extern void DIntr(void);
extern void EIntr__pn(void) __asm__("EIntr");

int DisableIntc(int a0) {
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
        EIntr__pn();
    }
    return rv;
}
extern int _EnableIntc();

int EnableIntc(int a0) {
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
        EIntr__pn();
    }
    return rv;
}
int DisableDmac(int a0) {
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
        EIntr__pn();
    }
    return rv;
}
int EnableDmac(int a0) {
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
        EIntr__pn();
    }
    return rv;
}
extern void _iEnableIntc();

void iEnableIntc(void) {
    _iEnableIntc();
    SYNC();
}
extern void _iDisableIntc();

void iDisableIntc(void) {
    _iDisableIntc();
    SYNC();
}
extern void _iEnableDmac();

void iEnableDmac(void) {
    _iEnableDmac();
    SYNC();
}
extern void _iDisableDmac();

void iDisableDmac(void) {
    _iDisableDmac();
    SYNC();
}
SYSCALL_WRAPPER(func_00100C28, 116)
SYSCALL_WRAPPER(Copy, 90)
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", kCopy);
SYSCALL_WRAPPER(GetEntryAddress, 91)
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", InitAlarm);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", func_00100D68);
extern int D_0028F4B0[];
extern int D_0063CB50[];
extern KernEventRing D_0063CB58;
extern int _iWakeupThread(void);
extern void iSignalSema(int handle);

int iWakeupThread(int id) {
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
int iRotateThreadReadyQueue(int id) {
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

int iSuspendThread(int id) {
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
int kputchar(int c) {
    unsigned int base;

    do {
        base = 0x10000000;
    } while (*(volatile unsigned int *)(base | 0xF130) & 0x8000);

    *(unsigned char *)(base | 0xF180) = c;
    return c;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", deci2Putchar);
void serialPutchar(int c) {
    if (c == 0xA) {
        kputchar(0xD);
        kputchar(0xA);
    } else {
        kputchar(c);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ftoi);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", printfloat);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _printf);
extern int _printf(int a0, void *va);

void kprintf(int a0, ...) {
    void *va = (char *)__builtin_next_arg(a0) - 0x38;
    _printf(a0, va);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", scePrintf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DIntr);
int EIntr(void) {
    int eie;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    EI();
    return eie != 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceDeci2Open);
extern void Deci2Call(int req, void *args);

void sceDeci2Close(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(2, args);
}
void sceDeci2ReqSend(int a0, signed char a1) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    Deci2Call(3, args);
}
void sceDeci2Poll(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(4, args);
}
void sceDeci2ExRecv(int a0, int a1, unsigned short a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    Deci2Call(-5, args);
}
void sceDeci2ExSend(int a0, int a1, unsigned short a2) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    Deci2Call(-6, args);
}
void sceDeci2ExReqSend(int a0, signed char a1) {
    int args[4];
    args[0] = a0;
    args[1] = a1;
    Deci2Call(-7, args);
}
void sceDeci2ExLock(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(-8, args);
}
void sceDeci2ExUnLock(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(-9, args);
}
void kputs(int a0) {
    int args[4];
    args[0] = a0;
    Deci2Call(0x10, args);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", func_00101C80);
