#include "common.h"
#include "mv_defs.h"
#include "r5900.h"

/* prototypes: their order is the inline tail's emission order */
void dispDelete(void);
void loadImage(int a0);
int handler_endimage(void);
void startDisplay(int a0);
void endDisplay(void);
void *setDMAscTag(void *a0, int a1, unsigned int a2, int a3, int p4, int p5, int p6);
void *setGIFtag(int *a0, long long a1, int a2, int a3, int p4, int p5, int p6, int p7);
void *setGIFad(int *a0, int a1, long long a2);
char *setTEXFLUSH(char *p);
void *setTEX1_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7);

void *setTEX0_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8,
                unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12);

void *setPRIM(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8,
              unsigned int p9);

void *setUV(int *a0, int a1, int a2);
void *setRGBAQ(int *a0, int a1, int a2, int a3, int p4, int p5);
void *setXYZ2(int *a0, int a1, int a2, int a3);
void *setFRAME_1(int *a0, int a1, int a2, int a3, int p4);
void *setTEST_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8);
void *setSCISSOR_1(int *a0, int a1, int a2, int a3, int p4);
void *setXYOFFSET_1(int *a0, unsigned int a1, unsigned int a2);
void *setPRMODECONT(int *a0, int a1);
void *setPRMODE(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8);

void *setCLAMP_1(int *a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4,
                 unsigned int a5, unsigned int a6);

int *setBITBLTBUF(int *a0, long long a1, long long a2, long long a3);
int *setTRXPOS(int *a0, long long a1, int a2, int a3);
void *setTRXREG(int *a0, int a1, int a2);
void *setTRXDIR(char *a0, unsigned int a1);
extern int D_0072A040[];
extern void sceGsPutDispEnv__pn(void *a0) __asm__("sceGsPutDispEnv");
extern int sceGsPutDispEnv();
extern char voBuf[];
extern int D_0063C0BC;
extern void voBufDecCount(int *p);
extern int D_0063C0B4;
extern int D_0063C0B8;
extern int D_0063C5C4;
extern int sceGsSyncV(int a0);

inline void loadImage(int a0)
{
    *(volatile unsigned int *)0x1000A030 = phys_addr(a0);
    *(volatile unsigned int *)0x1000A020 = 0;
    *(volatile unsigned int *)0x1000A000 = 0x105;
}

extern int D_0072A180[];
extern int sceGsSyncPath(int a0, int a1);

typedef struct MvRect {
    int x;
    int y;
    int w;
    int h;
} MvRect;

/* file-static: ROM carries no out-of-line copy, the listing inlines its body
   (mv_disp.c:29-44) into dispSetTags */
static inline int *setTexSprite(int *p, MvRect *r, MvRect *uv)
{
    p = setPRIM(p, 6, 0, 1, 0, 0, 0, 1, 0, 0);
    p = setUV(p, uv->x, uv->y);
    p = setXYZ2(p, r->x, r->y, 0);
    p = setUV(p, uv->x + uv->w, uv->y + uv->h);
    p = setXYZ2(p, r->x + r->w, r->y + r->h, 0);
    return p;
}

/* file-static: ROM carries no out-of-line copy, the listing inlines its body
   (mv_disp.c:54-70) into dispClear */
static inline int *setClearSprite(int *p, MvRect *r, unsigned int col)
{
    p = setPRIM(p, 6, 0, 0, 0, 0, 0, 1, 0, 0);
    p = setXYZ2(p, r->x, r->y, 0);
    p = setRGBAQ(p, col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF, (col >> 24) & 0xFF, 0);
    p = setXYZ2(p, r->x + r->w, r->y + r->h, 0);
    return p;
}

