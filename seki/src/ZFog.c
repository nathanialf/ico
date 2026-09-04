#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", fog_MakeFogClut);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", fog_DrawFog);

int fog_FogTool(int a0)
{
    int ret = -1;
    int i;
    for (i = 0; i < 11; i++)
    {
        if ((1 << i) >= a0)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

extern int tex_scrollClut(void);

int func_0012FC08(void) {
    return tex_scrollClut();
}

extern int tex_textureAnimation(void *a0, int a1);

int func_0012FC28(void *a0) {
    return tex_textureAnimation(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", tex_GetTextureNo);

extern unsigned char D_0067AE50[];

void *func_0012FCE0(int a0) {
    return &D_0067AE50[a0 * 0x2E8];
}

void *func_0012FCF8(int a0) {
    return &D_0067AE50[a0 * 0x2E8];
}

void tex_SetSamplingType(void *a0, int a1, int a2) {
    long v = *(long *)((char *)a0 + 0x78);
    *(long *)((char *)a0 + 0x78) = (a2 << 6) | ((a1 << 5) | (v & -0xE1));
}

extern unsigned char D_0067B0B8[];

void *func_0012FD38(int a0) {
    return &D_0067B0B8[a0 * 0x2E8];
}

extern unsigned char D_0067ADF8[];

short tex_GetVramFreeAddress(int a0) {
    return *(short *)(D_0067ADF8 + a0 * 6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FD70);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FE30);

extern int D_0062BF68;

int func_0012FEC0(void) {
    return D_0062BF68;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", tex_SetUVScroll);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", tex_Init);


/* recovered struct shapes */
typedef struct {
    unsigned short     f_E0;  /* 0xE0 */
    unsigned int       f_E4;  /* 0xE4 */
    unsigned int       f_20C;  /* 0x20C */
    unsigned char      f_21A;  /* 0x21A */
    unsigned char      f_21B;  /* 0x21B */
    unsigned short     f_21C;  /* 0x21C */
    unsigned short     f_21E;  /* 0x21E */
    unsigned int       f_2A8;  /* 0x2A8 */
    unsigned int       f_2AC;  /* 0x2AC */
    unsigned int       f_2B0;  /* 0x2B0 */
    unsigned int       f_2B4;  /* 0x2B4 */
    short              f_2B8;  /* 0x2B8 */
    short              f_2BA;  /* 0x2BA */
    unsigned int       f_2BC;  /* 0x2BC */
    unsigned int       f_2C0;  /* 0x2C0 */
    unsigned int       f_2C4;  /* 0x2C4 */
    unsigned short     f_2D6;  /* 0x2D6 */
    unsigned long long f_2D8;  /* 0x2D8 */
} S_0067AE50;  /* stride 0x2E8 */

typedef struct {
    unsigned short     f_E8;  /* 0xE8 */
    unsigned int       f_2B0;  /* 0x2B0 */
    unsigned long long f_2D8;  /* 0x2D8 */
    unsigned short     f_2DE;  /* 0x2DE */
    short              f_2E0;  /* 0x2E0 */
} S_0067AE48;  /* stride 0x2E8 */

/* end struct shapes */
