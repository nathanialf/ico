#include "common.h"
#include "Texture.h"
#include "DisplayList.h"
#include <string.h>

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

extern CdvdRec D_0068AFE0[];

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

extern int D_0063C164;
extern TexEntry D_0068AFD8[];

typedef struct TexClutEnt {
    int f0;
    int f4;
    int f8;
} TexClutEnt;

extern TexClutEnt D_00290B78[];

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_AllocVramAuto);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_loadImage);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_setTexReg);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_transVramClutTex);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_transVramDirectTex);

void tex_transRegister(int a0)
{
    dl_OpenDma(2, a0 + 0x58, 5);
    dl_CloseDma();
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_transTM2);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_initClutTexture);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_setRegisters);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_initTM2);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_convertClutCSM2ToCSM1);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_convertImage);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_makeCopyImage);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_makeTexturePacket);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_initTextureSub);

extern int file_LoadFile(int *size, char *name, int a2);
extern int sprintf(char *buf, const char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();
/* "%s" */
extern char D_0063A210[];
/* "%s.tm2" */
extern char D_0063A220[];
/* EUC-JP: texture "%s" not found. */
extern char D_00550908[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];

/* listing rows 1564-1578: a file-static helper with no symbol of its own, so
 * the January-2002 build inlined it here. It cuts the directory prefix and the
 * extension off the name in place. */
static inline void texTrimName(char *name)
{
    char tmp[256];
    int i;
    int k;

    k = 0;
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '/') {
            k = i + 1;
        }
    }
    sprintf(tmp, D_0063A210, &name[k]);
    sprintf(name, D_0063A210, tmp);
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '.') {
            name[i] = 0;
            break;
        }
    }
}

int tex_LoadTexturePart(void *name, int a1)
{
    char buf[272];
    int size = 0;

    sprintf(buf, D_0063A220, name);
    if (file_LoadFile(&size, buf, a1) >= 0) {
        texTrimName(buf);
        return tex_initTextureSub(buf, size);
    } else {
        debug_StdPrintfDummy(D_00550908, buf);
        debug_assert(D_00550328, 1590);
        __assert(D_00550328, 1590, D_0063A1F8);
        return -1;
    }
}

extern int tex_transTM2(void *pkt, void *tex, int id, int a3);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();
/* "tex_TransTexture:INVALID TEXTURE ID. %d/%d\n" */
extern char D_00550930[];
/* "tex_TransTexture:" + EUC-JP "texture transfer failed" + ". %d\n" */
extern char D_00550960[];
/* the same message with ". %d:%s\n" */
extern char D_00550998[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];
extern int D_0063B11C;

int tex_TransTexture(int id, int ret)
{
    CdvdRec *t = &D_0068AFE0[id];

    if (id < 0 || D_0063C164 <= id) {
        debug_Assert(D_00550930, id, D_0063C164);
    }
    if (id < 0) {
        ret = -1;
    } else if (*(int *)((char *)t + 0xDC) != 0) {
        ret = tex_transTM2((char *)t + 0x208, t, id, ret);
    } else {
        ret = -1;
    }
    if (ret < 0) {
        if (t == 0) {
            debug_StdPrintfDummy(D_00550960, id);
        } else {
            debug_StdPrintfDummy(D_00550998, id, t);
        }
        debug_assert(D_00550328, 1685);
        __assert(D_00550328, 1685, D_0063A1F8);
    }
    if (ret != 0) {
        D_0063B11C++;
    }
    dl_OpenDma(2, (int)((char *)t + 0xA8), 3);
    dl_CloseDma();
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_TransTextureDefocus);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_scrollClut);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_textureAnimation);

void tex_SetClutAnimation(int id, int frame)
{
    char *t = (char *)&D_0068AFE0[id];
    char *c = t + 0x268;

    if (*(int *)(c + 0x40) != 0) {
        int clut = D_00290B78[*(unsigned char *)(t + 0x21A) & 0x3F].f4;
        unsigned int n = *(unsigned int *)(t + 0x20C) >> 2;

        if (frame != -1) {
            *(short *)(c + 0x52) = frame;
        }
        tex_scrollClut(*(int *)(t + 0xE4) + 0x20, *(int *)(c + 0x54), *(int *)(c + 0x58), clut, n,
                       c, frame == -1 ? 0 : *(unsigned short *)(c + 0x52), t);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_FreeTexture);

typedef struct VramPri {
    short f0;
    short f1;
    short f2;
} VramPri;

extern VramPri D_0068AF88[];
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

    if (D_006AF518[pri] != 0) {
        D_0068AF88[pri].f0 = D_006AF518[pri];
    } else {
        D_0068AF88[pri].f0 = 0x2800;
    }
    D_0068AF88[pri].f1 = 0x3E80;
    D_0068AF88[pri].f2 = -1;
    for (i = 0; i < D_0063C164; i++) {
        D_0068AFD8[i].x2D0[pri] = 0;
    }
}

