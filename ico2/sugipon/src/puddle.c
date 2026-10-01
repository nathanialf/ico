#include "puddle.h"
#include "DObj.h"
#include "GifPacket.h"
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

typedef struct {
    unsigned char r, g, b, a;
} PuddleColor;

/* The TU's .data (MAIN.MAP names nothing in it), in ROM order: the ripple every
   slot starts from, and the centre and scale of the ripple mesh in texture
   space. */
static Ripple rippleInit = {{0.0f, 0.0f, 0.0f, 1.0f}, 10000.0f}; /* derived name */

static float rippleCenter[4] = {2048.0f, 2048.0f, 0.0f, 0.0f}; /* derived name */

static float rippleScale[4] = {1.5f, 1.5f, 0.0f, 0.0f}; /* derived name */

/* The TU's .sdata, in ROM order: the two work-area VRAM addresses and the three
   sprite colours. */
static int workVram = 0; /* derived name */

static int work1Vram = 0; /* derived name */

static PuddleColor setupColor = {128, 128, 128, 128}; /* derived name */

static PuddleColor leveldownColor = {0, 0, 0, 0}; /* derived name */

static PuddleColor copyColor = {128, 128, 128, 128}; /* derived name */

/* The TU's .bss (MAIN.MAP names nothing in it), in ROM order: the two vertex
   strips of the ripple mesh, the nine spoke directions and their scaled copies,
   and the five camera matrices drawAreaSetup saves and drawAreaRestore puts
   back. */
static float stripUpper[9 * 8]; /* derived name */

static float stripLower[9 * 8]; /* derived name */

static float spokeScaled[9 * 4]; /* derived name */

static float spokeDir[9 * 4]; /* derived name */

static float savedMatrixC0[16]; /* derived name */

static float savedMatrix1C0[16]; /* derived name */

static float savedMatrix100[16]; /* derived name */

static float savedMatrix200[16]; /* derived name */

static float savedMatrix340[16]; /* derived name */

/* Declared here, not through string.h: with newlib's prototype in scope gcc
   expands the four-byte zero fill below as one store, and the ROM calls
   memset there (ROM bytes 0x1BD6D0 frame). The non-standard prototype is
   what keeps the builtin off in this file. */
extern void memset(void *p, int c, int n);
/* kept local: this TU's view of the ios partition handles (ios.h declares them int) */
extern void *ios_partition_sugipon;
extern char D_002A79B8[];
extern char *matrixptr;
extern int stage_no;
extern int D_0028F4C0[];
void PuddleGeo(char *a0);
void EntryRippleToPuddle(char *a0, void *vec);
int puddleRideFunc(char **a0, char *a1);

PuddleWork *InitPuddleGeo(char *a0, char *a1)
{
    PuddleWork *w = (PuddleWork *)iosMallocDebug(ios_partition_sugipon, 0xD0, __FILE__, 69);
    float *v;
    int i;

    *(char **)w = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28), a1);

    v = spokeDir;
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
        w->rip[i] = rippleInit;
    }

    *(int *)(*(char **)(a0 + 0x15C) + 0x81C) = (int)puddleRideFunc;
    return w;
}

void baseSetup(char *a0)
{
    gif_StartPacketPri(4);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 5, 0x80);

    {
        PuddleRect r = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                        ScreenHeight * 16};

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

/* the sprite rectangle drawAreaSetup blits the frame through, in GS primitive
   coordinates, after InitPuddleGeo's file name in the TU's .rodata */
static const int drawAreaRect[4] = {-2048, -2048, 4096, 4096}; /* derived name */

void drawAreaSetup(void)
{
    PuddleRect r;

    tex_ResetVramPri(4);
    workVram = tex_AllocVramAuto(0, 0x400);
    work1Vram = tex_AllocVramAuto(0, 0x400);

    gif_StartPacketPri(4);

    CopyMatrix(savedMatrixC0, matrixptr + 0xC0);
    CopyMatrix(savedMatrix1C0, matrixptr + 0x1C0);
    CopyMatrix(savedMatrix100, matrixptr + 0x100);
    CopyMatrix(savedMatrix200, matrixptr + 0x200);
    CopyMatrix(savedMatrix340, matrixptr + 0x340);

    gsb_SetVSMatrix(0xE6, 0xE6, (float)currentFocusDistance);

    _MulMatrix(matrixptr + 0x100, matrixptr + 0xC0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x200, matrixptr + 0x1C0, matrixptr + 0x80);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();

    gif_StartPacketPri(4);
    gif_SetDrawEnviroment(workVram, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (work1Vram / 32));
    gif_SetAlpha(0, 4, 0);

    r = *(PuddleRect *)drawAreaRect;
    gif_SpriteSensitiveOrg(&r, 0, 0, &setupColor, 0);

    gif_SetZTest(1);
    gif_EndPacket();
}

