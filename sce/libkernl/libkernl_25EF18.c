/* Vendor SCE library run.  The archive attribution (libkernl.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"
#include <sifrpc.h>
#include <string.h>

typedef struct {
    int f0;
    int f4;
    char *f8;
} RingBuf_241C80;

typedef struct {
    int f0;
    int f4;
    char *f8;
    char *fC;
    char buf[1];
} PrintSink;

extern int D_0054A3E0[];
/* unprototyped: sceResetttyinit passes the port, write and read call it bare */
extern int sceTtyInit();

void sceResetttyinit(int a0)
{
    D_0054A3E0[0] = 0;
    sceTtyInit(a0);
}

/* VSync polls INTC_STAT (0x1000F000) for the VBLANK bit and clears it, which
   is one of the whole-function asm exceptions this project documents (a
   busy-wait on a hardware register).  It is assembled here rather than written
   in C because two measurements say no C that keeps the data model reaches the
   ROM's last two words, which end `jr $31` with `sw $2,-0x1000($1)` in the
   delay slot: gcc's reorg cannot fill a return's delay slot with a VOLATILE
   store, and a store through an ABSOLUTE CONSTANT address is a two-instruction
   assembler macro and so is not eligible for a delay slot either; this
   function's store is both.  ee-as never fills a `j $31` slot itself.  The C
   that produces the other fourteen words is kept on record in
   tails/seeds/libkernl_25EF18.c1p40_VSync_16of16_strict2.c. */
__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global VSync\n"
        ".type VSync, @function\n"
        "    .align 3\n"
        "VSync:\n"
        "    lui $2, (0x1000F000 >> 16)\n"
        "    addiu $3, $0, 0x4\n"
        "    ori $2, $2, (0x1000F000 & 0xFFFF)\n"
        "    sw $3, 0x0($2)\n"
        ".LVSync0025EF38:\n"
        "    lui $2, (0x10010000 >> 16)\n"
        "    lw $2, -0x1000($2)\n"
        "    andi $2, $2, 0x4\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    beqz $2, .LVSync0025EF38\n"
        "    nop\n"
        "    addiu $2, $0, 0x4\n"
        "    lui $1, (0x10010000 >> 16)\n"
        "    jr $31\n"
        "    sw $2, -0x1000($1)\n"
        "    .set reorder\n"
        "    .set at\n");

extern void SetVSyncFlag(void *a0, void *a1);

long long VSync2(void)
{
    volatile int flag;
    volatile long long val;
    volatile int *p;
    flag = 0;
    SetVSyncFlag((void *)&flag, (void *)&val);
    p = (volatile int *)0x1000F000;
    *p = 4;
    while ((*p & 4) == 0 && flag == 0) {}
    *p = 4;
    return val;
}

extern int sceTtyWrite(char *buf, int len);
extern int sceTtyRead(void *buf, int size);

int write(int fd, void *buf, int size)
{
    if (fd - 1 < 2U) {
        if (D_0054A3E0[0] == 0) {
            if (sceTtyInit() == 0) {
                return -1;
            }
            D_0054A3E0[0] = 1;
        }
        return sceTtyWrite(buf, size);
    }
    return -1;
}

int read(int fd, void *buf, int size)
{
    if (fd == 0) {
        if (D_0054A3E0[0] == 0) {
            if (sceTtyInit() == 0) {
                return -1;
            }
            D_0054A3E0[0] = 1;
        }
        return sceTtyRead(buf, size);
    }
    return -1;
}

extern int __errno(void);

int open(void)
{
    *(int *)__errno() = 5;
    return -1;
}

int close(int a1)
{
    return -1;
}

int ioctl(void)
{
    return -1;
}

int lseek(int a1, int a2, int a3)
{
    return -1;
}

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global sbrk\n"
        ".type sbrk, @function\n"
        "    .align 3\n"
        "sbrk:\n"
        "    addiu $29, $29, -0x40\n"
        "    sd $31, 0x30($29)\n"
        "    sd $18, 0x20($29)\n"
        "    sd $17, 0x10($29)\n"
        "    sd $16, 0x0($29)\n"
        "    mfc0 $17, $12\n"
        "    lui $2, (0x10000 >> 16)\n"
        "    and $17, $17, $2\n"
        "    beqz $17, .Lsbrk00241B14\n"
        "    lui $18, %hi(D_0054A3E4)\n"
        ".Lsbrk00241AF0:\n"
        "    di\n"
        "    sync.p\n"
        "    mfc0 $2, $12\n"
        "    lui $3, (0x10000 >> 16)\n"
        "    and $2, $2, $3\n"
        "    bnez $2, .Lsbrk00241AF0\n"
        "    nop\n"
        "    b .Lsbrk00241B18\n"
        "    lw $2, %lo(D_0054A3E4)($18)\n"
        ".Lsbrk00241B14:\n"
        "    lw $2, %lo(D_0054A3E4)($18)\n"
        ".Lsbrk00241B18:\n"
        "    jal EndOfHeap\n"
        "    addu $16, $2, $4\n"
        "    sltu $2, $2, $16\n"
        "    beqz $2, .Lsbrk00241B50\n"
        "    lw $2, %lo(D_0054A3E4)($18)\n"
        "    jal __errno\n"
        "    nop\n"
        "    addiu $3, $0, 0xC\n"
        "    beqz $17, .Lsbrk00241B44\n"
        "    sw $3, 0x0($2)\n"
        "    ei\n"
        ".Lsbrk00241B44:\n"
        "    lui $2, (0xFFFFFFFF >> 16)\n"
        "    b .Lsbrk00241B5C\n"
        "    ori $2, $2, (0xFFFFFFFF & 0xFFFF)\n"
        ".Lsbrk00241B50:\n"
        "    beqz $17, .Lsbrk00241B5C\n"
        "    sw $16, %lo(D_0054A3E4)($18)\n"
        "    ei\n"
        ".Lsbrk00241B5C:\n"
        "    ld $31, 0x30($29)\n"
        "    ld $18, 0x20($29)\n"
        "    ld $17, 0x10($29)\n"
        "    ld $16, 0x0($29)\n"
        "    jr $31\n"
        "    addiu $29, $29, 0x40\n"
        ".size sbrk, . - sbrk\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

int isatty(void)
{
    return 1;
}

int fstat(void *a0, void *a1)
{
    *(long long *)((char *)a1 + 0x48) = 0;
    *(int *)((char *)a1 + 0x4) = 0x2000;
    return 0;
}

int getpid(void)
{
    return 1;
}

extern void Exit(void *a0);

int kill(int a0, void *a1)
{
    if (a0 == 1) {
        Exit(a1);
    }
    return 0;
}

int stat(void)
{
    *(int *)__errno() = 5;
    return -1;
}

int unlink(void)
{
    *(int *)__errno() = 5;
    return -1;
}

extern PrintSink D_0072A600;

void *QueueInit(int a0)
{
    D_0072A600.f0 = a0;
    D_0072A600.f4 = 0;
    D_0072A600.fC = D_0072A600.buf;
    D_0072A600.f8 = D_0072A600.buf;
    return &D_0072A600;
}

void QueuePeekWriteDone(int *q)
{
    int count = q[1] + 1;
    char *wp = (char *)q[3] + 1;
    int cap = q[0];
    q[1] = count;
    cap += 0x10;
    {
        char *end = (char *)q + cap;
        q[3] = (int)wp;
        if (wp == end) {
            q[3] = (int)q + 0x10;
        }
    }
}

void QueuePeekReadDone(RingBuf_241C80 *a0)
{
    a0->f4--;
    a0->f8++;
    if (a0->f8 == (char *)a0 + (a0->f0 + 0x10)) {
        a0->f8 = (char *)a0 + 0x10;
    }
}

/* unprototyped: the ROM passes a second argument in a register at two of the
   four call sites */
extern void kprintf();
extern int sceDeci2ExRecv(int s, int buf, unsigned short len);
extern int sceDeci2ExSend(int s, int buf, unsigned short len);

/* RECONSTRUCTION: the tty socket record at D_0072A710 as the handler sees it.
   The four header words are volatile, the view sceTtyInit and sceTtyWrite
   already take (the handler writes them from interrupt level while the
   callers poll them); the buffer and queue pointers below them are plain.
   The names are ours. */
typedef struct {
    volatile int s;    /* 0x00 the DECI2 socket */
    volatile int wlen; /* 0x04 bytes left to send */
    volatile int rlen; /* 0x08 bytes received into rbuf */
    volatile int busy; /* 0x0C set while a send is outstanding */
    char *wbuf;        /* 0x10 */
    char *rbuf;        /* 0x14 */
    int *q;            /* 0x18 the receive queue */
} TtyRec;

void sceTtyHandler(int event, int param, void *opt)
{
    TtyRec *tty = opt;
    int n;
    int i;
    char *hdr;

    switch (event) {
    case 1:
    case 2:
        if (param != 0) {
            if (320 < (unsigned int)(tty->rlen + param)) {
                kprintf("TTY: packet size larger than expect\n");
            }
            i = sceDeci2ExRecv(tty->s, (int)(tty->rbuf + tty->rlen), (unsigned short)param);
            if (i < 0) {
                kprintf("TTY: receive error");
            }
            tty->rlen = tty->rlen + i;
            return;
        }
        hdr = tty->rbuf;
        for (i = 12; i < *(unsigned short *)hdr; i++) {
            *(char *)tty->q[3] = tty->rbuf[i];
            QueuePeekWriteDone(tty->q);
        }
        tty->rlen = 0;
        return;

    case 3:
        n = sceDeci2ExSend(tty->s, (int)tty->wbuf, (unsigned short)tty->wlen);
        if (n < 0) {
            kprintf("TTY: send err %d\n", n);
            break;
        }
        tty->wbuf = tty->wbuf + n;
        tty->wlen = tty->wlen - n;
        return;

    case 4:
        if (tty->wlen != 0) {
            kprintf("TTY: err ti->wlen=%08x\n", tty->wlen);
        }
        break;

    default:
        return;
    }
    tty->busy = 0;
}

extern int D_0072A710[];
extern char D_0072A740[];
extern int DIntr();
extern int EIntr();
extern int sceDeci2ReqSend(int s, int c);
extern void sceDeci2Poll(int s);

int sceTtyWrite(char *buf, int len)
{
    /* the tty handler owns this record from interrupt level: it clears the
       busy flag at +0xC when the send completes and writes the length at
       +0x4, so every read of it in this function is a volatile read.  The
       stores run with interrupts disabled and are plain. */
    volatile int *rec = D_0072A710;
    char *hdr;
    char *out;
    int n = 0;
    int i = 0;

    if (rec[3] != 0) {
        return -1;
    }
    DIntr();
    D_0072A710[3] = 1;
    /* the send buffer is addressed through the uncached accelerated window */
    hdr = (char *)((unsigned int)D_0072A740 | 0x20000000);
    D_0072A710[4] = (int)hdr;
    out = hdr + 12;
    while (len-- != 0) {
        if (*buf == '\n') {
            *out = '\r';
            n++;
            out++;
            if (n >= 256) {
                break;
            }
        }
        *out = *buf;
        n++;
        buf++;
        out++;
        i++;
        if (n >= 256) {
            break;
        }
    }
    D_0072A710[1] = n + 12;
    *(short *)hdr = *(volatile int *)&D_0072A710[1];
    if (sceDeci2ReqSend(*(volatile int *)&D_0072A710[0], hdr[7]) < 0) {
        D_0072A710[3] = 0;
        EIntr();
        return -1;
    }
    while (*(volatile int *)&D_0072A710[3] != 0) {
        sceDeci2Poll(*(volatile int *)&D_0072A710[0]);
    }
    EIntr();
    return i;
}

