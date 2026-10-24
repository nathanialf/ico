/*
 * ico2/fumi/include/cdvd.h
 *
 * The declarations of what cdvd.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef CDVD_H
#define CDVD_H

#ifdef VERSION_AUG6
#include <libcdvd.h>

struct InflateHandler;

/* a handle's control doubleword: bit 0 asks for the inflating read, word 1
   is the command */
union IosCdvdCtl { /* field names derived */
    long long ll;
    int i[2];
}; /* derived name */

/* the handle's directory record of its file, the 0x24 bytes sceCdSearchFile
   writes (cdvd.c's sceCdlFILE): sector, size, name column, date */
typedef struct IosCdvdFile { /* field names derived */
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int reserved;
} IosCdvdFile; /* derived name */

/* The cdvd handle a load request is made with (iosCdvd is the manager's own,
 * 33216 bytes): the command word, the result, the sector cursor the
 * stream reads advance, the read handler and its argument, the pack segment, the read counters, the file's name and its
 * directory record, the sceCdRead mode, the inflate handle, the stream
 * buffer, the 32 KB sector buffer and the streamed file's size. */
typedef struct IosCdvdHandle { /* field names derived */
    union IosCdvdCtl ctl;      /* 0x00, bit 0 asks for the inflating read; word 1 is
                            the command: 0 wait for the disc, 1 load, 2 pack
                            load */
    char pad8[4];
    int result; /* 0x0C */
    char pad10[4];
    int lsn;                                             /* 0x14 */
    int (*handler)(struct IosCdvdHandle *self, int arg); /* 0x18 */
    int handlerArg;                                      /* 0x1C */
    int seg;                                             /* 0x20, the pack's segment id */
    int readBytes;                                       /* 0x24 */
    int readSectorCnt;                                   /* 0x28 */
    int sectors;                                         /* 0x2C, the sectors still to stream */
    int buffCnt;                                         /* 0x30 */
    char name[256];                                      /* 0x34 */
    IosCdvdFile file;                                    /* 0x134 */
    CdRMode mode;                                        /* 0x158 */
    struct InflateHandler *inflate;                      /* 0x15C */
    int stMem;                                           /* 0x160 */
    int stBuf;                                           /* 0x164, stMem rounded up to 16 */
    char pad168[24];
    unsigned char buf[32768]; /* 0x180 */
    int stSize;               /* 0x8180 */
    char pad8184[60];
} IosCdvdHandle; /* derived name */
#else
struct IosCdvdHandle; /* the record ios/cdvd.c defines */
#endif

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
    int (*readFunc)(struct CdvdBgReq *self, void *arg); /* 0x100 */
    void *readArg;                                      /* 0x104 */

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
    void (*readyFunc)(struct CdvdBgReq *self, void *arg, int flag); /* 0x118 */
    void (*resumeFunc)(struct CdvdBgReq *self, void *arg);          /* 0x11C */
    void *cbArg;                                                    /* 0x120 */
    int (*closeFunc)(struct CdvdBgReq *self, void *arg);            /* 0x124 */
    void *closeArg;                                                 /* 0x128 */
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
#ifndef VERSION_AUG6
extern int iosCdvdStDelayCnt;
#endif
extern float inflateSec;
long long inflate_cd_read_func(void *buf, long long size, void *handle);

CdvdBgReq *iosCdvdBackGroundMgrAdd(const char *name, void *readFunc, void *readArg, void *readyFunc,
                                   void *resumeFunc, void *cbArg, void *closeFunc, void *closeArg);

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
    void (*func)(struct IosCdvdHandle *self, char *name, int size, int id, int kind, int word08,
                 int seg); /* 0x20 */
} PackKind; /* derived name */

extern const PackKind initFunc[]; /* 26 rows */

#endif /* CDVD_H */
