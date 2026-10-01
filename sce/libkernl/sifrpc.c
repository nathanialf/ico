/* libkernl.a(sifrpc.o) */

#include <eekernel.h>
#include <sifrpc.h>
#include <string.h>
#include <sifcmd.h>
#include <libkernl_internal.h>

/* sifrpc.o's .data: set once sceSifInitRpc has run, cleared by sceSifExitRpc */
static int rpc_inited = 0; /* derived name */

/* The words every RPC packet carries after the command header. */
typedef struct {
    SifCmdHeader header; /* 0x00 */
    int recId;           /* 0x10, the slot index << 16 | 5; bit 0 marks the slot taken */
    void *pktAddr;       /* 0x14, the packet's own address on the sending side */
    int rpcId;           /* 0x18 */
} SifRpcPktHeader;       /* derived name */

/* a 64-byte packet slot: the header, then the command's own words (the
   records below) */
typedef struct {
    SifRpcPktHeader rpch;
    char body[36];
} SifRpcPkt; /* derived name */

/* the bind request */
typedef struct {
    SifRpcPktHeader rpch;
    void *client;     /* 0x1C */
    unsigned int sid; /* 0x20 */
} SifRpcBindPkt;      /* derived name */

/* the request for data from the other side */
typedef struct {
    SifRpcPktHeader rpch;
    void *receive;    /* 0x1C, the requester's receive record */
    void *src;        /* 0x20 */
    void *dest;       /* 0x24 */
    int size;         /* 0x28 */
} SifRpcOtherDataPkt; /* derived name */

/* the answer that finishes a request: cid is the request's command, and a
   bind answer carries the server's record and buffers */
typedef struct {
    SifRpcPktHeader rpch;
    void *client;        /* 0x1C */
    unsigned int cid;    /* 0x20 */
    unsigned int server; /* 0x24 */
    unsigned int buff;   /* 0x28 */
    unsigned int cbuff;  /* 0x2C */
} SifRpcRendPkt;         /* derived name */

/* sifrpc.o's RPC state record.  Field names follow the public SDK naming of
   this record; the packet table is a void *, the two byte tables unsigned
   char *. */
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
    sceSifQueueData *active_queue;
} SifRpcData;

/* sifrpc.o's .bss, in link order: the 32 64-byte command packets, the
   32 receive-data slots and the 32 client slots sceSifInitRpc hands the
   record (each table a cache line per entry, and 64-aligned for the SIF DMA),
   then the record itself. */
static SifRpcPkt rpc_pkt_table[32] __attribute__((aligned(64))); /* derived name */

static int rpc_rdata_table[512] __attribute__((aligned(64))); /* derived name */

static int rpc_client_table[512] __attribute__((aligned(64))); /* derived name */

static SifRpcData rpc_data; /* derived name */

void sceSifInitRpc(int mode)
{
    SifCmdHeader *hdr;

    DIntr();
    if (rpc_inited != 0) {
        EIntr();
        return;
    }
    rpc_inited = 1;
    EIntr();
    sceSifInitCmd();
    DIntr();
    rpc_data.pkt_table = (void *)((unsigned int)rpc_pkt_table | 0x20000000);
    rpc_data.pkt_table_len = 32;
    rpc_data.unused1 = 0;
    rpc_data.unused2 = 0;
    rpc_data.rdata_table = (unsigned char *)((unsigned int)rpc_rdata_table | 0x20000000);
    rpc_data.rdata_table_len = 32;
    rpc_data.client_table = (unsigned char *)((unsigned int)rpc_client_table | 0x20000000);
    rpc_data.client_table_len = 32;
    rpc_data.rdata_table_idx = 0;
    rpc_data.pid = 1;
    sceSifAddCmdHandler(0x80000008, _request_end, &rpc_data);
    sceSifAddCmdHandler(0x80000009, _request_bind, &rpc_data);
    sceSifAddCmdHandler(0x8000000A, _request_call, &rpc_data);
    sceSifAddCmdHandler(0x8000000C, _request_rdata, &rpc_data);
    EIntr();
    if (sceSifGetReg(0x80000002) != 0) {
        return;
    }
    hdr = &rpc_pkt_table[1].rpch.header;
    hdr->opt = 1;
    sceSifSendCmd(0x80000002, hdr, 0x10, 0, 0, 0);
    while (sceSifGetSreg(0) == 0) {}
    sceSifSetReg(0x80000002, 1);
}

void sceSifExitRpc(void)
{
    sceSifExitCmd();
    rpc_inited = 0;
}

