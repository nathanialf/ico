/* libkernl.a(filestub.o) */

#include <eekernel.h>
#include <sifrpc.h>
#include <string.h>
#include <libkernl_internal.h>
#include <sifcmd.h>

/* filestub.o's .data, in link order.  _sceFs_q is the async request slot
   table _sceFs_Rcv_Intr matches a reply against, read and written under
   q_sema; an entry of -1 is free.  The table is written by the SIF receive
   interrupt, so every access to it is volatile.  Then whether sceFsInit has
   bound the server, the FS call semaphore, the iob table's semaphore and the
   slot table's guard semaphore (each -1 until created).  The last word,
   _fs_version's stamp, is defined beside its one user below. */

volatile int _sceFs_q[32] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

static int fs_inited = 0; /* derived name */

static int fs_sema = -1; /* derived name */

static int iob_sema = -1; /* derived name */

static int q_sema = -1; /* derived name */

/* the member's .bss: the ioctl caller's argument pointer, the 64-aligned RPC
   send buffer, receive buffer and reply packet the IOP writes (the handler
   reads the words at +0x10 and +0x14 of it), the iob table, the RPC client,
   the IOP module's version stamp and the command handler's buffer */
static void *fsIoctlArg; /* derived name */

static int fsSendBuf[0x310] __attribute__((aligned(64))); /* derived name */

static int fsRecvBuf[16] __attribute__((aligned(64))); /* derived name */

static char fsRcvPkt[0x440] __attribute__((aligned(64))); /* derived name */

static char fsIobTab[0x200]; /* derived name */

static int fsClient[10]; /* derived name */

static char fsVersion[4]; /* derived name */

static char fsCmdBuf[0x40]; /* derived name */

void _sceFsIobSemaMK(void)
{
    struct SemaParam args;
    if (iob_sema == -1) {
        args.option = 0;
        args.initCount = 1;
        args.maxCount = 1;
        iob_sema = CreateSema(&args);
        q_sema = CreateSema(&args);
    }
}

int new_iob(void)
{
    char *p;
    char *end;
    _sceFsIobSemaMK();
    WaitSema(iob_sema);
    p = fsIobTab;
    end = p + 0x200;
    while (p < end) {
        if (*(int *)(p + 4) == 0) {
            *(int *)(p + 4) = 0x10000000;
            SignalSema(iob_sema);
            return (int)p;
        }
        p += 0x10;
    }
    SignalSema(iob_sema);
    return 0;
}

void *get_iob(unsigned int i)
{
    char *p;
    _sceFsIobSemaMK();
    WaitSema(iob_sema);
    if (i < 0x20) {
        goto ok;
    }
    SignalSema(iob_sema);
    return 0;
ok:
    p = &fsIobTab[i * 16];
    SignalSema(iob_sema);
    return p;
}

/* The four-byte filesystem version stamp the IOP hands back
   in the RPC receive buffer; _fs_version() memcmps it against the two
   built-in stamps. */
typedef struct {
    char v[4];
} SceFsVersion;

/* the FS reply packet the IOP leaves in fsRcvPkt; the handler reads it
   through the uncached accelerated window, so every record copy below is a
   byte-array assignment and gcc expands each one inline with the unaligned
   pairs the window forces. */
/* the readdir reply record and the 0x40-byte stat record */
typedef struct {
    char v[0x144];
} SceFsDirent;

typedef struct {
    char v[0x40];
} SceFsStatRec;

/* The SIF command handler for the FS reply.  Each reply word is its own
   local (the header's request id, command, buffer and size, then a
   command's destination and length), filled by a four-byte record copy
   through the uncached window. */
