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
void loadImage(int a0);
int handler_endimage(int channel);
void startDisplay(int a0);
void endDisplay(void);
inline void *setDMAscTag(void *a0, int a1, unsigned int a2, int a3, int p4, int p5, int p6);
inline void *setGIFtag(int *a0, long long a1, int a2, int a3, int p4, int p5, int p6, int p7);
void *setGIFad(int *a0, int a1, long long a2);
inline void *setTEXFLUSH(int *a0);
inline void *setTEX1_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7);
void dispClear(MvDispEnv *self, unsigned int col);
void dispCreate(MvDispEnv *self, int a1, int a2, int a3, int a4);

void dispSetTags(MvDispEnv *self, int src, int a2, int a3, int p4, int p5, int p6, int p7, int p8,
                 int p9);

int vblankHandler(int cause);

#endif /* MV_DISP_H */
