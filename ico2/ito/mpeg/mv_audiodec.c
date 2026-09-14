#include "common.h"

extern int sceSifFreeIopHeap(int a0);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern int SgStPcmClose(unsigned int a0);
extern void SgStPcmQuit(void);
extern char D_006231D0[];
extern char D_006231F0[];
extern int SgStPcmStop(unsigned long long a0);
extern void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2);
extern int SgStPcmLseek(unsigned int a0, unsigned int a1);
extern int SgStPcmPlay(unsigned long long a0);
/* prototypes: their order is the inline tail's emission order */
int audioDecDelete(int *self);
void audioDecReset(int *self);
int audioDecIsPreset(int *self);
void audioDecStart(int *self);
int audioDecPause(int a0);
void audioDecResume(int *self);
extern int iosMallocAlignDebug(int heap, int size, int align, const char *file, int line);
extern void debug_assert(const char *file, int line);
extern void __assert(const char *file, int line, const char *expr);
extern void *memset(void *p, int c, int n);
extern int D_0063A468;
extern char D_00623160[];
extern char D_00623180[];
extern char D_00623190[];
extern char D_006231B0[];
extern int sceSifAllocIopHeap(int size);
extern void SgStPcmInit(void);
extern int SgStPcmOpen(int *param);
extern void SgStPcmSetEffect(int a0);
extern int SgStPcmIopReadAddr(int ch);

int audioDecCreate(int *self, int a1, int a2)
{
    int pcm[4];
    int p;
    int size = 0x6000;
    int bufsize = 0xC000;

    *(char *)((char *)self + 0x60) = 0;
    *(char *)((char *)self + 0x62) = 0;
    *(char *)((char *)self + 0x61) = 0;

    p = iosMallocAlignDebug(D_0063A468, bufsize, 0x40, D_00623160, 0x2B);
    if (p == 0) {
        debug_assert(D_00623160, 0x2C);
        __assert(D_00623160, 0x2C, D_00623180);
    }
    memset((void *)p, 0, bufsize);
    if (p == 0) {
        return -1;
    }

    self[0] = 0;
    self[0x2C / 4] = 0;
    self[0x30 / 4] = p;
    self[0x3C / 4] = bufsize;
    self[0x34 / 4] = 0;
    self[0x38 / 4] = 0;
    self[0x40 / 4] = 0;
    self[0x54 / 4] = 0;
    self[0x48 / 4] = size;
    self[0x4C / 4] = 0;
    self[0x50 / 4] = 0;

    self[0x44 / 4] = sceSifAllocIopHeap(size);
    if (self[0x44 / 4] == 0) {
        debug_StdPrintfDummy(D_00623190);
        return 0;
    }
    debug_StdPrintfDummy(D_006231B0, self[0x44 / 4]);

    *(char *)((char *)self + 0x58) = a1;
    self[0x5C / 4] = a2;
    SgStPcmInit();
    *(char *)((char *)self + 0x60) = 1;

    pcm[0] = 0;
    pcm[1] = 0x10400;
    pcm[2] = self[0x44 / 4];
    pcm[3] = size;
    if ((*(char *)((char *)self + 0x61) = (SgStPcmOpen(pcm) == 0)) == 0) {
        return -1;
    }

    pcm[0] = 1;
    pcm[1] = 0x10400;
    pcm[2] = self[0x44 / 4] + 0x200;
    pcm[3] = size;
    if ((*(char *)((char *)self + 0x62) = (SgStPcmOpen(pcm) == 0)) == 0) {
        return -1;
    }

    SgStPcmSetEffect(8);
    return 0;
}

inline int audioDecDelete(int *self)
{
    if (self[0x44 / 4]) {
        if (sceSifFreeIopHeap(self[0x44 / 4]) < 0) {
            debug_StdPrintfDummy(D_006231D0, self[0x44 / 4]);
        }
        debug_StdPrintfDummy(D_006231F0, self[0x44 / 4]);
        self[0x44 / 4] = 0;
    }
    if (*(signed char *)((char *)self + 0x61)) {
        SgStPcmClose(0);
    }
    if (*(signed char *)((char *)self + 0x62)) {
        SgStPcmClose(1);
    }
    if (*(signed char *)((char *)self + 0x60)) {
        SgStPcmQuit();
    }
    return 1;
}

inline void audioDecReset(int *self)
{
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    *(volatile int *)((char *)self + 0x50) = 0;
    *(volatile int *)((char *)self + 0) = 0;
    *(volatile int *)((char *)self + 0x2C) = 0;
    *(volatile int *)((char *)self + 0x34) = 0;
    *(volatile int *)((char *)self + 0x38) = 0;
    *(volatile int *)((char *)self + 0x40) = 0;
    *(volatile int *)((char *)self + 0x54) = 0;
    *(volatile int *)((char *)self + 0x4C) = 0;
}

extern char D_00623208[];
extern char D_00623240[];
extern char D_00623380[];

