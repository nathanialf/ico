/*
 * ico2/seki/include/GifPacket.h
 *
 * The declarations of what GifPacket.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GIFPACKET_H
#define GIFPACKET_H

/* the colour gif_DrawStripF and gif_DrawStripFST take by value, four bytes;
 * weapon.c's dispBlur and puddle.c's drawRipple build it at their call
 * sites. */
typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GifColor; /* derived name */

int _IsInScreen(volatile int *a0);
int gif_CheckOpen(void);
void gif_Draw2DStripG(int *v, GifColor *col, int n, int prim);
void gif_DrawPolyF4(void *p0, void *p1, void *p2, void *p3, int r, int g, int b, int a, int prim);
void gif_DrawStripF(void *p, GifColor c, int n, int f);
void gif_DrawStripFST(void *a, void *b, GifColor col, int n, int e);
void gif_EndPacket(void);
void gif_EndPacketPath1(void);
void gif_Init(void);
void gif_Line(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim);
void gif_MakeLine2D(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim);
void gif_PointOffset(int *v, long long z, unsigned char *col, int prim);
void gif_SetAlpha(long long a0, long long a1, long long a2);

void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                           unsigned int h, int useoffset, int clear);

void gif_SetGsReg(long long a0, long long a1);
void gif_SetZTest(int a0);
void gif_SetZWrite(int a0);
void gif_Sprite(int *r, long long z, int *uv, unsigned char *col, int prim);
void gif_SpriteSensitive(int *r, long long z, int *uv, unsigned char *col, int prim);
void gif_SpriteSensitiveOffset(int *r, long long z, int *uv, unsigned char *col, int prim);
void gif_SpriteSensitiveOrg(int *r, long long z, int *uv, unsigned char *col, int prim);
void gif_StartPacketPri(int pri);
void gif_StartPacketPriPath1(int pri);
void gif_MakeSpriteNoTexture(int x, int y, int w, int h, long long z, unsigned char *col, int prim);

#endif /* GIFPACKET_H */
