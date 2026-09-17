/*
 * ico2/fumi/include/mcard.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mcard.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MCARD_H
#define MCARD_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order mcard.c's inline tail has. */
void iosMcMgrSync(void *mp);
void iosMcTest(void);
int iosMcSync(unsigned long *a0);
int iosMcGetInfo(void *a0);
int iosMcFormat(void *a0);
int iosMcUnformat(void *a0);
int iosMcGetDir(void *a0);
int iosMcDelete(void *a0);
int iosMcSaveIconBlock(void *a0);
int iosMcSaveProductBlock(void *a0);
int iosMcLoadProductBlock(void *a0);
int iosMcSaveGameBlock(void *a0, int a1);
int iosMcLoadGameBlock(void *a0, int a1);
int iosMcChdirProduct(void *a0);
int iosMcGetBlockSaveInfo(void *a0);
int product_write(int *self);
int product_read(int *self);
int gameblock_write(int self, void *buf);
int gameblock_read(int *self, void *buf);

int iosMcHandlerRead();
int iosMcHandlerWrite();

#endif /* MCARD_H */
