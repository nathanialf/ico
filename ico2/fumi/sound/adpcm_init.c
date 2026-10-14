#include "debug.h"
#include "ios.h"
#include "adpcm_init.h"
#include <sifrpc.h>
#include "s_init.h"
#include "debug_exception.h"
#include "cdvd.h"
#include <assert.h>
#include <sound.h>
#include "include_asm.h"

static inline void adpcmDiskNotReady(void);
static inline void adpcmDiskReturnReady(void);
static inline int adpcmOpenProc(CdvdBgReq *bg, AdpcmOpenReq *open);
static inline void adpcmOpenDiskNotReady(void);

/* the 2 KB-aligned base of the IOP stream buffers, the two buffers' in-use
   flags, the pause request and the IOP heap block the base was cut from;
   then the two stream records and the four SPU slots the streams play on */
static int adpcmIopBase; /* derived name */

static int adpcmIopBuffUsed[2]; /* derived name */

static int adpcmPause; /* derived name */

static int adpcmIopHeap; /* derived name */

static AdpcmStream adpcmStream[2]; /* derived name */

static int adpcmSpuSlot[4]; /* derived name */

void AdpcmStreamFree(void)
{
    sceSifFreeIopHeap(adpcmIopHeap);
}

void adpcmTickProc2(SqEntry *obj)
{
    AdpcmStream *self = obj->stream;
    int i;

    if (iosCdvdDiskStatusGet() == 0 && adpcmPause == 0) {
        for (i = 0; i < self->n; i++) {
            char *ch = (char *)self->ch;
            int ofs = i * 4;
            int no = obj->num;
            SgStAdpcmChannelPitch(1LL << *(int *)(ch + ofs), adpcmFile[no].pitch);
        }
    } else {
        for (i = 0; i < self->n; i++) {
            char *ch = (char *)self->ch;
            int ofs = i * 4;
            SgStAdpcmChannelPitch(1LL << *(int *)(ch + ofs), 0);
        }
        return;
    }
    if (self->loopNum != 0) {
        int addr = SgStAdpcmIopReadAddr(self->ch[0]);
        int delta;

        if (addr >= self->lastAddr) {
            delta = addr - self->lastAddr;
        } else {
            delta = self->ringSize - self->lastAddr + addr;
        }
        self->lastAddr = addr;
        if (delta != 0) {
            self->remain -= delta;
            if (self->remain <= 0) {
                self->loopCount += 1;
                self->remain += self->dataSize - self->loopStart;
            }
            if (self->loopNum != 0 && self->loopCount >= self->loopNum) {
                soundDataClose(obj);
                return;
            }
        }
    }
    if (self->fadeStep != 0) {
        int d = AdpcmVolumeGet(obj) - self->fadeStep;

        if (d < 0) {
            d = 0;
        }
        if (d == 0) {
            soundDataClose(obj);
            return;
        }
        AdpcmVolumeSet(obj, d);
    }
}

/* adpcm_init.o's .rodata opens with these three named objects: the two
   messages are printed further down the file than the strings that follow
   them. */
static const char adpcmSrcFile[] = __FILE__; /* derived name */

static const char adpcmNoAllocMsg[] = "AdpcmIopBuffAlloc not alloc\n"; /* derived name */

/* the IOP area is reserved but unused, so it is being freed */
static const char adpcmFreeIopMsg[] =
    "IOP領域が確保されているのにもかかわらず,使われていなので解放します\n"; /* derived name */

int debugAdpcmOn = 1;

SqEntry *adpcmDataSet(int src, int no, int bank, int ch, int size, int iopBuf, int loopNum);

INCLUDE_ASM(adpcmDataSet);

void AdpcmPlay(AdpcmStream *self)
{
    debug_StdPrintfDummy("AdpcmPlay\n");
    SgStAdpcmPlay(self->mask);
}

void AdpcmStop(AdpcmStream *self)
{
    SgStAdpcmStop(self->mask);
}

INCLUDE_ASM(AdpcmOpen);

static inline void AdpcmIopBuffFree(AdpcmStream *self) /* derived name */
{
    int adr = self->iopBuf;
    int no = (adr - adpcmIopBase) / 0x5C000;

    if (no >= 3) {
        debug_assert(adpcmSrcFile, 143);
        __assert(adpcmSrcFile, 143, "0");
    }
    adpcmIopBuffUsed[no] = 0;
}

INCLUDE_ASM(AdpcmClose);

/* the levels come back out of the record the caller just wrote */
void AdpcmInterStereoVolumeSet(void *stream, int ch)
{
    char *st = (char *)stream;
    int j = ch + 1;
    short *r = (short *)(st + ch * 2);
    short *q = (short *)(st + j * 2);
    short lv = r[0x1E];
    short rv = q[0x20];

    if (debugAdpcmOn == 0) {
        rv = 0;
        lv = 0;
    }
    if (*(int *)(st + 0x38) == 0x10000) {
        return;
    }
    if (soundOutputModeGet() == 0) {
        int *p = (int *)(st + 8);
        int *c = p + ch;
        SgStAdpcmChannelVolume(1LL << *c, lv, 0);
        p += j;
        SgStAdpcmChannelVolume(1LL << *p, 0, rv);
    } else {
        int *p = (int *)(st + 8);
        int *c = p + ch;
        SgStAdpcmChannelVolume(1LL << *c, lv, rv);
        p += j;
        SgStAdpcmChannelVolume(1LL << *p, lv, rv);
    }
}

void AdpcmInterLeaveVolumeSet(SqEntry *self, int idx, int vol)
{
    char *b = (char *)self->stream;
    short *q = (short *)(b + (idx * 2 + 1) * 2);
    short *r = (short *)(b + idx * 4);
    q[0x20] = vol;
    r[0x1E] = vol;
    AdpcmInterStereoVolumeSet(b, idx * 2);
}

void AdpcmVolumeSet(SqEntry *self, int vol)
{
    AdpcmInterLeaveVolumeSet(self, 0, vol);
}

INCLUDE_ASM_LIT(AdpcmOpenSync);

INCLUDE_ASM(adpcmPauseRequest);

INCLUDE_ASM(AdpcmStreamHeap);

INCLUDE_ASM(AdpcmStreamInit);

INCLUDE_ASM(AdpcmIopBuffAlloc);

INCLUDE_ASM(AdpcmNotUseIopAreaFree);

INCLUDE_ASM(AdpcmOpenSync);

INCLUDE_ASM(AdpcmFadeCloseAll);

INCLUDE_ASM(AdpcmUseAreaGet);

INCLUDE_ASM(AdpcmFreeAreaGet);

INCLUDE_ASM(AdpcmInterStereoVolumeSetAll);

INCLUDE_ASM(AdpcmInterLeaveVolumeGet);

INCLUDE_ASM(AdpcmVolumeGet);

INCLUDE_ASM(adpcmTickProc);

INCLUDE_ASM(adpcmDiskNotReady);

INCLUDE_ASM(adpcmDiskReturnReady);

INCLUDE_ASM(adpcmOpenProc);

INCLUDE_ASM(adpcmOpenDiskNotReady);
