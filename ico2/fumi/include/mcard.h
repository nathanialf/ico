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

extern int iosMcChdirProduct(void *a0);
extern int iosMcDelete(void *a0);
extern int iosMcFormat(void *a0);
extern int iosMcGetBlockSaveInfo(void *a0);
extern int iosMcGetDir(void *a0);
extern int iosMcGetInfo(void *a0);
extern int iosMcHandlerRead();
extern int iosMcHandlerWrite();
extern int iosMcLoadGameBlock(void *a0, int a1);
extern int iosMcLoadProductBlock(void *a0);
extern void iosMcMgrSync(void *mp);
extern int iosMcSaveGameBlock(void *a0, int a1);
extern int iosMcSaveIconBlock(void *a0);
extern int iosMcSaveProductBlock(void *a0);
extern int iosMcSync(unsigned long *a0);
extern void iosMcTest(void);
extern int iosMcUnformat(void *a0);

#endif /* MCARD_H */