extern int D_0028F4C0[];
extern void tex_textureAnimation(void);

void tex_ResetVram(void)
{
    int i;

    for (i = 0; i < 13; i++) {
        D_006AF518[i] = 0;
        resetVramPri(i);
    }
    if (D_0028F4C0[5] == 0) {
        tex_textureAnimation();
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_dispClut);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_printTexture);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_Tool);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_ListTool);

int tex_GetTWTH(int a0)
{
    int ret = -1;
    int i;
    for (i = 0; i < 11; i++) {
        if ((1 << i) >= a0) {
            ret = i;
            break;
        }
    }
    return ret;
}

int tex_InitTexture(void)
{
    return tex_initTextureSub();
}

int tex_LoadTexture(void *a0)
{
    return tex_LoadTexturePart(a0, 0);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTextureNo into tex_SetUVScroll, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in getTextureNo, which collapses at layout. */
int tex_GetTextureNo(char *name)
{
    int i;
    int ret = -1;

    for (i = 0; i < D_0063C164; i++) {
        if (D_0068AFD8[i].used) {
            if (strcmp(name, D_0068AFD8[i].name) == 0) {
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

    for (i = 0; i < D_0063C164; i++) {
        if (D_0068AFD8[i].used) {
            if (strcmp(name, D_0068AFD8[i].name) == 0) {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTextureData into tex_SetUVScroll, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in getTextureData, which collapses at layout. */
int *tex_GetTextureData(int idx)
{
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
}

static inline int *getTextureData(int idx)
{
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
}

int *tex_GetTextureName(int idx)
{
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
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

short tex_GetVramFreeAddress(int a0)
{
    return D_0068AF88[a0].f0;
}

extern int D_0028F804[];

void tex_UpdateMipMapLevel(void)
{
    int i;
    for (i = 0; i < D_0063C164; i++) {
        CdvdRec *tex = &D_0068AFE0[i];
        int mxl = tex->xE0;
        int k, l;
        int mmag, mmin;
        if (tex->x2A8 != 0) {
            k = tex->x2A4;
            l = tex->x2A6;
            mmag = tex->x290;
            mmin = tex->x294;
        } else {
            k = -165;
            l = 0;
            mmag = 1;
            mmin = D_0028F804[0];
        }
        tex->x78 = ((long long)(mxl - 1) << 2) | ((long long)mmag << 5) | ((long long)mmin << 6) |
                   ((long long)l << 19) | ((long long)k << 32);
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

    if (D_006AF518[pri] != 0) {
        D_0068AF88[pri].f0 = D_006AF518[pri];
    } else {
        D_0068AF88[pri].f0 = 0x2800;
    }
    D_0068AF88[pri].f1 = 0x3E80;
    D_0068AF88[pri].f2 = -1;
    for (i = 0; i < D_0063C164; i++) {
        D_0068AFD8[i].x2D0[pri] = 0;
    }
}

int tex_GetTextureNum(void)
{
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

/* The int flag is the LAST parameter: EABI assigns the same registers either
   way, but a caller (script.c actSubSekizoSe) shows ROM loading it after the
   six floats. */
void tex_SetUVScroll(char *name, float u, float v, float su, float sv, float ou, float ov, int a1)
{
    int no = getTextureNo(name);
    char *tex = (char *)getTextureData(no);
    TexExt *ext = (TexExt *)(tex + 0x268);
    TexUV *uv = (TexUV *)(tex + 0xA8);

    if (ext->x40 != 0) {
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

extern int D_0063A22C;
extern void tex_ResetVram(void);

void tex_Init(void)
{
    int i;

    tex_ResetVram();
    D_0063C164 = 0;
    if (D_0063A22C == 0) {
        for (i = 199; i >= 0; i--) {
            D_0068AFD8[i].x2E0 = 1;
        }
        D_0063A22C = 1;
    } else {
        while (D_0068AFD8[D_0063C164].x2E0 == 0) {
            D_0063C164++;
        }
    }
}

extern int D_0028F720[];

int tex_RemakeRegistersSampleMin(void)
{
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
