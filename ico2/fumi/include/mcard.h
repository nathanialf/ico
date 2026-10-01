/*
 * ico2/fumi/include/mcard.h
 *
 * The declarations of what mcard.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MCARD_H
#define MCARD_H

/* mcard.c's globals (IosMcProductFile is declared by each user in its own
   view of the save record). */
extern int IosMcMgrSleep;
extern int IosMcLock;
extern char *iconName[];
extern char *iOSMcSaveSeg[];
extern int IosMcPreviewInfo[];
extern struct IosMsgQueue McMsgQ;
/* mcard.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
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
void iosMcManager(void);

/* iconfile: one memory card icon file, 0x24 bytes. Reader: ico2/fumi/ios/
 * mcard.c. Owner: ico2/fumi/include/mcard.h. */
typedef struct {   /* field names derived */
    char name[32]; /* 0x00 */
    int size;      /* 0x20 */
} IconFile;        /* derived name */
extern const IconFile iconFile[];

#endif /* MCARD_H */
