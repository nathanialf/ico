/*
 * ico2/fumi/include/message.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what message.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <eekernel.h>

/* a message queue: a ring of int messages guarded by a kernel semaphore */
typedef struct IosMsgQueue { /* field names derived */
    int *buf;             /* 0x00, the ring */
    int rd;               /* 0x04, the next slot iosMsgRecv reads */
    int num;              /* 0x08, messages held */
    int size;             /* 0x0C, slots in the ring */
    struct IosMsg *head;  /* 0x10, the first waiting sender (message.c's IosMsg) */
    struct SemaParam sem; /* 0x14 */
    int sema;             /* 0x2C, the semaphore id */
} IosMsgQueue;

/* message.o's .sdata global (MAIN.MAP): the signal thread's record */
extern int *th_sig;

void iosMsgInit(void);
void iosMsgQueueCreate(IosMsgQueue *q, int *buf, int size);
void iosMsgQueueDestroy(IosMsgQueue *q);
int iosMsgRecv(IosMsgQueue *q, int *out, int mode);
int iosMsgSend(IosMsgQueue *q, int val, int mode);
void iosMsgSetEvent(int intc, IosMsgQueue *q, int val);
int signal_handler(int a0);

#endif /* MESSAGE_H */
