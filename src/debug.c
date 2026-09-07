#include "common.h"

/* debug_exception_screen.c.inc (compiled into debug_exception.o) */

typedef struct { float f[4]; } __attribute__((packed)) Blk16;
typedef struct { int x, y, w, h; } FR;
typedef struct { char _0[0x20]; int f_20; char _24[0x18]; } GsysObjInfo;
extern char D_0061B440[];
extern char D_0063AE78[];
extern char D_0063AE80[];
void debug_Assert(char *fmt, ...) {
    char buf[0x100];
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 56);
    debug_assertMessage(D_0061B440, 0x570, buf);
    __assert(D_0061B440, 0x570, D_0063AE78);
    debug_assert(D_0061B440, 0x571);
    __assert(D_0061B440, 0x571, D_0063AE80);
}
extern int D_0063AE84;
void debug_openLog(void) {
    volatile char buf[256];
    D_0063AE84 = -1;

}
/* sceWrite returns the byte count (SCE sifdev); the unused return value is
   what makes $v0 live-and-dying at each call site. */
extern int sceWrite();
extern int strlen();
extern void vsprintf();
void debug_LogPrintf(const char *fmt, ...) {
    char buf[0x100];
    void *info;
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = strlen(buf);
    sceWrite(D_0063AE84, buf, info);
}
extern void debug_StdPrintfDummy(char *fmt, ...);
/* the debug-option table: 76 records of 0x1C bytes */
typedef struct { char *name; int _4; int *val; char _C[0x10]; } DbgOpt;
extern DbgOpt D_0061A4D0[];
extern char D_0061B5B0[];
extern char D_0061B5F0[];
extern char D_0061B608[];
extern char D_0061B640[];
extern char D_0061B570[];
extern char D_0063AE98[];
extern char D_0063AEA0[];
extern int sprintf();
extern int debugSceOpen(int a0, int a1);
extern int debugSceClose(int a0);
void debug_SaveDebugOptionFile(void)
{
    char buf[0x100];
    int i;
    int fd;
    debug_StdPrintfDummy(D_0061B5B0);
    fd = debugSceOpen((int)D_0061B5F0, 0x602) < 0;
    if (fd) {
        debug_StdPrintfDummy(D_0061B608);
    } else {
        for (i = 0; i < 76; i++) {
            sprintf(buf, D_0063AE98, D_0061A4D0[i].name);
            sceWrite(fd, buf, strlen(buf));
            sprintf(buf, D_0063AEA0, *D_0061A4D0[i].val);
            sceWrite(fd, buf, strlen(buf));
        }
        debugSceClose(fd);
        debug_StdPrintfDummy(D_0061B640);
    }
    debug_StdPrintfDummy(D_0061B570);
    debug_openLog();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_GetDebugOption);
extern int AddDmacHandler();
extern unsigned int D_0063AE8C;
extern void EnableDmac();
extern void RemoveDmacHandler();
extern int debug_CallbackGsFinish();
void debug_SetDmaCallback(void)
{
    if ((int)D_0063AE8C != -1) {
        RemoveDmacHandler(1, D_0063AE8C);
    }
    D_0063AE8C = AddDmacHandler(1, (int)debug_CallbackGsFinish, -1);
    EnableDmac(1);
}
extern int D_0063AD28;
extern int D_0063AE64;
extern int D_0063B130;
extern int D_0063B134;
extern int D_0063B138;
extern int D_0063B13C;
extern int D_0063B140;
extern int D_0063B144;
extern int D_0063B148;
extern int D_0063B14C;
extern int D_0063B150;
extern int D_0063B154;
extern int D_0063B158;
extern int D_0063B15C;
extern int D_0063B160;
extern int D_0063B164;
extern int D_0063B168;
extern int D_0063B16C;
extern int D_0063B170;
extern int D_0063B174;
extern int D_0063B178;
extern int D_0063B17C;
extern int D_0063B180;
extern int D_0063B184;
extern int D_0063B188;
extern int D_0063B18C;
extern int D_0063B190;
extern int D_0063B194;
extern int D_0063B198;
extern int D_0063B19C;
extern int D_0063B1A0;
extern int D_0063B1A4;
extern int D_0063B1A8;
extern int D_0063B1AC;
extern int D_0063B1B0;
extern int D_0063B1B4;
extern int D_0063B1B8;
extern int D_0063B1BC;
extern int D_0063B1C0;
extern int D_0063B1C8;
extern int D_0063B1CC;
extern int D_0063B1D8;
extern int D_0063B1DC;
extern int D_0063B1E0;
extern int D_0063B1E4;
extern int D_0063B1E8;
extern int D_0063B1EC;
extern int D_0063B1F0;
extern int D_0063B1F4;
extern int D_0063B1F8;
extern int D_0063B1FC;
extern int D_0063B200;
extern int D_0063B204;
extern int D_0063B208;
extern int D_0063B20C;
extern int D_0063B210;
extern int D_0063B214;
extern int D_0063B218;
extern int D_0063B21C;
extern int D_0063B220;
extern int D_0063B224;
extern int D_0063B228;
extern int D_0063B22C;
extern int D_0063B230;
extern int D_0063B234;
extern int D_0063B238;
extern int D_0063B23C;
extern int D_0063B240;
extern int D_0063B244;
extern int D_0063B248;
extern int D_0063B24C;
extern int D_0063B250;
extern int D_0063B254;
extern int D_0063B258;
extern int D_0063B25C;
extern int D_0063B260;
extern int game_pause;
extern int D_00639EA0;
extern void ChangeFieldCollisionDebugMode(int mode);
/* INTERIM: ChangeGirlControlMode (census function, own ROM slot later in this
   TU) is inlined here per the listing (rows src/debug.c:1188-1189 inside
   debug_VariableInit's ROM). While the tail still carries asm members its own
   definition cannot be marked `inline`, so this stand-in serves the call site.
   Fold the two together when the TU is complete. */
