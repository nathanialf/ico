#include "mv_defs.h"
#include "typedef.h"
#include "mv_vobuf.h"
#include "mv_disp.h"
#include <eeregs.h>
#include <libgraph.h>
#include "main.h"

inline void *setTEX0_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                       unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11,
                       unsigned int p12);

inline void *setPRIM(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                     unsigned int p8, unsigned int p9);

inline void *setUV(int *a0, int a1, int a2);
inline void *setRGBAQ(int *a0, int a1, int a2, int a3, int p4, int p5);
inline void *setXYZ2(int *a0, int a1, int a2, int a3);
inline void *setFRAME_1(int *a0, int a1, int a2, int a3, int p4);

inline void *setTEST_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                       unsigned int p8);

inline void *setSCISSOR_1(int *a0, int a1, int a2, int a3, int p4);
inline void *setXYOFFSET_1(int *a0, unsigned int a1, unsigned int a2);
inline void *setPRMODECONT(int *a0, int a1);

inline void *setPRMODE(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                       unsigned int p8);

inline void *setCLAMP_1(int *a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4,
                        unsigned int a5, unsigned int a6);

inline int *setBITBLTBUF(int *a0, long long a1, long long a2, long long a3);
inline int *setTRXPOS(int *a0, long long a1, int a2, int a3);
inline void *setTRXREG(int *a0, int a1, int a2);
inline void *setTRXDIR(int *a0, unsigned int a1);

/* the two GIF packets this file builds, one per display path */
static int mvDispPacket[80]; /* derived name */

static int mvClearPacket[80]; /* derived name */

/* The display state vblankHandler shares with the foreground code: the
   vblanks counted while displaying, the displaying flag, the image-done flag
   handler_endimage clears, the field the GS reports, and the path-sync
   result. */
static int dispVblankCount = 0; /* derived name */

static int dispRunning = 0; /* derived name */

static int dispImageDone = 0; /* derived name */

static int dispField = 0; /* derived name */

static int dispSyncBusy = 0; /* derived name */

/* the frame counter the display loop keeps */
static int mvFrameCount; /* derived name */

inline void loadImage(int a0)
{
    *D2_TADR = phys_addr(a0);
    *D2_QWC = 0;
    *D2_CHCR = 0x105;
}

typedef struct MvRect { /* field names derived */
    int x;
    int y;
    int w;
    int h;
} MvRect;

/* a textured sprite over r, sampling uv */
static inline int *setTexSprite(int *p, MvRect *r, MvRect *uv) /* derived name */
{
    p = setPRIM(p, 6, 0, 1, 0, 0, 0, 1, 0, 0);
    p = setUV(p, uv->x, uv->y);
    p = setXYZ2(p, r->x, r->y, 0);
    p = setUV(p, uv->x + uv->w, uv->y + uv->h);
    p = setXYZ2(p, r->x + r->w, r->y + r->h, 0);
    return p;
}

/* a flat sprite of colour col over r */
static inline int *setClearSprite(int *p, MvRect *r, unsigned int col) /* derived name */
{
    p = setPRIM(p, 6, 0, 0, 0, 0, 0, 1, 0, 0);
    p = setXYZ2(p, r->x, r->y, 0);
    p = setRGBAQ(p, col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF, (col >> 24) & 0xFF, 0);
    p = setXYZ2(p, r->x + r->w, r->y + r->h, 0);
    return p;
}

void dispClear(MvDispEnv *self, unsigned int col)
{
    MvRect r;
    int *p;

    r.x = 0;
    r.y = 0;
    r.w = self->width << 4;
    r.h = ((self->height + 31) / 32 * 64 + self->height * 2) << 4;

    p = setGIFtag((int *)uncached_accel_addr((int)mvClearPacket), 14, 1, 0, 0, 0, 1, 4);
    setClearSprite(p, &r, col);

    *D2_MADR = phys_addr((int)mvClearPacket);
    *D2_QWC = 5;
    *D2_CHCR = 0x101;

    sceGsSyncPath(0, 0);
}