void _sceFs_Rcv_Intr(void)
{
    int id;
    int cmd;
    int buf;
    int size;
    int addr;
    int len;
    int *q;
    int i;
    int k;

    *(SceFsVersion *)&id = *(SceFsVersion *)((int)(fsRcvPkt + 0x0) | 0x20000000);
    *(SceFsVersion *)&cmd = *(SceFsVersion *)((int)(fsRcvPkt + 0x4) | 0x20000000);
    *(SceFsVersion *)&buf = *(SceFsVersion *)((int)(fsRcvPkt + 0x8) | 0x20000000);
    *(SceFsVersion *)&size = *(SceFsVersion *)((int)(fsRcvPkt + 0xC) | 0x20000000);
    memcpy((void *)buf, (void *)((int)(fsRcvPkt + 0x10) | 0x20000000), size);
    switch (cmd) {
    case 2:
        q = (int *)((int)(fsRcvPkt + 0x14) | 0x20000000);
        if (q[0] > 0) {
            char *dst = (char *)q[2];

            for (i = 0; i < q[0]; i++) {
                char *src = (char *)q + 0x10;

                dst[i] = src[i];
            }
        }
        if (q[1] > 0) {
            char *dst = (char *)q[3];

            for (i = 0; i < q[1]; i++) {
                char *src = (char *)q + 0x50;

                dst[i] = src[i];
            }
        }
        break;
    case 11:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((int)(fsRcvPkt + 0x14) | 0x20000000);
        *(SceFsDirent *)addr = *(SceFsDirent *)((int)((fsRcvPkt + 0x14) + 4) | 0x20000000);
        break;
    case 12:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((int)(fsRcvPkt + 0x14) | 0x20000000);
        *(SceFsStatRec *)addr = *(SceFsStatRec *)((int)((fsRcvPkt + 0x14) + 4) | 0x20000000);
        break;
    case 23:
    case 25:
    case 26:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((int)(fsRcvPkt + 0x14) | 0x20000000);
        *(SceFsVersion *)&len = *(SceFsVersion *)((int)((fsRcvPkt + 0x14) + 4) | 0x20000000);
        k = len;
        if (1024 < (unsigned int)k) {
            len = 1024;
            k = 1024;
        }
        memcpy((void *)addr, (void *)((int)((fsRcvPkt + 0x14) + 8) | 0x20000000), k);
        break;
    }
    if (id < 0) {
        id = -id;
        for (i = 0; i < 32; i++) {
            if (_sceFs_q[i] == id) {
                _sceFs_q[i] = -1;
                break;
            }
        }
    } else {
        iSignalSema(id);
    }
}

void _sceFsSemInit(void)
{
    struct SemaParam self;
    if (fs_sema == -1) {
        self.initCount = 1;
        self.maxCount = 1;
        self.option = 0;
        fs_sema = CreateSema(&self);
    }
}

int _sceFsWaitS(int arg)
{
    _sceFsSemInit();
    WaitSema(fs_sema);
    return 0;
}

void _sceFsSigSema(void)
{
    SignalSema(fs_sema);
}

int sceFsInit(void)
{
    char *p;
    char *end;
    int i;
    int buf[1];

    sceSifInitRpc(0);
    DIntr();
    sceSifAddCmdHandler(0x80000011, (int)_sceFs_Rcv_Intr, (int)fsCmdBuf);
    EIntr();
    for (;;) {
        if (sceSifBindRpc(fsClient, 0x80000001, 0) < 0) {
            return -1;
        }
        if (fsClient[9] != 0) {
            break;
        }
        for (i = 0x100000; i != -1; i--) {
            ;
        }
    }
    _sceFsIobSemaMK();
    WaitSema(iob_sema);
    p = fsIobTab;
    end = fsIobTab + 0x200;
    while (p < end) {
        ((int *)p)[1] = 0;
        p += 0x10;
    }
    SignalSema(iob_sema);
    buf[0] = (int)fsRcvPkt;
    if (sceSifCallRpc(fsClient, 0xFF, 0, buf, 4, fsRecvBuf, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    *(SceFsVersion *)fsVersion = *(SceFsVersion *)((int)fsRecvBuf | 0x20000000);
    fs_inited = 1;
    return 0;
}

/* the stamp _fs_version accepts besides the library's own.  Defined here,
   after _sceFs_Rcv_Intr, its four dots follow that function's jump table in
   the member's .rodata, and the pointer is still the member's last .data
   word. */
static char *fs_stamp = "...."; /* derived name */

int _fs_version(void)
{
    char *s3 = __ps2_klibinfo__ + 12;
    char *s1 = fsVersion;
    int s2 = 0;
    int v0;
    v0 = memcmp(s1, s3, 4);
    if (v0 == 0)
        goto done;
    v0 = memcmp(s1, fs_stamp, 4);
    if (v0 == 0)
        goto done;
    v0 = memcmp(s3, fs_stamp, 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}

int sceFsReset(void)
{
    fs_inited = 0;
    memset(fsVersion, 0, 4);
    return 0;
}

/* The 16-byte file-descriptor record new_iob() hands out of
   the fsIobTab table; field 0 is the driver handle _sceCallCode returns and
   field 4 the in-use flag new_iob() sets to 0x10000000. */
typedef struct {
    int fd;
    int inuse;
    int _8[2];
} SceIob;

/* Varargs: the mode is the first anonymous argument, read after the
   new_iob() check.  One status local, rc, carries the RPC result, the
   uncached reply word and the returned index, the way sceLseek keeps its
   own.  The descriptor is stored before the in-use flag is or-ed. */
int sceOpen(unsigned char *name, int flags, ...)
{
    int *g = fsSendBuf;
    int mode;
    SceIob *iob;
    int i;
    int idx;
    int h;
    int rc;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0);
    if (fs_inited == 0)
        sceFsInit();
    if (_fs_version() != 0) {
        _sceFsSigSema();
        return 0xFFFEFFFC;
    }
    iob = (SceIob *)new_iob();
    if (iob == 0) {
        _sceFsSigSema();
        return -0x13;
    }
    mode = *(int *)((char *)__builtin_next_arg(flags) - 0x30);
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x14) = name[i];
        if (*((char *)g + i + 0x14) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x413] = 0;
    }
    idx = iob - (SceIob *)fsIobTab;
    g[3] = flags & 0xFFFFFFF;
    g[4] = mode;
    g[0x414 / 4] = idx;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0, 0, fsSendBuf, 0x418, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    rc = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (rc == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        WaitSema(iob_sema);
        iob->inuse = 0;
        SignalSema(iob_sema);
        return result;
    }
    rc = idx;
    WaitSema(iob_sema);
    iob->fd = result;
    iob->inuse |= flags;
    SignalSema(iob_sema);
    return rc;
}