static inline void ChangeGirlControlMode_interim(int a0)
{
    if (a0 == 1) {
        D_00639EA0 = a0;
    }
}
void debug_VariableInit(void)
{
    D_0063B170 = 15;
    D_0063B160 = 0;
    D_0063B134 = 0;
    D_0063B130 = 0;
    D_0063B1A4 = 0;
    D_0063B13C = 0;
    D_0063B140 = 0;
    D_0063B144 = 0;
    D_0063B15C = 0;
    D_0063B148 = 0;
    D_0063B14C = 0;
    D_0063B150 = 0;
    D_0063B154 = 0;
    D_0063B164 = 0;
    D_0063B158 = 0;
    D_0063B16C = 1;
    D_0063B168 = 1;
    D_0063B174 = 0;
    D_0063B178 = 0;
    D_0063B138 = 0;
    D_0063B17C = 0;
    D_0063B180 = 1;
    D_0063B184 = 0;
    D_0063B188 = 0;
    D_0063B18C = 1;
    D_0063B198 = 0;
    D_0063AE64 = 0;
    D_0063B194 = 0;
    D_0063B19C = 1;
    D_0063B1A8 = 0;
    D_0063B1AC = 1;
    D_0063B1B0 = 100;
    D_0063B1A0 = 0;
    D_0063B1B4 = 25;
    D_0063B1B8 = 100;
    D_0063B1BC = 0;
    D_0063B1C0 = 0;
    D_0063B1CC = 0;
    D_0063B1D8 = 0;
    D_0063B250 = 20;
    D_0063B254 = 0;
    D_0063B258 = 256;
    D_0063B25C = 0;
    D_0063B1DC = 0;
    D_0063B1E0 = 0;
    D_0063B1E4 = 4;
    D_0063B190 = 1;
    D_0063B1F0 = 1;
    D_0063B1F4 = 1;
    D_0063B1F8 = 1;
    D_0063B1FC = 1;
    D_0063B200 = 1;
    D_0063B204 = 1;
    D_0063AD28 = 0;
    D_0063B1E8 = 0;
    D_0063B1EC = 3;
    D_0063B20C = 1;
    D_0063B208 = 0;
    D_0063B210 = 1;
    D_0063B214 = 4;
    D_0063B218 = 4;
    D_0063B21C = 5;
    D_0063B220 = 0;
    D_0063B224 = 0;
    D_0063B228 = 0;
    D_0063B22C = 1;
    D_0063B230 = 0;
    D_0063B234 = 0;
    D_0063B238 = 0;
    D_0063B23C = 0;
    D_0063B240 = 0;
    D_0063B244 = 1;
    D_0063B248 = 1;
    D_0063B24C = 0;
    D_0063B260 = 0;
    D_0063B1C8 = 0;
    game_pause = 0;
    ChangeFieldCollisionDebugMode(0);
    ChangeGirlControlMode_interim(D_0063B24C);
}
extern int D_0063B110;
extern int D_0063B114;
extern int D_0063B118;
extern int D_0063B11C;
extern int D_0063B120;
extern int D_0063B124;
extern int D_0063B1C4;
extern void debug_ClearFontWindow(void);
extern void debug_makeBackImage(void);
void debug_Init(void) {
    debug_ClearFontWindow();
    D_0063B110 = 0;
    D_0063B114 = 0;
    D_0063B118 = 0;
    D_0063B11C = 0;
    D_0063B120 = 0;
    D_0063B124 = 0;
    D_0063B1C4 = 0;
    *(volatile int *)0x10000010 = 0x82;
    *(volatile int *)0x10000810 = 0x82;
    debug_makeBackImage();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Load);
ASM_LIT4_SLOT(D_00639338, 10059776.0f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MakeFont);
/* D_00619BB0 = the 8x8 1bpp font bitmap (8 bytes per glyph);
   D_00706AD0 = the glyph re-expanded to 8 shorts (shifted left one column);
   D_00704AD0 = the 3x3-dilated outline, 16 shorts per glyph. */
extern unsigned char D_00619BB0[];
extern unsigned short D_00704AD0[];
extern unsigned short D_00706AD0[];
extern void debug_MakeFont(void);
void debug_makeBackImage(void)
{
    int i;
    int j;
    unsigned char *src;
    unsigned short *a;
    unsigned short *b;
    for (i = 0; i < 256; i++) {
        src = &D_00619BB0[i * 8];
        a = &D_00704AD0[i * 16];
        b = &D_00706AD0[i * 8];

        for (j = 0; j < 16; j++) { a[j] = 0; b[j] = 0; }
        for (j = 0; j < 8; j++) b[j + 1] = src[j] << 1;
        a[0] = b[0] | (b[0] << 1) | (b[0] >> 1) | b[1] | (b[1] << 1) | (b[1] >> 1);
        for (j = 1; j < 9; j++)
            a[j] = b[j - 1] | (b[j - 1] << 1) | (b[j - 1] >> 1) | b[j] | (b[j] << 1) | (b[j] >> 1) | b[j + 1] | (b[j + 1] << 1) | (b[j + 1] >> 1);
        for (j = 0; j < 10; j++) a[j] = a[j] << 1;
        for (j = 0; j < 10; j++) a[j] = a[j] & ~b[j];
    }
    debug_MakeFont();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintCharacter);
extern int D_0063AEB0;
extern int D_0063B13C;
extern void debug_PrintCharacter(char *str, int x, int y, int r, int g, int b, int sz);
extern int gif_CheckOpen(void);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);
extern void gif_Sprite(void *a0, unsigned int a1, int a2, void *a3, int a4);
extern void gif_StartPacketPri(int a0);
void debug_PrintFont(int a0, int a1, int a2, char *a3) {
    FR buf[2];
    int r;

    buf[1].x = a0 - 0x142;
    buf[1].y = a1 - 0x71;
    r = strlen(a3);
    buf[1].h = 9;
    buf[1].w = r * 0xC + 4;
    buf[0] = buf[1];

    if (gif_CheckOpen() != 0) {
        return;
    }
    if (D_0063B13C & 2) {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_Sprite(&buf[0], 0xFFFFFFFDU, 0, &D_0063AEB0, 1);
        gif_EndPacket();
    } else {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_EndPacket();
    }
    debug_PrintCharacter(a3, a0, a1, (unsigned) a2 >> 24, ((unsigned) a2 >> 16) & 0xFF, ((unsigned) a2 >> 8) & 0xFF, 0x70);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_FlushFontWindow);
extern void debug_FlushFontWindow(void);
void debug_FlushFont(void) {
    debug_FlushFontWindow();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", draw_batsu);
INCLUDE_ASM("asm/nonmatchings/src/debug", draw_shikaku);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_brainBar);
extern char D_00704680[];
extern char D_0063AE90[];
extern int D_0063B13C;
extern void strcat(char *dst, char *src);
extern void debug_Printf(int a, int b, unsigned int c, int x, ...);
int debug_MakeBarString(char *p, int a, int b, FR fr, long long x, int line)
{
    char buf[16];
    int i;
    int len;

    len = strlen(p);
    if (len == 0) {
        return 0;
    }
    D_00704680[0] = 0;
    for (i = 0; i < len; i++, p++) {
        if (*p == '$') {
            switch (p[1]) {
            case 'P':
                sprintf(buf, D_0063AE90, a);
                strcat(D_00704680, buf);
                break;
            case 'T':
                sprintf(buf, D_0063AE90, b);
                strcat(D_00704680, buf);
                break;
            }
            p++;
            i++;
        } else {
            buf[0] = *p;
            buf[1] = 0;
            strcat(D_00704680, buf);
        }
    }
    if (strlen(D_00704680) != 0 && (D_0063B13C & 1)) {
        debug_Printf((int)(x + 0x148), fr.y + line * 7 + (fr.h + 0x71),
                     0xFFFFFF00u, (int)D_00704680);
    }
    return strlen(D_00704680);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DrawBar);
