#include "common.h"
#include "sugiCommon.h"
#include "windField.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include <libvu0.h>

extern int D_0063BC54;

/* This TU's .data run (VMA 0x4ED350..0x4ED760) and its .bss run (VMA
   0x724BE0..0x7281F0) are one file-static block each. MAIN.MAP records no
   symbol in either (only the sizes 0x410 and 0x3610, map lines 5991 and
   7755), so every name below is ours, read off the code that uses it; the
   definitions are written in the ROM's own run order because the compiler
   emits them in declaration order. */
static float windCenter[4] = {0.0f, 0.0f, 0.0f, 1.0f};

static float windDir[4] = {0.0f, 0.0f, 0.0f, 0.0f};

static float windPlane[4] = {0.0f, 0.0f, 0.0f, 1.0f};

typedef struct {
    float v[4];
    float str;
    float pad[3];
} WindCell;

static float windVector[4];

static float windStrength[256];

static WindCell windCell[20][20];

extern WindCell *getRadiateWindVector(float *power, float *pos);
extern int (*D_0063BC58)(void);

void InitWindField(int mode, float str, void *center, void *dir)
{
    int i;
    int j;

    D_0063BC58 = (int (*)(void))dummyGetWindVector;
    D_0063BC54 = mode;

    for (i = 255; i >= 0; i--) {
        windStrength[i] = str;
    }

    if (mode == 0) {
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 20; j++) {
                CopyVector(windCell[i][j].v, ZeroVector);
                windCell[i][j].str = 0.0f;
            }
        }
        CopyVector(windCenter, center);
        D_0063BC58 = (int (*)(void))getRadiateWindVector;
    } else {
        CopyVector(windCenter, center);
        sceVu0Normalize(windDir, dir);
        windDir[3] = 0.0f;
        CopyVector(windPlane, windDir);
        windPlane[3] = -sceVu0InnerProduct(windPlane, windCenter);
        D_0063BC58 = (int (*)(void))getParallelWindVector;
    }
}

extern short D_0063BC5C;

/* RGBA of every line this TU draws, in the int-per-channel form DrawLineG
   takes; colour bytes stay hex. */
static int lineColor[4] = {0x40, 0x40, 0x80, 0x80};

/* Vertex pairs, one line segment per two rows, terminated by a vertex whose
   x is the -10000 sentinel the draw loops test. */
static float haneLines[10][4] = {
    {0.0f, 0.0f, 0.0f, 1.0f},   {0.0f, 40.0f, 0.0f, 1.0f},  {0.0f, 40.0f, 0.0f, 1.0f},
    {15.0f, 40.0f, 0.0f, 1.0f}, {15.0f, 40.0f, 0.0f, 1.0f}, {40.0f, 20.0f, 0.0f, 1.0f},
    {40.0f, 20.0f, 0.0f, 1.0f}, {10.0f, 0.0f, 0.0f, 1.0f},  {-10000.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
};

/* The spoke drawSenpuukiHaneUnit sweeps sixteen times around Z. */
static float guardLines[12][4] = {
    {0.0f, 0.0f, 0.0f, 1.0f},      {0.0f, -10.0f, 0.0f, 1.0f},    {0.0f, -10.0f, 0.0f, 1.0f},
    {0.0f, -50.0f, 10.0f, 1.0f},   {0.0f, -50.0f, 10.0f, 1.0f},   {0.0f, -10.0f, 20.0f, 1.0f},
    {-10.0f, -50.0f, 10.0f, 1.0f}, {10.0f, -50.0f, 10.0f, 1.0f},  {-5.0f, -10.0f, 20.0f, 1.0f},
    {5.0f, -10.0f, 20.0f, 1.0f},   {-10000.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
};

/* INTERIM: `drawLines` is a real function at its own ROM slot further down this
   TU and the listing inlines it here; while the tail still carries asm members
   its definition cannot move up, so the two inlined copies are spelled through
   this stand-in. Fold them back onto drawLines once the TU is fully C. */
static inline void drawLinesInline(char *a0)
{
    char *cur = a0;

    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, lineColor, cur + 0x10, lineColor, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}

void drawSenpuukiHaneUnit(float scale)
{
    int i;

    MatrixDrive_PushMatrix();

    for (i = 0; i < 16; i++) {
        MatrixDrive_RotMatrixZ(0x1000);
        drawLinesInline((char *)guardLines);
    }

    MatrixDrive_PopMatrix();

    MatrixDrive_TransMatrix(0.0f, 0.0f, 10.0f);
    MatrixDrive_RotMatrixZ(D_0063BC5C);

    for (i = 0; i < 3; i++) {
        MatrixDrive_RotMatrixZ(21845);
        drawLinesInline((char *)haneLines);
    }

    D_0063BC5C = (short)(D_0063BC5C + scale * 4864.0f);
}

/* The motor housing: two 20 by 40 rectangles 20 apart in Y, joined at the
   corners. */
static float unitLines[26][4] = {
    {10.0f, 0.0f, 20.0f, 1.0f},     {10.0f, 0.0f, -20.0f, 1.0f},   {10.0f, 0.0f, -20.0f, 1.0f},
    {-10.0f, 0.0f, -20.0f, 1.0f},   {-10.0f, 0.0f, -20.0f, 1.0f},  {-10.0f, 0.0f, 20.0f, 1.0f},
    {-10.0f, 0.0f, 20.0f, 1.0f},    {10.0f, 0.0f, 20.0f, 1.0f},    {10.0f, -20.0f, 20.0f, 1.0f},
    {10.0f, -20.0f, -20.0f, 1.0f},  {10.0f, -20.0f, -20.0f, 1.0f}, {-10.0f, -20.0f, -20.0f, 1.0f},
    {-10.0f, -20.0f, -20.0f, 1.0f}, {-10.0f, -20.0f, 20.0f, 1.0f}, {-10.0f, -20.0f, 20.0f, 1.0f},
    {10.0f, -20.0f, 20.0f, 1.0f},   {10.0f, 0.0f, 20.0f, 1.0f},    {10.0f, -20.0f, 20.0f, 1.0f},
    {10.0f, 0.0f, -20.0f, 1.0f},    {10.0f, -20.0f, -20.0f, 1.0f}, {-10.0f, 0.0f, -20.0f, 1.0f},
    {-10.0f, -20.0f, -20.0f, 1.0f}, {-10.0f, 0.0f, 20.0f, 1.0f},   {-10.0f, -20.0f, 20.0f, 1.0f},
    {-10000.0f, 0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, 0.0f, 0.0f},
};

/* The stand: a 100 by 100 square on the floor and the post above it. */
static float baseLines[12][4] = {
    {50.0f, 0.0f, 50.0f, 1.0f},   {50.0f, 0.0f, -50.0f, 1.0f},   {50.0f, 0.0f, -50.0f, 1.0f},
    {-50.0f, 0.0f, -50.0f, 1.0f}, {-50.0f, 0.0f, -50.0f, 1.0f},  {-50.0f, 0.0f, 50.0f, 1.0f},
    {-50.0f, 0.0f, 50.0f, 1.0f},  {50.0f, 0.0f, 50.0f, 1.0f},    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, -100.0f, 0.0f, 1.0f},  {-10000.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
};

/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);

void drawSenpuuki(float scale)
{
    char *cur;

    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0);
    cur = (char *)baseLines;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, lineColor, cur + 0x10, lineColor, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    MatrixDrive_TransMatrix(0.0f, -100.0f, 0.0f);
    cur = (char *)unitLines;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, lineColor, cur + 0x10, lineColor, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    MatrixDrive_TransMatrix(0.0f, -10.0f, 20.0f);
    drawSenpuukiHaneUnit(scale);
    gif_EndPacket();
}

