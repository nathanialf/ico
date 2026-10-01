/*
 * ico2/fumi/include/cdvd.h
 *
 * The declarations of what cdvd.c defines, for the files that use
 * them.  The file name is derived.
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
typedef struct CdvdBgReq { /* field names derived */
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
} CdvdBgReq; /* derived name */

/* One entry of the directory cache iosCdvdMgrSearchFile fills: the file's
   sector and size and its disc name. */
typedef struct { /* field names derived */
    int lsn;
    int size;
    char name[40];
} CdSrhEnt; /* derived name */

/* cdvd.c's globals, with the stream motion late count streamMotionManager
   reads. */
extern struct IosCdvdHandle iosCdvd;
extern struct IosMsgQueue CdvdMsgQ;
extern struct IosMsgQueue CdvdMsgQ_LoadEnd;
extern CdSrhEnt iosCdvdSrhBuff[];
extern int IosCdvdMgrSleep;
extern int iosCdvdMediaType;
extern int iosCdvdBackGroundMgrRunning;
extern int iosCdvdStDelayCnt;
extern float inflateSec;
long long inflate_cd_read_func(void *buf, long long size, void *handle);

CdvdBgReq *iosCdvdBackGroundMgrAdd(const char *name, void *readFunc, int readArg, void *readyFunc,
                                   void *resumeFunc, int cbArg, void *closeFunc, int closeArg);

void iosCdvdBackGroundMgrDelete(CdvdBgReq *self);
int iosCdvdBackGroundMgrDeleteRequestGet(void);
int iosCdvdBackGroundMgrEntryNum(void);
int iosCdvdBackGroundMgrNotDiskReadyPauseSet(CdvdBgReq *req, int on);
void iosCdvdBackGroundMgrSeek(CdvdBgReq *self, int val);
int iosCdvdBackGroundRead(CdvdBgReq *self, void *buf, int size);
int iosCdvdBackGroundReadIOPm(CdvdBgReq *self, void *buf, int size);
char *iosCdvdChgFileName(char *name);
void iosCdvdDirectStClose(struct IosCdvdHandle *self);
void iosCdvdDirectStOpen(struct IosCdvdHandle *self);
int iosCdvdDirectStRead(struct IosCdvdHandle *stream, void *dst, int size, int *err);
int iosCdvdDiskStatusGet(void);
int iosCdvdGetFileLsn(char *name, int *size);
void iosCdvdHandlerRead(struct IosCdvdHandle *self, void *dst, int size);
void iosCdvdHandlerReadInflate(struct IosCdvdHandle *self, void *buf, int n);
void iosCdvdHandlerReadNoInflate(struct IosCdvdHandle *self, void *buf, int n);
void iosCdvdManager(void);
void iosCdvdLoadPackFile(int inflate, char *name, int seg);

/* init-func: one file kind and its loader, 0x24 bytes. Reader:
 * ico2/fumi/ios/cdvd.c (PackKind). Owner: ico2/fumi/include/cdvd.h. */
typedef struct {  /* field names derived */
    char ext[32]; /* 0x00 */
    void (*func)(char *self, char *name, int size, int id, int kind, int word08, int seg); /* 0x20 */
} PackKind; /* derived name */

extern const PackKind initFunc[]; /* 26 rows */

#endif /* CDVD_H */
