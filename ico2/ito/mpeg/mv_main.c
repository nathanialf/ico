#include "common.h"
#include "mv_main.h"
#include "debug.h"
#include "GsBase.h"
#include <eekernel.h>
#include <libmpeg.h>
#include "mv_audiodec.h"

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

/* .sbss, owned by mv_main.o (MAIN.MAP names no symbol in the run), in the ROM's
   run order: the two callback argument pairs videoDecSetStream is handed by
   address, the priority the decode thread is created at and its id, the started
   flag, the interrupt and DMA enables and the D_CTRL word saved across playback,
   the caller's own priority, and the GS interrupt mask saved across playback.
   The long long forces the 8-byte alignment that leaves the word before it
   unused, which is what makes the run 0x38 bytes. */
static int videoCbMgr;

static int videoCbStream;

static int pcmCbMgr;

static int pcmCbStream;

static int decThreadPri;

static int decThreadId;

static int decThreadStarted;

static int savedIntc;

static int savedDmac;

static int savedDmaCtrl;

static int callerPri;

static long long savedIMR;

extern int D_0063AC78;
extern char D_0063AC80[];
/* kept local: this TU's uses of strFileClose do not fit the prototype in mv_strfile.h */
extern void strFileClose(char *self);
extern int DIntr(void);
extern int EIntr(void);
/* kept local: this TU's uses of readBufDelete do not fit the prototype in mv_readbuf.h */
extern void readBufDelete(int *self);
/* kept local: this TU's uses of voBufDelete do not fit the prototype in mv_vobuf.h */
extern void voBufDelete(MvVoBuf *self);
/* kept local: this TU's uses of videoDecDelete do not fit the prototype in mv_videodec.h */
extern int videoDecDelete(int *self);
/* kept local: this TU's uses of dispDelete do not fit the prototype in mv_disp.h */
extern void dispDelete(MvDispEnv *self);
/* kept local: this TU's uses of dispClear do not fit the prototype in mv_disp.h */
extern void dispClear(MvDispEnv *self, unsigned int col);
extern int sceGsGetIMR(void);
extern void sceGsPutIMR(long long imr);
extern void sceGsSyncPath(int a0, int a1);
extern int D_0063AC70;
void movie_end(void);
extern int sceCdStStat(void);
/* kept local: this TU's uses of startDisplay do not fit the prototype in mv_disp.h */
extern void startDisplay(int on);
/* kept local: this TU's uses of endDisplay do not fit the prototype in mv_disp.h */
extern void endDisplay(void);
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
/* kept local: this TU's uses of voBufIsFull do not fit the prototype in mv_vobuf.h */
extern int voBufIsFull(MvVoBuf *self);
extern int D_0063AC74;
/* kept local: this TU's uses of dispCreate do not fit the prototype in mv_disp.h */
extern void dispCreate(MvDispEnv *self, int a1, int a2, int a3, int a4);
/* kept local: this TU's uses of strFileOpen do not fit the prototype in mv_strfile.h */
extern int strFileOpen(char *self, int name);
/* kept local: this TU's uses of readBufCreate do not fit the prototype in mv_readbuf.h */
extern int readBufCreate(int *self);
/* kept local: this TU's uses of videoDecCreate do not fit the prototype in mv_videodec.h */
extern int videoDecCreate(int *self);
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
/* kept local: this TU's uses of videoCallback do not fit the prototype in mv_videodec.h */
extern int videoCallback();
/* kept local: this TU's uses of videoDecMain do not fit the prototype in mv_videodec.h */
extern void videoDecMain();
/* kept local: this TU's uses of handler_endimage do not fit the prototype in mv_disp.h */
extern int handler_endimage();
/* kept local: this TU's uses of vblankHandler do not fit the prototype in mv_disp.h */
extern int vblankHandler();

/* Argument block handed to the videoDecMain thread; it reads the three
   members back as self[0], self[1] and self[2]. */
typedef struct {
    int *dec;        /* videoDec, the videoDec object   */
    MvDispEnv *disp; /* the display env, MAIN.MAP `display` */
    MvVoBuf *vo;     /* voBuf, the video-out ring          */
    /* the ROM's .bss run spaces the next object 0x40 on, so the block the
       developers declared reserves that much; only the three above are used */
    char reserved[64 - 12];
} MvThreadArg;

/* .bss, owned by mv_main.o (0x10380, the run, tiled exactly by these eight;
   MAIN.MAP's own link sizes it 0x1037C), in the ROM's run order: the stream
   file the movie is read through, the read buffer, the video and audio decoder
   objects, the argument block the decode thread is started with, its 0x8000
   stack, and the DMA and interrupt enables saved per channel. */
static char mpegStrFile[33216];

static int mpegReadBuf[4];

static int videoDec[50];

static AudioDec audioDec;

static MvThreadArg decThreadArg;

static int decThreadStack[8192];

static int savedDmacs[8];

static int savedIntcs[8];

extern int _gp; /* linker-defined global pointer */

void switchThread(void)
{
    RotateThreadReadyQueue(decThreadPri);
}

void proceedAudio(void)
{
    audioDecSendToIOP(&audioDec);
}

/* mv_main.c:55-57 */
static inline int audioIsPreset(void)
{
    return D_0063AC70 ? audioDecIsPreset(&audioDec) : 1;
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
                    audioDecResume(&audioDec);
                }
            } else if (D_0063AC74 == 30) {
                endDisplay();
                if (D_0063AC70 != 0) {
                    audioDecPause(&audioDec);
                }
            }
            if (D_0063AC74 > 0) {
                D_0063AC74--;
            }
            if (poll() != 0) {
                abort = 1;
                videoDecAbort(videoDec);
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
                audioDecStart(&audioDec);
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
        audioDecReset(&audioDec);
    }
    return abort;
}

