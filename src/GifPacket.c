#include "common.h"

typedef struct { int a, b, c, d; } GsAlphaEnt;

/* The display-list packet builder state.  `ptr` is the write cursor; `dma`,
   `tail`, `gif` and `end` are the back-pointers into the packet that
   gif_EndPacket patches once the packet's size is known (DMA tag, source
   chain tail, VIF DIRECT code and GIF tag respectively). */
typedef struct {
    int cur;
    int *buf[2];
    char *dma;
    unsigned long long *ptr;
    char *tail;
    char *gif;
    char *end;
} GifDpk;
extern GifDpk D_004EE6F0;
/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMA tag, GIF tag, A+D data) or as one of its two 32-bit halves. */
typedef union {
    long long d;
    int w[2];
} GifPkWord;
/* INTERIM (same construct as getSkeltonFocusNode in src/motionManager2.c):
   the listing inlines gif_SetGsReg (body line 233, parameter line 224) into
   most of this TU, so it is `inline` in the dev's TU; while this tail still
   has asm members a deferred inline would be emitted at the object end
   instead of at its ROM slot, so the public body stays a plain definition
   there and every C caller the listing shows inlining it calls this static
   stand-in.  Collapses to one `inline` definition at layout. */
static inline void setGsReg(long long a0, long long a1) {
    *D_004EE6F0.ptr++ = a1;
    *D_004EE6F0.ptr++ = a0;
}

void gif_StartPacket(void)
{
    char *c;

    c = (char *)D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.end = 0;
    D_004EE6F0.dma = c;
    D_004EE6F0.tail = c;
    D_004EE6F0.ptr = (unsigned long long *)(c + 8);
    ((GifPkWord *)(c + 8))->w[0] = 0x11000000;
    D_004EE6F0.gif = c + 0xC;
    D_004EE6F0.end = c + 0x10;
    D_004EE6F0.ptr = (unsigned long long *)(c + 0x18);
    ((GifPkWord *)(c + 0x18))->d = 0xE;
    D_004EE6F0.ptr = (unsigned long long *)(c + 0x20);
}
extern int D_00639F60;
extern void dl_OpenDma(int chan, void *dma, int flag);
extern void dl_CloseDma(void);

void gif_EndPacket(void)
{
    char *p;

    ((GifPkWord *)D_004EE6F0.end)->d =
        (unsigned int)(((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.end) >> 4) - 1)
        | 0x1000000000008000LL;
    ((GifPkWord *)D_004EE6F0.gif)->w[0] =
        ((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.gif) >> 4) | 0x50000000;
    ((GifPkWord *)D_004EE6F0.tail)->d =
        (unsigned int)((((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.tail) >> 4) - 1)
                       | 0x10000000);
    p = (char *)D_004EE6F0.ptr;
    D_004EE6F0.tail = p;
    ((GifPkWord *)p)->d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)(p + 8);
    ((GifPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 0xC);
    ((GifPkWord *)(p + 8))->w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 0x10);
    dl_OpenDma(5, D_004EE6F0.dma, 0);
    dl_CloseDma();
    D_00639F60 = 0;
}
void gif_StartPacketPath1(void)
{
    char *c;

    c = (char *)D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.end = 0;
    D_004EE6F0.dma = c;
    D_004EE6F0.tail = c;
    D_004EE6F0.ptr = (unsigned long long *)(c + 8);
    ((GifPkWord *)(c + 8))->w[0] = 0x11000000;
    D_004EE6F0.gif = c + 0xC;
    D_004EE6F0.end = c + 0x10;
    D_004EE6F0.ptr = (unsigned long long *)(c + 0x18);
    ((GifPkWord *)(c + 0x18))->d = 0xE;
    D_004EE6F0.ptr = (unsigned long long *)(c + 0x20);
}
void gif_EndPacketPath1(void)
{
    char *p;
    char *q;

    ((GifPkWord *)D_004EE6F0.end)->d =
        (unsigned int)(((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.end) >> 4) - 1)
        | 0x1000000000008000LL;
    ((GifPkWord *)D_004EE6F0.gif)->w[0] =
        (((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.gif) >> 4) << 16) | 0x6C008000;
    p = (char *)D_004EE6F0.ptr;
    ((GifPkWord *)p)->w[0] = 0x15000000;
    p += 4;
    D_004EE6F0.ptr = (unsigned long long *)p;
    ((GifPkWord *)p)->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    ((GifPkWord *)(p + 4))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 8);
    ((GifPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 0xC);
    ((GifPkWord *)D_004EE6F0.tail)->d =
        (unsigned int)((((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.tail) >> 4) - 1)
                       | 0x10000000);
    q = (char *)D_004EE6F0.ptr;
    D_004EE6F0.tail = q;
    ((GifPkWord *)q)->d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)(q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0x10);
    dl_OpenDma(5, D_004EE6F0.dma, 0);
    dl_CloseDma();
    D_00639F60 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeLine2DOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSprite);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSpriteOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSpriteWithStrip);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_PointOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Line);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Sprite);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SpriteSensitive);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SpriteOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SpriteSensitiveOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SpriteOrg);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SpriteSensitiveOrg);
