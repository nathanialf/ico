/*
 * ico2/ito/include/mv_disp.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what mv_disp.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
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
/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order mv_disp.c's inline tail has. */
void dispDelete(MvDispEnv *self);
void loadImage(int a0);
int handler_endimage(void);
void startDisplay(int a0);
void endDisplay(void);
void *setDMAscTag(void *a0, int a1, unsigned int a2, int a3, int p4, int p5, int p6);
void *setGIFtag(int *a0, long long a1, int a2, int a3, int p4, int p5, int p6, int p7);
void *setGIFad(int *a0, int a1, long long a2);
void *setTEXFLUSH(int *a0);
void *setTEX1_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7);
void dispClear(MvDispEnv *self, unsigned int col);
void dispCreate(MvDispEnv *self, int a1, int a2, int a3, int a4);

void dispSetTags(MvDispEnv *self, int src, int a2, int a3, int p4, int p5, int p6, int p7, int p8,
                 int p9);

int vblankHandler(void);

#endif /* MV_DISP_H */
