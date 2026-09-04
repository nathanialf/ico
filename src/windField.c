#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/windField", InitWindField);
INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuukiHaneUnit);
INCLUDE_ASM("asm/nonmatchings/src/windField", drawSenpuuki);
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
INCLUDE_ASM("asm/nonmatchings/src/windField", getRadiateWindVector);
INCLUDE_ASM("asm/nonmatchings/src/windField", StopWindField);
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
