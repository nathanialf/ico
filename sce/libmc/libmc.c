/* libmc.a member libmc.o */
#include <stdio.h>
#include <eekernel.h>
#include <sifrpc.h>
#include <sifcmd.h>
#include <libmc.h>
#include <string.h>

/* R5900 opcodes with no C spelling.  Defined in this member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")
#define EI() __asm__ __volatile__(".word 0x42000038" : : : "memory")

typedef struct { /* field names derived */
    char f0[0x20];
    char name[0x20];
} AuxReq; /* derived name */

/* the request block of the calls that name a file: the card, the call's
   flags, the directory-entry count sceMcGetDir asks for, and the buffer the
   answer goes to */
typedef struct { /* field names derived */
    int port;
    int slot;
    int flags;
    int maxent;
    void *data;
    char name[0x400];
} NameReq; /* derived name */

/* The member's .data in link order: the build stamp, the number of the call
   in flight that sceMcSync completes, and the semaphore every entry point
   takes, -1 until sceMcInit creates it. */
static char sceMcVersion[16] = "PsIIlibmc   2240"; /* derived name */

static int mcFunc = 0; /* derived name */

static int mcSema = -1; /* derived name */

/* The member's .bss in link order, all file statics: the mcserv client
   record, the three answer pointers sceMcGetInfo leaves for its end
   callback, and the RPC buffers, each SIF buffer on its own 64-byte cache
   line. */
static sceSifRpcClientData mcClient __attribute__((aligned(64))); /* derived name */

static int *mcInfoType; /* derived name */

static int *mcInfoFree; /* derived name */

static int *mcInfoFormat; /* derived name */

static AuxReq mcAux __attribute__((aligned(64))); /* derived name */

static char mcCmd[0x30] __attribute__((aligned(64))); /* derived name */

static NameReq mcName; /* derived name */

static char mcRecv[0xC0] __attribute__((aligned(64))); /* derived name */

static char mcPwd[0x1000] __attribute__((aligned(64))); /* derived name */

static char mcRdata[0x40] __attribute__((aligned(64))); /* derived name */

int sceMcInit(void)
{
    struct SemaParam sema;
    sceSifRpcClientData *cd;
    sceSifRpcClientData *dev;
    int i;
    int r;

    if (mcSema < 0) {
        sema.initCount = 1;
        sema.maxCount = 1;
        sema.option = 0;
        mcSema = CreateSema(&sema);
    }
    sceMcSync(0, 0, 0);
    WaitSema(mcSema);
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&mcClient, 0x80000400, 0) < 0) {
            printf("bind error libmc \n");
            for (;;) {}
        }
        cd = &mcClient;
        if (cd->serve != 0) {
            break;
        }
        for (i = 0x100000; i != 0; i--) {}
    }
    dev = &mcClient;
    r = sceSifCallRpc(dev, 0xFE, 0, mcCmd, 0x30, mcRdata, 0xC, 0, 0);
    SignalSema(mcSema);
    if (r < 0) {
        dev->serve = 0;
        return r - 0x64;
    }
    if (((int *)mcRdata)[1] < 0x20A) {
        printf("libmc: too old release of mcserv.irx\n");
        dev->serve = 0;
        return -0x78;
    }
    if (((int *)mcRdata)[2] < 0x20E) {
        printf("libmc: too old release of mcman.irx\n");
        dev->serve = 0;
        return -0x79;
    }
    return *(int *)mcRdata;
}

/* The two answer words are stored as integers: typed as pointer stores, the
   mcSema load below moves above the first of them. */
void *_lmcGetClientPtr(int *rdata, int *func)
{
    rdata[0] = (int)mcRdata;
    func[0] = (int)&mcFunc;
    *(int *)(mcRdata + 0x3C) = mcSema;
    return &mcClient;
}

