#include "common.h"

extern void gif_MakeSprite(int a0, int a1, int a2, int a3, int a4, int a5);
extern void gif_SetGsReg(int a0, long long a1);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gsb_KeepFrameBuffer(int a0);
extern void gif_MakeLine2DOffset(void *a0, int a1, void *a2, void *a3, int a4);

typedef struct Q16 {
    char b[16];
} Q16;

extern int D_004C2220[];
extern Q16 D_00612D10;
extern Q16 D_00612D20;
extern int D_0062B978;

void copyToWork2(void) {
    Q16 q;
    Q16 a;
    Q16 b;
    int uninit;
    *(volatile int *)&q = uninit;
    gif_MakeSprite(D_004C2220[0], 0, 0x100, 0x80, 0, 0);
    gif_SetGsReg(6, D_004C2220[1] | 0x20010000 | ((long long)0xB000 << 21));
    gif_SetGsReg(0x14, 0x60);
    gif_SetAlpha(1, 4, 0);
    gif_SetZTest(0);
    gsb_KeepFrameBuffer(0);
    a = D_00612D10;
    b = D_00612D20;
    gif_MakeLine2DOffset(&a, 0, &b, &D_0062B978, 0);
}
