/* libgraph.a member graph009.o */

typedef int u_int128 __attribute__((mode(TI)));

/* libgraph.h's sceGsGParam as this member reads it: the INTC pair as one
   doubleword, whose 8-byte alignment the member's code shows. */
typedef struct {
    short inter;    /* 0x0 */
    short omode;    /* 0x2 */
    short ffmd;     /* 0x4 */
    short version;  /* 0x6 */
    long long intc; /* 0x8, intcUsed and handler */
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

/* libgraph.h's prototypes, over this member's own field-level record types */
extern GParam *sceGsGetGParam(void);
extern short sceGszbufaddr(short psm, short w, short h);
extern void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy);
extern int sceGsSetDefDrawEnv(sceGsDrawEnv *env, short psm, short w, short h, short ztst,
                              short zpsm);
extern int sceGsSetDefClear(sceGsClear *cl, short ztst, short x, short y, short w, short h,
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
    if ((gp->inter == 1 && gp->ffmd == 1) || gp->inter == 0) {
        fbp = zb >> 1;
        db->disp1.dispfb.FBP = fbp;
        db->draw0.frame.FBP = zb >> 1;
    }
}
