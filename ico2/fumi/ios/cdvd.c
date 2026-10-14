#include "cdvd.h"
#include <ctype.h>
#include <eekernel.h>
#include "debug.h"
#include "debug_exception.h"
#include "inflate.h"
#include "memory.h"
#include "message.h"
#include "pad.h"
#include "StageManager.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "thread.h"
#include "ios.h"
#include <assert.h>
#include <libcdvd.h>
#include <sifrpc.h>
#include <sound.h>
#include "include_asm.h"

static inline void iosCdvdDiskReadyBlock(void);
static void iosCdvdBackGroundMgrInit(void);
static void iosCdvdBackGroundMgr(void);

/* a handle's control doubleword: bit 0 asks for the inflating read, word 1
   is the command */
union IosCdvdCtl { /* field names derived */
    long long ll;
    int i[2];
}; /* derived name */

/* The record sceCdSearchFile fills in: it writes 0x24 bytes of it (lsn, size,
 * the name column and the date), and the stack slot it is given is 0x30.  */
typedef struct sceCdlFILE {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int reserved;
} sceCdlFILE;

/* The cdvd handle a load request is made with (iosCdvd is the manager's own,
 * 33216 bytes): the command word, the result, the sector cursor and the
 * sectors left that the stream manager advances, the read handler and its
 * argument, the pack segment, the read counters, the file's name and its
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
    int left;                                            /* 0x18 */
    int (*handler)(struct IosCdvdHandle *self, int arg); /* 0x1C */
    int handlerArg;                                      /* 0x20 */
    int seg;                                             /* 0x24, the pack's segment id */
    int readBytes;                                       /* 0x28 */
    int readSectorCnt;                                   /* 0x2C */
    int sectors;                                         /* 0x30, the sectors still to stream */
    int buffCnt;                                         /* 0x34 */
    char name[256];                                      /* 0x38 */
    sceCdlFILE file;                                     /* 0x138 */
    CdRMode mode;                                        /* 0x15C */
    InflateHandler *inflate;                             /* 0x160 */
    int stMem;                                           /* 0x164 */
    int stBuf;                                           /* 0x168, stMem rounded up to 16 */
    char pad16C[20];
    unsigned char buf[32768]; /* 0x180 */
    int stSize;               /* 0x8180 */
    char pad8184[60];
} IosCdvdHandle; /* derived name */

/* The streaming request iosCdvdMgrStStart hands to the cdvd thread: the
 * request record stReq and the preload window it describes. */
typedef struct {          /* field names derived */
    IosCdvdHandle *owner; /* 0x00 */
    int state;    /* 0x04, 0 stopped, 1 reading, 2 buffer full; printed as "stream mode error" */
    int command;  /* 0x08, 0 start, 1 stop, 2 resume when the buffer drains */
    char *buf;    /* 0x0C */
    int size;     /* 0x10 */
    int writePos; /* 0x14, the ring sector the next read lands at */
    int count;    /* 0x18, sectors in the ring */
    int readPos;  /* 0x1C, the ring sector iosCdStRead copies from */
} CdStReq;        /* derived name */

/* .data, all zero.  iosCdvd is the manager's cdvd handle (33216 bytes, as
   unifileHandle), the two queues take the 48-byte message queue record,
   iosCdvdSrhBuff is the 200-entry directory cache; the stream manager's
   acknowledge queue and its request record follow them. */
/* the handle's 32 KB sector buffer at 0x180 is a DMA target, so the handle
   is 64-byte aligned (as jimaku's buffers are); that alignment is the
   48 bytes of fill before this TU's .data */
IosCdvdHandle iosCdvd __attribute__((aligned(64))) = {{0}};

IosMsgQueue CdvdMsgQ = {0};

IosMsgQueue CdvdMsgQ_LoadEnd = {0};

CdSrhEnt iosCdvdSrhBuff[200] = {0};

static IosMsgQueue stAckQ = {0}; /* derived name */

static CdStReq stReq = {0}; /* derived name */

