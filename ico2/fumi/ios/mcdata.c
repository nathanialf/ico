#include "cdvd.h"
#include "mcdata.h"
#include "thread.h"
#include "mcard.h"

#ifdef VERSION_JUN26
#include "memory.h"
#include "ios.h"

struct McIconWork { /* field names derived */
    void *buf;
    int size;
}; /* derived name */
#else
struct McIconWork { /* field names derived */
    int remain;
    int size;
    void *buf;
}; /* derived name */

/* the flag the mcard thread raises when the request the caller is spinning
   on has finished */
static int mcDataDone; /* derived name */
#endif

/* Background-read callback: pulls the icon file off the disc a chunk at a
   time into a 64-byte aligned buffer and waits for the writer to drain it. */
static inline int _iosMcIconWriteIconsys(CdvdBgReq *self, struct McIconWork *p)
{
#ifdef VERSION_JUN26
    iosCdvdBackGroundRead(self, p->buf, p->size);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    char buf[51200];
#else
    char buf[51200 + 64];
    char *ptr;
#endif
    int size;
    int loop = 1;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    p->buf = buf;
#else
    ptr = (char *)(((int)buf + 63) / 64 * 64);
    p->buf = ptr;
#endif

    do {
        size = p->remain > 51200 ? 51200 : p->remain;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        iosCdvdBackGroundRead(self, buf, size);
#else
        iosCdvdBackGroundRead(self, ptr, size);
#endif
        p->size = size;
        p->remain -= size;
        if (p->remain <= 0)
            loop = 0;
        IosCdvdMgrSleep = 1;
        mcDataDone = 0;
        do {
            iosThreadSleep();
        } while (mcDataDone == 0);
        IosCdvdMgrSleep = 0;
    } while (loop);

#endif
    return 1;
}

inline int iosMcIconWriteIconsys(struct McMgr *self, const IconFile *p)
{
    struct McIconWork work;
    CdvdBgReq *hdl;
#ifdef VERSION_JUN26

    work.size = (p->size + 2047) / 2048 * 2048;
    work.buf = iosMallocDebug(ios_partition_sound, work.size, __FILE__, 115);
#else
    int total = 0;
    int size;
    int len;

    work.remain = (p->size + 2047) / 2048 * 2048;
#endif

    hdl = iosCdvdBackGroundMgrAdd(p->name, _iosMcIconWriteIconsys, &work, 0, 0, 0, 0, 0);

#ifdef VERSION_JUN26
    while (hdl->readFunc != 0) {
        iosMcMgrSync(self);
    }
    iosCdvdBackGroundMgrDelete(hdl);
    iosMcHandlerWrite(self, work.buf, p->size);
    iosFree(work.buf);
#else
    while (work.remain > 0) {
        work.size = 0;
        do {
            iosMcMgrSync(self);
        } while (work.size == 0);
        size = work.size;
        total += size;
        if (p->size < total) {
            len = size - (total - p->size);
        } else {
            len = size;
        }
        iosMcHandlerWrite(self, work.buf, len);
        mcDataDone = 1;
    }
    iosCdvdBackGroundMgrDelete(hdl);
#endif
    return 0;
}

inline int iosMcIconWriteIcon(struct McMgr *self, const IconFile *p)
{
    return iosMcIconWriteIconsys(self, p);
}
