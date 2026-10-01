/*
 * sce/libkernl/eekernel.h
 *
 * Declarations of the EE kernel calls this tree makes, under the public name
 * of the PS2 SDK header for them (eekernel.h).  Each declaration is the
 * kernel call's public signature as the public ps2sdk headers spell it
 * (ee/kernel/include/kernel.h), in the SDK's own type names; the few marked
 * "definition in sce/" are the definitions in this tree.  Nothing here is
 * copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBKERNL_EEKERNEL_H
#define SCE_LIBKERNL_EEKERNEL_H

/* The kernel's parameter records, laid out as the public EE kernel ABI has
   them (ps2sdk ee/kernel/include/kernel.h: ee_sema_t, ee_thread_t and
   ee_thread_status_t).  The record names are the ones the SDK's public API
   is spelled with; the field names are the ones this tree's callers already
   used (ios.c's semaphore descriptors, mv_main.c's thread block).  One
   ThreadParam serves CreateThread and ReferThreadStatus, 0x30 bytes as
   libcdvd's status buffer and the ios thread object's head are; the last
   three words are written only by ReferThreadStatus. */
struct SemaParam {
    int currentCount;    /* 0x00 */
    int maxCount;        /* 0x04 */
    int initCount;       /* 0x08 */
    int numWaitThreads;  /* 0x0C */
    unsigned int attr;   /* 0x10 */
    unsigned int option; /* 0x14 */
};

struct ThreadParam {
    int status;            /* 0x00 */
    void (*entry)(void *); /* 0x04 */
    void *stack;           /* 0x08 */
    int stackSize;         /* 0x0C */
    void *gpReg;           /* 0x10 */
    int initPriority;      /* 0x14 */
    int currentPriority;   /* 0x18 */
    unsigned int attr;     /* 0x1C */
    unsigned int option;   /* 0x20 */
    int waitType;          /* 0x24 */
    int waitId;            /* 0x28 */
    int wakeupCount;       /* 0x2C */
};

/* Interrupt control (public signatures, ps2sdk kernel.h). */
int AddIntcHandler(int cause, int (*handler)(int cause), int next);
int RemoveIntcHandler(int cause, int id);
int AddDmacHandler(int channel, int (*handler)(int channel), int next);
int RemoveDmacHandler(int channel, int id);
int EnableIntc(int cause);
int DisableIntc(int cause);
int EnableDmac(int channel);
int DisableDmac(int channel);
int _iEnableIntc(int cause);
int _iDisableIntc(int cause);
int _iEnableDmac(int channel);
int _iDisableDmac(int channel);
int iEnableIntc(int cause);    /* definition in sce/ */
int iDisableIntc(int cause);   /* definition in sce/ */
int iEnableDmac(int channel);  /* definition in sce/ */
int iDisableDmac(int channel); /* definition in sce/ */

int SetAlarm(unsigned short time, void (*handler)(int id, unsigned short time, void *arg),
             void *arg);

int DIntr(void);
int EIntr(void);
/* Threads. */
int CreateThread(struct ThreadParam *param);
int DeleteThread(int id);
int StartThread(int id, void *arg);
void ExitThread(void);
void ExitDeleteThread(void);
int TerminateThread(int id);
int ChangeThreadPriority(int id, int priority);
int RotateThreadReadyQueue(int priority);
int GetThreadId(void);
int ReferThreadStatus(int id, struct ThreadParam *info);
int SleepThread(void);
int WakeupThread(int id);
int iWakeupThread(int id);
int CancelWakeupThread(int id);
int SuspendThread(int id);
int ResumeThread(int id);
/* Semaphores. */
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int SignalSema(int sema);
int iSignalSema(int sema);
int WaitSema(int sema);
int PollSema(int sema);
int ReferSemaStatus(int sema, struct SemaParam *info);
/* Miscellany. */
void Exit(int status);
void FlushCache(int operation);
void SyncDCache(void *start, void *end);
unsigned long GsGetIMR(void);
unsigned long GsPutIMR(unsigned long imr);
void SetGsCrt(short interlace, short omode, short ffmd);
void SetVSyncFlag(unsigned int *flag, unsigned long *csr);
void SetVTLBRefillHandler(int cause, void *handler);
void SetVCommonHandler(int cause, void *handler);
void VSync(void);               /* the spelling at 1 site */
long long VSync2(void);         /* definition in sce/ */
void scePrintf(char *fmt, ...); /* definition in sce/ */

#endif /* SCE_LIBKERNL_EEKERNEL_H */
