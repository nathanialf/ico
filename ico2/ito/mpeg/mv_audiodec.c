#define MV_DEFS_WANT_ALLOC

#include "common.h"
#include "mv_defs.h"
#include "debug.h"
#include "mv_sub.h"

extern int SgStPcmClose(unsigned int a0);
extern void SgStPcmQuit(void);
extern int SgStPcmStop(unsigned long long a0);
extern void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2);
extern int SgStPcmLseek(unsigned int a0, unsigned int a1);
extern int SgStPcmPlay(unsigned long long a0);

#include "mv_audiodec.h"
#include <eekernel.h>
#include <sifrpc.h>

extern void SgStPcmInit(void);
extern int SgStPcmOpen(int *param);
extern void SgStPcmSetEffect(int a0);
extern int SgStPcmIopReadAddr(int ch);

int audioDecCreate(AudioDec *self, int a1, int a2)
{
    int pcm[4];
    int p;
    int size = 0x6000;
    int bufsize = 0xC000;

    self->pcmInited = 0;
    self->ch1Open = 0;
    self->ch0Open = 0;

    p = alloc_zeroed(bufsize, 0x40);
    if (p == 0) {
        return -1;
    }

    self->state = 0;
    self->headerBytes = 0;
    self->ring = p;
    self->ringSize = bufsize;
    self->writePos = 0;
    self->filled = 0;
    self->putTotal = 0;
    self->sentTotal = 0;
    self->iopSize = size;
    self->iopPos = 0;
    self->f50 = 0;

    self->iopBuf = sceSifAllocIopHeap(size);
    if (self->iopBuf == 0) {
        debug_StdPrintfDummy("Cannot allocate IOP memory\n");
        return 0;
    }
    debug_StdPrintfDummy("Allocate IOP memory 0x%08x\n", self->iopBuf);

    self->mono = a1;
    self->volume = a2;
    SgStPcmInit();
    self->pcmInited = 1;

    pcm[0] = 0;
    pcm[1] = 0x10400;
    pcm[2] = self->iopBuf;
    pcm[3] = size;
    if ((self->ch0Open = (SgStPcmOpen(pcm) == 0)) == 0) {
        return -1;
    }

    pcm[0] = 1;
    pcm[1] = 0x10400;
    pcm[2] = self->iopBuf + 0x200;
    pcm[3] = size;
    if ((self->ch1Open = (SgStPcmOpen(pcm) == 0)) == 0) {
        return -1;
    }

    SgStPcmSetEffect(8);
    return 0;
}

inline int audioDecDelete(AudioDec *self)
{
    if (self->iopBuf) {
        if (sceSifFreeIopHeap(self->iopBuf) < 0) {
            debug_StdPrintfDummy("iop heap free failed 0x%08x\n", self->iopBuf);
        }
        debug_StdPrintfDummy("free iop heap 0x%08x\n", self->iopBuf);
        self->iopBuf = 0;
    }
    if (self->ch0Open) {
        SgStPcmClose(0);
    }
    if (self->ch1Open) {
        SgStPcmClose(1);
    }
    if (self->pcmInited) {
        SgStPcmQuit();
    }
    return 1;
}

inline void audioDecReset(AudioDec *self)
{
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    *(volatile int *)&self->f50 = 0;
    *(volatile int *)&self->state = 0;
    *(volatile int *)&self->headerBytes = 0;
    *(volatile int *)&self->writePos = 0;
    *(volatile int *)&self->filled = 0;
    *(volatile int *)&self->putTotal = 0;
    *(volatile int *)&self->sentTotal = 0;
    *(volatile int *)&self->iopPos = 0;
}

void audioDecEndPut(AudioDec *self, int n)
{
    unsigned int k;
    unsigned int cnt;
    unsigned int room;

    if (self->state == 0) {
        cnt = self->headerBytes;
        room = 40 - cnt;
        k = (room < n) ? room : n;
        cnt += k;
        self->headerBytes = cnt;
        if (cnt >= 40) {
            self->state = 1;
            debug_StdPrintfDummy("-------- audio information --------------------\n");
            debug_StdPrintfDummy(
                "[%c%c%c%c]\nheader size:                            %d\ntype(0:PCM big, 1:PCM "
                "little, 2:ADPCM): %d\nsampling rate:                          %dHz\nchannels:     "
                "                          %d\ninterleave size:                        "
                "%d\ninterleave start block address:         %d\ninterleave end block address:     "
                "      %d\n",
                self->id[0], self->id[1], self->id[2], self->id[3], self->headerSize, self->type,
                self->sampleRate, self->channels, self->interleaveSize, self->interleaveStart,
                self->interleaveEnd);
            debug_StdPrintfDummy("[%c%c%c%c]\ndata size:                              %d\n",
                                 self->dataId[0], self->dataId[1], self->dataId[2], self->dataId[3],
                                 self->dataSize);
        }
        n -= k;
    }
    self->writePos = (self->writePos + n) % self->ringSize;
    self->filled += n;
    self->putTotal += n;
}

inline int audioDecIsPreset(AudioDec *self)
{
    return self->sentTotal >= self->iopSize;
}