void drawAreaRestore(void)
{
    gif_StartPacketPri(4);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    gif_SetAlpha(0, 4, 0x80);

    CopyMatrix(matrixptr + 0xC0, savedMatrixC0);
    CopyMatrix(matrixptr + 0x1C0, savedMatrix1C0);
    CopyMatrix(matrixptr + 0x340, savedMatrix340);
    CopyMatrix(matrixptr + 0x100, savedMatrix100);
    CopyMatrix(matrixptr + 0x200, savedMatrix200);

    vsWidth = ScreenWidth;
    vsHeight = ScreenHeight;
    gif_SetGsReg(6, (long long)workVram | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(1, 0, 0x40);
    gif_EndPacket();
}

void leveldown(int pri)
{
    gif_StartPacketPri(pri);
    gif_SetGsReg(6, (long long)workVram | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetGsReg(0x47, 0x3F001);
    gif_SetAlpha(1, 2, 0x10);

    {
        PuddleRect r = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                        ScreenHeight * 16};

        gif_SpriteSensitiveOrg(&r, 0, 0, &leveldownColor, 1);
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
    gif_SetGsReg(6, (long long)workVram | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetGsReg(0x47, 0x3F001);

    if (stage_no == 0x22) {
        gif_SetAlpha(1, 4, 0x60);
    } else {
        gif_SetAlpha(1, 0, 0x60);
    }

    {
        int r[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                    ScreenHeight * 16};
        int uv[4] = {texUV(13.25f), texUV(13.25f), texUV(230.375f), texUV(230.375f)};

        gif_SpriteSensitiveOrg(r, 0, uv, &copyColor, 1);
    }

    gif_EndPacket();
}

void drawRipple(float t, void *pos)
{
    GifColor col;
    float v[4];
    float age;
    float sx;
    float sy;
    float s2;
    int c;
    int i;
    float *p0;
    float *p1;
    float *q0;
    float *q1;
    float *r0;
    float *r1;

    age = 200.0f - t;
    col.a = 0x80;
    c = (int)(age * 0.635f + 128.0f);
    col.r = c;
    col.g = c;
    col.b = c;
    sx = 0.9f / (float)ScreenWidth;
    sy = 0.9f / (float)ScreenHeight;
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY((short)(int)(age * 10.24f));

    p1 = spokeDir;
    p0 = spokeScaled;
    for (i = 8; i >= 0; i--) {
        _ApplyMatrix(p0, MatrixDrive_GetMatrix(), p1);
        p0 += 4;
        p1 += 4;
    }

    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < 9; i++) {
        float *m = &spokeDir[i * 4];

        q0 = &stripUpper[i * 8];
        r0 = &stripUpper[i * 8 + 4];
        q1 = &stripLower[i * 8];
        r1 = &stripLower[i * 8 + 4];

        _ScaleVectorXYZ(q0, m, t);
        s2 = t + 5.0f;
        _ScaleVectorXYZ(r0, m, s2);
        _AddVectorXYZ(q0, q0, pos);
        _AddVectorXYZ(r0, r0, pos);
        _ScaleVectorXYZ(v, &spokeScaled[i * 4], s2);
        _AddVectorXYZ(v, v, pos);
        _ApplyCurrentMatrix(q1, q0);
        _ApplyCurrentMatrix(r1, v);
        _ScaleVector(q1, q1, 1.0f / q1[3]);
        _ScaleVector(r1, r1, 1.0f / r1[3]);
        _SubVector(q1, q1, rippleCenter);
        _SubVector(r1, r1, rippleCenter);
        q1[0] = q1[0] * sx;
        q1[1] = q1[1] * sy;
        r1[0] = r1[0] * sx;
        r1[1] = r1[1] * sy;
        _AddVector(q1, q1, rippleScale);
        _AddVector(r1, r1, rippleScale);
    }

    gif_DrawStripFST(stripUpper, stripLower, col, 0x12, 1);
}

void drawRipples(char *a0, int pri)
{
    PuddleWork *w = (PuddleWork *)*(char **)(*(char **)(a0 + 0x15C) + 0x830);
    Ripple *p;
    float *t;
    int i;

    gif_StartPacketPri(pri);
    gif_SetGsReg(6, (long long)workVram | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
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
