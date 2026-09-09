#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void ChangeColorWireString(int a0, int a1, int a2);
void Draw2DBox(float x0, float y0, float x1, float y1);

typedef struct {
    float x;
    float y;
    int z;
} WLPnt;

extern int D_004EE590[];
extern int D_004EE5A0[];
extern void DrawLineG(void *a0, void *a1, void *a2, void *a3, int a4);
extern void gif_EndPacket(void);
extern void gif_StartPacketPri(int a0);

inline void Draw2DBox(float x0, float y0, float x1, float y1)
{
    WLPnt a __attribute__((aligned(16))) = {x0, y0, 0};
    WLPnt b __attribute__((aligned(16))) = {x0, y1, 0};
    WLPnt c __attribute__((aligned(16))) = {x1, y1, 0};
    WLPnt d __attribute__((aligned(16))) = {x1, y0, 0};
    gif_StartPacketPri(0xB);
    DrawLineG(&a, D_004EE5A0, &b, D_004EE5A0, -1);
    DrawLineG(&b, D_004EE5A0, &c, D_004EE5A0, -1);
    DrawLineG(&c, D_004EE5A0, &d, D_004EE5A0, -1);
    DrawLineG(&d, D_004EE5A0, &a, D_004EE5A0, -1);
    gif_EndPacket();
}

extern int D_004EE4D0[];
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void gif_SetAlpha(int a, int b, int c);
void DispWireLetter(int c);

void DispWireLetter(int c)
{
    int idx = c - '.';
    float *p;
    int i;

    if (c != ' ') {
        p = (float *)D_004EE4D0[idx];
        if (p != 0) {
            MatrixDrive_PushMatrix();
            gif_StartPacketPri(0xB);
            gif_SetAlpha(1, 5, 0);
            for (i = 0; p[i * 4] < 100.0f; i++) {
                WLPnt a = {p[i * 4 + 0], -p[i * 4 + 1], 0};
                WLPnt b = {p[i * 4 + 2], -p[i * 4 + 3], 0};

                DrawLineG(&a, D_004EE5A0, &b, D_004EE5A0, -1);
            }
            gif_EndPacket();
            MatrixDrive_PopMatrix();
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/wireLetter", DispWireString);

inline void ChangeColorWireString(int a0, int a1, int a2)
{
    D_004EE5A0[0] = a0;
    D_004EE5A0[1] = a1;
    D_004EE5A0[2] = a2;
}

void DefaultColorWireString(void)
{
    int new_var;
    new_var = D_004EE590[1];
    D_004EE5A0[0] = D_004EE590[0];
    D_004EE5A0[1] = new_var;
    D_004EE5A0[2] = D_004EE590[2];
}
