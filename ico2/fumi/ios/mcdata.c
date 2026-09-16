#include "common.h"

int iosMcIconWriteIconsys(int self, int *p);
int iosMcIconWriteIcon(int self, int *p);

struct McIconWork {
    int remain;
    int size;
    void *buf;
};

/* kept local: this TU's uses of iosCdvdBackGroundRead do not fit the prototype in cdvd.h */
extern int iosCdvdBackGroundRead(int self, void *buf, int size);
/* kept local: this TU's uses of iosThreadSleep do not fit the prototype in thread.h */
extern void iosThreadSleep(void);
extern int D_0063A368;
extern int D_0063C18C;
/* kept local: this TU's uses of iosCdvdBackGroundMgrAdd do not fit the prototype in cdvd.h */
extern int iosCdvdBackGroundMgrAdd();
/* kept local: this TU's uses of iosCdvdBackGroundMgrDelete do not fit the prototype in cdvd.h */
extern void iosCdvdBackGroundMgrDelete(int self);
/* kept local: this TU's uses of iosMcMgrSync do not fit the prototype in mcard.h */
extern void iosMcMgrSync(int self);
/* kept local: this TU's uses of iosMcHandlerWrite do not fit the prototype in mcard.h */
extern void iosMcHandlerWrite(int self, void *buf, int size);

/* Background-read callback: pulls the icon file off the disc a chunk at a
   time into a 64-byte aligned buffer and waits for the writer to drain it. */
static inline int _iosMcIconWriteIconsys(int self, struct McIconWork *p)
{
    char buf[0xC800 + 0x40];
    char *ptr;
    int size;
    int loop = 1;

    ptr = (char *)(((int)buf + 63) / 64 * 64);
    p->buf = ptr;

    do {
        size = p->remain > 0xC800 ? 0xC800 : p->remain;
        iosCdvdBackGroundRead(self, ptr, size);
        p->size = size;
        p->remain -= size;
        if (p->remain <= 0)
            loop = 0;
        D_0063A368 = 1;
        D_0063C18C = 0;
        do {
            iosThreadSleep();
        } while (D_0063C18C == 0);
        D_0063A368 = 0;
    } while (loop);

    return 1;
}

inline int iosMcIconWriteIconsys(int self, int *p)
{
    struct McIconWork work;
    int hdl;
    int total = 0;
    int size;
    int len;

    work.remain = (p[8] + 0x7FF) / 0x800 * 0x800;

    hdl = iosCdvdBackGroundMgrAdd(p, _iosMcIconWriteIconsys, &work, 0, 0, 0, 0, 0);

    while (work.remain > 0) {
        work.size = 0;
        do {
            iosMcMgrSync(self);
        } while (work.size == 0);
        size = work.size;
        total += size;
        if (p[8] < total) {
            len = size - (total - p[8]);
        } else {
            len = size;
        }
        iosMcHandlerWrite(self, work.buf, len);
        D_0063C18C = 1;
    }
    iosCdvdBackGroundMgrDelete(hdl);
    return 0;
}

inline int iosMcIconWriteIcon(int self, int *p)
{
    return iosMcIconWriteIconsys(self, p);
}
