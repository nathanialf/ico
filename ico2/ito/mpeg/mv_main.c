#include "mv_defs.h"
#include "mv_main.h"
#include "debug.h"
#include "GsBase.h"
#include <eekernel.h>
#include <libgraph.h>
#include <libmpeg.h>
#include "mv_audiodec.h"
#include "mv_strfile.h"
#include "mv_readbuf.h"
#include "mv_videodec.h"
#include <eeregs.h>
#include <libcdvd.h>
#include "include_asm.h"

/* the DMA and interrupt channels the player takes over for the length of the
   stream and hands back one by one in movie_end. */
static int movieDmacChannel[] = {0, 1, 2, 3, 4, 8, 9}; /* derived name */

static int movieIntcChannel[] = {0, 1, 2, 4, 5, 6, 7}; /* derived name */

/* the video-out ring the decoder fills and mv_disp drains (mv_vobuf.h) */
VoBuf voBuf = {0};

/* the movie's display environment (mv_disp.h); debug_exception's `display`
   routine is that file's own static */
MvDispEnv display = {0};

/* The two callback argument pairs videoDecSetStream is handed by address,
   the priority the decode thread is created at and its id, the started flag,
   the interrupt and DMA enables and the D_CTRL word saved across playback,
   the caller's own priority, and the GS interrupt mask saved across
   playback (a 64-bit register). */
static MvCbArg videoCbArg; /* derived name */

static MvCbArg pcmCbArg; /* derived name */

static int decThreadPri; /* derived name */

static int decThreadId; /* derived name */

static int decThreadStarted; /* derived name */

static int savedIntc; /* derived name */

static int savedDmac; /* derived name */

static int savedDmaCtrl; /* derived name */

static int callerPri; /* derived name */

static long long savedIMR; /* derived name */

/* set once the movie has an audio stream */
static int movieHasAudio = 1; /* derived name */

/* frames left of a read-starved pause */
static int moviePauseCount = 0; /* derived name */

/* the debug frame counter */
static int movieFrameNo = 0; /* derived name */

/* The stream file the movie is read through, the read buffer, the video and
   audio decoder objects, the argument block the decode thread is started
   with, its 32 KB stack, and the DMA and interrupt enables saved per
   channel. */
static char mpegStrFile[33216]; /* derived name */

static ReadBuf mpegReadBuf; /* derived name */

static VideoDec videoDec; /* derived name */

static AudioDec audioDec; /* derived name */

static MvThreadArg decThreadArg; /* derived name */

static int decThreadStack[8192]; /* derived name */

static int savedDmacs[8]; /* derived name */

static int savedIntcs[8]; /* derived name */

extern int _gp; /* linker-defined global pointer */

void switchThread(void)
{
    RotateThreadReadyQueue(decThreadPri);
}

static void proceedAudio(void)
{
    audioDecSendToIOP(&audioDec);
}

/* whether the audio side is ready: its first block is on the IOP, or there
   is no audio stream */
static inline int audioIsPreset(void) /* derived name */
{
    return movieHasAudio ? audioDecIsPreset(&audioDec) : 1;
}

static int readMpeg(VideoDec *dec, ReadBuf *rb, char *strf, int (*poll)(void));

INCLUDE_ASM(readMpeg);

static int initAll(char *name, int imageW, int imageH, int dbx, int dby, int mono, int volume,
                   int clearCol);

INCLUDE_ASM(initAll);

static void termAll(void)
{
    strFileClose(mpegStrFile);
    DIntr();
    if (savedDmac != 0) {
        DisableDmac(2);
    }
    savedDmac = 0;
    if (videoDec.dmacHandler >= 0) {
        RemoveDmacHandler(2, videoDec.dmacHandler);
    }
    if (savedIntc != 0) {
        DisableIntc(2);
    }
    savedIntc = 0;
    if (videoDec.intcHandler >= 0) {
        RemoveIntcHandler(2, videoDec.intcHandler);
    }
    EIntr();
    if (decThreadStarted != 0) {
        TerminateThread(decThreadId);
        DeleteThread(decThreadId);
    }
    readBufDelete(&mpegReadBuf);
    voBufDelete(&voBuf);
    videoDecDelete(&videoDec);
    audioDecDelete(&audioDec);
    dispDelete(&display);
    *D_CTRL = savedDmaCtrl;
}

/* the VU0 status register */
static inline int vu0Stat(void) /* derived name */
{
    int r;
    __asm__ __volatile__("cfc2.ni %0, $vi29" : "=r"(r));
    return r;
}

int movie_init(char *name, int imageW, int imageH, int dbx, int dby, int mono, int clearCol)
{
    struct ThreadParam st;
    unsigned int i;
    unsigned int j;

    while (vu0Stat() & 0x100) {}
    sceGsSyncPath(0, 0);

    ReferThreadStatus(GetThreadId(), &st);
    callerPri = st.currentPriority;
    decThreadPri = st.currentPriority;
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

    movieHasAudio = 1;
    if (initAll(name, imageW, imageH, dbx, dby, mono, 0x3FFF, clearCol) != 0) {
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

    dispClear(&display, 0x80000000);
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
    debug_StdPrintfDummy("= %d =\n", movieFrameNo++);
    r = readMpeg(&videoDec, &mpegReadBuf, mpegStrFile, poll);
    movie_end();
    return r;
}
