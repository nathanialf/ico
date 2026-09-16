#include "common.h"
#include "puddle.h"
#include "DObj.h"
#include "memory.h"
#include "GsBase.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "Texture.h"
#include "matrixDrive.h"
#include "tableSin.h"

/* 16-byte aligned: the template copy in InitPuddleGeo is ld/sd, not ldl/ldr. */
typedef struct {
    float pos[4];
    float t;
    float pad[3];
} __attribute__((aligned(16))) Ripple;

typedef struct {
    int pad0;
    int idx;
    int pad8[2];
    Ripple rip[6];
} PuddleWork;

typedef struct {
    int x0;
    int y0;
    int x1;
    int y1;
} PuddleRect;

extern void *D_0063A438;
extern char D_006209D8[];
extern char D_002A79B8[];
extern float D_00723910[];
extern char D_004ECEA0[];
/* kept local: this TU's uses of gif_SpriteSensitiveOrg do not fit the prototype in GifPacket.h */
extern void gif_SpriteSensitiveOrg(void *rect, int z, void *uv, void *col, int e);
extern void memset(void *p, int c, int n);
extern int D_0063BA8C;
extern int D_0063BA90;
extern int D_00639F94;
extern char D_006209E8[];
extern char *matrixptr;
extern int D_0063A064; /* screen width  */
extern int D_0063A068; /* screen height */
extern int D_0063A07C;
extern int D_0063A080;
extern int D_0063BA88;
extern char D_007239A0[];
extern char D_007239E0[];
extern char D_00723A20[];
extern char D_00723A60[];
extern char D_00723AA0[];
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int on);
/* kept local: this TU's uses of gif_SetZWrite do not fit the prototype in GifPacket.h */
extern void gif_SetZWrite(int on);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int reg, long long val);
/* kept local: this TU's uses of gif_SetDrawEnviroment do not fit the prototype in GifPacket.h */
extern void gif_SetDrawEnviroment(int a0, int a1, int a2, int a3, int a4, int a5);
extern int D_0063BA98;
extern int D_0063BAA0;
extern float D_00723640[];
extern float D_00723760[];
extern float D_00723880[];
extern char D_004ECEC0[];
extern char D_004ECED0[];
/* kept local: this TU's uses of gif_DrawStripFST do not fit the prototype in GifPacket.h */
extern void gif_DrawStripFST(void *a, void *b, unsigned long long col, int n, int e);
extern int stage_no;
extern int D_0028F4C0[];
void PuddleGeo(char *a0);
void EntryRippleToPuddle(char *a0, void *vec);
int puddleRideFunc(char **a0, char *a1);

PuddleWork *InitPuddleGeo(char *a0, char *a1)
{
    PuddleWork *w = (PuddleWork *)iosMallocDebug(D_0063A438, 0xD0, D_006209D8, 0x45);
    float *v;
    int i;

    *(char **)w = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28), a1);

    v = D_00723910;
    for (i = 0; i < 9; i++) {
        short s = i * 0x2000;

        v[0] = GetTableCos(s);
        v[2] = GetTableSin(s);
        v[1] = 0.0f;
        v[3] = 1.0f;
        v += 4;
    }

    w->idx = 0;

    for (i = 0; i < 6; i++) {
        w->rip[i] = *(Ripple *)D_004ECEA0;
    }

    *(int *)(*(char **)(a0 + 0x15C) + 0x81C) = (int)puddleRideFunc;
    return w;
}

void baseSetup(char *a0)
{
    gif_StartPacketPri(4);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 5, 0x80);

    {
        PuddleRect r = {-D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16, D_0063A064 * 16,
                        D_0063A068 * 16};

        {
            unsigned char col[4];

            memset(col, 0, 4);
            gif_SpriteSensitiveOrg(&r, 0, 0, col, 1);
        }
    }

    gif_SetZTest(1);
    gif_EndPacket();

    reg_RenderReflection(*(char **)(a0 + 0x15C), 4);
}

void drawAreaSetup(void)
{
    PuddleRect r;

    tex_ResetVramPri(4);
    D_0063BA88 = tex_AllocVramAuto(0, 0x400);
    D_0063BA8C = tex_AllocVramAuto(0, 0x400);

    gif_StartPacketPri(4);

    CopyMatrix(D_007239A0, matrixptr + 0xC0);
    CopyMatrix(D_007239E0, matrixptr + 0x1C0);
    CopyMatrix(D_00723A20, matrixptr + 0x100);
    CopyMatrix(D_00723A60, matrixptr + 0x200);
    CopyMatrix(D_00723AA0, matrixptr + 0x340);

    gsb_SetVSMatrix(0xE6, 0xE6, (float)D_00639F94);

    _MulMatrix(matrixptr + 0x100, matrixptr + 0xC0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x200, matrixptr + 0x1C0, matrixptr + 0x80);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();

    gif_StartPacketPri(4);
    gif_SetDrawEnviroment(D_0063BA88, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (D_0063BA8C / 32));
    gif_SetAlpha(0, 4, 0);

    r = *(PuddleRect *)D_006209E8;
    gif_SpriteSensitiveOrg(&r, 0, 0, &D_0063BA90, 0);

    gif_SetZTest(1);
    gif_EndPacket();
}

