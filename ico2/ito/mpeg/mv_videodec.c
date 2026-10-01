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

/* kept local: libmpeg.h declares sceMpegDelete (void), and this TU hands it
   the decoder; the other libmpeg calls follow libmpeg.h */
extern int sceMpegCreate(void *self, void *buf, int size);
extern int sceMpegAddCallback(void *a0, int a1, int a2, int a3);
extern int sceMpegAddStrCallback();
extern int sceMpegDelete();
extern int sceMpegGetPicture(int *a0, unsigned int a1, int a2);
extern int sceMpegIsEnd(int **a0);
extern int sceMpegIsRefBuffEmpty(void *a0);
extern void sceMpegReset(int *a0);

#include <string.h>

/* the MPEG library's callbacks; their out-of-line copies are deferred to the
   end of the file */
inline int mpegError(int a0, MvCbErr *cb)
{
    debug_StdPrintfDummy("%s\n", cb->message);
    return 1;
}

inline int mpegNodata(int a0, int a1, VideoDec *dec)
{
    switchThread();
    viBufAddDMA(&dec->vibuf);
    return 1;
}

inline int mpegStopDMA(int a0_unused, int a1_unused, VideoDec *dec)
{
    viBufStopDMA(&dec->vibuf);
    return 1;
}

inline int mpegRestartDMA(int a0_unused, int a1_unused, VideoDec *dec)
{
    viBufRestartDMA(&dec->vibuf);
    return 1;
}

inline int mpegTS(int a0_unused, MvCbTs *cb, VideoDec *dec)
{
    ViTs ts;
    viBufGetTs(&dec->vibuf, &ts);
    cb->pts = ts.pts;
    cb->dts = ts.dts;
    return 1;
}

void free_buf(VideoDec *self)
{
    Free(self->buf);
}

int videoDecCreate(VideoDec *self)
{
    int p;

    p = alloc_zeroed(0x1C8200, 0x40);
    self->buf = p;
    if (p == 0) {
        return -1;
    }
    sceMpegCreate(self, (void *)p, 0x1C8200);
    sceMpegAddCallback(self, 0, (int)mpegError, 0);
    sceMpegAddCallback(self, 1, (int)mpegNodata, (int)self);
    sceMpegAddCallback(self, 2, (int)mpegStopDMA, (int)self);
    sceMpegAddCallback(self, 3, (int)mpegRestartDMA, (int)self);
    sceMpegAddCallback(self, 5, (int)mpegTS, (int)self);
    self->state = 0;
    return viBufCreate(&self->vibuf) == 0 ? 0 : -1;
}

void videoDecBeginPut(VideoDec *self, void **addr1, int *size1, void **addr2, int *size2)
{
    viBufBeginPut(&self->vibuf, addr1, size1, addr2, size2);
}

void videoDecEndPut(VideoDec *self, int n)
{
    viBufEndPut(&self->vibuf, n);
}

typedef struct Code4 {
    char b[4];
} Code4;

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

int videoCallback(int a0, MvCbStr *pkt, MvCbArg *arg)
{
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

int decBitStrm0(VideoDec *dec, MvDispEnv *disp, VoBuf *vo)
{
    int ret = 1;
    VoData *p;
    int w;
    int h;
    int ox;
    int oy;
    int hh;
    int i;
    int j;

    while (!sceMpegIsEnd((int **)dec)) {
        /* videoDecGetState is defined below this function in ROM order, so its
           one-line body is written out here (INTERIM: the dev's file had it above) */
        if (dec->state == 1) {
            ret = -1;
            debug_StdPrintfDummy("decode thread: aborted\n");
            break;
        }
        while ((p = voBufGetData(vo)) == 0) {
            switchThread();
        }
        if (sceMpegGetPicture((int *)dec, (unsigned int)p, 1620) < 0) {
            ErrMessage("sceMpegGetPicture() decode error");
            ret = -1;
            break;
        }
        if (dec->frameCount == 0) {
            debug_StdPrintfDummy("movie %d x %d\n", dec->width, dec->height);
            w = dec->width;
            ox = (disp->imageWidth - w) >> 1;
            h = dec->height;
            oy = (disp->imageHeight - h) >> 2;
            hh = h >> 1;
            for (i = 0; i < vo->max; i++) {
                for (j = 0; j < 2; j++) {
                    dispSetTags(disp, (int)vo->tag[i].packet[j], (int)&vo->data[i], j, ox, oy, w,
                                hh, w, h);
                }
            }
        }
        voBufIncCount(vo);
        switchThread();
    }
    sceMpegReset((int *)dec);
    return ret;
}

void Free(int a0)
{
    iosFree(phys_addr(a0));
}

int videoDecDelete(VideoDec *self)
{
    viBufDelete(&self->vibuf);
    sceMpegDelete(self);
    free_buf(self);
    return 1;
}

int videoDecSetStream(VideoDec *self, int type, int ch, void *fn, void *data)
{
    sceMpegAddStrCallback(self, type, ch, fn, data);
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
        ret = sceMpegIsRefBuffEmpty(self) != 0;
    }
    return ret;
}

void videoDecMain(MvThreadArg *arg)
{
    viBufReset(&arg->dec->vibuf);
    voBufReset(arg->vo);
    decBitStrm0(arg->dec, arg->disp, arg->vo);
    arg->dec->state = 3;
}
