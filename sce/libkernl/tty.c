/* libkernl.a(tty.o) */
#include <eekernel.h>
#include <libkernl_internal.h>

/* the receive queue: a 16-byte header (the ring's size, the bytes queued,
   the read and write pointers) and the ring */
typedef struct { /* derived name */
    int size;
    int count;
    char *rp;
    char *wp;
    char buf[256];
} TtyQueue;

/* tty.o's .bss, in link order: the receive queue QueueInit sets up (a
   16-byte header and a 256-byte ring), the DECI2 socket record, then the send
   and receive packets (320 bytes each, 64-aligned for the DECI2 transfer). */
static TtyQueue tty_queue; /* derived name */

static int tty_rec[7]; /* derived name */

static char tty_sbuf[320] __attribute__((aligned(64))); /* derived name */

static char tty_rbuf[320] __attribute__((aligned(64))); /* derived name */

void *QueueInit(int a0)
{
    tty_queue.size = a0;
    tty_queue.count = 0;
    tty_queue.wp = tty_queue.buf;
    tty_queue.rp = tty_queue.buf;
    return &tty_queue;
}

void QueuePeekWriteDone(TtyQueue *q)
{
    int count = q->count + 1;
    char *wp = q->wp + 1;
    int cap = q->size;
    q->count = count;
    cap += 0x10;
    {
        char *end = (char *)q + cap;
        q->wp = wp;
        if (wp == end) {
            q->wp = q->buf;
        }
    }
}

void QueuePeekReadDone(TtyQueue *q)
{
    q->count--;
    q->rp++;
    if (q->rp == (char *)q + (q->size + 0x10)) {
        q->rp = q->buf;
    }
}

/* the tty socket record at tty_rec as the handler sees it.  The four header
   words are volatile, the view sceTtyInit and sceTtyWrite already take (the
   handler writes them from interrupt level while the callers poll them); the
   buffer and queue pointers below them are plain.  The names are ours. */
typedef struct {
    volatile int s;    /* 0x00 the DECI2 socket */
    volatile int wlen; /* 0x04 bytes left to send */
    volatile int rlen; /* 0x08 bytes received into rbuf */
    volatile int busy; /* 0x0C set while a send is outstanding */
    char *wbuf;        /* 0x10 */
    char *rbuf;        /* 0x14 */
    TtyQueue *q;       /* 0x18 the receive queue */
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
            *tty->q->wp = tty->rbuf[i];
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

int sceTtyWrite(const char *buf, int len)
{
    /* the tty handler owns this record from interrupt level: it clears the
       busy flag at +0xC when the send completes and writes the length at
       +0x4, so every read of it in this function is a volatile read.  The
       stores run with interrupts disabled and are plain. */
    volatile int *rec = tty_rec;
    char *hdr;
    char *out;
    int n = 0;
    int i = 0;

    if (rec[3] != 0) {
        return -1;
    }
    DIntr();
    tty_rec[3] = 1;
    /* the send buffer is addressed through the uncached accelerated window */
    hdr = (char *)((unsigned int)tty_sbuf | 0x20000000);
    tty_rec[4] = (int)hdr;
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
    tty_rec[1] = n + 12;
    *(short *)hdr = *(volatile int *)&tty_rec[1];
    if (sceDeci2ReqSend(*(volatile int *)&tty_rec[0], hdr[7]) < 0) {
        tty_rec[3] = 0;
        EIntr();
        return -1;
    }
    while (*(volatile int *)&tty_rec[3] != 0) {
        sceDeci2Poll(*(volatile int *)&tty_rec[0]);
    }
    EIntr();
    return i;
}

int sceTtyRead(void *buf, int size)
{
    int i;
    char *p;

    for (i = 0; i < size; i++) {
        p = (char *)buf + i;
        /* the queue's count, which the tty handler raises from interrupt
           level */
        while (((volatile int *)tty_rec[6])[1] == 0) {}
        *p = *((TtyQueue *)tty_rec[6])->rp;
        QueuePeekReadDone((TtyQueue *)tty_rec[6]);
        if (*p == '\n' || *p == '\r') {
            return i + 1;
        }
    }
    return i;
}

int sceTtyInit(void)
{
    /* the tty handler writes the socket's send length, receive count and busy
       flag from interrupt level (its stores at +0x4, +0x8 and +0xC), so the
       record's four header words are volatile; the buffer and queue pointers
       below them are plain */
    volatile int *rec = tty_rec;
    char *snd;
    char *rcv;

    FlushCache(0);
    rec[0] = sceDeci2Open(0x210, tty_rec, sceTtyHandler);
    if (rec[0] < 0) {
        return 0;
    }
    rec[3] = 0;
    rcv = (char *)((unsigned int)tty_rbuf | 0x20000000);
    snd = (char *)((unsigned int)tty_sbuf | 0x20000000);
    rec[1] = 0;
    rec[2] = 0;
    tty_rec[5] = (int)rcv;
    tty_rec[4] = (int)snd;
    *(short *)(snd + 4) = 0x210;
    snd[6] = 'E';
    snd[7] = 'H';
    *(short *)(snd + 2) = 0;
    *(int *)(snd + 8) = 0;
    tty_rec[6] = (int)QueueInit(256);
    return 1;
}