ASM_LIT4_SLOT(D_0063933C, 270000.0f);
ASM_LIT4_SLOT(D_00639340, 0.01f);
/* the profiler ring: 0x400 entries of 28 bytes, filled by debug_SetBar. */
typedef struct {
    char name[12];          /* 0x00 */
    unsigned char col[4];   /* 0x0C */
    char *file;             /* 0x10 */
    short count;            /* 0x14 */
    short pad16;            /* 0x16 */
    int line;               /* 0x18 */
} DebugBar;
extern DebugBar D_00708880[];
extern int D_0063C384;
extern int D_0063AE68;
extern int D_0028F4C0[];
extern int frame_count;
extern char D_0061BA18[];
extern char D_0061BA28[];
extern void debug_Printf(int a, int b, unsigned int c, int x, ...);
extern void debug_brainBar(void);
extern void debug_DrawBar(void);
void debug_DispBar(void)
{
    float inv;
    int va;
    int vb;
    int n;
    inv = 1.0f / (270000.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
    vb = (float)(D_00708880[D_0063C384 - 1].count * 100) * inv;
    va = (float)(D_0063AE68 * 100) * inv;

    if (D_0063B140 != 0 || (D_0063B13C & 1) != 0) debug_Printf(10, 10, 0xFFFFFF00u, (int)D_0061BA18, vb, va, frame_count);
    if (D_0063B138 != 0) debug_brainBar();
    if (D_0063B130 != 0) debug_DrawBar();
    if (D_0063B114 != 0 || D_0063B124 != 0) {
        n = 1;
        if (D_0063B114 != 0) n = D_0063B114;
        if (D_0063B140 != 0 || (D_0063B13C & 1) != 0) debug_Printf(10, 20, 0xFFFFFF00u, (int)D_0061BA28, D_0063B110, D_0063B114, D_0063B110 / n, D_0063B118, D_0063B124 / 1024, D_0063B11C);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_ResizeSnapShot);
/* 24-bit BMP file header, offset by two pad bytes so the 32-bit fields land
   4-aligned on the stack; the file image starts at &hdr.bfType. */
typedef struct {
    unsigned char pad[2];      /* 0x00 */
    unsigned char bfType[2];   /* 0x02 */
    int bfSize;                /* 0x04 */
    int bfReserved;            /* 0x08 */
    int bfOffBits;             /* 0x0C */
    int biSize;                /* 0x10 */
    int biWidth;               /* 0x14 */
    int biHeight;              /* 0x18 */
    short biPlanes;            /* 0x1C */
    short biBitCount;          /* 0x1E */
    int biCompression;         /* 0x20 */
    int biSizeImage;           /* 0x24 */
    int biXPelsPerMeter;       /* 0x28 */
    int biYPelsPerMeter;       /* 0x2C */
    int biClrUsed;             /* 0x30 */
    int biClrImportant;        /* 0x34 */
} BmpHeader;
void debug_WriteBMP(int fd, int w, int h, unsigned int *src)
{
    unsigned char line[w * 3];
    BmpHeader hdr;
    unsigned char *s;
    unsigned char *d;
    int x;
    int y;
    hdr.pad[0] = 0;
    hdr.pad[1] = 0;
    hdr.bfType[0] = 0x42;
    hdr.bfType[1] = 0x4D;
    hdr.bfOffBits = 0x36;
    hdr.biSize = 0x28;
    hdr.biPlanes = 1;
    hdr.biBitCount = 24;
    hdr.biCompression = 0;
    hdr.biXPelsPerMeter = 0;
    hdr.biYPelsPerMeter = 0;
    hdr.biClrUsed = 0;
    hdr.biClrImportant = 0;
    hdr.biWidth = w;
    hdr.biHeight = h;
    hdr.biSizeImage = w * h * 3;
    hdr.bfSize = hdr.biSizeImage + 0x36;
    sceWrite(fd, hdr.bfType, 0x36);
    for (y = h - 1; y >= 0; y--) {
        s = (unsigned char *)&src[y * w];
        d = line;
        for (x = 0; x < w; x++, d += 3) {
            d[0] = s[2];
            d[1] = s[1];
            d[2] = s[0];
            s += 4;
        }
        sceWrite(fd, line, w * 3);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SnapShot);
extern char D_0061BAA8[];
extern char D_0061BAC0[];
extern char D_0063AF38[];
extern char D_0063AF40[];
extern char D_0063AF48[];
extern char D_0063AF50[];
extern int fptodp(float v);
void debug_DispQW(void *p, int size)
{
    int isf = 0;
    int i;
    int j;

    switch (size) {
    case 0:
        isf = 1;
        size = 4;
        debug_StdPrintfDummy(D_0061BAA8, p);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_StdPrintfDummy(D_0061BAC0, p, size);
        break;
    default:
        return;
    }
    for (i = 0; i < 16 / size; i++) {
        if (isf == 0) {
            for (j = 16 / (16 / size) - 1; j >= 0; j--) {
                debug_StdPrintfDummy(D_0063AF38, ((unsigned char *)p)[i * size + j]);
            }
            debug_StdPrintfDummy(D_0063AF40);
        } else {
            debug_StdPrintfDummy(D_0063AF48, fptodp(((float *)p)[i]));
        }
    }
    debug_StdPrintfDummy(D_0063AF50);
}
extern void debug_PrintFont();
void debug_Printf(int a, int b, unsigned int c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}
void debug_Printf2(int a, int b, unsigned int c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFontWindow);
void debug_PrintfDummy(int a0, int a1, unsigned int a2, int a3, ...) {
}
void debug_PrintFontWindowDummy(int a0, int a1, ...) {
}
void debug_StdPrintfDummy(char *fmt, ...)
{
    (void)fmt;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_PrintFontf);
extern const char D_0060DAF0_a[] __asm__("D_0061BB40");
extern const char D_00631CF0_a[] __asm__("D_0063AF50");
extern void debug_StdPrintfDummy__pn() __asm__("debug_StdPrintfDummy");
extern int fptodp(float);
void debug_PrintMatrix(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = fptodp(arg[0]);
        int v1 = fptodp(arg[1]);
        int v2 = fptodp(arg[2]);
        int v3 = fptodp(arg[3]);
        debug_StdPrintfDummy__pn((int)D_0060DAF0_a, v0, v1, v2, v3);
        arg += 4;
    }
    debug_StdPrintfDummy__pn((int)D_00631CF0_a);
}
extern char D_0061BB50[];
extern char D_0061BB68[];
void debug_DispVu1FReg(int no, int mode)
{
    int i;
    float f[4];
    int buf[4];
    if (mode != 0) {
        if (no >= 0) {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x400));
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(f) : "memory");
            debug_StdPrintfDummy(D_0061BB50, no, fptodp(f[0]), fptodp(f[1]), fptodp(f[2]), fptodp(f[3]));
        } else {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x400));
            for (i = 0; i < 32; i++) {
                __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
                __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(f) : "memory");
                debug_StdPrintfDummy(D_0061BB50, i, fptodp(f[0]), fptodp(f[1]), fptodp(f[2]), fptodp(f[3]));
            }
        }
    } else {
        if (no >= 0) {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x400));
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(buf) : "memory");
            debug_StdPrintfDummy(D_0061BB68, no, buf[0], buf[1], buf[2], buf[3]);
        } else {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x400));
            for (i = 0; i < 32; i++) {
                __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
                __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(buf) : "memory");
                debug_StdPrintfDummy(D_0061BB68, i, buf[0], buf[1], buf[2], buf[3]);
            }
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Mode);
extern char D_0061BC38[];
extern char D_0063AF70[];
extern char D_0063AF78[];
extern int debug_SelectCsvWindow(char *a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7, int a8, int *a9);
extern int sprintf();
extern unsigned int strlen__pn(char *buf) __asm__("strlen");
int debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5,
                   int (*fn)(int, int), int a7) {
    char buf[count][0x25];
    int i;
    for (i = 0; i < count; i++) {
        if (fn != 0) {
            int r = fn(i, a7);
            sprintf(buf[i], D_0063AF70, i, r);
        } else {
            sprintf(buf[i], D_0063AF78, i);
        }
        if (strlen__pn(buf[i]) >= 0x26) {
            buf[i][0x24] = 0;
            debug_StdPrintfDummy__pn((int)D_0061BC38);
        }
    }
    return debug_SelectCsvWindow(a0, a1, a2, a3, (char *)buf, 0x25, 0, 0, count, a5);
}
extern int D_0063AF90[];
extern int sprintf();
void getLineBuffer(int a0, int a1, int a2)
{
    sprintf(a0, D_0063AF90, a1, a2);
}
extern int D_0063AF80[];
void getBuffer(int a0)
{
    sprintf(a0, D_0063AF80);
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindow);
/* stage records are 0x194 bytes; +0x80 (= D_005F5DD0) is the data file name */
typedef struct { char pad[0x194]; } StgFileName;
extern StgFileName D_005F5DD0[];
extern int D_0028F4D8[];
extern char D_0063AF98[];
extern char D_0061BC78[];
extern int stage_no;
extern int mpegPlayReturnStage;
extern int enable_game_pause;
extern int D_0063A650;
extern int D_0063AA08;
extern char *strstr(const char *s, const char *sub);
extern void soundDataSegAllClose(int a0, int a1);
extern void kanbanInit(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern void stgmgrForceSwitch(int stage);
extern void ACTGame_SetActors_Debug(int stage, int a1);
int debug_SelectStageMain(int ret, int stage)
{
    if (D_0028F4D8[0] != 0) {
        return 0;
    }
    if (ret > 0) {
        debug_StdPrintfDummy(D_0061BC78, stage);
        if (stage != 0) {
            int on = 1;
            if (strstr((char *)&D_005F5DD0[stage], D_0063AF98) == 0) {
                mpegPlayReturnStage = stage_no;
                soundDataSegAllClose(0, 2);
                D_0063A650 = on;
                enable_game_pause = on;
                kanbanInit(0);
                gflagOn(0x18A);
                D_0063AA08 = 0;
                stgmgrForceSwitch(stage);
                gflagOff(0x184);
                ACTGame_SetActors_Debug(stage, on);
            }
        }
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectStage);
/* memory-card request block */
/* one sceMcTblGetDir record: the file name sits at +0x20 in a 0x40-byte entry
   (debug_selectFile forms the table base as mc+0x4C0 and the name as
   mc + i*0x40 + 0x4E0). */
typedef struct {
    char _0[0x10];
    int size;           /* 0x10 */
    char _14[0xC];
    char name[0x20];    /* 0x20 */
} McDirEnt;
typedef struct {
    long long f0;       /* 0x00 -- iosMc flag word, 64-bit */
    char _8[0x8];
    int ret;            /* 0x10 */
    char _14[0x10];
    int f24;            /* 0x24 */
    char _28[0x18];
    int sel;            /* 0x40 */
    int num;            /* 0x44 -- entries filled in by iosMcGetDir */
    int _48;
    int f4C;            /* 0x4C */
    int f50;            /* 0x50 */
    char _54[0x400];
    char name454[0x28]; /* 0x454 */
    char name47C[0x24]; /* 0x47C */
    char _4A0[0x20];    /* 0x4A0 */
    McDirEnt dir[8];    /* 0x4C0 -- sceMcTblGetDir records, 0x40 each */
} McReq;
extern int D_0028F8F4[];

/* src/debug.c:4426-4435 in the listing: the sibling of debug_mcConfirm that
   prints an already-formatted message instead of a fixed prompt. */
static inline int debug_mcAsk(char *msg)
{
    int yes = 0;
    debug_PrintfDummy(0x50, 0x46, 0xFFFFFF00u, (int)D_0063AF80, (int)msg);
    if (D_0028F8F4[0] & 0x20) {
        yes = 1;
    }
    if (D_0028F8F4[0] & 0x40) {
        yes = -1;
    }
    return yes;
}
extern char D_0061BCE0[];
extern char D_0061BD10[];
extern char D_0061BD28[];
extern char D_0061BD40[];
extern char D_0061BD70[];
extern char D_0061BD90[];
extern char D_0061BDA0[];
int debug_mcRetErrCheck(McReq *mc)
{
    char buf[0x40];
    int r;
    if (mc->ret >= 0) {
        return 1;
    }
    switch (mc->ret) {
    case 0:
        r = 1;
        break;
    case -9:
    case -2:
        sprintf(buf, D_0061BCE0, mc->ret);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -4:
        sprintf(buf, D_0061BD10, mc->name47C);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -14:
        sprintf(buf, D_0061BD28, mc->name454);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -16:
        sprintf(buf, D_0061BD40, mc->f24, mc->f50, mc->f4C);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -15:
        sprintf(buf, D_0061BD70, mc->name47C);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -10:
        sprintf(buf, D_0061BD90);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    default:
        sprintf(buf, D_0061BDA0, mc->ret);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    }
    return r;
}
/* src/debug.c:4415-4423 in the listing: a static helper both mc(Un)format
   inline -- prints the confirmation prompt and reads the pad:
   circle (0x20) = yes -> 1, cross (0x40) = cancel -> -1, otherwise 0. */
extern char D_0061BC98[];
extern int D_0028F8F4[];
static inline int debug_mcConfirm(char *msg)
{
    int yes = 0;
    debug_PrintfDummy(0x50, 0x46, 0xFFFFFF00u, (int)D_0061BC98, (int)msg);
    if (D_0028F8F4[0] & 0x20) {
        yes = 1;
    }
    return (D_0028F8F4[0] & 0x40) ? -1 : yes;
}
/* the "*" wildcard pattern D_0063AFC0 is copied into the request block's name
   field as a 2-byte object, not by strcpy */
typedef struct { char c[2]; } McPat;
extern char D_0063AFC0[];
extern int D_0063AFB8;
extern char D_0061BE08[];
extern char D_0061BE18[];
extern void iosMcChdirProduct(McReq *mc);
extern void iosMcGetDir(McReq *mc);
extern int iosMcSync();
int debug_selectFile(McReq *mc)
{
    int i;
    int r = 0;
    int ret = 0;

    switch (D_0063AFB8) {
    case 0:
        mc->f0 &= ~2;
        iosMcChdirProduct(mc);
        D_0063AFB8++;
        break;
    case 1:
    case 4:
        if (iosMcSync(mc)) {
            D_0063AFB8++;
        }
        break;
    case 2:
    case 5:
        if ((ret = debug_mcRetErrCheck(mc)) != 0) {
            D_0063AFB8++;
        }
        break;
    case 3:
        *(McPat *)mc->name47C = *(McPat *)D_0063AFC0;
        iosMcGetDir(mc);
        D_0063AFB8++;
        break;
    case 6:
        for (i = 0; i < mc->num; i++) {
            debug_StdPrintfDummy(D_0061BE08, mc->dir[i].name, *(int *)((char *)mc + (i << 6) + 0x4D0));
        }
        D_0063AFB8++;
        break;
    default:
        debug_SelectCsvWindow(D_0061BE18, 0x50, 0x46, 0xA, mc->dir, 0x40, 0x20, 0,
                              mc->num, &mc->sel);
        if (D_0028F8F4[0] & 0x20) {
            r = 1;
        }
        if (D_0028F8F4[0] & 0x40) {
            r = -1;
        }
        break;
    }
    if (ret < 0) {
        r = -1;
    }
    if (r) {
        D_0063AFB8 = 0;
    }
    return r;
}
extern int D_0063AFD4;
extern char D_0063AFD8[];
extern char D_0061BE50[];
extern char D_0061BE90[];
extern char D_0063AFE0[];
extern char D_004DA788[];
extern char D_004DD700[];
extern void iosMcGetBlockSaveInfo(McReq *mc);
extern void iosMcSaveIconBlock(McReq *mc);
extern void iosMcSaveProductBlock(McReq *mc);
extern void iosMcSaveGameBlock(McReq *mc, void *buf);
extern void gamesysMemorySave(void *a0, void *a1, int a2);
extern void *debug_saveNumFunc(int a0, void *a1);
extern int debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5,
                                    int (*fn)(int, int), int a7);
/* the default save-file name "game." lives in .sdata as 6 bytes */
typedef struct { char c[6]; } McName6;
int debug_mcSaveMainBlock(McReq *mc)
{
    int r = 0;
    int ret = 0;

    switch (D_0063AFD4) {
    case 0:
        *(McName6 *)mc->name47C = *(McName6 *)D_0063AFD8;
        iosMcGetBlockSaveInfo(mc);
        D_0063AFD4++;
        break;
    case 1:
        if (iosMcSync(mc)) {
            D_0063AFD4++;
        }
        break;
    case 2:
    case 8:
    case 13:
        if ((ret = debug_mcRetErrCheck(mc)) != 0) {
            D_0063AFD4++;
        }
        break;
    case 3:
        if (mc->num >= 11) {
            debug_StdPrintfDummy(D_0061BE50);
        }
        r = debug_SelectCsvWindowVal((int)D_0061BE90, 0x50, 0x46, 0xA, 0xA,
                                     (int)&mc->sel,
                                     (int (*)(int, int))debug_saveNumFunc, (int)mc);
        if (r > 0) {
            r = 0;
            D_0063AFD4++;
        }
        break;
    case 4:
        iosMcSaveIconBlock(mc);
        D_0063AFD4++;
        break;
    case 6:
        iosMcSaveProductBlock(mc);
        D_0063AFD4++;
        break;
    case 5:
    case 7:
    case 12:
        debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0063AFE0, (int)mc->name47C);
        if (iosMcSync(mc)) {
            D_0063AFD4++;
        }
        break;
    case 9:
        gamesysMemorySave(D_004DA788, D_004DD700, 0);
        iosMcSaveGameBlock(mc, D_004DD700);
        D_0063AFD4++;
        break;
    default:
        r = 1;
        break;
    }
    if (ret < 0) {
        r = -1;
    }
    if (r) {
        D_0063AFD4 = 0;
    }
    return r;
}
extern int D_0063AFE8;
extern int D_0063AA08;
extern char D_0061BED8[];
extern char D_0063AFF0[];
extern char D_0061BF18[];
extern void iosMcLoadProductBlock(McReq *mc);
extern void iosMcLoadGameBlock(McReq *mc, void *buf);
extern void gamesysMemoryLoad(void *a0, void *a1, int a2);
int debug_mcLoadMainBlock(McReq *mc)
{
    int r = 0;
    int ret = 0;

    switch (D_0063AFE8) {
    case 0:
        *(McName6 *)mc->name47C = *(McName6 *)D_0063AFD8;
        iosMcGetBlockSaveInfo(mc);
        D_0063AFE8++;
        break;
    case 1:
        if (iosMcSync(mc)) {
            D_0063AFE8++;
        }
        break;
    case 2:
    case 6:
    case 10:
        if ((ret = debug_mcRetErrCheck(mc)) != 0) {
            D_0063AFE8++;
        }
        break;
    case 3:
        if (mc->num >= 11) {
            debug_StdPrintfDummy(D_0061BED8);
        }
        r = debug_SelectCsvWindowVal((int)D_0061BE90, 0x50, 0x46, 0xA, 0xA,
                                     (int)&mc->sel,
                                     (int (*)(int, int))debug_saveNumFunc, (int)mc);
        if (r > 0) {
            r = 0;
            D_0063AFE8++;
        }
        break;
    case 4:
        if (((1 << mc->sel) & *(long long *)((char *)mc + 0x9C0)) == 0) {
            D_0063AFE8 = 99;
            break;
        }
        iosMcLoadProductBlock(mc);
        D_0063AFE8++;
        break;
    case 5:
    case 8:
        debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0063AFF0, (int)mc->name47C);
        if (iosMcSync(mc)) {
            D_0063AFE8++;
        }
        break;
    case 7:
        iosMcLoadGameBlock(mc, D_004DD700);
        D_0063AFE8++;
        break;
    case 9:
        gamesysMemoryLoad(D_004DA788, D_004DD700, 0);
        D_0063AA08 = 0;
        D_0063AFE8++;
        break;
    case 99:
        if (debug_mcAsk(D_0061BF18)) {
            D_0063AFE8 = 3;
        }
        break;
    default:
        r = 1;
        break;
    }
    if (ret < 0) {
        r = -1;
    }
    if (r) {
        D_0063AFE8 = 0;
    }
    return r;
}
extern char D_0061C0C0[];
extern char D_0061C0D0[];
extern int D_0063AFF8;
extern int debug_selectFile(McReq *mc);
extern void iosMcDelete(McReq *mc);
extern char *strcpy(char *dst, const char *src);
int debug_mcDeleteFile(McReq *mc)
{
    char buf[0x20];
    int ret = 0;
    int r;

    switch (D_0063AFF8) {
    case 0:
        ret = debug_selectFile(mc);
        if (ret) {
            D_0063AFF8++;
        }
        if (ret > 0) {
            ret = 0;
        }
        break;
    case 1:
        sprintf(buf, D_0061C0C0, mc->dir[mc->sel].name);
        r = debug_mcConfirm(buf);
        if (r > 0) {
            D_0063AFF8++;
        } else if (r < 0) {
            D_0063AFF8 = 0;
        }
        break;
    case 2:
        strcpy(mc->name47C, mc->dir[mc->sel].name);
        iosMcDelete(mc);
        D_0063AFF8++;
        break;
    case 3:
        debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0061C0D0, (int)mc->name47C);
        if (iosMcSync(mc)) {
            D_0063AFF8++;
        }
        break;
    case 4:
        if (debug_mcRetErrCheck(mc)) {
            D_0063AFF8++;
        }
        break;
    default:
        ret = 1;
        break;
    }
    if (ret) {
        D_0063AFF8 = 0;
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_MemoryCard);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SETest);
extern void memset();
extern void strcat();
extern int SgGetSlotStatus(int a0, int slot);
extern char D_0063B050[];
extern char D_0063B058[];
void debug_SESlotDisp(void)
{
    unsigned char mask[6];
    char buf[32];
    char tmp[16];
    int i = 0;
    int k;
    int bit;
    int y;
    int col;
    memset(mask, 0, 6);
    for (; i < 48; i++) {
        if (SgGetSlotStatus(0, i) == 2) {
            mask[i / 8] |= 1 << (i % 8);
        }
    }
    for (k = 0; k < 2; k++) {
        col = 0xFFFFFF00;
        if (k != 0) {
            col = 0xFF000000;
        }
        for (i = 0; i < 48; i++) {
            y = i / 8 * 8 + 100;
            bit = i % 8;
            if (bit == 0) {
                buf[0] = 0;
            }
            if (((mask[i / 8] >> bit) & 1) == k) {
                sprintf(tmp, D_0063B050, i);
            } else {
                sprintf(tmp, D_0063B058);
            }
            strcat(buf, tmp);
            if (bit == 7) {
                debug_PrintfDummy(0x190, y, col, (int)D_0063AF80, (int)buf);
            }
        }
    }
}
extern int D_0070F880[];
extern char D_0063B068[];
extern char D_0063B070[];
extern char D_0055F828[];
extern char D_0061C1D0[];
extern char D_007048C0[];
char *debugCdvdLoadInfoSegDispFunc(int idx, int page)
{
    char buf[0x10];
    int d;
    d = *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8))
      - *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8) + 4);
    if (d < 0) {
        sprintf(buf, D_0063B068, -d);
    } else {
        sprintf(buf, D_0063B070, d);
    }
    sprintf(D_007048C0, D_0061C1D0, D_0055F828 + idx * 0x24,
            *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)),
            *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8) + 4),
            buf);
    return D_007048C0;
}
/* src/debug.c:5364-5376 in the listing: the sibling of debug_ListPadControlGobj
   that lists the actor GObjs the debug menu can print (kinds 1, 2, 4 and 0x2F). */
