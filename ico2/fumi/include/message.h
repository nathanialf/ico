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

extern void iosMsgInit(void);
extern void iosMsgQueueCreate(void *q, void *buf, int n);
extern void iosMsgQueueDestroy(void *q);
extern int iosMsgRecv(char *q, int *out, int mode);
extern int iosMsgSend(char *q, int val, int mode);
extern void iosMsgSetEvent(int ev, void *q, int msg);
extern int signal_handler(int a0);

#endif /* MESSAGE_H */