void drawAreaRestore(void)
{
    gif_StartPacketPri(4);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    gif_SetAlpha(0, 4, 0x80);

    CopyMatrix(matrixptr + 0xC0, D_007239A0);
    CopyMatrix(matrixptr + 0x1C0, D_007239E0);
    CopyMatrix(matrixptr + 0x340, D_00723AA0);
    CopyMatrix(matrixptr + 0x100, D_00723A20);
    CopyMatrix(matrixptr + 0x200, D_00723A60);

    D_0063A07C = D_0063A064;
    D_0063A080 = D_0063A068;
    gif_SetGsReg(6, (long long)D_0063BA88 | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(1, 0, 0x40);
    gif_EndPacket();
}

void leveldown(int pri)
{
    gif_StartPacketPri(pri);
    gif_SetGsReg(6, (long long)D_0063BA88 | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetGsReg(0x47, 0x3F001);
    gif_SetAlpha(1, 2, 0x10);

    {
        PuddleRect r = {-D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16, D_0063A064 * 16,
                        D_0063A068 * 16};

        gif_SpriteSensitiveOrg(&r, 0, 0, &D_0063BA98, 1);
    }

    gif_EndPacket();
}

/* gif_SpriteSensitiveOrg passes the uv rectangle straight through to
   gif_MakeSprite, so its caller supplies UV already in GS 1/16-texel units
   (gif_SpriteOrg is the variant that scales by 16 itself).  The conversion has
   to be a CALL and not a constant expression: an all-constant initialiser is
   emitted as a 16-byte .rodata blob and block-copied, and the ROM instead
   materialises 212 and 3686 with `li` into a stack temp and block-copies that,
   which is what expr.c does when safe_from_p rejects the target.  The exact
   spelling of the 2001 helper is not recoverable; this one reproduces the ROM
   word for word. */
static inline int texUV(float texel)
{
    return (int)(texel * 16.0f);
}

void copy(int pri)
{
    gif_StartPacketPri(pri);
    gif_SetGsReg(6, (long long)D_0063BA88 | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetGsReg(0x47, 0x3F001);

    if (stage_no == 0x22) {
        gif_SetAlpha(1, 4, 0x60);
    } else {
        gif_SetAlpha(1, 0, 0x60);
    }

    {
        int r[4] = {-D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16, D_0063A064 * 16, D_0063A068 * 16};
        int uv[4] = {texUV(13.25f), texUV(13.25f), texUV(230.375f), texUV(230.375f)};

        gif_SpriteSensitiveOrg(r, 0, uv, &D_0063BAA0, 1);
    }

    gif_EndPacket();
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/puddle", drawRipple);

void drawRipples(char *a0, int pri)
{
    PuddleWork *w = (PuddleWork *)*(char **)(*(char **)(a0 + 0x15C) + 0x830);
    Ripple *p;
    float *t;
    int i;

    gif_StartPacketPri(pri);
    gif_SetGsReg(6, (long long)D_0063BA88 | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetGsReg(0x47, 0x3F000);

    if (stage_no == 0x22) {
        gif_SetAlpha(1, 4, 0x60);
    } else {
        gif_SetAlpha(1, 0, 0x60);
    }

    gif_EndPacket();

    gif_StartPacketPri(pri);

    p = w->rip;
    t = &w->rip[0].t;
    for (i = 5; i >= 0; i--) {
        if (*t < 200.0f) {
            drawRipple(*t, p);
        }
        p++;
        t += sizeof(Ripple) / sizeof(float);
    }

    gif_EndPacket();
}

void PuddleDL(char *a0)
{
    char *p = *(char **)*(char **)(*(char **)(a0 + 0x15C) + 0x830);

    baseSetup(a0);
    drawAreaSetup();
    _UnitMatrix(MatrixDrive_GetMatrix());
    CopyMatrix(*(void **)(p + 0xC), MatrixDrive_GetMatrix());
    reg_RenderReflection(p, 4);
    drawAreaRestore();
    leveldown(4);
    drawRipples(a0, 4);
    copy(4);
}

inline void PuddleGeo(char *a0)
{
    char *p;
    int i;

    p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    for (i = 0; i < 6; i++) {
        if (*(float *)(p + 0x20) < 200.0f) {
            *(float *)(p + 0x20) +=
                60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 2.0f;
        }
        p += 0x20;
    }
}

inline void EntryRippleToPuddle(char *a0, void *vec)
{
    PuddleWork *w;

    w = *(PuddleWork **)(*(char **)(a0 + 0x15C) + 0x830);
    CopyVector(w->rip[w->idx].pos, vec);
    w->rip[w->idx].t = 0.0f;
    w->idx = w->idx + 1;
    if (w->idx >= 6) {
        w->idx = 0;
    }
}

inline int puddleRideFunc(char **a0, char *a1)
{
    float v[4];
    char *e;
    int n;

    e = *(char **)(a1 + 0x15C);
    if (*(int *)(e + 0x63C) != 0) {
        n = *(int *)(e + 0x220);
        if (n != -1) {
            CopyVector(v, *(char **)(e + 0xC) + n * 0x40 + 0x30);
            EntryRippleToPuddle(*a0, v);
        }
    }
    return 1;
}
