#include "common.h"

typedef struct {
    float pos[4];
    float t;
    float pad[3];
} Ripple;

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

extern char *iosMallocDebug(void *heap, int size, char *file, int line);
extern void *D_0063A438;
extern char D_006209D8[];
extern char D_002A79B8[];
extern float D_00723910[];
extern char D_004ECEA0[];
extern int CSVSYSTEM_InitDObj(int a0, void *a1, int a2);
extern float GetTableCos(short a);
extern float GetTableSin(short a);
extern void gif_SpriteSensitiveOrg(void *rect, int z, void *uv, void *col, int e);
extern void memset(void *p, int c, int n);
extern int D_0063BA8C;
extern int D_0063BA90;
extern int D_00639F94;
extern char D_006209E8[];
extern void tex_ResetVramPri(int pri);
extern int tex_AllocVramAuto(int a0, int a1);
extern void gsb_SetVSMatrix(int a0, int a1, float f);
extern void _MulMatrix(void *dst, void *a, void *b);
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
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_SetGsReg(int reg, long long val);
extern void gif_SetDrawEnviroment(int a0, int a1, int a2, int a3, int a4, int a5);
extern int D_0063BA98;
extern int D_0063BAA0;
extern float D_00639670;
extern float D_00639674;
extern float D_00639678;
extern float D_00723640[];
extern float D_00723760[];
extern float D_00723880[];
extern char D_004ECEC0[];
extern char D_004ECED0[];
extern void MatrixDrive_RotMatrixY(short a);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void _SetCurrentMatrix(void *m);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void _ScaleVector(void *dst, void *src, float k);
extern void _SubVector(void *dst, void *a, void *b);
extern void _AddVector(void *dst, void *a, void *b);
extern void gif_DrawStripFST(void *a, void *b, unsigned long long col, int n, int e);
extern int stage_no;
extern void drawRipple(float t, void *pos);
extern void baseSetup(char *a0);
extern void drawAreaSetup(void);
extern void drawAreaRestore(void);
extern void leveldown(int pri);
extern void copy(int pri);
extern void drawRipples(char *a0, int pri);
extern void *MatrixDrive_GetMatrix(void);
extern void _UnitMatrix(void *m);
extern void CopyMatrix(void *dst, void *src);
extern void reg_RenderReflection(void *o, int pri);
extern int D_0028F4C0[];
extern void CopyVector(void *a0, void *a1);

INCLUDE_ASM("asm/nonmatchings/src/puddle", InitPuddleGeo);
INCLUDE_ASM("asm/nonmatchings/src/puddle", baseSetup);

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

INCLUDE_ASM("asm/nonmatchings/src/puddle", copy);
INCLUDE_ASM("asm/nonmatchings/src/puddle", drawRipple);
INCLUDE_ASM("asm/nonmatchings/src/puddle", drawRipples);

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