typedef struct { char *name; void *obj; } DbgGobjEnt;
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *gobj);
extern char D_002C1270[];
static inline int debug_ListActGobj(DbgGobjEnt *list)
{
    void *g;
    int n = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        int kind = ((int *)g)[3];
        switch (kind) {
        case 1:
        case 2:
        case 4:
        case 0x2F:
            list[n].name = kind * 0x64 + D_002C1270;
            list[n].obj = g;
            n++;
        }
    }
    return n;
}
extern char D_0061C210[];
extern int D_0063B080;
extern void _ACTDebugPrint(void *gobj);
int debug_SelectActGobj(int reset)
{
    DbgGobjEnt list[10];
    int n;
    int r;
    n = debug_ListActGobj(list);
    if (reset != 0) {
        D_0063B080 = 0;
    }
    r = debug_SelectCsvWindow(D_0061C210, 0xA, 0x32, 0xB, list, 8, 0, 1, n, &D_0063B080);
    if (D_0063B080 >= 0) {
        _ACTDebugPrint(list[D_0063B080].obj);
    }
    return (r == -1) ? -1 : 0;
}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBox);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_DispBall);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_CollisionTest);
ASM_LIT4_SLOT(D_00639348, 0.001f);
ASM_LIT4_SLOT(D_0063934C, 0.001f);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_Menu);
extern int D_0063B0F4;
void debug_Menu_off(void) {
    D_0063B0F4 = 0;
}
void debug_BeginTimer(int a0) {
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}
extern Blk16 D_0061B7C8;
float debug_GetTimerSec(void) {
    Blk16 buf;
    int v;
    float f2;

    buf = D_0061B7C8;
    if (*(volatile unsigned int *)0x10000810 & 0x800) {
        return -1.0f;
    }
    v = *(volatile int *)0x10000800;
    f2 = (float)(unsigned int)v;
    return f2 / buf.f[*(volatile unsigned int *)0x10000810 & 3] / 60.0f;
}
float debug_GetTimerCount(void) {
    if ((*(volatile int *)0x10000810) & 0x800) {
        return -1.0f;
    }
    return (float)(*(volatile unsigned int *)0x10000800);
}
extern int D_0063AE64;
extern char D_007082D0[];
void debug_ClearFontWindow(void)
{
    char *p = D_007082D0;
    int i;
    p += 0x5B4;
    for (i = 0x1A; i >= 0; i--) {
        *p = 0;
        p -= 0x38;
    }
    D_0063AE64 = 0;
}
extern int D_0063AEB4;
void debug_ResizeFontWindowHeight(int val) {
    D_0063AEB4 = val;
}
/* Profiler bar table: 0x400 entries of 0x1C bytes; D_0063C384 = live count.
   Callers pass (label, colour, __FILE__, __LINE__) -- see the call sites in
   main.c and motionManager2.c, where a3 is literally the caller's line number.
   +0x14 samples the EE timer T0_COUNT at 0x10000000; volatile because it is a
   hardware counter (and the ROM's 32-bit `lw` shows the read is not narrowed). */
