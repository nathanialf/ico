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

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecSendToIOP);

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

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);