extern int D_0072A710[];
/* the DECI2 receive flag the tty handler sets from interrupt level */
extern volatile int *D_0072A728;

int sceTtyRead(void *buf, int size)
{
    int i;
    char *p;

    for (i = 0; i < size; i++) {
        p = (char *)buf + i;
        while (D_0072A728[1] == 0) {}
        *p = *((RingBuf_241C80 *)D_0072A710[6])->f8;
        QueuePeekReadDone((RingBuf_241C80 *)D_0072A710[6]);
        if (*p == '\n' || *p == '\r') {
            return i + 1;
        }
    }
    return i;
}

extern int sceDeci2Open(unsigned short protocol, void *opt, void *handler);
extern void sceTtyHandler(int event, int param, void *opt);
/* the DECI2 receive packet, reached through the uncached accelerated window */
extern char D_0072A880[];

int sceTtyInit(void)
{
    /* the tty handler writes the socket's send length, receive count and busy
       flag from interrupt level (its stores at +0x4, +0x8 and +0xC), so the
       record's four header words are volatile; the buffer and queue pointers
       below them are plain */
    volatile int *rec = D_0072A710;
    char *snd;
    char *rcv;

    FlushCache(0);
    rec[0] = sceDeci2Open(0x210, D_0072A710, sceTtyHandler);
    if (rec[0] < 0) {
        return 0;
    }
    rec[3] = 0;
    rcv = (char *)((unsigned int)D_0072A880 | 0x20000000);
    snd = (char *)((unsigned int)D_0072A740 | 0x20000000);
    rec[1] = 0;
    rec[2] = 0;
    D_0072A710[5] = (int)rcv;
    D_0072A710[4] = (int)snd;
    *(short *)(snd + 4) = 0x210;
    snd[6] = 'E';
    snd[7] = 'H';
    *(short *)(snd + 2) = 0;
    *(int *)(snd + 8) = 0;
    D_0072A710[6] = (int)QueueInit(256);
    return 1;
}

extern int D_0054A3E8[];

/* RECONSTRUCTION: sifrpc.o's RPC state record (the .bss object at
   0x0072C1C0).  Field names follow the public SDK naming of this record;
   the types are what the ROM needs: the ten stores in sceSifInitRpc only
   schedule as the ROM has them when the packet table (void *), the two
   byte tables (unsigned char *) and the int fields sit in three different
   alias sets, and active_queue keeps the `int *` the queue walkers below
   read it as. */
typedef struct {
    int pid;
    void *pkt_table;
    int pkt_table_len;
    int unused1;
    int unused2;
    unsigned char *rdata_table;
    int rdata_table_len;
    unsigned char *client_table;
    int client_table_len;
    int rdata_table_idx;
    int *active_queue;
} SifRpcData;

extern SifRpcData D_0072C1C0;
extern int D_0072A9C0[];
extern int D_0072B1C0[];
extern int D_0072B9C0[];
extern void _request_end();
extern void _request_bind();
extern void _request_call();
extern void _request_rdata();
extern int sceSifAddCmdHandler(int a0, int a1, int a2);
extern void sceSifInitCmd(void);
extern int sceSifGetSreg(int reg);
extern int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);

void sceSifInitRpc(int mode)
{
    int *hdr;
    char *pkt;

    DIntr();
    if (D_0054A3E8[0] != 0) {
        EIntr();
        return;
    }
    D_0054A3E8[0] = 1;
    EIntr();
    sceSifInitCmd();
    DIntr();
    pkt = (char *)D_0072A9C0;
    D_0072C1C0.pkt_table = (void *)((unsigned int)pkt | 0x20000000);
    D_0072C1C0.pkt_table_len = 32;
    D_0072C1C0.unused1 = 0;
    D_0072C1C0.unused2 = 0;
    D_0072C1C0.rdata_table = (unsigned char *)((unsigned int)D_0072B1C0 | 0x20000000);
    D_0072C1C0.rdata_table_len = 32;
    D_0072C1C0.client_table = (unsigned char *)((unsigned int)D_0072B9C0 | 0x20000000);
    D_0072C1C0.client_table_len = 32;
    D_0072C1C0.rdata_table_idx = 0;
    D_0072C1C0.pid = 1;
    sceSifAddCmdHandler(0x80000008, (int)_request_end, (int)&D_0072C1C0);
    sceSifAddCmdHandler(0x80000009, (int)_request_bind, (int)&D_0072C1C0);
    sceSifAddCmdHandler(0x8000000A, (int)_request_call, (int)&D_0072C1C0);
    sceSifAddCmdHandler(0x8000000C, (int)_request_rdata, (int)&D_0072C1C0);
    EIntr();
    if (sceSifGetReg(0x80000002) != 0) {
        return;
    }
    hdr = (int *)(pkt + 0x40);
    hdr[3] = 1;
    sceSifSendCmd(0x80000002, (int)hdr, 0x10, 0, 0, 0);
    while (sceSifGetSreg(0) == 0) {}
    sceSifSetReg(0x80000002, 1);
}

extern int D_0054A3E8[];

void sceSifExitRpc(void)
{
    sceSifExitCmd();
    D_0054A3E8[0] = 0;
}

extern int DIntr();
extern int EIntr();

int *_sceRpcGetPacket(int *q)
{
    int *p;
    int i;
    int sid;

    DIntr();
    p = (int *)q[1];
    for (i = 0; i < q[2]; i++) {
        if ((p[4] & 1) == 0) {
            p[4] = (i << 16) | 5;
            ++q[0];
            if (q[0] == 1) {
                ++q[0];
                sid = 1;
            } else {
                sid = q[0];
            }
            p[5] = (int)p;
            p[6] = sid;
            EIntr();
            return p;
        }
        p += 16;
    }
    EIntr();
    return 0;
}

void _sceRpcFreePacket(void *a0)
{
    int *p = (int *)a0;
    p[6] = 0;
    p[4] &= 0xFFFFFFFE;
}

int _sceRpcGetFPacket(int *a0)
{
    int rem = a0[9] % a0[6];
    int ret = a0[5] + rem * 64;
    a0[9] = rem + 1;
    return ret;
}

int _sceRpcGetFPacket2(int *a0, int a1)
{
    if (a1 < 0) {
        goto err;
    }
    if (a1 < a0[8]) {
        goto elem;
    }
err:
    return _sceRpcGetFPacket(a0);
elem:
    return a0[7] + a1 * 64;
}

extern int iSignalSema(int a0);

void _request_end(int *pkt)
{
    int *c;
    void (*fn)(int);

    /* unsigned: the ROM's range test is sltu, not slt */
    switch ((unsigned int)pkt[8]) {
    case 0x8000000A:
        c = *(int **)&pkt[7];
        fn = (void (*)(int))c[7];
        if (fn != 0) {
            fn(c[8]);
        }
        break;
    case 0x80000009:
        c = *(int **)&pkt[7];
        c[9] = pkt[9];
        c[5] = pkt[10];
        c[6] = pkt[11];
        break;
    /* nothing to finish for an RDATA reply, but the case is present: the ROM
       dispatches with the balanced beq/sltu tree gcc only builds for more than
       two cases. */
    case 0x8000000C:
        break;
    }
    c = *(int **)&pkt[7];
    if (c[2] >= 0) {
        iSignalSema(c[2]);
    }
    _sceRpcFreePacket((void *)c[0]);
    c[0] = 0;
}

extern int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);

void _request_rdata(int *a0, int *a1)
{
    int *ret = (int *)_sceRpcGetFPacket(a1);
    int f14 = a0[5], f1c = a0[7];
    ret[5] = f14;
    ret[7] = f1c;
    ret[8] = 0x8000000C;
    isceSifSendCmd(0x80000008, (int)ret, 0x40, a0[8], a0[9], a0[10]);
}

/* the RPC server's own record: the queue list head is the word at +0x28 */
extern int CreateSema(int *self);
extern int WaitSema(int a0);
extern int DeleteSema(int a0);
extern int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);

int sceSifGetOtherData(void *cd, void *src, void *dest, int size, int mode)
{
    int *c = (int *)cd;
    /* the request fields the SIF command callback reads back (see
       _request_end): written through the volatile view of the client record,
       the same way sceSifCallRpc writes its four */
    volatile int *vc = (volatile int *)cd;
    int *pkt;
    int buf[8];
    int pid;

    pkt = _sceRpcGetPacket((int *)&D_0072C1C0);
    if (pkt == 0) {
        return -1;
    }
    pid = pkt[6];
    vc[0] = (int)pkt;
    vc[1] = pid;
    pkt[8] = (int)src;
    pkt[9] = (int)dest;
    pkt[10] = size;
    pkt[5] = (int)pkt;
    pkt[7] = (int)c;
    if ((mode & 1) == 0) {
        buf[1] = 1;
        buf[2] = 0;
        c[2] = CreateSema(buf);
        if (c[2] < 0) {
            _sceRpcFreePacket(pkt);
            return -3;
        }
        if (sceSifSendCmd(0x8000000C, (int)pkt, 0x40, 0, 0, 0) == 0) {
            _sceRpcFreePacket(pkt);
            DeleteSema(c[2]);
            return -2;
        }
        WaitSema(c[2]);
        DeleteSema(c[2]);
        return 0;
    }
    c[2] = -1;
    if (sceSifSendCmd(0x8000000C, (int)pkt, 0x40, 0, 0, 0) == 0) {
        _sceRpcFreePacket(pkt);
        return -2;
    }
    return 0;
}

void *_search_svdata(int a0, void *a1)
{
    void *n5;
    void *n3;
    for (n5 = *(void **)((char *)a1 + 0x28); n5 != 0; n5 = *(void **)((char *)n5 + 0x14)) {
        for (n3 = *(void **)((char *)n5 + 0x8); n3 != 0; n3 = *(void **)((char *)n3 + 0x38)) {
            if (*(int *)n3 == a0) {
                return n3;
            }
        }
    }
    return 0;
}

void _request_bind(int *req, int *q)
{
    int *pkt = (int *)_sceRpcGetFPacket(q);
    int f14 = req[5], f1c = req[7];
    int *sv;

    pkt[7] = f1c;
    pkt[5] = f14;
    pkt[8] = 0x80000009;
    sv = (int *)_search_svdata(req[8], q);
    if (sv == 0) {
        pkt[9] = 0;
        pkt[10] = 0;
        pkt[11] = 0;
    } else {
        pkt[9] = (int)sv;
        pkt[10] = sv[2];
        pkt[11] = sv[5];
    }
    isceSifSendCmd(0x80000008, (int)pkt, 0x40, 0, 0, 0);
}

/* the RPC server's own record: the queue list head is the word at +0x28 */
extern int CreateSema(int *self);
extern int WaitSema(int a0);
extern int DeleteSema(int a0);
extern int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1);

