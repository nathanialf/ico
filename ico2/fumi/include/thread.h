/*
 * ico2/fumi/include/thread.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what thread.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef THREAD_H
#define THREAD_H

extern int iosGetIOSThreadFromId(unsigned int a0);
extern int iosSemaCreate(int *self, int a1, int a2, int a3);
extern int iosSemaDelete(int *self);
extern int iosSemaReferStatus(int *self);
extern int iosSemaSignal(int *self);
extern int iosSemaWait(int *self);
extern int iosThreadCancelWakeup(int *self);
extern void iosThreadCreate(void *th, int no, void (*func)(), int arg, void *stack, long stackSize, int pri);
extern void iosThreadCreateS(unsigned int *th, int no, void (*func)(), int arg, void *heap, long stackSize, int pri);
extern void iosThreadDestroy(int a0);
extern int iosThreadGetPri(int *a0);
extern void iosThreadInit(void);
extern int iosThreadJoin(void *a0);
extern void iosThreadSetPri(int *a0, int a1);
extern void iosThreadSleep(int a0, int a1, int a2, int a3);
extern void iosThreadStart(int a0);
extern void iosThreadStop(int a0);
extern int iosThreadWakeup(int *self);

#endif /* THREAD_H */
