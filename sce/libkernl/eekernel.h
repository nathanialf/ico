/*
 * sce/libkernl/eekernel.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called eekernel.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBKERNL_EEKERNEL_H
#define SCE_LIBKERNL_EEKERNEL_H

int AddDmacHandler();                                                  /* dominant spelling at 2 sites */
int AddIntcHandler(int ch, void *fn, int a2);                          /* dominant spelling at 2 sites */
int CancelWakeupThread();                                              /* dominant spelling at 1 sites */
void ChangeThreadPriority();                                           /* dominant spelling at 3 sites */
int CreateSema(int *self);                                             /* dominant spelling at 8 sites */
int DeleteSema(int sema);                                              /* dominant spelling at 7 sites */
void DeleteThread(int id);                                             /* dominant spelling at 2 sites */
int DisableDmac(int a0);                                               /* definition in sce/ */
int DisableIntc(int a0);                                               /* definition in sce/ */
int EnableDmac(int a0);                                                /* definition in sce/ */
int EnableIntc(int a0);                                                /* definition in sce/ */
void Exit(void *a0);                                                   /* dominant spelling at 1 sites */
void ExitThread();                                                     /* dominant spelling at 1 sites */
void FlushCache(int a0);                                               /* dominant spelling at 11 sites */
int GetThreadId();                                                     /* dominant spelling at 6 sites */
int PollSema(int sema);                                                /* dominant spelling at 1 sites */
int ReferSemaStatus(int sema, int *st);                                /* dominant spelling at 2 sites */
int ReferThreadStatus(int id, int *st);                                /* dominant spelling at 1 sites */
void RemoveDmacHandler();                                              /* dominant spelling at 3 sites */
void RemoveIntcHandler(int ch, int id);                                /* dominant spelling at 1 sites */
void ResumeThread();                                                   /* dominant spelling at 1 sites */
void RotateThreadReadyQueue();                                         /* dominant spelling at 2 sites */
int SetAlarm(int a0, void *a1, int a2);                                /* dominant spelling at 2 sites */
void SetVSyncFlag(void *a0, void *a1);                                 /* dominant spelling at 1 sites */
void SignalSema(int sema);                                             /* dominant spelling at 12 sites */
void SleepThread(void);                                                /* dominant spelling at 3 sites */
int StartThread(int id, void *arg);                                    /* dominant spelling at 3 sites */
void SuspendThread();                                                  /* dominant spelling at 2 sites */
void SyncDCache(void *a0, void *a1);                                   /* dominant spelling at 2 sites */
void TerminateThread();                                                /* dominant spelling at 3 sites */
int WaitSema(int sema);                                                /* dominant spelling at 9 sites */
int WakeupThread();                                                    /* dominant spelling at 2 sites */
void _iDisableDmac();                                                  /* dominant spelling at 1 sites */
void _iDisableIntc();                                                  /* dominant spelling at 1 sites */
void _iEnableDmac();                                                   /* dominant spelling at 1 sites */
void _iEnableIntc();                                                   /* dominant spelling at 1 sites */
int iSignalSema(int handle);                                           /* definition in sce/ */
int iWakeupThread(int id);                                             /* definition in sce/ */
void scePrintf(int a0, ...);                                           /* definition in sce/ */

#endif /* SCE_LIBKERNL_EEKERNEL_H */
