#include "common.h"

extern void debug_StdPrintfDummy(char *fmt, ...);
extern int D_0063C320;
extern void RotateThreadReadyQueue();
extern int D_006F2B98[];
extern void audioDecSendToIOP();
extern int D_0063AC78;
extern char D_0063AC80[];
extern int D_006F2AD0[];
extern int D_006F2AC0[];
extern char D_006EA900[];
extern char voBuf[];
extern int D_002A7978[];
extern int D_0063C324;
extern int D_0063C328;
extern int D_0063C32C;
extern int D_0063C330;
extern int D_0063C334;
extern void strFileClose(char *self);
extern int DIntr(void);
extern int EIntr(void);
extern int DisableDmac(int ch);
extern void RemoveDmacHandler(int ch, int id);
extern int DisableIntc(int ch);
extern void RemoveIntcHandler(int ch, int id);
extern void TerminateThread(int id);
extern void DeleteThread(int id);
extern void readBufDelete(int *self);
extern void voBufDelete(char *self);
extern int videoDecDelete(int *self);
extern void audioDecDelete(int *self);
extern void dispDelete(int *self);
extern void dispClear(int *self, unsigned int col);
extern int sceGsGetIMR(void);
extern void sceGsPutIMR(long long imr);
extern int EnableDmac(int ch);
extern int EnableIntc(int ch);
extern int GetThreadId(void);
extern void ChangeThreadPriority(int id, int prio);
extern int D_006FAC40[];
extern int D_006FAC60[];
extern int D_002A7920[];
extern int D_002A7940[];
extern int D_0063C338;
extern long long D_0063C340;
extern char D_00557648[];
extern char D_00557698[];
extern void sceGsSyncPath(int a0, int a1);
extern int ReferThreadStatus(int id, int *st);
extern int initAll(int a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7);
extern int D_0063AC70;
extern char D_00557660[];
extern char D_00557670[];
extern char D_00557680[];
void movie_end(void);
extern int sceCdStStat(void);
extern void startDisplay(int on);
extern void endDisplay(void);
extern void audioDecResume(int *self);
extern int audioDecPause(int *self);
extern int audioDecIsPreset(int *self);
extern void audioDecStart(int *self);
extern void audioDecReset(int *self);
extern void videoDecAbort(int *self);
extern int videoDecGetState(int *self);
extern int videoDecFlush(int *self);
extern int videoDecIsFlushed(int *self);
extern int readBufBeginPut(int *self, void **p);
extern void readBufEndPut(int *self, int n);
extern int readBufBeginGet(int *self, void **p);
extern int readBufEndGet(int *self, int n);
extern int strFileRead(char *self, void *buf, int n, int *eof);
extern int sceMpegDemuxPssRing(int *dec, void *p, int n, int a3, int p4);
extern int voBufIsFull(char *self);
extern void gsb_ClearFrameBuffer(void);
extern char D_00557590[];
extern int D_0063AC74;
extern void dispCreate(int *self, int a1, int a2, int a3, int a4);
extern int strFileOpen(char *self, int name);
extern int readBufCreate(int *self);
extern void sceMpegInit(void);
extern int videoDecCreate(int *self);
extern int audioDecCreate(int *self, int a1, int a2);
extern int videoDecSetStream(int *self, int id, int a2, void *fn, void *arg);
extern int voBufCreate(char *self);

typedef struct {
    int status;
    void *entry;
    void *stack;
    int stackSize;
    void *gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
} ThreadParam;

extern int CreateThread(ThreadParam *th);
extern int StartThread(int id, void *arg);
extern int AddIntcHandler(int ch, void *fn, int a2);
extern int AddDmacHandler(int ch, void *fn, int a2);
extern int videoCallback();
extern int pcmCallback();
extern void videoDecMain();
extern int handler_endimage();
extern int vblankHandler();

/* Argument block handed to the videoDecMain thread; it reads the three
   members back as self[0], self[1] and self[2]. */
typedef struct {
    int *dec;   /* D_006F2AD0, the videoDec object   */
    void *disp; /* D_002A7978, the display env       */
    char *vo;   /* voBuf, the video-out ring         */
} MvThreadArg;

extern MvThreadArg D_006F2C00;
extern int D_006F2C40[];
extern int _gp; /* linker-defined global pointer */
extern int D_0063C310;
extern int D_0063C314;
extern int D_0063C318;
extern int D_0063C31C;
extern char D_005575A0[];
extern char D_005575B0[];
extern char D_005575C8[];
extern char D_005575E8[];
extern char D_005575F8[];
extern char D_00557608[];
extern char D_00557620[];
extern char D_00557630[];