extern int D_0063A074;
extern int D_0063A078;

void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm,
                           unsigned int w, unsigned int h, int useoffset, int clear)
{

    setGsReg(0x4C, (fbp >> 5) | ((unsigned long long)((w >> 6) & 0x3F) << 16)
                   | ((psm & 0xF) << 24));
    setGsReg(0x40, ((unsigned long long)(w - 1) << 16)
                   | ((unsigned long long)(h - 1) << 48));
    if (clear) {
        setGsReg(0x47, 0x30000);
        setGsReg(0x00, 6);
        setGsReg(0x01, 0xFE00LL << 46);
        setGsReg(0x05, 0);
        setGsReg(0x05, (unsigned long long)(w << 4)
                       | ((unsigned long long)(h << 4) << 16));
        setGsReg(0x47, 0x50000);
    }
    if (useoffset) {
        setGsReg(0x18, (unsigned long long)(unsigned int)(((0x800 - (w >> 1)) << 4) + D_0063A074)
                       | ((unsigned long long)(((0x800 - (h >> 1)) << 4) + D_0063A078) << 32));
    } else {
        setGsReg(0x18, (unsigned long long)(unsigned int)((0x800 - (w >> 1)) << 4)
                       | ((unsigned long long)((0x800 - (h >> 1)) << 4) << 32));
    }
}
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawPolyF4);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripF);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripFST);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripG);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Draw2DStripG);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Draw2DUVStripG);
void gif_Init(void) {
    D_00639F60 = 0;
}
extern void dl_SetDLPriority();
extern void gif_StartPacket();

void gif_StartPacketPri(void)
{
    dl_SetDLPriority();
    gif_StartPacket();
    D_00639F60 = 1;
}
extern void gif_StartPacketPath1(void);

void gif_StartPacketPriPath1(void)
{
    dl_SetDLPriority();
    gif_StartPacketPath1();
    D_00639F60 = 1;
}

void gif_SetGsReg(long long a0, long long a1) {
    *D_004EE6F0.ptr++ = a1;
    *D_004EE6F0.ptr++ = a0;
}
int gif_CheckOpen(void) {
    return D_00639F60;
}
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakePoint2D);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakePoint2DOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeLine2D);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSpriteNoTexture);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSpriteNoTextureOffset);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Point);
extern int D_0063A064;
extern int D_0063A068;
extern void gif_MakeLine2DOffset(int *v0, int *v1, long long z0, long long z1,
                                 unsigned char *col, long long prim);

void gif_LineOffset(int *v0, int *v1, long long z0, long long z1,
                    unsigned char *col, long long prim)
{
    int p0[4];
    int p1[4];

    p0[0] = v0[0] * D_0063A064 / 640 * 16;
    p0[1] = v0[1] * D_0063A068 / 224 * 16;
    p1[0] = v1[0] * D_0063A064 / 640 * 16;
    p1[1] = v1[1] * D_0063A068 / 224 * 16;
    gif_MakeLine2DOffset(p0, p1, z0, z1, col, prim);
}
/* .rodata — carved VMA 0x54E0B0..0x54E170; the 12 ALPHA_1/2 blend-parameter
   quadruples gif_SetAlpha packs into the GS ALPHA register, bytes verified
   against baserom/pal/baseelf.rom */