int initAll(int a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7)
{
    ThreadParam th;
    int ret = 0;

    D_0063AC74 = 0;
    videoDec[0xC4 / 4] = -1;
    videoDec[0xC0 / 4] = -1;
    decThreadStarted = 0;

    dispCreate(&D_002A7978, a1, a2, a3, p4);
    dispClear(&D_002A7978, p7);

    savedDmaCtrl = *(volatile int *)0x1000E000;
    debug_StdPrintfDummy("D_CTRL %x\n", *(volatile int *)0x1000E000);
    *(volatile int *)0x1000E000 |= 3;
    *(volatile int *)0x1000E010 = 4;

    debug_StdPrintfDummy("open movie file %s\n", a0);
    if (strFileOpen(mpegStrFile, a0) == 0) {
        return -1;
    }
    if (readBufCreate(mpegReadBuf) != 0) {
        return -1;
    }
    sceMpegInit();
    if (videoDecCreate(videoDec) != 0) {
        return -1;
    }
    if (D_0063AC70 != 0) {
        if (audioDecCreate(&audioDec, p5, p6) != 0) {
            return -1;
        }
    }

    videoCbMgr = (int)mpegReadBuf;
    videoCbStream = (int)videoDec;
    videoDecSetStream(videoDec, 0, 0, videoCallback, &videoCbMgr);
    if (D_0063AC70 != 0) {
        pcmCbMgr = (int)mpegReadBuf;
        pcmCbStream = (int)&audioDec;
        videoDecSetStream(videoDec, 2, 0, pcmCallback, &pcmCbMgr);
    }

    if (voBufCreate(&voBuf) != 0) {
        return -1;
    }
    debug_StdPrintfDummy("create video decode thread\n");

    th.entry = (void *)videoDecMain;
    th.stack = (void *)decThreadStack;
    th.stackSize = 0x8000;
    th.initPriority = decThreadPri;
    th.gpReg = &_gp;
    th.option = 0;
    decThreadId = CreateThread(&th);
    debug_StdPrintfDummy("start thread\n");

    decThreadArg.dec = videoDec;
    decThreadArg.disp = &D_002A7978;
    decThreadArg.vo = &voBuf;
    StartThread(decThreadId, &decThreadArg);
    decThreadStarted = 1;

    DIntr();
    debug_StdPrintfDummy("add intc\n");
    videoDec[0xC4 / 4] = AddIntcHandler(2, vblankHandler, 0);
    if (videoDec[0xC4 / 4] < 0) {
        debug_StdPrintfDummy("add intc failed\n");
        ret = -1;
    } else {
        savedIntc = EnableIntc(2);
        debug_StdPrintfDummy("add dmac\n");
        videoDec[0xC0 / 4] = AddDmacHandler(2, handler_endimage, 0);
        if (videoDec[0xC0 / 4] < 0) {
            debug_StdPrintfDummy("add dmac failed\n");
            ret = -1;
        } else {
            savedDmac = EnableDmac(2);
        }
    }
    EIntr();
    return ret;
}

void termAll(void)
{
    strFileClose(mpegStrFile);
    DIntr();
    if (savedDmac != 0) {
        DisableDmac(2);
    }
    savedDmac = 0;
    if (videoDec[0xC0 / 4] >= 0) {
        RemoveDmacHandler(2, videoDec[0xC0 / 4]);
    }
    if (savedIntc != 0) {
        DisableIntc(2);
    }
    savedIntc = 0;
    if (videoDec[0xC4 / 4] >= 0) {
        RemoveIntcHandler(2, videoDec[0xC4 / 4]);
    }
    EIntr();
    if (decThreadStarted != 0) {
        TerminateThread(decThreadId);
        DeleteThread(decThreadId);
    }
    readBufDelete(mpegReadBuf);
    voBufDelete(&voBuf);
    videoDecDelete(videoDec);
    audioDecDelete(&audioDec);
    dispDelete(&D_002A7978);
    *(volatile unsigned int *)0x1000E000 = savedDmaCtrl;
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
    callerPri = st[0x18 / 4];
    decThreadPri = st[0x18 / 4];
    savedIMR = sceGsGetIMR();
    debug_StdPrintfDummy("sceGsGetIMR() %lx\n", sceGsGetIMR());

    DIntr();
    for (i = 0; i < 7; i++) {
        savedDmacs[i] = DisableDmac(movieDmacChannel[i]);
        debug_StdPrintfDummy("dmac %d %d\n", movieDmacChannel[i], savedDmacs[i]);
    }
    for (j = 0; j < 7; j++) {
        savedIntcs[j] = DisableIntc(movieIntcChannel[j]);
        debug_StdPrintfDummy("intc %d %d\n", movieIntcChannel[j], savedIntcs[j]);
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
    sceGsPutIMR(savedIMR);
    for (i = 0; i < 7; i++) {
        if (savedDmacs[i] != 0) {
            EnableDmac(movieDmacChannel[i]);
        }
    }
    for (j = 0; j < 7; j++) {
        if (savedIntcs[j] != 0) {
            EnableIntc(movieIntcChannel[j]);
        }
    }
    ChangeThreadPriority(GetThreadId(), callerPri);
    EIntr();
    debug_StdPrintfDummy("movie end\n");
}

int movie_proc(int (*poll)(void))
{
    int r;
    debug_StdPrintfDummy(D_0063AC80, D_0063AC78++);
    r = readMpeg(videoDec, mpegReadBuf, mpegStrFile, poll);
    movie_end();
    return r;
}
