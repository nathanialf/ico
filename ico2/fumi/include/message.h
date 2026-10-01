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

struct IosMsgQueue; /* the record ios/message.c defines */

/* message.o's .sdata global (MAIN.MAP): the signal thread's record */
extern int *th_sig;

void iosMsgInit(void);
void iosMsgQueueCreate(struct IosMsgQueue *q, int *buf, int size);
void iosMsgQueueDestroy(struct IosMsgQueue *q);
int iosMsgRecv(char *q, int *out, int mode);
int iosMsgSend(char *q, int val, int mode);
void iosMsgSetEvent(int intc, struct IosMsgQueue *q, int val);
int signal_handler(int a0);

#endif /* MESSAGE_H */