extern int D_0063C384;
extern int D_0063B1D4;
extern char D_0063AF30[];
void debug_SetBar(char *name, unsigned int col, char *file, int line)
{
    DebugBar *p = &D_00708880[D_0063C384];
    if (D_0063B1D4 == 0
        && D_0063C384 != 0x400) {
        sprintf(p->name, D_0063AF30, name);
        p->count = *(volatile int *)0x10000000;
        p->col[0] = col >> 24;
        p->col[1] = col >> 16;
        p->col[2] = col >> 8;
        p->col[3] = col;
        p->file = file;
        p->line = line;
        D_0063C384++;
    }
}
/* debug_SetBar with the inverted D_0063B1D4 gate (records only while the
   profiler flag is set). */
void debug_SetBar2(char *name, unsigned int col, char *file, int line)
{
    DebugBar *p = &D_00708880[D_0063C384];
    if (D_0063B1D4 != 0
        && D_0063C384 != 0x400) {
        sprintf(p->name, D_0063AF30, name);
        p->count = *(volatile int *)0x10000000;
        p->col[0] = col >> 24;
        p->col[1] = col >> 16;
        p->col[2] = col >> 8;
        p->col[3] = col;
        p->file = file;
        p->line = line;
        D_0063C384++;
    }
}
extern int D_0063B110;
extern int D_0063B114;
extern int D_0063B118;
extern int D_0063B11C;
extern int D_0063B120;
extern int D_0063B124;
extern int D_0063C384;
void debug_ResetBar(void)
{
    D_0063B120 = 0;
    *(volatile int *)0x10000000 = 0;
    D_0063B11C = 0;
    D_0063B118 = 0;
    D_0063B114 = 0;
    D_0063B110 = 0;
    D_0063B124 = 0;
    D_0063C384 = 0;
}
extern char D_0061BB80[];
void debug_DispVu1IReg(int no)
{
    int i;
    int buf[4];
    if (no >= 0) {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x420));
        __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
        debug_StdPrintfDummy(D_0061BB80, no, buf[0], buf[1], buf[2], buf[3]);
    } else {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x420));
        for (i = 0; i < 16; i++) {
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
            debug_StdPrintfDummy(D_0061BB80, i, buf[0], buf[1], buf[2], buf[3]);
        }
    }
}
extern char D_0061BBA0[];
void debug_DispVu1SReg(int no)
{
    int i;
    int buf[4];
    if (no >= 0) {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x420));
        __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
        debug_StdPrintfDummy(D_0061BBA0, no, buf[0], buf[1], buf[2], buf[3]);
    } else {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x420));
        for (i = 0; i < 16; i++) {
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
            debug_StdPrintfDummy(D_0061BBA0, i, buf[0], buf[1], buf[2], buf[3]);
        }
    }
}
extern void debug_DispQW();
void debug_DispMatrix(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        debug_DispQW(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}
void debug_SetBarDummy(void) {}
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowWithLine);
int debug_TryToGetStartStage(void) {
    return -1;
}
extern int D_0061C580[];
extern int D_0063B100;
extern int D_0063B108[];
extern int D_007049D0[];
extern int sceOpen(void *a0, int a1);
extern void sprintf__pn(void *a0, void *a1, void *a2, int a3) __asm__("sprintf");
int debugSceOpen(int a0, int a1) {
    sprintf__pn(D_007049D0, D_0063B108, D_0061C580, a0);
    return D_0063B100 = sceOpen(D_007049D0, a1);
}
extern int D_0063B100;
extern int sceClose();
int debugSceClose(int a0) {
    if (a0 == D_0063B100) {
        D_0063B100 = -1;
    }
    return sceClose();
}
int debugSceCloseFdNew(void)
{
    int r = 0;
    int h = D_0063B100;
    if (h != -1) {
        D_0063B100 = -1;
        r = sceClose(h);
        D_0063B100 = -1;
    }
    return r;
}
void debug_closeLog(void) {}
extern int D_0070F880[];
void debugCdvdLoadInfoSegInit(int idx)
{
  int *p;
  char *new_var2;
  int new_var;
  int i;
  new_var2 = (char *) D_0070F880;
  p = (int *) ((new_var2 + (idx * 0xD0)) + 0xC8);
  if (1)
  {
    for (i = 0x19; i >= 0; i--)
    {
      new_var = (*p = 0);
      p = (p = (int *) (((char *) p) - 8));
    }

  }
}
void debugCdvdLoadInfoSegAdd(int page, int idx, int delta)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) += delta;
}
void debugCdvdLoadInfoSegCls(int page, int idx)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) = 0;
}
extern int D_0028F4F0[];
extern void gsb_Init();
int gsResetFunc(void)
{
    gsb_Init(D_0028F4F0);
    return 1;
}
extern int D_00639EA0;
void ChangeGirlControlMode(int a0) {
    if (a0 == 1) {
        D_00639EA0 = a0;
    }
}
extern int D_0063AE68;
int debug_CallbackGsFinish(void)
{
    D_0063AE68 = *(volatile int *)0x10000000;
    return 0;
}
extern char D_0061B4A8[];
extern char D_0061B4E8[];
extern char D_0061B500[];
extern char D_0061B538[];
extern char D_0061B570[];
extern char D_0063AE90[];
void debug_SaveStartStageFile(int stage)
{
    char buf[0x100];
    debug_StdPrintfDummy(D_0061B4A8);
    if (debugSceOpen((int)D_0061B4E8, 0x602) < 0) {
        debug_StdPrintfDummy(D_0061B500);
    } else {
        sprintf(buf, D_0063AE90, stage);
        sceWrite(0, buf, strlen(buf));
        debug_StdPrintfDummy(D_0061B538, stage);
        debugSceClose(0);
    }
    debug_StdPrintfDummy(D_0061B570);
    debug_openLog();
}
INCLUDE_ASM("asm/nonmatchings/src/debug", _debug_SelectCsvWindow);
INCLUDE_ASM("asm/nonmatchings/src/debug", debug_SelectCsvWindowWithLineColor);
extern int D_0063AFA0;
extern int D_0063AFA4;
extern char D_0063AFA8[];
extern char D_0061BCA8[];
extern void iosMcFormat(int port);
extern int iosMcSync(int port);
int debug_mcFormat(int port)
{
    int r;
    switch (D_0063AFA0) {
    case 0:
        r = debug_mcConfirm(D_0063AFA8);
        if (r != 1) {
            return r;
        }
        iosMcFormat(port);
        D_0063AFA0++;
        break;
    case 1:
        if (D_0063AFA4++ & 0x10) {
            debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0061BCA8);
        }
        if (iosMcSync(port) != 0) {
            D_0063AFA0++;
        }
        break;
    default:
        D_0063AFA0 = 0;
        return 1;
    }
    return 0;
}
extern int D_0063AFB0;
extern int D_0063AFB4;
extern char D_0061BCB8[];
extern char D_0061BCC8[];
extern void iosMcUnformat(int port);
int debug_mcUnformat(int port)
{
    int r;
    switch (D_0063AFB0) {
    case 0:
        r = debug_mcConfirm(D_0061BCB8);
        if (r != 1) {
            return r;
        }
        iosMcUnformat(port);
        D_0063AFB0++;
        break;
    case 1:
        if (D_0063AFB4++ & 0x10) {
            debug_PrintfDummy(0x78, 0x46, 0xFFFFFF00u, (int)D_0061BCC8);
        }
        if (iosMcSync(port) != 0) {
            D_0063AFB0++;
        }
        break;
    default:
        D_0063AFB0 = 0;
        return 1;
    }
    return 0;
}
extern char D_0063AFC8[];
extern char D_0063AFD0[];
void *debug_saveNumFunc(int a0, void *a1) {
    if ((1 << a0) & *(long long *)((char *)a1 + 0x9C0)) {
        return D_0063AFC8;
    }
    return D_0063AFD0;
}
extern void iosMcTest(void);
int debug_mcTest(void) {
    iosMcTest();
    return 1;
}
extern void staffRollStart(int a0, float a1);
int debug_STAFFROLLTest(void) {
    staffRollStart(0x80, 1.0f);
    return 1;
}
extern unsigned short D_0030C4E0[];
extern GsysObjInfo D_005D6DB0[];
int debug_SETest_color(int idx)
{
  int new_var;
  int v3 = D_005D6DB0[idx].f_20;
  unsigned short a4 = *((unsigned short *) (((char *) D_0030C4E0) + (v3 * 2)));
  int v0 = 0x80808000;
  int a3 = -0x100;
  if (new_var = a4 != 0)
  {
    v0 = a3;
  }
  return v0;
}
extern int soundReverbDepthGet(void);
extern void soundReverbDepthSet(int depth);
/* pad state block: +0x4 held buttons, +0xC newly-pressed (trigger) buttons */
typedef struct { int _0; int hold; int _8; int trg; } DbgReverbPad;
extern DbgReverbPad D_0028F8F0[];
extern char D_0061C1A8[];
int debug_reverbTest(void)
{
    int depth = soundReverbDepthGet();
    if (D_0028F8F0[0].trg & 0x1000) {
        if (depth <= 99) {
            depth++;
        }
    }
    if (D_0028F8F0[0].trg & 0x4000) {
        depth -= (0 < depth);
    }
    soundReverbDepthSet(depth);
    debug_PrintfDummy(10, 0x50, 0xFFFFFF00u, (int)D_0061C1A8, soundReverbDepthGet());
    return (D_0028F8F0[0].hold & 0x60) != 0;
}
extern int D_0063B060;
extern int D_0063B05C;
extern char D_0061C1C0[];
extern char D_00559D50[];
int debug_AdpcmTest(int a0) {
    int r;
    if (a0 != 0) {
        D_0063B060 = -1;
    }
    r = debug_SelectCsvWindow(D_0061C1C0, 10, 0x3C, 10, D_00559D50, 0x40, 0, 0, 0x69, &D_0063B05C);
    if (r > 0) {
        if (D_0063B05C != 0) {
            scpAdpcmPlayRequestFunc(D_0063B05C, 0, 1, 1, 1);
        }
    }
    return r;
}
typedef struct { char s[20]; } DbgTitle20;
typedef struct { long long a; long long b; unsigned short c; unsigned char d; } DbgTitle19;
extern DbgTitle20 D_0061C1E0;
extern DbgTitle19 D_0061C1F8;
extern int D_0063B078;
extern int D_0063B07C;
int debugCdvdLoadInfoSegDisp(void)
{
    char title[0x20];
    int r;
    *(DbgTitle20 *)title = D_0061C1E0;
    if (D_0063B078 != 0) {
        DbgTitle19 *t = (DbgTitle19 *)title;
        t->a = D_0061C1F8.a;
        t->b = D_0061C1F8.b;
        t->c = D_0061C1F8.c;
        t->d = D_0061C1F8.d;
    }
    r = debug_SelectCsvWindowVal((int)title, 0x50, 0x46, 0xA, 0x1A, (int)&D_0063B07C,
                                 (int (*)(int, int))debugCdvdLoadInfoSegDispFunc, D_0063B078);
    if (D_0028F8F4[0] & 0x10) {
        int i;
        int *p = (int *)((char *)D_0070F880 + D_0063B078 * 0xD0);
        for (i = 0x19; i >= 0; i--) {
            p[1] = p[0];
            p += 2;
        }
    }
    return r;
}
int debug_GameOver(void) {
    debug_Menu_off();
    return -1;
}
int debug_EndingDemo(void) {
    debug_Menu_off();
    return -1;
}
extern void backStageProcessInStage(float a0);
int debug_BackStageTest(void) {
    backStageProcessInStage(10000000.0f);
    return 1;
}
extern void backStageDebugTimeZero(void);
int debug_tsuresariTimeZero(void) {
    backStageDebugTimeZero();
    return 1;
}
extern void *isysGObjGetExist_begin(void);
extern void *isysGObjGetExist_next(void *gobj);
extern int IsTopHint(void *gobj);
extern void DebugHintStart(void *gobj);
int debug_hintStart(void)
{
    void *gobj;
    for (gobj = isysGObjGetExist_begin(); gobj != 0; gobj = isysGObjGetExist_next(gobj)) {
        if (IsTopHint(gobj)) {
            DebugHintStart(gobj);
            break;
        }
    }
    return 1;
}
/* src/debug.c:5380-5397 in the listing: a static helper that builds the
   {name, gobj} list of the pad-controllable objects (kind 2 = boy, 4 = girl). */
static inline int debug_ListPadControlGobj(DbgGobjEnt *list)
{
    void *g;
    int n = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        int kind = ((int *)g)[3];
        if (kind == 2 || kind == 4) {
            list[n].obj = g;
            list[n].name = kind * 0x64 + D_002C1270;
            n++;
        }
    }
    return n;
}
extern int D_0063B084;
extern void *D_00639ED0;
extern char D_0061C228[];
int debug_SelectPad2ControlGobj(int reset)
{
    DbgGobjEnt list[10];
    int n;
    int r;
    n = debug_ListPadControlGobj(list);
    if (reset != 0) {
        D_0063B084 = 0;
    }
    r = debug_SelectCsvWindow(D_0061C228, 0xA, 0x32, 0xB, list, 8, 0, 1, n, &D_0063B084);
    if (r > 0) {
        D_00639ED0 = list[D_0063B084].obj;
        return 1;
    }
    return (r == -1) ? -1 : 0;
}
extern void CameraSetMode(int x);
extern int D_0028F8F4[];
int debug_FreeCamera(int a0)
{
    if (a0 != 0) {
        CameraSetMode(1);
    }
    CameraSetMode(1);
    return (D_0028F8F4[0] & 0x100) ? -1 : 0;
}