void setDispEnv(MvDispEnv *self, int a1, int a2, int a3, int a4)
{
    int *p;
    int w = 720;
    int h = 288;

    self->fbp[0] = 0;
    self->fbp[1] = 108;
    self->width = w;
    self->height = h;
    self->imageWidth = a1;
    self->imageHeight = a2;

    sceGsSetDefDispEnv(&self->env.gs, 0, a1, a2 / 2, 0, 0);

    self->env.w.dispfbDB = (self->env.w.dispfbDB & ~0x7FF) | (a3 & 0x7FF);
    self->env.w.dispfbDB = (self->env.w.dispfbDB & 0xFFC007FF) | ((a4 & 0x7FF) << 11);
    self->env.w.dispfb = (self->env.w.dispfb & ~0x7E00) | 0x1800;

    p = setGIFtag((int *)uncached_accel_addr((int)mvDispPacket), 14, 1, 0, 0, 0, 1, 6);
    p = setPRMODECONT(p, 1);
    p = setFRAME_1(p, 0, (self->width + 63) / 64, 0, 0);
    p = setTEST_1(p, 0, 0, 0, 0, 0, 0, 0, 0);
    p = setSCISSOR_1(p, 0, self->width - 1, 0, (self->height + 31) / 32 * 128 - 1);
    p = setXYOFFSET_1(p, 0, 0);
    setCLAMP_1(p, 1, 1, 0, 0, 0, 0);
}

void setImageSize(MvDispEnv *self, int a1, int a2, int a3, int a4)
{
    int lim = self->imageHeight;
    if (a2 <= lim) {
        a2 = lim;
    }
    setDispEnv(self, a1, a2, a3, a4);
}

void sendDispEnv(MvDispEnv *self)
{
    sceGsPutDispEnv(&self->env.gs);
    *D2_MADR = phys_addr((int)mvDispPacket);
    *D2_QWC = 7;
    *D2_CHCR = 0x101;
    sceGsSyncPath(0, 0);
}

void dispCreate(MvDispEnv *self, int a1, int a2, int a3, int a4)
{
    /* the five display-state words are read and written by vblankHandler on the
       vblank interrupt, so they are reset through volatile */
    *(volatile int *)&dispRunning = 0;
    *(volatile int *)&dispVblankCount = 0;
    *(volatile int *)&dispImageDone = 0;
    *(volatile int *)&dispField = 0;
    *(volatile int *)&dispSyncBusy = 0;
    sceGsSyncV(0);
    sceGsResetGraph(0, 1, systemStatus[0] != 0 ? 3 : 2, 1);
    sceGsResetPath();
    setDispEnv(self, a1, a2, a3, a4);
    sendDispEnv(self);
}

inline void dispDelete(MvDispEnv *self) {}

void dispSetTags(MvDispEnv *self, int src, int a2, int a3, int p4, int p5, int p6, int p7, int p8,
                 int p9)
{
    MvRect r;
    MvRect uv;
    void *p = (void *)uncached_accel_addr(src);
    int nx;
    int ny;
    int bw;
    int bh;
    int dbp;
    int i;
    int j;

    nx = p8 >> 4;
    ny = p9 >> 4;

    r.x = p4 << 4;
    r.y = p5 << 4;
    r.w = p6 << 4;
    r.h = p7 << 4;
    uv.x = 8;
    uv.y = 8;
    uv.w = p8 << 4;
    uv.h = p9 << 4;

    if (a3 == 0) {
        bh = (self->height + 31) / 32;
        bw = (self->width + 63) / 64;
        dbp = bh * (bw << 6);
        p = setDMAscTag(p, 0, 0, 0, 1, 0, 3);
        p = setGIFtag(p, 14, 1, 0, 0, 0, 0, 2);
        p = setBITBLTBUF(p, dbp, bw, 0);
        p = setTRXREG(p, 16, 16);
        for (i = 0; i < nx; i++) {
            for (j = 0; j < ny; j++) {
                p = setDMAscTag(p, 0, 0, 0, 1, 0, 4);
                p = setGIFtag(p, 14, 1, 0, 0, 0, 0, 2);
                p = setTRXPOS(p, 0, i << 4, j << 4);
                p = setTRXDIR(p, 0);
                p = setGIFtag(p, 0, 0, 2, 0, 0, 0, 64);
                p = setDMAscTag(p, 0, phys_addr(a2), 0, 3, 0, 64);
                a2 += 1024;
            }
        }
    } else {
        uv.y = 24;
        r.y = (p5 + (self->height + 31) / 32 * 32) << 4;
    }

    p = setDMAscTag(p, 0, 0, 0, 7, 0, 16);
    p = setGIFtag(p, 14, 1, 0, 0, 0, 1, 15);
    p = setTEXFLUSH(p);
    p = setTEX1_1(p, 0, 0, 1, 1, 0, 0, 0);
    p = setTEX0_1(p, (self->height + 31) / 32 * ((self->width + 63) / 64 << 6),
                  (self->width + 63) / 64, 0, 10, 10, 0, 1, 0, 0, 0, 0, 0);
    setTexSprite(p, &r, &uv);
}

