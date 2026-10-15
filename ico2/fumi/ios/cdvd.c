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
    sceCdlFILE file;                                     /* 0x134 */
    CdRMode mode;                                        /* 0x158 */
    InflateHandler *inflate;                             /* 0x15C */
    int stMem;                                           /* 0x160 */
    int stBuf;                                           /* 0x164, stMem rounded up to 16 */
    char pad168[24];
    unsigned char buf[32768]; /* 0x180 */
    int stSize;               /* 0x8180 */
    char pad8184[60];
} IosCdvdHandle; /* derived name */

/* .data, all zero.  iosCdvd is the manager's cdvd handle (33216 bytes), the
   two queues take the 48-byte message queue record, iosCdvdSrhBuff is the
   200-entry directory cache. */
/* the handle's 32 KB sector buffer at 0x180 is a DMA target, so the handle
   is 64-byte aligned (as jimaku's buffers are); that alignment is the
   48 bytes of fill before this TU's .data */
IosCdvdHandle iosCdvd __attribute__((aligned(64))) = {{0}};

IosMsgQueue CdvdMsgQ = {0};

IosMsgQueue CdvdMsgQ_LoadEnd = {0};

CdSrhEnt iosCdvdSrhBuff[200] = {0};

/* .sdata, the objects before the first string: the sleep flag, the
   directory cache count, the media mode (1, CD), the background read mode
   record (two tries; a record, so 8-aligned after the word) and the
   background drive state. */
int IosCdvdMgrSleep = 0;

static int srhBuffCnt = 0; /* derived name */

int iosCdvdMediaType = 1;

static CdRMode bgReadMode = {2}; /* derived name */

static int bgDriveState = 0; /* derived name */

/* bgReqTable the seven 300-byte background requests; skipBuf the 1 KB sink
   iosCdvdHandlerRead reads into when the caller passes no buffer. */
static CdvdBgReq bgReqTable[7]; /* derived name */

static unsigned char skipBuf[1024]; /* derived name */

/* cdvdMsgRing and cdvdLoadEndRing are the two-slot rings of the manager's
   request queue and its load-end queue, stPreLoadCnt the preloaded sector
   count, bgRunning the background request iosCdvdBackGroundMgr is
   running. */
static int cdvdMsgRing[2]; /* derived name */

static int cdvdLoadEndRing[2]; /* derived name */

static int stPreLoadCnt; /* derived name */

static int bgRunning; /* derived name */

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

/* Declared inline: iosCdvdMgrLoad, iosCdvdMgrPackLoad, iosCdvdManager,
 * iosCdvdDirectStOpen and cdWait expand it.  Until the disc is back it prints
 * the request on every pass and waits for a PlayStation 2 CD (disc type 18)
 * that holds the boot file. */