void switchThread(void)
{
    RotateThreadReadyQueue(D_0063C320);
}

void proceedAudio(void)
{
    audioDecSendToIOP(D_006F2B98);
}

/* mv_main.c:55-57 */
static inline int audioIsPreset(void)
{
    return D_0063AC70 ? audioDecIsPreset(D_006F2B98) : 1;
}

int readMpeg(int *dec, int *rb, char *strf, int (*poll)(void))
{
    void *p;
    int eof;
    void *q;
    int abort = 0;
    int started = 0;
    int left;
    int n;
    int rd;
    int size;
    int len;

    left = *(int *)(strf + 0x8180);
    n = left;

    while (D_0063AC74 != 0 || (left >= 5 && videoDecGetState(dec) != 3)) {
        if (sceCdStStat() < 0x20 && D_0063AC74 == 0) {
            debug_StdPrintfDummy(D_00557590);
            D_0063AC74 = 30;
        }
        if (dec[2] >= 11) {
            if (D_0063AC74 == 1) {
                startDisplay(1);
                if (D_0063AC70 != 0) {
                    audioDecResume(D_006F2B98);
                }
            } else if (D_0063AC74 == 30) {
                endDisplay();
                if (D_0063AC70 != 0) {
                    audioDecPause(D_006F2B98);
                }
            }
            if (D_0063AC74 > 0) {
                D_0063AC74--;
            }
            if (poll() != 0) {
                abort = 1;
                videoDecAbort(D_006F2AD0);
            }
        }
        size = readBufBeginPut(rb, &p);
        if (n > 0 && size > 0xFFFF) {
            rd = strFileRead(strf, p, 0x10000, &eof);
            if (eof != 0) {
                goto term;
            }
            readBufEndPut(rb, rd);
            n -= rd;
        }
        switchThread();
        len = readBufBeginGet(rb, &q);
        if (len > 0) {
            len = sceMpegDemuxPssRing(dec, q, len, rb[0], rb[1]);
            left -= len;
            readBufEndGet(rb, len);
        }
        proceedAudio();
        if (started == 0 && voBufIsFull(voBuf) && audioIsPreset()) {
            startDisplay(1);
            if (D_0063AC70 != 0) {
                audioDecStart(D_006F2B98);
            }
            started = 1;
        }
    }

    while (videoDecFlush(dec) == 0) {
        switchThread();
    }
    while (videoDecIsFlushed(dec) == 0 && videoDecGetState(dec) != 3) {
        switchThread();
    }

term:
    gsb_ClearFrameBuffer();
    endDisplay();
    if (D_0063AC70 != 0) {
        audioDecReset(D_006F2B98);
    }
    return abort;
}

int initAll(int a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7)
{
    ThreadParam th;
    int ret = 0;

    D_0063AC74 = 0;
    D_006F2AD0[0xC4 / 4] = -1;
    D_006F2AD0[0xC0 / 4] = -1;
    D_0063C328 = 0;

    dispCreate(D_002A7978, a1, a2, a3, p4);
    dispClear(D_002A7978, p7);

    D_0063C334 = *(volatile int *)0x1000E000;
    debug_StdPrintfDummy(D_005575A0, *(volatile int *)0x1000E000);
    *(volatile int *)0x1000E000 |= 3;
    *(volatile int *)0x1000E010 = 4;

    debug_StdPrintfDummy(D_005575B0, a0);
    if (strFileOpen(D_006EA900, a0) == 0) {
        return -1;
    }
    if (readBufCreate(D_006F2AC0) != 0) {
        return -1;
    }
    sceMpegInit();
    if (videoDecCreate(D_006F2AD0) != 0) {
        return -1;
    }
    if (D_0063AC70 != 0) {
        if (audioDecCreate(D_006F2B98, p5, p6) != 0) {
            return -1;
        }
    }

    D_0063C310 = (int)D_006F2AC0;
    D_0063C314 = (int)D_006F2AD0;
    videoDecSetStream(D_006F2AD0, 0, 0, videoCallback, &D_0063C310);
    if (D_0063AC70 != 0) {
        D_0063C318 = (int)D_006F2AC0;
        D_0063C31C = (int)D_006F2B98;
        videoDecSetStream(D_006F2AD0, 2, 0, pcmCallback, &D_0063C318);
    }

    if (voBufCreate(voBuf) != 0) {
        return -1;
    }
    debug_StdPrintfDummy(D_005575C8);

    th.entry = (void *)videoDecMain;
    th.stack = (void *)D_006F2C40;
    th.stackSize = 0x8000;
    th.initPriority = D_0063C320;
    th.gpReg = &_gp;
    th.option = 0;
    D_0063C324 = CreateThread(&th);
    debug_StdPrintfDummy(D_005575E8);

    D_006F2C00.dec = D_006F2AD0;
    D_006F2C00.disp = D_002A7978;
    D_006F2C00.vo = voBuf;
    StartThread(D_0063C324, &D_006F2C00);
    D_0063C328 = 1;

    DIntr();
    debug_StdPrintfDummy(D_005575F8);
    D_006F2AD0[0xC4 / 4] = AddIntcHandler(2, vblankHandler, 0);
    if (D_006F2AD0[0xC4 / 4] < 0) {
        debug_StdPrintfDummy(D_00557608);
        ret = -1;
    } else {
        D_0063C32C = EnableIntc(2);
        debug_StdPrintfDummy(D_00557620);
        D_006F2AD0[0xC0 / 4] = AddDmacHandler(2, handler_endimage, 0);
        if (D_006F2AD0[0xC0 / 4] < 0) {
            debug_StdPrintfDummy(D_00557630);
            ret = -1;
        } else {
            D_0063C330 = EnableDmac(2);
        }
    }
    EIntr();
    return ret;
}

