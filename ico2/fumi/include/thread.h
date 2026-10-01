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

#include <eekernel.h>

/* --- ios thread object (SCE ee_thread_t at offset 0 + ICO bookkeeping) --- */
typedef struct IOSThread {    /* field names derived */
    struct ThreadParam param; /* 0x00 the kernel's thread record */
    int id;                   /* 0x30 kernel thread id                */
    int arg;                  /* 0x34 argument handed to func         */
    void (*func)();           /* 0x38 body run by iosThreadMain       */
    int flags;                /* 0x3C */
    int sleeping;             /* 0x40 read by iosThreadMain           */
    int pad44;                /* 0x44 */
    int hasQueue;             /* 0x48 */
    void *queue;              /* 0x4C */
    char name[16];            /* 0x50 */
    char pad60[16];           /* 0x60: the record is 0x70 bytes, which is the gap
                            between the boot thread and its stack in the ROM's
                            own .bss run */
} IOSThread;

struct IosSema; /* the record ios/thread.c defines */

/* The functions thread.c defines `inline`, in the order its end-of-file block
 * emits their out-of-line copies: gcc 2.9 defers a plain-inline definition to
 * the end of the object and writes the copies in first-declaration order, so
 * this block is read from the ROM (thread.o's .text from iosThreadCreate on). */
void iosThreadCreate(IOSThread *th, int no, void (*func)(), int arg, void *stack, long stackSize,
                     int pri);

int iosThreadGetPri(IOSThread *th);
IOSThread *iosGetIOSThreadFromId(unsigned int a0);
int iosThreadWakeup(IOSThread *th);
int iosThreadJoin(IOSThread *th);
int iosThreadCancelWakeup(IOSThread *th);
int iosSemaCreate(struct IosSema *self, int initCount, int maxCount, int option);
int iosSemaDelete(struct IosSema *self);
int iosSemaWait(struct IosSema *self);
int iosSemaSignal(struct IosSema *self);
int iosSemaReferStatus(struct IosSema *self);

/* The entry points thread.c compiles in place. */
void iosThreadCreateS(IOSThread *th, int no, void (*func)(), int arg, void *heap, long stackSize,
                      int pri);

void iosThreadDestroy(IOSThread *th);
void iosThreadInit(void);
void iosThreadSetPri(IOSThread *th, int pri);
/* reconstruction corrected: the ROM sets no argument register at any call
   site (StageManager has a bare nop in the jal delay slot); ios/thread.c keeps
   four parameters only so they flow through to SleepThread. */
void iosThreadSleep(void);
void iosThreadStart(IOSThread *th);
void iosThreadStop(IOSThread *th);
void iosThreadMessage(int a0);

#endif /* THREAD_H */