void dispClear(int *self, unsigned int col)
{
    MvRect r;
    int *p;

    r.x = 0;
    r.y = 0;
    r.w = self[0x30 / 4] << 4;
    r.h = ((self[0x34 / 4] + 31) / 32 * 64 + self[0x34 / 4] * 2) << 4;

    p = setGIFtag((int *)uncached_accel_addr((int)D_0072A180), 14, 1, 0, 0, 0, 1, 4);
    setClearSprite(p, &r, col);

    *(volatile unsigned int *)0x1000A010 = phys_addr((int)D_0072A180);
    *(volatile unsigned int *)0x1000A020 = 5;
    *(volatile unsigned int *)0x1000A000 = 0x101;

    sceGsSyncPath(0, 0);
}

extern void sceGsSetDefDispEnv(int *env, int psm, short w, short h, short dx, short dy);

void setDispEnv(int *self, int a1, int a2, int a3, int a4)
{
    int *p;
    int w = 720;
    int h = 288;

    self[0x28 / 4] = 0;
    self[0x2C / 4] = 0x6C;
    self[0x30 / 4] = w;
    self[0x34 / 4] = h;
    self[0x38 / 4] = a1;
    self[0x3C / 4] = a2;

    sceGsSetDefDispEnv(self, 0, a1, a2 / 2, 0, 0);

    self[0x14 / 4] = (self[0x14 / 4] & ~0x7FF) | (a3 & 0x7FF);
    self[0x14 / 4] = (self[0x14 / 4] & 0xFFC007FF) | ((a4 & 0x7FF) << 11);
    self[0x10 / 4] = (self[0x10 / 4] & ~0x7E00) | 0x1800;

    p = setGIFtag((int *)uncached_accel_addr((int)D_0072A040), 14, 1, 0, 0, 0, 1, 6);
    p = setPRMODECONT(p, 1);
    p = setFRAME_1(p, 0, (self[0x30 / 4] + 63) / 64, 0, 0);
    p = setTEST_1(p, 0, 0, 0, 0, 0, 0, 0, 0);
    p = setSCISSOR_1(p, 0, self[0x30 / 4] - 1, 0, (self[0x34 / 4] + 31) / 32 * 128 - 1);
    p = setXYOFFSET_1(p, 0, 0);
    setCLAMP_1(p, 1, 1, 0, 0, 0, 0);
}

void setImageSize(int *self, int a1, int a2, int a3, int a4)
{
    int lim = self[0x3C / 4];
    if (a2 <= lim) {
        a2 = lim;
    }
    setDispEnv(self, a1, a2, a3, a4);
}

void sendDispEnv(void *a0)
{
    sceGsPutDispEnv__pn(a0);
    a0 = (void *)phys_addr((int)D_0072A040);
    *(volatile unsigned int *)0x1000A010 = (unsigned int)a0;
    *(volatile unsigned int *)0x1000A020 = 7;
    *(volatile unsigned int *)0x1000A000 = 0x101;
    sceGsSyncPath(0, 0);
}

extern int D_0063C0C0;
extern int D_0063C0C4;
extern int D_0028F4C0[];
extern void sceGsResetGraph(int a0, int a1, int a2, int a3);
extern void sceGsResetPath(void);

void dispCreate(int *self, int a1, int a2, int a3, int a4)
{
    /* the five display-state words are read and written by vblankHandler on the
       vblank interrupt, so the resets are volatile here exactly as they are at
       the two sites further down this file */
    *(volatile int *)&D_0063C0B8 = 0;
    *(volatile int *)&D_0063C0B4 = 0;
    *(volatile int *)&D_0063C0BC = 0;
    *(volatile int *)&D_0063C0C0 = 0;
    *(volatile int *)&D_0063C0C4 = 0;
    sceGsSyncV(0);
    sceGsResetGraph(0, 1, D_0028F4C0[0] != 0 ? 3 : 2, 1);
    sceGsResetPath();
    setDispEnv(self, a1, a2, a3, a4);
    sendDispEnv(self);
}

inline void dispDelete(void) {}

