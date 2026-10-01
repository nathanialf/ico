/*
 * ico2/ito/include/mv_disp.h
 *
 * The declarations of what mv_disp.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MV_DISP_H
#define MV_DISP_H

#include <libgraph.h>

/* The movie's display environment: the five GS privileged registers
   sceGsSetDefDispEnv fills, then the frame buffer pages of the two fields and
   the display and picture sizes setDispEnv keeps after them.  setDispEnv sets
   DISPFB's fields through its two words. */
typedef struct MvDispEnv { /* field names derived */

    union {
        sceGsDispEnv gs;

        struct {
            long long pmode;  /* 0x00 */
            long long smode2; /* 0x08 */
            int dispfb;       /* 0x10, DISPFB bits 0-31: FBP, FBW, PSM */
            int dispfbDB;     /* 0x14, DISPFB bits 32-63: DBX, DBY */
        } w;
    } env;

    int fbp[2];      /* 0x28, the frame buffer page each field shows */
    int width;       /* 0x30 */
    int height;      /* 0x34 */
    int imageWidth;  /* 0x38, the movie picture's size */
    int imageHeight; /* 0x3C */
} MvDispEnv;

extern MvDispEnv display;
void dispDelete(MvDispEnv *self);
void loadImage(int addr);
int handler_endimage(int channel);
void startDisplay(int field);
void endDisplay(void);
inline void *setDMAscTag(void *p, int spr, unsigned int addr, int irq, int id, int pce, int qwc);
inline void *setGIFtag(int *p, long long regs, int nreg, int flg, int prim, int pre, int eop, int nloop);
void *setGIFad(int *p, int addr, long long data);
inline void *setTEXFLUSH(int *p);
inline void *setTEX1_1(int *p, int lcm, int mxl, int mmag, int mmin, int mtba, int l, int k);
void dispClear(MvDispEnv *self, unsigned int col);
void dispCreate(MvDispEnv *self, int imageW, int imageH, int dbx, int dby);

void dispSetTags(MvDispEnv *self, int src, int image, int field, int x, int y, int w, int h, int texW,
                 int texH);

int vblankHandler(int cause);

#endif /* MV_DISP_H */
