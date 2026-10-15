#include "debug.h"
#include "cdvd.h"
#include "memory.h"
#include "matrixDrive.h"
#include "streamMotionManager.h"
#include "GsBase.h"
#include "BgAnimation.h"
#include "ios.h"
#include "main.h"
#include <string.h>
#include "thread.h"
#include "include_asm.h"

static int _closeHander(void);
static int _handler(struct CdvdBgReq *self);
static void _deleteStreamMotionManager(void);

/* the stream entry count and state, the background reader's state and id,
   the ring buffer's read and write offsets and buffers, the header parse, the
   owner, the ring use, the idle flag and the frame clock */
static int streamNum = 0; /* derived name */

static int streamState = 0; /* derived name */

static int readState = 0; /* derived name */

static CdvdBgReq *bgMgrId = 0; /* derived name */

static int ringRead = 0; /* derived name */

static int ringWrite = 0; /* derived name */

static char *ringBuf = 0; /* derived name */

static char *readBuf = 0; /* derived name */

static char *readBufRaw = 0; /* derived name */

static int headerRead = 0; /* derived name */

static int headerSize = 0; /* derived name */

static char *streamOwner = 0; /* derived name */

static int ringUsed = 0; /* derived name */

static unsigned int streamIdle = 1; /* derived name */

/* One character's stream: the node and shape counts the frame header gives,
   the frame's size, the ring offset of the current frame, the object and the
   function called when the stream ends. */
typedef struct {  /* field names derived */
    int nodeNum;  /* 0x00, 8 bytes a node */
    int shapeNum; /* 0x04, 4 bytes a shape */
    int size;     /* 0x08, 16 + the two */
    int cur;      /* 0x0C, -1 until data arrives */

    union {
        int i;
        GObj *p;
    } obj; /* 0x10, stored as a word: EntryStreamMotion's store of it stays
              behind the reads of the object it follows only under an
              any-type view */

    void (*finishFunc)(GObj *); /* 0x14 */
} SMotion;                      /* derived name */

/* the ten stream-motion slots _deleteStreamMotionManager resets to
   emptyEntry */
static SMotion streamEntry[10]; /* derived name */

/* The ring is 163840 bytes; the check asks whether the write pointer has run
 * far enough ahead of the read pointer for `room` more bytes to be there. */
static inline int _checkRing(int room) /* derived name */
{
    unsigned int p = ringRead;
    unsigned int end = p + room;
    unsigned int q = ringWrite;
    int r;

    if (q < p) {
        q += 163840;
    }
    r = 1;
    if (!(q < p) && (int)q < (int)end) {
        r = 0;
    }
    return r;
}

static inline void _setEntryOffsets(void) /* derived name */
{
    unsigned int off = 0;
    int i;

    for (i = 0; i < streamNum; i++) {
        streamEntry[i].cur = (ringRead + off) % 163840;
        off += streamEntry[i].size;
    }
}

static inline void _advanceRing(int amt) /* derived name */
{
    ringUsed += amt;
    ringRead += amt;
    if ((unsigned int)ringRead > 163839) {
        ringRead -= 163840;
    }
}

INCLUDE_ASM(_infoUpdate);

void PlayStreamMotion(void)
{
    if (bgMgrId == 0) {
        /* StandbyStreamMotion has not been called; nothing was played */
        debug_StdPrintfDummy("StandbyStreamMotionが呼ばれてません。再生はされませんでした。\n");
        return;
    }
    streamState = 1;
}

/* reset the actor's stream-motion state; the offset trace at the end is
 * switched off */
void ClearStreamMotionEntry(GObj *gobj)
{
    GOBJ_SUB(gobj)->ctrl.stream = -1;
    GOBJ_SUB(gobj)->streamScale = 1;
    CopyVector(GOBJ_SUB(gobj)->streamOfs, ZeroVector);
    GOBJ_SUB(gobj)->ctrl.catchBoy = 1;
    if (0) {
        float v[4];

        CopyVector(v, GOBJ_SUB(gobj)->streamOfs);
        debug_StdPrintfDummy("ADJUST %08x(%f)\n", gobj, v[0]);
    }
}