/* .sdata, the objects before the first string: the sleep flag, the
   directory cache count, the media mode (1, CD), the disc type the drive
   must report (18, a PlayStation 2 CD), the spindle control byte copied into
   each handle's read mode, the background read mode record (a record, so
   8-aligned after the byte), the background drive state and the stream
   load-end wait flag. */
int IosCdvdMgrSleep = 0;

static int srhBuffCnt = 0; /* derived name */

int iosCdvdMediaType = 1;

static int cdDiskType = 18; /* derived name */

static unsigned char cdSpindlCtrl = 1; /* derived name */

static CdRMode bgReadMode = {0}; /* derived name */

static int bgDriveState = 0; /* derived name */

static int stLoadEndWait = 0; /* derived name */

/* unifileHandle is the cdvd handle iosCdvdUnifileInfoGet loads the unifile
   through (a handle is 33216 bytes: the 0x180 header, the 32 KB sector
   buffer and the size word at 0x8180, the same size iosCdvdManager's reply
   buffer and mv_main's stream file take); bgReqTable the seven 300-byte
   background requests; skipBuf the 1 KB sink iosCdvdHandlerRead reads into
   when the caller passes no buffer; stThread, stStack and stReqQ the stream
   manager's thread record, its 16 KB stack and its request queue. */
static IosCdvdHandle unifileHandle; /* derived name */

static CdvdBgReq bgReqTable[7]; /* derived name */

static unsigned char skipBuf[1024]; /* derived name */

static char stThread[120]; /* derived name */

static char stStack[16384]; /* derived name */

static IosMsgQueue stReqQ; /* derived name */

/* cdvdMsgRing and cdvdLoadEndRing are the two-slot rings of the manager's
   request queue and its load-end queue, stPreLoadCnt the preloaded sector
   count iosCdvdMgrStStart hands the stream, bgRunning the background request
   iosCdvdBackGroundMgr is running, stReqRing and stAckRing the rings of the
   stream manager's request and acknowledge queues.  stReqRing's queue is
   created with one slot; no code reads its second word. */
static int cdvdMsgRing[2]; /* derived name */

static int cdvdLoadEndRing[2]; /* derived name */

static int stPreLoadCnt; /* derived name */

static int bgRunning; /* derived name */

static int stReqRing[2]; /* derived name */

static int stAckRing[1]; /* derived name */

/* The stream's TTY traces of a drive recovery, built only when DEBUG is
   defined; the retail build leaves each helper without a body.  The traces
   read the drive's own state, which is why they take no argument.  The two
   recovery prints below are compiled out; their strings ("get error fail",
   "st cd read error %d\n") stay in .rodata. */
static __inline__ void stDebugPrintError(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("cd error %d\n", sceCdGetError());
#endif
}

static __inline__ void stDebugPrintStatus(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("cd status %d\n", sceCdStatus());
#endif
}

static __inline__ void stDebugPrintMode(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("cd media mode %d\n", iosCdvdMediaType);
#endif
}

static void iosCdvdStManager(void);

INCLUDE_ASM(iosCdvdStManager);

/* The definition between the stream manager and the directory search.
 * Declared inline: iosCdvdMgrLoad, iosCdvdMgrPackLoad, iosCdvdManager and
 * iosCdvdDirectStOpen expand it, the stream manager above calls it, and the
 * out-of-line body goes to the end of the object.  Its two strings follow the
 * stream manager's in .rodata. */
static inline void iosCdvdDiskReadyBlock(void)
{
    if (sceCdDiskReady(1) != 2) {
        sceCdlFILE fp;
        char file[32];
        strcpy(file, "SCPS_110.03");
        iosCdvdChgFileName(file);
        debug_StdPrintfDummy("wait insert ico disk %s %s\n", "SCPS_110.03", file);
        do {
            sceCdDiskReady(0);
        } while (sceCdGetDiskType() != cdDiskType || sceCdSearchFile(&fp, file) == 0);
    }
}

/* the search-cache lookup of a file's sector, which iosCdvdGetFileLsn and
 * iosCdvdBackGroundMgrAdd inline */
