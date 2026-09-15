/* libgraph.a member graph009.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef int u_int128 __attribute__((mode(TI)));

typedef struct {
    short f0;     /* 0x00 */
    short f2;     /* 0x02 */
    short f4;     /* 0x04 */
    short f6;     /* 0x06 */
    long long f8; /* 0x08 */
} GParam;

/* GS privileged-register fields this member rewrites in place. */
typedef struct {
    unsigned long long FBP : 9;
    unsigned long long FBW : 6;
    unsigned long long PSM : 5;
    unsigned long long pad20 : 12;
    unsigned long long DBX : 11;
    unsigned long long DBY : 11;
    unsigned long long pad54 : 10;
} sceGsDispFb;

typedef struct {
    unsigned long long FBP : 9;
    unsigned long long FBW : 6;
    unsigned long long PSM : 6;
    unsigned long long pad21 : 11;
    unsigned long long FBMSK : 32;
} sceGsFrame;

typedef struct {
    unsigned long long NLOOP : 15;
    unsigned long long EOP : 1;
    unsigned long long pad16 : 16;
    unsigned long long id : 14;
    unsigned long long PRE : 1;
    unsigned long long PRIM : 11;
    unsigned long long FLG : 2;
    unsigned long long NREG : 4;
    unsigned long long REGS0 : 4;
    unsigned long long REGS1 : 60;
} sceGifTag;

typedef struct {
    long long pmode;    /* 0x00 */
    long long smode2;   /* 0x08 */
    sceGsDispFb dispfb; /* 0x10 */
    long long display;  /* 0x18 */
    long long bgcolor;  /* 0x20 */
} sceGsDispEnv;

typedef struct {
    sceGsFrame frame;     /* 0x00 */
    long long frame_addr; /* 0x08 */
    char rest[0x70];      /* 0x10 */
} sceGsDrawEnv;

typedef struct {
    char c[0x60];
} sceGsClear;

typedef struct {
    sceGsDispEnv disp0; /* 0x000 */
    sceGsDispEnv disp1; /* 0x028 */
    sceGifTag giftag0;  /* 0x050 */
    sceGsDrawEnv draw0; /* 0x060 */
    sceGsClear clear0;  /* 0x0E0 */
    sceGifTag giftag1;  /* 0x140 */
    sceGsDrawEnv draw1; /* 0x150 */
    sceGsClear clear1;  /* 0x1D0 */
} sceGsDBuff;

extern GParam *sceGsGetGParam(void);
extern int sceGszbufaddr(short psm, short w, short h);
extern int sceGsSetDefDispEnv(void *d, short psm, short w, short h, short dx, short dy);
extern int sceGsSetDefDrawEnv(void *d, short psm, short w, short h, short ztst, short zpsm);
extern int sceGsSetDefClear(void *c, short ztst, short x, short y, short w, short h,
                            unsigned char r, unsigned char g, unsigned char b, unsigned char a,
                            unsigned int z);

void sceGsSetDefDBuff(sceGsDBuff *db, short psm, short w, short h, short ztst, short zpsm,
                      short flag)
{
    GParam *gp = sceGsGetGParam();
    int zb;
    short fbp;

    sceGsSetDefDispEnv(&db->disp0, psm, w, h, 0, 0);
    sceGsSetDefDispEnv(&db->disp1, psm, w, h, 0, 0);
    sceGsSetDefDrawEnv(&db->draw0, psm, w, h, ztst, zpsm);
    sceGsSetDefDrawEnv(&db->draw1, psm, w, h, ztst, zpsm);
    if (flag) {
        sceGsSetDefClear(&db->clear0, ztst, 0x800 - (w >> 1), 0x800 - (h >> 1), w, h, 0, 0, 0, 0,
                         0);
        sceGsSetDefClear(&db->clear1, ztst, 0x800 - (w >> 1), 0x800 - (h >> 1), w, h, 0, 0, 0, 0,
                         0);
    }

    *(u_int128 *)&db->giftag0 = 0;
    *(u_int128 *)&db->giftag1 = 0;
    db->giftag0.NLOOP = flag ? 0xE : 8;
    db->giftag0.EOP = 1;
    db->giftag0.NREG = 1;
    db->giftag0.REGS0 = 0xE;
    db->giftag1.NLOOP = flag ? 0xE : 8;
    db->giftag1.EOP = 1;
    db->giftag1.NREG = 1;
    db->giftag1.REGS0 = 0xE;

    zb = sceGszbufaddr(psm, w, h);
    if ((gp->f0 == 1 && gp->f4 == 1) || gp->f0 == 0) {
        fbp = zb >> 1;
        db->disp1.dispfb.FBP = fbp;
        db->draw0.frame.FBP = zb >> 1;
    }
}
