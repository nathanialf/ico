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

void iosMsgInit(void);
void iosMsgQueueCreate(void *q, void *buf, int n);
void iosMsgQueueDestroy(void *q);
int iosMsgRecv(char *q, int *out, int mode);
int iosMsgSend(char *q, int val, int mode);
void iosMsgSetEvent(int ev, void *q, int msg);
int signal_handler(int a0);

#endif /* MESSAGE_H */
