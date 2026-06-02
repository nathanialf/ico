#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_StartPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_EndPacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_StartPacketPath1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_EndPacketPath1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeLine2DOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeSprite);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeSpriteOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_MakeSpriteWithStrip);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_PointOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Line);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Sprite);

extern int D_00629EA0;

void gif_SpriteSensitive(void) {
    D_00629EA0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_SpriteOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_SpriteSensitiveOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_SpriteOrg);

int gif_SpriteSensitiveOrg(void) {
    return D_00629EA0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_SetDrawEnviroment);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_DrawPolyF4);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_DrawStripF);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_DrawStripG);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Draw2DStripG);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Draw2DUVStripG);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GifPacket", gif_Init);
