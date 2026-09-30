/* Vendor SCE library member: libkernl.a(filestub.o).  MAIN.MAP names the
 * member and its .text size (0x3570), which tiles the shipped ELF from one
 * retail function start to the next; VMA 0x2606D0..0x263C40,
 * 38 functions. */

#include <sifrpc.h>
#include <string.h>

extern int DIntr();
extern int EIntr();
extern int iSignalSema(int a0);
extern int CreateSema(int *self);

/* filestub.o's .data, in the ROM's order.  _sceFs_q is MAIN.MAP's name: the
   async request slot table _sceFs_Rcv_Intr matches a reply against, read and
   written under q_sema; an entry of -1 is free.  The table is written by the
   SIF receive interrupt, so every access to it is volatile (C volatile ruling
   2026-09-07).  Then whether sceFsInit has bound the server, the FS call
   semaphore, the iob table's semaphore and the slot table's guard semaphore
   (each -1 until created).  The last word, _fs_version's stamp, is defined
   beside its one user below. */

volatile int _sceFs_q[32] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

static int fs_inited = 0;

static int fs_sema = -1;

static int iob_sema = -1;

static int q_sema = -1;

void _sceFsIobSemaMK(void)
{
    extern int CreateSema(int *a0);
    int args[8];
    if (iob_sema == -1) {
        args[5] = 0;
        args[2] = 1;
        args[1] = 1;
        iob_sema = CreateSema(args);
        q_sema = CreateSema(args);
    }
}

extern char D_0072D300[];
extern int SignalSema(int a0);
extern int WaitSema(int a0);

int new_iob(void)
{
    char *p;
    char *end;
    _sceFsIobSemaMK();
    WaitSema(iob_sema);
    p = D_0072D300;
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
    p = &D_0072D300[i * 16];
    SignalSema(iob_sema);
    return p;
}

/* Reconstruction: the four-byte filesystem version stamp the IOP hands back
   in the RPC receive buffer; _fs_version() memcmps it against the two
   built-in stamps. */
typedef struct {
    char v[4];
} SceFsVersion;

extern char D_0072CEC0[];