void *_sceRpcGetPacket(SifRpcData *rd)
{
    SifRpcPkt *p;
    int i;
    int sid;

    DIntr();
    p = rd->pkt_table;
    for (i = 0; i < rd->pkt_table_len; i++) {
        if ((p->rpch.recId & 1) == 0) {
            p->rpch.recId = (i << 16) | 5;
            ++rd->pid;
            if (rd->pid == 1) {
                ++rd->pid;
                sid = 1;
            } else {
                sid = rd->pid;
            }
            p->rpch.pktAddr = p;
            p->rpch.rpcId = sid;
            EIntr();
            return p;
        }
        p++;
    }
    EIntr();
    return 0;
}

void _sceRpcFreePacket(void *pkt)
{
    SifRpcPkt *p = pkt;
    p->rpch.rpcId = 0;
    p->rpch.recId &= 0xFFFFFFFE;
}

void *_sceRpcGetFPacket(SifRpcData *rd)
{
    int rem = rd->rdata_table_idx % rd->rdata_table_len;
    void *ret = rd->rdata_table + rem * 64;
    rd->rdata_table_idx = rem + 1;
    return ret;
}

void *_sceRpcGetFPacket2(SifRpcData *rd, int rid)
{
    if (rid < 0) {
        goto err;
    }
    if (rid < rd->client_table_len) {
        goto elem;
    }
err:
    return _sceRpcGetFPacket(rd);
elem:
    return rd->client_table + rid * 64;
}

void _request_end(void *pkt, void *data)
{
    SifRpcRendPkt *rend = pkt;
    sceSifRpcClientData *c;
    sceSifEndFunc fn;

    switch (rend->cid) {
    case 0x8000000A:
        c = rend->client;
        fn = c->endFunc;
        if (fn != 0) {
            fn(c->endParam);
        }
        break;
    case 0x80000009:
        c = rend->client;
        c->serve = rend->server;
        c->buff = rend->buff;
        c->cbuff = rend->cbuff;
        break;
    /* nothing to finish for an RDATA reply, but the case is present */
    case 0x8000000C:
        break;
    }
    c = rend->client;
    if (c->sema >= 0) {
        iSignalSema(c->sema);
    }
    _sceRpcFreePacket(c->pkt);
    c->pkt = 0;
}

/* The answer to an IOP's request for EE data is built word by word: the
   ROM orders the copies of the request's words and the stores of the
   answer's as one integer alias set, which typed packet records do not
   reproduce. */
void _request_rdata(void *pkt, void *data)
{
    int *req = pkt;
    int *rend = _sceRpcGetFPacket(data);
    int paddr = req[5], client = req[7];
    rend[5] = paddr;
    rend[7] = client;
    rend[8] = 0x8000000C;
    isceSifSendCmd(0x80000008, rend, 0x40, (void *)req[8], (void *)req[9], req[10]);
}

int sceSifGetOtherData(sceSifReceiveData *rd, void *src, void *dest, int size, int mode)
{
    /* the request fields the SIF command callback reads back (see
       _request_end): written through a volatile view of the record, as
       sceSifCallRpc writes its four */
    volatile sceSifReceiveData *vrd = rd;
    SifRpcOtherDataPkt *pkt;
    struct SemaParam buf;
    int pid;

    pkt = _sceRpcGetPacket(&rpc_data);
    if (pkt == 0) {
        return -1;
    }
    pid = pkt->rpch.rpcId;
    vrd->pkt = pkt;
    vrd->pid = pid;
    pkt->src = src;
    pkt->dest = dest;
    pkt->size = size;
    pkt->rpch.pktAddr = pkt;
    pkt->receive = rd;
    if ((mode & 1) == 0) {
        buf.maxCount = 1;
        buf.initCount = 0;
        rd->sema = CreateSema(&buf);
        if (rd->sema < 0) {
            _sceRpcFreePacket(pkt);
            return -3;
        }
        if (sceSifSendCmd(0x8000000C, pkt, 0x40, 0, 0, 0) == 0) {
            _sceRpcFreePacket(pkt);
            DeleteSema(rd->sema);
            return -2;
        }
        WaitSema(rd->sema);
        DeleteSema(rd->sema);
        return 0;
    }
    rd->sema = -1;
    if (sceSifSendCmd(0x8000000C, pkt, 0x40, 0, 0, 0) == 0) {
        _sceRpcFreePacket(pkt);
        return -2;
    }
    return 0;
}

void *_search_svdata(unsigned int sid, SifRpcData *rd)
{
    sceSifQueueData *q;
    sceSifServeData *s;
    for (q = rd->active_queue; q != 0; q = q->next) {
        for (s = q->link; s != 0; s = s->link) {
            if (s->command == sid) {
                return s;
            }
        }
    }
    return 0;
}

/* the bind answer is built word by word, as _request_rdata's is, and the
   server record's buffer words are read the same way */
