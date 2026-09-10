#include "common.h"

/* The fog CLUT upload packet: a VIF code quad (nop, nop, FLUSHA, DIRECT 65),
 * a GIFtag (EOP, NLOOP=64, FLG=IMAGE), the 256-entry 32-bit CLUT itself and a
 * trailing FLUSHA quad.  splat names the header D_006AF590 and the CLUT
 * D_006AF5B0 (= D_006AF590 + 0x20); they are one object. */
typedef struct FogClutPacket {
    unsigned int vif[4];    /* 0x000 */
    long long gif[2];       /* 0x010 */
    unsigned int clut[256]; /* 0x020 */
    unsigned int vifEnd[4]; /* 0x420 */
} FogClutPacket;

extern FogClutPacket D_006AF590;
extern int D_0028F720[]; /* stage settings; fog fields at 0x90..0xA8 */
extern void FlushCache(int a0);

void fog_MakeFogClut(void)
{
    unsigned int buf[8][2][2][8];
    unsigned int *clut = D_006AF590.clut;
    int i;
    int j;
    int k;
    int l;
    int near;
    int far;
    int r;
    int g;
    int b;
    int a;
    float v;

    near = D_0028F720[0xA4 / 4];
    far = D_0028F720[0xA8 / 4];

    r = D_0028F720[0x90 / 4];
    g = D_0028F720[0x94 / 4];
    b = D_0028F720[0x98 / 4];
    a = D_0028F720[0x9C / 4];

    D_006AF590.vif[0] = 0;
    D_006AF590.vif[1] = 0;
    D_006AF590.vif[2] = 0x13000000;
    D_006AF590.vif[3] = 0x50000041;
    D_006AF590.gif[0] = 0x0800000000008040;
    D_006AF590.gif[1] = 0;
    D_006AF590.vifEnd[0] = 0x13000000;
    D_006AF590.vifEnd[1] = 0;
    D_006AF590.vifEnd[2] = 0;
    D_006AF590.vifEnd[3] = 0;

    for (i = 0; i < 256; i++) {
        if (i <= near) {
            v = 0.0f;
        } else if (i > far) {
            v = a / 2;
        } else {
            v = a * (i - near) / (far - near) / 2;
        }
        clut[255 - i] = ((int)v << 24) | (b << 16) | (g << 8) | r;
    }

    /* GS 32-bit CLUT storage swizzle: the two middle 8-entry blocks of every
     * 32-entry run trade places. */
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                for (l = 0; l < 8; l++) {
                    buf[i][k][j][l] = *clut++;
                }
            }
        }
    }

    for (i = 0; i < 256; i++) {
        D_006AF590.clut[i] = ((unsigned int *)buf)[i];
    }

    FlushCache(0);
}

INCLUDE_ASM("asm/nonmatchings/src/ZFog", fog_DrawFog);

/* the shared pad-state array (GsBase.c's GsbPad): trg at 0x4, rep at 0xC */
typedef struct GsbPad {
    int _0;
    int trg; /* 0x4 */
    int _8;
    int rep; /* 0xC */
} GsbPad;

/* one row of the fog debug menu: a label, the int it edits and its range */
typedef struct FogToolItem {
    char *name; /* 0x0 */
    int *val;   /* 0x4 */
    int min;    /* 0x8 */
    int max;    /* 0xC */
} FogToolItem;

extern GsbPad D_0028F8F0[];
extern char *D_00290C08[];        /* "Off" / "On" */
extern FogToolItem D_00550AE8[];  /* 9 rows */
extern unsigned int D_00550C08[]; /* unselected / selected text colour */
extern char D_00550C10[];         /* "Fog Tool" */
extern char D_00550C20[];         /* "Fog %s => %s\n" */
extern char D_00550C30[];         /* "Fog %s => %d\n" */
extern int D_0063A354;            /* highlighted row */
extern char D_0063A358[];         /* "%s : %s" */
extern char D_0063A360[];         /* "%s : %d" */
extern void debug_PrintfDummy(int x, int y, unsigned int col, char *fmt, ...);
extern void debug_StdPrintfDummy(char *fmt, ...);

int fog_FogTool(void)
{
    int i;
    int v;
    int ret;

    ret = 0;
    debug_PrintfDummy(0xA, 0x32, 0xFF800000, D_00550C10);

    for (i = 0; i < 9; i++) {
        if (D_00550AE8[i].min == 0 && D_00550AE8[i].max == 1) {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 0x32, D_00550C08[(D_0063A354 == i) ? 1 : 0],
                              D_0063A358, D_00550AE8[i].name, D_00290C08[*D_00550AE8[i].val]);
        } else {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 0x32, D_00550C08[(D_0063A354 == i) ? 1 : 0],
                              D_0063A360, D_00550AE8[i].name, *D_00550AE8[i].val);
        }
    }

    if (D_0028F8F0[0].rep & 0x4000) {
        D_0063A354++;
        if (D_0063A354 >= 9) {
            D_0063A354 = 0;
        }
    }
    if (D_0028F8F0[0].rep & 0x1000) {
        D_0063A354--;
        if (D_0063A354 < 0) {
            D_0063A354 = 8;
        }
    }
    if (D_0028F8F0[0].rep & 0x2000) {
        v = ++*D_00550AE8[D_0063A354].val;
        if (D_00550AE8[D_0063A354].max < v) {
            *D_00550AE8[D_0063A354].val = D_00550AE8[D_0063A354].min;
        }
    }
    if (D_0028F8F0[0].rep & 0x8000) {
        v = --*D_00550AE8[D_0063A354].val;
        if (v < D_00550AE8[D_0063A354].min) {
            *D_00550AE8[D_0063A354].val = D_00550AE8[D_0063A354].max;
        }
    }
    if (D_0028F8F0[0].trg & 0x20) {
        for (i = 0; i < 9; i++) {
            if (D_00550AE8[i].min == 0 && D_00550AE8[i].max == 1) {
                debug_StdPrintfDummy(D_00550C20, D_00550AE8[i].name,
                                     D_00290C08[*D_00550AE8[i].val]);
            } else {
                debug_StdPrintfDummy(D_00550C30, D_00550AE8[i].name, *D_00550AE8[i].val);
            }
        }
        ret = 1;
    }
    if (D_0028F8F0[0].trg & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        D_0063A354 = 0;
    }
    fog_MakeFogClut();
    return ret;
}
