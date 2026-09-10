#include "common.h"
#include "mv_defs.h"
#include "r5900.h"

extern void Free(int a0);

void free_buf(int a0)
{
    Free(*(int *)(a0 + 0x48));
}

extern int iosMallocAlignDebug(int heap, int size, int align, const char *file, int line);
extern void debug_assert(const char *file, int line);
extern void __assert(const char *file, int line, const char *expr);
extern void *memset(void *p, int c, int n);
extern int D_0063A468;
extern char D_00557708[];
extern char D_00557728[];
extern int sceMpegCreate(void *self, void *buf, int size);
extern int sceMpegAddCallback(void *self, int id, void *fn, void *arg);
extern int viBufCreate(void *self);
int mpegError(int a0, int *self);
int mpegNodata(int a0, int a1, int a2);
int mpegStopDMA(int a0_unused, int a1_unused, char *p);
int mpegRestartDMA(int a0_unused, int a1_unused, char *p);
int mpegTS(int a0_unused, int *a1, char *a2);

int videoDecCreate(int self)
{
    int p;

    p = iosMallocAlignDebug(D_0063A468, 0x1C8200, 0x40, D_00557708, 0x2B);
    if (p == 0) {
        debug_assert(D_00557708, 0x2C);
        __assert(D_00557708, 0x2C, D_00557728);
    }
    memset((void *)p, 0, 0x1C8200);
    *(int *)(self + 0x48) = p;
    if (p == 0) {
        return -1;
    }
    sceMpegCreate((void *)self, (void *)p, 0x1C8200);
    sceMpegAddCallback((void *)self, 0, (void *)mpegError, 0);
    sceMpegAddCallback((void *)self, 1, (void *)mpegNodata, (void *)self);
    sceMpegAddCallback((void *)self, 2, (void *)mpegStopDMA, (void *)self);
    sceMpegAddCallback((void *)self, 3, (void *)mpegRestartDMA, (void *)self);
    sceMpegAddCallback((void *)self, 5, (void *)mpegTS, (void *)self);
    *(int *)(self + 0xB8) = 0;
    return viBufCreate((void *)(self + 0x50)) == 0 ? 0 : -1;
}

extern void viBufBeginPut(void *self, void **addr1, int *size1, void **addr2, int *size2);

void videoDecBeginPut(int a0, void **addr1, int *size1, void **addr2, int *size2)
{
    viBufBeginPut((void *)(a0 + 0x50), addr1, size1, addr2, size2);
}

extern void viBufEndPut(int *self, int a1);

void videoDecEndPut(int a0, int a1)
{
    viBufEndPut((int *)(a0 + 0x50), a1);
}

typedef struct Code4 {
    char b[4];
} Code4;

extern Code4 D_0063AC90[];
extern int copy2area(char *a0, int a1, char *a2, int a3, char *a4, int a5, char *a6, int a7);
extern void viBufFlush(int *self);

int videoDecFlush(int a0)
{
    Code4 code;
    void *p0;
    int n0;
    void *p1;
    int n1;

    code = D_0063AC90[0];
    videoDecBeginPut(a0, &p0, &n0, &p1, &n1);
    if (n0 + n1 < 4) {
        return 0;
    }
    videoDecEndPut(a0, copy2area((char *)uncached_accel_addr((int)p0), n0,
                                 (char *)uncached_accel_addr((int)p1), n1, code.b, 4, 0, 0));
    viBufFlush((int *)(a0 + 0x50));
    if (*(int *)(a0 + 0xB8) == 0) {
        *(int *)(a0 + 0xB8) = 2;
    }
    return 1;
}

typedef struct ViTs {
    long long pts;
    long long dts;
    int pos;
    int len;
} ViTs;

extern int viBufPutTs(void *self, ViTs *ts);
extern void ErrMessage(char *msg);
extern char D_00557738[];

int videoCallback(int a0, char *pkt, int *a2)
{
    ViTs ts;
    void *p0;
    int n0;
    void *p1;
    int n1;
    int *b = (int *)a2[0];
    int dec = a2[1];
    int rd = *(int *)(pkt + 8);
    int base = b[0];
    unsigned int len = *(unsigned int *)(pkt + 0xC);
    unsigned int first = base + b[1] - rd;
    unsigned int rest;
    int n;

    if (len < first) {
        first = len;
    }
    rest = len - first;
    videoDecBeginPut(dec, &p0, &n0, &p1, &n1);
    n = copy2area((char *)uncached_accel_addr((int)p0), n0, (char *)uncached_accel_addr((int)p1),
                  n1, (char *)rd, first, (char *)base, rest);
    if (n > 0) {
        ts.pts = *(long long *)(pkt + 0x10);
        ts.dts = *(long long *)(pkt + 0x18);
        ts.pos = (int)p0 - *(int *)(dec + 0x50);
        ts.len = n;
        if (viBufPutTs((void *)(dec + 0x50), &ts) == 0) {
            ErrMessage(D_00557738);
        }
    }
    videoDecEndPut(dec, n);
    return 0 < n;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_videodec", decBitStrm0);

extern void iosFree();

void Free(int a0)
{
    iosFree(phys_addr(a0));
}

extern int sceMpegDelete();
extern void viBufDelete();

int videoDecDelete(int a0)
{
    viBufDelete(a0 + 0x50);
    sceMpegDelete(a0);
    free_buf(a0);
    return 1;
}

extern void sceMpegAddStrCallback();

int videoDecSetStream(void)
{
    sceMpegAddStrCallback();
    return 1;
}

void videoDecAbort(int a0)
{
    *(int *)(a0 + 0xB8) = 1;
}

int videoDecGetState(int a0)
{
    return *(int *)(a0 + 0xB8);
}

extern int sceMpegIsRefBuffEmpty(char *self);
extern int viBufCount(int *self);

int videoDecIsFlushed(int *self)
{
    int ret = 0;
    if (viBufCount((int)((char *)self + 0x50)) == 0) {
        ret = sceMpegIsRefBuffEmpty(self) != 0;
    }
    return ret;
}

extern void decBitStrm0();
extern void viBufReset();
extern void voBufReset();

void videoDecMain(int *self)
{
    viBufReset(self[0] + 0x50);
    voBufReset(self[2]);
    decBitStrm0(self[0], self[1], self[2]);
    *(int *)(self[0] + 0xB8) = 3;
}

extern const char D_0063AC88[];
extern void debug_StdPrintfDummy(const char *fmt, int arg);

int mpegError(int a0, int *self)
{
    debug_StdPrintfDummy(D_0063AC88, self[1]);
    return 1;
}

extern void switchThread();
extern void viBufAddDMA();

int mpegNodata(int a0, int a1, int a2)
{
    switchThread(a0, a1);
    viBufAddDMA(a2 + 0x50);
    return 1;
}

extern void viBufStopDMA();

int mpegStopDMA(int a0_unused, int a1_unused, char *p)
{
    viBufStopDMA((int)(p + 0x50));
    return 1;
}

extern void viBufRestartDMA();

int mpegRestartDMA(int a0_unused, int a1_unused, char *p)
{
    viBufRestartDMA((int)(p + 0x50));
    return 1;
}

extern void viBufGetTs();

int mpegTS(int a0_unused, int *a1, char *a2)
{
    long long buf[4];
    viBufGetTs((int *)(a2 + 0x50), (int *)buf);
    *(long long *)((char *)a1 + 0x8) = buf[0];
    *(long long *)((char *)a1 + 0x10) = buf[1];
    return 1;
}
