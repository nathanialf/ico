#include "debug.h"
#include "s_init.h"
#include "pad.h"
#include "main.h"
#include "mcdata.h"
#include <string.h>
#include "mcard.h"
#include <eekernel.h>
#include <libmc.h>
#include <stdlib.h>
#include <stdio.h>
#include "message.h"
#include "typedef.h"
#include "include_asm.h"

/* the semaphore descriptor the card lock is created from, then the manager
   queue's 16-slot message ring */
static struct SemaParam mcLockSemaParam;

static int mcMsgRing[16]; /* derived name */

/* .data: the three icon file names, the save segment names, then after the
   block handlers the segment table, the two product records, the preview
   record and the manager's queue.
   .sdata: the two words, the "game." name (emitted with the segment names,
   last first, as are the two longer ones in .rodata), the lock count, then
   the literals in first-use order. */
int IosMcMgrSleep = 0;

int IosMcLock = -1;

char *iconName[3] = {"boy_blk.ico", "boy_blk.ico", "boy_blk.ico"};

char *iOSMcSaveSeg[6] = {"BESCES-50760ico", "icon.sys",    "boy_blk.ico",
                         "boy_blk.ico",     "boy_blk.ico", "game."};

static int mcLockCount = 0; /* derived name */

inline void iosMcMgrSync(McMgr *mp);

typedef struct { /* field names derived */
    char b[64];
} McBlk; /* derived name */

static inline int product_write(McMgr *self);
static inline int product_read(McMgr *self);
static inline int gameblock_write(McMgr *self, void *buf);
static inline int gameblock_read(McMgr *self, void *buf);

/* the product directory name, 17 bytes including the terminator, copied as
   a byte-aligned record */
typedef struct { /* field names derived */
    char c[17];
} McName; /* derived name */

static void iosMcMgrGetInfo(McMgr *mp);

/* the file-static card helpers the manager entry points inline */
static inline void iosMcMgrFormat(McMgr *mp) /* derived name */
{
    while (sceMcFormat(mp->port, mp->slot) > 0) {
        debug_StdPrintfDummy("iosMcMgrFormat: request busy\n");
    }

    iosMcMgrSync(mp);

    if (mp->result == 0) {
        mp->cardState = -1;
    }
}

static inline void iosMcMgrUnformat(McMgr *mp) /* derived name */
{
    while (sceMcUnformat(mp->port, mp->slot) > 0) {
        debug_StdPrintfDummy("iosMcMgrUnformat: request busy\n");
    }

    iosMcMgrSync(mp);

    if (mp->result == 0) {
        mp->cardState = -2;
    }
}