void dispSwitch(MvDispEnv *a0, int flag)
{
    int src;
    if (flag != 0) {
        src = a0->fbp[1];
    } else {
        src = a0->fbp[0];
    }
    a0->env.w.dispfb = (a0->env.w.dispfb & ~0x1FF) | (src & 0x1FF);
    sceGsPutDispEnv(&a0->env.gs);
}

int vblankHandler(int cause)
{
    VoTag *tag;
    int st;

    *(volatile int *)&dispField = (int)((*GS_CSR >> 13) & 1);
    if (*(volatile int *)&dispRunning != 0) {
        *(volatile int *)&dispVblankCount = *(volatile int *)&dispVblankCount + 1;
        /* the display-state words are shared with the foreground code, which
           reads them between vblanks */
        *(volatile int *)&dispSyncBusy = sceGsSyncPath(1, 0);
        if (*(volatile int *)&dispSyncBusy == 0) {
            tag = voBufGetTag(&voBuf);
            if (tag == 0) {
                mvFrameCount++;
                SYNC();
                EI();
                return 0;
            }
            if (*(volatile int *)&dispField == 0 && tag->status == 2) {
                dispSwitch(&display, 0);
                loadImage((int)tag->packet[1]);
                tag->status = 1;
            } else if (*(volatile int *)&dispField != 0 && (st = tag->status) == 1) {
                dispSwitch(&display, 1);
                loadImage((int)tag->packet[0]);
                tag->status = 0;
                *(volatile int *)&dispImageDone = st;
            }
        }
    }
    SYNC();
    EI();
    return 0;
}

inline int handler_endimage(int channel)
{
    if (dispImageDone != 0) {
        voBufDecCount(&voBuf);
        dispImageDone = 0;
    }
    SYNC();
    EI();
    return 0;
}

inline void startDisplay(int a0)
{
    while (sceGsSyncV(0) == a0)
        ;
    *(volatile int *)&dispRunning = 1;
    mvFrameCount = 0;
    *(volatile int *)&dispVblankCount = 0;
}

inline void endDisplay(void)
{
    dispRunning = 0;
    mvFrameCount = 0;
}

inline void *setDMAscTag(void *a0, int a1, unsigned int a2, int a3, int p4, int p5, int p6)
{
    unsigned long long g1 = ((unsigned long long)a1 << 63) | (unsigned int)p6;
    unsigned long long g2 =
        ((unsigned long long)(unsigned int)p4 << 28) | ((unsigned long long)(unsigned int)a3 << 31);
    unsigned long long g3 = ((unsigned long long)(a2 & 0xFFFFFFF0) << 32) |
                            ((unsigned long long)(unsigned int)p5 << 26);
    *(long long *)a0 = g1 | g2 | g3;
    return (char *)a0 + 0x10;
}

inline void *setGIFtag(int *a0, long long a1, int a2, int a3, int p4, int p5, int p6, int p7)
{
    int hi = (p5 << 14) | (a2 << 28);
    int lo = (a3 << 26) | (p4 << 15);
    a0[0] = (p6 << 15) | p7;
    a0[1] = hi | lo;
    a0[2] = (int)(a1 & 0xFFFFFFFFLL);
    a0[3] = (int)(a1 >> 32);
    return (char *)a0 + 0x10;
}

inline void *setTEXFLUSH(int *a0)
{
    a0[0] = 0;
    a0[2] = 63;
    a0[1] = 0;
    a0[3] = 0;
    return a0 + 4;
}

