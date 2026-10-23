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

/* The record sceCdSearchFile fills in: it writes 0x24 bytes of it (lsn, size,
 * the name column and the date), and the stack slot it is given is 0x30.  */
typedef struct sceCdlFILE {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int reserved;
} sceCdlFILE;

/* .data, all zero.  iosCdvd is the manager's cdvd handle (33216 bytes, as
   unifileHandle), the two queues take the 48-byte message queue record,
   iosCdvdSrhBuff is the 200-entry directory cache.  This build has no
   stream manager, so no acknowledge queue or request record follows them. */
/* the handle's 32 KB sector buffer at 0x180 is a DMA target, so the handle
   is 64-byte aligned (as jimaku's buffers are); that alignment is the
   48 bytes of fill before this TU's .data */
IosCdvdHandle iosCdvd __attribute__((aligned(64))) = {{0}};

IosMsgQueue CdvdMsgQ = {0};

IosMsgQueue CdvdMsgQ_LoadEnd = {0};

CdSrhEnt iosCdvdSrhBuff[200] = {0};

/* .sdata, the objects before the first string: the sleep flag, the
   directory cache count, the media mode (1, CD), the background read mode
   record (eight tries, normal spindle; a record, so 8-aligned) and the
   background drive state. */
int IosCdvdMgrSleep = 0;

static int srhBuffCnt = 0; /* derived name */

int iosCdvdMediaType = 1;

static CdRMode bgReadMode = {8, 1, 0}; /* derived name */

static int bgDriveState = 0; /* derived name */

/* bgReqTable the seven 300-byte background requests; skipBuf the 1 KB sink
   iosCdvdHandlerRead reads into when the caller passes no buffer. */
static CdvdBgReq bgReqTable[7]; /* derived name */

static unsigned char skipBuf[1024]; /* derived name */

/* cdvdMsgRing and cdvdLoadEndRing are the two-slot rings of the manager's
   request queue and its load-end queue, stPreLoadCnt the preloaded sector
   count iosCdvdMgrStStart hands the stream, bgRunning the background request
   iosCdvdBackGroundMgr is running. */
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

static void iosCdvdStManager(void);

/* Declared inline: the manager and the load paths expand it, and no
 * out-of-line body is written; its two strings come before getFileLsn's in
 * .rodata.  August waits on the USA product file and prints no names. */
static inline void iosCdvdDiskReadyBlock(void)
{
    if (sceCdDiskReady(1) != 2) {
        sceCdlFILE fp;
        char file[32];
        strcpy(file, "SCUS_971.13");
        iosCdvdChgFileName(file);
        debug_StdPrintfDummy("wait insert ico disk\n");
        do {
            sceCdDiskReady(0);
        } while (sceCdGetDiskType() != 18 ||
                 sceCdSearchFile(&fp, file) == 0); /* a PlayStation CD */
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
        if (sceCdSearchFile((sceCdlFILE *)&self->file, self->name) == 0) {
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

static void iosCdvdMgrStStart(IosCdvdHandle *self);

static void iosCdvdMgrStStop(IosCdvdHandle *self)
{
    self->result = 0;
    if (sceCdStStop() == 0) {
        self->result = sceCdGetError();
    }
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

INCLUDE_ASM(iosCdvdMgrLoad);

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
INCLUDE_ASM(iosCdvdMgrPackLoad);

static int iosCdStRead(unsigned int n, int *buf, int flag, int *result, char *self);

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

/* The 0x38 name column of a cdvd request is written 16 bytes at a time, so it
 * is typed as an 8-byte-aligned pair: the unifile request always loads the
 * fixed disc path "DFDATAS/DATA.DF", copied as two doublewords. */
typedef struct { /* field names derived */
    long long lo;
    long long hi;
} CdvdName16; /* derived name */

static void iosCdvdUnifileInfoGet(void);

int iosCdvdBackGroundMgrRunning = 0;

/* The cdvd manager thread, with iosCdvdDiskReadyBlock expanded in case 0.
   The reply buffer's block opens after the switch.  req is the request the
   switch dispatches on, held across case 0's calls; the default arm reads
   msg again.  The LoadEnd receivers never read the reply value. */
INCLUDE_ASM(iosCdvdManager);

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
   that it is saved, and inflateSec. */
static int cdWaitParamSet = 0; /* derived name */

static int cdWaitParamSave = 0; /* derived name */

float inflateSec = 0;

static void cdWait(int *busy);

INCLUDE_ASM(iosCdvdBackGroundMgr);

INCLUDE_ASM(iosCdvdDirectStOpen);

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

INCLUDE_ASM(iosCdvdBackGroundRead);

INCLUDE_ASM(iosCdvdBackGroundReadIOPm);

int iosCdvdBackGroundMgrGetRunning(void)
{
    return bgRunning;
}

void iosCdvdDirectStClose(IosCdvdHandle *self)
{
    int err;
    self->result = 0;
    err = sceCdStStop();
    if (err == 0) {
        self->result = sceCdGetError();
    }
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
