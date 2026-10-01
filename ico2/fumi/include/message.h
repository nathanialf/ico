/*
 * ico2/fumi/include/message.h
 *
 * The declarations of what message.c defines, for the files that use
 * them.  The file name is derived.
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
} IosMsgQueue; /* derived name */

/* message.o's .sdata global: the signal thread's record */
extern int *th_sig;

void iosMsgInit(void);
void iosMsgQueueCreate(IosMsgQueue *q, int *buf, int size);
void iosMsgQueueDestroy(IosMsgQueue *q);
int iosMsgRecv(IosMsgQueue *q, int *out, int mode);
int iosMsgSend(IosMsgQueue *q, int val, int mode);
void iosMsgSetEvent(int intc, IosMsgQueue *q, int val);
int signal_handler(int a0);

#endif /* MESSAGE_H */