inline void *setGIFad(int *a0, int a1, long long a2)
{
    a0[0] = (int)(a2 & 0xFFFFFFFFLL);
    a0[1] = (int)(a2 >> 32);
    a0[2] = a1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setTEX1_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 2) |
                  ((unsigned long long)(unsigned int)a3 << 5) |
                  ((unsigned long long)(unsigned int)p4 << 6) |
                  ((unsigned long long)(unsigned int)p5 << 9) |
                  ((unsigned long long)(unsigned int)p6 << 19) | ((long long)p7 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x14;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setTEX0_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                       unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11,
                       unsigned int p12)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 14) |
                  ((unsigned long long)(unsigned int)a3 << 20) |
                  ((unsigned long long)(unsigned int)p4 << 26) |
                  ((unsigned long long)(unsigned int)p5 << 30) | ((long long)p6 << 34) |
                  ((long long)p7 << 35) | ((unsigned long long)p8 << 37) |
                  ((unsigned long long)p9 << 51) | ((unsigned long long)p10 << 55) |
                  ((unsigned long long)p11 << 56) | ((unsigned long long)p12 << 61);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 6;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setPRIM(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                     unsigned int p8, unsigned int p9)
{
    long long t =
        (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 3) |
        ((unsigned long long)(unsigned int)a3 << 4) | ((unsigned long long)(unsigned int)p4 << 5) |
        ((unsigned long long)(unsigned int)p5 << 6) | ((unsigned long long)(unsigned int)p6 << 7) |
        ((unsigned long long)(unsigned int)p7 << 8) | ((unsigned long long)p8 << 9) |
        ((unsigned long long)p9 << 10);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setUV(int *a0, int a1, int a2)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 3;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setRGBAQ(int *a0, int a1, int a2, int a3, int p4, int p5)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 8) |
                  ((unsigned long long)(unsigned int)a3 << 16) |
                  ((unsigned long long)(unsigned int)p4 << 24) | ((long long)p5 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setXYZ2(int *a0, int a1, int a2, int a3)
{
    long long t =
        (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16) | ((long long)a3 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 5;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setFRAME_1(int *a0, int a1, int a2, int a3, int p4)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16) |
                  ((unsigned long long)(unsigned int)a3 << 24) | ((long long)p4 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x4C;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setTEST_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                       unsigned int p8)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 1) |
                  ((unsigned long long)(unsigned int)a3 << 4) |
                  ((unsigned long long)(unsigned int)p4 << 12) |
                  ((unsigned long long)(unsigned int)p5 << 14) |
                  ((unsigned long long)(unsigned int)p6 << 15) |
                  ((unsigned long long)(unsigned int)p7 << 16) | ((unsigned long long)p8 << 17);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x47;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setSCISSOR_1(int *a0, int a1, int a2, int a3, int p4)
{
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16) |
                  ((long long)a3 << 32) | ((long long)p4 << 48);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x40;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setXYOFFSET_1(int *a0, unsigned int a1, unsigned int a2)
{
    long long t = (unsigned int)a1 | ((unsigned long long)a2 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x18;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setPRMODECONT(int *a0, int a1)
{
    long long t = (unsigned int)a1;
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x1A;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setPRMODE(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                       unsigned int p8)
{
    long long t =
        ((unsigned long long)(unsigned int)a1 << 3) | ((unsigned long long)(unsigned int)a2 << 4) |
        ((unsigned long long)(unsigned int)a3 << 5) | ((unsigned long long)(unsigned int)p4 << 6) |
        ((unsigned long long)(unsigned int)p5 << 7) | ((unsigned long long)(unsigned int)p6 << 8) |
        ((unsigned long long)(unsigned int)p7 << 9) | ((unsigned long long)p8 << 10);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x1B;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setCLAMP_1(int *a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4,
                        unsigned int a5, unsigned int a6)
{
    long long v = a1 | ((long long)a2 << 2) | ((long long)a3 << 4) | ((long long)a4 << 14) |
                  ((long long)a5 << 24) | ((long long)a6 << 34);
    a0[0] = v & 0xffffffff;
    a0[2] = 8;
    a0[1] = (int)(v >> 32);
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline int *setBITBLTBUF(int *a0, long long a1, long long a2, long long a3)
{
    long long t = (a3 << 56) | (a2 << 48) | (a1 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x50;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}

inline int *setTRXPOS(int *a0, long long a1, int a2, int a3)
{
    long long t = (a1 << (27 + 32)) | ((long long)a3 << 48) | ((long long)a2 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x51;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}

inline void *setTRXREG(int *a0, int a1, int a2)
{
    unsigned long long v = (unsigned int)a1;
    unsigned long long packed = ((unsigned long long)a2 << 32) | v;
    a0[0] = (int)v;
    a0[1] = (int)(packed >> 32);
    a0[2] = 0x52;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

inline void *setTRXDIR(int *a0, unsigned int a1)
{
    unsigned long long v = (unsigned int)a1;
    a0[2] = 83;
    a0[0] = (int)v;
    a0[1] = (int)(v >> 32);
    a0[3] = 0;
    return a0 + 4;
}