static inline int getFileLsn(char *name, int *size) /* derived name */
{
    int i;

    for (i = 0; i < srhBuffCnt; i++) {
        if (strcmp(name, iosCdvdSrhBuff[i].name) == 0)
            goto found;
    }
    debug_assert(__FILE__, 749);
    __assert(__FILE__, 749, "0");
found:
    *size = iosCdvdSrhBuff[i].size;
    return iosCdvdSrhBuff[i].lsn;
}

static void iosCdvdMgrSearchFile(IosCdvdHandle *self)
{
    /* The walk index stays in its stack slot and is re-read after every
     * strcmp: the directory cache it indexes is the table the cdvd thread
     * also fills, so the counter is volatile. */
    volatile int i;
    int r = 1;

    if (strlen(self->name) < 0x28) {
        for (i = 0; i < srhBuffCnt; i++) {
            r = strcmp(self->name, iosCdvdSrhBuff[i].name);
            if (r == 0) {
                break;
            }
        }
    } else {
        debug_StdPrintfDummy("iosCdvdMgrSearchFile: warning filename length over\n");
    }
    if (r == 0) {
        self->file.lsn = iosCdvdSrhBuff[i].lsn;
        self->file.size = iosCdvdSrhBuff[i].size;
    } else {
        self->result = 0;
        if (sceCdSearchFile(&self->file, self->name) == 0) {
            self->result = 100;
        }
        if (srhBuffCnt < 200) {
            iosCdvdSrhBuff[srhBuffCnt].lsn = self->file.lsn;
            iosCdvdSrhBuff[srhBuffCnt].size = self->file.size;
            strncpy(iosCdvdSrhBuff[srhBuffCnt].name, self->name, 0x28);
            srhBuffCnt++;
        } else {
            debug_StdPrintfDummy("iosCdvdMgrSearchFile: warning iosCdvdSrhBuff over\n");
        }
    }
}

static void iosCdvdMgrStStart(IosCdvdHandle *self)
{
    int total;
    int rest;
    int cnt = stagePreLoadSectorCnt;
    int prelsn = stagePreLoadLsn;
    int lsn = self->file.lsn;

    stPreLoadCnt = cnt;
    self->buffCnt = 0;
    self->result = 0;
    if (lsn == prelsn) {
        lsn += cnt;
    } else {
        stagePreLoadSectorCnt = 0;
        stPreLoadCnt = 0;
    }
    stReq.owner = (IosCdvdHandle *)self;
    stReq.buf = stagePreLoadBuff;
    stReq.size = 0x380;
    stReq.count = stPreLoadCnt;
    stReq.writePos = stPreLoadCnt;
    if (stPreLoadCnt >= 0x380) {
        stReq.writePos = 0;
    }
    stReq.readPos = 0;
    self->lsn = lsn;
    total = (self->file.size - 1) >> 11;
    rest = lsn - self->file.lsn - 1;
    self->left = total - rest;
    stReq.command = 0;
    iosMsgSend(&stReqQ, &stReq, 1);
    self->inflate = open_inflate_handler(inflate_cd_read_func, self);
}

static void iosCdvdMgrStStop(IosCdvdHandle *self);

INCLUDE_ASM(iosCdvdMgrStStop);

/* a file name in the disc's form (a leading backslash, upper case, ";1"),
 * which iosCdvdChgFileName and the load paths inline */
static inline char *chgFileName(char *name) /* derived name */
{
    char buf[256];
    char *p = buf;
    char c;

    sprintf(buf, "\\%s;1", name);

    do {
        if ((c = *p) == '/') {
            *p = '\\';
        } else {
            *p = toupper(c);
        }
        p++;
    } while (*p != 0);
    return strcpy(name, buf);
}

