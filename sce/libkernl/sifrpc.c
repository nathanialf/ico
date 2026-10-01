/* Vendor SCE library member: libkernl.a(sifrpc.o).  MAIN.MAP names the
 * member and its .text size (0xF60), which tiles the shipped ELF from one
 * retail function start to the next; VMA 0x25F770..0x2606D0,
 * 22 functions. */

#include <eekernel.h>
#include <sifrpc.h>
#include <string.h>
#include <sifcmd.h>
#include <libkernl_internal.h>

/* sifrpc.o's .data: set once sceSifInitRpc has run, cleared by sceSifExitRpc */
static int rpc_inited = 0;

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

/* sifrpc.o's .bss, in the ROM's order: the 32 64-byte command packets, the
   32 receive-data slots and the 32 client slots sceSifInitRpc hands the
   record (each table a cache line per entry, and 64-aligned for the SIF DMA),
   then the record itself. */
static int rpc_pkt_table[512] __attribute__((aligned(64)));

static int rpc_rdata_table[512] __attribute__((aligned(64)));

static int rpc_client_table[512] __attribute__((aligned(64)));

static SifRpcData rpc_data;

void sceSifInitRpc(int mode)
{
    int *hdr;
    char *pkt;

    DIntr();
    if (rpc_inited != 0) {
        EIntr();
        return;
    }
    rpc_inited = 1;
    EIntr();
    sceSifInitCmd();
    DIntr();
    pkt = (char *)rpc_pkt_table;
    rpc_data.pkt_table = (void *)((unsigned int)pkt | 0x20000000);
    rpc_data.pkt_table_len = 32;
    rpc_data.unused1 = 0;
    rpc_data.unused2 = 0;
    rpc_data.rdata_table = (unsigned char *)((unsigned int)rpc_rdata_table | 0x20000000);
    rpc_data.rdata_table_len = 32;
    rpc_data.client_table = (unsigned char *)((unsigned int)rpc_client_table | 0x20000000);
    rpc_data.client_table_len = 32;
    rpc_data.rdata_table_idx = 0;
    rpc_data.pid = 1;
    sceSifAddCmdHandler(0x80000008, (int)_request_end, (int)&rpc_data);
    sceSifAddCmdHandler(0x80000009, (int)_request_bind, (int)&rpc_data);
    sceSifAddCmdHandler(0x8000000A, (int)_request_call, (int)&rpc_data);
    sceSifAddCmdHandler(0x8000000C, (int)_request_rdata, (int)&rpc_data);
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

void sceSifExitRpc(void)
{
    sceSifExitCmd();
    rpc_inited = 0;
}

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

int sceSifGetOtherData(void *cd, void *src, void *dest, int size, int mode)
{
    int *c = (int *)cd;
    /* the request fields the SIF command callback reads back (see
       _request_end): written through the volatile view of the client record,
       the same way sceSifCallRpc writes its four */
    volatile int *vc = (volatile int *)cd;
    int *pkt;
    struct SemaParam buf;
    int pid;

    pkt = _sceRpcGetPacket((int *)&rpc_data);
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
        buf.maxCount = 1;
        buf.initCount = 0;
        c[2] = CreateSema(&buf);
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

int sceSifBindRpc(void *cd, unsigned int sid, int mode)
{
    int *c = (int *)cd;
    /* the request fields the SIF command callback reads back (see
       _request_end): written through the volatile view of the client record,
       the same way sceSifCallRpc writes its four */
    volatile int *vc = (volatile int *)cd;
    int *pkt;
    struct SemaParam buf;
    int pid;

    c[4] = 0;
    c[9] = 0;
    pkt = _sceRpcGetPacket((int *)&rpc_data);
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
        buf.maxCount = 1;
        buf.initCount = 0;
        c[2] = CreateSema(&buf);
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
    struct SemaParam buf;
    int pid;

    pkt = _sceRpcGetPacket((int *)&rpc_data);
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
    buf.maxCount = 1;
    buf.initCount = 0;
    c[2] = CreateSema(&buf);
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
    if (rpc_data.active_queue == 0) {
        rpc_data.active_queue = qd;
    } else {
        for (q = rpc_data.active_queue; q[0x14 / 4] != 0; q = (int *)q[0x14 / 4]) {
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
    q = rpc_data.active_queue;
    if (q == qd) {
        rpc_data.active_queue = (int *)qd[0x14 / 4];
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
    DIntr();
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

/* the server function the record at +0x4 carries: it is handed the request
   number, the receive buffer and its length and returns the reply buffer */
typedef void *(*SifRpcFunc)(int fno, void *buff, int size);

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
        pkt = (int *)_sceRpcGetFPacket2((int *)&rpc_data, (int)((unsigned int)sd[0x34 / 4] >> 16));
    } else {
        pkt = (int *)_sceRpcGetFPacket((int *)&rpc_data);
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