static inline void iosCdvdDiskReadyBlock(void)
{
    if (sceCdDiskReady(1) != 2) {
        sceCdlFILE fp;
        char file[32];
        strcpy(file, "SCUS_971.13");
        iosCdvdChgFileName(file);
        do {
            debug_StdPrintfDummy("wait insert ico disk\n");
            sceCdDiskReady(0);
        } while (sceCdGetDiskType() != 18 || sceCdSearchFile(&fp, file) == 0);
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
    debug_assert(__FILE__, 483);
    __assert(__FILE__, 483, "0");
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

/* The stream is the library's: the preloaded sectors the stage
 * manager left are skipped, sceCdStInit gets an 80-sector ring in IOP memory
 * and the stream starts only when the preload does not already hold the whole
 * file. */
static void iosCdvdMgrStStart(IosCdvdHandle *self)
{
    int cnt = stagePreLoadSectorCnt;
    int lsn = self->file.lsn;
    int mem;

    stPreLoadCnt = cnt;
    self->buffCnt = 0;
    self->result = 0;
    if (lsn == stagePreLoadLsn) {
        lsn += cnt;
    } else {
        stPreLoadCnt = 0;
    }
    mem = iosSifAllocIopHeapDebug(80 * 2048 + 16, __FILE__, 565);
    /* an allocation check compiled out of the retail build; its message
     * stays in .rodata */
    if (0) {
        debug_StdPrintfDummy("\nCan't alloc cd stream buff %d \n", 80 * 2048 + 16);
    }
    self->stMem = mem;
    self->stBuf = (mem + 15) & 0xFFFFFFF0;
    sceCdStInit(80, 5, (void *)((mem + 15) & 0xFFFFFFF0));
    if ((stPreLoadCnt << 11) < self->file.size) {
        self->lsn = lsn;
        if (sceCdStStart(lsn, &self->mode) == 0) {
            self->result = sceCdGetError();
        }
    }
    self->inflate = open_inflate_handler(inflate_cd_read_func, self);
}

static void iosCdvdMgrStStop(IosCdvdHandle *self)
{
    self->result = 0;
    if (sceCdStStop() == 0) {
        self->result = sceCdGetError();
    }
    sceSifFreeIopHeap(self->stMem);
    close_inflate_handler(self->inflate);
}

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
    self->mode.spindlctrl = 1;
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
    debug_StdPrintfDummy("handler");
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

void temp_loadfunc(IosCdvdHandle *self, char *name, int size, int id, int kind, int word08, int seg)
{
    void *p = (void *)iosMallocDebug(ios_partition_seki, size, __FILE__, 828);

    iosCdvdHandlerRead(self, p, size);
    debug_StdPrintfDummy("temp_loadfunc::%s  (size:%d)(segid=%d)\n", name, size, seg);
    iosFree(p);
}

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

/* The pack load prints the file count, each member's load time and the
 * inflate time, and the total load time at the end. */
static void iosCdvdMgrPackLoad(IosCdvdHandle *self)
{
    int start = lock_execIcoMisc;
    float total = 0;
    float sec;

    chgFileName(self->name);
    self->mode.trycount = 0;
    self->mode.spindlctrl = 1;
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
    /* The pack pass runs in its own scope: the two inlined helpers above have
     * released their stack buffers by here, so the header lands in the slot
     * the sprintf buffer used. */
    {
        int hdr[4];
        PackEnt *ent;
        int *num;
        PackEnt *pk;
        PackFunc f;
        int kind;
        int seg;
        int size;
        float time;

        debug_StdPrintfDummy("try load %s\n", self->name);
        iosCdvdHandlerRead(self, hdr, 16);
        /* The entry count is the header's first word; the loop re-reads it
         * through this view after every member call. */
        num = hdr;
        debug_StdPrintfDummy("n=%d\n", *num);
        debug_StdPrintfDummy("------------------------------------------------files %d -----\n",
                             *num);
        systemStatus[7] = *num;
        systemStatus[8] = 0;
        size = *num * sizeof(PackEnt);
        ent = (PackEnt *)iosMallocDebug(ios_partition_seki, size, __FILE__, 898);
        iosCdvdHandlerRead(self, ent, size);
        pk = ent;
        for (seg = 0; seg < *num; seg++, pk++) {
            debug_BeginTimer(3);
            f = getPackLoader(pk->name, &kind);
            if (f != 0) {
                f(self, pk->name, pk->size, pk->id, pk->kind, pk->word08, self->seg);
            } else {
                temp_loadfunc(self, pk->name, pk->size, pk->id, pk->kind, pk->word08, self->seg);
            }
            debugCdvdLoadInfoSegAdd(self->seg, kind, pk->size);
            time = debug_GetTimerSec();
            total += time;
            debug_StdPrintfDummy("file id %s %d time %f read %d \n", pk->name, pk->size, time,
                                 self->readBytes);
            debug_StdPrintfDummy("inflate time %f\n", inflateSec);
        }
        iosFree(ent);
    }
    sec = debug_GetTimerSec();
    SgGetDmaTransferStatus(1);
    debug_StdPrintfDummy("load time %d %f Sec\n", lock_execIcoMisc - start, total + sec);
    debug_StdPrintfDummy("read done\n");
    iosCdvdMgrStStop(self);
    iosCdvdBackGroundMgr();
    if (self->result == 0) {
        self->result = 0;
    }
}

/* The read-retry sleep: IosCdvdMgrSleep marks the cdvd thread asleep, as
   cdWait and iosCdvdManager set it around their own sleeps. */
static inline void cdvdSleep(void) /* derived name */
{
    IosCdvdMgrSleep = 1;
    iosThreadSleep();
    IosCdvdMgrSleep = 0;
}

/* The stream read: on a drive error the stream is stopped, the disc waited
 * for and the stream restarted at the handle's sector. */
static inline int iosCdStRead(unsigned int n, int *buf, int flag, int *result, IosCdvdHandle *self)
{
    int r;

    do {
        r = sceCdStRead(n, buf, flag, result);
        if (*result == 0) {
            break;
        }
        debug_StdPrintfDummy("out %d\n", r);
        sceCdStStop();
        while (sceCdDiskReady(1) != 2) {
            cdvdSleep();
        }
        sceCdStStart(self->lsn, &self->mode);
    } while (1);
    self->lsn += r;
    return r;
}

/* self is the cdvd handle: the result word the stream read is handed, the
   bytes consumed, readSectorCnt and buffCnt, the sectors still to stream and
   the 32 KB sector buffer.  The sectors the stage manager preloaded are
   taken first, and the preload ring is refilled behind them; ofs is where in
   the buffer the stream's sectors follow the preloaded ones. */
void iosCdvdHandlerReadNoInflate(IosCdvdHandle *self, void *buf, int n)
{
    int total = n;
    int ofs = 0;
    int cnt;
    int size;
    int rest;
    int sz;

    while (n > 0) {
        if (self->buffCnt == 0) {
            cnt = ((unsigned int)self->sectors > 15) ? 16 : self->sectors;
            if (stPreLoadCnt != 0) {
                if (stPreLoadCnt >= cnt) {
                    self->readSectorCnt = cnt;
                    size = cnt << 11;
                    stPreLoadCnt -= cnt;
                    cnt = 0;
                } else {
                    self->readSectorCnt = stPreLoadCnt;
                    ofs = stPreLoadCnt << 11;
                    cnt -= stPreLoadCnt;
                    stPreLoadCnt = 0;
                    size = ofs;
                }
                memcpy(self->buf, stagePreLoadBuff + stagePreLoadReadOffset, size);
                stagePreLoadReadOffset += size;
                self->sectors -= self->readSectorCnt;
                rest = stagePreLoadReadOffset - stagePreLoad2ndReadOffset;
                if (self->sectors - stPreLoadCnt - stagePreLoad2ndReadOffset / 2048 > 0 &&
                    rest > 32768) {
                    FlushCache(0);
                    stagePreLoad2ndReadOffset +=
                        iosCdStRead(rest / 2048,
                                    (int *)(stagePreLoadBuff + stagePreLoad2ndReadOffset), 0,
                                    &self->result, self)
                        << 11;
                } else {
                    debug_StdPrintfDummy("skip !!!!");
                }
                if (stPreLoadCnt == 0) {
                    debug_StdPrintfDummy("RING %d\n", stagePreLoad2ndReadOffset);
                    stPreLoadCnt = stagePreLoad2ndReadOffset / 2048;
                    stagePreLoad2ndReadOffset = 0;
                    stagePreLoadReadOffset = 0;
                }
            } else {
                ofs = 0;
            }
            if (cnt != 0) {
                FlushCache(0);
                while ((self->readSectorCnt = iosCdStRead(cnt, (int *)(self->buf + ofs), 0,
                                                          &self->result, self)) == 0) {
                    cdvdSleep();
                }
                self->sectors -= self->readSectorCnt;
            }
        }
        sz = n;
        if (sz > (self->readSectorCnt << 11) - self->buffCnt) {
            sz = (self->readSectorCnt << 11) - self->buffCnt;
        }
        memcpy(buf, self->buf + self->buffCnt, sz);
        self->buffCnt += sz;
        if ((unsigned int)self->buffCnt >= (unsigned int)(self->readSectorCnt << 11)) {
            self->buffCnt = 0;
        }
        buf += sz;
        n -= sz;
    }
    self->readBytes += total;
}

void iosCdvdHandlerReadInflate(IosCdvdHandle *self, void *buf, int n)
{
    char *p;
    long long len;

    p = buf;
    while ((len = inflate(self->inflate, p, n)) > 0) {
        p += (int)len;
        n -= (int)len;
    }
    debug_StdPrintfDummy("iosCdvdHandlerReadInflate size %d\n", self->readBytes);
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

/* The unifile request is a handle on the stack: it always loads the fixed
 * disc path "DFDATAS/DATA.DF", whose directory unifile_read_func reads into
 * the search cache. */
static inline void iosCdvdUnifileInfoGet(void)
{
    IosCdvdHandle unifile;

    unifile.ctl.ll &= ~1LL;
    strcpy(unifile.name, "DFDATAS/DATA.DF");
    unifile.handler = unifile_read_func;
    iosCdvdMgrLoad(&unifile);
}

int iosCdvdBackGroundMgrRunning = 0;

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

    iosCdvdBackGroundMgrInit();
    debug_StdPrintfDummy("CD MANAGER START");

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
            debug_StdPrintfDummy("load");
            iosCdvdMgrLoad(msg);
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

CdvdBgReq *iosCdvdBackGroundMgrAdd(const char *name, void *readFunc, void *readArg, void *readyFunc,
                                   void *resumeFunc, void *cbArg, void *closeFunc, void *closeArg)
{
    char buf[256];
    int size;
    int i;
    CdvdBgReq *bg;
    char *p;

    for (i = 0; i < 7; i++) {
        if (bgReqTable[i].name[0] == 0)
            goto found;
    }
    for (i = 0; i < 7; i++) {
        debug_StdPrintfDummy("** %d %s %p\n", i, bgReqTable[i].name, bgReqTable[i].readFunc);
    }
    debug_assert(__FILE__, 1571);
    __assert(__FILE__, 1571, "0");
found:
    bg = &bgReqTable[i];
    bg->flags.busy = 1;
    bg->flags.del = 0;
    bg->flags.noPause = 0;
    bg->flags.ready = 1;
    strcpy(bg->name, name);
    bg->readFunc = readFunc;
    bg->readArg = readArg;
    bg->readyFunc = readyFunc;
    bg->resumeFunc = resumeFunc;
    bg->cbArg = cbArg;
    bg->closeFunc = closeFunc;
    bg->closeArg = closeArg;
    p = strrchr(bg->name, '/');
    if (p != 0) {
        p = p + 1;
    } else {
        p = bg->name;
    }
    sprintf(buf, "DFDATAS/%s", p);
    chgFileName(buf);
    bg->lsn = getFileLsn(buf, &size);
    bg->size = size;
    debug_StdPrintfDummy("%s lsn:%d handler:%p\n", buf, bg->lsn, readFunc);
    bg->pos = 0;
    bg->flags.busy = 0;
    return bg;
}

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
            strcpy(file, "SCUS_971.13");
            chgFileName(file);
            r = sceCdDiskReady(1);
            if (r == 2 && sceCdGetDiskType() == 18 && sceCdSearchFile(&fp, file) != 0) {
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

/* The sync wait's drive check: a drive that still reports seeking (status
   18) after five syncs has failed the read; any other status starts the
   count again. */
static inline int cdSeekErrorCheck(int *cnt) /* derived name */
{
    int err = 0;
    int st;

    while ((st = sceCdStatus()) == -1) {
        cdWait(&err);
    }
    if (st == 18) {
        if ((*cnt)++ >= 5) {
            err = 1;
        }
    } else if (st != -1) {
        *cnt = 0;
    }
    return err;
}

int iosCdvdBackGroundRead(CdvdBgReq *self, void *buf, int size)
{
    int flag;
    int cnt = 0;

    debug_StdPrintfDummy("lsn %d cnt %d size %d buf %p %s\n", self->lsn, self->pos, size, buf,
                         self->name);
    bgReadCnt++;
    while (1) {
        flag = 0;
        while (sceCdRead(self->lsn + self->pos / 2048, size / 2048, buf, &bgReadMode) == 0) {
            cdWait(&flag);
        }
        while (sceCdSync(1) != 0) {
            if (cdSeekErrorCheck(&cnt) != 0) {
                flag = 1;
                break;
            }
            cdWait(&flag);
        }
        if (flag != 0) {
            bgReadRetryCnt++;
            while (sceCdBreak() == 0) {
                cdWait(&flag);
            }
        } else {
            if (sceCdGetError() != 0 && self->flags.noPause == 0) {
                while (sceCdBreak() == 0) {
                    cdWait(&flag);
                }
            } else {
                break;
            }
        }
        cdWait(&flag);
    }
    self->pos += size;
    return !(self->pos < self->size);
}

int iosCdvdBackGroundReadIOPm(CdvdBgReq *self, void *buf, int size)
{
    int flag;
    int cnt = 0;

    debug_StdPrintfDummy("lsn %d cnt %d size %d iopbuf %p %s\n", self->lsn, self->pos, size, buf,
                         self->name);
    bgReadCnt++;
    while (1) {
        flag = 0;
        while (sceCdReadIOPm(self->lsn + self->pos / 2048, size / 2048, buf, &bgReadMode) == 0) {
            cdWait(&flag);
        }
        while (sceCdSync(1) != 0) {
            if (cdSeekErrorCheck(&cnt) != 0) {
                flag = 1;
                break;
            }
            cdWait(&flag);
        }
        if (flag != 0) {
            bgReadRetryCnt++;
            while (sceCdBreak() == 0) {
                cdWait(&flag);
            }
        } else {
            if (sceCdGetError() != 0 && self->flags.noPause == 0) {
                while (sceCdBreak() == 0) {
                    cdWait(&flag);
                }
            } else {
                break;
            }
        }
        cdWait(&flag);
    }
    self->pos += size;
    return !(self->pos < self->size);
}

void iosCdvdDirectStOpen(IosCdvdHandle *self)
{
    char buf[256];
    char *name;
    int mem;

    name = strrchr(self->name, '/');
    if (name == 0) {
        name = self->name;
    } else {
        name = name + 1;
    }
    sprintf(buf, "DFDATAS/%s", name);
    strcpy(self->name, buf);
    chgFileName(self->name);
    self->mode.trycount = 0;
    self->mode.spindlctrl = 0;
    self->mode.datapattern = 0;
    self->readBytes = 0;
    iosCdvdDiskReadyBlock();
    self->result = 0;
    iosCdvdMgrSearchFile(self);
    self->sectors = ((unsigned int)(self->file.size - 1) >> 11) + 1;
    mem = iosSifAllocIopHeapDebug(576 * 2048 + 16, __FILE__, 2140);
    /* an allocation check compiled out of the retail build; its message
     * stays in .rodata */
    if (0) {
        debug_StdPrintfDummy("\nCan't alloc cd stream buff %d \n", 576 * 2048 + 16);
    }
    self->stMem = mem;
    self->stBuf = (mem + 15) & 0xFFFFFFF0;
    sceCdStInit(576, 36, (void *)((mem + 15) & 0xFFFFFFF0));
    sceCdStStart(self->file.lsn, &self->mode);
    self->stSize = self->file.size;
}

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

int iosCdvdGetFileLsn(char *name, int *size)
{
    return getFileLsn(name, size);
}

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
 * its total length at +0x138 minus the bytes already consumed at +0x24.  */
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
