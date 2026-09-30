/* Vendor SCE library member: libkernl.a(tty.o).  MAIN.MAP names the
 * member and its .text size (0x51C), which tiles the shipped ELF from one
 * retail function start to the next; VMA 0x25F250..0x25F76C,
 * 7 functions. */

/* eekernel.h's spelling, the one sifcmd.o's sceSifInitCmd proves (a void call
   leaves no value register set after it). */
extern void FlushCache(int a0);

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
    char buf[256];
} PrintSink;

/* tty.o's .bss, in the ROM's order: the receive queue QueueInit sets up (a
   16-byte header and a 256-byte ring), the DECI2 socket record, then the send
   and receive packets (320 bytes each, 64-aligned for the DECI2 transfer). */
static PrintSink tty_queue;

static int tty_rec[7];

static char tty_sbuf[320] __attribute__((aligned(64)));

static char tty_rbuf[320] __attribute__((aligned(64)));

void *QueueInit(int a0)
{
    tty_queue.f0 = a0;
    tty_queue.f4 = 0;
    tty_queue.fC = tty_queue.buf;
    tty_queue.f8 = tty_queue.buf;
    return &tty_queue;
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

/* RECONSTRUCTION: the tty socket record at tty_rec as the handler sees it.
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
        *p = *((RingBuf_241C80 *)tty_rec[6])->f8;
        QueuePeekReadDone((RingBuf_241C80 *)tty_rec[6]);
        if (*p == '\n' || *p == '\r') {
            return i + 1;
        }
    }
    return i;
}

extern int sceDeci2Open(unsigned short protocol, void *opt, void *handler);
extern void sceTtyHandler(int event, int param, void *opt);

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