int sceSifBindRpc(void *cd, unsigned int sid, int mode)
{
    int *c = (int *)cd;
    /* the request fields the SIF command callback reads back (see
       _request_end): written through the volatile view of the client record,
       the same way sceSifCallRpc writes its four */
    volatile int *vc = (volatile int *)cd;
    int *pkt;
    int buf[8];
    int pid;

    c[4] = 0;
    c[9] = 0;
    pkt = _sceRpcGetPacket((int *)&D_0072C1C0);
    if (pkt == 0) {
        return -1;
    }
    pid = pkt[6];
    vc[0] = (int)pkt;
    vc[1] = pid;
    pkt[8] = sid;
    pkt[5] = (int)pkt;
    pkt[7] = (int)c;
    if ((mode & 1) == 0) {
        buf[1] = 1;
        buf[2] = 0;
        c[2] = CreateSema(buf);
        if (c[2] < 0) {
            _sceRpcFreePacket(pkt);
            return -3;
        }
        if (sceSifSendCmd(0x80000009, (int)pkt, 0x40, 0, 0, 0) == 0) {
            _sceRpcFreePacket(pkt);
            DeleteSema(c[2]);
            return -2;
        }
        WaitSema(c[2]);
        DeleteSema(c[2]);
        return 0;
    }
    c[2] = -1;
    if (sceSifSendCmd(0x80000009, (int)pkt, 0x40, 0, 0, 0) == 0) {
        _sceRpcFreePacket(pkt);
        return -2;
    }
    return 0;
}

extern void iWakeupThread(int a0);

void _request_call(int *a0)
{
    int *a5 = (int *)a0[13];
    int *a6 = (int *)a5[16];
    int *a2 = (int *)a6[3];
    if (a2 == 0) {
        a6[3] = (int)a5;
    } else {
        ((int *)a6[4])[15] = (int)a5;
    }
    a6[4] = (int)a5;
    {
        int t5 = a0[5], t7 = a0[7];
        a5[8] = t5;
        a5[7] = t7;
    }
    a5[9] = a0[8];
    a5[3] = a0[9];
    a5[10] = a0[10];
    a5[11] = a0[11];
    a5[12] = a0[12];
    a5[13] = a0[4];
    if ((int)a6[0] < 0) {
        return;
    }
    if (a6[1] != 0) {
        return;
    }
    iWakeupThread(a6[0]);
}

int sceSifCallRpc(void *cd, unsigned int rpc_number, unsigned int mode, void *sendbuf, int ssize,
                  void *recvbuf, int rsize, void *end_func, void *end_param)
{
    int *c = (int *)cd;
    /* The request fields of the client record are written through a volatile
       view: the record is shared with _request_end above, which runs from the
       SIF command callback and reads back the end function at +0x1C and its
       parameter at +0x20, tests the semaphore at +0x08 and clears the packet
       pointer at +0x00. The four stores below reach the record in the order
       written; the same view is what sceSifBindRpc and sceSifGetOtherData
       write their own two request fields through. */
    volatile int *vc = (volatile int *)cd;
    int *pkt;
    int buf[8];
    int pid;

    pkt = _sceRpcGetPacket((int *)&D_0072C1C0);
    if (pkt == 0) {
        return -1;
    }
    pid = pkt[6];
    vc[8] = (int)end_param;
    vc[0] = (int)pkt;
    vc[1] = pid;
    vc[7] = (int)end_func;
    pkt[8] = rpc_number;
    pkt[9] = ssize;
    pkt[10] = (int)recvbuf;
    pkt[11] = rsize;
    pkt[5] = (int)pkt;
    pkt[13] = c[9];
    pkt[7] = (int)c;
    if ((mode & 2) == 0) {
        if (sendbuf == recvbuf) {
            sceSifWriteBackDCache(sendbuf, (ssize < rsize) ? rsize : ssize);
        } else {
            if (ssize > 0) {
                sceSifWriteBackDCache(sendbuf, ssize);
            }
            if (rsize > 0) {
                sceSifWriteBackDCache(recvbuf, rsize);
            }
        }
    }
    if (mode & 1) {
        if (end_func == 0) {
            pkt[12] = 0;
        } else {
            pkt[12] = 1;
        }
        c[2] = -1;
        if (sceSifSendCmd(0x8000000A, (int)pkt, 0x40, (int)sendbuf, c[5], ssize) != 0) {
            return 0;
        }
        _sceRpcFreePacket(pkt);
        return -2;
    }
    buf[1] = 1;
    buf[2] = 0;
    c[2] = CreateSema(buf);
    if (c[2] < 0) {
        _sceRpcFreePacket(pkt);
        return -3;
    }
    pkt[12] = 1;
    if (sceSifSendCmd(0x8000000A, (int)pkt, 0x40, (int)sendbuf, c[5], ssize) == 0) {
        DeleteSema(c[2]);
        _sceRpcFreePacket(pkt);
        return -2;
    }
    WaitSema(c[2]);
    DeleteSema(c[2]);
    return 0;
}

int sceSifCheckStatRpc(char *a0)
{
    char *p = *(char **)a0;
    if (p == 0)
        goto ret0;
    if (*(int *)(a0 + 4) != *(int *)(p + 0x18))
        goto ret0;
    if (*(int *)(p + 0x10) & 1)
        goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}

/* Unprototyped in the K&R sense, so DIntr returns int: sceSifGetNextRequest
   passes its record and the queue routines call it bare.  The implicit int
   return is load bearing, not cosmetic: the call sets $2, which keeps the
   %hi address pseudo of D_0072C1C0 out of $2 in local-alloc and lets it tie
   with the lo_sum in $3, which is the ROM's `lui $3 / addiu $3,$3` pair. */
extern int DIntr();
/* EIntr is unprototyped for the same reason DIntr is, and it is load bearing
   in sceSifExecRequest: the call sets $2, which keeps the 0x8000000A constant
   born right after it out of $2 and puts it in $3 beside the client pointer
   in $4, the ROM's pair. */
extern int EIntr();

/* the RPC server's own record: the queue list head is the word at +0x28 */

void sceSifSetRpcQueue(int *qd, int key)
{
    int *q;

    DIntr();
    qd[0x0 / 4] = key;
    qd[0x4 / 4] = 0;
    qd[0x8 / 4] = 0;
    qd[0xC / 4] = 0;
    qd[0x10 / 4] = 0;
    qd[0x14 / 4] = 0;
    if (D_0072C1C0.active_queue == 0) {
        D_0072C1C0.active_queue = qd;
    } else {
        for (q = D_0072C1C0.active_queue; q[0x14 / 4] != 0; q = (int *)q[0x14 / 4]) {
            ;
        }
        q[0x14 / 4] = (int)qd;
    }
    EIntr();
}

/* sd is a server record and qd a data queue.  The record's 0x38 and 0x3C
   words are server-record pointers, the same type as the queue's 0x8 word,
   which is why the queue read has to stay behind those two stores and ahead
   of the 0x4..0x40 stores: those carry the callback and buffer pointers and
   the queue back-pointer, none of which the queue read can alias.  The word
   at 0x0 is the plain integer service id. */
void sceSifRegisterRpc(int *sd, int sid, void *func, void *buff, void *cfunc, void *cbuff, int *qd)
{
    int *q;

    DIntr();
    ((int **)sd)[0x3C / 4] = 0;
    ((int **)sd)[0x38 / 4] = 0;
    sd[0x0 / 4] = sid;
    ((void **)sd)[0x4 / 4] = func;
    ((void **)sd)[0x8 / 4] = buff;
    ((void **)sd)[0x10 / 4] = cfunc;
    ((void **)sd)[0x14 / 4] = cbuff;
    ((void **)sd)[0x40 / 4] = qd;
    if (((int **)qd)[0x8 / 4] == 0) {
        ((int **)qd)[0x8 / 4] = sd;
    } else {
        for (q = ((int **)qd)[0x8 / 4]; ((int **)q)[0x38 / 4] != 0; q = ((int **)q)[0x38 / 4]) {
            ;
        }
        ((int **)q)[0x38 / 4] = sd;
    }
    EIntr();
}

int *sceSifRemoveRpc(int *sd, int *qd)
{
    int *q;
    DIntr();
    q = (int *)qd[0x8 / 4];
    if (q == sd) {
        qd[0x8 / 4] = sd[0x38 / 4];
    } else {
        while (q != 0) {
            if ((int *)q[0x38 / 4] == sd) {
                q[0x38 / 4] = sd[0x38 / 4];
                break;
            }
            q = (int *)q[0x38 / 4];
        }
    }
    EIntr();
    return q;
}

int *sceSifRemoveRpcQueue(int *qd)
{
    int *q;
    DIntr();
    q = D_0072C1C0.active_queue;
    if (q == qd) {
        D_0072C1C0.active_queue = (int *)qd[0x14 / 4];
    } else {
        while (q != 0) {
            if ((int *)q[0x14 / 4] == qd) {
                q[0x14 / 4] = qd[0x14 / 4];
                break;
            }
            q = (int *)q[0x14 / 4];
        }
    }
    EIntr();
    return q;
}

int *sceSifGetNextRequest(int *self)
{
    int *p;
    int v;
    DIntr(self);
    p = (int *)self[0xC / 4];
    if (p == 0) {
        self[0x4 / 4] = 0;
        goto after;
    }
    v = p[0x3C / 4];
    self[0x4 / 4] = 1;
    self[0xC / 4] = v;
after:
    EIntr();
    return p;
}

/* Reconstruction: the SIF command packet the EE sends to the IOP kernel to
   ask for a reset.  psize is the byte count of the whole packet and dsize
   the DMA payload length; the ROM writes dsize through a 64-bit read/modify/
   write, which is get_best_mode picking DImode off the packet's 16-byte
   alignment. */
/* RECONSTRUCTION (user ruling 2026-09-22): the command id has its own
   type.  The ROM's schedule of _sceSifSendCmd needs the cid store outside
   the alias set of the int stores that fill the DMA records (the compiler's
   sched2 dump gives int set 1 and this enum set 10); with a plain int cid
   three words of that function come out in the wrong order.  Only the zero
   member is attested by the bytes; the developers' list of command ids is
   not recoverable from this member.  Re-audit (completeness pass 57): the
   public SDK naming's plain `int cid` was measured and changes 14 words of
   the object. */
typedef enum { SIF_CMD_DIAG = 0 } SifCmdId;

typedef struct {
    unsigned int psize : 8;
    unsigned int dsize : 24;
    void *dest;
    SifCmdId cid;
    unsigned int opt;
} SifCmdHeader;

typedef struct {
    SifCmdHeader header;
    int arglen;
    int mode;
    char arg[80];
} SifCmdResetData;

typedef struct {
    int src;
    int dest;
    int size;

    /* RECONSTRUCTION (user ruling 2026-09-22, same class as layout_action's
       R8Flags): the attribute word is reached through a union member.  The
       ROM's codegen of _sceSifSendCmd proves the store is an alias-set-0
       access: on the compiler's sched2 dump it must conflict with both the
       cid store and the size store while the cid store leaves the size
       store's set, and a 32-bit store gets set 0 only from a direct union
       member.  Only the word member is attested by the bytes; the
       developers' union may have carried a flag-bit view beside it.
       Re-audit (completeness pass 57): the public SDK naming's plain
       `int attr` was measured and puts three words of _sceSifSendCmd out of
       order. */
    union {
        int attr;
    } u;
} SifDmaTransfer;

