/* libmc.a member libmc.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <sifrpc.h>
#include <libmc.h>
#include <string.h>

/* R5900 opcodes with no C spelling.  This member's uses stand for a
   Sony-internal header this tree cannot name: MAIN.MAP attests archives and
   their members, never a header, so the definition is kept per member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")
#define EI() __asm__ __volatile__(".word 0x42000038" : : : "memory")

typedef struct {
    char f0[0x20];
    char name[0x20];
} AuxReq;

typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    char name[0x400];
} NameReq;

typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    unsigned int attr;
    unsigned int option;
} SemaParam;

/* The member's .data in the ROM's order (VMA 0x54C000..0x54C018): the build
   stamp, the number of the call in flight that sceMcSync completes, and the
   semaphore every entry point takes, -1 until sceMcInit creates it. */
static char sceMcVersion[16] = "PsIIlibmc   2240";

static int mcFunc = 0;

static int mcSema = -1;

/* The member's .bss in the ROM's order (VMA 0x72F5C0..0x730BC0), all file
   statics: the mcserv client record, the three answer pointers sceMcGetInfo
   leaves for its end callback, and the RPC buffers, each SIF buffer on its
   own 64-byte cache line. */
static char mcClient[0x28] __attribute__((aligned(64)));

static int *mcInfoType;

static int *mcInfoFree;

static int *mcInfoFormat;

static AuxReq mcAux __attribute__((aligned(64)));

static char mcCmd[0x30] __attribute__((aligned(64)));

static NameReq mcName;

static char mcRecv[0xC0] __attribute__((aligned(64)));

static char mcPwd[0x1000] __attribute__((aligned(64)));

static char mcRdata[0x40] __attribute__((aligned(64)));

extern int CreateSema(SemaParam *param);
extern int WaitSema(int sema);
extern void SignalSema(int sema);
extern int sceMcSync();
extern int printf(const char *fmt, ...);

int sceMcInit(void)
{
    SemaParam sema;
    char *cd;
    char *dev;
    int i;
    int r;

    if (mcSema < 0) {
        sema.init_count = 1;
        sema.max_count = 1;
        sema.option = 0;
        mcSema = CreateSema(&sema);
    }
    sceMcSync(0, 0, 0);
    WaitSema(mcSema);
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(mcClient, 0x80000400, 0) < 0) {
            printf("bind error libmc \n");
            for (;;) {}
        }
        cd = mcClient;
        if (*(int *)(cd + 0x24) != 0) {
            break;
        }
        for (i = 0x100000; i != 0; i--) {}
    }
    dev = mcClient;
    r = sceSifCallRpc(dev, 0xFE, 0, mcCmd, 0x30, mcRdata, 0xC, 0, 0);
    SignalSema(mcSema);
    if (r < 0) {
        *(int *)(dev + 0x24) = 0;
        return r - 0x64;
    }
    if (((int *)mcRdata)[1] < 0x20A) {
        printf("libmc: too old release of mcserv.irx\n");
        *(int *)(dev + 0x24) = 0;
        return -0x78;
    }
    if (((int *)mcRdata)[2] < 0x20E) {
        printf("libmc: too old release of mcman.irx\n");
        *(int *)(dev + 0x24) = 0;
        return -0x79;
    }
    return *(int *)mcRdata;
}

void *_lmcGetClientPtr(int *a0, int *a1)
{
    a0[0] = (int)mcRdata;
    a1[0] = (int)&mcFunc;
    *(int *)(mcRdata + 0x3C) = mcSema;
    return mcClient;
}

extern int PollSema(int sema);

int sceMcChangeThreadPriority(int arg)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    char *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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

int sceMcOpen(int a0, int a1, char *name, int flags)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f8 = flags;
    mcName.f4 = a1;
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

int sceMcMkdir(int a0, int a1, char *name)
{
    int ret = sceMcOpen(a0, a1, name, 0x40);
    if (ret == 0) {
        mcFunc = 0xB;
    }
    return ret;
}

int sceMcClose(int arg)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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

int sceMcSeek(int a0, int a1, int a2)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    *(int *)mcCmd = a0;
    *(int *)(mcCmd + 0x10) = a1;
    *(int *)(mcCmd + 0x14) = a2;
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

typedef struct {
    int n0;        /* 0x00 */
    int n1;        /* 0x04 */
    char *d0;      /* 0x08 */
    char *d1;      /* 0x0C */
    char b0[0x40]; /* 0x10 */
    char b1[0x70]; /* 0x50 */
} FixAlign;

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

extern void mceIntrReadFixAlign();

int sceMcRead(int a0, void *buf, int len)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    *(int *)mcCmd = a0;
    *(int *)(mcCmd + 0x1C) = (int)mcRecv;
    *(int *)(mcCmd + 0x18) = (int)buf;
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

extern void FlushCache(int a0);

/* RECONSTRUCTION: the 0x30-byte RPC command block sceMcWrite sends, as the
   ROM's offsets use it: the unaligned head of the caller's buffer travels in
   the block itself, the 16-byte aligned rest by address. */
typedef struct {
    int fd;               /* 0x00 */
    int f4;               /* 0x04 */
    int f8;               /* 0x08 */
    int size;             /* 0x0C */
    int f10;              /* 0x10 */
    unsigned int headLen; /* 0x14 */
    void *addr;           /* 0x18 */
    int f1C;              /* 0x1C */
    char head[16];        /* 0x20 */
} McCmd;

