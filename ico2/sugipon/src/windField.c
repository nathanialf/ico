#include "common.h"
#include "sugiCommon.h"
#include "windField.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include <libvu0.h>

extern int D_0063BC54;
extern float D_004ED350[];
extern float D_004ED360[];
extern float D_004ED370[];

typedef struct {
    float v[4];
    float str;
    float pad[3];
} WindCell;

extern WindCell D_00724FF0[20][20];
extern WindCell *getRadiateWindVector(float *power, float *pos);
extern int (*D_0063BC58)(void);
extern float D_00724BF0[];

void InitWindField(int mode, float str, void *center, void *dir)
{
    int i;
    int j;

    D_0063BC58 = (int (*)(void))dummyGetWindVector;
    D_0063BC54 = mode;

    for (i = 255; i >= 0; i--) {
        D_00724BF0[i] = str;
    }

    if (mode == 0) {
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 20; j++) {
                CopyVector(D_00724FF0[i][j].v, ZeroVector);
                D_00724FF0[i][j].str = 0.0f;
            }
        }
        CopyVector(D_004ED350, center);
        D_0063BC58 = (int (*)(void))getRadiateWindVector;
    } else {
        CopyVector(D_004ED350, center);
        sceVu0Normalize(D_004ED360, dir);
        D_004ED360[3] = 0.0f;
        CopyVector(D_004ED370, D_004ED360);
        D_004ED370[3] = -sceVu0InnerProduct(D_004ED370, D_004ED350);
        D_0063BC58 = (int (*)(void))getParallelWindVector;
    }
}

extern short D_0063BC5C;
extern float D_004ED390[];
extern float D_004ED430[];
extern char D_004ED380[];

/* INTERIM: `drawLines` is a real function at its own ROM slot further down this
   TU and the listing inlines it here; while the tail still carries asm members
   its definition cannot move up, so the two inlined copies are spelled through
   this stand-in. Fold them back onto drawLines once the TU is fully C. */
static inline void drawLinesInline(char *a0)
{
    char *cur = a0;

    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, D_004ED380, cur + 0x10, D_004ED380, -1);
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
        drawLinesInline((char *)D_004ED430);
    }

    MatrixDrive_PopMatrix();

    MatrixDrive_TransMatrix(0.0f, 0.0f, 10.0f);
    MatrixDrive_RotMatrixZ(D_0063BC5C);

    for (i = 0; i < 3; i++) {
        MatrixDrive_RotMatrixZ(21845);
        drawLinesInline((char *)D_004ED390);
    }

    D_0063BC5C = (short)(D_0063BC5C + scale * 4864.0f);
}

extern char D_004ED380[];
extern float D_004ED4F0[];
extern float D_004ED690[];
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
    cur = (char *)D_004ED690;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, D_004ED380, cur + 0x10, D_004ED380, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    MatrixDrive_TransMatrix(0.0f, -100.0f, 0.0f);
    cur = (char *)D_004ED4F0;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, D_004ED380, cur + 0x10, D_004ED380, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    MatrixDrive_TransMatrix(0.0f, -10.0f, 20.0f);
    drawSenpuukiHaneUnit(scale);
    gif_EndPacket();
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/windField", ExecWindField);

extern int (*D_0063BC58)(void);

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

extern int D_0028F4C0[];
extern float D_004ED360[];
extern float D_004ED370[];
extern float D_00724BE0[];
extern float D_00724BF0[];

float *getParallelWindVector(float *power, void *pos)
{
    float d;
    float s;
    int i;
    int n;

    d = plane_distance(pos, D_004ED370);
    if (d < 0.0f)
        d = -d;

    n = (int)(d * 0.1f * ((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f));
    i = n < 256 ? n : 255;
    s = D_00724BF0[i] * (60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]));
    if (power)
        *power = s;
    sceVu0ScaleVector(D_00724BE0, D_004ED360, s);
    return D_00724BE0;
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
        *power = (D_00724FF0[0] + x + z * 20)->str;
    return &D_00724FF0[z][x];
}

void StopWindField(void)
{
    D_0063BC58 = (int (*)(void))dummyGetWindVector;
}

extern char D_004ED380[];

void drawLines(char *a0)
{
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, D_004ED380, cur + 0x10, D_004ED380, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}

extern float D_004ED390[];

void drawSenpuukiHane(void)
{
    float *p;
    for (p = D_004ED390; -1000.0f < *p; p += 8) {
        DrawLineG(p, D_004ED380, p + 4, D_004ED380, -1);
    }
}

extern float D_004ED4F0[];

void drawSenpuukiUnit(void)
{
    float *p;
    for (p = D_004ED4F0; -1000.0f < *p; p += 8) {
        DrawLineG(p, D_004ED380, p + 4, D_004ED380, -1);
    }
}

extern float D_004ED690[];

void drawSenpuukiBase(void)
{
    float *p;
    for (p = D_004ED690; -1000.0f < *p; p += 8) {
        DrawLineG(p, D_004ED380, p + 4, D_004ED380, -1);
    }
}