/* the server function the record at +0x4 carries: it is handed the request
   number, the receive buffer and its length and returns the reply buffer */
typedef void *(*SifRpcFunc)(int fno, void *buff, int size);

extern int sceSifSetDma(int p, int a);
extern void sceSifWriteBackDCache(void *addr, int len);

void sceSifExecRequest(int *sd)
{
    int size = 0;
    void *rec;
    int *pkt;
    int i;
    SifDmaTransfer dmat[2];
    int j;
    int r;

    rec = ((SifRpcFunc)sd[0x4 / 4])(sd[0x24 / 4], (void *)sd[0x8 / 4], sd[0xC / 4]);
    if (rec != 0) {
        size = sd[0x2C / 4];
    }
    if (sd[0xC / 4] > 0) {
        sceSifWriteBackDCache((void *)sd[0x8 / 4], sd[0xC / 4]);
    }
    if (size > 0) {
        sceSifWriteBackDCache(rec, size);
    }
    DIntr();
    if (sd[0x34 / 4] & 4) {
        pkt =
            (int *)_sceRpcGetFPacket2((int *)&D_0072C1C0, (int)((unsigned int)sd[0x34 / 4] >> 16));
    } else {
        pkt = (int *)_sceRpcGetFPacket((int *)&D_0072C1C0);
    }
    EIntr();
    pkt[0x20 / 4] = 0x8000000A;
    ((void **)pkt)[0x1C / 4] = ((void **)sd)[0x1C / 4];
    if (sd[0x30 / 4] != 0) {
        while (sceSifSendCmd(0x80000008, (int)pkt, 0x40, (int)rec, sd[0x28 / 4], size) == 0) {
            ;
        }
        return;
    }
    pkt[0x18 / 4] = 0;
    i = 0;
    pkt[0x10 / 4] = 0;
    if (size > 0) {
        dmat[0].src = (int)rec;
        dmat[0].dest = sd[0x28 / 4];
        dmat[0].size = size;
        dmat[0].u.attr = 0;
        i = 1;
    }
    dmat[i].src = (int)pkt;
    dmat[i].dest = sd[0x20 / 4];
    dmat[i].size = 0x40;
    dmat[i].u.attr = 0;
    i++;
    do {
        r = sceSifSetDma((int)dmat, i);
        if (r != 0) {
            break;
        }
        for (j = 0x100000; j != -1; j--) {
            ;
        }
    } while (r == 0);
}

extern void SleepThread(void);

void sceSifRpcLoop(int *self)
{
    int *item;
    for (;;) {
        while ((item = sceSifGetNextRequest(self)) != 0) {
            sceSifExecRequest(item);
        }
        SleepThread();
    }
}

extern int CreateSema(int *self);
extern int D_0054A478;
extern int D_0054A47C[];

void _sceFsIobSemaMK(void)
{
    extern int CreateSema(int *a0);
    int args[8];
    if (D_0054A478 == -1) {
        args[5] = 0;
        args[2] = 1;
        args[1] = 1;
        D_0054A478 = CreateSema(args);
        D_0054A47C[0] = CreateSema(args);
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
    WaitSema(D_0054A478);
    p = D_0072D300;
    end = p + 0x200;
    while (p < end) {
        if (*(int *)(p + 4) == 0) {
            *(int *)(p + 4) = 0x10000000;
            SignalSema(D_0054A478);
            return (int)p;
        }
        p += 0x10;
    }
    SignalSema(D_0054A478);
    return 0;
}

void *get_iob(unsigned int i)
{
    char *p;
    _sceFsIobSemaMK();
    WaitSema(D_0054A478);
    if (i < 0x20) {
        goto ok;
    }
    SignalSema(D_0054A478);
    return 0;
ok:
    p = &D_0072D300[i * 16];
    SignalSema(D_0054A478);
    return p;
}

/* Reconstruction: the four-byte filesystem version stamp the IOP hands back
   in the RPC receive buffer; _fs_version() memcmps it against the two
   built-in stamps. */
typedef struct {
    char v[4];
} SceFsVersion;

extern char D_0072CEC0[];
/* the async request slot table _sceFs_Rcv_Intr matches a reply against, read
   and written here under the D_0054A47C guard semaphore; an entry of -1 is
   free.  The table is written by the SIF receive interrupt, so every access
   to it is volatile (C volatile ruling 2026-09-07). */
extern volatile int D_0054A3F0[];

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
            if (D_0054A3F0[i] == id) {
                D_0054A3F0[i] = -1;
                break;
            }
        }
    } else {
        iSignalSema(id);
    }
}

extern int D_0054A474[];