/* the FS reply packet the IOP leaves in D_0072CEC0; the handler reads it
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

extern char D_0072CED4[];

/* The SIF command handler for the FS reply.  Each reply word is its own
   local (the header's request id, command, buffer and size, then a
   command's destination and length), filled by a four-byte record copy
   through the uncached window.  Rung: ROM bytes.  The frame puts them at
   0x0..0x14 in first-use order, which is where gcc places locals whose
   address is taken once purge_addressof, after the first cse pass, sends
   them to the stack; an int array is allocated before them (measured).
   The same property gives the search its id register: until the purge the
   id is an ADDRESSOF MEM, so cse1 keeps the peel's read of it, gcse carries
   that read into the loop, and cse2 then forwards the negated id's store
   into it, which is the ROM's `daddu $6,$2,$0` beside the `sw $2,0($29)`
   (an int array or a copy into a second local measured 30 words off). */
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

    *(SceFsVersion *)&id = *(SceFsVersion *)((int)(D_0072CEC0 + 0x0) | 0x20000000);
    *(SceFsVersion *)&cmd = *(SceFsVersion *)((int)(D_0072CEC0 + 0x4) | 0x20000000);
    *(SceFsVersion *)&buf = *(SceFsVersion *)((int)(D_0072CEC0 + 0x8) | 0x20000000);
    *(SceFsVersion *)&size = *(SceFsVersion *)((int)(D_0072CEC0 + 0xC) | 0x20000000);
    memcpy((void *)buf, (void *)((int)(D_0072CEC0 + 0x10) | 0x20000000), size);
    switch (cmd) {
    case 2:
        q = (int *)((int)D_0072CED4 | 0x20000000);
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
        *(SceFsVersion *)&addr = *(SceFsVersion *)((int)D_0072CED4 | 0x20000000);
        *(SceFsDirent *)addr = *(SceFsDirent *)((int)(D_0072CED4 + 4) | 0x20000000);
        break;
    case 12:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((int)D_0072CED4 | 0x20000000);
        *(SceFsStatRec *)addr = *(SceFsStatRec *)((int)(D_0072CED4 + 4) | 0x20000000);
        break;
    case 23:
    case 25:
    case 26:
        *(SceFsVersion *)&addr = *(SceFsVersion *)((int)D_0072CED4 | 0x20000000);
        *(SceFsVersion *)&len = *(SceFsVersion *)((int)(D_0072CED4 + 4) | 0x20000000);
        k = len;
        if (1024 < (unsigned int)k) {
            len = 1024;
            k = 1024;
        }
        memcpy((void *)addr, (void *)((int)(D_0072CED4 + 8) | 0x20000000), k);
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
    int self[8];
    if (fs_sema == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        fs_sema = CreateSema(self);
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

extern char D_0072D300[];
extern int D_0072D500[];
extern char D_0072D528[];
extern char D_0072D530[];
extern int D_0072CE80[];
extern void _sceFsIobSemaMK(void);
extern int SignalSema(int a0);
extern int sceSifAddCmdHandler(int a0, int a1, int a2);
extern int sceSifBindRpc(void *cd, unsigned int sid, int mode);

int sceFsInit(void)
{
    char *p;
    char *end;
    int i;
    int buf[1];

    sceSifInitRpc(0);
    DIntr();
    sceSifAddCmdHandler(0x80000011, (int)_sceFs_Rcv_Intr, (int)D_0072D530);
    EIntr();
    for (;;) {
        if (sceSifBindRpc(D_0072D500, 0x80000001, 0) < 0) {
            return -1;
        }
        if (D_0072D500[9] != 0) {
            break;
        }
        for (i = 0x100000; i != -1; i--) {
            ;
        }
    }
    _sceFsIobSemaMK();
    WaitSema(iob_sema);
    p = D_0072D300;
    end = D_0072D300 + 0x200;
    while (p < end) {
        ((int *)p)[1] = 0;
        p += 0x10;
    }
    SignalSema(iob_sema);
    buf[0] = (int)D_0072CEC0;
    if (sceSifCallRpc(D_0072D500, 0xFF, 0, buf, 4, D_0072CE80, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    *(SceFsVersion *)D_0072D528 = *(SceFsVersion *)((int)D_0072CE80 | 0x20000000);
    fs_inited = 1;
    return 0;
}

extern char D_0072D528[];
extern int memcmp();

/* the stamp _fs_version accepts besides the library's own.  Defined here, after
   _sceFs_Rcv_Intr, its four dots follow that function's jump table in the
   member's .rodata as the ROM has them (0x636708), and the pointer is still
   the member's last .data word. */
static char *fs_stamp = "....";

int _fs_version(void)
{
    char *s3 = __ps2_klibinfo__ + 12;
    char *s1 = D_0072D528;
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

extern char D_0072D528[];

int sceFsReset(void)
{
    fs_inited = 0;
    memset(D_0072D528, 0, 4);
    return 0;
}

/* Reconstruction: the 16-byte file-descriptor record new_iob() hands out of
   the D_0072D300 table; field 0 is the driver handle _sceCallCode returns and
   field 4 the in-use flag new_iob() sets to 0x10000000. */
typedef struct {
    int fd;
    int inuse;
    int _8[2];
} SceIob;

extern int D_0072C240[];
extern int D_0072CE80[];
extern int D_0072D500[];
extern int CreateSema(int *self);
extern int WaitSema(int a0);
extern int DeleteSema(int a0);
extern void _sceFsSigSema(void);
extern void *get_iob(unsigned int a0);

/* Varargs: the mode is the first anonymous argument, read from gcc's own
   save area after the new_iob() check (the ROM's lw $7,0x120($29)).  One
   status local, rc, carries the RPC result, the uncached reply word and the
   returned index, the way sceLseek keeps its own; the ROM's register pairs
   (name and the semaphore in $s0, the request pointer and the reply word in
   $s1) need the reply word to be that cross-block variable, since a local
   used in one block is local-alloc's and takes $s0 first.  The descriptor is
   stored before the in-use flag is or-ed: the ROM loads `result` ahead of
   the flag store, which an addressed stack local cannot pass. */
int sceOpen(unsigned char *name, int flags, ...)
{
    int *g = D_0072C240;
    int mode;
    SceIob *iob;
    int i;
    int idx;
    int h;
    int rc;
    int result;
    int buf[8];

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
    idx = iob - (SceIob *)D_0072D300;
    g[3] = flags & 0xFFFFFFF;
    g[4] = mode;
    g[0x414 / 4] = idx;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0, 0, D_0072C240, 0x418, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    rc = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    SceIob *iob;
    int f0;
    int uv;
    int h;
    int rc;
    int result;
    int buf[8];

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
    g[4] = iob - (SceIob *)D_0072D300;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 1, 0, g, 0x14, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    iob->inuse = 0;
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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

/* RECONSTRUCTION, the name is ours: whether a descriptor was opened with the
   no-wait flag (0x8000, SCE_NOWAIT in the public SDK naming), read from the
   open-mode half of the descriptor's in-use word.  The ROM's second no-wait
   test in sceLseek (and in sceLseek64, sceRead and sceWrite) is its own
   `andi 0x8000` on the register the first test already masked: the
   argument's narrowing is its own insn when the call is inlined, so gcse
   sees (and (zero_extend (subreg:HI inuse)) 0x8000) apart from the first
   test's (and inuse 0x8000) and PRE keeps it, and combine then folds the
   extension into the mask (-da gcse and combine dumps, completeness pass
   57).  Written plainly, or with the cast at the test, PRE deletes it. */
static inline int isNowait(unsigned short mode)
{
    return mode & 0x8000;
}

int sceLseek(unsigned int fd, int offset, int whence)
{
    int *g = D_0072C240;
    SceIob *iob;
    int inuse;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    g[6] = iob - (SceIob *)D_0072D300;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = h = CreateSema(buf);
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
    rc = sceSifCallRpc(D_0072D500, 4, 0, D_0072C240, 0x1C, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    SceIob *iob;
    int inuse;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int sema[8];

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
    g[7] = iob - (SceIob *)D_0072D300;
    g[4] = (int)buf;
    g[5] = nbyte;
    sema[1] = 1;
    sema[2] = 0;
    sema[5] = 0;
    D_0072C240[0] = h = CreateSema(sema);
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
    sceSifWriteBackDCache(D_0072CEC0, 0xA4);
    /* the request record is flushed through g and handed to the RPC by its
       symbol: the ROM passes $17 here and rebuilds %lo(D_0072C240) for the
       call's fourth argument */
    sceSifWriteBackDCache(g, 0x20);
    rc = sceSifCallRpc(D_0072D500, 2, 0, D_0072C240, 0x20, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
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
    int sema[8];

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
    g[11] = iob - (SceIob *)D_0072D300;
    g[5] = nbyte;
    g[4] = (int)buf;
    sema[1] = 1;
    sema[2] = 0;
    sema[5] = 0;
    D_0072C240[0] = h = CreateSema(sema);
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
    /* What the bytes pin: the head-byte address g + 0x1C is its own insn in the
       copy loop's preheader, after the loop's test (addiu $6,$18,0x1C), and the
       store has displacement 0.  A constant-offset index (((char *)g)[0x1C + j])
       folds the 0x1C into the sb displacement (fold-const.c associate), and a
       pointer set before the loop is hoisted by gcse PRE above the async block;
       a set inside the body is what loop.c moves to that preheader.  The copy
       counter is its own variable: the ROM keeps it in $5, apart from the slot
       search's i in $6. */
    for (j = 0; j < nb; j++) {
        dst = (char *)g + 0x1C;
        dst[j] = ((char *)buf)[j];
    }
    rc = sceSifCallRpc(D_0072D500, 3, 0, D_0072C240, 0x30, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
extern void *D_0072C200;
/* the 8-byte status word the IOP leaves for requests 0x2 and 0x3 */
extern char D_0072CED0[];

typedef struct {
    char b[1024];
} SceIoctlArg;

int sceIoctl(unsigned int fd, int request, void *argp)
{
    int *g = D_0072C240;
    SceIob *iob;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int sema[8];

    rc = 1; /* RULING-VESTIGIAL-EXCEPTION instance (user-approved 2026-09-21):
               a dead assignment the 2001 source carried, overwritten by the
               sceSifCallRpc result below and read nowhere before it. The ROM
               proves it: `addiu $21,$0,0x1` at 0x00261A6C is the first
               instruction after the register saves and puts the constant 1 in
               a callee-saved register with no consumer until the switch's
               case-1 test, `beql $17,$21` at 0x00261AEC. Only a const-1
               pseudo born at the function head survives local_alloc into a
               callee-saved register and is there for that compare; without
               the statement the arm builds its own constant and the whole
               dispatch reorders (211 of 211 instructions, 38 differing
               words).  Re-audit (completeness pass 57): the two live reads of
               the 1 the function has, case 1's `*(int *)D_0072C200 = rc;`
               and `sema[1] = rc;`, were measured and change the function's
               size (0x344 and 0x354 against the ROM's 0x34C). */

    iob = (SceIob *)get_iob(fd);
    _sceFsWaitS(5);
    D_0072C200 = argp;
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
            *(int *)D_0072C200 = 0;
        } else {
            *(int *)D_0072C200 = 1;
        }
        SignalSema(q_sema);
        _sceFsSigSema();
        return 0;
    case 2:
        *(int *)argp = *(int *)((int)D_0072CED0 | 0x20000000);
        _sceFsSigSema();
        return 0;
    case 3:
        *(long long *)argp = *(long long *)((int)D_0072CED0 | 0x20000000);
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
    sema[1] = 1;
    sema[2] = 0;
    sema[5] = 0;
    h = CreateSema(sema);
    g[2] = 4;
    *(void **)(g + 1) = &result;
    g[0] = h;
    sceSifWriteBackDCache(D_0072C240, 0x420);
    rc = sceSifCallRpc(D_0072D500, 5, 0, D_0072C240, 0x420, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    SceIob *iob;
    int uv;
    int h;
    int rc;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[0x106] = buflen;
    g[2] = 4;
    *(void **)(g + 0x105) = bufp;
    g[0] = h;
    sceSifWriteBackDCache(D_0072C240, 0x420);
    rc = sceSifCallRpc(D_0072D500, 0x1A, 0, D_0072C240, 0x420, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, code, 0, D_0072C240, i + 0xD, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

extern int _sceCallCode(void *a0, int a1);

int sceRemove(void *a0)
{
    return _sceCallCode(a0, 6);
}

int sceMkdir(char *name, int mode)
{
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 7, 0, D_0072C240, i + 0x11, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(D_0072C240, 0xC10);
    rc = sceSifCallRpc(D_0072D500, 0xE, 0, D_0072C240, 0xC10, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}

extern int D_0072C240[];
extern int D_0072CE80[];
extern int D_0072D500[];
extern int CreateSema(int *a0);
extern int WaitSema(int a0);
extern int DeleteSema(int a0);
extern void _sceFsSigSema(void);
extern int sceFsInit(void);

int sceAddDrv(void *a0)
{
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int result;
    int buf[8];

    _sceFsWaitS(0xF);
    if (fs_inited == 0) {
        sceFsInit();
    }
    g[3] = (int)a0;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0xF, 0, g, 0x10, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -1;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    rc = iob - (SceIob *)D_0072D300;
    SignalSema(iob_sema);
    return rc;
}

extern int D_0072C240[];
extern int D_0072CE80[];
extern int D_0072D500[];
extern int DeleteSema(int a0);
extern void _sceFsSigSema(void);
extern void *get_iob(unsigned int a0);

int sceDclose(unsigned int a0)
{
    extern int CreateSema(int *a0);
    extern int WaitSema(int a0);
    int *g = D_0072C240;
    void *obj;
    int f0;
    int uv;
    int h;
    int rc;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0xA, 0, g, 0x14, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    ((int *)obj)[1] = 0;
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    extern int CreateSema(int *a0);
    extern int WaitSema(int a0);
    int *g = D_0072C240;
    void *obj;
    int f0;
    int uv;
    int rc;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0072C240[0] = a1 = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0xB, 0, g, 0x20, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        WaitSema(a1);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0xC, 0, D_0072C240, i + 0x11, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(D_0072C240, 0x450);
    rc = sceSifCallRpc(D_0072D500, 0xD, 0, D_0072C240, i + 0x51, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(D_0072C240, 0x80C);
    rc = sceSifCallRpc(D_0072D500, 0x11, 0, D_0072C240, 0x80C, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0x13, 0, D_0072C240, 0x414, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    sceSifWriteBackDCache(D_0072C240, 0xC14);
    rc = sceSifCallRpc(D_0072D500, 0x14, 0, D_0072C240, 0xC14, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    SceIob *iob;
    int f4;
    int uv;
    int h;
    int rc;
    int i;
    long long result;
    int buf[8];

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
    g[7] = iob - (SceIob *)D_0072D300;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 8;
    D_0072C240[0] = h;
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
    rc = sceSifCallRpc(D_0072D500, 0x16, 0, D_0072C240, 0x20, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    h = CreateSema(buf);
    g[0x206] = buflen;
    *(void **)(g + 1) = &result;
    g[2] = 4;
    *(void **)(g + 0x205) = bufp;
    g[0] = h;
    sceSifWriteBackDCache(D_0072C240, 0x81C);
    rc = sceSifCallRpc(D_0072D500, 0x17, 0, D_0072C240, 0x81C, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int buf[8];

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
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    g[0] = h = CreateSema(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0x18, 0, D_0072C240, 0x80C, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
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
    int *g = D_0072C240;
    int uv;
    int h;
    int rc;
    int i;
    int result;
    int sema[8];

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
    sema[1] = 1;
    sema[2] = 0;
    sema[5] = 0;
    g[0] = h = CreateSema(sema);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = sceSifCallRpc(D_0072D500, 0x19, 0, D_0072C240, 0x80C, D_0072CE80, 4, 0, 0);
    if (rc < 0) {
        DeleteSema(h);
        _sceFsSigSema();
        return -0xB;
    }
    uv = *(int *)((int)D_0072CE80 | 0x20000000);
    _sceFsSigSema();
    if (uv == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return result;
}
