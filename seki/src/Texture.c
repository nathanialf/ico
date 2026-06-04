#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_AllocVramAuto);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_loadImage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_setTexReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transVramClutTex);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transVramDirectTex);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transRegister);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_transTM2);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_initClutTexture);

extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);

void tex_setRegisters(void *a0) {
    dpk_Init(2, (char *)a0 + 0x58, 5);
    dl_GetPri();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_initTM2);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_convertClutCSM2ToCSM1);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_convertImage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_makeCopyImage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_makeTexturePacket);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_initTextureSub);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_LoadTexturePart);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_TransTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_scrollClut);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_textureAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_SetClutAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_FreeTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_ResetVram);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_dispClut);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_printTexture);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_Tool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_ListTool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Texture", tex_GetTWTH);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
    short              f_2;  /* 0x02 */
    short              f_4;  /* 0x04 */
} S_0067ADF8;  /* stride 0x6 */

typedef struct {
    short              f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_002725D8;  /* stride 0xC */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_002725B8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00272620;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005502D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00550480;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00550570;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00550660;  /* stride 0x4 */

/* end struct shapes */