const GsAlphaEnt D_0054E0B0[12] = {
    { 0, 2, 2, 1 }, { 2, 0, 2, 1 }, { 0, 1, 2, 1 }, { 1, 2, 2, 0 },
    { 0, 1, 0, 1 }, { 0, 2, 0, 1 }, { 2, 0, 0, 1 }, { 0, 1, 0, 1 },
    { 0, 2, 1, 1 }, { 2, 0, 1, 1 }, { 0, 1, 1, 1 }, { 1, 2, 0, 1 },
};

void gif_SetAlpha(long long a0, long long a1, long long a2) {
    unsigned long long *p, *q;
    unsigned long long v;
    int idx;

    idx = (int)a1;
    p = D_004EE6F0.ptr;
    *(volatile unsigned long long *)p = (a0 == 0);
    p++;
    *(unsigned long long * volatile *)&D_004EE6F0.ptr = p;
    *(volatile unsigned long long *)p = 0x49;
    *(unsigned long long * volatile *)&D_004EE6F0.ptr = p + 1;
    a1 = 0x42;
    v = (unsigned long long)D_0054E0B0[idx].a | ((unsigned long long)a2 << 32);
    v |= ((unsigned long long)D_0054E0B0[idx].c << 4)
       | ((unsigned long long)D_0054E0B0[idx].b << 2);
    v |= (unsigned long long)D_0054E0B0[idx].d << 6;
    *(volatile unsigned long long *)(p + 1) = v;
    *(unsigned long long * volatile *)&D_004EE6F0.ptr = p + 2;
    q = p + 3;
    *(volatile unsigned long long *)(p + 2) = a1;
    D_004EE6F0.ptr = q;
}
void gif_MoveImage(long long sbp, long long sbw, long long psm, int *rect,
                   long long dbp, long long dbw, long long dsax, long long dsay)
{
    setGsReg(0x50, (psm << 56) | (dbw << 48) | (dbp << 32) | (psm << 24)
                   | (sbw << 16) | sbp);
    setGsReg(0x51, (dsay << 48) | (rect[1] << 16) | (dsax << 32) | rect[0]);
    setGsReg(0x52, ((long long)rect[3] << 32) | rect[2]);
    setGsReg(0x53, 2);
}
void gif_SetZTest(int a0) {
    int new_var;
    unsigned long long *p, *q;
    if (a0) {
        a0 = 0x50000;
        new_var = 0; do { } while (new_var);
    } else {
        a0 = 0x30000;
    }
    p = D_004EE6F0.ptr;
    *(volatile unsigned long long *)p = a0;
    p++;
    *(unsigned long long * volatile *)&D_004EE6F0.ptr = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x47;
    D_004EE6F0.ptr = q;
}
void gif_SetZWrite(int a0) {
    unsigned long long *p, *q;
    int new_var;
    unsigned long long tag;
    if (a0) {
        tag = 0x300000C0;
        new_var = 0; do { } while (new_var);
    } else {
        tag = 0x1300000C0;
    }
    p = D_004EE6F0.ptr;
    *(volatile unsigned long long *)p = tag;
    p++;
    *(unsigned long long * volatile *)&D_004EE6F0.ptr = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x4E;
    D_004EE6F0.ptr = q;
}
void gif_SetHalfOffset(void)
{
    setGsReg(0x18,
             (long long)(((0x800 - D_0063A064 / 2) << 4) + D_0063A074)
             | ((long long)(((0x800 - D_0063A068 / 2) << 4) + D_0063A078) << 32));
}
int _IsInScreen(volatile int *a0) {
    if (a0[2] < 0) return 0;
    if (a0[2] > 0x0FFFFFF0) return 0;
    if (a0[0] < 0) return 0;
    if (a0[0] > 0xFFF0) return 0;
    if (a0[1] < 0) return 0;
    return a0[1] <= 0xFFF0;
}
