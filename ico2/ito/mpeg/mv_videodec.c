#include "mv_defs.h"
#include "mv_videodec.h"
#include "debug.h"
#include "memory.h"
#include "mv_disp.h"
#include "mv_sub.h"
#include "mv_vibuf.h"
#include "mv_vobuf.h"
#include "typedef.h"
#include "ios.h"
#include "mv_main.h"
#include <libmpeg.h>
#include <string.h>
#include "include_asm.h"

static void Free(int addr);

INCLUDE_ASM_LIT(mpegError);

/* the MPEG library's callbacks, which videoDecCreate registers */
static void free_buf(VideoDec *self)
{
    Free(self->buf);
}

INCLUDE_ASM(videoDecCreate);

static void videoDecBeginPut(VideoDec *self, void **addr1, int *size1, void **addr2, int *size2)
{
    viBufBeginPut(&self->vibuf, addr1, size1, addr2, size2);
}

static void videoDecEndPut(VideoDec *self, int n)
{
    viBufEndPut(&self->vibuf, n);
}

typedef struct Code4 { /* field names derived */
    char b[4];
} Code4; /* derived name */

int videoDecFlush(VideoDec *self)
{
    Code4 code = {{0x00, 0x00, 0x01, 0xB7}}; /* the MPEG sequence end code */
    void *p0;
    int n0;
    void *p1;
    int n1;

    videoDecBeginPut(self, &p0, &n0, &p1, &n1);
    if (n0 + n1 < 4) {
        return 0;
    }
    videoDecEndPut(self, copy2area((char *)uncached_accel_addr((int)p0), n0,
                                   (char *)uncached_accel_addr((int)p1), n1, code.b, 4, 0, 0));
    viBufFlush(&self->vibuf);
    if (self->state == 0) {
        self->state = 2;
    }
    return 1;
}

int videoCallback(sceMpeg *mp, void *cbdata, void *anyData)
{
    MvCbStr *pkt = cbdata;
    MvCbArg *arg = anyData;
    ViTs ts;
    void *p0;
    int n0;
    void *p1;
    int n1;
    ReadBuf *b = arg->rb;
    VideoDec *dec = arg->dec;
    int rd = (int)pkt->data;
    int base = (int)b->data;
    unsigned int len = pkt->len;
    unsigned int first = base + b->size - rd;
    unsigned int rest;
    int n;

    if (len < first) {
        first = len;
    }
    rest = len - first;
    videoDecBeginPut(dec, &p0, &n0, &p1, &n1);
    n = copy2area((char *)uncached_accel_addr((int)p0), n0, (char *)uncached_accel_addr((int)p1),
                  n1, (char *)rd, first, (char *)base, rest);
    if (n > 0) {
        ts.pts = pkt->pts;
        ts.dts = pkt->dts;
        ts.pos = (int)p0 - (int)dec->vibuf.data;
        ts.len = n;
        if (viBufPutTs(&dec->vibuf, &ts) == 0) {
            ErrMessage("pts buffer overflow\n");
        }
    }
    videoDecEndPut(dec, n);
    return 0 < n;
}

static int decBitStrm0(VideoDec *dec, MvDispEnv *disp, VoBuf *vo);

INCLUDE_ASM(decBitStrm0);

static void Free(int addr)
{
    /* the buffers are kept as addresses (alloc_zeroed), some at their
       uncached-accelerated alias; the heap takes the block back with the
       segment bits off */
    iosFree((void *)phys_addr(addr));
}

int videoDecDelete(VideoDec *self)
{
    viBufDelete(&self->vibuf);
    sceMpegDelete(&self->mpeg);
    free_buf(self);
    return 1;
}

int videoDecSetStream(VideoDec *self, int type, int ch, sceMpegCallback fn, void *data)
{
    sceMpegAddStrCallback(&self->mpeg, type, ch, fn, data);
    return 1;
}

void videoDecAbort(VideoDec *self)
{
    self->state = 1;
}

int videoDecGetState(VideoDec *self)
{
    return self->state;
}

int videoDecIsFlushed(VideoDec *self)
{
    int ret = 0;
    if (viBufCount(&self->vibuf) == 0) {
        ret = sceMpegIsRefBuffEmpty(&self->mpeg) != 0;
    }
    return ret;
}

void videoDecMain(void *thArg)
{
    MvThreadArg *arg = thArg;

    viBufReset(&arg->dec->vibuf);
    voBufReset(arg->vo);
    decBitStrm0(arg->dec, arg->disp, arg->vo);
    arg->dec->state = 3;
}

INCLUDE_ASM(mpegError);

INCLUDE_ASM(mpegNodata);

INCLUDE_ASM(mpegStopDMA);

INCLUDE_ASM(mpegRestartDMA);

INCLUDE_ASM(mpegTS);