void dispSetTags(int *self, int src, int a2, int a3, int p4, int p5, int p6, int p7, int p8, int p9)
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
        bh = (self[0x34 / 4] + 31) / 32;
        bw = (self[0x30 / 4] + 63) / 64;
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
        r.y = (p5 + (self[0x34 / 4] + 31) / 32 * 32) << 4;
    }

    p = setDMAscTag(p, 0, 0, 0, 7, 0, 16);
    p = setGIFtag(p, 14, 1, 0, 0, 0, 1, 15);
    p = setTEXFLUSH(p);
    p = setTEX1_1(p, 0, 0, 1, 1, 0, 0, 0);
    p = setTEX0_1(p, (self[0x34 / 4] + 31) / 32 * ((self[0x30 / 4] + 63) / 64 << 6),
                  (self[0x30 / 4] + 63) / 64, 0, 10, 10, 0, 1, 0, 0, 0, 0, 0);
    setTexSprite(p, &r, &uv);
}

void dispSwitch(int *a0, int flag)
{
    int src;
    int new_var;
    new_var = flag;
    if (new_var != 0) {
        src = a0[0x2C / 4];
    } else {
        src = a0[0x28 / 4];
    }
    {
        int cur = a0[0x10 / 4];
        cur = cur & (~0x1FF);
        cur = cur | (src & 0x1FF);
        a0[0x10 / 4] = cur;
    }
    return sceGsPutDispEnv(a0);
}

extern int D_002A7978[];
extern int D_0063C5C4;
extern int *voBufGetTag(char *vo);

int vblankHandler(void)
{
    int *tag;
    int st;

    *(volatile int *)&D_0063C0C0 = (int)((*(volatile unsigned long long *)0x12001000 >> 13) & 1);
    if (*(volatile int *)&D_0063C0B8 != 0) {
        *(volatile int *)&D_0063C0B4 = *(volatile int *)&D_0063C0B4 + 1;
        /* the display-state words are read back by this handler and by the
           foreground code between vblanks, the file's existing idiom */
        *(volatile int *)&D_0063C0C4 = sceGsSyncPath(1, 0);
        if (*(volatile int *)&D_0063C0C4 == 0) {
            tag = voBufGetTag(voBuf);
            if (tag == 0) {
                D_0063C5C4++;
                SYNC();
                EI();
                return 0;
            }
            if (*(volatile int *)&D_0063C0C0 == 0 && tag[0] == 2) {
                dispSwitch(D_002A7978, 0);
                loadImage((int)tag + 0x26740);
                tag[0] = 1;
            } else if (*(volatile int *)&D_0063C0C0 != 0 && (st = tag[0]) == 1) {
                dispSwitch(D_002A7978, 1);
                loadImage((int)tag + 0x40);
                tag[0] = 0;
                *(volatile int *)&D_0063C0BC = st;
            }
        }
    }
    SYNC();
    EI();
    return 0;
}

inline int handler_endimage(void)
{
    if (D_0063C0BC != 0) {
        voBufDecCount(voBuf);
        D_0063C0BC = 0;
    }
    SYNC();
    EI();
    return 0;
}

inline void startDisplay(int a0)
{
    while (sceGsSyncV(0) == a0)
        ;
    *(volatile int *)&D_0063C0B8 = 1;
    D_0063C5C4 = 0;
    *(volatile int *)&D_0063C0B4 = 0;
}

inline void endDisplay(void)
{
    D_0063C0B8 = 0;
    D_0063C5C4 = 0;
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

inline char *setTEXFLUSH(char *p)
{
    *(int *)(p + 0) = 0;
    *(int *)(p + 8) = 0x3F;
    *(int *)(p + 4) = 0;
    *(int *)(p + 0xC) = 0;
    return p + 0x10;
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
    unsigned long long v = (unsigned int)a1 | ((unsigned long long)a2 << 32);
    int new_var;
    a0[0] = (int)(v << 32 >> 32);
    new_var = (int)(v >> 32);
    a0[1] = new_var;
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

inline void *setTRXDIR(char *a0, unsigned int a1)
{
    unsigned long long v = (unsigned int)a1;
    *(int *)(a0 + 8) = 0x53;
    *(int *)(a0 + 0) = (int)v;
    *(int *)(a0 + 4) = (int)(v >> 32);
    *(int *)(a0 + 0xC) = 0;
    return a0 + 0x10;
}