void audioDecEndPut(int *self, int n)
{
    unsigned int k;
    unsigned int cnt;
    unsigned int room;

    if (self[0] == 0) {
        cnt = self[0x2C / 4];
        room = 40 - cnt;
        k = (room < n) ? room : n;
        cnt += k;
        self[0x2C / 4] = cnt;
        if (cnt >= 40) {
            self[0] = 1;
            debug_StdPrintfDummy(D_00623208);
            debug_StdPrintfDummy(
                D_00623240, *(signed char *)((char *)self + 4), *(signed char *)((char *)self + 5),
                *(signed char *)((char *)self + 6), *(signed char *)((char *)self + 7), self[8 / 4],
                self[0xC / 4], self[0x10 / 4], self[0x14 / 4], self[0x18 / 4], self[0x1C / 4],
                self[0x20 / 4]);
            debug_StdPrintfDummy(D_00623380, *(signed char *)((char *)self + 0x24),
                                 *(signed char *)((char *)self + 0x25),
                                 *(signed char *)((char *)self + 0x26),
                                 *(signed char *)((char *)self + 0x27), self[0x28 / 4]);
        }
        n -= k;
    }
    self[0x34 / 4] = (self[0x34 / 4] + n) % self[0x3C / 4];
    self[0x38 / 4] += n;
    self[0x40 / 4] += n;
}

inline int audioDecIsPreset(int *self)
{
    return *(int *)((char *)self + 0x54) >= *(int *)((char *)self + 0x48);
}

inline void audioDecStart(int *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self[0x5C / 4]);
        SgStPcmVolume(2, self[0x5C / 4], 0);
    }
    SgStPcmPlay(3);
    self[0] = 2;
}

extern void FlushCache(int a0);
extern int sceSifSetDma(int *dma, int n);
extern int sceSifDmaStat(int id);

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

int audioDecSendToIOP(int *self)
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

    switch (self[0]) {
    case 0:
        return 0;
    case 1:
        n0 = self[0x48 / 4] - self[0x54 / 4];
        p1 = 0;
        n1 = 0;
        p0 = (char *)(self[0x44 / 4] + self[0x54 / 4] % self[0x48 / 4]);
        break;
    case 2: {
        int rd = SgStPcmIopReadAddr(0);
        int sz = self[0x48 / 4];
        int cur = self[0x4C / 4];
        int want = (rd + sz - cur - 1024) % sz;
        int tail = sz - cur;

        want = want / 1024 * 1024;

        if (tail >= want) {
            n0 = want;
            p1 = 0;
            n1 = 0;
            p0 = (char *)(self[0x44 / 4] + cur);
        } else {
            n0 = tail;
            n1 = want - n0;
            p0 = (char *)(self[0x44 / 4] + cur);
            p1 = (char *)self[0x44 / 4];
        }
        break;
    }
    case 3:
        return 0;
    }

    len = self[0x38 / 4];
    rsz = self[0x3C / 4];
    off = (self[0x34 / 4] - len + rsz) % rsz;
    lim = len / 1024 * 1024;
    m0 = rsz - off;
    q0 = (char *)(self[0x30 / 4] + off);
    if (lim < m0) {
        m0 = lim;
    }
    m1 = lim - m0;
    q1 = (char *)self[0x30 / 4];

    if (n0 + n1 >= 1024 && m0 + m1 >= 1024) {
        n = sendToIOP2area(p0, n0, p1, n1, q0, m0, q1, m1);
    }

    self[0x38 / 4] = self[0x38 / 4] - n;
    self[0x54 / 4] += n;
    self[0x4C / 4] = (self[0x4C / 4] + n) % self[0x48 / 4];
    return n;
}

inline int audioDecPause(int a0)
{
    *(int *)a0 = 3;
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    return 0;
}

inline void audioDecResume(int *self)
{
    audioDecStart(self);
}

extern int copy2area(char *a0, int a1, char *a2, int a3, char *a4, int a5, char *a6, int a7);

int pcmCallback(int a0, int *pkt, int *ctx)
{
    char *p0;
    int n0;
    char *p1;
    int n1;
    int *b = (int *)ctx[0];
    int *ad = (int *)ctx[1];
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
    if (ad[0] == 0) {
        p0 = (char *)ad + (ad[0x2C / 4] + 4);
        n0 = 40 - ad[0x2C / 4];
        p1 = (char *)ad[0x30 / 4];
        n1 = ad[0x3C / 4];
    } else {
        int room = ad[0x3C / 4] - ad[0x38 / 4];
        int wr = ad[0x34 / 4];
        int tail = ad[0x3C / 4] - wr;

        if (tail >= room) {
            tail = room;
            p1 = 0;
            n1 = 0;
            p0 = (char *)(ad[0x30 / 4] + wr);
        } else {
            n1 = room - tail;
            p0 = (char *)(ad[0x30 / 4] + wr);
            p1 = (char *)ad[0x30 / 4];
        }
        n0 = tail;
    }

    k = copy2area(p0, n0, p1, n1, (char *)rd, first, (char *)base, rest);
    audioDecEndPut(ad, k);
    return 0 < k;
}