void _sceFsSemInit(void)
{
    int self[8];
    if (D_0054A474[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_0054A474[0] = CreateSema(self);
    }
}

int _sceFsWaitS(int arg)
{
    _sceFsSemInit();
    WaitSema(D_0054A474[0]);
    return 0;
}

void _sceFsSigSema(void)
{
    SignalSema(D_0054A474[0]);
}

extern char D_0072D300[];
extern int D_0072D500[];
extern char D_0072D528[];
extern char D_0072D530[];
extern int D_0072CE80[];
extern int D_0054A470[];
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
    WaitSema(D_0054A478);
    p = D_0072D300;
    end = D_0072D300 + 0x200;
    while (p < end) {
        ((int *)p)[1] = 0;
        p += 0x10;
    }
    SignalSema(D_0054A478);
    buf[0] = (int)D_0072CEC0;
    if (sceSifCallRpc(D_0072D500, 0xFF, 0, buf, 4, D_0072CE80, 4, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    *(SceFsVersion *)D_0072D528 = *(SceFsVersion *)((int)D_0072CE80 | 0x20000000);
    D_0054A470[0] = 1;
    return 0;
}

extern char D_0028ED0C[];
extern int D_0054A480[];
extern char D_0072D528[];
extern int memcmp();

int _fs_version(void)
{
    char *s3 = D_0028ED0C;
    char *s1 = D_0072D528;
    int s2 = 0;
    int v0;
    v0 = memcmp(s1, s3, 4);
    if (v0 == 0)
        goto done;
    v0 = memcmp(s1, (char *)D_0054A480[0], 4);
    if (v0 == 0)
        goto done;
    v0 = memcmp(s3, (char *)D_0054A480[0], 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}

extern int D_0054A470[];
extern char D_0072D528[];

int sceFsReset(void)
{
    D_0054A470[0] = 0;
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
    if (D_0054A470[0] == 0)
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
        WaitSema(D_0054A478);
        iob->inuse = 0;
        SignalSema(D_0054A478);
        return result;
    }
    rc = idx;
    WaitSema(D_0054A478);
    iob->fd = result;
    iob->inuse |= flags;
    SignalSema(D_0054A478);
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
        WaitSema(D_0054A47C[0]);
        for (i = 0; i < 0x20; i++) {
            if (D_0054A3F0[i] == -1) {
                D_0054A3F0[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(D_0054A47C[0]);
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
    if (D_0054A470[0] == 0) {
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
        WaitSema(D_0054A47C[0]);
        for (i = 0; i < 0x20; i++) {
            if (D_0054A3F0[i] == -1) {
                D_0054A3F0[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(D_0054A47C[0]);
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

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/libkernl_25EF18", sceWrite);

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
    if (D_0054A470[0] == 0) {
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
        WaitSema(D_0054A47C[0]);
        for (i = 0; i < 0x20; i++) {
            if (D_0054A3F0[i] != -1) {
                break;
            }
        }
        if (i == 0x20) {
            *(int *)D_0072C200 = 0;
        } else {
            *(int *)D_0072C200 = 1;
        }
        SignalSema(D_0054A47C[0]);
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
        WaitSema(D_0054A478);
        iob->inuse = 0;
        SignalSema(D_0054A478);
        return rc;
    }
    WaitSema(D_0054A478);
    iob->fd = rc;
    rc = iob - (SceIob *)D_0072D300;
    SignalSema(D_0054A478);
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
        WaitSema(D_0054A47C[0]);
        for (i = 0; i < 0x20; i++) {
            if (D_0054A3F0[i] == -1) {
                D_0054A3F0[i] = g[0];
                g[0] = -g[0];
                break;
            }
        }
        SignalSema(D_0054A47C[0]);
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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
    if (D_0054A470[0] == 0) {
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

extern int D_0054A484[];
extern int D_0072D580[];
extern char D_FFFFF[];

int sceSifInitIopHeap(void)
{
    int i;
    int ret;
    int val;
    for (;;) {
        ret = sceSifBindRpc(D_0072D580, 0x80000003, 0);
        if (ret < 0)
            return -1;
        val = D_0072D580[0x24 / 4];
        if (val != 0) {
            D_0054A484[0] = 0;
            break;
        }
        /* IOP-side retry back-off: spin 0x100000 times, no memory touched. */
        i = 0x100000;
        do {
            i--;
        } while (i != -1);
    }
    return 0;
}

extern int D_0072D5C0[];
extern int D_0072D600[];

int sceSifAllocIopHeap(int a0)
{
    int ret = D_0054A484[0];
    if (ret < 0)
        return 0;
    D_0072D600[0] = a0;
    ret = sceSifCallRpc(D_0072D580, 1, 0, D_0072D600, 4, D_0072D5C0, 4, 0, 0);
    if (ret >= 0)
        return D_0072D5C0[0];
    return 0;
}

extern int D_0072D640[];

int sceSifFreeIopHeap(int a0)
{
    int v2 = D_0054A484[0];
    if (v2 < 0)
        return 0;
    D_0072D640[0] = a0;
    v2 = sceSifCallRpc(D_0072D580, 2, 0, D_0072D640, 4, D_0072D5C0, 4, 0, 0);
    if (v2 < 0)
        return -1;
    return D_0072D5C0[0];
}

/* The LoadIopHeap RPC request block, reconstructed: the ROM stores the address
 * argument at offset 0, copies the module name into offset 4 and sends
 * i + 5 bytes, so the record is one int followed by a 252-byte name and the
 * sent length is the name length plus the int plus the terminator.  It is
 * spelled as a struct rather than as `char D_0072D680[]` because the ROM's
 * destination address is `addu $3,$3,$8`, base first: the C front end builds
 * `arr[j]` on an array object as PLUS_EXPR(ADDR_EXPR(arr), j), fold moves the
 * TREE_CONSTANT array address to the right and expand then emits
 * `addu dest,index,base`, while a COMPONENT_REF of a struct reaches expand
 * with the base already in a register and keeps the ROM's order. */
typedef struct {
    int addr;       /* 0x00 */
    char name[252]; /* 0x04 */
} SifHeapReq;

extern SifHeapReq D_0072D680;

int sceSifLoadIopHeap(char *name, void *addr)
{
    int i;

    if (D_0054A484[0] < 0) {
        return 0;
    }
    /* the terminator test reads the byte back out of the DESTINATION, which is
     * the value cse already holds; reading name[i] again cannot be folded away
     * because the char store may alias the char load, and the ROM loads the
     * name byte once (lbu, then sll 24 and beqz on the same register) */
    for (i = 0; i < 252; i++) {
        D_0072D680.name[i] = name[i];
        if (D_0072D680.name[i] == 0) {
            break;
        }
    }
    if (i == 252) {
        D_0072D680.name[251] = 0;
        i = 251;
    }
    D_0072D680.addr = (int)addr;
    D_0072D680.name[251] = 0;
    if (sceSifCallRpc(D_0072D580, 3, 0, &D_0072D680, i + 5, D_0072D5C0, 4, 0, 0) >= 0) {
        return D_0072D5C0[0];
    }
    return -1;
}

extern int D_0054A488[];
extern char D_0072D780[];
extern char D_0072D980[];
extern char D_0072D9A8[];

int _lf_bind(void)
{
    int i;
    int r;
    int val;
    if (D_0054A488[0] >= 0)
        goto ret0;
loop:
    r = sceSifBindRpc(D_0072D980, 0x80000006, 0);
    if (r < 0)
        return -1;
    val = *(int *)(D_0072D980 + 0x24);
    if (val == 0)
        goto delay;
    D_0054A488[0] = 0;
    r = sceSifCallRpc(D_0072D980, 0xFF, 0, 0, 0, D_0072D780, 4, 0, 0);
    if (r < 0)
        return 0xFFFEFFFF;
    __builtin_memcpy(D_0072D9A8, D_0072D780, 4);
    return 0;
delay:
    /* IOP-side retry back-off: spin 0x100000 times, no memory touched. */
    i = 0x100000;
    do {
        i--;
    } while (i != -1);
    goto loop;
ret0:
    return 0;
}

extern int D_0054A48C[];

int _lf_version(void)
{
    void *s3 = D_0028ED0C;
    void *s1 = D_0072D9A8;
    int s2 = 0;
    int v;
    if (memcmp(s1, (int)s3, 4) == 0)
        goto done;
    v = D_0054A48C[0];
    if (memcmp(s1, v, 4) == 0)
        goto done;
    v = D_0054A48C[0];
    s2 = (0 < (unsigned int)memcmp(s3, v, 4));
done:
    return s2;
}

int sceSifLoadFileReset(void)
{
    D_0054A488[0] = -1;
    memset(D_0072D9A8, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/libkernl_25EF18", _sceSifLoadModuleBuffer);

void sceSifLoadModuleBuffer(void *a0, int a1, int a2)
{
    int local[4];
    _sceSifLoadModuleBuffer(a0, a1, a2, &local);
}

int sceSifLoadStartModuleBuffer(void *a0, int a1, int a2, void *a3)
{
    return _sceSifLoadModuleBuffer(a0, a1, a2, a3);
}

extern char D_0072D788[];

/* The request's 0xFC-byte argument block.  The oversize copy below is a record
   assignment, which gcc expands inline through movstrsi; memcpy stays a call at
   -fno-builtin, so the inline ldl/ldr run can only come from a record. */
typedef struct {
    char v[0xFC];
} SceLfArgBuf;

int _sceSifLoadModule(void *name, int arglen, int args, int ret, int rpcno)
{
    char *buf;
    int r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (_lf_version() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_0072D788, (char *)name, 252);
    buf = D_0072D788 - 8;
    buf[0x103] = 0;
    if (args != 0) {
        if (arglen >= 0xFD) {
            *(SceLfArgBuf *)(buf + 0x104) = *(SceLfArgBuf *)args;
            *(int *)D_0072D780 = 0xFC;
        } else {
            memcpy(buf + 0x104, (char *)args, arglen);
            *(int *)buf = arglen;
        }
    } else {
        buf[0x104] = 0;
        *(int *)buf = 0;
    }
    if (sceSifCallRpc(D_0072D980, rpcno, 0, D_0072D780, 0x200, D_0072D780, 8, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = *(int *)(D_0072D780 + 0);
    *(int *)ret = *(int *)(D_0072D780 + 4);
    return r;
}

void sceSifLoadModule(void *a0, int a1, int a2)
{
    int local;
    _sceSifLoadModule(a0, a1, a2, (int)&local, 0);
}

void sceSifLoadStartModule(void *a0, int a1, int a2, int a3)
{
    do {
        _sceSifLoadModule(a0, a1, a2, a3, 0);
    } while (0);
}

extern char D_0072D788[];

int _sceSifLoadElfPart(void *name, int sec, int out, int rpcno)
{
    char *buf;
    int r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (_lf_version() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_0072D788, (char *)name, 252);
    buf = D_0072D788 - 8;
    buf[0x103] = 0;
    strncpy(D_0072D788 + 252, (char *)sec, 252);
    buf[0x1FF] = 0;
    if (sceSifCallRpc(D_0072D980, rpcno, 0, buf, 0x200, buf, 0x10, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    r = *(int *)buf;
    if (r == 0) {
        return 0xFFFEFFFD;
    }
    ((int *)out)[0] = r;
    ((int *)out)[1] = *(int *)(buf + 4);
    return 0;
}

int sceSifLoadElfPart(void *a0, int a1, int a2)
{
    return _sceSifLoadElfPart(a0, a1, a2, 1);
}

extern char D_00636718[];

int sceSifLoadElf(void *a0, int a1)
{
    return _sceSifLoadElfPart(a0, (int)D_00636718, a1, 1);
}

int sceSifGetIopAddr(int a0, void *a1, int a2)
{
    int r;
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_0072D780 + 0) = a0;
    *(int *)(D_0072D780 + 4) = a2;
    r = sceSifCallRpc(D_0072D980, 3, 0, D_0072D780, 0x20, D_0072D780, 0x20, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (a2 == 0) {
        *(unsigned char *)a1 = *(unsigned char *)D_0072D780;
    } else if (a2 == 1) {
        *(unsigned short *)a1 = *(unsigned short *)D_0072D780;
    } else if (a2 == 2) {
        *(int *)a1 = *(int *)D_0072D780;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}

int sceSifSetIopAddr(int a0, void *a1, int a2)
{
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    *(int *)(D_0072D780 + 0) = a0;
    *(int *)(D_0072D780 + 4) = a2;
    if (a2 == 0) {
        *(unsigned char *)(D_0072D780 + 8) = *(unsigned char *)a1;
    } else if (a2 == 1) {
        *(unsigned short *)(D_0072D780 + 8) = *(unsigned short *)a1;
    } else if (a2 == 2) {
        *(int *)(D_0072D780 + 8) = *(int *)a1;
    } else {
        return 0xFFFEFFFE;
    }
    if (sceSifCallRpc(D_0072D980, 2, 0, D_0072D780, 0x20, D_0072D780, 0x10, 0, 0) < 0) {
        return 0xFFFEFFFF;
    }
    return 0;
}

extern SifCmdResetData D_0072D9C0 __attribute__((aligned(16)));
extern void sceSifStopDma(void);

int sceSifResetIop(char *arg, int mode)
{
    SifDmaTransfer dma;
    int i;
    unsigned int addr;

    sceSifStopDma();
    addr = sceSifGetReg(0x80000000);
    D_0072D9C0.mode = mode;
    for (i = 0; arg[i] != 0; i++) {
        D_0072D9C0.arg[i] = arg[i];
    }
    D_0072D9C0.arglen = i;
    D_0072D9C0.header.dest = 0;
    D_0072D9C0.header.cid = 0x80000003;
    D_0072D9C0.header.dsize = 0;
    D_0072D9C0.header.psize = sizeof(D_0072D9C0);
    dma.src = (int)&D_0072D9C0;
    dma.dest = addr;
    dma.size = sizeof(D_0072D9C0);
    dma.u.attr = 0x44;
    sceSifWriteBackDCache(&D_0072D9C0, sizeof(D_0072D9C0));
    if (sceSifSetDma((int)&dma, 1) != 0) {
        sceSifSetReg(4, 0x10000);
        sceSifSetReg(4, 0x20000);
        sceSifSetReg(0x80000002, 0);
        sceSifSetReg(0x80000000, 0);
        return 1;
    }
    return 0;
}

int sceSifIsAliveIop(void)
{
    int t = sceSifGetReg(4) & 0x10000;
    return t != 0;
}

extern void sceResetttyinit();

int sceSifSyncIop(void)
{
    if (sceSifGetReg(4) & 0x40000) {
        sceSifSetReg(4, 0x40000);
        ((void (*)(void))sceResetttyinit)();
        return 1;
    }
    return 0;
}

extern char D_00636720[]; /* "rom0:UDNL " */
extern char D_00636730[]; /* "too long parameter '%s'\n" */
extern int printf(const char *fmt, ...);
extern int sceSifResetIop(char *arg, int mode);

int sceSifRebootIop(const char *arg)
{
    char buf[80];
    char *s = D_00636720;
    char *d;
    char *p;

    for (p = (char *)arg; *p != 0; p++) {}
    /* the ten characters of "rom0:UDNL " plus the terminator */
    if ((unsigned int)(p + 11 - (char *)arg) > 80) {
        printf(D_00636730, arg);
        return 0;
    }
    sceSifInitRpc(0);
    sceSifExitRpc();
    d = buf;
    while (*s != 0) {
        *d++ = *s++;
    }
    while (*arg != 0) {
        *d++ = *arg++;
    }
    *d = 0;
    return sceSifResetIop(buf, 0);
}

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _DumpTLB\n"
        ".type _DumpTLB, @function\n"
        "    .align 3\n"
        "_DumpTLB:\n"
        "    addiu $29, $29, -0x50\n"
        "    sd $31, 0x40($29)\n"
        "    sd $19, 0x30($29)\n"
        "    sd $18, 0x20($29)\n"
        "    sd $17, 0x10($29)\n"
        "    sd $16, 0x0($29)\n"
        "    mfc0 $17, $6\n"
        "    lui $19, %hi(D_00636750)\n"
        "    lui $18, %hi(D_00636790)\n"
        "    daddu $16, $0, $0\n"
        "    addiu $4, $19, %lo(D_00636750)\n"
        "    nop\n"
        ".L_DumpTLB002474E0:\n"
        "    bne $16, $17, .L_DumpTLB002474F0\n"
        "    daddu $5, $16, $0\n"
        "    jal scePrintf\n"
        "    nop\n"
        ".L_DumpTLB002474F0:\n"
        "    mtc0 $16, $0\n"
        "    sync.p\n"
        "    tlbr\n"
        "    sync.p\n"
        "    mfc0 $8, $2\n"
        "    mfc0 $9, $3\n"
        "    mfc0 $6, $5\n"
        "    mfc0 $7, $10\n"
        "    daddu $5, $16, $0\n"
        "    jal scePrintf\n"
        "    addiu $4, $18, %lo(D_00636790)\n"
        "    addiu $16, $16, 0x1\n"
        "    slti $2, $16, 0x30\n"
        "    bnel $2, $0, .L_DumpTLB002474E0\n"
        "    addiu $4, $19, %lo(D_00636750)\n"
        "    ld $31, 0x40($29)\n"
        "    ld $19, 0x30($29)\n"
        "    ld $18, 0x20($29)\n"
        "    ld $17, 0x10($29)\n"
        "    ld $16, 0x0($29)\n"
        "    jr $31\n"
        "    addiu $29, $29, 0x50\n"
        ".size _DumpTLB, . - _DumpTLB\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global kPutTLBEntry\n"
        ".type kPutTLBEntry, @function\n"
        "    .align 3\n"
        "kPutTLBEntry:\n"
        "    srl $3, $5, 24\n"
        "    addiu $2, $0, 0x30\n"
        "    beq $3, $2, .LTLBEntry002475BC\n"
        "    sltiu $2, $3, 0x31\n"
        "    beqz $2, .LTLBEntry00247590\n"
        "    addiu $2, $0, 0x10\n"
        "    beq $3, $2, .LTLBEntry002475CC\n"
        "    sltiu $2, $3, 0x11\n"
        "    beqz $2, .LTLBEntry00247580\n"
        "    addiu $2, $0, 0x20\n"
        "    beqz $3, .LTLBEntry002475C0\n"
        "    andi $2, $3, 0xF\n"
        "    b .LTLBEntry002475D4\n"
        "    nop\n"
        ".LTLBEntry00247580:\n"
        "    beq $3, $2, .LTLBEntry002475C0\n"
        "    andi $2, $3, 0xF\n"
        "    b .LTLBEntry002475D4\n"
        "    nop\n"
        ".LTLBEntry00247590:\n"
        "    addiu $2, $0, 0x50\n"
        "    beq $3, $2, .LTLBEntry002475CC\n"
        "    sltiu $2, $3, 0x51\n"
        "    bnez $2, .LTLBEntry002475D4\n"
        "    addiu $2, $0, 0x60\n"
        "    beq $3, $2, .LTLBEntry002475CC\n"
        "    addiu $2, $0, 0x70\n"
        "    beq $3, $2, .LTLBEntry002475CC\n"
        "    nop\n"
        "    b .LTLBEntry002475D4\n"
        "    nop\n"
        ".LTLBEntry002475BC:\n"
        "    andi $2, $3, 0xF\n"
        ".LTLBEntry002475C0:\n"
        "    sltiu $2, $2, 0x8\n"
        "    beqz $2, .LTLBEntry002475D4\n"
        "    nop\n"
        ".LTLBEntry002475CC:\n"
        "    jr $31\n"
        "    addiu $2, $0, -0x1\n"
        ".LTLBEntry002475D4:\n"
        "    mtc0 $4, $5\n"
        "    mtc0 $5, $10\n"
        "    mtc0 $6, $2\n"
        "    mtc0 $7, $3\n"
        "    sync.p\n"
        "    tlbwr\n"
        "    sync.p\n"
        "    tlbp\n"
        "    sync.p\n"
        "    mfc0 $2, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size kPutTLBEntry, . - kPutTLBEntry\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global kSetTLBEntry\n"
        "    .type kSetTLBEntry, @function\n"
        "    .align 3\n"
        "kSetTLBEntry:\n"
        "    mfc0  $2, $6\n"
        "    slt   $2, $4, $2\n"
        "    bnez  $2, 1f\n"
        "    slti  $2, $4, 0x30\n"
        "    bnez  $2, 2f\n"
        "    nop\n"
        "1:\n"
        "    jr    $31\n"
        "    addiu $2, $0, -0x1\n"
        "2:\n"
        "    mtc0  $4, $0\n"
        "    mtc0  $5, $5\n"
        "    mtc0  $6, $10\n"
        "    mtc0  $7, $2\n"
        "    mtc0  $8, $3\n"
        "    sync.p\n"
        "    tlbwi\n"
        "    sync.p\n"
        "    jr    $31\n"
        "    daddu $2, $4, $0\n"
        "    .size kSetTLBEntry, . - kSetTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global kGetTLBEntry\n"
        "    .type kGetTLBEntry, @function\n"
        "    .align 3\n"
        "kGetTLBEntry:\n"
        "    sltiu $2, $4, 0x30\n"
        "    bnez  $2, 1f\n"
        "    nop\n"
        "    jr    $31\n"
        "    addiu $2, $0, -0x1\n"
        "1:\n"
        "    mtc0  $4, $0\n"
        "    sync.p\n"
        "    tlbr\n"
        "    sync.p\n"
        "    mfc0  $2, $5\n"
        "    sw    $2, 0x0($5)\n"
        "    mfc0  $3, $10\n"
        "    sw    $3, 0x0($6)\n"
        "    mfc0  $2, $2\n"
        "    sw    $2, 0x0($7)\n"
        "    mfc0  $3, $3\n"
        "    sw    $3, 0x0($8)\n"
        "    jr    $31\n"
        "    daddu $2, $4, $0\n"
        "    .size kGetTLBEntry, . - kGetTLBEntry\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global kProbeTLBEntry\n"
        "    .type kProbeTLBEntry, @function\n"
        "    .align 3\n"
        "kProbeTLBEntry:\n"
        "    mtc0  $4, $10\n"
        "    sync.p\n"
        "    tlbp\n"
        "    sync.p\n"
        "    mfc0  $4, $0\n"
        "    bgez  $4, 1f\n"
        "    nop\n"
        "    b     2f\n"
        "    addiu $4, $0, -0x1\n"
        "1:\n"
        "    tlbr\n"
        "    sync.p\n"
        "    mfc0  $2, $5\n"
        "    sw    $2, 0x0($5)\n"
        "    mfc0  $3, $2\n"
        "    sw    $3, 0x0($6)\n"
        "    mfc0  $2, $3\n"
        "    sw    $2, 0x0($7)\n"
        "2:\n"
        "    jr    $31\n"
        "    daddu $2, $4, $0\n"
        "    .size kProbeTLBEntry, . - kProbeTLBEntry\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global kExpandScratchPad\n"
        ".type kExpandScratchPad, @function\n"
        "    .align 3\n"
        "kExpandScratchPad:\n"
        "    addiu $29, $29, -0x30\n"
        "    sd $16, 0x10($29)\n"
        "    daddu $16, $4, $0\n"
        "    andi $2, $16, 0xFFF\n"
        "    bnez $2, .LratchPad00247720\n"
        "    sd $31, 0x20($29)\n"
        "    lui $2, (0xFFFFE >> 16)\n"
        "    addiu $3, $16, -0x1\n"
        "    ori $2, $2, (0xFFFFE & 0xFFFF)\n"
        "    sltu $2, $2, $3\n"
        "    bnez $2, .LratchPad00247728\n"
        "    lui $4, (0x70004000 >> 16)\n"
        ".LratchPad00247720:\n"
        "    b .LratchPad00247810\n"
        "    addiu $2, $0, -0x1\n"
        ".LratchPad00247728:\n"
        "    daddu $5, $29, $0\n"
        "    ori $4, $4, (0x70004000 & 0xFFFF)\n"
        "    ori $6, $29, 0x4\n"
        "    jal kProbeTLBEntry\n"
        "    ori $7, $29, 0x8\n"
        "    daddu $5, $2, $0\n"
        "    bgez $5, .LratchPad00247768\n"
        "    nop\n"
        "    beqz $16, .LratchPad00247810\n"
        "    daddu $2, $0, $0\n"
        "    mfc0 $5, $6\n"
        "    addiu $2, $5, 0x1\n"
        "    mtc0 $2, $6\n"
        "    sync.p\n"
        "    b .LratchPad002477B0\n"
        "    nop\n"
        ".LratchPad00247768:\n"
        "    bnez $16, .LratchPad002477B0\n"
        "    addiu $2, $5, -0x1\n"
        "    lui $3, (0xE0010000 >> 16)\n"
        "    sll $2, $2, 13\n"
        "    addu $6, $2, $3\n"
        "    mfc0 $2, $6\n"
        "    addiu $2, $2, -0x1\n"
        "    mtc0 $2, $6\n"
        "    mtc0 $5, $0\n"
        "    mtc0 $0, $5\n"
        "    mtc0 $6, $10\n"
        "    mtc0 $0, $2\n"
        "    mtc0 $0, $3\n"
        "    sync.p\n"
        "    tlbwi\n"
        "    sync.p\n"
        "    b .LratchPad00247810\n"
        "    daddu $2, $0, $0\n"
        ".LratchPad002477B0:\n"
        "    lui $2, (0xFFFFF000 >> 16)\n"
        "    addiu $4, $16, 0x1000\n"
        "    ori $2, $2, (0xFFFFF000 & 0xFFFF)\n"
        "    lui $6, (0x70004000 >> 16)\n"
        "    and $4, $4, $2\n"
        "    sw $0, 0x0($29)\n"
        "    and $2, $16, $2\n"
        "    srl $4, $4, 6\n"
        "    srl $2, $2, 6\n"
        "    ori $4, $4, 0x1F\n"
        "    ori $2, $2, 0x1F\n"
        "    ori $6, $6, (0x70004000 & 0xFFFF)\n"
        "    sw $2, 0x4($29)\n"
        "    sw $4, 0x8($29)\n"
        "    mtc0 $5, $0\n"
        "    daddu $3, $0, $0\n"
        "    mtc0 $3, $5\n"
        "    mtc0 $6, $10\n"
        "    mtc0 $2, $2\n"
        "    mtc0 $4, $3\n"
        "    sync.p\n"
        "    tlbwi\n"
        "    sync.p\n"
        "    daddu $2, $5, $0\n"
        ".LratchPad00247810:\n"
        "    ld $31, 0x20($29)\n"
        "    ld $16, 0x10($29)\n"
        "    jr $31\n"
        "    addiu $29, $29, 0x30\n"
        ".size kExpandScratchPad, . - kExpandScratchPad\n"
        "    .set reorder\n"
        "    .set at\n");

extern int D_0054A490[];
extern void SetVTLBRefillHandler();
extern void _kTLBException(void);

void *SetTLBHandler(void *a0)
{
    D_0054A490[0] = (int)a0;
    SetVTLBRefillHandler(1, _kTLBException);
    SetVTLBRefillHandler(2, _kTLBException);
    SetVTLBRefillHandler(3, _kTLBException);
    return a0;
}

extern char _kDebugException[];
extern int D_0054A498[];
extern void SetVCommonHandler();

int SetDebugHandler(int a0, int a1)
{
    int old;
    int orig = a0;
    unsigned int err = 0xFFFFFFFF;
    if ((unsigned)(a0 - 1) >= 13) {
        return (int)err;
    }
    old = D_0054A498[orig];
    D_0054A498[orig] = a1;
    if ((unsigned)(a0 - 1) < 3) {
        SetVTLBRefillHandler(orig, (void *)_kDebugException);
    } else {
        SetVCommonHandler(orig, (void *)_kDebugException);
    }
    return old;
}

/* census setup, intr.o's file static (sce/libkernl/libkernl_100110 holds initsys.o's
   global of the name); the hand-typed leaf takes a local label. */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel setup, local\n"
        "    addiu      $3, $0, 0x74\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel setup\n"
        "    .set reorder\n"
        "    .set at\n");

extern int D_0054A4D8[];
static void setup(int x, int y);

void InitTLBFunctions(void)
{
    int *p = D_0054A4D8;
    unsigned int i = 0;
    do {
        i++;
        setup(p[0], p[1]);
        p += 2;
    } while (i < 6);
}

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel PutTLBEntry\n"
        "    addiu      $3, $0, 0x55\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel PutTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel iPutTLBEntry\n"
        "    addiu      $3, $0, -0x55\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel iPutTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel SetTLBEntry\n"
        "    addiu      $3, $0, 0x56\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel SetTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel iSetTLBEntry\n"
        "    addiu      $3, $0, -0x56\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel iSetTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel GetTLBEntry\n"
        "    addiu      $3, $0, 0x57\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel GetTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel iGetTLBEntry\n"
        "    addiu      $3, $0, -0x57\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel iGetTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel ProbeTLBEntry\n"
        "    addiu      $3, $0, 0x58\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel ProbeTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel iProbeTLBEntry\n"
        "    addiu      $3, $0, -0x58\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel iProbeTLBEntry\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel ExpandScratchPad\n"
        "    addiu      $3, $0, 0x59\n"
        "    syscall    0\n"
        "    jr         $31\n"
        "    nop\n"
        "endlabel ExpandScratchPad\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

/* tlbtrap.s:24: the TLB refill / invalid exception entry, hand-written assembly in the SDK (the January listing
   attributes every instruction to tlbtrap.s, not to a C file). */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel _kTLBException\n"
        "    lui        $26, %hi(D_0072EA40)\n"
        "    addiu      $26, $26, %lo(D_0072EA40)\n"
        "    sq         $1, 0x10($26)\n"
        "    sq         $2, 0x20($26)\n"
        "    sq         $3, 0x30($26)\n"
        "    sq         $4, 0x40($26)\n"
        "    sq         $5, 0x50($26)\n"
        "    sq         $6, 0x60($26)\n"
        "    sq         $7, 0x70($26)\n"
        "    sq         $8, 0x80($26)\n"
        "    sq         $9, 0x90($26)\n"
        "    sq         $10, 0xA0($26)\n"
        "    sq         $11, 0xB0($26)\n"
        "    sq         $12, 0xC0($26)\n"
        "    sq         $13, 0xD0($26)\n"
        "    sq         $14, 0xE0($26)\n"
        "    sq         $15, 0xF0($26)\n"
        "    sq         $16, 0x100($26)\n"
        "    sq         $17, 0x110($26)\n"
        "    sq         $18, 0x120($26)\n"
        "    sq         $19, 0x130($26)\n"
        "    sq         $20, 0x140($26)\n"
        "    sq         $21, 0x150($26)\n"
        "    sq         $22, 0x160($26)\n"
        "    sq         $23, 0x170($26)\n"
        "    sq         $24, 0x180($26)\n"
        "    sq         $25, 0x190($26)\n"
        "    sq         $28, 0x1C0($26)\n"
        "    sq         $29, 0x1D0($26)\n"
        "    sq         $30, 0x1E0($26)\n"
        "    sq         $31, 0x1F0($26)\n"
        "    mfhi       $2\n"
        "    lui        $1, %hi(D_0072EC40)\n"
        "    sd         $2, %lo(D_0072EC40)($1)\n"
        "    mfhi1      $2\n"
        "    lui        $1, %hi(D_0072EC48)\n"
        "    sd         $2, %lo(D_0072EC48)($1)\n"
        "    mflo       $2\n"
        "    lui        $1, %hi(D_0072EC50)\n"
        "    sd         $2, %lo(D_0072EC50)($1)\n"
        "    mflo1      $2\n"
        "    lui        $1, %hi(D_0072EC58)\n"
        "    sd         $2, %lo(D_0072EC58)($1)\n"
        "    mfsa       $2\n"
        "    lui        $1, %hi(D_0072EC60)\n"
        "    sd         $2, %lo(D_0072EC60)($1)\n"
        "    mfc0       $4, $12\n"
        "    mfc0       $5, $13\n"
        "    mfc0       $6, $14\n"
        "    mfc0       $7, $8\n"
        "    lui        $8, %hi(D_0072EA40)\n"
        "    addiu      $8, $8, %lo(D_0072EA40)\n"
        "    lui        $1, %hi(D_0072EC68)\n"
        "    sw         $6, %lo(D_0072EC68)($1)\n"
        "    lui        $1, %hi(_xlaunch)\n"
        "    addiu      $1, $1, %lo(_xlaunch)\n"
        "    mtc0       $1, $14\n"
        "    sync.p\n"
        "    mfc0       $1, $12\n"
        "    addiu      $2, $0, -0x2\n"
        "    and        $1, $1, $2\n"
        "    mtc0       $1, $12\n"
        "    sync.p\n"
        "    eret\n"
        "endlabel _kTLBException\n"
        "    .set reorder\n"
        "    .set at\n");

/* tlbtrap.s: the launcher the TLB trap path enters with its own stack,
   hand-written assembly in the SDK. */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel _xlaunch\n"
        "    lui        $1, %hi(D_0054A490)\n"
        "    lw         $1, %lo(D_0054A490)($1)\n"
        "    lui        $29, %hi(D_0072EA40)\n"
        "    jalr       $1\n"
        "    addiu     $29, $29, %lo(D_0072EA40)\n"
        "    addiu      $3, $0, -0x54\n"
        "    syscall    0\n"
        "endlabel _xlaunch\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

/* tlbtrap.s:103: the TLB trap handler's return path, hand-written
   assembly in the SDK (the January listing attributes every instruction to
   tlbtrap.s, not to a C file); transcribed the way this file already
   carries its syscall leaves. */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel _kExitTLBHandler\n"
        "    mfc0       $1, $12\n"
        "    addiu      $26, $0, -0x1C\n"
        "    and        $1, $1, $26\n"
        "    mtc0       $1, $12\n"
        "    sync.p\n"
        "    lui        $2, %hi(D_0072EC68)\n"
        "    lw         $2, %lo(D_0072EC68)($2)\n"
        "    mtc0       $2, $14\n"
        "    sync.p\n"
        "    lui        $2, %hi(D_0072EC40)\n"
        "    ld         $2, %lo(D_0072EC40)($2)\n"
        "    mthi       $2\n"
        "    lui        $2, %hi(D_0072EC48)\n"
        "    ld         $2, %lo(D_0072EC48)($2)\n"
        "    mthi1      $2\n"
        "    lui        $2, %hi(D_0072EC50)\n"
        "    ld         $2, %lo(D_0072EC50)($2)\n"
        "    mtlo       $2\n"
        "    lui        $2, %hi(D_0072EC58)\n"
        "    ld         $2, %lo(D_0072EC58)($2)\n"
        "    mtlo1      $2\n"
        "    lui        $2, %hi(D_0072EC60)\n"
        "    ld         $2, %lo(D_0072EC60)($2)\n"
        "    mtsa       $2\n"
        "    sync.p\n"
        "    lui        $26, %hi(D_0072EA40)\n"
        "    addiu      $26, $26, %lo(D_0072EA40)\n"
        "    lq         $1, 0x10($26)\n"
        "    lq         $2, 0x20($26)\n"
        "    lq         $3, 0x30($26)\n"
        "    lq         $4, 0x40($26)\n"
        "    lq         $5, 0x50($26)\n"
        "    lq         $6, 0x60($26)\n"
        "    lq         $7, 0x70($26)\n"
        "    lq         $8, 0x80($26)\n"
        "    lq         $9, 0x90($26)\n"
        "    lq         $10, 0xA0($26)\n"
        "    lq         $11, 0xB0($26)\n"
        "    lq         $12, 0xC0($26)\n"
        "    lq         $13, 0xD0($26)\n"
        "    lq         $14, 0xE0($26)\n"
        "    lq         $15, 0xF0($26)\n"
        "    lq         $16, 0x100($26)\n"
        "    lq         $17, 0x110($26)\n"
        "    lq         $18, 0x120($26)\n"
        "    lq         $19, 0x130($26)\n"
        "    lq         $20, 0x140($26)\n"
        "    lq         $21, 0x150($26)\n"
        "    lq         $22, 0x160($26)\n"
        "    lq         $23, 0x170($26)\n"
        "    lq         $24, 0x180($26)\n"
        "    lq         $25, 0x190($26)\n"
        "    lq         $28, 0x1C0($26)\n"
        "    lq         $29, 0x1D0($26)\n"
        "    lq         $30, 0x1E0($26)\n"
        "    lq         $31, 0x1F0($26)\n"
        "    mfc0       $26, $12\n"
        "    ori        $26, $26, 0x13\n"
        "    mtc0       $26, $12\n"
        "    sync.p\n"
        "    eret\n"
        "endlabel _kExitTLBHandler\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

/* tlbtrap.s:162: the debug exception entry, hand-written assembly in the
   SDK (the January listing attributes every instruction to tlbtrap.s, not
   to a C file); D_0026537C is the handler's own local label. */
__asm__(".section .text\n"
        "    .set at\n"
        "    .set noreorder\n"
        "    .align 3\n"
        "glabel _kDebugException\n"
        "    lui        $26, %hi(D_0072EA40)\n"
        "    addiu      $26, $26, %lo(D_0072EA40)\n"
        "    sq         $1, 0x10($26)\n"
        "    sq         $2, 0x20($26)\n"
        "    sq         $3, 0x30($26)\n"
        "    sq         $4, 0x40($26)\n"
        "    sq         $5, 0x50($26)\n"
        "    sq         $6, 0x60($26)\n"
        "    sq         $7, 0x70($26)\n"
        "    sq         $8, 0x80($26)\n"
        "    sq         $9, 0x90($26)\n"
        "    sq         $10, 0xA0($26)\n"
        "    sq         $11, 0xB0($26)\n"
        "    sq         $12, 0xC0($26)\n"
        "    sq         $13, 0xD0($26)\n"
        "    sq         $14, 0xE0($26)\n"
        "    sq         $15, 0xF0($26)\n"
        "    sq         $16, 0x100($26)\n"
        "    sq         $17, 0x110($26)\n"
        "    sq         $18, 0x120($26)\n"
        "    sq         $19, 0x130($26)\n"
        "    sq         $20, 0x140($26)\n"
        "    sq         $21, 0x150($26)\n"
        "    sq         $22, 0x160($26)\n"
        "    sq         $23, 0x170($26)\n"
        "    sq         $24, 0x180($26)\n"
        "    sq         $25, 0x190($26)\n"
        "    sq         $28, 0x1C0($26)\n"
        "    sq         $29, 0x1D0($26)\n"
        "    sq         $30, 0x1E0($26)\n"
        "    sq         $31, 0x1F0($26)\n"
        "    mfhi       $2\n"
        "    lui        $1, %hi(D_0072EC40)\n"
        "    sd         $2, %lo(D_0072EC40)($1)\n"
        "    mfhi1      $2\n"
        "    lui        $1, %hi(D_0072EC48)\n"
        "    sd         $2, %lo(D_0072EC48)($1)\n"
        "    mflo       $2\n"
        "    lui        $1, %hi(D_0072EC50)\n"
        "    sd         $2, %lo(D_0072EC50)($1)\n"
        "    mflo1      $2\n"
        "    lui        $1, %hi(D_0072EC58)\n"
        "    sd         $2, %lo(D_0072EC58)($1)\n"
        "    mfsa       $2\n"
        "    lui        $1, %hi(D_0072EC60)\n"
        "    sd         $2, %lo(D_0072EC60)($1)\n"
        "    mfc0       $4, $12\n"
        "    mfc0       $5, $13\n"
        "    mfc0       $6, $14\n"
        "    mfc0       $7, $8\n"
        "    mfc0       $8, $23\n"
        "    lui        $9, %hi(D_0072EA40)\n"
        "    addiu      $9, $9, %lo(D_0072EA40)\n"
        "    lui        $1, %hi(D_0026537C)\n"
        "    addiu      $1, $1, %lo(D_0026537C)\n"
        "    mtc0       $1, $14\n"
        "    sync.p\n"
        "    mfc0       $1, $12\n"
        "    addiu      $2, $0, -0x2\n"
        "    and        $1, $1, $2\n"
        "    mtc0       $1, $12\n"
        "    sync.p\n"
        "    eret\n"
        ".align 2\n"
        "alabel D_0026537C\n"
        "    andi       $2, $5, 0x7C\n"
        "    lui        $1, %hi(D_0054A498)\n"
        "    addu       $1, $1, $2\n"
        "    lw         $1, %lo(D_0054A498)($1)\n"
        "    lui        $29, %hi(D_0072EA40)\n"
        "    jalr       $1\n"
        "    addiu     $29, $29, %lo(D_0072EA40)\n"
        "    break      1023, 1023\n"
        "endlabel _kDebugException\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

void _set_sreg(int *a0, int *a1)
{
    ((int *)a1[7])[a0[4]] = a0[5];
}

void _change_addr(int *a0, int *a1)
{
    a1[2] = a0[4];
}

extern int D_0072EE80[];

int sceSifGetSreg(int a0)
{
    return D_0072EE80[a0];
}

extern int D_0072EE80[];

int sceSifSetSreg(int a0, int a1)
{
    D_0072EE80[a0] = a1;
    return a1;
}

extern int D_0072ED58[];

void *sceSifGetDataTable(void)
{
    return D_0072ED58;
}

INCLUDE_ASM("asm/nonmatchings/sce/libkernl/libkernl_25EF18", sceSifInitCmd);

extern int D_0054A508[];
extern int D_0072ED54[];
extern int DisableDmac(int a0);
extern int RemoveDmacHandler(int a0, int a1);

void sceSifExitCmd(void)
{
    DisableDmac(5);
    RemoveDmacHandler(5, D_0072ED54[0]);
    D_0054A508[0] = 0;
}

extern int D_0072ED58[];

int sceSifSetCmdBuffer(int a0, int a1)
{
    int old = D_0072ED58[5];
    D_0072ED58[5] = a0;
    D_0072ED58[6] = a1;
    return old;
}

int sceSifSetSysCmdBuffer(int a0, int a1)
{
    int old = D_0072ED58[3];
    D_0072ED58[3] = a0;
    D_0072ED58[4] = a1;
    return old;
}

extern int D_0072ED64[];
extern int D_0072ED6C[];

int sceSifAddCmdHandler(int a0, int a1, int a2)
{
    int off = a0 * 8;
    int *p;
    if (a0 >= 0)
        goto pos;
    a0 = D_0072ED64[0];
    goto done;
pos:
    a0 = D_0072ED6C[0];
done:
    off += a0;
    p = (int *)off;
    p[0] = a1;
    p[1] = a2;
}

void sceSifRemoveCmdHandler(int a0)
{
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_0072ED64[0];
    } else {
        a0 = D_0072ED6C[0];
    }
    off += a0;
    *(int *)off = 0;
}

extern int D_0072ED60;
extern int isceSifSetDma(int p, int a);

int _sceSifSendCmd(int cid, int mode, int pkt, int pktsize, int src, int dest, int size)
{
    SifDmaTransfer dmat[2];
    SifCmdHeader *header;
    int count;

    if (pktsize < 16 || pktsize > 112) {
        return 0;
    }
    header = (SifCmdHeader *)pkt;
    count = 0;
    if (size > 0) {
        header->dsize = size;
        dmat[0].src = src;
        dmat[0].dest = dest;
        dmat[0].size = size;
        header->dest = dest;
        dmat[0].u.attr = 0;
        count = 1;
        if (mode & 4) {
            sceSifWriteBackDCache((void *)src, size);
        }
    } else {
        header->dsize = 0;
        header->dest = 0;
    }
    dmat[count].src = pkt;
    dmat[count].dest = D_0072ED60;
    dmat[count].size = pktsize;
    header->cid = cid;
    header->psize = pktsize;
    dmat[count].u.attr = 0x44;
    count++;
    sceSifWriteBackDCache((void *)pkt, pktsize);
    if (mode & 1) {
        return isceSifSetDma((int)dmat, count);
    }
    return sceSifSetDma((int)dmat, count);
}

int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
    return _sceSifSendCmd(a0, 0, a1, a2, a3, t0, t1);
}

int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
    return _sceSifSendCmd(a0, 1, a1, a2, a3, t0, t1);
}

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _sceSifCmdIntrHdlr\n"
        ".type _sceSifCmdIntrHdlr, @function\n"
        "    .align 3\n"
        "_sceSifCmdIntrHdlr:\n"
        "    addiu $29, $29, -0x90\n"
        "    sd $16, 0x70($29)\n"
        "    sd $31, 0x80($29)\n"
        "    jal EIntr\n"
        "    nop\n"
        "    lui $3, %hi(D_0072ED58)\n"
        "    lw $7, %lo(D_0072ED58)($3)\n"
        "    addiu $16, $3, %lo(D_0072ED58)\n"
        "    lbu $2, 0x0($7)\n"
        "    andi $5, $2, 0xFF\n"
        "    beqz $5, .LIntrHdlr002483E8\n"
        "    daddu $2, $0, $0\n"
        "    addiu $2, $5, 0xF\n"
        "    addiu $3, $0, -0x1\n"
        "    addiu $4, $5, 0x1E\n"
        "    slt $3, $3, $2\n"
        "    movn $4, $2, $3\n"
        "    daddu $6, $7, $0\n"
        "    sra $5, $4, 4\n"
        "    sb $0, 0x0($7)\n"
        "    blez $5, .LIntrHdlr0024834C\n"
        "    daddu $4, $5, $0\n"
        "    daddu $3, $29, $0\n"
        "    nop\n"
        ".LIntrHdlr00248330:\n"
        "    lq $2, 0x0($6)\n"
        "    addiu $4, $4, -0x1\n"
        "    addiu $6, $6, 0x10\n"
        "    sq $2, 0x0($3)\n"
        "    addiu $3, $3, 0x10\n"
        "    bnez $4, .LIntrHdlr00248330\n"
        "    nop\n"
        ".LIntrHdlr0024834C:\n"
        "    jal isceSifSetDChain\n"
        "    nop\n"
        "    lw $3, 0x8($29)\n"
        "    bgez $3, .LIntrHdlr002483A8\n"
        "    nop\n"
        "    lw $2, 0x8($29)\n"
        "    lui $3, (0x7FFFFFFF >> 16)\n"
        "    ori $3, $3, (0x7FFFFFFF & 0xFFFF)\n"
        "    lw $4, 0x10($16)\n"
        "    and $5, $2, $3\n"
        "    slt $4, $5, $4\n"
        "    beqz $4, .LIntrHdlr002483DC\n"
        "    sll $2, $5, 3\n"
        "    lw $3, 0xC($16)\n"
        "    addu $2, $2, $3\n"
        "    lw $6, 0x0($2)\n"
        "    beqz $6, .LIntrHdlr002483DC\n"
        "    nop\n"
        "    lw $5, 0x4($2)\n"
        "    jalr $6\n"
        "    daddu $4, $29, $0\n"
        "    b .LIntrHdlr002483DC\n"
        "    nop\n"
        ".LIntrHdlr002483A8:\n"
        "    lw $5, 0x8($29)\n"
        "    lw $2, 0x18($16)\n"
        "    slt $2, $5, $2\n"
        "    beqz $2, .LIntrHdlr002483DC\n"
        "    sll $2, $5, 3\n"
        "    lw $3, 0x14($16)\n"
        "    addu $2, $2, $3\n"
        "    lw $6, 0x0($2)\n"
        "    beqz $6, .LIntrHdlr002483DC\n"
        "    nop\n"
        "    lw $5, 0x4($2)\n"
        "    jalr $6\n"
        "    daddu $4, $29, $0\n"
        ".LIntrHdlr002483DC:\n"
        "    sync\n"
        "    ei\n"
        "    daddu $2, $0, $0\n"
        ".LIntrHdlr002483E8:\n"
        "    ld $31, 0x80($29)\n"
        "    ld $16, 0x70($29)\n"
        "    jr $31\n"
        "    addiu $29, $29, 0x90\n"
        ".size _sceSifCmdIntrHdlr, . - _sceSifCmdIntrHdlr\n"
        "    .set reorder\n"
        "    .set at\n");

/* The four `.align 2` directives below are the ones the shipped function's own
 * asm carries at its internal labels; they emit no bytes here, but without them
 * the period assembler inserts two nops before the first loop's closing bgtz
 * as soon as any neighbouring member in this object is compiled C rather than
 * assembled. */
__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global sceSifWriteBackDCache\n"
        ".type sceSifWriteBackDCache, @function\n"
        "    .align 3\n"
        "sceSifWriteBackDCache:\n"
        "    lui $25, (0xFFFFFFC0 >> 16)\n"
        "    ori $25, $25, (0xFFFFFFC0 & 0xFFFF)\n"
        "    blez $5, .L00265A380024849C\n"
        "    addu $10, $4, $5\n"
        "    and $8, $4, $25\n"
        "    addiu $10, $10, -0x1\n"
        "    and $9, $10, $25\n"
        "    subu $10, $9, $8\n"
        "    srl $11, $10, 6\n"
        "    addiu $11, $11, 0x1\n"
        "    andi $9, $11, 0x7\n"
        "    beqz $9, .L00265A3800248448\n"
        "    srl $10, $11, 3\n"
        "    .align 2\n"
        ".L00265A380024842C:\n"
        "    sync\n"
        "    cache 0x18, 0x0($8)\n"
        "    sync\n"
        "    addiu $9, $9, -0x1\n"
        "    nop\n"
        "    bgtz $9, .L00265A380024842C\n"
        "    addiu $8, $8, 0x40\n"
        "    .align 2\n"
        ".L00265A3800248448:\n"
        "    beqz $10, .L00265A380024849C\n"
        "    .align 2\n"
        ".L00265A380024844C:\n"
        "    addiu $10, $10, -0x1\n"
        "    sync\n"
        "    cache 0x18, 0x0($8)\n"
        "    sync\n"
        "    cache 0x18, 0x40($8)\n"
        "    sync\n"
        "    cache 0x18, 0x80($8)\n"
        "    sync\n"
        "    cache 0x18, 0xC0($8)\n"
        "    sync\n"
        "    cache 0x18, 0x100($8)\n"
        "    sync\n"
        "    cache 0x18, 0x140($8)\n"
        "    sync\n"
        "    cache 0x18, 0x180($8)\n"
        "    sync\n"
        "    cache 0x18, 0x1C0($8)\n"
        "    sync\n"
        "    bgtz $10, .L00265A380024844C\n"
        "    addiu $8, $8, 0x200\n"
        "    .align 2\n"
        ".L00265A380024849C:\n"
        "    jr $31\n"
        "    nop\n"
        "    jr $31\n"
        ".size sceSifWriteBackDCache, . - sceSifWriteBackDCache\n"
        "    .set reorder\n"
        "    .set at\n");

/* The stray jr that closes the block above has no delay-slot instruction of
   its own: the next input, libcdvd.a(cdvd000), starts with CB_DelayTh at
   0x265AE8, whose first word sits in that slot.  The member boundary is the
   object boundary, as the retail link had it. */
