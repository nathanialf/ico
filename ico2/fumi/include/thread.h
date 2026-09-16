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

int iosGetIOSThreadFromId(unsigned int a0);
int iosSemaCreate(int *self, int a1, int a2, int a3);
int iosSemaDelete(int *self);
int iosSemaReferStatus(int *self);
int iosSemaSignal(int *self);
int iosSemaWait(int *self);
int iosThreadCancelWakeup(int *self);
void iosThreadCreate(void *th, int no, void (*func)(), int arg, void *stack, long stackSize, int pri);
void iosThreadCreateS(unsigned int *th, int no, void (*func)(), int arg, void *heap, long stackSize, int pri);
void iosThreadDestroy(int a0);
int iosThreadGetPri(int *a0);
void iosThreadInit(void);
int iosThreadJoin(void *a0);
void iosThreadSetPri(int *a0, int a1);
void iosThreadSleep(int a0, int a1, int a2, int a3);
void iosThreadStart(int a0);
void iosThreadStop(int a0);
int iosThreadWakeup(int *self);

#endif /* THREAD_H */