void _request_bind(void *pkt, void *data)
{
    int *req = pkt;
    int *rend = _sceRpcGetFPacket(data);
    int paddr = req[5], client = req[7];
    int *sv;

    rend[7] = client;
    rend[5] = paddr;
    rend[8] = 0x80000009;
    sv = _search_svdata(req[8], data);
    if (sv == 0) {
        rend[9] = 0;
        rend[10] = 0;
        rend[11] = 0;
    } else {
        rend[9] = (int)sv;
        rend[10] = sv[2];
        rend[11] = sv[5];
    }
    isceSifSendCmd(0x80000008, rend, 0x40, 0, 0, 0);
}

int sceSifBindRpc(sceSifRpcClientData *cd, unsigned int sid, int mode)
{
    /* the request fields the SIF command callback reads back (see
       _request_end): written through a volatile view of the client record,
       as sceSifCallRpc writes its four */
    volatile sceSifRpcClientData *vcd = cd;
    SifRpcBindPkt *pkt;
    struct SemaParam buf;
    int pid;

    cd->command = 0;
    cd->serve = 0;
    pkt = _sceRpcGetPacket(&rpc_data);
    if (pkt == 0) {
        return -1;
    }
    pid = pkt->rpch.rpcId;
    vcd->pkt = pkt;
    vcd->pid = pid;
    pkt->sid = sid;
    pkt->rpch.pktAddr = pkt;
    pkt->client = cd;
    if ((mode & 1) == 0) {
        buf.maxCount = 1;
        buf.initCount = 0;
        cd->sema = CreateSema(&buf);
        if (cd->sema < 0) {
            _sceRpcFreePacket(pkt);
            return -3;
        }
        if (sceSifSendCmd(0x80000009, pkt, 0x40, 0, 0, 0) == 0) {
            _sceRpcFreePacket(pkt);
            DeleteSema(cd->sema);
            return -2;
        }
        WaitSema(cd->sema);
        DeleteSema(cd->sema);
        return 0;
    }
    cd->sema = -1;
    if (sceSifSendCmd(0x80000009, pkt, 0x40, 0, 0, 0) == 0) {
        _sceRpcFreePacket(pkt);
        return -2;
    }
    return 0;
}

/* The call request is queued on its server word by word: the ROM orders
   every load and store here (the packet's words, the server record's
   request words, the queue's start and end) as one integer alias set. */
void _request_call(void *pkt, void *data)
{
    int *req = pkt;
    int *sd = (int *)req[13];
    int *q = (int *)sd[16];
    int *start = (int *)q[3];
    if (start == 0) {
        q[3] = (int)sd;
    } else {
        ((int *)q[4])[15] = (int)sd;
    }
    q[4] = (int)sd;
    {
        int paddr = req[5], client = req[7];
        sd[8] = paddr;
        sd[7] = client;
    }
    sd[9] = req[8];
    sd[3] = req[9];
    sd[10] = req[10];
    sd[11] = req[11];
    sd[12] = req[12];
    sd[13] = req[4];
    if (q[0] < 0) {
        return;
    }
    if (q[1] != 0) {
        return;
    }
    iWakeupThread(q[0]);
}

int sceSifCallRpc(sceSifRpcClientData *cd, unsigned int rpc_number, unsigned int mode,
                  void *sendbuf, int ssize, void *recvbuf, int rsize, sceSifEndFunc end_func,
                  void *end_param)
{
    /* The request words of the client record are written through a volatile
       word view: the record is shared with _request_end above, which runs
       from the SIF command callback and reads back the end function and its
       parameter, tests the semaphore and clears the packet pointer.  The
       four stores below reach the record in the order written, and the ROM
       orders them with the packet's words as one integer alias set. */
    volatile int *vc = (volatile int *)cd;
    int *pkt;
    struct SemaParam buf;
    int pid;

    pkt = _sceRpcGetPacket(&rpc_data);
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
    pkt[13] = cd->serve;
    pkt[7] = (int)cd;
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
        cd->sema = -1;
        if (sceSifSendCmd(0x8000000A, pkt, 0x40, sendbuf, (void *)cd->buff, ssize) != 0) {
            return 0;
        }
        _sceRpcFreePacket(pkt);
        return -2;
    }
    buf.maxCount = 1;
    buf.initCount = 0;
    cd->sema = CreateSema(&buf);
    if (cd->sema < 0) {
        _sceRpcFreePacket(pkt);
        return -3;
    }
    pkt[12] = 1;
    if (sceSifSendCmd(0x8000000A, pkt, 0x40, sendbuf, (void *)cd->buff, ssize) == 0) {
        DeleteSema(cd->sema);
        _sceRpcFreePacket(pkt);
        return -2;
    }
    WaitSema(cd->sema);
    DeleteSema(cd->sema);
    return 0;
}

