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

static inline int _closeHander(void);
static inline int _handler(struct CdvdBgReq *self);
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

static int headerRead = 0; /* derived name */

static int headerSize = 0; /* derived name */

static char *streamOwner = 0; /* derived name */

static int ringUsed = 0; /* derived name */

/* This build has no read-buffer alignment copy (readBuf is allocated
   directly) and no idle flag: streamMotionManager.o's .sdata ends with
   ExecStreamMotionManager's string in the demo. */

/* One character's stream, 20 bytes in this build: the node and shape counts
   the frame header gives, the frame's size, the ring offset of the current
   frame and the object (no end callback yet). */
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
} SMotion; /* derived name */

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

static int _infoUpdate(void)
{
    int i;

    if (headerRead == 0) {
        if (_checkRing(4096)) {
            headerSize = 0;
            for (i = 0; i < streamNum; i++) {
                int a = ringRead + headerSize;

                streamEntry[i].nodeNum = *(unsigned char *)(ringBuf + (a + 2) % 163840);
                streamEntry[i].shapeNum = *(unsigned char *)(ringBuf + (a + 3) % 163840);
                streamEntry[i].size = 16 + streamEntry[i].nodeNum * 8 + streamEntry[i].shapeNum * 4;
                headerSize += streamEntry[i].size;
            }
            headerRead = 1;
        } else {
            /* the data had not arrived in time when the stream motion started */
            debug_StdPrintfDummy(
                "ストリームモーション開始時にデータの転送が間に合っていませんでした。\n");
            return 0;
        }
    }
    if (_checkRing(headerSize)) {
        _setEntryOffsets();
        if (*(unsigned char *)(ringBuf + ringRead) != 0) {
            return 1;
        }
        _advanceRing(headerSize);
    } else {
        /* the stream motion data transfer is not keeping up */
        debug_StdPrintfDummy("ストリームモーションのデータ転送が間に合っていません。\n");
    }
    return 0;
}

void PlayStreamMotion(void)
{
    if (bgMgrId == 0) {
        /* StandbyStreamMotion has not been called; nothing was played */
        debug_StdPrintfDummy("StandbyStreamMotionが呼ばれてません。再生はされませんでした。\n");
        return;
    }
    streamState = 1;
}

/* reset the actor's stream-motion state */
inline void ClearStreamMotionEntry(GObj *gobj)
{
    GOBJ_SUB(gobj)->ctrl.stream = -1;
    GOBJ_SUB(gobj)->streamScale = 1;
    CopyVector(GOBJ_SUB(gobj)->streamOfs, ZeroVector);
    GOBJ_SUB(gobj)->ctrl.catchBoy = 1;
}

/* the cleared entry every slot is reset to */
static SMotion emptyEntry = {0, 0, -1, -1, {0}}; /* derived name */

static void _deleteStreamMotionManager(void)
{
    int i;

    if (streamNum != 0) {
        for (i = 0; i < streamNum; i++) {
            ClearStreamMotionEntry(streamEntry[i].obj.p);
        }
        streamNum = 0;
    }
    for (i = 0; i < 10; i++) {
        streamEntry[i] = emptyEntry;
    }
    streamState = 0;
    readState = 0;
    ringRead = 0;
    ringWrite = 0;
    headerRead = 0;
    headerSize = 0;
    ringUsed = 0;
    if (ringBuf != 0) {
        iosFree(ringBuf);
        iosFree(readBuf);
        ringBuf = 0;
        readBuf = 0;
    }
    if (bgMgrId != 0) {
        bgMgrId = 0;
    }
    debug_StdPrintfDummy("delete stream motion manager\n");
}

inline int GetDataSizeOfStreamMotion(int no)
{
    if (streamEntry[no].cur < 0) {
        /* tried to get the work size before the data has arrived */
        debug_StdPrintfDummy("データがまだ来ていないのにワークサイズの取得をしようとしました\n");
        return 4;
    }
    return streamEntry[no].size;
}

typedef struct { /* field names derived */
    char c[4];
} StreamMotionHead; /* derived name */

/* the four bytes GetStreamMotionData hands back while no data has arrived */
static const char streamDummyHead[] = {0, 0xFF, 0, 0}; /* derived name */