int sceClose(unsigned int fd)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int f0;
    int uv;
    int h;
    int rc;
    int result;
    struct SemaParam buf;

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(1);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (iob == 0 || iob->inuse == 0) {
        _sceFsSigSema();
        return -9;
    }
    f0 = iob->fd;
    g[3] = f0;
    g[4] = iob - (SceIob *)fsIobTab;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    fsSendBuf[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 1, 0, g, 0x14, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    iob->inuse = 0;
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        return result;
    }
    return 0;
}

/* whether a descriptor was opened with the no-wait flag (0x8000, SCE_NOWAIT
   in the public SDK naming), read from the open-mode half of the
   descriptor's in-use word.  The name is ours. */
static inline int isNowait(unsigned short mode)
{
    return mode & 0x8000;
}

int sceLseek(unsigned int fd, int offset, int whence)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int inuse;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(4);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _sceFsSigSema();
        return -9;
    }
    g[3] = iob->fd;
    g[4] = offset;
    g[5] = whence;
    g[6] = iob - (SceIob *)fsIobTab;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    fsSendBuf[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    if (inuse & 0x8000) {
        WaitSema(q_sema);
        for (i = 0; i < 0x20; i++) {
            if (_sceFs_q[i] == -1) {
                _sceFs_q[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(q_sema);
    }
    rc = sceSifCallRpc(fsClient, 4, 0, fsSendBuf, 0x1C, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (isNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceRead(int fd, void *buf, int nbyte)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int inuse;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam sema;

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(2);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _sceFsSigSema();
        return -9;
    }
    g[3] = iob->fd;
    g[7] = iob - (SceIob *)fsIobTab;
    g[4] = (int)buf;
    g[5] = nbyte;
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    fsSendBuf[0] = h = CreateSema(&sema);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    if (inuse & 0x8000) {
        WaitSema(q_sema);
        for (i = 0; i < 0x20; i++) {
            if (_sceFs_q[i] == -1) {
                _sceFs_q[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(q_sema);
    }
    if ((inuse & 0x20000000) == 0) {
        sceSifWriteBackDCache(buf, nbyte);
    }
    sceSifWriteBackDCache(fsRcvPkt, 0xA4);
    /* the request record is flushed through g and handed to the RPC by its
       symbol */
    sceSifWriteBackDCache(g, 0x20);
    rc = sceSifCallRpc(fsClient, 2, 0, fsSendBuf, 0x20, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (isNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceWrite(int fd, void *buf, int nbyte)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int inuse;
    int uv;
    int h;
    int rc;
    int i;
    int j;
    char *dst;
    int nb;
    int result;
    struct SemaParam sema;

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(3);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (iob == 0 || (inuse = iob->inuse) == 0) {
        _sceFsSigSema();
        return -9;
    }
    g[3] = iob->fd;
    g[11] = iob - (SceIob *)fsIobTab;
    g[5] = nbyte;
    g[4] = (int)buf;
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    fsSendBuf[0] = h = CreateSema(&sema);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    if (inuse & 0x8000) {
        WaitSema(q_sema);
        for (i = 0; i < 0x20; i++) {
            if (_sceFs_q[i] == -1) {
                _sceFs_q[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(q_sema);
    }
    if (((unsigned int)buf & 0xF) == 0) {
        nb = 0;
    } else {
        nb = (unsigned int)buf / 16 * 16 + 16 - (unsigned int)buf;
    }
    if (nb > nbyte) {
        nb = nbyte;
    }
    if ((inuse & 0x20000000) == 0) {
        sceSifWriteBackDCache(buf, nbyte);
    }
    buf = (char *)((unsigned int)buf | 0x20000000);
    g[6] = nb;
    /* the name bytes are copied from g + 0x1C on, with their own counter */
    for (j = 0; j < nb; j++) {
        dst = (char *)g + 0x1C;
        dst[j] = ((char *)buf)[j];
    }
    rc = sceSifCallRpc(fsClient, 3, 0, fsSendBuf, 0x30, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (isNowait(inuse)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* the ioctl argument pointer the request-0x1 arm reads back */
/* the 8-byte status word the IOP leaves for requests 0x2 and 0x3 */

typedef struct {
    char b[1024];
} SceIoctlArg;

int sceIoctl(unsigned int fd, int request, void *argp)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam sema;

    rc = 1; /* a dead assignment the 2001 source carried: the sceSifCallRpc
               result below overwrites it, and nothing reads it before. */

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(5);
    fsIoctlArg = argp;
    if (fs_inited == 0) {
        sceFsInit();
    }
    if (iob == 0 || iob->inuse == 0) {
        _sceFsSigSema();
        return -9;
    }
    g[0x105] = 0;
    g[0x106] = 0;
    switch (request) {
    case 1:
        WaitSema(q_sema);
        for (i = 0; i < 0x20; i++) {
            if (_sceFs_q[i] != -1) {
                break;
            }
        }
        if (i == 0x20) {
            *(int *)fsIoctlArg = 0;
        } else {
            *(int *)fsIoctlArg = 1;
        }
        SignalSema(q_sema);
        _sceFsSigSema();
        return 0;
    case 2:
        *(int *)argp = *(int *)((int)(fsRcvPkt + 0x10) | 0x20000000);
        _sceFsSigSema();
        return 0;
    case 3:
        *(long long *)argp = *(long long *)((int)(fsRcvPkt + 0x10) | 0x20000000);
        _sceFsSigSema();
        return 0;
    }
    g[3] = iob->fd;
    g[4] = request;
    if (argp == 0) {
        g[0x107] = 0;
    } else {
        g[0x107] = 1024;
        *(SceIoctlArg *)((char *)g + 0x14) = *(SceIoctlArg *)argp;
    }
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    h = CreateSema(&sema);
    g[2] = 4;
    *(void **)(g + 1) = &result;
    g[0] = h;
    sceSifWriteBackDCache(fsSendBuf, 0x420);
    rc = sceSifCallRpc(fsClient, 5, 0, fsSendBuf, 0x420, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceIoctl2(unsigned int fd, int request, void *argp, unsigned int arglen, void *bufp,
              unsigned int buflen)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int uv;
    int h;
    int rc;
    int result;
    struct SemaParam buf;

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(0x1A);
    if (fs_inited == 0) {
        sceFsInit();
    }
    if (iob == 0 || iob->inuse == 0) {
        _sceFsSigSema();
        return -9;
    }
    if (arglen > 0x400 || buflen > 0x400) {
        return -0x16;
    }
    if (argp == 0) {
        g[0x107] = 0;
    } else {
        memcpy((char *)g + 0x14, argp, arglen);
    }
    g[3] = iob->fd;
    g[4] = request;
    g[0x107] = arglen;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[0x106] = buflen;
    g[2] = 4;
    *(void **)(g + 0x105) = bufp;
    g[0] = h;
    sceSifWriteBackDCache(fsSendBuf, 0x420);
    rc = sceSifCallRpc(fsClient, 0x1A, 0, fsSendBuf, 0x420, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int _sceCallCode(void *name, int code)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(code);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = ((char *)name)[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x40B) = 0;
        i = 0x3FF;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, code, 0, fsSendBuf, i + 0xD, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceRemove(void *a0)
{
    return _sceCallCode(a0, 6);
}

int sceMkdir(char *name, int mode)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(7);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x10) = name[i];
        if (*((char *)g + i + 0x10) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x40F) = 0;
        i = 0x3FF;
    }
    g[3] = mode;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 7, 0, fsSendBuf, i + 0x11, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceRmdir(void *a0)
{
    return _sceCallCode(a0, 8);
}

int sceFormat(unsigned char *dev, unsigned char *blockdev, unsigned char *arg, int arglen)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0xE);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = dev[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    if (blockdev == 0) {
        ((char *)g)[0x40C] = 0;
    } else {
        for (i = 0; i < 0x400; i++) {
            char *d = (char *)g + 0x40C;
            d[i] = blockdev[i];
            if (d[i] == 0) {
                break;
            }
        }
        if (i == 0x400) {
            ((char *)g)[0x80B] = 0;
        }
    }
    if (arglen > 0x400) {
        _sceFsSigSema();
        return -7;
    }
    for (i = 0; i < arglen; i++) {
        char *d = (char *)g + 0x80C;
        d[i] = arg[i];
    }
    g[0x303] = arglen;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(fsSendBuf, 0xC10);
    rc = sceSifCallRpc(fsClient, 0xE, 0, fsSendBuf, 0xC10, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceAddDrv(void *a0)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0xF);
    if (fs_inited == 0) {
        sceFsInit();
    }
    g[3] = (int)a0;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    fsSendBuf[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0xF, 0, g, 0x10, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -1;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -1;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceDelDrv(void *a0)
{
    return _sceCallCode(a0, 0x10);
}

int sceDopen(void *name)
{
    SceIob *iob;
    int rc;

    iob = (SceIob *)new_iob();
    if (iob == 0) {
        return -19;
    }
    rc = _sceCallCode(name, 9);
    if (rc < 0) {
        WaitSema(iob_sema);
        iob->inuse = 0;
        SignalSema(iob_sema);
        return rc;
    }
    WaitSema(iob_sema);
    iob->fd = rc;
    rc = iob - (SceIob *)fsIobTab;
    SignalSema(iob_sema);
    return rc;
}

int sceDclose(unsigned int a0)
{
    int *g = fsSendBuf;
    void *obj;
    int f0;
    int uv;
    int h;
    int rc;
    int result;
    struct SemaParam buf;

    obj = get_iob(a0);
    _sceFsWaitS(0xA);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        _sceFsSigSema();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[3] = f0;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    fsSendBuf[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0xA, 0, g, 0x14, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    ((int *)obj)[1] = 0;
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    if (result < 0) {
        return result;
    }
    return 0;
}

int sceDread(unsigned int a0, int a1)
{
    int *g = fsSendBuf;
    void *obj;
    int f0;
    int uv;
    int rc;
    int result;
    struct SemaParam buf;

    obj = get_iob(a0);
    _sceFsWaitS(0xB);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        _sceFsSigSema();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[4] = a1;
    g[3] = f0;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    fsSendBuf[0] = a1 = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0xB, 0, g, 0x20, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        WaitSema(a1);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(a1);
        return -0xB;
    }
    WaitSema(a1);
    DeleteSema(a1);
    return result;
}

int sceGetstat(unsigned char *name, void *stat)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0xC);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((unsigned char *)g + i + 0x10) = name[i];
        if (*((unsigned char *)g + i + 0x10) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x40F) = 0;
        i = 0x3FF;
    }
    g[3] = (int)stat;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0xC, 0, fsSendBuf, i + 0x11, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

/* the 0x40-byte stat record the request carries; the copy below is a record
   assignment, which gcc expands inline, since memcpy stays a call at
   -fno-builtin */
typedef struct {
    char v[0x40];
} SceFsStat;

int sceChstat(unsigned char *name, void *stat, int mask)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0xD);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((unsigned char *)g + i + 0x50) = name[i];
        if (*((unsigned char *)g + i + 0x50) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        *((char *)g + 0x44F) = 0;
        i = 0x3FF;
    }
    *(SceFsStat *)((char *)g + 0x10) = *(SceFsStat *)stat;
    g[3] = mask;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(fsSendBuf, 0x450);
    rc = sceSifCallRpc(fsClient, 0xD, 0, fsSendBuf, i + 0x51, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceRename(unsigned char *oldname, unsigned char *newname)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0x11);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = oldname[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = newname[i];
        if (d[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x80B] = 0;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(fsSendBuf, 0x80C);
    rc = sceSifCallRpc(fsClient, 0x11, 0, fsSendBuf, 0x80C, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceChdir(void *a0)
{
    return _sceCallCode(a0, 0x12);
}

int sceSync(unsigned char *name, int flag)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0x13);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x14) = name[i];
        if (*((char *)g + i + 0x14) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x413] = 0;
    }
    g[4] = flag;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0x13, 0, fsSendBuf, 0x414, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceMount(unsigned char *fsname, unsigned char *devname, int flag, unsigned char *arg,
             int arglen)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0x14);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = fsname[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = devname[i];
        if (d[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x80B] = 0;
    }
    if (arglen > 0x400) {
        _sceFsSigSema();
        return -7;
    }
    for (i = 0; i < arglen; i++) {
        char *d = (char *)g + 0x80C;
        d[i] = arg[i];
    }
    g[0x304] = arglen;
    g[0x303] = flag;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(fsSendBuf, 0xC14);
    rc = sceSifCallRpc(fsClient, 0x14, 0, fsSendBuf, 0xC14, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceUmount(void *a0)
{
    return _sceCallCode(a0, 0x15);
}

long long sceLseek64(int fd, long long offset, int whence)
{
    int *g = fsSendBuf;
    SceIob *iob;
    int f4;
    int uv;
    int h;
    int rc;
    int i;
    long long result;
    struct SemaParam buf;

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(0x16);
    if (fs_inited == 0) {
        _sceFsSigSema();
        return -1;
    }
    if (iob == 0 || (f4 = iob->inuse) == 0) {
        _sceFsSigSema();
        return -9;
    }
    *(long long *)(g + 4) = offset;
    g[3] = iob->fd;
    g[6] = whence;
    g[7] = iob - (SceIob *)fsIobTab;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 8;
    fsSendBuf[0] = h;
    if (f4 & 0x8000) {
        WaitSema(q_sema);
        for (i = 0; i < 0x20; i++) {
            if (_sceFs_q[i] == -1) {
                _sceFs_q[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(q_sema);
    }
    rc = sceSifCallRpc(fsClient, 0x16, 0, fsSendBuf, 0x20, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    if (isNowait(f4)) {
        DeleteSema(h);
        return 0;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceDevctl(unsigned char *name, int cmd, unsigned char *arg, unsigned int arglen, void *bufp,
              unsigned int buflen)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0x17);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = name[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    if (arglen > 0x400 || buflen > 0x400) {
        return -0x16;
    }
    for (i = 0; i < arglen; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = arg[i];
    }
    g[0x204] = arglen;
    g[0x203] = cmd;
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    h = CreateSema(&buf);
    g[0x206] = buflen;
    *(void **)(g + 1) = &result;
    g[2] = 4;
    *(void **)(g + 0x205) = bufp;
    g[0] = h;
    sceSifWriteBackDCache(fsSendBuf, 0x81C);
    rc = sceSifCallRpc(fsClient, 0x17, 0, fsSendBuf, 0x81C, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceSymlink(unsigned char *existing, unsigned char *newpath)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam buf;

    _sceFsWaitS(0x11);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0xC) = existing[i];
        if (*((char *)g + i + 0xC) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x40B] = 0;
    }
    for (i = 0; i < 0x400; i++) {
        char *d = (char *)g + 0x40C;
        d[i] = newpath[i];
        if (d[i] == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x80B] = 0;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    buf.option = 0;
    g[0] = h = CreateSema(&buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0x18, 0, fsSendBuf, 0x80C, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

int sceReadlink(unsigned char *name, void *buf, unsigned int len)
{
    int *g = fsSendBuf;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    struct SemaParam sema;

    _sceFsWaitS(0x11);
    if (fs_inited == 0) {
        sceFsInit();
    }
    for (i = 0; i < 0x400; i++) {
        *((char *)g + i + 0x14) = name[i];
        if (*((char *)g + i + 0x14) == 0) {
            break;
        }
    }
    if (i == 0x400) {
        ((char *)g)[0x413] = 0;
    }
    if (len >= 0x400) {
        len = 0x3FF;
    }
    g[4] = (int)buf;
    g[3] = len;
    sceSifWriteBackDCache(buf, len);
    sema.maxCount = 1;
    sema.initCount = 0;
    sema.option = 0;
    g[0] = h = CreateSema(&sema);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(fsClient, 0x19, 0, fsSendBuf, 0x80C, fsRecvBuf, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)fsRecvBuf | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}