void termAll(void)
{
    strFileClose(D_006EA900);
    DIntr();
    if (D_0063C330 != 0) {
        DisableDmac(2);
    }
    D_0063C330 = 0;
    if (D_006F2AD0[0xC0 / 4] >= 0) {
        RemoveDmacHandler(2, D_006F2AD0[0xC0 / 4]);
    }
    if (D_0063C32C != 0) {
        DisableIntc(2);
    }
    D_0063C32C = 0;
    if (D_006F2AD0[0xC4 / 4] >= 0) {
        RemoveIntcHandler(2, D_006F2AD0[0xC4 / 4]);
    }
    EIntr();
    if (D_0063C328 != 0) {
        TerminateThread(D_0063C324);
        DeleteThread(D_0063C324);
    }
    readBufDelete(D_006F2AC0);
    voBufDelete(voBuf);
    videoDecDelete(D_006F2AD0);
    audioDecDelete(D_006F2B98);
    dispDelete(D_002A7978);
    *(volatile unsigned int *)0x1000E000 = D_0063C334;
}

/* mv_main.c:425 - the VU0 status register, read back into C */
static inline int vu0Stat(void)
{
    int r;
    __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(r));
    return r;
}

int movie_init(int a0, int a1, int a2, int a3, int p4, int p5, int p6)
{
    int st[12];
    unsigned int i;
    unsigned int j;

    while (vu0Stat() & 0x100) {}
    sceGsSyncPath(0, 0);

    ReferThreadStatus(GetThreadId(), st);
    D_0063C338 = st[0x18 / 4];
    D_0063C320 = st[0x18 / 4];
    D_0063C340 = sceGsGetIMR();
    debug_StdPrintfDummy(D_00557648, sceGsGetIMR());

    DIntr();
    for (i = 0; i < 7; i++) {
        D_006FAC40[i] = DisableDmac(D_002A7920[i]);
        debug_StdPrintfDummy(D_00557660, D_002A7920[i], D_006FAC40[i]);
    }
    for (j = 0; j < 7; j++) {
        D_006FAC60[j] = DisableIntc(D_002A7940[j]);
        debug_StdPrintfDummy(D_00557670, D_002A7940[j], D_006FAC60[j]);
    }
    EIntr();

    D_0063AC70 = 1;
    if (initAll(a0, a1, a2, a3, p4, p5, 0x3FFF, p6) != 0) {
        debug_StdPrintfDummy(D_00557680);
        movie_end();
        return -1;
    }
    return 0;
}

void movie_end(void)
{
    unsigned int i;
    unsigned int j;

    dispClear(D_002A7978, 0x80000000);
    termAll();
    DIntr();
    debug_StdPrintfDummy(D_00557648, sceGsGetIMR());
    sceGsPutIMR(D_0063C340);
    for (i = 0; i < 7; i++) {
        if (D_006FAC40[i] != 0) {
            EnableDmac(D_002A7920[i]);
        }
    }
    for (j = 0; j < 7; j++) {
        if (D_006FAC60[j] != 0) {
            EnableIntc(D_002A7940[j]);
        }
    }
    ChangeThreadPriority(GetThreadId(), D_0063C338);
    EIntr();
    debug_StdPrintfDummy(D_00557698);
}

int movie_proc(int (*poll)(void))
{
    int r;
    debug_StdPrintfDummy(D_0063AC80, D_0063AC78++);
    r = readMpeg(D_006F2AD0, D_006F2AC0, D_006EA900, poll);
    movie_end();
    return r;
}