void GetStreamMotionData(char *dst, int no)
{
    int off;
    int size;
    int over;

    if (streamEntry[no].cur < 0) {
        *(StreamMotionHead *)dst = *(const StreamMotionHead *)streamDummyHead;
        /* "tried to get the stream motion before the data has arrived" */
        debug_StdPrintfDummy(
            "データがまだ来ていないのにストリームモーションの取得をしようとしました\n");
        return;
    }
    off = streamEntry[no].cur;
    size = streamEntry[no].size;
    over = off + size - 163840;
    if (over > 0) {
        int first = 163840 - off;

        memcpy(dst, ringBuf + off, first);
        memcpy(dst + first, ringBuf, over);
    } else {
        memcpy(dst, ringBuf + off, size);
    }
}

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
            if (bgMgrId != 0) {
                iosCdvdBackGroundMgrDelete(bgMgrId);
            } else {
                _deleteStreamMotionManager();
            }
            if (streamNum != 0) {
                for (i = 0; i < streamNum; i++) {
                    ClearStreamMotionEntry(streamEntry[i].obj.p);
                }
                streamNum = 0;
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

inline void ClearAllStreamMotionEntry(void)
{
    int i;

    if (streamNum == 0) {
        return;
    }
    for (i = 0; i < streamNum; i++) {
        ClearStreamMotionEntry(streamEntry[i].obj.p);
    }
    streamNum = 0;
}

inline void DeleteStreamMotionManager(void)
{
    if (bgMgrId != 0) {
        iosCdvdBackGroundMgrDelete(bgMgrId);
    } else {
        _deleteStreamMotionManager();
    }
    ClearAllStreamMotionEntry();
}

inline void StandbyStreamMotion(char *file)
{
    DeleteStreamMotionManager();
    while (bgMgrId != 0) {
        debug_StdPrintfDummy("\033[36mWait!!!\033[m\n");
        iosThreadSleep();
    }
    ringBuf = iosMallocDebug(ios_partition_sugipon, 163840, "src/streamMotionManager.c", 456);
    readBuf = iosMallocDebug(ios_partition_sugipon, 163840, "src/streamMotionManager.c", 457);
    if (ringBuf == 0 || readBuf == 0) {
        /* "could not allocate the stream buffer memory" */
        debug_StdPrintfDummy("ストリーム用のバッファメモリが確保できませんでした\n");
    }
    bgMgrId = iosCdvdBackGroundMgrAdd(file, _handler, 0, 0, 0, 0, _closeHander, 0);
    streamOwner = file;
}

inline void StopStreamMotion(void)
{
    streamState = 0;
}

inline int EntryStreamMotion(GObj *gobj)
{
    int no = streamNum;

    streamEntry[no].obj.p = gobj;

    GOBJ_SUB(gobj)->ctrl.stream = no;
    GOBJ_SUB(gobj)->ctrl.loopFlag = 0;
    GOBJ_SUB(gobj)->ctrl.posReserve = 0;
    GOBJ_SUB(gobj)->ctrl.catchBoy = 0;
    streamNum = no + 1;
    return no;
}

inline void InitStreamMotionManager(void) {}

inline int CheckReadyStreamMotion(void)
{
    unsigned int p = ringRead;
    unsigned int q = ringWrite;
    unsigned int end = p + 4096;
    int r;
    if (q < p)
        q += 163840;
    r = 1;
    if (!(q < p) && (int)q < (int)end)
        r = 0;
    return r;
}

static inline int _closeHander(void)
{
    _deleteStreamMotionManager();
    return 1;
}

static inline int _handler(CdvdBgReq *self)
{
    unsigned int wp = ringWrite;
    unsigned int rp = ringRead;
    int rest;
    int size;

    if (wp < rp) {
        rest = wp + 163840 - rp;
    } else {
        rest = wp - rp;
    }
    switch (readState) {
    default:
    case 0:
        if (rest > 81919) {
            break;
        }
        readState = 1;
    case 1:
        size = 163840 - rest;
        size = ((size - 1) / 2048) * 2048;
        iosCdvdBackGroundRead(self, readBuf, size);
        _transRingBuf(&ringWrite, ringBuf, 163840, readBuf, size);
        readState = 0;
        break;
    }
    return 0;
}
