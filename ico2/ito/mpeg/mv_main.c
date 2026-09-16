#include "common.h"
#include "mv_main.h"
#include "debug.h"
#include "GsBase.h"

/* --- the TU's whole .data run, VMA 0x2A7920..0x2A79B8 (0x98, = MAIN.MAP
   mv_main.o .data 0x98).  MAIN.MAP names the last two objects of the run,
   voBuf at member offset 0x40 and `display` at 0x58; the two channel lists
   ahead of them carry no map symbol, so those names are ours. */

/* the DMA and interrupt channels the player takes over for the length of the
   stream and hands back one by one in movie_end. */
static int movieDmacChannel[] = {0, 1, 2, 3, 4, 8, 9};

static int movieIntcChannel[] = {0, 1, 2, 4, 5, 6, 7};

/* the video-out ring the decoder fills and mv_disp drains: the five fields
   mv_vobuf.c spells as VoBuf (data, tag, idx, count, max).  RECONSTRUCTION:
   the ROM shows only zeroes here, the field list comes from mv_vobuf.c. */
typedef struct {
    void *data;         /* 0x00 */
    void *tag;          /* 0x04 */
    volatile int idx;   /* 0x08 */
    volatile int count; /* 0x0C */
    int max;            /* 0x10 */
} MvVoBuf;

MvVoBuf voBuf = {0};

/* the movie's display environment: the five GS privileged registers
   sceGsSetDefDispEnv fills (sce/libgraph/graph009.c's sceGsDispEnv) and the
   six words mv_disp.c's setDispEnv keeps after them.  MAIN.MAP calls this
   object `display`; the name has to wait, because ico2/common/src/debug_
   exception's still-asm `display` stub emits a global of that name. */
typedef struct {
    long long pmode;   /* 0x00 */
    long long smode2;  /* 0x08 */
    long long dispfb;  /* 0x10 */
    long long display; /* 0x18 */
    long long bgcolor; /* 0x20 */
    int f28;           /* 0x28 */
    int f2C;           /* 0x2C */
    int width;         /* 0x30 */
    int height;        /* 0x34 */
    int f38;           /* 0x38 */
    int f3C;           /* 0x3C */
} MvDispEnv;

MvDispEnv D_002A7978 = {0};