int sceSifCheckStatRpc(sceSifRpcClientData *cd)
{
    SifRpcPkt *p = cd->pkt;
    if (p == 0)
        goto ret0;
    if (cd->pid != p->rpch.rpcId)
        goto ret0;
    if (p->rpch.recId & 1)
        goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}

void sceSifSetRpcQueue(sceSifQueueData *qd, int key)
{
    sceSifQueueData *q;

    DIntr();
    qd->key = key;
    qd->active = 0;
    qd->link = 0;
    qd->start = 0;
    qd->end = 0;
    qd->next = 0;
    if (rpc_data.active_queue == 0) {
        rpc_data.active_queue = qd;
    } else {
        for (q = rpc_data.active_queue; q->next != 0; q = q->next) {
            ;
        }
        q->next = qd;
    }
    EIntr();
}

void sceSifRegisterRpc(sceSifServeData *sd, unsigned int sid, sceSifRpcFunc func, void *buff,
                       sceSifRpcFunc cfunc, void *cbuff, sceSifQueueData *qd)
{
    sceSifServeData *q;

    DIntr();
    sd->next = 0;
    sd->link = 0;
    sd->command = sid;
    sd->func = func;
    sd->buff = buff;
    sd->cfunc = cfunc;
    sd->cbuff = cbuff;
    sd->base = qd;
    if (qd->link == 0) {
        qd->link = sd;
    } else {
        for (q = qd->link; q->link != 0; q = q->link) {
            ;
        }
        q->link = sd;
    }
    EIntr();
}

sceSifServeData *sceSifRemoveRpc(sceSifServeData *sd, sceSifQueueData *qd)
{
    sceSifServeData *q;
    DIntr();
    q = qd->link;
    if (q == sd) {
        qd->link = sd->link;
    } else {
        while (q != 0) {
            if (q->link == sd) {
                q->link = sd->link;
                break;
            }
            q = q->link;
        }
    }
    EIntr();
    return q;
}

sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *qd)
{
    sceSifQueueData *q;
    DIntr();
    q = rpc_data.active_queue;
    if (q == qd) {
        rpc_data.active_queue = qd->next;
    } else {
        while (q != 0) {
            if (q->next == qd) {
                q->next = qd->next;
                break;
            }
            q = q->next;
        }
    }
    EIntr();
    return q;
}

sceSifServeData *sceSifGetNextRequest(sceSifQueueData *qd)
{
    sceSifServeData *p;
    sceSifServeData *v;
    DIntr();
    p = qd->start;
    if (p == 0) {
        qd->active = 0;
        goto after;
    }
    v = p->next;
    qd->active = 1;
    qd->start = v;
after:
    EIntr();
    return p;
}

void sceSifExecRequest(sceSifServeData *sd)
{
    int size = 0;
    void *rec;
    SifRpcRendPkt *pkt;
    int i;
    sceSifDmaData dmat[2];
    int j;
    int r;

    rec = sd->func(sd->fno, sd->buff, sd->size);
    if (rec != 0) {
        size = sd->rsize;
    }
    if (sd->size > 0) {
        sceSifWriteBackDCache(sd->buff, sd->size);
    }
    if (size > 0) {
        sceSifWriteBackDCache(rec, size);
    }
    DIntr();
    if (sd->rid & 4) {
        pkt = _sceRpcGetFPacket2(&rpc_data, sd->rid >> 16);
    } else {
        pkt = _sceRpcGetFPacket(&rpc_data);
    }
    EIntr();
    pkt->cid = 0x8000000A;
    pkt->client = sd->client;
    if (sd->rmode != 0) {
        while (sceSifSendCmd(0x80000008, pkt, 0x40, rec, sd->receive, size) == 0) {
            ;
        }
        return;
    }
    pkt->rpch.rpcId = 0;
    i = 0;
    pkt->rpch.recId = 0;
    if (size > 0) {
        dmat[0].src = (unsigned int)rec;
        dmat[0].dest = (unsigned int)sd->receive;
        dmat[0].size = size;
        dmat[0].u.attr = 0;
        i = 1;
    }
    dmat[i].src = (unsigned int)pkt;
    dmat[i].dest = (unsigned int)sd->paddr;
    dmat[i].size = 0x40;
    dmat[i].u.attr = 0;
    i++;
    do {
        r = sceSifSetDma(dmat, i);
        if (r != 0) {
            break;
        }
        for (j = 0x100000; j != -1; j--) {
            ;
        }
    } while (r == 0);
}

void sceSifRpcLoop(sceSifQueueData *qd)
{
    sceSifServeData *item;
    for (;;) {
        while ((item = sceSifGetNextRequest(qd)) != 0) {
            sceSifExecRequest(item);
        }
        SleepThread();
    }
}