/* the cleared entry every slot is reset to */
static SMotion emptyEntry = {0, 0, -1, -1, {0}, 0}; /* derived name */

INCLUDE_ASM(_deleteStreamMotionManager);

void DisableStreamMotionManagerAutomaticDelete(void)
{
    streamIdle = 0;
    debug_StdPrintfDummy("disable automatic delete\n");
}

INCLUDE_ASM_LIT(GetDataSizeOfStreamMotion);

typedef struct { /* field names derived */
    char c[4];
} StreamMotionHead; /* derived name */

/* the four bytes GetStreamMotionData hands back while no data has arrived */
static const char streamDummyHead[] = {0, 0xFF, 0, 0}; /* derived name */

INCLUDE_ASM(func_001F0A38);

static void _transRingBuf(int *idx_p, char *dst, int size, char *src, int amt)
{
    int old_idx = *idx_p;
    int new_idx = old_idx + amt;
    *idx_p = new_idx;
    if (new_idx >= size) {
        int overflow = new_idx - size;
        int first_chunk = amt - overflow;
        *idx_p = overflow;
        memcpy(dst + old_idx, src, first_chunk);
        memcpy(dst, src + first_chunk, *idx_p);
        return;
    }
    memcpy(dst + old_idx, src, amt);
}

void ExecStreamMotionManager(void)
{
    int i;
    int pct;

    switch (streamState) {
    case 0:
        break;
    case 1:
        if (_infoUpdate() != 0) {
            /* "detected the end of the stream motion" */
            debug_StdPrintfDummy("ストリームモーションの終了を検知\n");
            streamState = 0;
            if (streamIdle != 0) {
                if (bgMgrId != 0) {
                    iosCdvdBackGroundMgrDelete(bgMgrId);
                } else {
                    _deleteStreamMotionManager();
                }
                if (streamNum != 0) {
                    for (i = 0; i < streamNum; i++) {
                        ClearStreamMotionEntry(streamEntry[i].obj.p);
                        if (streamEntry[i].finishFunc != 0) {
                            streamEntry[i].finishFunc(streamEntry[i].obj.p);
                        }
                    }
                    streamNum = 0;
                }
            }
        }
        break;
    }
    if (bgMgrId != 0) {
        unsigned int wp = ringWrite;
        unsigned int rp = ringRead;

        if (wp < rp) {
            pct = wp + 163840 - rp;
        } else {
            pct = wp - rp;
        }
        pct = pct * 100 / 163840;
        if (debug_font_flag & 1) {
            debug_Printf(0, ScreenHeight / 2 - 16, 0xFF404000, " %d%%", pct);
        }
        if (debug_font_flag & 1) {
            debug_Printf(58, ScreenHeight / 2 - 16, 0x40FF4000, "STANDBY %d CHARS %s", streamNum,
                         streamOwner);
        }
    }
}

INCLUDE_ASM(MallocStreamMotionBuffer);

INCLUDE_ASM_LIT(StandbyStreamMotion);

INCLUDE_ASM(StandbyStreamMotion);

INCLUDE_ASM(StopStreamMotion);

INCLUDE_ASM(DeleteStreamMotionManager);

INCLUDE_ASM(EntryStreamMotion);

INCLUDE_ASM(GetDataSizeOfStreamMotion);

INCLUDE_ASM(InitStreamMotionManager);

INCLUDE_ASM(CheckReadyStreamMotion);

INCLUDE_ASM(SetStreamMotionFinishCallBackFunc);

INCLUDE_ASM(FreeStreamMotionBuffer);

INCLUDE_ASM(ClearAllStreamMotionEntry);

INCLUDE_ASM(_closeHander);

INCLUDE_ASM(_handler);
