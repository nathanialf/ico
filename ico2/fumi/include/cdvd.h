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

struct IosCdvdHandle; /* the record ios/cdvd.c defines */

/* One background read request (ios/cdvd.c keeps seven): the file's name,
 * empty while the slot is free, the read function the manager calls each
 * pass and its argument, the state bits (1 while the slot is being set up,
 * 2 when its deletion is asked for, 4 once the disc is ready again, 0x10 when
 * a disc error is not to stop the read), the file's size, the read position
 * and the file's sector, the functions told when the disc goes away and
 * comes back with their argument, and the function that closes the request
 * with its argument. */
typedef struct CdvdBgReq { /* derived name */         /* field names derived */
    char name[256];                                   /* 0x000 */
    int (*readFunc)(struct CdvdBgReq *self, int arg); /* 0x100 */
    int readArg;                                      /* 0x104 */

    struct {
        unsigned int busy : 1;  /* being set up */
        unsigned int del : 1;   /* its deletion is asked for */
        unsigned int ready : 1; /* the disc is ready again */
        unsigned int : 1;
        unsigned int noPause : 1; /* a disc error does not stop the read */
    } flags;                      /* 0x108 */

    int size;                                                     /* 0x10C */
    int pos;                                                      /* 0x110 */
    int lsn;                                                      /* 0x114 */
    void (*readyFunc)(struct CdvdBgReq *self, int arg, int flag); /* 0x118 */
    void (*resumeFunc)(struct CdvdBgReq *self, int arg);          /* 0x11C */
    int cbArg;                                                    /* 0x120 */
    int (*closeFunc)(struct CdvdBgReq *self, int arg);            /* 0x124 */
    int closeArg;                                                 /* 0x128 */
} CdvdBgReq;

/* One entry of the directory cache iosCdvdMgrSearchFile fills: the file's
   sector and size and its disc name. */
typedef struct {
    int lsn;
    int size;
    char name[0x28];
} CdSrhEnt;

/* cdvd.c's globals: MAIN.MAP's cdvd.o names, and the stream motion late
   count streamMotionManager reads (our name). */
extern struct IosCdvdHandle iosCdvd;
extern struct IosMsgQueue CdvdMsgQ;
extern struct IosMsgQueue CdvdMsgQ_LoadEnd;
extern CdSrhEnt iosCdvdSrhBuff[];
extern int IosCdvdMgrSleep;
extern int iosCdvdMediaType;
extern int iosCdvdBackGroundMgrRunning;
extern int iosCdvdStDelayCnt;
extern float inflateSec;
void cdWait(int *busy);
long long inflate_cd_read_func(void *buf, long long size, struct IosCdvdHandle *self);
void iosCdvdBackGroundMgr(void);

CdvdBgReq *iosCdvdBackGroundMgrAdd(const char *name, void *readFunc, int readArg, void *readyFunc,
                                   void *resumeFunc, int cbArg, void *closeFunc, int closeArg);

void iosCdvdBackGroundMgrDelete(CdvdBgReq *self);
int iosCdvdBackGroundMgrDeleteRequestGet(void);
int iosCdvdBackGroundMgrEntryNum(void);
int iosCdvdBackGroundMgrNotDiskReadyPauseSet(CdvdBgReq *a0, int a1);
void iosCdvdBackGroundMgrSeek(CdvdBgReq *self, int val);
int iosCdvdBackGroundRead(CdvdBgReq *self, void *buf, int size);
int iosCdvdBackGroundReadIOPm(CdvdBgReq *self, void *buf, int size);
int iosCdvdChgFileName(int a0);
void iosCdvdDirectStClose(struct IosCdvdHandle *self);
void iosCdvdDirectStOpen(struct IosCdvdHandle *self);
int iosCdvdDirectStRead(int a0, int a1, int a2, int *a3);
int iosCdvdDiskStatusGet(void);
int iosCdvdGetFileLsn(char *name, int *size);
void iosCdvdHandlerRead(struct IosCdvdHandle *a0, void *a1, int a2);
void iosCdvdHandlerReadInflate(struct IosCdvdHandle *self, void *buf, int n);
void iosCdvdHandlerReadNoInflate(struct IosCdvdHandle *self, void *buf, int n);
void iosCdvdMgrSearchFile(struct IosCdvdHandle *self);
void iosCdvdMgrStStart(struct IosCdvdHandle *self);
void iosCdvdMgrStStop(struct IosCdvdHandle *self);
inline void iosCdvdDiskReadyBlock(void);
void iosCdvdManager(void);
void iosCdvdLoadPackFile(int a0, char *name, int a2);
void iosCdvdBackGroundMgrInit(void);

/* init-func: one file kind and its loader, 0x24 bytes. Reader:
 * ico2/fumi/ios/cdvd.c (PackKind). Owner: ico2/fumi/include/cdvd.h. */
typedef struct {  /* field names derived */
    char ext[32]; /* 0x00 */
    void (*func)(char *self, char *name, int size, int a3, int a4, int a5, int seg); /* 0x20 */
} PackKind; /* derived name */
extern const PackKind initFunc[]; /* 26 rows */

#endif /* CDVD_H */
