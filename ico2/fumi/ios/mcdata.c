#include "cdvd.h"
#include "mcdata.h"
#include "thread.h"
#include "mcard.h"
#include "memory.h"
#include "ios.h"
#include "include_asm.h"

struct McIconWork { /* field names derived */
    void *buf;
    int size;
}; /* derived name */

/* This build has no request-done flag here (no function of the demo
   addresses one). */

INCLUDE_ASM(D_002695F8);

/* Background-read callback: reads the whole icon file, rounded up to the
   disc's 2048-byte sectors, into the buffer the writer allocated. */
static inline int _iosMcIconWriteIconsys(CdvdBgReq *self, struct McIconWork *p)
{
    iosCdvdBackGroundRead(self, p->buf, p->size);
    return 1;
}

inline int iosMcIconWriteIconsys(struct McMgr *self, const IconFile *p)
{
    struct McIconWork work;
    CdvdBgReq *hdl;

    work.size = (p->size + 2047) / 2048 * 2048;
    work.buf = iosMallocDebug(ios_partition_sound, work.size, __FILE__, 115);

    hdl = iosCdvdBackGroundMgrAdd(p->name, _iosMcIconWriteIconsys, &work, 0, 0, 0, 0, 0);

    while (hdl->readFunc != 0) {
        iosMcMgrSync(self);
    }
    iosCdvdBackGroundMgrDelete(hdl);
    iosMcHandlerWrite(self, work.buf, p->size);
    iosFree(work.buf);
    return 0;
}

inline int iosMcIconWriteIcon(struct McMgr *self, const IconFile *p)
{
    return iosMcIconWriteIconsys(self, p);
}
