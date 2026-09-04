#include "common.h"

typedef struct CdvdRec {
    char pad0[0x78];
    long long x78;
    char pad80[0x290 - 0x80];
    int x290;
    int x294;
    char pad298[0x2A8 - 0x298];
    int x2A8;
    char pad2AC[0x2E8 - 0x2AC];
} CdvdRec;

INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_AllocVramAuto);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_loadImage);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_setTexReg);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transVramClutTex);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transVramDirectTex);
extern void dl_CloseDma();
extern void dl_OpenDma();

void tex_transRegister(int a0)
{
    dl_OpenDma(2, a0 + 0x58, 5);
    dl_CloseDma();
}
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_transTM2);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initClutTexture);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_setRegisters);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initTM2);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_convertClutCSM2ToCSM1);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_convertImage);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_makeCopyImage);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_makeTexturePacket);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_initTextureSub);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_LoadTexturePart);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_TransTexture);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_TransTextureDefocus);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_scrollClut);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_textureAnimation);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_SetClutAnimation);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_FreeTexture);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ResetVram);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_dispClut);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_printTexture);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_Tool);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ListTool);
int tex_GetTWTH(int a0)
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
extern int tex_initTextureSub();

int tex_InitTexture(void)
{
    return tex_initTextureSub();
}
extern int tex_LoadTexturePart(void *a0, int a1);

int tex_LoadTexture(void *a0)
{
    return tex_LoadTexturePart(a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_GetTextureNo);
extern int D_0068AFE0__pn[] __asm__("D_0068AFE0");

int *tex_GetTextureData(int idx)
{
    return (int *)((char *)D_0068AFE0__pn + idx * 0x2E8);
}
int *tex_GetTextureName(int idx)
{
    return (int *)((char *)D_0068AFE0__pn + idx * 0x2E8);
}
void tex_SetSamplingType(int *a0, int a1, int a2)
{
    long long *slot = (long long *)((char *)a0 + 0x78);
    *slot = (*slot & ~(long long)0xE0) | (a1 << 5) | (a2 << 6);
}
extern int D_0068B248[];

int *tex_GetTexExtData(int idx)
{
    return (int *)((char *)D_0068B248 + idx * 0x2E8);
}
extern short D_0068AF88[];

short tex_GetVramFreeAddress(int a0)
{
    return *(short *)((char *)D_0068AF88 + a0 * 6);
}
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_UpdateMipMapLevel);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_LockHeadTBP);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_UnlockHeadTBP);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_ResetVramPri);
extern int D_0063C164;

int tex_GetTextureNum(void) {
    return D_0063C164;
}
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_SetUVScroll);
INCLUDE_ASM("asm/nonmatchings/src/Texture", tex_Init);
extern int D_0028F720[];
extern int D_0063C164;
extern CdvdRec D_0068AFE0[];

int tex_RemakeRegistersSampleMin(void) {
    int count = D_0063C164;
    int i;
    for (i = 0; i < count; i++) {
        CdvdRec *b = &D_0068AFE0[i];
        int f5 = D_0028F720[57];
        int f8 = 1;
        if (b->x2A8 != 0) {
            f8 = b->x290;
            f5 = b->x294;
        }
        b->x78 = (b->x78 & ~0xE0) | (f8 << 5) | (f5 << 6);
    }
    return 0;
}
