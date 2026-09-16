/*
 * ico2/seki/include/Texture.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Texture.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

extern int tex_AllocVramAuto(int a0, int a1);
extern int *tex_GetTexExtData(int idx);
extern int *tex_GetTextureData(int idx);
extern int tex_GetTextureNo(char *name);
extern int tex_GetTextureNum(void);
extern void tex_Init(void);
extern int tex_InitTexture(void);
extern int tex_LoadTexturePart(void *a0, int a1);
extern void tex_LockHeadTBP(int tbp, int pri);
extern int tex_RemakeRegistersSampleMin(void);
extern void tex_ResetVramPri(int pri);
extern void tex_SetSamplingType(int *a0, int a1, int a2);
extern void tex_SetUVScroll(char *name, float u, float v, float su, float sv, float ou, float ov, int a1);
extern int tex_TransTexture(int no, int pri);
extern void tex_UnlockHeadTBP(int pri);
extern int tex_initTextureSub();
extern void tex_scrollClut(int a0, int a1, int a2, int a3, unsigned int a4, void *a5, int a6, void *a7);

#endif /* TEXTURE_H */