extern int D_0028F4C0[];

/* The cell centre ExecWindField samples, rewritten per cell; w stays 1. */
static float samplePos[4] = {0.0f, 0.0f, 0.0f, 1.0f};

extern int D_0063B148;

void ExecWindField(float str)
{
    float d[4];
    float len;
    int i;
    int j;
    int n;
    int m;

    windStrength[0] = str;
    for (i = 255; i != 0; i--) {
        windStrength[i] = windStrength[i - 1];
    }
    if (D_0063BC54 == 0) {
        for (i = 0; i < 20; i++) {
            samplePos[2] = ((float)i - 10.0f) * 100.0f;
            for (j = 0; j < 20; j++) {
                samplePos[0] = ((float)j - 10.0f) * 100.0f;
                sceVu0SubVector(d, samplePos, windCenter);
                len = FSqrt(sceVu0InnerProduct(d, d));
                n = (int)(len * 0.1f *
                          ((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f));
                m = n < 256 ? n : 255;
                (windCell[i] + j)->str = windStrength[m];
                sceVu0ScaleVector(windCell[i][j].v, d,
                                  60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) *
                                      windStrength[m] / len);
            }
        }
    }
    if (D_0063B148 != 0) {
        MatrixDrive_PushMatrix();
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV((char *)windCenter);
        MatrixDrive_RotMatrixY(GetTableArcTan2(windDir[0], windDir[2]));
        drawSenpuuki(str);
        MatrixDrive_PopMatrix();
    }
}

int GetWindVector(void)
{
    return D_0063BC58();
}

int *dummyGetWindVector(int *a0)
{
    if (a0)
        *a0 = 0;
    return ZeroVector;
}

float *getParallelWindVector(float *power, void *pos)
{
    float d;
    float s;
    int i;
    int n;

    d = plane_distance(pos, windPlane);
    if (d < 0.0f)
        d = -d;

    n = (int)(d * 0.1f * ((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f));
    i = n < 256 ? n : 255;
    s = windStrength[i] * (60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]));
    if (power)
        *power = s;
    sceVu0ScaleVector(windVector, windDir, s);
    return windVector;
}

WindCell *getRadiateWindVector(float *power, float *pos)
{
    int x;
    int z;

    z = (int)(pos[2] * 0.01f + 10.0f);
    x = (int)(pos[0] * 0.01f + 10.0f);
    z = z < 0 ? 0 : (z < 20 ? z : 19);
    x = x < 0 ? 0 : (x < 20 ? x : 19);
    if (power)
        *power = (windCell[0] + x + z * 20)->str;
    return &windCell[z][x];
}

void StopWindField(void)
{
    D_0063BC58 = (int (*)(void))dummyGetWindVector;
}

void drawLines(char *a0)
{
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, lineColor, cur + 0x10, lineColor, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}

void drawSenpuukiHane(void)
{
    float *p;
    for (p = (float *)haneLines; -1000.0f < *p; p += 8) {
        DrawLineG(p, lineColor, p + 4, lineColor, -1);
    }
}

void drawSenpuukiUnit(void)
{
    float *p;
    for (p = (float *)unitLines; -1000.0f < *p; p += 8) {
        DrawLineG(p, lineColor, p + 4, lineColor, -1);
    }
}

void drawSenpuukiBase(void)
{
    float *p;
    for (p = (float *)baseLines; -1000.0f < *p; p += 8) {
        DrawLineG(p, lineColor, p + 4, lineColor, -1);
    }
}