inline void audioDecStart(AudioDec *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (self->mono) {
        int half = self->volume / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self->volume);
        SgStPcmVolume(2, self->volume, 0);
    }
    SgStPcmPlay(3);
    self->state = 2;
}

/* mv_audiodec.c:375-392 */
static inline void sendToIOP(char *src, char *dst, int n)
{
    int dma[4];
    int id;

    if (n > 0) {
        dma[0] = (int)src;
        dma[1] = (int)dst;
        dma[2] = n;
        dma[3] = 0;
        FlushCache(0);
        id = sceSifSetDma(dma, 1);
        while (sceSifDmaStat(id) >= 0) {}
    }
}

int sendToIOP2area(char *p0, int n0, char *p1, int n1, char *q0, int m0, char *q1, int m1)
{
    int total = m0 + m1;

    if (n0 + n1 < total) {
        int over = total - (n0 + n1);

        if (over >= m1) {
            m0 -= over - m1;
            m1 = 0;
            total = m0;
        } else {
            m1 -= over;
            total = m0 + m1;
        }
    }

    if (m0 >= n0) {
        sendToIOP(q0, p0, n0);
        sendToIOP(q0 + n0, p1, m0 - n0);
        sendToIOP(q1, p1 + m0 - n0, m1);
    } else if (m1 >= n0 - m0) {
        sendToIOP(q0, p0, m0);
        sendToIOP(q1, p0 + m0, n0 - m0);
        sendToIOP(q1 + n0 - m0, p1, m1 - (n0 - m0));
    } else {
        sendToIOP(q0, p0, m0);
        sendToIOP(q1, p0 + m0, m1);
    }
    return total;
}

int audioDecSendToIOP(AudioDec *self)
{
    char *p0;
    int n0;
    char *p1;
    int n1;
    char *q0;
    int m0;
    char *q1;
    int m1;
    int n = 0;
    int len;
    int rsz;
    int off;
    int lim;

    switch (self->state) {
    case 0:
        return 0;
    case 1:
        n0 = self->iopSize - self->sentTotal;
        p1 = 0;
        n1 = 0;
        p0 = (char *)(self->iopBuf + self->sentTotal % self->iopSize);
        break;
    case 2: {
        int rd = SgStPcmIopReadAddr(0);
        int sz = self->iopSize;
        int cur = self->iopPos;
        int want = (rd + sz - cur - 1024) % sz;
        int tail = sz - cur;

        want = want / 1024 * 1024;

        if (tail >= want) {
            n0 = want;
            p1 = 0;
            n1 = 0;
            p0 = (char *)(self->iopBuf + cur);
        } else {
            n0 = tail;
            n1 = want - n0;
            p0 = (char *)(self->iopBuf + cur);
            p1 = (char *)self->iopBuf;
        }
        break;
    }
    case 3:
        return 0;
    }

    len = self->filled;
    rsz = self->ringSize;
    off = (self->writePos - len + rsz) % rsz;
    lim = len / 1024 * 1024;
    m0 = rsz - off;
    q0 = (char *)(self->ring + off);
    if (lim < m0) {
        m0 = lim;
    }
    m1 = lim - m0;
    q1 = (char *)self->ring;

    if (n0 + n1 >= 1024 && m0 + m1 >= 1024) {
        n = sendToIOP2area(p0, n0, p1, n1, q0, m0, q1, m1);
    }

    self->filled = self->filled - n;
    self->sentTotal += n;
    self->iopPos = (self->iopPos + n) % self->iopSize;
    return n;
}

inline int audioDecPause(AudioDec *self)
{
    self->state = 3;
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    return 0;
}

inline void audioDecResume(AudioDec *self)
{
    audioDecStart(self);
}

int pcmCallback(int a0, int *pkt, int *ctx)
{
    char *p0;
    int n0;
    char *p1;
    int n1;
    int *b = (int *)ctx[0];
    AudioDec *ad = (AudioDec *)ctx[1];
    unsigned int rd = pkt[2];
    int base = b[0];
    int n;
    int first;
    int rest;
    int k;

    rd += 4;
    if (rd >= (unsigned int)(base + b[1])) {
        rd -= b[1];
    }
    n = pkt[3] - 4;
    first = (base + b[1]) - rd;
    if (n < first) {
        first = n;
    }
    rest = n - first;

    /* INTERIM: the listing inlines the mv_audiodec.c:205-232 begin-put helper
       here; written out because a pointer-output helper forces its four results
       into stack slots that ROM does not have */
    if (ad->state == 0) {
        p0 = (char *)ad + (ad->headerBytes + 4);
        n0 = 40 - ad->headerBytes;
        p1 = (char *)ad->ring;
        n1 = ad->ringSize;
    } else {
        int room = ad->ringSize - ad->filled;
        int wr = ad->writePos;
        int tail = ad->ringSize - wr;

        if (tail >= room) {
            tail = room;
            p1 = 0;
            n1 = 0;
            p0 = (char *)(ad->ring + wr);
        } else {
            n1 = room - tail;
            p0 = (char *)(ad->ring + wr);
            p1 = (char *)ad->ring;
        }
        n0 = tail;
    }

    k = copy2area(p0, n0, p1, n1, (char *)rd, first, (char *)base, rest);
    audioDecEndPut(ad, k);
    return 0 < k;
}
