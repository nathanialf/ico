#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ios/mcdata", iosMcIconWriteIconsys);
INCLUDE_ASM("asm/nonmatchings/ios/mcdata", iosMcIconWriteIcon);
struct McIconWork {
    int   remain;
    int   size;
    void *buf;
};
extern int iosCdvdBackGroundRead(int self, void *buf, int size);
extern void iosThreadSleep(void);
extern int D_0063A368;
extern int D_0063C18C;

static int _iosMcIconWriteIconsys(int self, struct McIconWork *p)
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
        if (p->remain <= 0) loop = 0;
        D_0063A368 = 1;
        D_0063C18C = 0;
        do {
            iosThreadSleep();
        } while (D_0063C18C == 0);
        D_0063A368 = 0;
    } while (loop);

    return 1;
}
