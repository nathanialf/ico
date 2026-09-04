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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ResetEE);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetGsCrt);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU003);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", Exit);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU005);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", LoadExecPS2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ExecPS2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU008);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU009);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", AddSbusIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RemoveSbusIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", Interrupt2Iop);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetVTLBRefillHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetVCommonHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetVInterruptHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", AddIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", AddIntcHandler2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RemoveIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", AddDmacHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", AddDmacHandler2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RemoveDmacHandler);
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetAlarm);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ReleaseAlarm);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iEnableIntc);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iDisableIntc);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iEnableDmac);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iDisableDmac);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iSetAlarm);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iReleaseAlarm);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", CreateThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DeleteThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", StartThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ExitThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ExitDeleteThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", TerminateThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iTerminateThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DisableDispatchThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", EnableDispatchThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ChangeThreadPriority);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iChangeThreadPriority);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RotateThreadReadyQueue);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iRotateThreadReadyQueue);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ReleaseWaitThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iReleaseWaitThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetThreadId);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ReferThreadStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iReferThreadStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SleepThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", WakeupThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iWakeupThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", CancelWakeupThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iCancelWakeupThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SuspendThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _iSuspendThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ResumeThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iResumeThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", JoinThread);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU060);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU061);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", EndOfHeap);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU063);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", CreateSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DeleteSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SignalSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iSignalSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", WaitSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", PollSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iPollSema);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ReferSemaStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iReferSemaStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU073);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetOsdConfigParam);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetOsdConfigParam);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetGsHParam);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetGsVParam);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetGsHParam);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetGsVParam);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU080_CreateEventFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU081_DeleteEventFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU082_SetEventFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU083_iSetEventFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU084_ClearEventFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU085_iClearEventFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU086_WaitEvnetFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU087_PollEvnetFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU088_iPollEvnetFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU089_ReferEventFlagStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU090_iReferEventFlagStatus);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU091);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", EnableIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iEnableIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DisableIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iDisableIntcHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", EnableDmacHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iEnableDmacHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DisableDmacHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iDisableDmacHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", KSeg0);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", EnableCache);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", DisableCache);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetCop0);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", FlushCache);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", CpuConfig);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iGetCop0);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iFlushCache);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iCpuConfig);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceSifStopDma);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetCPUTimerHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetCPUTimer);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetOsdConfigParam2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetOsdConfigParam2);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GsGetIMR);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iGsGetIMR);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GsPutIMR);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", iGsPutIMR);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetPgifHandler);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", SetVSyncFlag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", RFU116);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", _print);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceSifDmaStat);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", isceSifDmaStat);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceSifSetDma);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", isceSifSetDma);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceSifSetDChain);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", isceSifSetDChain);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceSifSetReg);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", sceSifGetReg);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", ExecOSD);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", Deci2Call);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", PSMode);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", MachineType);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetMemorySize);
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", func_00100C28);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", Copy);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", kCopy);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_100110", GetEntryAddress);
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
