#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/windField", InitWindField);
INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuukiHaneUnit);
extern char D_004ED380[];
extern char D_004ED4F0__pn[] __asm__("D_004ED4F0");
extern char D_004ED690__pn[] __asm__("D_004ED690");
extern void DrawLineG();
extern void MatrixDrive_TransMatrix(float f12, float f13, float f14);
extern void drawSenpuukiHaneUnit(float f12);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_StartPacketPri(int a0);

void drawSenpuuki(float scale) {
    char *cur;

    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0);
    cur = D_004ED690__pn;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, D_004ED380, cur + 0x10, D_004ED380, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
    MatrixDrive_TransMatrix(0.0f, -100.0f, 0.0f);
    cur = D_004ED4F0__pn;
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
INCLUDE_ASM("asm/nonmatchings/src/windField", ExecWindField);
extern int (*D_0063BC58)(void);

int GetWindVector(void) {
    return D_0063BC58();
}
extern char D_0028FEF0[];

int *dummyGetWindVector(int *a0)
{
    if (a0) *a0 = 0;
    return D_0028FEF0;
}
INCLUDE_ASM("asm/nonmatchings/src/windField", getParallelWindVector);
typedef struct {
    float v[4];
    float str;
    float pad[3];
} WindCell;

extern float D_00639704;
extern WindCell D_00724FF0[20][20];

WindCell *getRadiateWindVector(float *power, float *pos)
{
    int x;
    int z;

    z = (int)(pos[2] * D_00639704 + 10.0f);
    x = (int)(pos[0] * D_00639704 + 10.0f);
    z = z < 0 ? 0 : (z < 20 ? z : 19);
    x = x < 0 ? 0 : (x < 20 ? x : 19);
    if (power) *power = (D_00724FF0[0] + x + z * 20)->str;
    return &D_00724FF0[z][x];
}
void StopWindField(void) {
    D_0063BC58 = (int (*)(void))dummyGetWindVector;
}
extern char D_004ED380[];
extern void DrawLineG();

void drawLines(char *a0) {
    char *cur = a0;
    if (-1000.0f < *(float *)cur) {
        do {
            DrawLineG(cur, D_004ED380, cur + 0x10, D_004ED380, -1);
            cur += 0x20;
        } while (-1000.0f < *(float *)cur);
    }
}
extern float D_004ED380__pn[] __asm__("D_004ED380");
extern float D_004ED390[];
extern void DrawLineG__pn(void *a0, void *a1, void *a2, void *a3, int a4) __asm__("DrawLineG");

void drawSenpuukiHane(void) {
    float *p;
    for (p = D_004ED390; -1000.0f < *p; p += 8) {
        DrawLineG__pn(p, D_004ED380__pn, p + 4, D_004ED380__pn, -1);
    }
}
extern float D_004ED4F0[];

void drawSenpuukiUnit(void) {
    float *p;
    for (p = D_004ED4F0; -1000.0f < *p; p += 8) {
        DrawLineG__pn(p, D_004ED380__pn, p + 4, D_004ED380__pn, -1);
    }
}
extern float D_004ED690[];

void drawSenpuukiBase(void) {
    float *p;
    for (p = D_004ED690; -1000.0f < *p; p += 8) {
        DrawLineG__pn(p, D_004ED380__pn, p + 4, D_004ED380__pn, -1);
    }
}