int sceMcChangeThreadPriority(int arg)
{
    sceSifRpcClientData *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    blk = mcCmd;
    *(int *)(blk + 0x14) = arg;
    r = sceSifCallRpc(dev, 0x14, 1, blk, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0x14;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcGetSlotMax(int arg)
{
    sceSifRpcClientData *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    blk = mcCmd;
    *(int *)(blk + 4) = arg;
    r = sceSifCallRpc(dev, 0x15, 0, blk, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        SignalSema(mcSema);
        return r;
    }
    SignalSema(mcSema);
    return *(int *)mcRdata;
}

int sceMcOpen(int port, int slot, char *name, int flags)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    strncpy(mcName.name, name, 0x3FF);
    mcName.port = port;
    mcName.flags = flags;
    mcName.slot = slot;
    mcName.name[0x3FF] = 0;
    r = sceSifCallRpc(dev, 2, 1, &mcName, 0x414, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 2;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcMkdir(int port, int slot, char *name)
{
    int ret = sceMcOpen(port, slot, name, 0x40);
    if (ret == 0) {
        mcFunc = 0xB;
    }
    return ret;
}

int sceMcClose(int arg)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    *(int *)mcCmd = arg;
    r = sceSifCallRpc(dev, 0x3, 1, mcCmd, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0x3;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcSeek(int fd, int offset, int origin)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    *(int *)mcCmd = fd;
    *(int *)(mcCmd + 0x10) = offset;
    *(int *)(mcCmd + 0x14) = origin;
    r = sceSifCallRpc(dev, 4, 1, mcCmd, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 4;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

typedef struct {   /* field names derived */
    int n0;        /* 0x00 */
    int n1;        /* 0x04 */
    char *d0;      /* 0x08 */
    char *d1;      /* 0x0C */
    char b0[0x40]; /* 0x10 */
    char b1[0x70]; /* 0x50 */
} FixAlign;        /* derived name */

void mceIntrReadFixAlign(void *arg)
{
    FixAlign *p;
    char *d;
    int i;

    p = (FixAlign *)((unsigned int)arg | 0x20000000);
    if (p->n0 != 0) {
        d = p->d0;
        for (i = 0; i < p->n0; i++) {
            *d++ = p->b0[i];
        }
    }
    if (p->n1 != 0) {
        d = p->d1;
        for (i = 0; i < p->n1; i++) {
            *d++ = p->b1[i];
        }
    }
}

/* the 0x30-byte RPC command block sceMcWrite sends: the unaligned head of
   the caller's buffer travels in the block itself, the 16-byte aligned rest
   by address. */
typedef struct {          /* field names derived */
    int fd;               /* 0x00 */
    int f4;               /* 0x04 */
    int f8;               /* 0x08 */
    int size;             /* 0x0C */
    int f10;              /* 0x10 */
    unsigned int headLen; /* 0x14 */
    void *addr;           /* 0x18 */
    void *recv;           /* 0x1C */
    char head[16];        /* 0x20 */
} McCmd;                  /* derived name */

int sceMcRead(int fd, void *buf, int len)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    *(int *)mcCmd = fd;
    ((McCmd *)mcCmd)->recv = mcRecv;
    ((McCmd *)mcCmd)->addr = buf;
    *(int *)(mcCmd + 0xC) = len;
    sceSifWriteBackDCache(buf, len);
    sceSifWriteBackDCache(mcRecv, 0xC0);
    r = sceSifCallRpc(dev, 5, 1, mcCmd, 0x30, mcRdata, 4, mceIntrReadFixAlign, mcRecv);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 5;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcWrite(int fd, void *buf, int len)
{
    sceSifRpcClientData *dev;
    int n;
    unsigned int i;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    ((McCmd *)mcCmd)->fd = fd;
    if (len < 0x11) {
        ((McCmd *)mcCmd)->headLen = len;
        ((McCmd *)mcCmd)->size = 0;
        ((McCmd *)mcCmd)->addr = 0;
    } else {
        n = (int)(((((unsigned int)buf - 1) & 0xFFFFFFF0) + 0x10) - (unsigned int)buf);
        ((McCmd *)mcCmd)->headLen = n;
        ((McCmd *)mcCmd)->size = len - n;
        ((McCmd *)mcCmd)->addr = (char *)buf + n;
    }
    for (i = 0; i < ((McCmd *)mcCmd)->headLen; i++) {
        ((McCmd *)mcCmd)->head[i] = ((char *)buf)[i];
    }
    FlushCache(0);
    r = sceSifCallRpc(&mcClient, 6, 1, mcCmd, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 6;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

void mcHearAlarm(int id, unsigned short time, void *arg)
{
    iWakeupThread((int)arg);
    SYNC();
    EI();
}

void mcDelayThread(int time)
{
    SetAlarm(time, mcHearAlarm, (void *)GetThreadId());
    SleepThread();
}

int sceMcSync(int mode, int *cmd, int *result)
{
    int r;
    if (mcFunc == 0) {
        return 0xFFFFFFFF;
    }
    r = sceSifCheckStatRpc(&mcClient);
    if (mode != 0)
        goto L050;
    if (r == 0)
        goto L050;
    while (sceSifCheckStatRpc(&mcClient) != 0) {
        mcDelayThread(0x3C);
    }
    r = 0;
L050:
    r = (r == 0);
    if (cmd != 0) {
        *cmd = mcFunc;
    }
    if (r != 0) {
        mcFunc = 0;
        if (result != 0) {
            *result = *(int *)mcRdata;
        }
        SignalSema(mcSema);
    }
    return r;
}

void mceGetInfoApdx(void *arg)
{
    int *info = (int *)((unsigned int)arg | 0x20000000);
    if (mcInfoType)
        *mcInfoType = info[0];
    if (mcInfoFree)
        *mcInfoFree = info[1];
    if (mcInfoFormat)
        *mcInfoFormat = info[36];
}

/* sceMcGetInfo's view of the same 0x30-byte command block: the card to ask,
   a flag per answer wanted, and the result buffer. */
typedef struct {    /* field names derived */
    int f0;         /* 0x00 */
    int port;       /* 0x04 */
    int slot;       /* 0x08 */
    int wantFormat; /* 0x0C */
    int wantFree;   /* 0x10 */
    int wantType;   /* 0x14 */
    int f18;        /* 0x18 */
    char *result;   /* 0x1C */
} McInfoCmd;        /* derived name */

int sceMcGetInfo(int port, int slot, int *type, int *free, int *format)
{
    sceSifRpcClientData *dev;
    int r;

    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    ((McInfoCmd *)mcCmd)->port = port;
    ((McInfoCmd *)mcCmd)->slot = slot;
    ((McInfoCmd *)mcCmd)->result = mcRecv;
    if (type != 0) {
        ((McInfoCmd *)mcCmd)->wantType = 1;
    } else {
        ((McInfoCmd *)mcCmd)->wantType = 0;
    }
    if (free != 0) {
        ((McInfoCmd *)mcCmd)->wantFree = 1;
    } else {
        ((McInfoCmd *)mcCmd)->wantFree = 0;
    }
    if (format != 0) {
        ((McInfoCmd *)mcCmd)->wantFormat = 1;
    } else {
        ((McInfoCmd *)mcCmd)->wantFormat = 0;
    }
    mcInfoType = type;
    mcInfoFree = free;
    mcInfoFormat = format;
    sceSifWriteBackDCache(mcRecv, 0xC0);
    r = sceSifCallRpc(&mcClient, 1, 1, mcCmd, 0x30, mcRdata, 4, mceGetInfoApdx, mcRecv);
    if (r == 0) {
        mcFunc = 1;
    } else {
        SignalSema(mcSema);
    }
    return r;
}

int sceMcGetDir(int port, int slot, char *name, int flags, int nblk, struct sceMcTblGetDir *table)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    mcName.port = port;
    mcName.slot = slot;
    mcName.flags = flags;
    mcName.maxent = nblk;
    mcName.data = table;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    if (nblk >= 0) {
        sceSifWriteBackDCache(table, nblk * 64);
    }
    r = sceSifCallRpc(dev, 0xD, 1, &mcName, 0x414, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0xD;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

void mceStorePwd(void *arg)
{
    char *pwd = arg;
    int n;
    if (pwd != 0) {
        if ((unsigned int)strlen((char *)((int)mcPwd | 0x20000000)) < 0x400) {
            n = strlen((char *)((int)mcPwd | 0x20000000));
        } else {
            n = 0x3FF;
        }
        memcpy(pwd, (char *)((int)mcPwd | 0x20000000), n);
        pwd[n] = 0;
    }
}

int sceMcChdir(int port, int slot, char *name, char *pwd)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    mcName.port = port;
    mcName.data = mcPwd;
    mcName.slot = slot;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    sceSifWriteBackDCache(mcPwd, 0x400);
    r = sceSifCallRpc(dev, 0xC, 1, &mcName, 0x414, mcRdata, 4, mceStorePwd, pwd);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0xC;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcFormat(int port, int slot)
{
    sceSifRpcClientData *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    blk = mcCmd;
    *(int *)(blk + 4) = port;
    *(int *)(blk + 8) = slot;
    r = sceSifCallRpc(dev, 0x10, 1, blk, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0x10;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcDelete(int port, int slot, char *name)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    strncpy(mcName.name, name, 0x3FF);
    mcName.port = port;
    mcName.slot = slot;
    mcName.name[0x3FF] = 0;
    mcName.flags = 0;
    r = sceSifCallRpc(dev, 0xF, 1, &mcName, 0x414, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0xF;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcFlush(int arg)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    *(int *)mcCmd = arg;
    r = sceSifCallRpc(dev, 0xA, 1, mcCmd, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0xA;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcSetFileInfo(int port, int slot, char *name, void *src, int flags)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    flags &= 7;
    mcName.port = port;
    mcName.slot = slot;
    mcName.flags = flags;
    mcAux = *(AuxReq *)src;
    mcName.data = &mcAux;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    FlushCache(0);
    r = sceSifCallRpc(dev, 0xE, 1, &mcName, 0x414, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0xE;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcRename(int port, int slot, char *name, char *newname)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name == 0) {
        goto badname;
    }
    if (newname != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    mcName.port = port;
    mcName.slot = slot;
    mcName.flags = 0x10;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    strncpy(mcAux.name, newname, 0x20);
    mcAux.name[0x1F] = 0;
    mcName.data = &mcAux;
    FlushCache(0);
    r = sceSifCallRpc(dev, 0xE, 1, &mcName, 0x414, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0x13;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcUnformat(int port, int slot)
{
    sceSifRpcClientData *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    blk = mcCmd;
    *(int *)(blk + 4) = port;
    *(int *)(blk + 8) = slot;
    r = sceSifCallRpc(dev, 0x11, 1, blk, 0x30, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0x11;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}

int sceMcGetEntSpace(int port, int slot, char *name)
{
    sceSifRpcClientData *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = &mcClient;
    if (dev->serve == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    SignalSema(mcSema);
    return -0xD2;
ok:
    mcName.port = port;
    mcName.slot = slot;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    r = sceSifCallRpc(dev, 0x12, 1, &mcName, 0x414, mcRdata, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    mcFunc = 0x12;
    goto done;
unlock:
    SignalSema(mcSema);
done:
    return r;
}