extern int D_0063C320;
extern void RotateThreadReadyQueue();
extern int D_006F2B98[];
/* kept local: this TU's uses of audioDecSendToIOP do not fit the prototype in mv_audiodec.h */
extern void audioDecSendToIOP();
extern int D_0063AC78;
extern char D_0063AC80[];
extern int D_006F2AD0[];
extern int D_006F2AC0[];
extern char D_006EA900[];
extern int D_0063C324;
extern int D_0063C328;
extern int D_0063C32C;
extern int D_0063C330;
extern int D_0063C334;
/* kept local: this TU's uses of strFileClose do not fit the prototype in mv_strfile.h */
extern void strFileClose(char *self);
extern int DIntr(void);
extern int EIntr(void);
extern int DisableDmac(int ch);
extern void RemoveDmacHandler(int ch, int id);
extern int DisableIntc(int ch);
extern void RemoveIntcHandler(int ch, int id);
extern void TerminateThread(int id);
extern void DeleteThread(int id);
/* kept local: this TU's uses of readBufDelete do not fit the prototype in mv_readbuf.h */
extern void readBufDelete(int *self);
/* kept local: this TU's uses of voBufDelete do not fit the prototype in mv_vobuf.h */
extern void voBufDelete(MvVoBuf *self);
/* kept local: this TU's uses of videoDecDelete do not fit the prototype in mv_videodec.h */
extern int videoDecDelete(int *self);
/* kept local: this TU's uses of audioDecDelete do not fit the prototype in mv_audiodec.h */
extern void audioDecDelete(int *self);
/* kept local: this TU's uses of dispDelete do not fit the prototype in mv_disp.h */
extern void dispDelete(MvDispEnv *self);
/* kept local: this TU's uses of dispClear do not fit the prototype in mv_disp.h */
extern void dispClear(MvDispEnv *self, unsigned int col);
extern int sceGsGetIMR(void);
extern void sceGsPutIMR(long long imr);
extern int EnableDmac(int ch);
extern int EnableIntc(int ch);
extern int GetThreadId(void);
extern void ChangeThreadPriority(int id, int prio);
extern int D_006FAC40[];
extern int D_006FAC60[];
extern int D_0063C338;
extern long long D_0063C340;
extern void sceGsSyncPath(int a0, int a1);
extern int ReferThreadStatus(int id, int *st);
extern int D_0063AC70;
void movie_end(void);
extern int sceCdStStat(void);
/* kept local: this TU's uses of startDisplay do not fit the prototype in mv_disp.h */
extern void startDisplay(int on);
/* kept local: this TU's uses of endDisplay do not fit the prototype in mv_disp.h */
extern void endDisplay(void);
/* kept local: this TU's uses of audioDecResume do not fit the prototype in mv_audiodec.h */
extern void audioDecResume(int *self);
/* kept local: this TU's uses of audioDecPause do not fit the prototype in mv_audiodec.h */
extern int audioDecPause(int *self);
/* kept local: this TU's uses of audioDecIsPreset do not fit the prototype in mv_audiodec.h */
extern int audioDecIsPreset(int *self);
/* kept local: this TU's uses of audioDecStart do not fit the prototype in mv_audiodec.h */
extern void audioDecStart(int *self);
/* kept local: this TU's uses of audioDecReset do not fit the prototype in mv_audiodec.h */
extern void audioDecReset(int *self);
/* kept local: this TU's uses of videoDecAbort do not fit the prototype in mv_videodec.h */
extern void videoDecAbort(int *self);
/* kept local: this TU's uses of videoDecGetState do not fit the prototype in mv_videodec.h */
extern int videoDecGetState(int *self);
/* kept local: this TU's uses of videoDecFlush do not fit the prototype in mv_videodec.h */
extern int videoDecFlush(int *self);
/* kept local: this TU's uses of videoDecIsFlushed do not fit the prototype in mv_videodec.h */
extern int videoDecIsFlushed(int *self);
/* kept local: this TU's uses of readBufBeginPut do not fit the prototype in mv_readbuf.h */
extern int readBufBeginPut(int *self, void **p);
/* kept local: this TU's uses of readBufEndPut do not fit the prototype in mv_readbuf.h */
extern void readBufEndPut(int *self, int n);
/* kept local: this TU's uses of readBufBeginGet do not fit the prototype in mv_readbuf.h */
extern int readBufBeginGet(int *self, void **p);
/* kept local: this TU's uses of readBufEndGet do not fit the prototype in mv_readbuf.h */
extern int readBufEndGet(int *self, int n);
/* kept local: this TU's uses of strFileRead do not fit the prototype in mv_strfile.h */
extern int strFileRead(char *self, void *buf, int n, int *eof);
extern int sceMpegDemuxPssRing(int *dec, void *p, int n, int a3, int p4);
/* kept local: this TU's uses of voBufIsFull do not fit the prototype in mv_vobuf.h */
extern int voBufIsFull(MvVoBuf *self);
extern int D_0063AC74;
/* kept local: this TU's uses of dispCreate do not fit the prototype in mv_disp.h */
extern void dispCreate(MvDispEnv *self, int a1, int a2, int a3, int a4);
/* kept local: this TU's uses of strFileOpen do not fit the prototype in mv_strfile.h */
extern int strFileOpen(char *self, int name);
/* kept local: this TU's uses of readBufCreate do not fit the prototype in mv_readbuf.h */
extern int readBufCreate(int *self);
extern void sceMpegInit(void);
/* kept local: this TU's uses of videoDecCreate do not fit the prototype in mv_videodec.h */
extern int videoDecCreate(int *self);
/* kept local: this TU's uses of audioDecCreate do not fit the prototype in mv_audiodec.h */
extern int audioDecCreate(int *self, int a1, int a2);
/* kept local: this TU's uses of videoDecSetStream do not fit the prototype in mv_videodec.h */
extern int videoDecSetStream(int *self, int id, int a2, void *fn, void *arg);
/* kept local: this TU's uses of voBufCreate do not fit the prototype in mv_vobuf.h */
extern int voBufCreate(MvVoBuf *self);

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
/* kept local: this TU's uses of videoCallback do not fit the prototype in mv_videodec.h */
extern int videoCallback();
/* kept local: this TU's uses of pcmCallback do not fit the prototype in mv_audiodec.h */
extern int pcmCallback();
/* kept local: this TU's uses of videoDecMain do not fit the prototype in mv_videodec.h */
extern void videoDecMain();
/* kept local: this TU's uses of handler_endimage do not fit the prototype in mv_disp.h */
extern int handler_endimage();
/* kept local: this TU's uses of vblankHandler do not fit the prototype in mv_disp.h */
extern int vblankHandler();

/* Argument block handed to the videoDecMain thread; it reads the three
   members back as self[0], self[1] and self[2]. */
