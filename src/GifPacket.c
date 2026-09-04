#include "common.h"

typedef struct { int a, b, c, d; } GsAlphaEnt;
typedef struct { unsigned char pad[0x10]; unsigned long long *cur; } GsBaseRed;

typedef struct { char _pad[0x10]; long long *cur; } GifBuf;

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_StartPacket);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_EndPacket);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_StartPacketPath1);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_EndPacketPath1);
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
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SetDrawEnviroment);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawPolyF4);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripF);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripFST);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripG);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Draw2DStripG);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Draw2DUVStripG);
extern int D_00639F60;

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
extern GifBuf D_004EE6F0;

void gif_SetGsReg(long long a0, long long a1) {
    *D_004EE6F0.cur++ = a1;
    *D_004EE6F0.cur++ = a0;
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
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_LineOffset);
extern GsBaseRed D_004EE6F0__pn __asm__("D_004EE6F0");
extern GsAlphaEnt D_0054E0B0[];

void gif_SetAlpha(long long a0, long long a1, long long a2) {
    unsigned long long *p, *q;
    unsigned long long v;
    int idx;

    idx = (int)a1;
    p = D_004EE6F0__pn.cur;
    *(volatile unsigned long long *)p = (a0 == 0);
    p++;
    *(unsigned long long * volatile *)&D_004EE6F0__pn.cur = p;
    *(volatile unsigned long long *)p = 0x49;
    *(unsigned long long * volatile *)&D_004EE6F0__pn.cur = p + 1;
    a1 = 0x42;
    v = (unsigned long long)D_0054E0B0[idx].a | ((unsigned long long)a2 << 32);
    v |= ((unsigned long long)D_0054E0B0[idx].c << 4)
       | ((unsigned long long)D_0054E0B0[idx].b << 2);
    v |= (unsigned long long)D_0054E0B0[idx].d << 6;
    *(volatile unsigned long long *)(p + 1) = v;
    *(unsigned long long * volatile *)&D_004EE6F0__pn.cur = p + 2;
    q = p + 3;
    *(volatile unsigned long long *)(p + 2) = a1;
    D_004EE6F0__pn.cur = q;
}
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MoveImage);
void gif_SetZTest(int a0) {
    int new_var;
    unsigned long long *p, *q;
    if (a0) {
        a0 = 0x50000;
        new_var = 0; do { } while (new_var);
    } else {
        a0 = 0x30000;
    }
    p = D_004EE6F0__pn.cur;
    *(volatile unsigned long long *)p = a0;
    p++;
    *(unsigned long long * volatile *)&D_004EE6F0__pn.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x47;
    D_004EE6F0__pn.cur = q;
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
    p = D_004EE6F0__pn.cur;
    *(volatile unsigned long long *)p = tag;
    p++;
    *(unsigned long long * volatile *)&D_004EE6F0__pn.cur = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x4E;
    D_004EE6F0__pn.cur = q;
}
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SetHalfOffset);
int _IsInScreen(volatile int *a0) {
    if (a0[2] < 0) return 0;
    if (a0[2] > 0x0FFFFFF0) return 0;
    if (a0[0] < 0) return 0;
    if (a0[0] > 0xFFF0) return 0;
    if (a0[1] < 0) return 0;
    return a0[1] <= 0xFFF0;
}