static void iosCdvdMgrLoad(IosCdvdHandle *self)
{
    int rv;

    chgFileName(self->name);
    self->mode.trycount = 0;
    self->mode.spindlctrl = cdSpindlCtrl;
    self->mode.datapattern = 0;
    self->readBytes = 0;
    iosCdvdDiskReadyBlock();
    self->result = 0;
    iosCdvdMgrSearchFile(self);
    if (self->result != 0) {
        debug_StdPrintfDummy("file %s not found\n", self->name);
        return;
    }
    self->sectors = ((unsigned int)(self->file.size - 1) >> 11) + 1;
    iosCdvdMgrStStart(self);
    if (self->result != 0) {
        return;
    }
    /* a print compiled out of the retail build; its string stays in
     * .rodata */
    if (0) {
        debug_StdPrintfDummy("handler");
    }
    if (self->handler != 0) {
        rv = (self->handler)(self, self->handlerArg);
        if (rv != 0) {
            self->result = 102;
        }
    }
    debug_StdPrintfDummy("read done\n");
    iosCdvdMgrStStop(self);
    if (self->result == 0) {
        self->result = 0;
    }
}

INCLUDE_ASM(temp_loadfunc);

/* One entry of a .PAK archive's directory: the four words the loader passes
 * on and the member's name, 0x224 bytes per entry. */
typedef struct PackEnt { /* field names derived */
    int id;              /* 0x00, the loader's file number */
    int kind;            /* 0x04, the sound loaders' bank */
    int word08;          /* 0x08, passed on; no loader reads it */
    int size;            /* 0x0C */
    char name[532];      /* 0x10 */
} PackEnt;               /* derived name */

typedef void (*PackFunc)(IosCdvdHandle *self, char *name, int size, int id, int kind, int word08,
                         int seg);

/* the extension lookup, expanded inside the scan below */
static inline PackFunc findPackKind(char *ext, int *kind) /* derived name */
{
    int i;

    for (i = 0; i < 26; i++) {
        if (strcmp(ext, initFunc[i].ext) == 0) {
            *kind = i;
            return initFunc[i].func;
        }
    }
    *kind = -1;
    return 0;
}

/* the loader lookup, expanded inside iosCdvdMgrPackLoad */
static inline PackFunc getPackLoader(char *name, int *kind) /* derived name */
{
    int len;
    char *p;
    int i;

    inflateSec = 0;
    len = strlen(name);
    p = name + (len - 1);
    for (i = 0; i < len; i++, p--) {
        if (*p == '.') {
            p++;
            return findPackKind(p, kind);
        }
    }
    return 0;
}

/* Three prints are compiled out here: the file count, each member's name and
 * the load time.  Their format strings stay in .rodata after "try load %s\n",
 * and the timer and DMA status calls whose values only the prints used
 * stay. */
static void iosCdvdMgrPackLoad(IosCdvdHandle *self);

INCLUDE_ASM(iosCdvdMgrPackLoad);

INCLUDE_ASM(iosCdStRead);

/* The read-retry sleep: IosCdvdMgrSleep marks the cdvd thread asleep, as
   cdWait and iosCdvdManager set it around their own sleeps. */
static inline void cdvdSleep(void) /* derived name */
{
    IosCdvdMgrSleep = 1;
    iosThreadSleep();
    IosCdvdMgrSleep = 0;
}

/* self is the cdvd handle: the result word iosCdStRead is handed, the bytes
   consumed, readSectorCnt and buffCnt (the assert format names both), the
   sectors still to stream and the 32 KB sector buffer.  buf is advanced in
   place.  ofs is the byte offset in the buffer the sectors are read to, zero
   because a read only happens once the buffer is drained. */
void iosCdvdHandlerReadNoInflate(IosCdvdHandle *self, void *buf, int n);

INCLUDE_ASM(iosCdvdHandlerReadNoInflate);

void iosCdvdHandlerReadInflate(IosCdvdHandle *self, void *buf, int n)
{
    char *p;
    long long len;

    p = buf;
    while ((len = inflate(self->inflate, p, n)) > 0) {
        p += (int)len;
        n -= (int)len;
    }
    if (len < 0) {
        debug_StdPrintfDummy("Decompression error\n");
    }
}

void iosCdvdHandlerRead(IosCdvdHandle *self, void *dst, int size)
{
    if (dst != 0) {
        if ((self->ctl.ll & 1) == 1) {
            iosCdvdHandlerReadInflate(self, dst, size);
        } else {
            iosCdvdHandlerReadNoInflate(self, dst, size);
        }
        return;
    }
    while (size > 0) {
        int n = (size < 0x401) ? size : 0x400;
        void *buf = skipBuf;
        if ((self->ctl.ll & 1) == 1) {
            iosCdvdHandlerReadInflate(self, buf, n);
        } else {
            iosCdvdHandlerReadNoInflate(self, buf, n);
        }
        size -= n;
    }
}

