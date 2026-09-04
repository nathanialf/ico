#include "common.h"

typedef struct { char _pad[0x10]; long long *cur; } GifBuf;




extern void func_0010F710(void);
extern void dpk_SwapBuffer();
extern void func_0010F5D8();
extern int D_00631BA0;
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_StartPacket);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_EndPacket);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_StartPacketPath1);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_SpriteOrg);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeLine2DOffset);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSprite);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawPolyF4);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripF);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripG);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Draw2DStripG);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Draw2DUVStripG);

void gif_SpriteSensitive(void) {
    D_00631BA0 = 0;
}

void gif_SpriteOffset(void)
{
    dpk_SwapBuffer();
    func_0010F5D8();
    D_00631BA0 = 1;
}

void gif_SpriteSensitiveOffset(void)
{
    dpk_SwapBuffer();
    func_0010F710();
    D_00631BA0 = 1;
}

extern GifBuf D_004C7710;

void gif_SetGsReg(long long a0, long long a1) {
    *D_004C7710.cur++ = a1;
    *D_004C7710.cur++ = a0;
}

int gif_SpriteSensitiveOrg(void) {
    return D_00631BA0;
}

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakePoint2D);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakePoint2DOffset);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeLine2D);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSpriteNoTexture);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_MakeSpriteNoTextureOffset);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_Point);

INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_LineOffset);