static inline void iosMcMgrWrite(McMgr *mp, void *p) /* derived name */
{
    while (sceMcWrite(mp->fd, p, mp->size) > 0) {
        debug_StdPrintfDummy("iosMcMgrWrite: request busy\n");
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrRead(McMgr *mp, void *p) /* derived name */
{
    while (sceMcRead(mp->fd, p, mp->size) > 0) {
        debug_StdPrintfDummy("iosMcMgrRead: request busy\n");
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrOpen(McMgr *mp) /* derived name */
{
    while (sceMcOpen(mp->port, mp->slot, mp->path, mp->openMode) > 0) {
        debug_StdPrintfDummy("sceMcOpen: request busy\n");
    }

    iosMcMgrSync(mp);

    if (mp->result < 0) {
        return;
    }

    mp->fd = mp->result;
    mp->sum = 0;
    mp->end = 0;
    mp->pos = 0;
}

static inline void iosMcMgrClose(McMgr *mp) /* derived name */
{
    while (sceMcClose(mp->fd) > 0) {
        debug_StdPrintfDummy("sceMcClose: request busy\n");
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrChdir(McMgr *mp) /* derived name */
{
    while (sceMcChdir(mp->port, mp->slot, mp->dirName, mp->pwd) > 0) {
        debug_StdPrintfDummy("iosMcMgrChdir: request busy\n");
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrGetDir(McMgr *mp) /* derived name */
{
    while (sceMcGetDir(mp->port, mp->slot, mp->path, 0, 20, mp->dir) > 0) {
        debug_StdPrintfDummy("sceMcGetdir: request busy\n");
    }

    iosMcMgrSync(mp);

    if (mp->result < 0) {
        mp->dirCount = 0;
    } else {
        mp->dirCount = mp->result;
    }
}

static inline void iosMcMgrMkdir(McMgr *mp) /* derived name */
{
    while (sceMcMkdir(mp->port, mp->slot, mp->path) > 0) {
        debug_StdPrintfDummy("iosMcMgrMkdir: request busy\n");
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrDelete(McMgr *mp) /* derived name */
{
    while (sceMcDelete(mp->port, mp->slot, mp->path) > 0) {
        debug_StdPrintfDummy("iosMcMgrDelete: request busy\n");
    }

    iosMcMgrSync(mp);
}

static inline void iosMcMgrSum(McMgr *mp, void *q, int n) /* derived name */
{
    unsigned char *p = q;
    int i;

    for (i = 0; i < n; i++) {
        mp->sum += p[i];
    }
}

INCLUDE_ASM(iosMcHandlerWrite);

INCLUDE_ASM(iosMcHandlerRead);

static void iosMcMgrChdirProduct(McMgr *mp);

INCLUDE_ASM(iosMcMgrChdirProduct);

/* the per-slot segment table: one record per loadable block */
typedef struct {   /* field names derived */
    int id;        /* 0x0 */
    int (*load)(); /* 0x4 */
    int (*save)(); /* 0x8 */
} McSegEnt;        /* derived name */

/* mcdata.c's icon writers */

McSegEnt iOSMcSaveList[6] = {
    {1, 0, iosMcIconWriteIconsys},    {2, 0, iosMcIconWriteIcon},
    {3, 0, iosMcIconWriteIcon},       {4, 0, iosMcIconWriteIcon},
    {0, product_read, product_write}, {5, gameblock_read, gameblock_write},
};

McProductFile IosMcProductFile[2] = {0};

int IosMcPreviewInfo[6] = {0};

IosMsgQueue McMsgQ = {0};

static void iosMcMgrSaveSeg(McMgr *mp, char *suffix);

INCLUDE_ASM(iosMcMgrSaveSeg);

static void iosMcMgrLoadSeg(McMgr *mp, char *suffix);

INCLUDE_ASM(iosMcMgrLoadSeg);

/* the three file-static block helpers the manager dispatch inlines.  The icon
   save ends with a DEBUG-build report of the card result. */
static __inline__ void iosMcMgrSaveIconDebugResult(int result) /* derived name */
{
#ifdef DEBUG
    debug_StdPrintfDummy("icon save result %d\n", result);
#endif
}

static inline void iosMcMgrSaveIcon(McMgr *mp) /* derived name */
{
    mp->segment = 1;
    mp->segArg = &iconFile[1];
    iosMcMgrSaveSeg(mp, 0);

    if (mp->result < 0) {
        return;
    }

    mp->segment = 2;
    mp->segArg = &iconFile[2];
    iosMcMgrSaveSeg(mp, 0);
    iosMcMgrSaveIconDebugResult(mp->result);
}

INCLUDE_ASM(iosMcMgrSaveProductBlock);

INCLUDE_ASM(iosMcMgrLoadProductBlock);

static inline void iosMcMgrSaveGame(McMgr *mp) /* derived name */
{
    char buf[16];

    sprintf(buf, "%3.3d", mp->fileNo);
    mp->segment = 5;
    iosMcMgrSaveSeg(mp, buf);
}

static inline void iosMcMgrLoadGame(McMgr *mp) /* derived name */
{
    char buf[16];

    sprintf(buf, "%3.3d", mp->fileNo);
    mp->segment = 5;
    iosMcMgrLoadSeg(mp, buf);
}

INCLUDE_ASM(iosMcMgrGetBlockSaveInfo);

INCLUDE_ASM(iosMcManager);

INCLUDE_ASM(iosMcMgrSync);

INCLUDE_ASM(iosMcTest);

INCLUDE_ASM(iosMcSync);

INCLUDE_ASM(iosMcGetInfo);

INCLUDE_ASM(iosMcFormat);

INCLUDE_ASM(iosMcUnformat);

INCLUDE_ASM(iosMcGetDir);

INCLUDE_ASM(iosMcDelete);

INCLUDE_ASM(iosMcSaveIconBlock);

INCLUDE_ASM(iosMcSaveProductBlock);

INCLUDE_ASM(iosMcLoadProductBlock);

INCLUDE_ASM(iosMcSaveGameBlock);

INCLUDE_ASM(iosMcLoadGameBlock);

INCLUDE_ASM(iosMcChdirProduct);

INCLUDE_ASM(iosMcGetBlockSaveInfo);

INCLUDE_ASM(product_write);

INCLUDE_ASM(product_read);

INCLUDE_ASM(gameblock_write);

INCLUDE_ASM(gameblock_read);