static int unifile_read_func(IosCdvdHandle *self, int arg)
{
    char work[32];
    int cnt;
    int lsn;

    iosCdvdHandlerRead(self, &cnt, 4);
    while (cnt-- > 0) {
        iosCdvdHandlerRead(self, work, 32);
        sprintf(self->name, "DFDATAS/%s", work);
        chgFileName(self->name);
        strcpy(iosCdvdSrhBuff[srhBuffCnt].name, self->name);
        iosCdvdHandlerRead(self, &lsn, 4);
        iosCdvdSrhBuff[srhBuffCnt].lsn = lsn / 2048 + self->file.lsn;
        iosCdvdHandlerRead(self, &iosCdvdSrhBuff[srhBuffCnt].size, 4);
        srhBuffCnt++;
    }
    return 1;
}

/* The 0x38 name column of a cdvd request is written 16 bytes at a time, so it
 * is typed as an 8-byte-aligned pair: the unifile request always loads the
 * fixed disc path "DFDATAS/DATA.DF", copied as two doublewords. */
typedef struct { /* field names derived */
    long long lo;
    long long hi;
} CdvdName16; /* derived name */

static void iosCdvdUnifileInfoGet(void)
{
    unifileHandle.ctl.ll &= ~1LL;
    *(CdvdName16 *)unifileHandle.name = *(CdvdName16 *)"DFDATAS/DATA.DF";
    unifileHandle.handler = unifile_read_func;
    iosCdvdMgrLoad(&unifileHandle);
}

int iosCdvdBackGroundMgrRunning = 0;

/* stThread is a 120-byte buffer, 8 bytes more than an IOSThread: typed as
   one, the object's .bss is 8 bytes shorter (measured) */

/* The cdvd manager thread, with iosCdvdDiskReadyBlock expanded in case 0.
   The reply buffer's block opens after the switch.  req is the request the
   switch dispatches on, held across case 0's calls; the default arm reads
   msg again.  The LoadEnd receivers never read the reply value. */
void iosCdvdManager(void)
{
    IosCdvdHandle *msg;
    IosCdvdHandle *req;

    sceCdInit(0);
    sceCdMmode(iosCdvdMediaType);
    sceFsReset();

    iosThreadCreate(stThread, 6, iosCdvdStManager, 0, stStack, 16384, 27);
    iosThreadStart(stThread);

    iosCdvdBackGroundMgrInit();
    /* the start banner, compiled out; its string stays in .rodata */
    if (0) {
        debug_StdPrintfDummy("CD MANAGER START");
    }

    iosMsgQueueCreate(&CdvdMsgQ, cdvdMsgRing, 2);
    iosMsgQueueCreate(&CdvdMsgQ_LoadEnd, cdvdLoadEndRing, 2);

    iosCdvdUnifileInfoGet();

    SignalSema(IosCdLock);

    while (1) {
        while (iosMsgRecv(&CdvdMsgQ, &msg, 0) == -1) {
            iosCdvdBackGroundMgrRunning = 1;
            iosCdvdBackGroundMgr();
            iosCdvdBackGroundMgrRunning = 0;
            IosCdvdMgrSleep = 1;
            iosThreadSleep();
            IosCdvdMgrSleep = 0;
        }
        req = msg;
        switch (req->ctl.i[1]) {
        case 0:
            iosCdvdDiskReadyBlock();
            req->result = 0;
            break;
        case 1:
            /* a print compiled out of the retail build; its string stays in
             * .rodata */
            if (0) {
                debug_StdPrintfDummy("load");
            }
            iosCdvdMgrLoad(req);
            break;
        case 2:
            iosCdvdMgrPackLoad(req);
            break;
        default:
            debug_StdPrintfDummy("iosMcManager: recv command %d error.", msg->ctl.i[1]);
            break;
        }
        {
            char reply[33216];
            iosMsgSend(&CdvdMsgQ_LoadEnd, reply, 0);
        }
    }
}

