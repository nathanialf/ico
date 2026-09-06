#include "common.h"

typedef struct CdvdRec {
    char pad0[0x78];
    long long x78;
    char pad80[0xE0 - 0x80];
    unsigned short xE0;
    char padE2[0x290 - 0xE2];
    int x290;
    int x294;
    char pad298[0x2A4 - 0x298];
    short x2A4;
    short x2A6;
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
typedef struct TexEntry {
    char pad0[8];
    char name[0x78];
    long long x80;
    char pad88[0x2D0 - 0x88];
    char x2D0[0x2D8 - 0x2D0];
    unsigned int pad2D8;
    unsigned char pad2DC;
    unsigned short used : 1;
    char pad2DE[0x2E0 - 0x2DE];
    short x2E0;
    char pad2E2[0x2E8 - 0x2E2];
} TexEntry;

extern int strcmp(const char *, const char *);
extern int D_0063C164;
extern TexEntry D_0068AFD8[];

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTextureNo into tex_SetUVScroll, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in getTextureNo, which collapses at layout. */
int tex_GetTextureNo(char *name)
{
    int i;
    int ret = -1;

    for (i = 0; i < D_0063C164; i++)
    {
        if (D_0068AFD8[i].used)
        {
            if (strcmp(name, D_0068AFD8[i].name) == 0)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}
static inline int getTextureNo(char *name)
{
    int i;
    int ret = -1;

    for (i = 0; i < D_0063C164; i++)
    {
        if (D_0068AFD8[i].used)
        {
            if (strcmp(name, D_0068AFD8[i].name) == 0)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}
extern int D_0068AFE0__pn[] __asm__("D_0068AFE0");

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTextureData into tex_SetUVScroll, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in getTextureData, which collapses at layout. */
int *tex_GetTextureData(int idx)
{
    return (int *)((char *)D_0068AFE0__pn + idx * 0x2E8);
}
static inline int *getTextureData(int idx)
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
typedef struct VramPri {
    short f0;
    short f1;
    short f2;
} VramPri;

extern VramPri D_0068AF88[];

short tex_GetVramFreeAddress(int a0)
{
    return D_0068AF88[a0].f0;
}
extern int D_0063C164;
extern CdvdRec D_0068AFE0[];
extern int D_0028F804[];

void tex_UpdateMipMapLevel(void)
{
    int i;
    for (i = 0; i < D_0063C164; i++)
    {
        CdvdRec *tex = &D_0068AFE0[i];
        int mxl = tex->xE0;
        int k, l;
        int mmag, mmin;
        if (tex->x2A8 != 0)
        {
            k = tex->x2A4;
            l = tex->x2A6;
            mmag = tex->x290;
            mmin = tex->x294;
        }
        else
        {
            k = -165;
            l = 0;
            mmag = 1;
            mmin = D_0028F804[0];
        }
        tex->x78 = ((long long)(mxl - 1) << 2) | ((long long)mmag << 5) |
                   ((long long)mmin << 6) | ((long long)l << 19) |
                   ((long long)k << 32);
    }
}
extern void dl_SetDLPriority(int pri);
extern int D_006AF518[];

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_ResetVramPri into tex_LockHeadTBP/tex_UnlockHeadTBP, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in resetVramPri, which collapses at layout. */
static inline void resetVramPri(int pri)
{
    int i;

    dl_SetDLPriority(pri);

    if (D_006AF518[pri] != 0)
    {
        D_0068AF88[pri].f0 = D_006AF518[pri];
    }
    else
    {
        D_0068AF88[pri].f0 = 0x2800;
    }
    D_0068AF88[pri].f1 = 0x3E80;
    D_0068AF88[pri].f2 = -1;
    for (i = 0; i < D_0063C164; i++)
    {
        D_0068AFD8[i].x2D0[pri] = 0;
    }
}
void tex_LockHeadTBP(int tbp, int pri)
{
    D_006AF518[pri] = tbp;
    resetVramPri(pri);
}
void tex_UnlockHeadTBP(int pri)
{
    D_006AF518[pri] = 0;
    resetVramPri(pri);
}
void tex_ResetVramPri(int pri)
{
    int i;

    dl_SetDLPriority(pri);

    if (D_006AF518[pri] != 0)
    {
        D_0068AF88[pri].f0 = D_006AF518[pri];
    }
    else
    {
        D_0068AF88[pri].f0 = 0x2800;
    }
    D_0068AF88[pri].f1 = 0x3E80;
    D_0068AF88[pri].f2 = -1;
    for (i = 0; i < D_0063C164; i++)
    {
        D_0068AFD8[i].x2D0[pri] = 0;
    }
}
extern int D_0063C164;

int tex_GetTextureNum(void) {
    return D_0063C164;
}
typedef struct TexUV {
    char pad0[0x10];
    float f10;
    float f14;
    char pad18[0x18];
} TexUV;

typedef struct TexExt {
    char pad0[4];
    float f04;
    float f08;
    char pad0C[0x40 - 0x0C];
    int x40;
    float f44;
    float f48;
    int x4C;
    short h50;
    char pad52[0x80 - 0x52];
} TexExt;

void tex_SetUVScroll(char *name, int a1, float u, float v, float su, float sv, float ou, float ov)
{
    int no = getTextureNo(name);
    char *tex = (char *)getTextureData(no);
    TexExt *ext = (TexExt *)(tex + 0x268);
    TexUV *uv = (TexUV *)(tex + 0xA8);

    if (ext->x40 != 0)
    {
        ext->f04 = su;
        ext->f08 = sv;
        ext->h50 = 0;
        uv->f10 = u;
        uv->f14 = v;
        ext->f44 = ou;
        ext->f48 = ov;
        ext->x4C = a1;
    }
}
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
