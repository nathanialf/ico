/*
 * ico2/fumi/include/cdvd.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what cdvd.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CDVD_H
#define CDVD_H

extern void cdWait(int *busy);
extern long long inflate_cd_read_func(void *buf, long long size, int *self);
extern void iosCdvdBackGroundMgr(void);
extern char *iosCdvdBackGroundMgrAdd(char *name, void *readFunc, int readArg, void *readyFunc, void *resumeFunc, int cbArg, void *closeFunc, int closeArg);
extern void iosCdvdBackGroundMgrDelete(char *self);
extern int iosCdvdBackGroundMgrDeleteRequestGet(void);
extern int iosCdvdBackGroundMgrEntryNum(void);
extern int iosCdvdBackGroundMgrNotDiskReadyPauseSet(void *a0, int a1);
extern void iosCdvdBackGroundMgrSeek(char *self, int val);
extern int iosCdvdBackGroundRead(char *self, void *buf, int size);
extern int iosCdvdBackGroundReadIOPm(char *self, void *buf, int size);
extern int iosCdvdChgFileName(int a0);
extern void iosCdvdDirectStClose(int *self);
extern int iosCdvdDirectStRead(int a0, int a1, int a2, int *a3);
extern int iosCdvdDiskStatusGet(void);
extern int iosCdvdGetFileLsn(char *name, int *size);
extern void iosCdvdHandlerRead(int *a0, void *a1, int a2);
extern void iosCdvdHandlerReadInflate(int *self, void *buf, int n);
extern void iosCdvdHandlerReadNoInflate(int *a0, void *buf, int n);
extern void iosCdvdMgrSearchFile(char *self);
extern void iosCdvdMgrStStart(char *self);
extern void iosCdvdMgrStStop(char *self);

#endif /* CDVD_H */
