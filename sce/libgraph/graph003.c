/* libgraph.a member graph003.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef long long s_long128;

typedef struct {
    short f0; /* 0x00 */
    short f2; /* 0x02 */
    short f4; /* 0x04 */
} GParam;

/* PMODE / SMODE2 / DISPFB / DISPLAY / BGCOLOR, one qword each. */
typedef struct {
    s_long128 pmode;   /* 0x00 */
    s_long128 smode2;  /* 0x08 */
    s_long128 dispfb;  /* 0x10 */
    s_long128 display; /* 0x18 */
    s_long128 bgcolor; /* 0x20 */
} sceGsDispEnv;

extern GParam *sceGsGetGParam(void);
extern void printf(const char *fmt, ...);
extern char D_006360E8[];

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    GParam *gp = sceGsGetGParam();

    disp->pmode = 0x66;
    if (gp->f0 != 0) {
        if (gp->f4 != 0) {
            disp->smode2 = 3;
        } else {
            disp->smode2 = 1;
        }
    } else {
        disp->smode2 = 2;
    }
    disp->dispfb = ((s_long128)(psm & 0xF) << 15) | ((s_long128)(((w + 0x3F) >> 6) & 0x3F) << 9);

    if (gp->f2 == 2) {
        if (gp->f0 == 1) {
            /* RECONSTRUCTION: the ROM issues this arm's divide-by-zero trap
             * (beql/break) ahead of `dsll $7,$3,12` (words 53-55), which the
             * compiler schedules only when one zero-byte instruction reading the
             * sum sits between `addiu $3,$18,50` and `andi $3,$3,0xfff` in both
             * schedulers: a same-register sign extension of dy + 50 that combine
             * folds in every C spelling measured (cast, 64-bit local, compound
             * assignment, short truncation, mask after shift, shared temporaries,
             * second quotient, the public DISPLAY bitfield record). The empty asm
             * stands in for that extension; the text here is presumed Sony's
             * plain `(dy + 50) & 0xFFF`, which the bytes cannot show. */
            s_long128 ddy = (s_long128)(({
                                            int e = dy + 0x32;
                                            __asm__("" : "+r"(e));
                                            e;
                                        }) &
                                        0xFFF)
                            << 12;
            int q = (w + 0x9FF) / w;
            s_long128 magh = (s_long128)(q - 1) << 23;
            s_long128 ddx = ((s_long128)(dx * q) + 0x27C) & 0xFFF;
            s_long128 dw = (s_long128)(q * w - 1) << 32;
            s_long128 display;

            if (gp->f4) {
                display = magh | dw | (ddx | (s_long128)(h * 2 - 1) << 44) | ddy;
            } else {
                display = magh | dw | (ddx | (s_long128)(h - 1) << 44) | ddy;
            }
            disp->display = display;
        } else {
            int q = (w + 0x9FF) / w;
            s_long128 dh = (s_long128)(h - 1) << 44;

            disp->display = (s_long128)(q - 1) << 23 | (s_long128)(q * w - 1) << 32 |
                            ((((s_long128)(dx * q) + 0x27C) & 0xFFF) | dh) |
                            (s_long128)((dy + 0x19) & 0xFFF) << 12;
        }
    } else if (gp->f2 == 3) {
        if (gp->f0 == 1) {
            /* RECONSTRUCTION: as in the f2 == 2 arm, the asm reproduces the trap
             * ahead of `dsll $7,$3,12` (words 95-97) in place of the folded sign
             * extension of dy + 72; the text is presumed Sony's plain
             * `(dy + 72) & 0xFFF`. */
            s_long128 ddy = (s_long128)(({
                                            int e = dy + 0x48;
                                            __asm__("" : "+r"(e));
                                            e;
                                        }) &
                                        0xFFF)
                            << 12;
            int q = (w + 0x9FF) / w;
            s_long128 magh = (s_long128)(q - 1) << 23;
            s_long128 ddx = ((s_long128)(dx * q) + 0x290) & 0xFFF;
            s_long128 dw = (s_long128)(q * w - 1) << 32;
            s_long128 display;

            if (gp->f4) {
                display = magh | dw | (ddx | (s_long128)(h * 2 - 1) << 44) | ddy;
            } else {
                display = magh | dw | (ddx | (s_long128)(h - 1) << 44) | ddy;
            }
            disp->display = display;
        } else {
            int q = (w + 0x9FF) / w;
            s_long128 dh = (s_long128)(h - 1) << 44;

            disp->display = (s_long128)(q - 1) << 23 | (s_long128)(q * w - 1) << 32 |
                            ((((s_long128)(dx * q) + 0x290) & 0xFFF) | dh) |
                            (s_long128)((dy + 0x24) & 0xFFF) << 12;
        }
    } else {
        printf(D_006360E8, gp->f2);
    }
    disp->bgcolor = 0;
}