int sceMcWrite(int fd, void *buf, int len)
{
    char *dev;
    int n;
    unsigned int i;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    r = sceSifCallRpc(mcClient, 6, 1, mcCmd, 0x30, mcRdata, 4, 0, 0);
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

extern void iWakeupThread(int a0);

void mcHearAlarm(int a0, int a1, int a2)
{
    iWakeupThread(a2);
    SYNC();
    EI();
}

extern int GetThreadId(void);
extern void SetAlarm(int a0, void *a1, int a2);
extern void SleepThread(void);

void mcDelayThread(int a0)
{
    SetAlarm((unsigned short)a0, mcHearAlarm, GetThreadId());
    SleepThread();
}

extern void SignalSema(int sema);
extern void mcDelayThread(int a0);

int sceMcSync(int a0, int *a1, int *a2)
{
    int r;
    if (mcFunc == 0) {
        return 0xFFFFFFFF;
    }
    r = sceSifCheckStatRpc(mcClient);
    if (a0 != 0)
        goto L050;
    if (r == 0)
        goto L050;
    while (sceSifCheckStatRpc(mcClient) != 0) {
        mcDelayThread(0x3C);
    }
    r = 0;
L050:
    r = (r == 0);
    if (a1 != 0) {
        *a1 = mcFunc;
    }
    if (r != 0) {
        mcFunc = 0;
        if (a2 != 0) {
            *a2 = *(int *)mcRdata;
        }
        SignalSema(mcSema);
    }
    return r;
}

void mceGetInfoApdx(int a0)
{
    a0 |= 0x20000000;
    if (mcInfoType)
        *mcInfoType = *(int *)a0;
    if (mcInfoFree)
        *mcInfoFree = *(int *)(a0 + 4);
    if (mcInfoFormat)
        *mcInfoFormat = *(int *)(a0 + 0x90);
}

/* RECONSTRUCTION: sceMcGetInfo's view of the same 0x30-byte command block:
   the card to ask, a flag per answer wanted, and the result buffer. */
typedef struct {
    int f0;         /* 0x00 */
    int port;       /* 0x04 */
    int slot;       /* 0x08 */
    int wantFormat; /* 0x0C */
    int wantFree;   /* 0x10 */
    int wantType;   /* 0x14 */
    int f18;        /* 0x18 */
    char *result;   /* 0x1C */
} McInfoCmd;

int sceMcGetInfo(int port, int slot, int *type, int *free, int *format)
{
    char *dev;
    int r;

    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    r = sceSifCallRpc(mcClient, 1, 1, mcCmd, 0x30, mcRdata, 4, mceGetInfoApdx, mcRecv);
    if (r == 0) {
        mcFunc = 1;
    } else {
        SignalSema(mcSema);
    }
    return r;
}

int sceMcGetDir(int a0, int a1, char *name, int a3, int nblk, void *buf)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f4 = a1;
    mcName.f8 = a3;
    mcName.fC = nblk;
    mcName.f10 = (int)buf;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    if (nblk >= 0) {
        sceSifWriteBackDCache(buf, nblk * 64);
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

void mceStorePwd(char *a0)
{
    int n;
    if (a0 != 0) {
        if ((unsigned int)strlen((char *)((int)mcPwd | 0x20000000)) < 0x400) {
            n = strlen((char *)((int)mcPwd | 0x20000000));
        } else {
            n = 0x3FF;
        }
        memcpy(a0, (char *)((int)mcPwd | 0x20000000), n);
        a0[n] = 0;
    }
}

int sceMcChdir(int a0, int a1, char *name, char *pwd)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f10 = (int)mcPwd;
    mcName.f4 = a1;
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

int sceMcFormat(int a0, int a1)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    blk = mcCmd;
    *(int *)(blk + 4) = a0;
    *(int *)(blk + 8) = a1;
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

int sceMcDelete(int a0, int a1, char *name)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f4 = a1;
    mcName.name[0x3FF] = 0;
    mcName.f8 = 0;
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
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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

int sceMcSetFileInfo(int a0, int a1, char *name, void *src, int flags)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f4 = a1;
    mcName.f8 = flags;
    mcAux = *(AuxReq *)src;
    mcName.f10 = (int)&mcAux;
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

int sceMcRename(int a0, int a1, char *name, char *newname)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f4 = a1;
    mcName.f8 = 0x10;
    strncpy(mcName.name, name, 0x3FF);
    mcName.name[0x3FF] = 0;
    strncpy(mcAux.name, newname, 0x20);
    mcAux.name[0x1F] = 0;
    mcName.f10 = (int)&mcAux;
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

int sceMcUnformat(int a0, int a1)
{
    char *dev;
    char *blk;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
        SignalSema(mcSema);
        return -0x64;
    }
    blk = mcCmd;
    *(int *)(blk + 4) = a0;
    *(int *)(blk + 8) = a1;
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

int sceMcGetEntSpace(int a0, int a1, char *name)
{
    char *dev;
    int r;
    if (PollSema(mcSema) < 0) {
        return -0xC8;
    }
    dev = mcClient;
    if (*(int *)(dev + 0x24) == 0) {
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
    mcName.f0 = a0;
    mcName.f4 = a1;
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