typedef struct {
    int *dec;        /* D_006F2AD0, the videoDec object   */
    MvDispEnv *disp; /* the display env, MAIN.MAP `display` */
    MvVoBuf *vo;     /* voBuf, the video-out ring          */
} MvThreadArg;

extern MvThreadArg D_006F2C00;
extern int D_006F2C40[];
extern int _gp; /* linker-defined global pointer */
extern int D_0063C310;
extern int D_0063C314;
extern int D_0063C318;
extern int D_0063C31C;

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
            debug_StdPrintfDummy("movie pause\n");
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
        if (started == 0 && voBufIsFull(&voBuf) && audioIsPreset()) {
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

    dispCreate(&D_002A7978, a1, a2, a3, p4);
    dispClear(&D_002A7978, p7);

    D_0063C334 = *(volatile int *)0x1000E000;
    debug_StdPrintfDummy("D_CTRL %x\n", *(volatile int *)0x1000E000);
    *(volatile int *)0x1000E000 |= 3;
    *(volatile int *)0x1000E010 = 4;

    debug_StdPrintfDummy("open movie file %s\n", a0);
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

    if (voBufCreate(&voBuf) != 0) {
        return -1;
    }
    debug_StdPrintfDummy("create video decode thread\n");

    th.entry = (void *)videoDecMain;
    th.stack = (void *)D_006F2C40;
    th.stackSize = 0x8000;
    th.initPriority = D_0063C320;
    th.gpReg = &_gp;
    th.option = 0;
    D_0063C324 = CreateThread(&th);
    debug_StdPrintfDummy("start thread\n");

    D_006F2C00.dec = D_006F2AD0;
    D_006F2C00.disp = &D_002A7978;
    D_006F2C00.vo = &voBuf;
    StartThread(D_0063C324, &D_006F2C00);
    D_0063C328 = 1;

    DIntr();
    debug_StdPrintfDummy("add intc\n");
    D_006F2AD0[0xC4 / 4] = AddIntcHandler(2, vblankHandler, 0);
    if (D_006F2AD0[0xC4 / 4] < 0) {
        debug_StdPrintfDummy("add intc failed\n");
        ret = -1;
    } else {
        D_0063C32C = EnableIntc(2);
        debug_StdPrintfDummy("add dmac\n");
        D_006F2AD0[0xC0 / 4] = AddDmacHandler(2, handler_endimage, 0);
        if (D_006F2AD0[0xC0 / 4] < 0) {
            debug_StdPrintfDummy("add dmac failed\n");
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
    voBufDelete(&voBuf);
    videoDecDelete(D_006F2AD0);
    audioDecDelete(D_006F2B98);
    dispDelete(&D_002A7978);
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
    debug_StdPrintfDummy("sceGsGetIMR() %lx\n", sceGsGetIMR());

    DIntr();
    for (i = 0; i < 7; i++) {
        D_006FAC40[i] = DisableDmac(movieDmacChannel[i]);
        debug_StdPrintfDummy("dmac %d %d\n", movieDmacChannel[i], D_006FAC40[i]);
    }
    for (j = 0; j < 7; j++) {
        D_006FAC60[j] = DisableIntc(movieIntcChannel[j]);
        debug_StdPrintfDummy("intc %d %d\n", movieIntcChannel[j], D_006FAC60[j]);
    }
    EIntr();

    D_0063AC70 = 1;
    if (initAll(a0, a1, a2, a3, p4, p5, 0x3FFF, p6) != 0) {
        debug_StdPrintfDummy("movie init failed\n");
        movie_end();
        return -1;
    }
    return 0;
}

void movie_end(void)
{
    unsigned int i;
    unsigned int j;

    dispClear(&D_002A7978, 0x80000000);
    termAll();
    DIntr();
    debug_StdPrintfDummy("sceGsGetIMR() %lx\n", sceGsGetIMR());
    sceGsPutIMR(D_0063C340);
    for (i = 0; i < 7; i++) {
        if (D_006FAC40[i] != 0) {
            EnableDmac(movieDmacChannel[i]);
        }
    }
    for (j = 0; j < 7; j++) {
        if (D_006FAC60[j] != 0) {
            EnableIntc(movieIntcChannel[j]);
        }
    }
    ChangeThreadPriority(GetThreadId(), D_0063C338);
    EIntr();
    debug_StdPrintfDummy("movie end\n");
}

int movie_proc(int (*poll)(void))
{
    int r;
    debug_StdPrintfDummy(D_0063AC80, D_0063AC78++);
    r = readMpeg(D_006F2AD0, D_006F2AC0, D_006EA900, poll);
    movie_end();
    return r;
}
