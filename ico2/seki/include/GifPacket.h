/*
 * ico2/seki/include/GifPacket.h
 *
 * The declarations of what GifPacket.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GIFPACKET_H
#define GIFPACKET_H

/* a colour, four bytes in RGBA order: gif_DrawStripF and gif_DrawStripFST
 * take it by value, the sprite family and gif_Draw2DStripG by address;
 * weapon.c's dispBlur and puddle.c's drawRipple build it at their call
 * sites. */
typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GifColor; /* derived name */

/* a sprite's rectangle, a corner and a size, for the screen and for the
 * texture: the Sensitive forms take both in the GS's 1/16 units, the others
 * in whole pixels and texels, and the forms without Org scale the screen
 * rectangle from a 640 by 224 screen */
typedef struct { /* field names derived */
    int x;
    int y;
    int w;
    int h;
} GifRect; /* derived name */

int _IsInScreen(volatile int *v);
int gif_CheckOpen(void);
void gif_Draw2DStripG(int *v, GifColor *col, int n, int prim);
void gif_DrawPolyF4(void *p0, void *p1, void *p2, void *p3, int r, int g, int b, int a, int prim);
void gif_DrawStripF(void *v, GifColor col, int n, int prim);
void gif_DrawStripFST(void *v, void *uv, GifColor col, int n, int prim);
void gif_EndPacket(void);
void gif_EndPacketPath1(void);
void gif_Init(void);
void gif_Line(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim);
void gif_MakeLine2D(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim);
void gif_PointOffset(int *v, long long z, unsigned char *col, int prim);
void gif_SetAlpha(long long alpha, long long mode, long long fix);

void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                           unsigned int h, int useoffset, int clear);

void gif_SetGsReg(long long reg, long long data);
void gif_SetZTest(int on);
void gif_SetZWrite(int on);
void gif_Sprite(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim);
void gif_SpriteSensitive(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim);
void gif_SpriteSensitiveOffset(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim);
void gif_SpriteSensitiveOrg(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim);
void gif_StartPacketPri(int pri);
void gif_StartPacketPriPath1(int pri);
void gif_MakeSpriteNoTexture(int x, int y, int w, int h, long long z, GifColor *col, int prim);

#endif /* GIFPACKET_H */