void iosCdvdDiskReady(int req)
{
    union IosCdvdCtl *p = (union IosCdvdCtl *)req;
    p->i[1] = 0;
    iosMsgSend(&CdvdMsgQ, req, 0);
}

void iosCdvdLoad(int req, int inflate)
{
    union IosCdvdCtl *p = (union IosCdvdCtl *)req;
    p->i[1] = 1;
    p->ll = (p->ll & ~1LL) | (inflate & 1);
    iosMsgSend(&CdvdMsgQ, req, 0);
}

static void iosCdvdPackLoad(IosCdvdHandle *cdvd)
{
    cdvd->ctl.i[1] = 2;
    iosMsgSend(&CdvdMsgQ, cdvd, 0);
}

INCLUDE_ASM(iosCdvdBackGroundMgrAdd);

/* The rest of the .sdata run, after iosCdvdManager's strings: the saved
   system parameter word cdWait restores after a drive recovery and the flag
   that it is saved, the background read and read retry counts, the stream
   motion late count streamMotionManager keeps, and inflateSec. */
static int cdWaitParamSet = 0; /* derived name */

static int cdWaitParamSave = 0; /* derived name */

static int bgReadCnt = 0; /* derived name */

static int bgReadRetryCnt = 0; /* derived name */

int iosCdvdStDelayCnt = 0; /* derived name */

float inflateSec = 0;

static void cdWait(int *busy)
{
    sceCdlFILE fp;
    char file[32];
    CdvdBgReq *self;
    int r;

    IosCdvdMgrSleep = 1;
    iosThreadSleep();
    IosCdvdMgrSleep = 0;
    while (1) {
        self = (CdvdBgReq *)bgRunning;
        switch (bgDriveState) {
        case 0:
            if (sceCdStatus() != 1) {
                break;
            }
            bgDriveState = 1;
            cdWaitParamSave = systemStatus[0x14 / 4];
        case 1:
            if (self->readyFunc != 0) {
                (self->readyFunc)(self, self->cbArg, self->flags.ready);
                self->flags.ready = 0;
            }
            if (self->flags.noPause == 0) {
                iosPadDisable();
                systemStatus[0x14 / 4] = 1;
                cdWaitParamSet = 1;
            }
            strcpy(file, "SCPS_110.03");
            chgFileName(file);
            r = sceCdDiskReady(1);
            if (r == 2 && sceCdGetDiskType() == cdDiskType && sceCdSearchFile(&fp, file) != 0) {
                self->flags.ready = 1;
                if (self->resumeFunc != 0) {
                    (self->resumeFunc)(self, self->cbArg);
                }
                bgDriveState = r;
                if (cdWaitParamSet != 0) {
                    iosPadEnable();
                    cdWaitParamSet = 0;
                    systemStatus[0x14 / 4] = cdWaitParamSave;
                }
            }
            break;
        case 2:
            bgDriveState = 0;
            break;
        }
        if (bgDriveState == 0) {
            break;
        }
        *busy = 1;
        IosCdvdMgrSleep = 1;
        iosThreadSleep();
        IosCdvdMgrSleep = 0;
    }
}

INCLUDE_ASM(iosCdvdBackGroundRead);

INCLUDE_ASM(iosCdvdBackGroundReadIOPm);

INCLUDE_ASM(iosCdvdDirectStOpen);

void iosCdvdDirectStClose(IosCdvdHandle *self)
{
    int err;
    self->result = 0;
    err = sceCdStStop();
    if (err == 0) {
        self->result = sceCdGetError();
    }
    sceSifFreeIopHeap(self->stMem);
}

/* The loop carries the next character in `c`, which the test assigns and
 * toupper reads. */
char *iosCdvdChgFileName(char *name)
{
    return chgFileName(name);
}

INCLUDE_ASM(iosCdvdGetFileLsn);

