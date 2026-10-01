/*
 * ico2/seki/include/Texture.h
 *
 * The declarations of what Texture.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

int tex_AllocVramAuto(int a0, int a1);
int *tex_GetTexExtData(int idx);
int *tex_GetTextureData(int idx);
int tex_GetTextureNo(char *name);
int tex_GetTextureNum(void);
void tex_Init(void);
int tex_InitTexture();
int tex_LoadTexturePart(void *a0, int a1);
void tex_LockHeadTBP(int tbp, int pri);
int tex_RemakeRegistersSampleMin(void);
void tex_ResetVramPri(int pri);
void tex_SetSamplingType(int *a0, int a1, int a2);
void tex_SetUVScroll(char *name, float u, float v, float su, float sv, float ou, float ov, int a1);
int tex_TransTexture(int no, int pri);
void tex_UnlockHeadTBP(int pri);
int tex_initTextureSub();
void tex_scrollClut(void *a0, void *a1, void *a2, int a3, int a4, void *a5, int a6, void *a7);
void tex_convertImage(void *dst, void *src, short fmt, short w, short h);
void tex_textureAnimation(void);
void tex_ResetVram(void);
void tex_UpdateMipMapLevel(float lv);
int tex_GetTWTH(int a0);

#endif /* TEXTURE_H */
