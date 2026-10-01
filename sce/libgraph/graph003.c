/* libgraph.a member graph003.o */
#include <stdio.h>
#include <libgraph.h>

typedef long long s_long128;

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    sceGsGParam *gp = sceGsGetGParam();

    disp->pmode = 0x66;
    if (gp->inter != 0) {
        if (gp->ffmd != 0) {
            disp->smode2 = 3;
        } else {
            disp->smode2 = 1;
        }
    } else {
        disp->smode2 = 2;
    }
    disp->dispfb = ((s_long128)(psm & 0xF) << 15) | ((s_long128)(((w + 0x3F) >> 6) & 0x3F) << 9);

    if (gp->omode == 2) {
        if (gp->inter == 1) {
            /* RECONSTRUCTION: the empty asm stands in for Sony's text, presumed
             * the plain `(dy + 50) & 0xFFF`.  The object reads the sum once
             * between the add and the mask, which places this arm's
             * divide-by-zero trap ahead of the shift; no C spelling of the
             * expression keeps that read. */
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

            if (gp->ffmd) {
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
    } else if (gp->omode == 3) {
        if (gp->inter == 1) {
            /* RECONSTRUCTION: as in the f2 == 2 arm, the empty asm stands in
             * for Sony's text, presumed the plain `(dy + 72) & 0xFFF`. */
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

            if (gp->ffmd) {
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
        printf("sceGsDefDispEnv:Not support displaymode for %d!!\n", gp->omode);
    }
    disp->bgcolor = 0;
}