int iosCdvdSync(int msg)
{
    int local = msg;
    iosMsgRecv(&CdvdMsgQ_LoadEnd, &local, 1);
    return 1;
}

void iosCdvdLoadPackFile(int inflate, char *name, int seg)
{
    int buf[4];
    iosCdvd.ctl.ll = (iosCdvd.ctl.ll & ~1LL) | (inflate & 1);
    strcpy(iosCdvd.name, name);
    iosCdvd.seg = seg;
    iosCdvd.handler = 0;
    iosCdvd.handlerArg = 0;
    iosCdvdPackLoad(&iosCdvd);
    buf[0] = (int)&iosCdvd;
    iosMsgRecv(&CdvdMsgQ_LoadEnd, buf, 1);
}

int iosCdvdDiskStatusGet(void)
{
    return bgDriveState;
}

void iosCdvdBackGroundMgrDelete(CdvdBgReq *self)
{
    self->flags.del = 1;
}

int iosCdvdBackGroundMgrNotDiskReadyPauseSet(CdvdBgReq *req, int on)
{
    int *p = (int *)&req->flags;
    return *p = (*p & ~0x10) | ((on & 1) << 4);
}

int iosCdvdBackGroundMgrDeleteRequestGet(void)
{
    CdvdBgReq *p = bgReqTable;
    CdvdBgReq *limit = p + 7;
    int count = 0;
    do {
        if (p->name[0] != 0) {
            count += p->flags.del;
        }
        p++;
    } while ((int)p < (int)limit);
    return count;
}

int iosCdvdBackGroundMgrEntryNum(void)
{
    CdvdBgReq *p = bgReqTable;
    CdvdBgReq *limit = p + 7;
    int count = 0;
    do {
        char b = p->name[0];
        int new_count = count + 1;
        p++;
        if (b != 0) {
            count = new_count;
        }
    } while ((int)p < (int)limit);
    return count;
}

void iosCdvdBackGroundMgrSeek(CdvdBgReq *self, int val)
{
    self->pos = val;
}

int iosCdvdBackGroundMgrGetRunning(void)
{
    return bgRunning;
}

int iosCdvdDirectStRead(IosCdvdHandle *stream, void *dst, int size, int *err)
{
    int local, result;
    *err = 0;
    result = sceCdStRead(size >> 11, dst, 1, &local) << 11;
    if (local != 0) {
        debug_StdPrintfDummy("cd read error %d\n", local);
        *err = 1;
    }
    return result;
}

/* The inflate handler's read callback (installed by iosCdvdMgrStStart): hand
 * the decoder at most as many bytes as are still left in the streamed file --
 * its total length at +0x13C minus the bytes already consumed at +0x28.  */
long long inflate_cd_read_func(void *buf, long long size, void *handle)
{
    IosCdvdHandle *self = handle;
    long long rest;
    long long len;

    rest = (unsigned int)(self->file.size - self->readBytes);

    if (rest < size)
        len = rest;
    else
        len = size;

    if (len != 0)
        iosCdvdHandlerReadNoInflate(self, buf, len);

    return len;
}

static void iosCdvdBackGroundMgrInit(void)
{
    CdvdBgReq *p = bgReqTable;
    int i;
    p += 6;
    for (i = 6; i >= 0; i--) {
        p->name[0] = 0;
        p--;
    }
    bgRunning = 0;
}

typedef int (*BgFunc)(CdvdBgReq *self, void *arg);

static void iosCdvdBackGroundMgr(void)
{
    CdvdBgReq *bg = bgReqTable;
    int i;
    BgFunc func;

    for (i = 6; i >= 0; i--, bg++) {
        if (bg->name[0] == 0 || bg->flags.busy)
            continue;
        bgRunning = (int)bg;
        if (bg->flags.del == 0) {
            if ((func = bg->readFunc) != 0) {
                if (func(bg, bg->readArg) > 0)
                    bg->readFunc = 0;
            }
        } else {
            if ((func = bg->closeFunc) != 0)
                func(bg, bg->closeArg);
            bg->name[0] = 0;
        }
        bgRunning = 0;
    }
}

INCLUDE_ASM(iosCdvdDiskReadyBlock);
