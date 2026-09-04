#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_StartPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_EndPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_StartPacketPath1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_SpriteOrg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeLine2DOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeSprite);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_DrawPolyF4);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_DrawStripF);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_DrawStripG);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Draw2DStripG);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Draw2DUVStripG);

extern int D_00629EA0;

void gif_SpriteSensitive(void) {
    D_00629EA0 = 0;
}

extern void dpk_SwapBuffer(void);
extern void func_0010F978(void);

void gif_SpriteOffset(void) {
    dpk_SwapBuffer();
    func_0010F978();
    D_00629EA0 = 1;
}

extern void func_0010FAB0(void);

void gif_SpriteSensitiveOffset(void) {
    dpk_SwapBuffer();
    func_0010FAB0();
    D_00629EA0 = 1;
}

typedef struct { char _pad[0x10]; long long *cur; } GifBuf;
extern GifBuf D_004C3850;

void gif_SetGsReg(long long a0, long long a1) {
    *D_004C3850.cur++ = a1;
    *D_004C3850.cur++ = a0;
}

int gif_SpriteSensitiveOrg(void) {
    return D_00629EA0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakePoint2D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakePoint2DOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeLine2D);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeSpriteNoTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeSpriteNoTextureOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Point);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_LineOffset);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
} S_004C3850;  /* stride 0x4 */

/* end struct shapes */
