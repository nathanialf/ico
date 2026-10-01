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

/* One entry of the directory cache iosCdvdMgrSearchFile fills: the file's
   sector and size and its disc name. */
typedef struct {
    int lsn;
    int size;
    char name[0x28];
} CdSrhEnt;

/* cdvd.c's globals: MAIN.MAP's cdvd.o names, and the stream motion late
   count streamMotionManager reads (our name). */
extern char iosCdvd[];
extern unsigned char CdvdMsgQ[];
extern int CdvdMsgQ_LoadEnd[];
extern CdSrhEnt iosCdvdSrhBuff[];
extern int IosCdvdMgrSleep;
extern int iosCdvdMediaType;
extern int iosCdvdBackGroundMgrRunning;
extern int iosCdvdStDelayCnt;
extern float inflateSec;

void cdWait(int *busy);
long long inflate_cd_read_func(void *buf, long long size, int *self);
void iosCdvdBackGroundMgr(void);
char *iosCdvdBackGroundMgrAdd(char *name, void *readFunc, int readArg, void *readyFunc, void *resumeFunc, int cbArg, void *closeFunc, int closeArg);
void iosCdvdBackGroundMgrDelete(char *self);
int iosCdvdBackGroundMgrDeleteRequestGet(void);
int iosCdvdBackGroundMgrEntryNum(void);
int iosCdvdBackGroundMgrNotDiskReadyPauseSet(void *a0, int a1);
void iosCdvdBackGroundMgrSeek(char *self, int val);
int iosCdvdBackGroundRead(char *self, void *buf, int size);
int iosCdvdBackGroundReadIOPm(char *self, void *buf, int size);
int iosCdvdChgFileName(int a0);
void iosCdvdDirectStClose(int *self);
int iosCdvdDirectStRead(int a0, int a1, int a2, int *a3);
int iosCdvdDiskStatusGet(void);
int iosCdvdGetFileLsn(char *name, int *size);
void iosCdvdHandlerRead(int *a0, void *a1, int a2);
void iosCdvdHandlerReadInflate(int *self, void *buf, int n);
void iosCdvdHandlerReadNoInflate(int *a0, void *buf, int n);
void iosCdvdMgrSearchFile(char *self);
void iosCdvdMgrStStart(char *self);
void iosCdvdMgrStStop(char *self);

void iosCdvdDiskReadyBlock(void);
void iosCdvdManager(void);
void iosCdvdLoadPackFile(int a0, char *name, int a2);
void iosCdvdBackGroundMgrInit(void);

#endif /* CDVD_H */
