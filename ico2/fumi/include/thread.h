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

struct IOSThread; /* the record ios/thread.c defines */
struct IosSema;   /* the record ios/thread.c defines */

/* The functions thread.c defines `inline`, in the order its end-of-file block
 * emits their out-of-line copies: gcc 2.9 defers a plain-inline definition to
 * the end of the object and writes the copies in first-declaration order, so
 * this block is read from the ROM (thread.o's .text from iosThreadCreate on). */
void iosThreadCreate(struct IOSThread *th, int no, void (*func)(), int arg, void *stack,
                     long stackSize, int pri);
int iosThreadGetPri(int *a0);
int iosGetIOSThreadFromId(unsigned int a0);
int iosThreadWakeup(int *self);
int iosThreadJoin(void *a0);
int iosThreadCancelWakeup(int *self);
int iosSemaCreate(struct IosSema *self, int initCount, int maxCount, int option);
int iosSemaDelete(struct IosSema *self);
int iosSemaWait(struct IosSema *self);
int iosSemaSignal(struct IosSema *self);
int iosSemaReferStatus(struct IosSema *self);

/* The entry points thread.c compiles in place. */
void iosThreadCreateS(struct IOSThread *th, int no, void (*func)(), int arg, void *heap,
                      long stackSize, int pri);
void iosThreadDestroy(int a0);
void iosThreadInit(void);
void iosThreadSetPri(int *a0, int a1);
/* reconstruction corrected: the ROM sets no argument register at any call
   site (StageManager has a bare nop in the jal delay slot); ios/thread.c keeps
   four parameters only so they flow through to SleepThread. */
void iosThreadSleep(void);
void iosThreadStart(int a0);
void iosThreadStop(int a0);
void iosThreadMessage(int a0);

#endif /* THREAD_H */
